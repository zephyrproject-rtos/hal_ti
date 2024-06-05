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

#ifndef ti_drivers_RCL_Scheduler_h__include
#define ti_drivers_RCL_Scheduler_h__include

#include <stdint.h>
#include <stddef.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/hal/hal.h>

/**
 *  Number of ticks in the given number of microseconds
 */
#define RCL_SCHEDULER_SYSTIM_US(x) (((uint32_t) (x)) * 4U)
/**
 *  Number of ticks in the given number of milliseconds
 */
#define RCL_SCHEDULER_SYSTIM_MS(x) (((uint32_t) (x)) * 4U * 1000U)


/* Timing constants */
#define ABS_START_TIME_OFFSET            RCL_SCHEDULER_SYSTIM_US(100U) /*!< Delay from scheduled start to start trigger to LRF */
#define IMM_START_TIME_OFFSET            RCL_SCHEDULER_SYSTIM_US(90U)  /*!< Delay from immediate start to start trigger to LRF */
#define RCL_SCHEDULER_MARGIN_ARM         RCL_SCHEDULER_SYSTIM_US(40U)  /*!< Time to prepare FIFO + PBE */
#define RCL_SCHEDULER_MARGIN_CONFIGURE   RCL_SCHEDULER_SYSTIM_US(76U)  /*!< Time to reload REGBANKs */
#define RCL_SCHEDULER_MARGIN_LOAD        RCL_SCHEDULER_SYSTIM_US(460U) /*!< Time to load TOPsm images */
#define RCL_SCHEDULER_SLEEP_CUTOFF       RCL_SCHEDULER_SYSTIM_MS(10U)  /*!< Time margin when not to arm LRF immediately */
#define RCL_SCHEDULER_TRIG_NOW_DELAY     RCL_SCHEDULER_SYSTIM_US(50U)  /*!< Delay to add to current time to allow start to be in the future */
#if defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R2) || defined(DeviceFamily_CC23X0R22) || defined(DeviceFamily_CC2340R53)
#define RCL_SCHEDULER_WAKEUP_MARGIN      RCL_SCHEDULER_SYSTIM_US(390U) /*!< Wakeup margin to allow for varying command and setup time */
#else
#define RCL_SCHEDULER_WAKEUP_MARGIN      RCL_SCHEDULER_SYSTIM_US(1000U)/*!< Wakeup margin to allow for varying command and setup time */
#endif

typedef enum {
    RCL_SchedulerStopReason_None = 0,       /*!< No stop active */
    RCL_SchedulerStopReason_Timeout = 1,    /*!< Command stop time is active  */
    RCL_SchedulerStopReason_Scheduling = 2, /*!< Scheduler stop is active */
    RCL_SchedulerStopReason_Api = 3,        /*!< API stop has been sent and will take precedence */
} RCL_SchedulerStopReason;

typedef enum {
    RCL_SchedulerStopTimeState_Init = 0,       /*!< Stop times not calculated or programmed */
    RCL_SchedulerStopTimeState_Found = 1,      /*!< Stop times calculated, but not programmed */
    RCL_SchedulerStopTimeState_Programmed = 2, /*!< Stop times calculated and programmed to timer */
} RCL_SchedulerStopTimeState;

typedef struct RCL_SchedulerStopInfo_s {
    uint32_t cmdStopEnabled                     : 1;
    uint32_t schedStopEnabled                   : 1;
    uint32_t apiStopEnabled                     : 1;
    RCL_SchedulerStopReason stopReason          : 2;
    uint32_t cmdStopTime;
    uint32_t schedStopTime;
} RCL_SchedulerStopInfo;

typedef struct RCL_SchedulerState_s {
    RCL_Command  *currCmd;
    uint32_t nextWantsStop                      : 1;
    RCL_SchedulerStopTimeState stopTimeState    : 2;
    RCL_SchedulerStopReason descheduleReason    : 2;
    RCL_Events postedRclEvents; /* Events to be handled by the command handler */
    uint32_t actualStartTime;
    RCL_SchedulerStopInfo hardStopInfo;
    RCL_SchedulerStopInfo gracefulStopInfo;
    uint16_t requestedPhyFeatures;
} RCL_SchedulerState;

