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
 *   MODULE:  txHwQueue.c
 *   
 *   PURPOSE: manage the wlan hardware Tx memory blocks allocation per queue. 
 * 
 *   DESCRIPTION:  
 *   ============
 *      This module is responsible for the HW Tx data-blocks and descriptors allocation.
 *      The HW Tx blocks are allocated in the driver by rough calculations without 
 *        accessing the FW. 
 *      They are freed according to FW counters that are provided by the FwEvent module
 *          on every FW interrupt.
 ****************************************************************************/
#define __FILE_ID__  FILE_ID_70
#if 0
#include "osApi.h"
#include "report.h"
#endif

#include "osi_kernel.h"
#include "tw_driver.h"
#include "tx_ctrl_blk_api.h"
#include <cc3xxx_public_host_if.h>
#include "tx_hw_queue_api.h"
#include "tx_data_queue_api.h"
#include "tx_ctrl.h"

/* Translate input TID to AC */            
/* Note: This structure is shared with other modules */
const EAcTrfcType WMEQosTagToACTable[MAX_NUM_OF_802_1d_TAGS] =
    {QOS_AC_BE, QOS_AC_BK, QOS_AC_BK, QOS_AC_BE, QOS_AC_VI, QOS_AC_VI, QOS_AC_VO, QOS_AC_VO};

/* 
 *  Local definitions:
 */

#define BLKS_HW_ALLOC_SPARE             1  /* Default spare blocks per packet needed for FW processing */

#define FAST_LINK_PRIORITY_PKTS_THRESH      10  /* Fast link with more packets than threshold in FW gets low priority (Defualt value!! During run-time will be set by FW) */
#define LINK_PACKETS_LIMIT_ACTIVE               32 /* Max pkts sent to link in active mode (actually unlimited) (Defualt value!! During run-time will be set by FW) */

/* Calculate new number of used byte (the else is for wrap around case) */
#define SUBTRACT_UINT8_COUNTERS(uMinuend, uSubtrahend)                              \
                               (((uSubtrahend) <= (uMinuend)) ?                     \
                               ((uint32_t)((uMinuend) - (uSubtrahend))) :           \
                               (0x100 - (uint32_t)((uSubtrahend) - (uMinuend))))
#define  QOS_TX_BLKS_THRESHOLD_VO_DEF           6

#define BLKS_RESERVE_MGMT   8
            
/* Callback function definition for UpdateBusyMap */
typedef void (* TUpdateBackpressureCb)(TTxHwBackpressure *pBackpressure);



/* Per Link information */
typedef struct 
{
    Bool_e    bEnabled;               /* Link is enabled */
    Bool_e    bIsUnicast;             /* The link is used for unicast traffic */
    uint8_t   uLinkHostSentPckts;     /* Per Link, number of Tx packets the Driver sent(**) to FW */
    uint8_t   uLinkFwReleasedPckts;   /* Per Link, number of TX packets the FW released */
    uint8_t   uMaxPackets;            /* Max mem packets per link */
    uint8_t   uPriorityThreshold;     /* The link's priority threshold in packets (if used > threshold then low priority) */
    uint8_t   uHighPriorityThreshold; /* The link's high priority threshold in packets */
    uint8_t   uLowPriorityThreshold;  /* The link's low priority threshold in packets  */
} TTxHwLinkInfo;

/* Per AC information */
typedef struct
{
    uint8_t   uAcHostSentPckts;        /* Per AC, number of Tx packets the Driver sent to FW */
    uint8_t   uAcFwReleasedPckts;      /* Per AC, number of TX packets the FW released */
    uint8_t   uNumBlksCausedBusy;      /* Number of HW blocks that caused queue busy state. */
} TTxHwAcInfo; 

/* Specific Voice AC information */
typedef struct
{
    uint8_t   uNumBlksThresh;          /* Minimum HW blocks that must be reserved for Voice. */
    uint8_t   uAllocatedBlksCntr;      /* Accumulates allocated blocks for FW freed-blocks counter coordination. */ 
    uint8_t   uReleasedBlksCntr;       /* Accumulated freed blocks in FW. */ 
} TAcVoiceBlksInfo;

typedef struct
{
    uint32_t          tx_BlocksAvailable;
    uint32_t          tx_Blockallocated;
    uint32_t          tx_NumTxDescriptor;             /* number of descriptor available on fw */

    TUpdateBackpressureCb  fUpdateBackpressureCb;     /* The upper layers UpdateBusyMap callback */
    void             *hUpdateBusyMapHndl;             /* The handle for the fUpdateBackpressureCb */
    uint32_t          uNumTotalBlks;                  /* The total number of Tx blocks        */
    uint32_t          uNumTotalBlksFree;              /* Total number of free HW blocks       */    
    uint32_t          uNumTotalBlksUsed;              /* Total number of HW blocks occupied in the FW */    
    uint32_t          uNumTotalBlksSent;              /* Accumulated number of allocated blocks by driver */    
    uint32_t          uNumTotalBlksReleased;          /* Accumulated number of released blocks by FW */    
    uint32_t          uNumTotalTxDescriptors;         /* Total number of Tx Descriptors in the FW */
    uint32_t          uFwTxResultsCntr;               /* Accumulated freed descriptors in FW. */
    uint32_t          uDrvTxPacketsCntr;              /* Accumulated allocated descriptors in driver. */
    TTxHwBackpressure  tBackpressure;                 /* Per link and per AC busy and priority state bitmaps */
    TTxHwAcInfo       aTxHwAcInfo[MAX_NUM_OF_AC];     /* The per queue variables */
    uint32_t          uTxAcAllocPkts[MAX_NUM_OF_AC];  /* Total allocated frames in HW per queue */
    uint32_t          uTxTotalAllcPkts;               /* Total allocated frames in HW in al queues */
    TAcVoiceBlksInfo  tAcVoiceInfo;                   /* voice variables */    
    uint32_t          uAcLastPriorityBitmap;          /* bitmap to save the last indication which AC is on low */
    Bool_e            bAcPriorityInfoChanged;         /* indicate if AC priority changed */
    Bool_e            bIgnoreNewThreshold;            /* indicate if the new threshold should be ignored */
    TTxHwLinkInfo     aTxHwLinkInfo[WLANLINKS_MAX_LINKS];  /* The per link variables */
    uint32_t          uNumUnicastLinks;               /* Number of unicast links currently allocated */
    uint32_t          uLinkPrioFwBitmap;              /* bitmap to save the last LINKs priority state */
    uint32_t          uLinkPsFwBitmap;                /* bitmap to save the last LINKs PS status */
    uint32_t          uLinkSuspendedFwBitmap;         /* bitmap to save the last LINKs Suspend status */
    uint8_t           uTxFCSuspendThreshold;          /* TX Flow Control descriptor Suspend link threshold */
    uint8_t           uTxFCFastThreshold;             /* TX Flow Control descriptor Fast link threshold */
    uint8_t           uTxFCSlowThreshold;             /* TX Flow Control descriptor Slow link threshold */
    uint8_t           uTxFCStopFastThreshold;         /* TX Flow Control descriptor Stop Fast link threshold */
    uint8_t           uTxFCStopSlowThreshold;         /* TX Flow Control descriptor Stop Slow link threshold */
    uint32_t          uTxExtraMemBlocks;              /* Extra mem-blocks number needed per Tx packet (above what's needed for the actual length) */
    uint32_t          uFwLastTsf;                     /* FW TSF */

} TTxHwQueue;

