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
/*
 *  ======== ble5.c ========
 */

#include <stdint.h>
#include <stdlib.h>

#include <ti/devices/DeviceFamily.h>

#include <ti/log/Log.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Profiling.h>

#include <ti/drivers/rcl/hal/hal.h>
#include <ti/drivers/rcl/commands/ble5.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/utils/Random.h>

#include DeviceFamily_constructPath(inc/pbe_ble5_ram_regs.h)
#include DeviceFamily_constructPath(inc/hw_lrfdtxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/pbe_ble5_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble5_regdef_regs.h)

#define RCL_HANDLER_BLE5_RESTORE_NONE           0x0000
#define RCL_HANDLER_BLE5_RESTORE_MODCTRL        0x0001
#define RCL_HANDLER_BLE5_RESTORE_WHITEN_POLY    0x0002

typedef struct
{
    RCL_Buffer_TxBuffer *lastEnteredTxBuffer;
    uint8_t *lastTxHdr;
    bool     isConnBuffer;
    uint16_t numBytes;
    uint16_t numBuffers;
} RCL_TxBufferInfo;

typedef struct
{
    uint8_t    pktLen;
    uint8_t    chIndex: 6;
    uint8_t    ca: 1;
    uint8_t    offsetUnits: 1;
    uint16_t   auxOffset: 13;
    uint16_t   auxPhy: 3;
    uint8_t    ptrIndex;
    uint8_t   *auxOffsetLowFifoPtr;
    uint8_t   *auxOffsetHighFifoPtr;
    uint8_t   *auxChCaOffsetUnitsFifoPtr;
    uint8_t    numPrimaryChPackets;
    bool       auxPtrPresent;
} RCL_AuxPtrInfo;

struct
{
    struct {
        uint32_t          defaultRfFrequency;
        bool              accessAddressModification;
        RCL_CommandStatus endStatus;
        bool              activeUpdate;
        RCL_Ble5Channel   channel;
        uint16_t          rxFifoSz;
        uint16_t          txFifoSz;
        uint16_t          phyFeatures;
        uint16_t          fifoCfg;
        int8_t            filterListUpdateIndex;
        RCL_MultiBuffer  *curBuffer;
        uint32_t          timestampAdjust;
        RCL_FilterList   *updatableFilterList;
        RCL_AuxPtrInfo    auxPtrInfo;
        RCL_TxBufferInfo  txBufferInfo;
    } common;
    union {
        struct {
            uint8_t       chanMap;
            bool          runRx;
            bool          gracefulStopObserved;
            bool          isExtAdv;
            bool          switchPhy;
            bool          auxScanReqReceived;
            uint8_t       auxScanRspLen;
            uint8_t       auxAdvIndLen;
        } adv;
        struct {
            bool          runRx;
            bool          gracefulStopObserved;
            bool          sendAuxAdv;
            bool          auxScanReqReceived;
            uint8_t       auxScanRspLen;
            uint8_t       auxAdvIndLen;
        } auxAdv;
        struct {
            bool          gracefulStopObserved;
        } perAdv;
        struct {
            bool          initiator;
            bool          dynamicWinOffset;
            bool          switchPhy;
            bool          followAuxPtr;
            bool          isExtAdv;
            uint8_t       advPktLen;
            uint16_t     *winOffsetFifoPtr;
            uint16_t     *winOffsetBufferPtr;
            uint16_t      transmitWindowOffset;
            uint16_t     *intervalFifoPtr;
            uint16_t      connectInterval;
            uint16_t      filterListInvertMask;
        } scanInit;
        struct {
            bool          followAuxPtr;
        } perScan;
        struct {
            bool          isPeripheral;
        } conn;
        struct {
            uint16_t      demc1be0;
            uint16_t      demc1be1;
            uint16_t      demc1be2;
#ifdef DeviceFamily_CC27XX
            uint16_t      demc1be12;
#endif
            bool          restoreThresh;
        } genericRx;
        struct {
            uint16_t      storedPbeTimPre;
        } dtmTx;
        struct {
            uint8_t       restoreSelector;
            uint32_t      storedWhitenPoly;
        } txTest;

    };
} ble5HandlerState;

uint32_t RCL_Handler_BLE5_getRandomNumber(void);
static void RCL_Handler_BLE5_updateRxCurBufferAndFifo(List_List *rxBuffers);
static uint16_t RCL_Handler_BLE5_findWhitenInit(RCL_Ble5Channel channel);
static uint32_t RCL_Handler_BLE5_findRfFreq(RCL_Ble5Channel channel);
static RCL_Ble5Channel RCL_Handler_BLE5_findAdvChannel(uint32_t advMap, uint32_t order);
static RCL_CommandStatus RCL_Handler_BLE5_setPhy(uint16_t phyFeatures);
static RCL_CommandStatus  RCL_Handler_BLE5_findPbeErrorEndStatus(uint16_t pbeEndStatus);
static uint32_t RCL_Handler_BLE5_updateTxBuffers(List_List *txBuffers,
                                                 uint32_t maxBuffers,
                                                 RCL_TxBufferInfo *txBufferInfo,
                                                 bool retransPossible);
static void RCL_Handler_BLE5_commitPacket(RCL_MultiBuffer *curBuffer, uint32_t numBytes);
static uint32_t RCL_Handler_BLE5_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate);
static bool RCL_Handler_BLE5_initAdvScanInitStats(RCL_StatsAdvScanInit *stats, uint32_t startTime);
static void RCL_Handler_BLE5_updateAdvScanInitStats(RCL_StatsAdvScanInit *stats, uint32_t startTime);
static bool RCL_Handler_BLE5_initConnStats(RCL_StatsConnection *stats, uint32_t startTime);
static void RCL_Handler_BLE5_updateConnStats(RCL_StatsConnection *stats, uint32_t startTime);
static bool RCL_Handler_BLE5_initGenericRxStats(RCL_StatsGenericRx *stats, uint32_t startTime);
static void RCL_Handler_BLE5_updateGenericRxStats(RCL_StatsGenericRx *stats, uint32_t startTime);
static void RCL_Handler_BLE5_InitializeFilterList(RCL_FilterList *filterList, uint32_t *pbeFilterList, uint32_t invertMask);
static void RCL_Handler_BLE5_updateFilterListEntry(RCL_FilterList *filterList, uint32_t *pbeFilterList, uint32_t invertMask, uint32_t index);
static uint32_t RCL_Handler_BLE5_prepareConnectTime(uint32_t *connectTime, uint32_t referenceTime, uint32_t interval);
static uint32_t RCL_Handler_BLE5_findConnectTime(uint32_t initialConnectTime, uint32_t referenceTime, uint32_t interval);
static uint32_t RCL_Handler_BLE5_findPacketDuration(uint32_t length, uint16_t phyFeatures);
static uint16_t RCL_Handler_BLE5_findRxSyncOverhead(uint16_t phyFeatures);
static uint32_t RCL_Handler_BLE5_findNumExtraBytes(uint32_t fifoCfg);
static void RCL_Handler_BLE5_getAuxPtrFromTxBuffer(RCL_Buffer_TxBuffer *curBuffer, RCL_AuxPtrInfo *auxPtrInfo, uint8_t offset);
static bool RCL_Handler_BLE5_updateAuxPtr(RCL_AuxPtrInfo *auxPtr, uint32_t packetDuration, uint8_t chanMap, bool switchPhy);
static void RCL_Handler_BLE5_readAuxPtrFromRxBuffer(uint32_t *data32, RCL_AuxPtrInfo *auxPtrInfo);
static void RCL_Handler_BLE5_updateBackoffParams(RCL_CtxScanInit * ctx, uint16_t endCause);
static uint8_t RCL_Handler_BLE5_checkExtHdrField(uint8_t extHdrFlags, uint8_t fieldMask);



/* First BLE data channel number */
#define BLE_DATA_CHAN_MIN      0U
/* Last BLE data channel number */
#define BLE_DATA_CHAN_MAX      36U
/* Frequency of first BLE data channel */
#define BLE_DATA_CHAN_BASE     2404000000U
/* BLE channel spacing */
#define BLE_CHAN_SPACE         2000000U
/* Lower advertising channel */
#define BLE_ADV_CHAN_LO        37U
/* Middle advertising channel */
#define BLE_ADV_CHAN_MID       38U
/* Upper advertising channel */
#define BLE_ADV_CHAN_HI        39U
/* First BLE PHY channel number */
#define BLE_PHY_CHAN_MIN       64U
/* Last BLE PHY channel number */
#define BLE_PHY_CHAN_MAX       103U
/* Frequency of lower advertising channel */
#define BLE_ADV_CHAN_LO_FREQ   2402000000U
/* Frequency of middle advertising channel */
#define BLE_ADV_CHAN_MID_FREQ  2426000000U
/* Frequency of upper advertising channel */
#define BLE_ADV_CHAN_HI_FREQ   2480000000U
/* Interval between advertising packets when using high duty cycle advertising */
#define HIGH_DUTY_CYCLE_INTERVAL RCL_SCHEDULER_SYSTIM_US(1250)
/* Transmit delay between primary channel extended advertising packets */
#define EXT_ADV_INTERVAL_US 330U
/* Transmit delay associated with phy switching */
#define EXT_ADV_PHY_SWITCHING_DELAY_US 120U
/* See RCL-513.To be characterized */
#define RX_START_OVERHEAD      240U
#define RX_SYNC_OVERHEAD_1MBPS 164U
#define RX_SYNC_OVERHEAD_2MBPS 120U
#define RX_SYNC_OVERHEAD_CODED 1600U
/* Express systim units in terms of offset units */
#define BLE_convertSystimUnitsToOffsetUnits(x, offsetUnit) \
((((uint32_t)(x) >> 2) + offsetUnit - 1) / ((uint32_t)(offsetUnit)))
/* Time from start of preamble to SYSTIM capture at sync found */
#define TIMESTAMP_ADJUST_1MBPS 267U
/* Time from start of preamble to SYSTIM capture at sync found */
#define TIMESTAMP_ADJUST_2MBPS 148U
/* Time from start of preamble to SYSTIM capture at sync found */
#define TIMESTAMP_ADJUST_CODED 1673U
/* Access address for advertising */
#define ADV_ACCESS_ADDRESS 0x8E89BED6U
/* Access address for DTM packets */
#define DTM_ACCESS_ADDRESS (~ADV_ACCESS_ADDRESS)
/* CRC initialization for advertising */
#define ADV_CRC_INIT (0x555555U << 8)
/* Maximum exponent of backoff algorithm */
#define BACKOFF_UPPER_MAX      8U
/* Timing of packets: */
/* Duration of a 1 Mbps packet with length = 0 */
#define BLE_1MBPS_PACKET_BASE_TIME RCL_SCHEDULER_SYSTIM_US(80)
/* Duration of an additional byte for 1 Mbps */
#define BLE_1MBPS_TIME_PER_BYTE RCL_SCHEDULER_SYSTIM_US(8)
/* Duration of a 2 Mbps packet with length = 0 */
#define BLE_2MBPS_PACKET_BASE_TIME RCL_SCHEDULER_SYSTIM_US(44)
/* Duration of an additional byte for 2 Mbps */
#define BLE_2MBPS_TIME_PER_BYTE RCL_SCHEDULER_SYSTIM_US(4)
/* Duration of a 125 kbps packet with length = 0 */
#define BLE_CODED_S8_PACKET_BASE_TIME RCL_SCHEDULER_SYSTIM_US(720)
/* Duration of an additional byte for 125 kbps */
#define BLE_CODED_S8_TIME_PER_BYTE RCL_SCHEDULER_SYSTIM_US(64)
/* Duration of a 500 kbps packet with length = 0 */
#define BLE_CODED_S2_PACKET_BASE_TIME RCL_SCHEDULER_SYSTIM_US(462)
/* Duration of an additional byte for 500 kbps */
#define BLE_CODED_S2_TIME_PER_BYTE RCL_SCHEDULER_SYSTIM_US(16)
/* Interframe space */
#define BLE_T_IFS RCL_SCHEDULER_SYSTIM_US(150)
/* Header length in bytes */
#define BLE_HEADER_LENGTH 2
/* Number of padding bytes */
#define BLE_NUM_PAD 3
/* CRC length in bytes */
#define BLE_CRC_LENGTH 3
/* Maximum length of a BLE packet */
#define BLE_MAX_PKT_LEN 255
/* Maximum length of a legacy advertising packet */
#define BLE_ADV_LEGACY_MAX_PKT_LEN 37
/* Maximum length of an extended advertising packet */
#define BLE_ADV_EXTENDED_MAX_PKT_LEN 255
/* Length of an AUX_SCAN_REQ */
#define BLE_ADV_AUX_SCAN_REQ_PKT_LEN 12
/* Clock Accuracy scale factor */
#define BLE_CLK_ACCURACY_SCALE_FACTOR 26
/* 50 PPM clock accuracy scaled by 2^26 */
#define BLE_SCALED_CLK_ACCURACY_50PPM 3355
/* 500 PPM clock accuracy scaled by 2^26 */
#define BLE_SCALED_CLK_ACCURACY_500PPM 33550

/* Bit controlling advertiser filter policy for scanning */
#define BLE_ADV_FILTER_POLICY_SCAN 1
/* Bit controlling advertiser filter policy for connection */
#define BLE_ADV_FILTER_POLICY_CONN 2

/* Number of filter list entries in PBE */
#define PBE_NUM_FILTER_ENTRIES 16U

/* PHY feature definitions - must match the setup */
#define BLE_PHY_FEATURE_PHY_1MBPS 0
#define BLE_PHY_FEATURE_PHY_2MBPS 1
#define BLE_PHY_FEATURE_PHY_CODED 2
#define BLE_PHY_FEATURE_PHY_MASK  0x0003
#define BLE_PHY_FEATURE_CODING_S8 0
#define BLE_PHY_FEATURE_CODING_S2 4
#define BLE_PHY_FEATURE_CODING_MASK  0x0004

/* DTM packet header definition */
#define BLE_DTM_PAYLOAD_TYPE_PRBS9                  0x00
#define BLE_DTM_PAYLOAD_TYPE_11110000               0x01
#define BLE_DTM_PAYLOAD_TYPE_10101010               0x02
#define BLE_DTM_PAYLOAD_TYPE_PRBS15                 0x03
#define BLE_DTM_PAYLOAD_TYPE_11111111               0x04
#define BLE_DTM_PAYLOAD_TYPE_00000000               0x05
#define BLE_DTM_PAYLOAD_TYPE_00001111               0x06
#define BLE_DTM_PAYLOAD_TYPE_01010101               0x07

/** Polynomial to use for PRBS9 data */
#define RCL_HANDLER_BLE5_PRBS9_POLY                 0x08800000
#define RCL_HANDLER_BLE5_PRBS9_INIT                 0x0000001F
/** Polynomial to use for PRBS15 data */
#define RCL_HANDLER_BLE5_PRBS15_POLY                0x00060000
#define RCL_HANDLER_BLE5_PRBS15_INIT                0x00003FFF
/** Polynomial to use for PRBS32 data */
#define RCL_HANDLER_BLE5_PRBS32_POLY                0x00400007
#define RCL_HANDLER_BLE5_PRBS32_INIT                0x00005555
#define RCL_HANDLER_BLE5_PRBS_SYNC                  0xAB05FA1C

/* Transmit window timing constants */
/* Payload length of a CONNECT_IND or AUX_CONNECT_REQ in bytes */
#define BLE_CONNECT_MSG_LEN                         34U
/* Payload length of an AUX_CONNECT_RSP in bytes */
#define BLE_AUX_CONNECT_RSP_MSG_LEN                 14U
/* Position of WinSize in a CONNECT_IND or AUX_CONNECT_REQ */
#define BLE_WIN_SIZE_POS                            19U
/* Position of WinOffset in a CONNECT_IND or AUX_CONNECT_REQ */
#define BLE_WIN_OFFSET_POS                          20U
/* Position of Interval in a CONNECT_IND or AUX_CONNECT_REQ */
#define BLE_INTERVAL_POS                            22U
/* Position of Latency in a CONNECT_IND or AUX_CONNECT_REQ */
#define BLE_LATENCY_POS                             24U
/* Position of Timeout in a CONNECT_IND or AUX_CONNECT_REQ */
#define BLE_TIMEOUT_POS                             26U
/* Transmit window delay for legacy advertising */
#define BLE_TRANSMIT_WINDOW_DELAY_LEGACY            RCL_SCHEDULER_SYSTIM_US(1250)
/* Transmit window delay for extended advertising */
#define BLE_TRANSMIT_WINDOW_DELAY_EXT_UNCODED       RCL_SCHEDULER_SYSTIM_US(2500)
#define BLE_TRANSMIT_WINDOW_DELAY_EXT_CODED         RCL_SCHEDULER_SYSTIM_US(3750)
/* Connection interval unit */
#define BLE_CONNECT_INT_UNIT                        RCL_SCHEDULER_SYSTIM_US(1250)
/* Number of sub-intervals per connection interval unit used in connection setup */
#define RCL_BLE5_CONNECT_INT_SUB_DIV                4
/* Duration of a sub-interval */
#define RCL_BLE5_CONNECT_SUB_INT                    (BLE_CONNECT_INT_UNIT / RCL_BLE5_CONNECT_INT_SUB_DIV)

/* LRFD runs on a 48 MHz clock */
#define LRF_CLOCK_TICKS_PER_US                      48

/* Offset units for Extended advertising */
#define BLE_AUX_OFFSET_300_US                       300U
#define BLE_AUX_OFFSET_30_US                        30U

/* Bitmask for the advertiser's device address flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_ADVA_BM                 0x01
/* Bitmask for the target's device address flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_TARGETA_BM              0x02
/* Bitmask for the CTEInfo flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_CTEINFO_BM              0x04
/* Bitmask for the ADI flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_ADI_BM                  0x08
/* Bitmask for the AuxPtr flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_AUXPTR_BM               0x10
/* Bitmask for the SyncInfo flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_SYNCINFO_BM             0x20
/* Bitmask for the Tx Power flag in the Extended Header Flags byte */
#define BLE_EXTENDED_HEADER_TXPOWER_BM              0x40

/* Length in bytes of the advertiser's device address */
#define BLE_EXTENDED_HEADER_ADVA_LEN                6
/* Length in bytes of the target's device address */
#define BLE_EXTENDED_HEADER_TARGETA_LEN             6
/* Length in bytes of the CTEInfo field */
#define BLE_EXTENDED_HEADER_CTEINFO_LEN             1
/* Length in bytes of the CTEInfo field */
#define BLE_EXTENDED_HEADER_ADI_LEN                 2
/* Length in bytes of the AuxPtr field */
#define BLE_EXTENDED_HEADER_AUXPTR_LEN              3
/* Length in bytes of the SyncInfo field */
#define BLE_EXTENDED_HEADER_SYNCINFO_LEN            18
/* Length in bytes of the Tx Power field */
#define BLE_EXTENDED_HEADER_TXPOWER_LEN             1

/* Bitmask for accessing PDU Type */
#define BLE_PDU_TYPE_BM                             0x0F

/* Bitmask for accessing advertising mode */
#define BLE_ADV_MODE_BM                             0xC0

/* Advertising physical channel PDU header's PDU Type */
#define BLE_PDU_ADV_IND                             0x00
#define BLE_PDU_ADV_DIRECT_IND                      0x01
#define BLE_PDU_ADV_NONCONN_IND                     0x02
#define BLE_PDU_ADV_SCAN_IND                        0x06
#define BLE_PDU_ADV_EXTENDED                        0x07
#define BLE_PDU_AUX_CONNECT_RSP                     0x08

/* Available advertising modes in the common extended advertising payload format */
#define BLE_ADV_MODE_NONCONN_NONSCAN                0x00
#define BLE_ADV_MODE_CONN_NONSCAN                   0x01
#define BLE_ADV_MODE_NONCONN_SCAN                   0x02


/**
 *  @brief Pointer to a given byte in the data part of a TX buffer
 *
 *  @param  buffer    Pointer to TX buffer
 *
 *  @param  pos       Position
 *
 */
#define txBuffer_dataByte(buffer, pos) ((buffer->data) + ((buffer->numPad) - 1 + pos))

/*
 *  ======== RCL_Handler_BLE5_adv ========
 */
