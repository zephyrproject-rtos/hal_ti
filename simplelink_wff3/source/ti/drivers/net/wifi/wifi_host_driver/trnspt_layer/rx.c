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
#include <stdint.h>
#include "osi_kernel.h"
#include "rx.h"
#include "wlan_if.h"
#include "host_event_if.h"
#include "errors.h"


#define WL1271_RX_DESC_STATUS_MASK      0x07
#define WL1271_RX_DESC_SUCCESS          0x00
#define WL1271_RX_DESC_DECRYPT_FAIL     0x01
#define WL1271_RX_DESC_MIC_FAIL         0x02


typedef enum
{
    RX_IDLE,
    RX_DESC,
    RX_DROP_PAD,
    RX_COPY_DATA,
    RX_DROP_EXTRA,
}rxState_e;


typedef enum wl_rx_buf_align
{
    WLCORE_RX_BUF_ALIGNED,
    WLCORE_RX_BUF_UNALIGNED,
    WLCORE_RX_BUF_PADDED,
} rxBufAlign_e;




/******************************************************************************

    RxIfDescriptor_t

    the structure of the Rx Descriptor recieved by HOST.

    THIS STRUCTURE IS BEING DUPLICATED FROM cc3xxx_public_DATA_PATH.h

******************************************************************************/
typedef struct
{
    uint16                length;             /* Length of payload (including headers and extra padding)*/
    uint8/*rxBufAlign_e*/ header_alignment;   /* Packet classification tagging info */

    uint8               status;             /* status is now a bit-field structure:         */
                                            /* Bits[7:6] = checsum status indication.       */
                                            /* Bits[5:3] = Process_ID_Tag                   */
                                            /* Bits[2:0] = Error code:                      */
                                            /*             0  ==> SUCCESS                   */
                                            /*             1  ==> RX_DECRYPT_FAIL           */
                                            /*             2  ==> RX_MIC_FAIL               */
                                            /*             3  ==> STA_NOT_FOUND             */
                                            /*             4  ==> KEY_NOT_FOUND             */
                                            /*                                              */
    uint32              timestamp;          /* Timestamp in microseconds,     */

    uint8               flags;              /* See RX_DESC_xxx above */

    uint8               rate;               /* Recevied Rate:at ETxRateClassId format */

    uint8               channel;            /* The received channel*/

    int8                rx_level;           /* The computed RSSI value in db of current frame */

    uint8               rx_snr;             /* The computed SNR value in db of current frame */


    uint8               hlid;               /* Host Link ID associated with the source of the frame  */
    uint8               extraBytes;         /* Number of padding bytes added to actual packet length */

    uint8               frameFormat;        /* holds the driver flags to be used internally */

} RxIfDescriptor_t;

typedef struct
{
    void *frame;
    RxIfDescriptor_t *desc;
    uint16_t frameSizeNeto;
    uint16_t handled_bytes;
    uint8_t /*rxState_e*/ state;
}rxStateMachine_t;

typedef struct
{
    rxStateMachine_t rxStateMachine;
    rxNextLayer_e nextLayer;
    uint32_t rx_counter;
    RxAllocationFunctionCB_t allocationFunction;
    void *allocationParams;
    RxRecvNextLayerFunctionCB_t recvNextLayerFunction;
    void *recvNextLayerParams;
}rxCB_t;

rxCB_t *gRx = NULL;


int rx_Init()
{
    gRx = os_zalloc(sizeof(rxCB_t));
    if(NULL == gRx)
    {
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__RX, WLAN_ERROR_TYPE__MALLOC);
    }
    return 0;
}

void rx_Deinit()
{
    os_free(gRx);
    gRx = NULL;
}


void rx_RegisterAllocationFunction(RxAllocationFunctionCB_t function, void *parameters)
{
    gRx->allocationFunction = function;
    gRx->allocationParams = parameters;
}

void rx_RegisterNextLayerRecvFunction(RxRecvNextLayerFunctionCB_t function, void *parameters,rxNextLayer_e nextLayer)
{
    gRx->nextLayer = nextLayer;
    gRx->recvNextLayerFunction = function;
    gRx->recvNextLayerParams = parameters;
}

