/*
 * Copyright (c) 2021-2026, Texas Instruments Incorporated
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
 *  ======== ieee.c ========
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <ti/log/Log.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Profiling.h>
#include <ti/drivers/rcl/RCL_Feature.h>

#include <ti/drivers/rcl/hal/RCL_Hal.h>
#include <ti/drivers/rcl/commands/ieee.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdtxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/pbe_ieee_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ieee_regdef_regs.h)
#include DeviceFamily_constructPath(inc/rfe_common_ram_regs.h)

/** Polynomial to use for PRBS9 data */
#define RCL_HANDLER_IEEE_PRBS9_POLY             0x08800000U
/** Polynomial to use for PRBS15 data */
#define RCL_HANDLER_IEEE_PRBS15_POLY            0x80020000U
/** Polynomial to use for PRBS32 data */
#define RCL_HANDLER_IEEE_PRBS32_POLY            0x00400007U
#define RCL_HANDLER_IEEE_PRBS_INIT              0x0000001FU

#define RCL_HANDLER_IEEE_RESTORE_NONE           0x0000U
#define RCL_HANDLER_IEEE_RESTORE_MODCTRL        0x0001U
#define RCL_HANDLER_IEEE_RESTORE_WHITENING      0x0002U
#define RCL_HANDLER_IEEE_RESTORE_SFD            0x0004U

/* Byte length of IEEE 802.15.4 frame fields */
#define IEEE_PHY_HDR_LEN                        1U
#define IEEE_MAC_FCF_LEN                        2U
#define IEEE_MAC_CRC_LEN                        2U

/* Time from start of preamble to SYSTIM capture at sync found */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
#define IEEE_TIMESTAMP_ADJUST 742U /* CC27XX: Sync found strobe comes 185.5 us after start of preamble */
#else
#define IEEE_TIMESTAMP_ADJUST 697U /* CC23XX: Sync found strobe comes 174.25 us after start of preamble */
#endif

/* Timing constants */
/* Backoff period for the O-QPSK PHY per the 802.15.4 standard */
#define IEEE_BACKOFF_PERIOD                     RCL_SCHEDULER_SYSTIM_US(320)
/* Necessary margin to start CCA */
#define IEEE_CCA_START_TIME_MARGIN              RCL_SCHEDULER_SYSTIM_US(192)

/* Ack length value to indicate no action */
#define RCL_HANDLER_IEEE_ACK_LENGTH_IDLE        0x00U
/* Ack length value to indicate abort */
#define RCL_HANDLER_IEEE_ACK_LENGTH_ABORT       0xFFU
/* Maximum allowed word length for an ACK frame entry */
#define RCL_HANDLER_IEEE_ACK_LENGTH_MAX         33U

/* Minimum possible RSSI value */
#define IEEE_RSSI_MIN_VALUE                     (-128)

/* Maximum correlation threshold in order to disable sync */
#define IEEE_THRESHOLD_NO_SYNC                  0x7FU

/* Special source matching index for busy operation */
#define IEEE_SOURCE_MATCHING_BUSY ((uint16_t) -2)

typedef enum
{
    txStateNoTx,
    txStateNewAction,
    txStateSetupCca,
    txStateWaitForCca,
    txStateStopToSetTx,
    txStateSetTxTime,
    txStateWaitForTx,
    txStateTx,
    txStateTxRx,
    txStateTxRxAck,
    txStateCheckAck,
    txStateWaitForCmdEnd,
    txStateFinished,
} RCL_Handler_Ieee_TxState;

typedef enum
{
    rxStateNoRx,
    rxStateWaitForStart,
    rxStateRunning
} RCL_Handler_Ieee_RxState;

typedef enum
{
    txAckStatePending,
    txAckStatePayloadExpected,
    txAckStatePayloadComplete,
    txAckStateAckAborted,
} RCL_Handler_Ieee_TxAckState;

typedef enum
{
    noEvent,
    customEvent,
    customHardStop,
} RCL_Handler_Ieee_EventType;

typedef enum
{
    noSrcMatchUpdate,
    srcMatchUpdateStart,
    srcMatchUpdateFinish,
} RCL_Handler_Ieee_SourceMatchUpdatePhase;

static struct
{
    struct {
        uint16_t            txFifoSize;
        uint16_t            rxFifoSize;
        RCL_CommandStatus   endStatus;
        bool                activeUpdate;
        bool                apiHardStopPending;
        RCL_MultiBuffer     *curBuffer;
        uint32_t            nextEventTime;
        RCL_Handler_Ieee_EventType eventTimeType;
    } common;
    union {
        struct {
            uint16_t        restoreOpt;
            uint16_t        storedWhitenInit;
            uint32_t        storedWhitenPoly;
            uint32_t        storedMdmSyncA;
        } txTest;
        struct {
            uint32_t        ccaTxStartTime;
            uint32_t        *ackData;
            uint16_t        fifoCfg;
            uint8_t         numPan;
            RCL_StopType    txActionStop;
            RCL_Handler_Ieee_TxState txState;
            RCL_Handler_Ieee_RxState rxState;
            RCL_Handler_Ieee_TxAckState txAckState;
            uint8_t         ccaContentionWindow;
            bool            waitingForValidRssi;
            bool            allowTxDelay;
            bool            alwaysStoreAck;
            bool            frameFiltStop;
            bool            immAckExpected;
            bool            temperatureRestart;
            uint8_t         expSeqNo;
            bool            restoreThresh;
            bool            coexNoGrant;
            uint8_t         coexPriority;
            bool            coexPriorityChange;
            bool            coexRestart;
            RCL_IEEE_SourceMatchingUpdate srcMatchUpdateDesc;
            union {
                RCL_CmdIeee_PanIdAddr newPanIdAddr;
                uint64_t newExtAddr;
            } newSrcMatch;
            bool (*srcMatchUpdateFun)(RCL_CmdIeeeRxTx *ieeeCmd);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            uint16_t        demc1be10;
            uint16_t        demc1be12;
#else
            uint16_t        demc1be1;
            uint16_t        demc1be2;
#endif
            volatile uint8_t ackNumRemainingWords;
            volatile uint8_t ackNumWords;
            volatile RCL_IEEE_AckEntryResult ackResult;
            volatile uint8_t bytesReadFromFifo;
            volatile uint16_t savedRxfRp;
            volatile bool rxActionUpdate;
            volatile RCL_Handler_Ieee_SourceMatchUpdatePhase srcMatchUpdatePhase;
        } rxTx;
    };
} ieeeHandlerState;

/* Access coex configuration for reading */
extern const LRF_CoexConfiguration lrfCoexConfiguration;

/* Check for global coex grant enable */
#define COEX_GRANT_GLOBAL_ENABLE(coexConfig) (coexConfig.grantPin != (RFE_COMMON_RAM_GRANTPIN_CFG_DIS >> RFE_COMMON_RAM_GRANTPIN_CFG_S))

/* Check for global coex request (+ priority) enable */
#define COEX_REQUEST_GLOBAL_ENABLE(coexConfig) (coexConfig.T1 != 0U)

static RCL_CommandStatus RCL_Handler_Ieee_processRxAction(const RCL_CmdIeee_RxAction *rxAction);
static RCL_IEEE_AckEntryResult RCL_Handler_Ieee_txAckUpdate(RCL_CmdIeeeRxTx *cmd, uint32_t *ackData, uint8_t numWords);
static void RCL_Handler_Ieee_updateRxCurBufferAndFifo(List_List *rxBuffers);
static RCL_CommandStatus RCL_Handler_Ieee_findPbeErrorEndStatus(uint16_t pbeEndStatus);
static uint32_t RCL_Handler_Ieee_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate);
static void RCL_Handler_Ieee_updateStats(RCL_StatsIeee *stats, uint32_t startTime);
static bool RCL_Handler_Ieee_initStats(RCL_StatsIeee *stats, uint32_t startTime);
static bool RCL_Handler_Ieee_setCustomEventTime(uint32_t eventTime, uint32_t timeMargin, bool hardStop);
static bool RCL_Handler_Ieee_restoreStopTime(void);
static RCL_IEEE_UpdateResult RCL_Handler_Ieee_processSourceMatchingOperation(RCL_IEEE_SourceMatchingUpdate description,
    uint16_t *entryEnable, uint16_t *framePending);
static bool RCL_Handler_Ieee_updateSrcMatchTableShort(RCL_CmdIeeeRxTx *ieeeCmd);
static bool RCL_Handler_Ieee_updateSrcMatchTableExt(RCL_CmdIeeeRxTx *ieeeCmd);
static void RCL_Handler_Ieee_updateSrcMatchTable(uint16_t *entryEnable, uint16_t *framePending, RCL_CmdIeee_PanIdAddr *shortEntry, uint64_t *extEntry);
static uint32_t RCL_Handler_Ieee_findNumExtraBytes(uint32_t fifoCfg);
static void RCL_Handler_Ieee_setCoexEndMode(void);
static void RCL_Handler_Ieee_setCoexPriority(bool tx);
static void RCL_Handler_Ieee_processCoexTxPriority(RCL_CmdIeee_TxAction *txAction);

/*
 *  ======== RCL_Handler_Ieee_RxTx ========
 */