RCL_Events RCL_Handler_BLE5_adv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    uint32_t rfFreq;
    RCL_CmdBle5Advertiser *advCmd = (RCL_CmdBle5Advertiser *) cmd;
    bool runAdv = false;
    bool runExtAdv = false;
    bool advDone = false;
    RCL_Ble5Channel curChannel;
    RCL_Events rclEvents = {.value = 0};
    uint32_t earliestStartTime = 0;

    if (rclEventsIn.setup != 0)
    {
        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        ble5HandlerState.adv.chanMap = advCmd->chanMap;

        /* Keep track of the number of primary channel packets to be sent based on the channel map */
        ble5HandlerState.common.auxPtrInfo.numPrimaryChPackets = (advCmd->chanMap & 1) + ((advCmd->chanMap >> 1) & 1) + ((advCmd->chanMap >> 2) & 1);
        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = ADV_CRC_INIT;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        if (LRF_programTxPower(advCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Initialize RF FIFOs */
            ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
            ble5HandlerState.common.curBuffer = NULL;
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&advCmd->ctx->rxBuffers);
            ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

            /* Enter address */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRL) = advCmd->ctx->advA[0];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRM) = advCmd->ctx->advA[1];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRH) = advCmd->ctx->advA[2];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRTYPE) = advCmd->ctx->addrType.own;

            /* Find which type of advertising */
            RCL_Buffer_TxBuffer *txBuffer = RCL_TxBuffer_head(&advCmd->ctx->txBuffers);
            uint16_t advCfg = 0;

            if (txBuffer != NULL)
            {
                uint8_t header = txBuffer->data[txBuffer->numPad - 1];

                /* Check advertising type */
                switch (header & BLE_PDU_TYPE_BM)
                {
                    case BLE_PDU_ADV_IND:
                        advCfg = PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M | PBE_BLE5_RAM_ADVCFG_SCANNABLE_M;
                        ble5HandlerState.adv.runRx = true;
                        ble5HandlerState.adv.isExtAdv = false;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                        break;

                    case BLE_PDU_ADV_DIRECT_IND:
                        advCfg = PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M | PBE_BLE5_RAM_ADVCFG_DIRECTED_M;
                        /* Enter address */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRL) = advCmd->ctx->peerA[0];
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRM) = advCmd->ctx->peerA[1];
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRH) = advCmd->ctx->peerA[2];
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRTYPE) = advCmd->ctx->addrType.peer;
                        ble5HandlerState.adv.runRx = true;
                        ble5HandlerState.adv.isExtAdv = false;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                        break;

                    case BLE_PDU_ADV_NONCONN_IND:
                        advCfg = 0;
                        ble5HandlerState.adv.runRx = false;
                        ble5HandlerState.adv.isExtAdv = false;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                        break;

                    case BLE_PDU_ADV_SCAN_IND:
                        advCfg = PBE_BLE5_RAM_ADVCFG_SCANNABLE_M;
                        ble5HandlerState.adv.runRx = true;
                        ble5HandlerState.adv.isExtAdv = false;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                        break;

                    case BLE_PDU_ADV_EXTENDED:
                        advCfg = 0;
                        ble5HandlerState.adv.runRx = false;
                        ble5HandlerState.adv.isExtAdv = true;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        /* Extract AuxPtr information if available */
                        RCL_Handler_BLE5_getAuxPtrFromTxBuffer(txBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                        if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                        {
                            /* Check if a PHY switch is needed before the move to secondary channel advertising */
                            if ((cmd->phyFeatures & 0x03) != ble5HandlerState.common.auxPtrInfo.auxPhy)
                            {
                                ble5HandlerState.adv.switchPhy = true;
                            }
                            else
                            {
                                ble5HandlerState.adv.switchPhy = false;
                            }
                        }
                        else
                        {
                            ble5HandlerState.adv.switchPhy = false;
                        }
                        break;

                    default:
                        advCfg = 0;
                        ble5HandlerState.adv.runRx = false;
                        ble5HandlerState.adv.isExtAdv = false;
                        ble5HandlerState.adv.auxScanReqReceived = false;
                        ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                        break;
                }
            }
            /* Enter payload.
             * For legacy advertising, maximum two Tx buffers can be entered (to account for possible SCAN_RSP PDUs).
             * For extended advertising, enter only one Tx buffer (corresponding to the ADV_EXT_IND PDU).
             */
            uint32_t nBuffer;
            if (ble5HandlerState.adv.isExtAdv)
            {
                ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { 0 };
                nBuffer = RCL_Handler_BLE5_updateTxBuffers(&advCmd->ctx->txBuffers, 1,
                                                           &ble5HandlerState.common.txBufferInfo,
                                                            false);
            }
            else
            {
                nBuffer = RCL_Handler_BLE5_updateTxBuffers(&advCmd->ctx->txBuffers, 2,
                                                            NULL, false);
            }
            if (nBuffer == 0)
            {
                status = RCL_CommandStatus_Error_MissingTxBuffer;
            }
            else
            {
                /* Scannable types also need a SCAN_RSP */
                if (((advCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0) && (nBuffer < 2))
                {
                    status = RCL_CommandStatus_Error_MissingTxBuffer;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = advCfg;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = (advCmd->ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_ADV_S) &
                                                                                      PBE_BLE5_RAM_FILTPOLICY_ADV_M;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = (advCmd->ctx->rpaModePeer << PBE_BLE5_RAM_RPAMODE_PEERADR_S);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPACONNECT) = advCmd->ctx->acceptAllRpaConnectInd << PBE_BLE5_RAM_RPACONNECT_ENDADV_S;

                    if ((advCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0)
                    {
                        RCL_FilterList *filterList = advCmd->ctx->filterListScan;
                        uint32_t invertMask = 0;
                        if ((advCmd->ctx->filterPolicy & BLE_ADV_FILTER_POLICY_SCAN) != 0)
                        {
                            /* Set filter list masks to normal accept list use: */
                            /* Bit 0: Consider enable bit */
                            /* Bit 1: Consider type bit */
                            /* Bit 3: Consider privIgn bit */
                            /* Bit 15: Consider match bit (found by PBE) */
                            /* Other bits are not checked */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_TYPE_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_EN_M;
                        }
                        else
                        {
                            if (advCmd->ctx->privIgnMode != 0)
                            {
                                /* Set filter list masks for RPA filtering: */
                                /* Bit 1: Consider type bit */
                                /* Bit 3: Consider pribvIgn bit */
                                /* Bit 15: Consider match bit (found by PBE) */
                                /* Other bits are not checked */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                              PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                              PBE_BLE5_RAM_FL1MASK_TYPE_M;
                                invertMask = PBE_BLE5_RAM_FL1MASK_PRIVIGN_M;
                            }
                            else
                            {
                                /* Filter list not used */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                                filterList = NULL;
                            }
                        }
                        RCL_Handler_BLE5_InitializeFilterList(filterList, (uint32_t *) (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1INFO0), invertMask);
                    }
                    else
                    {
                        /* Filter list not applicable */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                    }
                    if ((advCfg & PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M) != 0)
                    {
                        RCL_FilterList *filterList = advCmd->ctx->filterListConn;
                        uint32_t invertMask = 0;
                        if ((advCmd->ctx->filterPolicy & BLE_ADV_FILTER_POLICY_CONN) != 0)
                        {
                            /* Set filter list masks to normal accept list use: */
                            /* Bit 0: Consider enable bit */
                            /* Bit 1: Consider type bit */
                            /* Bit 3: Consider privIgn bit */
                            /* Bit 15: Consider match bit (found by PBE) */
                            /* Other bits are not checked */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = PBE_BLE5_RAM_FL2MASK_MATCH_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_PRIVIGN_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_TYPE_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_EN_M;
                        }
                        else
                        {
                            if (advCmd->ctx->privIgnMode != 0)
                            {
                                /* Set filter list masks for RPA filtering: */
                                /* Bit 1: Consider type bit */
                                /* Bit 3: Consider privIgn bit */
                                /* Bit 15: Consider match bit (found by PBE) */
                                /* Other bits are not checked */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = PBE_BLE5_RAM_FL2MASK_MATCH_M |
                                                                                              PBE_BLE5_RAM_FL2MASK_PRIVIGN_M |
                                                                                              PBE_BLE5_RAM_FL2MASK_TYPE_M;
                                invertMask = PBE_BLE5_RAM_FL2MASK_PRIVIGN_M;
                            }
                            else
                            {
                                /* Filter list not used */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                                filterList = NULL;
                            }
                        }
                        RCL_Handler_BLE5_InitializeFilterList(filterList, (uint32_t *) (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2INFO0), invertMask);
                    }
                    else
                    {
                        /* Filter list not applicable */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                    }
                    /* Run advertiser next */
                    runAdv = true;
                }

                /* Once packets are copied to the TX FIFO, consume them from the Tx Buffer list and notify the caller (only for extended) */
                if (ble5HandlerState.adv.isExtAdv)
                {
                    RCL_Buffer_TxBuffer *txBuffer;
                    txBuffer = RCL_TxBuffer_get(&advCmd->ctx->txBuffers);
                    if (txBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                    }
                    txBuffer->state = RCL_BufferStateFinished;
                    if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                    {
                        ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                    }
                    rclEvents.txBufferFinished = 1;
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }
    if(rclEventsIn.handlerCmdUpdate != 0)
    {
        /* PHY change concluded successfully. Proceed with the advertising event */
        runExtAdv = true;
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                          wordLength * 4);
                    if (curBuffer != ble5HandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        ble5HandlerState.common.curBuffer = curBuffer;
                    }
                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        RCL_Handler_BLE5_updateRxCurBufferAndFifo(&advCmd->ctx->rxBuffers);
                        rclEventsIn.rxBufferUpdate = 0;
                        if (ble5HandlerState.adv.isExtAdv)
                        {
                            ble5HandlerState.adv.auxScanReqReceived = true;
                        }
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                RCL_Handler_BLE5_updateAdvScanInitStats(advCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (rclEventsIn.gracefulStop != 0)
        {
            ble5HandlerState.adv.gracefulStopObserved = true;
        }

        if (lrfEvents.opDone != 0 && rclEventsIn.handlerCmdUpdate == 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);

            if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_CONNECT)
            {
                /* 32-bit access to also read LASTTIMESTAMPH */
                advCmd->connectPktTime = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) - ble5HandlerState.common.timestampAdjust;
                ble5HandlerState.common.endStatus = RCL_CommandStatus_Connect;
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
                runAdv = false;
                runExtAdv = false;
                advDone = true;
            }
            else if (rclEventsIn.hardStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
                runAdv = false;
                runExtAdv = false;
                advDone = true;
            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP ||
                        ble5HandlerState.adv.gracefulStopObserved ||
                        rclEventsIn.gracefulStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                runAdv = false;
                runExtAdv = false;
                advDone = true;
            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC && ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
            {
                /* If no AUX_SCAN_REQ is received, no point in sending any subsequent AUX_CHAIN_IND PDUs */
                runAdv = false;
                runExtAdv = false;
                advDone = true;
            }
            else
            {
                if (ble5HandlerState.adv.chanMap != 0)
                {
                    /* Retry TX FIFO. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RETRY >> LRFDPBE_FCMD_DATA_S);

                    if (ble5HandlerState.common.activeUpdate)
                    {
                        RCL_Handler_BLE5_updateAdvScanInitStats(advCmd->stats, rclSchedulerState.actualStartTime);
                    }

                    /* Turn off LRF to allow new synth programming  */
                    LRF_disable();
                    runAdv = true;
                    runExtAdv = false;
                    advDone = false;
                }
                else
                {
                    /* Once done with primary channel advertising, check AuxPtr and proceed with extended advertising if needed. */
                    if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                    {
                        if (ble5HandlerState.common.auxPtrInfo.offsetUnits == 1 && ble5HandlerState.common.auxPtrInfo.auxOffset == 0)
                        {
                            /* Reset TX FIFO to handle auxPtr updates. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);

                            /* Turn off LRF to allow new synth programming  */
                            LRF_disable();

                            if (ble5HandlerState.adv.switchPhy)
                            {
                                /* Update phyFeatures while keeping the code rate selection intact */
                                rclSchedulerState.requestedPhyFeatures = ble5HandlerState.common.auxPtrInfo.auxPhy | (cmd->phyFeatures & 0x04);

                                /* Raise a partialSetup event so that the PHY switching can be applied by the RCL */
                                rclEvents.partialSetup = 1;
                            }
                            else
                            {
                                runExtAdv = true;
                            }
                            runAdv = false;
                            advDone = false;
                        }
                        else
                        {
                            advDone = true;
                        }
                    }
                    else
                    {
                        advDone = true;
                    }
                }
            }
            if (advDone)
            {
                cmd->status = ble5HandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
                runAdv = false;
                runExtAdv = false;
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
            }
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
            runAdv = false;
            runExtAdv = false;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&advCmd->ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }

        if (runAdv)
        {
            curChannel = RCL_Handler_BLE5_findAdvChannel(ble5HandlerState.adv.chanMap, advCmd->order);
            uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

            rfFreq = RCL_Handler_BLE5_findRfFreq(curChannel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                RCL_CommandStatus startTimeStatus;

                if (rclEventsIn.setup != 0)
                {
                    startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                    if (startTimeStatus < RCL_CommandStatus_Finished)
                    {
                        if (ble5HandlerState.adv.isExtAdv && ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                        {
                            /* Calculate auxPtr offset and update Tx FIFO if needed */
                            if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, ble5HandlerState.adv.chanMap, ble5HandlerState.adv.switchPhy))
                            {
                                startTimeStatus = RCL_CommandStatus_Error_Param;
                            }
                        }
                        /* Initialize counters */
                        ble5HandlerState.common.activeUpdate =
                            RCL_Handler_BLE5_initAdvScanInitStats(advCmd->stats, rclSchedulerState.actualStartTime);
                        ble5HandlerState.adv.gracefulStopObserved = false;
                        if (rclSchedulerState.gracefulStopInfo.cmdStopEnabled || rclSchedulerState.gracefulStopInfo.schedStopEnabled)
                        {
                            /* Enable interrupt to service graceful stop */
                            hal_enable_graceful_stop_time_irq();
                        }
                    }
                }
                else
                {
                    if (advCmd->highDuty != 0)
                    {
                        startTimeStatus = RCL_Scheduler_setNewStartRelTime(HIGH_DUTY_CYCLE_INTERVAL);
                    }
                    else
                    {
                        if (ble5HandlerState.adv.isExtAdv && ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                        {
                            /*
                             * All primary advertising packets must point to the same time at which the auxiliary packet will be sent.
                             * Achieve this by using a relative start time to previous LRF start where the packet duration is also expressed
                             * in terms of 30 [us] units. This facilitates the calculation of the auxOffset.
                             */
                            uint32_t pktDurationInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(pktDuration, BLE_AUX_OFFSET_30_US);
                            uint32_t relStartTime = RCL_SCHEDULER_SYSTIM_US((pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US);
                            startTimeStatus = RCL_Scheduler_setNewStartRelTime(relStartTime);

                            /* Calculate auxPtr offset and update Tx FIFO if needed */
                            if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, ble5HandlerState.adv.chanMap, ble5HandlerState.adv.switchPhy))
                            {
                                startTimeStatus = RCL_CommandStatus_Error_Param;
                            }
                        }
                        else
                        {
                            startTimeStatus = RCL_Scheduler_setNewStartNow();
                        }
                    }
                }
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(curChannel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                    }

                    /* Enable interrupts */
                    if (ble5HandlerState.adv.runRx)
                    {
                        /* Set up sync found capture */
                        hal_setup_sync_found_cap();
                        uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                        LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                    LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                    LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                    fifoCfg, ble5HandlerState.common.activeUpdate));
                    }
                    else
                    {
                        LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                    }

                    /* Post cmd */
                    Log_printf(RclCore, Log_VERBOSE, "Starting advertiser on channel %1d", curChannel);

                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;

                    if ((curChannel & BLE_CUSTOM_FREQ_BM) != 0)
                    {
                        /* Custom channel - run only once */
                        ble5HandlerState.adv.chanMap = 0;
                    }
                    else
                    {
                        ble5HandlerState.adv.chanMap &= ~(1 << (curChannel - 37));
                        if (advCmd->highDuty != 0 && ble5HandlerState.adv.chanMap == 0)
                        {
                            /* High duty cycle advertising: Reload channel map when one round is done */
                            ble5HandlerState.adv.chanMap = advCmd->chanMap;
                        }
                    }
                }
            }
        }
        if (runExtAdv)
        {
            RCL_CommandStatus startTimeStatus;
            RCL_Ble5Channel channel;
            uint32_t startTimeDelta = 0;

            /* Switch to the channel indicated by the auxPtr */
            channel = ble5HandlerState.common.auxPtrInfo.chIndex;
            rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                RCL_Buffer_TxBuffer *nextTxBuffer = RCL_TxBuffer_head(&advCmd->ctx->txBuffers);
                uint16_t advCfg = 0;
                uint16_t aeCfg = PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;

                if (nextTxBuffer != NULL)
                {
                    /*
                    * Start time is calculated relative to the duration of the previous packet. If there was a PHY change,
                    * consider its duration with the previous PHY, before updating the timestamps associated with the new PHY.
                    */
                    if (ble5HandlerState.adv.switchPhy)
                    {
                        startTimeDelta = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);
                        /* Consider the time that it takes to handle the PHY switching */
                        startTimeDelta += RCL_SCHEDULER_SYSTIM_US(EXT_ADV_PHY_SWITCHING_DELAY_US);
                        /* Adjust timestamps accordingly */
                        RCL_Handler_BLE5_setPhy(rclSchedulerState.requestedPhyFeatures);
                        ble5HandlerState.adv.switchPhy = false;
                    }
                    else
                    {
                        startTimeDelta = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);
                    }

                    /*  Check advertising type and mode */
                    uint8_t header = nextTxBuffer->data[nextTxBuffer->numPad - 1];
                    uint8_t extHeader = nextTxBuffer->data[nextTxBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                    if ((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED)
                    {
                        switch ((extHeader & BLE_ADV_MODE_BM) >> 6)
                        {
                            case BLE_ADV_MODE_NONCONN_NONSCAN: /* Non-connectable - Non-scannable */
                                advCfg = 0;
                                /* Extract AuxPtr information if available */
                                RCL_Handler_BLE5_getAuxPtrFromTxBuffer(nextTxBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                                ble5HandlerState.adv.runRx = false;
                                break;

                            case BLE_ADV_MODE_CONN_NONSCAN: /* Connectable - Non-scannable */

                                RCL_Handler_BLE5_getAuxPtrFromTxBuffer(nextTxBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                                {
                                    ble5HandlerState.adv.runRx = false;
                                    /* Connectable PDUs must not have an AuxPtr */
                                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                                }
                                else
                                {
                                    advCfg = PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M;
                                    ble5HandlerState.adv.runRx = true;
                                }
                                break;

                            case BLE_ADV_MODE_NONCONN_SCAN: /* Non-connectable - Scannable */
                                /* Scannable PDUs must not have an AuxPtr in the AUX_ADV_IND, so perform a sanity check on it to be sure */
                                RCL_Handler_BLE5_getAuxPtrFromTxBuffer(nextTxBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                                {
                                    ble5HandlerState.adv.runRx = false;
                                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                                }
                                else
                                {
                                    advCfg = PBE_BLE5_RAM_ADVCFG_SCANNABLE_M;
                                    ble5HandlerState.adv.runRx = true;
                                }
                                break;

                            default:
                                advCfg = 0;
                                ble5HandlerState.adv.runRx = false;
                                ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                                break;
                        }
                    }
                    else
                    {
                        /* Only extended PDUs are valid at this point */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_Param;
                    }
                }

                /* Enter payload */
                uint32_t nBuffer = 0;
                if ((advCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0)
                {
                    /* Scannable advertising requires the presence of an additional Tx Buffer with an AUX_SCAN_RSP in the Tx buffer list */
                    RCL_Buffer_TxBuffer *auxScanRspTxBuffer;
                    auxScanRspTxBuffer = RCL_TxBuffer_next(nextTxBuffer);

                    if (auxScanRspTxBuffer != NULL)
                    {
                        uint8_t header = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad - 1];
                        uint8_t extHeader = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                        /* AUX_SCAN_RSP PDUs may or may not point to a subsequent auxiliary packet. Check the Tx Buffer to see if there is one */
                        if (((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED) && ((extHeader & BLE_ADV_MODE_BM) >> 6) == 0)
                        {
                            /*
                             * Since both Tx buffers will be put in the PBE FIFO, consider the entry length of the AUX_ADV_IND to determine
                             * the location of the AuxPtr in the PBE FIFO. This needs to be known so that the AuxPtr fields can be updated
                             * later.
                             */
                            uint8_t auxAdvEntryLength = RCL_Buffer_entryLen(BLE_NUM_PAD, BLE_HEADER_LENGTH, nextTxBuffer->data[nextTxBuffer->numPad]);
                            RCL_Handler_BLE5_getAuxPtrFromTxBuffer(auxScanRspTxBuffer, &ble5HandlerState.common.auxPtrInfo, auxAdvEntryLength);
                        }
                        /* Enter the two Tx Buffers corresponding to the AUX_ADV_IND and the AUX_SCAN_RSP */
                        nBuffer = RCL_Handler_BLE5_updateTxBuffers(&advCmd->ctx->txBuffers, 2,
                                                                   &ble5HandlerState.common.txBufferInfo,
                                                                   false);
                        /* Keep track of the lengths of the AUX_ADV_IND and the AUX_SCAN_IND since they will be used if an AUX_CHAIN_IND is to be sent afterwards */
                        ble5HandlerState.adv.auxScanRspLen = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad];
                        ble5HandlerState.adv.auxAdvIndLen = nextTxBuffer->data[nextTxBuffer->numPad];
                    }
                }
                else if ((advCfg & PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M) != 0)
                {
                    /* Connectable advertising requires a Tx Buffer with an AUX_CONNECT_RSP */
                    RCL_Buffer_TxBuffer *auxConnectRspTxBuffer;
                    auxConnectRspTxBuffer = RCL_TxBuffer_next(nextTxBuffer);

                    if (auxConnectRspTxBuffer != NULL)
                    {
                        /* Enter the two Tx Buffers corresponding to the AUX_ADV_IND and the AUX_CONNECT_RSP */
                        nBuffer = RCL_Handler_BLE5_updateTxBuffers(&advCmd->ctx->txBuffers, 2,
                                                                   &ble5HandlerState.common.txBufferInfo,
                                                                   false);
                    }
                }
                else
                {
                    /* Non-scannable advertising is handled one Tx buffer at a time */
                    nBuffer = RCL_Handler_BLE5_updateTxBuffers(&advCmd->ctx->txBuffers, 1,
                                                               &ble5HandlerState.common.txBufferInfo,
                                                               false);
                }

                if (nBuffer == 0 || (((advCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0) && (nBuffer < 2)) ||
                   (((advCfg & PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M) != 0) && (nBuffer < 2)))
                {
                    /* Error */
                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_MissingTxBuffer;
                }
                else
                {
                    /*
                     * Express the startTimeDelta in terms of offset units so that the relative start time is rounded up
                     * to the closest offset unit. Add a delay of a couple of microseconds to avoid sending the packets right
                     * at the beginning of the offset window.
                     */
                    startTimeDelta += RCL_SCHEDULER_SYSTIM_US(EXT_ADV_INTERVAL_US);
                    uint32_t startTimeDeltaInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(startTimeDelta, BLE_AUX_OFFSET_30_US);
                    uint32_t relStartTime = RCL_SCHEDULER_SYSTIM_US((startTimeDeltaInOffsetUnits * BLE_AUX_OFFSET_30_US)) + RCL_SCHEDULER_SYSTIM_US(2);
                    /*
                     * If an AUX_SCAN_REQ was received, the relative start time for the packet needs to consider the
                     * time spent sending the AUX_ADV_IND, receiving the AUX_SCAN_REQ and replying with the AUX_SCAN_RSP.
                     * In this particular case, the AUX_SCAN_RSP is the previously sent packet, so no need to include it here.
                     */
                    if (ble5HandlerState.adv.auxScanReqReceived)
                    {
                        /* Time spent sending the AUX_ADV_IND */
                        relStartTime += RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.adv.auxAdvIndLen, ble5HandlerState.common.phyFeatures);
                        /* Time spent receiving the AUX_SCAN_REQ */
                        relStartTime += RCL_Handler_BLE5_findPacketDuration(BLE_ADV_AUX_SCAN_REQ_PKT_LEN, ble5HandlerState.common.phyFeatures);
                        /* Time spent switching from Tx to Rx to receive the AUX_SCAN_REQ, and then back from Rx to Tx to send the AUX_SCAN_RSP */
                        relStartTime += (2 * BLE_T_IFS);
                        ble5HandlerState.adv.auxScanReqReceived = false;
                    }
                    startTimeStatus = RCL_Scheduler_setNewStartRelTime(relStartTime);

                    if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                    {
                        /* Consider the current packet duration when calculating the AuxOffset */
                        uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

                        if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, ble5HandlerState.adv.chanMap, ble5HandlerState.adv.switchPhy))
                        {
                            startTimeStatus = RCL_CommandStatus_Error_Param;
                        }
                    }

                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = advCfg;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = (advCmd->ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_ADV_S) &
                                                                                      PBE_BLE5_RAM_FILTPOLICY_ADV_M;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = (advCmd->ctx->rpaModePeer << PBE_BLE5_RAM_RPAMODE_PEERADR_S);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPACONNECT) = advCmd->ctx->acceptAllRpaConnectInd << PBE_BLE5_RAM_RPACONNECT_ENDADV_S;

                    if ((advCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0)
                    {
                        RCL_FilterList *filterList = advCmd->ctx->filterListScan;
                        uint32_t invertMask = 0;
                        if ((advCmd->ctx->filterPolicy & BLE_ADV_FILTER_POLICY_SCAN) != 0)
                        {
                            /* Set filter list masks to normal accept list use: */
                            /* Bit 0: Consider enable bit */
                            /* Bit 1: Consider type bit */
                            /* Bit 3: Consider privIgn bit */
                            /* Bit 15: Consider match bit (found by PBE) */
                            /* Other bits are not checked */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_TYPE_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_EN_M;
                        }
                        else
                        {
                            if (advCmd->ctx->privIgnMode != 0)
                            {
                                /* Set filter list masks for RPA filtering: */
                                /* Bit 1: Consider type bit */
                                /* Bit 3: Consider pribvIgn bit */
                                /* Bit 15: Consider match bit (found by PBE) */
                                /* Other bits are not checked */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                    PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                    PBE_BLE5_RAM_FL1MASK_TYPE_M;
                                invertMask = PBE_BLE5_RAM_FL1MASK_PRIVIGN_M;
                            }
                            else
                            {
                                /* Filter list not used */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                                filterList = NULL;
                            }
                        }
                        RCL_Handler_BLE5_InitializeFilterList(filterList, (uint32_t *) (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1INFO0), invertMask);
                    }
                    else
                    {
                        /* Filter list not applicable */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                    }
                    if ((advCfg & PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M) != 0)
                    {
                        RCL_FilterList *filterList = advCmd->ctx->filterListConn;
                        uint32_t invertMask = 0;
                        if ((advCmd->ctx->filterPolicy & BLE_ADV_FILTER_POLICY_CONN) != 0)
                        {
                            /* Set filter list masks to normal accept list use: */
                            /* Bit 0: Consider enable bit */
                            /* Bit 1: Consider type bit */
                            /* Bit 3: Consider privIgn bit */
                            /* Bit 15: Consider match bit (found by PBE) */
                            /* Other bits are not checked */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = PBE_BLE5_RAM_FL2MASK_MATCH_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_PRIVIGN_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_TYPE_M |
                                                                                          PBE_BLE5_RAM_FL2MASK_EN_M;
                        }
                        else
                        {
                            if (advCmd->ctx->privIgnMode != 0)
                            {
                                /* Set filter list masks for RPA filtering: */
                                /* Bit 1: Consider type bit */
                                /* Bit 3: Consider privIgn bit */
                                /* Bit 15: Consider match bit (found by PBE) */
                                /* Other bits are not checked */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = PBE_BLE5_RAM_FL2MASK_MATCH_M |
                                                                                              PBE_BLE5_RAM_FL2MASK_PRIVIGN_M |
                                                                                              PBE_BLE5_RAM_FL2MASK_TYPE_M;
                                invertMask = PBE_BLE5_RAM_FL2MASK_PRIVIGN_M;
                            }
                            else
                            {
                                /* Filter list not used */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                                filterList = NULL;
                            }
                        }
                        RCL_Handler_BLE5_InitializeFilterList(filterList, (uint32_t *) (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2INFO0), invertMask);
                    }
                    else
                    {
                        /* Filter list not applicable */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                    }
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        cmd->status = startTimeStatus;
                        rclEvents.lastCmdDone = 1;
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                        uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                        if (ble5HandlerState.common.accessAddressModification)
                        {
                            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                        }

                        /* Enable interrupts */
                        if (ble5HandlerState.adv.runRx)
                        {
                            /* Set up sync found capture */
                            hal_setup_sync_found_cap();
                            uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                            LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                        LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                        LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                        fifoCfg, ble5HandlerState.common.activeUpdate));
                        }
                        else
                        {
                            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                        }

                        LRF_waitForTopsmReady();

                        /* Post cmd */
                        Log_printf(RclCore, Log_VERBOSE, "Starting extended advertiser on channel %1d", channel);
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;

                        /* Free up finished Tx buffers from the Tx Buffer list and raise the appropriate RCL event */
                        uint32_t numBuffers = nBuffer;
                        RCL_Buffer_TxBuffer *txBuffer;
                        do
                        {
                            txBuffer = RCL_TxBuffer_get(&advCmd->ctx->txBuffers);
                            if (txBuffer == NULL)
                            {
                                /* Error */
                                ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                            }
                            txBuffer->state = RCL_BufferStateFinished;
                            if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                            {
                                ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                            }
                            numBuffers--;
                        } while (numBuffers > 0);
                        /* Raise RCL event indicating that the buffers have been consumed */
                        rclEvents.txBufferFinished = 1;
                    }
                }
            }
        }
        if (rclEvents.lastCmdDone != 0)
        {
            RCL_Handler_BLE5_updateAdvScanInitStats(advCmd->stats, rclSchedulerState.actualStartTime);
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_aux_adv ========
 */
RCL_Events RCL_Handler_BLE5_aux_adv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    uint32_t rfFreq;
    RCL_CmdBle5AuxAdvertiser *auxAdvCmd = (RCL_CmdBle5AuxAdvertiser *) cmd;
    bool runAuxAdv = false;
    bool runAuxChain = false;
    RCL_Events rclEvents = {.value = 0};
    uint32_t earliestStartTime = 0;
    RCL_Ble5Channel channel;

    if (rclEventsIn.setup != 0)
    {
        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = ADV_CRC_INIT;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);

        if (LRF_programTxPower(auxAdvCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Initialize RF FIFOs */
            ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
            ble5HandlerState.common.curBuffer = NULL;
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&auxAdvCmd->ctx->rxBuffers);
            ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

            /* Enter address */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRL) = auxAdvCmd->ctx->advA[0];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRM) = auxAdvCmd->ctx->advA[1];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRH) = auxAdvCmd->ctx->advA[2];
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRTYPE) = auxAdvCmd->ctx->addrType.own;

            /* Find which type of advertising */
            RCL_Buffer_TxBuffer *txBuffer = RCL_TxBuffer_head(&auxAdvCmd->ctx->txBuffers);
            uint16_t auxAdvCfg = 0;
            uint16_t aeCfg = PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;
            channel = auxAdvCmd->channel;

            if (txBuffer != NULL)
            {
                uint8_t header = txBuffer->data[txBuffer->numPad - 1];
                uint8_t extHeader = txBuffer->data[txBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                /* Check advertising type */
                if ((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED)
                {
                    ble5HandlerState.common.auxPtrInfo.numPrimaryChPackets = 0;

                    /* Check advertising mode */
                    switch ((extHeader & BLE_ADV_MODE_BM) >> 6)
                    {
                        case BLE_ADV_MODE_NONCONN_NONSCAN: /* Non-connectable - Non-scannable */
                            RCL_Handler_BLE5_getAuxPtrFromTxBuffer(txBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                            ble5HandlerState.auxAdv.runRx = false;
                            ble5HandlerState.auxAdv.sendAuxAdv = true;
                            ble5HandlerState.auxAdv.auxScanReqReceived = false;
                            break;
                        case BLE_ADV_MODE_CONN_NONSCAN: /* Connectable - Non-scannable */
                            ble5HandlerState.auxAdv.runRx = false;
                            ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                            ble5HandlerState.auxAdv.auxScanReqReceived = false;
                            auxAdvCfg = PBE_BLE5_RAM_ADVCFG_CONNECTABLE_M;
                            break;
                        case BLE_ADV_MODE_NONCONN_SCAN: /* Non-connectable - Scannable */
                            RCL_Handler_BLE5_getAuxPtrFromTxBuffer(txBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                            if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                            {
                                ble5HandlerState.auxAdv.runRx = false;
                                ble5HandlerState.auxAdv.auxScanReqReceived = false;
                                /* Scannable PDUs must not have an AuxPtr */
                                ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                            }
                            else
                            {
                                auxAdvCfg = PBE_BLE5_RAM_ADVCFG_SCANNABLE_M;
                                ble5HandlerState.auxAdv.runRx = true;
                                ble5HandlerState.auxAdv.auxScanReqReceived = false;
                            }
                            break;
                        default:
                            ble5HandlerState.auxAdv.runRx = false;
                            ble5HandlerState.common.auxPtrInfo.auxPtrPresent = false;
                            ble5HandlerState.auxAdv.auxScanReqReceived = false;
                            break;
                    }
                }
                else
                {
                    /* Error. Tx Buffer does not correspond to an Extended Advertising PDU */
                    status = RCL_CommandStatus_Error_TxBufferCorruption;
                }
            }

            /* Enter payload */
            uint32_t nBuffer = 0;
            if ((auxAdvCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0)
            {
                /* Scannable advertising requires a Tx Buffer with an AUX_SCAN_RSP */
                RCL_Buffer_TxBuffer *auxScanRspTxBuffer;
                auxScanRspTxBuffer = RCL_TxBuffer_next(txBuffer);
                if (auxScanRspTxBuffer != NULL)
                {
                    uint8_t header = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad - 1];
                    uint8_t extHeader = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                    /* Perform a sanity check on the AUX_SCAN_RSP and extract its AuxPtr if needed */
                    if (((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED) && ((extHeader & BLE_ADV_MODE_BM) >> 6) == 0)
                    {
                        /* Consider the entry length of the AUX_ADV_IND to determine the pointer to the AuxPtr in the FIFO */
                        uint8_t auxAdvEntryLength = RCL_Buffer_entryLen(BLE_NUM_PAD, BLE_HEADER_LENGTH, txBuffer->data[txBuffer->numPad]);
                        RCL_Handler_BLE5_getAuxPtrFromTxBuffer(auxScanRspTxBuffer, &ble5HandlerState.common.auxPtrInfo, auxAdvEntryLength);
                    }
                    /* If it's scannable advertising, two Tx buffers are needed */
                    ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { 0 };
                    nBuffer = RCL_Handler_BLE5_updateTxBuffers(&auxAdvCmd->ctx->txBuffers, 2,
                                                               &ble5HandlerState.common.txBufferInfo,
                                                               false);
                    /* Keep track of the lengths of the AUX_ADV_IND and the AUX_SCAN_IND since they will be used if an AUX_CHAIN_IND is to be sent afterwards */
                    ble5HandlerState.auxAdv.auxScanRspLen = auxScanRspTxBuffer->data[auxScanRspTxBuffer->numPad];
                    ble5HandlerState.auxAdv.auxAdvIndLen = txBuffer->data[txBuffer->numPad];
                }
            }
            else
            {
                ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { 0 };
                nBuffer = RCL_Handler_BLE5_updateTxBuffers(&auxAdvCmd->ctx->txBuffers, 1,
                                                           &ble5HandlerState.common.txBufferInfo,
                                                           false);
            }

            if (nBuffer == 0 || (((auxAdvCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0) && (nBuffer < 2)))
            {
                /* Error */
                ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_MissingTxBuffer;
            }
            else
            {
                /* Free up finished Tx buffers from the Tx Buffer list and raise the appropriate RCL event */
                uint32_t numBuffers = nBuffer;
                RCL_Buffer_TxBuffer *txBuffer;
                do
                {
                    txBuffer = RCL_TxBuffer_get(&auxAdvCmd->ctx->txBuffers);
                    if (txBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                    }
                    txBuffer->state = RCL_BufferStateFinished;
                    if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                    {
                        ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                    }
                    numBuffers--;
                } while (numBuffers > 0);
                /* Raise RCL event indicating that the buffers have been consumed */
                rclEvents.txBufferFinished = 1;

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = auxAdvCfg;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = (auxAdvCmd->ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_ADV_S) &
                                                                                  PBE_BLE5_RAM_FILTPOLICY_ADV_M;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = (auxAdvCmd->ctx->rpaModePeer << PBE_BLE5_RAM_RPAMODE_PEERADR_S);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPACONNECT) = auxAdvCmd->ctx->acceptAllRpaConnectInd << PBE_BLE5_RAM_RPACONNECT_ENDADV_S;

                if ((auxAdvCfg & PBE_BLE5_RAM_ADVCFG_SCANNABLE_M) != 0)
                {
                    RCL_FilterList *filterList = auxAdvCmd->ctx->filterListScan;
                    uint32_t invertMask = 0;
                    if ((auxAdvCmd->ctx->filterPolicy & BLE_ADV_FILTER_POLICY_SCAN) != 0)
                    {
                        /* Set filter list masks to normal accept list use: */
                        /* Bit 0: Consider enable bit */
                        /* Bit 1: Consider type bit */
                        /* Bit 3: Consider privIgn bit */
                        /* Bit 15: Consider match bit (found by PBE) */
                        /* Other bits are not checked */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_TYPE_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_EN_M;
                    }
                    else
                    {
                        if (auxAdvCmd->ctx->privIgnMode != 0)
                        {
                            /* Set filter list masks for RPA filtering: */
                            /* Bit 1: Consider type bit */
                            /* Bit 3: Consider pribvIgn bit */
                            /* Bit 15: Consider match bit (found by PBE) */
                            /* Other bits are not checked */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                          PBE_BLE5_RAM_FL1MASK_TYPE_M;
                            invertMask = PBE_BLE5_RAM_FL1MASK_PRIVIGN_M;
                        }
                        else
                        {
                            /* Filter list not used */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                            filterList = NULL;
                        }
                    }
                    RCL_Handler_BLE5_InitializeFilterList(filterList, (uint32_t *) (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1INFO0), invertMask);
                }
                else
                {
                    /* Filter list not applicable */
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                }
                if (status >= RCL_CommandStatus_Finished)
                {
                    cmd->status = status;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = auxAdvCfg;

                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                    }
                    /* Run advertiser next */
                    runAuxAdv = true;
                }
            }
        }

        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                          wordLength * 4);
                    if (curBuffer != ble5HandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        ble5HandlerState.common.curBuffer = curBuffer;
                    }
                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        RCL_Handler_BLE5_updateRxCurBufferAndFifo(&auxAdvCmd->ctx->rxBuffers);
                        rclEventsIn.rxBufferUpdate = 0;
                        ble5HandlerState.auxAdv.auxScanReqReceived = true;
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                RCL_Handler_BLE5_updateAdvScanInitStats(auxAdvCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (rclEventsIn.gracefulStop != 0)
        {
            ble5HandlerState.auxAdv.gracefulStopObserved = true;
        }

        if (lrfEvents.opDone != 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);

            if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_CONNECT)
            {
                /* 32-bit access to also read LASTTIMESTAMPH */
                auxAdvCmd->connectPktTime = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) - ble5HandlerState.common.timestampAdjust;

                ble5HandlerState.common.endStatus = RCL_CommandStatus_Connect;
                runAuxAdv = false;
                runAuxChain = false;
            }
            else if (rclEventsIn.hardStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
                runAuxAdv = false;
                runAuxChain = false;

            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP ||
                        ble5HandlerState.auxAdv.gracefulStopObserved ||
                        rclEventsIn.gracefulStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                runAuxAdv = false;
                runAuxChain = false;
            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC && ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
            {
                /* If no AUX_SCAN_REQ is received, no point in sending any subsequent AUX_CHAIN_IND PDUs */
                runAuxAdv = false;
                runAuxChain = false;
            }
            else
            {
                if (!ble5HandlerState.auxAdv.sendAuxAdv)
                {
                    if(ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                    {
                        if (ble5HandlerState.common.auxPtrInfo.offsetUnits == 1 && ble5HandlerState.common.auxPtrInfo.auxOffset == 0)
                        {
                            /* Reset TX FIFO to handle auxPtr updates. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S) ;
                            /* Turn off LRF to allow new synth programming  */
                            LRF_disable();
                            runAuxChain = true;
                        }
                        else
                        {
                            runAuxChain = false;
                        }
                    }
                    else
                    {
                        runAuxChain = false;
                    }
                    runAuxAdv = false;
                }
            }
            if (!runAuxAdv && !runAuxChain && cmd->status == RCL_CommandStatus_Active)
            {
                cmd->status = ble5HandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
                runAuxAdv = false;
                runAuxChain = false;
            }
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
            runAuxAdv = false;
            runAuxChain = false;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&auxAdvCmd->ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }

        if (runAuxAdv)
        {
            RCL_CommandStatus startTimeStatus;

            /* Set up channel */
            channel = auxAdvCmd->channel;
            rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);

                /* Consider the current packet duration when calculating the AuxOffset */
                uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);
                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                {
                    if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, 0, false))
                    {
                        startTimeStatus = RCL_CommandStatus_Error_Param;
                    }
                }
                if (startTimeStatus < RCL_CommandStatus_Finished)
                {
                    /* Initialize counters */
                    ble5HandlerState.common.activeUpdate =
                        RCL_Handler_BLE5_initAdvScanInitStats(auxAdvCmd->stats, rclSchedulerState.actualStartTime);
                    ble5HandlerState.auxAdv.gracefulStopObserved = false;

                    if (rclSchedulerState.gracefulStopInfo.cmdStopEnabled || rclSchedulerState.gracefulStopInfo.schedStopEnabled)
                    {
                        /* Enable interrupt to service graceful stop */
                        hal_enable_graceful_stop_time_irq();
                    }
                }

                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                    }

                    /* Enable interrupts */
                    if (ble5HandlerState.auxAdv.runRx)
                    {
                        /* Set up sync found capture */
                        hal_setup_sync_found_cap();
                        uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                        LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                    LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                    LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                    fifoCfg, ble5HandlerState.common.activeUpdate));
                    }
                    else
                    {
                        LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                    }

                    /* Post cmd */
                    Log_printf(RclCore, Log_VERBOSE, "Starting extended advertiser on channel %1d", channel);

                    LRF_waitForTopsmReady();
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;
                    ble5HandlerState.auxAdv.sendAuxAdv = false;
                }
            }
        }
        if (runAuxChain)
        {
            RCL_CommandStatus startTimeStatus;

            RCL_Ble5Channel channel = ble5HandlerState.common.auxPtrInfo.chIndex;
            uint16_t auxAdvCfg = 0;

            uint32_t startTimeDelta = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

            rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                /* Check advertising type */
                RCL_Buffer_TxBuffer *nextTxBuffer = RCL_TxBuffer_head(&auxAdvCmd->ctx->txBuffers);
                if(nextTxBuffer != NULL)
                {
                    uint8_t header = nextTxBuffer->data[nextTxBuffer->numPad - 1];
                    uint8_t extHeader = nextTxBuffer->data[nextTxBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                    if (((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED) && ((extHeader & BLE_ADV_MODE_BM) >> 6) == 0)
                    {
                        RCL_Handler_BLE5_getAuxPtrFromTxBuffer(nextTxBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                        ble5HandlerState.auxAdv.runRx = false;
                    }
                }

                uint32_t nBuffer = 0;
                nBuffer = RCL_Handler_BLE5_updateTxBuffers(&auxAdvCmd->ctx->txBuffers, 1,
                                                           &ble5HandlerState.common.txBufferInfo,
                                                           false);
                if (nBuffer == 0)
                {
                    /* Error */
                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_MissingTxBuffer;
                }
                else
                {
                    /*
                     * Express the startTimeDelta in terms of offset units so that the relative start time is rounded up
                     * to the closest offset unit. Also add a couple of microseconds to avoid sending the packets right
                     * at the beginning of the offset window.
                     */
                    startTimeDelta += RCL_SCHEDULER_SYSTIM_US(EXT_ADV_INTERVAL_US);
                    uint32_t startTimeDeltaInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(startTimeDelta, BLE_AUX_OFFSET_30_US);
                    uint32_t relStartTime = RCL_SCHEDULER_SYSTIM_US((startTimeDeltaInOffsetUnits * BLE_AUX_OFFSET_30_US)) + RCL_SCHEDULER_SYSTIM_US(2);

                    /*
                     * If an AUX_SCAN_REQ was received, the relative start time for the packet needs to consider the
                     * time spent sending the AUX_ADV_IND, receiving the AUX_SCAN_REQ and replying with the AUX_SCAN_RSP.
                     * In this particular case, the AUX_SCAN_RSP is the previously sent packet, so no need to include it here.
                     */
                    if (ble5HandlerState.auxAdv.auxScanReqReceived)
                    {
                        /* Time spent sending the AUX_ADV_IND */
                        relStartTime += RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.auxAdv.auxAdvIndLen, ble5HandlerState.common.phyFeatures);
                        /* Time spent receiving the AUX_SCAN_REQ */
                        relStartTime += RCL_Handler_BLE5_findPacketDuration(BLE_ADV_AUX_SCAN_REQ_PKT_LEN, ble5HandlerState.common.phyFeatures);
                        /* Time spent switching from Tx to Rx, and then back from Rx to Tx */
                        relStartTime += (2 * BLE_T_IFS);
                        ble5HandlerState.auxAdv.auxScanReqReceived = false;
                    }

                    /* Set new start time */
                    startTimeStatus = RCL_Scheduler_setNewStartRelTime(relStartTime);

                    /* Calculate auxPtr offset and update Tx FIFO if needed */
                    if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                    {
                        /* Consider the current packet duration when calculating the AuxOffset */
                        uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

                        if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, 0, false))
                        {
                            startTimeStatus = RCL_CommandStatus_Error_Param;
                        }
                    }
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        cmd->status = startTimeStatus;
                        rclEvents.lastCmdDone = 1;
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = auxAdvCfg;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                        uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                        if (ble5HandlerState.common.accessAddressModification)
                        {
                            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                        }

                        /* Enable interrupts */
                        if (ble5HandlerState.auxAdv.runRx)
                        {
                            /* Set up sync found capture */
                            hal_setup_sync_found_cap();
                            uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                            LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                        LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                        LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                        fifoCfg, ble5HandlerState.common.activeUpdate));
                        }
                        else
                        {
                            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                        }

                        LRF_waitForTopsmReady();

                        /* Deallocate TX FIFO. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_DEALLOC >> LRFDPBE_FCMD_DATA_S);

                        /* Post cmd */
                        Log_printf(RclCore, Log_VERBOSE, "Starting extended advertiser on channel %1d", channel);
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;

                        /* Free up the TxBuffer and notify caller with an RCL event */
                        RCL_Buffer_TxBuffer *txBuffer;
                        txBuffer = RCL_TxBuffer_get(&auxAdvCmd->ctx->txBuffers);
                        if (txBuffer == NULL)
                        {
                            /* Error */
                            ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                        }
                        txBuffer->state = RCL_BufferStateFinished;
                        if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                        {
                            ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                        }
                        rclEvents.txBufferFinished = 1;
                    }
                }
            }
        }
        if (rclEvents.lastCmdDone != 0)
        {
            RCL_Handler_BLE5_updateAdvScanInitStats(auxAdvCmd->stats, rclSchedulerState.actualStartTime);
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_periodicAdv ========
 */
RCL_Events RCL_Handler_BLE5_periodicAdv(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    uint32_t rfFreq;
    RCL_CmdBle5PeriodicAdvertiser *perAdvCmd = (RCL_CmdBle5PeriodicAdvertiser *) cmd;
    bool runAuxSync = false;
    bool runAuxChain = false;
    RCL_Ble5Channel channel;
    RCL_Events rclEvents = {.value = 0};
    uint32_t earliestStartTime = 0;

    if (rclEventsIn.setup != 0)
    {
        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        RCL_CtxPeriodicAdvertiser *ctx = perAdvCmd->ctx;
        uint32_t crcInit = ctx->crcInit;
        uint32_t accessAddress = ctx->accessAddress;

        /* 32-bit access to set the Access Address for the periodic advertisement */
        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = crcInit << 8;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        if (LRF_programTxPower(perAdvCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Initialize RF FIFOs */
            ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

            /* This operation is always non-connectable/non-scannable */
            RCL_Buffer_TxBuffer *txBuffer = RCL_TxBuffer_head(&perAdvCmd->ctx->txBuffers);
            uint16_t advCfg = 0;
            uint16_t aeCfg = PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;
            channel = perAdvCmd->channel;

            if (txBuffer != NULL)
            {
                uint8_t header = txBuffer->data[txBuffer->numPad - 1];
                uint8_t extHeader = txBuffer->data[txBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                /* Check advertising type. Only extended PDUs with AdvMode set to 0 are allowed */
                if (((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED) && (((extHeader & BLE_ADV_MODE_BM) >> 6) == BLE_ADV_MODE_NONCONN_NONSCAN))
                {
                    /* Extract AuxPtr information if available indicating that an AUX_CHAIN_IND will follow the AUX_SYNC_IND */
                    RCL_Handler_BLE5_getAuxPtrFromTxBuffer(txBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                }
                else
                {
                    status = RCL_CommandStatus_Error_TxBufferCorruption;
                }
            }

            /* Enter payload. Enter only one Tx Buffer corresponding to the AUX_SYNC_IND */
            uint32_t nBuffer;
            ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { 0 };
            nBuffer = RCL_Handler_BLE5_updateTxBuffers(&perAdvCmd->ctx->txBuffers, 1,
                                                       &ble5HandlerState.common.txBufferInfo,
                                                       false);
            if (nBuffer == 0)
            {
                status = RCL_CommandStatus_Error_MissingTxBuffer;
            }
            else
            {
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = advCfg;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPACONNECT) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;

                /* Once packets are copied to the TX FIFO, consume them from the Tx Buffer list and notify the caller */
                RCL_Buffer_TxBuffer *txBuffer;
                txBuffer = RCL_TxBuffer_get(&perAdvCmd->ctx->txBuffers);
                if (txBuffer == NULL)
                {
                    /* Error */
                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                }
                txBuffer->state = RCL_BufferStateFinished;
                if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                {
                    ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                }
                rclEvents.txBufferFinished = 1;

                /* Run periodic advertising next */
                runAuxSync = true;
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (rclEventsIn.gracefulStop != 0)
        {
            ble5HandlerState.perAdv.gracefulStopObserved = true;
        }

        if (lrfEvents.opDone != 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);

            if (rclEventsIn.hardStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
                runAuxSync = false;
                runAuxChain = false;
            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP ||
                        ble5HandlerState.adv.gracefulStopObserved ||
                        rclEventsIn.gracefulStop != 0)
            {
                ble5HandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                runAuxSync = false;
                runAuxChain = false;
            }
            else
            {
                if(ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                {
                    if (ble5HandlerState.common.auxPtrInfo.offsetUnits == 1 && ble5HandlerState.common.auxPtrInfo.auxOffset == 0)
                    {
                        /* Reset TX FIFO to handle auxPtr updates. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S) ;
                        /* Turn off LRF to allow new synth programming  */
                        LRF_disable();
                        runAuxChain = true;
                    }
                    else
                    {
                        runAuxChain = false;
                    }
                }
                else
                {
                    runAuxChain = false;
                }
                runAuxSync = false;
            }
            if (!runAuxSync && !runAuxChain && cmd->status == RCL_CommandStatus_Active)
            {
                cmd->status = ble5HandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
                runAuxSync = false;
                runAuxChain = false;
            }
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
            runAuxSync = false;
            runAuxChain = false;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (runAuxSync)
        {
            RCL_CommandStatus startTimeStatus;

            /* Set up channel */
            channel = perAdvCmd->channel;
            rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);

                /* Consider the current packet duration when calculating the AuxOffset */
                uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);
                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                {
                    if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, 0, false))
                    {
                        startTimeStatus = RCL_CommandStatus_Error_Param;
                    }
                }
                if (startTimeStatus < RCL_CommandStatus_Finished)
                {
                    /* Initialize counters */
                    ble5HandlerState.common.activeUpdate =
                        RCL_Handler_BLE5_initAdvScanInitStats(perAdvCmd->stats, rclSchedulerState.actualStartTime);
                    ble5HandlerState.perAdv.gracefulStopObserved = false;

                    if (rclSchedulerState.gracefulStopInfo.cmdStopEnabled || rclSchedulerState.gracefulStopInfo.schedStopEnabled)
                    {
                        /* Enable interrupt to service graceful stop */
                        hal_enable_graceful_stop_time_irq();
                    }
                }

                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = perAdvCmd->ctx->accessAddress ^ (whitenInit << 24);
                    }

                    /* Enable interrupts */
                    LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                    /* Post cmd */
                    Log_printf(RclCore, Log_VERBOSE, "Starting periodic advertising on channel %1d (access address %08X)", channel, perAdvCmd->ctx->accessAddress);
                    LRF_waitForTopsmReady();
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;
                }
            }
        }
        if (runAuxChain)
        {
            RCL_CommandStatus startTimeStatus;

            RCL_Ble5Channel channel = ble5HandlerState.common.auxPtrInfo.chIndex;

            /* Non-connectable/Non-scannable always*/
            uint16_t advCfg = 0;
            uint32_t startTimeDelta = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

            rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
            if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(rfFreq, true);
                LRF_enable();

                /* Check advertising type */
                RCL_Buffer_TxBuffer *nextTxBuffer = RCL_TxBuffer_head(&perAdvCmd->ctx->txBuffers);
                if(nextTxBuffer != NULL)
                {
                    uint8_t header = nextTxBuffer->data[nextTxBuffer->numPad - 1];
                    uint8_t extHeader = nextTxBuffer->data[nextTxBuffer->numPad - 1 + BLE_HEADER_LENGTH];

                    if (((header & BLE_PDU_TYPE_BM) == BLE_PDU_ADV_EXTENDED) && ((extHeader & BLE_ADV_MODE_BM) >> 6) == 0)
                    {
                        RCL_Handler_BLE5_getAuxPtrFromTxBuffer(nextTxBuffer, &ble5HandlerState.common.auxPtrInfo, 0);
                    }
                }
                uint32_t nBuffer = 0;
                nBuffer = RCL_Handler_BLE5_updateTxBuffers(&perAdvCmd->ctx->txBuffers, 1,
                                                           &ble5HandlerState.common.txBufferInfo,
                                                           false);
                if (nBuffer == 0)
                {
                    /* Error */
                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_MissingTxBuffer;
                }
                else
                {
                    /*
                     * Express the startTimeDelta in terms of offset units so that the relative start time is rounded up
                     * to the closest offset unit. Also add a couple of microseconds to avoid sending the packets right
                     * at the beginning of the offset window.
                     */
                    startTimeDelta += RCL_SCHEDULER_SYSTIM_US(EXT_ADV_INTERVAL_US);
                    uint32_t startTimeDeltaInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(startTimeDelta, BLE_AUX_OFFSET_30_US);
                    uint32_t relStartTime = RCL_SCHEDULER_SYSTIM_US((startTimeDeltaInOffsetUnits * BLE_AUX_OFFSET_30_US)) + RCL_SCHEDULER_SYSTIM_US(2);

                    /* Set new start time */
                    startTimeStatus = RCL_Scheduler_setNewStartRelTime(relStartTime);

                    /* Calculate auxPtr offset and update Tx FIFO if needed */
                    if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                    {
                        /* Consider the current packet duration when calculating the AuxOffset */
                        uint32_t pktDuration = RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.common.auxPtrInfo.pktLen, ble5HandlerState.common.phyFeatures);

                        if(!RCL_Handler_BLE5_updateAuxPtr(&ble5HandlerState.common.auxPtrInfo, pktDuration, 0, false))
                        {
                            startTimeStatus = RCL_CommandStatus_Error_Param;
                        }
                    }
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        cmd->status = startTimeStatus;
                        rclEvents.lastCmdDone = 1;
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_ADVCFG) = advCfg;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                        uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                        if (ble5HandlerState.common.accessAddressModification)
                        {
                            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = perAdvCmd->ctx->accessAddress ^ (whitenInit << 24);
                        }

                        /* Enable interrupts */
                        LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                        LRF_waitForTopsmReady();

                        /* Deallocate TX FIFO. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_DEALLOC >> LRFDPBE_FCMD_DATA_S);

                        /* Post cmd */
                        Log_printf(RclCore, Log_VERBOSE, "Sending AuxChain on channel %1d (access address %08X)", channel, perAdvCmd->ctx->accessAddress);
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_ADV;

                        /* Free up the TxBuffer and notify caller with an RCL event */
                        RCL_Buffer_TxBuffer *txBuffer;
                        txBuffer = RCL_TxBuffer_get(&perAdvCmd->ctx->txBuffers);
                        if (txBuffer == NULL)
                        {
                            /* Error */
                            ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                        }
                        txBuffer->state = RCL_BufferStateFinished;
                        if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                        {
                            ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                        }
                        rclEvents.txBufferFinished = 1;
                    }
                }
            }
        }
        if (rclEvents.lastCmdDone != 0)
        {
            RCL_Handler_BLE5_updateAdvScanInitStats(perAdvCmd->stats, rclSchedulerState.actualStartTime);
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_scan_init ========
 */
RCL_Events RCL_Handler_BLE5_scan_init(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBle5Scanner *scanCmd = (RCL_CmdBle5Scanner *) cmd;
    RCL_CmdBle5Initiator *initCmd = (RCL_CmdBle5Initiator *) cmd;
    uint32_t rfFreq;
    RCL_Events rclEvents = RCL_EventNone;
    RCL_CtxScanInit *ctx;
    RCL_StatsAdvScanInit *stats;
    bool followAuxPtr = false;
    RCL_ConnParams *connParams;

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_Ble5Channel channel;
        uint32_t interval = 0;
        RCL_Command_TxPower txPower;
        bool acceptLegacy;
        bool acceptExtended;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = ADV_CRC_INIT;

        /* The initial First Rx Timeout depends on the relative gaceful stop time configured for the command */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTRXTIMEOUT) = 0;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        if (cmd->cmdId == RCL_CMDID_BLE5_INITIATOR)
        {
            ble5HandlerState.scanInit.initiator = true;
            channel = initCmd->channel;
            txPower = initCmd->txPower;
            acceptLegacy = initCmd->acceptLegacy;
            acceptExtended = initCmd->acceptExtended;
        }
        else
        {
            ble5HandlerState.scanInit.initiator = false;
            channel = scanCmd->channel;
            txPower = scanCmd->txPower;
            acceptLegacy = scanCmd->acceptLegacy;
            acceptExtended = scanCmd->acceptExtended;
        }
        ble5HandlerState.scanInit.dynamicWinOffset = false; /* Default */

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);

        rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (!acceptLegacy && !acceptExtended)
        {
            cmd->status = RCL_CommandStatus_Error_Param;
        }
        else if (acceptLegacy && (cmd->phyFeatures != 0))
        {
            cmd->status = RCL_CommandStatus_Error_Param;
        }
        else if (acceptLegacy && !acceptExtended)
        {
            if (channel != BLE_ADV_CHAN_LO && channel != BLE_ADV_CHAN_MID && channel != BLE_ADV_CHAN_HI)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
            }
        }
        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                status = startTimeStatus;
            }
            else
            {
                if (ble5HandlerState.scanInit.initiator)
                {
                    ctx = initCmd->ctx;
                    stats = initCmd->stats;
                }
                else
                {
                    ctx = scanCmd->ctx;
                    stats = scanCmd->stats;
                }

                /* Initialize counters */
                ble5HandlerState.common.activeUpdate = RCL_Handler_BLE5_initAdvScanInitStats(stats,
                                                                                            rclSchedulerState.actualStartTime);

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
                uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                if (ble5HandlerState.common.accessAddressModification)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                }

                /* Configure maximum packet length */
                if (acceptExtended)
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MAXLEN) = BLE_ADV_EXTENDED_MAX_PKT_LEN;
                }
                else
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MAXLEN) = BLE_ADV_LEGACY_MAX_PKT_LEN;
                }

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRL) = ctx->ownA[0];
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRM) = ctx->ownA[1];
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRH) = ctx->ownA[2];
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRTYPE) = ctx->addrType.own;

                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
                ble5HandlerState.common.curBuffer = NULL;
                RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
                rclEventsIn.rxBufferUpdate = 0;
                ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = (ctx->rpaModeOwn << PBE_BLE5_RAM_RPAMODE_OWNADR_S) |
                                                                              (ctx->rpaModePeer << PBE_BLE5_RAM_RPAMODE_PEERADR_S);

                ble5HandlerState.common.filterListUpdateIndex = -1;
                /* Make sure status is correctly initialized */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FLSTAT) = 0;
                if (ble5HandlerState.scanInit.initiator)
                {
                    if (ctx->filterPolicy != 0)
                    {
                        /* Set filter list masks to normal accept list use: */
                        /* Bit 0: Consider enable bit */
                        /* Bit 1: Consider type bit */
                        /* Bit 3: Consider privIgn bit */
                        /* Bit 15: Consider match bit (found by PBE) */
                        /* Other bits are not checked */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = PBE_BLE5_RAM_FL2MASK_MATCH_M |
                                                                                      PBE_BLE5_RAM_FL2MASK_PRIVIGN_M |
                                                                                      PBE_BLE5_RAM_FL2MASK_TYPE_M |
                                                                                      PBE_BLE5_RAM_FL2MASK_EN_M;

                        /* Initialize filter list */
                        RCL_Handler_BLE5_InitializeFilterList(ctx->filterList, (uint32_t *)(volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2INFO0), 0);
                        ble5HandlerState.common.updatableFilterList = ctx->filterList;
                    }
                    else
                    {
                        /* Filter list not used */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                        RCL_Handler_BLE5_InitializeFilterList(NULL, (uint32_t *)(volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2INFO0), 0);
                        ble5HandlerState.common.updatableFilterList = NULL;
                    }
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0;
                    ble5HandlerState.scanInit.filterListInvertMask = 0;

                    /* Set legacy/extended acceptance configuration */
                    uint16_t aeCfg = (acceptLegacy << PBE_BLE5_RAM_AECFG_LEGACY_S) & PBE_BLE5_RAM_AECFG_LEGACY_M;
                    aeCfg |= (acceptExtended << PBE_BLE5_RAM_AECFG_EXTENDED_S) & PBE_BLE5_RAM_AECFG_EXTENDED_M;
                    if (acceptExtended)
                    {
                        /* Accept only connectable/non-scannable advertising modes */
                        aeCfg |= PBE_BLE5_RAM_AECFG_ADVMODE1_ACCEPT;

                        /* Inform the PBE about the type of channel that will be used for reception */
                        if (channel != BLE_ADV_CHAN_LO && channel != BLE_ADV_CHAN_MID && channel != BLE_ADV_CHAN_HI)
                        {
                            aeCfg |= PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;
                        }
                        /* Set backoff (only for connect requests on the secondary advertising physical channel) */
                        if (ctx->initialBackoff > 0)
                        {
                            /* Backoff definition in PBE is one count less than in Bluetooth spec */
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) = ctx->initialBackoff - 1;
                        }
                        else
                        {
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) = 0;
                        }
                    }
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;

                    /* Set filter policy */
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = (ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_INTOR_S) &
                                                                                      PBE_BLE5_RAM_FILTPOLICY_INTOR_M;

                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRL) = ctx->peerA[0];
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRM) = ctx->peerA[1];
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRH) = ctx->peerA[2];
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PEERADRTYPE) = ctx->addrType.peer;

                    RCL_Buffer_TxBuffer *txBuffer = RCL_TxBuffer_head(&ctx->txBuffers);
                    uint32_t numPad = txBuffer->numPad;
                    ble5HandlerState.scanInit.winOffsetFifoPtr =
                        (uint16_t *) LRF_getTxFifoWrAddr(offsetof(RCL_Buffer_DataEntry, pad0) + numPad + BLE_HEADER_LENGTH + BLE_WIN_OFFSET_POS);
                    ble5HandlerState.scanInit.intervalFifoPtr =
                        (uint16_t *) LRF_getTxFifoWrAddr(offsetof(RCL_Buffer_DataEntry, pad0) + numPad + BLE_HEADER_LENGTH + BLE_INTERVAL_POS);

                    if (txBuffer != NULL)
                    {
                        if (txBuffer->length >= 34)
                        {
                            ble5HandlerState.scanInit.winOffsetBufferPtr = ((uint16_t *)(txBuffer_dataByte(txBuffer, BLE_HEADER_LENGTH + BLE_WIN_OFFSET_POS)));
                            ble5HandlerState.scanInit.transmitWindowOffset = HWREGH_READ_LRF(ble5HandlerState.scanInit.winOffsetBufferPtr);

                            interval = *((uint16_t *)(txBuffer_dataByte(txBuffer, BLE_HEADER_LENGTH + BLE_INTERVAL_POS)));
                        }
                        else
                        {
                            ble5HandlerState.scanInit.transmitWindowOffset = 0;
                        }
                        if (initCmd->dynamicWinOffset)
                        {
                            if (interval == 0)
                            {
                                status = RCL_CommandStatus_Error_Param;
                            }
                            else
                            {
                                ble5HandlerState.scanInit.dynamicWinOffset = true;
                                /* Set WinSize to 2 */
                                *txBuffer_dataByte(txBuffer, BLE_HEADER_LENGTH + BLE_WIN_SIZE_POS) = 2;

                                /* TODO: See RCL-346 */
                                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_TIMPER1) = RCL_BLE5_CONNECT_SUB_INT - 1;

                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINMOD) = RCL_BLE5_CONNECT_INT_SUB_DIV * interval + RCL_BLE5_CONNECT_INT_SUB_DIV - 1;

                                ble5HandlerState.scanInit.connectInterval = interval;
                            }
                        }
                        else
                        {
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINMOD) = 0;
                        }
                    }
                    /* Enter CONNECT_IND or AUX_CONNECT_REQ */
                    ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { 0 };
                    if (RCL_Handler_BLE5_updateTxBuffers(&ctx->txBuffers, 1, &ble5HandlerState.common.txBufferInfo, false) == 0)
                    {
                        status = RCL_CommandStatus_Error_MissingTxBuffer;
                    }
                }
                else
                {
                    if (ctx->filterPolicy != 0)
                    {
                        /* Set filter list masks to normal accept list use: */
                        /* Bit 0: Consider enable bit */
                        /* Bit 1: Consider type bit */
                        /* Bit 2: Consider duplicateIgn bit */
                        /* Bit 3: Consider privIgn bit */
                        /* Bit 15: Consider match bit (found by PBE) */
                        /* Other bits are not checked */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = 0x800F;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_PRIVIGN_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_DUPLICATEIGN_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_TYPE_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_EN_M;
                        ble5HandlerState.scanInit.filterListInvertMask = 0;
                    }
                    else
                    {
                        /* Set filter list masks to duplicate address filtering: */
                        /* Bit 1: Consider type bit */
                        /* Bit 2: Consider duplicateIgn bit */
                        /* Bit 15: Consider match bit (found by PBE) */
                        /* Other bits are not checked */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_DUPLICATEIGN_M |
                                                                                      PBE_BLE5_RAM_FL1MASK_TYPE_M;
                        ble5HandlerState.scanInit.filterListInvertMask = PBE_BLE5_RAM_FL1MASK_DUPLICATEIGN_M;
                    }
                    RCL_Handler_BLE5_InitializeFilterList(ctx->filterList, (uint32_t *)(volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1INFO0),
                                                          ble5HandlerState.scanInit.filterListInvertMask);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;
                    ble5HandlerState.common.updatableFilterList = ctx->filterList;

                    /* Set active/passive scanner configuration */
                    uint16_t scanCfg = (scanCmd->activeScan << PBE_BLE5_RAM_SCANCFG_ACTPASS_S) & PBE_BLE5_RAM_SCANCFG_ACTPASS_M;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_SCANCFG) = scanCfg;

                    /* Set legacy/extended acceptance configuration */
                    uint16_t aeCfg = (acceptLegacy << PBE_BLE5_RAM_AECFG_LEGACY_S) & PBE_BLE5_RAM_AECFG_LEGACY_M;
                    aeCfg |= (acceptExtended << PBE_BLE5_RAM_AECFG_EXTENDED_S) & PBE_BLE5_RAM_AECFG_EXTENDED_M;
                    if (acceptExtended)
                    {
                        /* Scanner should accept all packets but only respond to scannable advertisements */
                        aeCfg |= PBE_BLE5_RAM_AECFG_ADVMODE0_ACCEPT;
                        aeCfg |= PBE_BLE5_RAM_AECFG_ADVMODE1_ACCEPT;
                        aeCfg |= PBE_BLE5_RAM_AECFG_ADVMODE2_ACCEPT;

                        /* Inform the PBE about the type of channel that will be used for reception */
                        if (channel != BLE_ADV_CHAN_LO && channel != BLE_ADV_CHAN_MID && channel != BLE_ADV_CHAN_HI)
                        {
                            aeCfg |= PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;
                        }
                    }
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;

                    /* Set filter policy */
                    // TODO: When available, enable SyncInfo filter policy
                    // HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = ((ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_SCANNER_S) |
                    //                                                                  (ctx->scanExtFilterPolicy << PBE_BLE5_RAM_FILTPOLICY_EXTSCANNER_S) |
                    //                                                                  (ctx->periodicSyncEstablishment << PBE_BLE5_RAM_FILTPOLICY_SYNCINFO_S)) &
                    //                                                                  (PBE_BLE5_RAM_FILTPOLICY_SCANNER_M | PBE_BLE5_RAM_FILTPOLICY_EXTSCANNER_M |
                    //                                                                   PBE_BLE5_RAM_FILTPOLICY_SYNCINFO_M);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = ((ctx->filterPolicy << PBE_BLE5_RAM_FILTPOLICY_SCANNER_S) |
                                                                                     (ctx->scanExtFilterPolicy << PBE_BLE5_RAM_FILTPOLICY_EXTSCANNER_S)) &
                                                                                     (PBE_BLE5_RAM_FILTPOLICY_SCANNER_M | PBE_BLE5_RAM_FILTPOLICY_EXTSCANNER_M);


                    /* Set backoff */
                    if (ctx->initialBackoff > 0)
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) = ctx->initialBackoff - 1;  /* Backoff definition in PBE is one less than in Bluetooth spec */
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) = 0;
                    }
                }

                if (status == RCL_CommandStatus_Active)
                {
                    uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                    LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                fifoCfg, ble5HandlerState.common.activeUpdate));

                    if (ble5HandlerState.scanInit.initiator)
                    {
                        Log_printf(RclCore, Log_VERBOSE, "Starting initiator");
                        LRF_waitForTopsmReady();
                        RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                        /* Post cmd */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_INITIATOR;

                        if (ble5HandlerState.scanInit.dynamicWinOffset)
                        {
                            /* Calculate initial winOffset while radio is starting */
                            if (acceptExtended && !acceptLegacy)
                            {
                               /*
                                * For extended advertising, a new referenceTime will be calculated once the initiator has moved to a
                                * secondary advertising channel.
                                */
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINOFFSET) = 0;
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINMOD) = 0;
                            }
                            else
                            {
                                /*
                                 * Calculate initial winOffset while radio is starting. Use the actual start time of the command as initial reference,
                                 * and consider that the transmit window starts after the end of the packet containing the AUX_CONNECT_REQ.
                                 */
                                uint32_t referenceTime = rclSchedulerState.actualStartTime +
                                    RCL_Handler_BLE5_findPacketDuration(BLE_CONNECT_MSG_LEN, ble5HandlerState.common.phyFeatures) +
                                    BLE_TRANSMIT_WINDOW_DELAY_LEGACY + 3 * RCL_BLE5_CONNECT_SUB_INT;

                                /*
                                 * Use the reference time and the requested connect time to calculate an appropriate value for the winOffset.
                                 * The winOffset value is initially set to hit the next window start by considering the desired connect interval,
                                 * but the PBE adjusts it based on the length of the window (WINMOD).
                                 */
                                uint32_t initialWinOffset = RCL_Handler_BLE5_prepareConnectTime(&initCmd->connectTime, referenceTime, interval);
                                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINOFFSET) = initialWinOffset;
                            }
                        }
                    }
                    else
                    {
                        Log_printf(RclCore, Log_VERBOSE, "Starting scanner");
                        LRF_waitForTopsmReady();
                        RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                        /* Post cmd */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_SCAN;
                    }
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }
    else
    {
        bool updateStats = false;
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                          wordLength * 4);
                    if (curBuffer != ble5HandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        ble5HandlerState.common.curBuffer = curBuffer;
                    }
                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        if(lrfEvents.rxOk && wordLength > 1)
                        {
                            uint32_t header = data32[1] >> 16;
                            uint32_t type = (header & BLE_PDU_TYPE_BM);

                            if (type == BLE_PDU_ADV_EXTENDED)
                            {
                                /* Attempt to extract an AuxPtr from the received packet */
                                RCL_Handler_BLE5_readAuxPtrFromRxBuffer(data32, &ble5HandlerState.common.auxPtrInfo);
                                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                                {
                                    /* Check auxPhy and request PHY change if needed */
                                    if (ble5HandlerState.common.channel == BLE_ADV_CHAN_LO ||
                                        ble5HandlerState.common.channel == BLE_ADV_CHAN_MID ||
                                        ble5HandlerState.common.channel == BLE_ADV_CHAN_HI)
                                    {
                                        if ((cmd->phyFeatures & 0x03) != ble5HandlerState.common.auxPtrInfo.auxPhy)
                                        {
                                            ble5HandlerState.scanInit.switchPhy = true;
                                        }
                                    }
                                    else
                                    {
                                        ble5HandlerState.scanInit.switchPhy = false;
                                    }
                                    ble5HandlerState.scanInit.followAuxPtr = true;
                                }
                                else
                                {
                                    ble5HandlerState.scanInit.followAuxPtr = false;
                                }
                                ble5HandlerState.scanInit.isExtAdv = true;
                            }
                            else if (type == BLE_PDU_AUX_CONNECT_RSP && ble5HandlerState.scanInit.initiator)
                            {
                                /* No auxiliary PDU is expected after receiving an AUX_CONNECT_RSP */
                                ble5HandlerState.scanInit.followAuxPtr = false;
                                ble5HandlerState.scanInit.isExtAdv = true;
                            }
                            else
                            {
                                /* Handle all other legacy PDU types */
                                if (ble5HandlerState.scanInit.initiator)
                                {
                                    /* Store BLE packet length if this was an accepted connectable advertiser message */
                                    if (type == BLE_PDU_ADV_IND || type == BLE_PDU_ADV_DIRECT_IND)
                                    {
                                        ble5HandlerState.scanInit.advPktLen = header >> 8;
                                    }
                                }
                                ble5HandlerState.scanInit.switchPhy = false;
                                ble5HandlerState.scanInit.isExtAdv = false;
                                ble5HandlerState.scanInit.followAuxPtr = false;
                            }
                        }
                        RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        ctx = (ble5HandlerState.scanInit.initiator) ? initCmd->ctx : scanCmd->ctx;
                        RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
                        rclEventsIn.rxBufferUpdate = 0;
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                updateStats = true;
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }

        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
            if (lrfEvents.opError == 0 && (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK ||
                                           endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR ||
                                           endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC))
            {
                /* Backoff updates are handled differently depending on whether it's a scanner or an initiator */
                ctx = (ble5HandlerState.scanInit.initiator) ? initCmd->ctx : scanCmd->ctx;

                if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK ||
                    endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR ||
                    endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC)
                {
                    if (!ble5HandlerState.scanInit.initiator)
                    {
                        if (ble5HandlerState.scanInit.isExtAdv)
                        {
                            /* Only update backoff related variables for the extended usecase after an AUX_SCAN_REQ has been sent. */
                            uint16_t chCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) & PBE_BLE5_RAM_AECFG_CHNL_M;
                            if (ble5HandlerState.scanInit.isExtAdv && (chCfg == PBE_BLE5_RAM_AECFG_CHNL_SECONDARY))
                            {
                                // TODO: Ensure that the backoff procedure is only executed when receiving AUX_SCAN_RSP PDUs and not for subsequent AUX_CHAIN_IND PDUs.
                                RCL_Handler_BLE5_updateBackoffParams(ctx, endCause);
                            }
                            /* Follow AuxPtr if needed and schedule new listening window */
                            if (ble5HandlerState.scanInit.followAuxPtr && (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK))
                            {
                                /* Turn off LRF to allow new synth programming */
                                LRF_disable();
                                if (ble5HandlerState.scanInit.switchPhy)
                                {
                                    /* Update phyFeatures while keeping the code rate selection intact. Raise a partialSetup event to handle the PHY switch. */
                                    rclSchedulerState.requestedPhyFeatures = ble5HandlerState.common.auxPtrInfo.auxPhy | (cmd->phyFeatures & 0x04);
                                    rclEvents.partialSetup = 1;
                                    followAuxPtr = false;
                                }
                                else
                                {
                                    /* No need to handle a PHY switch. Proceed with the operation. */
                                    rclSchedulerState.requestedPhyFeatures = cmd->phyFeatures;
                                    followAuxPtr = true;
                                }
                            }
                            else
                            {
                                followAuxPtr = false;
                                rclEvents.lastCmdDone = 1;
                                cmd->status = RCL_CommandStatus_Finished;
                            }
                        }
                        else
                        {
                            /* Always update the various variables associated with the backoff procedure for legacy advertising */
                            RCL_Handler_BLE5_updateBackoffParams(ctx, endCause);

                            /* Receiving on a primary channel. Restart scanner unless timed out */
                            /* Set to start immediately */
                            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setNewStartNow();
                            if (startTimeStatus >= RCL_CommandStatus_Finished)
                            {
                                cmd->status = startTimeStatus;
                                rclEvents.lastCmdDone = 1;
                            }
                            else
                            {
                                if (!(rclSchedulerState.hardStopInfo.apiStopEnabled || rclSchedulerState.gracefulStopInfo.apiStopEnabled))
                                {
                                    Log_printf(RclCore, Log_VERBOSE, "Restarting scanner");
                                    /* Reset TXFIFO - needed due to LPRF_PHY-511 */
                                    /* Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);
                                    /* Post cmd */
                                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_SCAN;
                                    if (ble5HandlerState.common.activeUpdate)
                                    {
                                        updateStats = true;
                                    }
                                }
                            }
                        }
                    }
                    else /* Initiator */
                    {
                        RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;

                        if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
                        {
                            if (ble5HandlerState.scanInit.isExtAdv && ble5HandlerState.scanInit.followAuxPtr)
                            {
                                /* Turn off LRF to allow new synth programming  */
                                LRF_disable();
                                /*  Check if a PHY switch was requested */
                                if (ble5HandlerState.scanInit.switchPhy)
                                {
                                    /* Update phyFeatures while keeping the code rate selection intact. Raise a partialSetup event to handle the PHY switch. */
                                    rclSchedulerState.requestedPhyFeatures = ble5HandlerState.common.auxPtrInfo.auxPhy | (cmd->phyFeatures & 0x04);
                                    rclEvents.partialSetup = 1;
                                    followAuxPtr = false;
                                }
                                else
                                {
                                    rclSchedulerState.requestedPhyFeatures = cmd->phyFeatures;
                                    followAuxPtr = true;
                                }
                            }
                            else
                            {
                                endStatus = RCL_CommandStatus_Connect;
                                /* Find connect time */
                                uint32_t transmitWindowOffset;
                                /* 32-bit acccess to also read LASTTIMESTAMPH */
                                uint32_t eventTime = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) - ble5HandlerState.common.timestampAdjust;
                                uint32_t connectTime;
                                if (ble5HandlerState.scanInit.dynamicWinOffset)
                                {
                                    transmitWindowOffset = HWREGH_READ_LRF(ble5HandlerState.scanInit.winOffsetFifoPtr);
                                    /* Write back to transmit buffer */
                                    HWREGH_WRITE_LRF(ble5HandlerState.scanInit.winOffsetBufferPtr) = transmitWindowOffset;
                                }
                                else
                                {
                                    transmitWindowOffset = ble5HandlerState.scanInit.transmitWindowOffset;
                                }
                                Log_printf(RclCore, Log_VERBOSE, "Connection formed, transmit window offset %1d", transmitWindowOffset);

                                /* Find the connect time and report it to the caller */
                                uint32_t referenceTime = eventTime;
                                if (ble5HandlerState.scanInit.isExtAdv && !ble5HandlerState.scanInit.followAuxPtr)
                                {
                                    /*
                                     * The transmit window starts after the end of the packet containing the AUX_CONNECT_REQ, but evenTime corresponds to the time at which
                                     * the AUX_CONNECT_RSP was received. Account for this by substracting the T_IFS.
                                     */
                                    referenceTime -= BLE_T_IFS;
                                    referenceTime += transmitWindowOffset * BLE_CONNECT_INT_UNIT;
                                    /* For extended advertising, PHY needs to be considered when calculating the transmit window delay */
                                    referenceTime += ((ble5HandlerState.common.phyFeatures & BLE_PHY_FEATURE_PHY_MASK) == BLE_PHY_FEATURE_PHY_CODED) ?
                                                      BLE_TRANSMIT_WINDOW_DELAY_EXT_CODED : BLE_TRANSMIT_WINDOW_DELAY_EXT_UNCODED;
                                }
                                else
                                {
                                    referenceTime += RCL_Handler_BLE5_findPacketDuration(ble5HandlerState.scanInit.advPktLen, ble5HandlerState.common.phyFeatures) +
                                                     BLE_T_IFS + RCL_Handler_BLE5_findPacketDuration(BLE_CONNECT_MSG_LEN, ble5HandlerState.common.phyFeatures) +
                                                     BLE_TRANSMIT_WINDOW_DELAY_LEGACY + transmitWindowOffset * BLE_CONNECT_INT_UNIT;
                                }

                                if (ble5HandlerState.scanInit.dynamicWinOffset)
                                {
                                    connectTime = RCL_Handler_BLE5_findConnectTime(initCmd->connectTime, referenceTime, ble5HandlerState.scanInit.connectInterval);
                                    /* Check that the connect time is within the bounds expected; if not (due to timer drift), report a different connect time */
                                    if (connectTime > referenceTime + 2 * BLE_CONNECT_INT_UNIT)
                                    {
                                        Log_printf(RclCore, Log_WARNING, "Transmitted window offset did not match requested transmit time. Reporting a different connect time");
                                        connectTime = referenceTime + BLE_CONNECT_INT_UNIT / 2;
                                    }
                                    else
                                    {
                                        Log_printf(RclCore, Log_DEBUG, "Margins: %1d us and %1d us", (connectTime - referenceTime + 2)/4, (referenceTime + 2 * BLE_CONNECT_INT_UNIT - connectTime + 2)/4);
                                    }
                                }
                                else
                                {
                                    connectTime = referenceTime + BLE_CONNECT_INT_UNIT / 2;
                                }
                                initCmd->connectTime = connectTime;
                                followAuxPtr = false;
                                rclEvents.lastCmdDone = 1;
                                cmd->status = endStatus;
                            }

                            /* Only update backOff related variables for the extended usecase after an AUX_CONNECT_REQ has been sent */
                            uint16_t chCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) & PBE_BLE5_RAM_AECFG_CHNL_M;
                            if (ble5HandlerState.scanInit.isExtAdv && chCfg == PBE_BLE5_RAM_AECFG_CHNL_SECONDARY)
                            {
                                RCL_Handler_BLE5_updateBackoffParams(ctx, endCause);
                            }
                        }
                    }
                }
            }
            else
            {
                RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
                if (lrfEvents.opError != 0 && endStatus == RCL_CommandStatus_Finished)
                {
                    endStatus = RCL_Handler_BLE5_findPbeErrorEndStatus(endCause);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;

                }
                else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else if (rclSchedulerState.hardStopInfo.apiStopEnabled && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);

                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else if (rclSchedulerState.gracefulStopInfo.apiStopEnabled && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else
                {
                    /* No change of status */
                }
            }
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (rclEvents.lastCmdDone != 0)
        {
            /* Write back backoff count */
            if (!ble5HandlerState.scanInit.initiator)
            {
                scanCmd->ctx->initialBackoff = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) + 1; /* Backoff definition in PBE is one less than in Bluetooth spec */
            }
            if (ble5HandlerState.scanInit.initiator && ble5HandlerState.scanInit.isExtAdv)
            {
                initCmd->ctx->initialBackoff = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) + 1; /* Backoff definition in PBE is one less than in Bluetooth spec */
            }
            updateStats = true;
        }
        if (updateStats)
        {
            RCL_Handler_BLE5_updateAdvScanInitStats((ble5HandlerState.scanInit.initiator) ? initCmd->stats : scanCmd->stats,
                                                    rclSchedulerState.actualStartTime);
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            ctx = (ble5HandlerState.scanInit.initiator) ? initCmd->ctx : scanCmd->ctx;
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }
        if (rclEventsIn.handlerCmdUpdate != 0)
        {
            if (ble5HandlerState.scanInit.followAuxPtr && ble5HandlerState.scanInit.switchPhy)
            {
                /* PHY change concluded successfully. Proceed with the scanner restart */
                followAuxPtr = true;
            }
            else
            {
                followAuxPtr = false;
            }
            if (ble5HandlerState.common.updatableFilterList != NULL && ble5HandlerState.common.filterListUpdateIndex >= 0)
            {
                uint32_t index = (uint32_t) ble5HandlerState.common.filterListUpdateIndex;
                uint32_t *targetPtr = (uint32_t *) (ble5HandlerState.scanInit.initiator ? (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2INFO0) : (volatile unsigned short*) (LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1INFO0));

                RCL_Handler_BLE5_updateFilterListEntry(ble5HandlerState.common.updatableFilterList,
                    targetPtr,
                    ble5HandlerState.scanInit.filterListInvertMask, index);
                ble5HandlerState.common.filterListUpdateIndex = -1;
            }
        }
        if (followAuxPtr)
        {
            uint32_t maxAuxPtrWaitTime = (ble5HandlerState.scanInit.initiator) ? initCmd->maxAuxPtrWaitTime : scanCmd->maxAuxPtrWaitTime;
            uint32_t auxOffsetUs = ble5HandlerState.common.auxPtrInfo.offsetUnits ? (ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_300_US) :
                                                                                    (ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_30_US);

            /* Switch to the channel indicated by the auxPtr */
            RCL_Ble5Channel nextChannel = (RCL_Ble5Channel) ble5HandlerState.common.auxPtrInfo.chIndex;
            rfFreq = RCL_Handler_BLE5_findRfFreq(nextChannel);

            if ((maxAuxPtrWaitTime != 0) && (maxAuxPtrWaitTime < auxOffsetUs))
            {
                cmd->status = RCL_CommandStatus_MaxAuxWaitTimeExceeded;
                rclEvents.lastCmdDone = 1;
            }
            else if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                if (ble5HandlerState.scanInit.initiator)
                {
                    connParams = initCmd->ctx->connParams;
                    if (initCmd->ctx->connParams != NULL)
                    {
                        /* Check received AuxPhy to determine if connection parameters need to be updated */
                        if (ble5HandlerState.common.auxPtrInfo.auxPhy == BLE_PHY_FEATURE_PHY_2MBPS)
                        {
                            /* Retry TX FIFO and point to the correct AUX_CONNECT_REQ. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RETRY >> LRFDPBE_FCMD_DATA_S);

                            /* Update parameters. Use position of Interval field as reference for other connection parameters */
                            HWREGH_WRITE_LRF(ble5HandlerState.scanInit.intervalFifoPtr) = connParams->ble2M.interval;
                            HWREGH_WRITE_LRF(((uintptr_t) ble5HandlerState.scanInit.intervalFifoPtr) + (BLE_LATENCY_POS - BLE_INTERVAL_POS)) = connParams->ble2M.latency;
                            HWREGH_WRITE_LRF(((uintptr_t) ble5HandlerState.scanInit.intervalFifoPtr) + (BLE_TIMEOUT_POS - BLE_INTERVAL_POS)) = connParams->ble2M.timeout;
                        }
                        else if (ble5HandlerState.common.auxPtrInfo.auxPhy == BLE_PHY_FEATURE_PHY_CODED)
                        {
                            /* Retry TX FIFO and point to the correct AUX_CONNECT_REQ. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RETRY >> LRFDPBE_FCMD_DATA_S);

                            /* Update parameters. Use position of Interval field as reference for other connection parameters */
                            HWREGH_WRITE_LRF(ble5HandlerState.scanInit.intervalFifoPtr) = connParams->bleCoded.interval;
                            HWREGH_WRITE_LRF(((uintptr_t) ble5HandlerState.scanInit.intervalFifoPtr) + (BLE_LATENCY_POS - BLE_INTERVAL_POS)) = connParams->bleCoded.latency;
                            HWREGH_WRITE_LRF(((uintptr_t) ble5HandlerState.scanInit.intervalFifoPtr) + (BLE_TIMEOUT_POS - BLE_INTERVAL_POS)) = connParams->bleCoded.timeout;
                        }
                        else
                        {
                            /* No need to update connection parameters for LE 1M PHY */
                        }
                    }
                    else
                    {
                        /* No change of the connection parameters regardless of the PHY */
                    }
                }

                /* Begin the start time calculation of the receive window by getting the time of the last sync plus the aux offset given in the AuxPtr */
                /* 32-bit access to also read LASTTIMESTAMPH */
                uint32_t startTime = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) - ble5HandlerState.common.timestampAdjust;

                /* Update timestamps for the next packet if there was been a PHY change */
                if (ble5HandlerState.scanInit.switchPhy)
                {
                    RCL_Handler_BLE5_setPhy(rclSchedulerState.requestedPhyFeatures);
                    ble5HandlerState.scanInit.switchPhy = false;
                }

                uint32_t offset = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ?
                                                          ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_300_US :
                                                          ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_30_US);
                startTime += offset;

                /* Use the local and remote clock accuracies to find the clock error contribution */
                uint16_t localClkAccuracy = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.scanInit.initiator ?
                                                                    initCmd->ctx->localClockAccuracy :
                                                                    scanCmd->ctx->localClockAccuracy);
                uint16_t remoteClkAccuracy = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ?
                                                                     BLE_SCALED_CLK_ACCURACY_500PPM :
                                                                     BLE_SCALED_CLK_ACCURACY_50PPM);

                /* Find clock error contribution. Add 1 us (4 systim units) to correct for rounding down. Also consider the sleep/active clock adjustments */
                uint16_t remoteClkError = (uint16_t)((((offset * remoteClkAccuracy) >> BLE_CLK_ACCURACY_SCALE_FACTOR)) + 4 + RCL_SCHEDULER_SYSTIM_US(2));
                uint16_t localClkError = (uint16_t)((((offset * localClkAccuracy) >> BLE_CLK_ACCURACY_SCALE_FACTOR)) + 4 + RCL_SCHEDULER_SYSTIM_US(16));

                /* Calculate the needed window widening. Consider the allowed deviations for active clock accuracy and sleep clock accuracy */
                uint16_t windowWidening = remoteClkError + localClkError;

                /* Add some additional time to the window widening due to missing constants describing the Rx Start Overhead. See RCL-513. */
                startTime -= (windowWidening + RX_START_OVERHEAD);

                /* Begin the timeout calculation by considering that the end of receive window occurs one offset unit after startTime */
                uint16_t endTime = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ? BLE_AUX_OFFSET_300_US : BLE_AUX_OFFSET_30_US);
                uint16_t timeout = windowWidening + endTime + windowWidening;

