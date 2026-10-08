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

#ifndef FW_STATUS_H_
#define FW_STATUS_H_
#define TX_RESULT_QUEUE_SIZE  108

typedef struct __PACKED__
{
    uint8_t txResultQueueIndex;
    uint8_t reserved1[3];
    uint8_t txResultQueue[TX_RESULT_QUEUE_SIZE];
    uint32_t linkPsBitmap; /* A bitmap (where each bit represents a single HLID) to indicate PS/Active mode of the link */
    uint32_t linkFastBitmap; /* A bitmap (where each bit represents a single HLID) to indicate if the station is in Fast mode */
    uint32_t linkSuspendedBitmap; /* A bitmap (where each bit represents a single HLID) to indicate if a links is suspended/aboout to be suspended*/
    uint8_t TxFlowControlAcThreshold; /* Host TX Flow Control descriptor per AC threshold */
    uint8_t TxFlowControlHostTxPsThreshold; /* Host TX Flow Control descriptor PS link threshold */
    uint8_t TxFlowControlSuspendThreshold; /* Host TX Flow Control descriptor Suspended link threshold */
    uint8_t TxFlowControlSlowThreshold; /* Host TX Flow Control descriptor Slow link threshold */
    uint8_t TxFlowControlFastThreshold; /* Host TX Flow Control descriptor Fast link threshold */
    uint8_t TxFlowControlStopSlowThreshold; /* Host TX Flow Control descriptor Stop Slow link threshold */
    uint8_t TxFlowControlStopFastThreshold; /* Host TX Flow Control descriptor Stop Fast link threshold */
    uint8_t reserved2;
    // Additional information can be added here
}core_fw_status_t;

typedef struct __PACKED__ {
    uint32_t block_pad[28];
    uint32_t host_interrupt_status;
    uint32_t rx_status;
    core_fw_status_t fwInfo;
    uint32_t tsf;
}FwStatus_t;



#endif /* FW_STATUS_H_ */
