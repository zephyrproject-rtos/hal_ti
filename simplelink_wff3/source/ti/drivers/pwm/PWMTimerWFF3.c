/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
/*!*****************************************************************************
 *  @file       PWMTimerWFF3.c
 *  @brief      WFF3 implementation of ti/drivers/PWM.h
 *
 *  # Overview #
 *  WFF3 PWM driver using the built-in GPTimer.
 *
 *******************************************************************************
 */

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/ClockP.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOWFF3.h>

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerWFF3.h>
#include <ti/drivers/timer/GPTimerWFF3.h>

/* Defines for maximal counter target values. Max count is set to (2^16 - 2),
 * (2^24 - 2), or (2^32 - 2) depending on the counter width for the selected
 * GPTimer instance, to allow for a glitch free 100% duty cycle at max period
 * count.
 */
#define PWM_COUNT_MAX_16_BITS 0xFFFE
#define PWM_COUNT_MAX_24_BITS 0xFFFFFE
#define PWM_COUNT_MAX_32_BITS 0xFFFFFFFE

/* PWMTimerWFF3 functions */
void PWMTimerWFF3_close(PWM_Handle handle);
int_fast16_t PWMTimerWFF3_control(PWM_Handle handle, uint_fast16_t cmd, void *arg);
void PWMTimerWFF3_init(PWM_Handle handle);
PWM_Handle PWMTimerWFF3_open(PWM_Handle handle, PWM_Params *params);
int_fast16_t PWMTimerWFF3_setDuty(PWM_Handle handle, uint32_t dutyValue);
int_fast16_t PWMTimerWFF3_setPeriod(PWM_Handle handle, uint32_t periodValue);
int_fast16_t PWMTimerWFF3_setDutyAndPeriod(PWM_Handle handle, uint32_t dutyValue, uint32_t periodValue);
void PWMTimerWFF3_start(PWM_Handle handle);
void PWMTimerWFF3_stop(PWM_Handle handle);

/* PWMTimerWFF3 internal functions */
static uint32_t PWMTimerWFF3_getMaxCount(PWM_Handle handle);
static uint32_t PWMTimerWFF3_getPeriodCounts(PWM_Handle handle, PWM_Period_Units periodUnit, uint32_t periodValue);
static uint32_t PWMTimerWFF3_getDutyCounts(PWM_Handle handle,
                                           uint32_t periodCounts,
                                           PWM_Duty_Units dutyUnit,
                                           uint32_t dutyValue);
static GPTimerWFF3_ChannelNo PWMTimerWFF3_getPwmChannelNo(uint_least8_t index);

/* PWM function table for PWMTimerWFF3 implementation */
const PWM_FxnTable PWMTimerWFF3_fxnTable = {
    PWMTimerWFF3_close,
    PWMTimerWFF3_control,
    PWMTimerWFF3_init,
    PWMTimerWFF3_open,
    PWMTimerWFF3_setDuty,
    PWMTimerWFF3_setPeriod,
    PWMTimerWFF3_setDutyAndPeriod,
    PWMTimerWFF3_start,
    PWMTimerWFF3_stop,
};

/* GPTimer configuration used by the PWM driver*/
extern const GPTimerWFF3_Config GPTimerWFF3_config[];

/*
 *  ======== PWMTimerWFF3_init ========
 *  This is a dummy function since driver implementation assumes
 *  the handle->object->isOpen flag is set to 0 at boot
 *
 *  @pre    Calling context: Hwi, Swi, Task, Main
 *
 */
void PWMTimerWFF3_init(PWM_Handle handle)
{}

/*
 *  ======== PWMTimerWFF3_open ========
 *  Open the specific PWM peripheral with the settings given in params.
 *  Will return a PWM handle if successfull, NULL if failed.
 *  PWM will output configured idle level when opened.
 *  Function sets a dependency on the underlying timer and muxes the PWM pin
 */
