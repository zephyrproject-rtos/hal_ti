/*
 * Copyright (c) 2026, Texas Instruments Incorporated
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
 *  ======== ClockPLPF3_zephyr.c ========
 */

#include <stdlib.h>
#include <stdint.h>

#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/utils/List.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/clock.h>

/* Driverlib includes */
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)
#include DeviceFamily_constructPath(inc/hw_rtc.h)
#include DeviceFamily_constructPath(driverlib/evtsvt.h)
#include DeviceFamily_constructPath(driverlib/interrupt.h)
#include DeviceFamily_constructPath(driverlib/systimer.h)

/* Defines */

/* ClockP tick period, in microseconds */
#define ClockP_TICK_PERIOD (USEC_PER_SEC / CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC)


/** Max number of ClockP ticks into the future supported by this ClockP
 * implementation.
 *
 * Under the hood, ClockP uses the SysTimer whose events trigger immediately if
 * the compare value is less than 2^22 systimer ticks in the past
 * (4.194sec at 1us resolution). Therefore, the max number of SysTimer ticks you
 * can schedule into the future is 2^32 - 2^22 - 1 ticks (~= 4290 sec at 1us
 * resolution).
 */
#define ClockP_PERIOD_MAX (SYSTIMER_MAX_DELTA / ClockP_TICK_PERIOD)

/** Max number of seconds into the future supported by this ClockP
 * implementation.
 *
 * This limit affects ClockP_sleep()
 */
#define ClockP_PERIOD_MAX_SEC (SYSTIMER_MAX_DELTA / 1000000)

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #define ClockP_EVTSVT_SUB_CPUIRQ (EVTSVT_SUB_CPUIRQ16)
    #define ClockP_INT_CPUIRQ        (INT_CPUIRQ16)
    #define ClockP_SYSTIM_CHANNEL    (0)
    #define ClockP_EVTSVT_PUB_SYSTIM (EVTSVT_PUB_SYSTIM0)
#else
    #error "Invalid Device Family defined"
#endif
/* Processing overhead.
 *
 * Empirically deduced processing overhead to ensure
 * ClockP_usleep() to be more accurate.
 */
#define ClockP_PROC_OVERHEAD_US 99U

/* Bit mask for the non-overlapping bits between RTC.TIME524M and SYSTIM.TIME1U */
#define RTC_TI_CC27XX_TOP_19_BITS_MASK  0xFFFFE000

/* Spinlock used while gathering 64-bit system ticks */
static struct k_spinlock lock;

typedef struct ClockP_Obj
{
    List_Elem elem;                ///< Clock's List element. Must be first in struct
    uint32_t timeout;              ///< Timeout value (used for one-shot)
    volatile uint32_t currTimeout; ///< Next timeout value in number of tick periods
    volatile uint32_t period;      ///< Period of periodic clock. 0 for one-shot.
    volatile bool active;          ///< Clock is active
    volatile ClockP_Fxn fxn;       ///< Callback function
    volatile uintptr_t arg;        ///< Argument passed to callback function
} ClockP_Obj;

/* Shared variables */
/* ClockP and Power policy share interrupt ClockP_INT_CPUIRQ, and therefore Hwi object. */
HwiP_Struct clockHwi;

/* Local variables */
/* The names of these variables are used by ROV */
static bool ClockP_initialized = false;

/* The existence of a variable with this name is the signal to ROV
 * that it is used on an LPF3 device
 */
static List_List ClockP_list;
static volatile uint32_t ClockP_ticks;
static uint32_t ClockP_nextScheduledTick;
static bool ClockP_inWorkFunc;
static bool ClockP_startOrStopDuringWorkFunc;
static ClockP_Params ClockP_defaultParams = {
    .startFlag = false,
    .period    = 0,
    .arg       = 0,
};

/* Function declarations */
static void ClockP_workFuncDynamic(uintptr_t arg);
static void ClockP_hwiCallback(uintptr_t arg0);
static void sleepTicks(uint32_t ticks);
static void sleepClkFxn(uintptr_t arg0);
static void ClockP_scheduleNextTick(uint32_t absTick);

