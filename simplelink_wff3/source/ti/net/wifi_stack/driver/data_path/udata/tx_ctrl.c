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
/*******************************************************************************/
/*                                                                             */
/*      MODULE: txCtrl.c                                                       */
/*    PURPOSE:  The central Tx path module.                                    */
/*              Prepares Tx packets sent from the data-queue and mgmt-queue    */
/*                for copy to the FW, including building the header and the    */
/*                Tx-descriptor.                                               */
/*                                                                             */
/*******************************************************************************/
#define __FILE_ID__  FILE_ID_31


#include "paramOut.h"
#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "public_share.h"
#include "ethernet.h"
#include "tw_driver.h"
#include "802_11defs.h"
#include "timer.h"
#include "tx_ctrl.h"
#include "tx_ctrl_api.h"
#include "tx_data_queue_api.h"
#include "udata_api.h"
#include "udata.h"
#include "txn_defs.h"
#include <fw_event_if.h>
#include <trnspt_if.h>
#include "tx_result_api.h"
#include "tx_hw_queue_api.h"
#include "cc3xxx_public_types.h"
#include "tx.h"
#include "mpdu.h"
#include "common.h"
#include "udata.h"

#define AES_AFTER_HEADER_PAD_SIZE         8

int32_t txHwQueue_VerifyDescriptorValid(uint32_t desc_id);


/* Current Tx packet original attributes to restore upon requeue */
typedef struct
{
    uint8_t    uTid;
    uint16_t   uLength;
    uint16_t   uTxnFirstBufLen;   /* Length of the first buffer in the packet TxnStruct. */
    uint8_t   *pTxnFirstBuf;      /* The first buffer in the packet TxnStruct. */
} TPktOriginalAttrib;

/* Save packet original attributes needed in case it will be requeued (no room in FW)
 * pPktCtrlBlk  - The Tx packet pointer, type TTxCtrlBlk*
 * tSavedAttrib - The structure that saves the attributes, type TPktOriginalAttrib
 */
#define SAVE_PKT_ORIGINAL_ATTRIB(pPktCtrlBlk, tSavedAttrib)                \
    {                                                                      \
        tSavedAttrib.uTid            = pPktCtrlBlk->tTxDescriptor.tid;     \
        tSavedAttrib.uLength         = pPktCtrlBlk->tTxDescriptor.length;  \
        tSavedAttrib.uTxnFirstBufLen = pPktCtrlBlk->tTxnStruct.aLen[0];    \
        tSavedAttrib.pTxnFirstBuf    = pPktCtrlBlk->tTxnStruct.aBuf[0];    \
    }

/* Restore packet original attributes when it is requeued (no room in FW)
 * tSavedAttrib - The structure that saved the attributes, type TPktOriginalAttrib
 * pPktCtrlBlk  - The Tx packet pointer, type TTxCtrlBlk*
 */
#define RESTORE_PKT_ORIGINAL_ATTRIB(tSavedAttrib, pPktCtrlBlk)             \
    {                                                                      \
        pPktCtrlBlk->tTxDescriptor.tid    =  tSavedAttrib.uTid;            \
        pPktCtrlBlk->tTxDescriptor.length =  tSavedAttrib.uLength;         \
        pPktCtrlBlk->tTxnStruct.aLen[0]   =  tSavedAttrib.uTxnFirstBufLen; \
        pPktCtrlBlk->tTxnStruct.aBuf[0]   =  tSavedAttrib.pTxnFirstBuf;    \
    }

/*
 * Module internal functions prototypes:
 */

/* Note: put here and not in txCtrl.h to avoid warning in the txCtrl submodules that include txCtrl.h */


static uint32_t txCtrl_BuildDataPktHdr(TTxCtrlBlk *pPktCtrlBlk, AckPolicy_e ackPolicy, Bool_e bEncrypt,uint8_t *hdrPadding);
static void   txCtrl_TxCompleteCb(TTxResultInfo *pTxResultInfo, uint32_t counter);
static void   txCtrl_BuildDataPkt (TTxCtrlBlk *pPktCtrlBlk, uint32_t uAc);
static void   txCtrl_BuildMgmtPkt (TTxCtrlBlk *pPktCtrlBlk, uint32_t uAc);
static void   txCtrl_UpdateUpDowngradeMapping (void);
static void   txCtrl_UpdateBackpressure (TTxHwBackpressure *pBackpressure);
static void   txCtrl_UpdateTxCounters (TTxResultInfo *pTxResultInfo,
                                       TTxCtrlBlk *pPktCtrlBlk,
                                       uint32_t ac,
                                       Bool_e bIsDataPkt);

static void txCtrl_TSMExpiredTimer (uint8_t tid , Bool_e bTwdInitOccured);
static void txCtrl_TSMExpiredTimer0 (Bool_e bTwdInitOccured);
static void txCtrl_TSMExpiredTimer1 (Bool_e bTwdInitOccured);
static void txCtrl_TSMExpiredTimer2 (Bool_e bTwdInitOccured);
static void txCtrl_NotifyOnTSMFinishedAndCleanObj (TSMReportData_t  *pReportData);
static void txCtrl_UpdateTSMDelayCounters (TTxResultInfo *pTxResultInfo, uint8_t tid);
int32_t txHwQueue_PrepareDescForFw(TTxCtrlBlk *pPktCtrlBlk, uint16_t uLifeTime);
void txHwQueue_FreeDescForFw(TTxCtrlBlk *pPktCtrlBlk);


txCtrl_t *gTxCtrlCB = NULL;

extern dbg_cntr_trnspt_t g_stat_trnpt;

/* Translate input AC to TID */
const uint8_t WMEQosAcToTid[MAX_NUM_OF_AC] = { 0, 2, 4, 6 };
/********************************************************************************
*                                                                               *
*                               INLINE FUNCTIONS                                *
*                                                                               *
*********************************************************************************/


int32_t txCtrl_tx_allocate(uint8_t ismgmt,TTxCtrlBlk *pPktCtrlBlk, uint16_t uLifeTime)
{
    int ret = TXN_STATUS_OK;

    trnspt_lockTxQueue();
    /* Prepare descriptor for FW (timestamp in FW time, lifeTime, driverHandlingTime and descID) */
    ret = txHwQueue_PrepareDescForFw(pPktCtrlBlk,uLifeTime);
    if(ret != TXN_STATUS_OK)
    {
        trnspt_unlockTxQueue();
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rError !! tx_allocate no free descriptor id");
        return TXN_STATUS_BUSY;
    }

    ret = txHwQueue_allocate_mem_blocks(ismgmt,pPktCtrlBlk);

    trnspt_unlockTxQueue();

    if(ret != TXN_STATUS_OK)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rNotice !! tx_allocate no mem blocks");
        txHwQueue_FreeDescForFw(pPktCtrlBlk); /* Free the allocated descriptor ID */
        return TXN_STATUS_BUSY;
    }

    /* Indicate that the packet is transfered to the FW, and the descriptor fields are in FW format! */
    pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_SENT_TO_FW;
    return ret;
}




/* Packet sent to FW pending TxComplete, so increment counter and request system Awake if needed */
static void updatePmConstraintPktSent(void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    pTxCtrl->uPktsPendCompleteCounter++;
    /* If it's first pending packet, disable device and host sleep */
    if (pTxCtrl->uPktsPendCompleteCounter == 1)
    {
        twIf_Awake();//TWD_Awake(pTxCtrl->hTWD, WAKE_REQ_ID_PENDING_TX_CMPLT);
    }
}

/* Packet TxComplete arrived, so decrement counter and if 0 allow system Sleep */
static  void updatePmConstraintPktComplete(uint32_t counter)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    if (pTxCtrl->uPktsPendCompleteCounter >= counter)
    {
        pTxCtrl->uPktsPendCompleteCounter -= counter;
    }
    else 
    {
        pTxCtrl->uPktsPendCompleteCounter = 0;
       //Report(REPORT_SEVERITY_ERROR, "updatePmConstraintPktComplete(): uPktsPendCompleteCounter is already 0!\r\n");
    }
    /* If no more pending packets, enable device and host sleep */
    if (pTxCtrl->uPktsPendCompleteCounter == 0)
    {
        twIf_Sleep();//TWD_Sleep(pTxCtrl->hTWD, WAKE_REQ_ID_PENDING_TX_CMPLT);
    }
}

/*--------------------------------------------------------------------------------------*/
/**
 * \fn     FreeTxPacket
 * \brief  Free the OS Tx packet
 *
 * Free the OS Tx packet after driver processing is finished.
 *
 * \note
 * \param  hDrv          - The Driver object handle
 * \param  pPktCtrlBlk  - The packet CtrlBlk
 * \param  eStatus      - The packet transmission status (OK/NOK)
 * \return void
 * \sa
 */
/*--------------------------------------------------------------------------------------*/
void FreeTxPacket (TTxCtrlBlk *pPktCtrlBlk, uint32_t eStatus)
{
    void *pPkt = pPktCtrlBlk->tTxPktParams.pInputPkt;
    pPktCtrlBlk->tTxPktParams.pInputPkt = NULL;
    if (pPkt != 0)
    {
        os_free(pPkt);
    }
}



/********************************************************************************
*                                                                               *
*                       PUBLIC  FUNCTIONS  IMPLEMENTATION                       *
*                                                                               *
*********************************************************************************/

/*************************************************************************
*                        txCtrl_Create                                   *
**************************************************************************
* DESCRIPTION:  This function initializes the Tx module.
*
* INPUT:        hOs - handle to Os Abstraction Layer
*
* OUTPUT:
*
* RETURN:       Handle to the allocated Tx data control block
*************************************************************************/
txCtrl_t* txCtrl_Create (void)
{
    /* allocate Tx module control block */
    gTxCtrlCB = (txCtrl_t *)os_zalloc(sizeof(txCtrl_t));
	
    if (!gTxCtrlCB)
        return NULL;

    return gTxCtrlCB;
}


