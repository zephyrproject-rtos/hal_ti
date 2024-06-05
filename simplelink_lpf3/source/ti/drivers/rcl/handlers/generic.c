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
 *  ======== generic.c ========
 */

#include <stdint.h>
#include <stdlib.h>

#include <ti/log/Log.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Profiling.h>

#include <ti/drivers/rcl/hal/hal.h>
#include <ti/drivers/rcl/commands/generic.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdtxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)

/** Polynomial to use for PRBS15 data */
#define RCL_HANDLER_GENERIC_PRBS15_POLY            0x80020000
/** Polynomial to use for PRBS32 data */
#define RCL_HANDLER_GENERIC_PRBS32_POLY            0x00400007
#define RCL_HANDLER_GENERIC_PRBS_INIT              0x00005555
#define RCL_HANDLER_GENERIC_PRBS_SYNC              0xAB05FA1C

#define RCL_HANDLER_GENERIC_RESTORE_NONE           0x0000
#define RCL_HANDLER_GENERIC_RESTORE_MODCTRL        0x0001
#define RCL_HANDLER_GENERIC_RESTORE_WHITEN_INIT    0x0002
#define RCL_HANDLER_GENERIC_RESTORE_WHITEN_POLY    0x0004


struct
{
    struct {
        uint16_t            txFifoSize;
        uint16_t            rxFifoSize;
        RCL_CommandStatus   endStatus;
        bool                activeUpdate;
        bool                powerConstraintsSet;
        RCL_MultiBuffer     *curBuffer;
    } common;
    union {
        struct {
            bool            gracefulStopObserved;
            bool            stopFs;
            uint32_t        txCount;
            uint32_t        period;
        } tx;
        struct {
            uint16_t        restoreOpt;
            uint16_t        storedWhitenInit;
            uint32_t        storedWhitenPoly;
        } txTest;
        struct {
            uint32_t        longOkCount;
            uint32_t        longNokCount;
            uint16_t        demc1be1;
            uint16_t        demc1be2;
#ifdef DeviceFamily_CC27XX
            uint16_t        demc1be12;
#endif
            bool            restoreThresh;
        } rx;
        struct {
            uint32_t        longTxCount;
            uint32_t        longOkCount;
            uint32_t        longNokCount;
            uint32_t        longRxIgnoredCount;
            uint32_t        longRxAddrMismatchCount;
            uint32_t        longRxBufFullCount;
        } nesb;
    };
} genericHandlerState;


static void RCL_Handler_Generic_setSynthPowerState(bool fsOff);
static void RCL_Handler_Generic_updateRxCurBufferAndFifo(List_List *rxBuffers);
static RCL_CommandStatus RCL_Handler_Generic_findPbeErrorEndStatus(uint16_t pbeEndStatus);
static uint32_t RCL_Handler_Generic_updateTxBuffers(List_List *txBuffers, uint32_t maxBuffers);
static uint32_t RCL_Handler_Generic_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate);
static void RCL_Handler_Generic_updateRxStats(RCL_StatsGeneric *stats, uint32_t startTime);
static void RCL_Handler_Generic_updateLongStats(void);
static bool RCL_Handler_Generic_initRxStats(RCL_StatsGeneric *stats, uint32_t startTime);
static uint32_t RCL_Handler_Generic_updateSyncWord(uint32_t syncWord);
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
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        /* Program frequency word */
        LRF_programFrequency(fsCmd->rfFrequency, fsCmd->fsType == RCL_FsType_Tx);

        /* Enable radio */
        LRF_enable();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;
        /* Default end status */
        genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = 0 << PBE_GENERIC_RAM_OPCFG_START_S;

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(RclCore, Log_VERBOSE, "Starting FS");
            LRF_waitForTopsmReady();
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_FS;
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
            cmd->status = genericHandlerState.common.endStatus;

            RCL_Handler_Generic_setSynthPowerState(false);

            /* Set additional power constraints if necessary */
            if(!genericHandlerState.common.powerConstraintsSet)
            {
                genericHandlerState.common.powerConstraintsSet = true;
                hal_power_set_constraint();
            }
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            RCL_Handler_Generic_setSynthPowerState(true);
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
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_FsOff ========
 */
RCL_Events RCL_Handler_Generic_FsOff(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        /* Enable radio */
        LRF_enable();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setCmdStopTimeNoStartTrigger(cmd);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = 0;

            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(RclCore, Log_VERBOSE, "Turning off FS");
            LRF_waitForTopsmReady();
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOPFS;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0)
        {
            cmd->status = RCL_CommandStatus_Finished;
            RCL_Handler_Generic_setSynthPowerState(true);
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
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
    }
    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_Tx ========
 */
