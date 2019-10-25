/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr.h>
#include <sys/__assert.h>
#include <kernel/zephyr/dpl/dpl.h>
#include <ti/drivers/dpl/HwiP.h>

#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <driverlib/rom.h>
#if defined(CONFIG_SOC_SERIES_CC32XX)
#include <driverlib/rom_map.h>
#endif
#include <driverlib/interrupt.h>

#include "stubs.h"

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

static void sl_isr(void *isr_arg)
{
	HwiP_Fxn cb = ((struct sl_isr_args *)isr_arg)->cb;
	uintptr_t arg =	 ((struct sl_isr_args *)isr_arg)->arg;

	/* Call the SimpleLink ISR Handler: */
	if (cb) {
		cb(arg);
	}
}

#if defined(CONFIG_SOC_SERIES_CC32XX)
static struct sl_isr_args sl_UDMA_cb = {NULL, 0};
static struct sl_isr_args sl_UDMAERR_cb = {NULL, 0};
static struct sl_isr_args sl_NWPIC_cb = {NULL, 0};
static struct sl_isr_args sl_LSPI_cb = {NULL, 0};

/* Must hardcode the IRQ for IRQ_CONNECT macro.	 Must be <= CONFIG_NUM_IRQS.*/
#define EXCEPTION_UDMA		46	/* == INT_UDMA	(62) - 16 */
#define EXCEPTION_UDMAERR	47	/* == INT_UDMAERR (63) - 16 */
#define EXCEPTION_NWPIC		171	/* == INT_NWPIC (187) - 16 */
#define EXCEPTION_LSPI		177	/* == INT_LSPI (193) - 16 */

HwiP_Handle HwiP_create(int interruptNum, HwiP_Fxn hwiFxn, HwiP_Params *params)
{
	HwiP_Handle handle = 0;
	uint32_t priority = ~0;
	uintptr_t arg = 0;

	if (params) {
		priority = params->priority;
		arg = params->arg;
	}

	/*
	 * SimpleLink only uses the NWPIC, UDMA, UDMAERR and LSPI interrupts:
	 */
	__ASSERT(INT_NWPIC == interruptNum || INT_UDMA == interruptNum ||
		 INT_UDMAERR == interruptNum || INT_LSPI == interruptNum,
		 "Unexpected interruptNum: %d\r\n",
		 interruptNum);
	/*
	 * Priority expected is either:
	 *    INT_PRIORITY_LVL_1,
	 *    or ~0 or 255 (meaning lowest priority)
	 *    ~0 and 255 are meant to be the same as INT_PRIORITY_LVL_7.
	 *    For ~0 or 255, we want 7; but Zephyr IRQ_CONNECT adds +1,
	 *    so we pass 6 for those TI drivers passing prio = ~0.
	 */
	__ASSERT((INT_PRIORITY_LVL_1 == priority) ||
		 (0xff == (priority & 0xff)),
		 "Expected priority: 0x%x or 0x%x, got: 0x%x\r\n",
		 INT_PRIORITY_LVL_1, 0xff, (unsigned int)priority);

	switch(interruptNum) {
	case INT_UDMA:
		sl_UDMA_cb.cb = hwiFxn;
		sl_UDMA_cb.arg = arg;
		IRQ_CONNECT(EXCEPTION_UDMA, 6, sl_isr, &sl_UDMA_cb, 0);
		break;
	case INT_UDMAERR:
		sl_UDMAERR_cb.cb = hwiFxn;
		sl_UDMAERR_cb.arg = arg;
		IRQ_CONNECT(EXCEPTION_UDMAERR, 6, sl_isr, &sl_UDMAERR_cb, 0);
		break;
	case INT_NWPIC:
		sl_NWPIC_cb.cb = hwiFxn;
		sl_NWPIC_cb.arg = arg;
		IRQ_CONNECT(EXCEPTION_NWPIC, 1, sl_isr, &sl_NWPIC_cb, 0);
		break;
	case INT_LSPI:
		sl_LSPI_cb.cb = hwiFxn;
		sl_LSPI_cb.arg = arg;
		IRQ_CONNECT(EXCEPTION_LSPI, 6, sl_isr, &sl_LSPI_cb, 0);
		break;
	default:
		return(handle);
	}
	irq_enable(interruptNum - 16);

	return (HwiP_Handle)interruptNum;
}

/* Can't actually de-register an interrupt in Zephyr, so just disable: */
void HwiP_delete(HwiP_Handle handle)
{
	int interruptNum = (int)handle;

	__ASSERT(INT_NWPIC == interruptNum || INT_UDMA == interruptNum ||
		 INT_UDMAERR == interruptNum || INT_LSPI == interruptNum,
		 "Unexpected interruptNum: %d\r\n",
		 interruptNum);

	irq_disable(interruptNum - 16);
}
#elif defined(CONFIG_SOC_SERIES_CC13X2_CC26X2)
/* INT_PENDSV is already taken by Zephyr, so let's use INT_SWEV0 to support
 * SwiP since this line is usually unused. Change this to a different
 * interrupt if desired.
 */
int HwiP_swiPIntNum = INT_SWEV0;

typedef struct _HwiP_Obj {
    uint32_t intNum;
    struct sl_isr_args * cb;
} HwiP_Obj;

static struct sl_isr_args sl_OSC_COMB_cb = {NULL, 0};
static struct sl_isr_args sl_AUX_COMB_cb = {NULL, 0};
static struct sl_isr_args sl_RFC_HW_COMB_cb = {NULL, 0};
static struct sl_isr_args sl_RFC_CPE_0_cb = {NULL, 0};
static struct sl_isr_args sl_SWEV0_cb = {NULL, 0};

/*
 *  ======== HwiP_construct ========
 */
