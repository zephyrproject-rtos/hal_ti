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

/*
 *  ======== GPTimerWFF3.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/timer/GPTimerWFF3.h>

/* driverlib header files */
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_gptimer.h)

/* Define for interrupt mask */
#define INT_MASK                                                                                                \
    (GPTimerWFF3_INT_TGT | GPTimerWFF3_INT_ZERO | GPTimerWFF3_INT_COUNTER_CHANGE | GPTimerWFF3_INT_DIR_CHANGE | \
     GPTimerWFF3_INT_CH0_CC | GPTimerWFF3_INT_CH1_CC | GPTimerWFF3_INT_CH2_CC)

/* Field mask defines */
#define COUNTER_MASK_16_BIT 0x0000FFFFU
#define COUNTER_MASK_24_BIT 0x00FFFFFFU
#define COUNTER_MASK_32_BIT 0xFFFFFFFFU

/* GPTimer configuration */
extern const GPTimerWFF3_Config GPTimerWFF3_config[];
extern const uint_least8_t GPTimerWFF3_count;

/* Static functions */
static void GPTimerWFF3_initHw(GPTimerWFF3_Handle handle);
static void GPTimerWFF3_resetHw(GPTimerWFF3_Handle handle);
static void GPTimerWFF3_initIO(GPTimerWFF3_Handle handle);
static bool GPTimerWFF3_isChannelActionCaptureType(GPTimerWFF3_ChannelAction channelAction);
static void GPTimerWFF3_resetIO(GPTimerWFF3_Handle handle);
static void GPTimerWFF3_configureDebugStall(GPTimerWFF3_Handle handle, GPTimerWFF3_DebugMode mode);
static void GPTimerWFF3_configurePrescaler(GPTimerWFF3_Handle handle, uint8_t prescalerDiv);
static void GPTimerWFF3_configureChannels(GPTimerWFF3_Handle handle);
static void GPTimerWFF3HwiFxn(uintptr_t a0);
static int GPTimerWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static uint32_t GPTimerWFF3_getCounterMask(GPTimerWFF3_Handle handle);

/* Default GPTimer parameters */
static const GPTimerWFF3_Params GPTimerWFF3_defaultParams = {
    .hwiCallbackFxn      = NULL,
    .intPhaseLate        = true,
    .prescalerDiv        = 0,
    .debugStallMode      = GPTimerWFF3_DEBUG_STALL_OFF,
    .counterDirChCompare = GPTimerWFF3_CH_COMPARE_COUNTER_DIR_BOTH,
    .channelProperty[0] =
        {
            .action    = GPTimerWFF3_CH_DISABLE,
            .inputEdge = GPTimerWFF3_CH_EDGE_NONE,
        },
    .channelProperty[1] =
        {
            .action    = GPTimerWFF3_CH_DISABLE,
            .inputEdge = GPTimerWFF3_CH_EDGE_NONE,
        },
    .channelProperty[2] =
        {
            .action    = GPTimerWFF3_CH_DISABLE,
            .inputEdge = GPTimerWFF3_CH_EDGE_NONE,
        },
    .channelProperty[3] =
        {
            .action    = GPTimerWFF3_CH_DISABLE,
            .inputEdge = GPTimerWFF3_CH_EDGE_NONE,
        },
};

/*
 *  ======== GPTimerWFF3_close ========
 */
void GPTimerWFF3_close(GPTimerWFF3_Handle handle)
{
    /* Get the pointer to the object and hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    GPTimerWFF3_Object *object         = handle->object;

    /* Stop and reset timer */
    GPTimerWFF3_resetHw(handle);

    /* Reset any configured GPIO pins */
    GPTimerWFF3_resetIO(handle);

    HwiP_destruct(&(object->hwi));

    /* Unregister power notification objects */
    Power_unregisterNotify(&object->postNotify);

    /* Release dependency for timer */
    Power_releaseDependency(hwAttrs->powerID);

    uint32_t key = HwiP_disable();

    /* Close Timer */
    object->isOpen = false;

    HwiP_restore(key);
}

/*
 *  ======== GPTimerWFF3_open ========
 */