#ifdef DeviceFamily_CC27XX
                startTime -= RCL_SCHEDULER_SYSTIM_US(100);
                timeout += RCL_SCHEDULER_SYSTIM_US(200);
#endif
                /* Set timeout by writing to FIRSTRXTIMEOUT. Consider the necessary Rx sync Overhead. See RCL-513. */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTRXTIMEOUT) = timeout + RCL_Handler_BLE5_findRxSyncOverhead(ble5HandlerState.common.phyFeatures);

                /* Program frequency word */
                LRF_programFrequency(rfFreq, false);
                /* Enable radio */
                LRF_enable();

                uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(nextChannel);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;

                /* Inform the PBE that we have moved to a secondary channel */
                uint16_t aeCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) | PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;

                if (ble5HandlerState.common.accessAddressModification)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ADV_ACCESS_ADDRESS ^ (whitenInit << 24);
                }

                if (ble5HandlerState.scanInit.dynamicWinOffset)
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINMOD) = RCL_BLE5_CONNECT_INT_SUB_DIV * ble5HandlerState.scanInit.connectInterval + RCL_BLE5_CONNECT_INT_SUB_DIV - 1;
                }

                /* Set new start time */
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setNewStartAbsTime(startTime, true);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    cmd->status = RCL_CommandStatus_Active;
                    /* Set up sync found capture */
                    hal_setup_sync_found_cap();

                    uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                    LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                fifoCfg, ble5HandlerState.common.activeUpdate));
                    Log_printf(RclCore, Log_VERBOSE, "Following AuxPointer on channel: %d", nextChannel);
                    LRF_waitForTopsmReady();

                    if (!ble5HandlerState.scanInit.initiator)
                    {
                        /* Post cmd */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_SCAN;
                    }
                    else
                    {
                        /* Post cmd */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_INITIATOR;

                        if (ble5HandlerState.scanInit.dynamicWinOffset)
                        {
                            /*
                             * Calculate initial winOffset while radio is starting. Use the actual start time of the command as initial reference,
                             * and consider that the transmit window starts after the end of the packet containing the AUX_CONNECT_REQ.
                             */
                            uint32_t referenceTime = rclSchedulerState.actualStartTime +
                                RCL_Handler_BLE5_findPacketDuration(BLE_CONNECT_MSG_LEN, ble5HandlerState.common.phyFeatures) +
                                3 * RCL_BLE5_CONNECT_SUB_INT;
                            /* The transmitWindowDelay needs to take into account the type of PHY in use */
                            referenceTime += ((ble5HandlerState.common.phyFeatures & BLE_PHY_FEATURE_PHY_MASK) == BLE_PHY_FEATURE_PHY_CODED) ?
                                              BLE_TRANSMIT_WINDOW_DELAY_EXT_CODED : BLE_TRANSMIT_WINDOW_DELAY_EXT_UNCODED;

                            /*
                             * Use the reference time and the requested connect time to calculate an appropriate value for the winOffset.
                             * The winOffset value is initially set to hit the next window start by considering the desired connect interval,
                             * but the PBE adjusts it based on the length of the window (WINMOD).
                             */
                            uint32_t initialWinOffset = RCL_Handler_BLE5_prepareConnectTime(&initCmd->connectTime, referenceTime,
                                                                                            ble5HandlerState.scanInit.connectInterval);
                            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WINOFFSET) = initialWinOffset;
                        }
                    }

                    if (ble5HandlerState.common.activeUpdate)
                    {
                        RCL_Handler_BLE5_updateAdvScanInitStats((ble5HandlerState.scanInit.initiator) ? initCmd->stats : scanCmd->stats,
                                                                 rclSchedulerState.actualStartTime);

                    }
                }
            }
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        ble5HandlerState.common.updatableFilterList = NULL;
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_periodicScan ========
 */
