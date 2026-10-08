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
#ifndef LOWER_MAC_IF_NAB_H_
#define LOWER_MAC_IF_NAB_H_

#include <osi_type.h>

#define NAB_EXTRA_BYTES 4
#define NAB_SEND_CMD        0x940d // 0x900D opcode for tX
#define NAB_SEND_FLAGS      0x08

#define HOST_SYNC_PATTERN   0x5C5C5C5C
#define HOST_CNYS_PATTERN   0xC5C5C5C5
#define DEVICE_SYNC_PATTERN 0xABCDDCBA
#define DEVICE_RECV_OPCODE  0x1004
#define NAB_GENERAL_ERROR_FW_LOGS_OPCODE  0x900
#define CC33XX_MAX_FW_LOGS_BUFFER_SIZE    ((0x1000) - (sizeof(NAB_header_t))) //a bit under ~4KB


#define FW_STATUS_ADDR      0x0000BFFC //read from status register address
#define NAB_CONTROL_ADDR    0x0000BFF8 //read from NAB mailBOX address
#define NAB_DATA_ADDR       0x0000BFF0 //command Mbox address

//The address of the shared memory at the core, which holds the tx status
#define CORE_MEMSS__TX_CTRL_STATUS__ADDR 0x0000000

enum HIF_STATUS_REQ_FLAGS_T
{
    HIF_GET_RX_HINT_CNTRL_STATUS = 0x1,
    HIF_GET_TX_CNTRL_STATUS = 0x2,
    HIF_GET_TSF_STATUS=0x4
};

typedef struct __PACKED__
{
    uint16_t Opcode;
    uint16_t Len;
}NAB_genericHeader_t;

typedef struct __PACKED__
{
    uint32_t sync_pattern;
    uint16_t opcode;
    uint16_t len;
}NAB_header_t;


typedef struct __PACKED__
{
    uint32_t sync;
    uint16_t opcode;//0x100A 0x1004
    uint16_t len;
    uint32_t rx_status;
    int16_t  desc_len_or_error;
    uint8_t  desc_sd;
    uint8_t  desc_flags;
}NAB_rx_header_t;

#define NAB_RX_HEADER_LEN_ADDITION (8) //contains : sync + opcode + len
#define NAB_RX_HEADER_LEN_SUBMISSION (8) //contains : rx_status + desc_len_or_error + desc_sd + desc_flags


#endif /* LOWER_MAC_IF_NAB_H_ */
