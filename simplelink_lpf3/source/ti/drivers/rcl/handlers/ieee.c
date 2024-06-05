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
 *  ======== ieee.c ========
 */

#ifndef DeviceFamily_CC27XX

#include <stdint.h>
#include <stdlib.h>

#include <ti/log/Log.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Profiling.h>

#include <ti/drivers/rcl/hal/hal.h>
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

/** Polynomial to use for PRBS9 data */
#define RCL_HANDLER_IEEE_PRBS9_POLY             0x08800000
/** Polynomial to use for PRBS15 data */
#define RCL_HANDLER_IEEE_PRBS15_POLY            0x80020000
/** Polynomial to use for PRBS32 data */
#define RCL_HANDLER_IEEE_PRBS32_POLY            0x00400007
#define RCL_HANDLER_IEEE_PRBS_INIT              0x0000001F

#define RCL_HANDLER_IEEE_RESTORE_NONE           0x0000
#define RCL_HANDLER_IEEE_RESTORE_MODCTRL        0x0001
#define RCL_HANDLER_IEEE_RESTORE_WHITENING      0x0002
#define RCL_HANDLER_IEEE_RESTORE_SFD            0x0004

/* Byte length of IEEE 802.15.4 frame fields */
#define IEEE_PHY_HDR_LEN                        1
#define IEEE_MAC_FCF_LEN                        2

/* Timing constants */
/* Backoff period for the O-QPSK PHY per the 802.15.4 standard */
#define IEEE_BACKOFF_PERIOD                     RCL_SCHEDULER_SYSTIM_US(320)
/* Necessary margin to start CCA */
#define IEEE_CCA_START_TIME_MARGIN              RCL_SCHEDULER_SYSTIM_US(192)

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
    noEvent,
    customEvent,
    customHardStop,
} RCL_Handler_Ieee_EventType;

struct
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
            RCL_Handler_Ieee_TxState txState;
            RCL_Handler_Ieee_RxState rxState;
            uint8_t         ccaContentionWindow;
            bool            waitingForValidRssi;
            bool            allowTxDelay;
            bool            alwaysStoreAck;
            uint8_t         expSeqNo;
            uint32_t        ccaTxStartTime;
            RCL_StopType    txActionStop;
        } rxTx;
    };
} ieeeHandlerState;