RCL_Events RCL_Handler_Ieee_RxTx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdIeeeRxTx *ieeeCmd = (RCL_CmdIeeeRxTx *) cmd;
    RCL_Events rclEvents = {.value = 0};
    bool startTx = false;
    bool doCca = false;
    bool restartRx = false;

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        ieeeHandlerState.rxTx.rxState = rxStateNoRx;
        ieeeHandlerState.rxTx.txState = txStateNoTx;
        ieeeHandlerState.rxTx.txAckState = txAckStatePending;
        ieeeHandlerState.rxTx.ackNumWords = RCL_HANDLER_IEEE_ACK_LENGTH_IDLE;
        ieeeHandlerState.rxTx.temperatureRestart = false;
        ieeeHandlerState.rxTx.bytesReadFromFifo = 0;
        ieeeHandlerState.common.eventTimeType = noEvent;
        ieeeHandlerState.common.apiHardStopPending = false;
        ieeeHandlerState.rxTx.txActionStop = RCL_StopType_None;
        ieeeHandlerState.rxTx.restoreThresh = false;
        ieeeHandlerState.rxTx.rxActionUpdate = false;
        ieeeHandlerState.rxTx.srcMatchUpdatePhase = noSrcMatchUpdate;
        ieeeHandlerState.rxTx.numPan = 0;
        ieeeHandlerState.rxTx.coexNoGrant = false;
        ieeeHandlerState.rxTx.fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FIFOCFG);
        ieeeHandlerState.rxTx.coexPriorityChange = false;
        ieeeHandlerState.rxTx.coexRestart = false;

        RCL_CmdIeee_RxAction *rxAction = ieeeCmd->rxAction;
        RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;

        RCL_CmdIeee_CcaMode ccaMode = RCL_CmdIeee_NoCca;
        if (txAction != NULL)
        {
            ccaMode = txAction->ccaMode;
        }

        if (rxAction == NULL)
        {
            if (txAction == NULL)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
                return rclEvents;
            }
            else
            {
                /* Go straight to TX */
                /* CSMA or RX ACK not possible with pure TX */
                if (ccaMode != RCL_CmdIeee_NoCca ||
                    txAction->expectImmAck != 0U ||
                    txAction->expectEnhAck != 0U)
                {
                    cmd->status = RCL_CommandStatus_Error_Param;
                    rclEvents.lastCmdDone = 1;
                    return rclEvents;
                }
            }
        }
        else
        {
            if (rxAction->numPan > RCL_CMD_IEEE_MAX_NUM_PAN)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
                return rclEvents;
            }
            else if (rxAction->numPan == 0U && txAction != NULL &&
                     (txAction->expectImmAck != 0U || txAction->expectEnhAck != 0U))
            {
                /* RX ACK not supported with promiscuous mode */
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
                return rclEvents;
            }
            else
            {
                /* Nothing to do */
            }
        }

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
        /* Make sure SWTCXO does not adjust clock while radio is running */
        RCL_Hal_powerSetSwTcxoUpdateConstraint();

        if (COEX_GRANT_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeCmd->coexControl.grantEnable)
        {
            LRF_enableCoexGrant();
            /* Clear and enable canceled grant interrupt */
            LRF_clearHwInterrupt(LRF_EventRfesoft1.value);
            LRF_enableHwInterrupt(LRF_EventRfesoft1.value);
        }
        if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeCmd->coexControl.requestPriorityEnable)
        {
            ieeeHandlerState.rxTx.coexPriority = ((uint8_t)ieeeCmd->coexControl.priority) ^ ((uint8_t)lrfCoexConfiguration.invertedPriority);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXT1) = lrfCoexConfiguration.T1;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_TSYNC) = lrfCoexConfiguration.ieeeTSync;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCORRMASK) = lrfCoexConfiguration.ieeeCorrMask;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG) =
                (((uint16_t) lrfCoexConfiguration.T2 << PBE_IEEE_RAM_COEXCFG_T2_S) & PBE_IEEE_RAM_COEXCFG_T2_M) |
                (((uint16_t) ieeeCmd->coexControl.rxMode) << PBE_IEEE_RAM_COEXCFG_RXSYNC_S) |
                ((uint16_t) ieeeHandlerState.rxTx.coexPriority << PBE_IEEE_RAM_COEXCFG_PRIORITY_S) |
                PBE_IEEE_RAM_COEXCFG_COEXEN_M;
        }
        else
        {
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG) = 0;
        }

        if (txAction != NULL)
        {
            uint32_t cmdTime = (cmd->scheduling == RCL_Schedule_AbsTime) ? cmd->timing.absStartTime : RCL_Scheduler_getCurrentTime();
            uint32_t txActionTime = (txAction->ccaScheduling == RCL_Schedule_AbsTime) ? txAction->absCcaStartTime : cmdTime;
            if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeCmd->coexControl.requestPriorityEnable)
            {
                RCL_Handler_Ieee_processCoexTxPriority(txAction);
            }
            /* Check that TX action start time is not before the command start time */
            if ((txAction->allowDelay == 0U) && (!RCL_Scheduler_isLater(cmdTime, txActionTime)))
            {
                txAction->txStatus = RCL_CommandStatus_Error_StartTooLate;
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
            else
            {
                if (ccaMode == RCL_CmdIeee_NoCca)
                {
                    /* Check if the command should go directly to TX */
                    uint32_t txTime = txActionTime + txAction->relativeTxStartTime;
                    ieeeHandlerState.rxTx.ccaTxStartTime = txTime;
                    ieeeHandlerState.rxTx.allowTxDelay = txAction->allowDelay || txAction->allowTxDelay;
                    if (rxAction == NULL || RCL_Scheduler_delta(cmdTime, txTime) < (int32_t)(2U * IEEE_CCA_START_TIME_MARGIN))
                    {
                        /* TX starts after a short time; don't do RX first */
                        startTx = true;
                    }
                    else
                    {
                        /* Set receiver to stop in time for TX */
                        ieeeHandlerState.rxTx.txState = txStateStopToSetTx;
                    }
                }
                else
                {
                    /* Schedule CCA evaluation */
                    txAction->txStatus = RCL_CommandStatus_Scheduled;
                    ieeeHandlerState.rxTx.txState = txStateSetupCca;
                }
            }
        }

        if (rclEvents.lastCmdDone == 0U)
        {
            /* Program frequency word */
            LRF_programFrequency(ieeeCmd->rfFrequency, startTx);

            if (LRF_programTxPower(ieeeCmd->txPower, ieeeCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
        }

        if (rclEvents.lastCmdDone == 0U)
        {
            /* Enable radio */
            LRF_enable();

            ieeeHandlerState.common.activeUpdate = RCL_Handler_Ieee_initStats(ieeeCmd->stats,
                                                                                rclSchedulerState.actualStartTime);

            RCL_CommandStatus startTimeStatus;
            if (startTx)
            {
                RCL_CommandTiming timing = cmd->timing;
                timing.absStartTime = ieeeHandlerState.rxTx.ccaTxStartTime;
                startTimeStatus = RCL_Scheduler_setCustomStartStopTimeEarliestStart(&timing, RCL_Schedule_AbsTime,
                    ieeeHandlerState.rxTx.allowTxDelay, earliestStartTime);
                ieeeHandlerState.rxTx.txState = txStateWaitForTx;
            }
            else
            {
                startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            }

            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1;
            }
        }

        if (rclEvents.lastCmdDone == 0U && rxAction != NULL)
        {
            /* Prepare receiver */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0; /* No timeout except from SYSTIM */
            RCL_CommandStatus status = RCL_Handler_Ieee_processRxAction(rxAction);
            if (status >= RCL_CommandStatus_Finished)
            {
                cmd->status = status;
                rclEvents.lastCmdDone = 1;
            }
        }

        if (rclEvents.lastCmdDone == 0U)
        {
            /* Initialize TX FIFO */
            ieeeHandlerState.common.txFifoSize = (uint16_t) LRF_prepareTxFifo();

            if (rxAction != NULL)
            {
                /* Start receiver */
                /* Set up sync found capture */
                RCL_Hal_setupSyncFoundCap();
                /* Initialize RX FIFO */
                ieeeHandlerState.common.rxFifoSize = (uint16_t) LRF_prepareRxFifo();
                ieeeHandlerState.common.curBuffer = NULL;
                RCL_Handler_Ieee_updateRxCurBufferAndFifo(&rxAction->rxBuffers);

                LRF_enableTemperatureMonitoring();
                if (!startTx)
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                        (ieeeHandlerState.rxTx.frameFiltStop ? PBE_IEEE_RAM_OPCFG_STOP_HARDEND : PBE_IEEE_RAM_OPCFG_STOP_SOFTEND) |
                        PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES |
                        PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES |
                        PBE_IEEE_RAM_OPCFG_TXINFINITE_NO |
                        PBE_IEEE_RAM_OPCFG_TXPATTERN_NO |
                        PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                        PBE_IEEE_RAM_OPCFG_START_SYNC |
                        PBE_IEEE_RAM_OPCFG_SINGLE_DIS |
                        PBE_IEEE_RAM_OPCFG_IFSPERIOD_EN;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                        PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT | PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_DIS;
                    /* Post cmd */
                    Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Ieee_RxTx: Starting IEEE RX");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_RX;
                    /* Clear RSSI valid interrupt flag */
                    LRF_clearHwInterrupt(LRF_EventRfesoft0.value);
                    ieeeHandlerState.rxTx.rxState = rxStateWaitForStart;
                }
            }
            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;

            /* End status not determined */
            ieeeHandlerState.common.endStatus = RCL_CommandStatus_Active;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.stopTimesUpdated != 0U)
        {
            if (ieeeHandlerState.common.eventTimeType != noEvent)
            {
                bool hardStop = (ieeeHandlerState.common.eventTimeType == customHardStop);
                /* Event has been turned off by stop time modification */
                ieeeHandlerState.common.eventTimeType = noEvent;
                /* Turn back on if possible */
                (void) RCL_Handler_Ieee_setCustomEventTime(ieeeHandlerState.common.nextEventTime, IEEE_CCA_START_TIME_MARGIN, hardStop);
            }
        }
        if (rclEventsIn.handlerCmdUpdate != 0U)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            RCL_StopType txActionStop = ieeeHandlerState.rxTx.txActionStop;
            if (txActionStop != RCL_StopType_None && txAction != NULL)
            {
                if (txAction->txStatus < RCL_CommandStatus_Active)
                {
                    Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Descheduling pending TX action");
                    /* TX action can be descheduled */
                    txAction->txStatus = RCL_CommandStatus_DescheduledApi;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if (ieeeHandlerState.rxTx.txState <= txStateWaitForTx)
                {
                    /* Waiting for CCA or TX to start; hard or graceful stop possible */
                    if (txActionStop == RCL_StopType_Graceful || txActionStop == RCL_StopType_Hard)
                    {
                        (void) RCL_Handler_Ieee_restoreStopTime();
                        Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Stopping pending CCA or TX");
                        txAction->txStatus = (txActionStop == RCL_StopType_Graceful) ? RCL_CommandStatus_GracefulStopApi : RCL_CommandStatus_HardStopApi;
                        ieeeHandlerState.rxTx.txState = txStateFinished;
                        startTx = false;
                    }
                }
                else if ((ieeeHandlerState.rxTx.txState == txStateTx ||
                          ieeeHandlerState.rxTx.txState == txStateTxRx ||
                          ieeeHandlerState.rxTx.txState == txStateTxRxAck) &&
                          (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXSTATUS) & PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS) != 0U)
                {
                    if (txActionStop == RCL_StopType_Hard)
                    {
                        Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Stopping TX due to hard stop");
                        /* Send hard stop to PBE */
                        LRF_sendHardStop();
                        /* TX action will end when PBE is finished */
                        ieeeHandlerState.common.apiHardStopPending = true;
                    }
                }
                else if (ieeeHandlerState.rxTx.txState == txStateTxRxAck)
                {
                    if (txActionStop == RCL_StopType_Hard)
                    {
                        /* Hard stop - give up on TX action, but keep receiver alive */
                        txAction->txStatus = RCL_CommandStatus_HardStopApi;
                        ieeeHandlerState.rxTx.txState = txStateFinished;
                    }
                }
                else
                {
                    /* No action needed, TX action should end very soon */
                }
                /* Clear stop action  */
                ieeeHandlerState.rxTx.txActionStop = RCL_StopType_None;
            }
            else if (ieeeHandlerState.rxTx.txState == txStateNewAction && txAction != NULL)
            {
                uint32_t currentTime = RCL_Scheduler_getCurrentTime();
                uint32_t txActionTime = (txAction->ccaScheduling == RCL_Schedule_AbsTime) ? txAction->absCcaStartTime : currentTime;
                /* Check that TX action start time is not in the past */
                if ((txAction->ccaScheduling == RCL_Schedule_AbsTime) && (txAction->allowDelay == 0U) &&
                    (!RCL_Scheduler_isLater(currentTime, txActionTime)))
                {
                    txAction->txStatus = RCL_CommandStatus_Error_StartTooLate;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if (ieeeHandlerState.rxTx.numPan == 0U &&
                     (txAction->expectImmAck != 0U || txAction->expectEnhAck != 0U))
                {
                    txAction->txStatus = RCL_CommandStatus_Error_Param;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else
                {
                    txAction->txStatus = RCL_CommandStatus_Scheduled;
                    if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeCmd->coexControl.requestPriorityEnable)
                    {
                        RCL_Handler_Ieee_processCoexTxPriority(txAction);
                    }
                    if (txAction->ccaMode == RCL_CmdIeee_NoCca)
                    {
                        /* Check if the command should go directly to TX */
                        uint32_t txTime = txActionTime + txAction->relativeTxStartTime;
                        ieeeHandlerState.rxTx.ccaTxStartTime = txTime;
                        ieeeHandlerState.rxTx.allowTxDelay = txAction->allowDelay || txAction->allowTxDelay;

                        if (RCL_Scheduler_delta(currentTime, txTime) < (int32_t)IEEE_CCA_START_TIME_MARGIN)
                        {
                            /* TX starts after a short time; stop RX now */
                            ieeeHandlerState.rxTx.txState = txStateSetTxTime;
                            /* Configure PBE to keep REQUEST asserted if coex is enabled, REQUEST was already asserted,
                               and priority is not set to be changed. */
                            RCL_Handler_Ieee_setCoexEndMode();
                            /* Stop running RX */
                            LRF_sendHardStop();
                        }
                        else
                        {
                            /* Set receiver to stop in time for TX */
                            ieeeHandlerState.rxTx.txState = txStateStopToSetTx;
                        }
                    }
                    else
                    {
                        /* Schedule CCA evaluation */
                        ieeeHandlerState.rxTx.txState = txStateSetupCca;
                    }
                }
            }
            else if (ieeeHandlerState.rxTx.rxActionUpdate)
            {
                /* The RX action update is not handled now if there is a TX action */
                if (ieeeHandlerState.rxTx.txState == txStateNoTx)
                {
                    /* Send graceful stop, but keep flag */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_EOPSTOP;
                }
            }
            else if (ieeeHandlerState.rxTx.srcMatchUpdatePhase == srcMatchUpdateStart)
            {
                if (ieeeHandlerState.rxTx.srcMatchUpdateFun(ieeeCmd))
                {
                    rclEvents.cmdUpdateDone = 1;
                }
            }
            else
            {
                /* Nothing to do */
            }
        }
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1;
            if (ieeeHandlerState.rxTx.rxState == rxStateWaitForStart)
            {
                ieeeHandlerState.rxTx.rxState = rxStateRunning;
            }
        }
        if (rclEventsIn.rxBufferUpdate != 0U)
        {
            RCL_CmdIeee_RxAction *rxAction = ieeeCmd->rxAction;
            if (rxAction != NULL)
            {
                RCL_Handler_Ieee_updateRxCurBufferAndFifo(&rxAction->rxBuffers);
            }
        }
        if (rclFeatureControl.enableTemperatureMonitoring)
        {
            if (rclEventsIn.silentlyRestartRadio != 0U && ieeeHandlerState.rxTx.rxState != rxStateNoRx)
            {
                ieeeHandlerState.rxTx.temperatureRestart = true;
                /* If TX command is pending or running, wait until it is done */
                if (ieeeHandlerState.rxTx.txState == txStateNoTx)
                {
                    /* Send graceful stop command to radio */
                    LRF_sendGracefulStop();
                }
            }
        }
        if (COEX_GRANT_GLOBAL_ENABLE(lrfCoexConfiguration) && lrfEvents.rfesoft1)
        {
            /* Send abort and set flag */
            LRF_sendHardStop();
            ieeeHandlerState.rxTx.coexNoGrant = true;
        }

        if (ieeeHandlerState.rxTx.txState == txStateStopToSetTx && ieeeHandlerState.rxTx.rxState == rxStateRunning)
        {
            /* Set receiver to stop in time for TX */
            bool timeSet = RCL_Handler_Ieee_setCustomEventTime(ieeeHandlerState.rxTx.ccaTxStartTime - IEEE_CCA_START_TIME_MARGIN, IEEE_CCA_START_TIME_MARGIN, true);
            if (timeSet)
            {
                ieeeHandlerState.rxTx.txState = txStateSetTxTime;
            }
            else
            {
                /* Command will end soon - park TX action until then */
                ieeeHandlerState.rxTx.txState = txStateWaitForCmdEnd;
            }
        }

        if (ieeeHandlerState.rxTx.txState == txStateSetupCca && ieeeHandlerState.rxTx.rxState == rxStateRunning)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            uint32_t ccaTime = txAction->absCcaStartTime;
            RCL_ScheduleType ccaScheduling = txAction->ccaScheduling;
            bool allowDelay = (ccaScheduling == RCL_Schedule_Now) ? true : (txAction->allowDelay != 0U);

            uint32_t currentTime = RCL_Scheduler_getCurrentTime();
            ieeeHandlerState.rxTx.waitingForValidRssi = false;

            uint8_t ccaContentionWindow = txAction->ccaContentionWindow;
            if (ccaContentionWindow < 1U)
            {
                ccaContentionWindow = 1;
            }
            ieeeHandlerState.rxTx.ccaContentionWindow = ccaContentionWindow;
            uint32_t ccaDuration = (uint32_t) (ccaContentionWindow - 1U) * IEEE_BACKOFF_PERIOD;
            if (ccaScheduling == RCL_Schedule_AbsTime &&
                RCL_Scheduler_isLater(currentTime + IEEE_CCA_START_TIME_MARGIN, ccaTime))
            {
                bool timeSet = RCL_Handler_Ieee_setCustomEventTime(ccaTime, ccaDuration + IEEE_CCA_START_TIME_MARGIN, false);
                ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime;
                if (timeSet)
                {
                    ieeeHandlerState.rxTx.txState = txStateWaitForCca;
                }
            }
            else if (allowDelay || ccaScheduling == RCL_Schedule_Now)
            {
                if (ccaScheduling == RCL_Schedule_Now)
                {
                    ieeeHandlerState.rxTx.ccaTxStartTime = currentTime;
                }
                else
                {
                    /* Use programmed CCA time for future calculations even if it was in the past */
                    ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime;
                }
                ieeeHandlerState.rxTx.txState = txStateWaitForCca;
                /* Start immediately */
                doCca = true;
            }
            else
            {
                /* Requested too late */
                txAction->txStatus = RCL_CommandStatus_Error_StartTooLate;
                /* Signal end of action */
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
        }

        if ((rclEventsIn.hardStop && ieeeHandlerState.common.eventTimeType == customEvent) ||
            (lrfEvents.rfesoft0 && LRF_readRssi() != LRF_RSSI_INVALID))
        {
            if (ieeeHandlerState.rxTx.txState == txStateWaitForCca)
            {
                /* The hard stop event means "do CCA" and will not cause PBE to stop */
                doCca = true;
                Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Perform CCA");
                /* Set back stop event */
                (void) RCL_Handler_Ieee_restoreStopTime();
            }
        }

        if (doCca)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            RCL_CmdIeee_CcaMode ccaMode = txAction->ccaMode;
            txAction->txStatus = RCL_CommandStatus_Active;

            bool busy = false;
            /* All CCA modes shall report busy if packet is in progress */
            if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXSTATUS) != 0U)
            {
                busy = true;
                Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: CCA busy because packet is in progress");
                if (ieeeHandlerState.rxTx.waitingForValidRssi)
                {
                    LRF_disableHwInterrupt(LRF_EventRfesoft0.value);
                    ieeeHandlerState.rxTx.waitingForValidRssi = false;
                }
            }

            if (!busy && (ccaMode != RCL_CmdIeee_CcaMode4Aloha))
            {
                /* Check RSSI */
                int8_t rssi = LRF_readRssi();
                /* RSSI is checked even for CCA mode 2, as invalid RSSI means that correlation result is not yet ready */
                if (rssi == LRF_RSSI_INVALID && !ieeeHandlerState.rxTx.waitingForValidRssi)
                {
                    /* Wait for RSSI valid */
                    Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: CCA invalid; check again");

                    ieeeHandlerState.rxTx.waitingForValidRssi = true;
                    /* Wait 1 backoff period for valid RSSI */
                    uint32_t ccaTime = ieeeHandlerState.rxTx.ccaTxStartTime;
                    ccaTime += IEEE_BACKOFF_PERIOD;
                    if (txAction->ccaContentionWindow <= 1U)
                    {
                        /* Non-slotted CSMA - wait only until the RSSI is ready, but use the backoff period as a timeout */
                        /* Enable notification on RSSI available */
                        LRF_enableHwInterrupt(LRF_EventRfesoft0.value);
                    }
                    else
                    {
                        /* Store updated CCA time only for slotted CCA */
                        ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime;
                    }

                    /* Set new compare time  */
                    (void) RCL_Handler_Ieee_setCustomEventTime(ccaTime, IEEE_CCA_START_TIME_MARGIN, false);

                    /* If RSSI is not valid the second time around, treat as busy */
                }
                else
                {
                    bool busyRssi = false;
                    bool busySignal = false;

                    LRF_disableHwInterrupt(LRF_EventRfesoft0.value);
                    ieeeHandlerState.rxTx.waitingForValidRssi = false;
                    if (rssi >= txAction->rssiLimit)
                    {
                        busyRssi = true;
                    }

                    uint16_t corrCount = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CORRCNT);

                    if (corrCount > txAction->ccaCorrThresh || rssi == LRF_RSSI_INVALID)
                    {
                        busySignal = true;
                    }

                    switch (ccaMode)
                    {
                        case RCL_CmdIeee_CcaMode1Energy:
                            busy = busyRssi;
                            break;

                        case RCL_CmdIeee_CcaMode2Signal:
                            busy = busySignal;
                            break;

                        case RCL_CmdIeee_CcaMode3EnergyOrSignal:
                            busy = busyRssi || busySignal;
                            break;

                        case RCL_CmdIeee_CcaMode3EnergyAndSignal:
                            busy = busyRssi && busySignal;
                            break;

                        default:
                            /* Other values are invalid or should not be processed here - treat as busy */
                            busy = true;
                            break;
                    }
                    if (busy)
                    {
                        Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: CCA busy; RSSI = %1d dBm, correlation top count = %1d", rssi, corrCount);
                    }
                    else
                    {
                        Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: CCA idle; RSSI = %1d dBm, correlation top count = %1d", rssi, corrCount);
                    }
                }
            }

            if (!ieeeHandlerState.rxTx.waitingForValidRssi)
            {
                if (busy)
                {
                    txAction->txStatus = RCL_CommandStatus_ChannelBusy;
                    /* Signal end of action */
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else
                {
                    uint32_t ccaTime = ieeeHandlerState.rxTx.ccaTxStartTime;
                    ieeeHandlerState.rxTx.ccaContentionWindow -= 1U;
                    if (ieeeHandlerState.rxTx.ccaContentionWindow == 0U)
                    {
                        /* Channel idle - transmit */
                        ieeeHandlerState.rxTx.txState = txStateSetTxTime;
                        ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime + txAction->relativeTxStartTime;
                        ieeeHandlerState.rxTx.allowTxDelay = (bool) txAction->allowTxDelay;
                        Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Stop RX to go to TX");
                        /* Configure PBE to keep REQUEST asserted if coex is enabled, REQUEST was already asserted,
                           and priority is not set to be changed. */
                        RCL_Handler_Ieee_setCoexEndMode();
                        /* Stop running RX */
                        LRF_sendHardStop();
                    }
                    else
                    {
                        /* Slotted CCA - check again after 1 backoff period */
                        ccaTime += IEEE_BACKOFF_PERIOD;
                        /* Set new compare time  */
                        (void) RCL_Handler_Ieee_setCustomEventTime(ccaTime, IEEE_CCA_START_TIME_MARGIN, false);
                        ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime;
                    }
                }
            }
        }

        if (lrfEvents.rxCtrlAck != 0U)
        {
            /* Ack with payload pending */
            ieeeHandlerState.rxTx.txAckState = txAckStatePayloadExpected;
            /* Prepare for new entry */
            ieeeHandlerState.rxTx.ackNumRemainingWords = 0;
            /* Invalidate received frame from reading partial frame */
            ieeeHandlerState.rxTx.bytesReadFromFifo = 0;
        }
        if (lrfEvents.rxEmpty != 0U)
        {
            /* Timeout or ACK reception */
            LRF_disableHwInterrupt(LRF_EventRxEmpty.value);
            if (ieeeHandlerState.rxTx.txState == txStateTxRxAck)
            {
                uint16_t ackStatus = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_ACKSTATUS);

                if ((ackStatus & PBE_IEEE_RAM_ACKSTATUS_SYNCTIMEOUT_M) != 0U)
                {
                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_NoSync;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if ((ackStatus & PBE_IEEE_RAM_ACKSTATUS_CRCOK_M) != 0U)
                {
                    if (ieeeHandlerState.rxTx.alwaysStoreAck && ieeeHandlerState.rxTx.immAckExpected)
                    {
                        /* Need to check received ACK below */
                        ieeeHandlerState.rxTx.txState = txStateCheckAck;
                    }
                    else
                    {
                        /* Check if frame pending (FP) bit was set in the received ACK */
                        if ((ackStatus & PBE_IEEE_RAM_ACKSTATUS_FPSTATE_M) != 0U)
                        {
                            /* FP = 1 */
                            ieeeCmd->txAction->txStatus = RCL_CommandStatus_FramePending;
                        }
                        else
                        {
                            /* FP = 0 */
                            ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
                        }
                        ieeeHandlerState.rxTx.txState = txStateFinished;
                    }
                }
                else if ((ackStatus &
                    (PBE_IEEE_RAM_ACKSTATUS_IGNORED_M | PBE_IEEE_RAM_ACKSTATUS_OTHERFRM_M |
                     PBE_IEEE_RAM_ACKSTATUS_CRCERR_M)) != 0U)
                {
                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_RxErr;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else
                {
                    /* ERROR: ACK status gives no known status; should not happen */
                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_Error;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
            }
        }
        if (lrfEvents.rxCtrl != 0U)
        {
            /* Frame filtering done */
            /* Check if a source matching update is due */
            if (ieeeHandlerState.rxTx.srcMatchUpdatePhase != noSrcMatchUpdate)
            {
                if (ieeeHandlerState.rxTx.srcMatchUpdateFun(ieeeCmd))
                {
                    rclEvents.cmdUpdateDone = 1;
                }
            }
            else
            {
                /* If not, disable interrupt (should not happen) */
                LRF_disableHwInterrupt(LRF_EventRxCtrl.value);
            }
        }

        if (lrfEvents.txDone != 0U)
        {
            LRF_disableHwInterrupt(LRF_EventTxDone.value);
            if (ieeeHandlerState.rxTx.txState == txStateTxRx)
            {
                ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
        }
        if (lrfEvents.opDone != 0U || lrfEvents.opError != 0U)
        {
            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
            ieeeHandlerState.rxTx.rxState = rxStateNoRx;
            if (ieeeHandlerState.rxTx.txState == txStateSetTxTime)
            {
                /* Set up TX start time */
                RCL_CommandStatus status = RCL_Scheduler_setNewStartAbsTime(ieeeHandlerState.rxTx.ccaTxStartTime, ieeeHandlerState.rxTx.allowTxDelay);
                if (status != RCL_CommandStatus_Active)
                {
                    ieeeCmd->txAction->txStatus = status;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                    if (RCL_CommandStatus_isAnyStop(status))
                    {
                        /* Entire command to stop */
                        cmd->status = status;
                        rclEvents.lastCmdDone = 1;
                    }
                }
                else
                {
                    /* Re-enable radio to force a restart of the PBE */
                    LRF_enable();
                    startTx = true;
                    ieeeHandlerState.rxTx.txState = txStateWaitForTx;
                }
            }
            else if (ieeeHandlerState.rxTx.txState == txStateTx)
            {
                if (lrfEvents.opDone != 0U)
                {
                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
                    ieeeHandlerState.rxTx.txState = txStateFinished;

                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
                }
                else
                {
                    RCL_CommandStatus endStatus = ieeeHandlerState.common.endStatus;
                    if (endStatus == RCL_CommandStatus_Active)
                    {
                        if (COEX_GRANT_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexNoGrant)
                        {
                            cmd->status = RCL_CommandStatus_CoexNoGrant;
                        }
                        else
                        {
                            cmd->status = RCL_Handler_Ieee_findPbeErrorEndStatus(endCause);
                        }
                    }
                    else
                    {
                        cmd->status = endStatus;
                    }
                    rclEvents.lastCmdDone = 1;
                }
            }
            else if ((ieeeHandlerState.rxTx.txState >= txStateTxRx && ieeeHandlerState.rxTx.txState <= txStateCheckAck) &&
                endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP && ieeeHandlerState.common.apiHardStopPending)
            {
                /* Hard stop of ongoing TX action */
                ieeeCmd->txAction->txStatus = RCL_CommandStatus_HardStopApi;
                ieeeHandlerState.rxTx.txState = txStateFinished;
                /* Stop is now done */
                ieeeHandlerState.common.apiHardStopPending = false;
            }
            else if (COEX_GRANT_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexNoGrant &&
                (ieeeHandlerState.rxTx.txState >= txStateTxRx && ieeeHandlerState.rxTx.txState <= txStateCheckAck) &&
                endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP)
            {
                /* Ongoing TX action stopped due to no grant */
                ieeeCmd->txAction->txStatus = RCL_CommandStatus_CoexNoGrant;
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
            /* Check if hard stop event happened due to no grant - will be no grant on ACK, since
             * no grant on TX was checked above */
            else if (COEX_GRANT_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexNoGrant
                     && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP
                     && rclSchedulerState.hardStopInfo.apiStopEnabled == 0U)
            {
                /* Receiver should start again */
                restartRx = true;
                /* Generate event */
                rclEvents.coexNoTx = 1;
                /* Stop ongoing ACK */
                ieeeHandlerState.rxTx.txAckState = txAckStatePending;
                /* Invalidate received frame from reading partial frame */
                ieeeHandlerState.rxTx.bytesReadFromFifo = 0;
            }
            /* Check if hard stop happened due to change of coex priority. Make sure that we
             * test that no graceful stop API was called, as the command should then end. */
            else if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexRestart
                     && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP
                     && rclSchedulerState.hardStopInfo.apiStopEnabled == 0U)
            {
                /* Receiver stopped to do coex priority change */
                restartRx = true;
            }
            /* Check if graceful stop event happened due to temperature or parameter update. Make sure that we
             * test that no graceful stop API was called, as the command should then end even if
             * a temperature adjustment is due */
            else if ((ieeeHandlerState.rxTx.temperatureRestart || ieeeHandlerState.rxTx.rxActionUpdate)
                     && endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP
                     && rclSchedulerState.gracefulStopInfo.apiStopEnabled == 0U)
            {
                /* Receiver stopped to do temperature or parameter update */
                restartRx = true;
            }
            else
            {
                RCL_CommandStatus endStatus = ieeeHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
                if (endStatus == RCL_CommandStatus_Active)
                {
                    if (lrfEvents.opError != 0U)
                    {
                        endStatus = RCL_Handler_Ieee_findPbeErrorEndStatus(endCause);
                    }
                    else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                    {
                        endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    }
                    else
                    {
                        endStatus = RCL_CommandStatus_Finished;
                    }
                }
                cmd->status = endStatus;
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
            }
            /* Check if a source matching update is due */
            if (ieeeHandlerState.rxTx.srcMatchUpdatePhase != noSrcMatchUpdate)
            {
                if (ieeeHandlerState.rxTx.srcMatchUpdateFun(ieeeCmd))
                {
                    rclEvents.cmdUpdateDone = 1;
                }
            }
            /* Clear no grant flag and interrupt in all cases */
            ieeeHandlerState.rxTx.coexNoGrant = false;
            LRF_clearHwInterrupt(LRF_EventRfesoft1.value);
        }
        if (rclEventsIn.txBufferUpdate != 0U)
        {
            /* ACK payload handling */
            uint_fast8_t ackNumWords = ieeeHandlerState.rxTx.ackNumWords;
            if (ackNumWords != RCL_HANDLER_IEEE_ACK_LENGTH_IDLE)
            {
                if (ackNumWords == RCL_HANDLER_IEEE_ACK_LENGTH_ABORT)
                {
                    if (ieeeHandlerState.rxTx.txAckState == txAckStatePayloadExpected ||
                        ieeeHandlerState.rxTx.txAckState == txAckStatePayloadComplete)
                    {
                        /* Send stop of ACK to PBE */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_ENHACKSTOP;
                        /* Confirm */
                        ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckAborted;
                        ieeeHandlerState.rxTx.txAckState = txAckStateAckAborted;
                    }
                    else
                    {
                        ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckNotExpected;
                    }
                }
                else
                {
                    if (ieeeHandlerState.rxTx.txAckState == txAckStatePayloadExpected)
                    {
                        uint32_t ackNumRemainingWords = ieeeHandlerState.rxTx.ackNumRemainingWords;

                        if (ackNumRemainingWords == 0U && ieeeHandlerState.rxTx.ackData != NULL)
                        {
                            RCL_Buffer_DataEntry *ackEntry = (RCL_Buffer_DataEntry *)ieeeHandlerState.rxTx.ackData;
                            ackNumRemainingWords = RCL_Buffer_bytesToWords(RCL_Buffer_DataEntry_paddedLen(ackEntry->length));
                            if (ackNumRemainingWords > RCL_HANDLER_IEEE_ACK_LENGTH_MAX)
                            {
                                /* Set value that will cause error below */
                                ackNumRemainingWords = 0;
                            }
                        }

                        if (ackNumWords > ackNumRemainingWords || ieeeHandlerState.rxTx.ackData == NULL)
                        {
                            /* Too many words for FIFO or entry - probably an error in the packet structure */
                            ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckError;
                        }
                        else if (ackNumWords > LRF_getTxFifoWritable() / 4U)
                        {
                            /* Error TX FIFO issue - should not happen */
                            /* Send stop of ACK to PBE */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_ENHACKSTOP;
                            ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckAborted;
                            ieeeHandlerState.rxTx.txAckState = txAckStateAckAborted;
                        }
                        else
                        {
                            /* Copy data into FIFO */
                            LRF_writeTxFifoWords(ieeeHandlerState.rxTx.ackData, ackNumWords);
                            ackNumRemainingWords -= ackNumWords;
                            if (ackNumRemainingWords > 0U)
                            {
                                ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckPartial;
                            }
                            else
                            {
                                ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckOk;
                                ieeeHandlerState.rxTx.txAckState = txAckStatePayloadComplete;
                            }
                        }
                        ieeeHandlerState.rxTx.ackNumRemainingWords = (uint8_t) ackNumRemainingWords;
                    }
                    else
                    {
                        ieeeHandlerState.rxTx.ackResult = RCL_IEEE_AckNotExpected;
                    }
                }
                /* Signal that exchange is done */
                ieeeHandlerState.rxTx.ackNumWords = RCL_HANDLER_IEEE_ACK_LENGTH_IDLE;
            }
        }

        if (startTx)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            txAction->txStatus = RCL_CommandStatus_Active;
            bool proceedToRx = false;
            /* Set coex priority for TX */
            RCL_Handler_Ieee_setCoexPriority(true);

            /* Reset TXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_TXFIFO_RESET >> LRFDPBE_FCMD_DATA_S);

            if ((ieeeCmd->rxAction != NULL) && (txAction->expectImmAck || txAction->expectEnhAck ||
                ((txAction->endCmdWhenDone == 0U) &&
                    !(COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexPriorityChange))))
            {
                /* Set TX to proceed with RX */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                    (ieeeHandlerState.rxTx.frameFiltStop ? PBE_IEEE_RAM_OPCFG_STOP_HARDEND : PBE_IEEE_RAM_OPCFG_STOP_SOFTEND) |
                    PBE_IEEE_RAM_OPCFG_STOP_SOFTEND |
                    PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES |
                    PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES |
                    PBE_IEEE_RAM_OPCFG_TXINFINITE_NO |
                    PBE_IEEE_RAM_OPCFG_TXPATTERN_NO |
                    PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                    PBE_IEEE_RAM_OPCFG_START_SYNC |
                    PBE_IEEE_RAM_OPCFG_SINGLE_DIS |
                    PBE_IEEE_RAM_OPCFG_IFSPERIOD_EN;
                /* RX will be running when TX is done */
                proceedToRx = true;
            }
            else
            {
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                    PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES |
                    PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES |
                    PBE_IEEE_RAM_OPCFG_TXINFINITE_NO |
                    PBE_IEEE_RAM_OPCFG_TXPATTERN_NO |
                    PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                    PBE_IEEE_RAM_OPCFG_START_SYNC |
                    PBE_IEEE_RAM_OPCFG_SINGLE_EN |
                    PBE_IEEE_RAM_OPCFG_IFSPERIOD_DIS;
            }

            /* Enter payload */
            RCL_Buffer_DataEntry *txEntry = txAction->txEntry;
            if (txEntry == NULL)
            {
                txAction->txStatus = RCL_CommandStatus_Error_MissingTxBuffer;
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
            else
            {
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(txEntry->length) / 4U;

                if (wordLength > LRF_getTxFifoWritable() / 4U)
                {
                    /* Packet will not fit - probably an error in the packet structure */
                    txAction->txStatus = RCL_CommandStatus_Error_TxBufferCorruption;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else
                {
                    uint32_t *data32 = (uint32_t *) (txEntry);

                    /* Copy packet into FIFO */
                    LRF_writeTxFifoWords(data32, wordLength);

                    /* Enable interrupts */
                    LRF_Events interrupts = {.value = (LRF_EventOpDone.value | LRF_EventOpError.value)};

                    if (txAction->expectImmAck != 0U)
                    {
                        /* Find sequence number from transmitted frame */
                        uint8_t seqNo = 0;
                        uint32_t pos = txEntry->numPad - sizeof(txEntry->pad0) + IEEE_PHY_HDR_LEN + IEEE_MAC_FCF_LEN;
                        if (txEntry->length >= sizeof(txEntry->numPad) + sizeof(txEntry->pad0) + pos)
                        {
                            seqNo = txEntry->data[pos];
                        }

                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = txAction->ackTimeout;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                            ((uint16_t) (ieeeHandlerState.rxTx.alwaysStoreAck ?
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT :
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_FILTIMMACK) |
                            PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_EN |
                            (seqNo << PBE_IEEE_RAM_CFGAUTOACK_EXPSEQNM_S));
                        /* Get informed on ACK result */
                        interrupts.rxEmpty = 1;
                        ieeeHandlerState.rxTx.txState = txStateTxRxAck;
                        ieeeHandlerState.rxTx.expSeqNo = seqNo;
                        ieeeHandlerState.rxTx.immAckExpected = true;
                    }
                    else if (txAction->expectEnhAck != 0U)
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = txAction->ackTimeout;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                            (ieeeHandlerState.rxTx.alwaysStoreAck ?
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT :
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_FILTENHACK) |
                            PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_EN;
                        /* Get informed on ACK result */
                        interrupts.rxEmpty = 1;
                        ieeeHandlerState.rxTx.txState = txStateTxRxAck;
                        ieeeHandlerState.rxTx.immAckExpected = false;
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                            PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT | PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_DIS;

                        if ((ieeeCmd->rxAction != NULL) && (txAction->endCmdWhenDone == 0U) &&
                            !(COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexPriorityChange))
                        {
                            /* RX will go on, but TX action is finished at the end of TX */
                            interrupts.txDone = 1;
                            ieeeHandlerState.rxTx.txState = txStateTxRx;
                        }
                        else
                        {
                            ieeeHandlerState.rxTx.txState = txStateTx;
                        }
                        ieeeHandlerState.rxTx.immAckExpected = false;
                    }
                    /* Make sure temperature compensation is updated, except if command just started */
                    if (rclEventsIn.setup == 0U)
                    {
                        LRF_updateTemperatureCompensation(ieeeCmd->rfFrequency, true);
                        ieeeHandlerState.rxTx.temperatureRestart = false;
                    }
                    /* Clear and enable interrupts */
                    LRF_clearHwInterrupt(interrupts.value);
                    LRF_enableHwInterrupt(interrupts.value);

                    /* Store TX start time */
                    txAction->txTimeStamp = rclSchedulerState.actualStartTime;

                    /* Post cmd */
                    Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Ieee_RxTx: Starting IEEE TX");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_TX;
                    if (proceedToRx)
                    {
                        /* RX will be running when TX is done */
                        ieeeHandlerState.rxTx.rxState = rxStateWaitForStart;
                    }
                }
            }
        }

        if ((lrfEvents.rxOk != 0U || lrfEvents.rxNok != 0U || lrfEvents.rxIgnored != 0U) && ieeeCmd->rxAction != NULL)
        {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            if (rclFeatureControl.enablePaEsdProtection)
            {
                LRF_updatePaEsdProtection();
            }
#endif
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            uint32_t rxFifoReadable = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE);
            while (rxFifoReadable >= 4U)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFFU) / 4U;
                if (wordLength > 0U)
                {
                    RCL_MultiBuffer *curBuffer;
                    if (wordLength * 4U > rxFifoReadable)
                    {
                        /* Error */
                        curBuffer = NULL;
                    }
                    else
                    {
                        curBuffer = RCL_MultiBuffer_getBuffer(ieeeHandlerState.common.curBuffer,
                                                            wordLength * 4U);
                        if (curBuffer != ieeeHandlerState.common.curBuffer)
                        {
                            rclEvents.rxBufferFinished = 1;
                            ieeeHandlerState.common.curBuffer = curBuffer;
                        }
                    }
                    if (curBuffer == NULL)
                    {
                        /* Error */
                        ieeeHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        LRF_sendHardStop();
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *data32;
                        if ((ieeeHandlerState.rxTx.txAckState != txAckStatePending) && (ieeeHandlerState.rxTx.txAckState != txAckStateAckAborted))
                        {
                            ieeeHandlerState.rxTx.bytesReadFromFifo = (uint8_t) (wordLength * sizeof(uint32_t));
                            ieeeHandlerState.rxTx.savedRxfRp = HWREGH_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRP);
                        }
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        RCL_MultiBuffer_commitBytes(curBuffer, wordLength * 4U);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        RCL_Handler_Ieee_updateRxCurBufferAndFifo(&ieeeCmd->rxAction->rxBuffers);
                        if (ieeeHandlerState.rxTx.txState == txStateCheckAck)
                        {
                            if (lrfEvents.rxOk && wordLength >= 2U)
                            {
                                /* Read out sequence number; expect rest of the frame to be checked OK by PBE */
                                RCL_Buffer_DataEntry *entry = (RCL_Buffer_DataEntry *) data32;
                                uint8_t seqNo = entry->data[entry->numPad - sizeof(entry->pad0) + IEEE_PHY_HDR_LEN + IEEE_MAC_FCF_LEN];
                                if (seqNo == ieeeHandlerState.rxTx.expSeqNo)
                                {
                                    uint8_t framePending = (entry->data[entry->numPad - sizeof(entry->pad0) + IEEE_PHY_HDR_LEN] >> 4) & 1U;
                                    ieeeCmd->txAction->txStatus = (framePending != 0U) ? RCL_CommandStatus_FramePending : RCL_CommandStatus_Finished;
                                }
                                else
                                {
                                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_RxErr;
                                }
                            }
                            else
                            {
                                ieeeCmd->txAction->txStatus = RCL_CommandStatus_RxErr;
                            }
                            ieeeHandlerState.rxTx.txState = txStateFinished;
                        }
                    }
                }
                rxFifoReadable = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE);
                if ((lrfEvents.rxNok != 0U) || (ieeeHandlerState.rxTx.txAckState == txAckStateAckAborted))
                {
                    /* No ACK will go out in case of CRC error or if it has been aborted */
                    ieeeHandlerState.rxTx.txAckState = txAckStatePending;
                    /* Invalidate received frame from reading partial frame */
                    ieeeHandlerState.rxTx.bytesReadFromFifo = 0;
                }
            }
            if (ieeeHandlerState.common.activeUpdate)
            {
                RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if ((lrfEvents.txAck != 0U || lrfEvents.txCtrl != 0U) && ieeeCmd->rxAction != NULL)
        {
            /* ACK was sent or aborted */
            ieeeHandlerState.rxTx.txAckState = txAckStatePending;
            /* Invalidate received frame from reading partial frame */
            ieeeHandlerState.rxTx.bytesReadFromFifo = 0;
            /* Update counters */
            if (ieeeHandlerState.common.activeUpdate)
            {
                RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
            }
        }

        if ((ieeeHandlerState.rxTx.txState == txStateFinished) && (cmd->status == RCL_CommandStatus_Active))
        {
            rclEvents.cmdStepDone = 1;
            LRF_disableHwInterrupt(LRF_EventRfesoft0.value);

            if (ieeeCmd->txAction->endCmdWhenDone || ieeeCmd->rxAction == NULL)
            {
                if (ieeeHandlerState.rxTx.rxState != rxStateNoRx)
                {
                    /* Stop running RX and let it finish */
                    ieeeHandlerState.common.endStatus = ieeeCmd->txAction->txStatus;
                    Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Stop RX as command should end");
                    LRF_sendHardStop();
                    ieeeHandlerState.rxTx.txState = txStateWaitForCmdEnd;
                }
                else
                {
                    /* End now */
                    cmd->status = ieeeCmd->txAction->txStatus;
                    rclEvents.lastCmdDone = 1;
                    ieeeHandlerState.rxTx.txState = txStateNoTx;
                }
            }
            else
            {
                if (ieeeHandlerState.rxTx.rxState == rxStateNoRx)
                {
                    /* Restart RX */
                    restartRx = true;
                    Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Restarting RX as command should continue");
                }
                else if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration) && ieeeHandlerState.rxTx.coexPriorityChange)
                {
                    /* Send hard stop. Set flag to restart RX afterwards. */
                    LRF_sendHardStop();
                    ieeeHandlerState.rxTx.coexRestart = true;
                }
                else if (ieeeHandlerState.rxTx.rxActionUpdate || ieeeHandlerState.rxTx.temperatureRestart)
                {
                    /* Send graceful stop to make update happen; keep flag enabled */
                    LRF_sendGracefulStop();
                }
                else
                {
                    /* Rx is already active */
                    ieeeHandlerState.rxTx.rxState = rxStateRunning;
                }
                ieeeHandlerState.rxTx.txState = txStateNoTx;
            }
            if (ieeeHandlerState.common.activeUpdate)
            {
                RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
    }
    if (restartRx)
    {
        /* Re-enable radio to force a restart of the PBE */
        LRF_enable();
        /* Check if a parameter update is due */
        if (ieeeHandlerState.rxTx.rxActionUpdate)
        {
            ieeeHandlerState.rxTx.rxActionUpdate = false;
            RCL_CommandStatus status = RCL_Handler_Ieee_processRxAction(ieeeCmd->rxAction);
            if (status >= RCL_CommandStatus_Finished)
            {
                cmd->status = status;
                rclEvents.lastCmdDone = 1;
            }
            rclEvents.cmdUpdateDone = 1;
        }
        if (rclEvents.lastCmdDone == 0U)
        {
            RCL_CommandStatus status = RCL_Scheduler_setNewStartNow();
            if (status == RCL_CommandStatus_Active)
            {
                /* Set up for RX */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                    (ieeeHandlerState.rxTx.frameFiltStop ? PBE_IEEE_RAM_OPCFG_STOP_HARDEND : PBE_IEEE_RAM_OPCFG_STOP_SOFTEND) |
                    PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES |
                    PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES |
                    PBE_IEEE_RAM_OPCFG_TXINFINITE_NO |
                    PBE_IEEE_RAM_OPCFG_TXPATTERN_NO |
                    PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                    PBE_IEEE_RAM_OPCFG_START_SYNC |
                    PBE_IEEE_RAM_OPCFG_SINGLE_DIS |
                    PBE_IEEE_RAM_OPCFG_IFSPERIOD_EN;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                    PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT | PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_DIS;
                /* Reset RXFIFO and TXFIFO. NOTE: Only allowed while PBE is not running, ref. RCL-367 */
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = (LRFDPBE_FCMD_DATA_FIFO_RESET >> LRFDPBE_FCMD_DATA_S);
                /* Make sure temperature compensation is updated */
                LRF_updateTemperatureCompensation(ieeeCmd->rfFrequency, false);
                ieeeHandlerState.rxTx.temperatureRestart = false;
                /* Turn off priority change */
                ieeeHandlerState.rxTx.coexPriorityChange = false;
                ieeeHandlerState.rxTx.coexRestart = false;
                /* Set coex priority for RX */
                RCL_Handler_Ieee_setCoexPriority(false);
                /* Post cmd */
                Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: Restarting IEEE RX. lastCmdDone = %1d", rclEvents.lastCmdDone);
                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_RX;
                /* Clear RSSI valid interrupt flag */
                LRF_clearHwInterrupt(LRF_EventRfesoft0.value);
                ieeeHandlerState.rxTx.rxState = rxStateWaitForStart;
            }
            else
            {
                cmd->status = status;
                rclEvents.lastCmdDone = 1;
            }
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        /* Check if TX action has finished */
        if (ieeeHandlerState.rxTx.txState != txStateNoTx)
        {
            Log_printf(LogModule_RCL, Log_VERBOSE, "RCL_Handler_Ieee_RxTx: TX action ending because command ended");
            if ((ieeeCmd->txAction != NULL) && (ieeeCmd->txAction->txStatus < RCL_CommandStatus_Finished))
            {
                /* End status not set - use command end status to show it ended with command */
                ieeeCmd->txAction->txStatus = cmd->status;
            }
            rclEvents.cmdStepDone = 1;
        }
        /* Check if command update is pending - if so, signal it as done */
        if (ieeeHandlerState.rxTx.rxActionUpdate)
        {
            rclEvents.cmdUpdateDone = 1;
        }
        /* Restore changed thresholds */
        if (ieeeHandlerState.rxTx.restoreThresh)
        {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE10) = ieeeHandlerState.rxTx.demc1be10;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = ieeeHandlerState.rxTx.demc1be12;
#else
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = ieeeHandlerState.rxTx.demc1be1;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = ieeeHandlerState.rxTx.demc1be2;
#endif
        }
        LRF_disable();
        LRF_disableSynthRefsys();
        LRF_disableTemperatureMonitoring();
        LRF_disableCoexGrant();
        if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration))
        {
            LRF_deassertCoexRequest();
        }
        LRF_disableHwInterrupt(LRF_EventRfesoft1.value);
        /* Allow SWTCXO again */
        RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
        RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Ieee_TxTest ========
 */