RCL_Events RCL_Handler_Generic_Tx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTx *txCmd = (RCL_CmdGenericTx *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if ((txCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(txCmd->syncWord);
            uint32_t opCfgVal =
                (0 << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S) |
                (2 << PBE_GENERIC_RAM_OPCFG_TXFCMD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_START_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_NEXTOP_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_SINGLE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);

            if (txCmd->config.fsOff != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            if (txCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = (PBE_GENERIC_RAM_NESB_NESBMODE_OFF);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize RF FIFO */
            genericHandlerState.common.txFifoSize = LRF_prepareTxFifo();

            /* Enter payload */
            uint32_t nBuffer = RCL_Handler_Generic_updateTxBuffers(&txCmd->txBuffers, 1);
            if (nBuffer == 0)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
                }
                else
                {
                    /* Enable interrupts */
                    LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                    /* Post cmd */
                    Log_printf(RclCore, Log_VERBOSE, "Starting TX");
                    LRF_waitForTopsmReady();
                    RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_TX;
                }
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
            cmd->status = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
            /* Pop transmitted packet */
            RCL_Buffer_TxBuffer *txBuffer;
            txBuffer = RCL_TxBuffer_get(&txCmd->txBuffers);
            if (txBuffer != NULL)
            {
                txBuffer->state = RCL_BufferStateFinished;
            }
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PostprocStart);
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
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
        RCL_Handler_Generic_setSynthPowerState(txCmd->config.fsOff);
    }
    return rclEvents;
}

RCL_Events RCL_Handler_Generic_TxRepeat(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTxRepeat *txCmd = (RCL_CmdGenericTxRepeat *) cmd;
    RCL_Events rclEvents = {.value = 0};
    bool runTx = false;

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if ((txCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else if ((txCmd->rfFrequency == 0) && (txCmd->config.fsRecal != 0))
        {
            /* Synth not to be programmed, recalibration for each packet requested */
            cmd->status = RCL_CommandStatus_Error_Param;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(txCmd->syncWord);
            /* Handle FS off in the end, so disable it in PBE */
            uint32_t opCfgVal =
                (0 << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_TXFCMD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_START_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_NEXTOP_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_SINGLE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);

            if (txCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }
            if (txCmd->config.fsRecal != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = (PBE_GENERIC_RAM_NESB_NESBMODE_OFF);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
            genericHandlerState.tx.stopFs = false;
            genericHandlerState.tx.txCount = 0;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize RF FIFO */
            genericHandlerState.common.txFifoSize = LRF_prepareTxFifo();

            /* Enter payload */
            if (txCmd->txEntry == NULL)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                uint32_t length = txCmd->txEntry->length;
                /* Number of words including length field and end padding */
                uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(length) / 4;
                if (wordLength > LRF_getTxFifoWritable() / 4)
                {
                    /* Packet will not fit */
                    /* TODO: See RCL-348 */
                    cmd->status = RCL_CommandStatus_Error_Param;
                    rclEvents.lastCmdDone = 1;
                }
                else {
                    LRF_writeTxFifoWords((uint32_t *) txCmd->txEntry, wordLength);

                    RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        cmd->status = startTimeStatus;
                        rclEvents.lastCmdDone = 1;
                    }
                    else
                    {
                        genericHandlerState.tx.period = txCmd->timePeriod;

                        runTx = true; /* Go on */
                        genericHandlerState.tx.gracefulStopObserved = false;
                        if (rclSchedulerState.gracefulStopInfo.cmdStopEnabled || rclSchedulerState.gracefulStopInfo.schedStopEnabled)
                        {
                            /* Enable interrupt to service graceful stop */
                            hal_enable_graceful_stop_time_irq();
                        }
                    }
                }
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.systim1 != 0)
        {
            genericHandlerState.tx.gracefulStopObserved = true;
        }
        if (lrfEvents.opDone != 0)
        {
            if (genericHandlerState.tx.stopFs)
            {
                runTx = false;
            }
            else {
                /* Retry TX FIFO. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = LRFDPBE_FCMD_DATA_TXFIFO_RETRY;

                if (txCmd->numPackets == 0 || genericHandlerState.tx.txCount < txCmd->numPackets)
                {
                    /* Reset PBE */
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_INIT) = 1 << LRFDPBE_INIT_TOPSM_S;

                    runTx = true;
                    if (rclEventsIn.hardStop != 0)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
                        runTx = false;
                    }
                    else if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE) == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP ||
                             genericHandlerState.tx.gracefulStopObserved ||
                             rclEventsIn.gracefulStop != 0)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                        runTx = false;
                    }
                    else {
                        RCL_CommandStatus startTimeStatus;
                        if (genericHandlerState.tx.period != 0)
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
                    if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE) == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
                    {
                        genericHandlerState.common.endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
                    }
                    runTx = false;
                }
            }
            if (!runTx && cmd->status == RCL_CommandStatus_Active)
            {
                if (!genericHandlerState.tx.stopFs && txCmd->config.fsRecal == 0 && txCmd->config.fsOff != 0)
                {
                    /* Send stop FS */
                    LRF_waitForTopsmReady();
                    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOPFS;
                    genericHandlerState.tx.stopFs = true;
                }
                else {
                    cmd->status = genericHandlerState.common.endStatus;
                    rclEvents.lastCmdDone = 1;
                }
            }
        }
        else if (lrfEvents.opError != 0)
        {
            if (genericHandlerState.common.endStatus == RCL_CommandStatus_Finished)
            {
                genericHandlerState.common.endStatus = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }

            if (!genericHandlerState.tx.stopFs && txCmd->config.fsRecal == 0 && txCmd->config.fsOff != 0 &&
                (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x01) != 0)
            {
                /* Synth was turned on, but should be off. Send stop FS */
                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOPFS;
                genericHandlerState.tx.stopFs = true;
            }
            else
            {
                cmd->status = genericHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;
            }
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }

        if (runTx)
        {
            uint32_t txCount = genericHandlerState.tx.txCount;
            if (txCount != 0 && txCmd->config.fsRecal == 0)
            {
                /* Frequency programming only for the first packet */
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) | PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
            }
            txCount++;
            if (txCount != 0)
            {
                /* Avoid wraparound */
                genericHandlerState.tx.txCount = txCount;
            }
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            Log_printf(RclCore, Log_VERBOSE, "Starting TX");

            LRF_waitForTopsmReady();
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_TX;
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState(txCmd->config.fsOff);
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_TxTest ========
 */
