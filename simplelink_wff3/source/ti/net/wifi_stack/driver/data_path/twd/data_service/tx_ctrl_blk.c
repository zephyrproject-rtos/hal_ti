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
 *   MODULE:  txCtrlBlk.c
 *
 *   PURPOSE: Maintains active packets Tx attributes table (including descriptor).
 *
 *   DESCRIPTION:
 *   ============
 *      This module allocates and frees table entry for each packet in the Tx
 *      process (from sendPkt by upper driver until Tx-complete).
 *
 ****************************************************************************/
#define __FILE_ID__  FILE_ID_69
#if 0
#include "osApi.h"
#include "tidef.h"
#include "report.h"
#include "context.h"
#include "public_types.h"
#endif

#include "osi_type.h"
#include <trnspt_thread.h>
#ifdef CC33xx
#include "public_share.h"
#else
#include "wl18xx_public_infoele.h"
#endif
#include "tw_driver.h"
#include "tx_ctrl_blk_api.h"
#include "tx_ctrl.h"
#include "osi_kernel.h"

/* The TxCtrlBlk module object - contains the control-block table. */
typedef struct
{
    TTxCtrlBlk  aTxCtrlBlkTbl[CTRL_BLK_ENTRIES_NUM]; /* The table of control-block entries. */
    uint32_t  uNumUsedEntries;
} TTxCtrlBlkObj;

TTxCtrlBlkObj *gTxCtrlBlkCB;

/****************************************************************************
 *                      txCtrlBlk_Create()
 ****************************************************************************
 * DESCRIPTION: Create the Tx control block table object
 *
 * INPUTS:  hOs
 *
 * OUTPUT:  None
 *
 * RETURNS: The Created object
 ****************************************************************************/
TTxCtrlBlkObj * txCtrlBlk_Create (void)
{
    gTxCtrlBlkCB = os_zalloc(sizeof(TTxCtrlBlkObj));
    if (gTxCtrlBlkCB == NULL)
	{
        return NULL;
	}
    return(gTxCtrlBlkCB);
}


/****************************************************************************
 *                      txCtrlBlk_Destroy()
 ****************************************************************************
 * DESCRIPTION: Destroy the Tx control block table object
 *
 * INPUTS:  hTxCtrlBlk - The object to free
 *
 * OUTPUT:  None
 *
 * RETURNS: OK or NOK
 ****************************************************************************/
uint32_t txCtrlBlk_Destroy (void)
{
    TTxCtrlBlkObj *pTxCtrlBlk = gTxCtrlBlkCB;

    if (pTxCtrlBlk)
    {
        os_free(pTxCtrlBlk);
    }

    return OK;
}


/****************************************************************************
 *               txCtrlBlk_Init()
 ****************************************************************************
   DESCRIPTION:  Initialize the Tx control block module.
 ****************************************************************************/
uint32_t txCtrlBlk_Init (void)
{
    TTxCtrlBlkObj *pTxCtrlBlk = txCtrlBlk_Create();
    TTxnStruct    *pTxn;
    uint32_t       entry;

    if (pTxCtrlBlk == NULL)
    {
        return NOK;
    }

    /* For all entries, write the entry index in the descriptor and the next entry address
         in the next free entery pointer. Init also some other fields. */
    for (entry = 0; entry < CTRL_BLK_ENTRIES_NUM; entry++)
    {
        pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.descID = 0;
        pTxCtrlBlk->aTxCtrlBlkTbl[entry].pNextFreeEntry       = &(pTxCtrlBlk->aTxCtrlBlkTbl[entry + 1]);
        pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.hlid    = 0;
        pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.csumData  = 0;

        /* Prepare the Txn fields to the host-slave register (fixed address) */
        pTxn = &(pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxnStruct);
        TXN_PARAM_SET(pTxn, TXN_LOW_PRIORITY, TXN_FUNC_ID_WLAN, TXN_DIRECTION_WRITE, TXN_FIXED_ADDR);
//        Report("\n\r, init : free-entry :0x%x \r\n",  (uint32_t) pTxCtrlBlk->aTxCtrlBlkTbl[entry].pNextFreeEntry);

    }

    /* Write null in the next-free index of the last entry. */
    pTxCtrlBlk->aTxCtrlBlkTbl[CTRL_BLK_ENTRIES_NUM - 1].pNextFreeEntry = NULL;

    pTxCtrlBlk->uNumUsedEntries = 0;

    return OK;
}

