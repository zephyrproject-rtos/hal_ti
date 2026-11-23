/*
 * Copyright (c) 2023-2025, Texas Instruments Incorporated
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
#include <string.h>
#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOWFF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_iomux.h)
#include DeviceFamily_constructPath(inc/hw_soc_aon.h)
#include DeviceFamily_constructPath(inc/hw_hostmcu_aon.h)
#include DeviceFamily_constructPath(inc/hw_types.h)

/* Missing defines from hw_hostmcu_aon.h */
#define HOSTMCU_AON_CFGWICSNS_GPIO_AND_EN (1U << 1)
#define HOSTMCU_AON_CFGWICSNS_GPIO_OR_EN  (1U << 2)
#define HOSTMCU_AON_CFGWUTP_GPIO_AND_FAST (1U << 1)
#define HOSTMCU_AON_CFGWUTP_GPIO_OR_FAST  (1U << 2)

static bool initCalled = false;

/* HW interrupt structure for I/O interrupt handler */
static HwiP_Struct gpioHwi;

/* Dedicated functions to set GPIO configuration and control registers. */
static void GPIO_setCfgReg(uint32_t cfgRegAddr, uint32_t tmpCfgReg);
static void GPIO_setCtlReg(uint32_t ctlRegAddr, uint32_t tmpCtlReg);

/* Link to config values defined by sysconfig */
extern GPIO_Config GPIO_config;
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* The size of each IO region in IOMUX id 4KB */
#define IOMUX_IO_REGION_SIZE (4096U)

#define IOMUX_CFG_ADDR(index) \
    (IOMUX_BASE + IOMUX_O_SCLKICFG + ((index)*IOMUX_IO_REGION_SIZE) + (IOMUX_O_GPIO2CFG - IOMUX_O_GPIO2CFG))
#define IOMUX_PULLCTL_ADDR(index) \
    (IOMUX_BASE + IOMUX_O_SCLKICFG + ((index)*IOMUX_IO_REGION_SIZE) + (IOMUX_O_GPIO2PCTL - IOMUX_O_GPIO2CFG))
#define IOMUX_CTL_ADDR(index) \
    (IOMUX_BASE + IOMUX_O_SCLKICFG + ((index)*IOMUX_IO_REGION_SIZE) + (IOMUX_O_GPIO2CTL - IOMUX_O_GPIO2CFG))
#define IOMUX_EVTCTL_ADDR(index) \
    (IOMUX_BASE + IOMUX_O_SCLKICFG + ((index)*IOMUX_IO_REGION_SIZE) + (IOMUX_O_GPIO2ECTL - IOMUX_O_GPIO2CFG))
#define IOMUX_PORTCFG_ADDR(index) (IOMUX_BASE + IOMUX_O_SCLKIPCFG + ((index) << 2))

/*
 *  ======== GPIO_clearInt ========
 */
void GPIO_clearInt(uint_least8_t index)
{
    uintptr_t key;
    uint32_t registerAddr;
    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    registerAddr = IOMUX_EVTCTL_ADDR(index);

    key = HwiP_disable();
    HWREG(registerAddr) |= IOMUX_GPIO2ECTL_CLR;
    HwiP_restore(key);
}

/*
 *  ======== GPIO_disableInt ========
 */
void GPIO_disableInt(uint_least8_t index)
{
    uintptr_t key;

    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    /* Clear bit in IMASK register to disable interrupts */
    key = HwiP_disable();
    if (index >= 32)
    {
        /* Disable interrupt by clearing functional mask bit */
        HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC1S) &= ~(1 << (index - 32));

        /* Disable wakeup event by setting the GPIO OR wakeup event mask bit.
         * When the bit is set, the event is disabled.
         */
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR1) |= (1 << (index - 32));
    }
    else
    {
        /* Disable interrupt by clearing functional mask bit */
        HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC0S) &= ~(1 << index);

        /* Disable wakeup event by setting the GPIO OR wakeup event mask bit.
         * When the bit is set, the event is disabled.
         */
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR) |= (1 << index);
    }
    HwiP_restore(key);
}

