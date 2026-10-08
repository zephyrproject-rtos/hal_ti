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
/** \file fw_event_if.h
 *  \brief FwEvent api
 *
 *  \see fw_event_if.c
 */


#ifndef _FW_EVENT_IF_H
#define _FW_EVENT_IF_H

#include <osi_kernel.h>
#include "txn_bus_drv.h"
#include "fw_status.h"

//#define DEBUG_FW_EVENT_LOG
#ifdef DEBUG_FW_EVENT_LOG
#define FW_EVENT_HANDLE_PRINT Report
#define FW_EVENT_HANDLE_PRINT_ERROR Report
#else
#define FW_EVENT_HANDLE_PRINT(...)
#define FW_EVENT_HANDLE_PRINT_ERROR Report
#endif

//#define DEBUG_FWEVENT
#ifdef DEBUG_FWEVENT
#define FWEVENT_PRINT Report
#else
#define FWEVENT_PRINT(...)
#endif

//#define DEBUG_CORE_STATUS
#ifdef DEBUG_CORE_STATUS
#define CORE_STATUS_PRINT Report
#else
#define CORE_STATUS_PRINT(...)
#endif

#define OSPREY_BUS_BLOCK_SIZE 64
#define HINT_NEW_TX_RESULT                         0x1  //bit_0
#define HINT_COMMAND_COMPLETE                      0x2  //bit_1
#define HINT_RX_DATA_PENDING                       0x4  //bit_2
#define HINT_ROM_LOADER_INIT_COMPLETE              0x8  //bit_3
#define HINT_SECOND_LOADER_INIT_COMPLETE           0x10 //bit_4
#define HINT_FW_WAKEUP_COMPLETE                    0x20 //bit_5
#define HINT_FW_DOWNLOADING_INI_PARAMS_COMPLETE    0x40 //bit_6
#define HINT_GENERAL_ERROR                         0x80000000 //bit_31

typedef enum
{
    FWEVENT_STATE_STOPPED,
    FWEVENT_STATE_IDLE,
    FWEVENT_STATE_WAIT_INTR_INFO,
    FWEVENT_STATE_WAIT_HANDLE_COMPLT
} EFwEventState;

typedef struct
{
    TTxnStruct    tTxnStruct;
    uint32_t      uData;

} TRegisterTxn;

typedef struct
{
    TTxnStruct     tTxnStruct;
    void           *tFwStatus;

} TFwStatusTxn;

typedef struct
{
    EFwEventState    eSmState;             /* State machine state */
    uint32_t           uEventMask;     /* Static interrupt event mask */
    uint32_t           uEventVector;   /* Saves the current active FW interrupts */
    TRegisterTxn     tMaskTxn;         /* The host mask register transaction */
    TFwStatusTxn     tFwStatusTxn;     /* The FW status structure transaction (read from FW memory) */
    uint32_t           uFwTimeOffset;  /* Offset in microseconds between driver and FW clocks */
    uint32_t           uContextId;     /* Client ID got upon registration to the context module */
    uint32_t           bIntrPending;   /* If TRUE a new interrupt is pending while handling the previous one */
    uint32_t           uNumPendHndlrs; /* Number of event handlers that didn't complete their event processing */
    OsiSyncObj_t       FwEventGeneralObj[4]; /* this is a general sync obj to signal events for other threads, currently used for init */
    uint32_t           eventSize; /* this is the size of the event and command complete */
    uint32_t           rxTxBufSize; /* holds the size of the RX TX buffer */
    uint8_t            *rxTxBuffer; /*this buffer used for rx and tx*/
    uint8_t            isDuringInit;
} TFwEvent;

typedef struct
{
    int16_t type :4;
    int16_t length :12;
} EventCompleteMboxTLV_t;

typedef struct
{
    void *message;
    uint32_t len;
}EventMessage_t;

#define UPDATE_PENDING_HANDLERS_NUMBER(eStatus)   if (eStatus == TXN_STATUS_PENDING) {pFwEvent->uNumPendHndlrs++;}

#define POLLING_INTERVAL_IN_MSEC    10


int fwEvent_Init (uint32_t rxTxBufferSize, uint32_t commandsEventsSize);
void fwEvent_set_cmdEventSize (uint32_t commandsEventsSize);
int fwEvent_Destroy();
void fwEvent_HandlerCompleted();
uint32_t fwEvent_TranslateToFwTime(uint32_t uHostTime);
void fwEvent_SetInitMask(TFwEvent *pFwEvent);
int fwEvent_Stop();
void fwEvent_MaskAllFwInterrupts(TFwEvent *pFwEvent);
void fwEvent_EnableExternalEvents(TFwEvent *pFwEvent);
int fwEvent_Wait(int timeout, uint32_t event);
void fwEvent_Signal(uint32_t hint_mask);
uint8_t *fwEvent_GetRxTxBuffer();
void fwEvent_SetDuringInit(uint8_t isDuringInit, uint32_t commandsEventsSize);
int FwEvent_irq_handler ();

#endif /* _FW_EVENT_IF_H */







