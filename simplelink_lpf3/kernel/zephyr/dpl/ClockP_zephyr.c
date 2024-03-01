/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>

/* Driverlib includes*/
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)

/** Max number of ClockP ticks into the future supported by this ClockP
 * implementation.
 *
 * Under the hood, ClockP uses the SysTimer whose events trigger immediately if
 * the compare value is less than 2^22 systimer ticks in the past
 * (4.194sec at 1us resolution). Therefore, the max number of SysTimer ticks you
 * can schedule into the future is 2^32 - 2^22 - 1 ticks (~= 4290 sec at 1us
 * resolution). */
#define ClockP_PERIOD_MAX     (0xFFBFFFFFU / ClockP_TICK_PERIOD)
/** Max number of seconds into the future supported by this ClockP
 * implementation.
 *
 * This limit affects ClockP_sleep() */
#define ClockP_PERIOD_MAX_SEC 4290U

/* Get the current ClockP tick value */
#define getClockPTick() (HWREG(SYSTIM_BASE + SYSTIM_O_TIME1U) / ClockP_TICK_PERIOD)

/*
 * ClockP_STRUCT_SIZE in ClockP.h must be updated to match the size of this
 * struct
 */
typedef struct _ClockP_Obj
{
    struct k_timer timer;
    ClockP_Fxn clock_fxn;
    uintptr_t arg;
    uint32_t timeout;
    uint32_t period;
    bool active;
} ClockP_Obj;

static ClockP_Params ClockP_defaultParams = {
    .startFlag = false,
    .period    = 0,
    .arg       = 0,
};

static void expiry_fxn(struct k_timer *timer_id)
{
    ClockP_Obj *obj = (ClockP_Obj *)k_timer_user_data_get(timer_id);

    obj->clock_fxn(obj->arg);
}

#ifdef CONFIG_DYNAMIC_DPL_OBJECTS

/* We can't easily dynamically allocate kernel objects so we use memory slabs */
#define DPL_MAX_CLOCKS 5
K_MEM_SLAB_DEFINE(clock_slab, sizeof(ClockP_Obj), DPL_MAX_CLOCKS,\
          MEM_ALIGN);

static ClockP_Obj *dpl_clock_pool_alloc()
{
    ClockP_Obj  *clock_ptr = NULL;

    if (k_mem_slab_alloc(&clock_slab, (void **)&clock_ptr, K_NO_WAIT) < 0) {

         __ASSERT(0, "Increase size of DPL clock pool");
    }
    return clock_ptr;
}

static void dpl_clock_pool_free(ClockP_Obj *clock)
{
    k_mem_slab_free(&clock_slab, (void *)&clock);

    return;
}

/*
 *  ======== ClockP_create ========
 */
ClockP_Handle ClockP_create(ClockP_Fxn clkFxn, uint32_t timeout, ClockP_Params *params)
{
    ClockP_Handle handle;

    handle = (ClockP_Handle)dpl_clock_pool_alloc();

    /* ClockP_construct will check handle for NULL, no need here */
    handle = ClockP_construct((ClockP_Struct *)handle, clkFxn, timeout, params);

    return (handle);
}

/*
 *  ======== ClockP_delete ========
 */
void ClockP_delete(ClockP_Handle handle)
{
    ClockP_destruct((ClockP_Struct *)handle);

    dpl_clock_pool_free((ClockP_Obj*) handle);
}

#endif /* CONFIG_DYNAMIC_DPL_OBJECTS */

/*
 *  ======== ClockP_construct ========
 */
ClockP_Handle ClockP_construct(ClockP_Struct *handle, ClockP_Fxn clockFxn, uint32_t timeout, ClockP_Params *params)
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

    obj->clock_fxn = clockFxn;
    obj->arg       = params->arg;
    obj->period    = params->period * ClockP_getSystemTickPeriod() / USEC_PER_MSEC;
    obj->timeout   = timeout;
    obj->active    = false;

    k_timer_init(&obj->timer, expiry_fxn, NULL);
    k_timer_user_data_set(&obj->timer, obj);

    if (params->startFlag)
    {
        ClockP_start(obj);
    }

    return ((ClockP_Handle)handle);
}

/*
 *  ======== ClockP_getSystemTickPeriod ========
 */
