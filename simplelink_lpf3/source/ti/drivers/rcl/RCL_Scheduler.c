/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
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
 *  ======== RCL_Scheduler.c ========
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <ti/log/Log.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/rcl/hal/hal.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Debug.h>

#include <ti/drivers/rcl/LRF.h>

RCL_SchedulerState rclSchedulerState;


typedef enum
{
    SchedulerNoStart = 0,
    SchedulerStartNow = 1,
    SchedulerStartAbsTimeAllowDelay = 2,
    SchedulerStartAbsTimeNoDelay = 3,
} SchedulerStartType;

static RCL_CommandStatus rclSchedulerProcessCmdStartStopTime(const RCL_CommandTiming *timing, uint32_t startTime, SchedulerStartType startType);
static void rclSchedulerFindEarliestStopTime(RCL_SchedulerStopInfo *stopInfo);
static RCL_StopType rclSchedulerSetNewStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t newStopTime, bool sched);
static RCL_StopType rclSchedulerCancelStopTime(RCL_SchedulerStopInfo *stopInfo, bool sched);

/*
 *  ======== RCL_Scheduler_findStopStatus ========
 */
RCL_CommandStatus RCL_Scheduler_findStopStatus(RCL_StopType stopType)
{
    RCL_CommandStatus status;
    switch (stopType)
    {
        case RCL_StopType_DescheduleOnly:
            switch (rclSchedulerState.descheduleReason)
            {
                case RCL_SchedulerStopReason_Scheduling:
                    status = RCL_CommandStatus_DescheduledScheduling;
                    break;
                case RCL_SchedulerStopReason_Api:
                    status = RCL_CommandStatus_DescheduledApi;
                    break;
                default:
                    /* Other values should not occur */
                    status = RCL_CommandStatus_Error;
                    break;
            }
            break;
        case RCL_StopType_Graceful:
            switch (rclSchedulerState.gracefulStopInfo.stopReason)
            {
                case RCL_SchedulerStopReason_Timeout:
                    status = RCL_CommandStatus_GracefulStopTimeout;
                    break;
                case RCL_SchedulerStopReason_Scheduling:
                    status = RCL_CommandStatus_GracefulStopScheduling;
                    break;
                case RCL_SchedulerStopReason_Api:
                    status = RCL_CommandStatus_GracefulStopApi;
                    break;
                default:
                    /* Other values should not occur */
                    status = RCL_CommandStatus_Error;
                    break;
            }
            break;
        case RCL_StopType_Hard:
            switch (rclSchedulerState.hardStopInfo.stopReason)
            {
                case RCL_SchedulerStopReason_Timeout:
                    status = RCL_CommandStatus_HardStopTimeout;
                    break;
                case RCL_SchedulerStopReason_Scheduling:
                    status = RCL_CommandStatus_HardStopScheduling;
                    break;
                case RCL_SchedulerStopReason_Api:
                    status = RCL_CommandStatus_HardStopApi;
                    break;
                default:
                    /* Other values should not occur */
                    status = RCL_CommandStatus_Error;
                    break;
            }
            break;
        default:
            /* Other stop types not allowed */
            status = RCL_CommandStatus_Error;
    }
    /* Error status should not be produced if function is used correctly */
    RCL_Debug_assert(status < RCL_CommandStatus_Error);

    return status;
}

/*
 *  ======== RCL_Scheduler_setStartStopTime ========
 */
RCL_CommandStatus RCL_Scheduler_setStartStopTime(const RCL_Command *cmd)
{
    uint32_t startTime;
    SchedulerStartType startType;

    RCL_Debug_assert(cmd != NULL);

    if (cmd->scheduling == RCL_Schedule_AbsTime)
    {
        startType = cmd->allowDelay ? SchedulerStartAbsTimeAllowDelay : SchedulerStartAbsTimeNoDelay;
        startTime = cmd->timing.absStartTime;
    }
    else
    {
        /* For schedule now, we don't need to check allowDelay here, as delays at this stage will be small */
        startType = SchedulerStartNow;
        startTime = 0;
    }

    return rclSchedulerProcessCmdStartStopTime(&cmd->timing, startTime, startType);
}