RCL_Events RCL_Handler_Generic_TxTest(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdGenericTxTest *txCmd = (RCL_CmdGenericTxTest *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
        genericHandlerState.txTest.restoreOpt = RCL_HANDLER_GENERIC_RESTORE_NONE;
        if ((txCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            uint32_t opCfgVal =
                (1 << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_TXFCMD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_START_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_NEXTOP_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_SINGLE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);

            if (txCmd->config.fsOff != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            if (txCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = (PBE_GENERIC_RAM_NESB_NESBMODE_OFF);

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enter configuration */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PATTERN) = txCmd->config.txWord;
            if (txCmd->config.sendCw != 0)
            {
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) | LRFDMDM_MODCTRL_TONEINSERT_M;
                genericHandlerState.txTest.restoreOpt = RCL_HANDLER_GENERIC_RESTORE_MODCTRL;
            }
            else
            {
                uint32_t whitenMode = txCmd->config.whitenMode;
                /* Configure whitening */
                if (whitenMode == RCL_CMD_GENERIC_WH_MODE_NONE)
                {
                    genericHandlerState.txTest.restoreOpt = RCL_HANDLER_GENERIC_RESTORE_WHITEN_INIT;
                    genericHandlerState.txTest.storedWhitenInit = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT);
                    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = 0;
                    /* Use pattern as sync word */
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(txCmd->config.txWord | (txCmd->config.txWord << 16));
                }
                else
                {
                    if (whitenMode >= RCL_CMD_GENERIC_WH_MODE_PRBS15)
                    {
                        genericHandlerState.txTest.restoreOpt = RCL_HANDLER_GENERIC_RESTORE_WHITEN_POLY | RCL_HANDLER_GENERIC_RESTORE_WHITEN_INIT;
                        genericHandlerState.txTest.storedWhitenPoly = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0);
                        genericHandlerState.txTest.storedWhitenInit = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT);
                        if (whitenMode > RCL_CMD_GENERIC_WH_MODE_PRBS15)
                        {
                            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = RCL_HANDLER_GENERIC_PRBS15_POLY;
                        }
                        else
                        {
                            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = RCL_HANDLER_GENERIC_PRBS32_POLY;
                        }
                        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = RCL_HANDLER_GENERIC_PRBS_INIT;
                    }
                    /* Use pseudo-random sync word (not necessarily matching selected PRBS) */
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_HANDLER_GENERIC_PRBS_SYNC;
                }
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
                if (txCmd->rfFrequency != 0)
                {
                    /* Program frequency word */
                    LRF_programFrequency(txCmd->rfFrequency, true);
                }

                /* Enable interrupts */
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

                /* Post cmd */
                Log_printf(RclCore, Log_VERBOSE, "Starting infinite TX");

                LRF_waitForTopsmReady();
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_TX;
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
            cmd->status = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
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
        RCL_Handler_Generic_setSynthPowerState(txCmd->config.fsOff);
        if ((genericHandlerState.txTest.restoreOpt & RCL_HANDLER_GENERIC_RESTORE_MODCTRL) != 0)        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) & (~LRFDMDM_MODCTRL_TONEINSERT_M);
        }
        if ((genericHandlerState.txTest.restoreOpt & RCL_HANDLER_GENERIC_RESTORE_WHITEN_INIT) != 0)
        {
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = genericHandlerState.txTest.storedWhitenInit;
        }
        if ((genericHandlerState.txTest.restoreOpt & RCL_HANDLER_GENERIC_RESTORE_WHITEN_POLY) != 0)
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = genericHandlerState.txTest.storedWhitenPoly;
        }
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

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if ((rxCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(rxCmd->syncWordA);
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCB) = RCL_Handler_Generic_updateSyncWord(rxCmd->syncWordB);
            uint32_t opCfgVal =
                (0 << PBE_GENERIC_RAM_OPCFG_RXFILTEROP_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_START_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S) |
                (1 << PBE_GENERIC_RAM_OPCFG_NEXTOP_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_SINGLE_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                (0 << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);

            if (rxCmd->config.fsOff != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            if (rxCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }
            if (rxCmd->config.repeated)
            {
                opCfgVal |= PBE_GENERIC_RAM_OPCFG_RFINTERVAL_M;
            }
            else
            {
                opCfgVal |= PBE_GENERIC_RAM_OPCFG_SINGLE_M;
            }

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = (PBE_GENERIC_RAM_NESB_NESBMODE_OFF);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = rxCmd->maxPktLen;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 0; /* No timeout except from SYSTIM */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 0; /* No timeout except from SYSTIM */

            /* If needed, configure demodulator correlator engine for syncwordA and syncwordB */
            if (rxCmd->config.disableSyncA != 0 || rxCmd->config.disableSyncB != 0)
            {
                uint16_t demc1be1 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1);
                uint16_t demc1be2 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2);
#ifdef DeviceFamily_CC27XX
                uint16_t demc1be12 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12);
#endif
                genericHandlerState.rx.restoreThresh = true;
                genericHandlerState.rx.demc1be1 = demc1be1;
                genericHandlerState.rx.demc1be2 = demc1be2;
#ifdef DeviceFamily_CC27XX
                genericHandlerState.rx.demc1be12 = demc1be12;
#endif
                if (rxCmd->config.disableSyncA != 0)
                {
                    demc1be1 = (demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDA_M) | (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDA_S);
                    demc1be2 = (demc1be2 & ~LRFDMDM_DEMC1BE2_THRESHOLDC_M) | (0x7F << LRFDMDM_DEMC1BE2_THRESHOLDC_S);
#ifdef DeviceFamily_CC27XX
                    demc1be12 = (demc1be12 & ~LRFDMDM_DEMC1BE12_THRESHOLDG_M) | (0x7F << LRFDMDM_DEMC1BE12_THRESHOLDG_S);
#endif
                }
                if (rxCmd->config.disableSyncB != 0)
                {
                    demc1be1 = (demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDB_M) | (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDB_S);
                }
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = demc1be1;
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = demc1be2;
#ifdef DeviceFamily_CC27XX
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = demc1be12;
#endif
            }
            else
            {
                genericHandlerState.rx.restoreThresh = false;
            }

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (rxCmd->rfFrequency != 0)
            {
                LRF_programFrequency(rxCmd->rfFrequency, false);
            }

            /* Enable radio */
            LRF_enable();

            RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
            if (startTimeStatus >= RCL_CommandStatus_Finished)
            {
                cmd->status = startTimeStatus;
                rclEvents.lastCmdDone = 1;
            }
            else {
                genericHandlerState.common.activeUpdate = RCL_Handler_Generic_initRxStats(rxCmd->stats,
                                                                                          rclSchedulerState.actualStartTime);
                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize RF FIFOs */
                genericHandlerState.common.rxFifoSize = LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;
                if (rxCmd->config.discardRxPackets == 0)
                {
                    RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
                }
                else
                {
                    /* Set FIFO size to maximum */
                    LRF_setRxFifoEffSz(genericHandlerState.common.rxFifoSize);
                }

                /* Enable interrupts */
                uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIFOCFG);
                LRF_enableHwInterrupt(RCL_Handler_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                               LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                               LRF_EventRxBufFull.value,
                                                                               fifoCfg, genericHandlerState.common.activeUpdate));

                /* Post cmd */
                Log_printf(RclCore, Log_VERBOSE, "Starting Rx");
                LRF_waitForTopsmReady();
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_RX;
            }
        }
    }
    else
    {
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxBufFull != 0)
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
                    if (rxCmd->config.discardRxPackets == 0)
                    {
                        RCL_MultiBuffer *curBuffer;
                        curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                            wordLength * 4);
                        if (curBuffer != genericHandlerState.common.curBuffer) {
                            rclEvents.rxBufferFinished = 1;
                            genericHandlerState.common.curBuffer = curBuffer;
                        }
                        if (curBuffer == NULL) {
                            /* Error */
                            genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                            /* Send abort */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOP;
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
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
            if (lrfEvents.opError != 0 && endStatus == RCL_CommandStatus_Finished)
            {
                endStatus = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE) == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
            {
                endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
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
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState(rxCmd->config.fsOff);
        RCL_Handler_Generic_updateRxStats(rxCmd->stats, rclSchedulerState.actualStartTime);
        /* Restore changed thresholds */
        if (genericHandlerState.rx.restoreThresh)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = genericHandlerState.rx.demc1be1;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = genericHandlerState.rx.demc1be2;
#ifdef DeviceFamily_CC27XX
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = genericHandlerState.rx.demc1be12;
#endif
        }
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_PbeOperation ========
 */
RCL_Events RCL_Handler_Generic_PbeOperation(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_Events rclEvents = {.value = 0};
    RCL_CmdGenericPbeOperation *pbeCmd = (RCL_CmdGenericPbeOperation *) cmd;

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
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts */
            LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);

            /* Post cmd */
            LRF_waitForTopsmReady();
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = pbeCmd->pbeOperation;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0)
        {
            cmd->status = RCL_CommandStatus_Finished;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
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
    }
    return rclEvents;
}


