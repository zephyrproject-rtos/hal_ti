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

/* Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/drivers/Temperature.h>
#include <ti/drivers/temperature/TemperatureLPF3.h>
#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>

#include <ti/drivers/utils/Math.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_evtull.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_pmud.h)
#include DeviceFamily_constructPath(inc/hw_pmctl.h)
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/interrupt.h)

/* Macros */
/* Offset to apply to all thresholds before programming the hardware.
 *
 * When the hardware samples the temperature sensor, the returned reading
 * is drawn from a probability distribution of measurements for each true
 * temperature. In order for a notification to trigger, two separate
 * measurements must cross the configured threshold temperature.
 * The first is initiated by the hardware in the background to check whether
 * to trigger the HWI. The second is triggered by software within the HWI
 * function. If the first measurement is part of the long tail of the
 * distribution, it is highly probable that the second measurement will not
 * cross the threshold. This is effectively a spurrious interrupt that wastes
 * energy and CPU cycles.
 * If we program the actual hardware registers with an additional offset, we
 * effectively shift the distribution up or down such that the first measurement
 * triggers on the long tail of the distribution that is DISTRIBUTION_OFFSET
 * degrees away from the threshold provided by the application. The second
 * measurement then has a much higher probability of crossing the threshold
 * and triggering the notification and an update of the thresholds.
 *
 * The risk is of course that a particular chip has a compressed distribution
 * where the long tail does not reach far enough to trigger the HWI with the
 * offset applied.
 * Additionally, the device does not sample nearly as frequently when in
 * standby.
 *
 * Both of these risks result in a less accurate but overall more useful system.
 * If the temperature keeps rising, both scenarios still cause a notification
 * to trigger. Given that temperature changes are usually not instantaneous,
 * this should be considered an acceptable risk.
 */
#define DISTRIBUTION_OFFSET 2

#define BATMON_TEMPERATURE_MAX (255)
#define BATMON_TEMPERATURE_MIN (-256)

#define INVALID_TEMPERATURE_MAX BATMON_TEMPERATURE_MAX
#define INVALID_TEMPERATURE_MIN BATMON_TEMPERATURE_MIN

/* Forward declarations */
static void walkNotifyList(void);
static void setNextThresholds(void);
static void temperatureEventCb(uint32_t eventMask);
static void updateThresholds(int16_t thresholdHigh, int16_t thresholdLow);
static uint32_t degreesToCode(int32_t temperatureDegreesC);
static void setTempLowerLimit(int16_t thresholdLow);
static void setTempUpperLimit(int16_t thresholdHigh);
static void enableTempLowerLimit(void);
static void enableTempUpperLimit(void);
static void disableTempLowerLimit(void);
static void disableTempUpperLimit(void);
static void clearEventFlags(void);
static void thermalShutdownCallback(int16_t currentTemperature,
                                    int16_t thresholdTemperature,
                                    uintptr_t clientArg,
                                    Temperature_NotifyObj *notifyObject);
static int16_t TemperatureLPF3_scaleToRealTemperature(int32_t temperature);
static int16_t TemperatureLPF3_scaleFromRealTemperature(int32_t temperature);

/* Globals */

/* Global list that stores all registered notifications */
static List_List notificationList;

/* Current threshold values. These should always reflect the state of the
 * batmon registers without the need to read them out, shift down, and sign
 * extend the values.
 */
static volatile int16_t currentThresholdHigh = INVALID_TEMPERATURE_MAX;
static volatile int16_t currentThresholdLow  = INVALID_TEMPERATURE_MIN;

static bool isInitialized = false;

/*
 *  This object is used to monitor the temperature and trigger thermal shutdown once the threshold is reached.
 */
static Temperature_NotifyObj thermalShutdown;

/*
 *  ======== degreesToCode ========
 */
