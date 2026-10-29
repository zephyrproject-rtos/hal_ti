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
/** \file   WBusDrv.c
 *  \brief  The transport bus driver upper layer. Platform independent.
 *          Uses the SpiAdapter/HIF adapter API.
 *          Introduces a generic bus-independent API upwards.
 *  
 *  \see    txn_bus_drv.h,
 */

#include <bus_if.h>
#include <txn_bus_drv.h>
#include "osi_type.h"
#include "osi_kernel.h"

#define __FILE_ID__		FILE_ID_89

/************************************************************************
 * Defines
 ************************************************************************/

#define MAX_TXN_PARTS     MAX_XFER_BUFS * 5

/************************************************************************
 * Types
 ************************************************************************/

/* A single SDIO bus transaction which is a part of a complete transaction (TTxnStruct) */
typedef struct
{
    uint32_t          bBlkMode;           /* If TRUE this is a block-mode SDIO transaction */
    uint32_t          uLength;            /* Length in byte */
    uint32_t          uHwAddr;            /* The device address to write to or read from */
    void *            pHostAddr;          /* The host buffer address to write from or read into */
    uint32_t          bMore;              /* If TRUE, indicates the lower driver to keep awake for more transactions */
} TTxnPart;


/* The busDrv module Object */
typedef struct _TBusDrvObj
{
    TTxnStruct *    pCurrTxn;           /* The transaction currently being processed */
    TTxnPart        aTxnParts[MAX_TXN_PARTS]; /* The actual bus transactions of current transaction */
    uint32_t        uCurrTxnPartsNum;   /* Number of transaction parts composing the current transaction */
    uint32_t        uTxnLength;         /* The current transaction accumulated length (including Tx aggregation case) */
    uint32_t        uPartNum;           /* The Transaction part number */
} TBusDrvObj;


TBusDrvObj *gBus = NULL;


/************************************************************************
 *
 *   Module functions implementation
 *
 ************************************************************************/

/** 
 * \fn     busDrv_Destroy
 * \brief  Destroy the module. 
 * 
 * Close  lower bus driver and free the module's object.
 * 
 * \note   
 * \param  The module's object
 * \return 0 on success or -1 on failure
 * \sa     busDrv_Create
 */ 
int busDrv_Destroy ()
{
    TBusDrvObj *pBusDrv = gBus;

    if (pBusDrv)
    {
        os_free (pBusDrv);
        gBus = NULL;
    }
    return 0;
}


/****************************************************************************
 *                      busDrv_Init
 ****************************************************************************
 * DESCRIPTION: config the module.
 *
 * INPUTS:  hBusDrv - handle to the module context
 *          hReport - handle to report module context that is used when we output debug messages
 *          CBFunc  - The callback to call upon transaction complete (calls the tasklet).
 *          CBArg   - The handle for the CBFunc.
 *
 * OUTPUT:  none.
 *
 * RETURNS: one of the error codes (0 => 0)
 ****************************************************************************/
void busDrv_Init ()
{
    gBus = os_malloc(sizeof(TBusDrvObj));
    
    os_memset (gBus, 0, sizeof(TBusDrvObj));
}


/**
 * \fn     busDrv_PrepareTxnParts
 * \brief  Prepare write or read transaction parts
 * 
 * Called by busDrv_Transact().
 * Prepares the actual sequence of SDIO bus transactions in a table.
 * Use a DMA-able buffer for the bus transaction, so all data is copied
 *     to it from the host buffer(s) before write transactions,
 *     or copied from it to the host buffers after read transactions.
 * 
 * \note
 * \param  pBusDrv - The module's object
 * \param  pTxn    - The transaction object
 * \return TRUE if we are in the middle of a Tx aggregation
 * \sa     busDrv_Transact, busDrv_SendTxnParts,
 */

