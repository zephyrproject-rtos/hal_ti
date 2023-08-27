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
/*!****************************************************************************
 *  @file       BatteryMonitor.h
 *
 *  @brief      Battery Monitor driver
 *
 *  @anchor ti_drivers_BatteryMonitor_Overview
 *  # Overview #
 *  The Battery Monitor driver provides services related to measuring and
 *  reacting to the current supply voltage of the device, and changes to it.
 *
 *  The two main services provided are:
 *      - Getting the current supply voltage
 *      - Providing notification callbacks when the supply voltage changes
 *
 *  @anchor ti_drivers_BatteryMonitor_Usage
 *  # Usage #
 *
 *  ## Initialisation #
 *  Unlike most drivers, there is only a single instance of the Battery Monitor
 *  driver that is always available once #BatteryMonitor_init() is called.
 *  #BatteryMonitor_init() should be called once before using other Battery
 *  Monitor driver APIs. Subsequent #BatteryMonitor_init() calls will have no
 *  effect.
 *
 *  ## Getting the Current Supply Voltage #
 *  The driver can read the current supply voltage and return it. The resolution
 *  is device-specific (see device-specific Battery Monitor documentation), but
 *  the voltage will always be encoded as an unsigned integer in millivolts
 *  (mV).
 *
 *  ## Notifications #
 *  The Battery Monitor driver can notify the application when the supply
 *  voltage crosses an application-defined threshold.
 *
 *  There are three default use cases for this:
 *      - High threshold.
 *        The application will receive a notification callback when
 *        currentVoltage >= thresholdHigh.
 *      - Low threshold.
 *        The application will receive a notification callback when
 *        currentVoltage <= thresholdLow.
 *      - Range threshold.
 *        The application will receive a notification callback when
 *        currentVoltage >= thresholdHigh || currentVoltage <=
 *        thresholdLow. This setup addresses use cases
 *        where a notification is required when the supply voltage changes by a
 *        certain amount regardless of whether it is up or down.
 *
 *  ### Registering Notifications
 *  There are three functions that register a notification for the application:
 *      - #BatteryMonitor_registerNotifyHigh()
 *      - #BatteryMonitor_registerNotifyLow()
 *      - #BatteryMonitor_registerNotifyRange()
 *
 *  Multiple notifications may be registered. The different parts of the
 *  application and drivers that need to respond to a supply voltage change do
 *  not need to know of one another.
 *  Each notification must have its own #BatteryMonitor_NotifyObj and must be
 *  registered individually.
 *
 *  ### Notification Callbacks
 *  Once the supply voltage crosses the smallest "high threshold" or largest
 *  "low threshold amongst the registered notifications, the driver will
 *  iterate over the entire list of registered notification and check which
 *  ones have triggered. Notifications that have triggered are removed from the
 *  list of registered notifications before their callback function is invoked.
 *
 *  If an application wishes to re-register a notification that just triggered
 *  and was unregistered, it may register it again from within the notification
 *  callback or another context.
 *
 *  It is possible to determine whether the high or low threshold triggered
 *  the notification callback as follows:
 *      - currentVoltage <= thresholdVoltage: Low threshold triggered
 *      - currentVoltage >= thresholdVoltage: High threshold triggered
 *  This information is only reasonably useful when registering a notification
 *  with both a high and low threshold using
 *  #BatteryMonitor_registerNotifyRange(). Even then, the expected basic use
 *  case only cares about the current voltage and adding an offset to it when
 *  registering the notification again.
 *
 *  ### Unregistering Notifications
 *  Registered notifications are unregistered in two ways:
 *      - Automatically when a notification triggers
 *      - By calling #BatteryMonitor_unregisterNotify()
 *
 *  Unregistered notifications may be registered again at any time.
 *
 *  @anchor ti_drivers_BatteryMonitor_Synopsis
 *  # Synopsis #
 *  @anchor ti_drivers_BatteryMonitor_Synopsis_Code
 *  @code
 *  #include <ti/drivers/BatteryMonitor.h>
 *
 *  #define WINDOW_DELTA_MILLIVOLT 300
 *
 *  BatteryMonitor_init();
 *
 *  currentVoltage = BatteryMonitor_getVoltage();
 *
 *  result = BatteryMonitor_registerNotifyRange(&notifyObject,
 *                                              currentVoltage + WINDOW_DELTA_MILLIVOLT,
 *                                              currentVoltage - WINDOW_DELTA_MILLIVOLT,
 *                                              myNotifyFxn,
 *                                              clientArg);
 *  @endcode
 *
 *  @anchor ti_drivers_BatteryMonitor_Examples
 *  # Examples #
 *
 *  ## Register a High Threshold Notification #
 *
 *  @code
 *
 *  // The notification will trigger when the supply voltage reaches 3.5V
 *  #define THRESHOLD_CUTOFF_MILLIVOLT 3500
 *
 *  #include <ti/drivers/BatteryMonitor.h>
 *
 *  void thresholdNotifyFxn(uint16_t currentVoltage,
 *                          uint16_t thresholdVoltage,
 *                          uintptr_t clientArg,
 *                          BatteryMonitor_NotifyObj *notifyObject) {
 *     // Post a semaphore, set a flag, or otherwise act upon the voltage change.
 *  }
 *
 *  ...
 *
 *  // Initialize the Battery Monitor driver and register a notification.
 *
 *  BatteryMonitor_init();
 *
 *  int_fast16_t status = BatteryMonitor_registerNotifyHigh(notifyObject,
 *                                                          THRESHOLD_CUTOFF_MILLIVOLT,
 *                                                          thresholdNotifyFxn,
 *                                                          NULL);
 *
 *  if (status != BatteryMonitor_STATUS_SUCCESS) {
 *      // Handle error
 *  }
 *
 *  @endcode
 *
 *  ## Register a Range Threshold Notification and re-register in Callback #
 *
 *  @code
 *
 *  #define THRESHOLD_DELTA_MILLIVOLT 300
 *
 *  #include <ti/drivers/BatteryMonitor.h>
 *
 *
 *  void deltaNotificationFxn(uint16_t currentVoltage,
 *                            uint16_t thresholdVoltage,
 *                            uintptr_t clientArg,
 *                            BatteryMonitor_NotifyObj *notifyObject) {
 *      int_fast16_t status;
 *
 *      status = BatteryMonitor_registerNotifyRange(notifyObject,
 *                                          currentVoltage + THRESHOLD_DELTA_MILLIVOLT,
 *                                          currentVoltage - THRESHOLD_DELTA_MILLIVOLT,
 *                                          deltaNotificationFxn,
 *                                          clientArg);
 *
 *      if (status != BatteryMonitor_STATUS_SUCCESS) {
 *          while(1);
 *      }
 *  }
 *
 *   ...
 *
 *  // Initialize the Battery Monitor driver and register a notification.
 *
 *  BatteryMonitor_init();
 *
 *  BatteryMonitor_NotifyObj rangeNotifyObject;
 *
 *  uint16_t currentVoltage = BatteryMonitor_getVoltage();
 *
 *  int_fast16_t status = BatteryMonitor_registerNotifyRange(6rangeNotifyObject,
 *                                                        currentVoltage + THRESHOLD_DELTA_MILLIVOLT,
 *                                                        currentVoltage - THRESHOLD_DELTA_MILLIVOLT,
 *                                                        deltaNotificationFxn,
 *                                                        (uintptr_t)NULL);
 *  @endcode
 */

