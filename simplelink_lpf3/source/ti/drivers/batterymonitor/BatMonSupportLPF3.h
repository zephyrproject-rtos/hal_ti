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
/*!****************************************************************************
 *  @file       BatMonSupportLPF3.h
 *
 *  @brief      BatMon Support layer
 *
 *  @anchor ti_drivers_batterymonitor_BatMonSupportLPF3_Overview
 *  # Overview #
 *  The purpose of the BatMon Support layer is to provide a way for multiple
 *  drivers to share the the BATMON hardware resource. The BATMON provides both
 *  temperature and supply voltage measurements. For this reason, both the
 *  Temperature driver and the Battery Monitor driver depends on the BATMON
 *  module.
 *
 *  Only a combined interrupt request for BATMON exists, and this needs to be
 *  shared by multiple drivers.
 *
 *  The two main services provided are:
 *      - Initializing the BATMON module
 *      - Dispatching the combined BATMON interrupt (AON_PMU_COMB) to registered
 *        callback functions
 *
 *  @note The BatMon Support layer is not intended to be used by the application.
 *  It is only intended to be used by TI drivers.
 *
 *  @anchor ti_drivers_batterymonitor_BatMonSupportLPF3_Usage
 *  # Usage #
 *
 *  ## Initialisation #
 *  The BatMon Support layer needs to be initialized by calling
 *  #BatMonSupportLPF3_init().
 *  #BatMonSupportLPF3_init() should be called once before using other BatMon
 *  Support APIs. Subsequent #BatMonSupportLPF3_init() calls will have no
 *  effect.
 *
 *  ## BATMON Event Callbacks #
 *  The main function of the BatMon Support layer is to dispatch the combined
 *  BATMON interrupt to registered callback functions when certain event flags
 *  are set.
 *
 *  ### Registering Event Callbacks
 *  There are two functions that register an event callback:
 *      - #BatMonSupportLPF3_registerTemperatureCb()
 *      - #BatMonSupportLPF3_registerBatteryCb()
 *
 *  Only one Temperature Callback and one Battery Callback can be registered,
 *  and registered callbacks cannot be unregistered.
 *
 *  @anchor ti_drivers_batterymonitor_BatMonSupportLPF3_Synopsis
 *  # Synopsis #
 *  @anchor ti_drivers_batterymonitor_BatMonSupportLPF3_Code
 *  @code
 *  #include <ti/drivers/BatMonSupportLPF3.h>
 *
 *  BatMonSupportLPF3_init();
 *
 *  BatMonSupportLPF3_registerTemperatureCb(PMUD_EVENT_TEMP_BELOW_LL | PMUD_EVENT_TEMP_OVER_UL, myTempCb);
 *  BatMonSupportLPF3_registerBatteryCb(PMUD_EVENT_BATT_BELOW_LL | PMUD_EVENT_BATT_OVER_UL, myBattCb);
 *  @endcode
 */
#ifndef ti_drivers_batterymonitor_BatMonSupportLPF3__include
#define ti_drivers_batterymonitor_BatMonSupportLPF3__include

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/utils/List.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  BatMon Support Configuration
 *
 *  A sample structure is shown below:
 *  @code
 *  const BatMonSupportLPF3_Config BatMonSupportLPF3_config = {
 *      .intNum = INT_CPUIRQ2,
 *      .intPriority = (~0),
 *      .intMux = EVTSVT_CPUIRQ2SEL_PUBID_AON_PMU_COMB,
 *  };
 *  @endcode
 */
typedef struct
{
    uint32_t intNum;      /*!< Device-specific interrupt number */
    uint32_t intPriority; /*!< Device-specific interrupt priority */
    uint32_t intMux;      /*!< Device-specific interrupt muxing */
} BatMonSupportLPF3_Config;

/*!
 *  @brief Function prototype for an event callback.
 *
 * The callback function is responsible for clearing the event flags associated
 * with the callback
 *
 *  @param [in]     eventFlags  The event flags read from PMUD.EVENT masked with
 *                              the event mask used when registering the
 *                              callback function in
 *                              #BatMonSupportLPF3_registerTemperatureCb()
 *                              or #BatMonSupportLPF3_registerBatteryCb().
 */
typedef void (*BatMonSupportLPF3_EventCb)(uint32_t eventFlags);

/*!
 *  @brief This function initializes the BatMon Support layer.
 *
 *  This function initializes the internal state of the BatMon Support layer.
 *  It must be called before calling any other BatMon Support functions.
 *  Subsequent calls to this function have no effect.
 */
extern void BatMonSupportLPF3_init(void);

/*!
 *  @brief This function registers a callback dedicated for the Temperature driver
 *
 *  @note This function does not set PMUD.EVENTMASK. The @c eventMask parameter
 *  is only used as a filter for when to to call the callback function defined
 *  by @c callback. The calling function is responsible to setting up BATMON to
 *  actually generate the desired events.
 *
 *  @param [in]     eventMask   Event mask used as filter for when to call the
 *                              callback function defined by @c callback.
 *                              In the AON_PMU_COMB ISR the value of PMUD.EVENT
 *                              will be AND'ed with @c eventMask, if the result
 *                              is non-zero the callback function will be
 *                              called.
 *
 *  @param [in]     callback    The callback function that is called by the
 *                              AON_PMU_COMB ISR if any of the event flags
 *                              defined by @c eventMask is set in PMUD.EVENT.
 */
extern void BatMonSupportLPF3_registerTemperatureCb(uint32_t eventMask, BatMonSupportLPF3_EventCb callback);

/*!
 *  @brief This function registers a callback dedicated for the Battery Monitor
 *  driver
 *
 *  @note This function does not set PMUD.EVENTMASK. The @c eventMask parameter
 *  is only used as a filter for when to to call the callback function defined
 *  by @c callback. The calling function is responsible to setting up BATMON to
 *  actually generate the desired events.
 *
 *  @param [in]     eventMask   Event mask used as filter for when to call the
 *                              callback function defined by @c callback.
 *                              In the AON_PMU_COMB ISR the value of PMUD.EVENT
 *                              will be AND'ed with @c eventMask, if the result
 *                              is non-zero the callback function will be
 *                              called.
 *
 *  @param [in]     callback    The callback function that is called by the
 *                              AON_PMU_COMB ISR if any of the event flags
 *                              defined by @c eventMask is set in PMUD.EVENT.
 */
extern void BatMonSupportLPF3_registerBatteryCb(uint32_t eventMask, BatMonSupportLPF3_EventCb callback);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_batterymonitor_BatMonSupportLPF3__include */
