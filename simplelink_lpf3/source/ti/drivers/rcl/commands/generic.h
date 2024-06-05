/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_commands_generic_h__include
#define ti_drivers_RCL_commands_generic_h__include

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/handlers/generic.h>

#include <ti/drivers/utils/List.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)

typedef struct RCL_CMD_GENERIC_FS_t            RCL_CmdGenericFs;
typedef struct RCL_CMD_GENERIC_FS_OFF_t        RCL_CmdGenericFsOff;
typedef struct RCL_CMD_GENERIC_TX_t            RCL_CmdGenericTx;
typedef struct RCL_CMD_GENERIC_TX_REPEAT_t     RCL_CmdGenericTxRepeat;
typedef struct RCL_CMD_GENERIC_TX_TEST_t       RCL_CmdGenericTxTest;
typedef struct RCL_CMD_GENERIC_RX_t            RCL_CmdGenericRx;
typedef struct RCL_CMD_GENERIC_PBE_OPERATION_t RCL_CmdGenericPbeOperation;
typedef struct RCL_STATS_GENERIC_t             RCL_StatsGeneric;
typedef struct RCL_CMD_NESB_PTX_t              RCL_CmdNesbPtx;
typedef struct RCL_CMD_NESB_PRX_t              RCL_CmdNesbPrx;
typedef struct RCL_STATS_NESB_t                RCL_StatsNesb;
typedef struct RCL_CONFIG_ADDRESS_t            RCL_ConfigAddress;

/* Command IDs for generic commands */
#define RCL_CMDID_GENERIC_FS            0x0001U
#define RCL_CMDID_GENERIC_FS_OFF        0x0002U
#define RCL_CMDID_GENERIC_TX            0x0003U
#define RCL_CMDID_GENERIC_TX_REPEAT     0x0004U
#define RCL_CMDID_GENERIC_TX_TEST       0x0005U
#define RCL_CMDID_GENERIC_RX            0x0006U
#define RCL_CMDID_GENERIC_PBE_OPERATION 0x0007U
#define RCL_CMDID_NESB_PTX              0x0008U
#define RCL_CMDID_NESB_PRX              0x0009U


/**
 *  @brief RF frequency programming type object
 *
 *  Type to specify how frequency programming is done for FS command
 */
typedef enum RCL_FsType_e {
    RCL_FsType_Rx,               /*!< Program synth as for RX operation */
    RCL_FsType_Tx,               /*!< Program synth as for TX operation */
} RCL_FsType;

/**
 *  @brief Frequency programming command
 *
 *  Command to program a synth frequency without directly starting RX or TX
 */
struct RCL_CMD_GENERIC_FS_t {
    RCL_Command     common;
    uint32_t        rfFrequency; /*!< RF frequency in Hz to program */
    RCL_FsType      fsType;      /*!< Rules for synth setup */
};

#define RCL_CmdGenericFs_Default()                          \
{                                                           \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_FS,     \
                                  RCL_Handler_Generic_Fs),  \
    .rfFrequency = 2440000000U,                             \
    .fsType = RCL_FsType_Rx,                                \
}
#define RCL_CmdGenericFs_DefaultRuntime() (RCL_CmdGenericFs) RCL_CmdGenericFs_Default()

/**
 *  @brief Stop frequency synthesizer command
 *
 *  Command to stop the frequency synthesizer if it is running after a command
 */
struct RCL_CMD_GENERIC_FS_OFF_t {
    RCL_Command     common;
};

#define RCL_CmdGenericFsOff_Default()                           \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_FS_OFF,     \
                                  RCL_Handler_Generic_FsOff),   \
}
#define RCL_CmdGenericFsOff_DefaultRuntime() (RCL_CmdGenericFsOff) RCL_CmdGenericFsOff_Default()


/**
 *  @brief Generic transmit command
 *
 *  Command to transmit a packet
 */
