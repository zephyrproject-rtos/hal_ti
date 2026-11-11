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
 *  ======== generic.c ========
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <ti/log/Log.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Profiling.h>
#include <ti/drivers/rcl/RCL_Feature.h>

#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/hal/RCL_Hal.h>
#include <ti/drivers/rcl/commands/generic.h>


struct
{
    struct {
        uint16_t                txFifoSize;
        uint16_t                rxFifoSize;
        RCL_CommandStatus       endStatus;
        bool                    activeUpdate;
        bool                    powerStandbyConstraintSet;
        bool                    powerSwtcxoConstraintSet;
        RCL_MultiBuffer         *curBuffer;
    } common;
    union {
        struct {
            bool                gracefulStopObserved;
            bool                stopFs;
            uint32_t            txCount;
            uint32_t            period;
        } tx;
        struct {
            LRF_ModulationCtrl  modulationCtrl;
        } txTest;
        struct {
            uint32_t            longOkCount;
            uint32_t            longNokCount;
            LRF_SyncSearchCtrl  syncSearchCtrl;
        } rx;
        struct {
            uint32_t            longTxCount;
            uint32_t            longOkCount;
            uint32_t            longNokCount;
            uint32_t            longRxIgnoredCount;
            uint32_t            longRxAddrMismatchCount;
            uint32_t            longRxBufFullCount;
            LRF_SyncSearchCtrl  syncSearchCtrl;
        } nesb;
    };
} genericHandlerState;


static uint32_t RCL_Handler_Generic_prepareSynth(void);
static void RCL_Handler_Generic_setSynthPowerState(bool fsOff);
static void RCL_Handler_Generic_updateRxCurBufferAndFifo(List_List *rxBuffers);
static RCL_CommandStatus RCL_Handler_Generic_mapLrfErrorStatusToRclStatus(void);
static uint32_t RCL_Handler_Generic_updateTxBuffers(List_List *txBuffers, uint32_t maxBuffers);
static void RCL_Handler_Generic_updateRxStats(RCL_StatsGeneric *stats, uint32_t startTime);
static void RCL_Handler_Generic_updateLongStats(void);
static bool RCL_Handler_Generic_initRxStats(RCL_StatsGeneric *stats, uint32_t startTime);
static void RCL_Handler_Nesb_updateHeader(List_List *txBuffers, uint8_t autoRetransmitMode,
                                          uint8_t hdrConf, uint8_t seqNumber);
static void RCL_Handler_Nesb_updateStats(RCL_StatsNesb *stats, uint32_t startTime);
static void RCL_Handler_Nesb_updateLongStats(void);
static bool RCL_Handler_Nesb_initStats(RCL_StatsNesb *stats, uint32_t startTime);

/*
 *  ======== RCL_Handler_Generic_Fs ========
 */
RCL_Events RCL_Handler_Generic_Fs(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericFs *fsCmd = (RCL_CmdGenericFs *) cmd;
    RCL_Events rclEvents = {.value = 0U};

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        /* Program frequency word */
        LRF_programFrequency(fsCmd->rfFrequency, fsCmd->fsType == RCL_FsType_Tx);

        /* Enable radio */
        LRF_enable();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;
        /* Default end status */
        genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
        /* Configure LRF for running operation Fs */
        LRF_Interface_Generic_configOpFs();

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_Fs: Starting Frequency Synthesizer");
            LRF_waitForTopsmReady();
            LRF_Interface_Generic_sendOpFs();
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U)
        {
            cmd->status = genericHandlerState.common.endStatus;

            RCL_Handler_Generic_setSynthPowerState(false);

            /* Set additional power constraints if necessary */
            if(!genericHandlerState.common.powerStandbyConstraintSet)
            {
                genericHandlerState.common.powerStandbyConstraintSet = true;
                RCL_Hal_powerSetStandbyConstraint();
            }
            rclEvents.lastCmdDone = 1U;
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else
            {
                cmd->status = endStatus;
            }
            RCL_Handler_Generic_setSynthPowerState(true);
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_FsOff ========
 */
RCL_Events RCL_Handler_Generic_FsOff(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_Events rclEvents = {.value = 0U};

    if (rclEventsIn.setup != 0U)
    {
        /* Enable radio */
        LRF_enable();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setCmdStopTimeNoStartTrigger(cmd);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Configure LRF for running operation FsOff */
            LRF_Interface_Generic_configOpFsOff();

            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_FsOff: Turning off Frequency Synthesizer");
            LRF_waitForTopsmReady();
            LRF_Interface_Generic_sendOpFsOff();
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0U)
        {
            cmd->status = RCL_CommandStatus_Finished;
            RCL_Handler_Generic_setSynthPowerState(true);
            rclEvents.lastCmdDone = 1U;
        }
        else if (lrfEvents.opError != 0U)
        {
            cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_Tx ========
 */
RCL_Events RCL_Handler_Generic_Tx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTx *txCmd = (RCL_CmdGenericTx *) cmd;
    RCL_Events rclEvents = {.value = 0U};

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        if ((txCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Program the sync word provided in the RCL_CmdGenericTx radio command to the LRF */
            LRF_Interface_Generic_programSyncWordA(txCmd->syncWord);

            /* Configure LRF for running operation generix tx */
            LRF_Interface_Generic_configOpTx(txCmd->config.fsOff, txCmd->rfFrequency);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0U)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower, txCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1U;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize RF FIFO */
            genericHandlerState.common.txFifoSize = (uint16_t) LRF_prepareTxFifo();

            /* Enter payload */
            uint32_t nBuffer = RCL_Handler_Generic_updateTxBuffers(&txCmd->txBuffers, 1U);
            if (nBuffer == 0U)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1U;
            }
            else
            {
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1U;
                }
                else
                {
                    /* Enable interrupts */
                    LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                    /* Post cmd */
                    Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_Tx: Starting TX");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    LRF_Interface_Generic_sendOpTx();
                }
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U)
        {
            cmd->status = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1U;
            /* Pop transmitted packet */
            RCL_Buffer_TxBuffer *txBuffer;
            txBuffer = RCL_TxBuffer_get(&txCmd->txBuffers);
            if (txBuffer != NULL)
            {
                txBuffer->state = RCL_BufferStateFinished;
            }
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) txCmd->config.fsOff);
    }
    return rclEvents;
}

