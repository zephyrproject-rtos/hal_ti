/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <ti/drivers/dpl/ClockP.h>

#define CLOCKP_TICK_PERIOD (USEC_PER_SEC / CONFIG_SYS_CLOCK_TICKS_PER_SEC);

/* 
 * ClockP_STRUCT_SIZE in ClockP.h must be updated to match the size of this
 * struct
 */
typedef struct _ClockP_Obj {
	struct k_timer timer;
	ClockP_Fxn clock_fxn;
	uintptr_t arg;
	uint32_t timeout; /* in sys clock uptime ticks */
	uint32_t period; /* in sys clock uptime ticks */
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
 *  @param timeout in sys clock uptime ticks
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
	obj->period = params->period;
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
 *  ======== ClockP_getSystemTickFreq ========
 */
inline uint32_t ClockP_getSystemTickFreq()
{
   return CONFIG_SYS_CLOCK_TICKS_PER_SEC;
}

/*
 *  ======== ClockP_getSystemTickPeriod ========
 *
 *  This implementation rounds the system tick period down by ~17250ppm
 *  which makes it useless for any precision timing. Use
 *  (timeUs * ClockP_getSystemTickFreq() for these purposes instead.
 */
inline uint32_t ClockP_getSystemTickPeriod()
{
   return CLOCKP_TICK_PERIOD;
}

uint32_t ClockP_getSystemTicks()
{
	/* may wrap */
	return k_uptime_ticks();
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
 *  @param timeout in sys clock uptime ticks
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

	k_timer_start(&obj->timer, K_TICKS(obj->timeout), K_TICKS(obj->period));
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
    return obj->active ? k_timer_remaining_ticks(&obj->timer) : obj->timeout;
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