/*
 *  ======== GPIO_enableInt ========
 */
void GPIO_enableInt(uint_least8_t index)
{
    uintptr_t key;

    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    /* Set bit in IMASK register to enable interrupts */
    key = HwiP_disable();
    if (index >= 32)
    {
        /* Enable interrupt by setting functional mask bit */
        HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC1S) |= (1 << (index - 32));

        /* Enable wakeup event by clearing the GPIO OR wakeup event mask bit.
         * When the bit is cleared, the event is enabled.
         */
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR1) &= ~(1 << (index - 32));
    }
    else
    {
        /* Enable interrupt by setting functional mask bit (IMASK equivalent) */
        HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC0S) |= (1 << index);

        /* Enable wakeup event by clearing the GPIO OR wakeup event mask bit.
         * When the bit is cleared, the event is enabled.
         */
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR) &= ~(1 << index);
    }
    HwiP_restore(key);
}

/*
 *  ======== GPIO_hwiIntFxn ========
 *  Hwi function that processes GPIO interrupts.
 */
void GPIO_hwiIntFxn(uintptr_t arg)
{
    uintptr_t key;
    uint32_t flagIndex;
    uint32_t eventMask0_31;
    uint32_t eventMask32_44;

    /* Get the masked interrupt status from the MIS registers */
    eventMask0_31  = HWREG(SOC_AON_BASE + SOC_AON_O_GPIOMIS0S);
    eventMask32_44 = HWREG(SOC_AON_BASE + SOC_AON_O_GPIOMIS1S);

    while (eventMask0_31)
    {
        /* MASK_TO_PIN only detects the highest set bit */
        flagIndex = GPIO_MASK_TO_PIN(eventMask0_31);

        /* So it's safe to use PIN_TO_MASK to clear that bit */
        eventMask0_31 &= ~GPIO_PIN_TO_MASK(flagIndex);

        /* Clear event */
        key = HwiP_disable();
        HWREG(IOMUX_EVTCTL_ADDR(flagIndex)) |= IOMUX_GPIO2ECTL_CLR;
        HwiP_restore(key);

        if (GPIO_config.callbacks[flagIndex] != NULL)
        {
            GPIO_config.callbacks[flagIndex](flagIndex);
        }
    }

    while (eventMask32_44)
    {
        /* MASK_TO_PIN only detects the highest set bit */
        flagIndex = GPIO_MASK_TO_PIN(eventMask32_44);

        /* So it's safe to use PIN_TO_MASK to clear that bit */
        eventMask32_44 &= ~GPIO_PIN_TO_MASK(flagIndex);

        /* Clear event */
        key = HwiP_disable();
        HWREG(IOMUX_EVTCTL_ADDR(flagIndex + 32)) |= IOMUX_GPIO2ECTL_CLR;
        HwiP_restore(key);

        if (GPIO_config.callbacks[flagIndex + 32] != NULL)
        {
            GPIO_config.callbacks[flagIndex + 32](flagIndex + 32);
        }
    }
}

/*
 *  ======== GPIO_init ========
 */
