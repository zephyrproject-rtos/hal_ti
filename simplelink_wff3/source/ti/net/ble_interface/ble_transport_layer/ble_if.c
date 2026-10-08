/*****************************************************************************

 FILENAME:       ble_if.c

 DESCRIPTION:    implements the BLE host-controller interface

 AUTHOR:         Guy M.
 Copyright (c) 2022 Texas Instruments Inc.
 All Rights Reserved This program is the confidential and proprietary
 product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
 transfer of this program is strictly prohibited.

 *****************************************************************************/
#include "ble_if.h"
#include "ble_transport.h"
#include "hci_transport.h"
#include "uart_hci.h"
#include "osi_type.h"
#include "osi_kernel.h"
#include "control_cmd_fw.h"
#ifdef CC35XX
#include <third_party/psa_crypto/include/psa/crypto.h>
#include <third_party/psa_crypto/include/psa/crypto_types.h>
#include <third_party/psa_crypto/include/psa/crypto_values.h>
#endif

/*****************************************************************************/
/* DEFINITIONS & GLOBALS                                                     */
/*****************************************************************************/
ble_if_cb_t bleIfCb;
OsiSyncObj_t bleInitEventSyncObj;
vsFormat_e vsFormat = VENDOR_SPECIFIC_FORMAT_TI;
#define HCI_EVENT_HDR_LEN 3
#define HCI_VE_HDR_LEN 5
#define HCI_VE_EVENT_CODE 0xFF
#define HCI_VE_BLE_INIT_DONE 0x2A04
#define HCI_COMMAND_COMPLETE_EVENT_CODE 0x0E

/*****************************************************************************/
/* IMPLEMENTATION                                                            */
/*****************************************************************************/
int BleIf_OpenTransport()
{
#ifdef CC33XX
    if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_BLE) == FALSE)
    {
        //Open the UART for HCI
        UartHciOpen();

        //Initialize the HCI transport
        HciTransport_Init(HCI_TRANSPORT_UART_BLE, &uartForHci);
    }

    //Register callbacks
    bleIfCb.cmd_cb = HciTransport_WriteHciPacketToCtrl;
    bleIfCb.event_cb_reg = HciTransport_HciRxCallbackbRegister;

    Report("\n\rBLE Serial transport opened\r\n");
#endif
#ifdef CC35XX
    //Note: shared transport was previously opened when WLAN started
    //It will not be opened here

    //Register callbacks
    bleIfCb.cmd_cb = BleTransport_SendCommand;
    bleIfCb.event_cb_reg = BleTransport_EventCallbackbRegister;

    Report("\n\rBLE Shared transport opened\r\n");
#endif

    return 0;
}

int BleIf_CloseTransport()
{
#ifdef CC33XX
    if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_BLE) == TRUE)
    {
        //Close the UART for HCI
        UartHciClose();

        //Release the HCI transport
        HciTransport_Release(HCI_TRANSPORT_UART_BLE);
    }
#endif

    //Note: shared transport was previously opened when WLAN started
    //It will not be closed here

    //Clear registered callbacks
    bleIfCb.cmd_cb = NULL;
    bleIfCb.event_cb_reg = NULL;

    return 0;
}

int BleIf_SendCommand(uint8_t* cmd, uint16_t cmdLen)
{
    return bleIfCb.cmd_cb(cmd, cmdLen);
}

int BleIf_EventCbRegister(ble_event_cb_t cb)
{
    if (cb == NULL)
    {
        return (-1);
    }

    bleIfCb.event_cb_reg(cb);
    return 0;
}

int BleIf_VendorSpecificEventFormat(vsFormat_e format)
{
    if ((format != VENDOR_SPECIFIC_FORMAT_TI) && (format != VENDOR_SPECIFIC_FORMAT_NIMBLE))
    {
        return (-1);
    }

    vsFormat = format;
    return 0;
}