GPTimerWFF3_Handle GPTimerWFF3_open(uint_least8_t index, const GPTimerWFF3_Params *params)
{
    GPTimerWFF3_Handle handle = NULL;
    uintptr_t key;
    GPTimerWFF3_Object *object;
    GPTimerWFF3_HWAttrs const *hwAttrs;

    /* Check that requested index is valid */
    if (index < GPTimerWFF3_count)
    {
        handle  = (GPTimerWFF3_Handle)&GPTimerWFF3_config[index];
        hwAttrs = handle->hwAttrs;
        object  = handle->object;
    }
    else
    {
        return NULL;
    }

    key = HwiP_disable();

    if (object->isOpen)
    {
        HwiP_restore(key);
        return NULL;
    }
    object->isOpen = true;

    HwiP_restore(key);

    /* Save param values used by GPTimerWFF3_initHw() */
    object->intPhaseLate        = params->intPhaseLate;
    object->prescalerDiv        = params->prescalerDiv;
    object->debugStallMode      = params->debugStallMode;
    object->counterDirChCompare = params->counterDirChCompare;
    object->channelProperty[0]  = params->channelProperty[0];
    object->channelProperty[1]  = params->channelProperty[1];
    object->channelProperty[2]  = params->channelProperty[2];
    object->channelProperty[3]  = params->channelProperty[3];

    /* Store callback function */
    object->hwiCallbackFxn = params->hwiCallbackFxn;

    /* Register power dependency */
    Power_setDependency(hwAttrs->powerID);

    /* Configure selected GPIO pins */
    GPTimerWFF3_initIO(handle);

    /* Initialize the GPT hardware module */
    GPTimerWFF3_initHw(handle);

    /* Register notification function */
    Power_registerNotify(&object->postNotify, PowerWFF3_AWAKE_SLEEP, GPTimerWFF3_postNotifyFxn, (uintptr_t)handle);

    /* Construct RTOS HWI for this GPT peripheral */
    HwiP_Params hwiParams;
    HwiP_Params_init(&hwiParams);
    hwiParams.arg       = (uintptr_t)handle;
    hwiParams.enableInt = true;
    hwiParams.priority  = hwAttrs->intPriority;
    HwiP_construct(&object->hwi, hwAttrs->intNum, GPTimerWFF3HwiFxn, &hwiParams);

    /* GPTimer opened successfully */
    return handle;
}

/*
 *  ======== GPTimerWFF3_Params_init ========
 */
void GPTimerWFF3_Params_init(GPTimerWFF3_Params *params)
{
    *params = GPTimerWFF3_defaultParams;
}

/*
 *  ======== GPTimerWFF3_start ========
 */
void GPTimerWFF3_start(GPTimerWFF3_Handle handle, GPTimerWFF3_Mode mode)
{
    uint32_t regVal;
    uintptr_t key;

    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Start timer counter in specified mode */
    key    = HwiP_disable();
    regVal = HWREG(hwAttrs->baseAddr + GPTIMER_O_CTL) & ~GPTIMER_CTL_MODE_M;
    regVal |= (mode & GPTIMER_CTL_MODE_M);
    HWREG(hwAttrs->baseAddr + GPTIMER_O_CTL) = regVal;
    HwiP_restore(key);

    /* Set constraint to disallow sleep while running */
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== GPTimerWFF3_stop ========
 */
void GPTimerWFF3_stop(GPTimerWFF3_Handle handle)
{
    uintptr_t key;

    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable timer counter */
    key = HwiP_disable();
    HWREG(hwAttrs->baseAddr + GPTIMER_O_CTL) &= ~GPTIMER_CTL_MODE_M;

    /* Clear constraint to allow sleep again */
    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    HwiP_restore(key);
}

/*
 *  ======== GPTimerWFF3_setInitialCounterTarget ========
 */
void GPTimerWFF3_setInitialCounterTarget(GPTimerWFF3_Handle handle, uint32_t value, bool intFlagClr)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Set timer counter target value. Timer width (16, 24, or 32 bits) depends
     * on the selected peripheral instance.
     */
    uint32_t targetReg = GPTIMER_O_TGT;
    uint32_t fieldMask = GPTimerWFF3_getCounterMask(handle);

    if (!intFlagClr)
    {
        targetReg = GPTIMER_O_TGTNC;
    }

    HWREG(hwAttrs->baseAddr + targetReg) = value & fieldMask;
}

/*
 *  ======== GPTimerWFF3_setNextCounterTarget ========
 */
