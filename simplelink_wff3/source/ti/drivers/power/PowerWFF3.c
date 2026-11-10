/*
 * Copyright (c) 2022-2026 Texas Instruments Incorporated
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
 *  ======== PowerWFF3.c ========
 */

#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/DebugP.h>

#include <ti/drivers/GPIO.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerWFF3.h>

#include <ti/log/Log.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(cmsis/core/cmsis_compiler.h)
#include DeviceFamily_constructPath(cmsis/cc35xx.h)
#include DeviceFamily_constructPath(cmsis/core/core_cm33.h)

/* Includes for resource dependencies */
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_rtc.h)
#include DeviceFamily_constructPath(inc/hw_hostmcu_aon.h)
#include DeviceFamily_constructPath(inc/hw_dcan.h)
#include DeviceFamily_constructPath(inc/hw_gptimer.h)
#include DeviceFamily_constructPath(inc/hw_i2c.h)
#include DeviceFamily_constructPath(inc/hw_i2s.h)
#include DeviceFamily_constructPath(inc/hw_pdm.h)
#include DeviceFamily_constructPath(inc/hw_prcm_aon.h)
#include DeviceFamily_constructPath(inc/hw_sdmmc.h)
#include DeviceFamily_constructPath(inc/hw_spi.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)
#include DeviceFamily_constructPath(inc/hw_uartlin.h)
#include DeviceFamily_constructPath(inc/hw_sdio_card_fn1.h)
#include DeviceFamily_constructPath(inc/hw_adc.h)
#include DeviceFamily_constructPath(driverlib/cpu.h)
#include DeviceFamily_constructPath(driverlib/prcm.h)

/* Missing defines from hw_hostmcu_aon.h */
#define HOSTMCU_AON_CFGWICSNS_RTC_EN                       (1U << 13)
#define HOSTMCU_AON_CFGWICSNS_DEBUGSS_HOST_CSYSPWRUPREQ_EN (1U << 14)
#define HOSTMCU_AON_CFGWUTP_RTC_FAST                       (1U << 13)
#define HOSTMCU_AON_CFGWUTP_DEBUGSS_HOST_CSYSPWRUPREQ_FAST (1U << 14)

/* Defines for NVIC bitmasks */
#define NVIC_IRQ_REG_NUM(num) ((num) >> 5U)
#define NVIC_IRQ_BIT_POS(num) (uint32_t)(1UL << (((uint32_t)(num)) & 0x1FUL))

/* Define for the RAM address where the TI bootloader (v0.0.0.45+) stores the
 * reset cause (2 bytes).
 */
#define RESET_CAUSE_ADDR 0x28000115U

/* Defines used by PowerWFF3_enterSleep() */
/* Workaround uses ELP wake-up timer to delay wake-up through problematic
 * time window. The threshold value is defined here.
 */
#define ELP_WAKEUP_THRESHOLD 0x3U
#define ELP_TIMER_IS_ENABLED() \
    (((HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) & HOSTMCU_AON_ELPTMREN_VAL_M)) != HOSTMCU_AON_ELPTMREN_VAL_DIS)
#define ELP_TIMER_STOP_AND_RELOAD()                                                            \
    do                                                                                         \
    {                                                                                          \
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRRST;    \
        while (ELP_TIMER_IS_ENABLED()) {}                                                      \
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) &= ~(HOSTMCU_AON_ELPTMREN_ELPTMRRST | \
                                                              HOSTMCU_AON_ELPTMREN_ELPTMRSET); \
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRLD;     \
    } while (0)
#define ELP_TIMER_START() HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRSET

/* Forward declarations */
int_fast16_t PowerWFF3_notify(uint_fast16_t eventType);
static void PowerWFF3_enterSleep(void);

/* Externs */
extern const PowerWFF3_Config PowerWFF3_config;
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* Function Macros */

/* Static Globals */

/* Array to maintain constraint reference counts.
 * Declare volatile variable to ensure the toolchain does not use
 * stack for the variable and does not optimize this memory allocation away.
 */
static volatile uint8_t constraintCounts[PowerWFF3_NUMCONSTRAINTS];

/* Mask of Power constraints for quick access.
 * Declare volatile variable to ensure the toolchain does not use
 * stack for the variable and does not optimize this memory allocation away.
 */
static volatile uint32_t constraintMask = 0;