static void updateLinksInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus, Bool_e *pLinkInfoChanged);
static void updateAcsInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus, Bool_e *pAcInfoChanged);
static void updateFwCoreStatusInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus,Bool_e *pLinkInfoChanged);
extern txCtrl_t *gTxCtrlCB;
TTxHwQueue *gTxHwQueueCB;

/* Translate packet timestamp to FW time, update lifeTime and uDriverDelay, and allocate desc-ID */
int32_t txHwQueue_PrepareDescForFw(TTxCtrlBlk *pPktCtrlBlk, uint16_t uLifeTime)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    uint32_t tx_NumMaxTxDescriptor;
#ifdef REMOVE_TX_CODE //TODO TX_CODE_WAS_REMOVED
    uint32_t uPktStartTime = pPktCtrlBlk->tTxDescriptor.startTime;  /* Contains host start time */
#endif
    uint32_t i;
    int32_t ret = TXN_STATUS_OK;

#ifdef REMOVE_TX_CODE //TODO TX_CODE_WAS_REMOVED
    /* Save host packet handling time until this point (for statistics) */
    pPktCtrlBlk->tTxPktParams.uDriverDelay = osi_GetTimeMS() - uPktStartTime;

    /* Translate packet timestamp to FW time and undate descriptor */
    //uPktStartTime = TWD_TranslateToFwTime(pTxCtrl->hTWD, uPktStartTime);
    uPktStartTime = fwEvent_TranslateToFwTime(uPktStartTime);
    pPktCtrlBlk->tTxDescriptor.startTime = uPktStartTime;//ENDIAN_HANDLE_LONG(uPktStartTime);
#endif
    pPktCtrlBlk->tTxDescriptor.lifeTime  = uLifeTime;//ENDIAN_HANDLE_WORD(uLifeTime);

    /* Allocate a free desc-ID from the O(1) free-stack */
    if (pTxCtrl->uDescIdFreeStackTop == 0)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rError !! no free descriptor id\n");
        return TXN_STATUS_ERROR;
    }
    i = pTxCtrl->aDescIdFreeStack[--pTxCtrl->uDescIdFreeStackTop];
    pTxCtrl->aTxDescIds[i] = pPktCtrlBlk;
    pPktCtrlBlk->tTxDescriptor.descID = i;
    TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rDescriptor Id chosen:, descID=%d", i);
    return TXN_STATUS_OK;
}


void txHwQueue_FreeDescForFw(TTxCtrlBlk *pPktCtrlBlk)
{
    uint8           descID;
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    trnspt_lockTxQueue();
    descID = pPktCtrlBlk->tTxDescriptor.descID;
    TX_FRAME_FLOW_CNTRL_PRINT("\r\nfree_tx_descr id , descID: %d ",descID);
    pTxCtrl->aTxDescIds[descID] = NULL;
    pPktCtrlBlk->tTxDescriptor.descID = 0;
    pTxCtrl->aDescIdFreeStack[pTxCtrl->uDescIdFreeStackTop++] = descID;
    trnspt_unlockTxQueue();
}

int32_t txHwQueue_VerifyDescriptorValid(uint32_t desc_id)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    uint32_t tx_NumMaxTxDescriptor;

    tx_NumMaxTxDescriptor = MIN(pTxHwQueue->tx_NumTxDescriptor,MAX_TX_DESC_ID);

    if(desc_id >= tx_NumMaxTxDescriptor)
    {
        return FALSE;
    }
    return TRUE;
}

#if 0
/* Calculate how many mem-blocks are available for this AC */
static inline uint32_t calcAcAvailableBlks(TTxHwQueue *pTxHwQueue, uint32_t uAcId)
{
    /* TTxHwAcInfo *pAcInfo = &(pTxHwQueue->aTxHwAcInfo[uAcId]); Unused variable */
    TAcVoiceBlksInfo *pVoInfo = &pTxHwQueue->tAcVoiceInfo;
    uint32_t uBlksToReserve;
    uint8_t  uVoBlksUsed;

    /* If no descriptors are available, return 0 (can't transmit anything). */
    if ((pTxHwQueue->uDrvTxPacketsCntr - pTxHwQueue->uFwTxResultsCntr) >= pTxHwQueue->uNumTotalTxDescriptors)
    {
        //Report(REPORT_SEVERITY_WARNING, "NO DESCRIPTORS. (Used Descriptors=%d out of Total TX Descriptors=%d)!!\r\n", (pTxHwQueue->uDrvTxPacketsCntr - pTxHwQueue->uFwTxResultsCntr), pTxHwQueue->uNumTotalTxDescriptors);
        return 0;
    }

    pVoInfo = &pTxHwQueue->tAcVoiceInfo;
    uVoBlksUsed = SUBTRACT_UINT8_COUNTERS(pVoInfo->uAllocatedBlksCntr, pVoInfo->uReleasedBlksCntr);

    /* If it's not VO AC and the VO is not using all its reserved blocks yet, we need to reserve them */
    if ((uAcId != QOS_AC_VO) && (uVoBlksUsed < pVoInfo->uNumBlksThresh))
    {
        uBlksToReserve = pVoInfo->uNumBlksThresh - uVoBlksUsed;
    }
    else 
    {
        uBlksToReserve = 0;
    }

    /* Return the total free blocks minus blocks reserved for VO */
    if (pTxHwQueue->uNumTotalBlksFree > uBlksToReserve) 
    {
        return (pTxHwQueue->uNumTotalBlksFree - uBlksToReserve);
    }
    return 0;
}
#endif

/****************************************************************************
 *                      txHwQueue_Create()
 ****************************************************************************
 * DESCRIPTION: Create the Tx buffers pool object 
 * 
 * INPUTS:  None
 * 
 * OUTPUT:  None
 * 
 * RETURNS: The Created object
 ****************************************************************************/
TTxHwQueue * txHwQueue_Create (void)
{
    gTxHwQueueCB = os_zalloc(sizeof(TTxHwQueue));
    if (gTxHwQueueCB == NULL)
    {
        return NULL;
    }

    return gTxHwQueueCB;
}


/****************************************************************************
 *                      txHwQueue_Destroy()
 ****************************************************************************
 * DESCRIPTION: Destroy the Tx buffers pool object 
 * 
 * INPUTS:  None
 * 
 * OUTPUT:  None
 * 
 * RETURNS: OK or NOK
 ****************************************************************************/
uint32_t txHwQueue_Destroy (void)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    if (pTxHwQueue)
    {
        os_free(pTxHwQueue);
    }
    return OK;
}


/****************************************************************************
 *               txHwQueue_Init()
 ****************************************************************************

  DESCRIPTION:  Initialize module handles.

 ****************************************************************************/
uint32_t txHwQueue_Init (void)
{
    TTxHwQueue *pTxHwQueue = txHwQueue_Create();
    uint32_t   uHlid;
    
    if (pTxHwQueue == NULL)
    {
        return NOK;
    }
#if 0
    pTxHwQueue->uNumUnicastLinks = 0;
    pTxHwQueue->uTxExtraMemBlocks = NUM_EXTRA_BLKS_DEFAULT_SECURITY;
    pTxHwQueue->bIgnoreNewThreshold = FALSE;
 #endif   
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pTxHwQueue->aTxHwLinkInfo[uHlid].bEnabled = FALSE;
        pTxHwQueue->aTxHwLinkInfo[uHlid].uHighPriorityThreshold = 0;
        pTxHwQueue->aTxHwLinkInfo[uHlid].uLowPriorityThreshold = 0;
    }

    return OK;
}


