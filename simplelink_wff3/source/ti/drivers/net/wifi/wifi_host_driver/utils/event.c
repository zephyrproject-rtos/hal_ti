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
#include "wlan_if.h"
#include "errors.h"
#include "osi_kernel.h"
#include <string.h>
#include "tx.h"
#include "fw_event_if.h"
#include "host_event_if.h"

// ============================================================================
//      Host Event Handler
// ============================================================================
extern OsiMsgQ_t eventMsgQueue;
#define FW_CRASH_EVENT_ID                               (0x40000000)//   BIT_30,
#define ERROR_EVENT_ID                                  (0x80000000)//   BIT_31,

void Wlan_HostSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen)
{
    // marking the parameter as unused to bypass 'unused parameter' warning
    (void)argsLen;

    EventMessage_t event;
    uint8_t *event_data;
    WlanEvent_t* pEvent;
    uint32_t* pId;


    event_data = os_malloc(HOST_EVENT_RESERVED_EVENT_HEADER + sizeof(WlanEvent_t));

    if (!args)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\r[Wlan_HostSendEvent] ERROR NULL buffer,opcode:%d\n\r",opcode);
    }
    if(event_data == NULL)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\r[Wlan_HostSendEvent] ERROR event_data allocation error\n\r");
        return;
    }

    switch (opcode)
    {
        case WLAN_EVENT_ERROR:
        {
            //those lines are for use by CC35XX , the data is written to HOST_EVENT_RESERVED_EVENT_HEADER
            //first 32 bit represent the eventId.
            pId = (uint32_t*)event_data;
            *pId = (uint32_t)ERROR_EVENT_ID;
            //end of code to support MX
            pEvent = (WlanEvent_t*)(event_data + HOST_EVENT_RESERVED_EVENT_HEADER);
            pEvent->Id = WLAN_EVENT_ERROR;
            pEvent->Data.error.module = ((WlanEventError_t *)(args))->module;
            pEvent->Data.error.error_num = ((WlanEventError_t *)(args))->error_num;
            pEvent->Data.error.severity =  ((WlanEventError_t *)(args))->severity;

        }
        break;
        case WLAN_EVENT_FW_CRASH:
        {
            //those lines are for use by CC35XX , the data is written to HOST_EVENT_RESERVED_EVENT_HEADER
            //first 32 bit represent the eventId.
            pId = (uint32_t*)event_data;
            *pId = (uint32_t)FW_CRASH_EVENT_ID;
            //end of code to support MX
            pEvent = (WlanEvent_t*)(event_data + HOST_EVENT_RESERVED_EVENT_HEADER);
            pEvent->Id = WLAN_EVENT_FW_CRASH;
            pEvent->Data.error.module = ((WlanEventError_t *)(args))->module;
            pEvent->Data.error.error_num = ((WlanEventError_t *)(args))->error_num;
            pEvent->Data.error.severity =  ((WlanEventError_t *)(args))->severity;


        }
        break;
    }

    event.message = event_data;
    event.len = HOST_EVENT_RESERVED_EVENT_HEADER + sizeof(WlanEvent_t);
    osi_MsgQWrite(&eventMsgQueue, &event, OSI_WAIT_FOREVER,OSI_FLAG_NOT_FROM_INTR);


}