RCL_Events RCL_Handler_Generic_TxRepeat(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTxRepeat *txCmd = (RCL_CmdGenericTxRepeat *) cmd;
    RCL_Events rclEvents = {.value = 0U};
    bool runTx = false;

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        if ((txCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else if ((txCmd->rfFrequency == 0U) && (txCmd->config.fsRecal != 0U))
        {
            /* Synth not to be programmed, recalibration for each packet requested */
            cmd->status = RCL_CommandStatus_Error_Param;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {

            /* Program the sync word provided in the RCL_CmdGenericTx radio command to the LRF */
            LRF_Interface_Generic_programSyncWordA(txCmd->syncWord);

            /* Configure LRF for running operation generic tx repeat */
            LRF_Interface_Generic_configOpTxRepeat(txCmd->rfFrequency, txCmd->config.fsRecal);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
            genericHandlerState.tx.stopFs = false;
            genericHandlerState.tx.txCount = 0U;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0U)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower, txCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1U;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize RF FIFO */
            genericHandlerState.common.txFifoSize = (uint16_t) LRF_prepareTxFifo();

            /* Enter payload */
            if (txCmd->txEntry == NULL)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1U;
            }
            else
            {
                uint32_t length = txCmd->txEntry->length;
                /* Number of words including length field and end padding */
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(length) / 4U;
                if (wordLength > LRF_getTxFifoWritable() / 4U)
                {
                    /* Packet will not fit */
                    /* TODO: See RCL-348 */
                    cmd->status = RCL_CommandStatus_Error_Param;
                    rclEvents.lastCmdDone = 1U;
                }
                else
                {
                    LRF_writeTxFifoWords((uint32_t *) txCmd->txEntry, wordLength);

                    RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        cmd->status = startTimeStatus;
                        rclEvents.lastCmdDone = 1U;
                    }
                    else
                    {
                        genericHandlerState.tx.period = txCmd->timePeriod;

                        runTx = true; /* Go on */
                        genericHandlerState.tx.gracefulStopObserved = false;
                        if (rclSchedulerState.gracefulStopInfo.cmdStopEnabled || rclSchedulerState.gracefulStopInfo.schedStopEnabled)
                        {
                            /* Enable interrupt to service graceful stop */
                            RCL_Hal_enableGracefulStopTimeIrq();
                        }
                    }
                }
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.systim1 != 0U)
        {
            genericHandlerState.tx.gracefulStopObserved = true;
        }
        if (lrfEvents.opDone != 0U)
        {
            if (genericHandlerState.tx.stopFs)
            {
                runTx = false;
            }
            else
            {
                /* Retry TX FIFO */
                LRF_retryTxFifo();

                if (txCmd->numPackets == 0U || genericHandlerState.tx.txCount < txCmd->numPackets)
                {
                    /* Configure LRF for next tx operation if there are more packets to transmit */
                    LRF_Interface_Generic_configNextOpTx();

                    runTx = true;
                    if (rclEventsIn.hardStop != 0U)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
                        runTx = false;
                    }
                    else if (LRF_Interface_isCmdEndCauseEopStop() == true ||
                             genericHandlerState.tx.gracefulStopObserved ||
                             rclEventsIn.gracefulStop != 0U)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                        runTx = false;
                    }
                    else
                    {
                        RCL_CommandStatus startTimeStatus;
                        if (genericHandlerState.tx.period != 0U)
                        {
                            startTimeStatus = RCL_Scheduler_setNewStartRelTime(genericHandlerState.tx.period);
                        }
                        else
                        {
                            startTimeStatus = RCL_Scheduler_setNewStartNow();
                        }
                        if (startTimeStatus >= RCL_CommandStatus_Finished)
                        {
                            genericHandlerState.common.endStatus = startTimeStatus;
                            runTx = false;
                        }
                    }
                }
                else
                {
                    if (LRF_Interface_isCmdEndCauseEopStop() == true)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    }
                    runTx = false;
                }
            }
            if (!runTx && cmd->status == RCL_CommandStatus_Active)
            {
                if (!genericHandlerState.tx.stopFs && txCmd->config.fsRecal == 0U && txCmd->config.fsOff != 0U)
                {
                    /* Send stop FS */
                    LRF_waitForTopsmReady();
                    LRF_Interface_Generic_sendOpFsOff();
                    genericHandlerState.tx.stopFs = true;
                }
                else {
                    cmd->status = genericHandlerState.common.endStatus;
                    rclEvents.lastCmdDone = 1U;
                }
            }
        }
        else if (lrfEvents.opError != 0U)
        {
            if (genericHandlerState.common.endStatus == RCL_CommandStatus_Finished)
            {
                genericHandlerState.common.endStatus = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }

            if (!genericHandlerState.tx.stopFs && txCmd->config.fsRecal == 0U && txCmd->config.fsOff != 0U &&
                (LRF_Interface_Generic_isFreqSynthLocked() == true))
            {
                /* Synth was turned on, but should be off. Send stop FS */
                LRF_waitForTopsmReady();
                LRF_Interface_Generic_sendOpFsOff();
                genericHandlerState.tx.stopFs = true;
            }
            else
            {
                cmd->status = genericHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1U;
            }
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (runTx)
        {
            uint32_t txCount = genericHandlerState.tx.txCount;
            if (txCount != 0U && txCmd->config.fsRecal == 0U)
            {
                /* Frequency programming only for the first packet */
                LRF_Interface_Generic_skipFreqProgramming();
            }
            txCount++;
            if (txCount != 0U)
            {
                /* Avoid wraparound */
                genericHandlerState.tx.txCount = txCount;
            }
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_TxRepeat: Starting TX");
            LRF_waitForTopsmReady();
            LRF_Interface_Generic_sendOpTx();
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) txCmd->config.fsOff);
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_TxTest ========
 */
