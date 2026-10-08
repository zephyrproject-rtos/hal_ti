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
/***************************************************************************/
/*                                                                         */
/*    MODULE:   txMgmtQueue_Api.h                                          */
/*    PURPOSE:  Tx Mgmt Queue module API Header file                       */
/*                                                                         */
/***************************************************************************/
#ifndef _TX_MGMT_QUEUE_API_H_
#define _TX_MGMT_QUEUE_API_H_

#include "tw_driver.h"
#include "udata_api.h"
#include "udata.h"
#include "osi_type.h"

typedef enum
{
    QUEUE_TYPE_EAPOL,   /* EAPOL-queue - low-priority, for other internal packets (EAPOL, NULL, IAPP). */
    QUEUE_TYPE_MGMT,    /* Mgmt-queue  - high-priority, for mgmt packets only. */
    NUM_OF_MGMT_QUEUES
} EMgmtQueueTypes;

/* State-Machine States */
typedef enum
{
    SM_STATE_CLOSE,         /* All Tx path is closed. */
    SM_STATE_MGMT,          /* Only mgmt Tx is permitted. */
    SM_STATE_EAPOL,         /* Only mgmt and EAPOL Tx is permitted. */
    SM_STATE_OPEN_MGMT,     /* All Tx permitted and Mgmt aQueues are currently active (date disabled). */
    SM_STATE_OPEN_DATA      /* All Tx permitted and Data aQueues are currently active (mgmt disabled). */
} ESmState;

typedef struct
{
    uint32_t aEnqueuePackets[NUM_OF_MGMT_QUEUES];
    uint32_t aDequeuePackets[NUM_OF_MGMT_QUEUES];
    uint32_t aRequeuePackets[NUM_OF_MGMT_QUEUES];
    uint32_t aDroppedPackets[NUM_OF_MGMT_QUEUES];
    uint32_t aXmittedPackets[NUM_OF_MGMT_QUEUES];
    uint32_t uNoResourcesCount;
} TDbgCount;

/* The LinkQ object. */
typedef struct
{
    Bool_e          bBusy;                         /* Link is busy. */
    Bool_e          bEnabled;                      /* Link is enabled */
    ESmState        eState;                        /* The current state of the Link SM. */
    ELinkState      eTxConnState;
    Bool_e          bSendEventNotEmpty;           /* Used to sign if to send QUEUE_NOT_EMPTY event when switching to driver context */
    void           *aQueues[NUM_OF_MGMT_QUEUES];   /* The mgmt-aQueues handles. */
    Bool_e          aQenabled[NUM_OF_MGMT_QUEUES]; /* Queue is enabled by the SM. */
    TDbgCount       tDbgCounters; /* Save Tx statistics per mgmt-queue. */
} TMgmtLinkQ;

/* The module object. */
typedef struct
{
    /* Udata handles */
    TUdata         *pUdata;

    Bool_e          bMgmtPortEnable;/* Port open for mgmt-aQueues or not. */
    uint32_t        uContextId;     /* ID allocated to this module on registration to context module */

    TMgmtLinkQ      aMgmtLinkQ[WLANLINKS_MAX_LINKS];   /* Link queues handles. */
    Bool_e          bMgmtAcBusy;                       /* Mgmt AC is busy. */
    uint32_t        uLastHlid;                         /* Last scheduler visited HLID */

    uint32_t        uDummyPackets;                     /* Number of generated Dummy-Blocks packets */
    int32_t        txMgmtReqScheduleCount;           /* number of frames which are currently enqueued */

} TTxMgmtQ;


/*
 *  The module public functions:
 */
TTxMgmtQ   *txMgmtQ_Create (void);
void        txMgmtQ_Init (TUdata *pUdata);
uint32_t    txMgmtQ_SetDefaults (void);
uint32_t    txMgmtQ_NotifyFwReset(void);
uint32_t    txMgmtQ_Destroy (void);
void        txMgmtQ_ClearQueues (void);
uint32_t    txMgmtQ_Xmit (TTxCtrlBlk *pPktCtrlBlk, Bool_e bExternalContext);
void        txMgmtQ_QueuesNotEmpty (void* hCbHndl);
void        txMgmtQ_UpdateBusyMap(TTxHwBackpressure *pBackpressure);
void        txMgmtQ_ReqToRunTxScheduler (void);
void        txMgmtQ_SuspendTx (void);
void        txMgmtQ_ResumeTx (void);
void        txMgmtQ_StopAll (void);
void        txMgmtQ_WakeAll (void);
void        txMgmtQ_SetLinkState(uint32_t uHlid, ELinkState eTxConnState);
ELinkState  txMgmtQ_GetLinkState (uint32_t uHlid);
void        txMgmtQ_ClearLink(uint32_t uHlid);
void        TxMgmtQ_FlushLinkQueues(uint32_t uHlid);
#ifdef TI_DBG
void        txMgmtQ_PrintModuleParams (void);
void        txMgmtQ_PrintQueueStatistics (void);
void        txMgmtQ_ResetQueueStatistics (void);
#endif


#endif /* _TX_MGMT_QUEUE_API_H_ */
