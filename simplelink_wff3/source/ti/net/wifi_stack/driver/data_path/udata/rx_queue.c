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
/** \file   RxQueue.c 
 *  \brief  RX Queue module that responsible to support re-ordering of received packets to upper layers.
 *  
 *  \see    RxQueue.h
 */
#define __FILE_ID__  FILE_ID_68



#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "public_share.h"
#include "tw_driver.h"
#include "timer.h"
#include "802_11defs.h"
#include "tx_data_queue_api.h"
#include "rx_defs.h"
#include "rx.h"
#include "rx_api.h"
#include "udata_api.h"
#include "udata_net_api.h"
#include "udata.h"
#include "commands.h"
#include "cc3xxx_public_commands.h"
#include "nab.h"
#include "tx.h" //for logs
#include "rx.h"
#include "drv_ti_internal.h"
#include "control_cmd_fw.h"
#include "gtrace.h"
#include "tx_ctrl.h"
#include "wlan_links.h"
#include "errors.h"
/************************ static definitions **************************************/

#define BA_SESSION_ID_NONE                                  0xff
#define BA_SESSION_TID_NONE                                 0xff
#define BA_SESSION_TIME_TO_SLEEP                            (50)
#define BA_SESSION_IS_A_BIGGER_THAN_B(A,B)                  (((((A)-(B)) & 0xFFF) < 0x7FF) && ((A)!=(B)))
#define BA_SESSION_IS_A_BIGGER_EQUAL_THAN_B(A,B)            (((((A)-(B)) & 0xFFF) < 0x7FF))
#define TID_2_BITMAP(tid)                                   (0x1 << tid)
#define ROLES_BITMAP_SET_ALL                                0xffff
#define PROTECTED_BIT_IN_80211HDR                           0x4000
#define ORDER_BIT_IN_80211HDR                               0x8000
#define EXT_IV_BIT_IN_CCMP                                  0x20
#define KEY_ID_BITS_IN_CCMP                                 0xc0
#define KEY_ID_OFFSET_IN_CCMP                               (6)
/************************ static function declaration *****************************/

static uint32_t     RxQueue_PassPacket          (uint32_t tStatus, void *pBuffer);
static uint32_t     RxQueue_CfgRxBaPolicy       (TRxQueueBaDataBase *pTidDataBase, uint8_t uHlid, uint8_t uTid, uint8_t uState);
static uint32_t     RxQueue_SendDELBA           (Edot11DelbaReasonCode eReasonCode, uint8_t uTid, uint8_t uHlid);
static uint32_t     RxQueue_SendADDBAResponse   (Edot11AddbaStatusCode eStatusCode, uint8_t uHlid, uint8_t uTid, uint8_t uDialogToken,uint8_t uAmsduPermitted);
static uint32_t     RxQueue_SendActionFrame     (uint8_t *pDataBuff, uint32_t dataLen, uint8_t uHlid, uint8_t uTid, TMgmtPacketCb fCb);
static Bool_e       IsBaSessionEstablished      (uint8_t uTid, uint8_t uHlid);
       void         rxData_MissingPktTimeout_task();
       void         rxData_ExpiryMissingPktTimeout_handler(void* hCbHndl);
       void         InactivityTimerExpire_task       ();
       void         InactivityTimer_handler(Bool_e bTwdInitOccured);
static void         RxQueue_InitBaData          (void);
static void         RxQueue_DelBaTxResultCB     (TMgmtPktReport *pTxResultInfo);
static Bool_e       CheckBroadcastPn            (ti_driver_ifData_t *pDRV, dot11_rsn_header_t *pRsnHdr, uint8_t frameTId, uint32_t uHlid);

/************************ Global paraneters declaration *****************************/
extern rxData_t *gRxDataCB;
extern txCtrl_t *gTxCtrlCB;

/************************ Structures *****************************/
typedef struct {
    NAB_header_t    nabHeader;
    CommandParam_t  commandParam ;
}CommandParamContol_t;

/**********************************************************************************/


/**
 * \brief   Stop the timer guarding the waiting for a missing packet
 *
 *          Stops the timer ONLY for the specified TID - other TID's timers will
 *          still run (if started)
 *
 * \param   uTid    index of TID timer to stop
 */
static void StopMissingPktTimer(uint8_t uTid, uint8_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;
    uint8_t           i;
    uint32_t          uMinRequestTime;
    uint8_t uNextClient;
    uint32_t          uNowMs;
    TRxQueueBaDataBase *pTidInfo =
            &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

    /* mark this TID no longer needs the timer */
    pTidInfo->uMissingPktTimeStamp = 0xffffffff;

    /* if timer was not started for this TID, don't stop it */
    if ( pRxData->uMissingPktTimerClient != uTid )
    {
        return;
    }

    uMinRequestTime = 0xffffffff;
    uNextClient = 0;
    uNowMs = osi_GetTimeMS();

    /* stop timer */
    osi_TimerStop(&pRxData->hMissingPktTimer);
    pRxData->uMissingPktTimerClient = TID_CLIENT_NONE;

    /* find the minimum request time of all link's TIDs */
    for (i = 0; i < MAX_NUM_OF_802_1d_TAGS; i++)
    {
        if (IsBaSessionEstablished(uTid, uHlid))
        {
            TRxQueueBaDataBase *pBaData =
                    &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

            if (pBaData->uMissingPktTimeStamp < uMinRequestTime)
            {
                uMinRequestTime = pBaData->uMissingPktTimeStamp;
                uNextClient = i;
            }
        }
    }

    /* restart timer if any requests left */
    if (uMinRequestTime < 0xffffffff)
    {
        osi_TimerStart(&pRxData->hMissingPktTimer, uMinRequestTime + BA_SESSION_TIME_TO_SLEEP - uNowMs, FALSE);
        pRxData->uMissingPktTimerClient = uNextClient;
    }
}

/**
 * \brief   Starts the timer guarding the waiting for a missing packet
 *
 * \param   uTid    index of TID timer to start
 */
static void StartMissingPktTimer(uint8_t uTid, uint8_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;
    /* request to clear this TID's queue */
    pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]].uMissingPktTimeStamp
       = osi_GetTimeMS();

    /* start timer (if not started already) */
    if ( pRxData->uMissingPktTimerClient == TID_CLIENT_NONE )
    {
        pRxData->uMissingPktTimerClient = uTid;
        BLOCK_ACK_PRINT_REPORT( "\r\nStartMissingPktTimer:"
                "uFrameTid:%d uHlid:%d\r\n",uTid, uHlid);

        GTRACE(GRP_DRIVER_CC33, "StartMissingPktTimer:"
                "uFrameTid:%d uHlid:%d",uTid, uHlid);


        osi_TimerStart (&pRxData->hMissingPktTimer, BA_SESSION_TIME_TO_SLEEP, FALSE);
    }
}


/**********************************************************************************/
/*                          Handling Inactivity timer                             */
/**********************************************************************************/

static void StartInactivityTimer(uint8_t uTid, uint8_t uHlid)
{
    rxData_t            *pRxData        = gRxDataCB;
    TRxQueueBaDataBase  *pTidDataBase   = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

    pTidDataBase->uInactivityTimeStampMs    = osi_GetTimeMS();

    tmr_StartTimer (pTidDataBase->hInactivityTimer, (TTimerCbFunc)InactivityTimer_handler, pRxData, pTidDataBase->uIncativityTimeoutMs, FALSE);
}

static void StopInactivityTimer(uint8_t uTid, uint8_t uHlid)
{
    rxData_t            *pRxData        = gRxDataCB;
    TRxQueueBaDataBase  *pTidDataBase   = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

    tmr_StopTimer(pTidDataBase->hInactivityTimer);
    pTidDataBase->uInactivityTimeStampMs    = 0;

}

static void ResetInactivityTimer(uint8_t uTid, uint8_t uHlid)
{
    rxData_t            *pRxData        = gRxDataCB;
    TRxQueueBaDataBase  *pTidDataBase   = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

    if (pTidDataBase->uIncativityTimeoutMs > 0)
    {
        StopInactivityTimer (uTid, uHlid);
        StartInactivityTimer(uTid, uHlid);
    }
}

void InactivityTimer_handler(Bool_e bTwdInitOccured)
{
    rxData_t *pRxData = gRxDataCB;
    uint32_t key;

    /* Request switch to driver context for handling timer events */
    trnspt_RequestSchedule (pRxData->uInactivityTimeoutContextId,FALSE);//perform InactivityTimerExpire_task
}

void InactivityTimerExpire_task()
{
    rxData_t             *pRxData        = gRxDataCB;
    uint8_t               uIndex;
    uint32_t              uNowMs         = osi_GetTimeMS();
    TRxQueueBaDataBase   *pTidDataBase;

    /* Find the BA for which the timer expired */
    for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; ++uIndex)
    {
        pTidDataBase = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex];

        /* Is there a BA session open for this Tid ? */
        if (pTidDataBase->bInUse && (pTidDataBase->uIncativityTimeoutMs>0))
        {
            /* Is timer expired ? */
            if ((uNowMs - pTidDataBase->uInactivityTimeStampMs) >= pTidDataBase->uIncativityTimeoutMs)
            {
                BLOCK_ACK_PRINT_REPORT_ERROR("\n\rDELBA:INACTIVITY TIMER expired! %u %u %u",uNowMs,pTidDataBase->uInactivityTimeStampMs,pTidDataBase->uIncativityTimeoutMs );
                GTRACE(GRP_DRIVER_CC33, "DELBA:INACTIVITY TIMER expired!");

                RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_INACTIVITY,
                                  pTidDataBase->uTid,
                                  pTidDataBase->uHlid);
            }
        }
    }
}

/**********************************************************************************/


