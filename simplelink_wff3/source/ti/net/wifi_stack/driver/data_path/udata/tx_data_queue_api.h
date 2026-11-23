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
/*                                                                         */
/*      PURPOSE:    Tx Data Queue module api functions header file         */
/*                                                                         */
/***************************************************************************/

#ifndef _TX_DATA_QUEUE_API_H_
#define _TX_DATA_QUEUE_API_H_

#include "tw_driver.h"
#include "tx_data_queue.h"
#include "tx_mgmt_queue_api.h"
#include "paramOut.h"
#include "cc3xxx_public_types.h"

/*
 * Tx-Data-Queue functions:
 */
TTxDataQ* txDataQ_Create        (void);
void      txDataQ_Init          (TUdata *pUdata);
uint32_t  txDataQ_Set           (TUdataInitParams TUdataParams);
uint32_t  txDataQ_Destroy       (void);
void      txDataQ_ClearQueues   (void);
uint32_t  txDataQ_InsertPacket  (TTxCtrlBlk *pPktCtrlBlk, uint8_t uPacketDtag);
void      txDataQ_UpdateBusyMap (TTxHwBackpressure  *pBackpressure);
void      txDataQ_StopAll       (void);
void      txDataQ_WakeAll       (void);
void      txDataQ_ReqToRunTxScheduler (void);
void      txDataQ_DisableLink   (uint32_t uHlid);
void      txDataQ_removeHlidFromScheduler ();
void      txDataQ_EnableLink    (uint32_t uHlid);

/*
 * Tx data queue per link functions:
 */
void        txDataQ_ClearLink               (uint32_t uHlid);
uint32_t    txDataQ_LinkMacAdd              (uint32_t uHlid, const TMacAddr tMacAddr);
void        txDataQ_LinkMacRemove           (uint32_t uHlid);
uint32_t    txDataQ_LinkMacFind             (uint8_t *uHlid, TMacAddr tMacAddr);
uint32_t    txDataQ_GetMacFromLink          (uint8_t uHlid, TMacAddr tMacAddr);

/*
 * Tx data resources functions:
 */
uint32_t  txDataQ_AllocCheckResources (TTxCtrlBlk *pPktCtrlBlk, uint8_t isDataFrame);
void      txDataQ_FreeResources       (TTxCtrlBlk *pPktCtrlBlk);
void      txDataQ_FreeFwAllocated     (TTxCtrlBlk *pPktCtrlBlk);
void      txDataQ_FlushLinkQueues     (uint32_t uHlid);
void      txDataQ_noticeRemoveHlid  ();


#ifdef TI_DBG
void      txDataQ_PrintModuleParams    (void);
void      txDataQ_PrintQueueStatistics (void);
void      txDataQ_ResetQueueStatistics (void);
#endif /* TI_DBG */


/*
 * Tx-Data-Classifier functions:
 */
uint32_t txDataClsfr_Config           (TClsfrInitParams *pClsfrInitParams);
uint32_t txDataClsfr_ClassifyTxPacket (TTxCtrlBlk *pPktCtrlBlk, uint8_t uPacketDtag);
uint32_t txDataClsfr_InsertClsfrEntry (TClsfrTableEntry *pNewEntry);
uint32_t txDataClsfr_RemoveClsfrEntry (TClsfrTableEntry *pRemEntry);
uint32_t txDataClsfr_SetClsfrType     (EClsfrType eNewClsfrType);
uint32_t txDataClsfr_GetClsfrType     (EClsfrType *pClsfrType);

#ifdef TI_DBG
void      txDataClsfr_PrintClsfrTable  (void);
#endif /* TI_DBG */

#define  FRAME_SEND_SUCCESFULY     (1)
#define  NO_FRAMES_IN_QUEUE        (-1)
#define  ERROR_SEND_FRAME_FAILED   (-2)

#endif /* _TX_DATA_QUEUE_API_H_ */

