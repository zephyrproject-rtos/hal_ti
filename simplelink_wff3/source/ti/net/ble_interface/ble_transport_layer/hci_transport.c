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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <osi_kernel.h>
#include <hci_transport.h>
#include "wlan_if.h"
#include "host_event_if.h"

//*****************************************************************************
//                          LOCAL DEFINES
//*****************************************************************************
// HCI Packet Types
#define HCI_CMD_PACKET                                    0x01        //!< Command Packet
#define HCI_ACL_DATA_PACKET                               0x02        //!< ACL Data Packet (2 bytes length)
#define HCI_SCO_DATA_PACKET                               0x03        //!< SCO Data Packet
#define HCI_EVENT_PACKET                                  0x04        //!< Event Packet
#define HCI_EXTENDED_EVENT_PACKET                         0x05        //!< Extended Event Packet   (2 bytes length)
#define HCI_EXTENDED_CMD_PACKET                           0x09        //!< Extended Command Packet (2 bytes length)
#define HCI_VENDOR_EVENT_PACKET                           0xFF        //!< Vendor Event Packet

//HCI MAX Lengths
#define HCI_MAX_PAYLOAD_LEN                               255
#define HCI_MAX_HEADER_LEN                                5
#define HCI_MAX_PKT_LEN                                   HCI_MAX_HEADER_LEN + HCI_MAX_PAYLOAD_LEN

//HCI Header Length
#define HCI_EVENT_PKT_HDR_LEN                             3
#define HCI_EXT_EVENT_PKT_HDR_LEN                         4
#define HCI_CMD_PKT_HDR_LEN                               4
#define HCI_EXT_CMD_PKT_HDR_LEN                           5
#define HCI_DATA_PKT_HDR_LEN                              5

//HCI Header Bytes Location
#define HCI_PKT_TYPE_BYTE                                 1
#define HCI_EVENT_HDR_LEN_BYTE                            2
#define HCI_EVENT_HDR_DATA_BYTE                           3
#define HCI_EXT_EVENT_HDR_DATA_BYTE                       4
#define HCI_CMD_HDR_LEN_BYTE                              3
#define HCI_CMD_HDR_DATA_BYTE                             4
#define HCI_EXT_CMD_HDR_DATA_BYTE                         5
#define HCI_DATA_HDR_LEN_BYTE1                            3
#define HCI_DATA_HDR_LEN_BYTE2                            4
#define HCI_DATA_HDR_DATA_BYTE                            5

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

//*****************************************************************************
//                          LOCAL VARIABLES
//*****************************************************************************
hciTransport_t g_pTransport[HCI_TRANSPORT_NUM_INSTANCES];

//*****************************************************************************
//                          GLOBAL VARIABLES
//*****************************************************************************
#define TransportRxCb(instance, buf, len)   g_pTransport[instance].rx_cb(buf, len)
#define TransportRead(instance, buf,len)    g_pTransport[instance].read(buf,len)
#define TransportWrite(instance, buf,len)   g_pTransport[instance].write(buf,len)
#define TransportInitialized(instance)      (g_pTransport[instance].read != NULL && g_pTransport[instance].write != NULL)

//*****************************************************************************
//                          LOCAL FUNCTIONS
//*****************************************************************************


//*****************************************************************************
//
//! HciTransport_WriteHciPacket
//!
//! This function writes a complete HCI packet with any transport
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
static int HciTransport_WriteHciPacket(uint8_t instance, uint8_t* pHciPkt, uint16_t hciPktLen)
{
    if( instance >= HCI_TRANSPORT_NUM_INSTANCES )
    {
        return -1;
    }
    return TransportWrite(instance, pHciPkt, hciPktLen);
}

//*****************************************************************************
//                          HCI THREAD
//*****************************************************************************
/******************************************************************************
THREAD DEFINES
******************************************************************************/
#ifdef CC33XX
#define HCI_THREAD_PRIORITY   (3)
#define NPI_THREAD_PRIORITY   (3)
#else
#define HCI_THREAD_PRIORITY   (6)
#define NPI_THREAD_PRIORITY   (6)
#endif
#define HCI_THRD_STACK_SIZE (2048)

