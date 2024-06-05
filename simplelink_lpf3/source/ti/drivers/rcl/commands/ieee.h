/*
 * Copyright (c) 2021-2024, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_commands_ieee_h__include
#define ti_drivers_RCL_commands_ieee_h__include

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>

#include <ti/drivers/utils/List.h>

typedef struct RCL_CMD_IEEE_RX_TX_t            RCL_CmdIeeeRxTx;
typedef struct RCL_CMD_IEEE_TX_TEST_t          RCL_CmdIeeeTxTest;
typedef struct RCL_STATS_IEEE_t                RCL_StatsIeee;
typedef struct RCL_CmdIeee_RxAction_t          RCL_CmdIeee_RxAction;
typedef struct RCL_CmdIeee_TxAction_t          RCL_CmdIeee_TxAction;

/* Command IDs for generic commands */
#define RCL_CMDID_IEEE_RX_TX            0x2001U
#define RCL_CMDID_IEEE_TX_TEST          0x2002U

/** Macro for finding RF frequency from channel */
#define RCL_CMD_IEEE_CHANNEL_FREQUENCY(channel) ((((channel) - 11UL) * 5000000UL) + 2405000000UL)

/**
 *  @brief Appended packet status field from RX buffer
 *
 */
typedef union {
    struct {
        uint8_t crcError    :1;     /*!< True if packet had CRC error */
        uint8_t ignored     :1;     /*!< True if packet was ignored */
        uint8_t reserved    :6;
    };
    uint8_t value;
} RCL_CmdIeee_RxPktStatus;

 /**
 *  @brief IEEE 802.15.4 Receive and transmit command
 *
 *  Command to receive or transmit a packet
 */
struct RCL_CMD_IEEE_RX_TX_t {
    RCL_Command             common;
    uint32_t                rfFrequency; /*!< RF frequency in Hz to program */
    RCL_Command_TxPower     txPower;     /*!< Transmit power */
    RCL_CmdIeee_RxAction    *rxAction;   /*!< Configuration of receive part of command. NULL: Transmit only */
    RCL_CmdIeee_TxAction    *txAction;   /*!< Configuration of transmit part of command. NULL: No transmission configured */
    RCL_StatsIeee           *stats;      /*!< Statistics */

};
#define RCL_CmdIeeeRxTx_Default()                           \
{                                                           \
    .common = RCL_Command_Default(RCL_CMDID_IEEE_RX_TX,     \
                                  RCL_Handler_Ieee_RxTx),   \
    .rfFrequency = 2440000000U,                             \
    .txPower = {.dBm = 0, .fraction = 0},                   \
    .rxAction = NULL,                                       \
    .txAction = NULL,                                       \
    .stats = NULL,                                          \
}
#define RCL_CmdIeeeRxTx_DefaultRuntime() (RCL_CmdIeeeRxTx) RCL_CmdIeeeRxTx_Default()

typedef enum
{
    RCL_CmdIeee_AutoAck_Off,                    /*!< No auto-ACK */
    RCL_CmdIeee_AutoAck_ImmAckNoAutoPend,       /*!< Send automatic Imm-Ack with frame pending from setting */
    RCL_CmdIeee_AutoAck_ImmAckAutoPendAll,      /*!< Send automatic Imm-Ack with frame pending from source matching table */
    RCL_CmdIeee_AutoAck_ImmAckAutoPendDataReq,  /*!< Send automatic Imm-Ack with frame pending from source matching table for data requests */
    RCL_CmdIeee_AutoAck_ProvidedFrame,          /*!< Send ACK frame provided externally (not supported in this version) */
} RCL_CmdIeee_AutoAckMode;

typedef union
{
    struct {
        uint16_t panId;                      /*!< Pan ID of the entry */
        uint16_t shortAddr;                  /*!< Short address of the entry */
    };
    uint32_t combined;
} RCL_CmdIeee_PanIdAddr;

/** Maximum number of entries in %RCL_CmdIeee_SourceMatchingTableShort (assuming no extended entry) */
#define RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_MAX_LEN 64