int BleIf_VendorSpecificEventHandler(uint8_t* data, uint16_t *len)
{
    uint8_t eventCode = data[1];
    uint16_t eventOpcode = (data[4] << 8) | data[3];

    if (eventCode == HCI_VE_EVENT_CODE)
    {
        //handle BLE init done event
        if (eventOpcode == HCI_VE_BLE_INIT_DONE)
        {
            osi_SyncObjSignal(&bleInitEventSyncObj);
            return TRUE;
        }

        //check the vendor specific format and convert if needed
        if (vsFormat == VENDOR_SPECIFIC_FORMAT_NIMBLE)
        {
            /***********************
            TI Vendor Specific Event:
            [0] = 0x04 (packet type)
            [1] = 0xFF (vendor specific)
            [2] = param_len (5 + return parameters length)
            [3] = event opcode LSB
            [4] = event opcode MSB
            [5] = status
            [6] = command opcode LSB
            [7] = command opcode MSB
            [8+] = return parameters

            Standard Command Complete Event:
            [0] = 0x04 (packet type)
            [1] = 0x0E (command complete)
            [2] = param_len (4 + return parameters length)
            [3] = num HCI cmd packets (1)
            [4] = command opcode LSB
            [5] = command opcode MSB
            [6] = status
            [7+] = return parameters
            *************************/

            uint8_t origParamLen = data[2];
            uint8_t status = data[5];
            uint8_t cmdOpcodeLsb = data[6];
            uint8_t cmdOpcodeMsb = data[7];
            uint8_t retParamsLen = origParamLen - HCI_VE_HDR_LEN;

            data[1] = HCI_COMMAND_COMPLETE_EVENT_CODE; //command complete opcode
            data[2] = origParamLen - 1; //parameters length
            data[3] = 1; //num of HCI command packets
            data[4] = cmdOpcodeLsb; //command opcode LSB
            data[5] = cmdOpcodeMsb; //command opcode MSB
            data[6] = status; //status
            if (retParamsLen > 0) //return parameters
            {
                os_memmove(&data[7], &data[8], retParamsLen);
            }

            //update packet length: header (3 bytes) + param_len
            *len = HCI_EVENT_HDR_LEN + data[2];
        }
    }

    return FALSE;
}

int BleIf_EnableBLE()
{
    int ret = 0;
    int status = 0;

    ret = osi_SyncObjCreate(&bleInitEventSyncObj);
    if(ret != 0)
    {
        Report("\n\rBleIf_EnableBLE: Failed to create sync object. error number %d", ret);
        ASSERT_GENERAL(0);
    }

#ifdef CC35XX
    ret = BleIf_SetSeed(MAX_SEED_SIZE);
    if (ret < 0)
    {
        Report("\n\rBleIf_EnableBLE: Failed to set initial seed. error number: %d", ret);
        ASSERT_GENERAL(0);
    }
#endif

    //Send BLE enable command to the controller
    ret = ctrlCmdFw_EnableBLECmd();

    if (ret < 0)
    {
        Report("\n\rBleIf_EnableBLE: Failed to enable BLE. error number: %d", ret);
        ASSERT_GENERAL(0);
    }

    //Wait for the controller to be enabled before starting host
    Report("\n\r-------------- Wait for BLE Controller");

    ret = osi_SyncObjWait(&bleInitEventSyncObj, OSI_WAIT_FOR_SECOND);
    if (OSI_OK != ret)
    {
        Report("\n\rBleIf_EnableBLE: Failed to receive BLE Init Done. error number %d", ret);
        Report("\n\rBleIf_EnableBLE: Check if BLE is supported and enabled in INI file and try again.");
        status = -1;
    }

    ret = osi_SyncObjDelete(&bleInitEventSyncObj);
    if (OSI_OK != ret)
    {
        Report("\n\rBleIf_EnableBLE: Failed to delete sync object. error number %d", ret);
        ASSERT_GENERAL(0);
    }

    return status;
}

int BleIf_SetBdAddr(const unsigned char *pBdAddr)
{
    return ctrlCmdFw_SetBdAddrCmd(pBdAddr);
}

int BleIf_SetSeed(uint8_t size)
{
    int ret = -1;
    uint8_t seed[MAX_SEED_SIZE] = {0};

    //Validate seed size
    if (size > MAX_SEED_SIZE)
    {
        Report("\n\rBleIf_SetSeed: seed size exceeded");
        return ret;
    }

#ifdef CC35XX
    //Check crypto engine status
    psa_status_t status  = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        Report("\n\rBleIf_SetSeed: Crypto is not initialized: %d", status);
        return ret;
    }

    //Get new seed from HSM
    status = psa_generate_random(seed, size);
    if (status != PSA_SUCCESS) {
        Report("\n\rBleIf_SetSeed: Failed to get initial seed. error number: %d", status);
        return ret;
    }
#endif

    //Send set initial seed to the controller
    return ctrlCmdFw_SetSeedCmd(seed, size);
}