/******************************************************************************
THREAD FUNCTIONS
******************************************************************************/
void HciThread_Entry(void* params);

/******************************************************************************
THREAD VARIABLES
******************************************************************************/
hciThread_t g_pThread[HCI_TRANSPORT_NUM_INSTANCES] =
{
   /*BLE_UART*/  { NULL, "hciThread", HCI_THRD_STACK_SIZE, HCI_THREAD_PRIORITY, HciThread_Entry, HCI_TRANSPORT_UART_BLE, FALSE },
   /*NPI_UART*/  { NULL, "npiThread", HCI_THRD_STACK_SIZE, NPI_THREAD_PRIORITY, HciThread_Entry, HCI_TRANSPORT_UART_NPI, FALSE }
};

#define TransportThreadIsRunning(instance)  g_pThread[instance].threadRunning

/******************************************************************************
THREAD FUNCTIONS
******************************************************************************/
void HciThread_Entry(void* params)
{
    uint8_t* hciPktBuf;
    uint16_t hciPktReadLen = 0;
    uint8_t  threadId;
    WlanEventError_t  error_event;

    if(params == NULL)
    {
        Report("\n\rInvalid parameters\n");
        return;
    }
    Report("\n\rHci_Thread: thrd is running\n");

    // Get instance id
    threadId = *((uint8_t*)params);

    //Mark thread as running
    TransportThreadIsRunning(threadId) = TRUE;

    //Allocate memory for the HCI packet
    //This memory will only be released when thread is destructed
    hciPktBuf = os_malloc(HCI_MAX_PKT_LEN);

    //Initialize the packet before reading it from the transport
    os_memset(hciPktBuf,0,HCI_MAX_PKT_LEN);

    Report("\n\rHci_Thread[%d]: Start Listening...\n", threadId);

    while (TransportThreadIsRunning(threadId))
    {
        if (HciTransport_ReadHciPacket(threadId, hciPktBuf, &hciPktReadLen) == 0)
        {
            if (BleIf_VendorSpecificEventHandler(hciPktBuf, &hciPktReadLen) == 0)
            {
                if(g_pTransport[threadId].rx_cb != NULL)
                {
                    TransportRxCb(threadId, hciPktBuf, hciPktReadLen);
                }
            }
        }
        else
        {
            Report("\n\rHci_Thread[%d]: Failed to HciTransport_ReadHciPacket", threadId);
            error_event.error_num = -1;
            error_event.module = WLAN_MODULE_BLE;
            error_event.severity = WLAN_SEVERITY_MID;
            Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
        }
    }

    Report("\n\rHciThread: Stop Listening...\n");

    //Release the packet memory
    os_free(hciPktBuf);

    Report("\n\rHci_Thread: thrd is stopped\n");
}

int HciThread_Init(uint8_t instance)
{
    OsiReturnVal_e rc = OSI_OK;
    hciThread_t* myThread;

    if( instance >= HCI_TRANSPORT_NUM_INSTANCES )
    {
        Report("\n\r HciThread_Init: ThreadCreate failed !!!");
        return -1;
    }

    myThread = &g_pThread[instance];

    //Create Task
    rc = osi_ThreadCreate(&myThread->threadTcb,            // Thread control block
                          myThread->pThreadName,           // Thread name
                          myThread->stackSize,             // Stack size
                          myThread->priority,              // Thread priority
                          myThread->pEntryFunc,            // Thread entry function
                          &myThread->instance);            // Thread init parameters
    if (OSI_OK != rc)
    {
        Report("\n\r HciThread_Init: ThreadCreate failed !!!");
        return -1;
    }

    return 0;
}

void HciThread_Destruct(uint8_t instance)
{
    OsiReturnVal_e rc = OSI_OK;
    WlanEventError_t  error_event;

    //Delete HCI Thread
    rc = osi_ThreadDelete(&g_pThread[instance].threadTcb);
    if (OSI_OK != rc)
    {
        Report("\n\rHciThread_Destruct[%d]: ThreadDelete failed !!!", instance);
        ASSERT_GENERAL(0);
        error_event.error_num = rc;
        error_event.module = WLAN_MODULE_BLE;
        error_event.severity = WLAN_SEVERITY_MID;
        Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));

    }

    //Mark thread as ended
    TransportThreadIsRunning(instance) = FALSE;
}


