/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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
 *  ======== PowerCC23X0.c ========
 */

#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/DebugP.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/Temperature.h>

#include <ti/drivers/utils/Math.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_clkctl.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_evtull.h)
#include DeviceFamily_constructPath(inc/hw_ckmd.h)
#include DeviceFamily_constructPath(inc/hw_rtc.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)
#include DeviceFamily_constructPath(inc/hw_pmctl.h)
#include DeviceFamily_constructPath(inc/hw_pmud.h)
#include DeviceFamily_constructPath(inc/hw_sys0.h)
#include DeviceFamily_constructPath(inc/hw_ioc.h)
#include DeviceFamily_constructPath(driverlib/cpu.h)
#include DeviceFamily_constructPath(driverlib/hapi.h)
#include DeviceFamily_constructPath(driverlib/gpio.h)
#include DeviceFamily_constructPath(driverlib/lrfd.h)
#include DeviceFamily_constructPath(driverlib/pmctl.h)
#include DeviceFamily_constructPath(cmsis/core/cmsis_compiler.h)

/* Forward declarations */
int_fast16_t PowerCC23X0_notify(uint_fast16_t eventType);
static void PowerCC23X0_oscillatorISR(uintptr_t arg);
static void PowerCC23X0_enterStandby(void);
static void PowerCC23X0_setDependencyCount(Power_Resource resourceId, uint8_t count);
bool PowerCC23X0_isValidResourceId(Power_Resource resourceId);
static void PowerCC23X0_startHFXT(void);
static void PowerCC23X0_hfxtCompensateFxn(int16_t currentTemperature,
                                          int16_t thresholdTemperature,
                                          uintptr_t clientArg,
                                          Temperature_NotifyObj *notifyObject);
static uint32_t PowerCC23X0_temperatureToRatio(int16_t temperature);
static void PowerCC23X0_updateHFXTRatio(uint32_t ratio);

/* Externs */
extern const PowerCC23X0_Config PowerCC23X0_config;
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* Function Macros */

/* We need to define the IOC_BASE_PIN_REG address ourselves since IOC_O_IOC0
 * does not exist on CC2340R2
 */
#define IOC_BASE_PIN_REG 0x00000100
#define IOC_ADDR(index)  (IOC_BASE + IOC_BASE_PIN_REG + (sizeof(uint32_t) * index))

/* Macro used to extract the resource group  from a resource ID */
#define RESOURCE_GROUP(resourceId) ((resourceId)&PowerCC23X0_PERIPH_GROUP_M)

/* Macro used to extract the bit index shift encoded from a resource ID */
#define RESOURCE_BIT_INDEX(resourceId) ((resourceId)&PowerCC23X0_PERIPH_BIT_INDEX_M)

#define HFXT_COMP_MAX_TEMP (125)
#define HFXT_COMP_MIN_TEMP (-40)

/* Type definitions */

/*! Type used for passing configuration information to HFXT temperature
 * notification callback
 */
typedef union
{
    struct
    {
        int16_t delta;
        int16_t threshold;
    } temperature;
    uint32_t value;
} PowerCC23X0_hfxtConfig;

/* Static Globals */

/*! Temperature notification to compensate the HFXT */
static Temperature_NotifyObj PowerCC23X0_hfxtCompNotifyObj = {0};

/*! Temperature compensation coefficients for HFXT */
static struct
{
    int32_t P0;
    int32_t P1;
    int32_t P2;
    int32_t P3;
    uint8_t shift;
} PowerCC23X0_hfxtCompCoefficients;

/* Global state variable to track if HFXT compensation is enabled or not.
 * It is used to check whether temperature notifications should be re-enabled
 * after an update or not, in case compensation has been asynchronously disabled
 */
static bool PowerCC23X0_hfxtCompEnabled = false;

/* Array to maintain constraint reference counts */
static uint8_t constraintCounts[PowerCC23X0_NUMCONSTRAINTS];

/* Mask of Power constraints for quick access */
static uint32_t constraintMask = 0;

/* Arrays to maintain resource dependency reference counts.
 * Each resource group will have an array associated with it, and the arrays can
 * be indexed using the bit index shift value encoded in the resource ID.
 */
static uint8_t resourceCountsClkctl0[PowerCC23X0_NUMRESOURCES_CLKCTL0];
static uint8_t resourceCountsLrfd[PowerCC23X0_NUMRESOURCES_LRFD];

/* Keeps track of the configured Power policy. Power_idleFunc() will not run
 * the policy if this is set to NULL
 */
static Power_PolicyFxn policyFxn = NULL;

/* Is the Power policy enabled? */
static bool isPolicyEnabled = false;

/* Has the Power driver been initialized */
static bool isInitialized = false;

