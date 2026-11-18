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
/** \file   txXfer_data.c
 *  \brief  Handle data Tx packets transfer to the firmware.
 *
 *      This module gets the upper driver's Tx packets after FW resources were
 *    allocated for them, aggregates them if possible, and handles their transfer
 *    to the FW via the host slave (indirect) interface, using the TwIf Transaction API.
 *  The aggregation processing is completed by the BusDrv where the packets are combined
 *    and sent to the FW in one transaction.
 *
 *  \see
 */


#define __FILE_ID__  FILE_ID_78
#include "osi_kernel.h"
#include "trnspt_thread.h"
#include "public_share.h"
#include "bus_if.h"
#include "nab.h"
#include "trnspt_if.h"
#include "tx.h"

#include "fw_event_handle.h"
#include "txXfer.h"
#include "tw_driver.h"
#include "tx_hw_queue_api.h"
#include "tx_ctrl_api.h"
/************************************************************************
 * Types
 ************************************************************************/

static void txXferAggr_SetDefaults (void);
static void txXferAggr_SetBusParams (uint32_t uDmaBufLen);
static void txXferAggr_FreeUnsendPakets();

void txXferAggr_Timeout(void* param);
void txXferAggr_EndOfBurst ();
uint32_t txXferAggr_Restart (void);
extern ETxnStatus txXfer_SendAggregatedPkts (TTxXferObj *pTxXfer, Bool_e bLastPktSentNow);



#define TXXFER_AGGR_TIMEOUT  (2) //mili

TTxXferObj *gTxXferAggrCB;

/********************************************************************************
*                                                                               *
*                       PUBLIC  FUNCTIONS  IMPLEMENTATION                       *
*                                                                               *
*********************************************************************************/

TTxXferObj* txXferAggr_Create(void)
{
    gTxXferAggrCB = (TTxXferObj *)os_zalloc(sizeof(TTxXferObj));
    if (gTxXferAggrCB == NULL)
    {
        return NULL;
    }

    osi_TimerCreate(&(gTxXferAggrCB->aggrTimer), "txXfer_aggr", txXferAggr_Timeout, (void *)NULL);
    gTxXferAggrCB->uAggrEndBurstContextId = trnspt_RegisterClient ((TTransportCbFunc)txXferAggr_EndOfBurst,TRUE);

    return gTxXferAggrCB;
}


uint32_t txXferAggr_Destroy(void)
{
    TTxXferObj *pTxXfer = gTxXferAggrCB;
    ETxnStatus eStatus = TXN_STATUS_COMPLETE;

    osi_TimerStop(&(pTxXfer->aggrTimer));
    osi_TimerDelete(&(pTxXfer->aggrTimer));
    eStatus = txXfer_SendAggregatedPkts (pTxXfer, FALSE);
    if(eStatus != TXN_STATUS_COMPLETE)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! Failed to send Aggr frames");
        txXferAggr_FreeUnsendPakets();
    }
    pTxXfer->uAggregPktsNum = 0;


    if (pTxXfer)
    {
        os_free (pTxXfer);
    }

    return OK;
}


//inits the TxXfer
uint32_t txXferAggr_Init (void)
{
    TTxXferObj *pTxXfer = txXferAggr_Create();
    if (pTxXfer == NULL)
    {
        return NOK;
    }


    return txXferAggr_Restart();
}


uint32_t txXferAggr_Restart (void)
{
    TTxXferObj *pTxXfer = gTxXferAggrCB;

    txXferAggr_SetDefaults();
    txXferAggr_SetBusParams(TWD_TX_AGGREG_PKTS_LIMIT_MAX);
    pTxXfer->uAggregPktsNum    = 0;

    return OK;
}


void txXferAggr_SetDefaults (void)
{
    TTxXferObj *pTxXfer = gTxXferAggrCB;

    pTxXfer->uAggregMaxPkts    = TWD_TX_AGGREG_PKTS_LIMIT_DEF; //pInitParams->tGeneral.uTxAggregPktsLimit;
    pTxXfer->uHostIfCfgBitmap  = TWD_HOST_IF_CFG_BITMAP_DEF; //pInitParams->tGeneral.uHostIfCfgBitmap;
    pTxXfer->uSdioBlkSizeShift = SDIO_BLK_SIZE_SHIFT_DEF; //pInitParams->tGeneral.uSdioBlkSizeShift;

    pTxXfer->uSdioBlkAlignMask = ((1 << pTxXfer->uSdioBlkSizeShift) - 1); /* Used for packets alignment to SDIO block size */
}


void txXferAggr_SetBusParams (uint32_t uDmaBufLen)
{
    TTxXferObj *pTxXfer = gTxXferAggrCB;

    pTxXfer->uAggregMaxLen = uDmaBufLen;
}


void txXferAggr_FreeUnsendPakets()
{
    //no need to free, if the code came into here it means that FW crash did happen
}