//return bytes wrote, and update rawBufferLen with reminder bytes
int rx_GetDesc(uint8_t *rawBuffer, uint32_t *rawBufferLen)
{
    uint32_t reminder = 0;
    char  *tempBlock;
    int ret = 0;
    if(NULL == gRx->rxStateMachine.desc)
    {
        gRx->rxStateMachine.desc = os_zalloc(sizeof(RxIfDescriptor_t));
    }
    if(gRx->rxStateMachine.desc == NULL)
    {
        ASSERT_GENERAL(0);
        return -1;
    }
    //check here if we are going to exceed the write of the descriptor
    if(gRx->rxStateMachine.handled_bytes + *rawBufferLen > sizeof(RxIfDescriptor_t))
    {
        //if we do, save the bytes reminder for the next state
        reminder = gRx->rxStateMachine.handled_bytes + *rawBufferLen - sizeof(RxIfDescriptor_t);
        *rawBufferLen = sizeof(RxIfDescriptor_t) - gRx->rxStateMachine.handled_bytes;
    }

    //we use the temp block here for better code read
    tempBlock = (char *)(gRx->rxStateMachine.desc);
    os_memcpy(tempBlock + gRx->rxStateMachine.handled_bytes,rawBuffer,*rawBufferLen);

    //accumulate the length received.
    gRx->rxStateMachine.handled_bytes += *rawBufferLen;

    //check if we got the whole header
    if(gRx->rxStateMachine.handled_bytes == sizeof(RxIfDescriptor_t))
    {
        uint32_t padding = 0;

        if (gRx->rxStateMachine.desc->header_alignment == WLCORE_RX_BUF_PADDED)
        {
            padding = 2;
        }

        gRx->rxStateMachine.state = RX_DROP_PAD;
        gRx->rxStateMachine.handled_bytes = 0;

        //desc length  = desc + padding + packetLen + extraBytes
        if((gRx->rxStateMachine.desc->length==0) || (gRx->rxStateMachine.desc->length < (gRx->rxStateMachine.desc->extraBytes + padding + sizeof(RxIfDescriptor_t))))
        {
            WlanEventError_t  error_event;
            RX_PRINT_ERROR("\n\r rx_GetDesc: Fail in getting RX Descriptor\n\r");
            error_event.error_num = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__RX, WLAN_ERROR_TYPE__RX_SM_LENGTH_OF_FRAME_IS_INVALID_FROM_FW);
            error_event.module = WLAN_MODULE_RX;
            error_event.severity = WLAN_SEVERITY_MID;
            Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));

            gRx->rxStateMachine.state = RX_IDLE;
            if(NULL != gRx->rxStateMachine.desc)
            {
                os_free(gRx->rxStateMachine.desc);
                gRx->rxStateMachine.desc = NULL;
            }

            ret = *rawBufferLen;
            *rawBufferLen = reminder;
            return ret;
        }
        gRx->rxStateMachine.frameSizeNeto = gRx->rxStateMachine.desc->length - gRx->rxStateMachine.desc->extraBytes - padding - sizeof(RxIfDescriptor_t);
    }

    ret = *rawBufferLen;
    *rawBufferLen = reminder;
    return ret;
}