HwiP_Handle HwiP_construct(HwiP_Struct *handle, int interruptNum,
                           HwiP_Fxn hwiFxn, HwiP_Params *params)
{
	HwiP_Obj *obj = (HwiP_Obj *)handle;
	uintptr_t arg = 0;
	uint8_t priority = INT_PRI_LEVEL7; /* default to lowest priority */
	
	if (handle == NULL) {
		return NULL;
	}

	if (params) {
		priority = params->priority;
		arg = params->arg;
	}

	/*
	 * Currently only support INT_OSC_COMB, INT_AUX_COMB, INT_SWEV0
	 */
	__ASSERT(INT_OSC_COMB == interruptNum || INT_AUX_COMB == interruptNum
		|| INT_RFC_HW_COMB == interruptNum
		|| INT_RFC_CPE_0 == interruptNum
		|| INT_SWEV0 == interruptNum,
		 "Unexpected interruptNum: %d\r\n",
		 interruptNum);

	/*
	 * Priority expected is either:
	 *    INT_PRI_LEVEL1 to INT_PRI_LEVEL7,
	 *    or ~0 or 255 (meaning lowest priority)
	 *    ~0 and 255 are meant to be the same as INT_PRI_LEVEL7.
	 *    For ~0 or 255, we want 7; but Zephyr IRQ_CONNECT adds +1
	 *    to reserve INT_PRI_LEVEL0,
	 *    so we pass 6 for those TI drivers passing prio = ~0.
	 */
	__ASSERT((INT_PRI_LEVEL7 == priority) ||
		(INT_PRI_LEVEL6 == priority) ||
		(INT_PRI_LEVEL5 == priority) ||
		(INT_PRI_LEVEL4 == priority) ||
		(INT_PRI_LEVEL3 == priority) ||
		(INT_PRI_LEVEL2 == priority) ||
		(INT_PRI_LEVEL1 == priority) ||
		(0xFF == priority),
		"Unexpected priority level, got: 0x%x\r\n",
		(unsigned int)priority);

	if (0xFF == priority) {
		priority = INT_PRI_LEVEL7;
	}

	/* The priority for IRQ_CONNECT is encoded in the top 3 bits */ 
	priority = (priority >> 5) - 1;

	switch(interruptNum) {
	case INT_RFC_CPE_0:
		sl_RFC_CPE_0_cb.cb = hwiFxn;
		sl_RFC_CPE_0_cb.arg = arg;
		obj->cb = &sl_RFC_CPE_0_cb;
		IRQ_CONNECT(INT_RFC_CPE_0 - 16, priority, sl_isr, &sl_RFC_CPE_0_cb, 0);
		break;
	case INT_RFC_HW_COMB:
		sl_RFC_HW_COMB_cb.cb = hwiFxn;
		sl_RFC_HW_COMB_cb.arg = arg;
		obj->cb = &sl_RFC_HW_COMB_cb;
		IRQ_CONNECT(INT_RFC_HW_COMB - 16, priority, sl_isr, &sl_RFC_HW_COMB_cb, 0);
		break;
	case INT_OSC_COMB:
		sl_OSC_COMB_cb.cb = hwiFxn;
		sl_OSC_COMB_cb.arg = arg;
		obj->cb = &sl_OSC_COMB_cb;
		IRQ_CONNECT(INT_OSC_COMB - 16, priority, sl_isr, &sl_OSC_COMB_cb, 0);
		break;
	case INT_AUX_COMB:
		sl_AUX_COMB_cb.cb = hwiFxn;
		sl_AUX_COMB_cb.arg = arg;
		obj->cb = &sl_AUX_COMB_cb;
		IRQ_CONNECT(INT_AUX_COMB - 16, priority, sl_isr, &sl_AUX_COMB_cb, 0);
		break;
	case INT_SWEV0:
		sl_SWEV0_cb.cb = hwiFxn;
		sl_SWEV0_cb.arg = arg;
		obj->cb = &sl_SWEV0_cb;
		IRQ_CONNECT(INT_SWEV0 - 16, priority, sl_isr, &sl_SWEV0_cb, 0);
		break;
	default:
		return(NULL);
	}
	irq_enable(interruptNum - 16);
	
	obj->intNum = interruptNum;

	return (HwiP_Handle)handle;
}
#endif

void HwiP_Params_init(HwiP_Params *params)
{
	params->arg = 0;
	params->priority = ~0;
}

/* Zephyr has no functions for clearing an interrupt, so use driverlib: */
void HwiP_clearInterrupt(int interruptNum)
{
#if defined(CONFIG_SOC_SERIES_CC13X2_CC26X2)
        IntPendClear((unsigned long)interruptNum);
#elif defined(CONFIG_SOC_SERIES_CC32XX)
	MAP_IntPendClear((unsigned long)interruptNum);
#endif
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

#if defined(CONFIG_SOC_SERIES_CC13X2_CC26X2)
void HwiP_post(int interruptNum)
{
	IntPendSet((uint32_t)interruptNum);
}

void HwiP_setFunc(HwiP_Handle hwiP, HwiP_Fxn fxn, uintptr_t arg)
{
	HwiP_Obj *obj = (HwiP_Obj *)hwiP;

	uintptr_t key = HwiP_disable();

	obj->cb->cb = fxn;
	obj->cb->arg = arg;

	HwiP_restore(key);
}

void HwiP_destruct(HwiP_Struct *hwiP)
{
	HwiP_Obj *obj = (HwiP_Obj *)hwiP->data;

	int interruptNum = obj->intNum;

	irq_disable(interruptNum - 16);

	obj->cb->cb = NULL;
	obj->cb->arg = (uintptr_t)NULL;
	obj->cb = NULL;
}
#endif
