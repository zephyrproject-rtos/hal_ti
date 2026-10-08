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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogWFF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/watchdog.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_hostmcu_aon.h)

/* Function prototypes */
void WatchdogWFF3_clear(Watchdog_Handle handle);
void WatchdogWFF3_close(Watchdog_Handle handle);
int_fast16_t WatchdogWFF3_control(Watchdog_Handle handle, uint_fast16_t cmd, void *arg);
void WatchdogWFF3_init(Watchdog_Handle handle);
Watchdog_Handle WatchdogWFF3_open(Watchdog_Handle handle, Watchdog_Params *params);
int_fast16_t WatchdogWFF3_setReload(Watchdog_Handle handle, uint32_t ticks);
uint32_t WatchdogWFF3_convertMsToTicks(Watchdog_Handle handle, uint32_t milliseconds);

/* WatchdogWFF3 internal functions */
static void WatchdogWFF3_initHw(Watchdog_Handle handle);

/* Watchdog function table for WFF3 implementation */
const Watchdog_FxnTable WatchdogWFF3_fxnTable = {WatchdogWFF3_clear,
                                                 WatchdogWFF3_close,
                                                 WatchdogWFF3_control,
                                                 WatchdogWFF3_init,
                                                 WatchdogWFF3_open,
                                                 WatchdogWFF3_setReload,
                                                 WatchdogWFF3_convertMsToTicks};

#define LFCLK_FREQ_HZ         32768    /* LFCLK frequency in Hz */
#define MAX_RELOAD_TICKS      0x7FFFFF /* Maximum possible reset value in ticks */
#define MIN_RELOAD_TICKS      0x1      /* Minimum allowable reload value in ticks */
#define MS_PER_SEC            1000     /* Millisecond to second ratio */
/* The reload value has a resolution of 256 (8 bits)/LFCLK_FREQ_HZ = 7.8125 ms.
 * By taking the inverse we get the tick frequency and avoid working with
 * decimal values. This division by 256 is possible without losing any precision
 * because 32768 is divisible by 256.
 */
#define WATCHDOG_TICK_FREQ_HZ (LFCLK_FREQ_HZ >> (HOSTMCU_AON_CFGWDT_THR_S))

/*
 *  ======== WatchdogWFF3_clear ========
 */
void WatchdogWFF3_clear(Watchdog_Handle handle)
{
    WatchdogReset();
}

/*
 *  ======== WatchdogWFF3_close ========
 */
void WatchdogWFF3_close(Watchdog_Handle handle)
{
    WatchdogWFF3_Object *object = handle->object;
    object->isOpen              = false;

    WatchdogDisableResetEvent();
    WatchdogStopSequence();
}

/*
 *  ======== WatchdogWFF3_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int_fast16_t WatchdogWFF3_control(Watchdog_Handle handle, uint_fast16_t cmd, void *arg)
{
    /* Not supported on WFF3 */
    return Watchdog_STATUS_UNDEFINEDCMD;
}

/*
 *  ======== WatchdogWFF3_init ========
 */
void WatchdogWFF3_init(Watchdog_Handle handle)
{
    WatchdogWFF3_Object *object = handle->object;
    object->isOpen              = false;
}

/*
 *  ======== WatchdogWFF3_open ========
 */
Watchdog_Handle WatchdogWFF3_open(Watchdog_Handle handle, Watchdog_Params *params)
{
    uintptr_t key;
    WatchdogWFF3_Object *object;
    WatchdogWFF3_HWAttrs const *hwAttrs;

    /* Return if the watchdog is configured to stall when debugging because this
     * functionality is not supported.
     */
    if (params->debugStallMode == Watchdog_DEBUG_STALL_ON)
    {
        return NULL;
    }

    /* Return if an unsupported reset mode is configured */
    if (params->resetMode != Watchdog_RESET_ON)
    {
        return NULL;
    }

    /* Get the pointer to the object and hwAttrs */
    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Return if the reload value exceeds or falls below the allowed range */
    if (WatchdogWFF3_convertMsToTicks(handle, hwAttrs->reloadValue) == 0)
    {
        return NULL;
    }

    /* Disable preemption while checking if the Watchdog is open */
    key = HwiP_disable();

    /* Check if the Watchdog is open already */
    if (object->isOpen == true)
    {
        HwiP_restore(key);
        return NULL;
    }

    object->isOpen = true;
    HwiP_restore(key);

    /* Callback is not supported (HW reserved), make sure interrupt is disabled.
     */
    HwiP_disableInterrupt(INT_HOST_ELP_TMR_WAKEUP_REQ);

    /* Initialize the watchdog hardware */
    WatchdogWFF3_initHw(handle);

    /* Return handle of the Watchdog object */
    return handle;
}