/***************************************************************************
*                           txCtrl_Init                                  *
****************************************************************************
* DESCRIPTION:  This function configures the TxCtrl module.
***************************************************************************/
void txCtrl_Init(TUdata *pUdata)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint32_t ac;
    uint8_t  i;

    /* Save other modules handles */
    pTxCtrl->pUdata         = pUdata;

    /* Set Tx parameters to defaults */
    pTxCtrl->uPktsPendCompleteCounter = 0;
    pTxCtrl->uUpDowngradedLink = WLANLINKS_INVALID_HLID;

    /* Initialize descriptor ID free-stack: push IDs 1..MAX-1 (ID 0 reserved for invalid) */
    pTxCtrl->uDescIdFreeStackTop = 0;
    for (i = 1; i < MAX_TX_DESC_ID; i++)
    {
        pTxCtrl->aDescIdFreeStack[pTxCtrl->uDescIdFreeStackTop++] = i;
    }

    for (i = 0; i < WLANLINKS_MAX_LINKS; i++)
    {
        pTxCtrl->aEncryptEapol[i] = DEF_EAPOL_ENCRYPTION_STATUS;
        pTxCtrl->aEncryptData[i] = DEF_CURRENT_PRIVACY_MODE;
    }

    for (i = 0; i < TSM_REPORT_NUM_OF_MEASUREMENT_IN_PARALLEL_MAX; i++)
    {
        pTxCtrl->tTSMTimers[i].hRequestTimer = tmr_CreateTimer ();
        if (pTxCtrl->tTSMTimers[i].hRequestTimer == NULL)
        {
           //Report(REPORT_SEVERITY_ERROR, "txCtrl_Init(): Failed to create hRequestTimer!\r\n");
            return;
        }

        pTxCtrl->tTSMTimers[i].bRequestTimerRunning = FALSE;
    }

    pTxCtrl->tTSMTimers[0].fExpiryCbFunc = (TTimerCbFunc)txCtrl_TSMExpiredTimer0;
    pTxCtrl->tTSMTimers[1].fExpiryCbFunc = (TTimerCbFunc)txCtrl_TSMExpiredTimer1;
    pTxCtrl->tTSMTimers[2].fExpiryCbFunc = (TTimerCbFunc)txCtrl_TSMExpiredTimer2;

    for (ac = 0; ac < MAX_NUM_OF_AC; ac++)
    {
        for (i = 0; i < MAX_NUM_WLAN_ROLE_IDS; i++)
        {
            pTxCtrl->aMsduLifeTimeTu[i][ac] = MGMT_PKT_LIFETIME_TU;
        }

        for (i = 0; i < WLANLINKS_MAX_LINKS; i++)
        {
            pTxCtrl->aAckPolicy[i][ac] = ACK_POLICY_LEGACY;
            pTxCtrl->aAdmissionState[i][ac] = AC_ADMITTED;
            pTxCtrl->aAdmissionRequired[i][ac] = ADMISSION_NOT_REQUIRED;
        }

        /* initialize the UP-downgrade mapping without downgrade, so we don't need to touch BE & BK mapping per update */
        pTxCtrl->aUpDowngradedLinkAcMapping[ac] = ac;
    }

    /* Reset counters */
    txCtrlParams_ResetCounters();
    txCtrlParams_resetDbgCounters();

    /* Register the Tx-Complete callback function. */
	txResult_RegisterCb((void*)txCtrl_TxCompleteCb, pTxCtrl);
#if 0
    /* Register the Update-Busy-Map callback function. */
    txHwQueue_RegisterCb((void*)txCtrl_UpdateBackpressure, (void *)pTxCtrl);
#endif
   //Report(REPORT_SEVERITY_INIT, ".....Tx Data configured successfully\r\n");
}


/*************************************************************************
*                        txCtrl_SetDefaults                              *
**************************************************************************
* DESCRIPTION:
*
* INPUT:
*               txDataInitParams - Tx Data creation parameters
*
* OUTPUT:
*
* RETURN:
*************************************************************************/
uint32_t txCtrl_SetDefaults (void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    /* Update queues mapping (AC/TID/Backpressure) after module init. */
    txCtrl_UpdateQueuesMapping ();

    pTxCtrl->TSMInProgressBitmap = 0;
    pTxCtrl->uSdioBlkSizeShift = SDIO_BLK_SIZE_SHIFT_DEF; //pInitTable->tTwdInitParams.tGeneral.uSdioBlkSizeShift;
    pTxCtrl->uHostIfCfgBitmap = TWD_HOST_IF_CFG_BITMAP_DEF; //pInitTable->tTwdInitParams.tGeneral.uHostIfCfgBitmap;
    return OK;
}


/***************************************************************************
*                           txCtrl_Unload                                  *
****************************************************************************
* DESCRIPTION:  This function unload the tx ctrl module.
*
***************************************************************************/
uint32_t txCtrl_Unload (void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint8_t  i;

    if (pTxCtrl == NULL)
    {
        return NOK;
    }

    /* Destroy the TSM timers */
    for (i = 0; i < TSM_REPORT_NUM_OF_MEASUREMENT_IN_PARALLEL_MAX; i++)
    {
        if (pTxCtrl->tTSMTimers[i].hRequestTimer)
        {
            tmr_DestroyTimer (pTxCtrl->tTSMTimers[i].hRequestTimer);
        }
    }

    /* free Tx Data control block */
    os_free (pTxCtrl);

    return OK;
}


/*************************************************************************
*                        txCtrl_SelectAcForTid                           *
**************************************************************************
* DESCRIPTION:  This function Return the AC that correlates with the
*               packet TID, including UP-downgrae if applicable for the link
*
* RETURN:       The calculated AC
*************************************************************************/
uint32_t txCtrl_SelectAcForTid(uint32_t uHlid, uint8_t *pTid)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint32_t uAc = WMEQosTagToACTable[*pTid];
    uint32_t uDowngradedAc;

    /* If WME is disabled for this link, use only BE */
    if (TI_UNLIKELY(!pTxCtrl->pUdata->aWmeEnabled[uHlid]))
    {
        uDowngradedAc = QOS_AC_BE;
    }
    /* Else, if it's a UP-downgraded link, set the AC according to the downgrade mapping */
    else if (TI_UNLIKELY(uHlid == pTxCtrl->uUpDowngradedLink))
    {
        uDowngradedAc = pTxCtrl->aUpDowngradedLinkAcMapping[uAc];
    }
    else 
    {
        uDowngradedAc = uAc;
    }

    /* AC to TID translation is bivalent so update TID only if the AC was changed. */
    if (uDowngradedAc != uAc) 
    {
        *pTid = WMEQosAcToTid[uDowngradedAc];
    }

    return uDowngradedAc;
}

/*******************************************************************************
*                          txCtrl_XmitData                                     *
********************************************************************************
* DESCRIPTION:  Get a packet from the data-queue, allocate HW resources and CtrlBlk,
*                 build header and descriptor, and send it to HW by TxXfer.
*
* RETURNS:      STATUS_XMIT_SUCCESS - Packet sent succesfully
*               STATUS_XMIT_BUSY    - Packet dropped due to lack of HW resources, retransmit later.
*               STATUS_XMIT_ERROR   - Packet dropped due to an unexpected problem (bug).
********************************************************************************/
EStatusXmit txCtrl_XmitData(TTxCtrlBlk *pPktCtrlBlk, uint8_t *pBackpressureMap)
{
    txCtrl_t   *pTxCtrl = gTxCtrlCB;
    ETxnStatus eStatus;       /* The Xfer return value (different than this function's return values). */
    uint32_t  uAc;
    uint32_t  uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    ETxHwQueStatus eHwQueStatus;
    TPktOriginalAttrib  tOriginalAttrib;
    //CL_TRACE_START_L3();

    /* Save packet original attributes needed in case it will be requeued (no room in FW, see ) */
    SAVE_PKT_ORIGINAL_ATTRIB(pPktCtrlBlk, tOriginalAttrib)

    uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];

#ifdef ENABLE_TRAFFIC_STATITIC
    if(pTxCtrl->dbgLinkCounters.dbgStartCollectCntr[uHlid])
    {
        pTxCtrl->dbgLinkCounters.dbgTimeFirstPacket_Ms[uHlid] = osi_GetTimeMS();
        pTxCtrl->dbgLinkCounters.dbgStartCollectCntr[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsSent[uHlid] = 0;

        pTxCtrl->dbgLinkCounters.dbgNumPktsXfered[uHlid] = 0;
        pTxCtrl->dbgCounters.dbgNumPktsXfered[uAc] = 0;

        pTxCtrl->dbgLinkCounters.dbgNumPktsError[uHlid] = 0;
        pTxCtrl->dbgCounters.dbgNumPktsError[uAc] = 0;

        pTxCtrl->dbgLinkCounters.dbgNumPktsSuccess[uHlid] = 0;
        pTxCtrl->dbgCounters.dbgNumPktsSuccess[uAc] = 0;

    }
    pTxCtrl->dbgLinkCounters.dbgTimeLastPacket_Ms[uHlid] = osi_GetTimeMS();

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_XmitData(): Pkt Tx, AC=%d, LINK=%d, Len=%d\r\n", uAc, uHlid, pPktCtrlBlk->tTxDescriptor.length);
    pTxCtrl->dbgCounters.dbgNumPktsSent[uAc]++;
    pTxCtrl->dbgLinkCounters.dbgNumPktsSent[uHlid]++;
#endif
    /* Prepare the packet control-block including the Tx-descriptor. */
    //CL_TRACE_START_L4();
    txCtrl_BuildDataPkt(pPktCtrlBlk, uAc);
   //CL_TRACE_END_L4("tiwlan_drv.ko", "INHERIT", "TX", ".FillCtrlBlk");

#if 0 //TODO OSPREY_MX-20
    /* Call TxHwQueue for Hw resources allocation. */
    //CL_TRACE_START_L4();
    eHwQueStatus = TWD_txHwQueue_AllocResources(pPktCtrlBlk, pBackpressureMap);
    //CL_TRACE_END_L4("tiwlan_drv.ko", "INHERIT", "TX", ".allocResources");

    /* If current packet can't be transmitted due to lack of resources,
     *    restore modified attributes and return with BUSY value.
     */
    if (eHwQueStatus == TX_HW_QUE_STATUS_XMIT_BUSY)
    {
        RESTORE_PKT_ORIGINAL_ATTRIB(tOriginalAttrib, pPktCtrlBlk)

        pTxCtrl->dbgCounters.dbgNumPktsBusy[uAc]++;
        pTxCtrl->dbgLinkCounters.dbgNumPktsAcBusy[uHlid]++;
        TX_DATA_SEND_PRINT_ERROR("\n\rERROR txCtrl_XmitData(): Queue busy - Packet dropped, queue = %d\r\n", uAc);
        //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX", "");

        return STATUS_XMIT_BUSY;
    }
#endif
    /* Call the Tx-Xfer to start packet transfer to the FW and return its result. */
    {
        RoleID_t eRoleId = pPktCtrlBlk->tTxPktParams.uFwRoleId;
        //CL_TRACE_START_L4();

        eStatus = txCtrl_tx_allocate(0,pPktCtrlBlk, pTxCtrl->aMsduLifeTimeTu[eRoleId][uAc]);
        /* Prepare descriptor for FW (timestamp in FW time, lifeTime, driverHandlingTime and descID) */
        if(eStatus != TXN_STATUS_OK)
        {
            TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rNotice !! txCtrl_XmitData ,allocate of mem-block or desc-id failed, ret :%d\n", ret);
        }
        else
        {
#ifdef ENABLE_TRAFFIC_STATITIC
            pTxCtrl->dbgCounters.dbgNumPktsXfered[uAc]++;   /* Count packets sent to Xfer. */
            pTxCtrl->dbgLinkCounters.dbgNumPktsXfered[uHlid]++; /* Count packets sent to Xfer. */
#endif
            TX_DATA_SEND_PRINT("\n\rtxCtrl_XmitData(): packet send \r\n");

#ifdef DEBUG_PRINT_FRAME_CONTENT
            //print packets data
            {
                int i;
                Report("\r\n dot11_header_t   size: %d****\r\n", pPktCtrlBlk->tTxnStruct.aLen[0]);
                for (i=0; i< pPktCtrlBlk->tTxnStruct.aLen[0]; i++)
                {
                    if (i % 16 == 0)
                    {
                        Report("\r\n");
                    }
                    Report("0x%02x ",(uint8_t)*((uint8_t *) (pPktCtrlBlk->tTxnStruct.aBuf[0]+i)));
                }
                Report("\r\n payload        ****\r\n");
                for (i=0; i< pPktCtrlBlk->tTxnStruct.aLen[1]; i++)
                {
                    if (i % 16 == 0)
                    {
                        Report("\r\n");
                    }
                    Report("0x%02x ",(uint8_t)*((uint8_t *) (pPktCtrlBlk->tTxnStruct.aBuf[1]+i)));
                }
                Report("\r\n");
            }
#endif

            eStatus = TWD_txXferAggr_SendPacket(pPktCtrlBlk);
        }
        
        //CL_TRACE_END_L4("tiwlan_drv.ko", "INHERIT", "TX", ".XferSendPacket");

    }


    if (eStatus == TXN_STATUS_ERROR)
    {
       //Report(REPORT_SEVERITY_ERROR, "txCtrl_XmitData(): Xfer Error, queue = %d, link = %d, Status = %d\r\n", uAc, uHlid, eStatus);
#ifdef ENABLE_TRAFFIC_STATITIC
        pTxCtrl->dbgCounters.dbgNumPktsError[uAc]++;
        pTxCtrl->dbgLinkCounters.dbgNumPktsError[uHlid]++;
#endif
        txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);
        /* Free the packet resources (packet and CtrlBlk)  */
        txCtrl_FreePacket(pPktCtrlBlk, NOK);//will also free the descriptor
        
        //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX", "");
        TX_DATA_SEND_PRINT_ERROR("\n\rError !! txCtrl_XmitData(): frame send eStatus = %d\r\n", eStatus);

        return STATUS_XMIT_ERROR;
    }
    if (eStatus == TXN_STATUS_BUSY)
    {
        //resources for the frame already free
        //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX", "");
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rtxCtrl_XmitData(): frame was not send due to no resources, requeue\r\n");

        return STATUS_XMIT_BUSY;
    }