/****************************************************************************
 *                      txHwQueue_Config()
 ****************************************************************************
 * DESCRIPTION: Configure the Tx buffers pool object 
 * 
 * INPUTS:  None
 * 
 * OUTPUT:  None
 * 
 * RETURNS: 
 ****************************************************************************/
#if 0
uint32_t txHwQueue_Config (void)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    pTxHwQueue->tAcVoiceInfo.uNumBlksThresh = QOS_TX_BLKS_THRESHOLD_VO_DEF;
    
    return OK;
}
#endif
/****************************************************************************
 *                      txHwQueue_SetInitializeHwBlocks()
 ****************************************************************************
 * DESCRIPTION: Configure the Tx buffers that the HW supports
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS:
 ****************************************************************************/
uint32_t txHwQueue_SetInitializeHwBlocks (uint32_t tx_BlocksAvailable, uint32_t tx_NumTxDescriptor)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    pTxHwQueue->tx_BlocksAvailable = tx_BlocksAvailable;
    pTxHwQueue->tx_Blockallocated = 0;
    pTxHwQueue->tx_NumTxDescriptor = tx_NumTxDescriptor;
    return OK;
}
/****************************************************************************
 * DESCRIPTION: reduce the availableTx buffers that the HW supports
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS:
 ****************************************************************************/
uint32_t txHwQueue_UpdateAllocHwBlocks (uint32_t tx_Blocks, uint32_t uAc)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    pTxHwQueue->tx_BlocksAvailable -= tx_Blocks;
    pTxHwQueue->tx_Blockallocated += tx_Blocks;
    pTxHwQueue->uTxAcAllocPkts[uAc]++;
    pTxHwQueue->uTxTotalAllcPkts++;
    return OK;
}

/****************************************************************************
 * DESCRIPTION: increase  the available Tx buffers that the HW supports
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS:
 ****************************************************************************/
uint32_t txHwQueue_UpdateFreeHwBlocks (uint32_t tx_Blocks, TTxCtrlBlk *pPktCtrlBlk)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    uint32_t    uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];

    pTxHwQueue->tx_BlocksAvailable += tx_Blocks;
    pTxHwQueue->tx_Blockallocated -= tx_Blocks;

    pTxHwQueue->uTxAcAllocPkts[uAc] -= pPktCtrlBlk->tTxPktParams.uAcCounteDone;
    pTxHwQueue->uTxTotalAllcPkts -= pPktCtrlBlk->tTxPktParams.uAcCounteDone;
    pPktCtrlBlk->tTxPktParams.uAcCounteDone = 0;

    return OK;
}

/****************************************************************************
 *                      txHwQueue_GetHwBlocks()
 ****************************************************************************
 * DESCRIPTION: Gets the Tx buffers that the HW supports
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS:
 ****************************************************************************/
uint32_t txHwQueue_GetHwBlocks ()
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

   return( pTxHwQueue->tx_BlocksAvailable);
}

/****************************************************************************
 * DESCRIPTION: Gets the  avg blocks that are required to be available for frame
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS:
 ****************************************************************************/
uint32_t txHwQueue_GetHwBlocksRequireForAvgFrame ()
{
   return (BLKS_RESERVE_MGMT + 3);
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetTxAcPktsCount()
 * 
 * DESCRIPTION: Gets the the tx count which were send to the FW and didn't recieve tx complete
 *
 * INPUTS:  uAc - access category
 *
 * OUTPUT:  None
 *
 * RETURNS: Tx Allocated Pkts Count in FW
 ****************************************************************************/
uint32_t txHwQueue_GetTxAcPktsCount(uint32_t uAc)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

   return( pTxHwQueue->uTxAcAllocPkts[uAc]);
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetTxTotalPktsCount()
 * 
 * DESCRIPTION: Gets the total tx packets that allocated in  FW
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS: Tx Total Allocated Pkts Count in FW
 ****************************************************************************/
uint32_t txHwQueue_GetTxTotalPktsCount()
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

   return( pTxHwQueue->uTxTotalAllcPkts);
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetlastFWTsf()
 * 
 * DESCRIPTION: Gets the last FW TSF time
 *
 * INPUTS:  None
 *
 * OUTPUT:  None
 *
 * RETURNS: FW Tsf
 ****************************************************************************/
uint32_t txHwQueue_GetlastFWTsf()
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

   return( pTxHwQueue->uFwLastTsf);
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetLinkPrioThreshold()
 * 
 * DESCRIPTION: Get high / low threshold per each link
 *
 * INPUTS:  hlid - link id, piority
 *
 * OUTPUT:  None
 *
 * RETURNS: threshold
 ****************************************************************************/
uint32_t txHwQueue_GetLinkPrioThreshold(uint32_t hlid, uint32_t linkPriorityToServe)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    if (linkPriorityToServe == 1) // HIGH_PRIORITY_LINK_LIST
    {
        return( pTxHwQueue->aTxHwLinkInfo[hlid].uHighPriorityThreshold);
    }
    else  //LOW_PRIORITY_LINK_LIST
    {
        return( pTxHwQueue->aTxHwLinkInfo[hlid].uLowPriorityThreshold);
    }
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetTxFlowControlLinkBitmaps()
 * 
 * DESCRIPTION: Gets Tx Flow control links bitmaps from fw core status
 *
 * INPUTS: None
 *
 * OUTPUT: pSuspendBitmap , pFastBitmap, pPsBitmap
 *
 * RETURNS: None
 ****************************************************************************/
void txHwQueue_GetTxFlowControlLinkBitmaps(uint32_t *pSuspendBitmap, uint32_t *pFastBitmap, uint32_t *pPsBitmap)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    *pSuspendBitmap = gTxHwQueueCB->uLinkSuspendedFwBitmap;
    *pFastBitmap    = gTxHwQueueCB->uLinkPrioFwBitmap;
    *pPsBitmap      = gTxHwQueueCB->uLinkPsFwBitmap;
}

/****************************************************************************
 * FUNCTION:    txHwQueue_GetTxFlowControlThresholds()
 * 
 * DESCRIPTION: Gets Tx Flow control link thresholds from fw core status
 *
 * INPUTS: None
 *
 * OUTPUT: 
 *
 * RETURNS: None
 ****************************************************************************/
void txHwQueue_GetTxFlowControlThresholds(uint8_t *pTxSuspendThold, uint8_t *pTxFastThold, 
                                            uint8_t *pTxSlowThold, uint8_t *pTxStopFastThold, uint8_t *pTxstopSlowThold)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    *pTxSuspendThold   = pTxHwQueue->uTxFCSuspendThreshold;
    *pTxFastThold      = gTxHwQueueCB->uTxFCFastThreshold;
    *pTxSlowThold      = gTxHwQueueCB->uTxFCSlowThreshold;
    *pTxStopFastThold  = gTxHwQueueCB->uTxFCStopFastThreshold;
    *pTxstopSlowThold  = gTxHwQueueCB->uTxFCStopSlowThreshold;
}

/****************************************************************************/

static uint32_t txHwQueue_get_spare_blocks(TTxCtrlBlk *pPktCtrlBlk)
{
    /* If we have keys requiring extra spare, indulge them */
    if (pPktCtrlBlk->tTxPktParams.extraSpareKeyCount  )
        return TX_HW_EXTRA_BLOCK_SPARE;

    return TX_HW_BLOCK_SPARE;
}