/* Array to maintain resource dependency reference counts.
 * Declare volatile variable to ensure the toolchain does not use
 * stack for the variable and does not optimize this memory allocation away.
 */
static volatile uint8_t resourceCounts[PowerWFF3_NUMRESOURCES];

/* Array of addresses to the clock enable register for each resource */
static const uint32_t resourceClkEnRegs[PowerWFF3_NUMRESOURCES] = {
    DCAN_BASE + DCAN_O_CLKCFG,                  /* PowerWFF3_PERIPH_DCAN */
    GPTIMER0_BASE + GPTIMER_O_CLKCFG,           /* PowerWFF3_PERIPH_GPTIMER0 */
    GPTIMER1_BASE + GPTIMER_O_CLKCFG,           /* PowerWFF3_PERIPH_GPTIMER1 */
    I2C0_BASE + I2C_O_CLKCFG,                   /* PowerWFF3_PERIPH_I2C0 */
    I2C1_BASE + I2C_O_CLKCFG,                   /* PowerWFF3_PERIPH_I2C1 */
    I2S_BASE + I2S_O_CLKCFG,                    /* PowerWFF3_PERIPH_I2S */
    SDMMC_BASE + SDMMC_O_CLKCFG,                /* PowerWFF3_PERIPH_SDMMC */
    SPI0_BASE + SPI_O_CLKCFG,                   /* PowerWFF3_PERIPH_SPI0 */
    SPI1_BASE + SPI_O_CLKCFG,                   /* PowerWFF3_PERIPH_SPI1 */
    SYSTIM_BASE + SYSTIM_O_CLKCFG,              /* PowerWFF3_PERIPH_SYSTIMER */
    UARTLIN0_BASE + UARTLIN_O_CLKCFG,           /* PowerWFF3_PERIPH_UARTLIN0 */
    UARTLIN1_BASE + UARTLIN_O_CLKCFG,           /* PowerWFF3_PERIPH_UARTLIN1 */
    SDIO_CARD_FN1_BASE + SDIO_CARD_FN1_O_CLKEN, /* PowerWFF3_PERIPH_SDIO */
    ADC_BASE + ADC_O_CLKCFG,                    /* PowerWFF3_PERIPH_ADC0 */
    UARTLIN2_BASE + UARTLIN_O_CLKCFG,           /* PowerWFF3_PERIPH_UARTLIN2 */
    PDM_BASE + PDM_O_CLKCFG,                    /* PowerWFF3_PERIPH_PDM */
};

/* Keeps track of the configured Power policy. Power_idleFunc() will not run
 * the policy if this is set to NULL
 */
static Power_PolicyFxn policyFxn = NULL;

/* Is the Power policy enabled? */
static bool isPolicyEnabled = false;

/* Has the Power driver been initialized */
static bool isInitialized = false;

/* Power state of the system. Idle, active, sleep, etc */
static uint8_t powerState = Power_ACTIVE;

/* Event notification list */
static List_List notifyList;

/* Macro for weak definition of the Power Log module */
Log_MODULE_DEFINE_WEAK(LogModule_Power, Log_MODULE_INIT_SINK_DUMMY);

/* ****************** Power APIs ******************** */

/*
 *  ======== Power_init ========
 */
int_fast16_t Power_init()
{
    /* If this function has already been called, just return */
    if (isInitialized)
    {
        return Power_SOK;
    }

    isInitialized = true;

    isPolicyEnabled = PowerWFF3_config.policyFxn != NULL;

    policyFxn = PowerWFF3_config.policyFxn;

    /* Use RTC channel 0 in compare mode. Channel 1 could be used for other
     * purposes.
     */
    HWREG(RTC_BASE + RTC_O_IMSET) = RTC_IMSET_EV0_SET;

    /* Configure RTC to halt when CPU stopped during debug */
    HWREG(RTC_BASE + RTC_O_EMU) = RTC_EMU_HALT_STOP;

    /* The sleep policy function depends on the SysTimer */
    Power_setDependency(PowerWFF3_PERIPH_SYSTIMER);

    /* Configure SysTimer to halt when CPU stopped during debug. The setting
     * is sync'd from RTC_EMU on each wakeup from sleep.
     */
    HWREG(SYSTIM_BASE + SYSTIM_O_EMU) = SYSTIM_EMU_HALT_STOP;

    /* Configure the RTC and CSYSPWRUPREQ as a sleep wakeup source.
     * RTC is used by the sleep policy function to schedule the wakeup, and
     * CSYSPWRUPREQ is used to enable the debugger to wake up the device
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) |= HOSTMCU_AON_CFGWICSNS_RTC_EN |
                                                         HOSTMCU_AON_CFGWICSNS_DEBUGSS_HOST_CSYSPWRUPREQ_EN;

    /* Configure the RTC and CSYSPWRUPREQ to be a fast wakeup source */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWUTP) |= HOSTMCU_AON_CFGWUTP_RTC_FAST |
                                                       HOSTMCU_AON_CFGWUTP_DEBUGSS_HOST_CSYSPWRUPREQ_FAST;

    /* Enable the RTC interrupt for the WFI instruction to be able to wake up on
     * an RTC event. No interrupt handler is registered for the RTC interrupt.
     * The sleep policy function will consume the pending interrupt after the
     * WFI instruction, before enabling interrupts.
     */
    HwiP_enableInterrupt(INT_RTC_EVENT_IRQ);

    return Power_SOK;
}

