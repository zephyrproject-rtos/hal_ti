/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
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
 *  ======== BatMonSupportLPF3.c ========
 *
 */

/* Includes */
#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>
#include <ti/drivers/temperature/TemperatureLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_evtull.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_pmud.h)
#include DeviceFamily_constructPath(inc/hw_types.h)

/* Forward declarations */
static void batMonHwiFxn(uintptr_t arg0);

/* Globals */

/* HWI struct for the shared BATMON interrupt */
static HwiP_Struct batMonHwi;

/* Allocate memory for registered event callback functions */
static BatMonSupportLPF3_EventCb temperatureCb = NULL;
static BatMonSupportLPF3_EventCb batteryCb     = NULL;

/* Event masks for the registered event callback functions */
static uint32_t temperatureEventMask = 0;
static uint32_t batteryEventMask     = 0;

static bool isInitialized = false;

extern const BatMonSupportLPF3_Config BatMonSupportLPF3_config;

/*
 *  ======== batMonHwiFxn ========
 *
 *  AON_PMU_COMB Interrupt
 */
static void batMonHwiFxn(uintptr_t arg0)
{
    uint32_t events = HWREG(PMUD_BASE + PMUD_O_EVENT);

    if (((events & batteryEventMask) != 0) && (batteryCb != NULL))
    {
        batteryCb(events & batteryEventMask);
    }

    if (((events & temperatureEventMask) != 0) && (temperatureCb != NULL))
    {
        temperatureCb(events & temperatureEventMask);
    }

    HwiP_clearInterrupt(BatMonSupportLPF3_config.intNum);
}

/*
 *  ======== BatMonSupportLPF3_init ========
 */
void BatMonSupportLPF3_init(void)
{
    uint32_t key;

    key = HwiP_disable();

    if (isInitialized == false)
    {
        /* Claim configurable CPUIRQ as AON_PMU_COMB */
        HWREG(EVTSVT_BASE + EVTSVT_O_CPUIRQ0SEL + (BatMonSupportLPF3_config.intNum - INT_CPUIRQ0) * sizeof(uint32_t)) = BatMonSupportLPF3_config.intMux;

        /* Initialise the BatMon HWI. The temperature sensor shares this
         * interrupt with the battery voltage monitoring events.
         */
        HwiP_Params hwiParams;
        HwiP_Params_init(&hwiParams);
        hwiParams.priority  = BatMonSupportLPF3_config.intPriority;
        hwiParams.enableInt = true;
        HwiP_construct(&batMonHwi, BatMonSupportLPF3_config.intNum, batMonHwiFxn, &hwiParams);

        /* Disable all events */
        HWREG(PMUD_BASE + PMUD_O_EVENTMASK) = 0;

        /* Enable BATMON. Explicitly disable HW hysteresis to avoid HW bug
         * causing poor temperature measurement accuracy.
         */
        HWREG(PMUD_BASE + PMUD_O_CTL) = PMUD_CTL_CALC_EN | PMUD_CTL_MEAS_EN | PMUD_CTL_HYST_EN_DIS;

        /* Set the combined BATMON interrupt as a wakeup source. This means the
         * BATMON can bring the device out of standby when an event is
         * triggered.
         */
        HWREG(EVTULL_BASE + EVTULL_O_WKUPMASK) |= EVTULL_WKUPMASK_AON_PMU_COMB;

        isInitialized = true;
    }

    HwiP_restore(key);
}

/*
 *  ======== BatMonSupportLPF3_registerTemperatureCb ========
 */
void BatMonSupportLPF3_registerTemperatureCb(uint32_t eventMask, BatMonSupportLPF3_EventCb callback)
{
    uint32_t key;

    key = HwiP_disable();

    temperatureEventMask = eventMask;
    temperatureCb        = callback;

    HwiP_restore(key);
}

/*
 *  ======== BatMonSupportLPF3_registerBatteryCb ========
 */
void BatMonSupportLPF3_registerBatteryCb(uint32_t eventMask, BatMonSupportLPF3_EventCb callback)
{
    uint32_t key;

    key = HwiP_disable();

    batteryEventMask = eventMask;
    batteryCb        = callback;

    HwiP_restore(key);
}