uint32_t busDrv_PrepareTxnParts(TBusDrvObj *pBusDrv, TTxnStruct *pTxn)
{
    uint32_t uPartNum     = 0;
    uint32_t uCurrHwAddr  = pTxn->uHwAddr;
    uint32_t bFixedHwAddr = TXN_PARAM_GET_FIXED_ADDR(pTxn);
    uint32_t bWrite       = (TXN_PARAM_GET_DIRECTION(pTxn) == TXN_DIRECTION_WRITE) ? TRUE : FALSE;
    uint8_t *pHostBuf    = NULL;
    uint32_t uBufNum;
    uint32_t uBufLen;

    pBusDrv->uTxnLength = 0;
    pBusDrv->uPartNum = 0;


    if(bWrite)
    {
        /* Go over the transaction buffers */
        for (uBufNum = 0; uBufNum < MAX_XFER_BUFS; uBufNum++)
        {
            uBufLen = pTxn->aLen[uBufNum];

            /* If no more buffers, exit the loop */
            if (uBufLen == 0)
            {
                break;
            }

            pHostBuf = pTxn->aBuf[uBufNum];

            /* Add buffer length to total transaction length */
            pBusDrv->uTxnLength += uBufLen;

            uPartNum = pBusDrv->uCurrTxnPartsNum;

            if (uPartNum > (MAX_XFER_BUFS-1))
            {
                ASSERT_GENERAL(0);//not suppose to happen
                return TXN_STATUS_ERROR; // Buffer overflow protection
            }

            /* If current buffer has full SDIO blocks, prepare a block-mode transaction part */
            pBusDrv->aTxnParts[uPartNum].bBlkMode = FALSE;
            pBusDrv->aTxnParts[uPartNum].uLength = uBufLen;
            pBusDrv->aTxnParts[uPartNum].uHwAddr = uCurrHwAddr;
            pBusDrv->aTxnParts[uPartNum].pHostAddr = (void*) pHostBuf;
            pBusDrv->aTxnParts[uPartNum].bMore = TRUE;


            uPartNum++;

            /* Set last More flag as specified for the whole Txn */
            //pBusDrv->aTxnParts[uPartNum - 1].bMore = TXN_PARAM_GET_MORE(pTxn);
            pBusDrv->uCurrTxnPartsNum = uPartNum;


        }

        /* If in a Tx aggregation, return TRUE (need to accumulate all parts before sending the transaction) */
        if (TXN_PARAM_GET_AGGREGATE(pTxn) == TXN_AGGREGATE_ON)
        {
            //TRACE(pBusDrv->hReport, REPORT_SEVERITY_INFORMATION, "busDrv_PrepareTxnParts: In aggregation so exit, uTxnLength=%d, bWrite=%d, Len0=%d, Len1=%d, Len2=%d, Len3=%d\n", pBusDrv->uTxnLength, bWrite, pTxn->aLen[0], pTxn->aLen[1], pTxn->aLen[2], pTxn->aLen[3]);
            return TRUE;//it is aggr
        }

        return FALSE;//not agge
    }
    else
    {
        /* Go over the transaction buffers */
        for (uBufNum = 0; uBufNum < MAX_XFER_BUFS; uBufNum++)
        {
            uBufLen = pTxn->aLen[uBufNum];

            /* If no more buffers, exit the loop */
            if (uBufLen == 0)
            {
                break;
            }

            /* Prepare Txn parts without copy */
            pBusDrv->aTxnParts[pBusDrv->uPartNum].bBlkMode  = FALSE;
            pBusDrv->aTxnParts[pBusDrv->uPartNum].uLength   = uBufLen;
            pBusDrv->aTxnParts[pBusDrv->uPartNum].uHwAddr   = uCurrHwAddr;
            pBusDrv->aTxnParts[pBusDrv->uPartNum].pHostAddr = (void *)pTxn->aBuf[uBufNum];
            pBusDrv->aTxnParts[pBusDrv->uPartNum].bMore     = TRUE;

            /* If not fixed HW address, increment it by this part's size */
            if (!bFixedHwAddr)
            {
                uCurrHwAddr += uBufLen;
            }

            pBusDrv->uPartNum++;


            /* Add buffer length to total transaction length */
            pBusDrv->uTxnLength += uBufLen;
        }
        /* TXN length of data packet might be aligned to SDIO block size.
           Thus, we add padding size to total transaction length
           without copy the padding to DMA buffer */


        /* If in a Tx aggregation, return TRUE (need to accumulate all parts before sending the transaction) */
        if (TXN_PARAM_GET_AGGREGATE(pTxn) == TXN_AGGREGATE_ON)
        {
            return TRUE;
        }

        /* all parts are ready */
        uPartNum = pBusDrv->uPartNum;

        /* Set last More flag as specified for the whole Txn */
        pBusDrv->aTxnParts[uPartNum - 1].bMore = TXN_PARAM_GET_MORE(pTxn);
        pBusDrv->uCurrTxnPartsNum = uPartNum;
        pBusDrv->uTxnLength = 0;
        pBusDrv->uPartNum = 0;

        /* Return FALSE to indicate that we are not in the middle of a Tx aggregation so the Txn is ready to send */
        return FALSE;
    }

}