/*
 *  ======== Power_disablePolicy ========
 *  Do not run the configured policy
 */
bool Power_disablePolicy(void)
{
    bool wasPolicyEnabled = isPolicyEnabled;

    isPolicyEnabled = false;

    return wasPolicyEnabled;
}

/*
 *  ======== Power_enablePolicy ========
 *  Run the configured policy
 */
void Power_enablePolicy(void)
{
    isPolicyEnabled = true;
}

/*
 *  ======== Power_setPolicy ========
 *  Set the Power policy function
 */
void Power_setPolicy(Power_PolicyFxn policy)
{
    policyFxn = policy;
}

/*
 *  ======== Power_getConstraintMask ========
 *  Get a bitmask indicating the constraints that have been registered with
 *  Power.
 */
uint_fast32_t Power_getConstraintMask(void)
{
    return constraintMask;
}

/*
 *  ======== Power_getDependencyCount ========
 *  Get the count of dependencies that are currently declared upon a resource.
 */
int_fast16_t Power_getDependencyCount(Power_Resource resourceId)
{
    DebugP_assert(resourceId < PowerWFF3_NUMRESOURCES);

    return (int_fast16_t)resourceCounts[resourceId];
}

/*
 *  ======== Power_getConstraintCount ========
 *  Get the count of constraints that are currently set on a certain
 *  operational transition
 */
int_fast16_t Power_getConstraintCount(uint_fast16_t constraintId)
{
    DebugP_assert(constraintId < PowerWFF3_NUMCONSTRAINTS);

    if (constraintId < PowerWFF3_NUMCONSTRAINTS)
    {
        return (int_fast16_t)constraintCounts[constraintId];
    }
    else
    {
        return (int_fast16_t)Power_EINVALIDINPUT;
    }
}

/*
 *  ======== Power_getTransitionLatency ========
 *  Get the transition latency for a sleep state.  The latency is reported
 *  in units of microseconds.
 */
uint_fast32_t Power_getTransitionLatency(uint_fast16_t sleepState, uint_fast16_t type)
{
    /* TODO: Make this a dynamic system based on the dynamically computed delta
     * between RTC timeout and re-enabling interrupts
     */

    uint32_t latency = 0;

    if (type == Power_RESUME)
    {
        if (sleepState == PowerWFF3_SLEEP)
        {
            latency = PowerWFF3_RESUMETIMESLEEP;
        }
    }
    else
    {
        if (sleepState == PowerWFF3_SLEEP)
        {
            latency = PowerWFF3_TOTALTIMESLEEP;
        }
    }

    return latency;
}

/*
 *  ======== Power_getTransitionState ========
 *  Get the current sleep transition state.
 */
uint_fast16_t Power_getTransitionState(void)
{
    return powerState;
}

/*
 *  ======== Power_idleFunc ========
 *  Function needs to be plugged into the idle loop.
 *  It calls the configured policy function if it is not NULL.
 */
void Power_idleFunc()
{
    if (policyFxn != NULL && isPolicyEnabled == true)
    {
        (*(policyFxn))();
    }
}

/*
 *  ======== Power_registerNotify ========
 *  Register a function to be called on a specific power event.
 */