/*
 *  ======== RCL_Handler_Nesb_Ptx ========
 */
RCL_Events RCL_Handler_Nesb_Ptx(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdNesbPtx *txCmd = (RCL_CmdNesbPtx *) cmd;
    RCL_Events rclEvents = {.value = 0};
    bool runTx = false;
    bool listenAck = false;
    uint32_t earliestStartTime = 0;

    if (rclEventsIn.setup != 0)
    {
        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if ((txCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(txCmd->syncWord);
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCB) = RCL_Handler_Generic_updateSyncWord(txCmd->syncWord);

            uint32_t opCfgVal = (PBE_GENERIC_RAM_OPCFG_NEXTOP_SWITCH) |
                                (PBE_GENERIC_RAM_OPCFG_TXFCMD_NONE) |
                                (PBE_GENERIC_RAM_OPCFG_FS_NOCAL_NOCAL) |
                                (PBE_GENERIC_RAM_OPCFG_FS_KEEPON_YES) |
                                (PBE_GENERIC_RAM_OPCFG_IFSPERIOD_EN) |
                                (PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_YES) |
                                (PBE_GENERIC_RAM_OPCFG_RXREPEATOK_YES) |
                                (PBE_GENERIC_RAM_OPCFG_RFINTERVAL_DIS) |
                                (PBE_GENERIC_RAM_OPCFG_SINGLE_DIS) |
                                (PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_YES);

            if (txCmd->config.fsOff != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            if (txCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }
            if (txCmd->config.autoRetransmitMode != 0)
            {
                opCfgVal |= (PBE_GENERIC_RAM_OPCFG_TXFCMD_RETRY);
            }
            else
            {
                opCfgVal |= (PBE_GENERIC_RAM_OPCFG_TXFCMD_DEALLOC);
            }

            /* Enable NESB mode */
            uint32_t nesbVal = (PBE_GENERIC_RAM_NESB_NESBMODE_ON);

            uint32_t seqStat0Val = (txCmd->config.autoRetransmitMode << PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_S)
                                    & PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_M;

            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 2500;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 800;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = 255;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = nesbVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) = seqStat0Val;

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;

            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;
            genericHandlerState.tx.txCount = 0;

            /* Program frequency word */
            if (txCmd->rfFrequency != 0)
            {
                LRF_programFrequency(txCmd->rfFrequency, true);
            }
            if (LRF_programTxPower(txCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }

            /* Enable radio */
            LRF_enable();

            /* Initialize Tx FIFO */
            genericHandlerState.common.txFifoSize = LRF_prepareTxFifo();

            /* Enter header and get ACK configuration */
            RCL_Handler_Nesb_updateHeader(&txCmd->txBuffers,
                                          txCmd->config.autoRetransmitMode,
                                          txCmd->config.hdrConf,
                                          txCmd->seqNo);

            /* Configure Rx if necessary */
            if (txCmd->config.autoRetransmitMode != PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_ALWAYS)
            {
                /* Initialize Rx FIFO */
                genericHandlerState.common.rxFifoSize = LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;

                /* Request notification on RX buffer updates */
                RCL_Handler_Generic_updateRxCurBufferAndFifo(&txCmd->rxBuffers);
                listenAck = true;
            }

            /* Enter payload */
            uint32_t nBuffer = RCL_Handler_Generic_updateTxBuffers(&txCmd->txBuffers, 1);
            if (nBuffer == 0)
            {
                cmd->status = RCL_CommandStatus_Error_MissingTxBuffer;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
                if (startTimeStatus >= RCL_CommandStatus_Finished)
                {
                    cmd->status = startTimeStatus;
                    rclEvents.lastCmdDone = 1;
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
        if (lrfEvents.rxOk != 0 || lrfEvents.rxNok != 0 || lrfEvents.rxIgnored != 0 || lrfEvents.rxBufFull != 0)
        {
            /* Copy received packet from PBE FIFO to buffer */
            /* First, check that there is actually a buffer available */
            while (HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) >= 4)
            {
                /* Check length of received buffer by peeking */
                uint32_t fifoWord = LRF_peekRxFifo(0);
                uint32_t numWords = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / sizeof(uint32_t);
                if (numWords > 0)
                {
                    RCL_MultiBuffer *curBuffer;
                    curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                          numWords * sizeof(uint32_t));

                    if (curBuffer != genericHandlerState.common.curBuffer)
                    {
                        rclEvents.rxBufferFinished = 1;
                        genericHandlerState.common.curBuffer = curBuffer;
                    }

                    if (curBuffer == NULL)
                    {
                        /* Error */
                        genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                        /* Send abort */
                        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOP;
                        /* Do not check for more packets from the RX FIFO */
                        break;
                    }
                    else
                    {
                        uint32_t *buffer32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                        LRF_readRxFifoWords(buffer32, numWords);
                        RCL_MultiBuffer_commitBytes(curBuffer, numWords * sizeof(uint32_t));
                        /* Raise event */
                        rclEvents.rxEntryAvail = 1;
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
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0)
        {
            /* Retry TX FIFO. Writing to FCMD is safe because PBE is finished, ref. RCL-367 */
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = LRFDPBE_FCMD_DATA_TXFIFO_RETRY;

            uint16_t endCause = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);

            if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
            {
                /* Increment the sequence number for next packet */
                txCmd->seqNo = (txCmd->seqNo + 1) % 4;

                cmd->status = genericHandlerState.common.endStatus;
                rclEvents.lastCmdDone = 1;

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
            else if (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC)
            {
                /* Reset PBE */
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_INIT) = 1 << LRFDPBE_INIT_TOPSM_S;

                /* Attempt to retransmit the packet */
                if (genericHandlerState.tx.txCount <= txCmd->maxRetrans)
                {
                    Log_printf(RclCore, Log_VERBOSE, "PTX needs to retransmit");

                    /* Set a new transmit time according to retransDelay. If unattainable, retransmit as soon as possible */
                    RCL_CommandStatus startTimeStatus = RCL_Scheduler_setNewStartRelTime(txCmd->retransDelay);
                    if (startTimeStatus >= RCL_CommandStatus_Finished)
                    {
                        Log_printf(RclCore, Log_VERBOSE, "Unattainable retranmission delay. Retransmitting as soon as possible");
                        RCL_Scheduler_setNewStartNow();
                    }
                    runTx = true;
                }
                else /* Finish the command without incrementing the sequence number */
                {
                    genericHandlerState.common.endStatus = RCL_CommandStatus_NoSync;
                    cmd->status = genericHandlerState.common.endStatus;
                    rclEvents.lastCmdDone = 1;
                    runTx = false;
                }
            }
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;

            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
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
            if (txCount != 0)
            {
                /* Avoid wraparound */
                genericHandlerState.tx.txCount = txCount;
            }
            /* Set up sync found capture */
            hal_setup_sync_found_cap();
            /* Enable interrupts */
            if (listenAck)
            {
                uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIFOCFG);
                LRF_enableHwInterrupt(RCL_Handler_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                               LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                               LRF_EventRxIgnored.value | LRF_EventRxBufFull.value,
                                                                               fifoCfg, genericHandlerState.common.activeUpdate));
            }
            else
            {
                LRF_enableHwInterrupt(LRF_EventOpDone.value | LRF_EventOpError.value);
            }
            /* Post cmd */
            Log_printf(RclCore, Log_VERBOSE, "Start of PTX operation");
            LRF_waitForTopsmReady();
            RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_TX;
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState(txCmd->config.fsOff);
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

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        if ((rxCmd->rfFrequency == 0) && ((HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & 0x0001) == 0))
        {
            /* Synth not to be programmed, but not already locked */
            cmd->status = RCL_CommandStatus_Error_Synth;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = RCL_Handler_Generic_updateSyncWord(rxCmd->syncWordA);
            HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCB) = RCL_Handler_Generic_updateSyncWord(rxCmd->syncWordB);

            uint32_t opCfgVal = (PBE_GENERIC_RAM_OPCFG_NEXTOP_SWITCH) |
                                (PBE_GENERIC_RAM_OPCFG_TXFCMD_RETRY) |
                                (PBE_GENERIC_RAM_OPCFG_FS_NOCAL_NOCAL) |
                                (PBE_GENERIC_RAM_OPCFG_FS_KEEPON_YES) |
                                (PBE_GENERIC_RAM_OPCFG_IFSPERIOD_EN) |
                                (PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_NO) |
                                (PBE_GENERIC_RAM_OPCFG_RXREPEATOK_NO) |
                                (PBE_GENERIC_RAM_OPCFG_RFINTERVAL_DIS) |
                                (PBE_GENERIC_RAM_OPCFG_SINGLE_DIS) |
                                (PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_YES);

            if (rxCmd->config.fsOff != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M);
            }
            if (rxCmd->rfFrequency != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M);
            }
            if (rxCmd->config.repeatNok != 0)
            {
                opCfgVal |= PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_M;
            }
            if (rxCmd->config.repeatOk != 0)
            {
                opCfgVal &= ~(PBE_GENERIC_RAM_OPCFG_RXREPEATOK_M);
            }

            /* Enable NESB mode */
            uint32_t nesbVal = (PBE_GENERIC_RAM_NESB_NESBMODE_ON);
            nesbVal |= (rxCmd->addrLen << PBE_GENERIC_RAM_NESB_PEERADRLEN_S) & PBE_GENERIC_RAM_NESB_PEERADRLEN_M;

            /* Configure AutoACK and Seq Status for syncword 0 */
            uint32_t seqStat0Val = (rxCmd->syncWord[0].seqValid << PBE_GENERIC_RAM_SEQSTAT0_VALID_S)
                                    & PBE_GENERIC_RAM_SEQSTAT0_VALID_M;

            seqStat0Val |= (rxCmd->syncWord[0].autoAckMode << PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_S)
                           & PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_M;

            /* Configure AutoACK and Seq Status for syncword 1 */
            uint32_t seqStat1Val = (rxCmd->syncWord[1].seqValid << PBE_GENERIC_RAM_SEQSTAT1_VALID_S)
                                    & PBE_GENERIC_RAM_SEQSTAT1_VALID_M;

            seqStat1Val |= (rxCmd->syncWord[1].autoAckMode << PBE_GENERIC_RAM_SEQSTAT1_STOPAUTO_S)
                           & PBE_GENERIC_RAM_SEQSTAT1_STOPAUTO_M;

            /* Set the addresses that will be used for address filtering */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0AL) = (rxCmd->syncWord[0].address & PBE_GENERIC_RAM_PEERADR0AL_VAL_M);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0AH) = (rxCmd->syncWord[0].address >> 0x10) & PBE_GENERIC_RAM_PEERADR0AH_VAL_M;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0BL) = (rxCmd->syncWord[1].address & PBE_GENERIC_RAM_PEERADR0BL_VAL_M);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0BH) = (rxCmd->syncWord[1].address >> 0x10) & PBE_GENERIC_RAM_PEERADR0BH_VAL_M;

            /* Set timeouts for the Rx operation */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 0; /* No timeout except from SYSTIM */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 0; /* No timeout except from SYSTIM */

            /* Set remaining configuration registers */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = nesbVal;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) = seqStat0Val;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT1) = seqStat1Val;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = 255;

            /* If needed, configure demodulator correlator engine for syncwordA and syncwordB */
            if (rxCmd->config.disableSyncA != 0 || rxCmd->config.disableSyncB != 0)
            {
                uint16_t demc1be1 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1);
                uint16_t demc1be2 = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2);
                genericHandlerState.rx.restoreThresh = true;
                genericHandlerState.rx.demc1be1 = demc1be1;
                genericHandlerState.rx.demc1be2 = demc1be2;
                if (rxCmd->config.disableSyncA != 0)
                {
                    demc1be1 = (demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDA_M) | (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDA_S);
                    demc1be2 = (demc1be2 & ~LRFDMDM_DEMC1BE2_THRESHOLDC_M) | (0x7F << LRFDMDM_DEMC1BE2_THRESHOLDC_S);
                }
                if (rxCmd->config.disableSyncB != 0)
                {
                    demc1be1 = (demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDB_M) | (0x7F << LRFDMDM_DEMC1BE1_THRESHOLDB_S);
                }
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = demc1be1;
                HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = demc1be2;
            }
            else
            {
                genericHandlerState.rx.restoreThresh = false;
            }

            /* Mark as active */
            cmd->status = RCL_CommandStatus_Active;
            /* Default end status */
            genericHandlerState.common.endStatus = RCL_CommandStatus_Finished;

            /* Program frequency word */
            if (rxCmd->rfFrequency != 0)
            {
                LRF_programFrequency(rxCmd->rfFrequency, false);
            }
            if (LRF_programTxPower(rxCmd->txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
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
                genericHandlerState.common.activeUpdate = RCL_Handler_Nesb_initStats(rxCmd->stats,
                                                                                     rclSchedulerState.actualStartTime);

                /* Set up sync found capture */
                hal_setup_sync_found_cap();
                /* Initialize Rx FIFO */
                genericHandlerState.common.rxFifoSize = LRF_prepareRxFifo();
                genericHandlerState.common.curBuffer = NULL;

                if (rxCmd->config.discardRxPackets == 0)
                {
                    RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
                }
                else
                {
                    /* Set FIFO size to maximum */
                    LRF_setRxFifoEffSz(genericHandlerState.common.rxFifoSize);
                }

                /* If an ACK is required, prepare Tx FIFOs */
                if ((rxCmd->syncWord[0].autoAckMode != 0) || (rxCmd->syncWord[1].autoAckMode != 0))
                {
                    genericHandlerState.common.txFifoSize = LRF_prepareTxFifo();
                }

                /* Enable interrupts */
                uint16_t fifoCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIFOCFG);
                LRF_enableHwInterrupt(RCL_Handler_Generic_maskEventsByFifoConf(LRF_EventOpDone.value | LRF_EventOpError.value |
                                                                               LRF_EventRxOk.value | LRF_EventRxNok.value |
                                                                               LRF_EventRxIgnored.value | LRF_EventRxBufFull.value,
                                                                               fifoCfg, genericHandlerState.common.activeUpdate));
                /* Post cmd */
                Log_printf(RclCore, Log_VERBOSE, "Starting of PRX operation");
                LRF_waitForTopsmReady();
                RCL_Profiling_eventHook(RCL_ProfilingEvent_PreprocStop);
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_RX;
            }
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
                uint32_t numWords = RCL_Buffer_DataEntry_paddedLen(fifoWord & 0xFFFF) / sizeof(uint32_t);
                if (numWords > 0)
                {
                    if (rxCmd->config.discardRxPackets == 0)
                    {
                        RCL_MultiBuffer *curBuffer;
                        curBuffer = RCL_MultiBuffer_getBuffer(genericHandlerState.common.curBuffer,
                                                              numWords * 4);
                        if (curBuffer != genericHandlerState.common.curBuffer)
                        {
                            rclEvents.rxBufferFinished = 1;
                            genericHandlerState.common.curBuffer = curBuffer;
                        }
                        if (curBuffer == NULL)
                        {
                            /* Error */
                            genericHandlerState.common.endStatus = RCL_CommandStatus_Error_RxBufferCorruption;
                            /* Send abort */
                            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOP;
                            /* Do not check for more packets from the RX FIFO */
                            break;
                        }
                        else
                        {
                            uint32_t *buffer32 = (uint32_t *)RCL_MultiBuffer_getNextWritableByte(curBuffer);
                            LRF_readRxFifoWords(buffer32, numWords);
                            RCL_MultiBuffer_commitBytes(curBuffer, numWords * sizeof(uint32_t));
                            /* Raise event */
                            rclEvents.rxEntryAvail = 1;
                            /* Adjust effective FIFO size */
                            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);

                            /* Update the sequence number to the one from to the last successfully received packet */
                            rxCmd->syncWord[0].seq = (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) & PBE_GENERIC_RAM_SEQSTAT0_PID_M) >> PBE_GENERIC_RAM_SEQSTAT0_PID_S;
                            rxCmd->syncWord[1].seq = (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT1) & PBE_GENERIC_RAM_SEQSTAT1_PID_M) >> PBE_GENERIC_RAM_SEQSTAT1_PID_S;

                            /* Update the CRC value to the one from the last successfully received packet */
                            rxCmd->syncWord[0].crcVal = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_CRCVAL0);
                            rxCmd->syncWord[1].crcVal = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_CRCVAL1);
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
        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }
        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = genericHandlerState.common.endStatus;

            rclEvents.lastCmdDone = 1;
            if (lrfEvents.opError != 0 && endStatus == RCL_CommandStatus_Finished)
            {
                endStatus = RCL_Handler_Generic_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else if (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE) == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
            {
                endStatus = RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
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
        if (rclEventsIn.rxBufferUpdate != 0)
        {
            RCL_Handler_Generic_updateRxCurBufferAndFifo(&rxCmd->rxBuffers);
        }
    }
    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        RCL_Handler_Generic_setSynthPowerState(rxCmd->config.fsOff);
        RCL_Handler_Nesb_updateStats(rxCmd->stats, rclSchedulerState.actualStartTime);
        /* Restore changed thresholds */
        if (genericHandlerState.rx.restoreThresh)
        {
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = genericHandlerState.rx.demc1be1;
            HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = genericHandlerState.rx.demc1be2;
        }
    }

    return rclEvents;
}