static uint32_t txHwQueue_calc_tx_blocks(uint32_t len, uint32_t spare_blks)
{
    uint32_t blk_size = OSPREY_TX_HW_BLOCK_SIZE;
    /* In osprey the packet will be stored along with its internal descriptor.
     * the descriptor is not part of the host transaction, but should be considered as part of
     * the allocate memory blocks in the device
     */
    len = len + OSPREY_INTERNAL_DESC_SIZE;
    return ((len + blk_size - 1) / blk_size) + spare_blks;
}

static void txHwQueue_set_tx_desc_blocks(TTxCtrlBlk *pPktCtrlBlk, uint32_t blks)
{
    pPktCtrlBlk->tTxDescriptor.totalMemBlks = blks;
    pPktCtrlBlk->tTxPktParams.uAcCounteDone = 1;
}

static uint32_t txHwQueue_unset_tx_desc_blocks(TTxCtrlBlk *pPktCtrlBlk)
{
    uint32_t blks;
    blks = pPktCtrlBlk->tTxDescriptor.totalMemBlks;
    pPktCtrlBlk->tTxDescriptor.totalMemBlks = 0;
    return blks;
}


int32_t txHwQueue_allocate_mem_blocks(uint8_t isMgmt,TTxCtrlBlk *pPktCtrlBlk)
{
    int ret = TXN_STATUS_ERROR;
    uint32_t spare_blocks;
    uint32_t total_len,total_required_blocks,available_hw_blocks;
    uint32_t uAc = WMEQosTagToACTable[pPktCtrlBlk->tTxDescriptor.tid];

    spare_blocks = txHwQueue_get_spare_blocks(pPktCtrlBlk);

    total_len = pPktCtrlBlk->tTxDescriptor.length;

    total_required_blocks = txHwQueue_calc_tx_blocks(total_len, spare_blocks);

    available_hw_blocks = txHwQueue_GetHwBlocks();

    if(!isMgmt)
    {
        if(available_hw_blocks <= BLKS_RESERVE_MGMT)
        {
            TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rWarning !! reserved ,allocate_mem_blocks no available mem blocks, isMgmt :%d total_required_blocks:%d available_hw_blocks:%d, requeue",
                    isMgmt,total_required_blocks,available_hw_blocks);
            return ret;
        }
    }

    if (total_required_blocks <= available_hw_blocks)
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\r\nallocate of block success !mem blocks isMgmt :%d total_required_blocks:%d available_hw_blocks:%d",
                isMgmt,total_required_blocks,available_hw_blocks);

        txHwQueue_set_tx_desc_blocks(pPktCtrlBlk, total_required_blocks);

        txHwQueue_UpdateAllocHwBlocks(total_required_blocks, uAc);
        ret = TXN_STATUS_OK;

    }
    else
    {
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rWarning !! allocate_mem_blocks no available mem blocks, isMgmt :%d total_required_blocks:%d available_hw_blocks:%d, requeue",
                isMgmt,total_required_blocks,available_hw_blocks);

    }
    return ret;//ret== TXN_STATUS_ERROR means there is no available blocks
}


int32_t txHwQueue_free_allocated_mem_blocks(TTxCtrlBlk *pPktCtrlBlk)
{
    uint32_t tx_blks, available_hw_blocks;
    trnspt_lockTxQueue();
    tx_blks = txHwQueue_unset_tx_desc_blocks(pPktCtrlBlk);
    txHwQueue_UpdateFreeHwBlocks (tx_blks, pPktCtrlBlk);
    available_hw_blocks = txHwQueue_GetHwBlocks();
    trnspt_unlockTxQueue();
    TX_FRAME_FLOW_CNTRL_PRINT_MUST("\r\nFree allocate of block success !mem blocks tx_blks:%d available_hw_blocks:%d",
            tx_blks,available_hw_blocks);
    return 0;
}

#if 0

/****************************************************************************
 *                  txHwQueue_SetHwInfo()
 ****************************************************************************

  DESCRIPTION:  
  
    Called after the HW configuration in the driver init or recovery process.
    Configure Tx HW information, including Tx-HW-blocks number, and per queue
      Tx-descriptors number. Than, restart the module variables.

    Two thresholds are defined per queue:
    a)  TxBlocksLowPercentPerQueue[queue] - The lower threshold is the minimal number of 
        Tx blocks guaranteed for each queue.
        The sum of all low thresholds should be less than 100%.
    b)  TxBlocksHighPercentPerQueue[queue] - The higher threshold is the maximal number of
        Tx blocks that may be allocated to the queue.
        The extra blocks above the low threshold can be allocated when needed only 
        if they are currently available and are not needed in order to guarantee
        the other queues low threshold.
        The sum of all high thresholds should be more than 100%.
 ****************************************************************************/
uint32_t txHwQueue_SetHwInfo(TDmaParams *pDmaParams) 
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    
    pTxHwQueue->uNumTotalBlks = pDmaParams->NumTxBlocks;
    pTxHwQueue->uNumTotalTxDescriptors = pDmaParams->uHostTxDescriptors;

    //Report(REPORT_SEVERITY_INFORMATION, "txHwQueue_SetHwInfo: uNumTotalBlks = %d, uNumTotalTxDescriptors = %d\r\n", pTxHwQueue->uNumTotalBlks, pTxHwQueue->uNumTotalTxDescriptors);
    
    /* Restart the module variables. */
    txHwQueue_Restart ();

    return OK;
}


/****************************************************************************
 *               txHwQueue_Restart()
 ****************************************************************************
   DESCRIPTION:  
   ============
     Called after the HW configuration in the driver init or recovery process.
     Restarts the Tx-HW-Queue module.
 ****************************************************************************/
uint32_t txHwQueue_Restart (void)
{
    TTxHwQueue     *pTxHwQueue = gTxHwQueueCB;
    TTxHwAcInfo    *pAcInfo;
    uint32_t      TxQid;
    TTxHwLinkInfo  *pLinkInfo;
    uint32_t      uHlid;

    pTxHwQueue->uNumTotalBlksFree = pTxHwQueue->uNumTotalBlks; /* All blocks are free at restart. */
    pTxHwQueue->uNumTotalBlksSent = 0;
    pTxHwQueue->uNumTotalBlksReleased = 0;
    pTxHwQueue->uFwTxResultsCntr = 0;
    pTxHwQueue->uDrvTxPacketsCntr = 0;
    pTxHwQueue->tBackpressure.uAcBusyBitmap = 0;
    pTxHwQueue->tBackpressure.uLinkBusyBitmap = 0;
    pTxHwQueue->tBackpressure.uLinkPriorityBitmap = 0;
    pTxHwQueue->tBackpressure.aAcQueueLen[0] = 0;
    pTxHwQueue->tBackpressure.aAcQueueLen[1] = 0;
    pTxHwQueue->tBackpressure.aAcQueueLen[2] = 0;
    pTxHwQueue->tBackpressure.aAcQueueLen[3] = 0;

    /* Info per AC */
    for (TxQid = 0; TxQid < MAX_NUM_OF_AC; TxQid++)
    {
        pAcInfo = &pTxHwQueue->aTxHwAcInfo[TxQid];

        pAcInfo->uAcHostSentPckts    = 0;
        pAcInfo->uAcFwReleasedPckts = 0;
        pAcInfo->uNumBlksCausedBusy = 0;
    }

    /* Voice AC specific params */
    pTxHwQueue->tAcVoiceInfo.uAllocatedBlksCntr = 0;
    pTxHwQueue->tAcVoiceInfo.uReleasedBlksCntr  = 0;

    /* Info per link */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkInfo = &pTxHwQueue->aTxHwLinkInfo[uHlid];

        pLinkInfo->uLinkFwReleasedPckts = 0;
        pLinkInfo->uLinkHostSentPckts = 0;
        pLinkInfo->uMaxPackets = LINK_PACKETS_LIMIT_ACTIVE;
        pLinkInfo->uPriorityThreshold = FAST_LINK_PRIORITY_PKTS_THRESH;
    }

    return OK;
}