/*
 *  ======== ClockP_Params_init ========
 */
void ClockP_Params_init(ClockP_Params *params)
{
    /* structure copy */
    *params = ClockP_defaultParams;
}

/*
 *  ======== ClockP_startup ========
 */
void ClockP_startup(void)
{
    if (!ClockP_initialized)
    {
        uint32_t nowTick;
        intptr_t key;

        /* Get current value as early as possible */
        nowTick = ClockP_getSystemTicks();

        /* Clear any pending interrupts on the ClockP SysTimer channel */
        SysTimerClearInterrupt(ClockP_SYSTIM_CHANNEL);

        /* Configure the ClockP SysTimer channel to compare mode with timer
         * resolution of 1 us. Note, idle mode must be used here, and the
         * channel will switch to compare mode when a compare value is written
         * to it.
         */
        SysTimerSetChannelConfig(ClockP_SYSTIM_CHANNEL, SYSTIMER_CONFIG_MODE_IDLE | SYSTIMER_CONFIG_RESOLUTION_1US);

        /* Make SysTimer halt on CPU debug halt */
        SysTimerSetDebugConfig(SYSTIMER_DEBUG_CONFIG_HALT_STOP);

        /* Construct clockHwi object.
         */
        HwiP_construct(&clockHwi, ClockP_INT_CPUIRQ, ClockP_hwiCallback, NULL);

        /* Mux the SysTimer event for SysTimer channel ClockP_SYSTIM_CHANNEL to
         * interrupt line ClockP_INT_CPUIRQ.
         */
        EVTSVTConfigureEvent(ClockP_EVTSVT_SUB_CPUIRQ, ClockP_EVTSVT_PUB_SYSTIM);

        /* Set IMASK for channel ClockP_SYSTIM_CHANNEL. IMASK is used by the
         * power driver to know which systimer channels are active.
         */
        SysTimerEnableInterrupt(ClockP_SYSTIM_CHANNEL);

        /* Initialize ClockP variables */
        List_clearList(&ClockP_list);
        ClockP_ticks                     = nowTick;
        ClockP_nextScheduledTick         = (uint32_t)(nowTick + ClockP_PERIOD_MAX);
        ClockP_inWorkFunc                = false;
        ClockP_startOrStopDuringWorkFunc = false;

        ClockP_initialized = true;

        /* Start the clock */
        key = HwiP_disable();
        ClockP_scheduleNextTick(ClockP_nextScheduledTick);
        HwiP_restore(key);
    }
}

/*
 *  ======== ClockP_getTicksUntilInterrupt  ========
 */
uint32_t ClockP_getTicksUntilInterrupt(void)
{
    uint32_t ticks;

    ticks = ClockP_nextScheduledTick - ClockP_getSystemTicks();

    /* Clamp value to zero if nextScheduledTick is less than current */
    if (ticks > ClockP_PERIOD_MAX)
    {
        ticks = 0;
    }

    return (ticks);
}

/*
 *  ======== ClockP_scheduleNextTick  ========
 *  Must be called with global interrupts disabled!
 */
void ClockP_scheduleNextTick(uint32_t absTick)
{
    /* Reprogram the timer for the new period and next interrupt */
    uint32_t newSystim = (uint32_t)(absTick * ClockP_TICK_PERIOD);

    /* At this point, we no longer care about the previously set compare value,
     * but we might end up getting an event and a pending interrupt from the old
     * compare value because it could now be in the past. To prevent the CPU
     * from vectoring to the ISR for the wrong compare value, we need to do the
     * following:
     *  1. Prevent event from being generated for the old compare value, by
     *     un-arming the channel.
     *  2. Clear any event that might have been set before un-arming the
     *     channel, by reading the channel compare value.
     *  3. Clear any pending interrupt that might have been set by the
     *     potential event cleared in step 2.
     *
     * After this, a new compare value can be written. This will re-arm the
     * channel as well. Any event/interrupt generated after this is guaranteed
     * to be for the new compare value.
     */

    /* Un-arm the ClockP SysTimer channel. The channel is no longer in compare
     * mode after this.
     */
    SysTimerDisarmChannel(ClockP_SYSTIM_CHANNEL);

    /* Read the capture/compare value. This will clear the event, if set, since
     * the channel is not in compare mode.
     */
    HWREG(SYSTIM_BASE + SYSTIM_O_CH0CC + (ClockP_SYSTIM_CHANNEL * sizeof(uint32_t)));

    /* Clear pending interrupt. */
    HwiP_clearInterrupt(ClockP_INT_CPUIRQ);

    /* Write new compare value. This will also re-arm the channel, and put the
     * channel in compare mode.
     */
    SysTimerSetCompareValue(ClockP_SYSTIM_CHANNEL, newSystim);

    /* Remember this */
    ClockP_nextScheduledTick = absTick;
}

