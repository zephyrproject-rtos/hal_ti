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
/*    MODULE:   txCtrl.h                                                   */
/*    PURPOSE:  txCtrl module Header file                                  */
/*                                                                         */
/***************************************************************************/
#ifndef _TX_CTRL_H_
#define _TX_CTRL_H_


#include <data_path/udata/export_inc/udata_api.h>
#include <data_path/udata/udata.h>
#include "paramOut.h"
#include "timer.h"


#define DEF_TX_PORT_STATUS              CLOSE
#define DEF_CURRENT_PRIVACY_MODE        FALSE
#define DEF_EAPOL_ENCRYPTION_STATUS     FALSE

#define MGMT_PKT_LIFETIME_TU            8000    /* Mgmt pkts lifetime in TUs (1024 usec). */

#define MAX_TX_DESC_ID                  (NUM_TX_DESCRIPTORS)   /* have more Desc-IDs than needed to avoid corner cases */


extern const EAcTrfcType WMEQosTagToACTable[MAX_NUM_OF_802_1d_TAGS];

/* The TX delay histogram ranges start and end in uSec. */
static const uint32_t txDelayRangeStart[TX_DELAY_RANGES_NUM] = {    0,  1000, 10000, 20000, 40000, 60000,  80000, 100000, 200000 };
static const uint32_t txDelayRangeEnd  [TX_DELAY_RANGES_NUM] = { 1000, 10000, 20000, 40000, 60000, 80000, 100000, 200000, 0xFFFFFFFF };

/* BE is ordered here above BK for priority sensitive functions (BE is 0 but has higher priority than BK). */
static const EAcTrfcType priorityOrderedAc[] = {QOS_AC_BK, QOS_AC_BE, QOS_AC_VI, QOS_AC_VO};

typedef struct 
{
    uint32_t  dbgNumPktsSent[MAX_NUM_OF_AC];       /* Pkts sent by data-queue or mgmt-queue. */
    uint32_t  dbgNumPktsBusy[MAX_NUM_OF_AC];      /* Pkts for which busy was received from HW-Q */
    uint32_t  dbgNumPktsLinkBusy[MAX_NUM_OF_AC];  /* Pkts for which link busy was received from HW-Q */
    uint32_t  dbgNumPktsXfered[MAX_NUM_OF_AC];    /* Pkts sent to Xfer */
    uint32_t  dbgNumPktsSuccess[MAX_NUM_OF_AC];   /* Pkts for which success was received from Xfer */
    uint32_t  dbgNumPktsError[MAX_NUM_OF_AC];     /* Pkts for which error was received from Xfer */
    uint32_t  dbgNumTxCmplt[MAX_NUM_OF_AC];        /* Pkts that reached complete CB */
    uint32_t  dbgNumTxCmpltOk[MAX_NUM_OF_AC];     /* Pkts that reached complete CB with status OK */
    uint32_t  dbgNumTxCmpltError[MAX_NUM_OF_AC];  /* Pkts that reached complete CB with status NOK */
    uint32_t  dbgNumTxCmpltOkBytes[MAX_NUM_OF_AC];/* Acknowledged bytes (complete status OK) */
    uint32_t  dbgNumTxCmpltFailBytes[MAX_NUM_OF_AC];

} txDataDbgCounters_t;

typedef struct 
{
    uint32_t  dbgStartCollectCntrStackEntr[WLANLINKS_MAX_LINKS];
    uint32_t  dbgStackEntrTimeFirstPacket_Ms[WLANLINKS_MAX_LINKS];
    uint32_t  dbgStackEntrTimeLastPacket_Ms[WLANLINKS_MAX_LINKS];
    uint32_t  dbgStackEntrNumByteSent[WLANLINKS_MAX_LINKS];
    uint32_t  link_tx_dbgStackEntNumPktsXfered[WLANLINKS_MAX_LINKS];

    uint32_t  dbgStartCollectCntr[WLANLINKS_MAX_LINKS];
    uint32_t  dbgTimeFirstPacket_Ms[WLANLINKS_MAX_LINKS];
    uint32_t  dbgTimeLastPacket_Ms[WLANLINKS_MAX_LINKS];

    uint32_t  dbgNumPktsSent[WLANLINKS_MAX_LINKS];       /* Pkts sent by data-link or mgmt-link. */
    uint32_t  dbgNumBytesSent[WLANLINKS_MAX_LINKS];       /* Bytes sent by data-link or mgmt-link. */
    uint32_t  dbgNumPktsBusy[WLANLINKS_MAX_LINKS];      /* Pkts for which busy was received from HW-Q */
    uint32_t  dbgNumPktsAcBusy[WLANLINKS_MAX_LINKS];      /* Pkts for which AC busy was received from HW-Q */
    uint32_t  dbgNumPktsXfered[WLANLINKS_MAX_LINKS];    /* Pkts sent to Xfer */
    uint32_t  dbgNumPktsSuccess[WLANLINKS_MAX_LINKS];   /* Pkts for which success was received from Xfer */
    uint32_t  dbgNumPktsError[WLANLINKS_MAX_LINKS];     /* Pkts for which error was received from Xfer */

    uint32_t  dbgNumTxCmplt[WLANLINKS_MAX_LINKS];        /* Pkts that reached complete CB */
    uint32_t  dbgNumTxCmpltOk[WLANLINKS_MAX_LINKS];     /* Pkts that reached complete CB with status OK */
    uint32_t  dbgNumTxCmpltError[WLANLINKS_MAX_LINKS];  /* Pkts that reached complete CB with status NOK */
    uint32_t  dbgNumTxCmpltOkBytes[WLANLINKS_MAX_LINKS];/* Acknowledged bytes (complete status OK) */
    uint32_t  dbgNumTxCmpltFailBytes[WLANLINKS_MAX_LINKS];/* Acknowledged bytes (complete status OK) */

} txDataDbgLinkCounters_t;