void GPIO_init()
{
    uintptr_t key;
    unsigned int i;
    HwiP_Params hwiParams;

    key = HwiP_disable();

    if (initCalled)
    {
        HwiP_restore(key);
        return;
    }
    initCalled = true;
    HwiP_restore(key);

    /* Setup HWI handler */
    HwiP_Params_init(&hwiParams);

    /* Make sure no GPIOs are wakeup sources. If the bit for a given GPIO is set
     * in the mask, it means the event will not propagate to the wakeup
     * interrupt. When interrupts are enabled/disabled for individual GPIOs, the
     * corresponding bit in relevant mask will be cleared/set.
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUAND)  = 0xFFFFFFFF;
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUAND1) = 0xFFFFFFFF;
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR)   = 0xFFFFFFFF;
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_GPWUOR1)  = 0xFFFFFFFF;

    /* Disallow all GPIO interrupt sources to pass from RIS to MIS */
    HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC0S) = 0;
    HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC1S) = 0;

    hwiParams.priority = GPIO_config.intPriority;
    HwiP_construct(&gpioHwi, INT_SECURED_GPIO_IRQ_EVT_IND_OUT, GPIO_hwiIntFxn, &hwiParams);

    for (i = GPIO_pinLowerBound; i <= GPIO_pinUpperBound; i++)
    {
        GPIO_setConfigAndMux(i, GPIO_config.configs[i], GPIO_MUX_GPIO);
    }

    /* Configure the GPIO OR event as a sleep wakeup source */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) |= HOSTMCU_AON_CFGWICSNS_GPIO_OR_EN;

    /* Disable GPIO AND event as a sleep wakeup source */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) &= ~(HOSTMCU_AON_CFGWICSNS_GPIO_AND_EN);

    /* Configure the GPIO OR event to be a fast wakeup source */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWUTP) |= HOSTMCU_AON_CFGWUTP_GPIO_OR_FAST;
}

/*
 *  ======== GPIO_read ========
 */
uint_fast8_t GPIO_read(uint_least8_t index)
{
    uint32_t ctlRegAddr;

    if (index == GPIO_INVALID_INDEX)
    {
        return GPIO_STATUS_ERROR;
    }

    ctlRegAddr = IOMUX_CTL_ADDR(index);

    return (HWREG(ctlRegAddr) & IOMUX_GPIO2CTL_PADVAL_M) >> IOMUX_GPIO2CTL_PADVAL_S;
}

/*
 *  ======== GPIO_setConfig ========
 */
int_fast16_t GPIO_setConfig(uint_least8_t index, GPIO_PinConfig pinConfig)
{
    return GPIO_setConfigAndMux(index, pinConfig, GPIO_MUX_GPIO);
}

/*
 *  ======== GPIO_setInterruptConfig ========
 */
void GPIO_setInterruptConfig(uint_least8_t index, GPIO_PinConfig config)
{
    uintptr_t key;
    uint32_t evtctlRegAddr;

    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    /* The EVTCTL contains all the interrupt configuration */
    evtctlRegAddr = IOMUX_EVTCTL_ADDR(index);

    /* Mask away all non-interrupt configuration (all non-EVTCTL configuration) */
    uint32_t maskedConfig = (config & GPIOWFF3_CFG_EVTCTL_M) >> GPIOWFF3_CFG_EVTCTL_S;

    /* Invert the EVTCTL mask, mask out current interrupt config and apply the new one */
    key                            = HwiP_disable();
    uint32_t currentRegisterConfig = HWREG(evtctlRegAddr) & ~(GPIOWFF3_CFG_EVTCTL_M >> GPIOWFF3_CFG_EVTCTL_S);
    HWREG(evtctlRegAddr)           = currentRegisterConfig | maskedConfig;
    HwiP_restore(key);

    if (config & GPIO_CFG_INT_ENABLE)
    {
        GPIO_enableInt(index);
    }
    else
    {
        GPIO_disableInt(index);
    }
}

/*
 *  ======== GPIO_getConfig ========
 */