static uint32_t degreesToCode(int32_t temperatureDegreesC)
{
    /* Adjust for BATMON temperature offset */
    temperatureDegreesC = TemperatureLPF3_scaleFromRealTemperature(temperatureDegreesC);

    uint32_t temperatureCode = (temperatureDegreesC << PMUD_TEMP_INT_S) & PMUD_TEMP_INT_M;

    return temperatureCode;
}

/*
 *  ======== setTempLowerLimit ========
 */
static void setTempLowerLimit(int16_t thresholdLow)
{
    uint32_t temperatureCode = degreesToCode(thresholdLow - DISTRIBUTION_OFFSET);

    HWREG(PMUD_BASE + PMUD_O_TEMPLL) = temperatureCode;

    currentThresholdLow = thresholdLow;
}

/*
 *  ======== setTempUpperLimit ========
 */
static void setTempUpperLimit(int16_t thresholdHigh)
{
    uint32_t temperatureCode = degreesToCode(thresholdHigh + DISTRIBUTION_OFFSET);

    HWREG(PMUD_BASE + PMUD_O_TEMPUL) = temperatureCode;

    currentThresholdHigh = thresholdHigh;
}

/*
 *  ======== enableTempLowerLimit ========
 */
static void enableTempLowerLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) |= PMUD_EVENTMASK_TEMP_BELOW_LL_MASK;
}

/*
 *  ======== enableTempUpperLimit ========
 */
static void enableTempUpperLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) |= PMUD_EVENTMASK_TEMP_OVER_UL_MASK;
}

/*
 *  ======== disableTempLowerLimit ========
 */
static void disableTempLowerLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) &= ~PMUD_EVENTMASK_TEMP_BELOW_LL_MASK;
}

/*
 *  ======== disableTempUpperLimit ========
 */
static void disableTempUpperLimit(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENTMASK) &= ~PMUD_EVENTMASK_TEMP_OVER_UL_MASK;
}

/*
 *  ======== clearEventFlags ========
 */
static void clearEventFlags(void)
{
    HWREG(PMUD_BASE + PMUD_O_EVENT) &= PMUD_EVENT_TEMP_BELOW_LL | PMUD_EVENT_TEMP_OVER_UL;
}

/*
 *  ======== setNextThresholds ========
 */
static void setNextThresholds(void)
{
    List_Elem *notifyLink;
    int16_t nextThresholdHigh = INVALID_TEMPERATURE_MAX;
    int16_t nextThresholdLow  = INVALID_TEMPERATURE_MIN;
    uint32_t key;

    key = HwiP_disable();

    /* Starting with the head of the list, keep track of the smallest high
     * threshold and largest low threshold.
     */
    notifyLink = List_head(&notificationList);

    while (notifyLink != NULL)
    {
        Temperature_NotifyObj *notifyObject = (Temperature_NotifyObj *)notifyLink;

        nextThresholdHigh = Math_MIN(nextThresholdHigh, notifyObject->thresholdHigh);
        nextThresholdLow  = Math_MAX(nextThresholdLow, notifyObject->thresholdLow);

        notifyLink = List_next(notifyLink);
    }

    /* Now that we have found the next upper and lower thresholds, set them.
     * These could be INVALID_TEMPERATURE_MAX and/or INVALID_TEMPERATURE_MIN
     * if the list is empty or only high/low notifications were registered.
     */
    updateThresholds(nextThresholdHigh, nextThresholdLow);

    HwiP_restore(key);
}

/*
 *  ======== walkNotifyList ========
 */