/*
 *  ======== ClockP_walkQueueDynamic ========
 *  Walk the Clock Queue for TickMode_DYNAMIC, optionally servicing a
 *  specific tick
 *
 *  Returns the number of ticks from thisTick to the next timeout.
 *  If no future timeouts exists, ~0 is returned.
 */
uint32_t ClockP_walkQueueDynamic(bool service, uint32_t thisTick)
{
    uint32_t distance = ~0;
    List_List *list   = &ClockP_list;
    List_Elem *elem;
    ClockP_Obj *obj;
    uint32_t delta;
    uint32_t period;
    uintptr_t arg;

    /* Traverse clock queue */
    for (elem = List_head(list); elem != NULL; elem = List_next(elem))
    {

        obj = (ClockP_Obj *)elem;

        /* If the object is active ... */
        if (obj->active == true)
        {

            /* Optionally service if tick matches timeout */
            if (service == true)
            {

                /* If this object is timing out update its state */
                if (obj->currTimeout == thisTick)
                {
                    /* Read volatile members to prevent undefined order of
                     * volatile accesses warnings.
                     */
                    period = obj->period;
                    arg    = obj->arg;

                    if (period == 0)
                    {
                        /* Oneshot: Mark object idle */
                        obj->active = false;
                    }
                    else
                    {
                        /* Periodic: Refresh timeout */
                        obj->currTimeout += period;
                    }

                    /* Call handler */
                    obj->fxn(arg);
                }
            }

            /* If object is still active, update distance to soonest timeout */
            if (obj->active == true)
            {

                delta = obj->currTimeout - thisTick;

                /* If this is the soonest timeout, update distance to soonest */
                if (delta < distance)
                {
                    distance = delta;
                }
            }
        }
    }

    return (distance);
}

/*
 *  ======== ClockP_workFuncDynamic ========
 *  Service Clock Queue for TickMode_DYNAMIC
 */
void ClockP_workFuncDynamic(uintptr_t arg)
{
    uintptr_t hwiKey;

    /* The tick count at the entry of this function. This is our definition of
     * "now".
     */
    uint32_t nowTick;

    /* The tick count for the current timeout to service */
    uint32_t timeoutTick;

    /* The number of ticks between the current timeout to service and the next
     * timeout.
     */
    uint32_t distance;

    /* The number of ticks since the current timeout to service relative to now.
     * (nowTick)
     */
    uint32_t ticksSinceTimeout;

    /* The next tick to schedule at the end of this function */
    uint32_t nextTick;

    hwiKey = HwiP_disable();

    /* Get current tick count. */
    nowTick = ClockP_getSystemTicks();

    /* Set flags while actively servicing queue */
    ClockP_inWorkFunc                = true;
    ClockP_startOrStopDuringWorkFunc = false;

    /* Determine the first expired timeout to service.
     * This function will be called by ClockP_hwiCallback after the "next
     * scheduled tick" has expired. The "next scheduled tick" will therefore be
     * now or in the past (until it is updated at the end of this function).
     * The "next scheduled tick" will either be the value of a timeout or it
     * will be a dummy tick that was scheduled ClockP_PERIOD_MAX ticks into the
     * future. In both scenarios the "next scheduled tick" will be treated as a
     * timeout. If it was a dummy tick, it will just result in no timeouts being
     * serviced for that specific tick.
     */
    timeoutTick       = ClockP_nextScheduledTick;
    /* Number of ticks since the timeout to service */
    ticksSinceTimeout = nowTick - timeoutTick;

    HwiP_restore(hwiKey);

    /* In the first iteration of below loop, the distance is set to 0, to ensure
     * that the first expired timeout will be serviced.
     */
    distance = 0;

    /* Walk queue until the next timeout is in the future. */
    while (ticksSinceTimeout >= distance)
    {
        /* Determine the next timeout to service */
        timeoutTick += distance;
        /* Number of ticks since the timeout */
        ticksSinceTimeout -= distance;
        /* Walk queue and service timeout(s) and return the distance to the next
         * timeout.
         */
        distance = ClockP_walkQueueDynamic(true, timeoutTick);
    }

    hwiKey = HwiP_disable();

    /* If ClockP_start() or ClockP_stop() was called during processing of queue,
     * re-walk to update distance.
     */
    if (ClockP_startOrStopDuringWorkFunc == true)
    {
        distance = ClockP_walkQueueDynamic(false, timeoutTick);
    }

    /* Cap the distance to the maximum distance supported by the timer */
    if (distance > ClockP_PERIOD_MAX)
    {
        distance = ClockP_PERIOD_MAX;
    }

    /* Next tick is the latest timeout that was serviced plus the distance to
     * the next timeout.
     */
    nextTick = timeoutTick + distance;

    /* Reprogram for next expected tick */
    ClockP_scheduleNextTick(nextTick);

    ClockP_inWorkFunc = false;
    ClockP_ticks      = timeoutTick;

    HwiP_restore(hwiKey);
}

