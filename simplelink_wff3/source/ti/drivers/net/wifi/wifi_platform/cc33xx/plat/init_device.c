/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "init_device.h"
#include <wlan_irq_adapt.h>
#include <fw_event_if.h>
#include "commands.h"
#include "macro_utils.h"
#include "bus_if.h"
#include "wlan_if.h"
#include "errors.h"
#include <upper_mac_versions.h>

extern int  ctrlCmdFw_DownloadIniParams();
extern int  ctrlCmdFw_GetCmdSize();
extern int WLSendFWDownloadCommand(void *cmd, uint32_t len, void *out,uint32_t outLen);
extern int16_t CME_SetMacAddress(uint32_t roleType, uint8_t *pMacAddress);

int ctrlCmdBtl_get_device_info_cmd(void* pgDevInfo);
static inline uint64_t mac_addr_to_u64(uint8_t *addr);
static inline void u64_to_mac_addr(uint64_t u, uint8_t *addr);
static void inc_mac_addr(uint8_t* pMacAddr);
int WLSendFWGetDeviceInfoCommand( void *out,uint32_t outLen);
static void set_device_fuse_mac_addr(device_info_t pgDevInfo);


extern device_info_t gDevice_info;
extern uint8_t g_fuse_mac_addr[6][MAC_ADDRESS_LEN];


#define CHUNK_SIZE (128*6)
#define RECORD_MAGIC_NUM (0xB007C0DE)


#define LIST_SIZE_OFFSET (52U) //parameter of manifest container
#define RECORD_SUFFIX_SIZE (82U) //parameter of manifest container
#define DNLD_PRINT_PERIODICITY (10)

/******************************************************************************
                                FUNCTION 
******************************************************************************/

typedef struct
{
    uint32_t magicNum;
    uint16_t type;
    uint8_t  sn;
    uint8_t  digestType;
    uint32_t len;
}recordHeader_t;


int NumOfRecordOffset(char *containerName)
{
    FILE *containerFileHandle;
    uint8_t buffer1;
    uint16_t buffer2;
    uint16_t target_device_list_size;
    uint16_t num_of_records_offset;


    containerFileHandle = osi_fopen(containerName, "rb");
    if(!containerFileHandle)
    {
        Report("\n\rError !! failed to open file: %s\n\r", containerName);
    }

    osi_fread(&buffer1, sizeof(uint8_t), LIST_SIZE_OFFSET, containerFileHandle);
    target_device_list_size = (uint16_t)buffer1 * 8;

    osi_fread(&buffer2, sizeof(uint16_t), target_device_list_size + RECORD_SUFFIX_SIZE + LIST_SIZE_OFFSET, containerFileHandle);
    num_of_records_offset = buffer2;


    osi_fclose(containerFileHandle);

    return (int32_t)(uint16_t)num_of_records_offset;
}