struct RCL_CMD_GENERIC_TX_t {
    RCL_Command     common;
    uint32_t        rfFrequency; /*!< RF frequency in Hz to program. 0: Do not program frequency */
    List_List       txBuffers;   /*!< Linked list of packets to transmit. RCL will pop the first packet when transmitted. */
    uint32_t        syncWord;    /*!< Sync word to transmit */
    RCL_Command_TxPower txPower; /*!< Transmit power */
    struct {
        uint8_t     fsOff: 1;    /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint8_t     reserved: 7; /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdGenericTx_Default()                          \
{                                                           \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_TX,     \
                                  RCL_Handler_Generic_Tx),  \
    .rfFrequency = 2440000000U,                             \
    .txBuffers = { 0 },                                     \
    .syncWord = 0x930B51DE,                                 \
    .txPower = {.dBm = 0, .fraction = 0},                   \
    .config = {                                             \
        .fsOff = 1,                                         \
        .reserved = 0,                                      \
    },                                                      \
}
#define RCL_CmdGenericTx_DefaultRuntime() (RCL_CmdGenericTx) RCL_CmdGenericTx_Default()

/**
 *  @brief Generic repeated packet transmit command
 *
 *  Command to transmit a packet repeatedly
 */
struct RCL_CMD_GENERIC_TX_REPEAT_t {
    RCL_Command          common;
    uint32_t             rfFrequency; /*!< RF frequency in Hz to program. 0: Do not program frequency */
    RCL_Buffer_DataEntry *txEntry;    /*!< Packet to transmit */
    uint32_t             syncWord;    /*!< Sync word to transmit */
    uint32_t             timePeriod;  /*!< Time period (0.25 us units) of repeated transmissions. 0: Back-to-back */
    uint16_t             numPackets;  /*!< Number of times to send the packet: 0: Unlimited */
    RCL_Command_TxPower  txPower;     /*!< Transmit power */
    struct {
        uint8_t          fsOff: 1;    /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint8_t          fsRecal: 1;  /*!< 0: Keep synth running between each packet. 1. Turn off synth after each packet and recalibrate for the next. Requires %rfFrequency != 0 */
        uint8_t          reserved: 6; /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdGenericTxRepeat_Default()                        \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_TX_REPEAT,  \
                                  RCL_Handler_Generic_TxRepeat),\
    .rfFrequency = 2440000000U,                                 \
    .txEntry = NULL,                                            \
    .syncWord = 0x930B51DE,                                     \
    .timePeriod = 0,                                            \
    .numPackets = 0,                                            \
    .config = {                                                 \
        .fsOff = 1,                                             \
        .fsRecal = 0,                                           \
        .reserved = 0,                                          \
    },                                                          \
}
#define RCL_CmdGenericTxRepeat_DefaultRuntime() (RCL_CmdGenericTxRepeat) RCL_CmdGenericTxRepeat_Default()

/**
 *  @brief Generic transmitter test command
 *
 *  Command to transmit continuously, either a modulated signal or continuous wave
 */
struct RCL_CMD_GENERIC_TX_TEST_t {
    RCL_Command     common;
    uint32_t        rfFrequency;   /*!< RF frequency in Hz to program. 0: Do not program frequency */
    RCL_Command_TxPower txPower;   /*!< Transmit power */
    struct {
        uint32_t     txWord: 16;   /*!< Repeated word to transmit */
        uint32_t     whitenMode: 2;/*!< 0. No whitening. 1: Default whitening. 2: PRBS-15. 3: PRBS-32 */
        uint32_t     sendCw: 1;    /*!< 0: Send modulated signal. 1: Send CW */
        uint32_t     fsOff: 1;     /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint32_t     reserved: 12; /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdGenericTxTest_Default()                          \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_TX_TEST,    \
                                  RCL_Handler_Generic_TxTest),  \
    .rfFrequency = 2440000000U,                                 \
    .txPower = {.dBm = 0, .fraction = 0},                       \
    .config = {                                                 \
        .txWord = 0,                                            \
        .whitenMode = 2,                                        \
        .sendCw = 0,                                            \
        .fsOff = 1,                                             \
        .reserved = 0,                                          \
    },                                                          \
}
#define RCL_CmdGenericTxTest_DefaultRuntime() (RCL_CmdGenericTxTest) RCL_CmdGenericTxTest_Default()

#define RCL_CMD_GENERIC_WH_MODE_NONE     0 /*!< config.whitenMode: No whitening */
#define RCL_CMD_GENERIC_WH_MODE_DEFAULT  1 /*!< config.whitenMode: Default whitening */
#define RCL_CMD_GENERIC_WH_MODE_PRBS15   2 /*!< config.whitenMode: PRBS-15 */
#define RCL_CMD_GENERIC_WH_MODE_PRBS32   3 /*!< config.whitenMode: PRBS-32 */

/**
 *  @brief Generic receive command
 *
 *  Command to receive a packet
 */
struct RCL_CMD_GENERIC_RX_t {
    RCL_Command     common;
    uint32_t        rfFrequency;         /*!< RF frequency in Hz to program. 0: Do not program frequency */
    List_List       rxBuffers;           /*!< Linked list of buffers where packets are stored */
    RCL_StatsGeneric *stats;             /*!< Pointer to statistics structure. NULL: Do not store statistics */
    uint32_t        syncWordA;           /*!< Sync word to listen for */
    uint32_t        syncWordB;           /*!< Alternate  Sync word to listen for */
    uint16_t        maxPktLen;           /*!< Maximum packet length, or packet length for fixed length */
    struct {
        uint8_t     repeated: 1;         /*!< 0: End after receiving one packet. 1: Go back to sync search after receiving. */
        uint8_t     disableSyncA: 1;     /*!< 0: Listen for syncWordA. 1: Do not listen for syncWordA */
        uint8_t     disableSyncB: 1;     /*!< 0: Listen for syncWordB. 1: Do not listen for syncWordB */
        uint8_t     discardRxPackets: 1; /*!< 0: Store received packets in rxBuffers. 1: Do not store packets, useful for link tests where checksum result is enough */
        uint8_t     fsOff: 1;            /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint8_t     reserved: 3;         /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdGenericRx_Default()                          \
{                                                           \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_RX,     \
                                  RCL_Handler_Generic_Rx),  \
    .rfFrequency = 2440000000U,                             \
    .rxBuffers = {0},                                       \
    .stats = NULL,                                          \
    .syncWordA = 0x930B51DE,                                \
    .syncWordB = 0x12345678,                                \
    .maxPktLen = 255,                                       \
    .config = {                                             \
        .repeated = 1,                                      \
        .disableSyncA = 0,                                  \
        .disableSyncB = 1,                                  \
        .discardRxPackets = 0,                              \
        .fsOff = 1,                                         \
        .reserved = 0,                                      \
    },                                                      \
}
#define RCL_CmdGenericRx_DefaultRuntime() (RCL_CmdGenericRx) RCL_CmdGenericRx_Default()

struct RCL_STATS_GENERIC_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   timestampValid;        /*!< Returns 1 if %lastTimestamp is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet. */
    uint32_t  lastTimestamp;         /*!< Timestamp of last successfully received packet */
    uint32_t  nRxNok;                /*!< Number of packets received with CRC error */
    uint32_t  nRxOk;                 /*!< Number of correctly received packets */
};

#define RCL_StatsGeneric_Default()  \
{                                   \
    .config = { 0 },                \
    .timestampValid = 0,            \
    .lastRssi = LRF_RSSI_INVALID,   \
}
#define RCL_StatsGeneric_DefaultRuntime() (RCL_StatsGeneric) RCL_StatsGeneric_Default()

/**
 *  @brief Send PBE operation
 *
 *  Send an opcode to the PBE and wait for it to report done
 */
struct RCL_CMD_GENERIC_PBE_OPERATION_t {
    RCL_Command     common;
    uint16_t        pbeOperation;     /*!<  Operation code to send to the PBE */
};

#define RCL_CmdGenericPbeOperation_Default()                        \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_GENERIC_PBE_OPERATION,  \
                                  RCL_Handler_Generic_PbeOperation),\
    .pbeOperation =  PBE_GENERIC_REGDEF_API_OP_PING,                \
}
#define RCL_CmdGenericPbeOperation_DefaultRuntime() (RCL_CmdGenericPbeOperation) RCL_CmdGenericPbeOperation_Default()

