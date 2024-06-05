/*
 * Copyright (c) 2020-2024, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_commands_ble5_h__include
#define ti_drivers_RCL_commands_ble5_h__include

typedef struct RCL_FL_ENTRY_t     RCL_FL_Entry;
typedef struct RCL_FILTER_LIST_t  RCL_FilterList;

typedef struct RCL_ADDR_TYPE_t    RCL_AddrType;
typedef struct RCL_CONN_PARAMS_t  RCL_ConnParams;

typedef struct RCL_CMD_BLE5_ADV_t          RCL_CmdBle5Advertiser;
typedef struct RCL_CMD_BLE5_AUX_ADV_t      RCL_CmdBle5AuxAdvertiser;
typedef struct RCL_CMD_BLE5_PER_ADV_t      RCL_CmdBle5PeriodicAdvertiser;
typedef struct RCL_CMD_BLE5_INITIATOR_t    RCL_CmdBle5Initiator;
typedef struct RCL_CMD_BLE5_SCANNER_t      RCL_CmdBle5Scanner;
typedef struct RCL_CMD_BLE5_PER_SCANNER_t  RCL_CmdBle5PeriodicScanner;
typedef struct RCL_CMD_BLE5_CONNECTION_t   RCL_CmdBle5Connection;
typedef struct RCL_CMD_BLE5_DTM_TX         RCL_CmdBle5DtmTx;
typedef struct RCL_CMD_BLE5_GENERIC_RX_t   RCL_CmdBle5GenericRx;
typedef struct RCL_CMD_BLE5_GENERIC_TX_t   RCL_CmdBle5GenericTx;
typedef struct RCL_CMD_BLE5_TX_TEST_t      RCL_CmdBle5TxTest;

typedef struct RCL_CTX_ADVERTISER_t        RCL_CtxAdvertiser;
typedef struct RCL_CTX_PER_ADVERTISER_t    RCL_CtxPeriodicAdvertiser;
typedef struct RCL_CTX_SCAN_INIT_t         RCL_CtxScanInit;
typedef struct RCL_CTX_PER_SCANNER_t       RCL_CtxPeriodicScanner;
typedef struct RCL_CTX_CONNECTION_t        RCL_CtxConnection;
typedef struct RCL_CTX_GENERIC_RX_t        RCL_CtxGenericRx;
typedef struct RCL_CTX_GENERIC_TX_t        RCL_CtxGenericTx;

typedef struct RCL_STATS_ADV_SCAN_INIT_t   RCL_StatsAdvScanInit;
typedef struct RCL_STATS_CONNECTION_t      RCL_StatsConnection;
typedef struct RCL_STATS_GENERIC_RX_t      RCL_StatsGenericRx;

/**
 * @brief Type for BLE channels
 *
 * 0-39:    BLE channel number, indicates standard BLE whitening
 * 64-103:  Physical channel number; 64 is 2402 MHz, 65 is 2404 MHz, etc. Whitening disabled
 * 128-255: Custom frequency programmed with %RCL_BLE5_setDefaultRfFrequency(); custom whitening.
 *          See %BLE_CUSTOM_FREQ_BM.
 */
typedef uint8_t RCL_Ble5Channel;

/**
 *  @brief PHY returned in status of received packets
 *
 */
typedef enum {
    RCL_Ble5_RxPhy1Mbps = 0,
    RCL_Ble5_RxPhy2Mbps = 1,
    RCL_Ble5_RxPhyCodedS8 = 2,
    RCL_Ble5_RxPhyCodedS2 = 3,
} RCL_Ble5_RxPhy;

/**
 *  @brief Appended packet status field from RX buffer
 *
 */
typedef union {
    struct {
        RCL_Ble5_RxPhy phy       :2;     /*!< Received PHY */
        uint8_t crcError         :1;     /*!< True if packet had CRC error */
        uint8_t ignored          :1;     /*!< True if packet was ignored */
        uint8_t ignoredRpa       :1;     /*!< True if packet should have been ignored due to unknown RPA, but was kept due to rpaMode */
        uint8_t ignoredSyncInfo  :1;     /*!< True if packet should have been ignored due to unknown RPA, but was kept due to periodicSyncEstablishment */
        uint8_t reserved         :2;
    };
    uint8_t value;
} RCL_Ble5_RxPktStatus;

/* Invalid packet status */
#define RCL_BLE5_RX_PKT_STATUS_INVALID 0xFF

/* Do includes after typedefs, as the types are needed in ti/drivers/rcl/handlers/ble5.h */
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/handlers/ble5.h>
#include <ti/drivers/utils/List.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/pbe_ble5_ram_regs.h)

