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
/** \file   TwIf.h 
 *  \brief  TwIf module API definition                                  
 *
 *  \see    TwIf.c
 */

#ifndef __TWIF_API_H__
#define __TWIF_API_H__


#include <txn_bus_drv.h>
#include "txn_defs.h"

//#define DEBUG_TWIF
#ifdef DEBUG_TWIF
#define TWIF_PRINT Report
#define TWIF_PRINT_ERROR Report
#else
#define TWIF_PRINT(...)
#define TWIF_PRINT_ERROR Report
#endif

//#define DEBUG_TRANSPORT_THRD_INIT
#ifdef DEBUG_TRANSPORT_THRD_INIT
#define TRANSPORT_PRINT_THRD_INIT Report
#else
#define TRANSPORT_PRINT_THRD_INIT(...)
#endif


//#define DEBUG_TRANSPORT
#ifdef DEBUG_TRANSPORT
#define TRANSPORT_PRINT Report
#define TRANSPORT_PRINT_ERROR Report
#else
#define TRANSPORT_PRINT(...)
#define TRANSPORT_PRINT_ERROR Report
#endif

//#define DEBUG_TRANSPORT_INIT
#ifdef DEBUG_TRANSPORT_INIT
#define TRANSPORT_PRINT_INIT Report
#else
#define TRANSPORT_PRINT_INIT(...)
#endif

//#define DEBUG_TRANSPORT_IRQ
#ifdef DEBUG_TRANSPORT_IRQ
#define TRANSPORT_PRINT_IRQ Report
#else
#define TRANSPORT_PRINT_IRQ(...)
#endif


/************************************************************************
 * Defines
 ************************************************************************/


/************************************************************************
 * Macros
 ************************************************************************/
/* 
 * Defines a TNETWIF read/write field with padding.
 * A low level driver may use this padding internally
 */
#define PADDING(field) \
    uint8_t padding [TNETWIF_READ_OFFSET_BYTES];  \
    field;

#define ENDIAN_HANDLE_LONG(x)       (x)
/************************************************************************
 * Types
 ************************************************************************/

typedef void (*TTwIfCallback)(void * hCb);
typedef void (*TRecoveryCb)(void * hCb);





/************************************************************************
 * Functions
 ************************************************************************/
int twIf_Destroy();
void twIf_Restart();
int twIf_Init();
void twIf_SetPartition(const TPartition *pPartition);
void twIf_Awake();
void twIf_Sleep();
void twIf_HwAvailable();
ETxnStatus twIf_Transact(TTxnStruct *pTxn);
ETxnStatus twIf_TransactReadFwStatus(TTxnStruct *pTxn);
uint32_t twIf_IsValidMemoryAddr(uint32_t Address, uint32_t Length);
uint32_t twIf_IsValidRegAddr(uint32_t Address);
uint32_t twIf_IsChipAwake();




#endif /*__TWIF_API_H__*/
