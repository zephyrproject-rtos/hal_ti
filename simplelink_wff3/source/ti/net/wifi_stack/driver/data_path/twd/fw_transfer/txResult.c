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
/****************************************************************************
 *
 *   MODULE:  txResult.c
 *   
 *   PURPOSE:  Handle packets Tx results upon Tx-complete from the FW. 
 * 
 *   DESCRIPTION:  
 *   ============
 *      This module is called upon Tx-complete from FW. 
 *      It retrieves the transmitted packets results from the FW TxResult table and
 *        calls the upper layer callback function for each packet with its results.
 *
 ****************************************************************************/

#define __FILE_ID__  FILE_ID_77
#if 0
#include "tidef.h"
#include "osApi.h"
#include "report.h"
#include "public_host_int.h"
#include "public_descriptors.h"
#include "public_types.h"
#endif

#include "osi_kernel.h"
#include "public_share.h"
#include "tx_result_api.h"
#include "tw_driver.h"
#include "tx_hw_queue_api.h"
#include "tx.h"

ETxnStatus txResult_TxCmpltIntr(FwStatus_t *pFwStatus, uint32_t *outNumOfTxCmpltPckts);

/* Callback function definition for Tx sendPacketComplete */
typedef void (* TSendPacketCompleteCb)(TTxResultInfo *pTxResultInfo, uint32_t counter);

/* The TxResult module object. */
typedef struct
{
    TSendPacketCompleteCb    fSendPacketCompleteCb;   /* Tx-Complete callback function */
    void                    *hSendPacketCompleteHndl; /* Tx-Complete callback function handle */
    uint8_t                  uLastFwReleasedIdx;

} TTxResultObj;


static void txResult_Restart(void);

TTxResultObj *gTxResultCB = NULL;

/****************************************************************************
 *                      txResult_Create()
 ****************************************************************************
 * DESCRIPTION: Create the Tx-Result object 
 * 
 * INPUTS:  hOs
 * 
 * OUTPUT:  None
 * 
 * RETURNS: The Created object
 ****************************************************************************/
TTxResultObj * txResult_Create(void)
{
    gTxResultCB = os_zalloc(sizeof(TTxResultObj));
    if (gTxResultCB == NULL)
	{
        return NULL;
	}

    return(gTxResultCB);
}


/****************************************************************************
 *                      txResult_Destroy()
 ****************************************************************************
 * DESCRIPTION: Destroy the Tx-Result object 
 * 
 * INPUTS:  pTxResult - The object to free
 * 
 * OUTPUT:  None
 * 
 * RETURNS: OK or NOK
 ****************************************************************************/
uint32_t txResult_Destroy(void)
{
    TTxResultObj *pTxResult = gTxResultCB;

    if (pTxResult)
	{
        os_free(pTxResult);
	}

    return OK;
}


/****************************************************************************
 *               txResult_Init()
 ****************************************************************************
   DESCRIPTION:  
   ============
     Initialize the txResult module.
 ****************************************************************************/
uint32_t txResult_Init(void)
{
    TTxResultObj *pTxResult = txResult_Create();

    if (pTxResult == NULL)
    {
        return NOK;
    }

    txResult_Restart();

    return OK;
}


/****************************************************************************
 *               txResult_Restart()
 ****************************************************************************
   DESCRIPTION:  
   ============
     Restarts the Tx-Result module.
     Called upon init and recovery.
 ****************************************************************************/
static void txResult_Restart()
{
    gTxResultCB->uLastFwReleasedIdx = 0;
}


/****************************************************************************
 *                      txResult_setHwInfo()
 ****************************************************************************
 * DESCRIPTION:  
 *      Called after the HW configuration upon init or recovery.
 ****************************************************************************/
void txResult_setHwInfo(void)
{
    txResult_Restart();
} 


/****************************************************************************
 *                      txResult_TxCmpltIntr()
 ****************************************************************************
 * DESCRIPTION:   
 * ============
 *  Called upon DATA interrupt from the FW.
 *  If new Tx results are available, start handling them.
 * 
 * INPUTS:  pTxResult - the txResult object handle.
 *          pFwStatus - The FW status registers read by the FwEvent
 *  
 * OUTPUT:  outNumOfTxCmpltPckts - the number of new results handled within this call
 * 
 * RETURNS:  ETxnStatus 
 ***************************************************************************/
void tx_ImmediateComplete(FwStatus_t *pFwEvent)
{
    ETxnStatus eStatus;
    uint32_t  uNumOfTxCmpltPckts = 0;

    eStatus = txHwQueue_UpdateFreeResources(pFwEvent, uNumOfTxCmpltPckts);
    eStatus = txResult_TxCmpltIntr( pFwEvent, &uNumOfTxCmpltPckts);
}