int_fast16_t Power_registerNotify(Power_NotifyObj *notifyObj,
                                  uint_fast16_t eventTypes,
                                  Power_NotifyFxn notifyFxn,
                                  uintptr_t clientArg)
{
    int_fast16_t status = Power_SOK;

    /* Check for NULL pointers */
    if ((notifyObj == NULL) || (notifyFxn == NULL))
    {
        Log_printf(LogModule_Power,
                   Log_WARNING,
                   "Power_registerNotify: Notify registration failed due to NULL pointer");

        status = Power_EINVALIDPOINTER;
    }
    else
    {
        notifyObj->eventTypes = eventTypes;
        notifyObj->notifyFxn  = notifyFxn;
        notifyObj->clientArg  = clientArg;

        Log_printf(LogModule_Power,
                   Log_INFO,
                   "Power_registerNotify: Register fxn at address 0x%x with event types 0x%x and clientArg 0x%x",
                   notifyFxn,
                   eventTypes,
                   clientArg);

        /* Place notify object on event notification queue. Assume that
         * List_Elem struct member is the first struct member in
         * Power_NotifyObj.
         */
        List_put(&notifyList, (List_Elem *)notifyObj);
    }

    return status;
}

/*
 *  ======== Power_unregisterNotify ========
 *  Unregister for a power notification.
 *
 */
void Power_unregisterNotify(Power_NotifyObj *notifyObj)
{
    Log_printf(LogModule_Power,
               Log_INFO,
               "Power_unregisterNotify: Unregister fxn at address 0x%x with event types 0x%x and clientArg 0x%x",
               notifyObj->notifyFxn,
               notifyObj->eventTypes,
               notifyObj->clientArg);

    /* Remove notify object from its event queue */
    List_remove(&notifyList, (List_Elem *)notifyObj);
}

/*
 *  ======== Power_setConstraint ========
 *  Declare an operational constraint.
 */