#ifdef ENABLE_TRAFFIC_STATITIC
    pTxCtrl->dbgCounters.dbgNumPktsSuccess[uAc]++;
    pTxCtrl->dbgLinkCounters.dbgNumPktsSuccess[uHlid]++;
#endif
    /* Keep system awake while there are Tx packets we expect TxComplete for */
    updatePmConstraintPktSent();

    //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX", "");
    return STATUS_XMIT_SUCCESS;
}


/*******************************************************************************
*                          txCtrl_XmitMgmt                                     *
********************************************************************************
* DESCRIPTION:  Get a packet from the Mgmt-Queue (management, EAPOL or IAPP),
*                 allocate HW resources and CtrlBlk, build header if Ethernet (EAPOL),
*                 build descriptor, and send packet to HW by TxXfer.
*
* RETURNS:      STATUS_XMIT_SUCCESS - Packet sent succesfully.
*               STATUS_XMIT_BUSY - Packet dropped due to lack of HW resources, retransmit later.
*               STATUS_XMIT_ERROR - Packet dropped due to an unexpected problem (bug).
********************************************************************************/
uint32_t txCtrl_XmitMgmt(TTxCtrlBlk *pPktCtrlBlk, uint8_t *pBackpressureMap)
{
    txCtrl_t   *pTxCtrl = gTxCtrlCB;
    ETxnStatus  eStatus;      /* The Xfer return value (different than this function's return values). */
    uint32_t    uAc;  /* The AC selected for the packet transmission. */
    uint32_t    uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    uint8_t     uPktType = pPktCtrlBlk->tTxPktParams.uPktType;
    ETxHwQueStatus eHwQueStatus;
    TPktOriginalAttrib  tOriginalAttrib;

    UDATA_PRINT("\n\rtxCtrl_XmitMgmt : receive packet to send");

    /* Save packet original attributes needed in case it will be requested (no room in FW, see ) */
    SAVE_PKT_ORIGINAL_ATTRIB(pPktCtrlBlk, tOriginalAttrib)

    /* Get an admitted AC corresponding to the packet TID.
     * If UP-downgraded due to admission limitation, the TID is downgraded as well.
     */
    uAc = txCtrl_SelectAcForTid(uHlid, &(pPktCtrlBlk->tTxDescriptor.tid));

#ifdef ENABLE_TRAFFIC_STATITIC
    pTxCtrl->dbgCounters.dbgNumPktsSent[uAc]++;
    pTxCtrl->dbgLinkCounters.dbgNumPktsSent[uHlid]++;
#endif
    /* Prepare the packet control-block including the Tx-descriptor. */
    txCtrl_BuildMgmtPkt(pPktCtrlBlk, uAc);

#if 0 //TODO OSPREY_MX-20
    /* Call TxHwQueue for Hw resources allocation. */
    eHwQueStatus = TWD_txHwQueue_AllocResources(pPktCtrlBlk, pBackpressureMap);

    /* If current packet can't be transmitted due to lack of resources, restore modified  
     *    attributes (including EAPOL Ether-header), and return BUSY (packet is requeued).
     */
    if (eHwQueStatus == TX_HW_QUE_STATUS_XMIT_BUSY)
    {
        if (uPktType == TX_PKT_TYPE_EAPOL)
        {
            os_memcpy(pPktCtrlBlk->aPktHdr, aEapolEtherHeader, ETHERNET_HDR_LEN);
        }
        RESTORE_PKT_ORIGINAL_ATTRIB(tOriginalAttrib, pPktCtrlBlk)

        pTxCtrl->dbgCounters.dbgNumPktsBusy[uAc]++;
        pTxCtrl->dbgLinkCounters.dbgNumPktsAcBusy[uHlid]++;
       //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_XmitMgmt(): Queue busy - Packet dropped, AC=%d, Hlid=%d, Backpressure=0x%x\r\n", uAc, uHlid, *pBackpressureMap);
        TX_PRINT_ERROR("\n\rERROR txCtrl_XmitMgmt(): Queue busy - frame dropped, AC=%d, Hlid=%d, Backpressure=0x%x\r\n", uAc, uHlid, *pBackpressureMap);
        return STATUS_XMIT_BUSY;
    }
#endif
   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_XmitMgmt: length=%d, hlid=%d, PktType=%d, TxDescAttr=0x%x, TID=%d\r\n", pPktCtrlBlk->tTxnStruct.aLen[1], uHlid, uPktType, pPktCtrlBlk->tTxDescriptor.txAttr, pPktCtrlBlk->tTxDescriptor.tid);

    eStatus = txCtrl_tx_allocate(1,pPktCtrlBlk, MGMT_PKT_LIFETIME_TU);
    if(eStatus != TXN_STATUS_OK)//ret = TXN_STATUS_BUSY
    {
        TX_DATA_SEND_PRINT("\n\r notice!! txCtrl_XmitMgmt , no free descriptor id or not enough memblock\n");
    }
    else
    {
        /* If WLAN-data packet with QoS mode, update TID in QoS header (needed in case it was downgraded). */
        /* Note: For EAPOL it is done in txCtrl_BuildDataPktHeader, and in mgmt pkt there is no QoS header. */
        if ((uPktType == TX_PKT_TYPE_WLAN_DATA) && (pTxCtrl->pUdata->aWmeEnabled[uHlid]))
        {
            uint16_t tidWord = (uint16_t)pPktCtrlBlk->tTxDescriptor.tid;
            dot11_header_t *pDot11Header = (dot11_header_t *)(pPktCtrlBlk->aPktHdr);
            pDot11Header->qosControl = tidWord;//COPY_WLAN_WORD(&pDot11Header->qosControl, &tidWord); /* copy with endianess handling. */
        }
#ifdef ENABLE_TRAFFIC_STATITIC
        pTxCtrl->dbgCounters.dbgNumPktsXfered[uAc]++;   /* Count packets sent to Xfer. */
        pTxCtrl->dbgLinkCounters.dbgNumPktsXfered[uHlid]++; /* Count packets sent to Xfer. */
#endif
#ifdef DEBUG_PRINT_FRAME_CONTENT
        //print packets data
        {
            int i;
            TX_DATA_SEND_PRINT_PKT("\n\r dot11_header_t ****\n\r");
            for (i=0; i< pPktCtrlBlk->tTxnStruct.aLen[0]; i++)
            {
                TX_DATA_SEND_PRINT_PKT("0x%02x ",(uint8_t)*((uint8_t *) (pPktCtrlBlk->tTxnStruct.aBuf[0]+i)));
            }
            TX_DATA_SEND_PRINT_PKT("\n\r payload        ****\n\r");
            for (i=0; i< pPktCtrlBlk->tTxnStruct.aLen[1]; i++)
            {
                TX_DATA_SEND_PRINT_PKT("0x%02x ",(uint8_t)*((uint8_t *) (pPktCtrlBlk->tTxnStruct.aBuf[1]+i)));
            }
            TX_DATA_SEND_PRINT_PKT("\n\r");
        }
#endif
        /* Call the Tx-Xfer to start packet transfer to the FW and return the result. */
        eStatus = TWD_txXfer_SendPacket(pPktCtrlBlk);
    }

    if (eStatus == TXN_STATUS_ERROR)
    {
#ifdef ENABLE_TRAFFIC_STATITIC
        //Report(REPORT_SEVERITY_ERROR, "txCtrl_XmitMgmt(): Xfer Error, AC=%d, Link=%d, Backpressure=0x%x, Status = %d\r\n", uAc, uHlid, *pBackpressureMap, eStatus);
        pTxCtrl->dbgCounters.dbgNumPktsError[uAc]++;
        pTxCtrl->dbgLinkCounters.dbgNumPktsError[uHlid]++;
#endif
        /* Call the packet callback function if available */
        if (pPktCtrlBlk->tTxPktParams.fCb)
        {
            TMgmtPktReport tPktReport;

            tPktReport.desc = pPktCtrlBlk->tTxPktParams.pInputDesc;
            tPktReport.status = 0;//0 error 1 success
            tPktReport.uDelBaTid = pPktCtrlBlk->tTxPktParams.uDelBaTidParam;
            tPktReport.uAckFailures = 0;
            ((TMgmtPacketCb)pPktCtrlBlk->tTxPktParams.fCb)(&tPktReport);
        }
         /* Free the packet resources (packet and CtrlBlk)  */
        txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);

        txCtrl_FreePacket(pPktCtrlBlk, NOK);

        TX_DATA_SEND_PRINT_ERROR("\n\rError !! rtxCtrl_XmitMgmt(): frame send eStatus = %d\r\n", eStatus);
        return STATUS_XMIT_ERROR;
    }
    if (eStatus == TXN_STATUS_BUSY)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rtxCtrl_XmitMgmt(): frame was not send due to no resources, requeue\r\n");
        return STATUS_XMIT_BUSY;
    }