RCL_Events RCL_Handler_BLE5_periodicScan(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBle5PeriodicScanner *perScanCmd = (RCL_CmdBle5PeriodicScanner *) cmd;
    uint32_t rfFreq;
    RCL_Events rclEvents = RCL_EventNone;
    bool followAuxPtr = false;

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_Ble5Channel channel;
        RCL_Command_TxPower txPower;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = perScanCmd->ctx->accessAddress;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = perScanCmd->ctx->crcInit << 8;

        /* The initial First Rx Timeout depends on the relative gaceful stop time configured for the command */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTRXTIMEOUT) = 0;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        channel = perScanCmd->channel;
        txPower = perScanCmd->txPower;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);

        rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (channel != BLE_ADV_CHAN_LO && channel != BLE_ADV_CHAN_MID && channel != BLE_ADV_CHAN_HI)
        {
            cmd->status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                status = startTimeStatus;
            }
            else
            {
                /* Initialize counters */
                ble5HandlerState.common.activeUpdate = RCL_Handler_BLE5_initAdvScanInitStats(perScanCmd->stats,
                                                                                             rclSchedulerState.actualStartTime);

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;

                /* Only accept non-connectable/non-scannable extended PDUs coming on a secondary channel */
                uint16_t aeCfg = PBE_BLE5_RAM_AECFG_EXTENDED_EN | PBE_BLE5_RAM_AECFG_ADVMODE0_ACCEPT | PBE_BLE5_RAM_AECFG_CHNL_SECONDARY;

                uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;

                if (ble5HandlerState.common.accessAddressModification)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = perScanCmd->ctx->accessAddress ^ (whitenInit << 24);
                }

                /* Configure maximum packet length */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MAXLEN) = BLE_ADV_EXTENDED_MAX_PKT_LEN;

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRL) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRM) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRH) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OWNADRTYPE) = 0;

                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
                ble5HandlerState.common.curBuffer = NULL;
                RCL_Handler_BLE5_updateRxCurBufferAndFifo(&perScanCmd->ctx->rxBuffers);
                rclEventsIn.rxBufferUpdate = 0;

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RPAMODE) = 0;

                ble5HandlerState.common.filterListUpdateIndex = -1;
                /* Make sure status is correctly initialized */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FLSTAT) = 0;

                /* Set filter list masks to duplicate address filtering: */
                /* Bit 1: Consider type bit */
                /* Bit 2: Consider duplicateIgn bit */
                /* Bit 15: Consider match bit (found by PBE) */
                /* Other bits are not checked */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL1MASK) = PBE_BLE5_RAM_FL1MASK_MATCH_M |
                                                                              PBE_BLE5_RAM_FL1MASK_DUPLICATEIGN_M |
                                                                              PBE_BLE5_RAM_FL1MASK_TYPE_M;
                ble5HandlerState.scanInit.filterListInvertMask = PBE_BLE5_RAM_FL1MASK_DUPLICATEIGN_M;

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FL2MASK) = 0;

                /* Set passive scanner configuration. No scan requests are sent */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_SCANCFG) = 0;

                /* Set acceptance configuration */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_AECFG) = aeCfg;

                /* Set filter policy */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FILTPOLICY) = 0;

                if (status == RCL_CommandStatus_Active)
                {
                    uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                    LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                fifoCfg, ble5HandlerState.common.activeUpdate));

                    Log_printf(RclCore, Log_VERBOSE, "Starting periodic scanner");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_SCAN;

                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }
    else
    {
        bool updateStats = false;
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                          wordLength * 4);
                    if (curBuffer != ble5HandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        ble5HandlerState.common.curBuffer = curBuffer;
                    }
                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        if(lrfEvents.rxOk && wordLength > 1)
                        {
                            uint32_t header = data32[1] >> 16;
                            uint32_t type = (header & BLE_PDU_TYPE_BM);

                            if (type == BLE_PDU_ADV_EXTENDED)
                            {
                                /* Attempt to extract an AuxPtr from the received packet */
                                RCL_Handler_BLE5_readAuxPtrFromRxBuffer(data32, &ble5HandlerState.common.auxPtrInfo);
                                if (ble5HandlerState.common.auxPtrInfo.auxPtrPresent)
                                {
                                    ble5HandlerState.perScan.followAuxPtr = true;
                                }
                                else
                                {
                                    ble5HandlerState.perScan.followAuxPtr = false;
                                }
                                RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                                /* Raise event */
                                rclEvents.rxEntryAvail = 1;
                                /* Adjust effective FIFO size */
                                RCL_Handler_BLE5_updateRxCurBufferAndFifo(&perScanCmd->ctx->rxBuffers);
                                rclEventsIn.rxBufferUpdate = 0;
                            }
                            else
                            {
                                rclEvents.lastCmdDone = 1;
                                cmd->status = RCL_CommandStatus_Error_RxBufferCorruption;
                            }
                        }
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                updateStats = true;
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }

        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
            if (lrfEvents.opError == 0 && (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK ||
                                           endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR ||
                                           endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC))
            {
                if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK && ble5HandlerState.perScan.followAuxPtr)
                {
                    /* Turn off LRF to allow new synth programming */
                    LRF_disable();
                    followAuxPtr = true;
                }
                else
                {
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = RCL_CommandStatus_Finished;
                }
            }
            else
            {
                RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
                if (lrfEvents.opError != 0 && endStatus == RCL_CommandStatus_Finished)
                {
                    endStatus = RCL_Handler_BLE5_findPbeErrorEndStatus(endCause);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;

                }
                else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else if (rclSchedulerState.hardStopInfo.apiStopEnabled && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);

                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else if (rclSchedulerState.gracefulStopInfo.apiStopEnabled && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    followAuxPtr = false;
                    rclEvents.lastCmdDone = 1;
                    cmd->status = endStatus;
                }
                else
                {
                    /* No change of status */
                }
            }
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (rclEvents.lastCmdDone != 0)
        {
            updateStats = true;
        }
        if (updateStats)
        {
            RCL_Handler_BLE5_updateAdvScanInitStats(perScanCmd->stats, rclSchedulerState.actualStartTime);
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&perScanCmd->ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }
        if (followAuxPtr)
        {
            uint32_t maxAuxPtrWaitTime = perScanCmd->maxAuxPtrWaitTime;
            uint32_t auxOffsetUs = ble5HandlerState.common.auxPtrInfo.offsetUnits ? (ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_300_US) :
                                                                                    (ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_30_US);

            /* Switch to the channel indicated by the auxPtr */
            RCL_Ble5Channel nextChannel = (RCL_Ble5Channel) ble5HandlerState.common.auxPtrInfo.chIndex;
            rfFreq = RCL_Handler_BLE5_findRfFreq(nextChannel);

            if (maxAuxPtrWaitTime < auxOffsetUs)
            {
                cmd->status = RCL_CommandStatus_MaxAuxWaitTimeExceeded;
                rclEvents.lastCmdDone = 1;
            }
            else if (rfFreq == 0)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Begin the start time calculation of the receive window by getting the time of the last sync plus the aux offset given in the AuxPtr */
                /* 32-bit access to also read LASTTIMESTAMPH */
                uint32_t startTime = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) - ble5HandlerState.common.timestampAdjust;
                uint32_t offset = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ?
                                                          ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_300_US :
                                                          ble5HandlerState.common.auxPtrInfo.auxOffset * BLE_AUX_OFFSET_30_US);
                startTime += offset;

                /* Use the local and remote clock accuracies to find the clock error contribution */
                uint16_t localClkAccuracy = RCL_SCHEDULER_SYSTIM_US(perScanCmd->ctx->localClockAccuracy);
                uint16_t remoteClkAccuracy = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ?
                                                                     BLE_SCALED_CLK_ACCURACY_500PPM :
                                                                     BLE_SCALED_CLK_ACCURACY_50PPM);

                /* Find clock error contribution. Add 1 us (4 systim units) to correct for rounding down. Also consider the sleep/active clock adjustments */
                uint16_t remoteClkError = (uint16_t)((((offset * remoteClkAccuracy) >> BLE_CLK_ACCURACY_SCALE_FACTOR)) + 4 + RCL_SCHEDULER_SYSTIM_US(2));
                uint16_t localClkError = (uint16_t)((((offset * localClkAccuracy) >> BLE_CLK_ACCURACY_SCALE_FACTOR)) + 4 + RCL_SCHEDULER_SYSTIM_US(16));

                /* Calculate the needed window widening. Consider the allowed deviations for active clock accuracy and sleep clock accuracy */
                uint16_t windowWidening = remoteClkError + localClkError;

                /* Add some additional time to the window widening due to missing constants describing the Rx Start Overhead. See RCL-513. */
                startTime -= (windowWidening + RX_START_OVERHEAD);

                /* Begin the timeout calculation by considering that the end of receive window occurs one offset unit after startTime */
                uint16_t endTime = RCL_SCHEDULER_SYSTIM_US(ble5HandlerState.common.auxPtrInfo.offsetUnits ? BLE_AUX_OFFSET_300_US : BLE_AUX_OFFSET_30_US);
                uint16_t timeout = windowWidening + endTime + windowWidening;