void GPTimerWFF3_setNextCounterTarget(GPTimerWFF3_Handle handle, uint32_t value, bool intFlagClr)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Set timer counter target value for next period. Timer width (16, 24, or
     * 32 bits) depends on the selected peripheral instance.
     */
    uint32_t targetReg = GPTIMER_O_PTGT;
    uint32_t fieldMask = GPTimerWFF3_getCounterMask(handle);
    if (!intFlagClr)
    {
        targetReg = GPTIMER_O_PTGTNC;
    }
    HWREG(hwAttrs->baseAddr + targetReg) = value & fieldMask;
}

/*
 *  ======== GPTimerWFF3_setInitialChannelCompVal ========
 */
void GPTimerWFF3_setInitialChannelCompVal(GPTimerWFF3_Handle handle,
                                          GPTimerWFF3_ChannelNo chNo,
                                          uint32_t value,
                                          bool intFlagClr)
{
    /* Set channel number dependent register offset */
    uint32_t regOffset = sizeof(uint32_t) * chNo;

    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Set channel compare value. Compare value width (16, 24, or 32 bits)
     * depends on the selected peripheral instance.
     */
    uint32_t regAddr   = GPTIMER_O_C0CC + regOffset;
    uint32_t fieldMask = GPTimerWFF3_getCounterMask(handle);
    if (!intFlagClr)
    {
        /* Use No clear variant of the C0CC register */
        regAddr = GPTIMER_O_C0CCNC + regOffset;
    }
    HWREG(hwAttrs->baseAddr + regAddr) = value & fieldMask;
}

/*
 *  ======== GPTimerWFF3_setNextChannelCompVal ========
 */
void GPTimerWFF3_setNextChannelCompVal(GPTimerWFF3_Handle handle,
                                       GPTimerWFF3_ChannelNo chNo,
                                       uint32_t value,
                                       bool intFlagClr)
{
    /* Set channel number dependent register offset */
    uint32_t regOffset = sizeof(uint32_t) * chNo;

    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Set channel compare value for next period. Compare value width (16, 24,
     * or 32 bits) depends on the selected peripheral instance.
     */
    uint32_t regAddr   = GPTIMER_O_PC0CC + regOffset;
    uint32_t fieldMask = GPTimerWFF3_getCounterMask(handle);
    if (!intFlagClr)
    {
        /* Use No clear variant of the PC0CC register */
        regAddr = GPTIMER_O_PC0CCNC + regOffset;
    }
    HWREG(hwAttrs->baseAddr + regAddr) = value & fieldMask;
}

/*
 *  ======== GPTimerWFF3_setChannelOutputLevel ========
 */
void GPTimerWFF3_setChannelOutputLevel(GPTimerWFF3_Handle handle,
                                       GPTimerWFF3_ChannelNo chNo,
                                       GPTimerWFF3_ChannelLevel level)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Manually override the current channel output level on the selected
     * peripheral instance.
     */
    uint32_t regVal                             = level << (chNo * 2);
    HWREG(hwAttrs->baseAddr + GPTIMER_O_OUTCTL) = regVal;
}

/*
 *  ======== GPTimerWFF3_getChCompareVal ========
 */
uint32_t GPTimerWFF3_getChCompareVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Get channel compare value. Timer width (16, 24, or 32 bits) depends on the
     * selected peripheral instance.
     */
    uint32_t targetReg = GPTIMER_O_C0CCNC + (sizeof(uint32_t) * chNo);

    return (HWREG(hwAttrs->baseAddr + targetReg));
}

/*
 *  ======== GPTimerWFF3_getChCaptureVal ========
 */
uint32_t GPTimerWFF3_getChCaptureVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo)
{
    uint32_t captureVal;

    captureVal = GPTimerWFF3_getChCompareVal(handle, chNo);

    return captureVal;
}

/*
 *  ======== GPTimerWFF3_getNextChCompareVal ========
 */
uint32_t GPTimerWFF3_getNextChCompareVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Get channel compare value. Timer width (16, 24, or 32 bits) depends on
     * the selected peripheral instance.
     */
    uint32_t targetReg = GPTIMER_O_PC0CCNC + (sizeof(uint32_t) * chNo);

    return (HWREG(hwAttrs->baseAddr + targetReg));
}

/*
 *  ======== GPTimerWFF3_getNextChCaptureVal ========
 */
uint32_t GPTimerWFF3_getNextChCaptureVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo)
{
    uint32_t captureVal;

    captureVal = GPTimerWFF3_getNextChCompareVal(handle, chNo);

    return captureVal;
}

/*
 *  ======== GPTimerWFF3_getCounter ========
 */
