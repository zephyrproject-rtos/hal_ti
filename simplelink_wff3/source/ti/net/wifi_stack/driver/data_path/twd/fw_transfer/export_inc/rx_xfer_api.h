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
 *   MODULE:  rxXfer_api.h
 *
 *   PURPOSE: Rx Xfer module API.
 * 
 ****************************************************************************/

#ifndef _RX_XFER_API_H
#define _RX_XFER_API_H


#include <bus_If.h>
#include <data_path/TWD/TWDriver/TWDriver.h>

/* Public Function Definitions */

void                rxXfer_Destroy(void);

uint32_t            rxXfer_Init(void);

void                rxXfer_SetDefaults (void);

void                rxXfer_SetBusParams (uint32_t uDmaBufLen);

ETxnStatus          rxXfer_RxEvent (void* FwStatus);

void                rxXfer_Register_CB(uint32_t CallBackID, void *CBFunc, void* CBObj);

//void              rxXfer_SetRxDirectAccessParams (TDmaParams *pDmaParams);
                    
void                rxXfer_RegisterErrCb (void *fErrCb, void* hErrCb);

void                rxXfer_Restart(void);

#ifdef TI_DBG

void rxXfer_ClearStats(void);

void rxXfer_PrintStats(void);

#endif /* TI_DBG */

#endif /* _RX_XFER_API_H */