static void walkNotifyList(void)
{
    List_Elem *notifyLink      = List_head(&notificationList);
    int16_t currentTemperature = Temperature_getTemperature();

    /* If the notification list is empty, the head pointer will be
     * NULL and the while loop will never execute the statement.
     */
    while (notifyLink != NULL)
    {
        Temperature_NotifyObj *notifyObject = (Temperature_NotifyObj *)notifyLink;

        /* Buffer the next link in case the notification triggers.
         * Without buffering, we might skip list entries if the
         * notifyObject is freed or reregistered and the notifyObject->link.next
         * pointer is altered.
         */
        List_Elem *notifyLinkNext = List_next(notifyLink);

        /* If the current temperature is below this notification's low
         * threshold or above its high threshold, remove it from the list and
         * call the callback fxn
         */
        if (currentTemperature <= notifyObject->thresholdLow || currentTemperature >= notifyObject->thresholdHigh)
        {

            /* Choose the threshold to provide to the notifyFxn based on the
             * thresholds and the current temperature.
             */
            int16_t threshold = (currentTemperature <= notifyObject->thresholdLow) ? notifyObject->thresholdLow
                                                                                   : notifyObject->thresholdHigh;

            List_remove(&notificationList, notifyLink);
            notifyObject->isRegistered = false;

            notifyObject->notifyFxn(currentTemperature, threshold, notifyObject->clientArg, notifyObject);
        }

        notifyLink = notifyLinkNext;
    }
}

/*
 *  ======== updateThresholds ========
 */
static void updateThresholds(int16_t thresholdHigh, int16_t thresholdLow)
{
    if (thresholdHigh < currentThresholdHigh)
    {
        setTempUpperLimit(thresholdHigh);
        enableTempUpperLimit();
    }

    if (thresholdLow > currentThresholdLow)
    {
        setTempLowerLimit(thresholdLow);
        enableTempLowerLimit();
    }
}

/*
 *  ======== temperatureEventCb ========
 *
 *  Batmon interrupt triggered on high or low temperature event
 */
static void temperatureEventCb(uint32_t eventMask)
{

    setTempUpperLimit(INVALID_TEMPERATURE_MAX);
    disableTempUpperLimit();

    setTempLowerLimit(INVALID_TEMPERATURE_MIN);
    disableTempLowerLimit();

    /* Walk the notification list and issue any callbacks that have triggered
     * at the current temperature.
     */
    walkNotifyList();

    /* Walk the queue another time to find and set the next set of thresholds.
     * This is faster than making even one extra access to AON_BATMON.
     */
    setNextThresholds();

    /* Clear event flags. They may not immediately clear properly. */
    clearEventFlags();
}

/*
 *  ======== thermalShutdownCallback ========
 *
 *  Callback function for thermal shutdown notify object
 */
static void thermalShutdownCallback(int16_t currentTemperature,
                                    int16_t thresholdTemperature,
                                    uintptr_t clientArg,
                                    Temperature_NotifyObj *notifyObject)
{
    /* Immediately bring the device into reset, and enable the thermal shutdown comparator. */
    TemperatureLPF3_triggerThermalShutdown();
}

/*
 *  ======== Temperature_init ========
 */
void Temperature_init(void)
{
    uint32_t key;

    key = HwiP_disable();

    if (isInitialized == false)
    {
        BatMonSupportLPF3_init();
        BatMonSupportLPF3_registerTemperatureCb(PMUD_EVENT_TEMP_BELOW_LL | PMUD_EVENT_TEMP_OVER_UL, temperatureEventCb);

        /* Wait first measurement is ready to prevent Temperature_getTemperature
         * returning an invalid value
         */
        while ((HWREG(PMUD_BASE + PMUD_O_TEMPUPD) & PMUD_TEMPUPD_STA_M) != PMUD_TEMPUPD_STA_M) {}

        isInitialized = true;
    }

    HwiP_restore(key);
}

/*
 *  ======== Temperature_getTemperature ========
 */