int_fast16_t Power_setConstraint(uint_fast16_t constraintId)
{
    uintptr_t key;

    DebugP_assert(constraintId < PowerWFF3_NUMCONSTRAINTS);

    key = HwiP_disable();

    /* Set the specified constraint in the constraintMask for faster access */
    constraintMask |= 1 << constraintId;

    /* Increment the specified constraint count */
    constraintCounts[constraintId]++;

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_releaseConstraint ========
 *  Release a previously declared constraint.
 */
int_fast16_t Power_releaseConstraint(uint_fast16_t constraintId)
{
    uintptr_t key;

    DebugP_assert(constraintId < PowerWFF3_NUMCONSTRAINTS);

    key = HwiP_disable();

    DebugP_assert(constraintCounts[constraintId] != 0);

    constraintCounts[constraintId]--;

    /* Only update the constraint mask if we removed the constraint entirely */
    if (constraintCounts[constraintId] == 0)
    {
        constraintMask &= ~(1 << constraintId);
    }

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_setDependency ========
 *  Declare a dependency upon a resource.
 */
int_fast16_t Power_setDependency(Power_Resource resourceId)
{
    uint8_t previousCount;
    uintptr_t key;

    DebugP_assert(resourceId < PowerWFF3_NUMRESOURCES);

    key = HwiP_disable();

    /* Buffer previous reference count */
    previousCount = resourceCounts[resourceId];

    /* Increment reference count */
    resourceCounts[resourceId]++;

    /* If the resource was NOT activated previously ... */
    if (previousCount == 0)
    {
        /* Enable clock for specified resource */
        HWREG(resourceClkEnRegs[resourceId]) = 1;
    }

    Log_printf(LogModule_Power,
               Log_INFO,
               "Power_setDependency: Updated resource counter = %d for resource ID = 0x%x",
               resourceCounts[resourceId], resourceId);

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_releaseDependency ========
 *  Release a previously declared dependency.
 */
int_fast16_t Power_releaseDependency(Power_Resource resourceId)
{
    uintptr_t key;

    DebugP_assert(resourceId < PowerWFF3_NUMRESOURCES);

    key = HwiP_disable();

    DebugP_assert(resourceCounts[resourceId] != 0);

    /* Decrement the reference count */
    resourceCounts[resourceId]--;

    /* If this was the last dependency being released.. */
    if (resourceCounts[resourceId] == 0)
    {
        /* Disable clock for specified resource */
        HWREG(resourceClkEnRegs[resourceId]) = 0;
    }

    Log_printf(LogModule_Power,
               Log_INFO,
               "Power_releaseDependency: Updated resource counter = %d for resource ID = 0x%x",
               resourceCounts[resourceId], resourceId);

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_shutdown ========
 */
int_fast16_t Power_shutdown(uint_fast16_t shutdownState, uint_fast32_t shutdownTime)
{
    /* Entering shutdown is not supported on WFF3 */
    return Power_EFAIL;
}

/*
 *  ======== Power_reset ========
 */
void Power_reset(void)
{
    HWREG(PRCM_AON_BASE + PRCM_AON_O_RSTCTL) = PRCM_AON_RSTCTL_SOCAON_M;
}

/*
 *  ======== Power_sleep ========
 */
int_fast16_t Power_sleep(uint_fast16_t sleepState)
{
    int_fast16_t status = Power_SOK;

    /* Signal all clients registered for pre sleep wakeup notification */
    status = PowerWFF3_notify(PowerWFF3_ENTERING_SLEEP);

    /* Check for any error */
    if (status != Power_SOK)
    {
        Log_printf(LogModule_Power,
                   Log_WARNING,
                   "Power_sleep: Entering sleep failed with status = 0x%x",
                   status);

        powerState = Power_ACTIVE;
        return status;
    }

    /* Disable clocks for all resources before entering sleep */
    for (uint32_t resourceId = 0; resourceId < PowerWFF3_NUMRESOURCES; resourceId++)
    {
        /* Disable clock for the resource if it has a power dependency */
        if (resourceCounts[resourceId] > 0)
        {
            HWREG(resourceClkEnRegs[resourceId]) = 0;
        }
    }

    /* Call RAM function to ensure that the CPU is not executing from flash
     * while it is disabled.
     */
    PowerWFF3_enterSleep();

    /* Re-enable clocks for all resources with a power dependency after
     * exiting sleep.
     */
    for (uint32_t resourceId = 0; resourceId < PowerWFF3_NUMRESOURCES; resourceId++)
    {
        /* Re-enable clock for the resource if it has a power dependency */
        if (resourceCounts[resourceId] > 0)
        {
            HWREG(resourceClkEnRegs[resourceId]) = 1;
        }
    }

    /* Now clear the transition state before re-enabling the scheduler */
    powerState = Power_ACTIVE;

    return Power_SOK;
}

/*
 *  ======== PowerWFF3_doWFI ========
 */
void PowerWFF3_doWFI(void)
{
    __WFI();
}

/*
 *  ======== PowerWFF3_getResetReason ========
 */
PowerWFF3_ResetReason PowerWFF3_getResetReason(void)
{
    PowerWFF3_ResetReason resetReason;
    uint16_t resetCause = HWREGH(RESET_CAUSE_ADDR);

    if ((resetCause & PowerWFF3_RESET_DSSM) == PowerWFF3_RESET_DSSM)
    {
        resetReason = PowerWFF3_RESET_DSSM;
    }
    else
    {
        switch (resetCause)
        {
            case (uint16_t)PowerWFF3_RESET_PIN_POR:
                resetReason = PowerWFF3_RESET_PIN_POR;
                break;
            case (uint16_t)PowerWFF3_RESET_RVML:
                resetReason = PowerWFF3_RESET_RVML;
                break;
            case (uint16_t)PowerWFF3_RESET_RVMH:
                resetReason = PowerWFF3_RESET_RVMH;
                break;
            case (uint16_t)PowerWFF3_RESET_BOD:
                resetReason = PowerWFF3_RESET_BOD;
                break;
            case (uint16_t)PowerWFF3_RESET_M33WD:
                resetReason = PowerWFF3_RESET_M33WD;
                break;
            case (uint16_t)PowerWFF3_RESET_CPU:
                resetReason = PowerWFF3_RESET_CPU;
                break;
            case (uint16_t)PowerWFF3_RESET_RFCORE:
                resetReason = PowerWFF3_RESET_RFCORE;
                break;
            default:
                resetReason = PowerWFF3_RESET_UNKNOWN;
                break;
        }
    }
    return resetReason;
}

/*
 *  ======== PowerWFF3_enterSleep ========
 *  Low level function used to enter sleep.
 *
 *  This function implements a workaround for a CM33 race condition between
 *  wakeup event and slow clock. If a wakeup event occurs within 1-2 slow clocks
 *  (~30.5-61 us) after the WFI instruction, the CM33 continues execution while
 *  the system goes to power-down. During this time window the CM33 cannot
 *  execute code from FLASH. Therefore, this function is placed in RAM and
 *  avoids external function calls.
 *
 *  The workaround uses ELP wake-up threshold and therefore that threshold
 *  cannot be used by other parts of the application. It delays the CM33 wakeup
 *  to happen at earliest when the ELP timer interrupt occurs.
 */
__attribute__((noinline, section(".TI.ramfunc"))) void PowerWFF3_enterSleep(void)
{
    uint32_t irqStatus0;
    uint32_t irqStatus1;
    uint32_t elptmren;

    bool elpRunning;
    bool elpSwMode;

    /* Set the SLEEPDEEP bit in SCB.SCR before executing WFI instruction. */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Store register values
     * - ISER[n]: NVIC IRQ status. IRQs 32-52 (bits 0-20) are valid in ISER[1].
     * - ELPTMR: ELP configuration
     */
#if NUM_INTERRUPTS > (64 + 16)
    #error "This driver has only been implemented to support up to 64 IRQs, but this device has more than 64 IRQs"
#endif
    irqStatus0 = NVIC->ISER[0];
    irqStatus1 = NVIC->ISER[1];
    elptmren   = HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN);

    /* Determine status of ELP module */
    elpRunning = (elptmren & HOSTMCU_AON_ELPTMREN_VAL_M) == HOSTMCU_AON_ELPTMREN_VAL_EN;
    elpSwMode  = (elptmren & HOSTMCU_AON_ELPTMREN_TMRSWCTL_M) == HOSTMCU_AON_ELPTMREN_TMRSWCTL_SW;

    /* Disable all enabled NVIC IRQs.
     * DSB and ISB instructions: Mimic CMSIS function NVIC_DisableIRQ().
     */
    NVIC->ICER[1] = irqStatus1;
    NVIC->ICER[0] = irqStatus0;
    __DSB();
    __ISB();

    /* Configure ELP timer interrupt:
     * - Enable ELP timer interrupt in NVIC.
     * - Disable ELP timer as wakeup source.
     * - Clear any pending ELP timer interrupt.
     * Compiler barrier macro included to mimic CMSIS function NVIC_EnableIRQ().
     */
    __COMPILER_BARRIER();
    NVIC->ISER[NVIC_IRQ_REG_NUM(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn)] = NVIC_IRQ_BIT_POS(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn);
    __COMPILER_BARRIER();
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGWICSNS) &= ~HOSTMCU_AON_CFGWICSNS_VAL_TMRREQ_EN;
    NVIC->ICPR[NVIC_IRQ_REG_NUM(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn)] = NVIC_IRQ_BIT_POS(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn);

    /* Make sure SW mode is enabled. */
    if (!elpSwMode)
    {
        HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_TMRSWCTL_SW;
    }

    /* Make sure ELP timer is stopped and counter reset. */
    ELP_TIMER_STOP_AND_RELOAD();

    /* Set and enable the wake-up threshold */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU) = (ELP_WAKEUP_THRESHOLD | HOSTMCU_AON_CFGTMRWU_EN_EN);

    /* Start the counter by setting the SET bit. We intentionally do not wait
     * for the ELP timer's enable bit (VAL) to go high as this takes around 2
     * slow clocks. The WFI acts as the waiting mechanism: The CPU stops
     * executing at WFI and will at earliest execute when the timer interrupt
     * gets pending.
     */
    ELP_TIMER_START();

    /* Ensure all memory accesses and side effects complete before WFI, and that
     * the pipeline is synchronized after wakeup.
     */
    __DSB();
    __WFI();
    __ISB();

    /* Disable wake-up timer threshold */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_CFGTMRWU) &= ~HOSTMCU_AON_CFGTMRWU_EN_EN;

    /* Disable ELP timer interrupt.
     * DSB and ISB instructions: Mimic CMSIS function NVIC_DisableIRQ().
     */
    NVIC->ICER[NVIC_IRQ_REG_NUM(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn)] = NVIC_IRQ_BIT_POS(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn);
    __DSB();
    __ISB();

    /* Clear the ELP wake-up timer event. */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_TMRWUREQ) = HOSTMCU_AON_TMRWUREQ_CLR_M;

    /* Clear the SET bit (skipped when calling ELP_TIMER_START()) */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) &= ~HOSTMCU_AON_ELPTMREN_ELPTMRSET;

    /* Stop ELP timer if it was not originally running. */
    if (!elpSwMode || (elpSwMode && !elpRunning))
    {
        ELP_TIMER_STOP_AND_RELOAD();
    }

    /* Clear pending ELP timer interrupt. */
    NVIC->ICPR[NVIC_IRQ_REG_NUM(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn)] = NVIC_IRQ_BIT_POS(INT_HOST_ELP_TMR_WAKEUP_REQ_IRQn);

    /* Restore previously enabled interrupts.
     * Compiler barrier macro included to mimic CMSIS function NVIC_EnableIRQ().
     */
    __COMPILER_BARRIER();
    NVIC->ISER[1] = irqStatus1;
    NVIC->ISER[0] = irqStatus0;
    __COMPILER_BARRIER();

    /* Clear the SLEEPDEEP bit in SCB.SCR such that any future WFI instructions
     * will only cause the CPU to enter IDLE.
     */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

