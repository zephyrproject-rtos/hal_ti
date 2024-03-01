/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>

#include <zephyr/sys/__assert.h>

#include <inc/hw_types.h>
#include <inc/hw_ints.h>

#include <driverlib/interrupt.h>

#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/EventP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>

#ifdef CONFIG_DYNAMIC_DPL_OBJECTS
/* We can't easily dynamically allocate kernel objects */
#define DPL_MAX_EVENTS 5
K_MEM_SLAB_DEFINE(event_slab, sizeof(struct k_event), DPL_MAX_EVENTS,\
          MEM_ALIGN);


static struct k_event *dpl_event_pool_alloc()
{
    struct k_event *event_ptr = NULL;

    if (k_mem_slab_alloc(&event_slab, (void **)&event_ptr, K_NO_WAIT) < 0) {

         __ASSERT(0, "Increase size of DPL event pool");
    }
    return event_ptr;
}

static void dpl_event_pool_free(struct k_event *event)
{
    k_mem_slab_free(&event_slab, (void *)event);

    return;
}

/*
 *  ======== EventP_create ========
 */
EventP_Handle EventP_create(void)
{
    struct k_event *event = dpl_event_pool_alloc();
    k_event_init(event);
    return (EventP_Handle) event;
}

/*
 *  ======== EventP_delete ========
 */
void EventP_delete(EventP_Handle handle)
{
    if (handle != NULL)
    {
        dpl_event_pool_free((struct k_event *) handle);
    }
}

#endif /* CONFIG_DYNAMIC_DPL_OBJECTS */

/*
 *  ======== EventP_construct ========
 */
EventP_Handle EventP_construct(EventP_Struct *obj)
{
    struct k_event *event;
    event = (struct k_event*)obj;

    if (event) {
        k_event_init(event);
    }

    return (EventP_Handle)event;
}

/*
 *  ======== EventP_destruct ========
 */
void EventP_destruct(EventP_Struct *obj)
{
    struct k_event *event;

    event = (struct k_event *)obj->data;

    k_event_clear(event, 0xFFFFFFFF);
}

/*
 *  ======== EventP_pend ========
 */
uint32_t EventP_pend(EventP_Handle event, uint32_t eventMask, bool waitForAll, uint32_t timeout)
{
    uint32_t eventBits, tickPeriod;
    k_timeout_t eventTimeout;
    uint64_t timeUS;


    if (timeout == EventP_WAIT_FOREVER)
    {
        eventTimeout = K_FOREVER;
    }
    else if (timeout == EventP_NO_WAIT)
    {
        eventTimeout = K_NO_WAIT;
    }
    else
    {
        /* if necessary, convert ClockP ticks to Zephyr ticks */
        /* Should really be ClockP_getSystemTickPeriod() but this causes issues with ielftool post build step */
        tickPeriod = ClockP_TICK_PERIOD;
        eventTimeout = K_TICKS(timeout);
    }

    if(waitForAll)
    {
       /* Wait for all event bits */
       eventBits = k_event_wait_all((struct k_event *) event, eventMask, false, eventTimeout);
    }
    else
    {
        /* Wait for any event bits */
        eventBits = k_event_wait((struct k_event *) event, eventMask, false, eventTimeout);
    }

    /* Clear the events that caused the return */
    k_event_clear((struct k_event *) event, eventBits);

    /* Check if wait returned because of timeout */
    if (((eventBits == 0)) || ((eventBits != eventMask) && (waitForAll == true)))
    {
        return 0;
    }
    else
    {
        return eventBits;
    }
}

/*
 *  ======== EventP_post ========
 */
void EventP_post(EventP_Handle event, uint32_t eventMask)
{
    /* Unpend all tasks waiting for these events, and merge these events with
       the ones already tracked by the object
    */
    k_event_set((struct k_event *) event, eventMask);
}

/*
 *  ======== EventP_clear ========
 */
void EventP_clear(EventP_Handle event, uint32_t eventMask)
{
    k_event_clear((struct k_event *) event, eventMask);
}

/*
 *  ======== EventP_get ========
 */
uint32_t EventP_get(EventP_Handle event)
{
    uint32_t events = ((struct k_event *)event)->events;
    return events;
}