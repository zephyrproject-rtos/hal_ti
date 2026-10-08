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

/* Kernel services */
#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/dpl/HwiP.h>

/* TI drivers */
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCWFF3.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOWFF3.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerWFF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/adc.h)
#include DeviceFamily_constructPath(driverlib/cpu.h)

/*
 * =============================================================================
 * Public Function Declarations
 * =============================================================================
 */
void ADCWFF3_close(ADC_Handle handle);
void ADCWFF3_init(ADC_Handle handle);
ADC_Handle ADCWFF3_open(ADC_Handle handle, ADC_Params *params);
int_fast16_t ADCWFF3_convert(ADC_Handle handle, uint16_t *value);
int_fast16_t ADCWFF3_convertChain(ADC_Handle *handleList, uint16_t *dataBuffer, uint8_t channelCount);
int_fast16_t ADCWFF3_control(ADC_Handle handle, uint_fast16_t cmd, void *arg);
uint32_t ADCWFF3_convertToMicroVolts(ADC_Handle handle, uint16_t adcValue);

/*
 * =============================================================================
 * Private Function Declarations
 * =============================================================================
 */
static int ADCWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);

/*
 * =============================================================================
 * Constants
 * =============================================================================
 */

/* ADC function table for ADCWFF3 implementation */
const ADC_FxnTable ADCWFF3_fxnTable = {ADCWFF3_close,
                                       ADCWFF3_control,
                                       ADCWFF3_convert,
                                       ADCWFF3_convertChain,
                                       ADCWFF3_convertToMicroVolts,
                                       ADCWFF3_init,
                                       ADCWFF3_open};

/*
 * =============================================================================
 * Global Variables
 * =============================================================================
 */

/* Keep track of the adc handle instance to create and delete ADCWFF3_adcSemaphore */
uint8_t ADCWFF3_adcInstanceCount = 0;

/* Semaphore to arbitrate access to the single ADC peripheral between multiple handles */
SemaphoreP_Struct ADCWFF3_adcSemaphore;

/*
 * =============================================================================
 * Function Definitions
 * =============================================================================
 */

/*
 *  ======== ADCWFF3_init ========
 */
void ADCWFF3_init(ADC_Handle handle)
{
    ADCWFF3_Object *object;

    /* Get the object */
    object = handle->object;

    /* Mark the object as available */
    object->isOpen = false;
}

/*
 *  ======== ADCWFF3_open ========
 */
ADC_Handle ADCWFF3_open(ADC_Handle handle, ADC_Params *params)
{
    ADCWFF3_Object *object;
    ADCWFF3_HWAttrs const *hwAttrs;

    DebugP_assert(handle);

    if (params->isProtected == false)
    {
        /* For this implementation, protection must always be enabled */
        return NULL;
    }

    /* Get object and hwAttrs */
    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Determine if the driver was already opened */
    uint32_t key = HwiP_disable();

    if (object->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }
    object->isOpen = true;

    /* If this is the first handle requested, set up the semaphore */
    if (ADCWFF3_adcInstanceCount == 0)
    {
        /* Setup semaphore */
        SemaphoreP_constructBinary(&ADCWFF3_adcSemaphore, 1);
    }
    ADCWFF3_adcInstanceCount++;

    /* Register power dependency - i.e. power up and enable clock for ADC */
    Power_setDependency(PowerWFF3_PERIPH_ADC0);

    HwiP_restore(key);

    /* Set input pin to analog function. If pin is unused, value is set to GPIO_INVALID_INDEX */
    GPIO_setConfigAndMux(hwAttrs->adcInputDIO, GPIO_CFG_INPUT, GPIOWFF3_MUX_ANALOG);

    /* Set sampling clock source */
    ADCSetSamplingClk(hwAttrs->sampleClkSrc);

    /* Register notification functions */
    Power_registerNotify(&object->postNotify, PowerWFF3_AWAKE_SLEEP, ADCWFF3_postNotifyFxn, (uintptr_t)handle);

    return handle;
}

/*
 *  ======== ADCWFF3_close ========
 */