/*
 *  ======== notify ========
 *  Send notifications to registered clients.
 *  Note: Task scheduling is disabled when this function is called.
 */
int_fast16_t PowerWFF3_notify(uint_fast16_t eventType)
{
    int_fast16_t notifyStatus;
    Power_NotifyFxn notifyFxn;
    uintptr_t clientArg;
    List_Elem *elem;

    /* If queue is empty, return immediately */
    if (!List_empty(&notifyList))
    {
        /* Point to first client notify object */
        elem = List_head(&notifyList);

        /* TODO: Change Power_registerNotify() & Power_unregisterNotify() to use
         * index instead of bitmask and then use multiple lists just like in
         * the TI-RTOS scheduler.
         * We currently walk the entire list 4 times when entering/exiting
         * sleep + switching HFXT...
         */

        /* Walk the queue and notify each registered client of the event */
        do
        {
            if (((Power_NotifyObj *)elem)->eventTypes & eventType)
            {
                /* Pull params from notify object */
                notifyFxn = ((Power_NotifyObj *)elem)->notifyFxn;
                clientArg = ((Power_NotifyObj *)elem)->clientArg;

                /* Call the client's notification function */
                Log_printf(LogModule_Power,
                           Log_VERBOSE,
                           "PowerWFF3_notify: Invoking notification fxn at address 0x%x with event type 0x%x and clientArg 0x%x",
                           notifyFxn,
                           eventType,
                           clientArg);

                notifyStatus = (int_fast16_t)(*(Power_NotifyFxn)notifyFxn)(eventType, 0, clientArg);

                /* If client declared error stop all further notifications */
                if (notifyStatus != Power_NOTIFYDONE)
                {
                    Log_printf(LogModule_Power,
                               Log_WARNING,
                               "PowerWFF3_notify: Notification fxn reported error, fxn at address 0x%x with event type 0x%x and notifyStatus 0x%x",
                               notifyFxn,
                               eventType,
                               notifyStatus);

                    return Power_EFAIL;
                }
            }

            /* Get next element in the notification queue */
            elem = List_next(elem);

        } while (elem != NULL);
    }

    return Power_SOK;
}