RCL_Events RCL_Handler_Generic_TxTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTxTest *txCmd = (RCL_CmdGenericTxTest *) cmd;
    RCL_Events rclEvents = { .value = 0U };

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();
        /* Reset whitening control state to avoid carryover from previous operations */
        genericHandlerState.txTest.modulationCtrl = (LRF_ModulationCtrl) { 0U };
        if ((txCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Cache tx word as it will be used multiple times */
            uint32_t txWord = txCmd->config.txWord;
            /* Configure the LRF for running operation Tx Test */
            LRF_Interface_Generic_configOpTxTest(txCmd->config.fsOff, txCmd->rfFrequency, txWord);

            /* LRF modulation mode is controlled differently based on the configuration per RCL_CmdGenericTxTest command */
            LRF_Interface_Generic_setModulationMode(txCmd->config.sendCw, txCmd->config.whitenMode, &(genericHandlerState.txTest.modulationCtrl));

            /* Program a sync word only when the radio is not sending a carrier wave */
            if (txCmd->config.sendCw == 0U)
            {
                if (txCmd->config.whitenMode == RCL_CMD_GENERIC_WH_MODE_NONE)
                {
                    /* Use pattern as sync word */
                    LRF_Interface_Generic_programSyncWordA(txWord | (txWord << 16U));
                }
                else
                {
                    /* Use pseudo-random sync word (not necessarily matching selected PRBS) */
                    LRF_Interface_programSyncWordA(LRF_INTERFACE_GENERIC_PRBS_SYNC);
                }
            }
            else
            {
                /* No sync word is needed for a carrier wave */
            }

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            if (LRF_programTxPower(txCmd->txPower, txCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1U;
            }

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1U;
            }
            else
            {
                if (txCmd->rfFrequency != 0U)
                {
                    /* Program frequency word */
                    LRF_programFrequency(txCmd->rfFrequency, true);
                }

                /* Enable interrupts */
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                /* Post cmd */
                Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_TxTest: Starting infinite TX");
                LRF_waitForTopsmReady();
                LRF_Interface_Generic_sendOpTx();
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U)
        {
            cmd->status = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1U;
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) txCmd->config.fsOff);
        LRF_Interface_Generic_restoreModulationMode(&(genericHandlerState.txTest.modulationCtrl));
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_Rx  ========
 */
RCL_Events RCL_Handler_Generic_Rx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericRx *rxCmd = (RCL_CmdGenericRx *) cmd;
    RCL_Events rclEvents = RCL_EventNone;
    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Reset sync search control state to avoid carryover from previous operations */
        genericHandlerState.rx.syncSearchCtrl = (LRF_SyncSearchCtrl) { 0U };

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        if ((rxCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Program sync words provided by the radio command to the LRF */
            LRF_Interface_Generic_programSyncWordA(rxCmd->syncWordA);
            LRF_Interface_Generic_programSyncWordB(rxCmd->syncWordB);

            /* Configure LRF for running operation generic rx */
            LRF_Interface_Generic_configOpRx(rxCmd->config.fsOff, rxCmd->rfFrequency, rxCmd->config.repeated, rxCmd->maxPktLen);

            /* Disable sync search for syncwordA and syncwordB if requested by the radio configuration */
            bool disableSyncA = (rxCmd->config.disableSyncA != 0U);
            bool disableSyncB = (rxCmd->config.disableSyncB != 0U);
            /* To avoid the overhead of calling functions by checking the parameters first */
            if (disableSyncA == true || disableSyncB == true)
            {
                LRF_Interface_Generic_disableSyncSearch(disableSyncA, disableSyncB, &(genericHandlerState.rx.syncSearchCtrl));
            }

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (rxCmd->rfFrequency != 0U)
            {
                LRF_programFrequency(rxCmd->rfFrequency, false);
            }

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1U;
            }
            else {
                genericHandlerState.common.activeUpdate = RCL_Handler_Generic_initRxStats(rxCmd->stats,
                                                                                          rclSchedulerState.actualStartTime);
                /* Set up sync found capture */
                RCL_Hal_setupSyncFoundCap();
                /* Initialize RF FIFOs */
                genericHandlerState.common.rxFifoSize = (uint16_t) LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;
                if (rxCmd->config.discardRxPackets == 0U)
                {
                    RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
                }
                else
                {
                    /* Set FIFO size to maximum */
                    LRF_setRxFifoEffSz(genericHandlerState.common.rxFifoSize);
                }

                /* Enable interrupts */
                uint16_t fifoCfg = LRF_Interface_Generic_getFifoCfg();
                LRF_enableHwInterrupt(LRF_Interface_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                 LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                                 LRF_EventRxBufFull.value,
                                                                                 fifoCfg,
                                                                                 genericHandlerState.common.activeUpdate));
                /* Post cmd */
                Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Generic_Rx: Starting Rx");
                LRF_waitForTopsmReady();
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                LRF_Interface_Generic_sendOpRx();
            }
        }
    }
    else
    {
        if (lrfEvents.rxOk != 0U || lrfEvents.rxNok != 0U || lrfEvents.rxBufFull != 0U)
        {
            /* Copy received packet from LRF FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (LRF_hasRxWordToRead() == true)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFFU) / 4U;
                if (wordLength > 0U)
                {
                    if (rxCmd->config.discardRxPackets == 0U)
                    {
                        RCL_MultiBuffer *curBuffer;
                        curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                            wordLength * 4U);
                        if (curBuffer != genericHandlerState.common.curBuffer)
                        {
                            rclEvents.rxBufferFinished = 1U;
                            genericHandlerState.common.curBuffer = curBuffer;
                        }
                        if (curBuffer == NULL)
                        {
                            /* Error */
                            genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                            /* Send abort */
                            LRF_Interface_Generic_sendOpStop();
                            /* Do not check for more packets from the RX FIFO */
                            break;
                        }
                        else
                        {
                            uint32_t *data32;
                            data32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                            LRF_readRxFifoWords(data32, wordLength);
                            RCL_MultiBuffer_commitBytes(curBuffer, wordLength * 4U);
                            /* Raise event */
                            rclEvents.rxEntryAvail = 1;
                            /* Adjust effective FIFO size */
                            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
                        }
                    }
                    else
                    {
                        LRF_discardRxFifoWords(wordLength);
                    }
                }
            }
            if (genericHandlerState.common.activeUpdate)
            {
                RCL_Handler_Generic_updateRxStats(rxCmd->stats, rclSchedulerState.actualStartTime);
            }
            else
            {
                RCL_Handler_Generic_updateLongStats();
            }
        }
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U || lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1U;
            if (lrfEvents.opError != 0U && endStatus == RCL_CommandStatus_Finished)
            {
                endStatus = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else if (LRF_Interface_isCmdEndCauseEopStop() == true)
            {
                endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
            }
            else
            {
                /* Nothing to do */
            }
            cmd->status = endStatus;
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.rxBufferUpdate != 0U)
        {
            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) rxCmd->config.fsOff);
        RCL_Handler_Generic_updateRxStats(rxCmd->stats, rclSchedulerState.actualStartTime);
        /* Restore sync search only if the sync search was disabled */
        LRF_Interface_Generic_restoreSyncSearch(&(genericHandlerState.rx.syncSearchCtrl));
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_LrfOperation ========
 */