int16_t Temperature_getTemperature(void)
{
    /* The temperature on Low Power F3 devices is stored in a 32-bit register
     * containing a 9-bit signed integer part and a 2-bit unsigned fractional
     * part. The fractional part is discarded from the returned result, but is
     * used in the correction-calculation below.
     */

    int32_t temperature = HWREG(PMUD_BASE + PMUD_O_TEMP);

    /* Mask and shift the integer and fractional parts of the temperature */
    temperature = (temperature & (PMUD_TEMP_INT_M | PMUD_TEMP_FRAC_M)) >> PMUD_TEMP_FRAC_S;

    /* Perform sign extension */
    temperature = (temperature << (32 - (PMUD_TEMP_INT_W + PMUD_TEMP_FRAC_W))) >>
                  (32 - (PMUD_TEMP_INT_W + PMUD_TEMP_FRAC_W));

    /* Correct for temperature-dependent error in BATMON sensor */
    temperature = TemperatureLPF3_scaleToRealTemperature(temperature);

    return temperature;
}

/*
 *  ======== Temperature_registerNotifyHigh ========
 */
int_fast16_t Temperature_registerNotifyHigh(Temperature_NotifyObj *notifyObject,
                                            int16_t thresholdHigh,
                                            Temperature_NotifyFxn notifyFxn,
                                            uintptr_t clientArg)
{
    uint32_t key;

    key = HwiP_disable();

    notifyObject->thresholdHigh = thresholdHigh;
    notifyObject->thresholdLow  = INVALID_TEMPERATURE_MIN;
    notifyObject->notifyFxn     = notifyFxn;
    notifyObject->clientArg     = clientArg;

    if (notifyObject->isRegistered == false)
    {
        /* Add the notification to the end of the list.
         * There is the implicit assumption that the notification is not already
         * in the list. Otherwise the list linkage will be corrupted.
         */
        List_put(&notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return Temperature_STATUS_SUCCESS;
}

/*
 *  ======== Temperature_registerNotifyLow ========
 */
int_fast16_t Temperature_registerNotifyLow(Temperature_NotifyObj *notifyObject,
                                           int16_t thresholdLow,
                                           Temperature_NotifyFxn notifyFxn,
                                           uintptr_t clientArg)
{
    uint32_t key;

    key = HwiP_disable();

    notifyObject->thresholdHigh = INVALID_TEMPERATURE_MAX;
    notifyObject->thresholdLow  = thresholdLow;
    notifyObject->notifyFxn     = notifyFxn;
    notifyObject->clientArg     = clientArg;

    if (notifyObject->isRegistered == false)
    {
        /* Add the notification to the end of the list.
         * There is the implicit assumption that the notification is not already
         * in the list. Otherwise the list linkage will be corrupted.
         */
        List_put(&notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return Temperature_STATUS_SUCCESS;
}

/*
 *  ======== Temperature_registerNotifyRange ========
 */
int_fast16_t Temperature_registerNotifyRange(Temperature_NotifyObj *notifyObject,
                                             int16_t thresholdHigh,
                                             int16_t thresholdLow,
                                             Temperature_NotifyFxn notifyFxn,
                                             uintptr_t clientArg)
{
    uint32_t key;

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
        List_put(&notificationList, &notifyObject->link);

        notifyObject->isRegistered = true;
    }

    updateThresholds(notifyObject->thresholdHigh, notifyObject->thresholdLow);

    HwiP_restore(key);

    return Temperature_STATUS_SUCCESS;
}

/*
 *  ======== Temperature_unregisterNotify ========
 */
int_fast16_t Temperature_unregisterNotify(Temperature_NotifyObj *notifyObject)
{
    uint32_t key;

    key = HwiP_disable();

    if (notifyObject->isRegistered == true)
    {
        /* Remove the notification from the list */
        List_remove(&notificationList, &(notifyObject->link));

        notifyObject->isRegistered = false;
    }

    /* Find the next set of thresholds and update the registers */
    setNextThresholds();

    HwiP_restore(key);

    return Temperature_STATUS_SUCCESS;
}

/*
 *  ======== TemperatureLPF3_enableTSDMonitoring ========
 */
void TemperatureLPF3_enableTSDMonitoring(int16_t shutdownThreshold)
{
    /*
     * Register a notify object on threshold value, that calls the thermal shutdown callback.
     * The callback will immediately trigger a thermal shutdown
     */
    Temperature_registerNotifyHigh(&thermalShutdown, shutdownThreshold, thermalShutdownCallback, (uintptr_t)NULL);
}

/*
 *  ======== TemperatureLPF3_disableTSDMonitoring ========
 */
void TemperatureLPF3_disableTSDMonitoring(void)
{
    /*
     * Unregister the thermal shutdown notify-object.
     */
    Temperature_unregisterNotify(&thermalShutdown);
}

/*
 *  ======== TemperatureLPF3_triggerThermalShutdown ========
 */
void TemperatureLPF3_triggerThermalShutdown(void)
{
    HWREG(PMCTL_BASE + PMCTL_O_RSTCTL) |= PMCTL_RSTCTL_TSDEN_EN;
}

/*
 *  ======== TemperatureLPF3_scaleToRealTemperature ========
 */
static int16_t TemperatureLPF3_scaleToRealTemperature(int32_t temperature)
{
    /* Due to a non-linearity in the BATMON temperature sensor, the temperature
     * returned by the hardware should be adjusted to attain a more accurate
     * temperature. The transfer function from batmon temperature to real
     * temperature is as follows:
     *
     * T_real(T) = p1*T + p0
     *
     * The coefficients account for the input temperature containing two
     * fractional bits, and the adjusted temperature will also contain two
     * fractional bits.
     *
     * p1 = 1.04348435
     * p0 = -6.71741627
     *
     * Scaled by 2^20 to fixed-point integers:
     *
     * p1 = 1094173
     * p0 = -7043721
     */

    int32_t p1 = 1094172;
    int32_t p0 = -7043721;

    temperature = (temperature * p1) + p0;

    /* Round to nearest integer. Divide by 2^22 to bring scaled
     * temperature with two fractional bits down to temperature with no
     * fractional bits. Do division instead of right-shift, since temperature
     * is a signed integer.
     */
    if (temperature > 0)
    {
        temperature = (temperature + (1 << 21)) / (1 << 22);
    }
    else
    {
        temperature = (temperature - (1 << 21)) / (1 << 22);
    }

    return temperature;
}

static int16_t TemperatureLPF3_scaleFromRealTemperature(int32_t temperature)
{
    /* Due to a non-linearity in the BATMON temperature sensor, the temperature
     * programmed in the hardware should be adjusted to reflect a more accruate
     * temperature. The transfer function accurate temperature to BATMON
     * temperature is as follows:
     *
     * T_batmon(T) = p1*T + p0
     *
     * p1 = 0.95832774109
     * p0 = 6.43748636
     *
     * Scaled by 2^20 to fixed-point integers:
     *
     * p1 = 1004879
     * p0 = 6750194
     */
    int32_t p1 = 1004879;
    int32_t p0 = 6750194;

    /* Add two fractional bits */
    temperature *= 4;

    /* Bring temperature from real temperature to BATMON temperature */
    temperature = (temperature * p1) + p0;

    /* Round to nearest integer. Divide by 2^22 to bring scaled
     * temperature with two fractional bits down to temperature with no
     * fractional bits. Do division instead of right-shift, since temperature
     * is a signed integer.
     */
    if (temperature > 0)
    {
        temperature = (temperature + (1 << 21)) / (1 << 22);
    }
    else
    {
        temperature = (temperature - (1 << 21)) / (1 << 22);
    }

    /* Limit the temperature to valid BATMON temperatures */
    if (temperature > BATMON_TEMPERATURE_MAX)
    {
        temperature = BATMON_TEMPERATURE_MAX;
    }
    else if (temperature < BATMON_TEMPERATURE_MIN)
    {
        temperature = BATMON_TEMPERATURE_MIN;
    }

    return temperature;
}