int ctrlCmdFw_ContainerDownload(char *containerName)
{
    char *buffer;
    FILE *containerFileHandle;
    recordHeader_t *header;
    uint32_t offset = 0;
    uint32_t currentRecordLength;
    uint32_t offsetInRecord;
    int32_t ret = 0;
    Bool_e isLastRecord = FALSE;
    uint32_t recordCounter = 0;
    uint32_t numOfRecords = 0;
    uint8_t printPeriod=0;
    uint32_t cmdSize = ctrlCmdFw_GetCmdSize();

    buffer = os_malloc( CHUNK_SIZE + cmdSize);

    if(NULL == buffer)
    {
        Report("\n\rcouldn't allocate for record download\n\r");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__CMD_CTRL, WLAN_ERROR_TYPE__MALLOC);
    }
    containerFileHandle = osi_fopen(containerName, "rb");
    if(!containerFileHandle)
    {
        Report("\n\rError !! failed to open file: %s\n\r", containerName);
		os_free(buffer);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__CMD_CTRL, WLAN_ERROR_TYPE__FOPEN);
    }

    osi_fread(buffer, sizeof(recordHeader_t), offset, containerFileHandle);

    header = (recordHeader_t *)buffer;

    while( RECORD_MAGIC_NUM == header->magicNum )
    {
        // find number of records
        if (0 == recordCounter)
        {
            numOfRecords = NumOfRecordOffset(containerName);
        }

        currentRecordLength = sizeof(recordHeader_t) + ALIGNN_TO_4(header->len);
        offsetInRecord = 0;

        //check if last record
        if(recordCounter == numOfRecords - 1)
        {
            isLastRecord = TRUE;
        }

        recordCounter++;


        // read chunks from flash
        while((currentRecordLength / CHUNK_SIZE) != 0)
        {
            osi_fread(buffer + cmdSize, CHUNK_SIZE, offset + offsetInRecord, containerFileHandle);

            //write to device
            printPeriod++;
            if(printPeriod == DNLD_PRINT_PERIODICITY)
            {
                // Report("\n\rDnld offset : %d -%d-%d", recordCounter,offset + offsetInRecord, CHUNK_SIZE);
                printPeriod = 0;
            }
            ret = WLSendFWDownloadCommand(buffer, CHUNK_SIZE, NULL, 0);
            //If there was an issue in one of the chunks- return error
            if (ret < 0)
            {
                osi_fclose(containerFileHandle);
                os_free(buffer);
                return ret;
            }
            currentRecordLength -= CHUNK_SIZE;
            offsetInRecord += CHUNK_SIZE;
        }

        if(currentRecordLength)
        {
            osi_fread(buffer + cmdSize, currentRecordLength, offset + offsetInRecord, containerFileHandle);

            /* ---------------------------------------------------------------------------------------------------------
             * 30/01/23, OSPREY_LDB-1212: RAM BM download bug workaround:
             * For each container chunk, ROM BM sends CMD_COMPLETE with core status.
             * Once the last RAM BM container chunk is sent, ROM BM sends CMD_COMPLETE, cleans SPI interface
             * and invokes RAM BM. This may cause the host to read a faulty core status if it is read after it
             * has been cleaned.
             * In order to fix this, we ignore the last CMD_COMPLETE by reducing the timeout and disabling interrupts
             * before sending the last chunk, and re-enabling them afterwards.
             * --------------------------------------------------------------------------------------------------------- */
            if (isLastRecord && (0 == os_strcmp("rambtlr",containerName)))
            {
                /* Set timeout of command complete to 100 ms and disable interrupts. */
                cmd_SetTimeoutMs(100);
                wlan_IRQDisableInt();
            }

            //write to device
            printPeriod++;
            if(printPeriod == DNLD_PRINT_PERIODICITY)
            {
                // Report("\n\rDnld : %d -%d-%d", recordCounter,offset + offsetInRecord, currentRecordLength);
                printPeriod = 0;
            }
            //We expect for timeout to be returned and ignoring it
            ret = WLSendFWDownloadCommand(buffer, currentRecordLength, NULL, 0);
            if (WLAN_RET_TIMEOUT == ret)
            {
                ret = 0;
            }

            if (isLastRecord && (0 == os_strcmp("rambtlr",containerName)))
            {
                cmd_SetTimeoutMs(0);
                wlan_IRQEnableInt();
            }
            offsetInRecord += currentRecordLength;
        }

        offset = offset + offsetInRecord;

        osi_fread(buffer , sizeof(recordHeader_t), offset, containerFileHandle);

        header = (recordHeader_t *)buffer;
    }

    osi_fclose(containerFileHandle);
    os_free(buffer);

    return ret;
}

/******************************************************************************

    NAME:           init_device

    PROTOTYPE:      init_device_adapt.h

    DESCRIPTION:    Device initialize

    CALLER:         InitHostDriver

    RETURNS:        NONE
******************************************************************************/
int32_t init_device(uint32_t commandsEventsSizeBTL,uint32_t commandsEventsSize)
{
    int32_t ret = 0;

    Report("getting device info.....\r\n");
    ctrlCmdBtl_get_device_info_cmd(&gDevice_info);

    //set real fuse mac address
    set_device_fuse_mac_addr(gDevice_info);

    fwEvent_SetDuringInit(TRUE, commandsEventsSizeBTL);

    // start downloading the RAM btlr and FW
    Report("\n\rStarting software download.....");

    // we need to wait so the LX device will wake up
    if(fwEvent_Wait(OSI_WAIT_FOR_SECOND * 2,HINT_ROM_LOADER_INIT_COMPLETE) == -1)
    {
        Report("\n\rSoftware download ! didn't receive HINT_ROM_LOADER_INIT_COMPLETE \n");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__ROM_LOADER_INIT);
    }

    Report("\n\r-------------- Download RAM-BTL");

    // RAM Bootloader download
    ret = ctrlCmdFw_ContainerDownload("rambtlr");
    if(ret != OSI_OK)
    {
        Report("\n\rctrlCmdFw_ContainerDownload FAILED to download rambtlr");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__ROM_LOADER_INIT);
    }

    Report("\n\r-------------- Wait for RAM BTL UP");

    if(fwEvent_Wait(OSI_WAIT_FOR_SECOND * 2, HINT_SECOND_LOADER_INIT_COMPLETE) == -1)
    {
        Report("\n\rdidn't receive RAM HINT_SECOND_LOADER_INIT_COMPLETE");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__RAM_LOADER_INIT);
    }

    Report("\n\r-------------- Download FW\n\r");

    // FW download
    ret = ctrlCmdFw_ContainerDownload("fw");
    if(ret != OSI_OK)
    {
        Report("\n\rctrlCmdFw_ContainerDownload FAILED to download fw");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__RAM_LOADER_INIT);
    }

    Report("-------------- Wait for FW UP\n\r");
    if(fwEvent_Wait(OSI_WAIT_FOR_SECOND * 2, HINT_FW_WAKEUP_COMPLETE) == -1)
    {
        Report("\n\rdidn't receive HINT_FW_WAKEUP_COMPLETE");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__WSOC_FW_INIT);
    }


    Report("-------------- Download IniParams");

    // Download ini File Params
    ret = ctrlCmdFw_DownloadIniParams();
    if(ret != OSI_OK)
    {
        Report("\n\rctrlCmdFw_DownloadIniParams FAILED to download fw");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__WSOC_FW_INIT);
    }

    Report("\n\r-------------- Wait for IniParams complete\n\r");
    if(fwEvent_Wait(OSI_WAIT_FOR_SECOND * 2, HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE) == -1)
    {
        Report("\n\rdidn't receive HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE");
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__INI_PARAMS_INIT);
    }
    fwEvent_SetDuringInit(FALSE,commandsEventsSize);

    return ret;
}