RCL_Events RCL_Handler_Generic_LrfOperation(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_Events rclEvents = {.value = 0U};
    RCL_CmdGenericLrfOperation *lrfCmd = (RCL_CmdGenericLrfOperation *) cmd;

    if (cmd->status == RCL_CommandStatus_Scheduled)
    {
        /* Enable radio */
        LRF_enable();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setCmdStopTimeNoStartTrigger(cmd);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            LRF_waitForTopsmReady();
            LRF_Interface_sendOp(lrfCmd->lrfOperation);
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0U)
        {
            cmd->status = RCL_CommandStatus_Finished;
            rclEvents.lastCmdDone = 1U;
        }
        else if (lrfEvents.opError != 0U)
        {
            cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
    }
    return rclEvents;
}


/*
 *  ======== RCL_Handler_Nesb_Ptx ========
 */
RCL_Events RCL_Handler_Nesb_Ptx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdNesbPtx *txCmd = (RCL_CmdNesbPtx *) cmd;
    RCL_Events rclEvents = {.value = 0U};
    bool runTx = false;
    bool listenAck = false;
    uint32_t earliestStartTime = 0U;

    if (rclEventsIn.setup != 0U)
    {
        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        if ((txCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Program the sync word provided by the radio command to the LRF */
            LRF_Interface_Generic_programSyncWordA(txCmd->syncWord);
            LRF_Interface_Generic_programSyncWordB(txCmd->syncWord);

            /* Configure the LRF for running operation NESB ptx */
            LRF_Interface_Generic_configOpNesbPtx(txCmd->config.fsOff, txCmd->rfFrequency, txCmd->config.autoRetransmitMode);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;

            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
            genericHandlerState.tx.txCount = 0U;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0U)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower, txCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1U;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize Tx FIFO */
            genericHandlerState.common.txFifoSize = (uint16_t) LRF_prepareTxFifo();

            /* Enter header and get ACK configuration */
            RCL_Handler_Nesb_updateHeader(&txCmd->txBuffers,
                                          txCmd->config.autoRetransmitMode,
                                          txCmd->config.hdrConf,
                                          txCmd->seqNo);

            /* Configure Rx if necessary */
            if (LRF_Interface_Generic_shouldNesbListenForAck(txCmd->config.autoRetransmitMode) == true)
            {
                /* Initialize Rx FIFO */
                genericHandlerState.common.rxFifoSize = (uint16_t) LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;

                /* Request notification on RX buffer updates */
                RCL_Handler_Generic_updateRxCurBufferAndFifo(&txCmd->rxBuffers);
                listenAck = true;
            }

            /* Enter payload */
            uint32_t nBuffer = RCL_Handler_Generic_updateTxBuffers(&txCmd->txBuffers, 1U);
            if (nBuffer == 0U)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1U;
            }
            else
            {
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1U;
                }
                else
                {
                    genericHandlerState.common.activeUpdate = RCL_Handler_Nesb_initStats(txCmd->stats,
                                                            rclSchedulerState.actualStartTime);
                    runTx = true;
                }
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        /* We only get an Rx LRF event if an Acknowledge is expected */
        if (lrfEvents.rxOk != 0U || lrfEvents.rxNok != 0U || lrfEvents.rxIgnored != 0U || lrfEvents.rxBufFull != 0U)
        {
            /* Copy received packet from LRF FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (LRF_hasRxWordToRead() == true)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t numWords = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFFU) / sizeof(uint32_t);
                if (numWords > 0U)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                          numWords * sizeof(uint32_t));

                    if (curBuffer != genericHandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1U;
                        genericHandlerState.common.curBuffer = curBuffer;
                    }

                    if (curBuffer == NULL)
                    {
                        /* Error */
                        genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        LRF_Interface_Generic_sendOpStop();
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *buffer32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(buffer32, numWords);
                        RCL_MultiBuffer_commitBytes(curBuffer, numWords * sizeof(uint32_t));
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1U;
                        /* Adjust effective FIFO size */
                        RCL_Handler_Generic_updateRxCurBufferAndFifo(&txCmd->rxBuffers);
                    }
                }
            }
            if (genericHandlerState.common.activeUpdate)
            {
                RCL_Handler_Nesb_updateStats(txCmd->stats, rclSchedulerState.actualStartTime);
            }
            else
            {
                RCL_Handler_Nesb_updateLongStats();
            }
        }
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U)
        {
            /* Retry TX FIFO */
            LRF_retryTxFifo();

            uint16_t lrfCmdEndCause = LRF_Interface_getCmdEndCause();
            if (LRF_Interface_isCmdEndCauseEndOk(lrfCmdEndCause) == true)
            {
                /* Increment the sequence number for next packet */
                txCmd->seqNo = (txCmd->seqNo + 1U) % 4U;

                cmd->status = genericHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1U;

                /* Pop transmitted packet */
                RCL_Buffer_TxBuffer *txBuffer;
                txBuffer = RCL_TxBuffer_get(&txCmd->txBuffers);
                if (txBuffer != NULL)
                {
                    txBuffer->state = RCL_BufferStateFinished;
                    runTx = false;
                }
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
            }
            /* Handle missed ACKs or ACKs with the wrong address */
            else if (LRF_Interface_isCmdEndCauseEndedWithoutSync(lrfCmdEndCause) == true)
            {
                /* Configure LRF for next tx operation to retransmit the packet */
                LRF_Interface_Generic_configNextOpTx();

                /* Attempt to retransmit the packet */
                if (genericHandlerState.tx.txCount <= txCmd->maxRetrans)
                {
                    Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Nesb_Ptx: PTX needs to retransmit");

                    /* Set a new transmit time according to retransDelay. If unattainable, retransmit as soon as possible */
                    RCL_CommandStatus startTimeStatus = RCL_Scheduler_setNewStartRelTime(txCmd->retransDelay);
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        Log_printf(LogModule_RCL, Log_WARNING, "RCL_Handler_Nesb_Ptx: Unattainable retranmission delay. Retransmitting as soon as possible");
                        (void) RCL_Scheduler_setNewStartNow();
                    }
                    runTx = true;
                }
                else /* Finish the command without incrementing the sequence number */
                {
                    genericHandlerState.common.endStatus = RCL_CommandStatus_NoSync;
                    cmd->status = genericHandlerState.common.endStatus;
                    rclEvents.lastCmdDone = 1U;
                    runTx = false;
                }
            }
            else
            {
                /* Nothing to do */
            }
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;

            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1U;
            runTx = false;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
        if (runTx)
        {
            uint32_t txCount = genericHandlerState.tx.txCount;
            txCount++;
            if (txCount != 0U)
            {
                /* Avoid wraparound */
                genericHandlerState.tx.txCount = txCount;
            }
            /* Set up sync found capture */
            RCL_Hal_setupSyncFoundCap();
            /* Enable interrupts */
            if (listenAck)
            {
                uint16_t fifoCfg = LRF_Interface_Generic_getFifoCfg();
                LRF_enableHwInterrupt(LRF_Interface_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                 LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                                 LRF_EventRxIgnored.value | LRF_EventRxBufFull.value,
                                                                                 fifoCfg,
                                                                                 genericHandlerState.common.activeUpdate));
            }
            else
            {
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
            }
            /* Post cmd */
            Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Nesb_Ptx: Start of PTX operation");
            LRF_waitForTopsmReady();
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
            LRF_Interface_Generic_sendOpTx();
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) txCmd->config.fsOff);
        RCL_Handler_Nesb_updateStats(txCmd->stats, rclSchedulerState.actualStartTime);
    }
    return rclEvents;
}