PWM_Handle PWMTimerWFF3_open(PWM_Handle handle, PWM_Params *params)
{
    PWMTimerWFF3_HwAttrs const *hwAttrs = handle->hwAttrs;
    PWMTimerWFF3_Object *object         = handle->object;
    GPTimerWFF3_ChannelNo pwmChannelNo;

    /* Check if PWM already open  */
    uint32_t key = HwiP_disable();
    if (object->isOpen)
    {
        HwiP_restore(key);
        DebugP_log1("PWM_open(%x):  Unit already in use.", (uintptr_t)handle);
        return NULL;
    }
    object->isOpen = true;
    HwiP_restore(key);

    /* Channel is taken directly from hwAttrs, set by the board configuration. */
    pwmChannelNo = (GPTimerWFF3_ChannelNo)hwAttrs->gpTimerChannelNo;

    /* Allocate only the required channel so that multiple PWMTimerWFF3 instances
     * can share one GPTimer peripheral, each assigned to an independent channel.
     */
    GPTimerWFF3_Params timerParams;
    GPTimerWFF3_Params_init(&timerParams);
    timerParams.channelProperty[pwmChannelNo].action = GPTimerWFF3_CH_SET_ON_0_TOGGLE_ON_CMP_PERIODIC;
    timerParams.prescalerDiv                         = hwAttrs->preScalerDivision - 1;
    GPTimerWFF3_Handle hTimer = GPTimerWFF3_openChannel(hwAttrs->gpTimerInstance, pwmChannelNo, &timerParams);

    /* Fail if cannot open timer channel */
    if (hTimer == NULL)
    {
        DebugP_log2("PWM_open(%x): Timer unit (%d) channel already in use.",
                    (uintptr_t)handle,
                    hwAttrs->gpTimerInstance);
        object->isOpen = false;
        return NULL;
    }

    /* Set idle level on PWM pin */
    GPTimerWFF3_ChannelLevel idleLevel = GPTimerWFF3_CH_LEVEL_HIGH;
    if (params->idleLevel == PWM_IDLE_LOW)
    {
        idleLevel = GPTimerWFF3_CH_LEVEL_LOW;
    }
    GPTimerWFF3_setChannelOutputLevel(hTimer, pwmChannelNo, idleLevel);

    /* Store configuration to object */
    object->periodUnit  = params->periodUnits;
    object->periodValue = params->periodValue;
    object->dutyUnit    = params->dutyUnits;
    object->dutyValue   = params->dutyValue;
    object->idleLevel   = params->idleLevel;
    object->hTimer      = hTimer;
    object->chNumber    = pwmChannelNo;

    /* Configure PWM period */
    if (PWMTimerWFF3_setPeriod(handle, object->periodValue) != PWM_STATUS_SUCCESS)
    {
        DebugP_log1("PWM_open(%x): Failed setting period", (uintptr_t)handle);
        /* Release only the designated channel so that other PWM instances
         * allocated to the same GPTimer peripheral are not affected.
         */
        GPTimerWFF3_closeChannel(hTimer, pwmChannelNo);
        object->isOpen = false;
        return NULL;
    }

    /* Configure PWM  duty cycle */
    if (PWMTimerWFF3_setDuty(handle, object->dutyValue) != PWM_STATUS_SUCCESS)
    {
        DebugP_log1("PWM_open(%x): Failed setting duty", (uintptr_t)handle);
        /* Release only the designated channel so that other PWM instances
         * allocated to the same GPTimer peripheral are not affected.
         */
        GPTimerWFF3_closeChannel(hTimer, pwmChannelNo);
        object->isOpen = false;
        return NULL;
    }

    DebugP_log1("PWM_open(%x): Opened with great success!", (uintptr_t)handle);
    return handle;
}

/*
 *  ======== PWMTimerWFF3_setPeriod ========
 *  Sets / update PWM period. Unit must already be defined in object.
 *  Also updates duty cycle.
 */