ETxnStatus txResult_TxCmpltIntr(FwStatus_t *pFwStatus, uint32_t *outNumOfTxCmpltPckts)
{
    TTxResultObj   *pTxResult = gTxResultCB;
    uint8_t         index = 0, hostDescr=0;
    TTxResultInfo   tTxResultInfo[TX_RESULT_QUEUE_SIZE];
    uint32_t        counter = 0;

    index = pTxResult->uLastFwReleasedIdx;


    if (pFwStatus->fwInfo.txResultQueueIndex >= TX_RESULT_QUEUE_SIZE)
    {
       //GTRACE(1, "Bad FW TXdesc release index %d", pFwStatus->txDescReleaseQ.fw_release_index));
        TX_RESULT_PRINT_ERROR("\n\rError !!! Bad FW TXdesc release index %d", pFwStatus->fwInfo.txResultQueueIndex);
        return TXN_STATUS_ERROR;
    }

    if (index == pFwStatus->fwInfo.txResultQueueIndex)
    {
        //TX_RESULT_PRINT("\n\rtx_result:no new response received");
        return TXN_STATUS_COMPLETE;
    }
    TX_RESULT_PRINT("\n\rtx_result:uLastFwReleasedIdx:%d FWStatus txResultQueueIndex:%d", pTxResult->uLastFwReleasedIdx, pFwStatus->fwInfo.txResultQueueIndex);

    /* loop for every packet released and call its tx-complete cb routine  */
    while (index != pFwStatus->fwInfo.txResultQueueIndex)
    {
        hostDescr = pFwStatus->fwInfo.txResultQueue[index];

        tTxResultInfo[counter].uDescId = (hostDescr & TX_STATUS_DESC_ID_MASK);// tx_stat_byte = (uint8) (frame->tcw | (hifStatus << 7));
        //eStatus == 1 means success
        tTxResultInfo[counter].eStatus = !(hostDescr & TI_BIT(TX_STATUS_STAT_BIT_IDX));

        if(tTxResultInfo[counter].eStatus != 1)
        {
            TX_RESULT_PRINT("\n\rtxResult_TxCmpltIntr, loop:tx result:failed!!!,index:%u offset:%d uDescId:%d", index,counter, tTxResultInfo[counter].uDescId);
        }
        else
        {
            TX_RESULT_PRINT("\n\rtxResult_TxCmpltIntr, loop:tx result:success!!!,index:%u offset:%d uDescId:%d",index, counter, tTxResultInfo[counter].uDescId);
        }

        counter++;
        index++;
        /* cyclic buffer */
        if (index == TX_RESULT_QUEUE_SIZE)
        {
            index = 0;
        }
    }

    if(pTxResult->fSendPacketCompleteCb != NULL)
    {
        /****call txCtrl_TxCompleteCb() *****/
        pTxResult->fSendPacketCompleteCb( tTxResultInfo, counter);
    }
    else
    {
        TX_RESULT_PRINT_ERROR("\n\rError !!! fSendPacketCompleteCb is null ");
    }
    (*outNumOfTxCmpltPckts)+= counter; /* to be reported to the TxHwQ */

    pTxResult->uLastFwReleasedIdx = pFwStatus->fwInfo.txResultQueueIndex;
    return TXN_STATUS_COMPLETE;
}

/****************************************************************************
 *                      txResult_RegisterCb()
 ****************************************************************************
 * DESCRIPTION:  Register the upper driver Tx-Result callback functions.
 ****************************************************************************/
void txResult_RegisterCb(void *CBFunc, void *hCbObj)
{
    TTxResultObj* pTxResult = gTxResultCB;

	pTxResult->fSendPacketCompleteCb   = (TSendPacketCompleteCb)CBFunc;
	pTxResult->hSendPacketCompleteHndl = hCbObj;

}


#ifdef TI_DBG      /*  Debug Functions   */

/****************************************************************************
 *                      txResult_PrintInfo()
 ****************************************************************************
 * DESCRIPTION:  Prints TX result debug information.
 ****************************************************************************/
void txResult_PrintInfo(void)
{
#ifdef REPORT_LOG
    TTxResultObj* pTxResult = (TTxResultObj*)pTxResult;

   //GTRACE(1, "Tx-Result Module Information:\r\n"));
   //Report(("=============================\r\n"));
   //GTRACE(1, "uLastFwReleasedIdx:     %d\r\n", pTxResult->uLastFwReleasedIdx));
   //Report(("=============================\r\n"));
#endif
}


/****************************************************************************
 *                      txResult_ClearInfo()
 ****************************************************************************
 * DESCRIPTION:  Clears TX result debug information.
 ****************************************************************************/
void txResult_ClearInfo(void)
{
}

#endif  /* TI_DBG */