/* Command IDs for BLE commands */
#define RCL_CMDID_BLE5_ADVERTISER              0x1001U
#define RCL_CMDID_BLE5_INITIATOR               0x1002U
#define RCL_CMDID_BLE5_SCANNER                 0x1003U
#define RCL_CMDID_BLE5_CONNECTION              0x1004U
#define RCL_CMDID_BLE5_DTM_TX                  0x1005U
#define RCL_CMDID_BLE5_GENERIC_RX              0x1006U
#define RCL_CMDID_BLE5_GENERIC_TX              0x1007U
#define RCL_CMDID_BLE5_TX_TEST                 0x1008U
#define RCL_CMDID_BLE5_AUX_ADV                 0x1009U
#define RCL_CMDID_BLE5_PERIODIC_ADV            0x100AU
#define RCL_CMDID_BLE5_PERIODIC_SCAN           0x100BU

/**
 * @brief Bit mask indicating the use of a custom frequency
 *
 * If a channel or chanMap parameter has this bit set, the RF frequency used must be programmed
 * with %RCL_BLE5_setDefaultRfFrequency(), and the whitening is initialzed by bits 0-6 of channel
 * or chanMap
 */
#define BLE_CUSTOM_FREQ_BM        0x80U

/**
 *  @brief Filter list entry
 *
 *  Accept or reject filter entry
 */
struct RCL_FL_ENTRY_t {
    union
    {
        struct
        {
            uint16_t enabled      : 1; /*!< 1 if the entry is used; 0 otherwise */
            uint16_t addType      : 1; /*!< Address type of this entry */
            uint16_t duplicateIgn : 1; /*!< 1 to ignore the entry due to duplicate address filtering (scanners only) */
            uint16_t privIgn      : 1; /*!< 1 to ignore the entry due to privacy (initiators only) */
            uint16_t reserved     : 12;/*!< Reserved, set to 0 */
        } ctl;
        uint16_t ctlWord;
    };
    uint16_t address[3];               /*!< Address of entry */
};

/**
 *  @brief Filter list object
 *
 *  Accept or reject filter list
 */
struct RCL_FILTER_LIST_t {
    uint32_t     numEntries;
    RCL_FL_Entry entries[16];
};

/**
 *  @brief Address type
 *
 *  Address type for own address and peer address
 */
struct RCL_ADDR_TYPE_t {
    uint8_t peer :1;     /*!< Address type for peer device (0: public. 1: random) */
    uint8_t own :1;      /*!< Address type for this device (0: public. 1: random) */
    uint8_t reserved: 6; /*!< Reserved, set to 0 */
};

/**
 *  @brief Connection parameters
 *
 *  Connection parameters for AUX_CONNECT_REQ based on received AuxPhy
 */
struct RCL_CONN_PARAMS_t {
    struct
    {
        uint16_t interval;
        uint16_t latency;
        uint16_t timeout;
    } ble2M;
    struct
    {
        uint16_t interval;
        uint16_t latency;
        uint16_t timeout;
    } bleCoded;
};

/**
 *  @brief Advertiser command
 *
 *  Command to run BLE advertiser. The advertisement type is found from the packet type transmitted.
 */
struct RCL_CMD_BLE5_ADV_t {
    RCL_Command  common;
    uint8_t chanMap;              /*!< Channel map. Bit positions 0-2 correspond to channels 37-39; a 1 means channel enabled */
    RCL_Command_TxPower txPower;  /*!< Transmit power */
    uint8_t order;                /*!< Order to run channels. 0: Run in increasing order. 1-5: Other order. Others: Reserved */
    uint8_t highDuty;             /*!< High duty-cycle advertising (directed advertising only) 0: Disabled. 1 Enabled */
    uint32_t connectPktTime;      /*!< Time of received CONNECT_IND or AUX_CONNECT_REQ packet is returned if connection is formed */
    RCL_CtxAdvertiser *ctx;       /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;  /*!< Pointer to statistics structure */
};

#define RCL_CmdBle5Advertiser_Default()                         \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_ADVERTISER,    \
                                  RCL_Handler_BLE5_adv),        \
    .chanMap = 0x7,                                             \
    .txPower = {.dBm = 0, .fraction = 0},                       \
    .order = 0,                                                 \
    .highDuty = 0,                                              \
    .connectPktTime = 0,                                        \
    .ctx = NULL,                                                \
    .stats = NULL,                                              \
}
#define RCL_CmdBle5Advertiser_DefaultRuntime() (RCL_CmdBle5Advertiser) RCL_CmdBle5Advertiser_Default()

/**
 *  @brief Secondary Channel Advertiser command
 *
 *  Command to run BLE advertiser on a secondary channel. The advertisement type is found from the packet type transmitted.
 */
