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
/** \file   BusDrv.h 
 *  \brief  Bus-Driver module API definition                                  
 *
 *  \see    SdioBusDrv.c, WspiBusDrv.c
 */

#ifndef __BUS_DRV_API_H__
#define __BUS_DRV_API_H__

#include "osi_type.h"
#include "txn_defs.h"
#include "w_queue.h"

#define MAX_BUS_TXN_SIZE            0x1000  /* Max bus transaction size in bytes (for the DMA buffer allocation) */
/************************************************************************
 * Defines
 ************************************************************************/

#define TRANPORT_BUS_PAD_LEN_READ           8
#define MAX_XFER_BUFS               (10*3)//need to be TWD_TX_AGGREG_PKTS_LIMIT_DEF X number of section per frame(3)

#define TXN_PARAM_STATUS_OK         0
#define TXN_PARAM_STATUS_ERROR      1
#define TXN_PARAM_STATUS_RECOVERY   2

#define TXN_DIRECTION_WRITE         0
#define TXN_DIRECTION_READ          1

#define TXN_HIGH_PRIORITY           0
#define TXN_LOW_PRIORITY            1
#define TXN_NUM_PRIORITYS           2

#define TXN_INC_ADDR                0
#define TXN_FIXED_ADDR              1

#define TXN_AGGREGATE_OFF           0
#define TXN_AGGREGATE_ON            1

#define TXN_NON_SLEEP_ELP           1
#define TXN_SLEEP_ELP               0

#define NUM_OF_PARTITION            4

/************************************************************************
 * Macros
 ************************************************************************/
/* Get field from TTxnStruct->uTxnParams */
#define TXN_PARAM_GET_PRIORITY(pTxn)            ( (pTxn->uTxnParams & 0x00000003) >> 0 )
#define TXN_PARAM_GET_FUNC_ID(pTxn)             ( (pTxn->uTxnParams & 0x0000000C) >> 2 )
#define TXN_PARAM_GET_DIRECTION(pTxn)           ( (pTxn->uTxnParams & 0x00000010) >> 4 )
#define TXN_PARAM_GET_FIXED_ADDR(pTxn)          ( (pTxn->uTxnParams & 0x00000020) >> 5 )
#define TXN_PARAM_GET_MORE(pTxn)                ( (pTxn->uTxnParams & 0x00000040) >> 6 )
#define TXN_PARAM_GET_SINGLE_STEP(pTxn)         ( (pTxn->uTxnParams & 0x00000080) >> 7 )
#define TXN_PARAM_GET_STATUS(pTxn)              ( (pTxn->uTxnParams & 0x00000F00) >> 8 )
#define TXN_PARAM_GET_AGGREGATE(pTxn)           ( (pTxn->uTxnParams & 0x00001000) >> 12 )
#define TXN_PARAM_GET_END_OF_BURST(pTxn)        ( (pTxn->uTxnParams & 0x00002000) >> 13 )



/* Set field in TTxnStruct->uTxnParams */
#define TXN_PARAM_SET_PRIORITY(pTxn, uValue)    ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000003) | (uValue << 0 ) )
#define TXN_PARAM_SET_FUNC_ID(pTxn, uValue)     ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x0000000C) | (uValue << 2 ) )
#define TXN_PARAM_SET_DIRECTION(pTxn, uValue)   ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000010) | (uValue << 4 ) )
#define TXN_PARAM_SET_FIXED_ADDR(pTxn, uValue)  ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000020) | (uValue << 5 ) )
#define TXN_PARAM_SET_MORE(pTxn, uValue)        ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000040) | (uValue << 6 ) )
#define TXN_PARAM_SET_SINGLE_STEP(pTxn, uValue) ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000080) | (uValue << 7 ) )
#define TXN_PARAM_SET_STATUS(pTxn, uValue)      ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00000F00) | (uValue << 8 ) )
#define TXN_PARAM_SET_AGGREGATE(pTxn, uValue)   ( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00001000) | (uValue << 12 ) )
#define TXN_PARAM_SET_END_OF_BURST(pTxn, uValue)( pTxn->uTxnParams = (pTxn->uTxnParams & ~0x00002000) | (uValue << 13 ) )