/*
 *  ======== ClockP_hwiCallback ========
 */
void ClockP_hwiCallback(uintptr_t arg)
{
    /* ClockP is using dedicated SysTimer channel event. Clearing the flag
     * for the combined interrupt is strictly not necessary, but doing it here
     * to avoid confusion for anyone using the SysTimer combined event.
     */
    SysTimerClearInterrupt(ClockP_SYSTIM_CHANNEL);

    /* Run worker function */
    ClockP_workFuncDynamic(arg);
}

/*
 *  ======== ClockP_construct ========
 */
ClockP_Handle ClockP_construct(ClockP_Struct *handle, ClockP_Fxn fxn, uint32_t timeout, ClockP_Params *params)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    if (handle == NULL)
    {
        return NULL;
    }

    if (params == NULL)
    {
        params = &ClockP_defaultParams;
    }

    obj->period  = params->period;
    obj->timeout = timeout;
    obj->fxn     = fxn;
    obj->arg     = params->arg;
    obj->active  = false;

    ClockP_startup();

    /* Clock object is always placed on the ClockP work queue */
    List_put(&ClockP_list, &obj->elem);

    if (params->startFlag)
    {
        ClockP_start(obj);
    }

    return ((ClockP_Handle)handle);
}

/*
 *  ======== ClockP_create ========
 */
ClockP_Handle ClockP_create(ClockP_Fxn clkFxn, uint32_t timeout, ClockP_Params *params)
{
    ClockP_Handle handle;

    handle = (ClockP_Handle)malloc(sizeof(ClockP_Obj));

    /* ClockP_construct will check handle for NULL, no need here */
    handle = ClockP_construct((ClockP_Struct *)handle, clkFxn, timeout, params);

    return (handle);
}

/*
 *  ======== ClockP_destruct ========
 */
void ClockP_destruct(ClockP_Struct *clk)
{
    ClockP_Obj *obj = (ClockP_Obj *)clk;

    List_remove(&ClockP_list, &obj->elem);
}

/*
 *  ======== ClockP_add ========
 */
void ClockP_add(ClockP_Struct *handle, ClockP_Fxn fxn, uint32_t timeout, uintptr_t arg)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    obj->period  = 0;
    obj->timeout = timeout;
    obj->fxn     = fxn;
    obj->arg     = arg;
    obj->active  = false;

    /* Clock object is always placed on Clock work Q */
    List_put(&ClockP_list, &obj->elem);
}

/*
 *  ======== ClockP_delete ========
 */
void ClockP_delete(ClockP_Handle handle)
{
    ClockP_destruct((ClockP_Struct *)handle);

    free(handle);
}