static uint32_t RxQueue_SendADDBAResponse(Edot11AddbaStatusCode eStatusCode,
                                           uint8_t uHlid, uint8_t uTid, uint8_t uDialogToken, uint8_t uAmsduPermitted)
{
    rxData_t                *pRxData  = gRxDataCB;
    TAddbaResFrame           tAddBa;
    uint8_t                 *pPktBuffer;
    uint8_t                  pFrameData[DOT11_FRAME_BODY_LENGTH_ADDBA_RESPONSE];
    TRxQueueBaDataBase      *pTidDataBase;


    BLOCK_ACK_PRINT_REPORT("\r\nRxQueue_SendADDBAResponse for Hlid %d, Tid: %d, status: %d\r\n", uHlid, uTid, eStatusCode);
    GTRACE(GRP_DRIVER_CC33, "RxQueue_SendADDBAResponse for Hlid %d, Tid: %d, status: %d\r\n", uHlid, uTid, eStatusCode);

    tAddBa.status                   = eStatusCode;
    tAddBa.BlockAckParameterSet     = 0;
    tAddBa.dialogToken              = uDialogToken;

    /* If status code is successful then BA data is already allocated */
    if (eStatusCode == DOT11_ADDBA_RESPONSE_STATUS_CODE_SUCCESSFUL)
    {
        pTidDataBase                    = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];
        tAddBa.BlockAckTimeoutValue     = ((pTidDataBase->uIncativityTimeoutMs * 1000) / 1024); /* Timeout in TUs (1 TU = 1024 us) */

        SET_WIN_SIZE_IN_ADDBA_PARAMETER_SET  (tAddBa.BlockAckParameterSet, pTidDataBase->uTidWinSize);
    }
    else
    {
        tAddBa.BlockAckTimeoutValue = 0;
        SET_WIN_SIZE_IN_ADDBA_PARAMETER_SET  (tAddBa.BlockAckParameterSet, 0);
    }

    SET_TID_IN_ADDBA_PARAMETER_SET       (tAddBa.BlockAckParameterSet, uTid);
    SET_BA_POLICY_IN_ADDBA_PARAMETER_SET (tAddBa.BlockAckParameterSet, DOT11_ADDBA_ACK_POLICY_ACK);
    SET_AMSDU_IN_AMPDU_PARAMETER_SET     (tAddBa.BlockAckParameterSet, uAmsduPermitted);

    /* Build packet */
    pPktBuffer = pFrameData; /* Instead of allocating pPktBuffer */

    *pPktBuffer = DOT11_CATEGORY_BLOCK_ACK; /* Category */
    pPktBuffer++;
    *pPktBuffer = DOT11_ACTION_ADDBA_RESPONSE; /* Action */
    pPktBuffer++;
    *pPktBuffer = tAddBa.dialogToken;
    pPktBuffer++;
    COPY_WLAN_WORD(pPktBuffer, &tAddBa.status);
    pPktBuffer += 2;
    COPY_WLAN_WORD(pPktBuffer, &tAddBa.BlockAckParameterSet);
    pPktBuffer += 2;
    COPY_WLAN_WORD(pPktBuffer, &tAddBa.BlockAckTimeoutValue);

    return RxQueue_SendActionFrame((uint8_t*)&pFrameData,
                                  DOT11_FRAME_BODY_LENGTH_ADDBA_RESPONSE,
                                  uHlid,
                                  uTid,
                                  NULL);
}

static uint32_t RxQueue_SendDELBA(Edot11DelbaReasonCode eReasonCode, uint8_t uTid, uint8_t uHlid)
{
        TDelbaFrame           tDelba;
    uint8_t              *pPktBuffer;
    uint8_t               pFrameData[DOT11_FRAME_BODY_LENGTH_DELBA];

    //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_SendDELBA"
    //        "for Hlid %d, Tid: %d\r\n", uHlid, uTid);
    BLOCK_ACK_PRINT_REPORT ("\n\rRxQueue_SendDELBA for Hlid %d, Tid: %d", uHlid, uTid);
    GTRACE(GRP_DRIVER_CC33, "RxQueue_SendDELBA for Hlid %d, Tid: %d", uHlid, uTid);


    tDelba.reasonCode = eReasonCode;
    tDelba.DELBAParameterSet = 0;

    SET_TID_IN_DELBA_PARAMETER_SET(tDelba.DELBAParameterSet, uTid);
    SET_INITIATOR_ROLE_IN_DELBA_PARAMETER_SET(tDelba.DELBAParameterSet, DOT11_DELBA_PARAMETER_RECIPIENT);

    /* Build packet */
    pPktBuffer = pFrameData; /* Instead of allocating pPktBuffer */

    *pPktBuffer = DOT11_CATEGORY_BLOCK_ACK; /* Category */
    pPktBuffer++;
    *pPktBuffer = DOT11_ACTION_DELBA; /* Action */
    pPktBuffer++;
    COPY_WLAN_WORD(pPktBuffer, &tDelba.DELBAParameterSet);
    pPktBuffer += 2;
    COPY_WLAN_WORD(pPktBuffer, &tDelba.reasonCode);

    return RxQueue_SendActionFrame((uint8_t*)&pFrameData,
                                  DOT11_FRAME_BODY_LENGTH_DELBA,
                                  uHlid,
                                  uTid,
                                  (TMgmtPacketCb)RxQueue_DelBaTxResultCB);
}


static uint32_t RxQueue_SendActionFrame(uint8_t *pDataBuff, uint32_t dataLen,
                                         uint8_t uHlid, uint8_t uTid, TMgmtPacketCb fCb)
{

    rxData_t           *pRxData  = gRxDataCB;
    uint32_t            eStatus,total_len,extra;
    TMgmtPktDesc       *pkt;
    TMacAddr            daBssid;
    uint16_t            fc = 0;
    RoleType_e          eRoleType = pRxData->pUdata->aLinkInfo[uHlid].eRoleType;
    RoleID_t            eFwRoleId = pRxData->pUdata->aLinkInfo[uHlid].eFwRoleId;
    TTxCtrlBlk         *pPktCtrlBlk;
    dot11_mgmtHeader_t *pDot11Header;
    txCtrl_t           *pTxCtrl = gTxCtrlCB;
    uint8_t             SecureHdrLength = 0;

    BLOCK_ACK_PRINT_REPORT ("\n\rRxQueue_SendActionFrame for Hlid %d, Tid: %d", uHlid, uTid);
    GTRACE(GRP_DRIVER_CC33, "RxQueue_SendActionFrame for Hlid %d, Tid: %d", uHlid, uTid);

    /* Get source and dest addresses */
    eStatus = txDataQ_GetMacFromLink(uHlid, daBssid);
    if (eStatus != OK)
    {
        return NOK;
    }
    if(pTxCtrl->aEncryptMgmt[uHlid])
    {
        SecureHdrLength = RSN_SEC_LEN;
        BLOCK_ACK_PRINT_REPORT ("\n\rRxQueue_SendActionFrame encrypted for Hlid %d, Tid: %d", uHlid, uTid);
    }
    //HT header is always set on TX, the FW decides if to use it or remove it
    /* allocate descriptor and payload */
    extra = IEEE80211_HT_CTL_LEN + SecureHdrLength; // Add 4 bytes gap + 8 for secure,  be filled later on by the PMAC
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + sizeof(dot11_mgmtHeader_t) + extra + dataLen;

    pkt = udata_AllocTxMgmtPacket(sizeof(dot11_mgmtHeader_t) + extra,dataLen, NULL );
    if (!pkt)
    {
        RX_QUEUE_PRINT_ERROR( "\r\nRxQueue_SendActionFrame: TMgmtPktDesc allocation failed!\r\n");
        return NOK;
    }
    set_nab_tx_header(pkt->nabHeader, total_len );

    pkt->flags |= PKTF_EXTERNAL_CONTEXT;
    pkt->link = uHlid;
    pkt->ePktType = UDATA_TX_PKT_TYPE_WLAN_MGMT;
    if (fCb)
    {
        pkt->fTxCompleteCb  = fCb;
        pkt->hTxCompleteCtx = (void *)pRxData;
    }

    /* prepare WLAN header */

    pDot11Header = (dot11_mgmtHeader_t *)pkt->header;
    fc |= DOT11_FC_ACTION;
    if(SecureHdrLength)
    {
        fc |= DOT11_FC_WEP;//mngmt control
        pkt->flags |= PKTF_ENCRYPT;//descriptor
    }
    pDot11Header->fc = fc;//COPY_WLAN_WORD(&pDot11Header->fc, &fc);
    MAC_COPY (pDot11Header->DA, daBssid);
    MAC_COPY(pDot11Header->SA, pRxData->pUdata->aRoleLocalMac[eFwRoleId]); 
    if (IS_ROLE_TYPE_AP_OR_P2PGO(eRoleType))
    {
        MAC_COPY(pDot11Header->BSSID, pRxData->pUdata->aRoleLocalMac[eFwRoleId]);
    }
    else
    {
        MAC_COPY (pDot11Header->BSSID, daBssid);
    }

    /* Need to extract the CtrlBlk in order to save the TID (needed for Tx-complete handling) */
    pPktCtrlBlk = udataNet_ExtractTxCtrlBlkFromDesc(pkt);
    pPktCtrlBlk->tTxPktParams.uDelBaTidParam = uTid;

    /* copy payload */
    if (pDataBuff != NULL)
    {
        os_memcpy(pkt->payload, pDataBuff, dataLen);
    }

    /* submit for tx */
    return udata_SendTxMgmtPacket(pkt);
}


/**
 * \fn     RxQueue_CloseBaSession
 * \brief  Close BA session receiver and pass all packets in the TID queue to upper layer.
 *
 * \note
 * \param  pRxData - RxQueue handle.
 * \param  uFrameTid - TID session.
 * \return None
 * \sa
 */
static void RxQueue_CloseBaSession(uint8_t uTid, uint8_t uHlid, Bool_e bNotifyFw)
{
    rxData_t   *pRxData = gRxDataCB;
    uint32_t    i;

    /* TID illegal value ? */
    if (uTid >= MAX_NUM_OF_802_1d_TAGS)
    {
        BLOCK_ACK_PRINT_REPORT_ERROR("\r\nRxQueue_CloseBaSession: BA event TID value too big, TID = %d\r\n", uTid);
        return;
    }

    /* validate existence of BA session */
    if(IsBaSessionEstablished(uTid, uHlid))
    {
        /* Set the SA Tid pointer */
        uint8_t           uIndex          = pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid];
        TRxQueueBaDataBase  *pTidDataBase   = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex];

        if (bNotifyFw)
        {
            /* Config FW to tear down ba session (skip if link already closed) */
            if (pRxData->aRxLinkInfo[uHlid].eState != LINK_STATE_CLOSED)
            {
                RxQueue_CfgRxBaPolicy(pTidDataBase, uHlid, uTid, BA_SESSION_SETUP_CLEAR);
            }
        }

        /* Pass all valid entries at the array */
        for (i = 0; i < RX_QUEUE_MAX_WIN_SIZE; i++)
        {
            if (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)
            {
                RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                                    pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

                pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;

                pTidDataBase->uStoredPackets--;
            }

            pTidDataBase->uWinStartArrayInex ++;

            /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
            pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;
        }

        /* Stop missing packet timer for this TID */
        StopMissingPktTimer(uTid, uHlid);

        /* Stop inactivity timer */
        StopInactivityTimer(uTid, uHlid);

        pTidDataBase->bInUse = FALSE;
        pTidDataBase->uHlid = 0;
        pTidDataBase->uTid = 0;
        pTidDataBase->uRoleId = ROLE_ID_NONE;
        pRxData->tRxQueueArraysMng.uNumOpenBaSessions--;
        pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid] = BA_SESSION_ID_NONE;
    }
}