/**
 *  @brief NESB transmit command
 *
 *  Command to transmit a packet
 */
struct RCL_CMD_NESB_PTX_t {
    RCL_Command     common;
    uint32_t        rfFrequency;            /*!< RF frequency in Hz to program. 0: Do not program frequency. */
    List_List       txBuffers;              /*!< Linked list of packets to transmit. RCL will pop the first packet when transmitted. */
    List_List       rxBuffers;              /*!< Linked list of buffers for storing received packets. In this case, the ACK. */
    RCL_StatsNesb   *stats;                /*!< Pointer to statistics structure. NULL: Do not store statistics */
    uint32_t        syncWord;               /*!< Sync word to transmit */
    RCL_Command_TxPower txPower;            /*!< Transmit power */
    uint8_t         seqNo;                  /*!< Sequence number to use for next packet */
    uint8_t         maxRetrans;             /*!< Maximum number of retransmissions */
    uint32_t        retransDelay;           /*!< Number of Systim ticks (250 [ns] resolution) from start of transmission of a packet to retransmission.
                                                 If an unattainable retransmission delay is set, the retransmission will start as soon as possible. */
    struct {
        uint8_t     fsOff: 1;               /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint8_t     autoRetransmitMode: 2;  /*!< 0: Do not listen for ACK.
                                                 1: Listen for ACK if transmitted NO_ACK = 0 and retransmit if missing.
                                                 2: Listen for ACK if transmitted NO_ACK = 1 and retransmit if missing.
                                                 3: Always listen for ACK and retransmit if missing. */
        uint8_t     hdrConf: 1;             /*!< 0: Insert NO_ACK field from TX buffer.
                                                 1: Insert SEQ and NO_ACK field from TX buffer. */
        uint8_t     reserved: 4;            /*!< Reserved, set to 0 */
    } config;
};
#define RCL_CmdNesbPtx_Default()                                   \
{                                                                  \
    .common = RCL_Command_Default(RCL_CMDID_NESB_PTX,              \
                                  RCL_Handler_Nesb_Ptx),           \
    .rfFrequency = 2440000000U,                                    \
    .txBuffers = { 0 },                                            \
    .rxBuffers = { 0 },                                            \
    .stats = NULL,                                                 \
    .syncWord = 0x930B51DE,                                        \
    .txPower = {.dBm = 0, .fraction = 0},                          \
    .seqNo = 0,                                                    \
    .maxRetrans = 5,                                               \
    .retransDelay = 100000,                                        \
    .config = {                                                    \
        .fsOff = 1,                                                \
        .autoRetransmitMode = 3,                                   \
        .hdrConf = 1,                                              \
        .reserved = 0,                                             \
    }                                                              \
}
#define RCL_CmdNesbPtx_DefaultRuntime() (RCL_CmdNesbPtx) RCL_CmdNesbPtx_Default()