void ADCWFF3_close(ADC_Handle handle)
{
    ADCWFF3_Object *object;
    ADCWFF3_HWAttrs const *hwAttrs;

    DebugP_assert(handle);

    /* Get object and hwAttrs */
    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    uint32_t key = HwiP_disable();

    if (object->isOpen)
    {
        ADCWFF3_adcInstanceCount--;
        if (ADCWFF3_adcInstanceCount == 0)
        {
            SemaphoreP_destruct(&ADCWFF3_adcSemaphore);
        }

        GPIO_resetConfig(hwAttrs->adcInputDIO);

        /* Unregister power notification objects */
        Power_unregisterNotify(&object->postNotify);

        /* Remove power dependency */
        Power_releaseDependency(PowerWFF3_PERIPH_ADC0);
    }

    object->isOpen = false;
    HwiP_restore(key);
}

/*
 *  ======== ADCWFF3_control ========
 */
int_fast16_t ADCWFF3_control(ADC_Handle handle, uint_fast16_t cmd, void *arg)
{
    /* No implementation yet */
    return ADC_STATUS_UNDEFINEDCMD;
}

/*
 *  ======== ADCWFF3_convert ========
 */
int_fast16_t ADCWFF3_convert(ADC_Handle handle, uint16_t *value)
{
    ADCWFF3_HWAttrs const *hwAttrs;
    int_fast16_t conversionResult = ADC_STATUS_SUCCESS;
    uint32_t conversionValue;
    uint32_t interruptStatus;
    uint32_t semaphorePendTimeout = HwiP_inISR() ? SemaphoreP_NO_WAIT : SemaphoreP_WAIT_FOREVER;

    DebugP_assert(handle);

    /* Get handle */
    hwAttrs = handle->hwAttrs;

    /* Acquire the lock for this particular ADC handle */
    if (SemaphoreP_pend(&ADCWFF3_adcSemaphore, semaphorePendTimeout) != SemaphoreP_OK)
    {
        return ADC_STATUS_ERROR;
    }

    /* Clear all ADC interrupt events */
    ADCClearInterrupt(ADC_INT_ALL);

    /* Set constraints to guarantee operation */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* Make sure conversion is disabled to allow configuration changes */
    ADCDisableConversion();

    /* Specify range of ctrl registers for conversion. Use ctrl register 0 */
    ADCSetMemctlRange(0, 0);

    /* Set clock-divider and sampling duration */
    ADCSetSampleDuration(hwAttrs->adcClkDivider, hwAttrs->samplingDuration);

    /* Set sampling mode to auto, meaning the sample duration is determined by
     * sample duration configured above.
     */
    ADCSetSamplingMode(ADC_SAMPLE_MODE_AUTO);

    /* Set reference source */
    ADCSetInput(hwAttrs->refSource, hwAttrs->internalChannel, hwAttrs->fullScaleRange, 0);

    /* Configure ADC to only do one conversion */
    ADCSetSequence(ADC_SEQUENCE_SINGLE);

    /* Use software trigger source */
    ADCSetTriggerSource(ADC_TRIGGER_SOURCE_SOFTWARE);

    /* Enable conversion. ADC will wait for trigger. */
    ADCEnableConversion();

    /* Start conversion. No need to call ADCStopConversion() since that is only
     * needed in manual sampling mode.
     */
    ADCStartConversion();

    /* There is a delay of 16 system-clock cycles on WFF3 between writing the
     * SC_START bit, and the BUSY-bit going high. If we start polling too early,
     * we will miss it. Delay 6 loops, where each loop is minimum 3 cycles.
     */
    CPUDelay(6);

    /* Read out conversion (blocking while ADC is busy) */
    conversionValue = ADCReadResult(0);

    /* Check if something went wrong. (Underflow or overflow) */
    interruptStatus = ADCRawInterruptStatus();

    if (interruptStatus & (ADC_INT_OVIFG | ADC_INT_UVIFG))
    {
        conversionResult = ADC_STATUS_ERROR;
    }

    /* Clear all interrupts generated by ADC */
    ADCClearInterrupt(ADC_INT_ALL);

    /* Allow entering standby again after ADC conversion complete */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* Release the lock for this particular ADC handle */
    SemaphoreP_post(&ADCWFF3_adcSemaphore);

    *value = conversionValue;

    /* Return the status-code of the conversion */
    return conversionResult;
}

/*
 *  ======== ADCWFF3_convertChain ========
 */