/******************************************************************************

    NAME:           deinit_device

    PROTOTYPE:      init_device_adapt.h

    DESCRIPTION:    Device deinitialize

    CALLER:

    RETURNS:        NONE
******************************************************************************/
int32_t Deinit_device(void)
{
    int32_t ret = 0;

    return ret;
}
/******************************************************************************

    NAME:           HwInit

    PROTOTYPE:      init_device_adapt.h

    DESCRIPTION:    Hardware initialize

    CALLER:         InitHostDriver

    RETURNS:        NONE
******************************************************************************/
int32_t HwInit(void)
{
    int32_t ret = 0;

    /* disable the IRQ interrupt */
    wlan_IRQDisableInt();

    /* make sure the device is turned off */
    wlan_TurnOffWlan();

    /* turn on the device */
    wlan_TurnOnWlan();

    /* enable the IRQ interrupt only if needed in some platforms*/
    //wlan_IRQEnableInt();

    return ret;
}


/******************************************************************************

    NAME:           DeHwInit

    PROTOTYPE:      init_device_adapt.h

    DESCRIPTION:    Hardware deinitialize

    CALLER:

    RETURNS:        NONE
******************************************************************************/
int32_t DeHwInit(void)
{
    int32_t ret = 0;

    bus_Send_deInit();
    wlan_IRQDeinit();

    /* in some platform bus driver de init should be called here */
    //deinit_spi()
    //deinit_sdio()

    return ret;
}