static void RCL_Handler_Ieee_updateRxCurBufferAndFifo(List_List *rxBuffers);
static RCL_CommandStatus RCL_Handler_Ieee_findPbeErrorEndStatus(uint16_t pbeEndStatus);
static uint32_t RCL_Handler_Ieee_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate);
static void RCL_Handler_Ieee_updateStats(RCL_StatsIeee *stats, uint32_t startTime);
static bool RCL_Handler_Ieee_initStats(RCL_StatsIeee *stats, uint32_t startTime);
static bool RCL_Handler_Ieee_setCustomEventTime(uint32_t eventTime, uint32_t timeMargin, bool hardStop);
static bool RCL_Handler_Ieee_restoreStopTime(void);

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

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        ieeeHandlerState.rxTx.rxState = rxStateNoRx;
        ieeeHandlerState.rxTx.txState = txStateNoTx;
        ieeeHandlerState.common.eventTimeType = noEvent;
        ieeeHandlerState.common.apiHardStopPending = false;
        ieeeHandlerState.rxTx.txActionStop = RCL_StopType_None;

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
                    txAction->expectImmAck != 0 ||
                    txAction->expectEnhAck != 0)
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
            else if (rxAction->numPan == 0 && txAction != NULL &&
                     (txAction->expectImmAck != 0 || txAction->expectEnhAck != 0))
            {
                /* RX ACK not supported with promiscuous mode */
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
                return rclEvents;
            }
        }

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if (txAction != NULL)
        {
            uint32_t cmdTime = (cmd->scheduling == RCL_Schedule_AbsTime) ? cmd->timing.absStartTime : RCL_Scheduler_getCurrentTime();
            uint32_t txActionTime = (txAction->ccaScheduling == RCL_Schedule_AbsTime) ? txAction->absCcaStartTime : cmdTime;
            /* Check that TX action start time is not before the command start time */
            if (!txAction->allowDelay && !RCL_Scheduler_isLater(cmdTime, txActionTime))
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
                    if (rxAction == NULL || RCL_Scheduler_delta(cmdTime, txTime) < (2 * IEEE_CCA_START_TIME_MARGIN))
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

        if (rclEvents.lastCmdDone == 0)
        {
            /* Program frequency word */
            LRF_programFrequency(ieeeCmd->rfFrequency, startTx);

            if (LRF_programTxPower(ieeeCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
        }

        if (rclEvents.lastCmdDone == 0)
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

        if (rclEvents.lastCmdDone == 0 && rxAction != NULL)
        {
            /* Prepare receiver */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0; /* No timeout except from SYSTIM */

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_PIB) = rxAction->numPan;

            uint32_t panRegOffset = 0;
            uint32_t sourceMatchHeaderOffset = 0;
            uint32_t sourceMatchTableOffset = 0;
            for (int i = 0; i < rxAction->numPan; i++)
            {
                RCL_CmdIeee_PanConfig *panConfig = &rxAction->panConfig[i];
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
                            PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY;
                        break;

                    case RCL_CmdIeee_AutoAck_ImmAckNoAutoPend:
                        frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                            PBE_IEEE_RAM_FFOPT0_AUTOPEND_DISABLE |
                            PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY;
                        break;

                    case RCL_CmdIeee_AutoAck_ImmAckAutoPendAll:
                        frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                            PBE_IEEE_RAM_FFOPT0_AUTOPEND_EN |
                            PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY;
                        break;

                    case RCL_CmdIeee_AutoAck_ImmAckAutoPendDataReq:
                        frameFilteringOption |= PBE_IEEE_RAM_FFOPT0_AUTOACK_EN |
                            PBE_IEEE_RAM_FFOPT0_AUTOPEND_EN |
                            PBE_IEEE_RAM_FFOPT0_PREQONLY_DATAREQ;
                        break;
                }

                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + panRegOffset + PBE_IEEE_RAM_O_FFOPT0) = frameFilteringOption;

                /* Set up source matching */
                if (panConfig->sourceMatchingTableExt != NULL)
                {
                    /* Extended source matching: Not yet supported */
                    cmd->status = RCL_CommandStatus_Error_Param;
                    rclEvents.lastCmdDone = 1;
                    break;
                }
                if (panConfig->sourceMatchingTableShort != NULL)
                {
                    RCL_CmdIeee_SourceMatchingTableShort *sourceMatchingTable = panConfig->sourceMatchingTableShort;
                    uint32_t numEntries = sourceMatchingTable->numEntries;
                    if (numEntries > RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_MAX_LEN)
                    {
                        cmd->status = RCL_CommandStatus_Error_Param;
                        rclEvents.lastCmdDone = 1;
                        break;
                    }
                    uint32_t entryNo = 0;
                    uint32_t index = 0;
                    while (entryNo < numEntries)
                    {
                        uint16_t mask = 0xFFFF;
                        if ((numEntries - entryNo) < 16)
                        {
                            mask >>= (16 - (numEntries - entryNo));
                        }
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE00 + (index << 1)) =
                            sourceMatchingTable->entryEnable[index] & mask;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_FRAMEPENDING00 + (index << 1)) =
                            sourceMatchingTable->framePending[index] & mask;
                        index++;
                        entryNo += 16;
                    }
                    while (index < RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_NUM_WORDS)
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_ENTRYENABLE00 + (index << 1)) = 0;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FRAMEPENDING00 + (index << 1)) = 0;
                        index++;
                    }
                    for (entryNo = 0; entryNo < numEntries; entryNo++)
                    {
                        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchTableOffset + PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START + (entryNo << 2)) =
                            sourceMatchingTable->shortEntry[entryNo].combined;
                    }
                }
                else
                {
                    for (int i = 0; i < RCL_CMD_IEEE_SOURCE_MATCH_TABLE_SHORT_NUM_WORDS; i++)
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + sourceMatchHeaderOffset + PBE_IEEE_RAM_O_ENTRYENABLE00 + (i << 1)) = 0;
                    }
                }

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
        }

        if (rclEvents.lastCmdDone == 0)
        {
            if (rxAction != NULL)
            {
                /* Start receiver */
                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                ieeeHandlerState.common.rxFifoSize = LRF_prepareRxFifo();
                ieeeHandlerState.common.curBuffer = NULL;
                RCL_Handler_Ieee_updateRxCurBufferAndFifo(&rxAction->rxBuffers);

                /* Enable interrupts */
                uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_FIFOCFG);
                LRF_enableHwInterrupt(RCL_Handler_Ieee_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                            LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                            LRF_EventRxIgnored.value | LRF_EventRxBufFull.value |
                                                                            (ieeeHandlerState.common.activeUpdate ? LRF_EventTxAck.value : 0),
                                                                            fifoCfg, ieeeHandlerState.common.activeUpdate));
                if (!startTx)
                {
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                        PBE_IEEE_RAM_OPCFG_STOP_SOFTEND |
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
                    Log_printf(RclCore, Log_VERBOSE, "Starting IEEE RX");
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
        if (rclEventsIn.stopTimesUpdated)
        {
            if (ieeeHandlerState.common.eventTimeType != noEvent)
            {
                bool hardStop = (ieeeHandlerState.common.eventTimeType == customHardStop);
                /* Event has been turned off by stop time modification */
                ieeeHandlerState.common.eventTimeType = noEvent;
                /* Turn back on if possible */
                RCL_Handler_Ieee_setCustomEventTime(ieeeHandlerState.common.nextEventTime, IEEE_CCA_START_TIME_MARGIN, hardStop);
            }
        }
        if (rclEventsIn.handlerCmdUpdate)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            RCL_StopType txActionStop = ieeeHandlerState.rxTx.txActionStop;
            if (txActionStop != RCL_StopType_None && txAction != NULL)
            {
                if (txAction->txStatus < RCL_CommandStatus_Active)
                {
                    Log_printf(RclCore, Log_VERBOSE, "Descheduling pending TX action");
                    /* TX action can be descheduled */
                    txAction->txStatus = RCL_CommandStatus_DescheduledApi;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if (ieeeHandlerState.rxTx.txState <= txStateWaitForTx)
                {
                    /* Waiting for CCA or TX to start; hard or graceful stop possible */
                    if (txActionStop == RCL_StopType_Graceful || txActionStop == RCL_StopType_Hard)
                    {
                        RCL_Handler_Ieee_restoreStopTime();
                        Log_printf(RclCore, Log_VERBOSE, "Stopping pending CCA or TX");
                        txAction->txStatus = (txActionStop == RCL_StopType_Graceful) ? RCL_CommandStatus_GracefulStopApi : RCL_CommandStatus_HardStopApi;
                        ieeeHandlerState.rxTx.txState = txStateFinished;
                        startTx = false;
                    }
                }
                else if ((ieeeHandlerState.rxTx.txState == txStateTx ||
                          ieeeHandlerState.rxTx.txState == txStateTxRx ||
                          ieeeHandlerState.rxTx.txState == txStateTxRxAck) &&
                          (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXSTATUS) & PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS) != 0)
                {
                    if (txActionStop == RCL_StopType_Hard)
                    {
                        Log_printf(RclCore, Log_VERBOSE, "Stopping TX due to hard stop");
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
                if (txAction->ccaScheduling == RCL_Schedule_AbsTime && !txAction->allowDelay &&
                    !RCL_Scheduler_isLater(currentTime, txActionTime))
                {
                    txAction->txStatus = RCL_CommandStatus_Error_StartTooLate;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if (ieeeCmd->rxAction->numPan == 0 &&
                     (txAction->expectImmAck != 0 || txAction->expectEnhAck != 0))
                {
                    txAction->txStatus = RCL_CommandStatus_Error_Param;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else
                {
                    txAction->txStatus = RCL_CommandStatus_Scheduled;
                    if (txAction->ccaMode == RCL_CmdIeee_NoCca)
                    {
                        /* Check if the command should go directly to TX */
                        uint32_t txTime = txActionTime + txAction->relativeTxStartTime;
                        ieeeHandlerState.rxTx.ccaTxStartTime = txTime;
                        ieeeHandlerState.rxTx.allowTxDelay = txAction->allowDelay || txAction->allowTxDelay;

                        if (RCL_Scheduler_delta(currentTime, txTime) < IEEE_CCA_START_TIME_MARGIN)
                        {
                            /* TX starts after a short time; stop RX now */
                            ieeeHandlerState.rxTx.txState = txStateSetTxTime;
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
        }
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
            if (ieeeHandlerState.rxTx.rxState == rxStateWaitForStart)
            {
                ieeeHandlerState.rxTx.rxState = rxStateRunning;
            }
        }
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_CmdIeee_RxAction *rxAction = ieeeCmd->rxAction;
            if (rxAction != NULL)
            {
                RCL_Handler_Ieee_updateRxCurBufferAndFifo(&rxAction->rxBuffers);
            }
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
            bool allowDelay = (ccaScheduling == RCL_Schedule_Now) ? true : txAction->allowDelay;

            uint32_t currentTime = RCL_Scheduler_getCurrentTime();
            ieeeHandlerState.rxTx.waitingForValidRssi = false;

            uint8_t ccaContentionWindow = txAction->ccaContentionWindow;
            if (ccaContentionWindow < 1)
            {
                ccaContentionWindow = 1;
            }
            ieeeHandlerState.rxTx.ccaContentionWindow = ccaContentionWindow;
            uint32_t ccaDuration = (ccaContentionWindow - 1) * IEEE_BACKOFF_PERIOD;
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
                Log_printf(RclCore, Log_VERBOSE, "Perform CCA");
                /* Set back stop event */
                RCL_Handler_Ieee_restoreStopTime();
            }
        }

        if (doCca)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            RCL_CmdIeee_CcaMode ccaMode = txAction->ccaMode;
            txAction->txStatus = RCL_CommandStatus_Active;

            bool busy = false;
            /* All CCA modes shall report busy if packet is in progress */
            if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXSTATUS) != 0)
            {
                busy = true;
                Log_printf(RclCore, Log_VERBOSE, "CCA busy because packet is in progress");
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
                    Log_printf(RclCore, Log_VERBOSE, "CCA invalid; check again");

                    ieeeHandlerState.rxTx.waitingForValidRssi = true;
                    /* Wait 1 backoff period for valid RSSI */
                    uint32_t ccaTime = ieeeHandlerState.rxTx.ccaTxStartTime;
                    ccaTime += IEEE_BACKOFF_PERIOD;
                    if (txAction->ccaContentionWindow <= 1)
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
                    RCL_Handler_Ieee_setCustomEventTime(ccaTime, IEEE_CCA_START_TIME_MARGIN, false);

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
                        Log_printf(RclCore, Log_VERBOSE, "CCA busy; RSSI = %1d dBm, correlation top count = %1d", rssi, corrCount);
                    }
                    else
                    {
                        Log_printf(RclCore, Log_VERBOSE, "CCA idle; RSSI = %1d dBm, correlation top count = %1d", rssi, corrCount);
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
                    ieeeHandlerState.rxTx.ccaContentionWindow -= 1;
                    if (ieeeHandlerState.rxTx.ccaContentionWindow == 0)
                    {
                        /* Channel idle - transmit */
                        ieeeHandlerState.rxTx.txState = txStateSetTxTime;
                        ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime + txAction->relativeTxStartTime;
                        ieeeHandlerState.rxTx.allowTxDelay = txAction->allowTxDelay;
                        Log_printf(RclCore, Log_VERBOSE, "Stop RX to go to TX");
                        /* Stop running RX */
                        LRF_sendHardStop();
                    }
                    else
                    {
                        /* Slotted CCA - check again after 1 backoff period */
                        ccaTime += IEEE_BACKOFF_PERIOD;
                        /* Set new compare time  */
                        RCL_Handler_Ieee_setCustomEventTime(ccaTime, IEEE_CCA_START_TIME_MARGIN, false);
                        ieeeHandlerState.rxTx.ccaTxStartTime = ccaTime;
                    }
                }
            }
        }

        if (lrfEvents.rxEmpty != 0)
        {
            /* Timeout or ACK reception */
            LRF_disableHwInterrupt(LRF_EventRxEmpty.value);
            if (ieeeHandlerState.rxTx.txState == txStateTxRxAck)
            {
                uint16_t ackStatus = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_ACKSTATUS);

                if (ackStatus & PBE_IEEE_RAM_ACKSTATUS_SYNCTIMEOUT_M)
                {
                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_NoSync;
                    ieeeHandlerState.rxTx.txState = txStateFinished;
                }
                else if (ackStatus & PBE_IEEE_RAM_ACKSTATUS_CRCOK_M)
                {
                    if (ieeeHandlerState.rxTx.alwaysStoreAck)
                    {
                        /* Need to check sequence number below */
                        ieeeHandlerState.rxTx.txState = txStateCheckAck;
                    }
                    else
                    {
                        ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
                        ieeeHandlerState.rxTx.txState = txStateFinished;
                    }
                }
                else if (ackStatus &
                    (PBE_IEEE_RAM_ACKSTATUS_IGNORED_M | PBE_IEEE_RAM_ACKSTATUS_OTHERFRM_M |
                     PBE_IEEE_RAM_ACKSTATUS_CRCERR_M))
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
        if (lrfEvents.txDone != 0)
        {
            LRF_disableHwInterrupt(LRF_EventTxDone.value);
            if (ieeeHandlerState.rxTx.txState == txStateTx || ieeeHandlerState.rxTx.txState == txStateTxRx)
            {
                ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
                ieeeHandlerState.rxTx.txState = txStateFinished;
            }
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
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
                    LRF_enable();
                    startTx = true;
                    ieeeHandlerState.rxTx.txState = txStateWaitForTx;
                }
            }
            else if (ieeeHandlerState.rxTx.txState == txStateTx)
            {
                if (lrfEvents.opDone != 0)
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
                        cmd->status = RCL_Handler_Ieee_findPbeErrorEndStatus(endCause);
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
            else
            {
                RCL_CommandStatus endStatus = ieeeHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
                if (endStatus == RCL_CommandStatus_Active)
                {
                    if (lrfEvents.opError != 0)
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
        }

        if (startTx)
        {
            RCL_CmdIeee_TxAction *txAction = ieeeCmd->txAction;
            txAction->txStatus = RCL_CommandStatus_Active;

            ieeeHandlerState.common.txFifoSize = LRF_prepareTxFifo();

            if (ieeeCmd->rxAction != NULL && (txAction->expectImmAck || !txAction->endCmdWhenDone))
            {
                /* Set TX to proceed with RX */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
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
                ieeeHandlerState.rxTx.rxState = rxStateWaitForStart;
            }
            else
            {
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                    PBE_IEEE_RAM_OPCFG_STOP_SOFTEND |
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
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(txEntry->length) / 4;

                if (wordLength > LRF_getTxFifoWritable() / 4)
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

                    if (txAction->expectImmAck)
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
                            (ieeeHandlerState.rxTx.alwaysStoreAck ?
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT :
                                PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_FILT) |
                            PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_EN |
                            (seqNo << PBE_IEEE_RAM_CFGAUTOACK_EXPSEQNM_S);
                        /* Get informed on ACK result */
                        interrupts.rxEmpty = 1;
                        ieeeHandlerState.rxTx.txState = txStateTxRxAck;
                        ieeeHandlerState.rxTx.expSeqNo = seqNo;
                    }
                    else
                    {
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_RXTIMEOUT) = 0;
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_CFGAUTOACK) =
                            PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT | PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_DIS;

                        if (ieeeCmd->rxAction != NULL && !txAction->endCmdWhenDone)
                        {
                            /* RX will go on, but TX action is finished at the end of TX */
                            interrupts.txDone = 1;
                            ieeeHandlerState.rxTx.txState = txStateTxRx;
                        }
                        else
                        {
                            ieeeHandlerState.rxTx.txState = txStateTx;
                        }
                    }
                    /* Clear and enable interrupts */
                    LRF_clearHwInterrupt(interrupts.value);
                    LRF_enableHwInterrupt(interrupts.value);

                    /* Post cmd */
                    Log_printf(RclCore, Log_VERBOSE, "Starting IEEE TX");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_TX;
                }
            }
        }

        if ((lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0) && ieeeCmd->rxAction != NULL)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            uint32_t rxFifoReadable = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE);
            while (rxFifoReadable >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / 4;
                if (wordLength > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    if (wordLength * 4 > rxFifoReadable)
                    {
                        /* Error */
                        curBuffer = NULL;
                    }
                    else
                    {
                        curBuffer = RCL_MultiBuffer_getBuffer(ieeeHandlerState.common.curBuffer,
                                                            wordLength * 4);
                        if (curBuffer != ieeeHandlerState.common.curBuffer) {
                            rclEvents.rxBufferFinished = 1;
                            ieeeHandlerState.common.curBuffer = curBuffer;
                        }
                    }
                    if (curBuffer == NULL) {
                        /* Error */
                        ieeeHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else {
                        uint32_t *data32;
                        data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(data32, wordLength);
                        RCL_MultiBuffer_commitBytes(curBuffer, wordLength * 4);
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
                        /* Adjust effective FIFO size */
                        RCL_Handler_Ieee_updateRxCurBufferAndFifo(&ieeeCmd->rxAction->rxBuffers);
                        if (ieeeHandlerState.rxTx.txState == txStateCheckAck)
                        {
                            if (lrfEvents.rxOk && wordLength >= 2)
                            {
                                /* Read out sequence number; expect rest of the frame to be checked OK by PBE */
                                RCL_Buffer_DataEntry *entry = (RCL_Buffer_DataEntry *) data32;
                                uint8_t seqNo = entry->data[entry->numPad - sizeof(entry->pad0) + IEEE_PHY_HDR_LEN + IEEE_MAC_FCF_LEN];
                                if (seqNo == ieeeHandlerState.rxTx.expSeqNo)
                                {
                                    ieeeCmd->txAction->txStatus = RCL_CommandStatus_Finished;
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
            }
            if (ieeeHandlerState.common.activeUpdate)
            {
                RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
            }
        }
        if (lrfEvents.txAck != 0 && ieeeCmd->rxAction != NULL)
        {
            if (ieeeHandlerState.common.activeUpdate)
            {
                RCL_Handler_Ieee_updateStats(ieeeCmd->stats, rclSchedulerState.actualStartTime);
            }
        }

        if (ieeeHandlerState.rxTx.txState == txStateFinished && cmd->status == RCL_CommandStatus_Active)
        {
            rclEvents.cmdStepDone = 1;
            LRF_disableHwInterrupt(LRF_EventRfesoft0.value);

            if (ieeeCmd->txAction->endCmdWhenDone || ieeeCmd->rxAction == NULL)
            {
                if (ieeeHandlerState.rxTx.rxState != rxStateNoRx)
                {
                    /* Stop running RX and let it finish */
                    ieeeHandlerState.common.endStatus = ieeeCmd->txAction->txStatus;
                    Log_printf(RclCore, Log_VERBOSE, "Stop RX as command should end");
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
                    LRF_enable();
                    /* Restart RX */
                    restartRx = true;
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
        RCL_CommandStatus status = RCL_Scheduler_setNewStartNow();
        if (status == RCL_CommandStatus_Active)
        {
            /* Set up for RX */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                PBE_IEEE_RAM_OPCFG_STOP_SOFTEND |
                PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES |
                PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES |
                PBE_IEEE_RAM_OPCFG_TXINFINITE_NO |
                PBE_IEEE_RAM_OPCFG_TXPATTERN_NO |
                PBE_IEEE_RAM_OPCFG_TXFCMD_NONE |
                PBE_IEEE_RAM_OPCFG_START_SYNC |
                PBE_IEEE_RAM_OPCFG_SINGLE_DIS |
                PBE_IEEE_RAM_OPCFG_IFSPERIOD_EN;
            /* Post cmd */
            Log_printf(RclCore, Log_VERBOSE, "Restarting IEEE RX");
            LRF_waitForTopsmReady();
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_RX;
            /* Clear RSSI valid interrupt flag */
            LRF_clearHwInterrupt(LRF_EventRfesoft0.value);
            ieeeHandlerState.rxTx.rxState = rxStateRunning;
        }
        else
        {
            cmd->status = status;
            rclEvents.lastCmdDone = 1;
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        /* Check if TX action has finished */
        if (ieeeHandlerState.rxTx.txState != txStateNoTx)
        {
            Log_printf(RclCore, Log_VERBOSE, "TX action ending because command ended");
            if (ieeeCmd->txAction != NULL && ieeeCmd->txAction->txStatus < RCL_CommandStatus_Finished)
            {
                /* End status not set - use command end status to show it ended with command */
                ieeeCmd->txAction->txStatus = cmd->status;
            }
            rclEvents.cmdStepDone = 1;
        }
        LRF_disable();
        LRF_disableSynthRefsys();
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

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
        ieeeHandlerState.txTest.restoreOpt = RCL_HANDLER_IEEE_RESTORE_NONE;
        ieeeHandlerState.common.apiHardStopPending = false;
        if ((txCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
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

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* End status not determined */
            ieeeHandlerState.common.endStatus = RCL_CommandStatus_Active;

            if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enter configuration */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_PATTERN) = txCmd->txWord;
            if (txCmd->config.sendCw != 0)
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
                HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = ieeeHandlerState.txTest.storedMdmSyncA ^ 0x00FF;
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
                Log_printf(RclCore, Log_VERBOSE, "Starting infinite TX");

                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_IEEE_REGDEF_API_OP_TX;
            }
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
        else if (lrfEvents.opError != 0)
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

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_MODCTRL) != 0)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) & (~LRFDMDM_MODCTRL_TONEINSERT_M);
        }
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_WHITENING) != 0)
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = ieeeHandlerState.txTest.storedWhitenPoly;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_WHITEINIT) = ieeeHandlerState.txTest.storedWhitenInit;
        }
        if ((ieeeHandlerState.txTest.restoreOpt & RCL_HANDLER_IEEE_RESTORE_SFD) != 0)
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
    if (txAction->txStatus != RCL_CommandStatus_Idle && txAction->txStatus < RCL_CommandStatus_Finished)
    {
        return RCL_CommandStatus_Error_AlreadySubmitted;
    }

    uintptr_t key = HwiP_disable();
    /* Check if command is finished */
    if (cmd == NULL || cmd->common.status >= RCL_CommandStatus_Finished)
    {
        /* TODO: New status */
        Log_printf(RclCore, Log_ERROR, "Command ended before TX action was submitted");
        status = RCL_CommandStatus_Error;
    }
    else if (cmd->txAction != NULL && cmd->txAction->txStatus != RCL_CommandStatus_Idle && cmd->txAction->txStatus < RCL_CommandStatus_Finished)
    {
        /* Another TX action is already running */
        status = RCL_CommandStatus_Error_AlreadySubmitted;
    }
    /* Extra check in case user modified status field */
    else if (rclSchedulerState.currCmd == &cmd->common && ieeeHandlerState.rxTx.txState != txStateNoTx)
    {
        status = RCL_CommandStatus_Error_AlreadySubmitted;
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
            RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
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
        RCL_Scheduler_postEvent(&cmd->common, RCL_EventHandlerCmdUpdate);
    }
    else
    {
        /* Command finished; nothing to do about TX action */
    }
    HwiP_restore(key);

    return txAction->txStatus;
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
        Log_printf(RclCore, Log_ERROR, "Unexpected error 0x%04X from PBE", pbeEndStatus);
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
        mask &= ~(((fifoConfVal & PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_M) ? LRF_EventRxIgnored.value : 0) |
                  ((fifoConfVal & PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_M) ? LRF_EventRxNok.value : 0) |
                  LRF_EventRxBufFull.value);
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
            stats->timestampValid = false;
        }
        else {
            stats->timestampValid = true;
            stats->lastTimestamp = lastTimestamp;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_LASTRSSI);
        stats->nRxNok = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK);
        stats->nRxFifoFull = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL);
        stats->nRxOk = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK);
        stats->nRxIgnored = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED);
        stats->nTx = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX);
        stats->nTxAck = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK);
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
        stats->timestampValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = stats->nRxFifoFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = stats->nRxIgnored;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = stats->nTx;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK) = stats->nTxAck;
        }
        else
        {
            /* Reset existing values in PBE */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTXACK) = 0;

            stats->nRxNok = 0;
            stats->nRxFifoFull = 0;
            stats->nRxOk = 0;
            stats->nRxIgnored = 0;
            stats->nTx = 0;
            stats->nTxAck = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in PBE */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXNOK) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXFIFOFULL) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXOK) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NRXIGNORED) = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_NTX) = 0;

        return false;
    }
}