extern RCL_SchedulerState rclSchedulerState;

/** @defgroup timingHandlerFunctions Timing Handler Functions
 *  These functions are meant mostly to be used by handlers and RCL itself
 *  @{
 */

/**
 *  @brief  Get relevant status when a command was stopped
 *
 *  Returns the status to be set for a command that was stopped with the given stop source,
 *  depending on what caused the stop
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  stopType Stop type observed
 *
 *  @return Command status that should be produced
 */
RCL_CommandStatus RCL_Scheduler_findStopStatus(RCL_StopType stopType);

/**
 *  @brief  Set start and stop time for LRF based on command
 *
 *  Sets start and stop times for LRF based on scheduled times
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  cmd Pointer to running command
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setStartStopTime(const RCL_Command *cmd);

/**
 *  @brief  Set start and stop time for LRF based on command with earliest start time
 *
 *  Sets start and stop times for LRF based on scheduled times, but delay start if needed due to hardware startup time
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  cmd Pointer to running command
 *
 *  @param  earliestStartTime Start at earliest at this time, or fail if delay not allowed
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setStartStopTimeEarliestStart(const RCL_Command *cmd, uint32_t earliestStartTime);

/**
 *  @brief  Set start and stop time for LRF
 *
 *  Sets start and stop times for LRF based on provided times
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  timing Start and stop times to set
 *
 *  @param  scheduling Scheduling type
 *
 *  @param  allowDelay True if start may be delayed; false if late start is an error
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setCustomStartStopTime(const RCL_CommandTiming *timing, RCL_ScheduleType scheduling, bool allowDelay);

/**
 *  @brief  Set start and stop time for LRF with earliest start time
 *
 *  Sets start and stop times for LRF based on provided times, but delay start if needed due to hardware startup time
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  timing Start and stop times to set
 *
 *  @param  scheduling Scheduling type
 *
 *  @param  allowDelay True if start may be delayed; false if late start is an error
 *
 *  @param  earliestStartTime Start at earliest at this time, or fail if delay not allowed
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setCustomStartStopTimeEarliestStart(const RCL_CommandTiming *timing, RCL_ScheduleType scheduling, bool allowDelay, uint32_t earliestStartTime);

/**
 *  @brief  Set stop time for LRF based on command when it does not need a start trigger
 *
 *  Sets stop times for LRF based on scheduled times, but do not program any start trigger
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  cmd Pointer to running command
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setCmdStopTimeNoStartTrigger(const RCL_Command *cmd);

/**
 *  @brief  Set new start time for LRF to now, after a previous start
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setNewStartNow(void);

/**
 *  @brief  Set new start time for LRF to given absolute time, after a previous start
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  startTime Absloute start time
 *
 *  @param  allowDelay True if start may be delayed; false if late start is an error
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setNewStartAbsTime(uint32_t startTime, bool allowDelay);

/**
 *  @brief  Set new start time for LRF to given time relative to previous LRF start
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param  relStartTime Start time relative to previous actual start time of LRF
 *
 *  @return Command status that should be produced if the command should end or RCL_CmdStatus_Active to go on
 */
RCL_CommandStatus RCL_Scheduler_setNewStartRelTime(uint32_t relStartTime);

/**
 *  @brief  Function to apply relevant stop times
 *
 *  Sets stop times for LRF based on scheduled times
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @return Stop type if stop needs to be applied immediately
 */
RCL_StopType RCL_Scheduler_setStopTimes(void);

/** @}
 */

/** @defgroup timingApiFunctions Timing API Functions
 *  These functions are useful as part of the API to RCL
 *  @{
 */