/*
 *  ======== RCL_Scheduler_setStartStopTimeEarliestStart ========
 */
RCL_CommandStatus RCL_Scheduler_setStartStopTimeEarliestStart(const RCL_Command *cmd, uint32_t earliestStartTime)
{
    uint32_t startTime;
    SchedulerStartType startType;

    RCL_Debug_assert(cmd != NULL);

    if (cmd->scheduling == RCL_Schedule_AbsTime)
    {
        startType = cmd->allowDelay ? SchedulerStartAbsTimeAllowDelay : SchedulerStartAbsTimeNoDelay;
        startTime = cmd->timing.absStartTime;
        if (!RCL_Scheduler_isLater(earliestStartTime, startTime))
        {
            /* Start time is earlier than indicated - delay start if allowed */
            if (startType == SchedulerStartAbsTimeNoDelay)
            {
                /* Delay not allowed */
                return RCL_CommandStatus_Error_StartTooLate;
            }
            else
            {
                startTime = earliestStartTime;
            }
        }
    }
    else
    {
        /* For schedule now, we don't need to check allowDelay here, as delays at this stage will be small */
        startType = SchedulerStartAbsTimeAllowDelay;
        startTime = earliestStartTime;
    }

    return rclSchedulerProcessCmdStartStopTime(&cmd->timing, startTime, startType);
}

/*
 *  ======== RCL_Scheduler_setCustomStartStopTime ========
 */
RCL_CommandStatus RCL_Scheduler_setCustomStartStopTime(const RCL_CommandTiming *timing, RCL_ScheduleType scheduling, bool allowDelay)
{
    uint32_t startTime;
    SchedulerStartType startType;

    RCL_Debug_assert(timing != NULL);

    if (scheduling == RCL_Schedule_AbsTime)
    {
        startType = allowDelay ? SchedulerStartAbsTimeAllowDelay : SchedulerStartAbsTimeNoDelay;
        startTime = timing->absStartTime;
    }
    else
    {
        /* For schedule now, we don't need to check allowDelay here, as delays at this stage will be small */
        startType = SchedulerStartNow;
        startTime = 0;
    }

    return rclSchedulerProcessCmdStartStopTime(timing, startTime, startType);
}

/*
 *  ======== RCL_Scheduler_setCustomStartStopTimeEarliestStart ========
 */
RCL_CommandStatus RCL_Scheduler_setCustomStartStopTimeEarliestStart(const RCL_CommandTiming *timing, RCL_ScheduleType scheduling, bool allowDelay, uint32_t earliestStartTime)
{
    uint32_t startTime;
    SchedulerStartType startType;

    RCL_Debug_assert(timing != NULL);

    if (scheduling == RCL_Schedule_AbsTime)
    {
        startType = allowDelay ? SchedulerStartAbsTimeAllowDelay : SchedulerStartAbsTimeNoDelay;
        startTime = timing->absStartTime;
        if (!RCL_Scheduler_isLater(earliestStartTime, startTime))
        {
            /* Start time is earlier than indicated - delay start if allowed */
            if (startType == SchedulerStartAbsTimeNoDelay)
            {
                /* Delay not allowed */
                return RCL_CommandStatus_Error_StartTooLate;
            }
            else
            {
                startTime = earliestStartTime;
            }
        }
    }
    else
    {
        /* For schedule now, we don't need to check allowDelay here, as delays at this stage will be small */
        startType = SchedulerStartAbsTimeAllowDelay;
        startTime = earliestStartTime;
    }

    return rclSchedulerProcessCmdStartStopTime(timing, startTime, startType);
}

/*
 *  ======== RCL_Scheduler_setCmdStopTimeNoStartTrigger ========
 */
RCL_CommandStatus RCL_Scheduler_setCmdStopTimeNoStartTrigger(const RCL_Command *cmd)
{
    RCL_Debug_assert(cmd != NULL);

    return rclSchedulerProcessCmdStartStopTime(&cmd->timing, 0, SchedulerNoStart);
}

/*
 *  ======== RCL_Scheduler_setNewStartNow ========
 */
RCL_CommandStatus RCL_Scheduler_setNewStartNow(void)
{
    return rclSchedulerProcessCmdStartStopTime(NULL, 0, SchedulerStartNow);
}