/* Power state of the system. Idle, active, standby, etc */
static uint8_t powerState = Power_ACTIVE;

/* Event notification list */
static List_List notifyList;

/* Interrupt for handling clock switching */
static HwiP_Struct ckmHwi;

/* Non-static Globals */

/* Interrupt for ClockP and Power policy */
HwiP_Struct clockHwi;

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

    isPolicyEnabled = PowerCC23X0_config.policyFxn != NULL;

    policyFxn = PowerCC23X0_config.policyFxn;

    /* Construct the CKM hwi responsible for oscillator related events.
     * Since there is no dedicated CKM interrupt line, we need to mux one of
     * the configurable lines to the CKM.
     * CPUIRQ3 is dedicated to this purpose.
     */
    HwiP_construct(&ckmHwi, INT_CPUIRQ3, PowerCC23X0_oscillatorISR, NULL);

    HWREG(EVTSVT_BASE + EVTSVT_O_CPUIRQ3SEL) = EVTSVT_CPUIRQ3SEL_PUBID_AON_CKM_COMB;

    /* Enable a selection of CKM signals as interrupt sources. For now,
     * we will stick to LKCLKGOOD and AMPSETTLED since those are related to existing
     * notifications.
     */
    HWREG(CKMD_BASE + CKMD_O_IMSET) = CKMD_IMASK_AMPSETTLED | CKMD_IMASK_HFXTFAULT;

    HwiP_enableInterrupt(INT_CPUIRQ3);

    /* Use RTC channel 0 in compare mode. Channel 1 could be used for other
     * purposes.
     */
    HWREG(RTC_BASE + RTC_O_IMSET) = RTC_IMSET_EV0_M;

    /* Configure RTC to halt when CPU stopped during debug */
    HWREG(RTC_BASE + RTC_O_EMU) = RTC_EMU_HALT_STOP;

    /* Configure SysTimer to halt when CPU stopped during debug. The setting
     * is sync'd from RTC_EMU on each wakeup from standby.
     */
    HWREG(SYSTIM_BASE + SYSTIM_O_EMU) = SYSTIM_EMU_HALT_STOP;

    /* Start HFXT */
    PowerCC23X0_startHFXT();

    /* Enable tracking loop with HFXT as reference. This will automatically
     * calibrate LFOSC against HFXT whenever HFXT is enabled; usually after
     * waking up from standby.
     * This is needed to ensure fast HFXT startup and a reasonably accurate
     * LFOSC frequency.
     */
    HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) |= CKMD_HFTRACKCTL_EN_M | CKMD_HFTRACKCTL_REFCLK_HFXT;

    /* Enable GPIO and RTC standby wakeup sources */
    HWREG(EVTULL_BASE + EVTULL_O_WKUPMASK) = EVTULL_WKUPMASK_AON_IOC_COMB_M | EVTULL_WKUPMASK_AON_RTC_COMB_M;

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
    DebugP_assert(PowerCC23X0_isValidResourceId(resourceId));

    uint8_t bitIndex    = RESOURCE_BIT_INDEX(resourceId);
    uint_fast16_t group = RESOURCE_GROUP(resourceId);
    if (group == PowerCC23X0_PERIPH_GROUP_CLKCTL0)
    {
        return (int_fast16_t)resourceCountsClkctl0[bitIndex];
    }
    else if (group == PowerCC23X0_PERIPH_GROUP_LRFD)
    {
        return (int_fast16_t)resourceCountsLrfd[bitIndex];
    }

    return (int_fast16_t)Power_EINVALIDINPUT;
}

/*
 *  ======== Power_getConstraintCount ========
 *  Get the count of constraints that are currently set on a certain
 *  operational transition
 */