/****************************************************************************
 *                  txHwQueue_AllocResources()
 ****************************************************************************
 * DESCRIPTION: 
   ============
    1.  Estimate required HW-blocks number.
    2.1  If the required blocks are not available for the link or no free descriptor, 
            return  link STOP_CURRENT  (to stop current link and requeue the packet).
    2.2  If the required blocks are not available for the queue or no free descriptor, 
            return  queue STOP_CURRENT  (to stop current queue and requeue the packet).
    3.  Resources are available so update allocated blocks and descriptors counters.
    4.1  If no link resources for another similar packet, set STOP_NEXT (to stop current link).
    4.2  If no queue resources for another similar packet, set STOP_NEXT (to stop current queue).
        Else, return SUCCESS
 ****************************************************************************/
ETxHwQueStatus txHwQueue_AllocResources(TTxCtrlBlk *pTxCtrlBlk, uint8_t *pBackpressureMap)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    uint32_t uNumBlksToAlloc; /* The number of blocks required for the current packet. */
    uint32_t uAvailableBlks;  /* Max blocks that are currently available for this queue. */
    uint32_t uAcId = WMEQosTagToACTable[pTxCtrlBlk->tTxDescriptor.tid];
    TTxHwAcInfo *pAcInfo = &(pTxHwQueue->aTxHwAcInfo[uAcId]);
    uint32_t uHlid = pTxCtrlBlk->tTxDescriptor.hlid;
    TTxHwLinkInfo *pLinkInfo = &(pTxHwQueue->aTxHwLinkInfo[uHlid]);
    uint32_t uLinkNumUsedPckts;  /* Number of packets in use for this link. */

    *pBackpressureMap = 0;

    /***********************************************************************/
    /*  Check Link resources and priority                                  */
    /***********************************************************************/

    uLinkNumUsedPckts = SUBTRACT_UINT8_COUNTERS(pLinkInfo->uLinkHostSentPckts, pLinkInfo->uLinkFwReleasedPckts);

    /* Check if we can send the current packet and the next one on this link */
    if ((uLinkNumUsedPckts + 1) >= pLinkInfo->uMaxPackets)
    {
        /* Indicate to stop the link */
        *pBackpressureMap |=  TX_HW_CURRENT_LINK_STOP;
        SET_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkBusyBitmap, uHlid);

        /*  If can't send even the current packet, return BUSY  (requeue packet). */
        if (uLinkNumUsedPckts >= pLinkInfo->uMaxPackets)
        {
            //Report(REPORT_SEVERITY_INFORMATION, "txHwQueue_AllocResources: No link resources, Link = %d, UsedPkts = %d, MaxPkts=%d\r\n", uHlid, uLinkNumUsedPckts, pLinkInfo->uMaxPackets);
            return TX_HW_QUE_STATUS_XMIT_BUSY;
        }
    }

    /* If below threshold (including current packet) then we have high priority for this link */
    if ((uLinkNumUsedPckts + 1) < pLinkInfo->uPriorityThreshold)
    {
        *pBackpressureMap |=  TX_HW_CURRENT_LINK_HIGH;
    }

    /***********************************************************************/
    /*  Check AC resources and priority                                    */
    /***********************************************************************/

    /*  RequiredBlocks = (PacketLength / BlockSize) + ExtraBlocks  */
    uNumBlksToAlloc = (pTxCtrlBlk->tTxDescriptor.length + MEMORY_BLOCK_DATA_SIZE - 1) / MEMORY_BLOCK_DATA_SIZE;
    uNumBlksToAlloc += pTxHwQueue->uTxExtraMemBlocks;

    /* Find number of available blocks for this packet (0 available may indicate no descriptors). */
    uAvailableBlks  = calcAcAvailableBlks(pTxHwQueue, uAcId);

    /* If not enough blocks for current packet plus another similar one, indicate to stop current AC */
    if ((uNumBlksToAlloc << 1) > uAvailableBlks)
    {
        pAcInfo->uNumBlksCausedBusy = uNumBlksToAlloc;
        SET_BIT_BY_IDX(pTxHwQueue->tBackpressure.uAcBusyBitmap, uAcId);
        *pBackpressureMap |= TX_HW_CURRENT_AC_STOP;

        /* If we need more blocks than available for the current packet, return BUSY (requeue packet). */
        if (uNumBlksToAlloc > uAvailableBlks)
        {
            //Report(REPORT_SEVERITY_INFORMATION, "txHwQueue_AllocResources: No resources for current pkt, AC=%d, ReqBlks=%d, FreeBlks=%d, AvailBlks=%d, UsedPkts=%d\r\n", uAcId, uNumBlksToAlloc, pTxHwQueue->uNumTotalBlksFree, uAvailableBlks, (pTxHwQueue->uDrvTxPacketsCntr - pTxHwQueue->uFwTxResultsCntr));
            return TX_HW_QUE_STATUS_XMIT_BUSY;
        }
    }

    /***********************************************************************/
    /*                    Update packets and blocks counters               */
    /***********************************************************************/

    /* Update blocks numbers in Tx descriptor */

    pTxCtrlBlk->tTxDescriptor.totalMemBlks = uNumBlksToAlloc;

    pTxHwQueue->uDrvTxPacketsCntr++;
    pLinkInfo->uLinkHostSentPckts++;
    pAcInfo->uAcHostSentPckts++;

    pTxHwQueue->uNumTotalBlksFree -= uNumBlksToAlloc;
    pTxHwQueue->uNumTotalBlksUsed += uNumBlksToAlloc;
    pTxHwQueue->uNumTotalBlksSent += uNumBlksToAlloc;
    if (uAcId == QOS_AC_VO) 
    {
        pTxHwQueue->tAcVoiceInfo.uAllocatedBlksCntr += uNumBlksToAlloc;
    }

    //Report(REPORT_SEVERITY_INFORMATION, "txHwQueue_AllocResources: SUCCESS, Length=%d, Link=%d, AC=%d, Req-blks=%d , Free=%d, ReservedVo=%d, Accumulated=%d, Bkprs=0x%x\r\n", pTxCtrlBlk->tTxDescriptor.length, uHlid, uAcId, uNumBlksToAlloc, pTxHwQueue->uNumTotalBlksFree, pTxHwQueue->tAcVoiceInfo.uNumBlksThresh, pTxHwQueue->tAcVoiceInfo.uAllocatedBlksCntr, *pBackpressureMap);

    return TX_HW_QUE_STATUS_SUCCESS;
}
#endif
extern txCtrl_t *gTxCtrlCB;
/****************************************************************************
 *                  txHwQueue_UpdateFreeResources()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
   Called by FwEvent upon Data interrupt to update freed HW-Queue resources as follows:
    1) For all queues, update blocks and descriptors numbers according to FwStatus information.
    2) For each busy queue, if now available indicate it in the backpressure bitmap.
 ****************************************************************************/
