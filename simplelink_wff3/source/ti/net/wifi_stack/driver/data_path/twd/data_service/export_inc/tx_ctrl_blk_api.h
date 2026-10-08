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
/*    MODULE:   txCtrlBlk_api.h                                            */
/*    PURPOSE:  Tx control block module API.                               */
/*                                                                         */
/***************************************************************************/
#ifndef _TX_CTRL_BLK_API_H_
#define _TX_CTRL_BLK_API_H_


#include "tw_driver.h"
#include "tx_ctrl.h"

/* Public Function Definitions */
uint32_t       txCtrlBlk_Destroy   (void);
uint32_t       txCtrlBlk_Init      (void);
TTxCtrlBlk     *txCtrlBlk_Alloc    (uint8_t isMgmt);
void           txCtrlBlk_Free      (TTxCtrlBlk *pCurrentEntry);
TTxCtrlBlk    *txCtrlBlk_GetPointer(uint32_t uIndex);
void           txCtrlBlk_Set       (txCtrl_t *pTxCtrl);
#ifdef TI_DBG
void           txCtrlBlk_PrintTable(void);
#endif /* TI_DBG */


#endif  /* _TX_CTRL_BLK_API_H_ */
        

