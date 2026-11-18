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
/*      MODULE: rx.h                                                       */
/*      PURPOSE:    Rx module functions header file                        */
/*                                                                         */
/***************************************************************************/
#ifndef _RX_DATA_H_
#define _RX_DATA_H_

#include "tw_driver.h"
#include "udata_api.h"
#include "udata.h"
#include "paramOut.h"
#include "export_inc/udata_api.h"

void  RxBufFree(void* pBuf);

#define DEF_EXCLUDE_UNENCYPTED              FALSE
#define DEF_RX_PORT_STATUS                  LINK_STATE_CLOSED

/* Rx Queue definitions */
#define RX_QUEUE_MAX_WIN_SIZE                               32
#define RX_QUEUE_ARRAY_SIZE_BIT_MASK                        (RX_QUEUE_MAX_WIN_SIZE -1)


#define SEQ_NUM_WRAP                                        0x1000
#define SEQ_NUM_MASK                                        0xFFF

#define TID_CLIENT_NONE                                     MAX_NUM_OF_802_1d_TAGS


#define BA_SESSION_SETUP_CLEAR      0
#define BA_SESSION_SETUP_SET        1

typedef struct
{
    uint32_t      excludedFrameCounter;
    uint32_t      rxDroppedDueToVLANIncludedCnt;
    uint32_t      rxWrongBssTypeCounter;
    uint32_t      rxWrongBssIdCounter;
    uint32_t       rcvUnicastFrameInOpenNotify;
    uint32_t       rxTidHlidInvalidCounter;       /* Count packets that arrive with invalid Hlid/Tid from FW */
}rxDataDbgCounters_t;

typedef struct
{
    uint32_t      recvFromWlan;
    uint32_t      recvBytesFromWlan;
    uint32_t      sendToUwd;
    uint32_t      sendToDataDispatcher;
    uint32_t      discardWrongHlid;
    uint32_t      discardHlidClose;
    uint32_t      discardBaEvent;
    uint32_t      discardUnknownClass;
}rxDataLinkCounters_t;

/*                         |                           |                         |
 31 30 29 28 | 27 26 25 24 | 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10 9 8 | 7 6 5 4 | 3 2 1 0
                           |                           |                         |
*/


typedef enum
{
    DATA_EAPOL_PACKET,
    DATA_DATA_PACKET,
    MAX_NUM_OF_RX_DATA_TYPES
}rxDataPacketType_e;


/* Rx Link Info */
typedef struct
{
    ELinkState         eState;         /* Link state */
    Bool_e             bRxDataExcludeUnencryptedUnicast;
    Bool_e             bRxDataExcludeUnencryptedBroadcast;
} TRxLinkInfo;

typedef void (*TRxDataDispatcherCb)(void *pBuffer);

/* Structure describes one entry of saved packet information in the packet queue array */
typedef struct
{
    void                *pPacket;   /* Packet address of the packet */
    uint32_t             eStatus;    /* RxXfer status. */
    uint16_t             uFrameSn;
} TRxQueuePacketEntry;

/* Structure describes set of data that of one Tid, also including the array itself */
typedef struct
{
    /* array packets Entries */
    TRxQueuePacketEntry aPaketsQueue[RX_QUEUE_MAX_WIN_SIZE];
    /* index that winStar point on */
    uint32_t          uWinStartArrayInex;
    /* windows size */
    uint32_t          uTidWinSize;
    /* expected sequence number (ESN) */
    uint16_t          uTidExpectedSn;

    uint16_t          uStoredPackets;         /* number of packets in aPacketsQueue */
    uint32_t          uMissingPktTimeStamp;   /* timestamp [ms] when detected a missing packet (if still missing BA_SESSION_TIME_TO_SLEEP [ms] later, the queued packets will be passed). 0xffffffff means no missing packets */

    void             *hInactivityTimer;
    uint32_t          uIncativityTimeoutMs;
    uint32_t          uInactivityTimeStampMs;

    uint8_t           uHlid;
    uint8_t           uTid;
    Bool_e            bInUse;
    uint8_t           uRoleId;
} TRxQueueBaDataBase;

typedef struct
{
    /* Hash table for BA session per link and Tid */
    uint8_t               aLinkTidBaIdTable[WLANLINKS_MAX_LINKS][MAX_NUM_OF_802_1d_TAGS];

    /* Pool of BA sessions */
    TRxQueueBaDataBase      aBaSessionDataBase[NUM_OF_RX_BA_SESSIONS_SUPPORTED];

    uint8_t               uNumOpenBaSessions;

} TRxQueueArraysMng;

typedef struct
{

    /* Udata handled */
    TUdata              *pUdata;

    /* Counters */
    TGlobalRxStats      rxDataCounters;
    rxDataDbgCounters_t rxDataDbgCounters;

    TRxDataDispatcherCb rxData_dispatchBuffer[LINK_STATE_NUM][MAX_NUM_OF_RX_DATA_TYPES];

    int32_t             prevSeqNum;

    tiwdrv_rate_e       eLastDataPktRate[WLANLINKS_MAX_LINKS];  /* save Rx packet rate for statistics */

    /* Info per link */
    TRxLinkInfo          aRxLinkInfo[WLANLINKS_MAX_LINKS];   /* information per link */
    rxDataLinkCounters_t rxDataLinkCounters[WLANLINKS_MAX_LINKS]; /* counters per link */

    TRxQueueArraysMng   tRxQueueArraysMng;          /* Holds BA sessions data per tid per link */

    OsiTimer_t          hMissingPktTimer;           /* missing packets timer */
    uint32_t            uMissingPktTimeoutContextId;
    uint32_t            uInactivityTimeoutContextId;
    uint8_t             uMissingPktTimerClient;     /* tid (number) the timer is running for; TID_CLIENT_NONE if not running */

    Bool_e              bBaAllowed[MAX_NUM_WLAN_ROLE_IDS];  /* Per role indication whether BA is allowed or not */
    uint8_t             uRxBaPolicy[WLANLINKS_MAX_LINKS];   /* Per link bitmap, in which each bit represents Tid */

    uint32_t            uReducedTidWinSize[WLANLINKS_MAX_LINKS];    /* IOP: This solves an IOP bug with APs that don't respect the max subframes in
                                                                            a single-frame and uses the max win_size instead. */

    uint32_t            uHostIfCfgBitmap;
}rxData_t;


typedef enum
{
    txPolicyMcs15 = 0,
    txPolicyMcs14,
    txPolicyMcs13,
    txPolicyMcs12,
    txPolicyMcs11,
    txPolicyMcs10,
    txPolicyMcs9,
    txPolicyMcs8,
    txPolicyMcs7,
    txPolicyMcs6,
    txPolicyMcs5,
    txPolicyMcs4,
    txPolicyMcs3,
    txPolicyMcs2,
    txPolicyMcs1,
    txPolicyMcs0,
    txPolicy54,
    txPolicy48,
    txPolicy36,
    txPolicy24,
    txPolicy22,
    txPolicy18,
    txPolicy12,
    txPolicy11,
    txPolicy9,
    txPolicy6,
    txPolicy5_5,
    txPolicy2,
    txPolicy1,
    MAX_NUM_OF_TX_RATES_IN_CLASS,
    TX_RATE_INDEX_ENUM_MAX_SIZE = 0xFF
} ETxRateClassId;

typedef ETxRateClassId TxRateIndex_t;


/* Public function definition */

#endif