void GPIO_getConfig(uint_least8_t index, GPIO_PinConfig *pinConfig)
{
    uint32_t cfgRegAddr;
    uint32_t pullctlRegAddr;
    uint32_t ctlRegAddr;
    uint32_t evtctlRegAddr;
    uint32_t tmpCfgReg;
    uint32_t tmpPullctlCfgReg;
    uint32_t tmpctlReg;
    uint32_t tmpEvtctlReg;
    uint32_t configValue;
    uint32_t tmpCfgRegBit;

    if (index == GPIO_INVALID_INDEX)
    {
        /* TODO: How to handle invalid index */
        return;
    }

    cfgRegAddr     = IOMUX_CFG_ADDR(index);
    pullctlRegAddr = IOMUX_PULLCTL_ADDR(index);
    ctlRegAddr     = IOMUX_CTL_ADDR(index);
    evtctlRegAddr  = IOMUX_EVTCTL_ADDR(index);

    tmpCfgReg        = HWREG(cfgRegAddr);
    tmpPullctlCfgReg = HWREG(pullctlRegAddr);
    tmpctlReg        = HWREG(ctlRegAddr);
    tmpEvtctlReg     = HWREG(evtctlRegAddr);

    configValue = ((tmpCfgReg << GPIOWFF3_CFG_CFG_S) & GPIOWFF3_CFG_CFG_M) |
                  ((tmpPullctlCfgReg << GPIOWFF3_CFG_PULLCTL_S) & GPIOWFF3_CFG_PULLCTL_M) |
                  ((tmpctlReg << GPIOWFF3_CFG_CTL_S) & GPIOWFF3_CFG_CTL_M) |
                  ((tmpEvtctlReg << GPIOWFF3_CFG_EVTCTL_S) & GPIOWFF3_CFG_EVTCTL_M);

    /* If IMASK bit is set, the interrupt is enabled. */
    if (index >= 32)
    {
        tmpCfgReg    = HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC1S);
        tmpCfgRegBit = 1 << (index - 32);
    }
    else
    {
        tmpCfgReg    = HWREG(SOC_AON_BASE + SOC_AON_O_GPIOFNC0S);
        tmpCfgRegBit = 1 << index;
    }

    if ((tmpCfgReg & tmpCfgRegBit) == tmpCfgRegBit)
    {
        configValue |= GPIO_CFG_INT_ENABLE;
    }

    /* Report current configuration */
    *pinConfig = (GPIO_PinConfig)configValue;
}

/*
 *  ======== GPIO_toggle ========
 */
void GPIO_toggle(uint_least8_t index)
{
    uint32_t ctlRegAddr;
    uint32_t tmpCtlReg;
    uintptr_t key;

    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    ctlRegAddr = IOMUX_CTL_ADDR(index);

    /* Protect read-modify-write operation to toggle GPIO. */
    key       = HwiP_disable();
    tmpCtlReg = HWREG(ctlRegAddr);
    tmpCtlReg ^= IOMUX_GPIO2CTL_OUT;
    GPIO_setCtlReg(ctlRegAddr, tmpCtlReg);
    HwiP_restore(key);
}

/*
 *  ======== GPIO_write ========
 */
void GPIO_write(uint_least8_t index, unsigned int value)
{
    uint32_t ctlRegAddr;
    uint32_t tmpCtlReg;
    uintptr_t key;

    if (index == GPIO_INVALID_INDEX)
    {
        return;
    }

    ctlRegAddr = IOMUX_CTL_ADDR(index);

    /* Protect read-modify-write operation to write to GPIO. */
    key       = HwiP_disable();
    tmpCtlReg = HWREG(ctlRegAddr);
    tmpCtlReg &= ~IOMUX_GPIO2CTL_OUT_M;
    tmpCtlReg |= (value & 0x1) << IOMUX_GPIO2CTL_OUT_S;
    GPIO_setCtlReg(ctlRegAddr, tmpCtlReg);
    HwiP_restore(key);
}

/*
 *  ======== GPIO_getMux ========
 */
uint32_t GPIO_getMux(uint_least8_t index)
{
    uint32_t cfgRegAddr;
    uint32_t portcfgRegAddr;
    uint32_t mux;
    bool swControlledAnalogSwitch;

    if (index == GPIO_INVALID_INDEX)
    {
        /* TODO: How to handle invalid index */
        return GPIO_STATUS_ERROR;
    }

    portcfgRegAddr = IOMUX_PORTCFG_ADDR(index);
    cfgRegAddr     = IOMUX_CFG_ADDR(index);

    /* Read mux settings */
    mux = (HWREG(portcfgRegAddr) & IOMUX_GPIO2PCFG_IOSEL_M) >> IOMUX_GPIO2PCFG_IOSEL_S;

    /* Check if analog switch is controlled by software */
    swControlledAnalogSwitch = (HWREG(cfgRegAddr) & IOMUX_GPIO2CFG_ANASWOVREN_M) >> IOMUX_GPIO2CFG_ANASWOVREN_S;

    /* If analog switch is not controlled by software, it is controlled by the
     * analog IP, and it is assumed that the IO is muxed to the analog IP
     */
    if (!swControlledAnalogSwitch)
    {
        mux |= GPIOWFF3_MUX_ANALOG_INTERNAL;
    }

    return mux;
}