/****************************************************************************
 *                  txCtrlBlk_Alloc()
 ****************************************************************************
 * DESCRIPTION:
    Allocate a free control-block entry for the current Tx packet's parameters
      (including the descriptor structure).
    Note that entry 0 in the list is never allocated and points to the
      first free entry.
   *input : isMgmt , is the packet is mgmt or data,
   *note : for mgmt  there are reserved control blocks
 ****************************************************************************/
TTxCtrlBlk *txCtrlBlk_Alloc (uint8_t isMgmt)
{
    TTxCtrlBlkObj   *pTxCtrlBlk = gTxCtrlBlkCB;
    TTxCtrlBlk      *pFreeEntry,*pCurrentEntry; /* The pointer of the new entry allocated for the packet. */
    TTxCtrlBlk      *pFirstFreeEntry; /* The first entry just points to the first free entry. */

    /* Protect block allocation from preemption (may be called from external context) */
    trnspt_lockTxCtrlAlloc();

    //keep CTRL_BLK_ENTRIES_NUM - CTRL_BLK_ENTRIES_FOR_DATA_NUM to mgmt frames
    if(!isMgmt &&
            (pTxCtrlBlk->uNumUsedEntries >= (CTRL_BLK_ENTRIES_FOR_DATA_NUM)))
    {
        trnspt_unlockTxCtrlAlloc();
        //Report("\n\rError txCtrlBlk_Alloc: num entries > CTRL_BLK_ENTRIES_FOR_DATA_NUM");
        return NULL;
    }

    pFirstFreeEntry = &(pTxCtrlBlk->aTxCtrlBlkTbl[0]);


    pFreeEntry = pFirstFreeEntry->pNextFreeEntry; /* Get free entry. */

    /* If no free entries, print error (not expected to happen) and return NULL. */
    if (pFreeEntry->pNextFreeEntry == NULL)
    {
        TX_PRINT("Notice ! txCtrlBlk_alloc():  No free entry,  uNumUsedEntries=%d\r\n", pTxCtrlBlk->uNumUsedEntries);
        trnspt_unlockTxCtrlAlloc();
        return NULL;
    }
    pTxCtrlBlk->uNumUsedEntries++;
    //Report("\n\r txCtrlBlk_alloc():  UsedEntries=%d  allocate packet address :0x%x \r\n", pTxCtrlBlk->uNumUsedEntries, (uint32_t)pCurrentEntry);


    /* Link the first entry to the next free entry. */
    pFirstFreeEntry->pNextFreeEntry = pFreeEntry->pNextFreeEntry;

    pCurrentEntry = pFreeEntry; //this free entry is now allocated
    /* Clear the next-free-entry index just as an indication that our entry is not free. */
    pCurrentEntry->pNextFreeEntry = NULL;

    trnspt_unlockTxCtrlAlloc();

    pCurrentEntry->tTxPktParams.uFlags = 0;
    pCurrentEntry->tTxPktParams.uHeadroomSize = 0;
    pCurrentEntry->tTxPktParams.isNullDataFrame = 0;
    pCurrentEntry->tTxPktParams.fCb = NULL;
    pCurrentEntry->tTxPktParams.pInputDesc = NULL;
    os_memset(&pCurrentEntry->tTxDescriptor, 0, sizeof(TxIfDescriptor_t));
    pCurrentEntry->tTxPktParams.uAcCounteDone = 0;
    pCurrentEntry->tTxPktParams.uAcPendTXDataDone = 0;

    return pCurrentEntry;
}



/****************************************************************************
 *                  txCtrlBlk_Free()
 ****************************************************************************
 * DESCRIPTION:
    Link the freed entry after entry 0, so now it is the first free entry to
      be allocated.
 ****************************************************************************/