#ifdef DeviceFamily_CC27XX
                startTime -= RCL_SCHEDULER_SYSTIM_US(100);
                timeout += RCL_SCHEDULER_SYSTIM_US(200);
#endif
                /* Set timeout by writing to FIRSTRXTIMEOUT. Consider the necessary Rx sync Overhead. See RCL-513. */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTRXTIMEOUT) = timeout + RCL_Handler_BLE5_findRxSyncOverhead(ble5HandlerState.common.phyFeatures);

                /* Program frequency word */
                LRF_programFrequency(rfFreq, false);
                /* Enable radio */
                LRF_enable();

                uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(nextChannel);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;

                if (ble5HandlerState.common.accessAddressModification)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = perScanCmd->ctx->accessAddress ^ (whitenInit << 24);
                }

                /* Set new start time */
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setNewStartAbsTime(startTime, true);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    cmd->status = RCL_CommandStatus_Active;
                    /* Set up sync found capture */
                    hal_setup_sync_found_cap();

                    uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                    LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                fifoCfg, ble5HandlerState.common.activeUpdate));
                    Log_printf(RclCore, Log_VERBOSE, "Following AuxPointer on channel: %d", nextChannel);
                    LRF_waitForTopsmReady();

                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_SCAN;

                    if (ble5HandlerState.common.activeUpdate)
                    {
                        RCL_Handler_BLE5_updateAdvScanInitStats(perScanCmd->stats, rclSchedulerState.actualStartTime);
                    }
                }
            }
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        ble5HandlerState.common.updatableFilterList = NULL;
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_conn ========
 */