int_fast16_t Power_getConstraintCount(uint_fast16_t constraintId)
{
    DebugP_assert(constraintId < PowerCC23X0_NUMCONSTRAINTS);

    if (constraintId < PowerCC23X0_NUMCONSTRAINTS)
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
    uint32_t latency = 0;

    if (type == Power_RESUME)
    {
        if (sleepState == PowerLPF3_STANDBY)
        {
            latency = PowerCC23X0_RESUMETIMESTANDBY;
        }
    }
    else
    {
        if (sleepState == PowerLPF3_STANDBY)
        {
            latency = PowerCC23X0_TOTALTIMESTANDBY;
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
        status = Power_EINVALIDPOINTER;
    }
    else
    {
        notifyObj->eventTypes = eventTypes;
        notifyObj->notifyFxn  = notifyFxn;
        notifyObj->clientArg  = clientArg;

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

    DebugP_assert(constraintId < PowerCC23X0_NUMCONSTRAINTS);

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

    DebugP_assert(constraintId < PowerCC23X0_NUMCONSTRAINTS);

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
    uint8_t bitIndex;

    DebugP_assert(PowerCC23X0_isValidResourceId(resourceId));

    key = HwiP_disable();

    /* Buffer previous reference count */
    previousCount = Power_getDependencyCount(resourceId);

    /* Increment reference count */
    PowerCC23X0_setDependencyCount(resourceId, previousCount + 1);

    /* If the resource was NOT activated previously ... */
    if (previousCount == 0)
    {
        bitIndex = RESOURCE_BIT_INDEX(resourceId);
        /* Turn on the peripheral */
        switch (RESOURCE_GROUP(resourceId))
        {
            case PowerCC23X0_PERIPH_GROUP_CLKCTL0:
                HWREG(CLKCTL_BASE + CLKCTL_O_CLKENSET0) = 1 << bitIndex;
                break;
            case PowerCC23X0_PERIPH_GROUP_LRFD:
                LRFDSetClockDependency(1 << bitIndex, LRFD_CLK_DEP_POWER);
                break;
            default:
                break;
        }
    }

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_releaseDependency ========
 *  Release a previously declared dependency.
 */
int_fast16_t Power_releaseDependency(Power_Resource resourceId)
{
    uint8_t resourceCount;
    uintptr_t key;
    uint8_t bitIndex;

    DebugP_assert(PowerCC23X0_isValidResourceId(resourceId));

    key = HwiP_disable();

    resourceCount = Power_getDependencyCount(resourceId);

    DebugP_assert(resourceCount != 0);

    /* Decrement the reference count */
    resourceCount--;
    PowerCC23X0_setDependencyCount(resourceId, resourceCount);

    /* If this was the last dependency being released.. */
    if (resourceCount == 0)
    {
        bitIndex = RESOURCE_BIT_INDEX(resourceId);
        /* Turn off the peripheral */
        switch (RESOURCE_GROUP(resourceId))
        {
            case PowerCC23X0_PERIPH_GROUP_CLKCTL0:
                HWREG(CLKCTL_BASE + CLKCTL_O_CLKENCLR0) = 1 << bitIndex;
                break;
            case PowerCC23X0_PERIPH_GROUP_LRFD:
                LRFDReleaseClockDependency(1 << bitIndex, LRFD_CLK_DEP_POWER);
                break;
            default:
                break;
        }
    }

    HwiP_restore(key);

    return Power_SOK;
}

/*
 *  ======== Power_shutdown ========
 */
int_fast16_t Power_shutdown(uint_fast16_t shutdownState, uint_fast32_t shutdownTime)
{
    int_fast16_t notifyStatus;
    uint32_t hwiKey;
    uint8_t i;
    bool ioPending = false;

    hwiKey = HwiP_disable();

    /* Check if there is a constraint to prohibit shutdown */
    if (Power_getConstraintMask() & (1 << PowerLPF3_DISALLOW_SHUTDOWN))
    {
        HwiP_restore(hwiKey);
        return Power_ECHANGE_NOT_ALLOWED;
    }

    /* Check whether we were transitioning to another power state */
    if (powerState != Power_ACTIVE)
    {
        HwiP_restore(hwiKey);
        return Power_EBUSY;
    }

    /* Set new transition state to entering shutdown */
    powerState = Power_ENTERING_SHUTDOWN;

    /* Signal all clients registered for pre-shutdown notification */
    notifyStatus = PowerCC23X0_notify(PowerLPF3_ENTERING_SHUTDOWN);

    for (i = GPIO_pinLowerBound; i <= GPIO_pinUpperBound; i++)
    {
        /* Read WUCFGSD field once and check both values.
         * Use IOC3 since CC2340R2 does not have IOC0, IOC1, or IOC2.
         */
        uint32_t ioShutdownConfig = HWREG(IOC_ADDR(i)) & IOC_IOC3_WUCFGSD_M;

        if ((ioShutdownConfig == IOC_IOC3_WUCFGSD_WAKE_HIGH || ioShutdownConfig == IOC_IOC3_WUCFGSD_WAKE_LOW) &&
            GPIOGetEventDio(i))
        {
            ioPending = true;
        }
    }

    /* If no IO event is pending on a shutdown wakeup IO, go to shutdown */
    if (ioPending == false && notifyStatus == Power_SOK)
    {
        HWREG(PMCTL_BASE + PMCTL_O_SHTDWN) = PMCTL_SHTDWN_KEY_VALID;
    }

    /* If shutdown succeeded, should never get here */

    powerState = Power_ACTIVE;

    HwiP_restore(hwiKey);

    /* If we get here, failed to shutdown, return error code */
    return Power_EFAIL;
}

/*
 *  ======== Power_sleep ========
 */
int_fast16_t Power_sleep(uint_fast16_t sleepState)
{
    int_fast16_t status = Power_SOK;

    /* Signal all clients registered for pre standby wakeup notification */
    status = PowerCC23X0_notify(PowerLPF3_ENTERING_STANDBY);

    /* Check for any error */
    if (status != Power_SOK)
    {
        powerState = Power_ACTIVE;
        return status;
    }

    /* Call wrapper function to ensure that R0-R3 are saved and restored before
     * and after this function call. Otherwise, compilers will attempt to stash
     * values on the stack while on the PSP and then restore them just after
     * HapiEnterStandby() on the MSP. Which will cause wildly unexpected
     * behaviour.
     */
    PowerCC23X0_enterStandby();

    /* Now that we have returned and are executing code from flash again, start
     * up the HFXT using the workaround for the HFXT amplitude control ADC bias
     * point
     */
    PowerCC23X0_startHFXT();

    /* Now clear the transition state before re-enabling the scheduler */
    powerState = Power_ACTIVE;

    return status;
}

/*
 *  ======== Power_reset ========
 */
void Power_reset(void)
{
    PMCTLResetSystem();
}

/*
 *  ======== PowerCC23X0_doWFI ========
 */
void PowerCC23X0_doWFI(void)
{
    __WFI();
}

/*
 *  ======== PowerCC23X0_enterStandby ========
 *  Wrapper function to ensure that R0-R3 are saved and restored before and
 *  after this function call. Otherwise, compilers will attempt to stash
 *  values on the stack while on the PSP and then restore them just after
 *  HapiEnterStandby() on the MSP. Which will cause wildly unexpected behaviour.
 */
void PowerCC23X0_enterStandby(void)
{
    /* Declare static volatile variable to ensure the toolchain does not use
     * stack for the variable and does not optimize this memory allocation
     * away.
     */
    static volatile uint32_t controlPreStandby;

    /* Clear all CKM LDO SW control bits. If we do not do this before entering
     * standby, the LDO will remain on in standby and consume power. We do not
     * disable it earlier after turning on HFXT to avoid waiting 20us to safely
     * disable it.
     */
    HWREG(CKMD_BASE + CKMD_O_LDOCTL) = 0x0;

    /* Stash current CONTROL configuration to re-apply after wakeup.
     * Depending on the kernel used, we could be on PSP or MSP
     */
    controlPreStandby = __get_CONTROL();

    /* Switch to MSP. HapiEnterStandby() must execute from MSP since the
     * device reboots into privileged mode on MSP and HapiEnterStandby()
     * assumes it will be called running on MSP.
     */
    __set_CONTROL(0 << 1);

    /* - Save CPU state on MSP and MSP in CLKCTL_STBYPTR
     * - Enter standby
     * - Exit standby
     * - Restore CPU state from MSP
     * - Apply copyList
     */
    HapiEnterStandby(NULL);

    /* Switch back to previous stack pointer. */
    __set_CONTROL(controlPreStandby);
}

/*
 *  ======== PowerLPF3_selectLFOSC ========
 */
void PowerLPF3_selectLFOSC(void)
{
    /* Increase LFOSC nanoamp bias current to 150nA to minimise RTN */
    HWREG(CKMD_BASE + CKMD_O_TRIM1) |= CKMD_TRIM1_NABIAS_LFOSC;

    /* Select LFOSC */
    HWREG(CKMD_BASE + CKMD_O_LFCLKSEL) = CKMD_LFCLKSEL_MAIN_LFOSC;

    /* Start LFOSC */
    HWREG(CKMD_BASE + CKMD_O_LFOSCCTL) = CKMD_LFOSCCTL_EN;

    /* Disable LFINC filter settling preventing standby */
    HWREG(CKMD_BASE + CKMD_O_LFINCCTL) &= ~CKMD_LFINCCTL_PREVENTSTBY_M;

    /* Enable LFCLKGOOD and TRACKREFLOSS. TRACKREFLOSS may occur when entering
     * and exiting fake standby with the debugger attached.
     */
    HWREG(CKMD_BASE + CKMD_O_IMSET) = CKMD_IMASK_LFCLKGOOD | CKMD_MIS_TRACKREFLOSS_M;

    /* Disallow standby until LF clock is running. Otherwise, we will only
     * vector to the ISR after we wake up from standby the next time since the
     * CKM interrupt is purposefully not configured as a wakeup source.
     */
    Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
}

/*
 *  ======== PowerLPF3_selectLFXT ========
 */
void PowerLPF3_selectLFXT(void)
{
    /* Set LFINC override to 32.768 kHz.
     * Will not impact RTC since the fake LF ticks will have a higher priority
     * than LFINCOVR.
     */
    HWREG(CKMD_BASE + CKMD_O_LFINCOVR) = 0x001E8480 | CKMD_LFINCOVR_OVERRIDE_M;

    /* Set LFCLK  */
    HWREG(CKMD_BASE + CKMD_O_LFCLKSEL) = CKMD_LFCLKSEL_MAIN_LFXT;

    /* Start LFXT */
    HWREG(CKMD_BASE + CKMD_O_LFXTCTL) = CKMD_LFXTCTL_EN;

    /* Enable LFCLKGOOD */
    HWREG(CKMD_BASE + CKMD_O_IMSET) = CKMD_IMASK_LFCLKGOOD;

    /* Disallow standby until LF clock is running. Otherwise, we will only
     * vector to the ISR after we wake up from standby the next time since the
     * CKM interrupt is purposefully not configured as a wakeup source.
     */
    Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
}

/*
 *  ======== PowerCC23X0_oscillatorISR ========
 */
static void PowerCC23X0_oscillatorISR(uintptr_t arg)
{
    uint32_t maskedStatus = HWREG(CKMD_BASE + CKMD_O_MIS);

    /* Manipulating ICLR alone does not actually do anything. The CKM_COMB
     * signals are almost all level values that reset one cycle after writing to
     * ICLR. We need to update the mask instead to avoid looping in the ISR
     */
    HWREG(CKMD_BASE + CKMD_O_ICLR)  = maskedStatus;
    HWREG(CKMD_BASE + CKMD_O_IMCLR) = maskedStatus;

    if (maskedStatus & CKMD_MIS_AMPSETTLED_M)
    {
        PowerCC23X0_notify(PowerLPF3_HFXT_AVAILABLE);

        /* Allow standby again now that HFXT has finished starting */
        Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    }
    else if (maskedStatus & CKMD_MIS_HFXTFAULT_M)
    {
        /* If there was a fault, restart HFXT. Consider issuing a notification
         * to allow logging. If we keep it like this, we could get stuck in an
         * infinite loop restarting a faulty oscillator. Then again, it is not
         * like there is a great way to recover from that.
         */
        HWREG(CKMD_BASE + CKMD_O_HFXTCTL) &= ~CKMD_HFXTCTL_EN_M;

        /* Start up the HFXT using the workaround for the HFXT amplitude control ADC
         * bias point
         */
        PowerCC23X0_startHFXT();
    }

    if (maskedStatus & CKMD_MIS_LFCLKGOOD_M)
    {
        /* Enable LF clock monitoring */
        HWREG(CKMD_BASE + CKMD_O_LFMONCTL) = CKMD_LFMONCTL_EN;

        /* Enable LF clock loss reset while in standby */
        HWREG(PMCTL_BASE + PMCTL_O_RSTCTL) |= PMCTL_RSTCTL_LFLOSS_ARMED;

        /* Send out notification for LF clock switch */
        PowerCC23X0_notify(PowerLPF3_LFCLK_SWITCHED);

        /* Allow standby again now that we have sent out the notification */
        Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    }

    if (maskedStatus & CKMD_MIS_TRACKREFLOSS_M)
    {
        /* Disable interrupts as HFXT SWTCXO may interrupt and modify HFTRACKCTL
         * with a higher priority depending on user interrupt priorities.
         */
        uintptr_t key = HwiP_disable();

        /* Disable tracking */
        HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) &= ~CKMD_HFTRACKCTL_EN_M;

        /* Re-enable tracking */
        HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) |= CKMD_HFTRACKCTL_EN_M;

        HwiP_restore(key);

        /* Re-enable TRACKREFLOSS */
        HWREG(CKMD_BASE + CKMD_O_IMSET) = CKMD_MIS_TRACKREFLOSS_M;
    }
}

/*
 *  ======== PowerCC23X0_startHFXT ========
 *  We need to manually start HFXT because the bias voltage around HFXT swings
 *  is not stable across voltage or temperature because it is not remeasured
 *  every time HFXT starts up.
 *  Not manually starting HFXT can lead to:
 *  - HFXT never becoming available
 *  - Poor phase noise in the radio
 */
static void PowerCC23X0_startHFXT(void)
{
    /* Return immediately if HFXT is already enabled. Not doing so will cause
     * TRACKREFLOSS when starting the LDO. This situation can arise when:
     * - Waking up from fake standby. Fake standby does not shut down the HFXT,
     *   unlike real standby.
     * - Waking up without actually entering real standby. If a wakeup source is
     *   pending when we reach WFI in the ROM function, the hardware will just
     *   turn that into a NOP instead and not run through the regular state
     *   machine.
     */
    if ((HWREG(CKMD_BASE + CKMD_O_HFXTCTL) & CKMD_HFXTCTL_EN_M) == CKMD_HFXTCTL_EN)
    {
        return;
    }

    /* Start LDO */
    HWREG(CKMD_BASE + CKMD_O_LDOCTL) = (CKMD_LDOCTL_SWOVR | CKMD_LDOCTL_STARTCTL | CKMD_LDOCTL_START | CKMD_LDOCTL_EN);

    /* Bypass a lowpass filter that is connected to the reference voltage for
     * 66us to ensure that reference has settled
     */
    HapiWaitUs(66);

    /* Clear START bits */
    HWREG(CKMD_BASE + CKMD_O_LDOCTL) = (CKMD_LDOCTL_SWOVR | CKMD_LDOCTL_HFXTLVLEN | CKMD_LDOCTL_EN);

    /* Force bias measurement before enabling HFXT - Set SRCSEL = BIAS.
     * Enable the peak detector in the HFXT amplitude control loop to control
     * RF phase jumps.
     */
    HWREG(CKMD_BASE + CKMD_O_AMPADCCTL) = (CKMD_AMPADCCTL_SWOVR | CKMD_AMPADCCTL_PEAKDETEN_ENABLE |
                                           CKMD_AMPADCCTL_ADCEN_ENABLE);

    /* Delay to settle PEAKDET + ADC */
    HapiWaitUs(6);

    /* Clear raw interrupt for ADCBIASUPD */
    HWREG(CKMD_BASE + CKMD_O_ICLR) = CKMD_ICLR_ADCBIASUPD;

    /* Start an SAR conversion */
    HWREG(CKMD_BASE + CKMD_O_AMPADCCTL) |= CKMD_AMPADCCTL_SARSTRT;

    /* Immediately prevent any SAR new conversions from starting. The one
     * started above will complete though.
     */
    HWREG(CKMD_BASE + CKMD_O_AMPADCCTL) &= ~CKMD_AMPADCCTL_SARSTRT;

    /* Wait until HFXT-ADC BIAS measurement is done */
    while (!((HWREG(CKMD_BASE + CKMD_O_RIS) & CKMD_RIS_ADCBIASUPD_M) == CKMD_RIS_ADCBIASUPD)) {}

    /* Clear SW override of amplitude ADC */

    /* Keep PEAKDET on */
    HWREG(CKMD_BASE + CKMD_O_AMPADCCTL) &= ~(CKMD_AMPADCCTL_SWOVR_M | CKMD_AMPADCCTL_ADCEN_M);

    /* Start HFXT */
    HWREG(CKMD_BASE + CKMD_O_HFXTCTL) |= CKMD_HFXTCTL_EN;

    /* Disallow standby until AMPSETTLED is true */
    Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);

    /* Enable the AMPSETTLED interrupt.
     * Since it is a level status signal, it remains asserted when we are
     * running on HFXT and cannot be cleared.
     * The oscillator interrupt removes it from the interrupt mask to prevent
     * repeated vectoring.
     */
    HWREG(CKMD_BASE + CKMD_O_ICLR)  = CKMD_ICLR_AMPSETTLED;
    HWREG(CKMD_BASE + CKMD_O_IMSET) = CKMD_IMSET_AMPSETTLED;
}