int_fast16_t PWMTimerWFF3_setPeriod(PWM_Handle handle, uint32_t periodValue)
{
    PWMTimerWFF3_Object *object = handle->object;
    /* Copy current duty value and store new period */
    uint32_t dutyValue          = object->dutyValue;
    uint32_t newPeriodCounts    = PWMTimerWFF3_getPeriodCounts(handle, object->periodUnit, periodValue);
    uint32_t newDutyCounts      = PWMTimerWFF3_getDutyCounts(handle, newPeriodCounts, object->dutyUnit, dutyValue);

    /* Get max PWM count */
    uint32_t maxCount = PWMTimerWFF3_getMaxCount(handle);

    /* Fail if period is out of range */
    if ((newPeriodCounts > maxCount) || (newPeriodCounts == 0))
    {
        DebugP_log2("PWM(%x): Period (%d) is out of range", (uintptr_t)handle, periodValue);
        return PWM_STATUS_INVALID_PERIOD;
    }

    /* Compare new period to duty, and fail if invalid */
    if (newDutyCounts != 0)
    {
        if (newPeriodCounts < (newDutyCounts - 1))
        {
            DebugP_log2("PWM(%x): Period is shorter than duty (%d)", (uintptr_t)handle, periodValue);
            return PWM_STATUS_INVALID_PERIOD;
        }
    }

    /* Store new period and duty cycle */
    object->periodValue  = periodValue;
    object->periodCounts = newPeriodCounts;
    object->dutyValue    = dutyValue;
    object->dutyCounts   = newDutyCounts;

    /* Update timer with new period and duty cycle */
    if (object->isRunning)
    {
        /* Timer counter is running. Set period and duty cycle for next counter cycle */
        GPTimerWFF3_setNextCounterTarget(object->hTimer, newPeriodCounts, false);
        GPTimerWFF3_setNextChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }
    else
    {
        /* Timer counter not yet started. Set inital period and duty cycle. */
        GPTimerWFF3_setInitialCounterTarget(object->hTimer, newPeriodCounts, false);
        GPTimerWFF3_setInitialChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }

    DebugP_log1("PWM_setPeriod(%x): Period set with great success!", (uintptr_t)handle);
    return PWM_STATUS_SUCCESS;
}

/*
 *  ======== PWMTimerWFF3_setDuty ========
 *  Sets / update PWM duty. Unit must already be defined in object.
 *  Period must already be configured in object before calling this API.
 */
int_fast16_t PWMTimerWFF3_setDuty(PWM_Handle handle, uint32_t dutyValue)
{
    PWMTimerWFF3_Object *object = handle->object;
    /* Copy current duty unit and store new duty value */
    PWM_Duty_Units dutyUnit     = object->dutyUnit;
    uint32_t newDutyCounts      = PWMTimerWFF3_getDutyCounts(handle, object->periodCounts, dutyUnit, dutyValue);

    /* Get max PWM count */
    uint32_t maxCount = PWMTimerWFF3_getMaxCount(handle);

    /* Fail if duty cycle count is out of range. */
    if (newDutyCounts > maxCount)
    {
        DebugP_log2("PWM(%x): Duty (%d) is out of range", (uintptr_t)handle, dutyValue);
        return PWM_STATUS_INVALID_DUTY;
    }

    /* Error checking:
     *  Unit PWM_DUTY_FRACTION will always be within range
     *  Unit PWM_DUTY_US with value 0 will always be correct(set by getdutyCounts)
     *  Unit PWM_DUTY_US value != 0 needs error checking
     *  Unit PWM_DUTY_COUNTS needs error checking
     */
    if ((newDutyCounts > (object->periodCounts + 1)) && ((dutyUnit == PWM_DUTY_US) || (dutyUnit == PWM_DUTY_COUNTS)))
    {
        DebugP_log2("PWM(%x): Duty (%d) is larger than period", (uintptr_t)handle, dutyValue);
        return PWM_STATUS_INVALID_DUTY;
    }

    /* Store new duty cycle and update timer */
    object->dutyValue  = dutyValue;
    object->dutyCounts = newDutyCounts;

    if (object->isRunning)
    {
        /* Timer counter is running. Set duty cycle for next counter cycle. */
        GPTimerWFF3_setNextChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }
    else
    {
        /* Timer counter not yet started. Set inital duty cycle. */
        GPTimerWFF3_setInitialChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }

    DebugP_log1("PWM_setDuty(%x): Duty set with great success!", (uintptr_t)handle);
    return PWM_STATUS_SUCCESS;
}

/*
 *  ======== PWMTimerWFF3_setDutyAndPeriod ========
 *  Sets / update PWM duty and period. Unit must already be defined in object.
 */