RCL_Events RCL_Handler_BLE5_conn(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    uint32_t rfFreq;
    RCL_CmdBle5Connection *connCmd = (RCL_CmdBle5Connection *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        uint32_t startDelay = 0;
        RCL_CtxConnection *ctx = connCmd->ctx;
        uint32_t crcInit = ctx->crcInit;
        uint32_t accessAddress = ctx->accessAddress;

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress;

        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = crcInit << 8;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MDCFG) = 0;

        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_SEQSTAT) = ctx->seqStat;

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        rfFreq = RCL_Handler_BLE5_findRfFreq(connCmd->channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(connCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, !ctx->isPeripheral);

            /* Enable radio */
            LRF_enable();

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = 0;
            uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(connCmd->channel);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
            if (ble5HandlerState.common.accessAddressModification)
            {
                HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress ^ (whitenInit << 24);
            }

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MAXLEN) = BLE_MAX_PKT_LEN;
            /* Set up timers */

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                status = startTimeStatus;
            }
            else
            {
                /* Initialize counters */
                ble5HandlerState.common.activeUpdate = RCL_Handler_BLE5_initConnStats(connCmd->stats, rclSchedulerState.actualStartTime);
                if (cmd->scheduling == RCL_Schedule_AbsTime)
                {
                    startDelay = rclSchedulerState.actualStartTime - cmd->timing.absStartTime;
                }
                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
                ble5HandlerState.common.curBuffer = NULL;
                RCL_Handler_BLE5_updateRxCurBufferAndFifo(&connCmd->ctx->rxBuffers);
                rclEventsIn.rxBufferUpdate = 0;
                ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

                /* Enter TX payload - maximum two packets in the beginning */
                bool retransPossible = ctx->isPeripheral &&
                    ((ctx->seqStat & (PBE_BLE5_RAM_SEQSTAT_EMPTY_M | PBE_BLE5_RAM_SEQSTAT_FIRSTPKT_M)) == 0);
                ble5HandlerState.common.txBufferInfo = (RCL_TxBufferInfo) { .isConnBuffer = true };
                RCL_Handler_BLE5_updateTxBuffers(&ctx->txBuffers, 2,
                                                 &ble5HandlerState.common.txBufferInfo, retransPossible);

                uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                            LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                            LRF_EventRxNok.value | LRF_EventRxEmpty.value |
                                                                            LRF_EventRxBufFull.value | LRF_EventTxDone.value,
                                                                            fifoCfg, ble5HandlerState.common.activeUpdate));
                if (ctx->isPeripheral)
                {
                    int32_t relRxTimeoutTime = connCmd->relRxTimeoutTime;
                    if (relRxTimeoutTime != 0)
                    {
                        relRxTimeoutTime -= startDelay;

                        if (relRxTimeoutTime <= 0)
                        {
                            status = RCL_CommandStatus_RxTimeout;
                        }
                    }

                    if (status == RCL_CommandStatus_Active)
                    {
                        /* Set timeout */
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTRXTIMEOUT) = relRxTimeoutTime;

                        Log_printf(RclCore, Log_VERBOSE, "Starting peripheral");
                        LRF_waitForTopsmReady();
                        RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                        /* Post cmd */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_PERIPHERAL;
                    }
                }
                else
                {
                    Log_printf(RclCore, Log_VERBOSE, "Starting central");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_CENTRAL;
                }
                if (status == RCL_CommandStatus_Active)
                {
                    /* Insert any more TX payload that can fit */
                    RCL_Handler_BLE5_updateTxBuffers(&ctx->txBuffers,
                                                    UINT32_MAX,
                                                    &ble5HandlerState.common.txBufferInfo,
                                                    false);
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }
    else
    {
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxEmpty != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                          wordLength * 4);
                    if (curBuffer != ble5HandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        ble5HandlerState.common.curBuffer = curBuffer;
                    }

                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        RCL_Handler_BLE5_updateRxCurBufferAndFifo(&connCmd->ctx->rxBuffers);
                        rclEventsIn.rxBufferUpdate = 0;
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                RCL_Handler_BLE5_updateConnStats(connCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if (lrfEvents.txDone != 0)
        {
            /* Free up finished tx buffers */
            uint32_t bytesWritten = ble5HandlerState.common.txFifoSz - LRF_getTxFifoWritable();
            uint32_t numBytes = ble5HandlerState.common.txBufferInfo.numBytes;
            int32_t numBuffers = ble5HandlerState.common.txBufferInfo.numBuffers;
            if (bytesWritten < numBytes)
            {
                RCL_Buffer_TxBuffer *txBuffer;
                do
                {
                    uint32_t entryBytes;
                    txBuffer = RCL_TxBuffer_get(&connCmd->ctx->txBuffers);
                    if (txBuffer == NULL)
                    {
                        /* Error */
                        break;
                    }
                    txBuffer->state = RCL_BufferStateFinished;
                    numBuffers--;
                    entryBytes = RCL_Buffer_DataEntry_paddedLen(txBuffer->length);
                    numBytes -= entryBytes;
                    if (txBuffer == ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer)
                    {
                        ble5HandlerState.common.txBufferInfo.lastEnteredTxBuffer = NULL;
                        ble5HandlerState.common.txBufferInfo.lastTxHdr = NULL;
                    }

                } while (bytesWritten < numBytes);

                /* Check consistency */
                if (numBytes != bytesWritten || numBuffers < 0)
                {
                    /* Error */
                    ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                    /* Send abort */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                }
                else
                {
                    ble5HandlerState.common.txBufferInfo.numBytes = numBytes;
                    ble5HandlerState.common.txBufferInfo.numBuffers = numBuffers;
                    rclEvents.txBufferFinished = 1;
                }
                /* Set flag to insert more data if possible */
                rclEventsIn.txBufferUpdate = 1;
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }

        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
            RCL_CommandStatus endStatus;
            connCmd->ctx->seqStat = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_SEQSTAT);
            /* Disable radio */

            rclEvents.lastCmdDone = 1;
            endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                uint16_t pbeEndcause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
                /* Check if we need to change status */
                if (lrfEvents.opError != 0)
                {
                    endStatus = RCL_Handler_BLE5_findPbeErrorEndStatus(pbeEndcause);
                }
                else
                {
                    if (pbeEndcause == PBE_COMMON_RAM_ENDCAUSE_STAT_RXTIMEOUT)
                    {
                        endStatus = RCL_CommandStatus_RxTimeout;
                    }
                    else if (pbeEndcause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                    {
                        endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    }
                    else if (pbeEndcause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC)
                    {
                        endStatus = RCL_CommandStatus_NoSync;
                    }
                    else if (pbeEndcause == PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR)
                    {
                            endStatus = RCL_CommandStatus_RxErr;
                    }
                    else if (pbeEndcause == PBE_COMMON_RAM_ENDCAUSE_STAT_MAXNAK)
                    {
                        endStatus = RCL_CommandStatus_MaxNak;
                    }
                    else
                    {
                        /* No change of status */
                    }
                }
            }
            cmd->status = endStatus;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
        if (rclEvents.lastCmdDone != 0)
        {
            RCL_Handler_BLE5_updateConnStats(connCmd->stats, rclSchedulerState.actualStartTime);
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&connCmd->ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }
        if (rclEventsIn.txBufferUpdate != 0)
        {
            /* Insert any more TX payload that can fit */
            RCL_Handler_BLE5_updateTxBuffers(&connCmd->ctx->txBuffers,
                                             UINT32_MAX,
                                             &ble5HandlerState.common.txBufferInfo,
                                             false);
            rclEventsIn.txBufferUpdate = 0;
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_dtmTx ========
 */
RCL_Events RCL_Handler_BLE5_dtmTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBle5DtmTx *txCmd = (RCL_CmdBle5DtmTx *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_Ble5Channel channel;
        uint8_t byteVal;
        uint32_t whitenPoly;
        uint32_t whitenSeed;
        uint32_t rfFreq;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = DTM_ACCESS_ADDRESS;
        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = ADV_CRC_INIT;
        /* Set PBE timer 1 prescaler to use 1 us ticks */
        uint16_t timPre = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TIMPRE);
        ble5HandlerState.dtmTx.storedPbeTimPre = timPre;
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_TIMPRE) = (timPre & ~LRFDPBE_TIMPRE_PRE1_M) | ((LRF_CLOCK_TICKS_PER_US - 1) << LRFDPBE_TIMPRE_PRE1_S);

        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_RFINTERVAL) = txCmd->periodUs;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXTARGET) = txCmd->numPackets;

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        channel = txCmd->channel;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enable radio */
            LRF_enable();

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = (PBE_BLE5_RAM_OPCFG_REPEAT_YES) |
                                                                        (PBE_BLE5_RAM_OPCFG_TXPATTERN_NO) |
                                                                        (PBE_BLE5_RAM_OPCFG_TXFCMD_RETRY) |
                                                                        (PBE_BLE5_RAM_OPCFG_RFINTERVAL_EN);

            /* Initialize RF FIFOs */
            ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

            /* Prepare payload */
            switch (txCmd->pduHeader & 0x0F)
            {
            case BLE_DTM_PAYLOAD_TYPE_PRBS9:
                byteVal = 0;
                whitenPoly = RCL_HANDLER_BLE5_PRBS9_POLY;
                whitenSeed = RCL_HANDLER_BLE5_PRBS9_INIT;
                break;
            case BLE_DTM_PAYLOAD_TYPE_11110000:
                byteVal = 0x0F; /* 11110000... in transmission order */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            case BLE_DTM_PAYLOAD_TYPE_10101010:
                byteVal = 0x55; /* 10101010... in transmission order */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            case BLE_DTM_PAYLOAD_TYPE_PRBS15:
                byteVal = 0;
                whitenPoly = RCL_HANDLER_BLE5_PRBS15_POLY;
                whitenSeed = RCL_HANDLER_BLE5_PRBS15_INIT;
                break;
            case BLE_DTM_PAYLOAD_TYPE_11111111:
                byteVal = 0xFF; /* All ones */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            case BLE_DTM_PAYLOAD_TYPE_00000000:
                byteVal = 0x00; /* All zeros */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            case BLE_DTM_PAYLOAD_TYPE_00001111:
                byteVal = 0xF0; /* 00001111... in transmission order */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            case BLE_DTM_PAYLOAD_TYPE_01010101:
                byteVal = 0xAA; /* 01010101... in transmission order */
                whitenPoly = 0;
                whitenSeed = 0;
                break;
            default:
                status = RCL_CommandStatus_Error_Param;
                whitenSeed = 0;
                whitenPoly = 0;
                byteVal = 0;
                break;
            }
            if (status == RCL_CommandStatus_Active)
            {
                /* Enter length field and padding length in FIFO */
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = (txCmd->pduLength + 6) | (3 << 16);
                /* Enter header in FIFO */
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = (txCmd->pduLength << 24) | (txCmd->pduHeader << 16);

                if (whitenSeed == 0)
                {
                    uint32_t txWord = byteVal | (byteVal << 8) | (byteVal << 16) | (byteVal << 24);
                    for (int i = 0; i < RCL_Buffer_bytesToWords(txCmd->pduLength); i++)
                    {
                        HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = txWord;
                    }
                }
                else
                {
                    /* Re-use PBE whitener for generating PRBS payload */
                    /* Save existing polynomial, which is part of the setup */
                    uint32_t whitenPolySave = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0);
                    /* Configure stand-alone whitening in PRBS0 of the PHA */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PHACFG) = (LRFDPBE_PHACFG_MODE0_WHITE) |
                                                             (LRFDPBE_PHACFG_MODE1_INDEP);
                    /* Set the polynomial of the configured PRBS sequence */
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = whitenPoly;
                    /* Seed the PRBS */
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_LFSR0BR) = whitenSeed;
                    /* Set byte accesses */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_LFSR0N) = 7;
                    /* Write the configured byte value into the whitener for the first byte */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_LFSR0INL) = byteVal;
                    for (int i = 0; i < RCL_Buffer_bytesToWords(txCmd->pduLength); i++)
                    {
                        /* Initialize combined 4-byte word */
                        uint32_t txWord = 0;
                        for (int j = 0; j < 4; j++)
                        {
                            /* Wait for PHA to be done whiteneing the byte */
                            while ((HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHASTA) & LRFDPBE_PHASTA_BUSY_M) != 0)
                            {}
                            /* Read whitened byte */
                            uint8_t txByte = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0);
                            /* Enter next byte */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_LFSR0INL) = byteVal;
                            /* Insert byte into word */
                            txWord |= txByte << (j * 8);
                        }
                        /* Write word to TX FIFO. If the packet length does not divide 4, there will be some extra non-zero bytes,
                        but they will be ignored by the radio, making the transmitted packet correct */
                        HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = txWord;
                    }
                    /* Restore whitener polynomial */
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = whitenPolySave;
                }

                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    status = startTimeStatus;
                }
                else
                {
                    LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = 0;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = DTM_ACCESS_ADDRESS ^ (whitenInit << 24);
                    }
                    Log_printf(RclCore, Log_VERBOSE, "Starting DTM TX");
                    LRF_waitForTopsmReady();
                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_TXRAW;
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            Log_printf(RclCore, Log_VERBOSE, "DTM TX started");
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            Log_printf(RclCore, Log_VERBOSE, "TX raw done");
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished && lrfEvents.opError != 0)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE) == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                {
                    endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                }

                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
        /* Restore PBE timer 1 prescaler */
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_TIMPRE) = ble5HandlerState.dtmTx.storedPbeTimPre;
    }
    return rclEvents;
}


/*
 *  ======== RCL_Handler_BLE5_genericRx ========
 */
RCL_Events RCL_Handler_BLE5_genericRx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBle5GenericRx *rxCmd = (RCL_CmdBle5GenericRx *) cmd;
    uint32_t rfFreq;
    RCL_Events rclEvents = RCL_EventNone;
    RCL_CtxGenericRx *ctx = rxCmd->ctx;

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_Ble5Channel channel;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        uint32_t crcInit = ctx->crcInit;
        uint32_t accessAddress = ctx->accessAddress;

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress;
        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = crcInit << 8;

        ble5HandlerState.common.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_EXTRABYTES) = RCL_Handler_BLE5_findNumExtraBytes(ble5HandlerState.common.fifoCfg);

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        channel = rxCmd->channel;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                status = startTimeStatus;
            }
            else
            {
                /* Initialize counters */
                ble5HandlerState.common.activeUpdate = RCL_Handler_BLE5_initGenericRxStats(rxCmd->stats,
                                                                                        rclSchedulerState.actualStartTime);

                uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;

                if (ble5HandlerState.common.accessAddressModification)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress ^ (whitenInit << 24);
                }

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_MAXLEN) = ctx->maxPktLen;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = ctx->config.repeated << PBE_BLE5_RAM_OPCFG_REPEAT_S;

                if (ctx->config.disableSync != 0)
                {
                    uint16_t demc1be0 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE0);
                    uint16_t demc1be1 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1);
                    uint16_t demc1be2 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2);
#ifdef DeviceFamily_CC27XX
                    uint16_t demc1be12 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12);
#endif
                    ble5HandlerState.genericRx.restoreThresh = true;
                    ble5HandlerState.genericRx.demc1be0 = demc1be0;
                    ble5HandlerState.genericRx.demc1be1 = demc1be1;
                    ble5HandlerState.genericRx.demc1be2 = demc1be2;
#ifdef DeviceFamily_CC27XX
                    ble5HandlerState.genericRx.demc1be12 = demc1be12;
#endif
                    demc1be0 |= LRFDMDM_DEMC1BE0_MASKA_M | LRFDMDM_DEMC1BE0_MASKB_M;
                    demc1be1 = (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDA_S) | (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDB_S);
                    demc1be2 = (demc1be2 & ~LRFDMDM_DEMC1BE2_THRESHOLDC_M) | (0x7F << LRFDMDM_DEMC1BE2_THRESHOLDC_S);
#ifdef DeviceFamily_CC27XX
                    demc1be12 = (demc1be12 & ~LRFDMDM_DEMC1BE12_THRESHOLDG_M) | (0x7F << LRFDMDM_DEMC1BE12_THRESHOLDG_S);
#endif
                    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE0) = demc1be0;
                    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = demc1be1;
                    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = demc1be2;
#ifdef DeviceFamily_CC27XX
                    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = demc1be12;
#endif
                }
                else
                {
                    ble5HandlerState.genericRx.restoreThresh = false;
                }

                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                ble5HandlerState.common.rxFifoSz = LRF_prepareRxFifo();
                ble5HandlerState.common.curBuffer = NULL;
                if (ctx->config.discardRxPackets == 0)
                {
                    RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
                    rclEventsIn.rxBufferUpdate = 0;
                }
                else
                {
                    /* Set FIFO size to maximum */
                    LRF_setRxFifoEffSz(ble5HandlerState.common.rxFifoSz);
                }

                if (status == RCL_CommandStatus_Active)
                {
                    uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIFOCFG);
                    LRF_enableHwInterrupt(RCL_Handler_BLE5_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                LRF_EventRxOk.value | LRF_EventRxIgnored.value |
                                                                                LRF_EventRxNok.value | LRF_EventRxBufFull.value,
                                                                                fifoCfg, ble5HandlerState.common.activeUpdate));

                    Log_printf(RclCore, Log_VERBOSE, "Starting generic RX");
                    LRF_waitForTopsmReady();
                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_RXRAW;
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }
    else
    {
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    if (ctx->config.discardRxPackets == 0)
                    {
                        RCL_MultiBuffer *curBuffer;
                        curBuffer = RCL_MultiBuffer_getBuffer(ble5HandlerState.common.curBuffer,
                                                            wordLength * 4);
                        if (curBuffer != ble5HandlerState.common.curBuffer)
                        {
                            rclEvents.rxBufferFinished = 1;
                            ble5HandlerState.common.curBuffer = curBuffer;
                        }
                        if (curBuffer == NULL)
                        {
                            /* Error */
                            ble5HandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                            /* Send abort */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_STOP;
                            /* Do not check for more packets from the RX FIFO */
                            break;
                        }
                        else
                        {
                            uint32_t *data32;
                            data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                            LRF_readRxFifoWords(data32, wordLength);
                            RCL_Handler_BLE5_commitPacket(curBuffer, wordLength * 4);
                            /* Raise event */
                            rclEvents.rxEntryAvail = 1;
                            /* Adjust effective FIFO size */
                            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
                            rclEventsIn.rxBufferUpdate = 0;
                        }
                    }
                    else
                    {
                        LRF_discardRxFifoWords(wordLength);
                    }
                }
            }
            if (ble5HandlerState.common.activeUpdate)
            {
                RCL_Handler_BLE5_updateGenericRxStats(rxCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if (rclEventsIn.timerStart != 0)
        {
            Log_printf(RclCore, Log_VERBOSE, "Generic RX started");
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
            /* Disable radio */
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
            if (lrfEvents.opError != 0 && endStatus == RCL_CommandStatus_Finished)
            {
                endStatus = RCL_Handler_BLE5_findPbeErrorEndStatus(endCause);
            }
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
            {
                endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
            }
            else
            {
                /* No change of status */
            }
            cmd->status = endStatus;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (rclEvents.lastCmdDone != 0)
        {
            RCL_Handler_BLE5_updateGenericRxStats(rxCmd->stats, rclSchedulerState.actualStartTime);
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if ( rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_BLE5_updateRxCurBufferAndFifo(&ctx->rxBuffers);
            rclEventsIn.rxBufferUpdate = 0;
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        if (ble5HandlerState.genericRx.restoreThresh)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE0) = ble5HandlerState.genericRx.demc1be0;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = ble5HandlerState.genericRx.demc1be1;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = ble5HandlerState.genericRx.demc1be2;
#ifdef DeviceFamily_CC27XX
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = ble5HandlerState.genericRx.demc1be12;
#endif
        }

        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_BLE5_genericTx ========
 */
RCL_Events RCL_Handler_BLE5_genericTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    uint32_t rfFreq;
    RCL_CmdBle5GenericTx *txCmd = (RCL_CmdBle5GenericTx *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;
        RCL_Ble5Channel channel;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        RCL_CtxGenericTx *ctx = txCmd->ctx;
        uint32_t crcInit = ctx->crcInit;
        uint32_t accessAddress = ctx->accessAddress;

        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress;
        /* 32-bit access to also write CRCINITH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_CRCINITL) = crcInit << 8;

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        channel = txCmd->channel;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enable radio */
            LRF_enable();

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = PBE_BLE5_RAM_OPCFG_TXFCMD_DEALLOC;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXTARGET) = 0;

            /* Initialize RF FIFOs */
            ble5HandlerState.common.txFifoSz = LRF_prepareTxFifo();

            /* Enter payload */
            uint32_t nBuffer = RCL_Handler_BLE5_updateTxBuffers(&txCmd->ctx->txBuffers, 1, NULL, false);
            if (nBuffer == 0)
            {
                status = RCL_CommandStatus_Error_MissingTxBuffer;
            }
            else
            {
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    status = startTimeStatus;
                }
                else
                {
                    LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(channel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (ble5HandlerState.common.accessAddressModification)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = accessAddress ^ (whitenInit << 24);
                    }
                    Log_printf(RclCore, Log_VERBOSE, "Starting generic TX");
                    LRF_waitForTopsmReady();
                    /* Post cmd */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_TXRAW;
                }
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            Log_printf(RclCore, Log_VERBOSE, "TX raw done");
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished && lrfEvents.opError != 0)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
                /* Pop transmitted packet */
                RCL_Buffer_TxBuffer *txBuffer;
                txBuffer = RCL_TxBuffer_get(&txCmd->ctx->txBuffers);
                if (txBuffer != NULL)
                {
                    txBuffer->state = RCL_BufferStateFinished;
                }
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Ble5_txTest ========
 */
RCL_Events RCL_Handler_Ble5_txTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBle5TxTest *txCmd = (RCL_CmdBle5TxTest *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
        ble5HandlerState.txTest.restoreSelector = RCL_HANDLER_BLE5_RESTORE_NONE;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_OPCFG) = PBE_BLE5_RAM_OPCFG_TXPATTERN_M;

        /* Default end status */
        ble5HandlerState.common.endStatus = RCL_CommandStatus_Finished;

        RCL_Ble5Channel channel = txCmd->channel;

        RCL_CommandStatus status = RCL_Handler_BLE5_setPhy(cmd->phyFeatures);
        uint32_t rfFreq = RCL_Handler_BLE5_findRfFreq(channel);
        if (rfFreq == 0)
        {
            status = RCL_CommandStatus_Error_Param;
        }
        else if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
        {
            status = RCL_CommandStatus_Error_Param;
        }

        if (status == RCL_CommandStatus_Active)
        {
            /* Program frequency word */
            LRF_programFrequency(rfFreq, false);

            /* Enter configuration */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_PATTERN) = txCmd->txWord;
            if (txCmd->config.sendCw != 0)
            {
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) | LRFDMDM_MODCTRL_TONEINSERT_M;
                ble5HandlerState.txTest.restoreSelector = RCL_HANDLER_BLE5_RESTORE_MODCTRL;
            }
            else
            {
                uint32_t whitenMode = txCmd->config.whitenMode;
                /* Configure whitening */
                /* Use pseudo-random sync word (not necessarily matching selected PRBS) */
                HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_HANDLER_BLE5_PRBS_SYNC;
                if (whitenMode == RCL_CMD_BLE5_WH_MODE_DEFAULT)
                {
                    uint16_t whitenInit = RCL_Handler_BLE5_findWhitenInit(txCmd->channel);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = whitenInit;
                    if (whitenInit == 0)
                    {
                        /* Use pattern as sync word */
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = txCmd->txWord | (txCmd->txWord << 16);
                    }
                }
                else
                {
                    ble5HandlerState.txTest.restoreSelector = RCL_HANDLER_BLE5_RESTORE_WHITEN_POLY;
                    ble5HandlerState.txTest.storedWhitenPoly = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0);
                    if (whitenMode == RCL_CMD_BLE5_WH_MODE_PRBS9)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = RCL_HANDLER_BLE5_PRBS9_POLY;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = RCL_HANDLER_BLE5_PRBS9_INIT;
                    }
                    else if (whitenMode == RCL_CMD_BLE5_WH_MODE_PRBS15)
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = RCL_HANDLER_BLE5_PRBS15_POLY;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = RCL_HANDLER_BLE5_PRBS15_INIT;
                    }
                    else
                    {
                        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = RCL_HANDLER_BLE5_PRBS32_POLY;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_WHITEINIT) = RCL_HANDLER_BLE5_PRBS32_INIT;
                    }
                }
            }

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                status = startTimeStatus;
            }
            else
            {
                /* Enable interrupts */
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                /* Post cmd */
                Log_printf(RclCore, Log_VERBOSE, "Starting BLE5 infinite TX");

                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE5_REGDEF_API_OP_TXRAW;
            }
        }
        /* Set status */
        cmd->status = status;
        if (status >= RCL_CommandStatus_Finished)
        {
            rclEvents.lastCmdDone = 1;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0)
        {
            cmd->status = ble5HandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = ble5HandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE5_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        if ((ble5HandlerState.txTest.restoreSelector & RCL_HANDLER_BLE5_RESTORE_MODCTRL) != 0)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) & (~LRFDMDM_MODCTRL_TONEINSERT_M);
        }
        if ((ble5HandlerState.txTest.restoreSelector & RCL_HANDLER_BLE5_RESTORE_WHITEN_POLY) != 0)
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = ble5HandlerState.txTest.storedWhitenPoly;
        }
        LRF_disable();
        LRF_disableSynthRefsys();
    }

    return rclEvents;
}