#define TXN_PARAM_SET(pTxn, uPriority, uId, uDirection, uAddrMode) \
        TXN_PARAM_SET_PRIORITY(pTxn, uPriority); \
        TXN_PARAM_SET_FUNC_ID(pTxn, uId); \
        TXN_PARAM_SET_DIRECTION(pTxn, uDirection); \
        TXN_PARAM_SET_FIXED_ADDR(pTxn, uAddrMode);

#define BUILD_TTxnStruct(pTxn, uAddr, pBuf, uLen, fCB, hCB) \
    pTxn->aBuf[0] = (uint8_t*)(pBuf); \
    pTxn->aLen[0] = (uint16_t)(uLen); \
    pTxn->aLen[1] = 0;                 \
    pTxn->uHwAddr = uAddr;             \
    pTxn->hCbHandle = (void*)hCB;      \
    pTxn->fTxnDoneCb = (TTxnDoneCb)fCB;\
    pTxn->uPaddingSize = 0;


/************************************************************************
 * Types
 ************************************************************************/
/* The TxnDone CB of the specific Txn originator (Xfer layer) called upon Async Txn completion */
typedef void (*TTxnDoneCb)(void * hCbHandle, void *pTxn);

/* The transactions structure */
typedef struct
{
    TQueNodeHdr tTxnQNode;                /* Header for queueing */
    uint32_t    uTxnParams;               /* Txn attributes (bit fields) - see macros above */
    uint32_t    uHwAddr;                  /* Physical (32 bits) HW Address */
    TTxnDoneCb  fTxnDoneCb;               /* CB called by TwIf upon Async Txn completion (may be NULL) */
    void *      hCbHandle;                /* The handle to use when calling fTxnDoneCb */
    uint16_t    aLen[MAX_XFER_BUFS];      /* Lengths of the following aBuf data buffers respectively.
                                             Zero length marks last used buffer, or MAX_XFER_BUFS of all are used. */
    uint8_t*    aBuf[MAX_XFER_BUFS];      /* Host data buffers to be written to or read from the device */
    uint8_t     aTransportBusPad[TRANPORT_BUS_PAD_LEN_READ]; /* Padding used by WSPI bus driver for its header or fixed-busy bytes */
    uint16_t    uPaddingSize;
    uint16_t    aligned;
} TTxnStruct;

/* Parameters for all bus types configuration in ConnectBus process */

typedef struct
{
    uint32_t    uBlkSizeShift;
    uint32_t    uBusDrvThreadPriority;
} TSdioCfg; 

typedef struct
{
    uint32_t    uDummy;
} TWspiCfg; 

typedef struct
{
    uint32_t    uBaudRate;
} TUartCfg; 

typedef union
{
    TSdioCfg    tSdioCfg;       
    TWspiCfg    tWspiCfg;       
    TUartCfg    tUartCfg;       

} TBusDrvCfg;


typedef struct
{
    uint32_t   uMemAdrr;
    uint32_t   uMemSize;
} TPartition;


/************************************************************************
 * Functions
 ************************************************************************/
int busDrv_Destroy ();

/****************************************************************************
 *                      busDrv_Init
 ****************************************************************************
 * DESCRIPTION: config the module.
 *
 * INPUTS:  hBusDrv - handle to the module context
 *          hReport - handle to report module context that is used when we output debug messages
 *          CBFunc  - The callback to call upon transaction complete (calls the tasklet).
 *          CBArg   - The handle for the CBFunc.
 *
 * OUTPUT:  none.
 *
 * RETURNS: one of the error codes (0 => 0)
 ****************************************************************************/
void busDrv_Init ();


/**
 * \fn     busDrv_Transact
 * \brief  Process transaction
 *
 * Called by the TwIf module to initiate a new transaction.
 * Prepare the transaction parts (SDIO driver layer transactions),
 *      and send them one by one to the lower layer.
 *
 * \note   It's assumed that this function is called only when idle (i.e. previous Txn is done).
 * \param  hBusDrv - The module's object
 * \param  pTxn    - The transaction object
 * \return COMPLETE or ERROR
 * \sa     busDrv_PrepareTxnParts, busDrv_SendTxnParts
 */
ETxnStatus busDrv_Transact(TTxnStruct *pTxn);








#endif /*__BUS_DRV_API_H__*/

