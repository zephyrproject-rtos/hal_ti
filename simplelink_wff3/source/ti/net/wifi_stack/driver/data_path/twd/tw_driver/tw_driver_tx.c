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
 *   MODULE:    TNETW_Driver_Tx.c
 *
 *   PURPOSE:   TNETW_Driver Tx API functions needed externally to the driver.
 *
 ****************************************************************************/

#define __FILE_ID__  FILE_ID_85
#if 0
#include "report.h"
#endif

#include "tw_driver.h"
#include "tx_ctrl_blk_api.h"
#include "tx_hw_queue_api.h"
#include "tx_xfer_api.h"
#include "tx_result_api.h"
#include "osi_kernel.h"

/** \file  TWDriverTx.c 
 *  \brief TI WLAN HW TX Access Driver
 *
 *  \see   TWDriver.h 
 */


/****************************************************************************
 *                  Tx Control Block API functions                          *
 ****************************************************************************/

TTxCtrlBlk *TWD_txCtrlBlk_Alloc (uint8_t isMgmt)
{
    HOOK(HOOK_TWDRIVERTX);

    return txCtrlBlk_Alloc (isMgmt);
}

void TWD_txCtrlBlk_Free (TTxCtrlBlk *pCurrentEntry)
{
    HOOK(HOOK_TWDRIVERTX);

    txCtrlBlk_Free (pCurrentEntry);
}

TTxCtrlBlk *TWD_txCtrlBlk_GetPointer(uint32_t uIndex)
{
    HOOK(HOOK_TWDRIVERTX);

    return txCtrlBlk_GetPointer(uIndex);
}



/****************************************************************************
 *                      Tx HW Queue API functions                           *
 ****************************************************************************/
#if 0 //TODO OSPREY_MX-20
ETxHwQueStatus TWD_txHwQueue_AllocResources (TTxCtrlBlk *pTxCtrlBlk, uint8_t *pBackpressureMap)
{
    HOOK(HOOK_TWDRIVERTX);

    return txHwQueue_AllocResources (pTxCtrlBlk, pBackpressureMap);
}
#endif
/****************************************************************************
 *                          Tx Xfer API functions                           *
 ****************************************************************************/

ETxnStatus TWD_txXfer_SendPacket (TTxCtrlBlk *pPktCtrlBlk)
{
    HOOK(HOOK_TWDRIVERTX);

    return txXfer_SendPacket (pPktCtrlBlk);
}


ETxnStatus TWD_txXferAggr_SendPacket (TTxCtrlBlk *pPktCtrlBlk)
{
    HOOK(HOOK_TWDRIVERTX);

    return txXferAggr_SendPacket (pPktCtrlBlk);
}

void TWD_txXferAggr_EndOfBurst (void)
{
    HOOK(HOOK_TWDRIVERTX);

    txXferAggr_EndOfBurst ();
}