/*
 *  ======== RCL_BLE5_updateFilterList ========
 */
RCL_BLE5_FilterListUpdateResult RCL_BLE5_updateFilterList(const RCL_FL_Entry *newEntry, RCL_FilterList *filterList, uint32_t index)
{
    if (filterList == NULL)
    {
        return RCL_BLE5_FilterListUpdateIndexError;
    }
    else if (index >= filterList->numEntries || index >= PBE_NUM_FILTER_ENTRIES)
    {
        return RCL_BLE5_FilterListUpdateIndexError;
    }
    else
    {
        /* Run in protected region to avoid race conditions */
        uintptr_t key = HwiP_disable();
        /* Insert updated entry */
        filterList->entries[index] = *newEntry;
        /* Check if handler should be notified */
        if (ble5HandlerState.common.updatableFilterList == filterList)
        {
            /* Set index */
            ble5HandlerState.common.filterListUpdateIndex = index;
            /* Send event to running command */
            RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventHandlerCmdUpdate);
        }
        HwiP_restore(key);

        return RCL_BLE5_FilterListUpdateOk;
    }
}

/*
 *  ======== RCL_BLE5_setDefaultRfFrequency ========
 */
void RCL_BLE5_setDefaultRfFrequency(uint32_t rfFrequency)
{
    ble5HandlerState.common.defaultRfFrequency = rfFrequency;
}

/*
 *  ======== RCL_BLE5_getRxStatus ========
 */
RCL_Ble5_RxPktStatus RCL_BLE5_getRxStatus(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ble5HandlerState.common.fifoCfg;

    if ((fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDSTATUS_M) != 0)
    {
        /* Find number of bytes in status and the appended bytes after that */
        uint32_t positionFromEnd = RCL_Handler_BLE5_findNumExtraBytes(fifoCfg &
                                                                     (PBE_BLE5_RAM_FIFOCFG_APPENDSTATUS_M |
                                                                     PBE_BLE5_RAM_FIFOCFG_APPENDLQI_M |
                                                                     PBE_BLE5_RAM_FIFOCFG_APPENDFREQEST_M |
                                                                     PBE_BLE5_RAM_FIFOCFG_APPENDRSSI_M |
                                                                     PBE_BLE5_RAM_FIFOCFG_APPENDTIMESTAMP_M));
        int32_t offset = rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - positionFromEnd;

        if (offset < 0)
        {
            return  (RCL_Ble5_RxPktStatus) {.value = RCL_BLE5_RX_PKT_STATUS_INVALID};
        }
        else
        {
            const RCL_Ble5_RxPktStatus *statusPtr = (const RCL_Ble5_RxPktStatus *) (rxEntry->data + offset);

            return *statusPtr;
        }
    }
    else
    {
        return (RCL_Ble5_RxPktStatus) {.value = RCL_BLE5_RX_PKT_STATUS_INVALID};
    }
}

/*
 *  ======== RCL_BLE5_getRxRssi ========
 */
int8_t RCL_BLE5_getRxRssi(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ble5HandlerState.common.fifoCfg;

    if ((fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDRSSI_M) != 0)
    {
        /* Find number of bytes in RSSI and the appended bytes after that */
        uint32_t positionFromEnd = RCL_Handler_BLE5_findNumExtraBytes(fifoCfg &
                                                                     (PBE_BLE5_RAM_FIFOCFG_APPENDRSSI_M |
                                                                     PBE_BLE5_RAM_FIFOCFG_APPENDTIMESTAMP_M));
        int32_t offset = rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - positionFromEnd;

        if (offset < 0)
        {
            return LRF_RSSI_INVALID;
        }
        else
        {
            const int8_t *rssiPtr = (const int8_t *) (rxEntry->data + offset);

            return *rssiPtr;
        }
    }
    else
    {
        return LRF_RSSI_INVALID;
    }
}

/*
 *  ======== RCL_BLE5_getRxTimestamp ========
 */
uint32_t RCL_BLE5_getRxTimestamp(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ble5HandlerState.common.fifoCfg;

    if ((fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDTIMESTAMP_M) != 0)
    {
        uint32_t timestamp;
        /* If status not appended; assume 1 Mbps */
        uint32_t timestampAdjust = TIMESTAMP_ADJUST_1MBPS;
        int32_t offset = (rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - sizeof(timestamp));
        if (offset < 0)
        {
            return 0;
        }
        else
        {
            const uint8_t *dataPtr = rxEntry->data + offset;
            timestamp = dataPtr[0] | (dataPtr[1] << 8) | (dataPtr[2] << 16) | (dataPtr[3] << 24);
            if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDSTATUS_M)
            {
                /* Find number of bytes in status and the appended bytes between status and timesptamp */
                uint32_t positionFromTimestamp = RCL_Handler_BLE5_findNumExtraBytes(fifoCfg &
                                                                                   (PBE_BLE5_RAM_FIFOCFG_APPENDSTATUS_M |
                                                                                   PBE_BLE5_RAM_FIFOCFG_APPENDLQI_M |
                                                                                   PBE_BLE5_RAM_FIFOCFG_APPENDFREQEST_M |
                                                                                   PBE_BLE5_RAM_FIFOCFG_APPENDRSSI_M));
                offset -= positionFromTimestamp;
                if (offset < 0)
                {
                    return 0;
                }
                else
                {
                    const RCL_Ble5_RxPktStatus *statusPtr = (const RCL_Ble5_RxPktStatus *) (rxEntry->data + offset);
                    switch (statusPtr->phy)
                    {
                        case RCL_Ble5_RxPhy1Mbps:
                        default:
                            timestampAdjust = TIMESTAMP_ADJUST_1MBPS;
                            break;
                        case RCL_Ble5_RxPhy2Mbps:
                            timestampAdjust = TIMESTAMP_ADJUST_2MBPS;
                            break;
                        case RCL_Ble5_RxPhyCodedS8:
                        case RCL_Ble5_RxPhyCodedS2:
                            timestampAdjust = TIMESTAMP_ADJUST_CODED;
                            break;
                    }
                }
            }
        }
        return timestamp - timestampAdjust;
    }
    else
    {
        return 0;
    }
}

/*
 *  ======== RCL_BLE5_getAuxAdvStartTimeDelta ========
 */
uint32_t RCL_BLE5_getAuxAdvStartTimeDelta(uint16_t phyFeatures, uint8_t chMap, uint8_t advPayloadLen)
{
    uint8_t numPrimaryChPackets = (chMap & 1) + ((chMap >> 1) & 1) + ((chMap >> 2) & 1);
    uint32_t advPayloadLenInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(RCL_Handler_BLE5_findPacketDuration(advPayloadLen, phyFeatures), BLE_AUX_OFFSET_30_US);

    return (RCL_SCHEDULER_SYSTIM_US((advPayloadLenInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US) * numPrimaryChPackets);
}

/*
 *  ======== RCL_BLE5_setAccessAddressModification ========
 */
/* This function should be secret, so no prototype is given in the .h file */
void RCL_BLE5_setAccessAddressModification(bool enable)
{
    ble5HandlerState.common.accessAddressModification = enable;
}

/*
 *  ======== RCL_Handler_BLE5_random ========
 */
__attribute__((weak)) uint32_t RCL_Handler_BLE5_getRandomNumber(void)
{
    return Random_getNumber();
}

/*
 *  ======== RCL_Handler_BLE5_updateRxCurBufferAndFifo ========
 */
static void RCL_Handler_BLE5_updateRxCurBufferAndFifo(List_List *rxBuffers)
{
    RCL_MultiBuffer *curBuffer = ble5HandlerState.common.curBuffer;

    if (curBuffer == NULL)
    {
        curBuffer = RCL_MultiBuffer_findFirstWritableBuffer((RCL_MultiBuffer *)rxBuffers->head);
    }
    ble5HandlerState.common.curBuffer = curBuffer;

    uint32_t rxSpace =
        RCL_MultiBuffer_findAvailableRxSpace(curBuffer);

    LRF_setRxFifoEffSz(rxSpace);
}

/*
 *  ======== RCL_Handler_BLE5_findWhitenInit ========
 */
static uint16_t RCL_Handler_BLE5_findWhitenInit(RCL_Ble5Channel channel)
{
    uint16_t whitenInit;

    if ((channel & BLE_CUSTOM_FREQ_BM) == 0)
    {
        if (channel < BLE_PHY_CHAN_MIN)
        {
            /* Standard channel - set bit as BLE standard requires */
            whitenInit = channel | 0x40;
        }
        else
        {
            /* PHY channel - no whitening */
            whitenInit = 0;
        }
    }
    else
    {
        /* Custom channel - use remaining bits as whitening initialization */
        whitenInit = channel & ~BLE_CUSTOM_FREQ_BM;
    }
    return whitenInit;
}

/*
 *  ======== RCL_Handler_BLE5_findRfFreq ========
 */
static uint32_t RCL_Handler_BLE5_findRfFreq(RCL_Ble5Channel channel)
{
    uint32_t rfFreq;

    ble5HandlerState.common.channel = channel;
    if (channel <= BLE_DATA_CHAN_MAX)
    {
        /*  Data channel */
        rfFreq = channel * BLE_CHAN_SPACE + BLE_DATA_CHAN_BASE;
        if (rfFreq >= BLE_ADV_CHAN_MID_FREQ)
        {
            rfFreq += BLE_CHAN_SPACE;
        }
    }
    else if (channel == BLE_ADV_CHAN_LO)
    {
        rfFreq = BLE_ADV_CHAN_LO_FREQ;
    }
    else if (channel == BLE_ADV_CHAN_MID)
    {
        rfFreq = BLE_ADV_CHAN_MID_FREQ;
    }
    else if (channel == BLE_ADV_CHAN_HI)
    {
        rfFreq = BLE_ADV_CHAN_HI_FREQ;
    }
    else if (channel >= BLE_PHY_CHAN_MIN && channel <= BLE_PHY_CHAN_MAX)
    {
        rfFreq = BLE_ADV_CHAN_LO_FREQ + ((channel - BLE_PHY_CHAN_MIN) * BLE_CHAN_SPACE);
    }
    else if ((channel & BLE_CUSTOM_FREQ_BM) != 0)
    {
        rfFreq = ble5HandlerState.common.defaultRfFrequency;
    }
    else
    {
        /* error */
        rfFreq = 0;
    }

    return rfFreq;
}

/*
 *  ======== RCL_Handler_BLE5_findAdvChannel ========
 */
static RCL_Ble5Channel RCL_Handler_BLE5_findAdvChannel(uint32_t advMap, uint32_t order)
{
    RCL_Ble5Channel channel;
    if ((advMap & BLE_CUSTOM_FREQ_BM) != 0)
    {
        channel = advMap;
    }
    else
    {
        if (order >= 6)
        {
            /* Error, but handle */
            order = 0;
        }
        switch (advMap & 0x07)
        {
        case 1:
            channel = 37;
            break;

        case 2:
            channel = 38;
            break;

        case 3:
            channel = ((order & 1) == 0) ? 37 : 38;
            break;

        case 4:
            channel = 39;
            break;

        case 5:
            channel = ((order & 1) == 0) ? 37 : 39;
            break;

        case 6:
            channel = ((order & 1) == 0) ? 38 : 39;
            break;

        case 7:
            channel = (order >> 1) + 37;
            break;

        default:
            channel = 37; /* Error, but handle */
            break;
        }
    }

    return channel;
}

/*
 *  ======== RCL_Handler_BLE5_setPhy ========
 */
static RCL_CommandStatus RCL_Handler_BLE5_setPhy(uint16_t phyFeatures)
{
    switch (phyFeatures & BLE_PHY_FEATURE_PHY_MASK)
    {
        case BLE_PHY_FEATURE_PHY_1MBPS:
            ble5HandlerState.common.timestampAdjust = TIMESTAMP_ADJUST_1MBPS;
            break;

        case BLE_PHY_FEATURE_PHY_2MBPS:
            ble5HandlerState.common.timestampAdjust = TIMESTAMP_ADJUST_2MBPS;
            break;

        case BLE_PHY_FEATURE_PHY_CODED:
            ble5HandlerState.common.timestampAdjust = TIMESTAMP_ADJUST_CODED;
            break;

        default:
            return RCL_CommandStatus_Error_Param;
    }

    ble5HandlerState.common.phyFeatures = phyFeatures;

    return RCL_CommandStatus_Active;
}

/*
 *  ======== RCL_Handler_BLE5_findPbeErrorEndStatus ========
 */
static RCL_CommandStatus RCL_Handler_BLE5_findPbeErrorEndStatus(uint16_t pbeEndStatus)
{
    RCL_CommandStatus status;
    switch (pbeEndStatus)
    {
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_RXF:
        status = RCL_CommandStatus_Error_RxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_TXF:
        status = RCL_CommandStatus_Error_TxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_SYNTH:
        Log_printf(RclCore, Log_ERROR, "Synth error. RFEMSGBOX = %04X", HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_MSGBOX));
        status = RCL_CommandStatus_Error_Synth;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        break;
     case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_PAR:
        status = RCL_CommandStatus_Error_Param;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP:
        status = RCL_CommandStatus_Error_UnknownOp;
        break;
    default:
        Log_printf(RclCore, Log_ERROR, "Unexpected error 0x%04X from PBE", pbeEndStatus);
        status = RCL_CommandStatus_Error;
        break;
    }
    return status;
}

/*
 *  ======== RCL_Handler_BLE5_updateTxBuffers ========
 */
static uint32_t RCL_Handler_BLE5_updateTxBuffers(List_List *txBuffers,
                                          uint32_t maxBuffers,
                                          RCL_TxBufferInfo *txBufferInfo,
                                          bool retransPossible)
{
    uint32_t nWords = 0;
    uint32_t nBuffers = 0;
    RCL_Buffer_TxBuffer *nextTxBuffer;
    RCL_Buffer_TxBuffer *txBuffer = NULL;
    uint8_t *lastTxHdr = NULL;
    bool isConnBuffer = false;

    if (txBufferInfo != NULL)
    {
        txBuffer = txBufferInfo->lastEnteredTxBuffer;
        lastTxHdr = txBufferInfo->lastTxHdr;
        isConnBuffer = txBufferInfo->isConnBuffer;
    }

    if (txBuffer == NULL)
    {
        nextTxBuffer = RCL_TxBuffer_head(txBuffers);
    }
    else
    {
        nextTxBuffer = RCL_TxBuffer_next(txBuffer);
    }

    if (nextTxBuffer != NULL && lastTxHdr != NULL && isConnBuffer)
    {
        /* Set MD = 1 */
        HWREGB_WRITE_LRF(lastTxHdr) = HWREGB_READ_LRF(lastTxHdr) | 0x10;
        lastTxHdr = NULL;
    }

    while (nextTxBuffer != NULL && nBuffers < maxBuffers)
    {

        uint32_t length = nextTxBuffer->length;
        /* Number of words including length field and end padding */
        uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(length) / 4;
        if (wordLength > LRF_getTxFifoWritable() / 4)
        {
            /* Packet will not fit */
            break;
        }
        txBuffer = nextTxBuffer;
        txBuffer->state = RCL_BufferStateInUse;

        uint32_t *data32 = (uint32_t *) &(txBuffer->length);

        if (txBufferInfo != NULL && isConnBuffer)
        {
            lastTxHdr = LRF_getTxFifoWrAddr(txBuffer->numPad + 3);
        }
        /* TODO: See RCL-347 */
        /* Copy packet into FIFO */
        LRF_writeTxFifoWords(data32, wordLength);
        nextTxBuffer = RCL_TxBuffer_next(txBuffer);
        if (nextTxBuffer != NULL && lastTxHdr != NULL && isConnBuffer)
        {
            /* Set MD = 1 */
            HWREGB_WRITE_LRF(lastTxHdr) = HWREGB_READ_LRF(lastTxHdr) | 0x10;
            lastTxHdr = NULL;
        }

        nBuffers++;
        nWords += wordLength;
        /* If the first packet is a possible retransmission, move the read pointer behind it */
        if (retransPossible)
        {
            LRF_skipTxFifoWords(wordLength);
            retransPossible = false;
        }
    }

    if (txBufferInfo != NULL)
    {
        txBufferInfo->lastEnteredTxBuffer = txBuffer;
        txBufferInfo->lastTxHdr = lastTxHdr;
        txBufferInfo->numBytes += nWords * 4;
        txBufferInfo->numBuffers += nBuffers;
    }

    return nBuffers;
}

/*
 *  ======== RCL_Handler_BLE5_commitPacket ========
 */
static void RCL_Handler_BLE5_commitPacket(RCL_MultiBuffer *curBuffer, uint32_t numBytes)
{
    /* Write channel into receive buffer entry - pad0 field is always part of the padding in BLE */
    RCL_Buffer_DataEntry *entry = (RCL_Buffer_DataEntry *) RCL_MultiBuffer_getNextWritableByte(curBuffer);
    entry->pad0 = ble5HandlerState.common.channel;

    /* Commit packet */
    RCL_MultiBuffer_commitBytes(curBuffer, numBytes);
}


/*
 *  ======== RCL_Handler_BLE5_maskEventsByFifoConf ========
 */
static uint32_t RCL_Handler_BLE5_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate)
{
    /* Remove events that will not give an entry in the RX FIFO, based on FIFOCFG, unless active update is used */
    if (!activeUpdate)
    {
        mask &= ~(((fifoConfVal & PBE_BLE5_RAM_FIFOCFG_AUTOFLUSHIGN_M) ? LRF_EventRxIgnored.value : 0) |
            ((fifoConfVal & PBE_BLE5_RAM_FIFOCFG_AUTOFLUSHCRC_M) ? LRF_EventRxNok.value : 0) |
            ((fifoConfVal & PBE_BLE5_RAM_FIFOCFG_AUTOFLUSHEMPTY_M) ? LRF_EventRxEmpty.value : 0) |
            LRF_EventRxBufFull.value);
    }

    return mask;
}

/*
 *  ======== RCL_Handler_BLE5_updateAdvScanInitStats ========
 */
static void RCL_Handler_BLE5_updateAdvScanInitStats(RCL_StatsAdvScanInit *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* 32-bit access to also read LASTTIMESTAMPH */
        uint32_t lastTimestamp = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL);
        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = false;
        }
        else
        {
            stats->timestampValid = true;
            stats->lastTimestamp = lastTimestamp - ble5HandlerState.common.timestampAdjust;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTRSSI);
        stats->nRxNok = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK);
        stats->nRxIgnored = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED);
        stats->nRxFifoFull = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL);
        stats->nRxOk = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK);
        stats->nTx = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX);
    }
}

/*
 *  ======== RCL_Handler_BLE5_initAdvScanInitStats ========
 */
static bool RCL_Handler_BLE5_initAdvScanInitStats(RCL_StatsAdvScanInit *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        /* 32-bit access to also write LASTTIMESTAMPH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) = startTime;

        stats->timestampValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED) = stats->nRxIgnored;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = stats->nRxFifoFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX) = stats->nTx;
        }
        else
        {
            /* Reset existing values in PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX) = 0;

            stats->nRxNok = 0;
            stats->nRxIgnored = 0;
            stats->nRxFifoFull = 0;
            stats->nRxOk = 0;
            stats->nTx = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        return false;
    }
}

/*
 *  ======== RCL_Handler_BLE5_initConnStats ========
 */
static bool RCL_Handler_BLE5_initConnStats(RCL_StatsConnection *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        /* 32-bit access to also write FIRSTTIMESTAMPH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTTIMESTAMPL) = startTime;

        stats->anchorValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXDONE) = stats->nTxDone;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXACK) = stats->nTxAck;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTLACK) = stats->nTxCtlAck;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTL) = stats->nTxCtl;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXRETRANS) = stats->nTxRetrans;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED) = stats->nRxIgnored;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXEMPTY) = stats->nRxEmpty;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = stats->nRxFifoFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX) = stats->nTx;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTL) = stats->nRxCtl;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTLACK) = stats->nRxCtlAck;
        }
        else
        {
            /* Reset existing values in PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXDONE) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXACK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTLACK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXRETRANS) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXEMPTY) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTLACK) = 0;

            stats->nTxDone = 0;
            stats->nTxAck = 0;
            stats->nTxCtlAck = 0;
            stats->nTxCtl = 0;
            stats->nTxRetrans = 0;
            stats->nRxNok = 0;
            stats->nRxIgnored = 0;
            stats->nRxEmpty = 0;
            stats->nRxFifoFull = 0;
            stats->nRxOk = 0;
            stats->nTx = 0;
            stats->nRxCtl = 0;
            stats->nRxCtlAck = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        return false;
    }
}

/*
 *  ======== RCL_Handler_BLE5_updateConnStats ========
 */
static void RCL_Handler_BLE5_updateConnStats(RCL_StatsConnection *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* 32-bit access to also read FIRSTTIMESTAMPH */
        uint32_t anchorPoint = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FIRSTTIMESTAMPL);

        /* Check if a new value is found in the first timestamp */
        if (anchorPoint == startTime)
        {
            stats->anchorValid = false;
        }
        else
        {
            stats->anchorValid = true;
            stats->anchorPoint = anchorPoint - ble5HandlerState.common.timestampAdjust;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTRSSI);
        stats->nTxDone = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXDONE);
        stats->nTxAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXACK);
        stats->nTxCtlAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTLACK);
        stats->nTxCtl = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXCTL);
        stats->nTxRetrans = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTXRETRANS);
        stats->nRxNok = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK);
        stats->nRxIgnored = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXIGNORED);
        stats->nRxEmpty = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXEMPTY);
        stats->nRxFifoFull = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL);
        stats->nRxOk = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK);
        stats->nTx = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NTX);
        stats->nRxCtl = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTL);
        stats->nRxCtlAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXCTLACK);
    }
}