static Bool_e IsBaSessionEstablished(uint8_t uTid, uint8_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;
    if (pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid] != BA_SESSION_ID_NONE)
    {
        return TRUE;
    }
    return FALSE;
}


static void RxQueue_InitBaData(void)
{
    rxData_t *pRxData = gRxDataCB;
    uint8_t uTid, uHlid, uBaIndex;

    /* Init all BA sessions data bases */
    for (uBaIndex = 0; uBaIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; uBaIndex++)
    {
        pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaIndex].uMissingPktTimeStamp    = 0xffffffff;
        pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaIndex].hInactivityTimer        = tmr_CreateTimer();
        pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaIndex].bInUse                  = FALSE;
        pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaIndex].uTid                    = 0;
        pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaIndex].uHlid                   = 0;
    }

    /* Init hash table */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        for (uTid = 0; uTid < MAX_NUM_OF_802_1d_TAGS; uTid++)
        {
            pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid] = BA_SESSION_ID_NONE;
        }
    }

    /* Init the reduced wind size. It is used with APs that don't respect the max subframes in
    a single-frame and uses the max win_size instead. */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pRxData->uReducedTidWinSize[uHlid] = 0;
    }
}

static void RxQueue_EstablishBaSession(uint8_t uTid, uint8_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;
    uint8_t  uBaId;
    RoleID_t  uFwRoleId = pRxData->pUdata->aLinkInfo[uHlid].eFwRoleId;

    for (uBaId = 0; uBaId < NUM_OF_RX_BA_SESSIONS_SUPPORTED; uBaId++)
    {
        if (pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaId].bInUse == FALSE)
        {
            pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]   = uBaId;
            pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaId].bInUse = TRUE;
            pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaId].uHlid  = uHlid;
            pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaId].uTid   = uTid;
            pRxData->tRxQueueArraysMng.aBaSessionDataBase[uBaId].uRoleId= uFwRoleId;
            pRxData->tRxQueueArraysMng.uNumOpenBaSessions++;

            return;
        }
    }
    /* We must never get here ! */
    //Report(  REPORT_SEVERITY_ERROR, "RxQueue_EstablishBaSession:"
    //        " Failed open BA session for Tid %d and Hlid %d - No sessions left\r\n", uTid, uHlid);
}

static void RxQueue_DelBaTxResultCB(TMgmtPktReport *pTxResultInfo)
{
    uint8_t   uTid     = pTxResultInfo->uDelBaTid;
    uint8_t   uHlid    = pTxResultInfo->desc->link;

    /* Validate TID value */
    if (uTid > MAX_NUM_OF_802_1d_TAGS)
    {
       //GTRACE(1, "RxQueue_DelBaTxResultCB: FATAL ERROR: Could not get TID from packet's descID. Can't continue!!!\r\n"));
        return;
    }

    /* If BA established, and sending DELBA succeeded - close BA session */
    if (IsBaSessionEstablished(uTid, uHlid))
    {
        RxQueue_CloseBaSession(uTid, uHlid, TRUE);
    }
}


void RxQueue_EventBaConstraintCB(void *pData, uint32_t uDataLen, uint32_t  uEventId)
{
    rxData_t                *pRxData     = (rxData_t *)gRxDataCB;
    uint32_t                 uIndex;
    BaSessionRxConstraint_t *pConstraint = (BaSessionRxConstraint_t *)pData;
    RoleID_t                 uRoleId;

    BLOCK_ACK_PRINT_REPORT("\r\nRxQueue_EventBaConstraintCB: called\r\n");
    GTRACE(GRP_DRIVER_CC33,"RxQueue_EventBaConstraintCB: called");

    for (uRoleId=0; uRoleId < MAX_NUM_WLAN_ROLE_IDS; uRoleId++)
    {
        if (TI_BIT(uRoleId) & pConstraint->roleIdBitMap)
        {
            if (IS_BIT_SET(pConstraint->stateBitMap,uRoleId)) //RX_BA_SESSION_ALLOWED
            {
                pRxData->bBaAllowed[uRoleId] = TRUE;
            }
            else ///RX_BA_SESSION_NOT_ALLOWED
            {
                pRxData->bBaAllowed[uRoleId] = FALSE;

                /* If there is a BA session established for this role Id - close it */
                for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; ++uIndex)
                {
                    if ((pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].bInUse) &&           /* Is there a BA session open for this Tid ? */
                       (pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uRoleId == uRoleId))  /* Is this BA session role id the same as the event role id? */

                    {
                        BLOCK_ACK_PRINT_REPORT("\r\nDOT11_DELBA_REASON_CODE_END_BA_REASON uIndex %d\r\n", uIndex);
                        GTRACE(GRP_DRIVER_CC33,"DOT11_DELBA_REASON_CODE_END_BA_REASON uIndex %d", uIndex);
                        RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_END_BA_REASON,
                                          pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uTid,
                                          pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uHlid);
                    }
                }
            }
        }
    }
}

void RxQueue_EventRxBaWinSizeChangetCB(void *pData, uint32_t uDataLen, uint32_t  uEventId)
{
    rxData_t            *pRxData          = gRxDataCB;
    RxBaWinSizeChange_t *pBaWinSizeChange = (RxBaWinSizeChange_t *)pData;
    uint32_t             uIndex;

    BLOCK_ACK_PRINT_REPORT("\r\nRxQueue_EventRxBaWinSizeChangetCB: called\r\n");
    GTRACE(GRP_DRIVER_CC33,"RxQueue_EventRxBaWinSizeChangetCB: called");

    /* Tear down the BA session for the requested link and save the new window size */
    for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; ++uIndex)
    {
        uint8_t uTid = pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uTid;
        uint8_t uHlid = pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uHlid;

        if ((uHlid != pBaWinSizeChange->linkId) || !IsBaSessionEstablished(uTid, uHlid) )
            continue;

        /* Save the new window size */
        pRxData->uReducedTidWinSize[uHlid] = pBaWinSizeChange->rxBaWinSize;

        BLOCK_ACK_PRINT_REPORT("\r\nRxQueue_EventRxBaWinSizeChangetCB closing for HLID %d\r\n", uHlid);
        GTRACE(GRP_DRIVER_CC33,"RxQueue_EventRxBaWinSizeChangetCB closing for HLID %d", uHlid);
        /* force a DELBA frame */
        RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_UNSPECIFIED, uTid, uHlid);
        RxQueue_CloseBaSession(uTid, uHlid, TRUE);
    }
}

/**
* RXQueue_CmdCallback - free the pointer of current cmd
*
* @param cmdStatus - Status of current cmd
* @param ptr - Pointer of current cmd
*/

void RXQueue_CmdCallback(int cmdStatus,void *ptr)
{
    if(NULL != ptr)
    {
        os_free(ptr);
    }
}

/* Config FW with RX BA policy
 *
 * Param uIndex is the index of the BA data in the array of possible sessions.
 * It is used for holding the same info in TWD for recovery
 */
static uint32_t RxQueue_CfgRxBaPolicy(TRxQueueBaDataBase *pTidDataBase,
                                      uint8_t uHlid,
                                      uint8_t uTid,
                                      uint8_t uState)
{
    CommandParamContol_t *cmd = NULL;
    Cfg_t cmdParams;
    RxBaSessionCfg_t baSessionCfg;
    
    cmd = os_malloc(sizeof(CommandParamContol_t));
    if (cmd == NULL)
    {
        return WlanError(WLAN_ERROR_SEVERITY__MID,
                         WLAN_ERROR_MODULE__TRANSPORT,
                         WLAN_ERROR_TYPE__MALLOC);
    }
    os_memset(cmd, 0x0, sizeof(CommandParamContol_t));
    os_memset(&cmdParams, 0x0, sizeof(Cfg_t));

    cmd->nabHeader.opcode       = CMD_CONFIGURE;
    cmd->nabHeader.sync_pattern = HOST_SYNC_PATTERN;
    cmd->commandParam.cmdID     = CMD_CONFIGURE;
    cmdParams.id                = BA_SESSION_RX_SETUP;
    cmdParams.length            = sizeof(RxBaSessionCfg_t);

    baSessionCfg.linkId = uHlid;
    baSessionCfg.tid = uTid;
    baSessionCfg.enable = uState;

    if (uState == BA_SESSION_SETUP_SET)
    {
        baSessionCfg.ssn = pTidDataBase->uTidExpectedSn;
    }
    else
    {
        baSessionCfg.ssn = 0;
    }
    baSessionCfg.win_size = pTidDataBase->uTidWinSize;

    /* Copy the data to the FW command */
    os_memcpy(&(cmdParams.ex.RxBaSession), &baSessionCfg, cmdParams.length);
    os_memcpy(cmd->commandParam.param, &cmdParams, sizeof(Cfg_t));

    cmd->nabHeader.len = ALIGNN_TO_4(sizeof(NAB_header_t) + sizeof(cmd->commandParam.cmdID) + sizeof(Cfg_t));

    BLOCK_ACK_PRINT_REPORT("\r\nBLOCK_ACK uState;%d ssn:%d win_size:%d",uState, baSessionCfg.ssn , baSessionCfg.win_size);
    GTRACE(GRP_DRIVER_CC33,"BLOCK_ACK uState;%d ssn:%d win_size:%d",uState, baSessionCfg.ssn , baSessionCfg.win_size);

    return cmd_SendInTransport((char*)cmd, cmd->nabHeader.len,RXQueue_CmdCallback,cmd);

}

