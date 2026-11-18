/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/kernel_structs.h>
#include <zephyr/sys/bitarray.h>

#include <zephyr/sys/__assert.h>

#include <inc/hw_types.h>
#include <inc/hw_ints.h>

#include <driverlib/interrupt.h>

#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/TaskP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/HwiP.h>

#ifdef TaskP_STRUCT_SIZE
#undef TaskP_STRUCT_SIZE
#endif
#define TaskP_STRUCT_SIZE (160)

#ifdef TaskP_DEFAULT_STACK_SIZE
#undef TaskP_DEFAULT_STACK_SIZE
#endif
#define TaskP_DEFAULT_STACK_SIZE (CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_STACK_SIZE)

#if (defined(CONFIG_DYNAMIC_DPL_OBJECTS) && defined(CONFIG_THREAD_STACK_INFO))
    #define DYNAMIC_THREADS
#endif

#ifdef DYNAMIC_THREADS
/* Space for thread objects */
K_MEM_SLAB_DEFINE(task_slab, sizeof(struct k_thread), CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE,\
          MEM_ALIGN);

/* Private stack pool for TaskP threads, independent of Zephyr's generic
 * dynamic thread pool (CONFIG_DYNAMIC_THREAD_STACK_SIZE / CONFIG_DYNAMIC_THREAD_POOL_SIZE).
 */
K_THREAD_STACK_ARRAY_DEFINE(dpl_task_stacks, CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE,
                             CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_STACK_SIZE);

SYS_BITARRAY_DEFINE_STATIC(dpl_stack_bitmap, CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE);

static struct k_thread *dpl_task_pool_alloc(void)
{
    struct k_thread *task_ptr = NULL;

    if (k_mem_slab_alloc(&task_slab, (void **)&task_ptr, K_NO_WAIT) < 0) {
        __ASSERT(0, "Increase CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE");
    }
    return task_ptr;
}

static void dpl_task_pool_free(struct k_thread *task)
{
    k_mem_slab_free(&task_slab, (void *)task);
}

static k_thread_stack_t *dpl_stack_alloc(void)
{
    size_t idx;

    if (sys_bitarray_alloc(&dpl_stack_bitmap, 1, &idx) < 0) {
        __ASSERT(0, "Increase CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE");
        return NULL;
    }
    return dpl_task_stacks[idx];
}

static void dpl_stack_free(k_thread_stack_t *stack)
{
    for (size_t i = 0; i < CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_POOL_SIZE; i++) {
        if (dpl_task_stacks[i] == stack) {
            sys_bitarray_free(&dpl_stack_bitmap, 1, i);
            return;
        }
    }
    __ASSERT(0, "Stack not in DPL pool");
}

#endif /* DYNAMIC_THREADS */

/*
 *  ======== Array for conversion of Zephyr thread state to DPL task state ========
 */
const TaskP_State taskState[] = {TaskP_State_RUNNING,  /*!< Running */
                                 TaskP_State_READY,    /*!< Ready */
                                 TaskP_State_BLOCKED,  /*!< Suspended */
                                 TaskP_State_INACTIVE, /*!< Suspended */
                                 TaskP_State_DELETED,  /*!< Terminated */
                                 TaskP_State_INVALID}; /*!< Dummy */

/*
 *  ======== Default TaskP_Params values ========
 */
static const TaskP_Params TaskP_defaultParams = {
    .name      = "NAME",
    .arg       = NULL,
    .priority  = 0,
    .stackSize = CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_STACK_SIZE,
    .stack     = NULL,
};

/*
 *  ======== TaskP_Params_init ========
 */
void TaskP_Params_init(TaskP_Params *params)
{
    /* structure copy */
    *params = TaskP_defaultParams;
}

#ifdef DYNAMIC_THREADS
/*
 *  ======== TaskP_create ========
 */