/*
 *  ======== GPIO_setConfigAndMux ========
 */
int_fast16_t GPIO_setConfigAndMux(uint_least8_t index, GPIO_PinConfig pinConfig, uint32_t mux)
{
    uint32_t cfgRegAddr;
    uint32_t pullctlRegAddr;
    uint32_t ctlRegAddr;
    uint32_t evtctlRegAddr;
    uint32_t portcfgRegAddr;
    uint32_t tmpCfgReg;
    uint32_t tmpPullctlCfgReg;
    uint32_t tmpCtlReg;
    uint32_t tmpEvtctlReg;
    uint32_t tmpPortcfgReg;

    /* Return immediately if pin should not be configured */
    if (pinConfig & GPIOWFF3_DO_NOT_CONFIG)
    {
        return GPIO_STATUS_SUCCESS;
    }

    if (index == GPIO_INVALID_INDEX)
    {
        return GPIO_STATUS_ERROR;
    }

    cfgRegAddr     = IOMUX_CFG_ADDR(index);
    pullctlRegAddr = IOMUX_PULLCTL_ADDR(index);
    ctlRegAddr     = IOMUX_CTL_ADDR(index);
    evtctlRegAddr  = IOMUX_EVTCTL_ADDR(index);
    portcfgRegAddr = IOMUX_PORTCFG_ADDR(index);

    /* Extract register-specific values from compressed pinConfig */
    tmpCfgReg        = (pinConfig & GPIOWFF3_CFG_CFG_M) >> GPIOWFF3_CFG_CFG_S;
    tmpPullctlCfgReg = (pinConfig & GPIOWFF3_CFG_PULLCTL_M) >> GPIOWFF3_CFG_PULLCTL_S;
    tmpCtlReg        = (pinConfig & GPIOWFF3_CFG_CTL_M) >> GPIOWFF3_CFG_CTL_S;
    tmpEvtctlReg     = (pinConfig & GPIOWFF3_CFG_EVTCTL_M) >> GPIOWFF3_CFG_EVTCTL_S;
    tmpPortcfgReg    = (mux << IOMUX_GPIO2PCFG_IOSEL_S) & IOMUX_GPIO2PCFG_IOSEL_M;

    /* If the IO is muxed to the analog IP for that IO, then the analog switch
     * must be controlled by the analog IP. If not, the analog switch must be
     * controlled by the SW to keep the switch open.
     * If tmpCfgReg is kept unmodified from above, the analog switch will be
     * controlled by the analog IP. So the value of tmpCfgReg needs to be
     * changed if the IO is not muxed to the analog IP.
     */
    if (!(mux & GPIOWFF3_MUX_ANALOG_INTERNAL))
    {
        /* Enable analog switch control override, and set the analog switch to
         * be disabled (open) */
        tmpCfgReg |= (IOMUX_GPIO2CFG_ANASWOVREN_ENABLE | IOMUX_GPIO2CFG_ANASW_DISABLE);
    }

    if (mux == GPIO_MUX_GPIO)
    {
        /* Mux to GPIO functionality.
         * Change muxing after changing configuration to prevent glitching.
         */

        GPIO_setCfgReg(cfgRegAddr, tmpCfgReg);
        HWREG(pullctlRegAddr) = tmpPullctlCfgReg;
        GPIO_setCtlReg(ctlRegAddr, tmpCtlReg);
        HWREG(evtctlRegAddr)  = tmpEvtctlReg;
        HWREG(portcfgRegAddr) = tmpPortcfgReg;
    }
    else
    {
        /* Change muxing before changing configuration
         * This is to prevent glitching. If output was previously overridden, and
         * if it will not be overridden by the new configuration, then the override
         * will be disabled after the muxing has been changed.
         */
        HWREG(portcfgRegAddr) = tmpPortcfgReg;
        GPIO_setCfgReg(cfgRegAddr, tmpCfgReg);
        HWREG(pullctlRegAddr) = tmpPullctlCfgReg;
        GPIO_setCtlReg(ctlRegAddr, tmpCtlReg);
        HWREG(evtctlRegAddr) = tmpEvtctlReg;
    }

    if (pinConfig & GPIO_CFG_INT_ENABLE)
    {
        GPIO_enableInt(index);
    }
    else
    {
        GPIO_disableInt(index);
    }

    return GPIO_STATUS_SUCCESS;
}