/*
 *  ======== RCL_Handler_Nesb_Prx  ========
 */
RCL_Events RCL_Handler_Nesb_Prx(RCL_Command *cmd, LRF_Events lrfEvents,  RCL_Events rclEventsIn)
{
    RCL_CmdNesbPrx *rxCmd = (RCL_CmdNesbPrx *) cmd;
    RCL_Events rclEvents = RCL_EventNone;

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = RCL_Handler_Generic_prepareSynth();

        /* Reset sync search control state in case the RF frequency was 0 without the synth running */
        genericHandlerState.nesb.syncSearchCtrl = (LRF_SyncSearchCtrl) { 0U };

        if ((rxCmd->rfFrequency == 0U) && (LRF_Interface_Generic_isFreqSynthLocked() == false))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1U;
        }
        else
        {
            /* Program sync words provided by the radio command to the LRF */
            LRF_Interface_Generic_programSyncWordA(rxCmd->syncWordA);
            LRF_Interface_Generic_programSyncWordB(rxCmd->syncWordB);

            uint16_t lrfOpCfg = LRF_Interface_Generic_getOpCfgNesbPrx(rxCmd->config.fsOff,
                                                                      rxCmd->rfFrequency,
                                                                      rxCmd->config.repeatNok,
                                                                      rxCmd->config.repeatOk);
            /* NOTE: rxCmd->syncWord is an array containing two sync word configurations, i.e. RCL_ConfigAddress */
            LRF_Interface_Generic_configOpNesbPrx(lrfOpCfg, rxCmd->addrLen, rxCmd->syncWord);

            /* Disable sync search for syncwordA and syncwordB if requested by the radio configuration */
            bool disableSyncA = (rxCmd->config.disableSyncA != 0U);
            bool disableSyncB = (rxCmd->config.disableSyncB != 0U);
            /* To avoid the overhead of calling functions by checking the parameters first */
            if (disableSyncA == true || disableSyncB == true)
            {
                LRF_Interface_Generic_disableSyncSearch(disableSyncA, disableSyncB, &(genericHandlerState.nesb.syncSearchCtrl));
            }

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (rxCmd->rfFrequency != 0U)
            {
                LRF_programFrequency(rxCmd->rfFrequency, false);
            }
            if (LRF_programTxPower(rxCmd->txPower, rxCmd->rfFrequency) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1U;
            }

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1U;
            }
            else
            {
                genericHandlerState.common.activeUpdate = RCL_Handler_Nesb_initStats(rxCmd->stats,
                                                                                     rclSchedulerState.actualStartTime);

                /* Set up sync found capture */
                RCL_Hal_setupSyncFoundCap();
                /* Initialize Rx FIFO */
                genericHandlerState.common.rxFifoSize = (uint16_t) LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;

                if (rxCmd->config.discardRxPackets == 0U)
                {
                    RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
                }
                else
                {
                    /* Set FIFO size to maximum */
                    LRF_setRxFifoEffSz(genericHandlerState.common.rxFifoSize);
                }

                /* If an ACK is required, prepare Tx FIFOs */
                if ((rxCmd->syncWord[0].autoAckMode != 0U) || (rxCmd->syncWord[1].autoAckMode != 0U))
                {
                    genericHandlerState.common.txFifoSize = (uint16_t) LRF_prepareTxFifo();
                }

                /* Enable interrupts */
                uint16_t fifoCfg = LRF_Interface_Generic_getFifoCfg();
                LRF_enableHwInterrupt(LRF_Interface_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                                 LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                                 LRF_EventRxIgnored.value | LRF_EventRxBufFull.value,
                                                                                 fifoCfg,
                                                                                 genericHandlerState.common.activeUpdate));

                /* Post cmd */
                Log_printf(LogModule_RCL, Log_INFO, "RCL_Handler_Nesb_Prx: Starting of PRX operation");
                LRF_waitForTopsmReady();
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                LRF_Interface_Generic_sendOpRx();
            }
        }
    }
    else
    {
        if (lrfEvents.rxOk != 0U || lrfEvents.rxNok != 0U || lrfEvents.rxIgnored != 0U || lrfEvents.rxBufFull != 0U)
        {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            if (rclFeatureControl.enablePaEsdProtection)
            {
                LRF_updatePaEsdProtection();
            }
#endif
            /* Copy received packet from LRF FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (LRF_hasRxWordToRead() == true)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t numWords = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFFU) / sizeof(uint32_t);
                if (numWords > 0U)
                {
                    if (rxCmd->config.discardRxPackets == 0U)
                    {
                        RCL_MultiBuffer *curBuffer;
                        curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                              numWords * 4U);
                        if (curBuffer != genericHandlerState.common.curBuffer)
                        {
                            rclEvents.rxBufferFinished = 1U;
                            genericHandlerState.common.curBuffer = curBuffer;
                        }
                        if (curBuffer == NULL)
                        {
                            /* Error */
                            genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                            /* Send abort */
                            LRF_Interface_Generic_sendOpStop();
                            /* Do not check for more packets from the RX FIFO */
                            break;
                        }
                        else
                        {
                            uint32_t *buffer32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                            LRF_readRxFifoWords(buffer32, numWords);
                            RCL_MultiBuffer_commitBytes(curBuffer, numWords * sizeof(uint32_t));
                            /* Raise event */
                            rclEvents.rxEntryAvail = 1U;
                            /* Adjust effective FIFO size */
                            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);

                            /* NOTE: rxCmd->syncWord is an array containing two sync word configurations,
                               i.e. RCL_ConfigAddress */
                            LRF_Interface_Generic_updateSyncWordCfg(rxCmd->syncWord);
                        }
                    }
                    else
                    {
                        LRF_discardRxFifoWords(numWords);
                    }
                }
            }
            if (genericHandlerState.common.activeUpdate)
            {
                RCL_Handler_Nesb_updateStats(rxCmd->stats, rclSchedulerState.actualStartTime);
            }
            else
            {
                RCL_Handler_Nesb_updateLongStats();
            }
        }
        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1U;
        }
        if (lrfEvents.opDone != 0U || lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;

            rclEvents.lastCmdDone = 1U;
            if (lrfEvents.opError != 0U && endStatus == RCL_CommandStatus_Finished)
            {
                endStatus = RCL_Handler_Generic_mapLrfErrorStatusToRclStatus();
            }
            else if (LRF_Interface_isCmdEndCauseEopStop() == true)
            {
                endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
            }
            else
            {
                /* Nothing to do */
            }
            cmd->status = endStatus;
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }
    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.rxBufferUpdate != 0U)
        {
            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
        }
    }
    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState((bool) rxCmd->config.fsOff);
        RCL_Handler_Nesb_updateStats(rxCmd->stats, rclSchedulerState.actualStartTime);
        /* Restore sync search only if the sync search was disabled */
        LRF_Interface_Generic_restoreSyncSearch(&(genericHandlerState.nesb.syncSearchCtrl));
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_prepareSynth ========
 */