/*
 *  ======== WatchdogWFF3_setReload ========
 */
int_fast16_t WatchdogWFF3_setReload(Watchdog_Handle handle, uint32_t ticks)
{
    WatchdogStopSequence();

    WatchdogSetResetThreshold(ticks);

    WatchdogStartSequence();

    return Watchdog_STATUS_SUCCESS;
}

/*
 *  ======== WatchdogWFF3_initHw ========
 *  This function initializes the Watchdog hardware module.
 *
 *  @pre    Function assumes that the Watchdog handle is pointing to a hardware
 *          module which has already been opened.
 */
static void WatchdogWFF3_initHw(Watchdog_Handle handle)
{
    uint32_t tickValue;
    WatchdogWFF3_HWAttrs const *hwAttrs;

    /* Get the pointer to the hwAttrs. */
    hwAttrs = handle->hwAttrs;

    /* Configure the timer to be controlled by software. This makes it
     * operational during sleep and active states, and allows to manually
     * control it in software.
     */
    WatchdogSetSwMode();

    /* Stop the timer before updating the reload value. */
    WatchdogStopSequence();

    /* Convert milliseconds to reset threshold ticks. */
    tickValue = WatchdogWFF3_convertMsToTicks(handle, hwAttrs->reloadValue);

    /* Set and enable the threshold. */
    WatchdogSetResetThreshold(tickValue);
    WatchdogEnableResetEvent();

    /* Start the Watchdog counter. */
    WatchdogStartSequence();
}

/*
 *  ======== WatchdogWFF3_convertMsToTicks ========
 *  This function converts the input value from milliseconds to watchdog timer
 *  reset threshold ticks.
 */
uint32_t WatchdogWFF3_convertMsToTicks(Watchdog_Handle handle, uint32_t milliseconds)
{
    uint32_t tickValue;
    uint32_t maxConvertMs;
    uint32_t minConvertMs;

    /* Determine maximum possible period, rounding down. Avoid overflow of the
     * intermediate multiplication.
     */
    maxConvertMs = (MAX_RELOAD_TICKS / WATCHDOG_TICK_FREQ_HZ) * MS_PER_SEC +
                   ((MAX_RELOAD_TICKS % WATCHDOG_TICK_FREQ_HZ) * MS_PER_SEC) / WATCHDOG_TICK_FREQ_HZ;

    /* Determine minimum allowed period, rounding up */
    minConvertMs = ((MIN_RELOAD_TICKS * MS_PER_SEC + (WATCHDOG_TICK_FREQ_HZ - 1)) / WATCHDOG_TICK_FREQ_HZ);

    /* Convert milliseconds to watchdog timer ticks as long as the value doesn't
     * exceed the maximum possible period or falls below the minimum allowed
     * period.
     */
    if ((milliseconds > maxConvertMs) || (milliseconds < minConvertMs))
    {
        tickValue = 0; /* Return zero to indicate overflow or underflow */
    }
    else
    {
        /* Avoid overflow of the intermediate multiplication when calculating
         * tickValue and round to the nearest integer.
         */
        tickValue = (milliseconds / MS_PER_SEC) * WATCHDOG_TICK_FREQ_HZ +
                    ((milliseconds % MS_PER_SEC) * WATCHDOG_TICK_FREQ_HZ + (MS_PER_SEC / 2)) / MS_PER_SEC;
    }

    return tickValue;
}
