/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/__assert.h>
#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/ClockP.h>

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
} ClockP_Obj;

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

	obj->clock_fxn = clockFxn;
	obj->arg = params->arg;
	obj->period = params->period * ClockP_getSystemTickPeriod() / 1000;
	obj->timeout = timeout;
	
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
uint32_t ClockP_getSystemTickPeriod()
{
	return (1000000 / CONFIG_SYS_CLOCK_TICKS_PER_SEC);
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

	__ASSERT_NO_MSG(obj->timeout > (UINT32_MAX / 1000));

	k_timer_start(&obj->timer, obj->timeout * 1000 /
		CONFIG_SYS_CLOCK_TICKS_PER_SEC, obj->period);
}

/*
 *  ======== ClockP_stop ========
 */
void ClockP_stop(ClockP_Handle handle)
{
	ClockP_Obj *obj = (ClockP_Obj *)handle;

	k_timer_stop(&obj->timer);
}

void ClockP_usleep(uint32_t usec)
{
	k_sleep((s32_t)usec);
}
