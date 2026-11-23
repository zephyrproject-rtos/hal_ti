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

#ifndef HOST_DRIVER_TX_H_
#define HOST_DRIVER_TX_H_


#include <user_errno.h>
#include "fw_status.h"

#define MAX_TX_FRAMES (8)
#ifndef WLAN_QOS_HDR_LEN
#define WLAN_QOS_HDR_LEN (26)
#endif
#ifndef WLAN_SNAP_HDR_LEN
#define WLAN_SNAP_HDR_LEN (8)
#endif
#ifndef WLAN_RSN_HEADER
#define WLAN_RSN_HEADER (8)
#endif
#ifndef WLAN_HT_CONTROL_FIELD_LEN
#define WLAN_HT_CONTROL_FIELD_LEN               (4)
#endif

#define TX_HW_BLOCK_SPARE        1
/* The maximum number of Tx descriptors in all chip families */
#define MAX_TX_DESCRIPTORS 100
#define MAX_TX_BLOCK       92
#define TX_BUFFER_SIZE (16 * 1024)

#define TI_BIT(x)                   (1 << (x))

#define TX_HW_BLOCK_SPARE 1
/* for special cases - namely, TKIP and GEM */
#define TX_HW_EXTRA_BLOCK_SPARE 2

#define SET_BIT_BY_IDX(bitmap, idx) ((bitmap) |= TI_BIT(idx))
#define CLEAR_BIT_BY_IDX(bitmap, idx) ((bitmap) &= ~TI_BIT(idx))
#define OSPREY_TX_HW_BLOCK_SIZE         256
#define OSPREY_INTERNAL_DESC_SIZE   200
#define TX_HW_MGMT_PKT_LIFETIME_TU       2000
#define TX_STATUS_STAT_BIT_IDX 7
#define TX_STATUS_DESC_ID_MASK    0x7F

//#define DEBUG_TX_RESULT
#ifdef DEBUG_TX_RESULT
#define TX_RESULT_PRINT Report
#define TX_RESULT_PRINT_ERROR Report
#else
#define TX_RESULT_PRINT(...)
#define TX_RESULT_PRINT_ERROR Report
#endif

//#define DEBUG_TX_DATA_SEND
#ifdef DEBUG_TX_DATA_SEND
#define TX_DATA_SEND_PRINT Report
#define TX_DATA_SEND_PRINT_ERROR Report
#else
#define TX_DATA_SEND_PRINT(...)
#define TX_DATA_SEND_PRINT_ERROR Report
#endif

//#define DEBUG_TX_FRAME_FLOW_CNTRL
#ifdef DEBUG_TX_FRAME_FLOW_CNTRL
#define TX_FRAME_FLOW_CNTRL_PRINT_MUST Report
#define TX_FRAME_FLOW_CNTRL_PRINT Report
#define TX_FRAME_FLOW_CNTRL_PRINT_ERROR Report
#else
#define TX_FRAME_FLOW_CNTRL_PRINT_MUST(...)
#define TX_FRAME_FLOW_CNTRL_PRINT(...)
#define TX_FRAME_FLOW_CNTRL_PRINT_ERROR Report
#endif

//#define DEBUG_TX_PRINT_PKT
#ifdef DEBUG_TX_PRINT_PKT
#define TX_DATA_SEND_PRINT_PKT Report
#else
#define TX_DATA_SEND_PRINT_PKT(...)
#endif


//#define DEBUG_TX
#ifdef DEBUG_TX
#define TX_PRINT Report
#define TX_PRINT_ERROR Report
#else
#define TX_PRINT(...)
#define TX_PRINT_ERROR Report
#endif

//#define DEBUG_TX_COMPLETE
#ifdef DEBUG_TX_COMPLETE
#define TX_PRINT_COMPLETE Report
#else
#define TX_PRINT_COMPLETE(...)
#endif

typedef struct __PACKED__{
    uint32_t sync;
    uint16_t opcode;
    uint16_t len;
    uint16_t desc_length;
    uint8_t  sd;
    uint8_t  flags;
} __attribute__ ((__packed__)) NAB_tx_header_t;


#define PADDING_COMPLETION_FOR_WLAN_HEADER ((WLAN_QOS_HDR_LEN + WLAN_SNAP_HDR_LEN + WLAN_RSN_HEADER + WLAN_HT_CONTROL_FIELD_LEN + sizeof(TxIfDescriptor_t)) - (ETHERNET_HDR_LEN))

void tx_ImmediateComplete(FwStatus_t *fwStatus);


#endif /* HOST_DRIVER_TX_H_ */
