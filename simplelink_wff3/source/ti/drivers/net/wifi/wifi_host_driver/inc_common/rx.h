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
#ifndef HOST_DRIVER_RX_H_
#define HOST_DRIVER_RX_H_

//#define DEBUG_RX_HIGH_PRIORITY
#ifdef DEBUG_RX_HIGH_PRIORITY
#define RX_PRINT_HIGH_PRIORITY Report
#define RX_PRINT_ERROR_HIGH_PRIORITY Report
#else
#define RX_PRINT_HIGH_PRIORITY(...)
#define RX_PRINT_ERROR_HIGH_PRIORITY Report
#endif

//#define DEBUG_RX
#ifdef DEBUG_RX
#define RX_PRINT Report
#define RX_PRINT_ERROR Report
#else
#define RX_PRINT(...)
#define RX_PRINT_ERROR Report
#endif

//#define DEBUG_RX_MGMT
#ifdef DEBUG_RX_MGMT
#define RX_MGMT_PRINT Report
#define RX_MGMT_PRINT_ERROR Report
#else
#define RX_MGMT_PRINT(...)
#define RX_MGMT_PRINT_ERROR Report
#endif


//#define DEBUG_RX_MGMT_DETAIL
#ifdef DEBUG_RX_MGMT_DETAIL
#define RX_MGMT_PRINT_DETAIL Report
#else
#define RX_MGMT_PRINT_DETAIL(...)
#endif

//#define DEBUG_RX_DATA
#ifdef DEBUG_RX_DATA
#define RX_DATA_PRINT Report
#define RX_DATA_PRINT_ERROR Report
#else
#define RX_DATA_PRINT(...)
#define RX_DATA_PRINT_ERROR Report
#endif

//#define DEBUG_RX_QUEUE
#ifdef DEBUG_RX_QUEUE
#define RX_QUEUE_PRINT Report
#define RX_QUEUE_PRINT_ERROR Report
#else
#define RX_QUEUE_PRINT(...)
#define RX_QUEUE_PRINT_ERROR Report
#endif

//#define DEBUG_BLOCK_ACK
#ifdef DEBUG_BLOCK_ACK
#define BLOCK_ACK_PRINT_REPORT Report
#define BLOCK_ACK_PRINT_REPORT_ERROR Report
#else
#define BLOCK_ACK_PRINT_REPORT(...)
#define BLOCK_ACK_PRINT_REPORT_ERROR Report
#endif

/*
 * Account for the padding inserted by the FW in case of RX_ALIGNMENT
 * or for fixing alignment in case the packet wasn't aligned.
 */
#define RX_BUF_ALIGN                 2

int rx_Init();
void rx_Deinit();
int rx(uint8_t *rx_buf_ptr, uint16_t rx_buf_len);


typedef struct
{
    uint16_t frame_control;
    uint16_t duration_id;
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint16_t seq_ctrl;
    /* followed by 'u8 addr4[6];' if ToDS and FromDS is set in data frame
     */
}ieee80211_hdr_t;





typedef enum
{
    RX_NEXT_LAYER_NONE,
    RX_NEXT_LAYER_WLAN,
    RX_NEXT_LAYER_ETHERNET
}rxNextLayer_e;







/*
 * This callback defines the allocation function
 * used by the rx module of the transport layer
 * parameters needed
 * output - buff - pointer to pointer of buffer for the allocated buffer
 * input  - size  - buffer size needed
 * return need to return -1 on allocation fail and 0 on success
 *
 */
typedef int  (* RxAllocationFunctionCB_t)(uint8_t **buff,uint32_t len);



/*
 * This callback defines the recv fucntion of the next layer
 * the frame will be moved to there
 * input -  buff - pointer to pointer of buffer for the allocated buffer
 * input  - len  - frame length if next layer is wifi, rxIFdescriptor will be included
 *
 */
typedef void (* RxRecvNextLayerFunctionCB_t)(uint32_t link, uint8_t *buff,uint32_t len);


void rx_RegisterAllocationFunction(RxAllocationFunctionCB_t function, void *parameters);


void rx_RegisterNextLayerRecvFunction(RxRecvNextLayerFunctionCB_t function, void *parameters,rxNextLayer_e nextLayer);



#endif /* HOST_DRIVER_RX_H_ */