TaskP_Handle TaskP_create(TaskP_Function fxn, const TaskP_Params *params)
{
    k_tid_t task_tid;
    struct k_thread *task = dpl_task_pool_alloc();

    __ASSERT(params->stackSize <= CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_STACK_SIZE,
             "Increase CONFIG_SOC_FAMILY_TI_SIMPLELINK_DPL_TASK_STACK_SIZE");

    k_thread_stack_t *task_stack = dpl_stack_alloc();

    if (task_stack != NULL)
    {
        /* TaskP uses inversed priority to Zephyr */
        task_tid = k_thread_create(task, task_stack,
                            params->stackSize,
                            (k_thread_entry_t) fxn,
                            params->arg, NULL, NULL,
                            (0 - params->priority), 0, K_NO_WAIT);
        if (task_tid != NULL)
        {
            k_thread_name_set(task_tid, params->name);
            return ((TaskP_Handle)task);
        }
    }
    return NULL;
}

/*
 *  ======== TaskP_delete ========
 */
void TaskP_delete(TaskP_Handle task)
{
    if (task != NULL)
    {
        TaskP_State state = TaskP_getState(task);
        if(state != TaskP_State_INVALID && state != TaskP_State_DELETED)
        {
            struct k_thread *thread = (struct k_thread *)task;
            k_thread_abort((k_tid_t) thread);

            dpl_stack_free((k_thread_stack_t *) thread->stack_info.start);
            dpl_task_pool_free(thread);
        }
    }
}
#endif /* DYNAMIC_THREADS */
/*
 *  ======== TaskP_construct ========
 */
TaskP_Handle TaskP_construct(TaskP_Struct *obj, TaskP_Function fxn, const TaskP_Params *params)
{
    if (params == NULL)
    {
        /* Set default parameter values */
        params = &TaskP_defaultParams;
    }

    /* TaskP uses inversed priority to Zephyr */
    k_tid_t task_tid = k_thread_create((struct k_thread*) obj, (k_thread_stack_t*) params->stack,
                                 params->stackSize,
                                 (k_thread_entry_t) fxn,
                                 params->arg, NULL, NULL,
                                 (0 - params->priority), 0, K_NO_WAIT);

    if(task_tid != NULL)
    {
        k_thread_name_set(task_tid, params->name);
        return ((TaskP_Handle) obj);
    }
    return NULL;
}

/*
 *  ======== TaskP_destruct ========
 */
void TaskP_destruct(TaskP_Struct *obj)
{
    if (obj != NULL)
    {
        TaskP_State state = TaskP_getState((TaskP_Handle) obj);
        if(state != TaskP_State_INVALID && state != TaskP_State_DELETED)
        {
            struct k_thread*  thread = (struct k_thread* )obj;
            k_thread_abort((k_tid_t) thread);
        }
    }
}

/*
 *  ======== TaskP_getState ========
 */
TaskP_State TaskP_getState(TaskP_Handle task)
{
    TaskP_State state;

    switch (((struct k_thread*) task)->base.thread_state) {
    case _THREAD_DUMMY:
        state = TaskP_State_INVALID;
        break;
    case _THREAD_DEAD:
        state = TaskP_State_DELETED;
        break;
    case _THREAD_SUSPENDED:
    case _THREAD_PENDING:
        state = TaskP_State_BLOCKED;
        break;
    case _THREAD_QUEUED:
        state = TaskP_State_READY;
        break;
    default:
        state = TaskP_State_INVALID;
        break;
    }

    /* Check if we are the currently running thread */
    if (k_current_get() == ((k_tid_t) ((struct k_thread *) task))) {
        state = TaskP_State_RUNNING;
    }

    return state;
}

/*
 *  ======== TaskP_getCurrentTask ========
 */
TaskP_Handle TaskP_getCurrentTask(void)
{
    return ((TaskP_Handle)k_current_get());
}

/*
 *  ======== TaskP_disableScheduler ========
 */
uintptr_t TaskP_disableScheduler(void)
{
    k_sched_lock();
    return (0);
}

/*
 *  ======== TaskP_restoreScheduler ========
 */
void TaskP_restoreScheduler(uintptr_t key)
{
    k_sched_unlock();
}

/*
 *  ======== TaskP_yield ========
 */
void TaskP_yield(void)
{
    k_yield();
}

/*
 *  ======== TaskP_getTaskObjectSize ========
 */
uint32_t TaskP_getTaskObjectSize(void)
{
    return (sizeof(struct k_thread));
}

void TaskP_setTaskResourcePool(struct k_heap *heap)
{
    k_thread_heap_assign(k_current_get(), heap);
}