int_fast16_t ADCWFF3_convertChain(ADC_Handle *handleList, uint16_t *dataBuffer, uint8_t channelCount)
{
    ADCWFF3_HWAttrs const *hwAttrs;
    int_fast16_t conversionResult = ADC_STATUS_SUCCESS;
    uint32_t conversionValue;
    uint32_t interruptStatus;
    uint32_t semaphorePendTimeout = HwiP_inISR() ? SemaphoreP_NO_WAIT : SemaphoreP_WAIT_FOREVER;

    /* Acquire the lock used arbitrate access to the ADC peripheral
     * between multiple handles.
     */
    if (SemaphoreP_pend(&ADCWFF3_adcSemaphore, semaphorePendTimeout) != SemaphoreP_OK)
    {
        return ADC_STATUS_ERROR;
    }

    /* Clear all ADC interrupt events */
    ADCClearInterrupt(ADC_INT_ALL);

    /* Set constraints to guarantee operation */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* Make sure conversion is disabled to allow configuration changes */
    ADCDisableConversion();

    /* Specify range of ctrl registers for conversion. Use ctrl register 0 */
    ADCSetMemctlRange(0, 0);

    /* Set sampling mode to auto, meaning the sample duration is determined by
     * sample duration configured above.
     */
    ADCSetSamplingMode(ADC_SAMPLE_MODE_AUTO);

    /* Configure ADC to only do one conversion */
    ADCSetSequence(ADC_SEQUENCE_SINGLE);

    /* Use software trigger source */
    ADCSetTriggerSource(ADC_TRIGGER_SOURCE_SOFTWARE);

    for (uint32_t i = 0; i < channelCount; i++)
    {
        DebugP_assert(handleList[i]);

        /* Get the particular handle */
        hwAttrs = handleList[i]->hwAttrs;

        /* Set clock-divider and sampling duration */
        ADCSetSampleDuration(hwAttrs->adcClkDivider, hwAttrs->samplingDuration);

        /* Set reference source */
        ADCSetInput(hwAttrs->refSource, hwAttrs->internalChannel, hwAttrs->fullScaleRange, 0);

        /* Enable conversion. ADC will wait for trigger. */
        ADCEnableConversion();

        /* Start conversion. No need to call ADCStopConversion() since that is
         * only needed in manual sampling mode.
         */
        ADCStartConversion();

        /* There is a delay of 16 system-clock cycles on WFF3 between writing
         * the SC_START bit, and the BUSY-bit going high. If we start polling
         * too early, we will miss it. Delay 6 loops, where each loop is minimum
         * 3 cycles.
         */
        CPUDelay(6);

        /* Read out conversion (blocking while ADC is busy) */
        conversionValue = ADCReadResult(0);

        dataBuffer[i] = conversionValue;
    }

    /* Check if something went wrong. (Underflow or overflow) */
    interruptStatus = ADCRawInterruptStatus();

    if (interruptStatus & (ADC_INT_OVIFG | ADC_INT_UVIFG))
    {
        conversionResult = ADC_STATUS_ERROR;
    }

    /* Clear all interrupts generated by ADC */
    ADCClearInterrupt(ADC_INT_ALL);

    /* Allow entering standby again after ADC conversion complete */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* Release the lock used arbitrate access to the single ADC peripheral
     * between multiple handles.
     */
    SemaphoreP_post(&ADCWFF3_adcSemaphore);

    /* Return the status-code of the conversion */
    return conversionResult;
}

/*
 *  ======== ADCWFF3_convertToMicroVolts ========
 */
uint32_t ADCWFF3_convertToMicroVolts(ADC_Handle handle, uint16_t adcValue)
{
    ADCWFF3_HWAttrs const *hwAttrs;
    uint32_t microVolts;

    DebugP_assert(handle);

    /* Get the pointer to the hwAttrs */
    hwAttrs = handle->hwAttrs;

    microVolts = ADCValueToMicrovolts(adcValue, hwAttrs->fullScaleRange);

    return microVolts;
}

/*
 *  ======== ADCWFF3_postNotifyFxn ========
 *  Called by Power module when waking up from sleep.
 */
static int ADCWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    ADC_Handle handle              = (ADC_Handle)clientArg;
    ADCWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Reconfigure the hardware if returning from sleep */
    if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        /* Set sampling clock source */
        ADCSetSamplingClk(hwAttrs->sampleClkSrc);

        /* Restore trim values */
        ADCRestoreTrims();
    }

    return Power_NOTIFYDONE;
}
