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
#include "wlan_if.h"
#include <ti/drivers/Power.h>

typedef struct __PACKED__
{
    uint8   role_id;
    uint8   macAddress[MAC_ADDRESS_LEN];
    uint8   padding[1];
} Macaddress_t;

typedef struct
{
    uint32_t magicNum;
    uint16_t type;
    uint16_t reserved;
    uint32_t len;
}recordHeader_t;

extern uint8_t g_fuse_mac_addr[6][MAC_ADDRESS_LEN];

int get_device_mac_address();
static inline uint64_t mac_addr_to_u64(uint8_t *addr);
static inline void u64_to_mac_addr(uint64_t u, uint8_t *addr);
static void inc_mac_addr(uint8_t* pMacAddr);
extern int  ctrlCmdFw_DownloadIniParams();
extern int  ctrlCmdFw_FirstCommand();
extern int  ctrlCmdFw_GetCmdSize();
extern int  WLSendFWDownloadCommand(void *cmd, uint32_t len, void *out,uint32_t outLen);
extern int  ctrlCmdFw_GetMacAddress(Macaddress_t* macaddress);


#define CHUNK_SIZE (600)
#define RECORD_MAGIC_NUM (0x690c47c2)
#define RECORD_MAGIC_NUM_ALT (0x96f3b83d)

#define LIST_SIZE_OFFSET (18) //offset of numberOf records in the manifest
#define RECORD_SUFFIX_SIZE (82U) //parameter of manifest container


/******************************************************************************
                                FUNCTION 
******************************************************************************/

/******************************************************************************

    NAME:           init_device

    PROTOTYPE:      init_device_adapt.h

    DESCRIPTION:    Device initialize

    CALLER:         InitHostDriver

    RETURNS:        NONE
******************************************************************************/

int NumOfRecordOffset(char *containerName , recordHeader_t *pHeader)
{
    FILE *containerFileHandle;
    uint16 buffer;
    uint16 target_device_list_size;
    uint16 num_of_records_offset;

    //buffer = os_malloc(CHUNK_SIZE + sizeof(cmd_download_t));


    containerFileHandle = osi_fopen(containerName, "rb");
    osi_fread(&buffer, sizeof(uint16_t), LIST_SIZE_OFFSET, containerFileHandle);
    num_of_records_offset = buffer;

    osi_fclose(containerFileHandle);

    return num_of_records_offset;
}