#ifndef ti_drivers_BatteryMonitor__include
#define ti_drivers_BatteryMonitor__include

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ti/drivers/utils/List.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Common Battery Monitor status code reservation offset.
 * Battery Monitor driver implementations should offset status codes with
 * BatteryMonitor_STATUS_RESERVED growing negatively.
 *
 * Example implementation specific status codes:
 * @code
 * #define BatteryMonitorXYZ_STATUS_ERROR0    BatteryMonitor_STATUS_RESERVED - 0
 * #define BatteryMonitorXYZ_STATUS_ERROR1    BatteryMonitor_STATUS_RESERVED - 1
 * #define BatteryMonitorXYZ_STATUS_ERROR2    BatteryMonitor_STATUS_RESERVED - 2
 * @endcode
 */
#define BatteryMonitor_STATUS_RESERVED (-32)

/*!
 * @brief   Successful status code.
 *
 * Functions return BatteryMonitor_STATUS_SUCCESS if the function was executed
 * successfully.
 */
#define BatteryMonitor_STATUS_SUCCESS (0)

/*!
 * @brief   Generic error status code.
 *
 * Functions return BatteryMonitor_STATUS_ERROR if the function was not executed
 * successfully.
 */
#define BatteryMonitor_STATUS_ERROR (-1)

