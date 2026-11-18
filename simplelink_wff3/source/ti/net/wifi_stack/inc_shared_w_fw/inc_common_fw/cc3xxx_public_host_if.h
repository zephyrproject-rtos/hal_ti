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
#ifndef FW_HOST_IF_SHARED_CC3XXX_PUBLIC_HOST_IF_H_
#define FW_HOST_IF_SHARED_CC3XXX_PUBLIC_HOST_IF_H_


// Interrupts
typedef enum
{
    HOST_INT_TX_RESULT         = 0,
    HOST_INT_EVENT_CMD_CMPLT   = 1,
    HOST_INT_RX_DATA           = 2,
    HOST_INT_ROM_INIT_CMPLT    = 3,
    HOST_INT_RAM_INIT_CMPLT    = 4,
    HOST_INT_FW_WAKE_UP_CMPLT  = 5,
    HOST_INT_FW_INIT_COMPLETE  = 6,
    HOST_INT_GENERAL_ERR       = 31,
    HOST_INT_MAX_NUM           = 0xFF
}hostIfInt_e;

//******************************************************************************
//                       LX Core Status
//   This structure is read by the host at the end of every SDIO transaction.
//   It holds the information required for the host to manage its current and next transaction.
//   Some of the information is attached automatically by the NAB (from registers),
//   and some is prepared by FW.
//   The structure contains three parts -
//   1. Two registers -  HINT_STATUS_REG - 32 bit interrupt status. set by FW, cleared on read.
//                       NAB_RX_STATUS_REG - managed by NAB. reflects the amount of rx data in queue + other info (see details in the register description
//   2. SW information - * Information location starts right after the socket 0 pointer entry (MEM_SKT_JUMP_TBL_ADDR + 4).
//                       * Information size - should be defined in CORE_STATUS_LEN_1.
//                       This structure holds the tx result queue, and other SW info.
//   3. extra info     - Can be added from any location  (memory or registers).
//                       * Information location - can be located anywhere. pointer should be stored in SUB_DESC_RAM_BASE
//                       * Information size - should be defined in CORE_STATUS_LEN_2
//                       Currently we use this for sending the TSF to the host.
//******************************************************************************
#define TX_RESULT_QUEUE_SIZE  108

typedef struct
{
    uint8_t   txResultQueueIndex;
    uint8_t   reserved1[3];
    uint8_t   txResultQueue[TX_RESULT_QUEUE_SIZE];
    uint32_t  linkPsBitmap;                       /* A bitmap (where each bit represents a single HLID) to indicate PS/Active mode of the link */
    uint32_t  linkFastBitmap;                     /* A bitmap (where each bit represents a single HLID) to indicate if the station is in Fast mode */
    uint32_t  linkSuspendedBitmap;                /* A bitmap (where each bit represents a single HLID) to indicate if a links is suspended/aboout to be suspended*/
    uint8_t   TxFlowControlAcThreshold;           /* Host TX Flow Control descriptor per AC threshold */
    uint8_t   TxFlowControlHostTxPsThreshold;     /* Host TX Flow Control descriptor PS link threshold */
    uint8_t   TxFlowControlSuspendThreshold;      /* Host TX Flow Control descriptor Suspended link threshold */
    uint8_t   TxFlowControlSlowThreshold;         /* Host TX Flow Control descriptor Slow link threshold */
    uint8_t   TxFlowControlFastThreshold;         /* Host TX Flow Control descriptor Fast link threshold */
    uint8_t   TxFlowControlStopSlowThreshold;     /* Host TX Flow Control descriptor Stop Slow link threshold */
    uint8_t   TxFlowControlStopFastThreshold;     /* Host TX Flow Control descriptor Stop Fast link threshold */
    uint8_t   reserved2;
    // Additional information can be added here
}LxCoreStatus_FwInfo_t;



// Structure below define the structure as seen by the host. In the FW it is gathered from several location.
typedef struct
{
    uint32_t                HINT_STATUS_REG;
    uint32_t                NAB_RX_STATUS_REG;
    LxCoreStatus_FwInfo_t fwInfo;
    uint32_t                TSF_L_REG;
}LxCoreStatus_t;

typedef struct
{

}LxNabHeaderData_t;

typedef struct
{

}LxNabHeaderEvent_t;


typedef struct
{
    uint16_t Short;
    uint8_t  Byte1;
    uint8_t  Byte2;
} OSPREY_Protocol_SyncPattern_t ;



/* Endian auto detection both sides should use the same SYNC / CNYS patterns  */
typedef union
{
    OSPREY_Protocol_SyncPattern_t   pattern ;
    uint32_t                           w32     ;
} OSPREY_Protocol_SyncPattern_u;

#if 1 // O3 configuration - temporary
#define OSPREY_PROTOCOL_H2D_SYNC_PATTERN_STRUCT         \
        (                                           \
            (OSPREY_Protocol_SyncPattern_u)             \
            {                                       \
                .pattern =                          \
                {                                   \
                    .Short = 0x5c5c ,               \
                    .Byte1 = 0x5c   ,               \
                    .Byte2 = 0x5c                   \
                }                                   \
            }                                       \
        ) /* MACRO OSPREYL_PROTOCOL_H2N_SYNC_PATTERN_STRUCT */

#define OSPREY_PROTOCOL_H2D_CNYS_PATTERN_STRUCT         \
        (                                           \
            (OSPREY_Protocol_SyncPattern_u)             \
            {                                       \
                .pattern =                          \
                {                                   \
                    .Short = 0xc5c5 ,               \
                    .Byte1 = 0xc5   ,               \
                    .Byte2 = 0xc5                   \
                }                                   \
            }                                       \
        ) /* MACRO OSPREY_PROTOCOL_H2N_SYNC_PATTERN_STRUCT */
#else // should be
#define OSPREY_PROTOCOL_H2D_SYNC_PATTERN_STRUCT         \
        (                                           \
            (OSPREY_Protocol_SyncPattern_u)             \
            {                                       \
                .pattern =                          \
                {                                   \
                    .Short = 0x4321 ,               \
                    .Byte1 = 0x34   ,               \
                    .Byte2 = 0x12                   \
                }                                   \
            }                                       \
        ) /* MACRO OSPREYL_PROTOCOL_H2N_SYNC_PATTERN_STRUCT */

#define OSPREY_PROTOCOL_H2D_CNYS_PATTERN_STRUCT         \
        (                                           \
            (OSPREY_Protocol_SyncPattern_u)             \
            {                                       \
                .pattern =                          \
                {                                   \
                    .Short = 0x8765 ,               \
                    .Byte1 = 0x78   ,               \
                    .Byte2 = 0x56                   \
                }                                   \
            }                                       \
        ) /* MACRO OSPREY_PROTOCOL_H2N_SYNC_PATTERN_STRUCT */
#endif

#define NAB_SYNC_PATTERN                \
        (OSPREY_PROTOCOL_H2D_SYNC_PATTERN_STRUCT.w32)

#define NAB_CNYS_PATTERN                \
        (OSPREY_PROTOCOL_H2D_CNYS_PATTERN_STRUCT.w32)

#define  NAB_D2H_SYNC_PATTERN   0xABCDDCBA

#define HOST_INERFACE_RX_STATUS_BLOCK_SIZE  (64)  // rx status contains event size in block

#endif /* FW_HOST_IF_SHARED_CC3XXX_PUBLIC_HOST_IF_H_ */