typedef struct
{
    void          *hRequestTimer; 
    Bool_e         bRequestTimerRunning;  
    uint8_t        tid;
    TTimerCbFunc   fExpiryCbFunc;
} TSMTimerData_t;

/* 
 * TokenCalculationParams_t - struct used for the tokens calculation
 *                           of the WMM-AC 
*/
typedef struct
{
    uint16_t  allocatedMediumTime;
    int16_t   tokens;
    uint32_t  timeDiffMinThreshold;
    uint32_t  defTimeDiffMinThreshold;
    uint32_t  lastCalcTimeStamp;
    uint32_t  usedTokensRemainder;
    uint32_t  unusedTokensRemainder;
    uint16_t  maxTokensThreshold;
    uint16_t  minTokensThreshold;
} TokenCalculationParams_t;


/* 
 *  Module object structure. 
 */
typedef struct 
{
    /* Udata handles */
    TUdata             *pUdata;

    Bool_e              aEncryptData[WLANLINKS_MAX_LINKS];
    Bool_e              aEncryptMgmt[WLANLINKS_MAX_LINKS];//PMF
    Bool_e              aEncryptEapol[WLANLINKS_MAX_LINKS];
    uint16_t            aMsduLifeTimeTu[MAX_NUM_WLAN_ROLE_IDS][MAX_NUM_OF_AC];
    uint8_t/*AckPolicy_e*/  aAckPolicy[WLANLINKS_MAX_LINKS][MAX_NUM_OF_AC];

    TTxCtrlBlk         *aTxDescIds[MAX_TX_DESC_ID]; /* An allocated entry holds the TxCtrlBlk of a Tx pakcet sent to FW (NULL if free). */
                                                    /* The entry index is used as the descID written in the TxDescriptor and returned in the TxResult. */
    uint8_t             aDescIdFreeStack[MAX_TX_DESC_ID]; /* Stack of free descriptor IDs for O(1) alloc/free. */
    uint8_t             uDescIdFreeStackTop;               /* Number of IDs currently in the stack. */

    /* Admission control and backpressure (for busy queues mapping) */
    TTxHwBackpressure   tBackpressure;                    /* Last backpressure update from FW. */
    uint32_t            uUpDowngradedLink;                /* The Link ID that has downgraded UP. set it to WLANLINKS_INVALID_HLID if none. */
    EAcTrfcType         aUpDowngradedLinkAcMapping[MAX_NUM_OF_AC]; /* The UP-downgrade link mapping to highest admitted AC equal or below given AC. */
    ETrafficAdmState    aAdmissionState[WLANLINKS_MAX_LINKS][MAX_NUM_OF_AC];    /* AC is allowed to transmit or not. */
    EAdmissionState     aAdmissionRequired[WLANLINKS_MAX_LINKS][MAX_NUM_OF_AC]; /* AC requires AP's admission or not. */

    /* Counters */
    TTxDataCounters     txDataCounters[MAX_NUM_OF_AC]; /* Save Tx statistics per Tx-queue. */
    uint32_t            SumTotalDelayUs[MAX_NUM_OF_AC]; /* Store pkt delay sum in Usecs to avoid divide per 
                                                            pkt, and covert to msec on user request. */
    tiwdrv_rate_e       eCurrentTxRate[WLANLINKS_MAX_LINKS]; /* Save last data Tx rate for applications' query */

    /* TSM (802.11k measurements) */
    TSMReportData_t     TSMReportStat[TSM_REPORT_NUM_OF_TID_MAX]; 
    uint32_t            TSMInProgressBitmap;
    /*  Timers to be used for regular TSM (not triggered one) */
    TSMTimerData_t      tTSMTimers[TSM_REPORT_NUM_OF_MEASUREMENT_IN_PARALLEL_MAX];                  
    TTsmReportHandler   fTriggerReportCB;
    void               *hTriggerReportHandle;

    uint32_t            uSdioBlkSizeShift;       /* In block-mode:  uBlkSize = (1 << uBlkSizeShift)   */
    uint32_t            uHostIfCfgBitmap;        /* Host interface configuration bitmap */
    uint64_t            uPktsPendCompleteCounter;/* Count Tx packets sent to FW and pending TxComplete (for PM constraints) */

    txDataDbgCounters_t dbgCounters;    /* debug counters */
    txDataDbgLinkCounters_t dbgLinkCounters;    /* debug counters per link */

    TSecuritySeqHandler fSecSeqCb;
    void               *hSecSeqHandle;

} txCtrl_t;



#endif  /* _TX_CTRL_H_ */
