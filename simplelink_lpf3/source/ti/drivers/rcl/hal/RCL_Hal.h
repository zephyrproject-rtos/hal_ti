/*
 * Copyright (c) 2020-2025, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_hal_RCL_Hal__include
#define ti_drivers_rcl_hal_RCL_Hal__include

#include <stdint.h>

void RCL_Hal_initFsm(void (*setupFsmCb)(void), void (*schedFsmCb)(void),
                  void (*commandFsmCb)(void));
void RCL_Hal_triggerCommandFsm(void);
void RCL_Hal_triggerDispatchFsm(void);
void RCL_Hal_triggerSchedulerFsm(void);
uint32_t RCL_Hal_getCommandIfgReg(void);
uint32_t RCL_Hal_getDispatchIfgReg(void);
uint32_t RCL_Hal_getCurrentTime(void);
void RCL_Hal_enableSetupTimeIrq(void);
void RCL_Hal_setupSetupTime(uint32_t setupTime);
void RCL_Hal_setupStartTime(uint32_t startTime);
void RCL_Hal_setupPacketTimeout(uint32_t stopTime);
void RCL_Hal_setupHardStopTime(uint32_t stopTime);
void RCL_Hal_enableHardStopTimeIrq(void);
void RCL_Hal_disableHardStopTimeIrq(void);
void RCL_Hal_setupGracefulStopTime(uint32_t stopTime);
void RCL_Hal_enableGracefulStopTimeIrq(void);
void RCL_Hal_cancelSetupTime(void);
void RCL_Hal_cancelStartTime(void);
void RCL_Hal_cancelPacketTimeout(void);
void RCL_Hal_cancelHardStopTime(void);
void RCL_Hal_cancelGracefulStopTime(void);
void RCL_Hal_initDispatchRadioInterrupts(uint32_t mask);
void RCL_Hal_enableCommandRadioInterrupt(uint32_t mask);
void RCL_Hal_disableCommandRadioInterrupt(uint32_t mask);
void RCL_Hal_clearCommandRadioInterrupt(uint32_t mask);
void RCL_Hal_disableAllCommandRadioInterrupts(void);
void RCL_Hal_disableAllDispatchRadioInterrupts(void);
void RCL_Hal_temperatureInit(void);
int16_t RCL_Hal_getTemperature(void);
uint16_t RCL_Hal_getVddsVoltage(void);
uint32_t RCL_Hal_getHfxtRatio(void);
uint32_t RCL_Hal_getHfxtRatioDefault(void);

typedef enum {
    HAL_TIMER_EVT_NONE = 0,
    HAL_TIMER_EVT_SETUP = 1,
    HAL_TIMER_EVT_START = 2,
    HAL_TIMER_EVT_GRACEFUL_STOP = 3,
    HAL_TIMER_EVT_HARD_STOP = 4,
    HAL_TIMER_EVT_PACKET_TIMEOUT = 5,
} HalTimerEvent;

typedef enum {
    RCL_POWER_STANDBY_AWAKE = 0,
    RCL_POWER_XTAL_AVAILABLE = 1,
    RCL_POWER_STANDBY_ENTER = 2,
} RCL_PowerEvent;

HalTimerEvent RCL_Hal_checkClearTimerCompare(void);
void RCL_Hal_setupCmdStartCap(void);
void RCL_Hal_armCmdStartCap(void);
uint32_t RCL_Hal_getCmdStartCap(void);
void RCL_Hal_setupSyncFoundCap(void);
void RCL_Hal_armSyncFoundCap(void);
uint32_t RCL_Hal_getSyncFoundCap(void);
void RCL_Hal_setupCmdDoneCap(void);
void RCL_Hal_armCmdDoneCap(void);
uint32_t RCL_Hal_getCmdDoneCap(void);
void RCL_Hal_setRclClockEnable(uint16_t mask);
void RCL_Hal_clearRclClockEnable(uint16_t mask);
uint8_t RCL_Hal_setDcdcIpeakSetting(uint8_t setting);
void RCL_Hal_enableClkBuffer(void);
void RCL_Hal_powerSetStandbyConstraint(void);
void RCL_Hal_powerReleaseStandbyConstraint(void);
void RCL_Hal_powerSetSwTcxoUpdateConstraint(void);
void RCL_Hal_powerReleaseSwTcxoUpdateConstraint(void);
void RCL_Hal_powerOpen(void (*rclPowerNotifyFunction)(RCL_PowerEvent));
void RCL_Hal_powerClose(void);
void RCL_Hal_setTemperatureNotification(int16_t currentTemperature, uint16_t temperatureRange, void (*rclTemperatureNotify)(int16_t));
void RCL_Hal_stopTemperatureNotification(void);

#endif /* ti_drivers_rcl_hal_RCL_Hal__include */