struct RCL_CONFIG_ADDRESS_t {
    uint32_t    address;                /*!< Address after header */
    uint16_t    crcVal;                 /*!< CRC value (last two bytes if more than 2 CRC bytes) of last successfully received
                                             packet. */
    uint8_t     maxPktLen;              /*!< Packet length for fixed length, maximum packet length for variable
                                             length */
    uint8_t     autoAckMode: 2;         /*!< 0: Disable auto-acknowledgement.
                                             1: Enable auto-acknowledgement if received NO_ACK = 0.
                                             2: Enable auto-acknowledgement if received NO_ACK = 1.
                                             3: Enable auto-acknowledgement regardless of received NO_ACK. */
    uint8_t     varLen: 1;              /*!< 0: Use fixed length given by maxPktLenA in receiver when receiving packets
                                             1: Use variable length in receiver when receiving packets */
    uint8_t     seqValid: 1;            /*!< 0: The status is not valid. Any packet is viewed as new.
                                             1: The status is valid. Only packets with sequence number and CRC different from
                                                the previous one are accepted. */
    uint8_t     seq: 2;                 /*!< Sequence number of last successfully received packet */
    uint8_t     reserved: 2;            /*!< Reserved, set to 0  */
};

#define RCL_ConfigAddress_Default(_addr)       \
{                                              \
    .address = _addr,                          \
    .crcVal = 0,                               \
    .maxPktLen = 255,                          \
    .autoAckMode = 3,                          \
    .varLen = 1,                               \
    .seqValid = 0,                             \
    .seq = 1,                                  \
    .reserved = 0,                             \
}
#define RCL_ConfigAddress_DefaultRuntime(_addr) (RCL_ConfigAddress) RCL_ConfigAddress_Default(_addr)


/**
 *  @brief NESB receive command
 *
 *  Command to receive a packet
 */