static uint32_t RxQueue_configureFw(void)
{
    //TWD_RegisterEvent(TWD_OWN_BA_SESSION_RX_CONSTRAINT, RxQueue_EventBaConstraintCB, pRxData, ROLE_NONE);
    //TWD_RegisterEvent(TWD_OWN_EVENT_RX_BA_WIN_SIZE_CHANGE, RxQueue_EventRxBaWinSizeChangetCB, pRxData, ROLE_NONE);
    return OK;
}

/** 
 * \fn     RxQueue_Init() 
 * \brief  Init RxQueue internals (handle already initiated in rx.c)
 * 
 * Init RxQueue internals variables.
 * 
 * \note    
 * \param  pRxData - The module object
 * \
 * \return OK on success or NOK on failure  
 * \sa     
 */ 
uint32_t RxQueue_Init (void)
{
    rxData_t *pRxData = gRxDataCB;
    uint32_t  aStatus;
    uint8_t   RoleId;

    osi_TimerCreate(&pRxData->hMissingPktTimer, "TMissingPktTimer", rxData_ExpiryMissingPktTimeout_handler,(void *)NULL);
    pRxData->uMissingPktTimerClient     = TID_CLIENT_NONE;

    for (RoleId = 0; RoleId < MAX_NUM_WLAN_ROLE_IDS ;RoleId++)
    {
        pRxData->bBaAllowed[RoleId] = TRUE;
    }

    aStatus = RxQueue_configureFw();
    if (aStatus != OK)
    {
        //Report(REPORT_SEVERITY_ERROR, "RxQueue_Init: Call TWD_RegisterEvent"
        //        "for event BA_SESSION_RX_CONSTRAINT_EVENT_ID failed\r\n");
        return NOK;
    }

    RxQueue_InitBaData();

    pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter = 0;
    pRxData->tRxQueueArraysMng.uNumOpenBaSessions = 0;

    return OK;
}

uint32_t RxQueue_DeInit (void)
{
    rxData_t    *pRxData = gRxDataCB;
    uint8_t      uIndex;

    for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; uIndex++)
    {
        tmr_DestroyTimer(pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].hInactivityTimer);
    }
    return OK;
}

uint32_t RxQueue_NotifyFwReset(void)
{
    return RxQueue_configureFw();
}


void RxQueue_CloseAllBaSessions(void)
{
    rxData_t *pRxData = gRxDataCB;
    uint32_t   uIndex;
    uint8_t    RoleId;

    //Report(REPORT_SEVERITY_INFORMATION , "RxQueue_CloseAllBaSessions called\r\n");

    /* close all BA sessions */
    /* Note: this function is called only upon FW reset (recovery), so we notify not to send related commands to FW. */
    for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; ++uIndex) {
        uint8_t uTid = pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uTid;
        uint8_t uHlid = pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uHlid;

        if(!IsBaSessionEstablished(uTid, uHlid))
            continue;

        BLOCK_ACK_PRINT_REPORT_ERROR("\r\nRxQueue_CloseAllBaSessions closing for HLID %d\r\n", uHlid);
        /* force a DELBA frame */
        RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_UNSPECIFIED, uTid, uHlid);
        RxQueue_CloseBaSession(uTid, uHlid, FALSE);
    }

    /* The FW is reset so start again from the default state (BA enabled for all roles) */
    for (RoleId = 0; RoleId < MAX_NUM_WLAN_ROLE_IDS ;RoleId++)
    {
        pRxData->bBaAllowed[RoleId] = TRUE;
    }
}

/* Close all BA sessions that are related with one specific link */
void RxQueue_CloseAllLinkBaSessions(uint8_t uHlid)
{
    rxData_t *pRxData = gRxDataCB;
    uint32_t  uIndex;

    //Report(REPORT_SEVERITY_INFORMATION , "RxQueue_CloseAllLinkBaSessions called for Hlid: %d\r\n", uHlid);

    /* Go over all sessions */
    for (uIndex = 0; uIndex < NUM_OF_RX_BA_SESSIONS_SUPPORTED; ++uIndex)
    {
        /* If the session is open and is related with the requested Hlid - close it, including sending related command to FW */

        /* Note: If we got here during recovery process, we must have already called RxQueue_CloseAllBaSessions,
         *        so all sessions are already closed. This is why we don't mind setting the last param to TRUE anyway.
         */
        if ((pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uHlid == uHlid) &&
            (pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].bInUse))
        {
            RxQueue_CloseBaSession(pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uTid,
                                   pRxData->tRxQueueArraysMng.aBaSessionDataBase[uIndex].uHlid,
                                   FALSE); //TODO: needed to verify
        }
    }

    /* Init also the reduced win size for IOP bug with APs that don't respect the max subframes in
    a single-frame and uses the max win_size instead. */
    pRxData->uReducedTidWinSize[uHlid] = 0;
}

/**
 * \fn     RxQueue_CheckPnReplyAttack
 * \brief  Check for PN reply attack on received frames, for both broadcast
 *         and unicast frames.
 *
 * \note
 * \param  pBuffer - RXed frame.
 * \return TRUE if PN reply attack detected, FALSE otherwise.
 * \sa
 */
