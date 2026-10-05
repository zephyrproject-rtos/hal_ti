/*
 * Copyright (c) 2022-2025, Texas Instruments Incorporated
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
 *  ======== BatteryMonitorLPF3.c ========
 *
 */

/* Includes */
#include <stdint.h>
#include <stdbool.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/BatteryMonitor.h>
#include <ti/drivers/batterymonitor/BatteryMonitorLPF3.h>
#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>

#include <ti/drivers/utils/Math.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_pmud.h)
#include DeviceFamily_constructPath(inc/hw_pmctl.h)
#include DeviceFamily_constructPath(driverlib/interrupt.h)

/* Forward declarations */
static void BatteryMonitorLPF3_walkNotifyList(uint16_t currentVoltage);
static void BatteryMonitorLPF3_setNextThresholds(void);
static void BatteryMonitorLPF3_batteryEventCb(uint32_t eventMask);
static void BatteryMonitorLPF3_updateThresholds(uint16_t thresholdHigh, uint16_t thresholdLow);
static uint32_t BatteryMonitorLPF3_millivoltsToCode(uint16_t voltageMillivolts);
static void BatteryMonitorLPF3_setBatLowerLimit(uint16_t thresholdLow);
static void BatteryMonitorLPF3_setBatUpperLimit(uint16_t thresholdHigh);
static void BatteryMonitorLPF3_enableBatLowerLimit(void);
static void BatteryMonitorLPF3_enableBatUpperLimit(void);
static void BatteryMonitorLPF3_disableBatLowerLimit(void);
static void BatteryMonitorLPF3_disableBatUpperLimit(void);
static void BatteryMonitorLPF3_clearEventFlags(void);

/* Globals */

/* Global list that stores all registered notifications */
static volatile List_List BatteryMonitorLPF3_notificationList;

/* Current threshold values. These should always reflect the state of the
 * BATMON registers without the need to read them out, and convert to
 * millivolts.
 */
static volatile uint16_t BatteryMonitorLPF3_currentThresholdHigh = INVALID_VOLTAGE_MAX;
static volatile uint16_t BatteryMonitorLPF3_currentThresholdLow  = INVALID_VOLTAGE_MIN;

/*
 *  ======== BatteryMonitorLPF3_millivoltsToCode ========
 * This function takes in a voltage in millivolts (with no fractional bits) and
 * converts it to a code that can be written directly to the BATMON hardware,
 * when configuring thresholds.
 */
static uint32_t BatteryMonitorLPF3_millivoltsToCode(uint16_t voltageMillivolts)
{
    /* Add fractional bits */
    uint32_t voltageCode = ((uint32_t)voltageMillivolts) << PMUD_BAT_INT_S;

#if DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX
    /* Convert from millivolts to volts */
    voltageCode /= 1000U;
#else
    /* Convert from millivolts to volts */
    voltageCode = Math_divideBy1000(voltageCode);
#endif

    /* Mask result */
    voltageCode &= (PMUD_BAT_INT_M | PMUD_BAT_FRAC_M);

    return voltageCode;
}

/*
 *  ======== BatteryMonitorLPF3_setBatLowerLimit ========
 */
static void BatteryMonitorLPF3_setBatLowerLimit(uint16_t thresholdLow)
{
    uintptr_t key;
    uint32_t voltageCode = BatteryMonitorLPF3_millivoltsToCode(thresholdLow);

    key                              = HwiP_disable();
    HWREG(PMUD_BASE + PMUD_O_BATTLL) = voltageCode;

    BatteryMonitorLPF3_currentThresholdLow = thresholdLow;
    HwiP_restore(key);
}

/*
 *  ======== BatteryMonitorLPF3_setBatUpperLimit ========
 */
static void BatteryMonitorLPF3_setBatUpperLimit(uint16_t thresholdHigh)
{
    uintptr_t key;
    uint32_t voltageCode = BatteryMonitorLPF3_millivoltsToCode(thresholdHigh);

    key                              = HwiP_disable();
    HWREG(PMUD_BASE + PMUD_O_BATTUL) = voltageCode;

    BatteryMonitorLPF3_currentThresholdHigh = thresholdHigh;
    HwiP_restore(key);
}

/*
 *  ======== BatteryMonitorLPF3_enableBatLowerLimit ========
 */