ETxnStatus txHwQueue_UpdateFreeResources(FwStatus_t *pFwStatus, uint32_t uNumPcktsCompleted)
{
    TTxHwQueue      *pTxHwQueue = gTxHwQueueCB;
    Bool_e           uLinkInfoChanged = FALSE;
    Bool_e           uAcInfoChanged = FALSE;


    pTxHwQueue->tBackpressure.TransmitQOnTxComplete = gTxCtrlCB->tBackpressure.TransmitQOnTxComplete;
    /* Update global blocks and packets numbers according to FwStatus information */
    pTxHwQueue->uFwTxResultsCntr += uNumPcktsCompleted;

    /* Update fw core status info */
    updateFwCoreStatusInfo(pTxHwQueue, pFwStatus, &uLinkInfoChanged);

    /* Update the links information */
    updateLinksInfo(pTxHwQueue, pFwStatus, &uLinkInfoChanged);

    /* Update the ACs information */
    updateAcsInfo(pTxHwQueue, pFwStatus, &uAcInfoChanged);

    /* If link or AC info changed, send update to the upper layers (if CB available) */
    if (pTxHwQueue->fUpdateBackpressureCb != NULL)
    {
        pTxHwQueue->fUpdateBackpressureCb(&pTxHwQueue->tBackpressure);
    }
#if 0
    /* Notify RunScheduler when some frames where freed*/
    if (uLinkInfoChanged)
    {
        txDataQ_ReqToRunTxScheduler();
    }
#endif
    return TXN_STATUS_COMPLETE;
}

#if  0
/****************************************************************************
 *                  txHwQueue_AddLink()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
  Increment counter of currently active data links
****************************************************************************/
void  txHwQueue_AddLink(uint8_t uHlid, Bool_e bIsUnicast)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    pTxHwQueue->aTxHwLinkInfo[uHlid].bEnabled = TRUE;
    if (bIsUnicast)
    {
        pTxHwQueue->aTxHwLinkInfo[uHlid].bIsUnicast = TRUE;
        pTxHwQueue->uNumUnicastLinks++;
    }
    else 
    {
        pTxHwQueue->aTxHwLinkInfo[uHlid].bIsUnicast = FALSE;
    }
}

/****************************************************************************
 *                  txHwQueue_RemoveLink()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
  Deccrement counter of currently active data links
****************************************************************************/
void  txHwQueue_RemoveLink(uint8_t uHlid)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    if (pTxHwQueue->aTxHwLinkInfo[uHlid].bIsUnicast)
    {
        if (pTxHwQueue->uNumUnicastLinks)
        {
            pTxHwQueue->uNumUnicastLinks--;
        }
        else
        {
            //Report(REPORT_SEVERITY_ERROR, "txHwQueue_RemoveLink: Unicast Hlid %d removed when uNumUnicdastLinks is 0!!\r\n", uHlid);
        }
    }
    pTxHwQueue->aTxHwLinkInfo[uHlid].bEnabled = FALSE;
    CLEAR_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkBusyBitmap, uHlid);
}


/** 
 * \fn     txHwQueue_SetExtraMemBlocksNum
 * \brief  Update the extra mem-blocks number (upon links security types change).
 */ 
void txHwQueue_SetExtraMemBlocksNum(uint32_t uTxExtraMemBlocks)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    pTxHwQueue->uTxExtraMemBlocks = uTxExtraMemBlocks;
}

/**
 * \fn     txHwQueue_SetExtraMemBlocksNum
 * \brief  Update the extra mem-blocks number (upon links security types change).
 */
uint32_t txHwQueue_GetExtraMemBlocksNum()
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    return pTxHwQueue->uTxExtraMemBlocks;
}


/****************************************************************************
 *                      txHwQueue_SetIgnoreNewThreshold()
 ****************************************************************************
 * DESCRIPTION:  Set the Ignore New Threshold flag for the flow control mechanism
 ****************************************************************************/
void txHwQueue_SetIgnoreNewThreshold(Bool_e bIgnore)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

    pTxHwQueue->bIgnoreNewThreshold = bIgnore;
}


/****************************************************************************
 *                      txHwQueue_RegisterCb()
 ****************************************************************************
 * DESCRIPTION:  Register the upper driver TxHwQueue callback functions.
 ****************************************************************************/
void txHwQueue_RegisterCb (void *fCbFunc, void *hCbHndl)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;

	pTxHwQueue->fUpdateBackpressureCb = (TUpdateBackpressureCb)fCbFunc;
	pTxHwQueue->hUpdateBusyMapHndl = hCbHndl;
}

#endif

/****************************************************************************
 *                      txHwQueue_PrintInfo()
 ****************************************************************************
 * DESCRIPTION: Print the Hw Queue module current information
 ****************************************************************************/
#ifdef TI_DBG
void txHwQueue_PrintInfo (void)
{
    TTxHwQueue *pTxHwQueue = gTxHwQueueCB;
    int32_t  TxQid;
    uint32_t uHlid;

    /* Print the Tx-HW-Queue information: */
   //GTRACE(1, "Hw-Queues Information:\r\n"));
   //Report(("======================\r\n"));
   //GTRACE(1, "Total Blocks:           %d\r\n", pTxHwQueue->uNumTotalBlks));
   //GTRACE(1, "Total Free Blocks:      %d\r\n", pTxHwQueue->uNumTotalBlksFree));
   //GTRACE(1, "Total Used Blocks:      %d\r\n", pTxHwQueue->uNumTotalBlksUsed));
   //GTRACE(1, "Total Sent Blocks:      %d\r\n", pTxHwQueue->uNumTotalBlksSent));
   //GTRACE(1, "Total Released Blocks:  %d\r\n", pTxHwQueue->uNumTotalBlksReleased));
   //GTRACE(1, "Total Used Descriptors: %d\r\n", (pTxHwQueue->uDrvTxPacketsCntr - pTxHwQueue->uFwTxResultsCntr)));
   //GTRACE(1, "FwTxResultsCntr:        %d\r\n", pTxHwQueue->uFwTxResultsCntr));
   //GTRACE(1, "DrvTxPacketsCntr:       %d\r\n", pTxHwQueue->uDrvTxPacketsCntr));
   //GTRACE(1, "uLinkPsFwBitmap:        0x%x\r\n", pTxHwQueue->uLinkPsFwBitmap));
   //GTRACE(1, "uLinkPrioFwBitmap:      0x%x\r\n", pTxHwQueue->uLinkPrioFwBitmap));
   //GTRACE(1, "uLinkSuspendedFwBitmap:   0x%x\r\n", pTxHwQueue->uLinkSuspendedFwBitmap));
   //GTRACE(1, "uAcBusyBitmap:          0x%x\r\n", pTxHwQueue->tBackpressure.uAcBusyBitmap));
   //GTRACE(1, "uLinkBusyBitmap:        0x%x\r\n", pTxHwQueue->tBackpressure.uLinkBusyBitmap));
   //GTRACE(1, "uLinkPriorityBitmap:    0x%x\r\n", pTxHwQueue->tBackpressure.uLinkPriorityBitmap));

   //GTRACE(1, "Queue=AC_VOICE: HostAllocCount=%d, FwFreeCount=%d, ReservedBlksThresh=%d\r\n", 
                    pTxHwQueue->tAcVoiceInfo.uAllocatedBlksCntr,
                    pTxHwQueue->tAcVoiceInfo.uReleasedBlksCntr,
                    pTxHwQueue->tAcVoiceInfo.uNumBlksThresh));
   //Report(("\r\n"));

    for(TxQid = 0; TxQid < MAX_NUM_OF_AC; TxQid++)
    {
       //GTRACE(1, "Q=%d: AcHostSentPkts=%3d, FwReleased=%3d, NumBlksCausedBusy=%3d\r\n", 
                        TxQid,
                        pTxHwQueue->aTxHwAcInfo[TxQid].uAcHostSentPckts,
                        pTxHwQueue->aTxHwAcInfo[TxQid].uAcFwReleasedPckts,
                        pTxHwQueue->aTxHwAcInfo[TxQid].uNumBlksCausedBusy));
    }
   //Report(("\r\n"));

   //GTRACE(1, "Number of Active Links = %d\r\n", pTxHwQueue->uNumUnicastLinks));
    for(uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
       //GTRACE(1, "Link=%d: Enabled=%d, HostSentPkts=%3d, FwReleasedPckts=%3d, MaxPkts=%d, PriorThresh=%d\r\n", 
                        uHlid,
                        pTxHwQueue->aTxHwLinkInfo[uHlid].bEnabled,
                        pTxHwQueue->aTxHwLinkInfo[uHlid].uLinkHostSentPckts,
                        pTxHwQueue->aTxHwLinkInfo[uHlid].uLinkFwReleasedPckts,
                        pTxHwQueue->aTxHwLinkInfo[uHlid].uMaxPackets,
                        pTxHwQueue->aTxHwLinkInfo[uHlid].uPriorityThreshold));
    }
}