static Bool_e RxQueue_CheckPnReplyAttack(void *pBuffer)
{
    RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t *)pBuffer;
    dot11_header_t *pHdr;
    uint16_t uQosControl;
    uint8_t *pFrame;

    pFrame = RX_BUF_DATA(pBuffer);
    pHdr = (dot11_header_t *)pFrame;

    uQosControl = pHdr->qosControl;
    /*
     * Check if packet has RSN header for PN replay detection 
     * Validate that PN number of the Rx frame higher that last frame with the same key ID
     */
    if ((pHdr->fc & PROTECTED_BIT_IN_80211HDR)) // Check protected bit on frame control 
    {
        dot11_rsn_header_t *pRsnHdr = NULL;
        uint8_t uFrameTid = uQosControl & DOT11_QOS_CONTROL_FIELD_TID_BITS;
        uint8_t uFrameHlid = pRxParams->hlid;

        /* Update pointer for RSN header (note: dot11_header_t has qosControl field) */
        if (IS_QOS_FRAME(*(uint16_t*)pFrame))
        {
            pRsnHdr = (dot11_rsn_header_t *)(pFrame + sizeof(dot11_header_t));
        }
        else
        {
            pRsnHdr = (dot11_rsn_header_t *)(pFrame + sizeof(dot11_header_t) - sizeof(pHdr->qosControl));
        }
        
        /* Advance 4 extra bytes in IEEE80211 header if order bit is on (mostly 11ax support) */
        if (pHdr->fc & ORDER_BIT_IN_80211HDR)
        {
            pRsnHdr = (dot11_rsn_header_t *)(((uint8_t *)pRsnHdr) + 4);
        }

        /* Check PN reply only if extended IV is on */
        if (pRsnHdr->extIVkeyID & EXT_IV_BIT_IN_CCMP)
        {
            /* Multicast or broadcast frame PN test */
            if (is_broadcast_ether_addr(pHdr->address1) ||
                is_multicast_ether_addr(pHdr->address1))
            {
                ti_driver_ifData_t *pDrv;

                pDrv = drv_getDriverFromDescriptor(pRxParams);
                if (pDrv == NULL)
                {
                    GTRACE(GRP_DRIVER_CC33, "pDrv is NULL, dropping packet");
                    return TRUE;
                }

                if (CheckBroadcastPn(pDrv, pRsnHdr, uFrameTid, uFrameHlid) == FALSE)
                {
                    GTRACE(GRP_DRIVER_CC33, "RxQueue_CheckPnReplyAttack: BAD PN drop broadcast packet");
                    return TRUE;
                }
            }
            /* Unicast frame PN test */
            else
            {
                if ((wlanLinks_CheckLinkPn(uFrameHlid, pRsnHdr, uFrameTid, pRxParams->status & RX_DESC_STATUS_NEW_KEY)) == FALSE)
                {
                    GTRACE(GRP_DRIVER_CC33, "RxQueue_CheckPnReplyAttack: BAD PN drop unicast packet");
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/** 
 * \fn     RxQueue_PassPacket()
 * \brief  Responsible on decode packet parameters and pass it to upper layer.
 *
 * \note   
 * \param  eStatus - RxXfer status that indicate if the upper layer should free the packet or use it.
 * \param  pFrame  - Address of the packet.
 * \return OK on success or NOK on failure 
 * \sa     
 */ 
static uint32_t RxQueue_PassPacket(uint32_t eStatus, void *pBuffer)
{
    if (eStatus == OK)
    {
        //dot11_header_t *pMacHdr;
        RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t*)pBuffer;
        Bool_e pnReplyAttackDetected = RxQueue_CheckPnReplyAttack(pBuffer);


        if (pnReplyAttackDetected)
        {
            RxBufFree(pBuffer);
            return OK;
        }
    }
    else
    {
        RxIfDescriptor_t *pRxParams = (RxIfDescriptor_t*)pBuffer;


        if (eStatus == (uint32_t)RX_DESC_HOST_UNWANTED_SEQUENCE_NUMBER)
        {
            /* Packet with unwanted sequence number (either frame sequence number already passed or lower than expected sequence number) */
            RxBufFree((void*)pBuffer);
            return OK;
        }
        else if (eStatus != (uint32_t)RX_DESC_HOST_STATUS_HANDLED)

        {
            GTRACE(GRP_DRIVER_CC33, "RxQueue_PassPacket: Error! received packet with status error %d", eStatus);
            RX_PRINT_ERROR("\n\rERROR RxQueue_PassPacket : Error! received with status error eStatus:%d",eStatus);//it happens a lot that is the reason rX_PRINT is used
        }
    }

    /* Set the packet to upper layer */
    /* if the packet status not success it will be discarded */
    rxData_ReceivePacket((void *)pBuffer);

    return OK;
}

/** 
 * \fn     CheckBroadcastPn()
 * \brief  Responsible on Validate packet PN for broadcast frame and drop it if invalid PN.
 *
 * \note   
 * \param  pDRV      - pointer to driver instant.
 * \param  pRsnHdr   - pointer to RSN header.
 * \param  frameTId  - frameTID
 * \param  uHlid     - frame linkID.
 * \return OK on success or NOK on failure 
 * \sa     
 */ 
static Bool_e CheckBroadcastPn(ti_driver_ifData_t *pDRV, dot11_rsn_header_t *pRsnHdr, uint8_t frameTId, uint32_t uHlid)
{
    uint16_t pn0_15 = WPA_GET_LE16 (&(pRsnHdr->pn0));
    uint32_t pn16_47 = WPA_GET_LE32 (&(pRsnHdr->pn2));
    uint8_t keyID = ((pRsnHdr->extIVkeyID & KEY_ID_BITS_IN_CCMP) >> KEY_ID_OFFSET_IN_CCMP) - 1;

    HOOK(HOOK_WLAN_LINKS);

    if (uHlid >= WLANLINKS_MAX_LINKS)
        return FALSE;

    if (pDRV->broadcastPn[keyID].rxPN32[frameTId] > pn16_47)
        return FALSE;
    if (pDRV->broadcastPn[keyID].rxPN32[frameTId] == pn16_47)
    {
        if (pDRV->broadcastPn[keyID].rxPN16[frameTId] >= pn0_15)
            return FALSE;
        pDRV->broadcastPn[keyID].rxPN16[frameTId] = pn0_15;
        return TRUE;
    }

    pDRV->broadcastPn[keyID].rxPN32[frameTId] = pn16_47;
    pDRV->broadcastPn[keyID].rxPN16[frameTId] = pn0_15;    

    return TRUE;
}

/** 
 * \fn     RxQueue_ReceivePacket()
 * \brief  Main function of the RxQueue module. 
 * Responsible for handling RX BA session (including reorder buffers).
 * Called from RxXfer in order to pass packet to uppers layers.
 * When BA session is established, it is assigned with a data structure that holds
 * all the information including the buffer itself, in which each entry describe a packet.
 * The array elements are sorted in the way that the winStart array index represent always
 * the winStart packet and the lowest SN.
 * Each increment index represent index at the BA window. Array index winEnd always
 * represent winEnd packet. The indexes of winStart and winEnd handled cyclicly.
 *
 * SN range      :  0 - 4095
 * winStart range:  0 - 31       [0 - (RX_QUEUE_MAX_WIN_SIZE - 1)]
 * winSize       :  Determined by the BA session. We limit it to maximum 32 [RX_QUEUE_MAX_WIN_SIZE]
 * winEnd        :  = winStart + winSize - 1
 *
 * The function functionality divided to parts:
 *   Part 1:
 * In case the module received a packet with SN equal to the expected SN:
 * "    pass it to upper layers
 * "    increases winStart and array index winStart
 * "    validate that all sequential queue packet are pass to the upper layers.
 *   Part 2:
 * In case the module received a packet with SN between winStart to winEnd:
 * "    Save it sorted at the array at index: Save index = ((SN - winStart) + index array winStart) % arraySize.
 *   Part 3:
 * In case the module received a packet with SN higher than winEnd:
 * "    Update winStart and WinEnd.
 * "    Save it sorted at the array in index winEnd index.
 * "    Pass to the upper layers all packets at the array indexes from old winStart index to the updated winStart index.
 *   Part 4 + 5:
 * In case the module received a BA event packet: [Remember: This is an Rx module - We expect BAR and not BA (as well as ADDBE / DELBA]
 * "    Update winStart and WinEnd
 * "    Pass to the upper layers all packets at the array indexes from old winStart index to the updated winStart index.
 * "    Free BA event packet via pass it to upper layers with error status.
 *
 * \note   
 * \param  pRxData - RxQueue handle.
 * \param  aStatus - RxXfer status that indicates whether the upper layer should free the packet or use it.
 * \param  pBuffer - Address of the packet [contains the RxIfDescriptor_t added by the FW].
 * \return None 
 * \sa     
 */ 
void RxQueue_ReceivePacket(uint8_t * pBuffer, uint32_t len)
{
    rxData_t            *pRxData    = gRxDataCB;
    RxIfDescriptor_t    *pRxParams  = (RxIfDescriptor_t*)pBuffer;

    uint32_t             eStatus    = OK;
    uint8_t             *pFrame;
    dot11_header_t      *pHdr;
    uint16_t             uQosControl;
    uint8_t              uFrameHlid;
    PacketClassTag_enum  class;


    /* 
     * Retrieving the TAG from the packet itself and not from the Rx Descriptor since by now it is not correct.
     * If the packet is a QoS packet but the tag is not TAG_CLASS_QOS_DATA or TAG_CLASS_AMSDU - force TAG_CLASS_QOS_DATA or TAG_CLASS_AMSDU.
     *
     * Note: in the DR TAG_CLASS_EAPOL packet handled as TAG_CLASS_QOS_DATA   
     */
     
    pFrame = RX_BUF_DATA(pBuffer);

    pHdr = (dot11_header_t *)pFrame;
    uQosControl = pHdr->qosControl;//COPY_WLAN_WORD(&uQosControl, &pHdr->qosControl); /* copy with endianess handling. */
    class = rxData_GetCRxClassification(pBuffer);

    if (IS_QOS_FRAME(*(uint16_t*)pFrame) && (class != TAG_CLASS_QOS_DATA) && (class != TAG_CLASS_AMSDU))
    {
        //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: BAD CLASS TAG =0x%x from FW.\r\n", pRxParams->packet_class_tag);
        RX_PRINT("\n\rRxQueue_ReceivePacket: BAD CLASS TAG =0x%x from FW.", class);


        /* Get AMSDU bit from frame */
        if( uQosControl & DOT11_QOS_CONTROL_FIELD_A_MSDU_BITS)
        {
            class = TAG_CLASS_AMSDU;
        }
        else
        {
            class = TAG_CLASS_QOS_DATA;
        }
    }

    /* Packet doesn't need reorder ? */

    if ((class != TAG_CLASS_QOS_DATA) && (class != TAG_CLASS_BA_EVENT) && (class != TAG_CLASS_AMSDU))
    {
        //Report(REPORT_SEVERITY_INFORMATION , "RxQueue_ReceivePacket: pass packet without reorder (doesn't need reorder).\r\n");
        RX_PRINT("\n\rRxQueue_ReceivePacket: pass packet without reorder (doesn't need reorder). class:%d", class);

        RxQueue_PassPacket (OK, pBuffer);

        return;
    }

    /* Get HLID from frame */
    uFrameHlid = pRxParams->hlid;

    /* Validate HLID value */
    if (uFrameHlid >= WLANLINKS_MAX_LINKS)
    {
        //Report(REPORT_SEVERITY_ERROR, "RxQueue_ReceivePacket: HLID value too big, "
        //        "packet discarded!  HLID = %d, Max HLID = %d\r\n",
        //        uFrameHlid, WLANLINKS_MAX_LINKS);

    	RX_PRINT_ERROR("\n\rRxQueue_ReceivePacket: HLID value too big,HLID = %d, Max HLID = %d",
                  uFrameHlid, WLANLINKS_MAX_LINKS);

        pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter++;

        RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

        return;
    }

    /* pRxParams->type == TAG_CLASS_QOS_DATA ? */

    if ((class== TAG_CLASS_QOS_DATA) || (class == TAG_CLASS_AMSDU))
    {
        uint8_t             uFrameTid;
        uint16_t            uFrameSn;
        uint16_t            uSequenceControl;
        TRxQueueBaDataBase  *pTidDataBase;
        uint8_t             uSessionIndex;

        /* Get TID from frame */
        uFrameTid = uQosControl & DOT11_QOS_CONTROL_FIELD_TID_BITS;

        //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: QoS Packet received\r\n");
        //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: uFrameTid = 0x%x(%d)\r\n",uFrameTid,uFrameTid);

        uSessionIndex = pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uFrameHlid][uFrameTid];

        /* Packet TID BA session not established ? */
        if (pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uFrameHlid][uFrameTid] == BA_SESSION_ID_NONE)
        {
            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: pass packet without reorder (No BA).\r\n");
            RX_PRINT("\n\rRxQueue_ReceivePacket: pass packet without reorder (No BA).");

            RxQueue_PassPacket (OK, pBuffer);

            return;
        }

        //BA session
        /* Set the SA Tid pointer */
        pTidDataBase = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[uSessionIndex];

        /* If frame is part of aggregation OR ack policy is BA -  reset inactivity timer */
        if ((pRxParams->flags & RX_DESC_A_MPDU) ||
            (DOT11_QOS_CONTROL_BLOCK_ACK == (uQosControl & DOT11_QOS_CONTROL_FIELD_ACK_POLICY_BITS)))
        {
            ResetInactivityTimer(uFrameTid, uFrameHlid);
        }

        /* Get Sequence Number from frame */
        uSequenceControl = pHdr->seqCtrl;//COPY_WLAN_WORD(&uSequenceControl, &pHdr->seqCtrl); /* copy with endianess handling. */
        uFrameSn = (uSequenceControl & DOT11_SC_SEQ_NUM_MASK) >> 4;

        BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: uFrameSn = 0x%x(%d)", uFrameSn, uFrameSn);
        BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)",pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);


        //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: uFrameSn = 0x%x(%d)\r\n", uFrameSn, uFrameSn);
        //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)\r\n",pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);

        /*
         * Note:
         * The FW never sends packet, in establish TID BA, with SN less than ESN !!!
         */


        /* Part 1 - Received Frame Sequence Number is the expected one ? */
        if (uFrameSn == pTidDataBase->uTidExpectedSn)
        {
            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: frame Sequence Number == expected one Sequence Number.\r\n");


            /*
               If the expected SN received and timer was running - Stop the timer.

               If we wait for more than one packet we should not stop the timer - This is why we are checking after the while loop, if we have
               more packets stored, and if we have, we start the timer again.
            */
            if (pTidDataBase->uMissingPktTimeStamp != 0xffffffff)
            {
                StopMissingPktTimer(uFrameTid, uFrameHlid);
            }

            /* Pass the packet */
            RxQueue_PassPacket (OK, pBuffer);

            /* Increase expected SN to the next */
            pTidDataBase->uTidExpectedSn++;
            pTidDataBase->uTidExpectedSn &= 0xfff;  /* SN is 12 bits long */

            /* Increase the ArrayInex to the next */
            pTidDataBase->uWinStartArrayInex++;

            /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
            pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;


            /* Pass all saved queue consecutive packets with SN higher than the expected one */
            while (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)
            {
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Pass all saved queue packets with SN higher than the expected one that was just received.");
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aWinStartArrayInex = 0x%x(%d)", pTidDataBase->uWinStartArrayInex, pTidDataBase->uWinStartArrayInex);

                BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: Pass all saved queue packets with SN higher than the expected one that was just received.");
                BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);
                BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: aWinStartArrayInex = 0x%x(%d)", pTidDataBase->uWinStartArrayInex, pTidDataBase->uWinStartArrayInex);

                RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                                    pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

                pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;

                pTidDataBase->uWinStartArrayInex++;

                /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
                pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

                pTidDataBase->uTidExpectedSn++;
                pTidDataBase->uTidExpectedSn &= 0xfff; /* SN is 12 bits long */

                /* Decrease the packets in queue */
                pTidDataBase->uStoredPackets--;
            }


            /* aTidExpectedSn % 0xfff in order to tack care of wrap around */
            pTidDataBase->uTidExpectedSn &= 0xfff;

            /* If there are still packets stored in the queue - start timer */
            if (pTidDataBase->uStoredPackets)
            {
                StartMissingPktTimer(uFrameTid, uFrameHlid);
            }

            return;
        }

        /* Frame Sequence Number is lower than Expected sequence number (ISN) ? */
        if (! BA_SESSION_IS_A_BIGGER_THAN_B (uFrameSn, pTidDataBase->uTidExpectedSn))
        {
            //Report(REPORT_SEVERITY_WARNING, "RxQueue_ReceivePacket: frame Sequence Number (%d) is lower than expected sequence number (%d).\r\n", uFrameSn, pTidDataBase->uTidExpectedSn);
            BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: frame Sequence Number (%d) is lower than expected sequence number (%d).", uFrameSn, pTidDataBase->uTidExpectedSn);
            GTRACE(GRP_DRIVER_CC33,"RxQueue_ReceivePacket: frame Sequence Number (%d) is lower than expected sequence number (%d).", uFrameSn, pTidDataBase->uTidExpectedSn);

            RxQueue_PassPacket (RX_DESC_HOST_UNWANTED_SEQUENCE_NUMBER, pBuffer);
            return;
        }

        /* Part 2 - Frame Sequence Number between winStart and winEnd ? */
        if ((BA_SESSION_IS_A_BIGGER_THAN_B (uFrameSn, pTidDataBase->uTidExpectedSn)) &&
            /* mean: uFrameSn <= pTidDataBase->aTidExpectedSn + pTidDataBase->aTidWinSize) */
            ( ! BA_SESSION_IS_A_BIGGER_THAN_B (uFrameSn,(pTidDataBase->uTidExpectedSn + pTidDataBase->uTidWinSize - 1))))
        {
            uint16_t uSaveIndex = pTidDataBase->uWinStartArrayInex + (uint16_t)((uFrameSn + SEQ_NUM_WRAP - pTidDataBase->uTidExpectedSn) & SEQ_NUM_MASK);

            /* uSaveIndex % RX_QUEUE_MAX_WIN_SIZE */
            uSaveIndex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

            //BLOCK_ACK_PRINT_REPORT( "\n\rRxQueue_ReceivePacket: frame Sequence Number between winStart and winEnd uFrameSn:%d.\r\n", uFrameSn);
            //BLOCK_ACK_PRINT_REPORT( "\n\rRxQueue_ReceivePacket: uSaveIndex = 0x%x(%d)",uSaveIndex,uSaveIndex);

            /* Before storing packet in queue, make sure the place in the queue is vacant */
            if (pTidDataBase->aPaketsQueue[uSaveIndex].pPacket == NULL)
            {
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Enter packet to Reorder Queue");
                BLOCK_ACK_PRINT_REPORT( "RxQueue_ReceivePacket: Enter packet to Reorder Queue\r\n");

                /* Store the packet in the queue */
                pTidDataBase->aPaketsQueue[uSaveIndex].eStatus  = eStatus;
                pTidDataBase->aPaketsQueue[uSaveIndex].pPacket  = (void *)pBuffer;
                pTidDataBase->aPaketsQueue[uSaveIndex].uFrameSn = uFrameSn;

                pTidDataBase->uStoredPackets++;


                /* Start Timer */
                StartMissingPktTimer(uFrameTid, uFrameHlid);
            }
            else
            {
                 //Report(REPORT_SEVERITY_WARNING, "RxQueue_ReceivePacket: frame Sequence has already saved. uFrameSn = %d\r\n", uFrameSn);
                 BLOCK_ACK_PRINT_REPORT("\n\rRxQueue_ReceivePacket: frame Sequence has already saved. uFrameSn = %d", uFrameSn);

                 RxQueue_PassPacket (RX_DESC_HOST_UNWANTED_SEQUENCE_NUMBER, pBuffer);
                 return;
            }

            return;
        }


        /*
        Part 3 - Frame Sequence Number higher than winEnd ?
        */
        if ( BA_SESSION_IS_A_BIGGER_THAN_B (uFrameSn, (pTidDataBase->uTidExpectedSn + pTidDataBase->uTidWinSize - 1)) )
        {
            uint32_t i;
            uint16_t uNewWinStartSn = (uFrameSn + SEQ_NUM_WRAP - pTidDataBase->uTidWinSize + 1) & SEQ_NUM_MASK;
            uint16_t uSaveIndex;


            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: frame Sequence Number higher than winEnd.\r\n");
            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: uNewWinStartSn = 0x%x(%d) STOP TIMER\r\n", uNewWinStartSn, uNewWinStartSn);

            /* stop timer */
            if (pTidDataBase->uMissingPktTimeStamp != 0xffffffff)
            {
                StopMissingPktTimer(uFrameTid, uFrameHlid);
            }

            /* Increase the ArrayInex to the next */
            pTidDataBase->uWinStartArrayInex++;

            /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
            pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

            /* Update the Expected SN since the current one is lost */
            pTidDataBase->uTidExpectedSn++;
            pTidDataBase->uTidExpectedSn &= 0xFFF;

            /* Pass all saved queue packets with SN lower than the new win start */
            for (i = 0;
                 BA_SESSION_IS_A_BIGGER_THAN_B(uNewWinStartSn, pTidDataBase->uTidExpectedSn) &&
                  (i < RX_QUEUE_MAX_WIN_SIZE) &&
                  (i < pTidDataBase->uTidWinSize);
                 i++)
            {
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)\r\n", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aWinStartArrayInex = 0x%x(%d)\r\n", pTidDataBase->uWinStartArrayInex,pTidDataBase->uWinStartArrayInex);

                if (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)
                {
                    //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Send Packet to Upper layer\r\n");
                    RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                                        pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

                    pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;

                    pTidDataBase->uStoredPackets--;
                }

                pTidDataBase->uWinStartArrayInex++;

                /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
                pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

                pTidDataBase->uTidExpectedSn++;
                pTidDataBase->uTidExpectedSn &= 0xFFF;

            }

            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)\r\n", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);
            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: i = %d\r\n",i);


            /* Calculate the new Expected SN */
            if (i == pTidDataBase->uTidWinSize)
            {
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Set aTidExpectedSn to uNewWinStartSn\r\n");
                pTidDataBase->uTidExpectedSn = uNewWinStartSn;
            }
            else
            {
                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Send all saved packets\r\n");
                /* In case the uWinStartDelta lower than aTidWinSize - check if there are packets stored in Array */

                while (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)
                {
                    //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Send packet with SN = 0x%x(%d)\r\n", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);

                    RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                                        pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

                    pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;

                    pTidDataBase->uWinStartArrayInex++;

                    /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
                    pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

                    pTidDataBase->uTidExpectedSn++;
                    pTidDataBase->uTidExpectedSn &= 0xFFF;


                    pTidDataBase->uStoredPackets--;
                }
            }

            //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: aTidExpectedSn = 0x%x(%d)\r\n", pTidDataBase->uTidExpectedSn, pTidDataBase->uTidExpectedSn);

            if(pTidDataBase->uTidExpectedSn == uFrameSn)
            {
                BLOCK_ACK_PRINT_REPORT ("\r\nRxQueue_ReceivePacket: Send current packet to upper layer\r\n");
                GTRACE(GRP_DRIVER_CC33,"RxQueue_ReceivePacket: Send current packet to upper layer");

                /* pass the packet */
                RxQueue_PassPacket (eStatus, pBuffer);

                pTidDataBase->uTidExpectedSn++;
                pTidDataBase->uTidExpectedSn &= 0xfff;
            }
            else
            {
                uSaveIndex = pTidDataBase->uWinStartArrayInex + (uint16_t)((uFrameSn + SEQ_NUM_WRAP - pTidDataBase->uTidExpectedSn) & SEQ_NUM_MASK);

                BLOCK_ACK_PRINT_REPORT( "\r\nRxQueue_ReceivePacket: Enter current packet to Reorder Queue\r\n");
                BLOCK_ACK_PRINT_REPORT( "\r\nRxQueue_ReceivePacket: uSaveIndex = 0x%x(%d)\r\n", uSaveIndex, uSaveIndex);

                /* uSaveIndex % RX_QUEUE_MAX_WIN_SIZE */
                uSaveIndex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

                /* Save the packet in the last entry of the queue */
                pTidDataBase->aPaketsQueue[uSaveIndex].eStatus = eStatus;
                pTidDataBase->aPaketsQueue[uSaveIndex].pPacket = (void *)pBuffer;
                pTidDataBase->aPaketsQueue[uSaveIndex].uFrameSn = uFrameSn;

                pTidDataBase->uStoredPackets++;
            }



            /* aTidExpectedSn % 0xfff in order to take care of wrap around */
            pTidDataBase->uTidExpectedSn &= 0xfff;

            /* If there are still packets stored in the queue - start timer */
            if (pTidDataBase->uStoredPackets)
            {
                StartMissingPktTimer(uFrameTid, uFrameHlid);
            }

            return;
        }
    }

    /* BA event ? */

    if (class == TAG_CLASS_BA_EVENT)
    {

        TRxQueueBaDataBase *pTidDataBase;
        uint8_t           uSessionIndex;
        uint8_t            *pDataFrameBody;
        uint16_t           ufc;
        uint8_t            uFrameTid;
        uint8_t            uAmsduPermitted;
        uint8_t           uDialogToken;
        uint16_t           uStartingSequenceNumber;
        uint16_t           uWinStartDelta;
        uint16_t           uBarControlField;
        uint16_t           uBaStartingSequenceControlField;
        uint16_t           uBAParameterField;
        uint16_t          uInactivityTimeout;
        uint8_t           uInitiatorBit;
        uint32_t           i;
        uint8_t           uControlledLink;
        RoleID_t            eFwRoleId;

        BLOCK_ACK_PRINT_REPORT("\n\r RxQueue_ReceivePacket: BA event");

        /* Get the frame's sub type from its header */
        ufc = pHdr->fc;//COPY_WLAN_WORD(&ufc, &pHdr->fc); /* copy with endianess handling. */

        /* Get the type to BA event */
        switch ((dot11_Fc_Sub_Type_e)(ufc & DOT11_FC_SUB_MASK))
        {
        case DOT11_FC_SUB_BAR://block ack request, bar is never encrypted
        {
            uint16_t fc;

            fc = le_to_host16((uint16_t)(*((uint16_t*)&pHdr->fc)));

            BLOCK_ACK_PRINT_REPORT("\n\r RxQueue_ReceivePacket: BA event - BAR frame :DOT11_FC_SUB_BAR recv");
            GTRACE(GRP_DRIVER_CC33,"RxQueue_ReceivePacket: BA event - BAR frame :DOT11_FC_SUB_BAR recv");

            /* get pointer to the frame body */
            pDataFrameBody = pFrame + sizeof(dot11_BarFrameHeader_t);

            if (IS_HT_ON(fc))
            {
                pDataFrameBody += IEEE80211_HT_CTL_LEN;
            }

            /* Get TID from BAR frame */
            COPY_WLAN_WORD (&uBarControlField, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */
            uFrameTid = (uBarControlField & DOT11_BAR_CONTROL_FIELD_TID_BITS) >> 12;

            /* TID illegal value ? */
            if (uFrameTid >= MAX_NUM_OF_802_1d_TAGS)
            {
                BLOCK_ACK_PRINT_REPORT_ERROR( "\r\nRxQueue_ReceivePacket: BA event - BAR frame with TID value too big, TID = %d.\r\n",uFrameTid);

                pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter++;

                RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                return;
            }

            /* Set the SA Tid pointer */
            pTidDataBase = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uFrameHlid][uFrameTid]];

            /* TID legal value */
            /* packet TID BA not established ? */
            if (IsBaSessionEstablished(uFrameTid, uFrameHlid) == FALSE)
            {
                BLOCK_ACK_PRINT_REPORT_ERROR( "\r\nRxQueue_ReceivePacket: BA event - BAR frame for TID not established, TID = %d.\r\n",uFrameTid);

                RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_UNSPECIFIED, uFrameTid, uFrameHlid);
                RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                return;
            }

            /* BAR of established BA session - reset inactivity timer */
            ResetInactivityTimer(uFrameTid, uFrameHlid);

            /* Get Starting Sequence number from BAR frame */
            pDataFrameBody = pDataFrameBody + 2;
            COPY_WLAN_WORD (&uBaStartingSequenceControlField, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */
            uStartingSequenceNumber = (uBaStartingSequenceControlField & DOT11_SC_SEQ_NUM_MASK) >> 4;


            /* Starting Sequence Number is higher than Expcted SN ? */
            if ( BA_SESSION_IS_A_BIGGER_THAN_B (uStartingSequenceNumber, pTidDataBase->uTidExpectedSn) )
            {
                uWinStartDelta = uStartingSequenceNumber - pTidDataBase->uTidExpectedSn;

                /* If timer is on - stop it. Later on we may start it again [in case we still have packets stored] */
                if (pTidDataBase->uMissingPktTimeStamp != 0xffffffff)
                {
                    BLOCK_ACK_PRINT_REPORT( "\r\nRxQueue_ReceivePacket:StopMissingPktTimer StopMissingPktTimer "
                            "uFrameTid:%d uFrameTid:%d\r\n",uFrameTid, uFrameTid);
                    GTRACE(GRP_DRIVER_CC33, "RxQueue_ReceivePacket:StopMissingPktTimer StopMissingPktTimer "
                            "uFrameTid:%d uFrameTid:%d",uFrameTid, uFrameTid);

                    StopMissingPktTimer(uFrameTid, uFrameHlid);
                }

                /* Pass all saved queue packets with SN lower than the new win start */
                for (i = 0;
                     ((i < uWinStartDelta) || (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)) &&
                      (i < RX_QUEUE_MAX_WIN_SIZE);
                     i++)
                {
                    if (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL)
                    {
                        RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                                            pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

                        pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;
                        pTidDataBase->uStoredPackets--;
                    }

                    pTidDataBase->uWinStartArrayInex++;

                    pTidDataBase->uTidExpectedSn++;
                    pTidDataBase->uTidExpectedSn &= 0xFFF;

                    /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
                    pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;
                }

                /* If there are still packets stored - start the timer */
                if (pTidDataBase->uStoredPackets)
                {
                    BLOCK_ACK_PRINT_REPORT( "\r\nRxQueue_ReceivePacket:StartMissingPktTimer"
                            "uFrameTid:%d uFrameTid:%d\r\n",uFrameTid, uFrameTid);
                    StartMissingPktTimer(uFrameTid, uFrameHlid);
                }
            }
            }
            break;


        case DOT11_FC_SUB_ACTION:
        {

            uint16_t fc;

            /* get pointer to the frame body */
            pDataFrameBody = pFrame + sizeof(dot11_mgmtHeader_t);

            fc = le_to_host16((uint16_t)(*((uint16_t*)&pHdr->fc)));

            if (IS_WEP_ON(fc) != 0)
            {
                pDataFrameBody += RSN_SEC_LEN;
            }
            /* Advance 4 extra bytes in IEEE80211 header if order bit is on (mostly 11ax support) */
            if (IS_HT_ON(fc))
            {
                pDataFrameBody += IEEE80211_HT_CTL_LEN;
            }

            /* get Action field from BA action frame */
            pDataFrameBody++;//remove categoty
            switch(*pDataFrameBody)
            {
            case DOT11_BA_ACTION_ADDBA:

                //GTRACE(1, "RxQueue_ReceivePacket of type DOT11_BA_ACTION_ADDBA \r\n");

                /* Get dialog token from ADDBA request frame */
                pDataFrameBody++;//remove action
                uDialogToken = *pDataFrameBody;

                /* Get parameters set from ADDBA request frame */
                pDataFrameBody++;//remove dialog token
                COPY_WLAN_WORD(&uBAParameterField, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */

                /* get uControlledLink */
                uControlledLink = pRxData->pUdata->aLinkInfo[uFrameHlid].uHandoverLink;

                /* get TID parameter set */
                uFrameTid = (uBAParameterField & DOT11_BA_PARAMETER_SET_FIELD_TID_BITS) >> 2;

                uAmsduPermitted = (uBAParameterField & HT_BA_POLICY_INITIATOR_BIT);

                /* get the role id */
                eFwRoleId = pRxData->pUdata->aLinkInfo[uControlledLink].eFwRoleId;

                /* TID illegal value ? */
                if (uFrameTid >= MAX_NUM_OF_802_1d_TAGS)
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event - ADDBA frame with TID value too big, TID = %d.\r\n",uFrameTid);

                    pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter++;

                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }

                /* BA already established , the initiator can update the timeout*/
                if (IsBaSessionEstablished(uFrameTid, uControlledLink))
                {
                    uint32_t          uFormerIncativityTimeoutMs;

                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: Received ADDBA frame for Hlid: %d, uControlledLink: %d, Tid %d. uBAParameterField: 0x%x Session already established.\r\n",
                            uFrameHlid, uControlledLink, uFrameTid, uBAParameterField);
                    RxQueue_SendDELBA(DOT11_DELBA_REASON_CODE_UNSPECIFIED, uFrameTid, uControlledLink);
                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }

                /* Link is closed (peer removed), discard packet without sending response */
                if (pRxData->aRxLinkInfo[uControlledLink].eState == LINK_STATE_CLOSED)
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event (ADDBA) - Link closed, discarding.\r\n");

                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }

                /* Max allowed number of BA sessions reached yet ?   OR
                 * BA session establishment not allowed (FW general constraint) ?   OR
                 * BA session establishment not allowed for this link and TID (Rx policy) ? */

                if ((pRxData->tRxQueueArraysMng.uNumOpenBaSessions >= NUM_OF_RX_BA_SESSIONS_SUPPORTED) ||
                    (!pRxData->bBaAllowed[eFwRoleId]) ||
                    (!pRxData->uRxBaPolicy[uControlledLink]) ||
                    (IsBaSessionEstablished(uFrameTid, uFrameHlid) == TRUE))
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event (ADDBA) - BA establishment not allowed.\r\n");
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event (ADDBA) - uNumOpenBaSessions = %x, bBaAllowed = %x, uFrameHlid = 0x%x, uFrameTid = %x, uRxBaPolicy[uControlledLink=%d] = 0x%x IsBaSessionEstablished:%d\r\n", pRxData->tRxQueueArraysMng.uNumOpenBaSessions, pRxData->bBaAllowed[eFwRoleId], uFrameHlid, uFrameTid,
                            uControlledLink, pRxData->uRxBaPolicy[uControlledLink],IsBaSessionEstablished(uFrameTid, uFrameHlid));

                    RxQueue_SendADDBAResponse(DOT11_ADDBA_RESPONSE_STATUS_CODE_DECLINE, uControlledLink, uFrameTid, uDialogToken, uAmsduPermitted);

                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_HANDLED, pBuffer);

                    return;
                }

                BLOCK_ACK_PRINT_REPORT( "\r\nRxQueue_ReceivePacket: RxQueue_EstablishBaSession.\r\n");
                GTRACE(GRP_DRIVER_CC33, "RxQueue_ReceivePacket: RxQueue_EstablishBaSession.");


                /* Establish BA */
                RxQueue_EstablishBaSession(uFrameTid, uControlledLink);

                /* Set the SA Tid pointer */
                uSessionIndex   = pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uControlledLink][uFrameTid];
                pTidDataBase    = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[uSessionIndex];

                /* Get winSize from ADDBA action frame */
                pTidDataBase->uTidWinSize = (uBAParameterField & DOT11_BA_PARAMETER_SET_FIELD_WINSIZE_BITS) >> 6;

                /* Set actual window size */
                if (pRxData->uReducedTidWinSize[uControlledLink] != 0)
                {
                    pTidDataBase->uTidWinSize = pRxData->uReducedTidWinSize[uControlledLink];
                }
                else if (pTidDataBase->uTidWinSize > RX_QUEUE_MAX_WIN_SIZE)
                {
                    pTidDataBase->uTidWinSize = RX_QUEUE_MAX_WIN_SIZE;
                }
                else if (pTidDataBase->uTidWinSize == 0)
                {
                    pTidDataBase->uTidWinSize = RX_QUEUE_DEFAULT_WIN_SIZE;
                }


                /* get inactivity timeout from ADDBA action frame */

                pDataFrameBody = pDataFrameBody + 2;
                COPY_WLAN_WORD (&uInactivityTimeout, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */

                /* Inactivity timeout in ADDBA request is in TUs. 1 TU = 1024 us */
                pTidDataBase->uIncativityTimeoutMs = ((uInactivityTimeout * 1024) / 1000);

                *pDataFrameBody = 30;

                /* get initial sequence number (ISN) from ADDBA request frame */

                pDataFrameBody = pDataFrameBody + 2;
                COPY_WLAN_WORD (&uStartingSequenceNumber, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */
                pTidDataBase->uTidExpectedSn = (uStartingSequenceNumber & DOT11_SC_SEQ_NUM_MASK) >> 4;
                pTidDataBase->uWinStartArrayInex = 0;
                os_memset(pTidDataBase->aPaketsQueue, 0, sizeof (TRxQueuePacketEntry) * RX_QUEUE_MAX_WIN_SIZE);

                RxQueue_CfgRxBaPolicy(pTidDataBase, uControlledLink, uFrameTid, BA_SESSION_SETUP_SET);

                RxQueue_SendADDBAResponse(DOT11_ADDBA_RESPONSE_STATUS_CODE_SUCCESSFUL, uControlledLink, uFrameTid, uDialogToken, uAmsduPermitted);

                /* Start inactivity timer */
                if (pTidDataBase->uIncativityTimeoutMs > 0)
                {
                    StartInactivityTimer(uFrameTid, uControlledLink);
                }
                break;

            case DOT11_BA_ACTION_DELBA:

                //Report(REPORT_SEVERITY_INFORMATION, "RxQueue_ReceivePacket: Receive ADDBA request\r\n");

                /* get TID field and winSize from DELBA action frame */
                pDataFrameBody = pDataFrameBody + 1;
                COPY_WLAN_WORD(&uBAParameterField, (uint16_t *)pDataFrameBody); /* copy with endianess handling. */
                uFrameTid = (uBAParameterField & DOT11_DELBA_PARAMETER_FIELD_TID_BITS) >> 12;

                /* TID illegal value ? */
                if (uFrameTid >= MAX_NUM_OF_802_1d_TAGS)
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event - DELBA frame with TID value too big, TID = %d.\r\n",uFrameTid);

                    pRxData->rxDataDbgCounters.rxTidHlidInvalidCounter++;
                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }

                /* TID legal value */

                /* Check that this is RX DELBA packtet. FW handles TX DELBA packets */
                uInitiatorBit = (uBAParameterField & DOT11_DELBA_PARAMETER_FIELD_INITIATOR_BIT) >> 11;

                if (uInitiatorBit != DOT11_DELBA_PARAMETER_INITIATOR)
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event - DELBA frame for TX session. FW handles.\r\n");

                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }


                /* packet TID BA not established ? */
                if (IsBaSessionEstablished(uFrameTid, uFrameHlid) == FALSE)
                {
                    BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event - DELBA frame for TID not established, TID = %d.\r\n",uFrameTid);
                    GTRACE(GRP_DRIVER_CC33, "RxQueue_ReceivePacket: BA event - DELBA frame for TID not established, TID = %d.",uFrameTid);


                    RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                    return;
                }

                RxQueue_CloseBaSession(uFrameTid, uFrameHlid, TRUE);
                break;

            default:
                BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event Action field from BA action frame illegal. action = 0x%x\r\n",*pDataFrameBody);

                RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

                return;
            }//switch(*pDataFrameBody)
            break;

        default:
            BLOCK_ACK_PRINT_REPORT_ERROR ("\r\nRxQueue_ReceivePacket: BA event with Subtype illegal. Subtype = 0x%x\r\n",((ufc & DOT11_FC_SUB_MASK) >> 4));
            GTRACE(GRP_DRIVER_CC33, "RxQueue_ReceivePacket: BA event with Subtype illegal. Subtype = 0x%x",((ufc & DOT11_FC_SUB_MASK) >> 4));

            RxQueue_PassPacket (RX_DESC_HOST_STATUS_FAIL, pBuffer);

            return;
          }//case DOT11_FC_SUB_ACTION:
          }//switch ((dot11_Fc_Sub_Type_e)(ufc & DOT11_FC_SUB_MASK))
    }//if (class == TAG_CLASS_BA_EVENT)

    RxQueue_PassPacket (eStatus, pBuffer);

    return;
}