/** Maximum number of entries in %RCL_CmdIeee_SourceMatchingTableShort if an extended table is present*/
#define RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_WITH_EXT_MAX_LEN 32

#define RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_NUM_WORDS \
(((RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_MAX_LEN) + ((8 * sizeof(uint16_t)) - 1)) / (8 * sizeof(uint16_t)))

typedef struct
{
    uint32_t numEntries;                                                    /*!< Number of entries in the list */
    uint16_t entryEnable[RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_NUM_WORDS];  /*!< Bits indicating which entires are enabled for matching (1 means enabled) */
    uint16_t framePending[RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_NUM_WORDS]; /*!< Frame pending bits for the entries */
    RCL_CmdIeee_PanIdAddr shortEntry[];                                     /*!< PAN ID and short address for the entry */
} RCL_CmdIeee_SourceMatchingTableShort;

/** Maximum number of entries in %RCL_CmdIeee_SourceMatchingTableExt */
#define RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_MAX_LEN 16

#define RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_NUM_WORDS \
(((RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_MAX_LEN) + ((8 * sizeof(uint16_t)) - 1)) / (8 * sizeof(uint16_t)))

typedef struct
{
    uint32_t numEntries;                                                    /*!< Number of entries in the list */
    uint16_t entryEnable[RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_NUM_WORDS];    /*!< Bits indicating which entires are enabled for matching (1 means enabled) */
    uint16_t framePending[RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_NUM_WORDS];   /*!< Frame pending bits for the entries */
    uint64_t extEntry[];                                                    /*!< Extended address for the entry */
} RCL_CmdIeee_SourceMatchingTableExt;

typedef struct RCL_CmdIeee_PanConfig_t
{
    uint64_t localExtAddr;                      /*!< Extended address of device */
    uint16_t localPanId;                        /*!< PAN ID of device */
    uint16_t localShortAddr;                    /*!< Short address of device */
    RCL_CmdIeee_AutoAckMode autoAckMode : 3;    /*!< Auto-ACK mode */
    uint8_t defaultPend : 1;                    /*!< Default value of frame pending bit */
    uint8_t panCoord : 1;                       /*!< 0: Device is not pan coordinator. 1: Device is PAN coordinator */
    uint8_t maxFrameVersion : 2;                /*!< Maximum frame version to accept */
    RCL_CmdIeee_SourceMatchingTableShort *sourceMatchingTableShort; /*!< Source matching table for short addresses */
    RCL_CmdIeee_SourceMatchingTableExt *sourceMatchingTableExt;     /*!< Source matching table for extended addresses (not supported in this version)*/
} RCL_CmdIeee_PanConfig;

#define RCL_CmdIeee_PanConfig_Default()                     \
{                                                           \
    .localExtAddr = 0,                                      \
    .localPanId = 0,                                        \
    .localShortAddr = 0,                                    \
    .autoAckMode = RCL_CmdIeee_AutoAck_Off,                 \
    .defaultPend = 0,                                       \
    .panCoord = 0,                                          \
    .maxFrameVersion = 1,                                   \
    .sourceMatchingTableShort = NULL,                       \
    .sourceMatchingTableExt = NULL,                         \
}
#define RCL_CmdIeee_PanConfig_DefaultRuntime() (RCL_CmdIeee_PanConfig) RCL_CmdIeee_PanConfig_Default()

/* Do include after typedefs, as the types are needed in ti/drivers/rcl/handlers/ieee.h */
#include <ti/drivers/rcl/handlers/ieee.h>

/** Maximum number of simultaneously supported PANs */
#define RCL_CMD_IEEE_MAX_NUM_PAN    1   /* Maximum number of PANs; will be updated to 2 when dual PAN support is added */