RCL_Events RCL_Handler_Ieee_TxTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdIeeeTxTest *txCmd = (RCL_CmdIeeeTxTest *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
        /* Make sure SWTCXO does not adjust clock while radio is running */
        RCL_Hal_powerSetSwTcxoUpdateConstraint();
        ieeeHandlerState.txTest.restoreOpt = RCL_HANDLER_IEEE_RESTORE_NONE;
        ieeeHandlerState.common.apiHardStopPending = false;
        if ((txCmd->rfFrequency == 0U) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001U) == 0U))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                PBE_IEEE_RAM_OPCFG_RXREPEATOK_NO |
                PBE_IEEE_RAM_OPCFG_RXREPEATNOK_NO |
                PBE_IEEE_RAM_OPCFG_TXINFINITE_YES |
                PBE_IEEE_RAM_OPCFG_TXPATTERN_YES |
                PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                PBE_IEEE_RAM_OPCFG_START_SYNC |
                PBE_IEEE_RAM_OPCFG_SINGLE_EN |
                PBE_IEEE_RAM_OPCFG_IFSPERIOD_DIS;

            /* Turn off Coex */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG) = 0;

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* End status not determined */
            ieeeHandlerState.common.endStatus = RCL_CommandStatus_Active;

            if (LRF_programTxPower(txCmd->txPower, txCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enter configuration */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_PATTERN) = txCmd->txWord;
            if (txCmd->config.sendCw != 0U)
            {
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) | LRFDMDM_MODCTRL_TONEINSERT_M;
                ieeeHandlerState.txTest.restoreOpt = RCL_HANDLER_IEEE_RESTORE_MODCTRL;
            }
            else
            {
                uint32_t whitenMode = txCmd->config.whitenMode;
                /* Configure whitening */
                if (whitenMode != RCL_CMD_IEEE_WH_MODE_OFF)
                {
                    ieeeHandlerState.txTest.restoreOpt = RCL_HANDLER_IEEE_RESTORE_WHITENING;
                    ieeeHandlerState.txTest.storedWhitenPoly = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0);
                    ieeeHandlerState.txTest.storedWhitenInit = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_WHITEINIT);
                    uint32_t whitenPoly;
                    switch (whitenMode)
                    {
                        case RCL_CMD_IEEE_WH_MODE_PRBS9:
                        default:
                            whitenPoly = RCL_HANDLER_IEEE_PRBS9_POLY;
                            break;
                        case RCL_CMD_IEEE_WH_MODE_PRBS15:
                            whitenPoly = RCL_HANDLER_IEEE_PRBS15_POLY;
                            break;
                        case RCL_CMD_IEEE_WH_MODE_PRBS32:
                            whitenPoly = RCL_HANDLER_IEEE_PRBS32_POLY;
                            break;
                    }
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = whitenPoly;
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_WHITEINIT) = RCL_HANDLER_IEEE_PRBS_INIT;
                }

                ieeeHandlerState.txTest.restoreOpt |= RCL_HANDLER_IEEE_RESTORE_SFD;
                ieeeHandlerState.txTest.storedMdmSyncA = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA);
                /* Set non-standard SFD */
                HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ieeeHandlerState.txTest.storedMdmSyncA ^ 0x00FFU;
            }
            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Program frequency word */
                LRF_programFrequency(txCmd->rfFrequency, true);

                /* Enable interrupts */
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                /* Post cmd */
                Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Ieee_TxTest: Starting infinite TX");

                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_TX;
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0U)
        {
            RCL_CommandStatus endStatus = ieeeHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Active)
            {
                cmd->status = RCL_CommandStatus_Finished;
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = ieeeHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Active)
            {
                cmd->status = RCL_Handler_Ieee_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
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

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
        /* Allow SWTCXO again */
        RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_MODCTRL) != 0U)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) & (~LRFDMDM_MODCTRL_TONEINSERT_M);
        }
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_WHITENING) != 0U)
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = ieeeHandlerState.txTest.storedWhitenPoly;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_WHITEINIT) = ieeeHandlerState.txTest.storedWhitenInit;
        }
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_SFD) != 0U)
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ieeeHandlerState.txTest.storedMdmSyncA;
        }
    }

    return rclEvents;
}