/*
 *  ======== RCL_Scheduler_setNewStartAbsTime ========
 */
RCL_CommandStatus RCL_Scheduler_setNewStartAbsTime(uint32_t startTime, bool allowDelay)
{
    return rclSchedulerProcessCmdStartStopTime(NULL, startTime,
        allowDelay ? SchedulerStartAbsTimeAllowDelay : SchedulerStartAbsTimeNoDelay);
}

/*
 *  ======== RCL_Scheduler_setNewStartRelTime ========
 */
RCL_CommandStatus RCL_Scheduler_setNewStartRelTime(uint32_t relStartTime)
{
    uint32_t startTime = rclSchedulerState.actualStartTime + relStartTime;

    return rclSchedulerProcessCmdStartStopTime(NULL, startTime, SchedulerStartAbsTimeAllowDelay);
}

/*
 *  ======== rclSchedulerProcessCmdStartStopTime ========
 */
static RCL_CommandStatus rclSchedulerProcessCmdStartStopTime(const RCL_CommandTiming *timing, uint32_t startTime, SchedulerStartType startType)
{
    uintptr_t key;
    uint32_t currentTime;
    uint32_t actualStartTime = startTime;

    key = HwiP_disable();

    if (startType == SchedulerNoStart)
    {
        actualStartTime = hal_get_current_time();
    }
    else if (startType == SchedulerStartNow)
    {
        /* Find start time to trig now; add a delay to allow trigger to be in the future */
        actualStartTime = hal_get_current_time() + RCL_SCHEDULER_TRIG_NOW_DELAY;
    }
    else
    {
        /* Check if there is enough time for start */
        currentTime = hal_get_current_time();
        if (!RCL_Scheduler_isLater(currentTime + RCL_SCHEDULER_TRIG_NOW_DELAY, startTime))
        {
            if (startType == SchedulerStartAbsTimeAllowDelay)
            {
                actualStartTime = currentTime + RCL_SCHEDULER_TRIG_NOW_DELAY;
            }
            else {
                /* Error - start is too late */
                HwiP_restore(key);
                return RCL_CommandStatus_Error_StartTooLate;
            }
        }
    }

    rclSchedulerState.actualStartTime = actualStartTime;
    if (startType != SchedulerNoStart)
    {
        hal_setup_start_time(actualStartTime);
        /* Due to protected area and added delay, the programmed start time is not expected to be in the future. */
        RCL_Debug_assert(RCL_Scheduler_isLater(RCL_Scheduler_getCurrentTime(), actualStartTime));
    }

    /* Set up stop times from command if not already done */
    if (timing != NULL && (rclSchedulerState.stopTimeState < RCL_SchedulerStopTimeState_Found))
    {
        uint32_t relHardStopTime = timing->relHardStopTime;
        int32_t relGracefulStopTime = timing->relGracefulStopTime;
        if (relHardStopTime != 0)
        {
            rclSchedulerState.hardStopInfo.cmdStopTime = startTime + relHardStopTime;
            rclSchedulerState.hardStopInfo.cmdStopEnabled = true;
        }

        if (relGracefulStopTime < 0 && relHardStopTime != 0)
        {
            /* Graceful stop time relative to hard stop time */
            relGracefulStopTime += relHardStopTime;
            if (relGracefulStopTime <= 0)
            {
                /* Stop immediately */
                relGracefulStopTime = 1;
            }
        }
        if (relGracefulStopTime > 0)
        {
            rclSchedulerState.gracefulStopInfo.cmdStopTime = actualStartTime + relGracefulStopTime;
            rclSchedulerState.gracefulStopInfo.cmdStopEnabled = true;
        }

        /* Find earliest stop times */
        rclSchedulerFindEarliestStopTime(&rclSchedulerState.hardStopInfo);
        rclSchedulerFindEarliestStopTime(&rclSchedulerState.gracefulStopInfo);

        rclSchedulerState.stopTimeState = RCL_SchedulerStopTimeState_Found;
    }

    /* Check if stop has been requested; at this time, radio may not have started */
    if (rclSchedulerState.hardStopInfo.apiStopEnabled)
    {
        /* Hard stop before modem start */
        HwiP_restore(key);
        return RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
    }
    else if (rclSchedulerState.hardStopInfo.stopReason != RCL_SchedulerStopReason_None)
    {
        uint32_t stopTime = (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Timeout) ?
            rclSchedulerState.hardStopInfo.cmdStopTime : rclSchedulerState.hardStopInfo.schedStopTime;

        if (!RCL_Scheduler_isLater(actualStartTime, stopTime))
        {
            /* Hard stop before modem start */
            HwiP_restore(key);
            return RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        }
    }

    if (rclSchedulerState.gracefulStopInfo.apiStopEnabled)
    {
        /* Graceful stop before modem start */
        HwiP_restore(key);
        return RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
    }
    else if (rclSchedulerState.gracefulStopInfo.stopReason != RCL_SchedulerStopReason_None)
    {
        uint32_t stopTime = (rclSchedulerState.gracefulStopInfo.stopReason == RCL_SchedulerStopReason_Timeout) ?
            rclSchedulerState.gracefulStopInfo.cmdStopTime : rclSchedulerState.gracefulStopInfo.schedStopTime;

        if (!RCL_Scheduler_isLater(actualStartTime, stopTime))
        {
            /* Graceful stop before modem start */
            HwiP_restore(key);
            return RCL_Scheduler_findStopStatus(RCL_StopType_Graceful);
        }
    }

    HwiP_restore(key);

    Log_printf(RclCore, Log_DEBUG, "Using PBE start time 0x%08X (current time 0x%08X)", actualStartTime, RCL_Scheduler_getCurrentTime());

    return RCL_CommandStatus_Active;
}