#ifdef ENABLE_TRAFFIC_STATITIC
    pTxCtrl->dbgCounters.dbgNumPktsSuccess[uAc]++;
    pTxCtrl->dbgLinkCounters.dbgNumPktsSuccess[uHlid]++;
#endif
    /* Keep system awake while there are Tx packets we expect TxComplete for */
    updatePmConstraintPktSent();

    //Report("\n\rtxCtrl_XmitMgmt(): Success, AC=%d, Link=%d, Backpressure=0x%x, Status = %d\r\n", uAc, uHlid, *pBackpressureMap, eStatus);
    return STATUS_XMIT_SUCCESS;
}


/***************************************************************************
*                           txCtrl_UpdateQueuesMapping
****************************************************************************
* DESCRIPTION:  This function should be called upon the following events:
*                   1) Init
*                   2) ACs admission required change (upon association)
*                   3) ACs admission state change (upon association and add/delete Tspec).
*               It updates the following mappings (by this oredr!):
*                   1) Update mapping from requested-AC to highest-admitted-AC.
*                   2) Update mapping from actual-AC to requested-TID (for backpressure mapping).
*                   3) Update TID-backpressure bitmap, and if changed update data-queue and mgmt-queue.
*
***************************************************************************/
void txCtrl_UpdateQueuesMapping(void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    /* Look for a link that requires UP-downgrade, and if found, prepare a downgrade mapping for it. */
    txCtrl_UpdateUpDowngradeMapping();

    /* Update backpressure bitmap, using last backpressure (updates data-queue and mgmt-queue). */
    txCtrl_UpdateBackpressure(&(pTxCtrl->tBackpressure));
}


/***************************************************************************
*                           txCtrl_AllocPacketBuffer
****************************************************************************
* DESCRIPTION:  Allocate a raw buffer for the whole Tx packet.
                Used for driver generated packets and when the OAL needs to
                    copy the packet to a new buffer (e.g. to gather multiple buffers).
***************************************************************************/
void *txCtrl_AllocPacketBuffer(TTxCtrlBlk *pPktCtrlBlk, uint32_t uPacketLen)
{
    void     *pRawBuf = NULL;

    if (uPacketLen != 0)
    {
        pRawBuf = os_malloc(uPacketLen);
    
        if (pRawBuf)
        {
            /* Indicate that the packet is in a raw buffer (i.e. not OS packet) and save its address and length */
            pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_PKT_IN_RAW_BUF;

            /* Save buffer address and length for the free operation */
            pPktCtrlBlk->tTxPktParams.pInputPkt    = pRawBuf;
            pPktCtrlBlk->tTxPktParams.uInputPktLen = uPacketLen;

        //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_AllocPacketBuffer(): pRawBuf = 0x%x, uPacketLen = %d\r\n", pRawBuf, uPacketLen);
        }
        else
        {
        //Report(REPORT_SEVERITY_ERROR, "txCtrl_AllocPacketBuffer(): uPacketLen = %d, returning NULL\r\n", uPacketLen);
            Report("\n\rERROR txCtrl_AllocPacketBuffer(): uPacketLen = %d, returning NULL", uPacketLen);
        }
    }
    else
    {
        /* Save buffer address and length for the free operation */
        pPktCtrlBlk->tTxPktParams.pInputPkt    = NULL;
        pPktCtrlBlk->tTxPktParams.uInputPktLen = uPacketLen;
    }

    return pRawBuf;
}


/***************************************************************************
*                           txCtrl_FreePacket
****************************************************************************
* DESCRIPTION:  Free the packet resources, including the packet and the CtrlBlk
***************************************************************************/
void txCtrl_FreePacket(TTxCtrlBlk *pPktCtrlBlk, uint32_t eStatus)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint8_t uDescId  = pPktCtrlBlk->tTxDescriptor.descID;

    TX_FRAME_FLOW_CNTRL_PRINT("\n\r txCtrl_FreePacket : 0x%x ", (uint32_t)pPktCtrlBlk);

    //the buffer tTxnStruct.aBuf[0] may be dynamic allocated or static allocated
    // in case it was dynamically allocated, it will be freed.
    //so the address of aPktNabHdr is compared to the address stored in aBuf[0]
    //if it is different than it was dynamic allocation
    if((pPktCtrlBlk->tTxnStruct.aBuf[0] != NULL) &&
            (((uint32_t)((uint32_t*)pPktCtrlBlk->tTxnStruct.aBuf[0])) !=((uint32_t) &(pPktCtrlBlk->aPktNabHdr))))
    {
        os_free(pPktCtrlBlk->tTxnStruct.aBuf[0]);
        pPktCtrlBlk->tTxnStruct.aBuf[0] = NULL;
    }

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_FreePacket(): RawBufFlag = 0x%x, pBuf = 0x%x, Len = %d, DescID = %d\r\n", (pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_PKT_IN_RAW_BUF), pPktCtrlBlk->tTxPktParams.pInputPkt, pPktCtrlBlk->tTxPktParams.uInputPktLen, uDescId);
    os_free(pPktCtrlBlk->tTxPktParams.pInputPkt);
    pPktCtrlBlk->tTxPktParams.pInputPkt = NULL;

    /* If the packet has an input descriptor (for Mgmt pkts), free its memory */
    if (pPktCtrlBlk->tTxPktParams.pInputDesc)
    {
        //Report("\n\rfree pInputDesc :%d", (uint32_t)pPktCtrlBlk->tTxPktParams.pInputDesc);
        os_free(pPktCtrlBlk->tTxPktParams.pInputDesc);
        pPktCtrlBlk->tTxPktParams.pInputDesc = NULL;
    }

    /* Free TxData resources before freeing the tx ctrl block */
    txDataQ_FreeResources(pPktCtrlBlk);

    /* If DescID was already allocated for this packet, free it. */
    if (uDescId != 0)
    {
        txHwQueue_FreeDescForFw(pPktCtrlBlk);
    }

    /* Free the CtrlBlk */
    TWD_txCtrlBlk_Free(pPktCtrlBlk);
}

void txCtrl_RegisterSecuritySeqHandler(TSecuritySeqHandler cb, void *ctx)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pTxCtrl->fSecSeqCb = cb;
    pTxCtrl->hSecSeqHandle = ctx;
}


/********************************************************************************
*                                                                               *
*                       LOCAL  FUNCTIONS  IMPLEMENTATION                        *
*                                                                               *
*********************************************************************************/