/*
 *  ======== PowerCC23X0_notify ========
 *  Send notifications to registered clients.
 *  Note: Task scheduling is disabled when this function is called.
 */
int_fast16_t PowerCC23X0_notify(uint_fast16_t eventType)
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

        /* Walk the queue and notify each registered client of the event */
        do
        {
            if (((Power_NotifyObj *)elem)->eventTypes & eventType)
            {
                /* Pull params from notify object */
                notifyFxn = ((Power_NotifyObj *)elem)->notifyFxn;
                clientArg = ((Power_NotifyObj *)elem)->clientArg;

                /* Call the client's notification function */
                notifyStatus = (int_fast16_t)(*(Power_NotifyFxn)notifyFxn)(eventType, 0, clientArg);

                /* If client declared error stop all further notifications */
                if (notifyStatus != Power_NOTIFYDONE)
                {
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
 *  ======== PowerCC23X0_setDependencyCount ========
 */
void PowerCC23X0_setDependencyCount(Power_Resource resourceId, uint8_t count)
{
    uint8_t bitIndex    = RESOURCE_BIT_INDEX(resourceId);
    uint_fast16_t group = RESOURCE_GROUP(resourceId);

    DebugP_assert(PowerCC23X0_isValidResourceId(resourceId));

    if (group == PowerCC23X0_PERIPH_GROUP_CLKCTL0)
    {
        resourceCountsClkctl0[bitIndex] = count;
    }
    else if (group == PowerCC23X0_PERIPH_GROUP_LRFD)
    {
        resourceCountsLrfd[bitIndex] = count;
    }
}

/*
 *  ======== PowerCC23X0_isValidResourceId ========
 */
bool PowerCC23X0_isValidResourceId(Power_Resource resourceId)
{
    uint8_t bitIndex    = RESOURCE_BIT_INDEX(resourceId);
    uint_fast16_t group = RESOURCE_GROUP(resourceId);

    if (group == PowerCC23X0_PERIPH_GROUP_CLKCTL0)
    {
        return bitIndex < PowerCC23X0_NUMRESOURCES_CLKCTL0;
    }
    else if (group == PowerCC23X0_PERIPH_GROUP_LRFD)
    {
        return bitIndex < PowerCC23X0_NUMRESOURCES_LRFD;
    }
    else
    {
        return false;
    }
}

/*
 *  ======== PowerCC23X0_temperatureToRatio ========
 */
static uint32_t PowerCC23X0_temperatureToRatio(int16_t temperature)
{
    /* Calculate unshifted ppm offset. Fixed-point coefficients are assumed to
     * be set so that this computation does not overflow 32 bits in the -40, 125
     * degC range.
     */
    int32_t hfxtPpmOffset = PowerCC23X0_hfxtCompCoefficients.P3 * temperature * temperature * temperature +
                            PowerCC23X0_hfxtCompCoefficients.P2 * temperature * temperature +
                            PowerCC23X0_hfxtCompCoefficients.P1 * temperature + PowerCC23X0_hfxtCompCoefficients.P0;

    /* Calculate correct frequency offset, using shifted hfxtPpmOffset.
     * Frequency offset = 48000000 Hz * (hfxtPpmOffset >> shift) / 1000000
     *                  = 48 Hz * hfxtPpmOffset >> shift
     * Do 64-bit multiplication, since this will most likely overflow 32 bits.
     * Signed right-shift will result in an arithmetic shift operation.
     */
#if !(defined(__IAR_SYSTEMS_ICC__) || (defined(__clang__) && defined(__ti_version__)) || defined(__GNUC__))
    #warning The following signed right-shift operation is implementation-defined
#endif
    int32_t hfxtFreqOffset = (int32_t)((48LL * (int64_t)hfxtPpmOffset) >> PowerCC23X0_hfxtCompCoefficients.shift);

    /* Calculate temperature dependent ppm offset of the capacitor array on the
     * crystal input pins, modelled as ppm(T) = 0.07 * (T - 25) + 10
     * Input frequency is assumed 48 MHz, and any potential crystal offset is
     * neglected and not factored into the cap array offset calculation.
     * frequency_offset(T) = 48000000 * (0.07 * (T - 25) + 10) / 1000000
     *                     = 3.36 * (T - 25) + 480
     * To avoid floating-point multiplication and integer division, 3.36 is
     * approximated as 3523215 / 2^20 ~ 3.35999966. The error introduced by
     * this approximation is negligable.
     */
#if !(defined(__IAR_SYSTEMS_ICC__) || (defined(__clang__) && defined(__ti_version__)) || defined(__GNUC__))
    #warning The following signed right-shift operation is implementation-defined
#endif
    int32_t capArrayOffset = ((3523215 * (temperature - 25)) >> 20) + 480;

    /* Calculate the actual reference input frequency to the tracking loop,
     * accounting for the HFXT offset and cap array offset
     */
    int32_t refFreq = 48000000 + hfxtFreqOffset + capArrayOffset;

    /* Calculate word to write to HFTRACKCTL.RATIO. Expression taken from
     * register description: ratio = 24MHz / (2 * reference_frequency) * 2^24
     * 64-bit division is required, which is truncated to 32 bit
     */
    uint32_t ratio = (uint32_t)(0xB71B00000000LL / (int64_t)refFreq);

    return ratio;
}

/*
 *  ======== PowerCC23X0_updateHFXTRatio ========
 */
static void PowerCC23X0_updateHFXTRatio(uint32_t ratio)
{
    /* Update HFTRACKCTL atomically */
    uintptr_t key = HwiP_disable();
    uint32_t temp = HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) & ~CKMD_HFTRACKCTL_RATIO_M;
    temp |= ratio & CKMD_HFTRACKCTL_RATIO_M;
    HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) = temp;
    HwiP_restore(key);
}

/*
 *  ======== PowerCC23X0_hfxtCompensateFxn ========
 */
static void PowerCC23X0_hfxtCompensateFxn(int16_t currentTemperature,
                                          int16_t thresholdTemperature,
                                          uintptr_t clientArg,
                                          Temperature_NotifyObj *notifyObject)
{
    uintptr_t key;
    uint32_t ratio;
    PowerCC23X0_hfxtConfig hfxtConfig;
    hfxtConfig.value = (uint32_t)clientArg;

    /* Sanitize current temperature to fall within valid range. This ensures
     * that 32-bit overflow does not occur in the ppm calculation below.
     */
    if (currentTemperature > HFXT_COMP_MAX_TEMP)
    {
        currentTemperature = HFXT_COMP_MAX_TEMP;
    }

    if (currentTemperature < HFXT_COMP_MIN_TEMP)
    {
        currentTemperature = HFXT_COMP_MIN_TEMP;
    }

    key = HwiP_disable();

    /* If HFXT compensation has been disabled asynchronously during execution of
     * this callback then do not re-register the notification object
     */
    if (PowerCC23X0_hfxtCompEnabled)
    {
        if (currentTemperature > hfxtConfig.temperature.threshold)
        {
            /* If temperature is above compensation threshold then compute a
             * compensated ratio-value and update the ratio register in the
             * tracking loop
             */
            ratio = PowerCC23X0_temperatureToRatio(currentTemperature);
            PowerCC23X0_updateHFXTRatio(ratio);

            /* Register the notification again with updated thresholds. Notification thresholds must be crossed to
             * trigger, so the upper and lower limits are decreased by 1 to maintain a range of +/- delta.
             */
            Temperature_registerNotifyRange(notifyObject,
                                            currentTemperature + hfxtConfig.temperature.delta - 1,
                                            currentTemperature - hfxtConfig.temperature.delta + 1,
                                            PowerCC23X0_hfxtCompensateFxn,
                                            clientArg);
        }
        else
        {
            /* If temperature is at or below compensation threshold then reset
             * the tracking loop ratio to remove any compensation, and register
             * a new high notification. The new limit should not be lower than
             * the compensation threshold.
             */
            PowerCC23X0_updateHFXTRatio(CKMD_HFTRACKCTL_RATIO_REF48M);

            Temperature_registerNotifyHigh(notifyObject,
                                           Math_MAX(hfxtConfig.temperature.threshold,
                                                    currentTemperature + hfxtConfig.temperature.delta - 1),
                                           PowerCC23X0_hfxtCompensateFxn,
                                           clientArg);
        }
    }

    HwiP_restore(key);
}

/*
 *  ======== PowerLPF3_initHFXTCompensation ========
 */
void PowerLPF3_initHFXTCompensation(int32_t P0,
                                    int32_t P1,
                                    int32_t P2,
                                    int32_t P3,
                                    uint8_t shift,
                                    __attribute__((unused)) bool fcfgInsertion)
{
    PowerCC23X0_hfxtCompCoefficients.P0    = P0;
    PowerCC23X0_hfxtCompCoefficients.P1    = P1;
    PowerCC23X0_hfxtCompCoefficients.P2    = P2;
    PowerCC23X0_hfxtCompCoefficients.P3    = P3;
    PowerCC23X0_hfxtCompCoefficients.shift = shift;

    /* If device offers FCFG insertion data it will be factored in here.
     * Currently no device supports this.
     */
}

/*
 *  ======== PowerLPF3_enableHFXTCompensation ========
 */
void PowerLPF3_enableHFXTCompensation(int16_t tempThreshold, int16_t tempDelta)
{

    if (PowerCC23X0_hfxtCompEnabled == false)
    {
        PowerCC23X0_hfxtCompEnabled = true;

        Temperature_init();

        int16_t currentTemperature = Temperature_getTemperature();

        PowerCC23X0_hfxtConfig config;
        config.temperature.threshold = tempThreshold;
        config.temperature.delta     = tempDelta;

        /* Only perform temperature compensation if the temperature is above the
         * set threshold. If it is not, then register a high notification on the
         * threshold
         */
        if (currentTemperature > tempThreshold)
        {
            PowerCC23X0_hfxtCompensateFxn(currentTemperature,
                                          0,
                                          (uintptr_t)config.value,
                                          &PowerCC23X0_hfxtCompNotifyObj);
        }
        else
        {
            Temperature_registerNotifyHigh(&PowerCC23X0_hfxtCompNotifyObj,
                                           tempThreshold,
                                           PowerCC23X0_hfxtCompensateFxn,
                                           (uintptr_t)config.value);
        }
    }
}

/*
 *  ======== PowerLPF3_disableHFXTCompensation ========
 */
void PowerLPF3_disableHFXTCompensation(void)
{

    uintptr_t key = HwiP_disable();
    if (PowerCC23X0_hfxtCompEnabled == true)
    {
        PowerCC23X0_hfxtCompEnabled = false;

        Temperature_unregisterNotify(&PowerCC23X0_hfxtCompNotifyObj);

        /* Update HFTRACKCTL.RATIO to reset-value */
        PowerCC23X0_updateHFXTRatio(CKMD_HFTRACKCTL_RATIO_REF48M);
    }
    HwiP_restore(key);
}