/*
 *  ======== RCL_IEEE_Tx_submit ========
 */
RCL_CommandStatus RCL_IEEE_Tx_submit(RCL_CmdIeeeRxTx *cmd, RCL_CmdIeee_TxAction *txAction)
{
    RCL_CommandStatus status = RCL_CommandStatus_Idle;
    /* Can't submit action again if already submitted */
    if ((txAction->txStatus != RCL_CommandStatus_Idle) && (txAction->txStatus < RCL_CommandStatus_Finished))
    {
        return RCL_CommandStatus_Error_AlreadySubmitted;
    }

    uintptr_t key = HwiP_disable();
    /* Check if command is finished */
    if ((cmd == NULL) || (cmd->common.status >= RCL_CommandStatus_Finished))
    {
        /* TODO: New status */
        Log_printf(LogModule_RCL, Log_ERROR, "RCL_IEEE_Tx_submit: Command ended before TX action was submitted");
        status = RCL_CommandStatus_Error;
    }
    else if ((cmd->txAction != NULL) && (cmd->txAction->txStatus != RCL_CommandStatus_Idle) && (cmd->txAction->txStatus < RCL_CommandStatus_Finished))
    {
        /* Another TX action is already running */
        status = RCL_CommandStatus_Error_AlreadySubmitted;
    }
    /* Extra check in case user modified status field */
    else if ((rclSchedulerState.currCmd == &cmd->common) && (ieeeHandlerState.rxTx.txState != txStateNoTx))
    {
        status = RCL_CommandStatus_Error_AlreadySubmitted;
    }
    else
    {
        /* Nothing to do */
    }

    if (status != RCL_CommandStatus_Idle)
    {
        HwiP_restore(key);

        return status;
    }
    else
    {
        /* Insert TX action */
        txAction->txStatus = RCL_CommandStatus_Idle;
        cmd->txAction = txAction;

        if (rclSchedulerState.currCmd == &cmd->common)
        {
            /* Trigger handler */
            ieeeHandlerState.rxTx.txState = txStateNewAction;
            (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
        }
        HwiP_restore(key);

        return txAction->txStatus;
    }
}

/*
 *  ======== RCL_IEEE_Tx_stop ========
 */
RCL_CommandStatus RCL_IEEE_Tx_stop(RCL_CmdIeeeRxTx *cmd, RCL_StopType stopType)
{
    if (cmd == NULL)
    {
        return RCL_CommandStatus_Error_Param;
    }
    uintptr_t key = HwiP_disable();
    RCL_CmdIeee_TxAction *txAction = cmd->txAction;
    if (txAction == NULL)
    {
        /* No TX action at all */
        HwiP_restore(key);
        return RCL_CommandStatus_Error_Param;
    }
    /* Check command state */
    else if (cmd->common.status < RCL_CommandStatus_Active)
    {
        /* TX action can be descheduled without any other action */
        txAction->txStatus = RCL_CommandStatus_DescheduledApi;
        /* In this case, we have to set the TX action to NULL to avoid it starting */
        cmd->txAction = NULL;
    }
    else if (cmd->common.status < RCL_CommandStatus_Finished)
    {
        /* Inform handler about stop */
        ieeeHandlerState.rxTx.txActionStop = stopType;
        (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
    }
    else
    {
        /* Command finished; nothing to do about TX action */
    }
    HwiP_restore(key);

    return txAction->txStatus;
}

/*
 *  ======== RCL_IEEE_enterAck ========
 */
RCL_IEEE_AckEntryResult RCL_IEEE_enterAck(RCL_CmdIeeeRxTx *cmd, uint32_t *ackData, uint8_t numWords)
{

    if (numWords == RCL_HANDLER_IEEE_ACK_LENGTH_ABORT || ackData == NULL || cmd == NULL)
    {
        return RCL_IEEE_AckError;
    }
    else
    {
        uint32_t actualNumWords = numWords;
        if (numWords == 0U)
        {
            actualNumWords = RCL_Buffer_bytesToWords(RCL_Buffer_DataEntry_paddedLen(((RCL_Buffer_DataEntry *)ackData)->length));
        }
        if (actualNumWords > RCL_HANDLER_IEEE_ACK_LENGTH_MAX)
        {
            return RCL_IEEE_AckError;
        }
        else
        {
            return RCL_Handler_Ieee_txAckUpdate(cmd, (uint32_t *)ackData, (uint8_t) actualNumWords);
        }
    }
}

/*
 *  ======== RCL_IEEE_cancelAck ========
 */
RCL_IEEE_AckEntryResult RCL_IEEE_cancelAck(RCL_CmdIeeeRxTx *cmd)
{
    if (cmd == NULL)
    {
        return RCL_IEEE_AckError;
    }
    else
    {
        return RCL_Handler_Ieee_txAckUpdate(cmd, NULL, RCL_HANDLER_IEEE_ACK_LENGTH_ABORT);
    }
}

/*
 *  ======== RCL_IEEE_readPartialFrame ========
 */
size_t RCL_IEEE_readPartialFrame(RCL_CmdIeeeRxTx *cmd, RCL_Buffer_DataEntry *dataEntry, size_t entrySize)
{
    /* Default to no data available */
    size_t numBytesAvailable = 0;
    if (cmd != NULL && cmd->common.status == RCL_CommandStatus_Active &&
        dataEntry != NULL && entrySize >= offsetof(RCL_Buffer_DataEntry, data))
    {
        uint32_t rp;
        uintptr_t key = HwiP_disable();
        numBytesAvailable = ieeeHandlerState.rxTx.bytesReadFromFifo;
        if (numBytesAvailable == 0U)
        {
            numBytesAvailable = LRF_getUncommittedFifoStatus(&rp);
        }
        else
        {
            rp = ieeeHandlerState.rxTx.savedRxfRp;
        }

        /* Round number of words up - unintialized bytes may be read, but will not be shown as available */
        uint32_t numWords = (numBytesAvailable + 3U) >> 2;
        /* Make sure that everything fits in the entry, and do not use non-word part of entry */
        if ((numWords << 2) > entrySize)
        {
            numWords = entrySize >> 2;
            numBytesAvailable = numWords << 2;
        }

        if (numBytesAvailable >= sizeof(dataEntry->length))
        {
            LRF_peekRxFifoWords((uint32_t *)dataEntry, numWords, rp);
            /* Write actual number of available bytes in length field */
            dataEntry->length = (uint16_t) (numBytesAvailable - sizeof(dataEntry->length));
        }
        HwiP_restore(key);
    }
    return numBytesAvailable;
}

/*
 *  ======== RCL_IEEE_updateRxAction ========
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateRxAction(RCL_CmdIeeeRxTx *cmd)
{
    if (cmd == NULL || cmd->common.cmdId != RCL_CMDID_IEEE_RX_TX)
    {
        return RCL_IEEE_UpdateCmdError;
    }

    RCL_IEEE_UpdateResult result;
    uintptr_t key = HwiP_disable();
    if (cmd->rxAction == NULL)
    {
        /* Error: Command has no RX */
        result = RCL_IEEE_UpdateCmdError;
    }
    else if (cmd->common.status != RCL_CommandStatus_Active)
    {
        /* Command is not running, so no need to wait */
        result = RCL_IEEE_UpdateDone;
    }
    else if (ieeeHandlerState.rxTx.rxActionUpdate || ieeeHandlerState.rxTx.srcMatchUpdatePhase != noSrcMatchUpdate)
    {
        /* Update is already running */
        result = RCL_IEEE_UpdateCmdError;
    }
    else
    {
        /* Inform handler */
        ieeeHandlerState.rxTx.rxActionUpdate = true;
        (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
        /* Report success */
        result = RCL_IEEE_UpdatePending;
    }
    HwiP_restore(key);
    return result;
}

/*
 *  ======== RCL_IEEE_updateSourceMatchingTableShort ========
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableShort(RCL_CmdIeeeRxTx *cmd, RCL_IEEE_SourceMatchingUpdate description,
                                                              RCL_CmdIeee_PanIdAddr newPanIdAddr)
{
    if (cmd == NULL || cmd->common.cmdId != RCL_CMDID_IEEE_RX_TX)
    {
        return RCL_IEEE_UpdateCmdError;
    }

    RCL_IEEE_UpdateResult result;
    uintptr_t key = HwiP_disable();
    if (cmd->rxAction == NULL)
    {
        /* Error: Command has no RX */
        result = RCL_IEEE_UpdateCmdError;
    }
    else if (description.panNo >= cmd->rxAction->numPan)
    {
        /* Error: PAN number is out of range */
        result = RCL_IEEE_UpdateIndexError;
    }
    else
    {
        /* Check that table and index is valid */
        RCL_CmdIeee_SourceMatchingTableShort *table = cmd->rxAction->panConfig[description.panNo].sourceMatchingTableShort;
        if (table == NULL || description.index >= table->numEntries)
        {
            result = RCL_IEEE_UpdateIndexError;
        }
        else if (cmd->common.status != RCL_CommandStatus_Active)
        {
            /* Command is not running, so no need to wait */
            result = RCL_Handler_Ieee_processSourceMatchingOperation(description, table->entryEnable, table->framePending);
            if (result == RCL_IEEE_UpdatePending)
            {
                /* Update address */
                table->shortEntry[description.index] = newPanIdAddr;
                /* Update is done; indicate in result */
                result = RCL_IEEE_UpdateDone;
            }
        }
        else if (ieeeHandlerState.rxTx.rxActionUpdate || ieeeHandlerState.rxTx.srcMatchUpdatePhase != noSrcMatchUpdate)
        {
            /* Update is already running */
            result = RCL_IEEE_UpdateCmdError;
        }
        else
        {
            /* Inform handler */
            ieeeHandlerState.rxTx.srcMatchUpdateDesc = description;
            ieeeHandlerState.rxTx.newSrcMatch.newPanIdAddr = newPanIdAddr;
            ieeeHandlerState.rxTx.srcMatchUpdatePhase = srcMatchUpdateStart;
            ieeeHandlerState.rxTx.srcMatchUpdateFun = RCL_Handler_Ieee_updateSrcMatchTableShort;
            (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
            /* Report success */
            result = RCL_IEEE_UpdatePending;
        }
    }
    HwiP_restore(key);
    return result;
}