struct RCL_CMD_BLE5_AUX_ADV_t {
    RCL_Command  common;
    RCL_Ble5Channel channel;      /*!< Channel index */
    RCL_Command_TxPower txPower;  /*!< Transmit power */
    uint32_t connectPktTime;      /*!< Time of received CONNECT_IND packet is returned if connection is formed - Not supported in this release. */
    RCL_CtxAdvertiser *ctx;       /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;  /*!< Pointer to statistics structure */
};

#define RCL_CmdBle5AuxAdvertiser_Default()                      \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_AUX_ADV,       \
                                  RCL_Handler_BLE5_aux_adv),    \
    .channel = 0,                                               \
    .txPower = {.dBm = 0, .fraction = 0},                       \
    .ctx = NULL,                                                \
    .stats = NULL,                                              \
}
#define RCL_CmdBle5AuxAdvertiser_DefaultRuntime() (RCL_CmdBle5AuxAdvertiser) RCL_CmdBle5AuxAdvertiser_Default()

/**
 *  @brief Advertiser context
 *
 *  Context for advertiser command
 */
struct RCL_CTX_ADVERTISER_t {
    RCL_FilterList *filterListConn;     /*!< Filter list for initiator packets */
    RCL_FilterList *filterListScan;     /*!< Filter list for scanner packets */
    List_List txBuffers;                /*!< Linked list of packets to transmit: Advertisement followed by scan response */
    List_List rxBuffers;                /*!< Linked list of buffers for storing received packets */
    uint16_t advA[3];                   /*!< Advertiser address of type %addrType.own */
    uint16_t peerA[3];                  /*!< Directed advertising: Peer device address of type %addrType.peer */
    RCL_AddrType addrType;              /*!< Address types */
    uint8_t filterPolicy: 2;            /*!< Filter policy */
    uint8_t privIgnMode: 1;             /*!< Privacy ignore mode. 0: Use filter list only when filter policy says. 1: Use filter list to ignore packets with privIgn bit set for all filter policies */
    uint8_t rpaModePeer: 1;             /*!< RPA mode for peer address. 0: Treat RPA normally. 1: Report packets where advertiser address is an unknown RPA */
    uint8_t acceptAllRpaConnectInd: 1;  /*!< CONNECT_IND RPA treatment. 0: Treat RPA in InitA normally. 1: Accept all RPA in InitA of CONNECT_IND. */
};

#define RCL_CtxAdvertiser_Default() \
{                                   \
    .filterListConn = NULL,         \
    .filterListScan = NULL,         \
    .txBuffers = { 0 },             \
    .rxBuffers = { 0 },             \
    .advA = { 0 },                  \
    .peerA = { 0 },                 \
    .addrType =  { 0 },             \
    .filterPolicy = 0,              \
    .privIgnMode = 0,               \
    .rpaModePeer = 0,               \
    .acceptAllRpaConnectInd = 0     \
}
#define RCL_CtxAdvertiser_DefaultRuntime() (RCL_CtxAdvertiser) RCL_CtxAdvertiser_Default()

/**
 *  @brief Periodic advertiser command
 *
 *  Command to run BLE periodic advertiser.
 */
struct RCL_CMD_BLE5_PER_ADV_t {
    RCL_Command  common;
    RCL_Ble5Channel channel;         /*!< Channel index */
    RCL_Command_TxPower txPower;     /*!< Transmit power */
    RCL_CtxPeriodicAdvertiser *ctx;  /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;     /*!< Pointer to statistics structure */
};

#define RCL_CmdBle5PeriodicAdvertiser_Default()                         \
{                                                                       \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_PERIODIC_ADV,          \
                                  RCL_Handler_BLE5_periodicAdv),        \
    .channel = 0,                                                       \
    .txPower = {.dBm = 0, .fraction = 0},                               \
    .ctx = NULL,                                                        \
    .stats = NULL,                                                      \
}
#define RCL_CmdBle5PeriodicAdvertiser_DefaultRuntime() (RCL_CmdBle5PeriodicAdvertiser) RCL_CmdBle5PeriodicAdvertiser_Default()

/**
 *  @brief Periodic Advertiser context
 *
 *  Context for periodic advertiser command
 */
struct RCL_CTX_PER_ADVERTISER_t {
    List_List txBuffers;       /*!< Linked list of packets to transmit. Only AUX_SYNC_IND and AUX_CHAIN_IND */
    uint32_t accessAddress;    /*!< Access address */
    uint32_t crcInit;          /*!< CRC initialization value (24 bits) */
};