/*
 *  ======== RCL_Handler_Generic_setSynthPowerState ========
 */
static void RCL_Handler_Generic_setSynthPowerState(bool fsOff)
{
    /* Do power management for synth at the end of a command.
       If synth is off, turn off refsys and remove constraint on standby.
       If synth is on, keep refsys on and ensure constraint on standby is set */
    if (fsOff)
    {
        LRF_disableSynthRefsys();
        /* Release additional power constraints if necessary */
        if(genericHandlerState.common.powerConstraintsSet)
        {
            genericHandlerState.common.powerConstraintsSet = false;
            hal_power_release_constraint();
        }
    }
    else
    {
        /* Set additional power constraints if necessary */
        if(!genericHandlerState.common.powerConstraintsSet)
        {
            genericHandlerState.common.powerConstraintsSet = true;
            hal_power_set_constraint();
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
 *  ======== RCL_Handler_Generic_findPbeErrorEndStatus ========
 */
static RCL_CommandStatus RCL_Handler_Generic_findPbeErrorEndStatus(uint16_t pbeEndStatus)
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
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
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
        uint32_t wordLength = RCL_Buffer_DataEntry_paddedLen(length) / 4;

        if (wordLength > LRF_getTxFifoWritable() / 4)
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
 *  ======== RCL_Handler_Generic_maskEventsByFifoConf ========
 */
static uint32_t RCL_Handler_Generic_maskEventsByFifoConf(uint32_t mask, uint16_t fifoConfVal, bool activeUpdate)
{
    /* Remove events that will not give an entry in the RX FIFO, based on FIFOCFG, unless active update is used
       Note: never remove the CRC error event, as it is needed to update the long CRC error counter */
    if (!activeUpdate)
    {
        mask &= ~(((fifoConfVal & PBE_GENERIC_RAM_FIFOCFG_AUTOFLUSHIGN_M) ? LRF_EventRxIgnored.value : 0) |
                  LRF_EventRxBufFull.value);
    }
    return mask;
}

/*
 *  ======== RCL_Handler_Generic_updateRxStats ========
 */
static void RCL_Handler_Generic_updateRxStats(RCL_StatsGeneric *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        uint32_t lastTimestamp = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL);
        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = false;
        }
        else {
            stats->timestampValid = true;
            stats->lastTimestamp = lastTimestamp;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTRSSI);
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
    uint32_t newRxOk = (oldRxOk & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK);
    uint32_t newRxNok = (oldRxNok & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK);

    if (newRxOk < oldRxOk)
    {
        newRxOk += 0x10000;
    }
    if (newRxNok < oldRxNok)
    {
        newRxNok += 0x10000;
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
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL) = startTime;
        stats->timestampValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            genericHandlerState.rx.longNokCount = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = stats->nRxNok & 0xFFFF;
            genericHandlerState.rx.longOkCount = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = stats->nRxOk & 0xFFFF;
        }
        else
        {
            /* Reset existing values in PBE */
            genericHandlerState.rx.longNokCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = 0;
            genericHandlerState.rx.longOkCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = 0;

            stats->nRxNok = 0;
            stats->nRxOk = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in PBE */
        genericHandlerState.rx.longNokCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = 0;
        genericHandlerState.rx.longOkCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = 0;

        return false;
    }
}