static uint32_t RCL_Handler_Generic_prepareSynth(void)
{
    /* Power up synth refsys and set a constraint on swtcxo to ensure it is not changed while radio is running */
    if (!genericHandlerState.common.powerSwtcxoConstraintSet)
    {
        genericHandlerState.common.powerSwtcxoConstraintSet = true;
        RCL_Hal_powerSetSwTcxoUpdateConstraint();
    }
    return LRF_enableSynthRefsys();
}

/*
 *  ======== RCL_Handler_Generic_setSynthPowerState ========
 */
static void RCL_Handler_Generic_setSynthPowerState(bool fsOff)
{
    /* Do power management for synth at the end of a command.
       If synth is off, turn off refsys and remove constraint on standby and swtcxo.
       If synth is on, keep refsys on and ensure constraint on standby is set */
    if (fsOff)
    {
        LRF_disableSynthRefsys();
        /* Release additional power standby constraints if necessary */
        if (genericHandlerState.common.powerStandbyConstraintSet)
        {
            genericHandlerState.common.powerStandbyConstraintSet = false;
            RCL_Hal_powerReleaseStandbyConstraint();
        }
        /* Release power SWTCXO constraints if necessary */
        if (genericHandlerState.common.powerSwtcxoConstraintSet)
        {
            genericHandlerState.common.powerSwtcxoConstraintSet = false;
            RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
        }
    }
    else
    {
        /* Set additional power constraints if necessary */
        if (!genericHandlerState.common.powerStandbyConstraintSet)
        {
            genericHandlerState.common.powerStandbyConstraintSet = true;
            RCL_Hal_powerSetStandbyConstraint();
        }
    }
}

/*
 *  ======== RCL_Handler_Generic_updateRxCurBufferAndFifo ========
 */
static void RCL_Handler_Generic_updateRxCurBufferAndFifo(List_List *rxBuffers)
{
    RCL_MultiBuffer *curBuffer = genericHandlerState.common.curBuffer;

    if (curBuffer == NULL)
    {
        curBuffer = RCL_MultiBuffer_findFirstWritableBuffer((RCL_MultiBuffer *)rxBuffers->head);
    }
    genericHandlerState.common.curBuffer = curBuffer;

    uint32_t rxSpace = RCL_MultiBuffer_findAvailableRxSpace(curBuffer);

    LRF_setRxFifoEffSz(rxSpace);
}

/*
 *  ======== RCL_Handler_Generic_mapLrfErrorStatusToRclStatus ========
 */
static RCL_CommandStatus RCL_Handler_Generic_mapLrfErrorStatusToRclStatus(void)
{
    /* Get LRF command end cause */
    uint16_t lrfCmdEndCause = LRF_Interface_getCmdEndCause();

    /* Map LRF command end cause to corresponding RCL command status */
    RCL_CommandStatus status;
    switch (lrfCmdEndCause)
    {
    case LRF_INTERFACE_ENDCAUSE_STAT_ERR_RXF:
        status = RCL_CommandStatus_Error_RxFifo;
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_ERR_TXF:
        status = RCL_CommandStatus_Error_TxFifo;
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_ERR_SYNTH:
        status = RCL_CommandStatus_Error_Synth;
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_RXTIMEOUT:
        status = RCL_CommandStatus_RxTimeout;
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_EOPSTOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_ERR_STOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        break;
    case LRF_INTERFACE_ENDCAUSE_STAT_ERR_BADOP:
        status = RCL_CommandStatus_Error_UnknownOp;
        break;
    default:
        Log_printf(LogModule_RCL, Log_ERROR, "RCL_Handler_Generic_mapLrfErrorStatusToRclStatus: Unexpected error 0x%04X from LRF", lrfCmdEndCause);
        status = RCL_CommandStatus_Error;
        break;
    }

    return status;
}

/*
 *  ======== RCL_Handler_Generic_updateTxBuffers ========
 */