struct RCL_CmdIeee_RxAction_t
{
    List_List rxBuffers;                /*!< Linked list of buffers for storing received packets */
    uint8_t numPan;                     /*!< Number of PANs to support. 0: Frame filtering disabled (promiscuous mode). 1: Single PAN. 2: Dual PAN (not supported in this version). */
    bool frameFiltStop;                 /*!< 0: Receive frame to the end on frame filtering mismatch. 1: Go back to sync search on frame filtering mismatch. Not supported in this version. */
    bool disableSync;                   /*!< 0: Receive packets normally. 1: Do not sync to received SFD (not supported in this version). */
    bool alwaysStoreAck;                /*!< 0: Store ACKs received after transmission only. 1: Store all received ACKs. */
    RCL_CmdIeee_PanConfig panConfig[RCL_CMD_IEEE_MAX_NUM_PAN];  /*!< PAN configuration for the supplied PANs */
};

#define RCL_CmdIeee_RxAction_Default()                      \
{                                                           \
    .rxBuffers = { 0 },                                     \
    .numPan = 0,                                            \
    .frameFiltStop = false,                                 \
    .disableSync = false,                                   \
    .alwaysStoreAck = false,                                \
    .panConfig = {RCL_CmdIeee_PanConfig_Default()}          \
}
#define RCL_CmdIeee_RxAction_DefaultRuntime() (RCL_CmdIeee_RxAction) RCL_CmdIeee_RxAction_Default()

typedef enum
{
    RCL_CmdIeee_NoCca = 0,                   /*!< No CCA; transmit unconditionally */
    RCL_CmdIeee_CcaMode1Energy = 1,          /*!< Report busy channel on energy above threshold */
    RCL_CmdIeee_CcaMode2Signal = 2,          /*!< Report busy channel on DSSS signal observed */
    RCL_CmdIeee_CcaMode3EnergyOrSignal = 3,  /*!< Report busy channel on energy above threshold OR DSSS signal observed */
    RCL_CmdIeee_CcaMode4Aloha = 4,           /*!< Always report idle channel when not receiving a packet */
    RCL_CmdIeee_CcaMode3EnergyAndSignal = 7, /*!< Report busy channel on energy above threshold AND DSSS signal observed */
} RCL_CmdIeee_CcaMode;

struct RCL_CmdIeee_TxAction_t
{
    RCL_CommandStatus txStatus;         /*!< Returned status of TX operation */
    int8_t rssiLimit;                   /*!< RSSI limit (dBm) for energy based CCA */
    RCL_ScheduleType ccaScheduling : 1; /*!< Schedule type for the CCA part */
    uint16_t allowDelay : 1;            /*!< 0: Give error if CCA time is in the past. 1: Start immediately if CCA time is in the past */
    RCL_CmdIeee_CcaMode ccaMode : 3;    /*!< CCA mode */
    uint16_t ccaCorrThresh : 3;         /*!< Correlation threshold for signal based CCA (0-7; correlation tops in 128 us window) */
    uint16_t ccaContentionWindow : 2;   /*!< Initial contention window value for CCA */
    uint16_t expectImmAck : 1;          /*!< 0: Immediate ACK not expected. 1: Immediate ACK expected */
    uint16_t expectEnhAck : 1;          /*!< 0: Enhanced ACK not expected. 1: Enhanced ACK expected. Not supported in this version. */
    uint16_t allowTxDelay : 1;          /*!< 0: Give error if TX time is in the past. 1: Send TX packet immediately if TX time is in the past */
    uint16_t endCmdWhenDone : 1;        /*!< 0: Keep command and RX action alive after TX action is done. 1: End command after TX action is done */
    uint32_t absCcaStartTime;           /*!< Absolute start time of the CCA part */
    uint16_t relativeTxStartTime;       /*!< Start time of TX packet relative to the CCA start time */
    uint16_t ackTimeout;                /*!< Timeout for getting sync on ACK relative to end of transmitted packet */
    RCL_Buffer_DataEntry *txEntry;      /*!< Entry holding frame to be transmitted */
    uint32_t txTimeStamp;               /*!< Returned time stamp of transmitted packet. Not supported in this version. */
};
#define RCL_CmdIeee_TxAction_Default()                      \
{                                                           \
    .txStatus = RCL_CommandStatus_Idle,                     \
    .rssiLimit = -70,                                       \
    .ccaScheduling = RCL_Schedule_Now,                      \
    .allowDelay = 1,                                        \
    .ccaMode = RCL_CmdIeee_NoCca,                           \
    .ccaCorrThresh = 3,                                     \
    .ccaContentionWindow = 1,                               \
    .expectImmAck = 0,                                      \
    .expectEnhAck = 0,                                      \
    .allowTxDelay = 1,                                      \
    .endCmdWhenDone = 0,                                    \
    .absCcaStartTime = 0,                                   \
    .relativeTxStartTime = 0,                               \
    .ackTimeout = RCL_SCHEDULER_SYSTIM_US(300),             \
    .txEntry = NULL,                                        \
    .txTimeStamp = 0,                                       \
}
#define RCL_CmdIeee_TxAction_DefaultRuntime() (RCL_CmdIeee_TxAction) RCL_CmdIeee_TxAction_Default()