int_fast16_t PWMTimerWFF3_setDutyAndPeriod(PWM_Handle handle, uint32_t dutyValue, uint32_t periodValue)
{
    PWMTimerWFF3_Object *object = handle->object;

    uint32_t newPeriodCounts = PWMTimerWFF3_getPeriodCounts(handle, object->periodUnit, periodValue);
    uint32_t newDutyCounts   = PWMTimerWFF3_getDutyCounts(handle, newPeriodCounts, object->dutyUnit, dutyValue);

    /* Get max PWM count */
    uint32_t maxCount = PWMTimerWFF3_getMaxCount(handle);

    /* Fail if period is out of range or incompatible with new duty */
    if ((newPeriodCounts > maxCount) || (newPeriodCounts == 0))
    {
        return PWM_STATUS_INVALID_PERIOD;
    }

    if (newDutyCounts != 0)
    {
        if (newPeriodCounts < (newDutyCounts - 1))
        {
            DebugP_log2("PWM(%x): Period is shorter than duty (%d)", (uintptr_t)handle, periodValue);
            return PWM_STATUS_INVALID_PERIOD;
        }
    }

    /* Fail if duty cycle count is out of range. */
    if (newDutyCounts > maxCount)
    {
        return PWM_STATUS_INVALID_DUTY;
    }

    /* Store new period */
    object->periodValue  = periodValue;
    object->periodCounts = newPeriodCounts;

    /* Store new duty cycle */
    object->dutyValue  = dutyValue;
    object->dutyCounts = newDutyCounts;

    /* Update timer */
    if (object->isRunning)
    {
        /* Timer counter is running. Set period and duty cycle for next counter cycle. */
        GPTimerWFF3_setNextCounterTarget(object->hTimer, newPeriodCounts, false);
        GPTimerWFF3_setNextChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }
    else
    {
        /* Timer counter not yet started. Set inital period and duty cycle. */
        GPTimerWFF3_setInitialCounterTarget(object->hTimer, newPeriodCounts, false);
        GPTimerWFF3_setInitialChannelCompVal(object->hTimer, object->chNumber, newDutyCounts, false);
    }

    return PWM_STATUS_SUCCESS;
}

/*
 *  ======== PWMTimerWFF3_stop ========
 *  Stop PWM output for given PWM peripheral. Timer is stopped and PWM pin
 *  will be set to Idle level.
 */
void PWMTimerWFF3_stop(PWM_Handle handle)
{
    PWMTimerWFF3_Object *object = handle->object;

    object->isRunning = false;

    GPTimerWFF3_stop(object->hTimer);

    /* Set PWM pin to idle level */
    GPTimerWFF3_ChannelLevel idleLevel = GPTimerWFF3_CH_LEVEL_HIGH;
    if (object->idleLevel == PWM_IDLE_LOW)
    {
        idleLevel = GPTimerWFF3_CH_LEVEL_LOW;
    }
    GPTimerWFF3_setChannelOutputLevel(object->hTimer, object->chNumber, idleLevel);
}

/*
 *  ======== PWMTimerWFF3_start ========
 *  Start PWM output for given PWM peripheral
 */
void PWMTimerWFF3_start(PWM_Handle handle)
{
    PWMTimerWFF3_Object *object = handle->object;

    /* Restore period and duty cycle in case coming out of standby */
    GPTimerWFF3_setInitialCounterTarget(object->hTimer, object->periodCounts, false);
    GPTimerWFF3_setInitialChannelCompVal(object->hTimer, object->chNumber, object->dutyCounts, false);

    object->isRunning = 1;

    GPTimerWFF3_start(object->hTimer, GPTimerWFF3_CTL_MODE_UP_PER);
}

/*
 *  ======== PWMTimerWFF3_close ========
 *  Close the specific PWM peripheral. A running PWM must be stopped first.
 *  PWM output will revert to GPIO reset value.
 */
void PWMTimerWFF3_close(PWM_Handle handle)
{
    PWMTimerWFF3_Object *object = handle->object;

    /* Release the channel allocated to this instance. The underlying GPTimer
     * peripheral is de-initialized only when all associated instances are closed.
     */
    GPTimerWFF3_closeChannel(object->hTimer, object->chNumber);
    object->hTimer = NULL;

    /* Clear isOpen flag */
    object->isOpen = 0;
}

/*
 *  ======== PWMTimerWFF3_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int_fast16_t PWMTimerWFF3_control(PWM_Handle handle, uint_fast16_t cmd, void *arg)
{
    /* No implementation yet */
    return (PWM_STATUS_UNDEFINEDCMD);
}

/*
 *  ======== PWMTimerWFF3_getMaxCount ========
 *  Return max counter value.
 */
static uint32_t PWMTimerWFF3_getMaxCount(PWM_Handle handle)
{
    PWMTimerWFF3_Object *object = handle->object;
    uint32_t timerWidth         = GPTimerWFF3_getCounterWidth(object->hTimer);

    uint32_t maxCount;
    switch (timerWidth)
    {
        case 32:
            maxCount = PWM_COUNT_MAX_32_BITS;
            break;
        case 24:
            maxCount = PWM_COUNT_MAX_24_BITS;
            break;
        case 16:
        default:
            maxCount = PWM_COUNT_MAX_16_BITS;
    }

    return maxCount;
}

