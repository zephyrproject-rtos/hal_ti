/*
 * Copyright (c) 2020-2023, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_Command_h__include
#define ti_drivers_RCL_Command_h__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/rcl/RCL_Types.h>
#include <ti/drivers/rcl/RCL_Event.h>
#include <ti/drivers/rcl/LRF.h>

/**
 *  @brief Command handler function type
 */
typedef RCL_Events (*RCL_CommandHandler)(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEvents);

/**
 *  @brief Callback function type
 */
typedef void (*RCL_Callback)(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEvents);

/**
 *  @brief Command runtime structure
 *
 *  Holds information on running the command
 */
struct RCL_CommandRuntime_s {
    RCL_CommandHandler handler;         /*!< Command handler to use for this command */
    RCL_Client *client;                 /*!< Client */
    LRF_Events lrfCallbackMask;         /*!< Callbacks enabled for events directly from LRF */
    RCL_Events rclCallbackMask;         /*!< Callbacks enabled for events generated in RCL */
    RCL_Callback callback;              /*!< Callback function */
};

/**
 *  @brief Command timing structure
 *
 *  Holds information on the timing of the command
 */
struct RCL_CommandTiming_s {
    uint32_t absStartTime;        /*!< Unless timing is Schedule_Now: Start time of the command on SYSTIM (0.25 us steps) */
    uint32_t relMinTime;          /*!< For scheduler: Minimum time command must be allowed to run (0.25 us steps). Not supported in this version. */
    int32_t  relGracefulStopTime; /*!< Time to initiate graceful stop of command. If negative: Relative to hardStopTime, otherwise relative to startTime (0.25 us steps). 0: Not used */
    uint32_t relHardStopTime;     /*!< Time to stop the command as soon as possible; relative to start time (0.25 us steps). 0: Not used. */
};

/**
 *  @brief Command status
 *
 *  Gives information on the command, and if finished, how it finished.
 */