struct RCL_CMD_NESB_PRX_t {
    RCL_Command     common;
    uint32_t        rfFrequency;            /*!< RF frequency in Hz to program. 0: Do not program frequency */
    List_List       rxBuffers;              /*!< Linked list of buffers where packets are stored */
    RCL_StatsNesb   *stats;                /*!< Pointer to statistics structure. NULL: Do not store statistics */
    uint32_t        syncWordA;              /*!< Sync word to listen for */
    uint32_t        syncWordB;              /*!< Alternate Sync word to listen for */
    RCL_Command_TxPower txPower;            /*!< Transmit power for ACKs */
    uint8_t         addrLen;                /*!< Length of address after header (0-4 bytes) */
    struct {
        uint8_t     disableSyncA: 1;        /*!< 0: Listen for syncWordA. 1: Do not listen for syncWordA */
        uint8_t     disableSyncB: 1;        /*!< 0: Listen for syncWordB. 1: Do not listen for syncWordB */
        uint8_t     discardRxPackets: 1;    /*!< 0: Store received packets in rxBuffers.
                                                 1: Do not store packets, useful for link tests where checksum result is enough */
        uint8_t     fsOff: 1;               /*!< 0: Keep PLL enabled after command. 1: Turn off FS after command. */
        uint8_t     repeatOk: 1;            /*!< 0: End operation after receiving a packet correctly.
                                                 1: Go back to sync search after receiving a packet correctly */
        uint8_t     repeatNok: 1;           /*!< 0: End operation after receiving a packet with CRC error or address mismatch.
                                                 1: Go back to sync search after receiving a packet with CRC error or address
                                                    mismatch */
        uint8_t     reserved: 2;            /*!< Reserved, set to 0 */
    } config;
    union {
        RCL_ConfigAddress syncWord[2];
        struct {
            RCL_ConfigAddress syncWordACfg;
            RCL_ConfigAddress syncWordBCfg;
        };
    };
};
#define RCL_CmdNesbPrx_Default()                                   \
{                                                                  \
    .common = RCL_Command_Default(RCL_CMDID_NESB_PRX,              \
                                  RCL_Handler_Nesb_Prx),           \
    .rfFrequency = 2440000000U,                                    \
    .rxBuffers = {0},                                              \
    .stats = NULL,                                                 \
    .syncWordA = 0x930B51DE,                                       \
    .syncWordB = 0x570451AE,                                       \
    .txPower = {.dBm = 0, .fraction = 0},                          \
    .addrLen = 4,                                                  \
    .config = {                                                    \
        .disableSyncA = 0,                                         \
        .disableSyncB = 1,                                         \
        .discardRxPackets = 0,                                     \
        .fsOff = 1,                                                \
        .repeatOk = 1,                                             \
        .repeatNok = 0,                                            \
        .reserved = 0,                                             \
    },                                                             \
    .syncWord[0] = RCL_ConfigAddress_Default(0xEFFEABBA),          \
    .syncWord[1] = RCL_ConfigAddress_Default(0xEFFEABBC)           \
}
#define RCL_CmdNesbPrx_DefaultRuntime() (RCL_CmdNesbPrx) RCL_CmdNesbPrx_Default()

struct RCL_STATS_NESB_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   timestampValid;        /*!< Returns 1 if %lastTimestamp is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet. */
    uint32_t  lastTimestamp;         /*!< Timestamp of last successfully received packet */
    uint32_t  nTx;                   /*!< Number of packets or acknowledgements transmitted */
    uint32_t  nRxNok;                /*!< Number of packets that have been received with CRC error */
    uint32_t  nRxOk;                 /*!< Number of packets that have been received with CRC OK and not ignored */
    uint32_t  nRxIgnored;            /*!< Number of packets ignored as retransmissions */
    uint32_t  nRxAddrMismatch;       /*!< Number of packets ignored due to address mismatch */
    uint32_t  nRxBufFull;            /*!< Number of packets that have been received and discarded due to lack of buffer space */
};

#define RCL_StatsNesb_Default()  \
{                                   \
    .config = { 0 },                \
    .timestampValid = 0,            \
    .lastRssi = -128,               \
}
#define RCL_StatsNesb_DefaultRuntime() (RCL_StatsNesb) RCL_StatsNesb_Default()


#endif