/*
 *  ======== PWMTimerWFF3_getPeriodCounts ========
 *  Return period in timer counts.
 */
static uint32_t PWMTimerWFF3_getPeriodCounts(PWM_Handle handle, PWM_Period_Units periodUnit, uint32_t periodValue)
{
    PWMTimerWFF3_HwAttrs const *hwAttrs = handle->hwAttrs;
    ClockP_FreqHz freq;
    ClockP_getCpuFreq(&freq);

    /* On CC35XX, the GPT reference clock is half the CPU clock */
    freq.lo /= 2;

    uint32_t counterFreq = freq.lo / hwAttrs->preScalerDivision;
    uint32_t periodCounts;

    switch (periodUnit)
    {
        case PWM_PERIOD_US:
            periodCounts = ((uint64_t)counterFreq * (uint64_t)periodValue / 1000000) - 1;
            break;
        case PWM_PERIOD_HZ:
            periodCounts = (counterFreq / periodValue) - 1;
            break;
        case PWM_PERIOD_COUNTS:
        /* Fall through */
        default:
            periodCounts = periodValue;
            break;
    }
    return periodCounts;
}

/*
 *  ======== PWMTimerWFF3_getDutyCounts ========
 *  Return duty cycle in timer counts.
 */
static uint32_t PWMTimerWFF3_getDutyCounts(PWM_Handle handle,
                                           uint32_t periodCounts,
                                           PWM_Duty_Units dutyUnit,
                                           uint32_t dutyValue)
{
    PWMTimerWFF3_HwAttrs const *hwAttrs = handle->hwAttrs;
    ClockP_FreqHz freq;
    ClockP_getCpuFreq(&freq);

    /* On CC35XX, the GPT counter clock is half the CPU bus clock */
    freq.lo /= 2;

    uint32_t counterFreq = freq.lo / hwAttrs->preScalerDivision;
    uint32_t dutyCounts;

    /* Corner case, 0% duty cycle. Set timer count to period count */
    if (dutyValue == 0)
    {
        dutyCounts = 0;
    }
    else
    {
        /* Get the duty cycle count to get the expected PWM signal output. */
        switch (dutyUnit)
        {
            case PWM_DUTY_US:
                dutyCounts = (uint64_t)counterFreq * (uint64_t)dutyValue / 1000000;
                break;
            case PWM_DUTY_FRACTION:
                dutyCounts = (uint64_t)dutyValue * (uint64_t)periodCounts / PWM_DUTY_FRACTION_MAX;
                break;
            case PWM_DUTY_COUNTS:
            /* Fall through */
            default:
                dutyCounts = dutyValue;
                break;
        }

        /* Corner case: If 100% duty cycle, the resulting dutyCount will be 0, set new dutyCounts to periodCounts + 1 to
         * create a glitch free signal. */
        if ((periodCounts - dutyCounts) == 0)
        {
            dutyCounts = periodCounts + 1;
        }
    }
    return dutyCounts;
}

/*
 *  ======== PWMTimerWFF3_getPwmChannelNo ========
 */
static GPTimerWFF3_ChannelNo PWMTimerWFF3_getPwmChannelNo(uint_least8_t index)
{
    GPTimerWFF3_HWAttrs const *hwAttrs;
    GPTimerWFF3_Handle handle;
    GPTimerWFF3_ChannelNo channelNo;

    handle  = (GPTimerWFF3_Handle)&GPTimerWFF3_config[index];
    hwAttrs = handle->hwAttrs;

    /* Find the channel that has been connected to a pin.
     * It's assumed that only one of the ordinary channels have been
     * muxed to a pin.
     */
    if (hwAttrs->channelConfig[0].pin != GPIO_INVALID_INDEX)
    {
        channelNo = GPTimerWFF3_CH_NO_0;
    }
    else if (hwAttrs->channelConfig[1].pin != GPIO_INVALID_INDEX)
    {
        channelNo = GPTimerWFF3_CH_NO_1;
    }
    else if (hwAttrs->channelConfig[2].pin != GPIO_INVALID_INDEX)
    {
        channelNo = GPTimerWFF3_CH_NO_2;
    }
    else
    {
        channelNo = GPTimerWFF3_CH_NO_3;
    }

    return channelNo;
}