typedef enum RCL_CommandStatus_e {
    RCL_CommandStatus_Idle = 0,                     /*!< Command is not yet run. This state is mandatory when submitting. */
    RCL_CommandStatus_Queued,                       /*!< Command is queued, but pending end of previous command */
    RCL_CommandStatus_Scheduled,                    /*!< Command is scheduled, pending start time. */
    RCL_CommandStatus_Active,                       /*!< Command is currently running. */
    RCL_CommandStatus_Suspended,                    /*!< Command is suspended and will resume once the othe running commands have finished */
    RCL_CommandStatus_Deferred,                     /*!< Command is deferred. */
    RCL_CommandStatus_Finished = 0x10,              /*!< Command has finished normally */
    RCL_CommandStatus_ChannelIdle,                  /*!< Channel assessment has finished with channel idle */
    RCL_CommandStatus_ChannelBusy,                  /*!< Channel assessment has finished with channel busy */
    RCL_CommandStatus_RxTimeout,                    /*!< Command timed out waiting for sync */
    RCL_CommandStatus_NoSync,                       /*!< Command timed out waiting for a returned packet from peer device */
    RCL_CommandStatus_RxErr,                        /*!< Command ended due to errors with the received packet (e.g, CRC errors) */
    RCL_CommandStatus_RejectedStart,                /*!< Command was rejected start due to scheduling parameters */
    RCL_CommandStatus_UnexpectedMdrRx,              /*!< Command ended because an MDR packet was received when we have MDR disabled */
    RCL_CommandStatus_DescheduledApi = 0x31,        /*!< Command was descheduled before starting running in the radio because stop API was called */
    RCL_CommandStatus_DescheduledScheduling,        /*!< Command was descheduled before starting running in the radio due to scheduling of another command */
    RCL_CommandStatus_GracefulStopTimeout = 0x34,   /*!< Command ended because graceful stop time was reached */
    RCL_CommandStatus_GracefulStopApi,              /*!< Command ended because stop API was called with RCL_StopType_Graceful argument */
    RCL_CommandStatus_GracefulStopScheduling,       /*!< Command ended due to scheduling where interrupting command had RCL_ConflictPolicy_Polite */
    RCL_CommandStatus_HardStopTimeout = 0x38,       /*!< Command ended because hard stop time was reached */
    RCL_CommandStatus_HardStopApi,                  /*!< Command ended because stop API was called with RCL_StopType_Hard argument */
    RCL_CommandStatus_HardStopScheduling,           /*!< Command ended due to scheduling where interrupting command had RCL_ConflictPolicy_AlwaysInterrupt */
    RCL_CommandStatus_Connect = 0x40,               /*!< Command has finished and a connection may be established (BLE5 advertiser and initiator) */
    RCL_CommandStatus_MaxNak,                       /*!< Command ended because more subsequent NAKs than supported were received (BLE5) */
    RCL_CommandStatus_MaxAuxWaitTimeExceeded,       /*!< Command ended because the wait time for a new packet following an AuxPtr was exceeded (BLE5 scanner and initiator) */
    RCL_CommandStatus_Error  = 0x80,                /*!< Command ended with unknown error */
    RCL_CommandStatus_Error_Setup,                  /*!< Command ended because of an error in the setup */
    RCL_CommandStatus_Error_Param,                  /*!< Command ended because of an error with a parameter */
    RCL_CommandStatus_Error_MissingTxBuffer,        /*!< Command ended because no TX buffer was available when required */
    RCL_CommandStatus_Error_TxBufferCorruption,     /*!< Command ended because of errors in TX buffer structure */
    RCL_CommandStatus_Error_RxBufferCorruption,     /*!< Command ended because of errors in RX buffer structure */
    RCL_CommandStatus_Error_StartTooLate,           /*!< Command ended because start time was in the past */
    RCL_CommandStatus_Error_TxFifo,                 /*!< Command ended because of underflow of TX FIFO */
    RCL_CommandStatus_Error_RxFifo,                 /*!< Command ended because of unsupported overflow of RX FIFO (no buffer to store packets) */
    RCL_CommandStatus_Error_Synth,                  /*!< Command ended because of synth programming error */
    RCL_CommandStatus_Error_UnknownOp,              /*!< Command ended because radio did not recognize command; probably wrong image for given command */
    RCL_CommandStatus_Error_AlreadySubmitted,       /*!< Command is already submitted and planned or running and can't be submitted again without calling stop first */
    RCL_CommandStatus_Error_CommandQueueFull        /*!< Command was not submitted because there is no space in the pending commands queue */
} RCL_CommandStatus;

/**
 * Helper macros to compare command status
 */
#define RCL_CommandStatus_isAnyStop(x)           (((x) >= RCL_CommandStatus_DescheduledApi) && ((x) <= RCL_CommandStatus_HardStopScheduling))
#define RCL_CommandStatus_isAnyDescheduled(x)    (((x) >= RCL_CommandStatus_DescheduledApi) && ((x) <= RCL_CommandStatus_DescheduledScheduling))
#define RCL_CommandStatus_isAnyGracefulStop(x)   (((x) >= RCL_CommandStatus_GracefulStopTimeout) && ((x) <= RCL_CommandStatus_GracefulStopScheduling))
#define RCL_CommandStatus_isAnyHardStop(x)       (((x) >= RCL_CommandStatus_HardStopTimeout) && ((x) <= RCL_CommandStatus_HardStopScheduling))
#define RCL_CommandStatus_isAnyTimeoutStop(x)    (((x) == RCL_CommandStatus_GracefulStopTimeout) || ((x) == RCL_CommandStatus_HardStopTimeout))
#define RCL_CommandStatus_isAnyApiStop(x)        (((x) == RCL_CommandStatus_DescheduledApi) || ((x) == RCL_CommandStatus_GracefulStopApi) || ((x) == RCL_CommandStatus_HardStopApi))
#define RCL_CommandStatus_isAnySchedulingStop(x) (((x) == RCL_CommandStatus_DescheduledScheduling) || ((x) == RCL_CommandStatus_GracefulStopScheduling) || ((x) == RCL_CommandStatus_HardStopScheduling))