static void BatteryMonitorLPF3_enableBatLowerLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) |= PMUD_EVENTMASK_BATT_BELOW_LL_MASK;
}

/*
 *  ======== BatteryMonitorLPF3_enableBatUpperLimit ========
 */
static void BatteryMonitorLPF3_enableBatUpperLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) |= PMUD_EVENTMASK_BATT_OVER_UL_MASK;
}

/*
 *  ======== BatteryMonitorLPF3_disableBatLowerLimit ========
 */
static void BatteryMonitorLPF3_disableBatLowerLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) &= ~(uint32_t)PMUD_EVENTMASK_BATT_BELOW_LL_MASK;
}

/*
 *  ======== BatteryMonitorLPF3_disableBatUpperLimit ========
 */
static void BatteryMonitorLPF3_disableBatUpperLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) &= ~(uint32_t)PMUD_EVENTMASK_BATT_OVER_UL_MASK;
}

/*
 *  ======== BatteryMonitorLPF3_clearEventFlags ========
 */
static void BatteryMonitorLPF3_clearEventFlags(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENT) &= (PMUD_EVENT_BATT_BELOW_LL | PMUD_EVENT_BATT_OVER_UL);
}

/*
 *  ======== BatteryMonitorLPF3_updateThresholds ========
 */
static void BatteryMonitorLPF3_updateThresholds(uint16_t thresholdHigh, uint16_t thresholdLow)
{
    if (thresholdHigh < BatteryMonitorLPF3_currentThresholdHigh)
    {
        BatteryMonitorLPF3_setBatUpperLimit(thresholdHigh);
        BatteryMonitorLPF3_enableBatUpperLimit();
    }

    if (thresholdLow > BatteryMonitorLPF3_currentThresholdLow)
    {
        BatteryMonitorLPF3_setBatLowerLimit(thresholdLow);
        BatteryMonitorLPF3_enableBatLowerLimit();
    }
}

/*
 *  ======== BatteryMonitorLPF3_batteryEventCb ========
 *
 *  BATMON interrupt triggered on high or low battery event
 */
static void BatteryMonitorLPF3_batteryEventCb(uint32_t eventMask)
{
    /* Unused parameter */
    (void)eventMask;

    /* Get the current voltage */
    uint16_t currentVoltage = BatteryMonitor_getVoltage();

    /* Read volatile variables in well defined order */
    uint16_t thresholdLow  = BatteryMonitorLPF3_currentThresholdLow;
    uint16_t thresholdHigh = BatteryMonitorLPF3_currentThresholdHigh;

    /* Only walk through notify list if the current voltage is actually above the high threshold or below the low
     * threshold. */
    if ((currentVoltage <= thresholdLow) || (currentVoltage >= thresholdHigh))
    {
        BatteryMonitorLPF3_setBatUpperLimit(INVALID_VOLTAGE_MAX);
        BatteryMonitorLPF3_disableBatUpperLimit();

        BatteryMonitorLPF3_setBatLowerLimit(INVALID_VOLTAGE_MIN);
        BatteryMonitorLPF3_disableBatLowerLimit();

        /* Walk the notification list and issue any callbacks that have triggered
         * at the current voltage.
         */
        BatteryMonitorLPF3_walkNotifyList(currentVoltage);

        /* Walk the queue another time to find and set the next set of thresholds.
         */
        BatteryMonitorLPF3_setNextThresholds();
    }

    /* Clear event flags. */
    BatteryMonitorLPF3_clearEventFlags();
}

/*
 *  ======== BatteryMonitor_init ========
 */
void BatteryMonitor_init(void)
{
    /* Static variable to track if the driver has been initialized */
    static bool isInitialized = false;

    uintptr_t key;

    key = HwiP_disable();

    if (isInitialized == false)
    {
        BatMonSupportLPF3_init();
        BatMonSupportLPF3_registerBatteryCb((PMUD_EVENT_BATT_BELOW_LL | PMUD_EVENT_BATT_OVER_UL),
                                            BatteryMonitorLPF3_batteryEventCb);

        /* Wait until first measurement is ready to prevent BatteryMonitor_getVoltage
         * returning an invalid value.
         */
        while ((HWREG(PMUD_BASE + PMUD_O_BATUPD) & PMUD_BATUPD_STA_M) != PMUD_BATUPD_STA_M) {}

        isInitialized = true;
    }

    HwiP_restore(key);
}