/* @cond NODOC
 *
 * Type declaration for the notification object made separately from the
 * struct definition because of the circular dependency between
 * #BatteryMonitor_NotifyFxn() and #BatteryMonitor_NotifyObj.
 */
typedef struct BatteryMonitor_NotifyObj BatteryMonitor_NotifyObj;
/* @endcond */

/*!
 *  @brief Function prototype for a notification callback.
 *
 *  @param [in]     currentVoltage      Current supply voltage in millivolts
 *
 *  @param [in]     thresholdVoltage    Voltage threshold in millivolts that
 *                                      caused this notification callback.
 *
 *  @param [in]     clientArg           Argument provided by the application
 *                                      during registration.
 *
 *  @param [in/out] notifyObject        Pointer to notification object that was
 *                                      registered previously. This may be used
 *                                      to register the notification again with
 *                                      updated inputs from within the
 *                                      notification callback.
 */
typedef void (*BatteryMonitor_NotifyFxn)(uint16_t currentVoltage,
                                         uint16_t thresholdVoltage,
                                         uintptr_t clientArg,
                                         BatteryMonitor_NotifyObj *notifyObject);

/*!
 *  @brief Battery Monitor notify object structure.
 *
 *  This structure specification is for internal use. Notification clients must
 *  pre-allocate a notify object when registering for a notification;
 *  #BatteryMonitor_registerNotifyHigh(), #BatteryMonitor_registerNotifyLow(),
 *  or #BatteryMonitor_registerNotifyRange() will take care initializing the
 *  internal elements appropriately.
 */
struct BatteryMonitor_NotifyObj
{
    List_Elem link;                     /*!< For placing on the notify list */
    BatteryMonitor_NotifyFxn notifyFxn; /*!< Application callback function */
    uint16_t thresholdHigh;             /*!< High threshold in millivolts */
    uint16_t thresholdLow;              /*!< Low threshold in millivolts */
    uintptr_t clientArg;                /*!< Application provided arg */
    bool isRegistered;                  /*!< Is the notification active */
};

/*!
 *  @brief This function initializes the Battery Monitor driver.
 *
 *  This function initializes the internal state of the Battery Monitor driver.
 *  It must be called before calling any other Battery Monitor functions.
 *  Subsequent calls to this function have no effect.
 */
void BatteryMonitor_init(void);

/*!
 *  @brief Gets the current supply voltage in millivolts.
 *
 *  @return Current supply voltage in millivolts
 */
uint16_t BatteryMonitor_getVoltage(void);