/**
 *  @brief Stop types
 *
 *  Type of stop to perform
 */
typedef enum {
    RCL_StopType_None = 0,        /*!< No stop requested */
    RCL_StopType_DescheduleOnly,  /*!< Stop a command that is queued or pending start, but do not stop it from running */
    RCL_StopType_Graceful,        /*!< Stop the command gracefully, that is finish a packet or transaction in progress before ending */
    RCL_StopType_Hard,            /*!< Stop the command as soon as possible */
} RCL_StopType;

/**
 *  @brief Schedule type
 *
 *  The type of scheduling used for a command
 */
typedef enum  {
    RCL_Schedule_Now = 0,               /*!< Schedule the command to start as soon as possible */
    RCL_Schedule_AbsTime = 1,           /*!< Schedule command to start at a given time; give error if delays occur */
} RCL_ScheduleType;

/**
 *  @brief Conflict resolution policy
 *
 *  How will this command interact with an already running and overlapping command
 */
typedef enum {
    RCL_ConflictPolicy_AlwaysInterrupt = 0, /*!< Always stop a running command if necessary to run this command */
    RCL_ConflictPolicy_Polite = 1,          /*!< Stop a running command unless it is communicating, i.e. transmitting or is actively receiving */
    RCL_ConflictPolicy_NeverInterrupt = 2,  /*!< Never stop an ongoing command */
} RCL_ConflictPolicy;

/**
 *  @brief General command
 *
 *  Fields common for all commands
 */
struct RCL_Command_s {
    uint16_t cmdId;                         /*!< Command ID */
    uint16_t phyFeatures;                   /*!< PHY feature selector; use 0 if only one PHY */
    RCL_ScheduleType scheduling : 8;        /*!< Scheduling type */
    RCL_CommandStatus status    : 8;        /*!< Status of command */
    RCL_ConflictPolicy conflictPolicy : 8;  /*!< Conflict resolution policy */
    bool allowDelay;                        /*!< Start may be delayed */
    RCL_CommandRuntime runtime;             /*!< Runtime information */
    RCL_CommandTiming timing;               /*!< Timing information */
};

#define RCL_Command_Default(_id, _handler)                  \
{                                                           \
    .cmdId   = _id,                                         \
    .phyFeatures = 0,                                       \
    .scheduling = RCL_Schedule_Now,                         \
    .status  = RCL_CommandStatus_Idle,                      \
    .conflictPolicy = RCL_ConflictPolicy_AlwaysInterrupt,   \
    .allowDelay = false,                                    \
    .runtime = {                                            \
        .handler = _handler,                                \
    },                                                      \
    .timing = {                                             \
        .absStartTime = 0,                                  \
        .relGracefulStopTime = 0,                           \
        .relHardStopTime = 0,                               \
    },                                                      \
}
#define RCL_Command_DefaultRuntime(_id, _handler) (RCL_Command) RCL_Command_Default(_id, _handler)

/**
 * @brief Type for TX power
 *
 * The wanted TX power to program; the RCL will select the highest available power smaller than or
 * equal to the requested setting.
 *
 * Special settings:
 * %LRF_TxPower_Use_Min: Use minimum available TX power
 * %LRF_TxPower_Use_Max: Use maximum available TX power
 * %LRF_TxPower_Use_Raw: Use a raw TX power register setting given with %RCL_Command_setRawTxPower()
 * %LRF_TxPower_None:    Do not write TX power
 */
typedef LRF_TxPowerTable_Index RCL_Command_TxPower;

/**
 * @brief Set raw TX power
 *
 * Set the TX power to be written directly into the TX power register applicable to the chip.
 * The setting only applies to commands where the TX power is set to %LRF_TxPower_Use_Raw
 */
static inline void RCL_Command_setRawTxPower(uint32_t registerSetting, uint32_t temperatureCoefficient)
{
    LRF_setRawTxPower(registerSetting, temperatureCoefficient);
}

#endif /* ti_drivers_RCL_Command_h__include */