/**
 * \brief   pass all the packets in a TID's queue
 *
 * \param   uTid    index of TID queue to clear
 */
static Bool_e SendQueuedPackets(uint8_t uTid, uint8_t uHlid)
{

    rxData_t            *pRxData = gRxDataCB;
    TRxQueueBaDataBase  *pTidDataBase;
    uint32_t             uPacketsChecked = 0;

    /* Set the SA Tid pointer */
    pTidDataBase = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

    /* Find the first stored packet */
    while ( (uPacketsChecked < RX_QUEUE_MAX_WIN_SIZE) && /* avoid infinite loop */
            (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket == NULL) )
    {
        pTidDataBase->uWinStartArrayInex++;

        /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
        pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

        pTidDataBase->uTidExpectedSn++;
        pTidDataBase->uTidExpectedSn &= 0xFFF;

        uPacketsChecked++;
    }

    /* Send all packets in order */
    while ((pTidDataBase->uStoredPackets > 0) && (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket != NULL))
    {
        RxQueue_PassPacket (pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].eStatus,
                            pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket);

        pTidDataBase->aPaketsQueue[pTidDataBase->uWinStartArrayInex].pPacket = NULL;

        pTidDataBase->uWinStartArrayInex++;

        /* aWinStartArrayInex % RX_QUEUE_MAX_WIN_SIZE */
        pTidDataBase->uWinStartArrayInex &= RX_QUEUE_ARRAY_SIZE_BIT_MASK;

        pTidDataBase->uTidExpectedSn++;
        pTidDataBase->uTidExpectedSn &= 0xFFF;

        pTidDataBase->uStoredPackets--;
    }

    if (pTidDataBase->uStoredPackets > 0)
        return TRUE;

    return FALSE;
}

