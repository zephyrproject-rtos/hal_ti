/*
 * Copyright (c) 2021-2026, Texas Instruments Incorporated
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
 *  ======== RCLLPF3_Hal.c ========
 */

#include <ti/drivers/Power.h>

#include <ti/drivers/Temperature.h>
#include <ti/drivers/BatteryMonitor.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_clkctl.h)
#include DeviceFamily_constructPath(inc/hw_ckmd.h)
#include DeviceFamily_constructPath(inc/hw_sys0.h)

#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)

#include DeviceFamily_constructPath(driverlib/lrfd.h)

#include <ti/log/Log.h>

#include <ti/drivers/rcl/hal/RCL_Hal.h>

#ifndef SOCFPGA
/* FPGA doesn't support Standby */
static int RCL_Hal_powerPostNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
static void RCL_Hal_temperaturePostNotifyFxn(int16_t currentTemperature,
                                            int16_t thresholdTemperature,
                                            uintptr_t clientArg,
                                            Temperature_NotifyObj *notifyObject);
static Power_NotifyObj powerAwakeStandbyObj;
static Power_NotifyObj powerEnterStandbyObj;
#endif
static Temperature_NotifyObj temperatureChangeNotifyObj = {0};

static void RCL_Hal_cancelLrfdSystim0(void);

#define RCL_DEFAULT_HFTRACKCTL_RATIO    CKMD_HFTRACKCTL_RATIO_REF48M

static HwiP_Struct schedHwi;
void (*halSchedFsmCb)(void) = NULL;

static void RF_schedHwi(uintptr_t a)
{
    (void) a;
    if (halSchedFsmCb != NULL)
    {
        halSchedFsmCb();
    }
}

static HwiP_Struct dispatchHwi;
void (*halDispatchFsmCb)(void) = NULL;
static void RF_dispatchHwi(uintptr_t a)
{
    (void) a;
    if (halDispatchFsmCb != NULL)
    {
        halDispatchFsmCb();
    }
}

static HwiP_Struct commandHwi;
void (*halCommandFsmCb)(void) = NULL;
static void RF_commandHwi(uintptr_t a)
{
    (void) a;
    if (halCommandFsmCb != NULL)
    {
        halCommandFsmCb();
    }
}

uint32_t RCL_Hal_getCommandIfgReg(void)
{
    uint32_t dbellIrq;
    /* Using masked interrupt */
    dbellIrq = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_MIS0);
    /* Remove SYSTIM 0 and 1 interrupts, as they should be handled by RCL_Hal_checkClearTimerCompare() */
    dbellIrq &= ~(LRFDDBELL_MIS0_SYSTIM0_M | LRFDDBELL_MIS0_SYSTIM1_M);
    /* Clear interrupts (unmasked only) */
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = dbellIrq;

    return dbellIrq;
}

uint32_t RCL_Hal_getDispatchIfgReg(void)
{
    uint32_t dbellIrq;
    /* Using masked interrupt */
    dbellIrq = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_MIS1);
    /* Clear interrupts (unmasked only) */
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR1) = dbellIrq;

    return dbellIrq;
}

/*
 * Initialize RCL interrupt handlers
 */
void RCL_Hal_initFsm(void (*dispatchFsmCb)(void), void (*schedFsmCb)(void),
                  void (*commandFsmCb)(void))
{
    HwiP_Params hp;
    HwiP_Params_init(&hp);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    hp.priority = INT_PRI_LEVEL4;
#else
    hp.priority = INT_PRI_LEVEL2;
#endif
    (void) HwiP_construct(&schedHwi, INT_CPUIRQ4, RF_schedHwi, &hp);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    hp.priority = INT_PRI_LEVEL2;
#else
    hp.priority = INT_PRI_LEVEL1;
#endif
    (void) HwiP_construct(&dispatchHwi, INT_LRFD_IRQ1, RF_dispatchHwi,  &hp);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    hp.priority = INT_PRI_LEVEL1;
#else
    hp.priority = INT_PRI_LEVEL0;
#endif
    (void) HwiP_construct(&commandHwi, INT_LRFD_IRQ0, RF_commandHwi,  &hp);

    halDispatchFsmCb = dispatchFsmCb;
    halSchedFsmCb = schedFsmCb;
    halCommandFsmCb = commandFsmCb;
    /* TODO: See RCL-345 */

    HWREG(EVTSVT_BASE + EVTSVT_O_CPUIRQ4SEL) = 0xE; /* LRFDIRQ2 */
}


void RCL_Hal_triggerCommandFsm(void)
{
    /* Software trig command FSM */
    HwiP_post(INT_LRFD_IRQ0);
}

