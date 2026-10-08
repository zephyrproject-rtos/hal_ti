/*
 * Copyright (c) 2024-2025, Texas Instruments Incorporated
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
/*!****************************************************************************
 *  @file       WatchdogWFF3.h
 *
 *  @brief      Watchdog driver implementation for WiFi F3 devices
 *
 *  # Driver include #
 *  The Watchdog header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/Watchdog.h>
 *  #include <ti/drivers/watchdog/WatchdogWFF3.h>
 *  @endcode
 *
 *  Refer to @ref Watchdog.h for a complete description of APIs.
 *
 *  # Overview #
 *
 *  The general Watchdog API should be used in application code, i.e.
 *  #Watchdog_open() should be used instead of WatchdogWFF3_open(). The board
 *  file will define the device specific config, and casting in the general API
 *  will ensure that the correct device specific functions are called.
 *
 *  # General Behavior #
 *  This Watchdog driver implementation is designed to operate on a WFF3 device.
 *  Before using the Watchdog on WFF3, the Watchdog driver is initialized by
 *  calling #Watchdog_init(). The Watchdog HW is configured by calling
 *  #Watchdog_open(). Once opened, the Watchdog will count up from zero to the
 *  reload value specified in #WatchdogWFF3_HWAttrs. If it times out, a reset
 *  signal will be generated. To prevent a reset, #Watchdog_clear() must be
 *  called to clear the timer, or #Watchdog_close() to stop the Watchdog timer.
 *
 *  @note
 *  In these devices, the Watchdog Timer operates differently: it counts up to
 *  the reload value (reset threshold) instead of counting down from a reload
 *  value to zero as described in the general API. However, the device-specific
 *  API abstracts this difference, allowing the user to interact with the
 *  Watchdog Timer as though it behaves as described in the general API. Be
 *  aware that internally, the implementation and naming conventions may differ
 *  to accommodate this behavior.
 *
 *  The Watchdog counts up at the rate of the device clock LFCLK divided by 2^8,
 *  which results in a frequency of 128 Hz. The watchdog driver assumes LFCLK is
 *  running at 32768 Hz and will not produce accurate timeouts at other
 *  frequencies. LFOSC is an inherently inaccurate clock source and will present
 *  variations around the target 32768 Hz frequency. These inaccuracies have to
 *  be taken into consideration at the application level.
 *
 *  The reload value which the Watchdog timer counts up to may be changed during
 *  runtime using #Watchdog_setReload(). This value should be specified in
 *  Watchdog threshold ticks and should not exceed "2^23 - 1" or fall below "1".
 *  At the rate of 128 Hz, the resolution of each threshold tick is 7.8125 ms.
 *  This corresponds to a maximum timeout period of 65535992 ms and a minimum
 *  period of 7.8125 ms. Calling #Watchdog_setReload() will also reset counter
 *  value.
 *
 *  The function #Watchdog_convertMsToTicks() can be used to convert from ms
 *  to Watchdog threshold ticks. If the converted value exceeds or falls below
 *  the allowed range, a zero (0) will be returned to indicate
 *  overflow/underflow. The period has a resolution of 7.8125 ms, which imposes
 *  limitations on achieving certain exact values. When a requested period
 *  cannot be precisely implemented, the system will automatically adjust to the
 *  nearest possible value within the resolution. For instance, if a period of
 *  22 ms is specified, the actual implemented period will be 23.4375 ms.
 *
 *  #Watchdog_close() can be used to stop the Watchdog timer.
 *
 *  <b>No</b> WFF3 specific command exists. Any call to #Watchdog_control() will
 *  return #Watchdog_STATUS_UNDEFINEDCMD.
 *
 *  The Watchdog module available on WFF3 devices does not support debug
 *  stalling. Therefore, the #Watchdog_Params.debugStallMode parameter in the
 *  #Watchdog_Params struct must be Watchdog_DEBUG_STALL_OFF will. Calling
 *  #Watchdog_open() with the debug stall mode to Watchdog_DEBUG_STALL_ON will
 *  fail and return a NULL handle.
 *
 *  The Watchdog driver available for WFF3 only supports reset enabled mode, it
 *  cannot be used as a timer interrupt, that is, specifying a callback function
 *  is not supported by the driver.
 *
 *  # Power Management #
 *  Once started, the Watchdog will keep running in Active, Idle and Standby
 *  mode. Note that the Watchdog timer is restarted by the Power driver whenever
 *  the device enters Standby. If the device remains in Standby for a duration
 *  longer than the Watchdog timeout, the device will reset.
 *
 *  # Supported Functions #
 *  | Generic API Function         | API Function                    | Description                               |
 *  |------------------------------|---------------------------------|-------------------------------------------|
 *  | #Watchdog_init()             | WatchdogWFF3_init()             | Initialize Watchdog driver                |
 *  | #Watchdog_open()             | WatchdogWFF3_open()             | Initialize HW and set system dependencies |
 *  | #Watchdog_clear()            | WatchdogWFF3_clear()            | Reload Watchdog counter                   |
 *  | #Watchdog_setReload()        | WatchdogWFF3_setReload()        | Update timer reload value in clock ticks  |
 *  | #Watchdog_convertMsToTicks() | WatchdogWFF3_convertMsToTicks() | Converts milliseconds to clock ticks      |
 *  | #Watchdog_close()            | WatchdogWFF3_close()            | Stop Watchdog timer                       |
 *
 *  @note All calls should go through the generic API. Please refer to @ref
 *  Watchdog.h for a complete description of the generic APIs.
 *
 *  # Use Cases #
 *  ## Basic Watchdog #
 *  In this basic watchdog example, the application is expected to start the
 *  Watchdog timer by calling #Watchdog_open(). If needed, #Watchdog_setReload()
 *  may be called to change the timeout period. If all monitored tasks are doing
 *  alright, #Watchdog_clear() should be called regularly to reload the counter
 *  so as to restart the timeout period and to avoid the Watchdog resetting the
 *  device. If the #Watchdog_clear() is missed and the Watchdog timer is allowed
 *  to timeout, the device will be reset.
 *
 *  The following code example shows how to correctly initialize the driver's
 *  parameters, start the Watchdog timer and modify at runtime the timeout
 *  period.
 *  @code
 *
 *  Watchdog_Handle handle;
 *  Watchdog_Params params;
 *  uint32_t tickValue;
 *
 *  Watchdog_init();
 *  Watchdog_Params_init(&params);
 *  params.debugStallMode = Watchdog_DEBUG_STALL_OFF;
 *  handle = Watchdog_open(Watchdog_configIndex, &params);
 *  // set timeout period to 100 ms
 *  tickValue = Watchdog_convertMsToTicks(handle, 100);
 *  Watchdog_setReload(handle, tickValue);
 *
 *  @endcode
 */

#ifndef ti_drivers_watchdog_WatchdogWFF3__include
#define ti_drivers_watchdog_WatchdogWFF3__include

#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/Watchdog.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @}*/

/*! @brief  Watchdog function table for WFF3 */
extern const Watchdog_FxnTable WatchdogWFF3_fxnTable;

/*!
 *  @brief  Watchdog hardware attributes for WFF3
 */
typedef struct
{
    uint32_t reloadValue; /*!< Reload value in milliseconds for Watchdog */
} WatchdogWFF3_HWAttrs;

/*!
 *  @brief      Watchdog Object for WFF3
 *
 *  Not to be accessed by the user.
 */
typedef struct
{
    bool isOpen; /* Flag for open/close status */
} WatchdogWFF3_Object;

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_watchdog_WatchdogWFF3__include */