#define RCL_CtxPeriodicAdvertiser_Default() \
{                                           \
    .txBuffers = { 0 },                     \
    .accessAddress = 0,                     \
    .crcInit = 0,                           \
}
#define RCL_CtxPeriodicAdvertiser_DefaultRuntime() (RCL_CtxPeriodicAdvertiser) RCL_CtxPeriodicAdvertiser_Default()

/**
 *  @brief Initiator command
 *
 *  Command to run BLE initiator.
 */
struct RCL_CMD_BLE5_INITIATOR_t {
    RCL_Command common;
    RCL_Ble5Channel channel;      /*!< Channel index */
    RCL_Command_TxPower txPower;  /*!< Transmit power */
    uint16_t maxAuxPtrWaitTime;   /*!< Maximum time to wait for AuxPtr before ending command (1 us units). 0: No limit */
    bool dynamicWinOffset;        /*!< Window offset processing. 0: Fixed. 1: Dynamic */
    bool acceptLegacy : 1;        /*!< Accept legacy advertising. 0: Do not accept. 1: Accept */
    bool acceptExtended : 1;      /*!< Accept extended advertising. 0: Do not accept. 1: Accept */
    uint32_t connectTime;         /*!< For dynamic window offset, wanted connect time is given as input. In all cases, actual connect time is returned. */
    RCL_CtxScanInit *ctx;         /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;  /*!< Pointer to statistics structure */
};

#define RCL_CmdInitiator_Default()                                  \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_INITIATOR,         \
                                  RCL_Handler_BLE5_scan_init),      \
    .channel = 37,                                                  \
    .txPower = {.dBm = 0, .fraction = 0},                           \
    .maxAuxPtrWaitTime = 30000,                                     \
    .dynamicWinOffset = 0,                                          \
    .acceptLegacy = 1,                                              \
    .acceptExtended = 0,                                            \
    .connectTime = 0,                                               \
    .ctx = NULL,                                                    \
    .stats = NULL,                                                  \
}
#define RCL_CmdInitiator_DefaultRuntime() (RCL_CmdBle5Initiator) RCL_CmdInitiator_Default()

/**
 *  @brief Scanner command
 *
 *  Command to run BLE scanner
 */
struct RCL_CMD_BLE5_SCANNER_t {
    RCL_Command common;
    RCL_Ble5Channel channel;       /*!< Channel index */
    RCL_Command_TxPower txPower;   /*!< Transmit power */
    uint16_t maxAuxPtrWaitTime;    /*!< Maximum time to wait for AuxPtr before ending command (1 us units). 0: No limit */
    bool activeScan;               /*!< Scan type. 0: Passive. 1: Active */
    bool acceptLegacy : 1;         /*!< Accept legacy advertising. 0: Do not accept. 1: Accept */
    bool acceptExtended : 1;       /*!< Accept extended advertising. 0: Do not accept. 1: Accept */
    RCL_CtxScanInit *ctx;          /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;   /*!< Pointer to statistics structure */
};

#define RCL_CmdScanner_Default()                                    \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_SCANNER,           \
                                  RCL_Handler_BLE5_scan_init),      \
    .channel = 37,                                                  \
    .txPower = {.dBm = 0, .fraction = 0},                           \
    .maxAuxPtrWaitTime = 20000,                                     \
    .activeScan = 0,                                                \
    .acceptLegacy = 1,                                              \
    .acceptExtended = 0,                                            \
    .ctx = NULL,                                                    \
    .stats = NULL,                                                  \
}
#define RCL_CmdScanner_DefaultRuntime() (RCL_CmdBle5Scanner) RCL_CmdScanner_Default()

/**
 *  @brief Scanner and initiator context
 *
 *  Context for scanner or initiator command
 */
