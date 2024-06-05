/*
 * Copyright (c) 2021-2024, Texas Instruments Incorporated
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
 *  ======== hal_cc23x0rx.c ========
 */

#include <ti/drivers/Power.h>

#include <ti/drivers/Temperature.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_clkctl.h)
#include DeviceFamily_constructPath(inc/hw_ckmd.h)

#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)

#include DeviceFamily_constructPath(driverlib/lrfd.h)

#include <ti/log/Log.h>

#include <ti/drivers/rcl/hal/hal.h>

#ifndef SOCFPGA
/* FPGA doesn't support Standby */
static int hal_power_post_notify_fxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg);
Power_NotifyObj powerAwakeStandbyObj;
Power_NotifyObj powerEnterStandbyObj;

static void (*rclPowerNotify)(RCL_PowerEvent) = NULL;
#endif
static void hal_cancel_lrfd_systim0(void);

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

uint32_t hal_get_command_ifg_reg(void)
{
    uint32_t dbellIrq;
    /* Using masked interrupt */
    dbellIrq = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_MIS0);
    /* Remove SYSTIM 0 and 1 interrupts, as they should be handled by hal_check_clear_timer_compare() */
    dbellIrq &= ~(LRFDDBELL_MIS0_SYSTIM0_M | LRFDDBELL_MIS0_SYSTIM1_M);
    /* Clear interrupts (unmasked only) */
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = dbellIrq;

    return dbellIrq;
}

uint32_t hal_get_dispatch_ifg_reg(void)
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
void hal_init_fsm(void (*dispatchFsmCb)(void), void (*schedFsmCb)(void),
                  void (*commandFsmCb)(void))
{
    HwiP_Params hp;
    HwiP_Params_init(&hp);
#ifdef DeviceFamily_CC27XX
    hp.priority = INT_PRI_LEVEL4;
#else
    hp.priority = INT_PRI_LEVEL2;
#endif
    HwiP_construct(&schedHwi, INT_CPUIRQ4, RF_schedHwi, &hp);
#ifdef DeviceFamily_CC27XX
    hp.priority = INT_PRI_LEVEL2;
#else
    hp.priority = INT_PRI_LEVEL1;
#endif
    HwiP_construct(&dispatchHwi, INT_LRFD_IRQ1, RF_dispatchHwi,  &hp);
#ifdef DeviceFamily_CC27XX
    hp.priority = INT_PRI_LEVEL1;
#else
    hp.priority = INT_PRI_LEVEL0;
#endif
    HwiP_construct(&commandHwi, INT_LRFD_IRQ0, RF_commandHwi,  &hp);

    halDispatchFsmCb = dispatchFsmCb;
    halSchedFsmCb = schedFsmCb;
    halCommandFsmCb = commandFsmCb;
    /* TODO: See RCL-345 */

    HWREG(EVTSVT_BASE + EVTSVT_O_CPUIRQ4SEL) = 0xE; /* LRFDIRQ2 */
}


void hal_trigger_command_fsm(void)
{
    /* Software trig command FSM */
    HwiP_post(INT_LRFD_IRQ0);
}

void hal_trigger_dispatch_fsm(void)
{
    /* Software trig dispatch IRQ */
    HwiP_post(INT_LRFD_IRQ1);
}

void hal_trigger_scheduler_fsm(void)
{
    /* Software schedule IRQ */
    HwiP_post(INT_CPUIRQ4);
}

uint32_t hal_get_current_time(void)
{
    return HWREG(SYSTIM_BASE + SYSTIM_O_TIME250N);
}

enum {
    SYSTIM_CH2_SETUP = 1, /* Early start, to kick off setup */
    SYSTIM_CH2_START = 2, /* Start event to radio */
    SYSTIM_CH2_STOP = 3,  /* Hard stop time */
} channel2usage = SYSTIM_CH2_SETUP;

void hal_enable_setup_time_irq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void hal_setup_setup_time(uint32_t time)
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

void hal_setup_start_time(uint32_t time)
{
    channel2usage = SYSTIM_CH2_START;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = time;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void hal_setup_hard_stop_time(uint32_t time)
{
    channel2usage = SYSTIM_CH2_STOP;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM0_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH2CC) = time;
    /* Interrupt is not always needed, as event will be handled by PBE */
}

void hal_enable_hard_stop_time_irq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM0_M;
}

void hal_disable_hard_stop_time_irq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~LRFDDBELL_IMASK0_SYSTIM0_M;
}

void hal_setup_graceful_stop_time(uint32_t time)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM1_M;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CC) = time;
    /* Interrupt is not always needed, as event will be handled by PBE */
}

void hal_enable_graceful_stop_time_irq(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | LRFDDBELL_IMASK0_SYSTIM1_M;
}

static void hal_cancel_lrfd_systim0(void)
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

void hal_cancel_setup_time(void)
{
    hal_cancel_lrfd_systim0();
}

void hal_cancel_start_time(void)
{
    hal_cancel_lrfd_systim0();
}

void hal_cancel_hard_stop_time(void)
{
    hal_cancel_lrfd_systim0();
}