/*
 *  ======== RCL_Scheduler_setStopTimes ========
 */
RCL_StopType RCL_Scheduler_setStopTimes(void)
{
    RCL_StopType stopType = RCL_StopType_None;

    /* If stop times have not been found, do not program stop. Note that this
       should only be done for very fast commands that are over as soon as
       they start */
    if (rclSchedulerState.stopTimeState >= RCL_SchedulerStopTimeState_Found)
    {
        uintptr_t key = HwiP_disable();

        if (rclSchedulerState.hardStopInfo.stopReason != RCL_SchedulerStopReason_None)
        {
            uint32_t stopTime = (rclSchedulerState.hardStopInfo.stopReason == RCL_SchedulerStopReason_Timeout) ?
                rclSchedulerState.hardStopInfo.cmdStopTime : rclSchedulerState.hardStopInfo.schedStopTime;

            hal_setup_hard_stop_time(stopTime);

            if (!RCL_Scheduler_isLater(RCL_Scheduler_getCurrentTime(), stopTime))
            {
                /* Hard stop already occurred */
                hal_cancel_hard_stop_time();
                stopType = RCL_StopType_Hard;
            }
        }

        if (rclSchedulerState.gracefulStopInfo.stopReason != RCL_SchedulerStopReason_None)
        {
            uint32_t stopTime = (rclSchedulerState.gracefulStopInfo.stopReason == RCL_SchedulerStopReason_Timeout) ?
                rclSchedulerState.gracefulStopInfo.cmdStopTime : rclSchedulerState.gracefulStopInfo.schedStopTime;

            hal_setup_graceful_stop_time(stopTime);

            if (!RCL_Scheduler_isLater(RCL_Scheduler_getCurrentTime(), stopTime))
            {
                /* Graceful stop already occurred */
                hal_cancel_graceful_stop_time();
                stopType = RCL_StopType_Graceful;
            }
        }

        rclSchedulerState.stopTimeState = RCL_SchedulerStopTimeState_Programmed;

        HwiP_restore(key);
    }
    return stopType;
}

/*
 *  ======== RCL_Scheduler_isLater ========
 */
bool RCL_Scheduler_isLater(uint32_t refTime, uint32_t chkTime)
{
    uint32_t timediff = refTime - chkTime;
    if (timediff >= 0x20000000)
    {
        /* chkTime is later than refTime */
        return true;
    }
    else
    {
        /* chkTime is earlier than or same time as refTime */
        return false;
    }
}

/*
 *  ======== RCL_Scheduler_delta ========
 */