/*
 *  ======== ClockP_start ========
 *  Set the Clock object's currTimeout value and set its active flag
 *  to true.
 */
void ClockP_start(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    uintptr_t key   = HwiP_disable();

    uint32_t nowTick;
    uint32_t nowDelta;
    uint32_t scheduledTick;
    uint32_t scheduledDelta;
    uint32_t remainingTicks;
    bool objectServiced = false;

    /* if Clock is NOT currently processing its Q */
    if (ClockP_inWorkFunc == false)
    {

        /* get current tick count */
        nowTick = ClockP_getSystemTicks();

        nowDelta       = nowTick - ClockP_ticks;
        scheduledTick  = ClockP_nextScheduledTick;
        scheduledDelta = scheduledTick - ClockP_ticks;

        /* Check if this new timeout is before next scheduled tick ... */
        if (nowDelta <= scheduledDelta)
        {
            objectServiced = true;

            /* Start new Clock object */
            obj->currTimeout = nowTick + obj->timeout;
            obj->active      = true;

            /* How many ticks until scheduled tick? */
            remainingTicks = scheduledTick - nowTick;

            if (obj->timeout < remainingTicks)
            {
                ClockP_scheduleNextTick(obj->currTimeout);
            }
        }
    }

    if (objectServiced == false)
    {
        /* Get current tick count */
        nowTick = ClockP_getSystemTicks();

        /* Start new Clock object */
        obj->currTimeout = nowTick + obj->timeout;
        obj->active      = true;

        if (ClockP_inWorkFunc == true)
        {
            ClockP_startOrStopDuringWorkFunc = true;
        }
    }

    HwiP_restore(key);
}

/*
 *  ======== ClockP_stop ========
 *  Remove and clear Clock object's queue elem from clockQ
 */
void ClockP_stop(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    uintptr_t key   = HwiP_disable();

    uint32_t nowTick;
    uint32_t nowDelta;
    uint32_t scheduledTick;
    uint32_t scheduledDelta;
    uint32_t newScheduledTickDelta;

    obj->active = false;

    if (ClockP_inWorkFunc)
    {
        /* If in the work function, let it handle scheduling the next tick */
        ClockP_startOrStopDuringWorkFunc = true;
    }
    else
    {
        /* Re-compute next scheduled tick, if the current one is the timeout of
         * the stopped clock.
         */
        if (obj->currTimeout == ClockP_nextScheduledTick)
        {
            /* Get current tick count */
            nowTick = ClockP_getSystemTicks();

            nowDelta       = nowTick - ClockP_ticks;
            scheduledTick  = ClockP_nextScheduledTick;
            scheduledDelta = scheduledTick - ClockP_ticks;

            /* Check if "now" is before the next scheduled tick.
             * If "now" is after the next scheduled tick (i.e. the next
             * scheduled tick is in the past), then there will be a pending
             * interrupt, and the rescheduling will be done in
             * ClockP_workFuncDynamic(), instead of below.
             */
            if (nowDelta < scheduledDelta)
            {
                /* Determine distance to next tick */
                newScheduledTickDelta = ClockP_walkQueueDynamic(false, nowTick);

                /* Cap the distance to the maximum distance supported by the timer */
                if (newScheduledTickDelta > ClockP_PERIOD_MAX)
                {
                    newScheduledTickDelta = ClockP_PERIOD_MAX;
                }

                /* Schedule the next tick */
                ClockP_scheduleNextTick(nowTick + newScheduledTickDelta);

                ClockP_ticks = nowTick;
            }
        }
    }

    HwiP_restore(key);
}

/*
 *  ======== ClockP_setFunc ========
 */
void ClockP_setFunc(ClockP_Handle handle, ClockP_Fxn clockFxn, uintptr_t arg)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    uintptr_t key = HwiP_disable();

    obj->fxn = clockFxn;
    obj->arg = arg;

    HwiP_restore(key);
}

/*
 *  ======== ClockP_setTimeout ========
 */
void ClockP_setTimeout(ClockP_Handle handle, uint32_t timeout)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    obj->timeout = timeout;
}