/**
 * \fn     rxData_ExpiryMissingPktTimeout_handler
 * \brief  Handles expiry events in driver context
 *
 * This is the Timer module's callback that is registered to the ContextEngine module to be invoked
 *   from the driver task (after requested by tmr_GetExpiry through trnspt_RequestSchedule ()).
 * It dequeues all expiry events from the queue that correlates to the current driver state,
 *   and calls their users callbacks.
 *
 * \note
 * \return void
 * \sa     tmr_GetExpiry
 */
void rxData_ExpiryMissingPktTimeout_handler (void* hCbHndl)
{
    rxData_t *pRxData = gRxDataCB;
    uint32_t key;

    /* Request switch to driver context for handling timer events */
    trnspt_RequestSchedule (pRxData->uMissingPktTimeoutContextId,FALSE);//perform rxData_MissingPktTimeout_task
}

/*
Function Name : MissingPktTimeout

Description   : This function sends all consecutive old packets stored in a specific TID queue to the upper layer.

                This function is called on timer wake up. 
                [The timer is started when we have stored packets in the RxQueue].
                

Parameters    : pRxData        - A handle to the RxQueue structure.
                bTwdInitOccured - Not used.

Returned Value: void
*/
void rxData_MissingPktTimeout_task ()
{
    rxData_t *pRxData = gRxDataCB;
    uint8_t   uTid, uHlid;
    uint32_t  uNowMs = osi_GetTimeMS();
    uint32_t  uMinRequestTime = 0xffffffff; /* the next request-time to be served */
    uint8_t   uTidClient = TID_CLIENT_NONE;

    pRxData->uMissingPktTimerClient = TID_CLIENT_NONE;

    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        for (uTid = 0; uTid < MAX_NUM_OF_802_1d_TAGS; uTid++)
        {
            if (IsBaSessionEstablished(uTid, uHlid))
            {
                TRxQueueBaDataBase *pTidInfo = &pRxData->tRxQueueArraysMng.aBaSessionDataBase[pRxData->tRxQueueArraysMng.aLinkTidBaIdTable[uHlid][uTid]];

                /* skip if no request was made to clear this queue */
                if ( (pTidInfo->uMissingPktTimeStamp == 0xffffffff) ||
                     (pTidInfo->uStoredPackets == 0) )
                {
                    continue;
                }

                /* if this tid expired, clear its queue */
                if ( uNowMs - pTidInfo->uMissingPktTimeStamp >= BA_SESSION_TIME_TO_SLEEP )
                {
                    if (SendQueuedPackets(uTid, uHlid))
                        pTidInfo->uMissingPktTimeStamp = osi_GetTimeMS();
                    else
                        pTidInfo->uMissingPktTimeStamp = 0xffffffff;
                }


                /* keep uMinRequestTime as minimum */
                if (pTidInfo->uMissingPktTimeStamp < uMinRequestTime)
                {
                    uMinRequestTime = pTidInfo->uMissingPktTimeStamp;
                    uTidClient = uTid;
                    BLOCK_ACK_PRINT_REPORT( "\r\nMissingPktTimeout: request for timer ,uFrameTid:%d uHlid:%d\r\n",uTid, uHlid);
                }
            }
        }
    }


    /* if any TID needs clearing, restart timer */
    if (uMinRequestTime < 0xffffffff)
    {
        BLOCK_ACK_PRINT_REPORT( "\r\nMissingPktTimeout: uFrameTid:%d uHlid:%d\r\n",uTid, uHlid);
        osi_TimerStart (&pRxData->hMissingPktTimer,uMinRequestTime + BA_SESSION_TIME_TO_SLEEP - uNowMs, FALSE);
        pRxData->uMissingPktTimerClient = uTidClient;
    }
}

void RxQueue_SetInternalRxBaPolicy(uint32_t uHlid, uint8_t uPolicyBitmap)
{
    rxData_t *pRxData = gRxDataCB;

    pRxData->uRxBaPolicy[uHlid] = uPolicyBitmap;
}



