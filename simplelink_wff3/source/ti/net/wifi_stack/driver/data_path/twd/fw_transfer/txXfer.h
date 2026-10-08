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
/** \file   txXfer.h
 *  \brief  Handle Tx packets transfer to the firmware.
 *
 *
 *  \see
 */


#ifndef FW_TRANSFER_TXXFER_H_
#define FW_TRANSFER_TXXFER_H_


#include "osi_kernel.h"
#include "trnspt_thread.h"
#include "public_share.h"
#include "bus_if.h"
#include "nab.h"
#include "trnspt_if.h"
#include "tx.h"

#include "fw_event_handle.h"
#include "tw_driver.h"

#ifdef TI_DBG
#define DBG_MAX_AGGREG_PKTS     TWD_TX_AGGREG_PKTS_LIMIT_MAX + 1
#endif


/* The TxXfer module object. */
typedef struct
{
    uint32_t             uAggregMaxPkts;          /* Max number of packets that may be aggregated */
    uint32_t             uAggregMaxLen;           /* Max length in bytes of a single aggregation */
    uint32_t             uAggregPktsNum;          /* Number of packets in current aggregation */
    uint32_t             uAggregPktsLen;          /* Aggregated length of current aggregation */
    TTxCtrlBlk *         pAggregFirstPkt;         /* Pointer to the first packet of current aggregation */
    TTxCtrlBlk *         pAggregLastPkt;          /* Pointer to the last packet of current aggregation */
    uint32_t             uSdioBlkSizeShift;       /* In block-mode:  uBlkSize = (1 << uBlkSizeShift)   */
    uint16_t             uSdioBlkAlignMask;       /* Mask used for packets alignment to SDIO block size */
    uint32_t             uHostIfCfgBitmap;        /* Host interface configuration bitmap */
    OsiTimer_t           aggrTimer;               /* timer for sending aggr.*/
    uint32_t             uAggrEndBurstContextId;  /* Id of the end of burst task */
#ifdef TI_DBG
    uint32_t             aDbgCountPktAggreg[DBG_MAX_AGGREG_PKTS];
#endif
} TTxXferObj;



#endif /* SOURCE_TI_NET_WIFI_STACK_DRIVER_DATA_PATH_TWD_FW_TRANSFER_TXXFER_H_ */