uint32_t GPTimerWFF3_getCounter(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    return HWREG(hwAttrs->baseAddr + GPTIMER_O_CNTR);
}

/*
 *  ======== GPTimerWFF3_enableInterrupt ========
 */
void GPTimerWFF3_enableInterrupt(GPTimerWFF3_Handle handle, GPTimerWFF3_IntMask intMask)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Enable interrupts in timer unit */
    HWREG(hwAttrs->baseAddr + GPTIMER_O_IMSET) = intMask;
}

/*
 *  ======== GPTimerWFF3_disableInterrupt ========
 */
void GPTimerWFF3_disableInterrupt(GPTimerWFF3_Handle handle, GPTimerWFF3_IntMask intMask)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable the specified interrupts */
    HWREG(hwAttrs->baseAddr + GPTIMER_O_IMCLR) = intMask;
}

/*
 *  ======== GPTimerWFF3_setArg ========
 */
void GPTimerWFF3_setArg(GPTimerWFF3_Handle handle, uintptr_t arg)
{
    GPTimerWFF3_Object *object = handle->object;
    object->arg                = arg;
}

/*
 *  ======== GPTimerWFF3_getCounterWidth ========
 */
uint32_t GPTimerWFF3_getCounterWidth(GPTimerWFF3_Handle handle)
{
    /* Get the pointer to the hwAttrs */
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    uint32_t counterWidth;
    uint32_t regField = HWREG(hwAttrs->baseAddr + GPTIMER_O_DESCEX) & GPTIMER_DESCEX_CNTRW_M;
    switch (regField)
    {
        case GPTIMER_DESCEX_CNTRW_CNTR32:
            counterWidth = 32;
            break;
        case GPTIMER_DESCEX_CNTRW_CNTR24:
            counterWidth = 24;
            break;
        case GPTIMER_DESCEX_CNTRW_CNTR16:
        default:
            counterWidth = 16;
    }

    return counterWidth;
}

/*
 *  ======== GPTimerWFF3_getArg ========
 */
uintptr_t GPTimerWFF3_getArg(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_Object *object = handle->object;

    return (object->arg);
}

/*!
 *  @brief  Function that controls timer debug stall mode.
 *          When enabled, the timer counter will stop either immediatly or when the
 *          timer counter equals 0 dependent on the selected mode.
 *
 *  @param[in]  handle   A GPTimerWFF3 handle returned from GPTimerWFF3_open()
 *  @param[in]  mode     One of the defined debug stall modes
 *
 */
static void GPTimerWFF3_configureDebugStall(GPTimerWFF3_Handle handle, GPTimerWFF3_DebugMode mode)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    HWREG(hwAttrs->baseAddr + GPTIMER_O_EMU) = mode;
}

/*!
 *  @brief  Function that sets the timer prescaler division factor on the specified GPTimer
 *          and selects prescaler source tick to be the system clock.
 *          The default prescaler division factor after chip reset is 0 which forces
 *          a division by 1 (prescaler not used).
 *          The prescaler outputs the timer counter clock. This clock equals system clock
 *          divided by the division factor pluss 1.
 *          Timer counter clock = system_clock / (prescalerDiv + 1)
 *          This function must be called by GPTimerWFF3_initHw().
 *
 *  @param[in]  handle         A GPTimerWFF3 handle returned from GPTimerWFF3_open()
 *  @param[in]  prescalerDiv   The prescaler division factor. Must be a value in the range
 *                             of 0-255.
 *
 */
static void GPTimerWFF3_configurePrescaler(GPTimerWFF3_Handle handle, uint8_t prescalerDiv)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Configure prescaler division and set prescaler tick source to system clock */
    HWREG(hwAttrs->baseAddr + GPTIMER_O_PRECFG) = (prescalerDiv) << GPTIMER_PRECFG_TICKDIV_S;
}

/*!
 *  @brief  Function that initializes the HW when GPTimerWFF3_open() is called.
 *          Timer counter is disabled and channels are reset.
 *          Then the following is configured as specified by params that are stored in
 *          object:
 *          - Interrupt phase
 *          - Prescaler
 *          - Debug stall mode
 *          - Counter compare direction
 *          - Capture/compare channels
 *
 *  @param[in]  handle   A GPTimerWFF3 handle returned from GPTimerWFF3_open()
 *
 */