/*!
 *  @brief Registers a notification with a high threshold.
 *
 *  This function registers a Battery Monitor notification with a high
 *  threshold. Once the supply voltage rises above @c thresholdHigh,
 *  the notification is automatically unregistered and function @c notifyFxn is
 *  called.
 *
 *  @param  notifyObject        Structure to be initialized. After returning,
 *                              it will contain the data necessary to issue a
 *                              notification callback. The memory of the
 *                              structure must persist while the notification
 *                              is registered.
 *
 *  @param  [in] thresholdHigh  Threshold supply voltage in millivolts
 *
 *  @param  [in] notifyFxn      Callback function that is called once the
 *                              supply voltage rises above @c thresholdHigh.
 *
 *  @param  [in] clientArg      Application-specified argument
 *
 *  @retval #BatteryMonitor_STATUS_SUCCESS The notification was successfully
 *                                         registered.
 *  @retval #BatteryMonitor_STATUS_ERROR   There was an error during
 *                                         registration.
 *
 *  @pre BatteryMonitor_init() called
 */
int_fast16_t BatteryMonitor_registerNotifyHigh(BatteryMonitor_NotifyObj *notifyObject,
                                               uint16_t thresholdHigh,
                                               BatteryMonitor_NotifyFxn notifyFxn,
                                               uintptr_t clientArg);

/*!
 *  @brief Registers a notification with a low threshold.
 *
 *  This function registers a Battery Monitor notification with a low threshold.
 *  Once the supply voltage falls below @c thresholdLow, the notification is
 *  automatically unregistered and function @c notifyFxn is called.
 *
 *  @param  notifyObject        Structure to be initialized. After returning,
 *                              it will contain the data necessary to issue a
 *                              notification callback. The memory of the
 *                              structure must persist while the notification
 *                              is registered.
 *
 *  @param  [in] thresholdLow   Threshold supply voltage in millivolts
 *
 *  @param  [in] notifyFxn      Callback function that is called once the
 *                              supply voltage falls below @c thresholdLow.
 *
 *  @param  [in] clientArg      Application-specified argument
 *
 *  @retval #BatteryMonitor_STATUS_SUCCESS The notification was successfully
 *                                         registered.
 *  @retval #BatteryMonitor_STATUS_ERROR   There was an error during registration.
 *
 *  @pre BatteryMonitor_init() called
 */
int_fast16_t BatteryMonitor_registerNotifyLow(BatteryMonitor_NotifyObj *notifyObject,
                                              uint16_t thresholdLow,
                                              BatteryMonitor_NotifyFxn notifyFxn,
                                              uintptr_t clientArg);

/*!
 *  @brief Registers a notification with both a high and low threshold.
 *
 *  This function registers a Battery Monitor notification with a high and low
 *  threshold. Once the supply voltage rises above @c thresholdHigh or
 *  falls below @c thresholdLow, the notification is automatically unregistered
 *  and function @c notifyFxn is called.
 *
 *  @param  notifyObject        Structure to be initialized. After returning,
 *                              it will contain the data necessary to issue a
 *                              notification callback. The memory of the
 *                              structure must persist while the notification
 *                              is registered.
 *
 *  @param  [in] thresholdHigh  High threshold supply voltage in millivolts
 *
 *  @param  [in] thresholdLow   Low threshold supply voltage in millivolts
 *
 *  @param  [in] notifyFxn      Callback function that is called once the
 *                              supply voltage falls below
 *                              @c thresholdLow, or rises above
 *                              @c thresholdHigh.
 *
 *  @param  [in] clientArg      Application-specified argument
 *
 *  @retval #BatteryMonitor_STATUS_SUCCESS The notification was successfully
 *                                         registered
 *  @retval #BatteryMonitor_STATUS_ERROR   There was an error during
 *                                         registration
 *
 *  @pre BatteryMonitor_init() called
 */
int_fast16_t BatteryMonitor_registerNotifyRange(BatteryMonitor_NotifyObj *notifyObject,
                                                uint16_t thresholdHigh,
                                                uint16_t thresholdLow,
                                                BatteryMonitor_NotifyFxn notifyFxn,
                                                uintptr_t clientArg);