int32_t RCL_Scheduler_delta(uint32_t refTime, uint32_t chkTime)
{
    uint32_t timediff = refTime - chkTime;
    if (timediff >= 0x20000000)
    {
        /* chkTime is later than refTime. Get difference as a positive number */
        timediff = chkTime - refTime;
        if (timediff >= 0x80000000)
        {
            /* Large difference - saturate */
            return (int32_t) 0x7FFFFFFF;
        }
        else
        {
            /* Difference is a positive value also as signed */
            return (int32_t) timediff;
        }
    }
    else
    {
        /* chkTime is earlier than or same time as refTime. Return negative result or 0 */
        return (int32_t)(-timediff);
    }
}

/*
 *  ======== RCL_Scheduler_setSchedStopTime ========
 */
RCL_StopType RCL_Scheduler_setSchedStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t schedStopTime)
{
    return rclSchedulerSetNewStopTime(stopInfo, schedStopTime, true);
}

/*
 *  ======== RCL_Scheduler_setCmdStopTime ========
 */
RCL_StopType RCL_Scheduler_setCmdStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t cmdStopTime)
{
    return rclSchedulerSetNewStopTime(stopInfo, cmdStopTime, false);
}

/*
 *  ======== RCL_Scheduler_cancelSchedStopTime ========
 */
RCL_StopType RCL_Scheduler_cancelSchedStopTime(RCL_SchedulerStopInfo *stopInfo)
{
    return rclSchedulerCancelStopTime(stopInfo, true);
}

/*
 *  ======== RCL_Scheduler_cancelCmdStopTime ========
 */
RCL_StopType RCL_Scheduler_cancelCmdStopTime(RCL_SchedulerStopInfo *stopInfo)
{
    return rclSchedulerCancelStopTime(stopInfo, false);
}

static RCL_StopType rclSchedulerSetNewStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t newStopTime, bool sched)
{
    RCL_StopType immediateStop = RCL_StopType_None;

    /* Store current state of the stop info */
    RCL_SchedulerStopReason oldStopReason = stopInfo->stopReason;
    uint32_t oldStopTime;
    switch (stopInfo->stopReason)
    {
        case RCL_SchedulerStopReason_Timeout:
            oldStopTime = stopInfo->cmdStopTime;
            break;

        case RCL_SchedulerStopReason_Scheduling:
            oldStopTime = stopInfo->schedStopTime;
            break;
        default:
            oldStopTime = 0;
    }

    /* Set new stop time and enable it */
    if (sched)
    {
        stopInfo->schedStopTime = newStopTime;
        stopInfo->schedStopEnabled = 1;
    }
    else
    {
        stopInfo->cmdStopTime = newStopTime;
        stopInfo->cmdStopEnabled = 1;
    }

    /* Find updated earliest stop time */
    rclSchedulerFindEarliestStopTime(stopInfo);

    uint32_t stopTime;
    /* One of the stop times will be set, since we just set it */
    stopTime = (stopInfo->stopReason == RCL_SchedulerStopReason_Timeout) ?
        stopInfo->cmdStopTime : stopInfo->schedStopTime;

    /* Check if stop time has changed */
    if (oldStopReason != RCL_SchedulerStopReason_None || stopTime != oldStopTime)
    {
        /* Check if stop has been activated */
        if (rclSchedulerState.stopTimeState == RCL_SchedulerStopTimeState_Programmed)
        {
            /* Modify stop time and see if immediate stop is needed */
            immediateStop = RCL_Scheduler_setStopTimes();
            /* Notify handler that stop time has been changed */
            RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventStopTimesUpdated);
        }
    }

    return immediateStop;
}

