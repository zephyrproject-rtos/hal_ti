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
/** \file   txXfer.c
 *  \brief  Handle Tx packets transfer to the firmware.
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


static uint32_t txXfer_Restart (void);
static void txXfer_SetDefaults (void);
static void txXfer_SetBusParams (uint32_t uDmaBufLen);



/************************************************************************
 * Types
 ************************************************************************/
/* The TxXfer module object. */

ETxnStatus txXfer_SendAggregatedPkts (TTxXferObj *pTxXfer, Bool_e bLastPktSentNow);



/********************************************************************************
*                                                                               *
*                       PUBLIC  FUNCTIONS  IMPLEMENTATION                       *
*                                                                               *
*********************************************************************************/
TTxXferObj *gTxXferCB;

TTxXferObj* txXfer_Create(void)
{
    gTxXferCB = (TTxXferObj *)os_zalloc(sizeof(TTxXferObj));
    if (gTxXferCB == NULL)
    {
        return NULL;
    }

    return gTxXferCB;
}


uint32_t txXfer_Destroy(void)
{
    TTxXferObj *pTxXfer = gTxXferCB;

    if (pTxXfer)
    {
        os_free (pTxXfer);
    }

    return OK;
}


//inits the TxXfer
uint32_t txXfer_Init (void)
{
    TTxXferObj *pTxXfer = txXfer_Create();
    if (pTxXfer == NULL)
    {
        return NOK;
    }


    return txXfer_Restart();
}


uint32_t txXfer_Restart (void)
{
    TTxXferObj *pTxXfer = gTxXferCB;

    txXfer_SetDefaults();
    txXfer_SetBusParams(MAX_BUS_TXN_SIZE/*not used*/);
    pTxXfer->uAggregPktsNum    = 0;

    return OK;
}


void txXfer_SetDefaults (void)
{
    TTxXferObj *pTxXfer = gTxXferCB;

    pTxXfer->uAggregMaxPkts    = 1; //no aggregation;
    pTxXfer->uHostIfCfgBitmap  = TWD_HOST_IF_CFG_BITMAP_DEF; //pInitParams->tGeneral.uHostIfCfgBitmap;
    pTxXfer->uSdioBlkSizeShift = SDIO_BLK_SIZE_SHIFT_DEF; //pInitParams->tGeneral.uSdioBlkSizeShift;

    pTxXfer->uSdioBlkAlignMask = ((1 << pTxXfer->uSdioBlkSizeShift) - 1); /* Used for packets alignment to SDIO block size */
}


void txXfer_SetBusParams (uint32_t uDmaBufLen)
{
    TTxXferObj *pTxXfer = gTxXferCB;

    pTxXfer->uAggregMaxLen = uDmaBufLen;
}

ETxnStatus txXfer_SendPacket (TTxCtrlBlk *pPktCtrlBlk)
{
    TTxXferObj       *pTxXfer = gTxXferCB;
    TxIfDescriptor_t *pDesc = &(pPktCtrlBlk->tTxDescriptor);
    uint32_t          uPktLen = pDesc->length;
    ETxnStatus        eStatus = TXN_STATUS_COMPLETE;
    uint16_t          uAlignedLength;
    uint16_t          uPaddingLength;

    TX_DATA_SEND_PRINT("\n\rtxXfer_SendPacket: Len=%d TotalBlks=%d Hlid=%d TxAttr=%d DescId=%d, PadLen=%d AggregNum=%d, TID=%d\r\n", uPktLen, pDesc->totalMemBlks, pDesc->hlid, pDesc->txAttr, pDesc->descID, pPktCtrlBlk->tTxnStruct.uPaddingSize, pTxXfer->uAggregPktsNum+1, pDesc->tid);

    trnspt_lockTxXfer();
    /* WL8 - each packet in the aggregation needs to be 4-byte aligned.*/
    uAlignedLength = (uPktLen + 0x3) & (~0x3); /* alignment to 4 bytes */
    uPaddingLength = pPktCtrlBlk->tTxnStruct.uPaddingSize = uAlignedLength - uPktLen;

    /* If starting a new aggregation, prepare it, and send packet if aggregation is disabled. */
    pTxXfer->uAggregPktsNum  = 1;
    pTxXfer->uAggregPktsLen  = uAlignedLength;
    pTxXfer->pAggregFirstPkt = pPktCtrlBlk;
    pTxXfer->pAggregLastPkt  = pPktCtrlBlk;
    pPktCtrlBlk->pNextAggregEntry = pPktCtrlBlk;  /* First packet points to itself */
    TX_DATA_SEND_PRINT("\n\rtxXfer_SendPacket:txXfer_SendAggregatedPkts \r\n");
    eStatus = txXfer_SendAggregatedPkts (pTxXfer, TRUE);//TXN_STATUS_COMPLETE for success
    pTxXfer->uAggregPktsNum = 0;


    trnspt_unlockTxXfer();
    /* Return the Txn result - COMPLETE or PENDING. */
    /* Note: For PENDING, a callback function will be called only if registered (needed for WHA) */
    return eStatus;
}



/********************************************************************************
*                                                                               *
*                       INTERNAL  FUNCTIONS  IMPLEMENTATION                     *
*                                                                               *
*********************************************************************************/

/**
 * \fn     txXfer_SendAggregatedPkts
 * \brief  Send aggregated Tx packets to bus Txn layer
 *
 * Send aggregated Tx packets to bus Txn layer one by one.
 * Increase the packets counter by the number of packets and send it to the FW (generates an interrupt).
 * If xfer completion CB is registered and status is Complete, call CB for all packets (except last one if inseted now).
 *
 * \note   The BusDrv combines the packets and sends them in one transaction.
 * \param  pTxXfer         - The module's object
 * \param  bLastPktSentNow - If TRUE, last packet in the aggregation was inserted in current call to txXfer_SendPacket.
 * \return COMPLETE if transaction completed in this context, PENDING if not, ERROR if failed
 * \sa
 */