/*
 *  ======== RCL_IEEE_updateSourceMatchingTableExt ========
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateSourceMatchingTableExt(RCL_CmdIeeeRxTx *cmd, RCL_IEEE_SourceMatchingUpdate description,
                                                            const uint64_t *newAddr)
{
    if (cmd == NULL || cmd->common.cmdId != RCL_CMDID_IEEE_RX_TX)
    {
        return RCL_IEEE_UpdateCmdError;
    }

    RCL_IEEE_UpdateResult result;
    uintptr_t key = HwiP_disable();
    if (cmd->rxAction == NULL)
    {
        /* Error: Command has no RX */
        result = RCL_IEEE_UpdateCmdError;
    }
    else if (description.panNo >= cmd->rxAction->numPan)
    {
        /* Error: PAN number is out of range */
        result = RCL_IEEE_UpdateIndexError;
    }
    else
    {
        /* Check that table and index is valid */
        RCL_CmdIeee_SourceMatchingTableExt *table = cmd->rxAction->panConfig[description.panNo].sourceMatchingTableExt;
        if (table == NULL || description.index >= table->numEntries)
        {
            result = RCL_IEEE_UpdateIndexError;
        }
        else if (cmd->common.status != RCL_CommandStatus_Active)
        {
            /* Command is not running, so no need to wait */
            result = RCL_Handler_Ieee_processSourceMatchingOperation(description, table->entryEnable, table->framePending);
            if (result == RCL_IEEE_UpdatePending)
            {
                /* Update address */
                table->extEntry[description.index] = *newAddr;
                /* Update is done; indicate in result */
                result = RCL_IEEE_UpdateDone;
            }
        }
        else if (ieeeHandlerState.rxTx.rxActionUpdate || ieeeHandlerState.rxTx.srcMatchUpdatePhase != noSrcMatchUpdate)
        {
            /* Update is already running */
            result = RCL_IEEE_UpdateCmdError;
        }
        else
        {
            /* Inform handler */
            ieeeHandlerState.rxTx.srcMatchUpdateDesc = description;
            ieeeHandlerState.rxTx.newSrcMatch.newExtAddr = *newAddr;
            ieeeHandlerState.rxTx.srcMatchUpdatePhase = srcMatchUpdateStart;
            ieeeHandlerState.rxTx.srcMatchUpdateFun = RCL_Handler_Ieee_updateSrcMatchTableExt;
            (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
            /* Report success */
            result = RCL_IEEE_UpdatePending;
        }
    }
    HwiP_restore(key);
    return result;
}