/*************************************************************************
*                        txCtrl_TxCompleteCb                             *
**************************************************************************
* DESCRIPTION:  Called by the TWD upon Tx-complete of one packet.
*               Handle packet result:
*               - Update counters
*               - Free the packet resources (OS packet and TxCtrlBlk)
*
* INPUT:    hTWD -  The Tnetw-Driver handle.
*           pTxResultInfo - The packet's Tx result information.
*
*************************************************************************/
static void txCtrl_TxCompleteCb(TTxResultInfo *pTxResultInfo, uint32_t counter)
{
    txCtrl_t    *pTxCtrl = gTxCtrlCB;
    TTxCtrlBlk  *pPktCtrlBlk;
    uint32_t   ac;
    uint32_t   uHlid;
    Bool_e     bIsDataPkt;
    uint8_t    uPktType;
    uint32_t    i;
    uint32_t    uSuccessfulTxCompletePkts = 0;
    uint32_t    aSeqNumIncrTable[WLANLINKS_MAX_LINKS] = {0};

    //CL_TRACE_START_L3();
    
    /* Decrement pending packets counter and if 0 allow system sleep */
    updatePmConstraintPktComplete(counter);

    for (i=0; i < counter; i++)
    {

        if(pTxResultInfo[i].uDescId == 0)
        {
            TX_PRINT_ERROR("\n\rERROR txCtrl_TxCompleteCb:zero uDescId i: %d uDescId:%d", i, pTxResultInfo[i].uDescId)  ;
            continue;
        }

        if(!txHwQueue_VerifyDescriptorValid(pTxResultInfo[i].uDescId))
        {
            TX_PRINT_ERROR("\n\rERROR txCtrl_TxCompleteCb:not valid uDescId i: %d uDescId:%d", i, pTxResultInfo[i].uDescId)  ;
            continue;
        }

        /* Get packet ctrl-block by desc-ID. */
        pPktCtrlBlk = pTxCtrl->aTxDescIds[pTxResultInfo[i].uDescId];
        if(pPktCtrlBlk == NULL)
        {
            TX_PRINT_ERROR("\n\rERROR txCtrl_TxCompleteCb:ERROR!pPktCtrlBlk is empty, pTxResultInfo[%d].uDescId:%d", i, pTxResultInfo[i].uDescId)  ;
            continue;
        }

        ac = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];
        uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
        uPktType = pPktCtrlBlk->tTxPktParams.uPktType;

        
#ifdef TI_DBG
        /* If the pointed entry is already free, print error and exit (not expected to happen). */
        if (pPktCtrlBlk->pNextFreeEntry != NULL)
        {
           //Report(REPORT_SEVERITY_ERROR, "txCtrl_TxCompleteCb(): Pkt already free!!, DescID=%d, AC=%d, uHlid=%d\r\n", pTxResultInfo->uDescId, ac, uHlid);
            //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX_Cmplt", "");
            return;
        }
       //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_TxCompleteCb(): Status=%d, DataLen=%d, hlid=%d, DescID=%d, AC=%d\r\n", pTxResultInfo->eStatus, pPktCtrlBlk->tTxnStruct.aLen[1], uHlid, pTxResultInfo->uDescId, ac);
#endif
        if (uPktType == TX_PKT_TYPE_DUMMY_BLKS)
        {
#ifdef ENABLE_TRAFFIC_STATITIC
            pTxCtrl->dbgCounters.dbgNumTxCmplt[ac]++;
            pTxCtrl->dbgLinkCounters.dbgNumTxCmplt[uHlid]++;
            pTxCtrl->dbgCounters.dbgNumTxCmpltOk[ac]++;
            pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOk[uHlid]++;
#endif
            TX_PRINT("\n\rtxCtrl_TxCompleteCb:free packet: TX_PKT_TYPE_DUMMY_BLKS");

            txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);
            txCtrl_FreePacket(pPktCtrlBlk, OK);
            uSuccessfulTxCompletePkts++;
            continue;
        }

        aSeqNumIncrTable[uHlid]++;
        
        bIsDataPkt = ((uPktType == TX_PKT_TYPE_ETHER) || (uPktType == TX_PKT_TYPE_WLAN_DATA));

        /* For STA/P2PCL role data packets */
        if ((IS_PKT_TYPE_IF_ROLE_STA(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_P2PCL(pPktCtrlBlk)) && TRUE == bIsDataPkt)
        {
            if (pTxCtrl->TSMInProgressBitmap && (0x01 << pPktCtrlBlk->tTxDescriptor.tid))
            {
                txCtrl_UpdateTSMDelayCounters(&pTxResultInfo[i], pPktCtrlBlk->tTxDescriptor.tid);
            }
        }

        /* update TX counters for txDistributer */
        {
            //CL_TRACE_START_L4();
            txCtrl_UpdateTxCounters(&pTxResultInfo[i], pPktCtrlBlk, ac, bIsDataPkt);
            //CL_TRACE_END_L4("tiwlan_drv.ko", "INHERIT", "TX_Cmplt", ".Cntrs");
        }

        /* Call the packet callback function if available */
        if (pPktCtrlBlk->tTxPktParams.fCb)
        {
            TMgmtPktReport tPktReport;
    
            tPktReport.desc = pPktCtrlBlk->tTxPktParams.pInputDesc;
            tPktReport.status = pTxResultInfo[i].eStatus;//1 Success, 0 failure
            tPktReport.uDelBaTid = pPktCtrlBlk->tTxPktParams.uDelBaTidParam;
            tPktReport.uAckFailures = 0;  /* Currently not provided by FW */
            ((TMgmtPacketCb)pPktCtrlBlk->tTxPktParams.fCb)(&tPktReport);//this calls to pkt->fTxCompleteCb CME_TxResult
        }
    
        TX_PRINT("\n\rtxCtrl_TxCompleteCb: txCtrl_FreePacket i:%d uDescId:%d", i,pTxResultInfo[i].uDescId);
        /* Free the packet resources (packet and CtrlBlk)  */
        txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);
        txCtrl_FreePacket(pPktCtrlBlk, OK);
        uSuccessfulTxCompletePkts++;
    }//end of loop

    /* Notify RunScheduler when some frames where freed*/
    //probably memblock were freed
    if (uSuccessfulTxCompletePkts > 0)
    {
        //Report("\n\r dbg_tx. txDataQ_ReqToRunTxScheduler");
        txDataQ_ReqToRunTxScheduler();
    }
    /* Increment the link TKIP/AES-sequence-number by one per packet. */
    if (pTxCtrl->fSecSeqCb)
    {
        pTxCtrl->fSecSeqCb(pTxCtrl->hSecSeqHandle, aSeqNumIncrTable);
    }

    //CL_TRACE_END_L3("tiwlan_drv.ko", "INHERIT", "TX_Cmplt", "");
}


