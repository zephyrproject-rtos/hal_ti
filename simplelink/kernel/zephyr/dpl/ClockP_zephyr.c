/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/__assert.h>
#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/ClockP.h>

#include "stubs.h"

/* 
 * ClockP_STRUCT_SIZE in ClockP.h must be updated to match the size of this
 * struct
 */
typedef struct _ClockP_Obj {
	struct k_timer timer;
	ClockP_Fxn clock_fxn;
	uintptr_t arg;
	uint32_t timeout;
	uint32_t period;
	bool active;
} ClockP_Obj;

static ClockP_Params ClockP_defaultParams = {
    .startFlag = false,
    .period = 0,
    .arg = 0,
};

static void expiry_fxn(struct k_timer *timer_id)
{
	ClockP_Obj *obj = (ClockP_Obj *)k_timer_user_data_get(timer_id);
	
	obj->clock_fxn(obj->arg);
}

/*
 *  ======== ClockP_construct ========
 */
ClockP_Handle ClockP_construct(ClockP_Struct *handle, ClockP_Fxn clockFxn,
        uint32_t timeout, ClockP_Params *params)
{
	ClockP_Obj *obj = (ClockP_Obj *)handle;

	if (handle == NULL) {
		return NULL;
	}

	if (params == NULL) {
		params = &ClockP_defaultParams;
	}

	obj->clock_fxn = clockFxn;
	obj->arg = params->arg;
	obj->period = params->period * ClockP_getSystemTickPeriod() / 1000;
	obj->timeout = timeout;
	obj->active = false;
	
	k_timer_init(&obj->timer, expiry_fxn, NULL);
	k_timer_user_data_set(&obj->timer, obj);
	
	if (params->startFlag) {
		ClockP_start(obj);
	}
	
	return  ((ClockP_Handle)handle);
}

/*
 *  ======== ClockP_getSystemTickPeriod ========
 */
uint32_t ClockP_tickPeriod = (1000000 / CONFIG_SYS_CLOCK_TICKS_PER_SEC);
uint32_t ClockP_getSystemTickPeriod()
{
   return ClockP_tickPeriod;
}

uint32_t ClockP_getSystemTicks()
{
	return (uint32_t)z_ms_to_ticks(k_uptime_get_32());
}

/*
 *  ======== ClockP_Params_init ========
 */
void ClockP_Params_init(ClockP_Params *params)
{
	params->arg = 0;
	params->startFlag = false;
	params->period = 0;
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

	__ASSERT_NO_MSG(obj->timeout /
		CONFIG_SYS_CLOCK_TICKS_PER_SEC <= UINT32_MAX / 1000);
	__ASSERT_NO_MSG(obj->period /
		CONFIG_SYS_CLOCK_TICKS_PER_SEC <= UINT32_MAX / 1000);

	/* Avoid overflow */
	if (obj->timeout > UINT32_MAX / 1000) {
		timeout = obj->timeout / CONFIG_SYS_CLOCK_TICKS_PER_SEC * 1000;
	} else if ((obj->timeout != 0) &&
		(obj->timeout < CONFIG_SYS_CLOCK_TICKS_PER_SEC / 1000)) {
		/* For small timeouts we use 1 msec */
		timeout = 1;		
	} else {
		timeout = obj->timeout * 1000 / CONFIG_SYS_CLOCK_TICKS_PER_SEC;
	}

	if (obj->period > UINT32_MAX / 1000) {
		period = obj->period / CONFIG_SYS_CLOCK_TICKS_PER_SEC * 1000;
	} else if ((obj->period != 0) &&
		(obj->period < CONFIG_SYS_CLOCK_TICKS_PER_SEC / 1000)) {
		period = 1;		
	} else {
		period = obj->period * 1000 / CONFIG_SYS_CLOCK_TICKS_PER_SEC;
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
 *  ======== ClockP_usleep ========
 */
void ClockP_usleep(uint32_t usec)
{
	k_sleep(K_USEC(usec));
}

/*
 *  ======== ClockP_getTimeout ========
 */
uint32_t ClockP_getTimeout(ClockP_Handle handle) {
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    return k_timer_remaining_get(&obj->timer) * CONFIG_SYS_CLOCK_TICKS_PER_SEC / 1000;
}

/*
 *  ======== ClockP_isActive ========
 */
bool ClockP_isActive(ClockP_Handle handle) {
    ClockP_Obj *obj = (ClockP_Obj *)handle;
    return obj->active;
}

void ClockP_destruct(ClockP_Struct *clockP)
{
	ClockP_Obj *obj = (ClockP_Obj *)clockP->data;

	obj->clock_fxn = NULL;
	obj->arg = 0;
	obj->period = 0;
	obj->timeout = 0;
	obj->active = false;

	k_timer_stop(&obj->timer);
}
