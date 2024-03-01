/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>
#include <ti/drivers/dpl/HwiP.h>

#include <inc/hw_types.h>
#include <inc/hw_ints.h>

#include <driverlib/interrupt.h>

/*
 * IRQ_CONNECT requires we know the ISR signature and argument
 * at build time; whereas SimpleLink plugs the interrupts
 * at run time, so we create an ISR shim, and register that.
 * The callback argument doesn't change after the ISR is registered.
 */
struct sl_isr_args
{
    HwiP_Fxn cb;
    uintptr_t arg;
};

static void sl_isr(const void *isr_arg)
{
    HwiP_Fxn cb   = ((struct sl_isr_args *)isr_arg)->cb;
    uintptr_t arg = ((struct sl_isr_args *)isr_arg)->arg;

    /* Call the SimpleLink ISR Handler: */
    if (cb)
    {
        cb(arg);
    }
}

typedef struct _HwiP_Obj
{
    uint32_t intNum;
    struct sl_isr_args *cb;
} HwiP_Obj;

/* interrupt reserved for SwiP */
int HwiP_swiPIntNum = INT_CPUIRQ1;

static struct sl_isr_args sl_IRQ01_cb = {NULL, 0};
static struct sl_isr_args sl_IRQ03_cb = {NULL, 0};
static struct sl_isr_args s1_IRQ04_cb = {NULL, 0};
static struct sl_isr_args sl_IRQ16_cb = {NULL, 0};
static struct sl_isr_args s1_LRFD_IRQ0_cb = {NULL, 0};
static struct sl_isr_args s1_LRFD_IRQ1_cb = {NULL, 0};

/*
 *  ======== HwiP_construct ========
 */
HwiP_Handle HwiP_construct(HwiP_Struct *handle, int interruptNum, HwiP_Fxn hwiFxn, HwiP_Params *params)
{
    HwiP_Obj *obj    = (HwiP_Obj *)handle;
    uintptr_t arg    = 0;
    uint8_t priority = INT_PRI_LEVEL3; /* default to lowest priority */

    if (handle == NULL)
    {
        return NULL;
    }

    if (params)
    {
        priority = params->priority & 0xFF;
        arg      = params->arg;
    }

    /*
     * Currently only support INT_CPUIRQ1 (SwiP), INT_CPUIRQ3 (Oscillator ISR),
     * INT_CPUIRQ16 (Batmon ISR), INT_CPUIRQ4 (RCL Scheduler ISR), INT_LRFD_IRQ0
     * (RCL Command Handler ISR) and INT_LRFD_IRQ1 (RCL Dispatcher ISR)
     */
    __ASSERT((INT_CPUIRQ1 == interruptNum) || (INT_CPUIRQ3 == interruptNum) || (INT_CPUIRQ4 == interruptNum) ||
                 (INT_CPUIRQ16 == interruptNum) || (INT_LRFD_IRQ0 == interruptNum) || (INT_LRFD_IRQ1 == interruptNum),
             "Unexpected interruptNum: %d\r\n",
             interruptNum);

    /*
     * Priority expected is either:
     *    INT_PRI_LEVEL0 to INT_PRI_LEVEL3,
     *    or ~0 or 255 (meaning lowest priority)
     *    ~0 and 255 are meant to be the same as INT_PRI_LEVEL3.
     */
    __ASSERT((INT_PRI_LEVEL0 == priority) || (INT_PRI_LEVEL3 == priority) || (INT_PRI_LEVEL2 == priority) ||
                 (INT_PRI_LEVEL1 == priority) || (0xFF == priority),
             "Unexpected priority level, got: 0x%x\r\n",
             (unsigned int)priority);

    if (0xFF == priority)
    {
        priority = INT_PRI_LEVEL3;
    }

    /* The priority for IRQ_CONNECT is encoded in the top 2 bits */
    priority = (priority >> 6);

    switch (interruptNum)
    {
        case INT_CPUIRQ1:
            sl_IRQ01_cb.cb  = hwiFxn;
            sl_IRQ01_cb.arg = arg;
            obj->cb         = &sl_IRQ01_cb;
            irq_connect_dynamic(INT_CPUIRQ1 - 16, priority, sl_isr, &sl_IRQ01_cb, 0);
            break;
        case INT_CPUIRQ3:
            sl_IRQ03_cb.cb  = hwiFxn;
            sl_IRQ03_cb.arg = arg;
            obj->cb         = &sl_IRQ03_cb;
            irq_connect_dynamic(INT_CPUIRQ3 - 16, priority, sl_isr, &sl_IRQ03_cb, 0);
            break;
        case INT_CPUIRQ4:
            s1_IRQ04_cb.cb  = hwiFxn;
            s1_IRQ04_cb.arg = arg;
            obj->cb         = &s1_IRQ04_cb;
            irq_connect_dynamic(INT_CPUIRQ4 - 16, priority, sl_isr, &s1_IRQ04_cb, 0);
            break;
        case INT_CPUIRQ16:
            sl_IRQ16_cb.cb  = hwiFxn;
            sl_IRQ16_cb.arg = arg;
            obj->cb         = &sl_IRQ16_cb;
            irq_connect_dynamic(INT_CPUIRQ16 - 16, priority, sl_isr, &sl_IRQ16_cb, 0);
            break;
        case INT_LRFD_IRQ0:
            s1_LRFD_IRQ0_cb.cb  = hwiFxn;
            s1_LRFD_IRQ0_cb.arg = arg;
            obj->cb             = &s1_LRFD_IRQ0_cb;
            irq_connect_dynamic(INT_LRFD_IRQ0 - 16, priority, sl_isr, &s1_LRFD_IRQ0_cb, 0);
            break;
        case INT_LRFD_IRQ1:
            s1_LRFD_IRQ1_cb.cb  = hwiFxn;
            s1_LRFD_IRQ1_cb.arg = arg;
            obj->cb             = &s1_LRFD_IRQ1_cb;
            irq_connect_dynamic(INT_LRFD_IRQ1 - 16, priority, sl_isr, &s1_LRFD_IRQ1_cb, 0);
            break;
        default:
            return (NULL);
    }
    irq_enable(interruptNum - 16);

    obj->intNum = interruptNum;

    return (HwiP_Handle)handle;
}

