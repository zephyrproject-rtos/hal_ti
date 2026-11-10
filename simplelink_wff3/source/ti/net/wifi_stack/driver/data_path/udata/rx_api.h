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
/*    MODULE:   rx_api.h                                                   */
/*    PURPOSE:  Rx module API Header file                                  */
/*                                                                         */
/***************************************************************************/
#ifndef _RX_API_H_
#define _RX_API_H_



#include <data_path/udata/export_inc/udata_api.h>
#include "rx_defs.h"

/* rx.c functions */
/*----------------*/
rxData_t     *rxData_create(void);
void          rxData_init(TUdata *pUdata);
uint32_t      rxData_NotifyFwReset(void);
uint32_t      rxData_unLoad(void);

void          rxData_GetCounters(dbg_cntr_trnspt_t* pCounters);
void          rxData_ResetCounters();

void          rxData_GetLinkCounters(uint32_t uHlid, dbg_cntr_trnspt_t* buf);
void          rxData_ResetLinkCounters(uint32_t uHlid);

void          rxData_GetLinkDataCounters(uint32_t link, TLinkDataCounters *pLinksDataCounters);

void          rxData_SetExcludeUnencrypted(uint32_t uHlid, Bool_e bDropBcast, Bool_e bDropUcast);
tiwdrv_rate_e rxData_GetCurrentRate(uint32_t uHlid);
void          rxData_SetLinkState(uint32_t uHlid, ELinkState eRxConnState);
void          rxData_ReceivePacket(void *pBuffer);

PacketClassTag_enum rxData_GetCRxClassification(void *pBuffer);
#ifdef TI_DBG
void          rxData_resetCounters(void);
void          rxData_resetDbgCounters(void);
void          rxData_printRxBlock(void);
void          rxData_printRxCounters(void);
#endif /* TI_DBG */

/* RxQueue.c functions */
/*---------------------*/
uint32_t  RxQueue_Init(void);
uint32_t  RxQueue_DeInit(void);
uint32_t  RxQueue_NotifyFwReset(void);
void      RxQueue_CloseAllBaSessions(void);
void      RxQueue_CloseAllLinkBaSessions(uint8_t uHlid);
void      RxQueue_ReceivePacket (uint8_t * pBuffer, uint32_t len);
void      RxQueue_SetInternalRxBaPolicy(uint32_t uHlid, uint8_t uPolicyBitmap);


#endif /* _RX_API_H_ */