int ctrlCmdFw_ContainerDownload(char *containerName)
{
    char *buffer;
    FILE *containerFileHandle;
    recordHeader_t *header;
    uint32_t offset = 0;
    uint32_t currentRecordLength, writeRecordLen;
    uint32_t offsetInRecord;
    int ret;
    Bool_e isLastRecord = FALSE;
    uint32_t recordCounter = 0;
    uint32_t numOfRecords = 0;
    uint32_t cmdSize = ctrlCmdFw_GetCmdSize();

    buffer = os_malloc(CHUNK_SIZE + cmdSize);

    if(NULL == buffer)
    {
        Report("\n\rcouldn't allocate for record download\n\r");
        ASSERT_GENERAL(0);
    }
    containerFileHandle = osi_fopen(containerName, "rb");
    osi_fread(buffer, sizeof(recordHeader_t), offset, containerFileHandle);

    header = (recordHeader_t *)buffer;

    while( (RECORD_MAGIC_NUM == header->magicNum) || (RECORD_MAGIC_NUM_ALT == header->magicNum) )
    {
        // find number of records
        if (0 == recordCounter)
        {
            numOfRecords = NumOfRecordOffset(containerName, header);
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
           // Report("\r\nsending 0x%x 0x%x ends 0x%x 0x%x",(buffer + cmdSize)[0],(buffer + cmdSize)[1],(buffer + cmdSize)[CHUNK_SIZE - 2],(buffer + cmdSize)[CHUNK_SIZE - 1]);
           // Report(" offset - %d",offset + offsetInRecord);
            //write to device
            ret = WLSendFWDownloadCommand(buffer, CHUNK_SIZE, NULL, 0);
            currentRecordLength -= CHUNK_SIZE;
            offsetInRecord += CHUNK_SIZE;
        }

        if(currentRecordLength)
        {
            osi_fread(buffer + cmdSize, currentRecordLength, offset + offsetInRecord, containerFileHandle);
          //  Report("\r\nsending 0x%x 0x%x ends 0x%x 0x%x",(buffer + cmdSize)[0],(buffer + cmdSize)[1],(buffer + cmdSize)[currentRecordLength - 2],(buffer + cmdSize)[currentRecordLength - 1]);
          //  Report(" offset - %d",offset + offsetInRecord);
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
            ret = WLSendFWDownloadCommand(buffer, currentRecordLength, NULL, 0);

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
    return 0;
}


int32_t init_device(uint32_t commandsEventsSizeBTL,uint32_t commandsEventsSize)
{
    int ret = 0;

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    fwEvent_SetDuringInit(1,commandsEventsSize);

    /* start downloading the RAM btlr and FW */
    Report("\n\rStarting software download.....\r\n");

    /* we need to wait so the LX device will wake up */
    if(fwEvent_Wait(OSI_WAIT_FOREVER,HINT_ROM_LOADER_INIT_COMPLETE) == -1)
    {
        Report("didn't receive ROM init complete\n\r");
        //ASSERT_GENERAL(0);
        while(1);
    }

    Report("\n\rreceived ROM init complete.....\r\n");

    // RAM Bootloader download
    ctrlCmdFw_ContainerDownload("fw");

    /* we need to wait so the LX device will wake up */
    if(fwEvent_Wait(OSI_WAIT_FOREVER,HINT_FW_WAKEUP_COMPLETE) == -1)
    {
        Report("didn't receive ROM init complete");
        //ASSERT_GENERAL(0);
        while(1);
    }

    fwEvent_SetDuringInit(0,commandsEventsSize);

    Report("-------------- Download First CMD\n\r");
    // download first comand
    // Note: ! Must come before ini !
    ctrlCmdFw_FirstCommand();

    Report("-------------- Download IniParams\n\r");

    // Download ini File Params
    ctrlCmdFw_DownloadIniParams();

    Report("-------------- Wait for IniParams complete\n\r");
    if(fwEvent_Wait(OSI_WAIT_FOREVER,HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE) == -1)
    {
        Report("didn't receive HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE\n\r");
        while(1);
    }

#if 0
    /* same command size fro BTL and Stack*/
    fwEvent_set_cmdEventSize(commandsEventsSize);
#endif

    get_device_mac_address();

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
    
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
    int ret = 0;

    /* to be coded when need deinit device functions */

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
    int ret = 0;

    /* make sure the device is turned off */
    wlan_TurnOffWlan();

    /* disable the IRQ interrupt */
    wlan_IRQDisableInt();

    /* turn on the device */
    wlan_TurnOnWlan();

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
    int ret = 0;

    wlan_IRQDeinit();

    return ret;
}

/******************************************************************************/
static inline uint64_t mac_addr_to_u64(uint8_t *addr)
{
   uint64_t u = 0;
   int8_t i;

   for (i = 0; i < MAC_ADDRESS_LEN; i++)
       u = u << 8 | addr[i];

   return u;
}

static void inc_mac_addr(uint8_t* pMacAddr)
{
    uint64_t mac64;


    mac64 = mac_addr_to_u64(pMacAddr);
    mac64++;
    u64_to_mac_addr(mac64, pMacAddr);
}

static inline void u64_to_mac_addr(uint64_t u, uint8_t *addr)
{
   int8_t i;

   for (i = MAC_ADDRESS_LEN - 1; i >= 0; i--) {
       addr[i] = u & 0xff;
       u = u >> 8;
   }
}
/******************************************************************************

    NAME:           get_device_mac_address

    PROTOTYPE:      init

    DESCRIPTION:    get device fw mac address

******************************************************************************/
int get_device_mac_address()
{
    int ret = 0;
    Macaddress_t macaddress;
    uint8_t oui_laa_bit = BIT(1);

    macaddress.role_id = WLAN_ROLE_STA;
    ret = ctrlCmdFw_GetMacAddress(&macaddress);
    if (ret < 0)
    {
        return ret;
    }

    //get mac address 0
    memcpy(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA]),macaddress.macAddress,MAC_ADDRESS_LEN);

    //mac address 2 is mac_address_1 + 1
    memcpy(&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_BLE]),&(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA]),MAC_ADDRESS_LEN);
    memcpy(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE],g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA],MAC_ADDRESS_LEN);
    memcpy(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP],g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_STA],MAC_ADDRESS_LEN);

    //flip the second bit
    g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_BLE][0] |= oui_laa_bit;
    g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE][0] |= oui_laa_bit;

    //increase mac_address 2 in 1.
    inc_mac_addr(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_DEVICE]);

    //increase mac_address 3 in 1.
    inc_mac_addr(g_fuse_mac_addr[WLAN_MAC_OFFSET_ROLE_AP]);


    return 0;
}