ETxnStatus txXferAggr_SendPacket (TTxCtrlBlk *pPktCtrlBlk)
{
    TTxXferObj       *pTxXfer = gTxXferAggrCB;
    TxIfDescriptor_t *pDesc = &(pPktCtrlBlk->tTxDescriptor);
    uint32_t          uPktLen = pDesc->length;
    ETxnStatus        eStatus = TXN_STATUS_COMPLETE;
    uint16_t          uAlignedLength;
    uint16_t          uPaddingLength;
    int32_t           ret = 0;

    TX_DATA_SEND_PRINT("\n\rtxXfer_SendPacket: Len=%d TotalBlks=%d Hlid=%d TxAttr=%d DescId=%d, PadLen=%d AggregNum=%d, TID=%d\r\n", uPktLen, pDesc->totalMemBlks, pDesc->hlid, pDesc->txAttr, pDesc->descID, pPktCtrlBlk->tTxnStruct.uPaddingSize, pTxXfer->uAggregPktsNum+1, pDesc->tid);

    //trnspt_lockTxXfer();
    /* WL8 - each packet in the aggregation needs to be 4-byte aligned.*/
    uAlignedLength = (uPktLen + 0x3) & (~0x3); /* alignment to 4 bytes */
    uPaddingLength = pPktCtrlBlk->tTxnStruct.uPaddingSize = uAlignedLength - uPktLen;

    /* If starting a new aggregation, prepare it, and send packet if aggregation is disabled. */
    if (pTxXfer->uAggregPktsNum == 0)
    {
        pTxXfer->uAggregPktsNum  = 1;
        pTxXfer->uAggregPktsLen  = uAlignedLength;
        pTxXfer->pAggregFirstPkt = pPktCtrlBlk;
        pTxXfer->pAggregLastPkt  = pPktCtrlBlk;
        pPktCtrlBlk->pNextAggregEntry = pPktCtrlBlk;  /* First packet points to itself */
        if (pTxXfer->uAggregMaxPkts <= 1)
        {
            TX_DATA_SEND_PRINT("\n\rtxXfer_SendPacket:txXfer_SendAggregatedPkts \r\n");
            eStatus = txXfer_SendAggregatedPkts (pTxXfer, TRUE);//TXN_STATUS_COMPLETE for success
            pTxXfer->uAggregPktsNum = 0;
        }
        else
        {
            ret = osi_TimerStart(&(pTxXfer->aggrTimer), TXXFER_AGGR_TIMEOUT  , FALSE);
            if(ret != OSI_OK)
            {
                TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! cant start aggr timer");
                eStatus = txXfer_SendAggregatedPkts (pTxXfer, TRUE);//TXN_STATUS_COMPLETE for success
                pTxXfer->uAggregPktsNum = 0;
            }
            else
            {
                eStatus = TXN_STATUS_PENDING;

            }
        }
    }

    /* Else, if new packet can be added to aggregation, add it and set status as Pending. */
    else if ((pTxXfer->uAggregPktsNum + 1 <= pTxXfer->uAggregMaxPkts)  &&
             (pTxXfer->uAggregPktsLen + uPktLen <= pTxXfer->uAggregMaxLen))
    {
        pTxXfer->uAggregPktsNum++;
        pTxXfer->uAggregPktsLen += uAlignedLength;
        pTxXfer->pAggregLastPkt->pNextAggregEntry = pPktCtrlBlk;  /* Link new packet to last */
        pTxXfer->pAggregLastPkt = pPktCtrlBlk;                    /* Save new packet as last */
        pPktCtrlBlk->pNextAggregEntry = pTxXfer->pAggregFirstPkt; /* Point from last to first */
        eStatus = TXN_STATUS_PENDING;
    }

    /* Else, we can't add the new packet, so send current aggregation and start a new one */
    else
    {
        osi_TimerStop(&(pTxXfer->aggrTimer));
        eStatus = txXfer_SendAggregatedPkts (pTxXfer, FALSE);
        if(eStatus != TXN_STATUS_COMPLETE)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! Failed to send Aggr frames");
            txXferAggr_FreeUnsendPakets();
        }
        eStatus = TXN_STATUS_PENDING;  /* The current packet is not sent yet so return Pending */
        pTxXfer->uAggregPktsNum  = 1;
        pTxXfer->uAggregPktsLen  = uAlignedLength;
        pTxXfer->pAggregFirstPkt = pPktCtrlBlk;
        pTxXfer->pAggregLastPkt  = pPktCtrlBlk;
        pPktCtrlBlk->pNextAggregEntry = pPktCtrlBlk;  /* First packet points to itself */
        ret = osi_TimerStart(&(pTxXfer->aggrTimer), TXXFER_AGGR_TIMEOUT  , FALSE);
        if(ret != OSI_OK)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! cant start aggr timer");
            eStatus = txXfer_SendAggregatedPkts (pTxXfer, FALSE);
            if(eStatus != TXN_STATUS_COMPLETE)
            {
                TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! Failed to send Aggr frames");
            }
            pTxXfer->uAggregPktsNum  = 0;
        }
    }

    //trnspt_unlockTxXfer();
    /* Return the Txn result - COMPLETE or PENDING. */
    /* Note: For PENDING, a callback function will be called only if registered (needed for WHA) */
    return eStatus;
}

void txXferAggr_Timeout(void* param)
{
    trnspt_RequestSchedule (gTxXferAggrCB->uAggrEndBurstContextId,FALSE);//perform txXferAggr_EndOfBurst_task
}


void txXferAggr_EndOfBurst ()
{
    TTxXferObj *pTxXfer = gTxXferAggrCB;
    ETxnStatus eStatus = TXN_STATUS_COMPLETE;

    //trnspt_lockTxXfer();
    //verify that aggregation is enabled
    if (pTxXfer->uAggregPktsNum > 0 )
    {
        osi_TimerStop(&(pTxXfer->aggrTimer));

        /* No more packets from TxDataQ so send any aggregated packets and clear aggregation */
        eStatus = txXfer_SendAggregatedPkts (pTxXfer, FALSE);
        if(eStatus != TXN_STATUS_COMPLETE)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\r ERROR!! Failed to send Aggr frames");
            txXferAggr_FreeUnsendPakets();
        }
        pTxXfer->uAggregPktsNum = 0;

    }
    //trnspt_unlockTxXfer();

}