/*
 *  ======== RCL_Handler_Generic_updateSyncWord ========
 */
static uint32_t RCL_Handler_Generic_updateSyncWord(uint32_t syncWord)
{
    uint32_t syncWordOut;
    /* Check bit ordering of header and follow that */
    if ((HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PKTCFG) & PBE_GENERIC_RAM_PKTCFG_HDRORDER_M) != 0)
    {
        /* MSb first configured - bit reverse sync word */
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0) = syncWord & 0x0000FFFF;
        syncWordOut = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0BR) << 16;
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0) = syncWord >> 16;
        syncWordOut |= HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0BR);
        /* Check sync word length to see ensure that sync word ends up in least significant bits */
        uint32_t syncWordLen = (HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMSWQU0) & LRFDMDM_DEMSWQU0_REFLEN_M) + 1;
        syncWordOut >>= (32 - syncWordLen);
    }
    else
    {
        syncWordOut = syncWord;
    }

    return syncWordOut;
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
    uint8_t indexHeader = nextTxBuffer->numPad - 1;

    if (hdrConf == 0)
    {
        /* Insert NO_ACK field from TX buffer. */
        noAck = nextTxBuffer->data[indexHeader] & 0x01;
        seqNo = seqNumber;
    }
    else
    {
        /* Insert SEQ and NO_ACK field from TX buffer. */
        noAck = nextTxBuffer->data[indexHeader] & 0x01;
        seqNo = (nextTxBuffer->data[indexHeader] >> 1) & 0x03;
    }

    /* Update header */
    nextTxBuffer->data[indexHeader] = ((nextTxBuffer->data[indexHeader] & 0xF8) | ((seqNo & 0x03) << 1) | noAck);
}

