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
 *   MODULE:  txHwQueue_api.h
 *
 *   PURPOSE: HW Tx Queue module API.
 * 
 ****************************************************************************/

#ifndef _TX_HW_QUEUE_API_H
#define _TX_HW_QUEUE_API_H


#include "tw_driver.h"
#include "txn_defs.h"
#include "cc3xxx_public_host_if.h"
#include "fw_status.h"
/* Public Function Definitions */

uint32_t    txHwQueue_Destroy(void);
uint32_t    txHwQueue_Init(void);
uint32_t    txHwQueue_Config(void);
uint32_t    txHwQueue_SetInitializeHwBlocks (uint32_t tx_BlocksAvailable, uint32_t tx_NumTxDescriptor);
uint32_t    txHwQueue_UpdateAllocHwBlocks (uint32_t tx_BlocksAvailable, uint32_t uAc);
uint32_t    txHwQueue_UpdateFreeHwBlocks (uint32_t tx_Blocks, TTxCtrlBlk *pPktCtrlBlk);
uint32_t    txHwQueue_GetHwBlocks();
uint32_t    txHwQueue_GetHwBlocksRequireForAvgFrame ();

uint32_t    txHwQueue_GetTxAcPktsCount(uint32_t uAc);
uint32_t    txHwQueue_GetTxTotalPktsCount();
uint32_t    txHwQueue_GetlastFWTsf();
uint32_t    txHwQueue_GetLinkPrioThreshold(uint32_t hlid, uint32_t linkPriorityToServe);
void        txHwQueue_GetTxFlowControlLinkBitmaps(uint32_t *pSuspendBitmap, uint32_t *pFastBitmap, uint32_t *pPsBitmap);
int32_t     txHwQueue_allocate_mem_blocks(uint8_t isMgmt,TTxCtrlBlk *pPktCtrlBlk);
int32_t     txHwQueue_free_allocated_mem_blocks(TTxCtrlBlk *pPktCtrlBlk);
uint32_t    txHwQueue_SetHwInfo(TDmaParams *pDmaParams);
uint32_t    txHwQueue_Restart(void);
ETxHwQueStatus txHwQueue_AllocResources(TTxCtrlBlk *pTxCtrlBlk, uint8_t *pBackpressureMap);
ETxnStatus  txHwQueue_UpdateFreeResources(FwStatus_t *pFwStatus, uint32_t uNumPcktsCompleted);
//void        txHwQueue_RegisterCb(void *fCbFunc, void *hCbHndl);
void        txHwQueue_AddLink(uint8_t uHlid, Bool_e bIsUnicast);
void        txHwQueue_RemoveLink(uint8_t uHlid);
void        txHwQueue_SetExtraMemBlocksNum(uint32_t uTxExtraMemBlocks);
uint32_t    txHwQueue_GetExtraMemBlocksNum();
void        txHwQueue_SetIgnoreNewThreshold(Bool_e bIgnore);
void        txHwQueue_GetTxFlowControlThresholds(uint8_t *pTxSuspendThold, uint8_t *pTxFastThold, 
                                                 uint8_t *pTxSlowThold, uint8_t *pTxStopFastThold, uint8_t *pTxstopSlowThold);

#ifdef TI_DBG
void        txHwQueue_PrintInfo(void);
#endif /* TI_DBG */


#endif /* _TX_HW_QUEUE_API_H */