//*****************************************************************************
//                          API FUNCTIONS
//*****************************************************************************
//*****************************************************************************
//
//! HciTransport_Init
//!
//! This function initialize the transport layer for HCI
//!
//! \param  pTransport - pointer to
//!
//! \return none
//
//*****************************************************************************
void HciTransport_Init(uint8_t instance, const hciTransport_t* const pTransport)
{
    //Set the transport functions
    if (pTransport != NULL)
    {
        g_pTransport[instance].read = pTransport->read;
        g_pTransport[instance].write = pTransport->write;
        g_pTransport[instance].rx_cb = pTransport->rx_cb;
    }

    //Start the HCI thread in case it is not running
    if (TransportThreadIsRunning(instance) == FALSE)
    {
        HciThread_Init(instance);
    }
}

//*****************************************************************************
//
//! HciTransport_Release
//!
//! This function releases the transport layer for HCI
//!
//! \param  none
//!
//! \return none
//
//*****************************************************************************
void HciTransport_Release(uint8_t instance)
{
    g_pTransport[instance].read = NULL;
    g_pTransport[instance].write = NULL;
    g_pTransport[instance].rx_cb = NULL;
    HciThread_Destruct(instance);
}

//*****************************************************************************
//
//! HciTransport_IsInitialized
//!
//! This function checks if transport was previously initialized
//!
//! \param  none
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_IsInitialized(uint8_t instance)
{
    return TransportThreadIsRunning(instance);
}

