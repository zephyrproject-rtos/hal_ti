/*
 * Copyright (c) 2025, Texas Instruments Incorporated
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

# ifndef __LRF_OVERHEAD_H__
# define __LRF_OVERHEAD_H__

 /* Time from start of preamble to SYSTIM capture at sync found */
#define LRF_OVERHEAD_BLE_TIMESTAMP_ADJUST_1MBPS 240U
#define LRF_OVERHEAD_BLE_TIMESTAMP_ADJUST_2MBPS 148U
#define LRF_OVERHEAD_BLE_TIMESTAMP_ADJUST_CODED 1662U


/* Minimal time to stay in RX to be able to receive and detect the sync word */
/* Preamble + sync word + demodulator delay */
#define LRF_OVERHEAD_BLE_RX_SYNC_1MBPS 240U
#define LRF_OVERHEAD_BLE_RX_SYNC_2MBPS 148U
#define LRF_OVERHEAD_BLE_RX_SYNC_CODED 1662U


/* RX start overhead  factors */
/* PBE_BLE5_RAM.SYNTHCALTIMEOUT */
/* Final RX_START_OVERHEAD is RX_START_LRFD_OVERHEAD + SYNCCALTIMEOUT + COEX_T1 */

#define LRF_OVERHEAD_BLE_RX_START_1MBPS 140U
#define LRF_OVERHEAD_BLE_RX_START_2MBPS 140U
#define LRF_OVERHEAD_BLE_RX_START_CODED 200U


/* TX_START_OVERHEAD factors*/
/* LRFDMDM.SPARE0: Pilot tone length */
/* PBE_BLE5_RAM.SYNTHCALTIMEOUT */
/* Final TX_START_OVERHEAD is TX_START_LRFD_OVERHEAD + [TX_START_COEX_OVERHEAD] COEXT1+ SYNCCALTIMEOUT + PILOT_TONE  */
#define LRF_OVERHEAD_BLE_TX_START_LRFD_1MBPS 62U
#define LRF_OVERHEAD_BLE_TX_START_LRFD_2MBPS 39U
#define LRF_OVERHEAD_BLE_TX_START_LRFD_CODED 57U

/* If PBE_BLE5_RAM_O_COEX != 0 add this coex overhead to the final TX_START_OVERHEAD */
#define LRF_OVERHEAD_BLE_TX_START_COEX 6U

# endif /* __LRF_OVERHEAD_H__ */