ETxnStatus txXfer_SendAggregatedPkts (TTxXferObj *pTxXfer, Bool_e bLastPktSentNow)
{
    TTxCtrlBlk  *pCurrPktCtrlBlk;
    TTxnStruct  *pTxn;
    ETxnStatus   eStatus = TXN_STATUS_COMPLETE;
    int32_t     i;
    uint16_t     uAlignedLength;

    /* Prepare and send all aggregated packets (combined and sent in one transaction by the BusDrv) */
    pCurrPktCtrlBlk = pTxXfer->pAggregFirstPkt;
    for (i = 0; i < pTxXfer->uAggregPktsNum; i++)
    {
        pTxn = (TTxnStruct *)pCurrPktCtrlBlk;

        /* If not last packet, set aggregation flag, clear completion CB and progress to next packet */
        if (i < (int32_t)((int32_t)pTxXfer->uAggregPktsNum - 1))
        {
            /* Indicate the host-slave HW that it's not the last frame within an aggregation */
            pCurrPktCtrlBlk->tTxDescriptor.extraMemBlks = 0;
            //pCurrPktCtrlBlk->tTxDescriptor.extraMemBlks |= BIT_7;
            TXN_PARAM_SET_AGGREGATE(pTxn, TXN_AGGREGATE_ON);
            pCurrPktCtrlBlk = pCurrPktCtrlBlk->pNextAggregEntry;

        }
        /* If last packet, clear aggregation flag and set completion CB (exist only if registered) */
        else
        {
            /* In WL8 PG2.0 and on - no need to pad each frame to SDIO block size. */
            /* We will pad 1 time for the all aggregation.                         */
            if (pTxXfer->uHostIfCfgBitmap & HOST_IF_CFG_BITMAP_TX_PAD_TO_SDIO_BLK)
            {
                /* if any padding was added to this frame by "txXfer_SendPacket" - */
                /* remove it from the total length (because it will get over-ridden shortly) */
                pTxXfer->uAggregPktsLen -= pTxn->uPaddingSize;

                /* Calculate the required padding to SDIO block size, override the padding field. */
                uAlignedLength = (pTxXfer->uAggregPktsLen + pTxXfer->uSdioBlkAlignMask) & (~(pTxXfer->uSdioBlkAlignMask));
                pTxn->uPaddingSize = uAlignedLength - pTxXfer->uAggregPktsLen;
            }
            /* No need for "else" - if the alignment is not to SDIO block than it is to 4-bytes. */
            /* This was already taken care of by "txXfer_SendPacket".                            */

            TXN_PARAM_SET_AGGREGATE(pTxn, TXN_AGGREGATE_OFF);
        }

        /* Send packet */
        pTxn->uHwAddr = NAB_DATA_ADDR;//SLV_MEM_DATA;
        eStatus = twIf_Transact (pTxn);
        TX_DATA_SEND_PRINT("\n\r call twIf_Transact \r\n");
		if(eStatus != TXN_STATUS_COMPLETE)
        {
            TX_DATA_SEND_PRINT_ERROR("\n\r call twIf_Transact failed eStatus:%d\r\n",eStatus);
        }
    }

#ifdef TI_DBG
    pTxXfer->aDbgCountPktAggreg[pTxXfer->uAggregPktsNum]++;
//   //Report(REPORT_SEVERITY_INFORMATION, "txXfer_SendAggregatedPkts: Status=%d, NumPkts=%d, AggregLen=%d, pFirstPkt=0x%x, pLastPkt=0x%x\r\n", eStatus, pTxXfer->uAggregPktsNum, pTxXfer->uAggregPktsLen, pTxXfer->pAggregFirstPkt, pTxXfer->pAggregLastPkt);
    if (eStatus == TXN_STATUS_ERROR)
    {
//       //Report(REPORT_SEVERITY_ERROR, "txXfer_SendAggregatedPkts: Status=%d, NumPkts=%d, AggregLen=%d, pFirstPkt=0x%x, pLastPkt=0x%x\r\n", eStatus, pTxXfer->uAggregPktsNum, pTxXfer->uAggregPktsLen, pTxXfer->pAggregFirstPkt, pTxXfer->pAggregLastPkt);
    }
#endif  /* TI_DBG */

    return eStatus;
}


#ifdef TI_DBG

void txXfer_ClearStats ()
{
    TTxXferObj *pTxXfer = gTxXferCB;

    os_memset (pTxXfer, 0,(sizeof(pTxXfer->aDbgCountPktAggreg)));
}

void txXfer_PrintStats ()
{
#ifdef REPORT_LOG
    TTxXferObj *pTxXfer = gTxXferCB;
    uint32_t   i;

   //GTRACE(1, "Print Tx Xfer module info\r\n"));
   //Report(("=========================\r\n"));
   //GTRACE(1, "uAggregMaxPkts     = %d\r\n", pTxXfer->uAggregMaxPkts));
   //GTRACE(1, "uAggregMaxLen      = %d\r\n", pTxXfer->uAggregMaxLen));
   //GTRACE(1, "uAggregPktsNum     = %d\r\n", pTxXfer->uAggregPktsNum));
   //GTRACE(1, "uAggregPktsLen     = %d\r\n", pTxXfer->uAggregPktsLen));
    for (i = 1; i < DBG_MAX_AGGREG_PKTS; i++)
    {
       //GTRACE(1, "uCountPktAggreg-%2d = %d\r\n", i, pTxXfer->aDbgCountPktAggreg[i]));
    }
#endif
}

#endif /* TI_DBG */