static uint32_t RCL_Handler_Generic_updateTxBuffers(List_List *txBuffers,
                                                    uint32_t maxBuffers)
{
    uint32_t nBuffers = 0;
    RCL_Buffer_TxBuffer *nextTxBuffer;

    nextTxBuffer = RCL_TxBuffer_head(txBuffers);

    while (nextTxBuffer != NULL && nBuffers < maxBuffers)
    {
        uint32_t length = nextTxBuffer->length;
        /* Number of words including length field and end padding */
        uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(length) / 4U;

        if (wordLength > LRF_getTxFifoWritable() / 4U)
        {
            /* Packet will not fit */
            /* TODO: See RCL-348 */
            break;
        }
        nextTxBuffer->state = RCL_BufferStateInUse;
        uint32_t *data32 = (uint32_t *) &(nextTxBuffer->length);

        /* Copy packet into FIFO */
        LRF_writeTxFifoWords(data32, wordLength);
        nextTxBuffer = RCL_TxBuffer_next(nextTxBuffer);

        nBuffers++;
    }

    return nBuffers;
}

/*
 *  ======== RCL_Handler_Generic_updateRxStats ========
 */
static void RCL_Handler_Generic_updateRxStats(RCL_StatsGeneric *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        uint32_t lastTimestamp = LRF_Interface_Generic_getLastPacketTimestamp();
        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = 0U;
        }
        else {
            stats->timestampValid = 1U;
            stats->lastTimestamp = lastTimestamp;
        }
        stats->lastRssi = LRF_Interface_Generic_getLastPacketRssi();
        RCL_Handler_Generic_updateLongStats();
        stats->nRxNok = genericHandlerState.rx.longNokCount;
        stats->nRxOk = genericHandlerState.rx.longOkCount;
    }
}

/*
 *  ======== RCL_Handler_Generic_updateLongStats ========
 */
static void RCL_Handler_Generic_updateLongStats(void)
{
    uint32_t oldRxOk = genericHandlerState.rx.longOkCount;
    uint32_t oldRxNok = genericHandlerState.rx.longNokCount;
    uint32_t newRxOk = (oldRxOk & ~0xFFFFU) | LRF_Interface_Generic_getNumOfRxOkPackets();
    uint32_t newRxNok = (oldRxNok & ~0xFFFFU) | LRF_Interface_Generic_getNumOfNotRxOkPackets();

    if (newRxOk < oldRxOk)
    {
        newRxOk += 0x10000U;
    }
    if (newRxNok < oldRxNok)
    {
        newRxNok += 0x10000U;
    }
    genericHandlerState.rx.longOkCount = newRxOk;
    genericHandlerState.rx.longNokCount = newRxNok;
}

/*
 *  ======== RCL_Handler_Generic_initRxStats ========
 */
static bool RCL_Handler_Generic_initRxStats(RCL_StatsGeneric *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        LRF_Interface_Generic_setLastPacketTimestamp(startTime);
        stats->timestampValid = 0U;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0U)
        {
            /* Copy existing values into LRF */
            genericHandlerState.rx.longNokCount = stats->nRxNok;
            LRF_Interface_Generic_setNumOfNotRxOkPackets((uint16_t) stats->nRxNok & 0xFFFFU);
            genericHandlerState.rx.longOkCount = stats->nRxOk;
            LRF_Interface_Generic_setNumOfRxOkPackets((uint16_t) stats->nRxOk & 0xFFFFU);
        }
        else
        {
            /* Reset existing values in LRF */
            genericHandlerState.rx.longNokCount = 0U;
            LRF_Interface_Generic_setNumOfNotRxOkPackets(0U);
            genericHandlerState.rx.longOkCount = 0U;
            LRF_Interface_Generic_setNumOfRxOkPackets(0U);

            stats->nRxNok = 0U;
            stats->nRxOk = 0U;
        }
        return (bool) stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in LRF */
        genericHandlerState.rx.longNokCount = 0U;
        LRF_Interface_Generic_setNumOfNotRxOkPackets(0U);
        genericHandlerState.rx.longOkCount = 0U;
        LRF_Interface_Generic_setNumOfRxOkPackets(0U);

        return false;
    }
}

/*
 *  ======== RCL_Handler_Nesb_updateHeader ========
 */
static void RCL_Handler_Nesb_updateHeader(List_List *txBuffers, uint8_t autoRetransmitMode,
                                          uint8_t hdrConf, uint8_t seqNumber)
{
    uint8_t noAck;
    uint8_t seqNo;

    RCL_Buffer_TxBuffer *nextTxBuffer;
    nextTxBuffer = RCL_TxBuffer_head(txBuffers);
    uint8_t indexHeader = nextTxBuffer->numPad - 1U;

    if (hdrConf == 0U)
    {
        /* Insert NO_ACK field from TX buffer. */
        noAck = nextTxBuffer->data[indexHeader] & 0x01U;
        seqNo = seqNumber;
    }
    else
    {
        /* Insert SEQ and NO_ACK field from TX buffer. */
        noAck = nextTxBuffer->data[indexHeader] & 0x01U;
        seqNo = (nextTxBuffer->data[indexHeader] >> 1) & 0x03U;
    }

    /* Update header */
    nextTxBuffer->data[indexHeader] = ((nextTxBuffer->data[indexHeader] & 0xF8U) | ((seqNo & 0x03U) << 1) | noAck);
}

/*
 *  ======== RCL_Handler_Nesb_updateStats ========
 */
static void RCL_Handler_Nesb_updateStats(RCL_StatsNesb *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        uint32_t lastTimestamp = LRF_Interface_Generic_getLastPacketTimestamp();
        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = 0U;
        }
        else {
            stats->timestampValid = 1U;
            stats->lastTimestamp = lastTimestamp;
        }
        stats->lastRssi = LRF_Interface_Generic_getLastPacketRssi();
        RCL_Handler_Nesb_updateLongStats();
        stats->nTx = genericHandlerState.nesb.longTxCount;
        stats->nRxOk = genericHandlerState.nesb.longOkCount;
        stats->nRxNok = genericHandlerState.nesb.longNokCount;
        stats->nRxIgnored = genericHandlerState.nesb.longRxIgnoredCount;
        stats->nRxAddrMismatch = genericHandlerState.nesb.longRxAddrMismatchCount;
        stats->nRxBufFull = genericHandlerState.nesb.longRxBufFullCount;
    }
}

/*
 *  ======== RCL_Handler_Nesb_updateLongStats ========
 */
