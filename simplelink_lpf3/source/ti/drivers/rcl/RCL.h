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

#ifndef ti_drivers_RCL_h__include
#define ti_drivers_RCL_h__include

#include <stdint.h>
#include <stddef.h>

#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/RCL_Types.h>
#include <ti/drivers/rcl/RCL_Client.h>
#include <ti/drivers/rcl/RCL_Event.h>
#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>

#include <ti/drivers/rcl/hal/hal.h>

#include <ti/drivers/dpl/SemaphoreP.h>

/**
 * @brief RCL power state
 *
 * Tracks when the RCL core has requested standby to be disallowed to the power driver.
 */
typedef enum {
    RCL_standbyAllow = 0,
    RCL_standbyDisallow,
} RCL_PowerState;

/**
 * @brief Global shared driver state
 */
typedef struct RCL_s {
    uint8_t                   numClients;
    uint8_t                   powerNotifyEnableCount;
    LRF_RadioState            lrfState;
    RCL_PowerState            powerState;
    const LRF_Config         *lrfConfig;
    RCL_Command              *nextCmd;
    RCL_Command              *doneCmd;
} RCL;

/**
 * @brief Initializes the RCL driver state
 *
 * Resets global state and initialize hardware.
 *
 * @note Must be called before using any other RCL API
 */
void RCL_init(void);

/**
 * @brief Initializes an RCL client instance
 *
 * @param[in] c - Client object struct to be initialized
 * @param[in] lrfConfig - Radio configuration to be used by client
 *
 * @return Instance %RCL_Handle handle or NULL
 */
RCL_Handle RCL_open(RCL_Client *c, const LRF_Config *lrfConfig);

/**
 * @brief Closes client instance and deallocates open resources
 *
 * @param[in] h - Client handle
 */
void RCL_close(RCL_Handle h);

/**
 * @brief Request RCL power notifications
 */
void RCL_openPowerNotifications(void);

/**
 * @brief Remove RCL power notification request
 */
void RCL_closePowerNotifications(void);

/**
 * @brief Submit RCL command object to be scheduled for execution
 *
 * This API returns immediately with either %RCL_CommandStatus_Error or the asynchronous
 * current state of the command.
 *
 * @param[in] h - Client handle
 * @param[in] c - Command handle
 *
 * @return %RCL_CommandStatus result of the submission
 */
RCL_CommandStatus RCL_Command_submit(RCL_Handle h, RCL_Command_Handle c);

/**
 * @brief Wait for a submitted command to complete.
 *
 * Uses %SemaphoreP_pend to block in the callers context.
 *
 * @pre This function must be called from a task context, with interrupts enabled.
 *
 * @param[in] c - Client handle
 */
RCL_CommandStatus RCL_Command_pend(RCL_Command_Handle c);

/**
 * @brief Stop a command
 *
 * Sends the message to try to stop a command. When the function returns, the command may still be
 * running. Depending on the stop type, the command may stop after some time. %RCL_Command_pend
 * may be used to wait for the command to finish.
 *
 * @param c [in] - Command handle
 * @param stopType [in] - Stop type; telling which situations the command will stop
 *
 * @return Status of the command; if the command is not finished, a wait is needed.
 */
RCL_CommandStatus RCL_Command_stop(RCL_Command_Handle c, RCL_StopType stopType);

/**
 * @brief Get the last valid RSSI value.
 *
 * This API returns the last valid RSSI value or a specific error status if the last obtained RSSI
 * value is no longer valid.
 *
 * @return Returns RSSI value, or LRF_RSSI_INVALID if the last obtained RSSI value is no longer valid
 * or if the radio is unavailable (e.g. in the middle of a Tx operation).
 */
int8_t RCL_readRssi(void);

#endif