static RCL_StopType rclSchedulerCancelStopTime(RCL_SchedulerStopInfo *stopInfo, bool sched)
{
    RCL_StopType immediateStop = RCL_StopType_None;

    /* Store current state of the stop info */
    RCL_SchedulerStopReason oldStopReason = stopInfo->stopReason;
    uint32_t oldStopTime;
    switch (stopInfo->stopReason)
    {
        case RCL_SchedulerStopReason_Timeout:
            oldStopTime = stopInfo->cmdStopTime;
            break;

        case RCL_SchedulerStopReason_Scheduling:
            oldStopTime = stopInfo->schedStopTime;
            break;
        default:
            oldStopTime = 0;
    }

    /* Disable applicable stop time */
    if (sched)
    {
        stopInfo->schedStopEnabled = 0;
    }
    else
    {
        stopInfo->cmdStopEnabled = 0;
    }

    /* Find updated earliest stop time */
    rclSchedulerFindEarliestStopTime(stopInfo);

    if (stopInfo->stopReason == RCL_SchedulerStopReason_None)
    {
        if (oldStopReason != RCL_SchedulerStopReason_None && rclSchedulerState.stopTimeState == RCL_SchedulerStopTimeState_Programmed)
        {
            /* Cancel stop time */
            if (stopInfo == &rclSchedulerState.hardStopInfo)
            {
                hal_cancel_hard_stop_time();
            }
            else
            {
                hal_cancel_graceful_stop_time();
            }
        }
    }
    else
    {
        uint32_t stopTime = (stopInfo->stopReason == RCL_SchedulerStopReason_Timeout) ?
            stopInfo->cmdStopTime : stopInfo->schedStopTime;

        /* Check if stop time has changed */
        if (stopTime != oldStopTime)
        {
            /* Check if stop has been activated */
            if (rclSchedulerState.stopTimeState == RCL_SchedulerStopTimeState_Programmed)
            {
                /* Modify stop time and see if immediate stop is needed */
                immediateStop = RCL_Scheduler_setStopTimes();
                /* Notify handler that stop time has been changed */
                RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventStopTimesUpdated);
            }
        }
    }

    return immediateStop;
}

/*
 *  ======== rclSchedulerFindEarliestStopTime ========
 */
static void rclSchedulerFindEarliestStopTime(RCL_SchedulerStopInfo *stopInfo)
{
    /* Find which stop time comes first */
    if (stopInfo->cmdStopEnabled)
    {
        if (stopInfo->schedStopEnabled)
        {
            uint32_t currentTime = RCL_Scheduler_getCurrentTime();
            if (RCL_Scheduler_isLater(currentTime, stopInfo->cmdStopTime))
            {
                if (RCL_Scheduler_isLater(currentTime, stopInfo->schedStopTime))
                {
                    /* Find difference from current time for each stop time */
                    uint32_t timeDiffSched = stopInfo->schedStopTime - currentTime;
                    uint32_t timeDiffCmd = stopInfo->cmdStopTime - currentTime;
                    if (timeDiffSched < timeDiffCmd)
                    {
                        /* Scheduler stop time is first */
                        stopInfo->stopReason = RCL_SchedulerStopReason_Scheduling;
                    }
                    else
                    {
                        /* Command stop time is first */
                        stopInfo->stopReason = RCL_SchedulerStopReason_Timeout;
                    }
                }
                else
                {
                    /* Scheduler stop time is already in the past */
                    stopInfo->stopReason = RCL_SchedulerStopReason_Scheduling;
                }
            }
            else
            {
                /* Command stop time is already in the past */
                stopInfo->stopReason = RCL_SchedulerStopReason_Timeout;
            }
        }
        else
        {
            /* Command stop time is the only one */
            stopInfo->stopReason = RCL_SchedulerStopReason_Timeout;
        }
    }
    else if (stopInfo->schedStopEnabled)
    {
        /* Scheduler stop time is the only one */
        stopInfo->stopReason = RCL_SchedulerStopReason_Scheduling;
    }
    else
    {
        stopInfo->stopReason = RCL_SchedulerStopReason_None;
    }
}

/*
 *  ======== RCL_Scheduler_postEvent ========
 */
bool RCL_Scheduler_postEvent(RCL_Command_Handle c, RCL_Events e)
{
    RCL_Command *cmd = (RCL_Command *)c;
    bool result = false;
    if (cmd != NULL)
    {
        uintptr_t key = HwiP_disable();
        if (cmd->status > RCL_CommandStatus_Queued && cmd->status < RCL_CommandStatus_Finished)
        {
            rclSchedulerState.postedRclEvents.value |= e.value | RCL_EventSoftwareTriggered.value;
            hal_trigger_command_fsm();
            result = true;
        }
        HwiP_restore(key);
    }
    return result;
}