#endif /* TI_DBG */


/****************************************************************************
 *                  updateFwCoreStatusInfo()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
    Update the core status info according to the FW status.
    pFwStatus        - The FW status structure (read from FW upon data interrupt)
 ****************************************************************************/
static void updateFwCoreStatusInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus,Bool_e *pLinkInfoChanged)
{
    if(pTxHwQueue->uLinkPsFwBitmap         != pFwStatus->fwInfo.linkPsBitmap)
    {
        pTxHwQueue->uLinkPsFwBitmap         = pFwStatus->fwInfo.linkPsBitmap;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uLinkPrioFwBitmap       != pFwStatus->fwInfo.linkFastBitmap)
    {
        pTxHwQueue->uLinkPrioFwBitmap       = pFwStatus->fwInfo.linkFastBitmap;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uLinkSuspendedFwBitmap  != pFwStatus->fwInfo.linkSuspendedBitmap)
    {
        pTxHwQueue->uLinkSuspendedFwBitmap  = pFwStatus->fwInfo.linkSuspendedBitmap;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uTxFCStopFastThreshold   != pFwStatus->fwInfo.TxFlowControlStopFastThreshold)
    {
        pTxHwQueue->uTxFCStopFastThreshold   = pFwStatus->fwInfo.TxFlowControlStopFastThreshold;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uTxFCStopSlowThreshold   != pFwStatus->fwInfo.TxFlowControlStopSlowThreshold)
    {
        pTxHwQueue->uTxFCStopSlowThreshold   = pFwStatus->fwInfo.TxFlowControlStopSlowThreshold;
        *pLinkInfoChanged = TRUE;
    }
    if( pTxHwQueue->uTxFCFastThreshold      != pFwStatus->fwInfo.TxFlowControlFastThreshold)
    {
        pTxHwQueue->uTxFCFastThreshold       = pFwStatus->fwInfo.TxFlowControlFastThreshold;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uTxFCSlowThreshold       != pFwStatus->fwInfo.TxFlowControlSlowThreshold)
    {
        pTxHwQueue->uTxFCSlowThreshold       = pFwStatus->fwInfo.TxFlowControlSlowThreshold;
        *pLinkInfoChanged = TRUE;
    }
    if(pTxHwQueue->uTxFCSuspendThreshold    != pFwStatus->fwInfo.TxFlowControlSuspendThreshold)
    {
        pTxHwQueue->uTxFCSuspendThreshold   = pFwStatus->fwInfo.TxFlowControlSuspendThreshold;
        *pLinkInfoChanged = TRUE;
    }
    pTxHwQueue->uFwLastTsf   = pFwStatus->tsf;
}

/****************************************************************************
 *                  updateLinksInfo()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
    Update the links busy and priority info according to the FW status.
    pFwStatus        - The FW status structure (read from FW upon data interrupt)
    pLinkInfoChanged - TRUE if there was any change in the links info.
 ****************************************************************************/
static void updateLinksInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus, Bool_e *pLinkInfoChanged)
{
#if 0 //TODO OSPREY_MX-20 
    uint8_t        uNewFwReleased;
    uint8_t        uNewMaxPackets;
    uint8_t        uNewPriorityThreshold;
    uint32_t       uLinkNumUsedPckts;
    uint32_t       uHlid;    

    /* Save the links update from FW */
    pTxHwQueue->uLinkPsFwBitmap         = pFwStatus->fwInfo.linkPsBitmap;//ENDIAN_HANDLE_LONG(pFwStatus->linkPsBitmap);
    pTxHwQueue->uLinkPrioFwBitmap       = pFwStatus->fwInfo.linkFastBitmap;//ENDIAN_HANDLE_LONG(pFwStatus->linkFastBitmap);
    pTxHwQueue->uLinkSuspendedFwBitmap  = pFwStatus->fwInfo.linkSuspendedBitmap;//ENDIAN_HANDLE_LONG(pFwStatus->linkSuspendedBitmap);   
    /* Update Busy state and priority for all enabled links */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
        pLinkInfo = &(pTxHwQueue->aTxHwLinkInfo[uHlid]);

        if (!pLinkInfo->bEnabled)
        {
            continue;
        }

        uNewFwReleased = pFwStatus->fwInfo.linkTxCompletePkts[uHlid];

        /* Update Busy Threshold */
        /* Exception: ignore the new threshold if there is only one connected STA */
        if ((IS_BIT_SET(pTxHwQueue->uLinkPsFwBitmap, uHlid)) && (!pTxHwQueue->bIgnoreNewThreshold) 
            && (pTxHwQueue->aTxHwLinkInfo[uHlid].bIsUnicast))
        {
            uNewMaxPackets = pFwStatus->fwInfo.TxFlowControlHostTxPsThreshold;
        }
        else if(IS_BIT_SET(pTxHwQueue->uLinkSuspendedFwBitmap, uHlid))
        {
            uNewMaxPackets = pFwStatus->fwInfo.TxFlowControlSuspendThreshold;
        }
        else if (!IS_BIT_SET(pTxHwQueue->uLinkPrioFwBitmap, uHlid) && (pTxHwQueue->uNumUnicastLinks > 1))
        {
            uNewMaxPackets = pFwStatus->fwInfo.TxFlowControlStopSlowThreshold;
        }
        else
        {
            uNewMaxPackets = pFwStatus->fwInfo.TxFlowControlStopFastThreshold;
        }

        /* Update Priority Threshold */
        /* Exception: ignore the new threshold if there is only one connected STA */
        if ( ((IS_BIT_SET(pTxHwQueue->uLinkPsFwBitmap, uHlid)) && (!pTxHwQueue->bIgnoreNewThreshold)) || (IS_BIT_SET(pTxHwQueue->uLinkSuspendedFwBitmap, uHlid)) )
        {
            uNewPriorityThreshold = 0;
        }
        else if (IS_BIT_SET(pTxHwQueue->uLinkPrioFwBitmap, uHlid))
        {
            uNewPriorityThreshold = pFwStatus->fwInfo.TxFlowControlFastThreshold;
        }
        else
        {
            uNewPriorityThreshold = pFwStatus->fwInfo.TxFlowControlSlowThreshold;
        }

        /* Check if there is a change in link info */
        if (((pLinkInfo->uLinkFwReleasedPckts != uNewFwReleased) || 
            (pLinkInfo->uMaxPackets != uNewMaxPackets)) ||
            (pLinkInfo->uPriorityThreshold != uNewPriorityThreshold))
        {

            *pLinkInfoChanged = TRUE;
            pLinkInfo->uPriorityThreshold = uNewPriorityThreshold;
            pLinkInfo->uMaxPackets = uNewMaxPackets;
            pLinkInfo->uLinkFwReleasedPckts = uNewFwReleased;

            uLinkNumUsedPckts = SUBTRACT_UINT8_COUNTERS(pLinkInfo->uLinkHostSentPckts, pLinkInfo->uLinkFwReleasedPckts);

            /* If we have resources for the link CLEAR the link's BUSY bit, else set it. */
            if (uLinkNumUsedPckts < pLinkInfo->uMaxPackets)
            {
                CLEAR_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkBusyBitmap, uHlid);
            }
            /* No resources for the link so SET the link's BUSY bit */
            else
            {
                SET_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkBusyBitmap, uHlid);
            }

            /* If above threshold then we have low priority for this link, else, high priority */
            if (uLinkNumUsedPckts > pLinkInfo->uPriorityThreshold)
            {
                CLEAR_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkPriorityBitmap, uHlid); 
            }
            else 
            {
                SET_BIT_BY_IDX(pTxHwQueue->tBackpressure.uLinkPriorityBitmap, uHlid); 
            }

            //Report(REPORT_SEVERITY_INFORMATION, "updateLinkResources: Updated link resources, Link = %d, UsedPkts = %d, MaxPkts=%d\r\n", uHlid, uLinkNumUsedPckts, pLinkInfo->uMaxPackets);
        }
    }