/**
 *  @brief IEEE 802.15.4 transmitter test command
 *
 *  Command to transmit continuously, either a modulated signal or continuous wave
 */
struct RCL_CMD_IEEE_TX_TEST_t {
    RCL_Command     common;
    uint32_t        rfFrequency;    /*!< RF frequency in Hz to program */
    RCL_Command_TxPower txPower;    /*!< Transmit power */
    uint16_t     txWord;            /*!< Repeated word to transmit */
    struct {
        uint8_t  whitenMode: 2;     /*!< 0. No whitening. 1: PRBS-9. 2: PRBS-15. 3: PRBS-32 */
        uint8_t  sendCw: 1;         /*!< 0: Send modulated signal. 1: Send CW */
        uint8_t  reserved: 5;       /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdIeeeTxTest_Default()                             \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_IEEE_TX_TEST,    \
                                  RCL_Handler_Ieee_TxTest),  \
    .rfFrequency = 2440000000U,                                 \
    .txPower = {.dBm = 0, .fraction = 0},                       \
    .txWord = 0,                                                \
    .config = {                                                 \
        .whitenMode = 2,                                        \
        .sendCw = 0,                                            \
        .reserved = 0,                                          \
    },                                                          \
}
#define RCL_CmdIeeeTxTest_DefaultRuntime() (RCL_CmdIeeeTxTest) RCL_CmdIeeeTxTest_Default()

#define RCL_CMD_IEEE_WH_MODE_OFF         0 /*!< config.whitenMode: No whitening */
#define RCL_CMD_IEEE_WH_MODE_PRBS9       1 /*!< config.whitenMode: PRBS-9 */
#define RCL_CMD_IEEE_WH_MODE_PRBS15      2 /*!< config.whitenMode: PRBS-15 */
#define RCL_CMD_IEEE_WH_MODE_PRBS32      3 /*!< config.whitenMode: PRBS-32 */

struct RCL_STATS_IEEE_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   timestampValid;        /*!< Returns 1 if %lastTimestamp is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet */
    int8_t    maxRssi;               /*!< Highest RSSI observed during the operation (only updated after packets and at the end of operation). Not supported in this version. */
    uint32_t  lastTimestamp;         /*!< Timestamp of last successfully received packet */
    uint16_t  nRxNok;                /*!< Number of packets received with CRC error */
    uint16_t  nRxFifoFull;           /*!< Number of packets received that did not fit in RX FIFO */
    uint16_t  nRxOk;                 /*!< Number of correctly received packets */
    uint16_t  nRxIgnored;            /*!< Number of ignored packets received */
    uint16_t  nTxAck;                /*!< Number of auto-ACKs transmitted */
    uint16_t  nTx;                   /*!< Number of frames transmitted */
};

#define RCL_StatsIeee_Default()  \
{                                   \
    .config = { 0 },                \
    .timestampValid = 0,            \
    .lastRssi = LRF_RSSI_INVALID,   \
    .maxRssi = LRF_RSSI_INVALID,    \
}
#define RCL_StatsIeee_DefaultRuntime() (RCL_StatsIeee) RCL_StatsIeee_Default()



#endif