uint32_t ClockP_tickPeriod = (USEC_PER_SEC / CONFIG_SYS_CLOCK_TICKS_PER_SEC);
uint32_t ClockP_getSystemTickPeriod()
{
    return ClockP_tickPeriod;
}

uint32_t ClockP_getSystemTicks()
{
    return (uint32_t)k_ms_to_ticks_ceil32(k_uptime_get_32());
}

/*
 *  ======== ClockP_Params_init ========
 */
void ClockP_Params_init(ClockP_Params *params)
{
    params->arg       = 0;
    params->startFlag = false;
    params->period    = 0;
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
 *  ======== ClockP_start ========
 */
void ClockP_start(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    int32_t timeout;
    int32_t period;

    __ASSERT_NO_MSG(obj->timeout / CONFIG_SYS_CLOCK_TICKS_PER_SEC <= UINT32_MAX / USEC_PER_MSEC);
    __ASSERT_NO_MSG(obj->period / CONFIG_SYS_CLOCK_TICKS_PER_SEC <= UINT32_MAX / USEC_PER_MSEC);

    /* Avoid overflow */
    if (obj->timeout > UINT32_MAX / USEC_PER_MSEC)
    {
        timeout = obj->timeout / CONFIG_SYS_CLOCK_TICKS_PER_SEC * USEC_PER_MSEC;
    }
    else if ((obj->timeout != 0) && (obj->timeout < CONFIG_SYS_CLOCK_TICKS_PER_SEC / USEC_PER_MSEC))
    {
        /* For small timeouts we use 1 msec */
        timeout = 1;
    }
    else
    {
        timeout = obj->timeout * USEC_PER_MSEC / CONFIG_SYS_CLOCK_TICKS_PER_SEC;
    }

    if (obj->period > UINT32_MAX / USEC_PER_MSEC)
    {
        period = obj->period / CONFIG_SYS_CLOCK_TICKS_PER_SEC * USEC_PER_MSEC;
    }
    else if ((obj->period != 0) && (obj->period < CONFIG_SYS_CLOCK_TICKS_PER_SEC / USEC_PER_MSEC))
    {
        period = 1;
    }
    else
    {
        period = obj->period * USEC_PER_MSEC / CONFIG_SYS_CLOCK_TICKS_PER_SEC;
    }

    k_timer_start(&obj->timer, K_MSEC(timeout), K_MSEC(period));

    obj->active = true;
}

/*
 *  ======== ClockP_stop ========
 */
void ClockP_stop(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    k_timer_stop(&obj->timer);
    obj->active = false;
}

/*
 *  ======== ClockP_setFunc ========
 */
void ClockP_setFunc(ClockP_Handle handle, ClockP_Fxn clockFxn, uintptr_t arg)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;

    uintptr_t key = HwiP_disable();

    obj->clock_fxn = clockFxn;
    obj->arg = arg;

    HwiP_restore(key);
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
    ticksToSleep = (sec * USEC_PER_SEC) / ClockP_TICK_PERIOD;
    k_sleep(K_TICKS(ticksToSleep));
}

/*
 *  ======== ClockP_usleep ========
 */
void ClockP_usleep(uint32_t usec)
{
    k_sleep(K_USEC(usec));
}

/*
 *  ======== ClockP_getTimeout ========
 */
uint32_t ClockP_getTimeout(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    return k_timer_remaining_get(&obj->timer) * CONFIG_SYS_CLOCK_TICKS_PER_SEC / USEC_PER_MSEC;
}

/*
 *  ======== ClockP_isActive ========
 */
bool ClockP_isActive(ClockP_Handle handle)
{
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    return obj->active;
}

/*
 *  ======== ClockP_getCpuFreq ========
 */
void ClockP_getCpuFreq(ClockP_FreqHz *freq)
{
    freq->lo = (uint32_t)CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC;
    freq->hi = 0;
}

void ClockP_destruct(ClockP_Struct *clockP)
{
    ClockP_Obj *obj = (ClockP_Obj *)clockP->data;

    obj->clock_fxn = NULL;
    obj->arg       = 0;
    obj->period    = 0;
    obj->timeout   = 0;
    obj->active    = false;

    k_timer_stop(&obj->timer);
}