/*
 *  ======== RCL_IEEE_updateTxPower ========
 */
RCL_IEEE_UpdateResult RCL_IEEE_updateTxPower(RCL_CmdIeeeRxTx *cmd, RCL_Command_TxPower newTxPower)
{
    if (cmd == NULL || cmd->common.cmdId != RCL_CMDID_IEEE_RX_TX)
    {
        return RCL_IEEE_UpdateCmdError;
    }

    /* Not allowed to update to no TX power programming */
    if (newTxPower.rawValue == LRF_TxPower_None.rawValue)
    {
        return RCL_IEEE_UpdateParamError;
    }

    RCL_IEEE_UpdateResult result;
    uintptr_t key = HwiP_disable();
    if (cmd->common.status == RCL_CommandStatus_Active)
    {
        /* Update current TX power value */
        if (LRF_programTxPower(newTxPower, cmd->rfFrequency) != TxPowerResult_Ok)
        {
            /* Update failed */
            result = RCL_IEEE_UpdateParamError;
        }
        else
        {
            /* Update was successful - update command structure */
            cmd->txPower = newTxPower;
            result = RCL_IEEE_UpdateDone;
        }
    }
    else
    {
        /* Command not running - update TX power */
        /* Note: value check will be done when command is parsed, so an invalid value will cause
           command to end with error and not be detected here */
        cmd->txPower = newTxPower;
        result = RCL_IEEE_UpdateDone;
    }
    HwiP_restore(key);

    return result;
}

/*
 *  ======== RCL_Handler_Ieee_processRxAction ========
 */
static RCL_CommandStatus RCL_Handler_Ieee_processRxAction(const RCL_CmdIeee_RxAction *rxAction)
{
    bool providedAckFrameEnabled = false;

    uint8_t numPan = rxAction->numPan;
    ieeeHandlerState.rxTx.numPan = numPan;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_PIB) = numPan;

    /* Turn off sync search if requested */
    if (rxAction->disableSync && !ieeeHandlerState.rxTx.restoreThresh)
    {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        uint16_t demc1be10 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE10);
        uint16_t demc1be12 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12);

        ieeeHandlerState.rxTx.restoreThresh = true;
        ieeeHandlerState.rxTx.demc1be10 = demc1be10;
        ieeeHandlerState.rxTx.demc1be12 = demc1be12;

        /* Set threshold G to maximum to disable sync search, and mask out correlator D and E */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE10) = LRFDMDM_DEMC1BE10_MASKE_M | LRFDMDM_DEMC1BE10_MASKD_M;
        demc1be12 = (uint16_t) ((demc1be12 & ~LRFDMDM_DEMC1BE12_THRESHOLDG_M) | (IEEE_THRESHOLD_NO_SYNC << LRFDMDM_DEMC1BE12_THRESHOLDG_S));
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = demc1be12;
#else
        uint16_t demc1be1 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1);
        uint16_t demc1be2 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2);

        ieeeHandlerState.rxTx.restoreThresh = true;
        ieeeHandlerState.rxTx.demc1be1 = demc1be1;
        ieeeHandlerState.rxTx.demc1be2 = demc1be2;

        /* Set threshold A and C (shadow) to maximum to disable sync search. Leave threshold B unchanged to get correlation tops for CCA */
        demc1be1 = (uint16_t) ((demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDA_M) | (IEEE_THRESHOLD_NO_SYNC << LRFDMDM_DEMC1BE1_THRESHOLDA_S));
        demc1be2 = (uint16_t) ((demc1be2 & ~LRFDMDM_DEMC1BE2_THRESHOLDC_M) | (IEEE_THRESHOLD_NO_SYNC << LRFDMDM_DEMC1BE2_THRESHOLDC_S));
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = demc1be1;
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = demc1be2;
#endif
    }
    /* Restore correlation threshold if sync is re-enabled */
    if (!rxAction->disableSync && ieeeHandlerState.rxTx.restoreThresh)
    {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE10) = ieeeHandlerState.rxTx.demc1be10;
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = ieeeHandlerState.rxTx.demc1be12;
#else
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = ieeeHandlerState.rxTx.demc1be1;
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = ieeeHandlerState.rxTx.demc1be2;
#endif
    }

    uint32_t panRegOffset = 0;
    uint32_t sourceMatchHeaderOffset = 0;
    uint32_t sourceMatchTableOffset = 0;
    for (uint8_t i = 0; i < numPan; i++)
    {
        /* Write PAN configuration to bufram for use by the PBE */
        const RCL_CmdIeee_PanConfig *panConfig = &rxAction->panConfig[i];
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_PANID0) = panConfig->localPanId;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_SHORTADDR0) = panConfig->localShortAddr;
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_EXTADDR00) = (uint32_t) panConfig->localExtAddr;
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_EXTADDR02) = (uint32_t) (panConfig->localExtAddr >> 32);
        uint32_t frameFilteringOption =
            (panConfig->maxFrameVersion << PBE_IEEE_RAM_FFOPT0_MAXFRAME_S) |
            (panConfig->panCoord << PBE_IEEE_RAM_FFOPT0_PANCOORD_S) |
            (panConfig->defaultPend << PBE_IEEE_RAM_FFOPT0_DEFPEND_S);

        switch (panConfig->autoAckMode)
        {
            case RCL_CmdIeee_AutoAck_Off:
            default:
                frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_DISABLE |
                    PBE_IEEE_RAM_FFOPT0_AUTOPEND_DISABLE |
                    PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY |
                    PBE_IEEE_RAM_FFOPT0_IMMACKSEL_PBE;
                break;

            case RCL_CmdIeee_AutoAck_ImmAckNoAutoPend:
                frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                    PBE_IEEE_RAM_FFOPT0_AUTOPEND_DISABLE |
                    PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY |
                    PBE_IEEE_RAM_FFOPT0_IMMACKSEL_PBE;
                break;

            case RCL_CmdIeee_AutoAck_ImmAckAutoPendAll:
                frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                    PBE_IEEE_RAM_FFOPT0_AUTOPEND_EN |
                    PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY |
                    PBE_IEEE_RAM_FFOPT0_IMMACKSEL_PBE;
                break;

            case RCL_CmdIeee_AutoAck_ImmAckAutoPendDataReq:
                frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                    PBE_IEEE_RAM_FFOPT0_AUTOPEND_EN |
                    PBE_IEEE_RAM_FFOPT0_PREQONLY_DATAREQ |
                    PBE_IEEE_RAM_FFOPT0_IMMACKSEL_PBE;
                break;

            case RCL_CmdIeee_AutoAck_ImmAckProvidedFrame:
                frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                    PBE_IEEE_RAM_FFOPT0_IMMACKSEL_MCU;
                providedAckFrameEnabled = true;
                break;
        }
        if (panConfig->autoAckMode != RCL_CmdIeee_AutoAck_Off && panConfig->maxFrameVersion >= 2U)
        {
            providedAckFrameEnabled = true;
        }

        /* Set up source matching */
        uint32_t maxNumShortEntries;
        uint32_t numExtEntries = 0;
        if (panConfig->sourceMatchingTableExt != NULL)
        {
            RCL_CmdIeee_SourceMatchingTableExt *sourceMatchingTable = panConfig->sourceMatchingTableExt;
            numExtEntries = sourceMatchingTable->numEntries;
            if (numExtEntries > RCL_CMD_IEEE_SOURCE_MATCH_TABLE_EXT_MAX_LEN)
            {
                return RCL_CommandStatus_Error_Param;
            }

            if (numExtEntries > 0U)
            {
                /* Write source matching table to bufram for use by the PBE */
                /* Write entry enable and frame pending bits for the entries given to bufram */
                /* If the table has fewer entries than the maximum, set the corresponding bits to 0 */
                uint16_t mask = 0xFFFFU;
                mask >>= (16U - numExtEntries);
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE02) =
                    sourceMatchingTable->entryEnable[0] & mask;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_FRAMEPENDING02) =
                    sourceMatchingTable->framePending[0] & mask;

                /* Set remaining enable and frame pending words to 0 */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE03) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_FRAMEPENDING03) = 0;
                /* Write entries to bufram */
                for (uint32_t entryNo = 0; entryNo < numExtEntries; entryNo++)
                {
                    HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchTableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_EXT_START + (entryNo << 3)) =
                        (uint32_t) sourceMatchingTable->extEntry[entryNo];
                    HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchTableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_EXT_START + (entryNo << 3) + 4U) =
                        (uint32_t) (sourceMatchingTable->extEntry[entryNo] >> 32ULL);
                }
            }
        }

        if (numExtEntries == 0U)
        {
            frameFilteringOption = (frameFilteringOption & ~PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_M) | PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_SHORTONLY;
            maxNumShortEntries = RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_MAX_LEN;
        }
        else
        {
            frameFilteringOption = (frameFilteringOption & ~PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_M) | PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_MIX;
            maxNumShortEntries = RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_WITH_EXT_MAX_LEN;
        }

        if (panConfig->sourceMatchingTableShort != NULL)
        {
            /* Write source matching table to bufram for use by the PBE */
            RCL_CmdIeee_SourceMatchingTableShort *sourceMatchingTable = panConfig->sourceMatchingTableShort;
            uint32_t numEntries = sourceMatchingTable->numEntries;
            if (numEntries > maxNumShortEntries)
            {
                return RCL_CommandStatus_Error_Param;
            }
            uint32_t entryNo = 0;
            uint32_t index = 0;
            while (entryNo < numEntries)
            {
                /* Write entry enable and frame pending bits for the entries given to bufram */
                /* If the table has fewer entries than the maximum, set the corresponding bits to 0 */
                uint16_t mask = 0xFFFFU;
                if ((numEntries - entryNo) < 16U)
                {
                    mask >>= (16U - (numEntries - entryNo));
                }
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE00 + (index << 1)) =
                    sourceMatchingTable->entryEnable[index] & mask;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_FRAMEPENDING00 + (index << 1)) =
                    sourceMatchingTable->framePending[index] & mask;
                index++;
                entryNo += 16U;
            }
            /* Set remaining enable and frame pending words to 0 (if any) */
            while (entryNo < maxNumShortEntries)
            {
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE00 + (index << 1)) = 0;
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_FRAMEPENDING00 + (index << 1)) = 0;
                index++;
                entryNo += 16U;
            }
            /* Write entries (Pan ID and address) to bufram */
            for (entryNo = 0; entryNo < numEntries; entryNo++)
            {
                HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchTableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START + (entryNo << 2)) =
                    sourceMatchingTable->shortEntry[entryNo].combined;
            }
        }
        else
        {
            uint32_t index = 0;
            /* If no table is provided, set all entry enble words to 0 */
            for (uint32_t entryNo = 0U; entryNo < maxNumShortEntries; entryNo += 16U)
            {
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE00 + (index << 1)) = 0;
                index++;
            }
        }
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_FFOPT0) = (uint16_t) frameFilteringOption;

        panRegOffset += PBE_IEEE_RAM_O_PANID1 - PBE_IEEE_RAM_O_PANID0;
        sourceMatchHeaderOffset += PBE_IEEE_RAM_O_ENTRYENABLE10 - PBE_IEEE_RAM_O_ENTRYENABLE00;
        sourceMatchTableOffset += PBE_IEEE_RAM_O_PAN1_SRC_MATCH_SHORT_START - PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START;
    }
    uint16_t ffType =
        PBE_IEEE_RAM_FFTYPE_MACCMD1_M |
        PBE_IEEE_RAM_FFTYPE_DATA1_M |
        PBE_IEEE_RAM_FFTYPE_BEACON1_M |
        PBE_IEEE_RAM_FFTYPE_MACCMD0_M |
        PBE_IEEE_RAM_FFTYPE_DATA0_M |
        PBE_IEEE_RAM_FFTYPE_BEACON0_M;
    ieeeHandlerState.rxTx.alwaysStoreAck = rxAction->alwaysStoreAck;
    if (ieeeHandlerState.rxTx.alwaysStoreAck)
    {
        ffType |= PBE_IEEE_RAM_FFTYPE_ACK1_M | PBE_IEEE_RAM_FFTYPE_ACK0_M;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FFTYPE) = ffType;
    ieeeHandlerState.rxTx.frameFiltStop = rxAction->frameFiltStop;

    /* Make sure any optional interrupts are disabled */
    LRF_disableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value |
                            LRF_EventRxOk.value | LRF_EventRxNok.value |
                            LRF_EventRxIgnored.value | LRF_EventRxBufFull.value |
                            LRF_EventTxAck.value | LRF_EventRxCtrlAck.value | LRF_EventTxCtrl.value);
    /* Enable interrupts */
    uint32_t lrfEvents = RCL_Handler_Ieee_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                LRF_EventRxIgnored.value | LRF_EventRxBufFull.value |
                                                                LRF_EventTxAck.value,
                                                                ieeeHandlerState.rxTx.fifoCfg,
                                                                ieeeHandlerState.common.activeUpdate);
    /* If ACKs will be provided, some more interrupts are always needed */
    if (providedAckFrameEnabled)
    {
        lrfEvents |= LRF_EventRxCtrlAck.value | LRF_EventTxAck.value | LRF_EventRxNok.value | LRF_EventTxCtrl.value;
    }
    LRF_enableHwInterrupt(lrfEvents);

    return RCL_CommandStatus_Active;
}