int rx_DropPadding(uint32_t *rawBufferLen)
{
    uint32_t reminder = 0;
    uint32_t padding = 0;
    int ret = 0;
    uint32_t includeDescSize = 0;


    //if next layer is still wlan we need to include the rx descriptor before the frame
    if(RX_NEXT_LAYER_WLAN == gRx->nextLayer)
    {
        includeDescSize = sizeof(RxIfDescriptor_t);
    }

    if (gRx->rxStateMachine.desc->header_alignment == WLCORE_RX_BUF_PADDED)
    {
        padding = 2;
    }

    //check here if we are going to exceed the write of the padding
    if((gRx->rxStateMachine.handled_bytes + *rawBufferLen)> padding)
    {
        //if we do, save the bytes reminder for the next state
        reminder = gRx->rxStateMachine.handled_bytes + *rawBufferLen - padding;
        *rawBufferLen = padding - gRx->rxStateMachine.handled_bytes;
    }

    //accumulate the length received.
    gRx->rxStateMachine.handled_bytes += *rawBufferLen;

    //check if we got the whole padding
    if(gRx->rxStateMachine.handled_bytes == padding)
    {
        gRx->rxStateMachine.state = RX_COPY_DATA;
        gRx->rxStateMachine.handled_bytes = 0;

        //if there is an allocation function use it, if not, use mem malloc
        if(gRx->allocationFunction)
        {
            //RX_MGMT_PRINT("\n\rrx_DropPadding:call rxData_RequestForBuffer size : %d + extraBytes:%d padding:%d",
             //             gRx->rxStateMachine.frameSizeNeto + includeDescSize, gRx->rxStateMachine.desc->extraBytes,padding);
            //rxData_RequestForBuffer
            gRx->allocationFunction((uint8_t **)(&(gRx->rxStateMachine.frame)),gRx->rxStateMachine.frameSizeNeto + includeDescSize);
            //need to be freed by RxBufFree
        }
        else
        {
            gRx->rxStateMachine.frame = os_malloc(gRx->rxStateMachine.frameSizeNeto + includeDescSize);
        }

        if((NULL != gRx->rxStateMachine.frame) && (includeDescSize))
        {
            gRx->rxStateMachine.desc->header_alignment = WLCORE_RX_BUF_ALIGNED;
            gRx->rxStateMachine.desc->length -= padding;
            os_memcpy(gRx->rxStateMachine.frame,gRx->rxStateMachine.desc,includeDescSize);
        }
    }


    ret = *rawBufferLen;
    *rawBufferLen = reminder;
    return ret;
}


int rx_CopyBuffer(uint8_t *rawBuffer, uint32_t *rawBufferLen)
{
    uint32_t reminder = 0;
    char  *tempBlock;
    int ret = 0;
    uint32_t packetLength;
    uint32_t includeDescSize = 0;


    //if next layer is still wlan we need to include the rx descriptor before the frame
    if(RX_NEXT_LAYER_WLAN == gRx->nextLayer)
    {
        includeDescSize = sizeof(RxIfDescriptor_t);
    }

    packetLength = gRx->rxStateMachine.frameSizeNeto;

    //check here if we are going to exceed the write of the packet
    if((gRx->rxStateMachine.handled_bytes + *rawBufferLen) > packetLength)
    {
        //if we do, save the bytes reminder for the next state
        reminder = gRx->rxStateMachine.handled_bytes + *rawBufferLen - packetLength;
        *rawBufferLen = packetLength - gRx->rxStateMachine.handled_bytes;
    }

    if(NULL != gRx->rxStateMachine.frame)
    {
        //we use the temp block here for better code read, copy the packet to the gRx frame
        tempBlock = (char *)(gRx->rxStateMachine.frame);
        if((gRx->rxStateMachine.handled_bytes + *rawBufferLen) > packetLength)
        {
            ASSERT_GENERAL(0);
            return -1;
        }
        os_memcpy(tempBlock + includeDescSize + gRx->rxStateMachine.handled_bytes,rawBuffer,*rawBufferLen);
    }

    //accumulate the length received.
    gRx->rxStateMachine.handled_bytes += *rawBufferLen;

    //check if we got the whole packet
    if(gRx->rxStateMachine.handled_bytes == packetLength)
    {

        if(NULL != gRx->rxStateMachine.frame)
        {
            if(includeDescSize)
            {
                RxIfDescriptor_t    *pRxParams  = (RxIfDescriptor_t*)gRx->rxStateMachine.frame;
                if(pRxParams->extraBytes)
                {
                   pRxParams->length -= pRxParams->extraBytes;//the descriptor length includes the extra bytes
                   pRxParams->extraBytes = 0;
                }
            }
            //buffer needs to be free in the next layer
            if(NULL != gRx->recvNextLayerFunction)
            {
                //call next layer function , for Mx see @rx_callback->RxQueue_ReceivePacket
                //RX_MGMT_PRINT("\n\rrx_CopyBuffer:call to RxQueue_ReceivePacket");
                gRx->recvNextLayerFunction(gRx->rxStateMachine.desc->hlid? 1:0,gRx->rxStateMachine.frame,gRx->rxStateMachine.frameSizeNeto + includeDescSize);
            }

            gRx->rx_counter++;

            //if no allocation function it means the buffer is allocated inside this module and need to be free here
            if(NULL == gRx->allocationFunction)
            {
                os_free(gRx->rxStateMachine.frame);
            }

            gRx->rxStateMachine.frame = NULL;
        }

        if(gRx->rxStateMachine.desc->extraBytes > 0)
        {
            gRx->rxStateMachine.state = RX_DROP_EXTRA;
        }
        else
        {
            gRx->rxStateMachine.state = RX_IDLE;
            if(NULL != gRx->rxStateMachine.desc)
            {
                os_free(gRx->rxStateMachine.desc);
                gRx->rxStateMachine.desc = NULL;
            }
        }

        gRx->rxStateMachine.handled_bytes = 0;
    }

    ret = *rawBufferLen;
    *rawBufferLen = reminder;
    return ret;
}