/*
 *  ======== BatteryMonitor_getVoltage ========
 */
uint16_t BatteryMonitor_getVoltage(void)
{
    /* The voltage on LPF3 is stored in a 32-bit register
     * containing a 3-bit unsigned integer part and a 8-bit unsigned fractional
     * part.
     */

    /* Voltage in 3.8 fixed-point format (in Volts) */
    uint32_t voltage = HWREG(PMUD_BASE + PMUD_O_BAT) & (PMUD_BAT_INT_M | PMUD_BAT_FRAC_M);

    /* Convert to mV by multiplying by 1000 */
    voltage *= 1000U;

#if (PMUD_BAT_INT_W + PMUD_BAT_INT_S + 10U) > 32U
    #error Intermediate result in BatteryMonitor_getVoltage() will not fit in 32 bits
#endif

    /* Round to nearest integer and discard fractional part */
    voltage = (voltage + ((uint32_t)1U << (PMUD_BAT_INT_S - 1U))) >> PMUD_BAT_INT_S;

#if (PMUD_BAT_INT_W + 10U) > 16U
    #error Result for BatteryMonitor_getVoltage() will not fit in 16 bits
#endif

    /* Cast to 16 bits. This is safe to do. The multiplier (1000) uses 10
     * integer bits, so the result of the product will have a format of
     * 13.8 and after discarding the fractional bits only 13 bits will be used.
     * Which fits within 16 bits.
     */
    return (uint16_t)voltage;
}

/*
 *  ======== BatteryMonitorLPF3_setNextThresholds ========
 */
static void BatteryMonitorLPF3_setNextThresholds(void)
{
    List_Elem *notifyLink;
    uint16_t nextThresholdHigh = INVALID_VOLTAGE_MAX;
    uint16_t nextThresholdLow  = INVALID_VOLTAGE_MIN;
    uintptr_t key;

    key = HwiP_disable();

    /* Starting with the head of the list, keep track of the smallest high
     * threshold and largest low threshold.
     */
    notifyLink = List_head((List_List *)&BatteryMonitorLPF3_notificationList);

    while (notifyLink != NULL)
    {
        BatteryMonitor_NotifyObj *notifyObject = (BatteryMonitor_NotifyObj *)notifyLink;

        nextThresholdHigh = Math_MIN(nextThresholdHigh, notifyObject->thresholdHigh);
        nextThresholdLow  = Math_MAX(nextThresholdLow, notifyObject->thresholdLow);

        notifyLink = List_next(notifyLink);
    }

    /* Now that we have found the next upper and lower thresholds, set them.
     * These could be INVALID_VOLTAGE_MAX and/or INVALID_VOLTAGE_MIN
     * if the list is empty or only high/low notifications were registered.
     */
    BatteryMonitorLPF3_updateThresholds(nextThresholdHigh, nextThresholdLow);

    HwiP_restore(key);
}

/*
 *  ======== BatteryMonitorLPF3_walkNotifyList ========
 */
static void BatteryMonitorLPF3_walkNotifyList(uint16_t currentVoltage)
{
    List_Elem *notifyLink = List_head((List_List *)&BatteryMonitorLPF3_notificationList);

    /* If the notification list is empty, the head pointer will be
     * NULL and the while loop will never execute the statement.
     */
    while (notifyLink != NULL)
    {
        BatteryMonitor_NotifyObj *notifyObject = (BatteryMonitor_NotifyObj *)notifyLink;

        /* Buffer the next link in case the notification triggers.
         * Without buffering, we might skip list entries if the
         * notifyObject is freed or re-registered and the notifyObject->link.next
         * pointer is altered.
         */
        List_Elem *notifyLinkNext = List_next(notifyLink);

        /* If the current voltage is below this notification's low
         * threshold or above its high threshold, remove it from the list and
         * call the callback fxn
         */
        if ((currentVoltage <= notifyObject->thresholdLow) || (currentVoltage >= notifyObject->thresholdHigh))
        {

            /* Choose the threshold to provide to the notifyFxn based on the
             * thresholds and the current voltage.
             */
            uint16_t threshold = (currentVoltage <= notifyObject->thresholdLow) ? notifyObject->thresholdLow
                                                                                : notifyObject->thresholdHigh;

            List_remove((List_List *)&BatteryMonitorLPF3_notificationList, notifyLink);
            notifyObject->isRegistered = false;

            notifyObject->notifyFxn(currentVoltage, threshold, notifyObject->clientArg, notifyObject);
        }

        notifyLink = notifyLinkNext;
    }
}