/*
 *  ======== RCL_Handler_BLE5_initGenericRxStats ========
 */
static bool RCL_Handler_BLE5_initGenericRxStats(RCL_StatsGenericRx *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        /* 32-bit access to also write LASTIMESTAMPH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL) = startTime;

        stats->timestampValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = stats->nRxFifoFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = stats->nRxOk;
        }
        else
        {
            /* Reset existing values in PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK) = 0;

            stats->nRxNok = 0;
            stats->nRxFifoFull = 0;
            stats->nRxOk = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        return false;
    }
}

/*
 *  ======== RCL_Handler_BLE5_updateGenericRxStats ========
 */
static void RCL_Handler_BLE5_updateGenericRxStats(RCL_StatsGenericRx *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* 32-bit access to also read LASTTIMESTAMPH */
        uint32_t lastTimestamp = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTTIMESTAMPL);

        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = false;
        }
        else
        {
            stats->timestampValid = true;
            stats->lastTimestamp = lastTimestamp - ble5HandlerState.common.timestampAdjust;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_LASTRSSI);
        stats->nRxNok = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXNOK);
        stats->nRxFifoFull = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXFIFOFULL);
        stats->nRxOk = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_NRXOK);
    }
}

/*
 *  ======== RCL_Handler_BLE5_InitializeFilterList ========
 */
static void RCL_Handler_BLE5_InitializeFilterList(RCL_FilterList *filterList, uint32_t *pbeFilterList, uint32_t invertMask)
{
    uint32_t numEntries;
    uint32_t *targetPtr = pbeFilterList;

    if (filterList == NULL)
    {
        numEntries = 0;
    }
    else
    {
        uint32_t *sourcePtr;

        numEntries = filterList->numEntries;
        sourcePtr = (uint32_t *) filterList->entries;
        if (numEntries > PBE_NUM_FILTER_ENTRIES)
        {
            numEntries = PBE_NUM_FILTER_ENTRIES;
        }

        /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
        ASM_4_NOPS();
#endif //DeviceFamily_CC27XX

        /* Set info of unused entries to be ignored */
        for (int i = 0; i < numEntries; i++)
        {
            uint32_t entry0 = *sourcePtr++;
            uint32_t entry1 = *sourcePtr++;
            entry0 ^= invertMask;
            *targetPtr++ = entry0;
            *targetPtr++ = entry1;
        }
    }

        /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
        ASM_4_NOPS();
#endif //DeviceFamily_CC27XX

    /* Set info of unused entries to be ignored */
    for (int i = numEntries; i < PBE_NUM_FILTER_ENTRIES; i++)
    {
        *targetPtr = invertMask;
        targetPtr += 2;
    }
}

/*
 *  ======== RCL_Handler_BLE5_updateFilterListEntry ========
 */
static void RCL_Handler_BLE5_updateFilterListEntry(RCL_FilterList *filterList, uint32_t *pbeFilterList, uint32_t invertMask, uint32_t index)
{
    if (filterList != NULL)
    {
        uint32_t *sourcePtr;
        sourcePtr = (uint32_t *) &filterList->entries[index];
        volatile uint32_t *targetPtr = pbeFilterList + 2 * index;

        /* [RCL-515 WORKAROUND]: Protect the first memory write on BLE High PG1.x due to the hardware bugs */
#ifdef DeviceFamily_CC27XX
        ASM_4_NOPS();
#endif //DeviceFamily_CC27XX

        /* Disable given entry and remove any match if set up */
        targetPtr[0] = invertMask;
        /* TOPsm uses read-modify-write on this entry. Write several times to ensure it is not overwritten */
        targetPtr[0] = invertMask;
        targetPtr[0] = invertMask;
        targetPtr[0] = invertMask;
        targetPtr[0] = invertMask;

        /* Read updated entry */
        uint32_t entry0 = sourcePtr[0];
        uint32_t entry1 = sourcePtr[1];
        /* Apply invert mask */
        entry0 ^= invertMask;

        uint32_t flstat = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FLSTAT);
        /* Check if matching algorithm is running */
        if (flstat == 0)
        {
            /* If not, set match bit */
            entry0 |= PBE_BLE5_RAM_FL1MASK_MATCH_M;
        }

        /* Write back, making sure to write info last */
        targetPtr[1] = entry1;
        targetPtr[0] = entry0;
        /* TOPsm uses read-modify-write on this entry. Write several times to ensure it is not overwritten */
        targetPtr[0] = entry0;
        targetPtr[0] = entry0;
        targetPtr[0] = entry0;
        targetPtr[0] = entry0;

        /* Check if matching algorithm has started during this operation */
        if (flstat == 0 && HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_FLSTAT) != 0)
        {
            /* If so, clear match bit */
            entry0 &= ~PBE_BLE5_RAM_FL1MASK_MATCH_M;
            /* Update entry so no match is found by error */
            targetPtr[0] = entry0;
            /* TOPsm uses read-modify-write on this entry. Write several times to ensure it is not overwritten */
            targetPtr[0] = entry0;
            targetPtr[0] = entry0;
            targetPtr[0] = entry0;
            targetPtr[0] = entry0;
        }
    }
}

/*
 *  ======== RCL_Handler_BLE5_prepareConnectTime ========
 */
static uint32_t RCL_Handler_BLE5_prepareConnectTime(uint32_t *connectTime, uint32_t referenceTime, uint32_t interval)
{
    uint32_t initialConnectTime = *connectTime;
    uint32_t newConnectTime;

    /* Always allow 2 sub-periods extra to ensure that subIntervalStart is in the range [2, (2 * interval)] */
    newConnectTime = RCL_Handler_BLE5_findConnectTime(initialConnectTime, referenceTime + BLE_CONNECT_INT_UNIT, interval);
    *connectTime = newConnectTime;

    uint32_t subIntervalStart = ((newConnectTime - referenceTime) / RCL_BLE5_CONNECT_SUB_INT);
    Log_printf(RclCore, Log_DEBUG, "subIntervalStart = %d", subIntervalStart);
    return subIntervalStart;
}

/*
 *  ======== RCL_Handler_BLE5_findConnectTime ========
 */
static uint32_t RCL_Handler_BLE5_findConnectTime(uint32_t initialConnectTime, uint32_t referenceTime, uint32_t interval)
{
    uint32_t connectTime;
    uint32_t timeDiff = initialConnectTime - referenceTime;
    if (timeDiff < 0x80000000)
    {
        /* initialConnectTime >= referenceTime */
        uint32_t intervalAdjust = timeDiff / (interval * BLE_CONNECT_INT_UNIT);
        connectTime = initialConnectTime - intervalAdjust * (interval * BLE_CONNECT_INT_UNIT);
    }
    else
    {
        /* Result was negative; turn it around */
        timeDiff = referenceTime - initialConnectTime;
        uint32_t intervalAdjust = (timeDiff + (interval * BLE_CONNECT_INT_UNIT) - 1) / (interval * BLE_CONNECT_INT_UNIT);
        connectTime = initialConnectTime + intervalAdjust * (interval * BLE_CONNECT_INT_UNIT);
    }
    Log_printf(RclCore, Log_DEBUG, "referenceTime = 0x%08X, connectTime = 0x%08X", referenceTime, connectTime);

    return connectTime;
}

/*
 *  ======== RCL_Handler_BLE5_findPacketDuration ========
 */
static uint32_t RCL_Handler_BLE5_findPacketDuration(uint32_t length, uint16_t phyFeatures)
{
    uint32_t duration;
    switch (phyFeatures & BLE_PHY_FEATURE_PHY_MASK)
    {
        case BLE_PHY_FEATURE_PHY_1MBPS:
        default:
            duration = BLE_1MBPS_PACKET_BASE_TIME + BLE_1MBPS_TIME_PER_BYTE * length;
            break;

        case BLE_PHY_FEATURE_PHY_2MBPS:
            duration = BLE_2MBPS_PACKET_BASE_TIME + BLE_2MBPS_TIME_PER_BYTE * length;
            break;

        case BLE_PHY_FEATURE_PHY_CODED:
            if ((phyFeatures & 0x0004) == BLE_PHY_FEATURE_CODING_S8)
            {
                duration = BLE_CODED_S8_PACKET_BASE_TIME + BLE_CODED_S8_TIME_PER_BYTE * length;
            }
            else
            {
                duration = BLE_CODED_S2_PACKET_BASE_TIME + BLE_CODED_S2_TIME_PER_BYTE * length;
            }
            break;
    }
    return duration;
}

/*
 *  ======== RCL_Handler_BLE5_findNumExtraBytes ========
 */
static uint32_t RCL_Handler_BLE5_findNumExtraBytes(uint32_t fifoCfg)
{
    uint32_t numExtraBytes = 0;
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDCRC_M)
    {
        numExtraBytes += BLE_CRC_LENGTH;
    }
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDSTATUS_M)
    {
        numExtraBytes += 1;
    }
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDLQI_M)
    {
        numExtraBytes += 1;
    }
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDFREQEST_M)
    {
        numExtraBytes += 1;
    }
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDRSSI_M)
    {
        numExtraBytes += 1;
    }
    if (fifoCfg & PBE_BLE5_RAM_FIFOCFG_APPENDTIMESTAMP_M)
    {
        numExtraBytes += sizeof(uint32_t);
    }

    return numExtraBytes;
}

/*
 *  ======== RCL_Handler_BLE5_findRxSyncOverhead ========
 */
static uint16_t RCL_Handler_BLE5_findRxSyncOverhead(uint16_t phyFeatures)
{
    uint16_t overhead;
    switch (phyFeatures & BLE_PHY_FEATURE_PHY_MASK)
    {
        case BLE_PHY_FEATURE_PHY_1MBPS:
        default:
            overhead = RX_SYNC_OVERHEAD_1MBPS;
            break;

        case BLE_PHY_FEATURE_PHY_2MBPS:
            overhead = RX_SYNC_OVERHEAD_2MBPS;
            break;

        case BLE_PHY_FEATURE_PHY_CODED:
            overhead = RX_SYNC_OVERHEAD_CODED;
            break;
    }
    return overhead;
}

/*
 *  ======== RCL_Handler_BLE5_updateBackoffParams ========
 */
static void RCL_Handler_BLE5_updateBackoffParams(RCL_CtxScanInit *ctx, uint16_t endCause)
{
    if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
    {
        /* SCAN_RSP, AUX_SCAN_RSP, AUX_CONNECT_RSP received OK */
        ctx->backoffStatus.backOffLastFail = 0;
        if (ctx->backoffStatus.backOffLastSucceed != 0)
        {
            /* Decrement backoffUpper */
            if (ctx->backoffUpper > 0)
            {
                ctx->backoffUpper--;
            }
            ctx->backoffStatus.backOffLastSucceed = 0;
        }
        else
        {
            ctx->backoffStatus.backOffLastSucceed = 1;
        }
    }
    else
    {
        /* SCAN_RSP, AUX_SCAN_RSP or AUX_CONNECT_RSP not received OK */
        ctx->backoffStatus.backOffLastSucceed = 0;
        if (ctx->backoffStatus.backOffLastFail != 0)
        {
            /* Increment backoffUpper */
            if (ctx->backoffUpper < BACKOFF_UPPER_MAX)
            {
                ctx->backoffUpper++;
            }
            ctx->backoffStatus.backOffLastFail = 0;
        }
        else
        {
            ctx->backoffStatus.backOffLastFail = 1;
        }
    }
    /* Set new backoff count */
    /* Backoff definition in PBE is one less count than in Bluetooth spec */
    /* This gives value from 0 to (2^backoffUpper - 1) */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE5_RAM_O_BACKOFFCNT) = (RCL_Handler_BLE5_getRandomNumber() & ((1 << ctx->backoffUpper) - 1));
}

/*
 *  ======== RCL_Handler_BLE5_getAuxPtrFromTxBuffer ========
 */
static void RCL_Handler_BLE5_getAuxPtrFromTxBuffer(RCL_Buffer_TxBuffer *curBuffer, RCL_AuxPtrInfo *auxPtrInfo, uint8_t offset)
{
    uint8_t payloadIndex = curBuffer->numPad - 1 + BLE_HEADER_LENGTH;
    uint8_t pktLen = curBuffer->data[payloadIndex - 1];
    uint8_t extHdrFlags = curBuffer->data[payloadIndex + 1];

    uint8_t auxPtrIndex = RCL_Handler_BLE5_checkExtHdrField(extHdrFlags, BLE_EXTENDED_HEADER_AUXPTR_BM);

    if (auxPtrIndex != 0)
    {
        /*
         * Consider that the extended header takes 2 bytes, one for the extended header length
         * and one for the header flags.
         */
        auxPtrIndex += payloadIndex + 2;

        /* Determine Tx FIFO pointer to the auxOffset */
        auxPtrInfo->auxChCaOffsetUnitsFifoPtr = LRF_getTxFifoWrAddr(offset + payloadIndex + auxPtrIndex);
        auxPtrInfo->auxOffsetLowFifoPtr = LRF_getTxFifoWrAddr(offset + payloadIndex + auxPtrIndex + 1);
        auxPtrInfo->auxOffsetHighFifoPtr = LRF_getTxFifoWrAddr(offset + payloadIndex + auxPtrIndex + 2);

        /* Extract AuxPtr information from Tx Buffer */
        auxPtrInfo->pktLen = pktLen;
        auxPtrInfo->ptrIndex = auxPtrIndex;
        auxPtrInfo->chIndex = curBuffer->data[auxPtrIndex] & 0x3F;
        auxPtrInfo->ca = ((curBuffer->data[auxPtrIndex] & 0x40) >> 6);
        auxPtrInfo->offsetUnits = (curBuffer->data[auxPtrIndex] >> 7);
        auxPtrInfo->auxOffset = ((uint16_t)(curBuffer->data[auxPtrIndex + 2] & 0x1F) << 8) | (uint16_t)(curBuffer->data[auxPtrIndex + 1]);
        auxPtrInfo->auxPhy = curBuffer->data[auxPtrIndex + 2] >> 5;
        auxPtrInfo->auxPtrPresent = true;
    }
    else
    {
        auxPtrInfo->pktLen = pktLen;
        auxPtrInfo->ptrIndex = 0;
        auxPtrInfo->chIndex = 0;
        auxPtrInfo->offsetUnits = 0;
        auxPtrInfo->auxOffset = 0;
        auxPtrInfo->ca = 0;
        auxPtrInfo->auxPhy = 0;
        auxPtrInfo->auxChCaOffsetUnitsFifoPtr = NULL;
        auxPtrInfo->auxOffsetLowFifoPtr = NULL;
        auxPtrInfo->auxOffsetHighFifoPtr = NULL;
        auxPtrInfo->auxPtrPresent = false;
    }
}

/*
 *  ======== RCL_Handler_BLE5_checkExtHdrField ========
 */
static uint8_t RCL_Handler_BLE5_checkExtHdrField(uint8_t extHdrFlags, uint8_t fieldMask)
{
    uint8_t fieldIndex = 0;

    /* Check extended header flags to determine the index of the desired field (if present) */
    if (extHdrFlags & fieldMask)
    {
        if (extHdrFlags & BLE_EXTENDED_HEADER_ADVA_BM)
        {
            fieldIndex += BLE_EXTENDED_HEADER_ADVA_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_TARGETA_BM)
        {
            fieldIndex += BLE_EXTENDED_HEADER_TARGETA_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_CTEINFO_BM)
        {
            fieldIndex += BLE_EXTENDED_HEADER_CTEINFO_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_ADI_BM)
        {
            fieldIndex += BLE_EXTENDED_HEADER_ADI_LEN;
        }
        if ((extHdrFlags & BLE_EXTENDED_HEADER_AUXPTR_BM) && (fieldMask == BLE_EXTENDED_HEADER_SYNCINFO_BM))
        {
            fieldIndex += BLE_EXTENDED_HEADER_AUXPTR_LEN;
        }
    }

    return fieldIndex;
}

/*
 *  ======== RCL_Handler_BLE5_readAuxPtrFromRxBuffer ========
 */
static void RCL_Handler_BLE5_readAuxPtrFromRxBuffer(uint32_t *data32, RCL_AuxPtrInfo *auxPtrInfo)
{
    uint8_t *data8;
    data8 = (uint8_t*) data32;
    uint8_t payloadIndex = 6 + BLE_HEADER_LENGTH;
    uint8_t extHdrFlags = data8[payloadIndex + 1];

    /* Check advertising type */
    if (extHdrFlags & BLE_EXTENDED_HEADER_AUXPTR_BM)
    {
        /* Extract AuxPtr information */
        uint8_t auxPtrIndex = payloadIndex + 2;

        if (extHdrFlags & BLE_EXTENDED_HEADER_ADVA_BM)
        {
            auxPtrIndex += BLE_EXTENDED_HEADER_ADVA_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_TARGETA_BM)
        {
            auxPtrIndex += BLE_EXTENDED_HEADER_TARGETA_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_CTEINFO_BM)
        {
            auxPtrIndex += BLE_EXTENDED_HEADER_CTEINFO_LEN;
        }
        if (extHdrFlags & BLE_EXTENDED_HEADER_ADI_BM)
        {
            auxPtrIndex += BLE_EXTENDED_HEADER_ADI_LEN;
        }

        auxPtrInfo->auxOffset = ((uint16_t)(data8[auxPtrIndex + 2] & 0x1F) << 8) | (uint16_t)(data8[auxPtrIndex + 1]);
        auxPtrInfo->ca = ((data8[auxPtrIndex] & 0x40) >> 6);
        auxPtrInfo->offsetUnits = data8[auxPtrIndex] >> 7;
        auxPtrInfo->chIndex = data8[auxPtrIndex] & 0x3F;
        auxPtrInfo->auxPhy = data8[auxPtrIndex + 2] >> 5;
        auxPtrInfo->ptrIndex = auxPtrIndex;
        auxPtrInfo->pktLen = data8[payloadIndex - 1];

        auxPtrInfo->auxChCaOffsetUnitsFifoPtr = NULL;
        auxPtrInfo->auxOffsetHighFifoPtr = NULL;
        auxPtrInfo->auxOffsetLowFifoPtr = NULL;
        auxPtrInfo->auxPtrPresent = true;
    }
    else
    {
        auxPtrInfo->pktLen = 0;
        auxPtrInfo->ptrIndex = 0;
        auxPtrInfo->chIndex = 0;
        auxPtrInfo->offsetUnits = 0;
        auxPtrInfo->auxOffset = 0;
        auxPtrInfo->ca = 0;
        auxPtrInfo->auxPhy = 0;
        auxPtrInfo->auxChCaOffsetUnitsFifoPtr = NULL;
        auxPtrInfo->auxOffsetLowFifoPtr = NULL;
        auxPtrInfo->auxOffsetHighFifoPtr = NULL;
        auxPtrInfo->auxPtrPresent = false;
    }
}

/*
 *  ======== RCL_Handler_BLE5_updateAuxPtr ========
 */
static bool RCL_Handler_BLE5_updateAuxPtr(RCL_AuxPtrInfo *auxPtr, uint32_t packetDuration, uint8_t chanMap, bool switchPhy)
{
    uint16_t auxOffsetUs;
    uint16_t auxOffset;
    uint8_t  auxChCaOffsetUnits;
    uint8_t  auxOffsetLow;
    uint8_t  auxOffsetHigh;
    bool status = true;

    uint8_t primaryChPacketsLeft = (chanMap & 1) + ((chanMap >> 1) & 1) + ((chanMap >> 2) & 1);

    /*
     * First calculate the packet duration in terms of 30 us offset units. Then round up to avoid being too late.
     * Note: Packet Duration is given in systim units [250 ns], so divide by 4 to get value in microseconds.
     */
    uint32_t pktDurationInOffsetUnits = BLE_convertSystimUnitsToOffsetUnits(packetDuration, BLE_AUX_OFFSET_30_US);
     /*
      * Automatic calculation of the AuxPtr.
      * All primary advertising channel packets must point to the same time. Since they have the same duration,
      * the packet duration can be used to calculate the auxPtr.
      */
    if ((auxPtr->offsetUnits == 1) && (auxPtr->auxOffset == 0))
    {
        if (primaryChPacketsLeft == 0)
        {
            auxOffsetUs = (pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US;
        }
        else
        {
            auxOffsetUs = primaryChPacketsLeft * ((pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US);
        }

        /* Consider the time that it takes to handle the PHY switching */
        if (switchPhy)
        {
            auxOffsetUs += EXT_ADV_PHY_SWITCHING_DELAY_US;
        }

        /* Calculate the auxOffset in 30 us offset units  */
        auxOffset = auxOffsetUs / BLE_AUX_OFFSET_30_US;

        /* Use 30 [us] offset units. Keep the rest of the AuxPtr information intact */
        auxChCaOffsetUnits = (auxPtr->chIndex | (auxPtr->ca << 6));
    }
    /*
     * If valid, use existing AuxPtr to send the first primary advertising channel packet, and derive the
     * correct value for the rest of the primary advertising channel packets.
     */
    else
    {
        uint32_t minReqOffsetUs;
        auxOffsetUs = auxPtr->offsetUnits ? (auxPtr->auxOffset * BLE_AUX_OFFSET_300_US) : (auxPtr->auxOffset * BLE_AUX_OFFSET_30_US);

        if (primaryChPacketsLeft == 0)
        {
            /* No need to recalculate auxOffset. All primary advertising channel packets sent or start from secondary channel. */
            minReqOffsetUs = (pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US;

            if (auxOffsetUs < minReqOffsetUs)
            {
                /* Invalid initial auxOffset. Deadline can't be met. */
                status = false;
            }
        }
        else
        {
            /* Derive correct auxOffset value based on the number of primary channel packets sent. */
            minReqOffsetUs = primaryChPacketsLeft * ((pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US);

            if (auxOffsetUs < minReqOffsetUs)
            {
                /* Invalid initial auxOffset. Deadline can't be met. */
                status = false;
            }
            else
            {
                auxOffsetUs -= (auxPtr->numPrimaryChPackets - primaryChPacketsLeft) * ((pktDurationInOffsetUnits * BLE_AUX_OFFSET_30_US) + EXT_ADV_INTERVAL_US);
            }
        }

        /* Consider the time that it takes to handle the PHY switching */
        if (switchPhy)
        {
            auxOffsetUs += EXT_ADV_PHY_SWITCHING_DELAY_US;
        }

        /* Calculate the auxOffset in offset units (i.e. 30 us or 300 us) */
        auxOffset = auxPtr->offsetUnits ? (auxOffsetUs / BLE_AUX_OFFSET_300_US) : (auxOffsetUs / BLE_AUX_OFFSET_30_US);

        /* Keep the AuxPtr information intact */
        auxChCaOffsetUnits = (auxPtr->chIndex | (auxPtr->ca << 6) | (auxPtr->offsetUnits << 7));
    }

    auxOffsetLow = auxOffset & 0xFF;
    auxOffsetHigh = (auxOffset >> 8) & 0x1F;
    Log_printf(RclCore, Log_VERBOSE, "Start of next auxiliary packet in %d [us] or %d [offset units]", auxOffsetUs, auxOffset);

    /* Update Tx FIFO */
    *auxPtr->auxChCaOffsetUnitsFifoPtr = auxChCaOffsetUnits;
    *auxPtr->auxOffsetLowFifoPtr = auxOffsetLow;
    *auxPtr->auxOffsetHighFifoPtr = auxOffsetHigh | (auxPtr->auxPhy << 5);

    return status;
}