struct RCL_CTX_SCAN_INIT_t {
    RCL_FilterList *filterList;           /*!< Filter list */
    List_List txBuffers;                  /*!< Linked list of packets to transmit: Only CONNECT_IND and AUX_CONNECT_REQ */
    List_List rxBuffers;                  /*!< Linked list of buffers for storing received packets */
    uint16_t ownA[3];                     /*!< Own device address of type %addrType.own */
    uint16_t peerA[3];                    /*!< Initiator: Peer device address of type %addrType.peer */
    RCL_AddrType addrType;                /*!< Address types */
    uint8_t filterPolicy : 1;             /*!< Filter policy */
    uint8_t scanExtFilterPolicy: 1;       /*!< Extended filter policy for scanners */
    uint8_t rpaModeOwn: 1;                /*!< RPA mode for own address. 0: Treat RPA normally. 1: Report packets where target address is an unknown RPA */
    uint8_t rpaModePeer: 1;               /*!< RPA mode for peer address. 0: Treat RPA normally. 1: Report packets where advertiser address is an unknown RPA */
    uint8_t acceptAllRpaConnectRsp: 1;    /*!< AUX_CONNECT_RSP RPA treatment. 0: Treat RPA in TargetA normally. 1: Accept all RPA in TargetA of AUX_CONNECT_RSP - Not supported in this release */
    uint8_t periodicSyncEstablishment: 1; /*!< Synchronization to periodic advertisement. 0: Disabled. 1: Report all packets with SyncInfo present */
    uint16_t initialBackoff;              /*!< Initial backoff value */
    uint8_t backoffUpper;                 /*!< Backoff parameter */
    struct
    {
        uint8_t backOffLastFail : 1;
        uint8_t backOffLastSucceed : 1;
        uint8_t reserved  : 6;
    } backoffStatus;                      /*!< Backoff parameter */
    uint16_t localClockAccuracy;          /*!< Maximum relative local clock error (in ppm) scaled by 2^26 */
    RCL_ConnParams *connParams;           /*!< Pointer to connection parameters structure (LE 2M and LE Coded only). LE 1M parameters are provided in the default CONNECT_IND/AUX_CONNECT_REQ */
};

#define RCL_CtxScanInit_Default()   \
{                                   \
    .filterList = NULL,             \
    .txBuffers = { 0 },             \
    .rxBuffers = { 0 },             \
    .ownA = { 0 },                  \
    .peerA = { 0 },                 \
    .addrType =  { 0 },             \
    .filterPolicy = 0,              \
    .scanExtFilterPolicy = 0,       \
    .rpaModeOwn = 0,                \
    .rpaModePeer = 0,               \
    .acceptAllRpaConnectRsp = 0,    \
    .periodicSyncEstablishment = 0, \
    .initialBackoff = 1,            \
    .backoffUpper = 0,              \
    .backoffStatus = { 0 },         \
    .localClockAccuracy = 3355,     \
    .connParams = NULL,             \
}
#define RCL_CtxScanInit_DefaultRuntime() (RCL_CtxScanInit) RCL_CtxScanInit_Default()

/**
 *  @brief Periodic Scanner command
 *
 *  Command to run BLE periodic scanner
 */
struct RCL_CMD_BLE5_PER_SCANNER_t {
    RCL_Command common;
    RCL_Ble5Channel channel;       /*!< Channel index */
    RCL_Command_TxPower txPower;   /*!< Transmit power */
    uint16_t maxAuxPtrWaitTime;    /*!< Maximum time to wait for AuxPtr before ending command (1 us units). 0: No limit */
    RCL_CtxPeriodicScanner *ctx;   /*!< Pointer to context structure */
    RCL_StatsAdvScanInit *stats;   /*!< Pointer to statistics structure */
};

#define RCL_CmdPeriodicScanner_Default()                            \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_PERIODIC_SCAN,     \
                                  RCL_Handler_BLE5_periodicScan),   \
    .channel = 37,                                                  \
    .txPower = {.dBm = 0, .fraction = 0},                           \
    .maxAuxPtrWaitTime = 20000,                                     \
    .ctx = NULL,                                                    \
    .stats = NULL,                                                  \
}
#define RCL_CmdPeriodicScanner_DefaultRuntime() (RCL_CmdBle5PeriodicScanner) RCL_CmdPeriodicScanner_Default()

/**
 *  @brief Periodic scanner context
 *
 *  Context for periodic scanner command
 */
struct RCL_CTX_PER_SCANNER_t {
    List_List rxBuffers;                  /*!< Linked list of buffers for storing received packets */
    uint16_t localClockAccuracy;          /*!< Maximum relative local clock error (in ppm) scaled by 2^26 */
    uint32_t accessAddress;               /*!< Access address */
    uint32_t crcInit;                     /*!< CRC initialization value (24 bits) */
};

#define RCL_CtxPeriodicScanner_Default()   \
{                                          \
    .rxBuffers = { 0 },                    \
    .localClockAccuracy = 3355,            \
    .accessAddress = 0,                    \
    .crcInit = 0,                          \
}
#define RCL_CtxPeriodicScanner_DefaultRuntime() (RCL_CtxPeriodicScanner) RCL_CtxPeriodicScanner_Default()

/**
 *  @brief Statistics structure for advertiser, scanner and initiator
 *
 *  Statistics for advertiser, scanner or initiator command
 */