/**
 *  @brief  Find if a time instant occurs after another, allowing wrap-around
 *
 *  Checks if a time is before or after another. In the processing, a time is assumed to be before
 *  the reference if it is less than 1/8 of the full timer range (134 seconds) before it; otherwise
 *  it is assumed to be in the future. This means that the time presumed to be the latest should
 *  always be the second parameter (%chkTime)
 *
 *  @param  refTime Reference time
 *
 *  @param  chkTime Time to be checked
 *
 *  @return true if %chkTime comes after %refTime. false if %chkTime comes before %refTime or if they are equal.
 */
bool               RCL_Scheduler_isLater(uint32_t refTime, uint32_t chkTime);

/**
 *  @brief  Find the time difference between two times, allowing wrap-around
 *
 *  Finds the signed difference between two times, saturated at the maximum signed 32-bit integer
 *  value. In the processing, a time is assumed to be before the reference if it is less than 1/8
 *  of the full timer range (134 seconds) before it; otherwise
 *  it is assumed to be in the future.
 *
 *  @param  refTime Reference time
 *
 *  @param  chkTime Time to be checked
 *
 *  @return Time difference (%chkTime-%refTime) corrected for wrap-around.
 *          Saturated at 0x7FFFFFFF (8 min 57 sec).
 */
int32_t            RCL_Scheduler_delta(uint32_t refTime, uint32_t chkTime);

/**
 *  @brief  Get current time
 *
 *  @return Current SYSTIM time (0.25 us steps) usable for radio command timing
 */
static inline uint32_t RCL_Scheduler_getCurrentTime(void)
{
    return hal_get_current_time();
}

/**
 *  @brief  Set scheduler stop time
 *
 * Sets scheduler stop time for the given stop type, finds which of the
 * active stop times comes first, sets selection bits accordingly and
 * reprograms the stop time if it was already programmed.
 *
 *  @param  stopInfo Pointer to stop info for the relevant stop type
 *
 *  @param  schedStopTime New scheduler stop time to apply
 *
 *  @return Stop type if stop needs to be applied immediately
 */
RCL_StopType RCL_Scheduler_setSchedStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t schedStopTime);

/**
 *  @brief  Set command stop time
 *
 * Sets command stop time for the given stop type, finds which of the
 * active stop times comes first, sets selection bits accordingly and
 * reprograms the stop time if it was already programmed.
 *
 *  @param  stopInfo Pointer to stop info for the relevant stop type
 *
 *  @param  cmdStopTime New command stop time to apply
 *
 *  @return Stop type if stop needs to be applied immediately
 */
RCL_StopType RCL_Scheduler_setCmdStopTime(RCL_SchedulerStopInfo *stopInfo, uint32_t cmdStopTime);

/**
 *  @brief  Cancel scheduler stop time
 *
 * Cancels scheduler stop time for the given stop type, finds if there
 * is still an active stop time, cancels or reprograms the stop time
 * if it was already programmed.
 *
 *  @param  stopInfo Pointer to stop info for the relevant stop type
 *
 *  @return Stop type if stop needs to be applied immediately
 */
RCL_StopType RCL_Scheduler_cancelSchedStopTime(RCL_SchedulerStopInfo *stopInfo);

/**
 *  @brief  Cancel command stop time
 *
 * Cancels command stop time for the given stop type, finds if there
 * is still an active stop time, cancels or reprograms the stop time
 * if it was already programmed.
 *
 *  @param  stopInfo Pointer to stop info for the relevant stop type
 *
 *  @return Stop type if stop needs to be applied immediately
 */
RCL_StopType RCL_Scheduler_cancelCmdStopTime(RCL_SchedulerStopInfo *stopInfo);

/**
 * @brief Post event to command handler
 *
 * @param[in] c Command to post event to
 * @param[in] e Event(s) to post
 * @return true If command was active and event was posted
 * @return false If command was not active
 */
bool RCL_Scheduler_postEvent(RCL_Command_Handle c, RCL_Events e);

/** @}
 */

#endif