/*
 *  ======== GPIO_setCfgReg ========
 * The GPIO configuration registers have two fields that are controlled with an
 * "override enable" bit. These are the "Output from pad disable/enable" and
 * "Analog switch open/close" fields.
 * To avoid a glitch when any of these fields are set, the value must be set
 * before the "override enable" field is set.
 */
static void GPIO_setCfgReg(uint32_t cfgRegAddr, uint32_t tmpCfgReg)
{
    bool enableOverrideOutputPad = (tmpCfgReg & IOMUX_GPIO2CFG_OUTDISOVREN_M) == IOMUX_GPIO2CFG_OUTDISOVREN_ENABLE;
    bool enableOverrideAnalogSwitchControl = (tmpCfgReg & IOMUX_GPIO2CFG_ANASWOVREN_M) ==
                                             IOMUX_GPIO2CFG_ANASWOVREN_ENABLE;
    uint32_t orMask = 0U;

    /* If the "override enable" is set, change it to disabled for the first write */
    if (enableOverrideOutputPad)
    {
        tmpCfgReg &= ~IOMUX_GPIO2CFG_OUTDISOVREN_M;
        orMask |= IOMUX_GPIO2CFG_OUTDISOVREN_ENABLE;
    }

    if (enableOverrideAnalogSwitchControl)
    {
        tmpCfgReg &= ~IOMUX_GPIO2CFG_ANASWOVREN_M;
        orMask |= IOMUX_GPIO2CFG_ANASWOVREN_ENABLE;
    }

    /* First write of the config register */
    HWREG(cfgRegAddr) = tmpCfgReg;

    /* If overrides enabled, set enable and do second write */
    if (enableOverrideOutputPad || enableOverrideAnalogSwitchControl)
    {
        tmpCfgReg |= orMask;
        HWREG(cfgRegAddr) = tmpCfgReg;
    }
}

/*
 *  ======== GPIO_setCtlReg ========
 * The GPIO control registers have one field that is controlled with an
 * "override enable" bit. This is the "IO drive out value" field.
 * To avoid a glitch when this field is set, the value must be set before the
 * "override enable" field is set.
 */
static void GPIO_setCtlReg(uint32_t ctlRegAddr, uint32_t tmpCtlReg)
{
    bool enableOverrideOut = tmpCtlReg & IOMUX_GPIO2CTL_OUTOVREN_ENABLE;

    /* If the "override enable" is set, change it to disabled for the first write */
    if (enableOverrideOut)
    {
        tmpCtlReg &= ~IOMUX_GPIO2CTL_OUTOVREN_M;
    }

    /* Firs write of the control register */
    HWREG(ctlRegAddr) = tmpCtlReg;

    /* If overrides enabled, set enable and do second write */
    if (enableOverrideOut)
    {
        tmpCtlReg |= IOMUX_GPIO2CTL_OUTOVREN_ENABLE;
        HWREG(ctlRegAddr) = tmpCtlReg;
    }
}
