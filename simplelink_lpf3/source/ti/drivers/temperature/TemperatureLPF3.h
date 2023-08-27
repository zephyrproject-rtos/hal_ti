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
 *  @file       TemperatureLPF3.h
 *
 *  @brief      Temperature driver implementation for the Low Power F3 family
 *
 *  The temperature driver on Low Power F3 devices is a part of the battery
 *  monitoring system in AON (always on). It periodically takes measurements of
 *  the temperature of the chip and will issue interrupts if the configured
 *  upper limit or lower limit is crossed.
 *
 *  # Standby Power Mode Behavior #
 *  The temperature measurement is active while in standby power mode as well.
 *  The interrupt used by the temperature module is capable of bringing the
 *  device out of standby and into active mode to handle it. That means that an
 *  application will not miss a change in temperature just because the device
 *  has transitioned to standby power mode. While in standby, the temperature
 *  will only be sampled during a VDDR recharge pulse. This means that the
 *  sampling frequency in standby will be determined by the temperature as
 *  leakage increases with temperature and requires more frequent recharging of
 *  VDDR.
 */

#ifndef ti_drivers_temperature_TemperatureLPF3__include
#define ti_drivers_temperature_TemperatureLPF3__include

#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/Temperature.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief Temperature driver configuration struct for Low Power F3 devices
 *
 *  This struct globally controls configuration settings for the Temperature
 *  driver.
 *
 *  The Low Power F3 Temperature driver implementation links against a structure
 *  of this type named TemperatureLPF3_config.
 *
 *  This structure must be allocated and configured by the application. If
 *  SysConfig is used, this struct will be automatically created when the
 *  Temperature module is used in SysConfig.
 */
typedef struct
{
    /*! @brief  Temperature sensor's interrupt priority.
     *
     *  The interrupt line is shared between the temperature sensor and the
     *  battery voltage monitor on Low Power F3 devices
     *
     *  The Low Power F3 devices use either three or two priority bits,
     *  depending on the device. That means ~0 has the same effect as (7 << 5)
     *  or (3 << 6), respectively.
     *
     *  Setting the priority to 0 is not supported by this driver.
     *
     *  HWI's with priority 0 ignore the HWI dispatcher to support zero-latency
     *  interrupts, thus invalidating the critical sections in this driver.
     */
    uint8_t intPriority;
} TemperatureLPF3_Config;

/**
 * @brief Enable thermal shutdown monitoring
 *
 * Set threshold for thermal shutdown, in degrees Celsius, and enable thermal shutdown monitoring. Once the
 * temperature of the device reaches or goes above @c shutdownThreshold, the driver will invoke
 * an internal callback-function that will invoke @ref TemperatureLPF3_triggerThermalShutdown. If a custom shutdown
 * procedure is required, one would need to install their own callback using @ref Temperature_registerNotifyHigh,
 * and optionally call @ref TemperatureLPF3_triggerThermalShutdown as the last thing in the custom callback.
 *
 * @param shutdownThreshold Thermal shutdown threshold in degrees Celsius
 */
void TemperatureLPF3_enableTSDMonitoring(int16_t shutdownThreshold);

/**
 * @brief Disable thermal shutdown monitoring
 *
 * Disable thermal shutdown monitoring. To re-enable, @ref TemperatureLPF3_enableTSDMonitoring must be called again
 * with the desired temperature threshold.
 */
void TemperatureLPF3_disableTSDMonitoring(void);

/**
 * @brief Trigger thermal shutdown
 *
 * Immediately trigger thermal shutdown, and enable the thermal shutdown comparator. The device will remain in
 * reset for as long as the comparator is high (i.e for as long as the temperature is above 95 degrees C.
 * See technical reference manual for more details. This function is called if TSD monitoring is enabled through
 * @ref TemperatureLPF3_enableTSDMonitoring and the given threshold temperature is reached. The threshold should
 * always be set to greater than 95, or the device will immediately come back out of reset. Typically, the threshold
 * would be set near the maximum operating temperature of 125 degrees C.
 *
 * @note Calling this function will immediately bring the device into reset
 */
void TemperatureLPF3_triggerThermalShutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_temperature_TemperatureLPF3__include */