//*****************************************************************************
//
//! HciTransport_ReadHciPacket
//!
//! This function reads a complete HCI packet with any transport
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_ReadHciPacket(uint8_t instance, uint8_t* pHciPkt, uint16_t* hciPktLen)
{
    uint8_t packetType = 0;
    uint16_t dataLength = 0;

    //check if module was previously initialized
    if (TransportInitialized(instance) == FALSE)
    {
        Report("\n\rHciTransport_ReadHciPacket: Transport was not initialized\n");
        return -1;
    }

    if (instance >= HCI_TRANSPORT_NUM_INSTANCES)
    {
        Report("\n\rHciTransport_ReadHciPacket: Invalid transport instance %d\n", instance);
        return -1;
    }

    //Initialize the local buffer
    os_memset(pHciPkt, 0x00, HCI_MAX_PKT_LEN);

    //Read Packet Type
    TransportRead(instance, pHciPkt, HCI_PKT_TYPE_BYTE);

    //Set Packet Type
    packetType = pHciPkt[0];

    if ((packetType == HCI_EVENT_PACKET) || (packetType == HCI_EXTENDED_EVENT_PACKET) || (packetType == HCI_VENDOR_EVENT_PACKET))
    {
        //Read the rest of packet header
        TransportRead(instance, (pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_EVENT_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Event Parameters Data Length
        dataLength = pHciPkt[HCI_EVENT_HDR_LEN_BYTE];

        //Read Event Parameters Data
        if (dataLength > 0)
        {
            if (dataLength > HCI_MAX_PAYLOAD_LEN)
            {
                Report("\n\rHciTransport_ReadHciPacket: Packet params length %d exceeded max supported of %d\n", dataLength, HCI_MAX_PAYLOAD_LEN);
                ASSERT_GENERAL(0);
                return -1;
            }
            TransportRead(instance, (pHciPkt + HCI_EVENT_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_EVENT_PKT_HDR_LEN + dataLength;
    }
    else if (packetType == HCI_CMD_PACKET)
    {
        //Read the rest of packet header
        TransportRead(instance, (pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_CMD_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Command Parameters Data Length
        dataLength = pHciPkt[HCI_CMD_HDR_LEN_BYTE];

        //Read Command Parameters Data
        if (dataLength > 0)
        {
            if (dataLength > HCI_MAX_PAYLOAD_LEN)
            {
                Report("\n\rHciTransport_ReadHciPacket: Packet params length %d exceeded max supported of %d\n", dataLength, HCI_MAX_PAYLOAD_LEN);
                ASSERT_GENERAL(0);
                return -1;
            }
            TransportRead(instance, (pHciPkt + HCI_CMD_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_CMD_PKT_HDR_LEN + dataLength;
    }
    else if (packetType == HCI_EXTENDED_CMD_PACKET)
    {
        //Read the rest of packet header
        TransportRead(instance, (pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_EXT_CMD_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Command Parameters Data Length
        dataLength = BUILD_UINT16(pHciPkt[HCI_CMD_HDR_LEN_BYTE], pHciPkt[HCI_CMD_HDR_LEN_BYTE + 1]);

        //Read Command Parameters Data
        if (dataLength > 0)
        {
            if (dataLength > HCI_MAX_PAYLOAD_LEN)
            {
                Report("\n\rHciTransport_ReadHciPacket: Packet params length %d exceeded max supported of %d\n", dataLength, HCI_MAX_PAYLOAD_LEN);
                ASSERT_GENERAL(0);
                return -1;
            }
            TransportRead(instance, (pHciPkt + HCI_EXT_CMD_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_EXT_CMD_PKT_HDR_LEN + dataLength;
    }
    else if (packetType == HCI_ACL_DATA_PACKET)
    {
        //Read the rest of packet header
        TransportRead(instance, (pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_DATA_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Data Total Length
        dataLength = pHciPkt[HCI_DATA_HDR_LEN_BYTE1];
        dataLength |= ((uint16_t)pHciPkt[HCI_DATA_HDR_LEN_BYTE2] << 8);

        //Read Data Total Length
        if (dataLength > 0)
        {
            if (dataLength > HCI_MAX_PAYLOAD_LEN)
            {
                Report("\n\rHciTransport_ReadHciPacket: Packet data length %d exceeded max supported of %d\n", dataLength, HCI_MAX_PAYLOAD_LEN);
                ASSERT_GENERAL(0);
                return -1;
            }
            TransportRead(instance, (pHciPkt + HCI_DATA_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_DATA_PKT_HDR_LEN + dataLength;
    }
    else
    {
        Report("\n\rHciTransport_ReadHciPacket: Received invalid packet type 0x%x. Discarding packet.\n", packetType);
        return -1;
    }

    return 0;
}

//*****************************************************************************
//
//! HciTransport_WriteHciPacketToNpi
//!
//! This function writes a complete HCI packet to NPI
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_WriteHciPacketToNpi(uint8_t* pHciPkt, uint16_t hciPktLen)
{
    return HciTransport_WriteHciPacket(HCI_TRANSPORT_UART_NPI, pHciPkt, hciPktLen);
}

//*****************************************************************************
//
//! HciTransport_WriteHciPacketToCtrl
//!
//! This function writes a complete HCI packet to BLE controller
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_WriteHciPacketToCtrl(uint8_t* pHciPkt, uint16_t hciPktLen)
{
    return HciTransport_WriteHciPacket(HCI_TRANSPORT_UART_BLE, pHciPkt, hciPktLen);
}

//*****************************************************************************
//
//! HciTransport_RxCallbackbRegister
//!
//! This function register the RX callback function
//!
//! \param  cb - callback to be called upon receiving hci packet from transport
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_RxCallbackbRegister(uint8_t instance, hcitrans_rx_cb_t cb)
{
    if (cb == NULL)
    {
        //ERROR
        return -1;
    }

    if( instance >= HCI_TRANSPORT_NUM_INSTANCES )
    {
        //ERROR
        return -1;
    }

    g_pTransport[instance].rx_cb = cb;
    return 0;
}

//*****************************************************************************
//
//! HciTransport_RxCallbackbRegister
//!
//! This function register the RX callback function to BLE controller
//!
//! \param  cb - callback to be called upon receiving hci packet from transport
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_HciRxCallbackbRegister(hcitrans_rx_cb_t cb)
{
    return HciTransport_RxCallbackbRegister(HCI_TRANSPORT_UART_BLE, cb);
}

//*****************************************************************************
//
//! HciTransport_RxCallbackbRegister
//!
//! This function register the RX callback function to NPI
//!
//! \param  cb - callback to be called upon receiving hci packet from Npi
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_NpiRxCallbackbRegister(hcitrans_rx_cb_t cb)
{
    return HciTransport_RxCallbackbRegister(HCI_TRANSPORT_UART_NPI, cb);
}