/*
 *  ======== RCL_Handler_Ieee_txAckUpdate ========
 */
static RCL_IEEE_AckEntryResult RCL_Handler_Ieee_txAckUpdate(RCL_CmdIeeeRxTx *cmd, uint32_t *ackData, uint8_t numWords)
{
    RCL_IEEE_AckEntryResult result;

    uintptr_t key = HwiP_disable();

    if (cmd->common.status != RCL_CommandStatus_Active)
    {
        result = RCL_IEEE_AckNotExpected;
        HwiP_restore(key);
    }
    else
    {
        /* Enter ACK into handler state */
        ieeeHandlerState.rxTx.ackData = ackData;
        ieeeHandlerState.rxTx.ackNumWords = numWords;
        /* Inform handler */
        (void) RCL_Scheduler_postEvent(&cmd->common, RCL_EventTxBufferUpdate);
        /* Allow handler to run */
        HwiP_restore(key);
        /* Check that handler finished (should be instant due to interrupt prority) */
        if (ieeeHandlerState.rxTx.ackNumWords == RCL_HANDLER_IEEE_ACK_LENGTH_IDLE)
        {
            result = ieeeHandlerState.rxTx.ackResult;
        }
        else
        {
            /* Ack not processed (because function was called with interrupts disabled or at a higher priority than cmd handler) */
            result = RCL_IEEE_AckNotProcessed;
        }
    }
    return result;
}

/*
 *  ======== RCL_Handler_Ieee_updateRxCurBufferAndFifo ========
 */
static void RCL_Handler_Ieee_updateRxCurBufferAndFifo(List_List *rxBuffers)
{
    RCL_MultiBuffer *curBuffer = ieeeHandlerState.common.curBuffer;

    if (curBuffer == NULL)
    {
        curBuffer = RCL_MultiBuffer_findFirstWritableBuffer((RCL_MultiBuffer *)rxBuffers->head);
    }
    ieeeHandlerState.common.curBuffer = curBuffer;

    uint32_t rxSpace = RCL_MultiBuffer_findAvailableRxSpace(curBuffer);

    LRF_setRxFifoEffSz(rxSpace);
}

/*
 *  ======== RCL_Handler_Ieee_findPbeErrorEndStatus ========
 */
static RCL_CommandStatus RCL_Handler_Ieee_findPbeErrorEndStatus(uint16_t pbeEndStatus)
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
        status = RCL_CommandStatus_Error_Synth;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_RXTIMEOUT:
        status = RCL_CommandStatus_RxTimeout;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP:
        if (ieeeHandlerState.common.apiHardStopPending)
        {
            status = RCL_CommandStatus_HardStopApi;
        }
        else
        {
            status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        }
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP:
        status = RCL_CommandStatus_Error_UnknownOp;
        break;
    default:
        Log_printf(LogModule_RCL, Log_ERROR, "RCL_Handler_Ieee_findPbeErrorEndStatus: Unexpected error 0x%04X from PBE", pbeEndStatus);
        status = RCL_CommandStatus_Error;
        break;
    }
    return status;
}

/*
 *  ======== RCL_Handler_Ieee_maskEventsByFifoConf ========
 */
static uint32_t RCL_Handler_Ieee_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate)
{
    /* Remove events that will not give an entry in the RX FIFO, based on FIFOCFG, unless active update is used */
    if (!activeUpdate)
    {
        /* Remove events that will not give an entry in the RX FIFO, based on FIFOCFG. */
        mask &= ~(((fifoConfVal & PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_M) ? LRF_EventRxIgnored.value : 0U) |
                  ((fifoConfVal & PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_M) ? LRF_EventRxNok.value : 0U) |
                  LRF_EventRxBufFull.value | LRF_EventTxAck.value);
    }
    return mask;
}

/*
 *  ======== RCL_Handler_Ieee_updateRxStats ========
 */
static void RCL_Handler_Ieee_updateStats(RCL_StatsIeee *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Read LASTTIMESTAMP andf LASTTIMESTAMPH as one unit */
        uint32_t lastTimestamp = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_LASTTIMESTAMPL);

        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = 0U;
        }
        else
        {
            stats->timestampValid = 1U;
            stats->lastTimestamp = lastTimestamp - IEEE_TIMESTAMP_ADJUST;
        }
        stats->lastRssi = (int8_t) HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_LASTRSSI);
        int8_t maxRssi = LRF_readMaxRssi();
        if (maxRssi == IEEE_RSSI_MIN_VALUE)
        {
            /* If we see the minimum value, there is probably no valid max RSSI. But if the RSSI is valid
               and minimum, this value is indeed the maximum observed */
            if (LRF_readRssi() != IEEE_RSSI_MIN_VALUE)
            {
                maxRssi = LRF_RSSI_INVALID;
            }
        }
        stats->maxRssi = maxRssi;
        stats->nRxNok = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK);
        stats->nRxFifoFull = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL);
        stats->nRxOk = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK);
        stats->nRxIgnored = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED);
        stats->nTx = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX);
        stats->nTxImmAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK);
        stats->nTxEnhAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXENHACK);
    }
}

/*
 *  ======== RCL_Handler_Ieee_initStats ========
 */
static bool RCL_Handler_Ieee_initStats(RCL_StatsIeee *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        /* This accesses PBE_IEEE_RAM_O_LASTTIMESTAMPL and PBE_IEEE_RAM_O_LASTTIMESTAMPH */
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_LASTTIMESTAMPL) = startTime;
        stats->timestampValid = 0U;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0U)
        {
            /* Copy existing values into PBE */
            if (stats->maxRssi == LRF_RSSI_INVALID)
            {
                /* Invalidate max RSSI by setting minimum value */
                LRF_initializeMaxRssi(IEEE_RSSI_MIN_VALUE);
            }
            else
            {
                /* Store old maximum value */
                LRF_initializeMaxRssi(stats->maxRssi);
            }
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = stats->nRxFifoFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = stats->nRxIgnored;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = stats->nTx;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK) = stats->nTxImmAck;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXENHACK) = stats->nTxEnhAck;
        }
        else
        {
            /* Reset existing values in PBE */
            LRF_initializeMaxRssi(IEEE_RSSI_MIN_VALUE);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXENHACK) = 0;

            stats->maxRssi = LRF_RSSI_INVALID;
            stats->nRxNok = 0;
            stats->nRxFifoFull = 0;
            stats->nRxOk = 0;
            stats->nRxIgnored = 0;
            stats->nTx = 0;
            stats->nTxImmAck = 0;
            stats->nTxEnhAck = 0;
        }
        return (bool) stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in PBE */
        LRF_initializeMaxRssi(IEEE_RSSI_MIN_VALUE);
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = 0;

        return false;
    }
}

/*
 *  ======== RCL_Handler_Ieee_setCustomEventTime ========
 */
static bool RCL_Handler_Ieee_setCustomEventTime(uint32_t eventTime, uint32_t timeMargin, bool hardStop)
{
    bool setCustomEventTime = true;
    if (rclSchedulerState.hardStopInfo.stopReason != RCL_SchedulerStopReason_None)
    {
        if (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Timeout)
        {
            /* Only set custom time if the next hard stop (timeout) is expected after the margin */
            setCustomEventTime = RCL_Scheduler_isLater(eventTime + timeMargin, rclSchedulerState.hardStopInfo.cmdStopTime);
        }
        else if (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Scheduling)
        {
            /* Only set custom time if the next hard stop (scheduler) is expected after the margin */
            setCustomEventTime = RCL_Scheduler_isLater(eventTime + timeMargin, rclSchedulerState.hardStopInfo.schedStopTime);
        }
        else
        {
            /* Otherwise API stop is active and command should stop shortly - do not set custom time */
            setCustomEventTime = false;
        }
    }
    if (setCustomEventTime)
    {
        if (hardStop)
        {
            /* Configure PBE to keep REQUEST asserted if coex is enabled, REQUEST was already asserted,
               and priority is not set to be changed. */
            RCL_Handler_Ieee_setCoexEndMode();
            /* Program hard stop time */
            RCL_Hal_setupHardStopTime(eventTime);
            /* Flag as custom time */
            ieeeHandlerState.common.nextEventTime = eventTime;
            ieeeHandlerState.common.eventTimeType = customHardStop;
        }
        else
        {
            /* Change the stop time and set it to a soft timing */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) | PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_M;
            RCL_Hal_setupHardStopTime(eventTime);
            RCL_Hal_enableHardStopTimeIrq();
            ieeeHandlerState.common.nextEventTime = eventTime;
            ieeeHandlerState.common.eventTimeType = customEvent;
        }
    }
    else
    {
        /* Command will stop very soon, so time not set */
        if (ieeeHandlerState.common.eventTimeType != noEvent)
        {
            (void) RCL_Handler_Ieee_restoreStopTime();
        }
    }
    return setCustomEventTime;
}

/*
 *  ======== RCL_Handler_Ieee_restoreStopTime ========
 */
static bool RCL_Handler_Ieee_restoreStopTime(void)
{
    if (ieeeHandlerState.common.eventTimeType != noEvent)
    {
        RCL_Hal_cancelHardStopTime();
        /* Set back stop event */
        RCL_StopType stopType = RCL_Scheduler_setStopTimes();

        /* Clear systimer event in TOPsm to avoid an old event stopping the RX */
        HWREGH_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_EVTCLR0) = LRFDPBE_EVTCLR0_SYSTCMP0_M;

        /* Set stop time back to hard stop */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
            (uint16_t) (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) & ~PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_M);

        ieeeHandlerState.common.eventTimeType = noEvent;
        /* If hard stop already occurred, it needs to be executed (unless already planned) */
        /* Other stop types returned should not need special handling */
        if (stopType == RCL_StopType_Hard)
        {
            if (rclSchedulerState.hardStopInfo.apiStopEnabled == 0U)
            {
                LRF_sendHardStop();
                rclSchedulerState.hardStopInfo.apiStopEnabled = 1;
            }
            return true;
        }
    }
    return false;
}

/*
 *  ======== RCL_Handler_Ieee_processSourceMatchingOperation ========
 */
static RCL_IEEE_UpdateResult RCL_Handler_Ieee_processSourceMatchingOperation(RCL_IEEE_SourceMatchingUpdate description,
        uint16_t *entryEnable, uint16_t *framePending)
{
    uint32_t index = description.index;

    uint32_t bitMaskIndex = index / 16U;
    uint16_t bitMask = 1U << (index & 0x0FU);
    /* Default result */
    RCL_IEEE_UpdateResult result = RCL_IEEE_UpdateDone;
    switch (description.operation)
    {
        case RCL_IEEE_DisableEntry:
            /* Disable the entry */
            entryEnable[bitMaskIndex] &= ~bitMask;
            break;
        case RCL_IEEE_EnableEntry:
            /* Enable the entry */
            entryEnable[bitMaskIndex] |= bitMask;
            break;
        case RCL_IEEE_FrameNotPending:
            /* Set frame not pending */
            framePending[bitMaskIndex] &= ~bitMask;
            break;
        case RCL_IEEE_FramePending:
            /* Set frame pending */
            framePending[bitMaskIndex] |= bitMask;
            break;
        case RCL_IEEE_NewAddrFrameNotPending:
            /* Enable and set frame not pending */
            framePending[bitMaskIndex] &= ~bitMask;
            entryEnable[bitMaskIndex] |= bitMask;
            /* Inform caller to update address */
            result = RCL_IEEE_UpdatePending;
            break;
        case RCL_IEEE_NewAddrFramePending:
            /* Enable and set frame pending */
            framePending[bitMaskIndex] |= bitMask;
            entryEnable[bitMaskIndex] |= bitMask;
            /* Inform caller to update address */
            result = RCL_IEEE_UpdatePending;
            break;
        default:
            /* Error */
            result = RCL_IEEE_UpdateParamError;
            break;
    }
    return result;
}

/*
 * ======== RCL_Handler_Ieee_updateSrcMatchTableShort ========
 */
