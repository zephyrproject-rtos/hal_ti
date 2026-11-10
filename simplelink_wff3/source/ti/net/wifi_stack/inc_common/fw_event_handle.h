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
/*
 * FwEvent_osprey.h
 *
 *  Created on: 24 Oct 2021
 *      Author: a0387677
 */


#ifndef _FW_EVENT_HANDLER_
#define _FW_EVENT_HANDLER_

#include "osi_type.h"
#include "txn_bus_drv.h"
#include "fw_status.h"
#include "wlan_if.h"
#include "cc3xxx_public_event.h"

#define HINT_NEW_TX_RESULT               0x1  //bit_0
#define HINT_COMMAND_COMPLETE            0x2  //bit_1
#define HINT_RX_DATA_PENDING             0x4  //bit_2
#define HINT_ROM_LOADER_INIT_COMPLETE    0x8  //bit_3
#define HINT_SECOND_LOADER_INIT_COMPLETE 0x10 //bit_4
#define HINT_FW_INIT_COMPLETE            0x20 //bit_5

#define RX_TX_BUFFER   13000 //(17664-- for 16k RXaggr )(for 8k RX aggr 13000 same buffer size as in the fW)
#define SDIO_BLOCK_SIZE 128

#define NAB_EXTRA_BYTES 4


//the NAB adds the sync pattern + add 4 bytes for the status(NAB_EXTRA_BYTES)
#define EVENT_COMPLETE_MAX_LENGTH (sizeof(NAB_header_t) + NAB_EXTRA_BYTES + sizeof(EventCompleteMboxTLV_t) + sizeof( CommandComplete_t) + sizeof(EventCompleteMboxTLV_t) + sizeof(EventMailBox_t))
#define CONTROL_BUFFER_READ_SIZE ((EVENT_COMPLETE_MAX_LENGTH+SDIO_BLOCK_SIZE-1)/SDIO_BLOCK_SIZE*SDIO_BLOCK_SIZE) //align to block size



typedef struct
{
    uint16 /*CommandStatus_e*/     status;
    uint8               param[MAX_MBOX_SIZE_BTL];
} CommandCompleteInfoBTL_t;

typedef struct
{
    uint16/*Command_e*/        cmdID;
    CommandCompleteInfoBTL_t   info;
} CommandCompleteBTL_t;

//the NAB adds the sync pattern + add 4 bytes for the status(NAB_EXTRA_BYTES)
#define EVENT_MAILBOX_TYPE_LEN (180U)  // Size of event_mailbox type. The type itself is not needed, but its size is used for the event_complete buffer size
#define EVENT_COMPLETE_MAX_LENGTH_BTL (sizeof(NAB_header_t) + NAB_EXTRA_BYTES + sizeof(EventCompleteMboxTLV_t) + sizeof( CommandCompleteBTL_t) + sizeof(EventCompleteMboxTLV_t) + EVENT_MAILBOX_TYPE_LEN)
#define CONTROL_BUFFER_READ_SIZE_BTL  ((EVENT_COMPLETE_MAX_LENGTH_BTL+SDIO_BLOCK_SIZE-1)/SDIO_BLOCK_SIZE*SDIO_BLOCK_SIZE) //align to block size





#define RX_BYTE_COUNT_MASK 0xFFFF


#define    CMD_BM_CODE_DOWNLOAD      (36)
#define    CMD_DOWNLOAD_INI_PARAMS   (37)
#define    CMD_DOWNLOAD_FIRST_CMD    (43)




#define MAX_POSITIVE16 0x7FFF




#endif /* _FW_EVENT_HANDLER_ */