struct RCL_STATS_ADV_SCAN_INIT_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   timestampValid;        /*!< Returns 1 if %lastTimestamp is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet */
    uint32_t  lastTimestamp;         /*!< Timestamp of last successfully received packet */
    uint16_t  nRxNok;                /*!< Number of packets received with CRC error */
    uint16_t  nRxIgnored;            /*!< Number of packets to be ignored received */
    uint16_t  nRxOk;                 /*!< Number of correctly received, accepted packets */
    uint8_t   nRxFifoFull;           /*!< Number of packets received which could not be stored */
    uint8_t   nTx;                   /*!< Number of packets transmitted */
};

#define RCL_StatsAdvScanInit_Default()  \
{                                       \
    .config = { 0 },                    \
    .timestampValid = 0,                \
    .lastRssi = LRF_RSSI_INVALID,       \
}
#define RCL_StatsAdvScanInit_DefaultRuntime() (RCL_StatsAdvScanInit) RCL_StatsAdvScanInit_Default()

/**
 *  @brief Connection command
 *
 *  Command to run connection event as central or peripheral
 */
struct RCL_CMD_BLE5_CONNECTION_t {
    RCL_Command common;
    RCL_Ble5Channel channel;      /*!< Channel index */
    RCL_Command_TxPower txPower;  /*!< Transmit power */
    uint16_t relRxTimeoutTime;    /*!< Peripheral only: Time before timing out the first packet of the event (0.25 us units). 0: No timeout. */
    RCL_CtxConnection *ctx;       /*!< Pointer to context structure */
    RCL_StatsConnection *stats;   /*!< Pointer to statistics structure */
};

#define RCL_CmdBle5Connection_Default()                             \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_CONNECTION,        \
                                  RCL_Handler_BLE5_conn),           \
    .channel = 0,                                                   \
    .txPower = {.dBm = 0, .fraction = 0},                           \
    .ctx = NULL,                                                    \
    .stats = NULL,                                                  \
}
#define RCL_CmdBle5Connection_DefaultRuntime() (RCL_CmdBle5Connection) RCL_CmdBle5Connection_Default()

/**
 *  @brief Connection context
 *
 *  Context for a connection
 */
struct RCL_CTX_CONNECTION_t {
    List_List txBuffers;       /*!< Linked list of packets to transmit. RCL will pop packets that have been ACKed */
    List_List rxBuffers;       /*!< Linked list of buffers for storing received packets */
    bool      isPeripheral;    /*!< 0: Run as central. 1: Run as peripheral */
    uint16_t  seqStat;         /*!< Sequencer status. Use default initialization for a new connection and keep unchanged between connection events on the same connection. */
    uint32_t  accessAddress;   /*!< Access address */
    uint32_t  crcInit;         /*!< CRC initialization value (24 bits) */
};

#define _INIT_SEQSTAT (PBE_BLE5_RAM_SEQSTAT_LASTRXSN_M | \
                       PBE_BLE5_RAM_SEQSTAT_LASTTXSN_M | \
                       PBE_BLE5_RAM_SEQSTAT_FIRSTPKT_M )

#define RCL_CtxConnection_Default() \
{                                   \
    .txBuffers = { 0 },             \
    .rxBuffers = { 0 },             \
    .isPeripheral = 0,              \
    .seqStat = _INIT_SEQSTAT,       \
    .accessAddress = 0,             \
    .crcInit = 0,                   \
}
#define RCL_CtxConnection_DefaultRuntime() (RCL_CtxConnection) RCL_CtxConnection_Default()

/**
 *  @brief Statistics structure for connection
 *
 *  Statistics for connection command
 */
struct RCL_STATS_CONNECTION_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   anchorValid;           /*!< Returns 1 if %anchorPoint is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet */
    uint32_t  anchorPoint;           /*!< Peripheral only: Timestamp of first received packet */
    uint8_t   nTxDone;               /*!< Number of TX buffers finished because ACK is received */
    uint8_t   nTxAck;                /*!< Number of ACKs received on transmitted packets */
    uint8_t   nTxCtlAck;             /*!< Number of ACKs received on transmitted control packets */
    uint8_t   nTxCtl;                /*!< Number of control packets transmitted */
    uint8_t   nTxRetrans;            /*!< Number of packets retransmitted */
    uint8_t   nRxNok;                /*!< Number of packets received with CRC error */
    uint8_t   nRxIgnored;            /*!< Number of packets to be ignored received */
    uint8_t   nRxEmpty;              /*!< Number of empty packets received */
    uint8_t   nRxFifoFull;           /*!< Number of packets received which could not be stored */
    uint8_t   nRxOk;                 /*!< Number of correctly received, accepted packets */
    uint8_t   nTx;                   /*!< Number of packets transmitted */
    uint8_t   nRxCtl;                /*!< Number of control packets received */
    uint8_t   nRxCtlAck;             /*!< Number of ACKs transmitted on received control packets */
};