/*
 *  ======== ClockP_setPeriod ========
 */
void ClockP_setPeriod(ClockP_Handle handle, uint32_t period)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    obj->period = period;
}

/*
 *  ======== ClockP_getTimeout ========
 */
uint32_t ClockP_getTimeout(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    uint32_t currentTime;

    if (obj->active == true)
    {
        currentTime = ClockP_getSystemTicks();
        return (obj->currTimeout - currentTime);
    }
    else
    {
        return (obj->timeout);
    }
}

/*
 *  ======== ClockP_isActive ========
 */
bool ClockP_isActive(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    return (obj->active);
}

/*
 *  ======== ClockP_getCpuFreq ========
 */
void ClockP_getCpuFreq(ClockP_FreqHz *freq)
{
    freq->lo = CONFIG_CPU_FREQUENCY;
    freq->hi = 0;
}

/*
 *  ======== ClockP_getSystemTickPeriod ========
 */
uint32_t ClockP_getSystemTickPeriod(void)
{
    return ClockP_TICK_PERIOD;
}

/*
 *  ======== ClockP_getSystemTicks ========
 */
uint32_t ClockP_getSystemTicks(void)
{
    /* SysTimer is always running.
     * This function needs to convert the SysTimer ticks into ClockP ticks.
     * The ClockP tick period is ClockP_TICK_PERIOD us * CLOCK_FREQUENCY_DIVIDER.
     * The SysTimer tick period is 1 us * CLOCK_FREQUENCY_DIVIDER when using
     * the SysTimerGetTime1Us() API.
     * So the ratio between the SysTimer tick period and the ClockP tick period
     * is (1 us * CLOCK_FREQUENCY_DIVIDER) / (ClockP_TICK_PERIOD us * CLOCK_FREQUENCY_DIVIDER)
     * The two CLOCK_FREQUENCY_DIVIDER cancel out, leaving us with the ratio of
     * (1 / ClockP_TICK_PERIOD). This ratio must be multiplied with the SysTimer
     * tick count to get the ClockP tick count. This it implemented by just
     * dividing the SysTimer tick count by ClockP_TICK_PERIOD, which is
     * equivalent to multiplying it with (1 / ClockP_TICK_PERIOD).
     */
    return (SysTimerGetTime1Us() / ClockP_TICK_PERIOD);
}

/*
 *  ======== ClockP_getSystemTicks64 ========
 */
uint64_t ClockP_getSystemTicks64(void)
{
    /*
	 * NOTE: This function does not implement true 64-bit cycle count, only 51 bit.
	 * However, since it would take 71.4 years for the 51 bits to overflow, it
	 * is deemed acceptable.
	 */

	k_spinlock_key_t key = k_spin_lock(&lock);

	uint64_t low;
	uint64_t high;

	/*
	 * We combine both RTC and SYSTIM to get 51 bit cycle count.
	 * RTC is a 67-bit timer, of which we can read the first 51 bits. The SYSTIM is a
	 * 34 bit-timer. The RTC and SYSTIM are synchronized through hardware, however the RTC
	 * is only updated every ~30us, which is too rare for it to be used for Zephyr's system
	 * clock. What this means is that reading RTC.TIME1U to get a resolution of 1 us could be
	 * up to 30 us behind the actual cycle count. Therefore we use SYSTIM.TIME1U for these
	 * least significant bits that are updated more often than 30 us,
	 * since SYSTIM is updated immediately on count.
	 * We use RTC.TIME524M to get the most significant bits.
	 */

	high = HWREG(RTC_BASE + RTC_O_TIME524M) / ClockP_TICK_PERIOD;
	low  = SysTimerGetTime1Us() / ClockP_TICK_PERIOD;

	/*
	 * The 13 most significant bits of TIME1U and the 13 least significant bits of TIME524M
	 * "overlaps". There is a possibility that the 13 bits in low are incremented, and we
	 * call this function before the RTC is updated. Normally, if the overlapping bits in
	 * TIME1U are numerically higher than those in TIME524U, no action is needed. However, if
	 * the increment of TIME1U makes the counter overflow, this needs to be accounted for.
	 * We check the overlapping bits, if those in "low" are numerically higher than those in
	 * "high", no action is needed. If they are numerically lower, then this means TIME1U has
	 * overflowed and the RTC is not yet updated. We do not want to wait for the RTC to
	 * update, so we manually increment the high part by add 1 to the first non-overlapping
	 * bit (bit 13). We can never have the opposite, where those in "high" are numerically
	 * higher than those in "low", since the RTC is always updated to the current value of
	 * the more frequently updated SYSTIM timer.
	 */
	if ((high & 0x1FFF) > (low  >> 19)) {

		high += 1<<13;

	}
	/*
	 * We mask out TIME524M[12:0] bits since they overlap, and shift the first
	 * valid bit (bit 13) to position 32 in the resulting 64 bit cycle count. We do this
	 * by left shifting the masked valued 32-13 = 19 positions.
	 */

	high = (high & RTC_TI_CC27XX_TOP_19_BITS_MASK) << 19;

	k_spin_unlock(&lock, key);

	return high | low;
}