/***************************************************************************
*                   txCtrl_BuildDataPktHdr                                 *
****************************************************************************
* DESCRIPTION:  this function builds the WLAN header from ethernet format,
*               including 802.11-MAC, LLC/SNAP, alignment padding.
*
* INPUTS:       hTxCtrl - the object
*               pPktCtrlBlk - data packet control block (Ethernet header)
*
* RETURNS:      uHdrAlignPad - Num of bytes (0 or 2) added at the header's beginning for 4-bytes alignment.
***************************************************************************/
uint32_t txCtrl_BuildDataPktHdr(TTxCtrlBlk *pPktCtrlBlk, AckPolicy_e ackPolicy, Bool_e bEncrypt, uint8_t *hdrPadding)
{
    txCtrl_t            *pTxCtrl = gTxCtrlCB;
    TEthernetHeader     *pEthHeader;
    dot11_header_t      *pDot11Header;
    Wlan_LlcHeader_T    *pWlanSnapHeader;
    uint32_t            uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    Bool_e              bWmeEnabled = pTxCtrl->pUdata->aWmeEnabled[uHlid];
    uint32_t            uHdrLen = 0;
    uint16_t            uQosControl;
    uint16_t            fc = 0;
    uint16_t            typeLength;
    RoleID_t            eRoleId = pPktCtrlBlk->tTxPktParams.uFwRoleId;
    uint32_t            extraHThdr = IEEE80211_HT_CTL_LEN; // Add 4 bytes gap, may be filled later on by the PMAC
    Bool_e              isNullDataFrame = pPktCtrlBlk->tTxPktParams.isNullDataFrame;

    *hdrPadding = 0;


    /*
     * Handle QoS if needed:
     */
    pDot11Header = (dot11_header_t *)&(pPktCtrlBlk->aPktHdr[0]);
    if (bWmeEnabled)
    {
        *hdrPadding = 2; //require padding of header in 2 bytes to make the header 4 aligned
        pDot11Header = (dot11_header_t *)&(pPktCtrlBlk->aPktHdr[*hdrPadding]);
        uHdrLen = *hdrPadding + WLAN_QOS_HDR_LEN;

        /* Set Qos control fields. */
        uQosControl = (uint16_t)(pPktCtrlBlk->tTxDescriptor.tid);
        if ( TI_UNLIKELY(ackPolicy == ACK_POLICY_NO_ACK) )
            uQosControl |= DOT11_QOS_CONTROL_DONT_ACK;
        pDot11Header->qosControl = uQosControl;//COPY_WLAN_WORD(&pDot11Header->qosControl, &uQosControl); /* copy with endianess handling. */
    }
    else  /* No QoS (legacy header, padding is not needed). */
    {
        uHdrLen = WLAN_HDR_LEN;
    }
    
    /* Before the header translation the first buf-pointer points to the Ethernet header. */
    pEthHeader = (TEthernetHeader *)(pPktCtrlBlk->tTxnStruct.aBuf[TX_BUF_HDR_OFFSET]);

    if (TI_UNLIKELY(MAC_MULTICAST(pEthHeader->dst)))
    {
        pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_MULTICAST;
        if (MAC_BROADCAST(pEthHeader->dst))
        {
            pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_BROADCAST;
        }
    }

    /* Set MAC addresses in header according to the role type */

    if (TI_UNLIKELY(IS_PKT_TYPE_IF_ROLE_IBSS(pPktCtrlBlk)))
    {
        MAC_COPY (pDot11Header->address1, pEthHeader->dst);
        MAC_COPY (pDot11Header->address2, pEthHeader->src);
        MAC_COPY(pDot11Header->address3, pEthHeader->dst);//BSSID is the dest

        fc = DOT11_FC_TO_DS;
        if (bWmeEnabled)
            fc |= DOT11_FC_DATA_QOS;
        else
            fc |= DOT11_FC_DATA;
    }
    else if (IS_PKT_TYPE_IF_ROLE_AP(pPktCtrlBlk) ||  IS_PKT_TYPE_IF_ROLE_P2PGO(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_DEV(pPktCtrlBlk))
    {
        MAC_COPY (pDot11Header->address1, pEthHeader->dst);
        MAC_COPY(pDot11Header->address2, pTxCtrl->pUdata->aRoleLocalMac[eRoleId]);  /* BSSID is our role address */
        MAC_COPY (pDot11Header->address3, pEthHeader->src);

        fc |= DOT11_FC_FROM_DS;

        if (bWmeEnabled)
        {
            fc |= isNullDataFrame?DOT11_FC_DATA_NULL_QOS:DOT11_FC_DATA_QOS;
        }
        else
        {
            fc |= isNullDataFrame?DOT11_FC_DATA_NULL_FUNCTION:DOT11_FC_DATA;

        }
    }
    else  /* STA or P2PCL */
    {
        txDataQ_GetMacFromLink(uHlid, pDot11Header->address1);  /* BSSID is the peer (AP) address */
        MAC_COPY (pDot11Header->address2, pEthHeader->src);
        MAC_COPY (pDot11Header->address3, pEthHeader->dst);

        if (bWmeEnabled)
            fc |= DOT11_FC_DATA_QOS | DOT11_FC_TO_DS;
        else
            fc |= DOT11_FC_DATA | DOT11_FC_TO_DS;
    }

    uHdrLen += extraHThdr;

    if (bEncrypt && !isNullDataFrame)
    {
        fc |= DOT11_FC_WEP;

        /* The current FW API requires adding a pad for the AES overhead */
        if (pTxCtrl->pUdata->aLinkInfo[uHlid].eKeyType >= KEY_TKIP)
        {
            uHdrLen += AES_AFTER_HEADER_PAD_SIZE;//RSN header
        }
    }
    COPY_WLAN_WORD(&pDot11Header->fc, &fc); /* copy with endianess handling. */

    if(isNullDataFrame == FALSE)
    {

        /* Set the SNAP header pointer right after the other header parts handled above. */
        pWlanSnapHeader = (Wlan_LlcHeader_T *)&(pPktCtrlBlk->aPktHdr[uHdrLen]);

        typeLength = HTOWLANS(pEthHeader->type);

        /* Detect the packet type and decide if to create a     */
        /*          new SNAP or leave the original LLC.         */
        /*------------------------------------------------------*/
        if( typeLength > ETHERNET_MAX_PAYLOAD_SIZE )
        {
            /* Create the SNAP Header:     */
            /*-----------------------------*/
            /*
            * Make a working copy of the SNAP header
            * initialised to zero
            */

            pWlanSnapHeader->DSAP = SNAP_CHANNEL_ID;
            pWlanSnapHeader->SSAP = SNAP_CHANNEL_ID;
            pWlanSnapHeader->Control = LLC_CONTROL_UNNUMBERED_INFORMATION;

            /* Check to see if the Ethertype matches anything in the translation     */
            /* table (Appletalk AARP or DixII/IPX).  If so, add the 802.1h           */
            /* SNAP.                                                                 */

            if(( ETHERTYPE_APPLE_AARP == typeLength ) ||
            ( ETHERTYPE_DIX_II_IPX == typeLength ))
            {
                /* Fill out the SNAP Header with 802.1H extention   */
                pWlanSnapHeader->OUI[0] = SNAP_OUI_802_1H_BYTE0;
                pWlanSnapHeader->OUI[1] = SNAP_OUI_802_1H_BYTE1;
                pWlanSnapHeader->OUI[2] = SNAP_OUI_802_1H_BYTE2;

            }
            else
            {
                /* otherwise, add the RFC1042 SNAP   */
                pWlanSnapHeader->OUI[0] = SNAP_OUI_RFC1042_BYTE0;
                pWlanSnapHeader->OUI[1] = SNAP_OUI_RFC1042_BYTE0;
                pWlanSnapHeader->OUI[2] = SNAP_OUI_RFC1042_BYTE0;
            }

            /* set type length */
            pWlanSnapHeader->Type = pEthHeader->type;

            /* Add the SNAP length to the total header length. */
            uHdrLen += sizeof(Wlan_LlcHeader_T);
        }
    }
    if (pPktCtrlBlk->tTxDescriptor.csumData)
    {
        pPktCtrlBlk->tTxDescriptor.csumData = (((uint8_t)(uHdrLen))<< 1) |
                (pPktCtrlBlk->tTxDescriptor.csumData & 0x1);
    }

    os_free(pEthHeader);//free the allocation of etherenet header
    /* Replace first buffer pointer and length to the descriptor and WLAN-header (instead of Ether header) */
    pPktCtrlBlk->tTxnStruct.aBuf[TX_BUF_HDR_OFFSET] = (uint8_t *)&(pPktCtrlBlk->aPktNabHdr);//OSPREY_MX-7
    pPktCtrlBlk->tTxnStruct.aLen[TX_BUF_HDR_OFFSET] += uHdrLen - ETHERNET_HDR_LEN; /*sizeof(pPktCtrlBlk->aPktNabHdr)
                                                            + sizeof(TxIfDescriptor_t) +uHdrLen;*/
    pPktCtrlBlk->tTxDescriptor.length += uHdrLen - ETHERNET_HDR_LEN;
    pPktCtrlBlk->aPktNabHdr.len += uHdrLen - ETHERNET_HDR_LEN;
    pPktCtrlBlk->aPktNabHdr.desc_length += uHdrLen - ETHERNET_HDR_LEN; //== pPktCtrlBlk->tTxDescriptor.length

    TX_DATA_SEND_PRINT("\n\rtxCtrl_BuildDataPktHdr uHdrLen:%d PktNabHdr.len:%d", uHdrLen,pPktCtrlBlk->aPktNabHdr.len);
    TX_DATA_SEND_PRINT("\n\rtxCtrl_BuildDataPktHdr sizes: buffer[0]:%d buffer[1]:%d", pPktCtrlBlk->tTxnStruct.aLen[0],pPktCtrlBlk->tTxnStruct.aLen[1]);

    /* Return the number of bytes (0 or 2) added at the header's beginning for 4-bytes alignment. */
    return 0;
}


/***************************************************************************
*                       txCtrl_BuildDataPkt
****************************************************************************
* DESCRIPTION:  Prepare the Data packet control-block including the Tx-descriptor.
***************************************************************************/
static void txCtrl_BuildDataPkt (TTxCtrlBlk *pPktCtrlBlk, uint32_t uAc)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint16_t  uTxDescAttr;
    uint32_t  uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    uint8     hdrPadding = 0;

    if(pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_HDR_BUILD)
    {
        return;//hdr already build for this frame, this frame was re-queue.
    }

    /* Build packet header (including MAC, LLC/SNAP, security padding, header alignment padding). */
    txCtrl_BuildDataPktHdr(pPktCtrlBlk, pTxCtrl->aAckPolicy[uHlid][uAc], pTxCtrl->aEncryptData[uHlid], &hdrPadding);

    /* Update link byte counter*/
    pTxCtrl->dbgLinkCounters.dbgNumBytesSent[uHlid] += (pPktCtrlBlk->tTxDescriptor.length - sizeof(TxIfDescriptor_t));


    /* Set the descriptor attributes */
    //each interface is identified by link id and session id
    uTxDescAttr  = pTxCtrl->pUdata->aSessionId[uHlid] << TX_ATTR_OFST_SESSION_COUNTER;

    if (hdrPadding)
    {
        uTxDescAttr |= TX_ATTR_HEADER_PAD;
    }

    if ((IS_PKT_TYPE_IF_ROLE_AP(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_P2PGO(pPktCtrlBlk) || 
         IS_PKT_TYPE_IF_ROLE_IBSS(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_DEV(pPktCtrlBlk)) &&
        (pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_MULTICAST))
    {
        uTxDescAttr |= (GET_PKT_RATE_POLICY(pPktCtrlBlk) << TX_ATTR_OFST_RATE_POLICY);
    }
    else
    {
        uTxDescAttr |= ((GET_PKT_RATE_POLICY(pPktCtrlBlk) + uAc) << TX_ATTR_OFST_RATE_POLICY);
    }

    pPktCtrlBlk->tTxDescriptor.txAttr = uTxDescAttr;//ENDIAN_HANDLE_WORD(uTxDescAttr);

    pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_HDR_BUILD;

}


/***************************************************************************
*                       txCtrl_BuildMgmtPkt
****************************************************************************
* DESCRIPTION:  Prepare the Mgmt-Queue packet control-block including the Tx-descriptor.
***************************************************************************/
static void txCtrl_BuildMgmtPkt(TTxCtrlBlk *pPktCtrlBlk, uint32_t uAc)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint16_t  uTxDescAttr = 0;
    uint8_t   uPktType = pPktCtrlBlk->tTxPktParams.uPktType;
    uint32_t  uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    Bool_e    bEncrypt = 0;
    uint8     hdrPadding = 0;

    if(pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_HDR_BUILD)
    {
        return;//hdr already build for this frame, this frame was re-queue.
    }
    /* Update link byte counter*/
    //pTxCtrl->dbgLinkCounters.dbgNumBytesSent[uHlid] += pPktCtrlBlk->tTxDescriptor.length;


    UDATA_PRINT("\n\r txCtrl_BuildMgmtPkt: address1: " MACSTR "  addres2: " MACSTR "  address3: " MACSTR "\r\n",
            MAC2STR(((dot11_mgmtHeader_t *)&(pPktCtrlBlk->aPktHdr[hdrPadding]))->DA),
            MAC2STR(((dot11_mgmtHeader_t *)&(pPktCtrlBlk->aPktHdr[hdrPadding]))->SA),
            MAC2STR(((dot11_mgmtHeader_t *)&(pPktCtrlBlk->aPktHdr[hdrPadding]))->BSSID));

    /* If EAPOL packet, it has Ethernet header (as data packets) */
    if ((uPktType == TX_PKT_TYPE_EAPOL) || (uPktType == TX_PKT_TYPE_ETHER))
    {
        if (uPktType == TX_PKT_TYPE_EAPOL)
        {
            /* Encrypt Eapol only if its encryption is enabled and station is connected (i.e. re-key, not connection and roaming) */
            bEncrypt = (pTxCtrl->aEncryptEapol[uHlid] &&
                                ((txMgmtQ_GetLinkState(uHlid) == LINK_STATE_OPEN) ||
                                (txMgmtQ_GetLinkState(uHlid) == LINK_STATE_EAPOL)));

            /* For EAPOLs, set relevant field in descriptor attributes bitmap */
            uTxDescAttr |= TX_ATTR_EAPOL_FRAME;

        }

        /* convert the Ethernet header to WLAN header as for data packets (including MAC, SNAP & alignment pad). */
        txCtrl_BuildDataPktHdr(pPktCtrlBlk, ACK_POLICY_LEGACY, bEncrypt, &hdrPadding);

    }
    /*  Other types are already in WLAN format so no header translation is needed */
    if (hdrPadding)//will always be zero for mgmt packets
    {
        uTxDescAttr |= TX_ATTR_HEADER_PAD;
    }
    /* mark in-connection if auth packet is sent in AP mode */
    if (IS_PKT_TYPE_IF_ROLE_P2PGO(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_AP(pPktCtrlBlk) || IS_PKT_TYPE_IF_ROLE_DEV(pPktCtrlBlk)) {
        dot11_mgmtHeader_t *wlanHeader = (dot11_mgmtHeader_t *)&(pPktCtrlBlk->aPktHdr[hdrPadding]);
        if (IS_AUTH(wlanHeader->fc)) {
            ACXInConnectionSTA_t param;
            uint32_t eStatus;
            os_memcpy(param.mac_address, wlanHeader->DA ,TIW_DRV_MAC_ADDR);
            param.RoleID = pPktCtrlBlk->tTxPktParams.uFwRoleId;

            //TODO
            //eStatus = TWD_SendInfoEle(ACX_UPDATE_INCONNECTION_STA_LIST, (void*)&param, sizeof(param), NULL, NULL);

            //Report("\n\r txCtrl_BuildMgmtPkt ,set in-connection state status %d " REPORT_MACSTR "\r\n",
            //       eStatus, REPORT_MAC2STR(param.mac_address));
        }
    }

    /* Set fields in the descriptor attributes bitmap. */
    uTxDescAttr |= GET_PKT_RATE_POLICY(pPktCtrlBlk) << TX_ATTR_OFST_RATE_POLICY;
    uTxDescAttr |= pTxCtrl->pUdata->aSessionId[uHlid] << TX_ATTR_OFST_SESSION_COUNTER;
    uTxDescAttr |= TX_ATTR_TX_CMPLT_REQ;

    /* For Dummy Blocks Packets, set relevant fields */
    if (uPktType == TX_PKT_TYPE_DUMMY_BLKS)
    {
        /* FW expects the dummy packet to have an invalid session id - any session id
         * that is different than the one set in the join process */
        uTxDescAttr |= ((~(pTxCtrl->pUdata->aSessionId[uHlid])) << TX_ATTR_OFST_SESSION_COUNTER) & TX_ATTR_SESSION_COUNTER;

        /* Mark as dummy packet for FW */
        uTxDescAttr |= TX_ATTR_TX_DUMMY_REQ;
    }

    pPktCtrlBlk->tTxDescriptor.txAttr = uTxDescAttr;//ENDIAN_HANDLE_WORD(uTxDescAttr);
    pPktCtrlBlk->tTxPktParams.uFlags |= TX_CTRL_FLAG_HDR_BUILD;
}


/***************************************************************************
*                           txCtrl_UpdateUpDowngradeMapping
****************************************************************************
* DESCRIPTION:  Look for a link that has at least one not-admitted AC, and if found then prepare
*                   a UP-downgrade mapping for it. This mapping provides for each requested AC
*                 the highest AC that can be currently used, as follows:
*                   If requested AC is admitted use it.
*                   If not, find highest AC below it that doesn't require admission.
* 
*               Note: we assume that only VO and/or VI ACs may require admission!!
* 
***************************************************************************/
static void txCtrl_UpdateUpDowngradeMapping(void)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
    uint32_t  link;
    uint32_t  ac;
    TUdata    *pUdata = pTxCtrl->pUdata;

    /* First, clean the UP-downgrade mapping */
    pTxCtrl->uUpDowngradedLink = WLANLINKS_INVALID_HLID;
    for (ac = 0; ac < MAX_NUM_OF_AC; ac++) 
    {
        pTxCtrl->aUpDowngradedLinkAcMapping[ac] = ac;
    }

    /* 
     *  Look for a link that has at least one not-admitted AC,
     *      and if found then prepare a UP-downgrade mapping for it.
     *  
     *  Note: we assume that only VO and/or VI ACs may require admission!!
     */

    for (link = 0; link < WLANLINKS_MAX_LINKS; link++)
    {
        /* Skip links that are not in use or don't support WME */
        if (!pUdata->aLinkInfo[link].bIsAllocated || !pUdata->aWmeEnabled[link])
        {
            continue;
        }

        /* If the link's VO is not admitted */
        if (pTxCtrl->aAdmissionState[link][QOS_AC_VO] != AC_ADMITTED)
        {
            /* If VI admission is not required, we downgrade VO to VI, and map VI to itself (no need to downgrade it) */
            if (pTxCtrl->aAdmissionRequired[link][QOS_AC_VI] == ADMISSION_NOT_REQUIRED)
            {
                pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VO] = QOS_AC_VI;
                pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VI] = QOS_AC_VI;
            }
            /* Else - VI requires admission */
            else 
            {
                /* Downgrade VO to BE (we avoid downgrade to VI even if admitted since it requires admission) */
                pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VO] = QOS_AC_BE;

                /* If VI is also not admitted, downgrade it to BE as well */
                if (pTxCtrl->aAdmissionState[link][QOS_AC_VI] != AC_ADMITTED)
                {
                    pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VI] = QOS_AC_BE;
                }
            }

            /* We've found a UP-downgraded link so we save it and exit (we support only one downgraded link) */
            pTxCtrl->uUpDowngradedLink = link;
            return;
        }
        /* Else - if only the VI is not admitted, downgrade from VI to BE (VO is mapped to itself) */
        else if (pTxCtrl->aAdmissionState[link][QOS_AC_VI] != AC_ADMITTED)
        {
            pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VO] = QOS_AC_VO;
            pTxCtrl->aUpDowngradedLinkAcMapping[QOS_AC_VI] = QOS_AC_BE;

            /* We've found a UP-downgraded link so we save it and exit (we support only one downgraded link) */
            pTxCtrl->uUpDowngradedLink = link;
            return;
        }
    }
}