/*
 *  ======== RCL_Handler_Nesb_updateStats ========
 */
static void RCL_Handler_Nesb_updateStats(RCL_StatsNesb *stats, uint32_t startTime)
{
    if (stats != NULL)
    {
        uint32_t lastTimestamp = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL);
        /* Check if a new value is found in the first timestamp */
        if (lastTimestamp == startTime)
        {
            stats->timestampValid = false;
        }
        else {
            stats->timestampValid = true;
            stats->lastTimestamp = lastTimestamp;
        }
        stats->lastRssi = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTRSSI);
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

    uint32_t newTx = (oldTx & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX);
    uint32_t newRxOk = (oldRxOk & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK);
    uint32_t newRxNok = (oldRxNok & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK);
    uint32_t newRxIgnored = (oldRxIgnored & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED);
    /* TODO: See RCL-343 */
    uint32_t newRxAddrMismatch = (oldRxAddrMismatch & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED);
    uint32_t newRxBufFull = (oldRxBufFull & ~0xFFFF) | HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL);

    if (newTx < oldTx)
    {
        newTx += 0x10000;
    }
    if (newRxOk < oldRxOk)
    {
        newRxOk += 0x10000;
    }
    if (newRxNok < oldRxNok)
    {
        newRxNok += 0x10000;
    }
    if (newRxIgnored < oldRxIgnored)
    {
        newRxIgnored += 0x10000;
    }
    if (newRxAddrMismatch < oldRxAddrMismatch)
    {
        newRxAddrMismatch += 0x10000;
    }
    if (newRxBufFull < oldRxBufFull)
    {
        newRxBufFull += 0x10000;
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
        HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL) = startTime;
        stats->timestampValid = false;
        stats->lastRssi = LRF_RSSI_INVALID;
        if (stats->config.accumulate != 0)
        {
            /* Copy existing values into PBE */
            genericHandlerState.nesb.longTxCount = stats->nTx;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX) = stats->nRxOk & 0xFFFF;
            genericHandlerState.nesb.longOkCount = stats->nRxOk;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = stats->nRxOk & 0xFFFF;
            genericHandlerState.nesb.longNokCount = stats->nRxNok;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = stats->nRxNok & 0xFFFF;
            genericHandlerState.nesb.longRxIgnoredCount = stats->nRxIgnored;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = stats->nRxIgnored & 0xFFFF;
            genericHandlerState.nesb.longRxAddrMismatchCount = stats->nRxAddrMismatch;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = stats->nRxAddrMismatch & 0xFFFF;
            genericHandlerState.nesb.longRxBufFullCount = stats->nRxBufFull;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL) = stats->nRxBufFull & 0xFFFF;
        }
        else
        {
            /* Reset existing values in PBE */
            genericHandlerState.nesb.longTxCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX) = 0;
            genericHandlerState.nesb.longOkCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = 0;
            genericHandlerState.nesb.longNokCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = 0;
            genericHandlerState.nesb.longRxIgnoredCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = 0;
            genericHandlerState.nesb.longRxAddrMismatchCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = 0;
            genericHandlerState.nesb.longRxBufFullCount = 0;
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL) = 0;

            stats->nTx = 0;
            stats->nRxOk = 0;
            stats->nRxNok = 0;
            stats->nRxIgnored = 0;
            stats->nRxAddrMismatch = 0;
            stats->nRxBufFull = 0;
        }
        return stats->config.activeUpdate;
    }
    else
    {
        /* Reset existing values in PBE */
        genericHandlerState.nesb.longTxCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX) = 0;
        genericHandlerState.nesb.longOkCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = 0;
        genericHandlerState.nesb.longNokCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = 0;
        genericHandlerState.nesb.longRxIgnoredCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = 0;
        genericHandlerState.nesb.longRxAddrMismatchCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = 0;
        genericHandlerState.nesb.longRxBufFullCount = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL) = 0;

        return false;
    }
}