int rx_DropExtraBytes(uint32_t *rawBufferLen)
{
    uint32_t reminder = 0;
    uint32_t extraBytes = 0;
    int ret = 0;

    extraBytes = gRx->rxStateMachine.desc->extraBytes;

    //check here if we are going to exceed the write of the extra bytes
    if(gRx->rxStateMachine.handled_bytes + *rawBufferLen > extraBytes)
    {
        //if we do, save the bytes reminder for the next state
        reminder = gRx->rxStateMachine.handled_bytes + *rawBufferLen - extraBytes;
        *rawBufferLen = extraBytes - gRx->rxStateMachine.handled_bytes;
    }

    //accumulate the length received.
    gRx->rxStateMachine.handled_bytes += *rawBufferLen;

    //check if we got the whole extra bytes
    if(gRx->rxStateMachine.handled_bytes == extraBytes)
    {
        gRx->rxStateMachine.state = RX_IDLE;
        gRx->rxStateMachine.handled_bytes = 0;
        if(NULL != gRx->rxStateMachine.desc)
        {
            os_free(gRx->rxStateMachine.desc);
            gRx->rxStateMachine.desc = NULL;
        }

        if((NULL == gRx->allocationFunction) && (NULL != gRx->rxStateMachine.frame))
        {
            os_free(gRx->rxStateMachine.frame);
            gRx->rxStateMachine.frame = NULL;
        }
    }

    ret = *rawBufferLen;
    *rawBufferLen = reminder;
    return ret;
}


void rx_StateMachine(uint8_t *rawBuffer, uint32_t rawBufferLen)
{
    int ret = 0;
    WlanEventError_t  error_event;
    //RX_MGMT_PRINT("\n\rrx_StateMachine:started: rawBufferLen:%d state:%d handled_bytes:%d",rawBufferLen,gRx->rxStateMachine.state,gRx->rxStateMachine.handled_bytes);

    while(rawBufferLen > 0)
    {
        rxState_e state = (rxState_e) gRx->rxStateMachine.state;
        switch(state)
        {
        case RX_IDLE:
            os_memset(&(gRx->rxStateMachine),0,sizeof(rxStateMachine_t));
            gRx->rxStateMachine.state = RX_DESC;
            break;
        case RX_DESC:
            ret = rx_GetDesc(rawBuffer, &rawBufferLen);
            rawBuffer = rawBuffer + ret;
            break;
        case RX_DROP_PAD:
            ret = rx_DropPadding(&rawBufferLen);
            rawBuffer = rawBuffer + ret;
            break;
        case RX_COPY_DATA:
            ret = rx_CopyBuffer(rawBuffer, &rawBufferLen);
            rawBuffer = rawBuffer + ret;
            break;
        case RX_DROP_EXTRA:
            ret = rx_DropExtraBytes(&rawBufferLen);
            rawBuffer = rawBuffer + ret;
            break;
        }
        if(ret < 0)
        {
            RX_PRINT_ERROR("\n\r rx_StateMachine: Fail in state: %d",state);
            error_event.error_num = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__RX, WLAN_ERROR_TYPE__RX_SM);
            error_event.module = WLAN_MODULE_RX;
            error_event.severity = WLAN_SEVERITY_MID;
            Wlan_HostSendEvent(WLAN_EVENT_ERROR, (uint8_t*)&error_event, sizeof(WlanEventError_t));
        }

    }
}







int rx(uint8_t *rx_buf_ptr, uint16_t rx_buf_len)
{
    rx_StateMachine(rx_buf_ptr, rx_buf_len);
    return(0);
}