/**
 * \fn     busDrv_SendTxnParts
 * \brief  Send prepared transaction parts
 * 
 * Called by busDrv_Transact().
 * Sends the prepared transaction parts in a loop.
 * All transaction parts are completed in this context, since the SDIO driver
 *   blocks us until completion if it uses a DMA.
 * 
 * \note
 * \param  pBusDrv - The module's object
 * \return COMPLETE or ERROR
 * \sa     busDrv_Transact, busDrv_PrepareTxnParts
 */
ETxnStatus busDrv_SendTxnParts(TBusDrvObj *pBusDrv)
{
    int eStatus;
    TTxnPart   *pTxnPart;
    TTxnStruct *pTxn = pBusDrv->pCurrTxn;
    uint32_t   i;
    uint8_t direction = TXN_PARAM_GET_DIRECTION(pTxn);
    uint32_t FixedAdder = ((TXN_PARAM_GET_FIXED_ADDR(pTxn) == 1) ? 1 : 0);



    /* Send all transaction parts one by one to SDIO driver */
    for (i = 0; i < pBusDrv->uCurrTxnPartsNum; i++)
    {
        pTxnPart = &(pBusDrv->aTxnParts[i]);

        /* If single step, send ELP byte */
        if (TXN_PARAM_GET_SINGLE_STEP(pTxn))
        {
            if(0 != direction)
            {
                //read
                eStatus = bus_sendReadCommand(pTxnPart->uHwAddr, pTxnPart->pHostAddr, pTxnPart->uLength, 0, 0xFF);
            }
            else
            {
                eStatus = bus_sendWriteCommand(pTxnPart->uHwAddr, pTxnPart->pHostAddr, pTxnPart->uLength, 0);
            }
            if (eStatus != 0)
            {
                pBusDrv->uCurrTxnPartsNum = 0;
                return TXN_STATUS_ERROR;
            }
        }
        else
        {
            if(0 != direction)
            {
                //read
                eStatus = bus_sendReadCommand(pTxnPart->uHwAddr, pTxnPart->pHostAddr, pTxnPart->uLength, FixedAdder, 0xFF);
            }
            else
            {
                eStatus = bus_sendWriteCommand(pTxnPart->uHwAddr, pTxnPart->pHostAddr, pTxnPart->uLength, FixedAdder);
            }

            /* If error, set error in Txn struct, call TxnDone CB if not fully sync, and exit */
            if (eStatus < 0)
            {
                pBusDrv->uCurrTxnPartsNum = 0;
                TXN_PARAM_SET_STATUS(pTxn, TXN_PARAM_STATUS_ERROR);
                return TXN_STATUS_ERROR;
            }
        }
    }
    pBusDrv->uCurrTxnPartsNum = 0;
    return TXN_STATUS_COMPLETE;
}



/**
 * \fn     busDrv_Transact
 * \brief  Process transaction
 *
 * Called by the TwIf module to initiate a new transaction.
 * Prepare the transaction parts (SDIO driver layer transactions),
 *      and send them one by one to the lower layer.
 *
 * \note   It's assumed that this function is called only when idle (i.e. previous Txn is done).
 * \param  hBusDrv - The module's object
 * \param  pTxn    - The transaction object
 * \return COMPLETE or ERROR
 * \sa     busDrv_PrepareTxnParts, busDrv_SendTxnParts
 */
ETxnStatus busDrv_Transact(TTxnStruct *pTxn)
{
    TBusDrvObj *pBusDrv = gBus;
    uint32_t     bWithinAggregation;
    ETxnStatus  eStatus;

    pBusDrv->pCurrTxn = pTxn;

    /* Set status OK in Txn struct (changed later to error if transaction fails) */
    TXN_PARAM_SET_STATUS(pTxn, TXN_PARAM_STATUS_OK);

    /* Prepare the transaction parts in a table. */
    bWithinAggregation = busDrv_PrepareTxnParts(pBusDrv, pTxn);

    /* If in the middle of Tx aggregation, return Complete (current Txn was coppied to buffer but not sent) */
    if (bWithinAggregation)
    {
        return TXN_STATUS_COMPLETE;
    }

    /* Send the prepared transaction parts. */
    eStatus = busDrv_SendTxnParts(pBusDrv);

    /* return transaction status - COMPLETE or ERROR */
    return eStatus;
}