void RCL_Hal_triggerDispatchFsm(void)
{
    /* Software trig dispatch IRQ */
    HwiP_post(INT_LRFD_IRQ1);
}

void RCL_Hal_triggerSchedulerFsm(void)
{
    /* Software schedule IRQ */
    HwiP_post(INT_CPUIRQ4);
}

uint32_t RCL_Hal_getCurrentTime(void)
{
    return (uint32_t) HWREG(SYSTIM_BASE + SYSTIM_O_TIME250N);
}

enum {
    SYSTIM_CH2_SETUP = 1, /* Early start, to kick off setup */
    SYSTIM_CH2_START = 2, /* Start event to radio */
    SYSTIM_CH2_STOP = 3,  /* Hard stop time */
} channel2usage = SYSTIM_CH2_SETUP;

void RCL_Hal_enableSetupTimeIrq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void RCL_Hal_setupSetupTime(uint32_t time)
{
    channel2usage = SYSTIM_CH2_SETUP;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = time;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
#ifndef SOCFPGA
    /* The power driver uses SYSTIM_0_IMASK to restore the timeouts (including CH2).
       Therefore, we need to set this register in case the system goes into standby. */
    HWREG(SYSTIM_BASE + SYSTIM_O_IMSET) = SYSTIM_IMSET_EV2_SET;
#endif
}

void RCL_Hal_setupStartTime(uint32_t time)
{
    channel2usage = SYSTIM_CH2_START;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = time;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void RCL_Hal_setupHardStopTime(uint32_t time)
{
    channel2usage = SYSTIM_CH2_STOP;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = time;
    /* Interrupt is not always needed, as event will be handled by PBE */
}

void RCL_Hal_enableHardStopTimeIrq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void RCL_Hal_disableHardStopTimeIrq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~LRFDDBELL_IMASK0_SYSTIM0_M;
}

void RCL_Hal_setupGracefulStopTime(uint32_t time)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM1_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CC) = time;
    /* Interrupt is not always needed, as event will be handled by PBE */
}

void RCL_Hal_enableGracefulStopTimeIrq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM1_M;
}

static void RCL_Hal_cancelLrfdSystim0(void)
{
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = 0;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CFG) = SYSTIM_CH2CFG_MODE_CAPT;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CFG) = SYSTIM_CH2CFG_MODE_DIS;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & (~LRFDDBELL_IMASK0_SYSTIM0_M);
#ifndef SOCFPGA
    /* The power driver uses SYSTIM_0_IMASK to restore the timeouts (including CH2).
       Therefore, we need to clear the CH2 IMASK field in addition. */
    HWREG(SYSTIM_BASE + SYSTIM_O_IMCLR) = SYSTIM_IMCLR_EV2_CLR;
#endif
}

void RCL_Hal_cancelSetupTime(void)
{
    RCL_Hal_cancelLrfdSystim0();
}

void RCL_Hal_cancelStartTime(void)
{
    RCL_Hal_cancelLrfdSystim0();
}

void RCL_Hal_cancelHardStopTime(void)
{
    RCL_Hal_cancelLrfdSystim0();
}

void RCL_Hal_cancelGracefulStopTime(void)
{
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CC) = 0;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CFG) = SYSTIM_CH3CFG_MODE_CAPT;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CFG) = SYSTIM_CH3CFG_MODE_DIS;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =  HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~LRFDDBELL_IMASK0_SYSTIM1_M;
}

void RCL_Hal_enableClkBuffer(void)
{
#ifndef SOCFPGA
    /* FPGA doesn't support standby */
    HWREG( CKMD_BASE + CKMD_O_HFXTCTL ) |= CKMD_HFXTCTL_HPBUFEN;
#endif
}

void RCL_Hal_setupSyncFoundCap(void)
{
    /* SRAT sync found repeat capture config */
    /* Route event_ibus(21) (mdm) to DBELL input (capt_sources[0]) */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SYSTIMEVTMUX0) = (21 << LRFDMDM_SYSTIMEVTMUX0_SEL0_S);
    /* Route through DBELL */
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_SYSTIMOEV) = (LRFDDBELL_SYSTIMOEV_SRC2_MCESYSTIM0);
    /* SYSTIM channel 4 uses srat_ievent(0) as repeated capture trigger */
    HWREG(SYSTIM_BASE + SYSTIM_O_CH4CFG) |= SYSTIM_CH4CFG_INP_RISE | SYSTIM_CH4CFG_MODE_CAPT | SYSTIM_CH4CFG_REARM_EN;
}