static void GPTimerWFF3_initHw(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_Object *object         = handle->object;
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable timer counter, reset channels and configure both interrupt phase and
     * counter compare direction.
     */
    uint32_t regVal = GPTIMER_CTL_C2RST | GPTIMER_CTL_C1RST | GPTIMER_CTL_C0RST | GPTIMER_CTL_MODE_DIS |
                      object->counterDirChCompare;
    if (object->intPhaseLate)
    {
        regVal |= GPTIMER_CTL_INTP_LATE;
    }
    HWREG(hwAttrs->baseAddr + GPTIMER_O_CTL) = regVal;

    /* Configure the prescaler */
    GPTimerWFF3_configurePrescaler(handle, object->prescalerDiv);

    /* Configure debug stall mode */
    GPTimerWFF3_configureDebugStall(handle, object->debugStallMode);

    /* Configure capture/compare channels */
    GPTimerWFF3_configureChannels(handle);
}

/*!
 *  @brief  Restore GPTimer unit registers back to reset values.
 *          Needed since module does not have reset functionality.
 *
 * @param[in]  handle   A GPTimerWFF3 handle returned from GPTimerWFF3_open()
 *
 */
static void GPTimerWFF3_resetHw(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    uint32_t base                      = hwAttrs->baseAddr;
    GPTimerWFF3_IntMask intMask        = INT_MASK;

    /* Disable timer and reset channels */
    uint32_t regVal             = (GPTIMER_CTL_C2RST | GPTIMER_CTL_C1RST | GPTIMER_CTL_C0RST | GPTIMER_CTL_MODE_DIS);
    HWREG(base + GPTIMER_O_CTL) = regVal;

    /* Reset interrupt mask */
    GPTimerWFF3_disableInterrupt(handle, intMask);

    /* Clear interrupt statuses */
    HWREG(base + GPTIMER_O_ICLR) = intMask;

    /* Reset timer counter register */
    HWREG(base + GPTIMER_O_CNTR) = 0x0;

    /* Reset timer counter target registers.
     * Supported counter widths are 16, 24, and 32 bits.
     */
    uint32_t resetVal              = GPTimerWFF3_getCounterMask(handle);
    HWREG(base + GPTIMER_O_TGT)    = resetVal;
    HWREG(base + GPTIMER_O_TGTNC)  = resetVal;
    HWREG(base + GPTIMER_O_PTGT)   = 0x00;
    HWREG(base + GPTIMER_O_PTGTNC) = 0x00;

    /* Reset pre-scaler */
    HWREG(base + GPTIMER_O_PRECFG)   = 0;
    HWREG(base + GPTIMER_O_PREEVENT) = 0;

    /* Reset debug configuration */
    HWREG(base + GPTIMER_O_EMU) = 0;
}

/*!
 *  @brief  Configures the three capture/compare channels of the GPTimer.
 *
 */
static void GPTimerWFF3_configureChannels(GPTimerWFF3_Handle handle)
{
    uint32_t regAddr;
    uint32_t regVal;
    uint32_t regOffset = GPTIMER_O_C1CFG - GPTIMER_O_C0CFG;

    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    GPTimerWFF3_Object *object         = handle->object;

    /* Configure each channel selected to be used */
    for (uint32_t i = 0; i < NO_OF_GPT_CHANNELS; i++)
    {
        if (object->channelProperty[i].action != GPTimerWFF3_CH_DISABLE)
        {
            regAddr = GPTIMER_O_C0CFG + (i * regOffset);
            regVal  = object->channelProperty[i].inputEdge;
            regVal |= object->channelProperty[i].action;
            regVal |= (GPTIMER_C0CFG_OUT0_EN << i);
            if (GPTimerWFF3_isChannelActionCaptureType(object->channelProperty[i].action))
            {
                regVal |= GPTIMER_C0CFG_INPUT_IO;
            }
            HWREG(hwAttrs->baseAddr + regAddr) = regVal;
        }
    }
}

/*!
 *  @brief  Initializes selected GPIO pins for the three capture/compare
 *          channels of the GPTimer including their complementary channels.
 *          The complementary channels are outputs only.
 *
 */