/******************************************************************************

    NAME:           get_device_info

    PROTOTYPE:      init

    DESCRIPTION:    read fw address from bootloader

    RETURNS:
******************************************************************************/
int ctrlCmdBtl_get_device_info_cmd(void* pgDevInfo)
{
    int ret;
    union hw_info hw_info;
    uint64_t mac_address;
    device_info_t* pDevInfo = pgDevInfo;
    int i;

    uint8_t oui_laa_bit = BIT(1);

    ret = WLSendFWGetDeviceInfoCommand( &hw_info, sizeof(hw_info));
    if (ret < 0)
        return ret;

    pDevInfo->struct_is_updateed = 1;

    mac_address = hw_info.bitmap.mac_address;

    pDevInfo->udi = hw_info.bitmap.udi;
    pDevInfo->pg_version = hw_info.bitmap.pg_version;
    pDevInfo->metal_version = hw_info.bitmap.metal_version;
    pDevInfo->boot_rom_version = hw_info.bitmap.boot_rom_version;
    pDevInfo->fuse_rom_structure_version = hw_info.bitmap.fuse_rom_structure_version;
    pDevInfo->device_part_number = hw_info.bitmap.device_part_number;
    pDevInfo->disable_5g = hw_info.bitmap.disable_5g;
    pDevInfo->disable_6g = hw_info.bitmap.disable_6g;
    pDevInfo->disable_ble = hw_info.bitmap.disable_ble;

    pDevInfo->mac_address[0][5] = (uint8_t) (mac_address);
    pDevInfo->mac_address[0][4] = (uint8_t) (mac_address >> 8);
    pDevInfo->mac_address[0][3] = (uint8_t) (mac_address >> 16);
    pDevInfo->mac_address[0][2] = (uint8_t) (mac_address >> 24);
    pDevInfo->mac_address[0][1] = (uint8_t) (mac_address >> 32);
    pDevInfo->mac_address[0][0] = (uint8_t) (mac_address >> 40);

    //mac address 2 is mac_address_1 + 1
    memcpy(pDevInfo->mac_address[1],pDevInfo->mac_address[0],MAC_ADDRESS_LEN);
    memcpy(pDevInfo->mac_address[2],pDevInfo->mac_address[0],MAC_ADDRESS_LEN);
    memcpy(pDevInfo->mac_address[3],pDevInfo->mac_address[0],MAC_ADDRESS_LEN);

    //flip the second bit
    pDevInfo->mac_address[1][0] |= oui_laa_bit;
    pDevInfo->mac_address[2][0] |= oui_laa_bit;

    //increase mac_address 2 in 1.
    inc_mac_addr(pDevInfo->mac_address[2]);

    //increase mac_address 3 in 1.
    inc_mac_addr(pDevInfo->mac_address[3]);

    Report("------");
    Report("\n\rCC33XX device info: "
        "\n\rPG version: %u"
        "\n\rMetal version: %u"
        "\n\rBoot ROM version: %u ",
        pDevInfo->pg_version,
        pDevInfo->metal_version,
        pDevInfo->boot_rom_version);

    Report(
        "\n\rFuse_rom_structure_version: %u"
        "\n\rDevice part number: %u",
        pDevInfo->fuse_rom_structure_version,
        pDevInfo->device_part_number);

    // Print the host version
    Report("\n\rHost version: %s", &version_upper_mac[VERSION_NUMBER_START_INDEX]);

    for(i=0;i<WLAN_MAX_MAC_ADDRESSES; i++)
    {
        Report("\n\rFW MAC address: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x",
        pDevInfo->mac_address[i][0],
        pDevInfo->mac_address[i][1],
        pDevInfo->mac_address[i][2],
        pDevInfo->mac_address[i][3],
        pDevInfo->mac_address[i][4],
        pDevInfo->mac_address[i][5]);

    }
    
    Report("\n\r------");

    return 0;
}
static inline uint64_t mac_addr_to_u64(uint8_t *addr)
{
   uint64_t u = 0;
   int8_t i;

   for (i = 0; i < MAC_ADDRESS_LEN; i++)
       u = u << 8 | addr[i];

   return u;
}
static inline void u64_to_mac_addr(uint64_t u, uint8_t *addr)
{
   int8_t i;

   for (i = MAC_ADDRESS_LEN - 1; i >= 0; i--) {
       addr[i] = u & 0xff;
       u = u >> 8;
   }
}
static void inc_mac_addr(uint8_t* pMacAddr)
{
    uint64_t mac64;


    mac64 = mac_addr_to_u64(pMacAddr);
    mac64++;
    u64_to_mac_addr(mac64, pMacAddr);
}

/******************************************************************************

    NAME:           set_device_fuse_mac_addr

    PROTOTYPE:      init

    DESCRIPTION:    set device fuce mac address

    RETURNS:
******************************************************************************/
static void set_device_fuse_mac_addr(device_info_t pgDevInfo)
{
    WlanMacAddress_t macAddressParams;
    memset(&macAddressParams, 0, sizeof(WlanMacAddress_t));
    const uint8 address2[MAC_ADDRESS_LEN] = {0};

    //set sta mac address
    if(!os_memcmp(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA]), address2, MAC_ADDRESS_LEN))
    {
        macAddressParams.roleType = WLAN_ROLE_STA;
        os_memcpy(macAddressParams.pMacAddress, pgDevInfo.mac_address[0], MAC_ADDRESS_LEN);
        Wlan_Set(WLAN_SET_MACADDRESS, &macAddressParams);
    }

    //set ap mac address
    if(!os_memcmp(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP]), address2, MAC_ADDRESS_LEN))
    {
        macAddressParams.roleType = WLAN_ROLE_AP;
        os_memcpy(macAddressParams.pMacAddress, pgDevInfo.mac_address[3], MAC_ADDRESS_LEN);
        Wlan_Set(WLAN_SET_MACADDRESS, &macAddressParams);
    }

    //set device mac address
    if(!os_memcmp(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE]), address2, MAC_ADDRESS_LEN))
    {
        macAddressParams.roleType = WLAN_ROLE_DEVICE;
        os_memcpy(macAddressParams.pMacAddress, pgDevInfo.mac_address[2], MAC_ADDRESS_LEN);
        Wlan_Set(WLAN_SET_MACADDRESS, &macAddressParams);
    }

    //set ble mac address
    if(!os_memcmp(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_BLE]), address2, MAC_ADDRESS_LEN))
    {
        macAddressParams.roleType = WLAN_ROLE_IBSS; //BLE role, we do not have role type BLE so we use this
        os_memcpy(macAddressParams.pMacAddress, pgDevInfo.mac_address[1], MAC_ADDRESS_LEN);
        Wlan_Set(WLAN_SET_MACADDRESS, &macAddressParams);
    }

}