void hal_cancel_graceful_stop_time(void)
{
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CC) = 0;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CFG) = SYSTIM_CH3CFG_MODE_CAPT;
    HWREG(SYSTIM_BASE + SYSTIM_O_CH3CFG) = SYSTIM_CH3CFG_MODE_DIS;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =  HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~LRFDDBELL_IMASK0_SYSTIM1_M;
}

void hal_enable_clk_buffer(void)
{
#ifndef SOCFPGA
    /* FPGA doesn't support standby */
    HWREG( CKMD_BASE + CKMD_O_HFXTCTL ) |= CKMD_HFXTCTL_HPBUFEN;
#endif
}

void hal_setup_sync_found_cap(void)
{
    /* SRAT sync found repeat capture config */
    /* Route event_ibus(21) (mdm) to DBELL input (capt_sources[0]) */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SYSTIMEVTMUX0) = (21 << LRFDMDM_SYSTIMEVTMUX0_SEL0_S);
    /* Route through DBELL */
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_SYSTIMOEV) = (LRFDDBELL_SYSTIMOEV_SRC2_MCESYSTIM0);
    /* SYSTIM channel 4 uses srat_ievent(0) as repeated capture trigger */
    HWREG(SYSTIM_BASE + SYSTIM_O_CH4CFG) |= SYSTIM_CH4CFG_INP_RISE | SYSTIM_CH4CFG_MODE_CAPT | SYSTIM_CH4CFG_REARM_EN;
}

HalTimerEvent hal_check_clear_timer_compare(void)
{
    HalTimerEvent event = HAL_TIMER_EVT_NONE;

    uint32_t mis0 = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_MIS0);

    /* Start or hard-stop takes priority, meaning hard-stop takes priority over graceful. */
    if (mis0 & LRFDDBELL_MIS0_SYSTIM0_M)
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
    else if (mis0 & LRFDDBELL_MIS0_SYSTIM1_M)
    {
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & (~LRFDDBELL_IMASK0_SYSTIM1_M);
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = LRFDDBELL_ICLR0_SYSTIM1_M;
        event = HAL_TIMER_EVT_GRACEFUL_STOP;
    }
    return event;
}

void hal_init_dispatch_radio_interrupts(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR1) = ~0;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK1) = mask;
}

void hal_enable_command_radio_interrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
        HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) | mask;
}

void hal_clear_command_radio_interrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = mask;
}

void hal_disable_command_radio_interrupt(uint32_t mask)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
            HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) & ~mask;
}

void hal_disable_all_command_radio_interrupts(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) = 0;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = ~0;
}

void hal_disable_all_dispatch_radio_interrupts(void)
{
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK1) = 0;
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR1) = ~0;
}

void hal_set_rcl_clock_enable(uint16_t mask)
{
    uintptr_t key = HwiP_disable();
    LRFDSetClockDependency(mask, LRFD_CLK_DEP_RCL);
    HwiP_restore(key);
}

void hal_clear_rcl_clock_enable(uint16_t mask)
{
    uintptr_t key = HwiP_disable();
    LRFDReleaseClockDependency(mask, LRFD_CLK_DEP_RCL);
    HwiP_restore(key);
}

#ifndef SOCFPGA
static int hal_power_post_notify_fxn(unsigned int eventType, uintptr_t eventArg, uintptr_t clientArg)
{
    (void) eventArg;
    (void) clientArg;

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
    }
    return (Power_NOTIFYDONE);
}
#endif

void hal_power_set_constraint(void)
{
#ifndef SOCFPGA
    /* FPGA doesn't support standby */
    Power_setConstraint(PowerLPF3_DISALLOW_STANDBY);
    Log_printf(RclCore, Log_INFO, "Power constraints set");
#endif
}

void hal_power_release_constraint(void)
{
#ifndef SOCFPGA
    /* FPGA doesn't support standby */
    Power_releaseConstraint(PowerLPF3_DISALLOW_STANDBY);
    Log_printf(RclCore, Log_INFO, "Power constraints released");
#endif
}

void hal_power_open(void (*f)(RCL_PowerEvent))
{
#ifndef SOCFPGA
    rclPowerNotify = f;

   /* Register power notification functions */
    Power_registerNotify(&powerEnterStandbyObj, PowerLPF3_ENTERING_STANDBY, hal_power_post_notify_fxn, (uintptr_t)NULL);
    Power_registerNotify(&powerAwakeStandbyObj, PowerLPF3_AWAKE_STANDBY, hal_power_post_notify_fxn, (uintptr_t)NULL);
#endif
}

void hal_power_close(void)
{
#ifndef SOCFPGA
    /* Unregister power notification objects */
    Power_unregisterNotify(&powerEnterStandbyObj);
    Power_unregisterNotify(&powerAwakeStandbyObj);
#endif
}

void hal_temperature_init(void)
{
    Temperature_init();
}

/* Make function weak to allow tests to override reported temperature */
__attribute__((weak)) int16_t hal_get_temperature(void)
{
    return Temperature_getTemperature();
}

uint32_t hal_get_hfxt_ratio(void)
{
    return (HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) & CKMD_HFTRACKCTL_RATIO_M) >> CKMD_HFTRACKCTL_RATIO_S;
}

uint32_t hal_get_hfxt_ratio_default(void)
{
#ifdef DeviceFamily_CC27XX
    return 0x00200000U;
#else
    return RCL_DEFAULT_HFTRACKCTL_RATIO;
#endif
}