#else 
    /* update per each link the latest thresholds according to bitmaps and FW thresholds, if changed */
    uint32_t       uHlid;
    TTxHwLinkInfo  *pLinkInfo;

    if (*pLinkInfoChanged != TRUE)
    {
        return;
    }
 
    /* Update Busy state and priority for all enabled links */
    for (uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {   
        pLinkInfo = &(pTxHwQueue->aTxHwLinkInfo[uHlid]);

        /* Update High Priority Link Threshold */

        if (IS_BIT_SET(pFwStatus->fwInfo.linkSuspendedBitmap, uHlid))
        {
            pLinkInfo->uHighPriorityThreshold = 0;
        }
        else if (IS_BIT_SET(pFwStatus->fwInfo.linkFastBitmap, uHlid) && 
                !IS_BIT_SET(pFwStatus->fwInfo.linkPsBitmap, uHlid))
        {
            pLinkInfo->uHighPriorityThreshold = pFwStatus->fwInfo.TxFlowControlFastThreshold;
        }
        else
        {
            pLinkInfo->uHighPriorityThreshold = pFwStatus->fwInfo.TxFlowControlSlowThreshold;
        }

        /* Update Low Priority Link Threshold */
        if (IS_BIT_SET(pFwStatus->fwInfo.linkSuspendedBitmap, uHlid))
        {
            pLinkInfo->uLowPriorityThreshold = pFwStatus->fwInfo.TxFlowControlSuspendThreshold;
        }
        else if (IS_BIT_SET(pFwStatus->fwInfo.linkFastBitmap, uHlid) && 
                !IS_BIT_SET(pFwStatus->fwInfo.linkPsBitmap, uHlid))
        {
            pLinkInfo->uLowPriorityThreshold = pFwStatus->fwInfo.TxFlowControlStopFastThreshold;
        }
        else
        {
            pLinkInfo->uLowPriorityThreshold = pFwStatus->fwInfo.TxFlowControlStopSlowThreshold;
        }
    }
#endif
}


/****************************************************************************
 *                  updateAcsInfo()
 ****************************************************************************
 * DESCRIPTION: 
   ===========
    Update the ACs busy and priority info according to the FW status.
    pFwStatus      - The FW status structure (read from FW upon data interrupt)
    pAcInfoChanged - TRUE if there was any change in the ACs info.
 ****************************************************************************/
static void updateAcsInfo(TTxHwQueue *pTxHwQueue, FwStatus_t *pFwStatus, Bool_e *pAcInfoChanged)
{
#ifdef REMOVE_TX_CODE //TODO TX_CODE_WAS_REMOVED
    TTxHwAcInfo  *pAcInfo;
    uint32_t    uAcId;
    uint32_t    uAvailableBlks;
    
    /* Update all total blocks numbers (for all ACs together) */
    pTxHwQueue->uNumTotalBlks = pFwStatus->totalTxMemory;//ENDIAN_HANDLE_LONG(pFwStatus->totalTxMemory);
    pTxHwQueue->tAcVoiceInfo.uReleasedBlksCntr = pFwStatus->txVoiceReleasedBlks;//ENDIAN_HANDLE_LONG(pFwStatus->txVoiceReleasedBlks);
    pTxHwQueue->uNumTotalBlksReleased = pFwStatus->txReleasedBlks;//ENDIAN_HANDLE_LONG(pFwStatus->txReleasedBlks);
    pTxHwQueue->uNumTotalBlksUsed = pTxHwQueue->uNumTotalBlksSent - pTxHwQueue->uNumTotalBlksReleased;

    /* Calculate free blocks number (free = total - used). 
     * If total is temporarily lower than used (due to dynamic allocation process), then free=0 
     */
    if (pTxHwQueue->uNumTotalBlks > pTxHwQueue->uNumTotalBlksUsed) 
    {
        pTxHwQueue->uNumTotalBlksFree = pTxHwQueue->uNumTotalBlks - pTxHwQueue->uNumTotalBlksUsed;
    }
    else 
    {
        pTxHwQueue->uNumTotalBlksFree = 0;
    }

    /* For each AC, update backpressure and priority bitmaps */
    for (uAcId = 0; uAcId < MAX_NUM_OF_AC; uAcId++)
    {
        pAcInfo = &(pTxHwQueue->aTxHwAcInfo[uAcId]);
        pAcInfo->uAcFwReleasedPckts = pFwStatus->AcTxCompletePkts[uAcId];//ENDIAN_HANDLE_LONG(pFwStatus->AcTxCompletePkts[uAcId]);

        pTxHwQueue->tBackpressure.aAcQueueLen[uAcId] = SUBTRACT_UINT8_COUNTERS(pAcInfo->uAcHostSentPckts, pAcInfo->uAcFwReleasedPckts);

        /* If the AC was stopped, if it can be restarted set its bit in the backpressure bitmap */
        if (IS_BIT_SET(pTxHwQueue->tBackpressure.uAcBusyBitmap, uAcId))
        {
            /* Find max available blocks for this AC (0 could indicate no descriptors). */
            uAvailableBlks = calcAcAvailableBlks(pTxHwQueue, uAcId);

            /* If the resources are available, clear the AC's BUSY bit and indicate status change. */
            if (pAcInfo->uNumBlksCausedBusy <= uAvailableBlks)
            {
                //Report(REPORT_SEVERITY_INFORMATION, "updateAcInfo: AC Available, AC=%d, ReqBlks=%d, FreeBlks=%d, AvailBlks=%d, UsedPkts=%d\r\n", uAcId, pAcInfo->uNumBlksCausedBusy, pTxHwQueue->uNumTotalBlksFree, uAvailableBlks, (pTxHwQueue->uDrvTxPacketsCntr - pTxHwQueue->uFwTxResultsCntr));
                CLEAR_BIT_BY_IDX(pTxHwQueue->tBackpressure.uAcBusyBitmap, uAcId);
                *pAcInfoChanged = TRUE;
            }
        }
    }
#endif
}
