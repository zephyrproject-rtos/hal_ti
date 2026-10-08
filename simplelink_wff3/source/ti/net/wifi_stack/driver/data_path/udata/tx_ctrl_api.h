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
/*    MODULE:   txCtrl_Api.h                                               */
/*    PURPOSE:  TxCtrl module API Header file                              */
/*                                                                         */
/***************************************************************************/
#ifndef _TX_CTRL_API_H_
#define _TX_CTRL_API_H_

#include <data_path/udata/export_inc/udata_api.h>
//#include "udata_api.h"
#include "tx_ctrl.h"
#include <data_path/udata/udata.h>
#include "wlan_if.h"

#define TX_HEADER_PAD_SIZE      2       /* 2-byte pad before header with QoS, for 4-byte alignment */

/* TxCtrl Xmit results */
typedef enum
{
    STATUS_XMIT_SUCCESS,
    STATUS_XMIT_BUSY,
    STATUS_XMIT_ERROR
} EStatusXmit;



/****************************************************************/
/*                  MODULE  PUBLIC  FUNCTIONS                   */
/****************************************************************/

/*
 *  The TxCtrl MAIN public functions (in txCtrl.c):
 */
txCtrl_t *  txCtrl_Create (void);
void		txCtrl_Init (TUdata *pUdata);
uint32_t	txCtrl_SetDefaults (void);
uint32_t	txCtrl_Unload (void);
uint32_t 	txCtrl_SelectAcForTid(uint32_t uHlid, uint8_t *pTid);
EStatusXmit	txCtrl_XmitData (TTxCtrlBlk *pPktCtrlBlk, uint8_t *pBackpressureMap);
uint32_t	txCtrl_XmitMgmt (TTxCtrlBlk *pPktCtrlBlk, uint8_t *pBackpressureMap);
void		txCtrl_UpdateQueuesMapping (void);
void*		txCtrl_AllocPacketBuffer (TTxCtrlBlk *pPktCtrlBlk, uint32_t uPacketLen);
void		txCtrl_FreePacket (TTxCtrlBlk *pPktCtrlBlk, uint32_t eStatus);
uint32_t	txCtrl_NotifyFwReset(void);
uint32_t	txCtrl_CheckForTxStuck(void);
void		txCtrl_RegisterSecuritySeqHandler(TSecuritySeqHandler cb, void *ctx);


/* TSM (802.11k measurements) */
uint32_t txCtrl_UpdateTSMParameters(uint32_t uHlid, TTsmParams *pTSMParams);

/*
 *  The txCtrlParams.c sub-module public functions:
 */
void txCtrlParams_SetStackCounters(uint32_t uHlid, uint32_t buflen);
void txCtrlParams_ResetCounters(void);
uint32_t txCtrlParams_SetAdmissionCtrlParams(uint32_t uHlid, uint8_t acId, uint16_t mediumTime, Bool_e admFlag);
void txCtrlParams_GetTxCtrlCounters(TTxDataCounters *pCounters);
void txCtrlParams_SetDataEncryptMode(uint32_t uHlid, Bool_e bEncryptMode);
void txCtrlParams_SetMgmtEncryptMode(uint32_t uHlid, Bool_e bPMFEncrypt);
Bool_e txCtrlParams_GetMgmtEncryptMode(uint32_t uHlid);
void txCtrlParams_SetEapolEncryptionStatus(uint32_t uHlid, Bool_e bEapolEncryptionStatus);
tiwdrv_rate_e txCtrlParams_GetTxRate (uint32_t uHlid);
void txCtrlParams_SetAcAdmissionStatus(uint32_t uHlid,
                                       uint8_t ac,
                                       EAdmissionState admissionRequired,
                                       ETrafficAdmState admissionState);
void txCtrlParams_setAcMsduLifeTime (RoleID_t eLmacRoleId, uint8_t ac, uint32_t uMsduLifeTimeTu);
void txCtrlParams_setAcAckPolicy (uint32_t uHlid, uint8_t ac, AckPolicy_e ackPolicy);
void txCtrlParams_GetTsStatistics(reportTsStatisticsReq_t *pTsStatisticsReq);
void txCtrlParams_resetDbgCounters(void);

void txCtrlParams_GetDataLinkCounter(uint32_t link, TLinkDataCounters *pLinksDataCounters);

void txCtrlParams_GetLinkCounters(uint32_t link, dbg_cntr_trnspt_t *counters);
void txCtrlParams_resetLinkCounters(uint32_t uHlid);

#ifdef TI_DBG
void txCtrlParams_printInfo(void);
void txCtrlParams_printDebugCounters(void);
#endif /* TI_DBG */



#endif /* _TX_CTRL_API_H_ */
