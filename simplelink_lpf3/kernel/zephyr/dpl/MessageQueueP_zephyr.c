/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#include <assert.h>
#include <zephyr/sys/__assert.h>

#include <inc/hw_types.h>
#include <inc/hw_ints.h>

#include <driverlib/interrupt.h>

#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/MessageQueueP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>

#ifdef CONFIG_DYNAMIC_DPL_OBJECTS
/* We can't easily dynamically allocate kernel objects */
#define DPL_MAX_MSGQS 4
K_MEM_SLAB_DEFINE(msgq_slab, sizeof(struct k_msgq) , DPL_MAX_MSGQS, MEM_ALIGN);

static struct k_msgq *dpl_msgq_pool_alloc()
{
	struct k_msgq  *msgq_ptr = NULL;

	if (k_mem_slab_alloc(&msgq_slab, (void **)&msgq_ptr, K_NO_WAIT) < 0) {

		 __ASSERT(0, "Increase size of DPL message queue pool");
	}
	return msgq_ptr;
}

static void dpl_msgq_pool_free(struct k_msgq *msgq)
{

	k_mem_slab_free(&msgq_slab, (void *)msgq);

	return;
}

/*
 *  ======== MessageQueueP_create ========
 */
MessageQueueP_Handle MessageQueueP_create(size_t msgSize, size_t msgCount)
{
    struct k_msgq *msgq = dpl_msgq_pool_alloc();
    int status = k_msgq_alloc_init(msgq, msgSize, msgCount);
    if(status != 0)
    {
        return NULL;
    }
    return (MessageQueueP_Handle) msgq;
}

/*
 *  ======== MessageQueueP_delete ========
 */
void MessageQueueP_delete(MessageQueueP_Handle handle)
{
    if (handle != NULL)
    {
        struct k_msgq* msgq;
        msgq = (struct k_msgq* )handle;
        k_msgq_purge(msgq);
        k_msgq_cleanup(msgq);
        dpl_msgq_pool_free(msgq);
    }
}
#endif  /* CONFIG_DYNAMIC_DPL_OBJECTS */

/*
 *  ======== MessageQueueP_construct ========
 */
MessageQueueP_Handle MessageQueueP_construct(MessageQueueP_Struct *msgStruct,
                                             size_t msgSize,
                                             size_t msgCount,
                                             void *msgBuf)
{
    struct k_msgq* msgq;
    msgq = (struct k_msgq* )msgStruct;
    if (msgq) {
        k_msgq_init(msgq, msgBuf, msgSize, msgCount);
    }

    return (MessageQueueP_Handle)msgq;
}

/*
 *  ======== MessageQueueP_destruct ========
 */
void MessageQueueP_destruct(MessageQueueP_Handle handle)
{
    k_msgq_purge((struct k_msgq* )handle);
}

/*
 *  ======== MessageQueueP_pend ========
 */
MessageQueueP_Status MessageQueueP_pend(MessageQueueP_Handle handle, void *message, uint32_t timeout)
{
    uint32_t tickPeriod;
    k_timeout_t msgTimeout;

    /* Timeout must be K_NO_WAIT if in an ISR */
    if ((timeout == MessageQueueP_NO_WAIT) || k_is_in_isr())
    {
        msgTimeout = K_NO_WAIT;
    }
    else if (timeout == MessageQueueP_WAIT_FOREVER)
    {
        msgTimeout = K_FOREVER;
    }
    else
    {
        /* If necessary, convert ClockP ticks to Zephyr ticks */
        /* Should really be ClockP_getSystemTickPeriod() but this causes issues with ielftool post build step */
        tickPeriod = CLOCKP_TICK_PERIOD;
        msgTimeout = K_TICKS(timeout);
    }
    int status = k_msgq_get((struct k_msgq*) handle, message, msgTimeout);
    if(status == 0)
    {
        return MessageQueueP_OK;
    }
    return MessageQueueP_TIMEOUT;
}

/*
 *  ======== MessageQueueP_peek ========
 */
MessageQueueP_Status MessageQueueP_peek(MessageQueueP_Handle handle, void *message, uint32_t timeout)
{
    assert(timeout == MessageQueueP_NO_WAIT);
    /* Zephyr peek does not support timeouts*/
    uint32_t status = k_msgq_peek((struct k_msgq*) handle, message);

    if(status == 0)
    {
        return MessageQueueP_OK;
    }
    return MessageQueueP_TIMEOUT;
}

/*
 *  ======== MessageQueueP_post ========
 */
MessageQueueP_Status MessageQueueP_post(MessageQueueP_Handle handle, const void *message, uint32_t timeout)
{
    uint32_t tickPeriod;
    k_timeout_t msgTimeout;
    uint64_t timeUS;

    if (timeout == MessageQueueP_NO_WAIT)
    {
        msgTimeout = K_NO_WAIT;
    }
    else if (timeout == MessageQueueP_WAIT_FOREVER)
    {
        msgTimeout = K_FOREVER;
    }
    else
    {
        /* if necessary, convert ClockP ticks to Zephyr ticks */
        /* Should really be ClockP_getSystemTickPeriod() but this causes issues with ielftool post build step */
        tickPeriod = CLOCKP_TICK_PERIOD;
        if (tickPeriod != CONFIG_SYS_CLOCK_TICKS_PER_SEC)
        {
            timeUS  = timeout * (uint64_t)tickPeriod;
            msgTimeout = K_USEC(timeUS);
        }
        else
        {
            msgTimeout = K_TICKS(timeout);
        }
    }

    int status = k_msgq_put((struct k_msgq*) handle, message, msgTimeout);

    if(status == 0)
    {
        return MessageQueueP_OK;
    }
    return MessageQueueP_TIMEOUT;
}

/*
 *  ======== MessageQueueP_postFront ========
 */
MessageQueueP_Status MessageQueueP_postFront(MessageQueueP_Handle handle, const void *message, uint32_t timeout)
{
    return MessageQueueP_post(handle, message, timeout);
}

/*
 *  ======== MessageQueueP_getPendingCount ========
 */
size_t MessageQueueP_getPendingCount(MessageQueueP_Handle handle)
{
    size_t msgCount = k_msgq_num_used_get((struct k_msgq*) handle);
    return msgCount;
}

/*
 *  ======== MessageQueueP_getFreeCount ========
 */
size_t MessageQueueP_getFreeCount(MessageQueueP_Handle handle)
{
    size_t freeMsgCount = k_msgq_num_free_get((struct k_msgq*) handle);

    return freeMsgCount;
}

/*
 *  ======== MessageQueueP_getMessageQueueObjectSize ========
 */
uint32_t MessageQueueP_getMessageQueueObjectSize(void)
{
    return sizeof(struct k_msgq);
}