void txCtrlBlk_Free (TTxCtrlBlk *pCurrentEntry)
{
    TTxCtrlBlkObj   *pTxCtrlBlk = gTxCtrlBlkCB;
    TTxCtrlBlk *pFirstFreeEntry;

    if (!pTxCtrlBlk)
    {
        TX_PRINT_ERROR("\n\rpTxCtrlBlk was not allocated");
        return;
    }
    /* Protect block freeing from preemption (may be called from external context) */
    trnspt_lockTxCtrlAlloc();

    pFirstFreeEntry = &(pTxCtrlBlk->aTxCtrlBlkTbl[0]);

    /* If the pointed entry is already free, print error and exit (not expected to happen). */
    if (pCurrentEntry->pNextFreeEntry != NULL)
    {
        TX_PRINT_ERROR("\n\rtxCtrlBlk_Dree(): Entry %d already free, UsedEntries=%d\r\n",
                pCurrentEntry->tTxDescriptor.descID, pTxCtrlBlk->uNumUsedEntries);
        trnspt_unlockTxCtrlAlloc();
        return;
    }
    pTxCtrlBlk->uNumUsedEntries--;
    //Report("txCtrlBlk_Free():  UsedEntries=%d  free packet address :0x%x \r\n", pTxCtrlBlk->uNumUsedEntries, (uint32_t)pCurrentEntry);

    /* Link the freed entry between entry 0 and the next free entry. */
    pCurrentEntry->pNextFreeEntry   = pFirstFreeEntry->pNextFreeEntry;
    pFirstFreeEntry->pNextFreeEntry = pCurrentEntry;


    trnspt_unlockTxCtrlAlloc();
}


/****************************************************************************
 *                  txCtrlBlk_GetPointer()
 ****************************************************************************
 * DESCRIPTION:
    Return a pointer to the control block entry of the requested packet.
    Used upon tx-complete to retrieve info after getting the descId from the FW.
 ****************************************************************************/
TTxCtrlBlk *txCtrlBlk_GetPointer(uint32_t uIndex)
{
    TTxCtrlBlkObj *pTxCtrlBlk = gTxCtrlBlkCB;
    return ( &(pTxCtrlBlk->aTxCtrlBlkTbl[uIndex]) );
}


/****************************************************************************
 *                      txCtrlBlk_PrintTable()
 ****************************************************************************
 * DESCRIPTION:  Print the txCtrlBlk table main fields.
 ****************************************************************************/
#ifdef TI_DBG
void txCtrlBlk_PrintTable (void)
{
#ifdef REPORT_LOG
    TTxCtrlBlkObj *pTxCtrlBlk = gTxCtrlBlkCB;
    uint32_t      entry;

   //GTRACE(1, " Tx-Control-Block Information,  UsedEntries=%d\r\n", pTxCtrlBlk->uNumUsedEntries));
   //Report(("==============================================\r\n"));

    //for(entry = 0; entry < CTRL_BLK_ENTRIES_NUM; entry++)
    {
       //GTRACE(1, "Entry %d: DescID=%d, Next=0x%x, Len=%d, StartTime=%d, TID=%d, TotalBlks=%d, Flags=0x%x\r\n",
       //     entry, 
       //    pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.descID,
       //     pTxCtrlBlk->aTxCtrlBlkTbl[entry].pNextFreeEntry,
       //     ENDIAN_HANDLE_WORD(pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.length),
       //     ENDIAN_HANDLE_LONG(pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.startTime),
       //     pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxDescriptor.tid,
       //     pTxCtrlBlk->aTxCtrlBlkTbl[entry].tTxPktParams.uFlags));
    }
#endif
}
#endif /* TI_DBG */

extern txCtrl_t *gTxCtrlCB;
void txCtrlBlk_Set (txCtrl_t *pTxCtrl)
{
    TUdata *pUdata = pTxCtrl->pUdata;
    udata_SetParam(pUdata);

    gTxCtrlCB->tBackpressure.TransmitQOnTxComplete = pTxCtrl->tBackpressure.TransmitQOnTxComplete;
}
