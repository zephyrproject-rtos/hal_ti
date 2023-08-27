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
/** ============================================================================
 *  @file       BatteryMonitorLPF3.h
 *
 *  @brief      Battery Monitor driver implementation for the LPF3 family
 *
 *  The Battery Monitor driver on LPF3 is a part of the battery monitoring
 *  system in the Always On domain (AON). It periodically takes measurements of
 *  the supply voltage of the device and will issue interrupts if the configured
 *  upper limit or lower limit is crossed.
 *
 *  # Supply Voltage Resolution
 *  The battery monitoring system on LPF3 has a resolution of 1/256 V (around
 *  3.91 mV). The #BatteryMonitor_getVoltage() function will round the voltage
 *  to the nearest mV. For example, if the supply voltage is measured to be
 *  2003.91 mV, then #BatteryMonitor_getVoltage() will return 2004.
 *
 *  # Standby Power Mode Behavior #
 *  The supply voltage measurement remains active in standby power mode.
 *  The interrupt used by the battery monitor module is capable of bringing the
 *  device out of standby and into active mode to handle it. That means that
 *  an application will not miss a change in supply voltage just because the device
 *  has transitioned to standby power mode.
 *  While in standby, the supply voltage will only be sampled during a VDDR
 *  recharge pulse. This means that the sampling frequency in standby will be
 *  determined by the temperature as leakage increases with temperature and
 *  requires more frequent recharging of VDDR.
 */

#ifndef ti_drivers_batterymonitor_BatteryMonitorLPF3__include
#define ti_drivers_batterymonitor_BatteryMonitorLPF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/BatteryMonitor.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_batterymonitor_BatteryMonitorLPF3__include */