/*
 *  ======== ClockP_sleep ========
 */
void ClockP_sleep(uint32_t sec)
{
    uint32_t ticksToSleep;

    if (sec > ClockP_PERIOD_MAX_SEC)
    {
        sec = ClockP_PERIOD_MAX_SEC;
    }
    /* Convert from seconds to number of ticks */
    ticksToSleep = (sec * USEC_PER_SEC) / ClockP_getSystemTickPeriod();
    sleepTicks(ticksToSleep);
}

/*
 *  ======== ClockP_usleep ========
 */
void ClockP_usleep(uint32_t usec)
{
    uint32_t currTick;
    uint32_t endTick;
    uint32_t ticksToSleep;

    /* Systimer is always running, get tick as soon as possible */
    currTick = ClockP_getSystemTicks();

    /* Make sure we sleep at least one tick if usec > 0 */
    endTick = currTick + ((usec + ClockP_TICK_PERIOD - 1) / (ClockP_getSystemTickPeriod()));

    /* If usec large enough, sleep for the appropriate number of clock ticks. */
    if (usec > ClockP_PROC_OVERHEAD_US)
    {
        ClockP_startup();
        ticksToSleep = (usec - ClockP_PROC_OVERHEAD_US) / ClockP_getSystemTickPeriod();
        sleepTicks(ticksToSleep);
    }

    /* Spin remaining time */
    do
    {
        currTick = ClockP_getSystemTicks();
    } while (currTick < endTick);
}

/*
 *  ======== ClockP_staticObjectSize ========
 *  Internal function for testing that ClockP_Struct is large enough
 *  to hold ClockP object.
 */
size_t ClockP_staticObjectSize(void)
{
    return (sizeof(ClockP_Obj));
}

/*
 *  ======== sleepTicks ========
 *  Sleep for a given number of ClockP ticks.
 */
static void sleepTicks(uint32_t ticks)
{
    /* Cap to max number of ticks supported */
    if (ticks > ClockP_PERIOD_MAX)
    {
        ticks = ClockP_PERIOD_MAX;
    }

    SemaphoreP_Struct semStruct;
    ClockP_Struct clkStruct;
    ClockP_Params clkParams;
    SemaphoreP_Handle sem;

    /* Construct a semaphore, and a clock object to post the semaphore */
    sem = SemaphoreP_construct(&semStruct, 0, NULL);
    ClockP_Params_init(&clkParams);
    clkParams.startFlag = true;
    clkParams.arg       = (uintptr_t)sem;
    ClockP_construct(&clkStruct, sleepClkFxn, ticks, &clkParams);

    /* Pend forever on the semaphore, wait for ClockP callback to post it */
    SemaphoreP_pend(sem, SemaphoreP_WAIT_FOREVER);

    /* Clean up */
    SemaphoreP_destruct(&semStruct);
    ClockP_destruct(&clkStruct);
}

/*
 *  ======== sleepClkFxn ========
 *  Timeout function for sleepTicks().
 */
static void sleepClkFxn(uintptr_t arg0)
{
    SemaphoreP_post((SemaphoreP_Handle)arg0);
}