/*
 *  ======== BatteryMonitor_registerNotifyHigh ========
 */
int_fast16_t BatteryMonitor_registerNotifyHigh(BatteryMonitor_NotifyObj *notifyObject,
                                               uint16_t thresholdHigh,
                                               BatteryMonitor_NotifyFxn notifyFxn,
                                               uintptr_t clientArg)
{
    uintptr_t key;

    key = HwiP_disable();

    notifyObject->thresholdHigh = thresholdHigh;
    notifyObject->thresholdLow  = INVALID_VOLTAGE_MIN;
    notifyObject->notifyFxn     = notifyFxn;
    notifyObject->clientArg     = clientArg;

    if (notifyObject->isRegistered == false)
    {
        /* Add the notification to the end of the list.
         * There is the implicit assumption that the notification is not already
         * in the list. Otherwise the list linkage will be corrupted.
         */
        List_put((List_List *)&BatteryMonitorLPF3_notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    BatteryMonitorLPF3_updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return BatteryMonitor_STATUS_SUCCESS;
}

/*
 *  ======== BatteryMonitor_registerNotifyLow ========
 */
int_fast16_t BatteryMonitor_registerNotifyLow(BatteryMonitor_NotifyObj *notifyObject,
                                              uint16_t thresholdLow,
                                              BatteryMonitor_NotifyFxn notifyFxn,
                                              uintptr_t clientArg)
{
    uintptr_t key;

    key = HwiP_disable();

    notifyObject->thresholdHigh = INVALID_VOLTAGE_MAX;
    notifyObject->thresholdLow  = thresholdLow;
    notifyObject->notifyFxn     = notifyFxn;
    notifyObject->clientArg     = clientArg;

    if (notifyObject->isRegistered == false)
    {
        /* Add the notification to the end of the list.
         * There is the implicit assumption that the notification is not already
         * in the list. Otherwise the list linkage will be corrupted.
         */
        List_put((List_List *)&BatteryMonitorLPF3_notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    BatteryMonitorLPF3_updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return BatteryMonitor_STATUS_SUCCESS;
}

/*
 *  ======== BatteryMonitor_registerNotifyRange ========
 */
int_fast16_t BatteryMonitor_registerNotifyRange(BatteryMonitor_NotifyObj *notifyObject,
                                                uint16_t thresholdHigh,
                                                uint16_t thresholdLow,
                                                BatteryMonitor_NotifyFxn notifyFxn,
                                                uintptr_t clientArg)
{
    uintptr_t key;

    key = HwiP_disable();

    notifyObject->thresholdHigh = thresholdHigh;
    notifyObject->thresholdLow  = thresholdLow;
    notifyObject->notifyFxn     = notifyFxn;
    notifyObject->clientArg     = clientArg;

    if (notifyObject->isRegistered == false)
    {
        /* Add the notification to the end of the list.
         * There is the implicit assumption that the notification is not already
         * in the list. Otherwise the list linkage will be corrupted.
         */
        List_put((List_List *)&BatteryMonitorLPF3_notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    BatteryMonitorLPF3_updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return BatteryMonitor_STATUS_SUCCESS;
}

/*
 *  ======== BatteryMonitor_unregisterNotify ========
 */
int_fast16_t BatteryMonitor_unregisterNotify(BatteryMonitor_NotifyObj *notifyObject)
{
    uintptr_t key;

    key = HwiP_disable();

    if (notifyObject->isRegistered == true)
    {
        /* Remove the notification from the list */
        List_remove((List_List *)&BatteryMonitorLPF3_notificationList, &(notifyObject->link));

        notifyObject->isRegistered = false;
    }

    /* Find the next set of thresholds and update the registers */
    BatteryMonitorLPF3_setNextThresholds();

    HwiP_restore(key);

    return BatteryMonitor_STATUS_SUCCESS;
}