/*!
 *  @brief Unregisters a currently registered notification.
 *
 *  This function unregisters a currently registered notification.
 *
 *  @param  notifyObject    Notification to unregister.
 *
 *  @retval #BatteryMonitor_STATUS_SUCCESS The notification was successfully
 *                                         unregistered.
 *  @retval #BatteryMonitor_STATUS_ERROR   There was an error during
 *                                         unregistration.
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyHigh(),
 *       #BatteryMonitor_registerNotifyLow(), or #BatteryMonitor_registerNotifyRange()
 */
int_fast16_t BatteryMonitor_unregisterNotify(BatteryMonitor_NotifyObj *notifyObject);

/*!
 *  @brief Get the high threshold of a notification.
 *
 *  @warning This function should not be called on a @c notifyObject registered
 *  with #BatteryMonitor_registerNotifyLow(). The high threshold value returned
 *  in that case will be a device-specific invalid voltage.
 *
 *  @param  notifyObject    Notification to get the high threshold of.
 *
 *  @return High threshold in millivolts.
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyHigh(),
 *       or #BatteryMonitor_registerNotifyRange()
 */
static inline uint16_t BatteryMonitor_getThresholdHigh(BatteryMonitor_NotifyObj *notifyObject)
{
    return notifyObject->thresholdHigh;
}

/*!
 *  @brief Get the low threshold of a notification.
 *
 *  @warning This function should not be called on a @c notifyObject registered
 *  with #BatteryMonitor_registerNotifyHigh(). The low threshold value returned
 *  in that case will be a device-specific invalid voltage.
 *
 *  @param  notifyObject    Notification to get the low threshold of.
 *
 *  @return Low threshold in millivolts.
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyLow(),
 *       or #BatteryMonitor_registerNotifyRange()
 */
static inline uint16_t BatteryMonitor_getThresholdLow(BatteryMonitor_NotifyObj *notifyObject)
{
    return notifyObject->thresholdLow;
}

/*!
 *  @brief Get the high and low threshold of a notification.
 *
 *  @warning This function should not be called on a @c notifyObject registered
 *  with #BatteryMonitor_registerNotifyLow() or
 *  #BatteryMonitor_registerNotifyHigh(). The unconfigured threshold value
 *  returned in that case will be a device-specific invalid voltage.
 *
 *  @param  notifyObject            Notification to get the high and low threshold
 *                                  of.
 *
 *  @param [out]    thresholdHigh   High threshold value in millivolts written
 *                                  back by this function.
 *
 *  @param [out]    thresholdLow    Low threshold value in millivolts written
 *                                  back by this function.
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyRange()
 */
static inline void BatteryMonitor_getThresholdRange(BatteryMonitor_NotifyObj *notifyObject,
                                                    uint16_t *thresholdHigh,
                                                    uint16_t *thresholdLow)
{
    *thresholdHigh = notifyObject->thresholdHigh;
    *thresholdLow  = notifyObject->thresholdLow;
}

/*!
 *  @brief Get the application-provided clientArg of a notification.
 *
 *  @param  notifyObject    Notification to get the clientArg of.
 *
 *  @return The clientArg provided during registration.
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyHigh(),
 *       #BatteryMonitor_registerNotifyLow(), or #BatteryMonitor_registerNotifyRange()
 */
static inline uintptr_t BatteryMonitor_getClientArg(BatteryMonitor_NotifyObj *notifyObject)
{
    return notifyObject->clientArg;
}

/*!
 *  @brief Get the notifyFxn provided during registration.
 *
 *  @param  notifyObject    Notification to get the notifyFxn of.
 *
 *  @return The notifyFxn provided during registration
 *
 *  @pre Register @c notifyObject with #BatteryMonitor_registerNotifyHigh(),
 *       #BatteryMonitor_registerNotifyLow(), or #BatteryMonitor_registerNotifyRange()
 */
static inline BatteryMonitor_NotifyFxn BatteryMonitor_getNotifyFxn(BatteryMonitor_NotifyObj *notifyObject)
{
    return notifyObject->notifyFxn;
}

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_BatteryMonitor__include */