#define RCL_StatsConnection_Default()   \
{                                       \
    .config = { 0 },                    \
    .anchorValid = 0,                   \
    .lastRssi = LRF_RSSI_INVALID,       \
}
#define RCL_StatsConnection_DefaultRuntime() (RCL_StatsConnection) RCL_StatsConnection_Default()

/**
 *  @brief DTM TX command
 *
 *  Command to send BLE direct test mode packets
 */
struct RCL_CMD_BLE5_DTM_TX {
    RCL_Command common;
    RCL_Ble5Channel channel;      /*!< Channel index */
    RCL_Command_TxPower txPower;  /*!< Transmit power */
    uint8_t   pduHeader;          /*!< PDU header to transmit; payload is given according to BLE DTM spec */
    uint8_t   pduLength;          /*!< PDU length */
    uint8_t   cteInfo;            /*!< CTE info; decides length of CTE. Ignored if bit #5 of %pduHeader is 0. Not supported in this version. */
    uint16_t  periodUs;           /*!< Time between start of each packet in 1 us units */
    uint16_t  numPackets;         /*!< Number of packets to transmit. 0: Transmit indefinitely until command times out or is stopped. */
};

#define RCL_CmdBle5DtmTx_Default()                          \
{                                                           \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_DTM_TX,    \
                                  RCL_Handler_BLE5_dtmTx),  \
    .channel = 64,                                          \
    .txPower = {.dBm = 0, .fraction = 0},                   \
    .pduHeader = 0x00,                                      \
    .pduLength = 37,                                        \
    .cteInfo = 0x14,                                        \
    .periodUs = 625,                                        \
    .numPackets = 0,                                        \
}
#define RCL_CmdBle5DtmTx_DefaultRuntime() (RCL_CmdBle5DtmTx) RCL_CmdBle5DtmTx_Default()

/**
 *  @brief Generic RX command
 *
 *  Command to receive generic BLE packets
 */
struct RCL_CMD_BLE5_GENERIC_RX_t {
    RCL_Command common;
    RCL_Ble5Channel channel;       /*!< Channel index */
    RCL_CtxGenericRx *ctx;         /*!< Pointer to context structure */
    RCL_StatsGenericRx *stats;     /*!< Pointer to statistics structure */
};

#define RCL_CmdBle5GenericRx_Default()                              \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_GENERIC_RX,        \
                                  RCL_Handler_BLE5_genericRx),      \
    .channel = 64,                                                  \
    .ctx = NULL,                                                    \
    .stats = NULL,                                                  \
}
#define RCL_CmdBle5GenericRx_DefaultRuntime() (RCL_CmdBle5GenericRx) RCL_CmdBle5GenericRx_Default()

/**
 *  @brief Generic RX context
 *
 *  Context for generic RX command
 */
struct RCL_CTX_GENERIC_RX_t {
    List_List rxBuffers;       /*!< Linked list of buffers for storing received packets */
    uint32_t  accessAddress;   /*!< Access address */
    uint32_t  crcInit;         /*!< CRC initialization value (24 bits) */
    uint8_t   maxPktLen;       /*!< Maximum payload length of received packets */
    struct {
        uint8_t  repeated: 1;         /*!< 0: End after receiving one packet. 1: Go back to sync search after receiving. */
        uint8_t  disableSync: 1;      /*!< 0: Listen for sync 1: Do not listen for sync */
        uint8_t  discardRxPackets: 1; /*!< 0: Store received packets in rxBuffers. 1: Do not store packets, useful for link tests where CRC result is enough */
        uint8_t  reserved: 4;         /*!< Reserved, set to 0 */
    } config;
};

#define RCL_CtxGenericRx_Default()  \
{                                   \
    .rxBuffers = { 0 },             \
    .accessAddress = 0x71764129U,   \
    .crcInit = 0x555555,            \
    .config = {                     \
        .repeated = 1,              \
        .disableSync = 0,           \
        .discardRxPackets = 1,      \
        .reserved = 0,              \
    },                              \
}
#define RCL_CtxGenericRx_DefaultRuntime() (RCL_CtxGenericRx) RCL_CtxGenericRx_Default()

/**
 *  @brief Statistics structure for generic RX
 *
 *  Statistics for generic RX command
 */