void HwiP_Params_init(HwiP_Params *params)
{
    params->arg      = 0;
    params->priority = ~0;
}

/* Zephyr has no functions for clearing an interrupt, so use driverlib: */
void HwiP_clearInterrupt(int interruptNum)
{
    IntClearPend((uint32_t)interruptNum);
}

void HwiP_enableInterrupt(int interruptNum)
{
    irq_enable(interruptNum - 16);
}

void HwiP_disableInterrupt(int interruptNum)
{
    irq_disable(interruptNum - 16);
}

uintptr_t HwiP_disable(void)
{
    uintptr_t key;

    key = irq_lock();

    return (key);
}

void HwiP_restore(uintptr_t key)
{
    irq_unlock(key);
}

void HwiP_post(int interruptNum)
{
    IntSetPend((uint32_t)interruptNum);
}

void HwiP_setFunc(HwiP_Handle hwiP, HwiP_Fxn fxn, uintptr_t arg)
{
    HwiP_Obj *obj = (HwiP_Obj *)hwiP;

    uintptr_t key = HwiP_disable();

    obj->cb->cb  = fxn;
    obj->cb->arg = arg;

    HwiP_restore(key);
}

void HwiP_destruct(HwiP_Struct *hwiP)
{
    HwiP_Obj *obj = (HwiP_Obj *)hwiP->data;

    int interruptNum = obj->intNum;

    irq_disable(interruptNum - 16);

    obj->cb->cb  = NULL;
    obj->cb->arg = (uintptr_t)NULL;
    obj->cb      = NULL;
}

void HwiP_setPriority(int interruptNum, uint32_t priority)
{
    /*
     * On CM0+, dynamically changing priorities is not allowed. In order to
     * change priority of an interrupt, after it already has been enabled, the
     * following must be done:
     * - Disable the interrupt whose priority needs to be updated
     * - Set the priority to be at the desired priority level
     * - Re-enable the interrupt.
     *
     * These steps are all handled by IntSetPriority().
     *
     * HwiP_disable/enable here serves the purpose of deferring the handling of
     * user interrupts until the priority of interruptNum has been changed. This
     * prevents another interrupt from changing the global state potentially
     * altering the outcome of this function.
     */

    uintptr_t key = HwiP_disable();
    IntSetPriority((uint32_t)interruptNum, (uint8_t)priority);
    HwiP_restore(key);
}

/*
 *  ======== HwiP_inISR ========
 */
bool HwiP_inISR(void)
{
    bool stat;

    if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) == 0)
    {
        /* Not currently in an ISR */
        stat = false;
    }
    else
    {
        stat = true;
    }

    return (stat);
}

/*
 *  ======== HwiP_inSwi ========
 */
bool HwiP_inSwi(void)
{
    uint32_t intNum = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
    if (intNum == HwiP_swiPIntNum)
    {
        /* Currently in a Swi */
        return (true);
    }

    return (false);
}