static bool RCL_Handler_Ieee_setCustomEventTime(uint32_t eventTime, uint32_t timeMargin, bool hardStop)
{
    uint32_t activeStopTime;
    if (rclSchedulerState.hardStopInfo.stopReason != RCL_SchedulerStopReason_None)
    {
        if (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Timeout)
        {
            activeStopTime = rclSchedulerState.hardStopInfo.cmdStopTime;
        }
        else if (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Scheduling)
        {
            activeStopTime = rclSchedulerState.hardStopInfo.schedStopTime;
        }
        else
        {
            /* Otherwise API stop is active and command should stop shortly */
            activeStopTime = RCL_Scheduler_getCurrentTime();
        }
    }
    if (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_None ||
        RCL_Scheduler_isLater(eventTime + timeMargin, activeStopTime))
    {
        if (hardStop)
        {
            /* Program hard stop time */
            hal_setup_hard_stop_time(eventTime);
            /* Flag as custom time */
            ieeeHandlerState.common.nextEventTime = eventTime;
            ieeeHandlerState.common.eventTimeType = customHardStop;
        }
        else
        {
            /* Change the stop time and set it to a soft timing */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
                HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) | PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_M;
            hal_setup_hard_stop_time(eventTime);
            hal_enable_hard_stop_time_irq();
            ieeeHandlerState.common.nextEventTime = eventTime;
            ieeeHandlerState.common.eventTimeType = customEvent;
        }
        return true;
    }
    else
    {
        /* Command will stop very soon, so time not set */
        if (ieeeHandlerState.common.eventTimeType != noEvent)
        {
            RCL_Handler_Ieee_restoreStopTime();
        }
        return false;
    }
}

static bool RCL_Handler_Ieee_restoreStopTime(void)
{
    if (ieeeHandlerState.common.eventTimeType != noEvent)
    {
        hal_cancel_hard_stop_time();
        /* Set back stop event */
        RCL_StopType stopType = RCL_Scheduler_setStopTimes();

        /* Clear systimer event in TOPsm to avoid an old event stopping the RX */
        HWREGH_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_EVTCLR0) = LRFDPBE_EVTCLR0_SYSTCMP0_M;

        /* Set stop time back to hard stop */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) =
            HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_IEEE_RAM_O_OPCFG) & ~PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_M;

        ieeeHandlerState.common.eventTimeType = noEvent;
        /* If hard stop already occurred, it needs to be executed (unless already planned) */
        /* Other stop types returned should not need special handling */
        if (stopType == RCL_StopType_Hard)
        {
            if (rclSchedulerState.hardStopInfo.apiStopEnabled == 0)
            {
                LRF_sendHardStop();
                rclSchedulerState.hardStopInfo.apiStopEnabled = 1;
            }
            return true;
        }
    }
    return false;
}
#endif
