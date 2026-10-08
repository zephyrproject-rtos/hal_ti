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
/** \file   Transport.h
 *  \brief  Transport module header file.
 *
 *  \see    Transport.c
 */

#ifndef _Transport_H_
#define _Transport_H_

#include "osi_kernel.h"

#define TRANSPORT_THRD_STACK_SIZE (4096)

/* The callback function type for Transport clients */
typedef void (*TTransportCbFunc)(void* hCbHndl);

/*****************************************************************************/
/* transport thread DEFINITIONS                                                        */
/*****************************************************************************/
/* Transport module structure */
#define MAX_CLIENTS     9   /* Maximum number of clients using Transport services */
#define MAX_NAME_SIZE   16  /* Maximum client's name string size */

typedef struct
{
    uint32_t            isAlive;
    uint32_t            uNumClients;                      /* Number of registered clients     */
    TTransportCbFunc    aClientCbFunc [MAX_CLIENTS];      /* Clients' callback functions      */
    void *              aClientCbHndl [MAX_CLIENTS];      /* Clients' callback handles        */
    uint32_t            aClientEnabled[MAX_CLIENTS];      /* Clients' enable/disable flags    */
    uint32_t            aClientPending[MAX_CLIENTS];      /* Clients' pending flags           */
    OsiLockObj_t        lockObj;                          /* protection from cross calls      */
    OsiLockObj_t        lockTxQueue;                      /* protection from cross calls      */
    OsiLockObj_t        lockTxCtrlAlloc;                  /* protect allocation of txCtrl block*/
    OsiLockObj_t        lockTTxXfer;                      /* protect txXfer_SendPacket from multi-thread*/
    OsiLockObj_t        lockTxReqSched;                   /* protection from cross calls      */
    OsiSyncObj_t        syncObj;                          /* wait for reschedule event        */
    OsiSyncObj_t        trnsptThrdRunStopSyncObject;      /* sync object for kill the thread  */
} TTransport;

/* External Functions Prototypes */
/* ============================= */
int trnspt_Init(uint32_t TrnsptThrdPrior);
void Transport_WlanInterrupt(unsigned char index);
uint32_t trnspt_RegisterClient (TTransportCbFunc  fCbFunc, uint32_t bEnable);
void trnspt_RequestSchedule(uint32_t uClientId, uint32_t isFromISR);
void trnspt_EnterCriticalSection ();
void trnspt_LeaveCriticalSection ();
void trnspt_lockTxQueue();
void trnspt_unlockTxQueue();
int  trnspt_Destroy(uint32_t uDestroyClientId);
void trnspt_unlockTxXfer();
void trnspt_unlockTxReqSched();
void trnspt_lockTxReqSched();
void trnspt_lockTxXfer();
void trnspt_lockTxCtrlAlloc();
void trnspt_unlockTxCtrlAlloc();
int trnspt_Destroy(uint32_t uDestroyClientId);


#endif  /* _Transport_H_ */