static bool RCL_Handler_Ieee_updateSrcMatchTableShort(RCL_CmdIeeeRxTx *ieeeCmd)
{
    uint32_t panNo = ieeeHandlerState.rxTx.srcMatchUpdateDesc.panNo;
    uint32_t index = ieeeHandlerState.rxTx.srcMatchUpdateDesc.index;
    if (ieeeCmd->rxAction == NULL || panNo >= ieeeHandlerState.rxTx.numPan)
    {
        /* No RX action or pan number out of range - give up */
        ieeeHandlerState.rxTx.srcMatchUpdatePhase = noSrcMatchUpdate;
    }
    else
    {
        RCL_CmdIeee_SourceMatchingTableShort *table = ieeeCmd->rxAction->panConfig[panNo].sourceMatchingTableShort;
        if (table == NULL || index >= table->numEntries)
        {
            /* Index out of range - give up */
            ieeeHandlerState.rxTx.srcMatchUpdatePhase = noSrcMatchUpdate;
        }
        else
        {
            RCL_Handler_Ieee_updateSrcMatchTable(
                table->entryEnable,
                table->framePending,
                &table->shortEntry[index],
                NULL);
        }
    }
    return (ieeeHandlerState.rxTx.srcMatchUpdatePhase == noSrcMatchUpdate);
}

/*
 * ======== RCL_Handler_Ieee_updateSrcMatchTableExt ========
 */
static bool RCL_Handler_Ieee_updateSrcMatchTableExt(RCL_CmdIeeeRxTx *ieeeCmd)
{
    uint32_t panNo = ieeeHandlerState.rxTx.srcMatchUpdateDesc.panNo;
    uint32_t index = ieeeHandlerState.rxTx.srcMatchUpdateDesc.index;
    if (ieeeCmd->rxAction == NULL || panNo >= ieeeHandlerState.rxTx.numPan)
    {
        /* No RX action or pan number out of range - give up */
        ieeeHandlerState.rxTx.srcMatchUpdatePhase = noSrcMatchUpdate;
    }
    else
    {
        RCL_CmdIeee_SourceMatchingTableExt *table = ieeeCmd->rxAction->panConfig[panNo].sourceMatchingTableExt;
        if (table == NULL || index >= table->numEntries)
        {
            /* Index out of range - give up */
            ieeeHandlerState.rxTx.srcMatchUpdatePhase = noSrcMatchUpdate;
        }
        else
        {
            RCL_Handler_Ieee_updateSrcMatchTable(
                table->entryEnable,
                table->framePending,
                NULL,
                &table->extEntry[index]);
        }
    }
    return (ieeeHandlerState.rxTx.srcMatchUpdatePhase == noSrcMatchUpdate);
}

/*
 * ======== RCL_Handler_Ieee_updateSrcMatchTable ========
 */
static void RCL_Handler_Ieee_updateSrcMatchTable(uint16_t *entryEnable, uint16_t *framePending, RCL_CmdIeee_PanIdAddr *shortEntry, uint64_t *extEntry)
{
    RCL_Handler_Ieee_SourceMatchUpdatePhase currentPhase = ieeeHandlerState.rxTx.srcMatchUpdatePhase;
    uint32_t index = ieeeHandlerState.rxTx.srcMatchUpdateDesc.index;
    uint32_t panNo = ieeeHandlerState.rxTx.srcMatchUpdateDesc.panNo;
    RCL_IEEE_SourceMatchingOperation operation = ieeeHandlerState.rxTx.srcMatchUpdateDesc.operation;

    uint32_t bitMaskIndex = index / 16U;
    uint32_t ramRegOffset = ((extEntry != NULL) ? 4U : 0U) + panNo * (PBE_IEEE_RAM_O_ENTRYENABLE10 - PBE_IEEE_RAM_O_ENTRYENABLE00);
    uint32_t tableOffset = panNo * (PBE_IEEE_RAM_O_PAN1_SRC_MATCH_SHORT_START - PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START);
    uint16_t bitMask = 1U << (index & 0x0FU);
    uint16_t newValue;
    if (currentPhase == srcMatchUpdateStart)
    {
        if (operation == RCL_IEEE_FrameNotPending || operation == RCL_IEEE_FramePending)
        {
            if (operation == RCL_IEEE_FrameNotPending)
            {
                /* Set frame not pending */
                newValue = framePending[bitMaskIndex] & ~bitMask;
            }
            else
            {
                /* Set frame pending */
                newValue = framePending[bitMaskIndex] | bitMask;
            }
            uintptr_t key = HwiP_disable();
            if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_SRCMATCHIDX) != IEEE_SOURCE_MATCHING_BUSY)
            {
                /* Value can be updated */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FRAMEPENDING00 + ramRegOffset + (bitMaskIndex << 1)) = newValue;
                HwiP_restore(key);
                /* Done - update table and end */
                framePending[bitMaskIndex] = newValue;
                currentPhase = noSrcMatchUpdate;
                LRF_disableHwInterrupt(LRF_EventRxCtrl.value);
            }
            else
            {
                HwiP_restore(key);
                /* Entry can't be udated now. Wait for frame filtering done */
                LRF_enableHwInterrupt(LRF_EventRxCtrl.value);
            }
        }
        else
        {
            if (operation == RCL_IEEE_EnableEntry)
            {
                /* Enable the entry */
                newValue = entryEnable[bitMaskIndex] | bitMask;
            }
            else
            {
                /* Disable the entry. This is also done when changing address. */
                newValue = entryEnable[bitMaskIndex] & ~bitMask;
            }
            uintptr_t key = HwiP_disable();
            if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_SRCMATCHIDX) != IEEE_SOURCE_MATCHING_BUSY)
            {
                /* Value can be updated */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_ENTRYENABLE00 + ramRegOffset + (bitMaskIndex << 1)) = newValue;
                HwiP_restore(key);
                if (operation <= RCL_IEEE_EnableEntry)
                {
                    /* Done - update table and end */
                    entryEnable[bitMaskIndex] = newValue;
                    currentPhase = noSrcMatchUpdate;
                }
                else
                {
                    /* Set new frame pending value and address */
                    if (operation == RCL_IEEE_NewAddrFrameNotPending)
                    {
                        /* Set frame not pending */
                        newValue = framePending[bitMaskIndex] & ~bitMask;
                    }
                    else
                    {
                        /* Set frame pending */
                        newValue = framePending[bitMaskIndex] | bitMask;
                    }
                    /* Set new values in BUFRAM; update table when change is done.
                    The change is safe to do now, since the entry has been disabled. */
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FRAMEPENDING00 + ramRegOffset + (bitMaskIndex << 1)) = newValue;
                    if (extEntry != NULL)
                    {
                        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + tableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_EXT_START + (index << 3)) =
                            (uint32_t) ieeeHandlerState.rxTx.newSrcMatch.newExtAddr;
                        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + tableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_EXT_START + (index << 3) + 4U) =
                            (uint32_t) (ieeeHandlerState.rxTx.newSrcMatch.newExtAddr >> 32ULL);
                    }
                    else
                    {
                        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + tableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START + (index << 2)) =
                            ieeeHandlerState.rxTx.newSrcMatch.newPanIdAddr.combined;
                    }
                    currentPhase = srcMatchUpdateFinish;
                }
                LRF_disableHwInterrupt(LRF_EventRxCtrl.value);
            }
            else
            {
                HwiP_restore(key);
                /* Entry can't be udated now. Wait for frame filtering done */
                LRF_enableHwInterrupt(LRF_EventRxCtrl.value);
            }
        }
    }
    if (currentPhase == srcMatchUpdateFinish)
    {
        if (operation == RCL_IEEE_NewAddrFrameNotPending || operation == RCL_IEEE_NewAddrFramePending)
        {
            /* Enable the entry */
            newValue = entryEnable[bitMaskIndex] | bitMask;
            uintptr_t key = HwiP_disable();
            if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_SRCMATCHIDX) != IEEE_SOURCE_MATCHING_BUSY)
            {
                /* Value can be updated */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_ENTRYENABLE00 + ramRegOffset + (bitMaskIndex << 1)) = newValue;
                HwiP_restore(key);
                /* Done - update table and end */
                if (extEntry != NULL)
                {
                    *extEntry = ieeeHandlerState.rxTx.newSrcMatch.newExtAddr;
                }
                else
                {
                    *shortEntry = ieeeHandlerState.rxTx.newSrcMatch.newPanIdAddr;
                }
                if (operation == RCL_IEEE_NewAddrFrameNotPending)
                {
                    /* Set frame not pending to match what was previously done in BUFRAM */
                    framePending[bitMaskIndex] &= ~bitMask;
                }
                else
                {
                    /* Set frame pending to match what was previously done in BUFRAM */
                    framePending[bitMaskIndex] |= bitMask;
                }
                entryEnable[bitMaskIndex] = newValue;
                currentPhase = noSrcMatchUpdate;
                LRF_disableHwInterrupt(LRF_EventRxCtrl.value);
            }
            else
            {
                HwiP_restore(key);
                /* Entry can't be updated now. Wait for frame filtering done */
                LRF_enableHwInterrupt(LRF_EventRxCtrl.value);
            }
        }
    }
    ieeeHandlerState.rxTx.srcMatchUpdatePhase = currentPhase;
}


/*
 *  ======== RCL_Handler_Ieee_findNumExtraBytes ========
 */
static uint32_t RCL_Handler_Ieee_findNumExtraBytes(uint32_t fifoCfg)
{
    uint32_t numExtraBytes = 0;
    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDCRC_M) != 0U)
    {
        numExtraBytes += IEEE_MAC_CRC_LEN;
    }
    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDSTATUS_M) != 0U)
    {
        numExtraBytes += 1U;
    }
    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDLQI_M) != 0U)
    {
        numExtraBytes += 1U;
    }
    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_M) != 0U)
    {
        numExtraBytes += 1U;
    }
    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_M) != 0U)
    {
        numExtraBytes += sizeof(uint32_t);
    }

    return numExtraBytes;
}

/*
 *  ======== RCL_IEEE_getRxRssi ========
 */
int8_t RCL_IEEE_getRxRssi(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ieeeHandlerState.rxTx.fifoCfg;

    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_M) != 0U)
    {
        /* Find number of bytes in RSSI and the appended bytes after that */
        uint32_t positionFromEnd = RCL_Handler_Ieee_findNumExtraBytes(fifoCfg &
                                                                     (PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_M |
                                                                      PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_M));
        int32_t offset = (int32_t) (rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - positionFromEnd);

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
 *  ======== RCL_IEEE_getRxLqi ========
 */
uint8_t RCL_IEEE_getRxLqi(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ieeeHandlerState.rxTx.fifoCfg;

    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDLQI_M) != 0U)
    {
        /* Find number of bytes in LQI and the appended bytes after that */
        uint32_t positionFromEnd = RCL_Handler_Ieee_findNumExtraBytes(fifoCfg &
                                                                     (PBE_IEEE_RAM_FIFOCFG_APPENDLQI_M |
                                                                      PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_M |
                                                                      PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_M));
        int32_t offset = (int32_t) (rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - positionFromEnd);

        if (offset < 0)
        {
            return 0;
        }
        else
        {
            const uint8_t *lqiPtr = (const uint8_t *) (rxEntry->data + offset);

            return *lqiPtr;
        }
    }
    else
    {
        return 0;
    }
}

/*
 *  ======== RCL_IEEE_getRxTimestamp ========
 */
uint32_t RCL_IEEE_getRxTimestamp(const RCL_Buffer_DataEntry *rxEntry)
{
    uint16_t fifoCfg = ieeeHandlerState.rxTx.fifoCfg;

    if ((fifoCfg & PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_M) != 0U)
    {
        uint32_t timestamp;
        int32_t offset = (int32_t) (rxEntry->length - sizeof(rxEntry->numPad) - sizeof(rxEntry->pad0) - sizeof(timestamp));
        if (offset < 0)
        {
            return 0;
        }
        else
        {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            const uint32_t *dataPtr = (uint32_t *) (rxEntry->data + offset);
            timestamp = *dataPtr;
#else
            const uint8_t *dataPtr = rxEntry->data + offset;
            timestamp = dataPtr[0] | (dataPtr[1] << 8) | (dataPtr[2] << 16) | (dataPtr[3] << 24);
#endif
        }
        return timestamp - IEEE_TIMESTAMP_ADJUST;
    }
    else
    {
        return 0;
    }
}

/*
 * ======== RCL_Handler_Ieee_setCoexEndMode ========
 */
static void RCL_Handler_Ieee_setCoexEndMode(void)
{
    /* Configure PBE to keep REQUEST asserted if coex is enabled, REQUEST was already asserted,
       and priority is not set to be changed. */
    if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration))
    {
        uint16_t coexCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG);
        if (coexCfg != 0U)
        {
            if (ieeeHandlerState.rxTx.coexPriorityChange)
            {
                coexCfg &= ~PBE_IEEE_RAM_COEXCFG_RETAINREQ_M;
            }
            else
            {
                coexCfg |= PBE_IEEE_RAM_COEXCFG_RETAINREQ_M;
            }
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG) = coexCfg;
        }
    }
}

/*
 * ======== RCL_Handler_Ieee_setCoexPriority ========
 */
static void RCL_Handler_Ieee_setCoexPriority(bool tx)
{
    /* Set the coex priority to use next, and turn off RETAINREQ to allow PBE to deassert REQUEST
       when applicable */
    if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration))
    {
        uint16_t coexCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG);
        if (coexCfg != 0U)
        {
            /* Always disable RETAINREQ when starting operation */
            coexCfg &= (uint16_t) ~PBE_IEEE_RAM_COEXCFG_RETAINREQ_M;
            uint32_t priority = ieeeHandlerState.rxTx.coexPriority;
            if (tx && ieeeHandlerState.rxTx.coexPriorityChange)
            {
                priority = (priority == 0U) ? 1U : 0U;
            }
            if (priority == 0U)
            {
                coexCfg &= (uint16_t) (~PBE_IEEE_RAM_COEXCFG_PRIORITY_M);
            }
            else
            {
                coexCfg |= PBE_IEEE_RAM_COEXCFG_PRIORITY_M;
            }
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_COEXCFG) = coexCfg;
        }
    }
}

/*
 * ======== RCL_Handler_Ieee_processCoexTxPriority ========
 */
static void RCL_Handler_Ieee_processCoexTxPriority(RCL_CmdIeee_TxAction *txAction)
{
    if (COEX_REQUEST_GLOBAL_ENABLE(lrfCoexConfiguration))
    {
        uint32_t txPriority = ((bool)txAction->coexPriority) ^ lrfCoexConfiguration.invertedPriority;

        ieeeHandlerState.rxTx.coexPriorityChange = (txPriority != ieeeHandlerState.rxTx.coexPriority);
    }
}