HalTimerEvent RCL_Hal_checkClearTimerCompare(void)
{
    HalTimerEvent event = HAL_TIMER_EVT_NONE;

    uint32_t mis0 = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_MIS0);

    /* Start or hard-stop takes priority, meaning hard-stop takes priority over graceful. */
    if ((mis0 & LRFDDBELL_MIS0_SYSTIM0_M) != 0U)
    {
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & (~LRFDDBELL_IMASK0_SYSTIM0_M);
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
#ifndef SOCFPGA
        /* The power driver uses SYSTIM_0_IMASK to restore the timeouts (including CH2).
        Therefore, we need to clear the CH2 IMASK field in addition. */
        HWREG(SYSTIM_BASE + SYSTIM_O_IMCLR) = SYSTIM_IMCLR_EV2_CLR;
#endif
        switch (channel2usage)
        {
            case SYSTIM_CH2_SETUP:
                event = HAL_TIMER_EVT_SETUP;
                break;
            case SYSTIM_CH2_START:
                event = HAL_TIMER_EVT_START;
                break;
            case SYSTIM_CH2_STOP:
                event = HAL_TIMER_EVT_HARD_STOP;
                break;
            default:
                break;
        }
    }
    else if ((mis0 & LRFDDBELL_MIS0_SYSTIM1_M) != 0U)
    {
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & (~LRFDDBELL_IMASK0_SYSTIM1_M);
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM1_M;
        event = HAL_TIMER_EVT_GRACEFUL_STOP;
    }
    else
    {
        /* Do nothing */
    }

    return event;
}

void RCL_Hal_initDispatchRadioInterrupts(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR1) = UINT32_MAX;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK1) = mask;
}

void RCL_Hal_enableCommandRadioInterrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
        HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | mask;
}

void RCL_Hal_clearCommandRadioInterrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = mask;
}

void RCL_Hal_disableCommandRadioInterrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
            HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~mask;
}

void RCL_Hal_disableAllCommandRadioInterrupts(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = 0;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = UINT32_MAX;
}

void RCL_Hal_disableAllDispatchRadioInterrupts(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK1) = 0;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR1) = UINT32_MAX;
}

void RCL_Hal_setRclClockEnable(uint16_t mask)
{
    uintptr_t key = HwiP_disable();
    LRFDSetClockDependency(mask, LRFD_CLK_DEP_RCL);
    HwiP_restore(key);
}

void RCL_Hal_clearRclClockEnable(uint16_t mask)
{
    uintptr_t key = HwiP_disable();
    LRFDReleaseClockDependency(mask, LRFD_CLK_DEP_RCL);
    HwiP_restore(key);
}

uint8_t RCL_Hal_setDcdcIpeakSetting(uint8_t setting)
{
    /* Read previous value so that it can be restored later */
    uint8_t previousIpeakSetting = (uint8_t) (HWREG(SYS0_BASE + SYS0_O_TMUTE4) & SYS0_TMUTE4_IPEAK_M) >> SYS0_TMUTE4_IPEAK_S;
    /* Run in protected region to ensure no interrupt comes in between the writes */
    uintptr_t key = HwiP_disable();
    /*
    * Unlock mutable registers to allow writing back tmute4. Register-write must follow within 32 clk-cycles,
    * after which the mutable registers will be automatically locked.
    */
    HWREG(SYS0_BASE + SYS0_O_MUNLOCK) = SYS0_MUNLOCK_KEY_UNLOCK;
    /* Set IPEAK value */
    HWREG(SYS0_BASE + SYS0_O_TMUTE4) = (HWREG(SYS0_BASE + SYS0_O_TMUTE4) & ~SYS0_TMUTE4_IPEAK_M) | (((uint32_t) setting << SYS0_TMUTE4_IPEAK_S) & SYS0_TMUTE4_IPEAK_M);
    /* Lock the mutable registers by writing something other than the key */
    HWREG(SYS0_BASE + SYS0_O_MUNLOCK) = SYS0_MUNLOCK_KEY_LOCK;
    HwiP_restore(key);
    return previousIpeakSetting;
}

#ifndef SOCFPGA
static int RCL_Hal_powerPostNotifyFxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    (void) eventArg;

    void (*rclPowerNotify)(RCL_PowerEvent) = (void (*)(RCL_PowerEvent)) clientArg;

    if (rclPowerNotify != NULL)
    {
        if (eventType == PowerLPF3_AWAKE_STANDBY)
        {
            rclPowerNotify(RCL_POWER_STANDBY_AWAKE);
        }
        else if (eventType == PowerLPF3_ENTERING_STANDBY)
        {
            rclPowerNotify(RCL_POWER_STANDBY_ENTER);
        }
        else
        {
            /* Do nothing */
        }
    }
    return (Power_NOTIFYDONE);
}
#endif