struct RCL_STATS_GENERIC_RX_t {
    struct
    {
        uint8_t accumulate : 1;      /*!< 0: Reset counters to 0 at start of command. 1: Add to incoming value of counters. */
        uint8_t activeUpdate : 1;    /*!< 0: Update only at end of command. 1: Update after receiving or transmitting packets. */
        uint8_t reserved : 6;        /*!< Reserved, set to 0 */
    } config;                        /*!< Configuration provided to RCL */
    uint8_t   timestampValid;        /*!< Returns 1 if %lastTimestamp is updated; 0 otherwise */
    int8_t    lastRssi;              /*!< RSSI of last received packet */
    uint32_t  lastTimestamp;         /*!< Timestamp of last successfully received packet */
    uint16_t  nRxNok;                /*!< Number of packets received with CRC error */
    uint16_t  nRxOk;                 /*!< Number of correctly received, accepted packets */
    uint8_t   nRxFifoFull;           /*!< Number of packets received which could not be stored */
};

#define RCL_StatsGenericRx_Default()    \
{                                       \
    .config =  { 0 },                   \
    .timestampValid = 0,                \
    .lastRssi = LRF_RSSI_INVALID,       \
}
#define RCL_StatsGenericRx_DefaultRuntime() (RCL_StatsGenericRx) RCL_StatsGenericRx_Default()

/**
 *  @brief Generic TX command
 *
 *  Command to transmit a generic BLE packet with no restriction on packet contents
 */
struct RCL_CMD_BLE5_GENERIC_TX_t {
    RCL_Command common;
    RCL_Ble5Channel channel;       /*!< Channel index */
    RCL_Command_TxPower txPower;   /*!< Transmit power */
    RCL_CtxGenericTx *ctx;         /*!< Pointer to context structure */
};

#define RCL_CmdBle5GenericTx_Default()                              \
{                                                                   \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_GENERIC_TX,        \
                                  RCL_Handler_BLE5_genericTx),      \
    .channel = 64,                                                  \
    .txPower = {.dBm = 0, .fraction = 0},                           \
    .ctx = NULL,                                                    \
}
#define RCL_CmdBle5GenericTx_DefaultRuntime() (RCL_CmdBle5GenericTx) RCL_CmdBle5GenericTx_Default()

/**
 *  @brief Generic TX context
 *
 *  Context for generic TX command
 */
struct RCL_CTX_GENERIC_TX_t {
    List_List txBuffers;            /*!< Linked list of packets to transmit. First packet will be transmitted and consumed. */
    uint32_t  accessAddress;        /*!< Access address */
    uint32_t  crcInit;              /*!< CRC initialization value (24 bits) */
};

#define RCL_CtxGenericTx_Default()  \
{                                   \
    .txBuffers = { 0 },             \
    .accessAddress = 0x71764129U,   \
    .crcInit = 0x555555,            \
}
#define RCL_CtxGenericTx_DefaultRuntime() (RCL_CtxGenericTx) RCL_CtxGenericTx_Default()

/**
 *  @brief BLE5 transmitter test command
 *
 *  Command to transmit continuously, either a modulated signal or continuous wave
 */
struct RCL_CMD_BLE5_TX_TEST_t {
    RCL_Command  common;
    uint8_t      channel;           /*!< Channel index */
    RCL_Command_TxPower txPower;    /*!< Transmit power */
    uint16_t     txWord;            /*!< Repeated word to transmit */
    struct {
        uint8_t  whitenMode: 2;     /*!< 0. No or default whitening. 1: PRBS-9. 2: PRBS-15. 3: PRBS-32 */
        uint8_t  sendCw: 1;         /*!< 0: Send modulated signal. 1: Send CW */
        uint8_t  reserved: 5;       /*!< Reserved, set to 0 */
    } config;
};

#define RCL_CmdBle5TxTest_Default()                             \
{                                                               \
    .common = RCL_Command_Default(RCL_CMDID_BLE5_TX_TEST,       \
                                  RCL_Handler_Ble5_txTest),     \
    .channel = 64,                                              \
    .txPower = {.dBm = 0, .fraction = 0},                       \
    .txWord = 0,                                                \
    .config = {                                                 \
        .whitenMode = 2,                                        \
        .sendCw = 0,                                            \
        .reserved = 0,                                          \
    },                                                          \
}
#define RCL_CmdBle5TxTest_DefaultRuntime() (RCL_CmdBle5TxTest) RCL_CmdBle5TxTest_Default()

#define RCL_CMD_BLE5_WH_MODE_DEFAULT  0 /*!< config.whitenMode: Default (or no) whitening */
#define RCL_CMD_BLE5_WH_MODE_PRBS9    1 /*!< config.whitenMode: PRBS-9  */
#define RCL_CMD_BLE5_WH_MODE_PRBS15   2 /*!< config.whitenMode: PRBS-15 */
#define RCL_CMD_BLE5_WH_MODE_PRBS32   3 /*!< config.whitenMode: PRBS-32 */

#endif