/***************************************************************************
*                           txCtrl_UpdateBackpressure
****************************************************************************
* DESCRIPTION:  This function is called whenever the busy-TIDs bitmap may change,
*                 (except on packet-xmit - handled separately for performance).
*               This includes:
*                   1) Init
*                   2) ACs admission required change (upon association)
*                   3) ACs admission state change (upon association and add/delete Tspec).
*                   4) Tx-Complete - provides also freed ACs.
*
*               It updates the local bitmap, and the data-queue and mgmt-queue.
*
***************************************************************************/
static void txCtrl_UpdateBackpressure(TTxHwBackpressure *pBackpressure)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;

    /* Save the backpressure bitmaps */
    pTxCtrl->tBackpressure.uAcBusyBitmap       = pBackpressure->uAcBusyBitmap;
    pTxCtrl->tBackpressure.uLinkBusyBitmap     = pBackpressure->uLinkBusyBitmap;
    pTxCtrl->tBackpressure.uLinkPriorityBitmap = pBackpressure->uLinkPriorityBitmap;
    pTxCtrl->tBackpressure.TransmitQOnTxComplete = pBackpressure->TransmitQOnTxComplete;

    /* Update the data-queue and mgmt-queue busy-maps. */
    txMgmtQ_UpdateBusyMap(pBackpressure);
    txDataQ_UpdateBusyMap(pBackpressure);
}


static void txCtrl_TSMExpiredTimer (uint8_t tid , Bool_e bTwdInitOccured)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;

    pTxCtrl->TSMReportStat[tid].reportingReason = 0; /* regular TSM report (non triggered one )*/

    txCtrl_NotifyOnTSMFinishedAndCleanObj(&pTxCtrl->TSMReportStat[tid]);
}

static void txCtrl_TSMExpiredTimer0 (Bool_e bTwdInitOccured)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
    txCtrl_TSMExpiredTimer(pTxCtrl->tTSMTimers[0].tid, bTwdInitOccured);
}

static void txCtrl_TSMExpiredTimer1 (Bool_e bTwdInitOccured)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
    txCtrl_TSMExpiredTimer(pTxCtrl->tTSMTimers[1].tid, bTwdInitOccured);
}

static void txCtrl_TSMExpiredTimer2 (Bool_e bTwdInitOccured)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
    txCtrl_TSMExpiredTimer(pTxCtrl->tTSMTimers[2].tid, bTwdInitOccured);
}


static void txCtrl_NotifyOnTSMFinishedAndCleanObj (TSMReportData_t  *pReportData)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_NotifyOnTSMFinishedAndCleanObj: TID=%d, //Reporting reason = %d\r\n", pReportData->uTID, pReportData->reportingReason);

    pTxCtrl->TSMInProgressBitmap &= ~(0x01 << pReportData->uTID);
    pTxCtrl->fTriggerReportCB(pTxCtrl->hTriggerReportHandle, pReportData);

    os_memset(pReportData, 0, sizeof(TSMReportData_t));
}

static void txCtrl_UpdateTSMDelayCounters(TTxResultInfo *pTxResultInfo, uint8_t tid)
{
    txCtrl_t  *pTxCtrl = gTxCtrlCB;
    TSMReportData_t *pReportData = &pTxCtrl->TSMReportStat[tid];

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_UpdateTSMDelayCounters: status=%d, tid=%d\r\n", pTxResultInfo->eStatus, tid);

    pReportData->uMsduTotalCounter++;

    if (pTxResultInfo->eStatus == OK)
    {
        pReportData->uMsduTransmittedOKCounter++;
        pReportData->uConsecutiveDiscardedMsduCounter = 0;
    }
    else
    {
        pReportData->uConsecutiveDiscardedMsduCounter++;  /* serves the consecutive condition trigger */
    }

    /* check if any of the reporting trigger has been met, if true send the report row data to the RRM object */
    if (TRUE == pReportData->bIsTriggeredReport)
    {
        /* the dealy threshold condition */
        if (pReportData->uDelayThreshold > 0)
        {
            if (pReportData->uMaxConsecutiveDelayedPktsCounter == pReportData->uMaxConsecutiveDelayedPktsThr)
            {
                /* call rrm to build and send the TSM report */
                pReportData->reportingReason = (uint8_t)TSM_REQUEST_TRIGGER_CONDITION_DELAY;
                txCtrl_NotifyOnTSMFinishedAndCleanObj(pReportData);
                return;
            }
        }

        /* the Consecutive threshold condition */
        if (pReportData->uConsecutiveErrorThreshold > 0)
        {
            if (pReportData->uConsecutiveDiscardedMsduCounter == pReportData->uConsecutiveErrorThreshold)
            {
                /* call rrm to build and send the TSM report */
                pReportData->reportingReason = (uint8_t)TSM_REQUEST_TRIGGER_CONDITION_CONSECUTIVE;
                txCtrl_NotifyOnTSMFinishedAndCleanObj(pReportData);
                return;
            }
        }

        /* the Average threshold condition */
        if (pReportData->uAverageErrorThreshold > 0)
        {
            if (pReportData->uAverageDiscardedMsduCredit <= 0)
            {
                /* call rrm to build and send the TSM report */
                pReportData->reportingReason = (uint8_t)TSM_REQUEST_TRIGGER_CONDITION_AVERAGE;
                txCtrl_NotifyOnTSMFinishedAndCleanObj(pReportData);
                return;
            }

            /* Every measurementCount num of packets load the creadit with the average threshold */
            if (0 == (pReportData->uMsduTotalCounter % pReportData->measurementCount))
            {
                pReportData->uAverageDiscardedMsduCredit += pReportData->uAverageErrorThreshold;
            }
        }
    }
}


/***************************************************************************
*                       txCtrl_UpdateTxCounters
****************************************************************************
* DESCRIPTION:  Update Tx statistics counters according to the transmitted packet.
***************************************************************************/
static void txCtrl_UpdateTxCounters(TTxResultInfo *pTxResultInfo,
                                    TTxCtrlBlk *pPktCtrlBlk,
                                    uint32_t ac,
                                    Bool_e bIsDataPkt)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint32_t  pktLen;
    uint32_t  dataLen;
    uint32_t  uHlid = pPktCtrlBlk->tTxDescriptor.hlid;
    
    pktLen = (uint32_t)pPktCtrlBlk->tTxDescriptor.length-sizeof(TxIfDescriptor_t);//(uint32_t)ENDIAN_HANDLE_WORD(pPktCtrlBlk->tTxDescriptor.length);
    //pktLen = pktLen << 2;//convert words to bytes
    
    /* If it's not a data packet, exit (the formal statistics are only on network stack traffic). */
    if ( !bIsDataPkt )
    {
        return;
    }

#ifdef ENABLE_TRAFFIC_STATITIC
    /* update debug counters. */
    pTxCtrl->dbgCounters.dbgNumTxCmplt[ac]++;
    pTxCtrl->dbgLinkCounters.dbgNumTxCmplt[uHlid]++;
    if (pTxResultInfo->eStatus == 1/*success*/)
    {
        pTxCtrl->dbgCounters.dbgNumTxCmpltOk[ac]++;
        pTxCtrl->dbgCounters.dbgNumTxCmpltOkBytes[ac] += pktLen;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOk[uHlid]++;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOkBytes[uHlid] += pktLen;
    }
    else
    {
        pTxCtrl->dbgCounters.dbgNumTxCmpltFailBytes[ac] += pktLen;
        pTxCtrl->dbgCounters.dbgNumTxCmpltError[ac]++;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltError[uHlid]++;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltFailBytes[uHlid] += pktLen;

        
       //Report(REPORT_SEVERITY_WARNING, "txCtrl_UpdateTxCounters(): TxResult = %d !!!\r\n", pTxResultInfo->eStatus);
    }

    if (pTxResultInfo->eStatus == 1/*success*/)
    {
        if (pTxCtrl->pUdata->aWmeEnabled[uHlid])
        {
            dataLen = pktLen - (WLAN_WITH_SNAP_QOS_HEADER_MAX_SIZE - ETHERNET_HDR_LEN);
        }
        else
        {
            dataLen = pktLen - (WLAN_WITH_SNAP_HEADER_MAX_SIZE - ETHERNET_HDR_LEN);
        }
        
        if (pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_MULTICAST)
        {
            if (pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_BROADCAST)
            {
                /* Broadcast frame */
                pTxCtrl->txDataCounters[ac].BroadcastFramesXmit++;
                pTxCtrl->txDataCounters[ac].BroadcastBytesXmit += dataLen;
            }
            else
            {
                /* Multicast Address */
                pTxCtrl->txDataCounters[ac].MulticastFramesXmit++;
                pTxCtrl->txDataCounters[ac].MulticastBytesXmit += dataLen;
            }
        }
        else
        {
            /* Directed frame statistics */
            pTxCtrl->txDataCounters[ac].DirectedFramesXmit++;
            pTxCtrl->txDataCounters[ac].DirectedBytesXmit += dataLen;
        }
        
        pTxCtrl->txDataCounters[ac].XmitOk++;
    }
    else    /* Handle Errors */
    {
        pTxCtrl->txDataCounters[ac].FailCounter++;
    }