void RCL_Hal_powerSetStandbyConstraint(void)
{
    /* Note: The power driver requires that setting and releasing constraints come in pairs */
#ifndef SOCFPGA /* FPGA doesn't support standby */
    (void) Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
    Log_printf(LogModule_RCL, Log_INFO, "RCL_Hal_powerSetStandbyConstraint: Power constraints set");
#endif
}

void RCL_Hal_powerReleaseStandbyConstraint(void)
{
    /* Note: The power driver requires that setting and releasing constraints come in pairs */

#ifndef SOCFPGA /* FPGA doesn't support standby */
    (void) Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    Log_printf(LogModule_RCL, Log_INFO, "RCL_Hal_powerReleaseStandbyConstraint: Power constraints released");
#endif
}

void RCL_Hal_powerSetSwTcxoUpdateConstraint(void)
{
    /* Note: The power driver requires that setting and releasing constraints come in pairs */
#ifndef SOCFPGA /* FPGA doesn't support standby */
    (void) Power_setConstraint(PowerLPF3_DISALLOW_SWTCXO);
#endif
}

void RCL_Hal_powerReleaseSwTcxoUpdateConstraint(void)
{
    /* Note: The power driver requires that setting and releasing constraints come in pairs */
#ifndef SOCFPGA /* FPGA doesn't support standby */
    (void) Power_releaseConstraint(PowerLPF3_DISALLOW_SWTCXO);
    /* If all constraints are now released, perform any update that may have happened while SWTCXO was disallowed */
    if (Power_getConstraintCount(PowerLPF3_DISALLOW_SWTCXO) == 0)
    {
        PowerLPF3_forceHFXTCompensationUpdate();
    }
#endif
}

void RCL_Hal_powerOpen(void (*rclPowerNotifyFunction)(RCL_PowerEvent))
{
#ifndef SOCFPGA
   /* Register power notification functions */
    (void) Power_registerNotify(&powerEnterStandbyObj, PowerLPF3_ENTERING_STANDBY, RCL_Hal_powerPostNotifyFxn, (uintptr_t)rclPowerNotifyFunction);
    (void) Power_registerNotify(&powerAwakeStandbyObj, PowerLPF3_AWAKE_STANDBY, RCL_Hal_powerPostNotifyFxn, (uintptr_t)rclPowerNotifyFunction);
#endif
}

void RCL_Hal_powerClose(void)
{
#ifndef SOCFPGA
    /* Unregister power notification objects */
    Power_unregisterNotify(&powerEnterStandbyObj);
    Power_unregisterNotify(&powerAwakeStandbyObj);
#endif
}

void RCL_Hal_temperatureInit(void)
{
    Temperature_init();
}

/* Make function weak to allow tests to override reported temperature */
__attribute__((weak)) int16_t RCL_Hal_getTemperature(void)
{
    return Temperature_getTemperature();
}

/* Make function weak to allow tests to override reported VDDS voltage */
__attribute__((weak)) uint16_t RCL_Hal_getVddsVoltage(void)
{
    return BatteryMonitor_getVoltage();
}

uint32_t RCL_Hal_getHfxtRatio(void)
{
    return (uint32_t) (HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) & CKMD_HFTRACKCTL_RATIO_M) >> CKMD_HFTRACKCTL_RATIO_S;
}

uint32_t RCL_Hal_getHfxtRatioDefault(void)
{
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    return 0x00200000U;
#else
    return RCL_DEFAULT_HFTRACKCTL_RATIO;
#endif
}

static void RCL_Hal_temperaturePostNotifyFxn(int16_t currentTemperature,
                                            int16_t thresholdTemperature,
                                            uintptr_t clientArg,
                                            Temperature_NotifyObj *notifyObject)
{
    (void) thresholdTemperature;
    (void) notifyObject;
    void (*rclTemperatureNotify)(int16_t) = (void (*)(int16_t)) clientArg;

    if (rclTemperatureNotify != NULL)
    {
        rclTemperatureNotify(currentTemperature);
    }
}

void RCL_Hal_setTemperatureNotification(int16_t currentTemperature, uint16_t temperatureRange, void (*rclTemperatureNotify)(int16_t))
{
    /* Register the notification again with updated thresholds. Notification thresholds must be crossed to
     * trigger, so the upper and lower limits are decreased by 1 to maintain a range of +/- delta.
     */
    (void) Temperature_registerNotifyRange(&temperatureChangeNotifyObj,
                                            currentTemperature + (int16_t)temperatureRange - 1,
                                            currentTemperature - (int16_t)temperatureRange + 1,
                                            RCL_Hal_temperaturePostNotifyFxn,
                                            (uintptr_t) rclTemperatureNotify);
}

void RCL_Hal_stopTemperatureNotification(void)
{
    (void) Temperature_unregisterNotify(&temperatureChangeNotifyObj);
}
