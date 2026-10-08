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
/*    MODULE:   TxDataQueue.h                                              */
/*    PURPOSE:  Tx Data Queue module Header file                           */
/*                                                                         */
/***************************************************************************/
#ifndef _TX_DATA_QUEUE_H_
#define _TX_DATA_QUEUE_H_


#include "tw_driver.h"
#include "udata_api.h"
#include "udata.h"

#define TX_SEND_PACE_TIMEOUT_MSEC_DEF   16


/* Max number of packets in each queue - make sure it sums up as required below or you'll get a compilation error!!
 * NOTE: take from SimpleLiik */
#define DATA_QUEUE_DEPTH_BE  50 //was 60 for all but reduced to 50 to reduce memory
#define DATA_QUEUE_DEPTH_BK  50
#define DATA_QUEUE_DEPTH_VI  50
#define DATA_QUEUE_DEPTH_VO  50
#define DATA_QUEUE_DEPTH_TOTAL  (DATA_QUEUE_DEPTH_BE + DATA_QUEUE_DEPTH_BK + DATA_QUEUE_DEPTH_VI + DATA_QUEUE_DEPTH_VO)

#if 0
/* Verify that there are enough TxCtrlBlks for all users that are queueing packets (driver + FW) */
#if ((DATA_QUEUE_DEPTH_TOTAL + (MGMT_QUEUES_DEPTH * 2) + HOST_TX_DESCRIPTORS_DEF) > (CTRL_BLK_ENTRIES_NUM - 2))
    #error  Not enough TxCtrlBlks for all users !!
#endif
#endif

/* Tx packets handling statistics */
typedef struct
{
    uint32_t uEnqueuePacket;
    uint32_t uDequeuePacket;
    uint32_t uRequeuePacket;
    uint32_t uXmittedPacket;
    uint32_t uDroppedPacket;
    uint32_t uAcStopped;
    uint32_t uLinkStopped;
} TTxDataQueueDebugCnt;


/* The LinkQ object. */
typedef struct
{
    Bool_e                bEnabled;                             /* Link is enabled */
    Bool_e                bEncrypt;                             /* encrypt data packet */
    void                 *aQueues[MAX_NUM_OF_AC];               /* The Tx aQueues handles */
    TTxDataQueueDebugCnt  aQueueCounters[MAX_NUM_OF_AC];        /* Save Tx statistics per Tx-queue. */
    uint8_t               cEncryptSize;
} TDataLinkQ;

/* The DataResources object */
typedef struct
{
    /* Resources per Ac */
    uint32_t uPktInUsePerAc[MAX_NUM_OF_AC];           /* Packet counter per AC */
    int32_t uPktPendTXDataPerAc[MAX_NUM_OF_AC];          /* Packet counter per AC */
    uint32_t uMinGuaranteePerAc[MAX_NUM_OF_AC];       /* Configurable min guarantee packets per AC */
    uint32_t uEffectiveTotalAc;                       /* Effective total packets for AC check */
    uint32_t uEffectiveTotalAcMin;                    /* Just for sunity check */
    /* Resources per Link */
    uint32_t uPktInUsePerLink[WLANLINKS_MAX_LINKS];   /* Packet counter per AC */
    uint32_t uPktAllocPerLink[WLANLINKS_MAX_LINKS];   /* Packet counter per AC */
    uint32_t uMinGuaranteePerLink;                    /* Configurable min guarantee packets per AC */
    uint32_t uEffectiveTotalLink;                     /* Effective total packets for LINK check */
    uint32_t uEffectiveTotalLinkMin;                   /* Just for sunity check */
    /* MaxTotal packets */
    uint32_t uMaxTotal;
} TDataResources;

/* The LinkMac object. */
#define LINK_MAC_TABLE_SIZE  WLANLINKS_MAX_LINKS
typedef struct
{
    Bool_e              uValid;
    TMacAddr            tMacAddr;
} TLinkMac;

#define HIGH_PRIORITY_AC_LIST       1
#define LOW_PRIORITY_AC_LIST        0

#define HIGH_PRIORITY_LINK_LIST     1
#define LOW_PRIORITY_LINK_LIST      0

/* The module's object */
typedef struct
{
    /* Udata handles */
    TUdata              *pUdata;

    TClsfrParams         tClsfrParams;  /* The classifier sub-module parameters */

    Bool_e               bDataPortEnable; /* Data port open or not */
    uint32_t             uContextId;  /* ID allocated to this module on registration to context module */
    void                *hTxSendPaceTimer; /* If queued packets number doesn't reach threshold within timeout, Tx handling is started */

    /* Tx aQueues */
    uint32_t             aQueueMaxSize[MAX_NUM_OF_AC]; /* indicates the max size of each Data queue */

    /* Tx Link Queues */
    TDataLinkQ           aDataLinkQ[WLANLINKS_MAX_LINKS]; /* Link queues handles. */
    TLinkMac             aLinkMac[WLANLINKS_MAX_LINKS];   /* Per link peer MAC address */

    /* Network Interface to Role Type Mapping Table*/
    RoleType_e        aNetToRoleType[TIWDRV_NETIF_NUM];
    
    /* Data resources */
    TDataResources       tDataRsrc; /* Resources object DB */
    uint32_t             uNextToServeLink;         /* the last link served by the scheduler (packet sent successfuly) */
    uint32_t             uMaxEnabledHlid;           /* The highest link ID currently enabled */

    /* Backpressure bitmaps */
    uint32_t             uAcBusyBitmap;             /* bitmap to indicate which AC is busy (stopped) */
    uint32_t             uLinkBusyBitmap;           /* bitmap to indicate which LINK is busy (stopped) */
    uint32_t             uLinkPriorityBitmap;       /* per Link priority indication */

    
    uint8_t              aAcQueueLen[MAX_NUM_OF_AC];

    /* Counters */
    uint32_t             uClsfrMismatchCount;
    uint32_t             uTxSendPaceTimeoutsCount;
    uint32_t             uNoResourcesCount;
    int32_t              txMgmtReqScheduleCount;

    uint8_t              txDataLinkRemoved;      /* notice to the data scheduler that link was removed */
} TTxDataQ;



#endif /* _TX_DATA_QUEUE_H_ */