/*
 *  ======== PowerWFF3_SelectLFXT ========
 *  Configure the LFXT using external crystal oscillator
 *  as the slow-clock source.
 */
void PowerWFF3_selectLFXT(void)
{

    /* Set trim values before turning on the oscillator */
    PRCMSetLFXTTrims();

    /* Enable LFXT oscillator core */
    PRCMEnableLFXT();

    /* Set GPIO pull configuration */
    HWREG(IOMUX_BASE + IOMUX_O_LFXTNPCTL) |= IOMUX_LFXTNPCTL_CTL_UP;
    HWREG(IOMUX_BASE + IOMUX_O_SCLKIPCTL) |= IOMUX_SCLKIPCTL_CTL_UP;

    /* Wait 500 ms for LFXT to settle, this is the worst case settling time for the LFXT */
    CPUDelay(30000000);

    /* Verify that 5 clock cycles of LFXT has been detected */
    while (!PRCMLFXTStatusGood()) {}

    /* Tell HW that LFXT is operational */
    PRCMSetLFXTGood();

    /* Select LFXT as LF Clock source */
    PRCMSelectLFXT();

    Log_printf(LogModule_Power,
                  Log_INFO,
                  "PowerWFF3_selectLFXT: LFXT selected as LFCLK source");

    /* Turn off LFOSC to save power, as it is no longer needed */
    PRCMDisableLFOSC();
}