static void GPTimerWFF3_initIO(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    GPTimerWFF3_Object *object         = handle->object;

    /* Loop over all available channels on the LGPT peripheral */
    for (uint32_t i = 0; i < NO_OF_GPT_CHANNELS; i++)
    {
        /* Check if channel is selected for GPIO usage */
        if (hwAttrs->channelConfig[i].pin != GPIO_INVALID_INDEX)
        {
            /* Channel selected for GPIO pin usage. Configure dependent on channel action */
            if (GPTimerWFF3_isChannelActionCaptureType(object->channelProperty[i].action))
            {
                /* Configure as input */
                GPIO_setConfigAndMux(hwAttrs->channelConfig[i].pin, GPIO_CFG_INPUT, hwAttrs->channelConfig[i].pinMux);
            }
            else
            {
                /* Configure as output */
                GPIO_setConfigAndMux(hwAttrs->channelConfig[i].pin, GPIO_CFG_NO_DIR, hwAttrs->channelConfig[i].pinMux);
            }
        }

        /* Check if complementary channel is selected for GPIO usage */
        if (hwAttrs->channelConfig[i].nPin != GPIO_INVALID_INDEX)
        {
            /* Complementary channel output selected for GPIO pin usage. Configure as output */
            GPIO_setConfigAndMux(hwAttrs->channelConfig[i].nPin, GPIO_CFG_NO_DIR, hwAttrs->channelConfig[i].nPinMux);
        }
    }
}

/*!
 *  @brief  Checks if specified channel action is a capture type action.
 *          Capture type channel action requires the channel to be configured
 *          as input.
 *
 */
static bool GPTimerWFF3_isChannelActionCaptureType(GPTimerWFF3_ChannelAction channelAction)
{
    bool captureType = false;

    if ((channelAction == GPTimerWFF3_CH_SET_ON_CAPTURE_PERIODIC) ||
        (channelAction == GPTimerWFF3_CH_SET_ON_CAPTURE_ONCE) || (channelAction == GPTimerWFF3_CH_PULSE_WIDTH_MEASURE))
    {
        captureType = true;
    }

    return captureType;
}

/*!
 *  @brief  Resets configured GPIO pins of the GPTimer.
 *
 */
static void GPTimerWFF3_resetIO(GPTimerWFF3_Handle handle)
{
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Loop over all available channels on the LGPT peripheral */
    for (uint32_t i = 0; i < NO_OF_GPT_CHANNELS; i++)
    {
        GPIO_resetConfig(hwAttrs->channelConfig[i].pin);
        GPIO_resetConfig(hwAttrs->channelConfig[i].nPin);
    }
}

/*!
 *  @brief  GPTimer interrupt handler - Clears corresponding interrupt(s)
 *          and calls callback function with handle and bitmask argument.
 *
 */
static void GPTimerWFF3HwiFxn(uintptr_t a0)
{
    GPTimerWFF3_Handle handle          = (GPTimerWFF3_Handle)a0;
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;
    GPTimerWFF3_Object *object         = handle->object;

    GPTimerWFF3_HwiFxn callbackFxn = object->hwiCallbackFxn;

    /* Get masked interrupt status */
    uint32_t intMask = HWREG(hwAttrs->baseAddr + GPTIMER_O_MIS);

    /* Clear interrupt status */
    HWREG(hwAttrs->baseAddr + GPTIMER_O_ICLR) = intMask;

    if (callbackFxn != NULL)
    {
        callbackFxn(handle, intMask);
    }
}

/*
 *  ======== GPTimerWFF3_postNotifyFxn ========
 *  Called by Power module when waking up from sleep.
 */
static int GPTimerWFF3_postNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    /* Reconfigure the hardware if returning from sleep */
    if (eventType == PowerWFF3_AWAKE_SLEEP)
    {
        GPTimerWFF3_initHw((GPTimerWFF3_Handle)clientArg);
    }

    return Power_NOTIFYDONE;
}

/*
 *  ======== GPTimerWFF3_openChannel ========
 *  Allows multiple drivers to share one GPTimer peripheral by claiming
 *  individual channels. The first channel caller performs full peripheral
 *  initialization; subsequent callers configure only their own channel.
 */
