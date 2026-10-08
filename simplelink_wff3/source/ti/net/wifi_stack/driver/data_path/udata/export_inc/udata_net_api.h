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
/** \file   udataNet_api.h 
 *  \brief  Declarations of specific functions from the udata.c public functions
 *              that are required only for the MCP network-stack interface and
 *              are not visible to the UWD.
 *
 *  \see    udata.c
 */


#ifndef UDATA_NET_API_H_
#define UDATA_NET_API_H_

#ifdef CC33xx
#include "public_share.h"
#else
#include "wl18xx_public_infoele.h"
#endif
#include "tw_driver.h"
#include "udata_api.h"


/* \brief   Provides the Net-IF related to the specified link ID
 * \param   hUdata  - The udata module handle
 * \param   link    - The link ID to use for this packet
 * \return  The Network interface ID
 */
uint32_t udataNet_GetNetIfByLink(uint32_t link);

/* \brief   Provides the link ID related to a Tx management packet from the network stack
 * \param   hUdata    - The udata module handle
 * \param   uNetIfId  - The Network interface ID from which the packet arrived
 * \param   mac       - The destination MAC address of the packet
 * \return  The link ID to use for this packet
 */
uint32_t udataNet_GetTxMgmtLink(uint32_t uNetIfId, TMacAddr mac);

/* \brief   Inserts a Tx data packet from the network stack to the driver Tx-data path
 * \param   hUdata      - The udata module handle
 * \param   pPktCtrlBlk - The TxCtrlBlk struct that wraps the packet
 * \param   uNetIfId    - The Network interface ID from which the packet arrived
 * \param   uPacketDtag - The packet QoS priority optionaly set by the OAL
 * \return  OK if inserted successfully, NOK if dropped due to lack of resources
 */
uint32_t udataNet_InsertDataPacket(TTxCtrlBlk *pPktCtrlBlk, uint32_t uNetIfId, uint8_t uPacketDtag);


#ifdef TI_DBG  

void udataNet_RxTxDebug(TUdata *hUdata, uint32_t funcType, void *pParam);

#endif /* TI_DBG */


#endif /* UDATA_NET_API_H_ */