static void RCL_Handler_Nesb_updateLongStats(void)
{
    uint32_t oldTx = genericHandlerState.nesb.longTxCount;
    uint32_t oldRxOk = genericHandlerState.nesb.longOkCount;
    uint32_t oldRxNok = genericHandlerState.nesb.longNokCount;
    /* TODO: RCL-308: Long counters should not be needed for anything except RX Ok and CRC error */
    uint32_t oldRxIgnored = genericHandlerState.nesb.longRxIgnoredCount;
    uint32_t oldRxAddrMismatch = genericHandlerState.nesb.longRxAddrMismatchCount;
    uint32_t oldRxBufFull = genericHandlerState.nesb.longRxBufFullCount;

    uint32_t newTx = (oldTx & ~0xFFFFU) | LRF_Interface_Generic_getNumOfTxPackets();
    uint32_t newRxOk = (oldRxOk & ~0xFFFFU) | LRF_Interface_Generic_getNumOfRxOkPackets();
    uint32_t newRxNok = (oldRxNok & ~0xFFFFU) | LRF_Interface_Generic_getNumOfNotRxOkPackets();
    uint32_t newRxIgnored = (oldRxIgnored & ~0xFFFFU) | LRF_Interface_Generic_getNumOfIgnoredRxPackets();
    /* TODO: See RCL-343 */
    uint32_t newRxAddrMismatch = (oldRxAddrMismatch & ~0xFFFFU) | LRF_Interface_Generic_getNumOfIgnoredRxPackets();
    uint32_t newRxBufFull = (oldRxBufFull & ~0xFFFFU) | LRF_Interface_Generic_getRxFifoFullCount();

    if (newTx < oldTx)
    {
        newTx += 0x10000U;
    }
    if (newRxOk < oldRxOk)
    {
        newRxOk += 0x10000U;
    }
    if (newRxNok < oldRxNok)
    {
        newRxNok += 0x10000U;
    }
    if (newRxIgnored < oldRxIgnored)
    {
        newRxIgnored += 0x10000U;
    }
    if (newRxAddrMismatch < oldRxAddrMismatch)
    {
        newRxAddrMismatch += 0x10000U;
    }
    if (newRxBufFull < oldRxBufFull)
    {
        newRxBufFull += 0x10000U;
    }
    genericHandlerState.nesb.longTxCount = newTx;
    genericHandlerState.nesb.longOkCount = newRxOk;
    genericHandlerState.nesb.longNokCount = newRxNok;
    genericHandlerState.nesb.longRxIgnoredCount = newRxIgnored;
    genericHandlerState.nesb.longRxAddrMismatchCount = newRxAddrMismatch;
    genericHandlerState.nesb.longRxBufFullCount = newRxBufFull;
}

/*
 *  ======== RCL_Handler_Nesb_initStats ========
 */
static bool RCL_Handler_Nesb_initStats(RCL_StatsNesb *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        /* Set timestamp to start time of command (will not occur again) to know if a valid value has been found */
        LRF_Interface_Generic_setLastPacketTimestamp(startTime);
        stats->timestampValid = 0U;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0U)
        {
            /* Copy existing values into LRF */
            genericHandlerState.nesb.longTxCount = stats->nTx;
            LRF_Interface_Generic_setNumOfTxPackets((uint16_t) stats->nRxOk & 0xFFFFU);
            genericHandlerState.nesb.longOkCount = stats->nRxOk;
            LRF_Interface_Generic_setNumOfRxOkPackets((uint16_t) stats->nRxOk & 0xFFFFU);
            genericHandlerState.nesb.longNokCount = stats->nRxNok;
            LRF_Interface_Generic_setNumOfNotRxOkPackets((uint16_t) stats->nRxNok & 0xFFFFU);
            genericHandlerState.nesb.longRxIgnoredCount = stats->nRxIgnored;
            LRF_Interface_Generic_setNumOfIgnoredRxPackets((uint16_t) stats->nRxIgnored & 0xFFFFU);
            genericHandlerState.nesb.longRxAddrMismatchCount = stats->nRxAddrMismatch;
            LRF_Interface_Generic_setNumOfIgnoredRxPackets((uint16_t) stats->nRxAddrMismatch & 0xFFFFU);
            genericHandlerState.nesb.longRxBufFullCount = stats->nRxBufFull;
            LRF_Interface_Generic_setRxFifoFullCount((uint16_t) stats->nRxBufFull & 0xFFFFU);
        }
        else
        {
            /* Reset existing values in LRF */
            genericHandlerState.nesb.longTxCount = 0U;
            LRF_Interface_Generic_setNumOfTxPackets(0U);
            genericHandlerState.nesb.longOkCount = 0U;
            LRF_Interface_Generic_setNumOfRxOkPackets(0U);
            genericHandlerState.nesb.longNokCount = 0U;
            LRF_Interface_Generic_setNumOfNotRxOkPackets(0U);
            genericHandlerState.nesb.longRxIgnoredCount = 0U;
            LRF_Interface_Generic_setNumOfIgnoredRxPackets(0U);
            genericHandlerState.nesb.longRxAddrMismatchCount = 0U;
            LRF_Interface_Generic_setNumOfIgnoredRxPackets(0U);
            genericHandlerState.nesb.longRxBufFullCount = 0U;
            LRF_Interface_Generic_setRxFifoFullCount(0U);

            stats->nTx = 0U;
            stats->nRxOk = 0U;
            stats->nRxNok = 0U;
            stats->nRxIgnored = 0U;
            stats->nRxAddrMismatch = 0U;
            stats->nRxBufFull = 0U;
        }
        return (bool) stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in LRF */
        genericHandlerState.nesb.longTxCount = 0U;
        LRF_Interface_Generic_setNumOfTxPackets(0U);
        genericHandlerState.nesb.longOkCount = 0U;
        LRF_Interface_Generic_setNumOfRxOkPackets(0U);
        genericHandlerState.nesb.longNokCount = 0U;
        LRF_Interface_Generic_setNumOfNotRxOkPackets(0U);
        genericHandlerState.nesb.longRxIgnoredCount = 0U;
        LRF_Interface_Generic_setNumOfIgnoredRxPackets(0U);
        genericHandlerState.nesb.longRxAddrMismatchCount = 0U;
        LRF_Interface_Generic_setNumOfIgnoredRxPackets(0U);
        genericHandlerState.nesb.longRxBufFullCount = 0U;
        LRF_Interface_Generic_setRxFifoFullCount(0U);

        return false;
    }
}