#endif
}

#if 0
/***************************************************************************
*                           txCtrl_notifyFwReset                           *
****************************************************************************
* DESCRIPTION:  Go over all CtrlBlk entries and free the active ones including the packet.
***************************************************************************/
uint32_t txCtrl_NotifyFwReset (void)
{
    txCtrl_t   *pTxCtrl = gTxCtrlCB;
    uint32_t  entry;
    TTxCtrlBlk *pPktCtrlBlk;

    /* clean busy bitmap */
    os_memset(&pTxCtrl->tBackpressure, 0, (sizeof(pTxCtrl->tBackpressure)));
    txCtrl_UpdateBackpressure (&pTxCtrl->tBackpressure);

    for (entry = 0; entry < CTRL_BLK_ENTRIES_NUM-1; entry++)
    {
        /* Get packet ctrl-block by desc-ID. */
        pPktCtrlBlk = TWD_txCtrlBlk_GetPointer(entry);
        if (pPktCtrlBlk->pNextFreeEntry == 0)
        {
            /* Don't free if the packet still in tx input queues */
            if ((pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_SENT_TO_FW))
            {
                txHwQueue_free_allocated_mem_blocks(pPktCtrlBlk);

                /* Free the packet resources (packet and CtrlBlk)  */
                txCtrl_FreePacket (pPktCtrlBlk, NOK);
            }
        }
    }

    /* Reset pending packets counter and allow the system to sleep */
    pTxCtrl->uPktsPendCompleteCounter = 0;
    twIf_Sleep();//TWD_Sleep(pTxCtrl->hTWD, WAKE_REQ_ID_PENDING_TX_CMPLT);
    
    return OK;
} /* txCtrl_notifyFwReset */
#endif

/***************************************************************************
*                           txCtrl_CheckForTxStuck                         *
****************************************************************************
* DESCRIPTION:  Check if there are stale packets in the TxCtrlTable.
* The criterion for staleness is function of life time (2 times the longest life time)
* Note that only packets that were not sent to the FW are checked for simplicity!
***************************************************************************/
uint32_t txCtrl_CheckForTxStuck (void)
{
    uint32_t  entry;
    TTxCtrlBlk *pPktCtrlBlk;
    uint32_t  uPktAge;      /* Time in uSec since packet start time. */

#ifdef REMOVE_TX_CODE //TODO TX_CODE_WAS_REMOVED

    for (entry = 0; entry < CTRL_BLK_ENTRIES_NUM-1; entry++)
    {
        /* Get packet ctrl-block by desc-ID. */
        pPktCtrlBlk = TWD_txCtrlBlk_GetPointer(entry);

        /* If entry is in use */
        if (pPktCtrlBlk->pNextFreeEntry == 0)
        {
            /* If the packet wasn't sent to the FW yet (time is in host format) */
            if ((pPktCtrlBlk->tTxPktParams.uFlags & TX_CTRL_FLAG_SENT_TO_FW) == 0)
            {
                /* If packet age is more than twice the maximum lifetime, return NOK */
                uPktAge = osi_GetTimeMS() - pPktCtrlBlk->tTxDescriptor.startTime;
                if (uPktAge > ((MGMT_PKT_LIFETIME_TU << SHIFT_BETWEEN_TU_AND_USEC) * 2))
                {
                    return NOK; /* call for recovery */
                }
            }
        }
    }
#endif
    return OK;
} /* txCtrl_FailureTest */


uint32_t txCtrl_UpdateTSMParameters(uint32_t uHlid, TTsmParams *pTSMParams)
{
    uint8_t            i=0;
    Bool_e             bRequestIsValid = FALSE;
    TSMReportData_t   *pReportData = NULL;
    txCtrl_t          *pTxCtrl = gTxCtrlCB;

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_UpdateTSMParameters: tid=%d, bIsTriggeredReport=%d, uDuration=%d\r\n", pTSMParams->uTID, pTSMParams->bIsTriggeredReport, pTSMParams->uDuration);

    if ((pTSMParams->uTID < 0) || (pTSMParams->uTID >= TSM_REPORT_NUM_OF_TID_MAX))
    {
       //Report(REPORT_SEVERITY_ERROR, "txCtrl_UpdateTSMParameters: TID should be in range of 0-7!!!n");
        return NOK;
    }

    /* The STA does not support the TSM off more than 3 TIDs in parallel */
    if (pTxCtrl->TSMInProgressBitmap & ((0x01 << pTSMParams->uTID)))
    {
       //Report(REPORT_SEVERITY_ERROR, "txCtrl_UpdateTSMParameters: TSM Measurement is in progress already. reject this measurement request!!n");
        return NOK;
    }

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_UpdateTSMParameters: Updating TSM//Report params for TID = %d \r\n",pTSMParams->uTID );

    pReportData = &pTxCtrl->TSMReportStat[pTSMParams->uTID];
    pReportData->uTID = pTSMParams->uTID;
    pReportData->bIsTriggeredReport = pTSMParams->bIsTriggeredReport;
    pReportData->measurementToken = pTSMParams->measurementToken;
    pReportData->frameToken = pTSMParams->frameToken;
    pReportData->frameNumOfRepetitions = pTSMParams->frameNumOfRepetitions;
    pReportData->measurementDuration = pTSMParams->uDuration;
    pReportData->bin0Range = pTSMParams->uBin0Range;
    MAC_COPY(pReportData->peerSTA, pTSMParams->peerSTA);

   //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_UpdateTSMParameters: Bin0 range = %d \r\n",pReportData->bin0Range);

    pReportData->binDelayThreshold[0] = pTSMParams->uBin0Range;
    pReportData->binDelayThreshold[1] = pTSMParams->uBin0Range << 1;
    pReportData->binDelayThreshold[2] = pTSMParams->uBin0Range << 2;
    pReportData->binDelayThreshold[3] = pTSMParams->uBin0Range << 3;
    pReportData->binDelayThreshold[4] = pTSMParams->uBin0Range << 4;
    pReportData->binDelayThreshold[5] = 0xFFFFFFFF; /* Actually, it is defined as every delay which is bigger than bin4 threshold */

    /* register for the trigger report CB to be called upon trigger condition met/duration ended */
    pTxCtrl->fTriggerReportCB = pTSMParams->fCB;
    pTxCtrl->hTriggerReportHandle = pTSMParams->hCB;

    /* For non-triggered TSM , allocate timer if available and start the measurment */
    if (FALSE == pReportData->bIsTriggeredReport)
    {
        for (i = 0; i < TSM_REPORT_NUM_OF_MEASUREMENT_IN_PARALLEL_MAX; i++)
        {
            if (pTxCtrl->tTSMTimers[i].bRequestTimerRunning == FALSE)
            {
                if ((pTxCtrl->tTSMTimers[i].hRequestTimer != NULL) && (pTxCtrl->tTSMTimers[i].fExpiryCbFunc != NULL))
                {
                    //Report(REPORT_SEVERITY_INFORMATION, "txCtrl_UpdateTSMParameters: Measurment Started for timer Index=%d, TID=%d, Duration=%d [TUs] \r\n", i, pTSMParams->uTID, pTSMParams->uDuration);

                     tmr_StartTimer(pTxCtrl->tTSMTimers[i].hRequestTimer,
                               pTxCtrl->tTSMTimers[i].fExpiryCbFunc,
                               pTxCtrl,
                               (pTSMParams->uDuration*1024/1000),
                               FALSE);

                     pTxCtrl->tTSMTimers[i].bRequestTimerRunning = TRUE;
                     pTxCtrl->tTSMTimers[i].tid = pTSMParams->uTID;
                     bRequestIsValid = TRUE;
                     break;
                }

            }
        }

        if (FALSE == bRequestIsValid)
        {
           //Report(REPORT_SEVERITY_ERROR, "txCtrl_UpdateTSMParameters: Timer can not be allocated for this non-triggered report !!n");
            return NOK;
        }

    }
    else
    {
        pReportData->measurementCount = pTSMParams->tTriggerReporting.measuCount;
        pReportData->triggerCondition = pTSMParams->tTriggerReporting.triggerCondition;
        pReportData->uMaxConsecutiveDelayedPktsThr = pTSMParams->uDelayedMsduCount;

        if (pReportData->triggerCondition &  TSM_REQUEST_TRIGGER_CONDITION_DELAY)
        {
            pReportData->uDelayThreshold = pReportData->binDelayThreshold[pTSMParams->uDelayedMsduRange + 1];
        }
        else
        {
            pReportData->uDelayThreshold = 0;
        }


        pReportData->uConsecutiveErrorThreshold = (pReportData->triggerCondition &
                                                   TSM_REQUEST_TRIGGER_CONDITION_CONSECUTIVE) ?
                                                   pTSMParams->tTriggerReporting.consecutiveErrorThreshold: 0;

        if (pReportData->triggerCondition & TSM_REQUEST_TRIGGER_CONDITION_AVERAGE)
        {
            pReportData->uAverageErrorThreshold = pTSMParams->tTriggerReporting.averageErrorThreshold;
            /* Load the average delay trigger condition credit with the threshold received */
            pReportData->uAverageDiscardedMsduCredit = pReportData->uAverageErrorThreshold;
        }
        else
        {
            pReportData->uAverageErrorThreshold = 0;
        }


    }

    /* save the measurement start time TSF */
    os_memcpy(pReportData->actualMeasurementTSF, pTSMParams->aActualMeasurementTSF, TIME_STAMP_LEN);

    /* Mark that this measurement has just started */
    pReportData->bTSMInProgress = TRUE;
    pTxCtrl->TSMInProgressBitmap |= (0x01 << pTSMParams->uTID);

    return OK;
}