GPTimerWFF3_Handle GPTimerWFF3_openChannel(uint_least8_t index,
                                           GPTimerWFF3_ChannelNo chNo,
                                           const GPTimerWFF3_Params *params)
{
    GPTimerWFF3_Handle handle;
    GPTimerWFF3_Object *object;
    GPTimerWFF3_HWAttrs const *hwAttrs;
    uintptr_t key;

    if (index >= GPTimerWFF3_count)
    {
        return NULL;
    }

    handle  = (GPTimerWFF3_Handle)&GPTimerWFF3_config[index];
    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    key = HwiP_disable();

    /* Fail if the peripheral was opened exclusively via GPTimerWFF3_open(),
     * or if the specified channel is already allocated.
     */
    if (object->isOpen && (object->openChannelMask == 0))
    {
        HwiP_restore(key);
        return NULL;
    }
    if (object->openChannelMask & (1u << chNo))
    {
        HwiP_restore(key);
        return NULL;
    }

    bool firstChannel = (object->openChannelMask == 0);
    object->openChannelMask |= (1u << chNo);
    object->isOpen = true;

    HwiP_restore(key);

    if (firstChannel)
    {
        /* First channel: full peripheral initialization */
        object->intPhaseLate        = params->intPhaseLate;
        object->prescalerDiv        = params->prescalerDiv;
        object->debugStallMode      = params->debugStallMode;
        object->counterDirChCompare = params->counterDirChCompare;
        object->channelProperty[0]  = params->channelProperty[0];
        object->channelProperty[1]  = params->channelProperty[1];
        object->channelProperty[2]  = params->channelProperty[2];
        object->channelProperty[3]  = params->channelProperty[3];
        object->hwiCallbackFxn      = params->hwiCallbackFxn;

        Power_setDependency(hwAttrs->powerID);
        GPTimerWFF3_initIO(handle);
        GPTimerWFF3_initHw(handle);
        Power_registerNotify(&object->postNotify, PowerWFF3_AWAKE_SLEEP, GPTimerWFF3_postNotifyFxn, (uintptr_t)handle);

        HwiP_Params hwiParams;
        HwiP_Params_init(&hwiParams);
        hwiParams.arg       = (uintptr_t)handle;
        hwiParams.enableInt = true;
        hwiParams.priority  = hwAttrs->intPriority;
        HwiP_construct(&object->hwi, hwAttrs->intNum, GPTimerWFF3HwiFxn, &hwiParams);
    }
    else
    {
        /* Peripheral already running: configure only the new channel */
        object->channelProperty[chNo] = params->channelProperty[chNo];
        GPTimerWFF3_configureChannels(handle);
    }

    return handle;
}

/*
 *  ======== GPTimerWFF3_closeChannel ========
 *  Releases one channel previously allocated by GPTimerWFF3_openChannel().
 *  The peripheral is de-initialized only when all allocated channels are released.
 */
void GPTimerWFF3_closeChannel(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo)
{
    GPTimerWFF3_Object *object         = handle->object;
    GPTimerWFF3_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Disable the channel in hardware */
    uint32_t regOffset                                              = GPTIMER_O_C1CFG - GPTIMER_O_C0CFG;
    HWREG(hwAttrs->baseAddr + GPTIMER_O_C0CFG + (chNo * regOffset)) = 0;

    /* Reset the GPIO pin(s) associated with the specified channel */
    GPIO_resetConfig(hwAttrs->channelConfig[chNo].pin);
    GPIO_resetConfig(hwAttrs->channelConfig[chNo].nPin);

    uintptr_t key                        = HwiP_disable();
    object->channelProperty[chNo].action = GPTimerWFF3_CH_DISABLE;
    object->openChannelMask &= ~(1u << chNo);
    bool lastChannel = (object->openChannelMask == 0);
    HwiP_restore(key);

    if (lastChannel)
    {
        /* Last channel: full peripheral teardown */
        GPTimerWFF3_resetHw(handle);
        GPTimerWFF3_resetIO(handle);
        HwiP_destruct(&object->hwi);
        Power_unregisterNotify(&object->postNotify);
        Power_releaseDependency(hwAttrs->powerID);

        key            = HwiP_disable();
        object->isOpen = false;
        HwiP_restore(key);
    }
}

/*
 *  ======== GPTimerWFF3_getCounterMask ========
 *  Get counter field mask value based on the counter width.
 */
static uint32_t GPTimerWFF3_getCounterMask(GPTimerWFF3_Handle handle)
{
    uint32_t fieldMask;
    uint32_t counterWidth = GPTimerWFF3_getCounterWidth(handle);
    switch (counterWidth)
    {
        case 32:
            fieldMask = COUNTER_MASK_32_BIT;
            break;
        case 24:
            fieldMask = COUNTER_MASK_24_BIT;
            break;
        case 16:
        default:
            fieldMask = COUNTER_MASK_16_BIT;
    }

    return fieldMask;
}
