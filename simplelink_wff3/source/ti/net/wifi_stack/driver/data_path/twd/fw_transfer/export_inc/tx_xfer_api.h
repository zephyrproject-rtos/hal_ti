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
 *   MODULE:  txXfer_api.h
 *
 *   PURPOSE: Tx Xfer module API.
 * 
 ****************************************************************************/

#ifndef _TX_XFER_API_H
#define _TX_XFER_API_H


#include "tw_driver.h"
#include "txn_defs.h"

/* 
 *   Public Function Definitions:
 *   ============================
 */

/**
 * \fn     txXfer_Create
 * \brief  Initialize module variables
 *
 * Initialize module variables including saving other modules handles
 *
 * \note
 * \param
 * \return 0
 * \sa
 */
uint32_t txXfer_Init (void);


/** 
 * \fn     txXfer_Destroy
 * \brief  Destroy module
 * 
 * Destroy module
 * 
 * \note   
 * \param  
 * \return 0
 * \sa     
 */ 
uint32_t txXfer_Destroy (void);

/**
 * \fn     txXfer_SendPacket
 * \brief  Send a Tx packet to the FW
 *
 * Called by the Tx upper layers to send a new Tx packet to the FW (after FW resources were allocated).
 * Call txXfer_SendAggregatedPkts to forward
 *     the aggregation to the FW.
 *
 * \note
 * \param  pPktCtrlBlk - The new packet to send
 * \return COMPLETE if completed in this context, PENDING if not, ERROR if failed
 * \sa
 */
ETxnStatus txXfer_SendPacket (TTxCtrlBlk *pPktCtrlBlk);

/** 
 * \fn     txXferAggr_Init
 * \brief  Initialize module variables
 * 
 * Initialize module variables including saving other modules handles
 * 
 * \note   
 * \param  
 * \return 0
 * \sa     
 */ 
uint32_t txXferAggr_Init (void);

/**
 * \fn     txXferAggr_Destroy
 * \brief  Destroy module
 *
 * Destroy module
 *
 * \note
 * \param
 * \return 0
 * \sa
 */
uint32_t txXferAggr_Destroy (void);

/**
 * \fn     txXfer_SendPacket
 * \brief  Send a Tx packet to the FW with delay to create aggregation
 *
 * Called by the Tx upper layers to send a new Tx packet to the FW (after FW resources were allocated).
 * Aggregate the packet if possible, and if needed call txXfer_SendAggregatedPkts to forward 
 *     the aggregation to the FW.
 * 
 * \note   
 * \param  pPktCtrlBlk - The new packet to send
 * \return COMPLETE if completed in this context, PENDING if not, ERROR if failed
 * \sa     
 */ 
ETxnStatus txXferAggr_SendPacket (TTxCtrlBlk *pPktCtrlBlk);


/** 
 * \fn     txXfer_EndOfBurst
 * \brief  Indicates that current packets burst stopped
 * 
 * Called by the Tx upper layers to indicate that the current packets burst stopped.
 * Sends the current aggregation of packets to the FW.
 * 
 * \note   
 * \param  
 * \return void
 * \sa     
 */ 
void txXferAggr_EndOfBurst (void);


#ifdef TI_DBG
void txXfer_ClearStats (void);
void txXfer_PrintStats (void);
#endif



#endif /* _TX_XFER_API_H */




