/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
/*!*****************************************************************************
 *  @file       GPTimerWFF3.h
 *  @brief      GPTimer driver implementation for Wi-Fi F3 devices
 *
 *  @anchor ti_drivers_GPTimerWFF3_Overview
 *  # Overview #
 *  The GPTimer driver allows you to measure elapsed time with simple and
 *  portable APIs. It also allows for asynchronous callbacks after a
 *  certain amount of time has elapsed.
 *  In addition the driver supports APIs for both capture and compare
 *  of IO signals muxable to the four channels of each GPT peripheral
 *  instance. The channel capture functionality can be used to measure period
 *  and duty cycle of an input signal. The channel compare functionality can
 *  be used for generating PWM signals.
 *
 *  The GPTimer driver also handles the general purpose timer resource
 *  allocation. For each driver that requires use of a general purpose timer, it
 *  calls #GPTimerWFF3_open() to occupy the specified timer, and calls
 *  #GPTimerWFF3_close() to release the occupied timer resource.
 *
 *  @anchor ti_drivers_GPTimerWFF3_PeripheralProperties
 *  # GPT peripheral properties #
 *  The table below lists supported counter widths for each peripheral instance
 *  number on available device types.
 *  The timer counter clock is sourced from the internal prescaler stage which
 *  has the system clock as input.
 *  The prescaler can be configured to divide the input system clock,
 *  effectively extending the maximal time interval for the timer counter while
 *  reducing the timer resolution.
 *
 * | Device type   | GPT0    | GPT1    |
 * |---------------|---------|---------|
 * | CC35xx        | 32 bits | 32 bits |

 *
 *  @anchor ti_drivers_GPTimerWFF3_CounterModes
 *  # Counter Modes #
 *  The GPTimer driver supports the following timer counter modes:
 *    - Oneshot mode counting upwards. When the counter reaches the target
 *      value, the timer is stopped automatically and the TGT interrupt status
 *      flag (#GPTimerWFF3_INT_TGT) is set.
 *    - Periodic mode counting upwards. When the counter reaches target value it
 *      wraps and restarts counting from 0 again. The TGT interrupt status flag
 *      is set each time the target value is reached. The ZERO interrupt status
 *      flag (#GPTimerWFF3_INT_ZERO) is set each time the counter restarts
 *      from 0.
 *    - Periodic mode counting upwards/downwards. When the counter reaches
 *      target value while counting upwards the TGT interrupt flag is set and it
 *      starts counting downwards to 0. When 0 is reached the ZERO interrupt
 *      status flag is set and the sequence is repeated.
 *
 *  @anchor ti_drivers_GPTimerWFF3_UnsupportedFeatures
 *  # GPT peripheral features not supported by the GPTimer driver #
 *  - Channel input from the event fabric is not supported
 *  - Channel output dead band control is not supported
 *  - Use of channel input filter is not supported
 *  - DMA usage is not supported
 *  - ADC trigger is not supported
 *  - QDEC mode where the timer acts as a quadrature decoder is not supported
 *  - Timer synchronization is not supported
 *  - IR generation is not supported
 *  - Brushless DC motor control is not supported
 *  - Fault and Park is not supported
 *  - Prescaler counter clock sourced from events is not supported
 *
 *  @anchor ti_drivers_GPTimerWFF3_PowerManagement
 *  # Power Management #
 *  The power management framework will try to put the device into the most
 *  power efficient mode whenever possible. Please see the technical reference
 *  manual for further details on each power mode.
 *
 *  The GPTimer driver will set constraints on disallowed power modes when
 *  needed, removing the need for the application to handle this.
 *  The following statements are valid:
 *    - After #GPTimerWFF3_open():
 *        The device is still allowed to enter Sleep. When the device is
 *        active, the corresponding GPT peripheral will be enabled and clocked.
 *        Note that a configured counter target and configured channels will not
 *        be retained when going in and out of Sleep.
 *        The counter target is set by the functions
 *        #GPTimerWFF3_setInitialCounterTarget() and
 *        #GPTimerWFF3_setNextCounterTarget().
 *    - After #GPTimerWFF3_start():
 *        The device will only go to Idle power mode since the system clock is
 *        needed for timer operation.
 *    - After #GPTimerWFF3_stop():
 *        The device is still allowed to enter Sleep. When the device is
 *        active, the corresponding GPT peripheral will be enabled and clocked.
 *    - After #GPTimerWFF3_close():
 *        The underlying GPT peripherals bus clock is turned off. The device is
 *        allowed to enter Sleep.
 *
 *  @anchor ti_drivers_GPTimerWFF3_Accuracy
 *  # Accuracy #
 *  The timer clock of the GPT peripheral is dependent on the system clock.
 *
 *  @anchor ti_drivers_GPTimerWFF3_Usage
 *  # Usage #
 *
 *  This documentation provides some basic @ref ti_drivers_GPTimerWFF3_Examples
 *  "examples" in the form of commented code fragments.
 *
 *
 *  <hr>
 *  @anchor ti_drivers_GPTimerWFF3_Examples
 *  # Examples
 *
 *  @note
 *  <b>The following examples are intended for reference only and are not
 *  intended for application use.</b>
 *
 *  @li @ref ti_drivers_GPTimerWFF3_Example_periodic "Periodic timer"
 *  @li @ref ti_drivers_GPTimerWFF3_Example_output "Output signal generation"
 *
 *
 *  @anchor ti_drivers_GPTimerWFF3_Example_periodic
 *  ## Periodic timer example##
 *  The code example below will generate an interrupt using the GPTimer every
 *  1 ms.
 *  Note that when a count-up counter mode is used, the number of counter ticks
 *  to reach the target value equals target value + 1.
 *
 *  @anchor ti_drivers_GPTimerWFF3_Code
 *  @code
 *  #include <ti/drivers/timer/GPTimerWFF3.h>
 *
 *  void timerCallback(GPTimerWFF3_Handle gptHandle, GPTimerWFF3_IntMask interruptMask) {
 *      // interrupt callback code goes here. Minimize processing in interrupt.
 *  }
 *
 *  void* taskFxn(void* arg) {
 *
 *    GPTimerWFF3_Handle gptHandle;
 *    GPTimerWFF3_Params params;
 *    uint32_t counterTarget;
 *
 *    // Initialize parameters and assign callback function to be used
 *    GPTimerWFF3_Params_init(&params);
 *    params.hwiCallbackFxn = timerCallback;
 *
 *    // Open driver
 *    gptHandle = GPTimerWFF3_open(0, &params);
 *
 *    // Set counter target
 *    counterTarget = 40000 - 1;  // 1 ms with a counter clock of 40 MHz
 *    GPTimerWFF3_setInitialCounterTarget(gptHandle, counterTarget, true);
 *
 *    // Enable counter target interrupt
 *    GPTimerWFF3_enableInterrupt(gptHandle, GPTimerWFF3_INT_TGT);
 *
 *    // Start counter in count-up-periodic mode
 *    GPTimerWFF3_start(gptHandle, GPTimerWFF3_CTL_MODE_UP_PER);
 *
 *    // Generate counter target interrupt every 1 ms forever
 *    while(1);
 *  }
 *  @endcode
 *
 *
 *  @anchor ti_drivers_GPTimerWFF3_Example_output
 *  ## Output signal generation example##
 *  The code example below will generate an output signal of 32 kHz with a 50 %
 *  duty cycle on channel 2.
 *  With an up/down counter mode, the counter target value determines the signal
 *  period and the value must be set to half the number of the total counter
 *  ticks per signal period.
 *  With a channel action of toggle-on-compare, the channel compare value must
 *  be set to (counter target value)/2 in order to obtain a 50 % duty cycle of
 *  the output signal.
 *  The period of a 32 kHz signal equals 1250 counter ticks when the counter has
 *  a 40 MHz clock.
 *
 *
 *  @code
 *  #include <ti/drivers/timer/GPTimerWFF3.h>
 *
 *  void* taskFxn(void* arg) {
 *
 *    GPTimerWFF3_Handle gptHandle;
 *    GPTimerWFF3_Params params;
 *    uint32_t cntTargetVal = 1250/2;
 *    uint32_t chCompVal    = cntTargetVal/2;
 *
 *    // Configure channel 2 action
 *    GPTimerWFF3_Params_init(&params);
 *    params.channelProperty[2].action = GPTimerWFF3_CH_TOGGLE_ON_COMPARE_PERIODIC;
 *
 *    // Open driver
 *    gptHandle = GPTimerWFF3_open(0, &params);
 *
 *    // Set channel output signal period
 *    GPTimerWFF3_setInitialCounterTarget(gptHandle, cntTargetVal, false);
 *
 *    // Set channel output signal duty cycle
 *    GPTimerWFF3_setInitialChannelCompVal(gptHandle, GPTimerWFF3_CH_NO_2, chCompVal, false);
 *
 *    // Start the GPTimer in up-down-periodic mode
 *    GPTimerWFF3_start(gptHandle, GPTimerWFF3_CTL_MODE_UPDWN_PER);
 *
 *    // Output signal forever
 *    while(1);
 *  }
 *  @endcode
 *
 *
 *  ## Opening the GPTimerWFF3 Driver #
 *
 *  Opening a GPTimerWFFF3 requires four steps:
 *  1.  Create and initialize a #GPTimerWFF3_Params structure.
 *  2.  Set non-default parameter values.
 *  3.  Call #GPTimerWFF3_open(), passing the index of the timer in the
 *      #GPTimerWFF3_Config structure, and the address of the #GPTimerWFF3_Params
 *      structure. The timer instance is specified by the index in the
 *      #GPTimerWFF3_Config structure.
 *  4.  Verify that the timer handle returned by #GPTimerWFF3_open() is non-NULL.
 *      The handle will be used to operate the timer driver instance you just
 *      opened.
 *
 *  <hr>
 *  @anchor ti_drivers_GPTWFF3_Configuration
 *  # Configuration
 *
 *  Refer to the @ref driver_configuration "Driver's Configuration" section
 *  for driver configuration information.
 *  <hr>
 *
 *  ============================================================================
 */

#ifndef ti_drivers_timer_GPTimerWFF3__include
#define ti_drivers_timer_GPTimerWFF3__include

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/GPIO.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_gptimer.h)

#ifdef __cplusplus
extern "C" {
#endif

/* Define for number of channels on the GPT peripheral */
#define NO_OF_GPT_CHANNELS 4

/*!
 *  @brief
 *  Definitions for supported GPTimer channel numbers.
 *
 */
typedef enum
{
    GPTimerWFF3_CH_NO_0 = 0,
    GPTimerWFF3_CH_NO_1 = 1,
    GPTimerWFF3_CH_NO_2 = 2,
    GPTimerWFF3_CH_NO_3 = 3,
} GPTimerWFF3_ChannelNo;

/*!
 *  @brief
 *  Definitions for supported GPTimer channel direction.
 *
 */
typedef enum
{
    GPTimerWFF3_CH_DIR_NONE   = 0,
    GPTimerWFF3_CH_DIR_INPUT  = 1,
    GPTimerWFF3_CH_DIR_OUTPUT = 2,
} GPTimerWFF3_ChannelDir;

/*!
 *  @brief
 *  Definitions for supported GPTimer channel output levels.
 *
 */
typedef enum
{
    GPTimerWFF3_CH_LEVEL_LOW  = GPTIMER_OUTCTL_CLROUT0,
    GPTimerWFF3_CH_LEVEL_HIGH = GPTIMER_OUTCTL_SETOUT0,
} GPTimerWFF3_ChannelLevel;

/*!
 *  @brief
 *  Definitions for supported GPTimer channel input edge.
 *
 */
typedef enum
{
    GPTimerWFF3_CH_EDGE_NONE = GPTIMER_C0CFG_EDGE_NONE,
    GPTimerWFF3_CH_EDGE_RISE = GPTIMER_C0CFG_EDGE_RISE,
    GPTimerWFF3_CH_EDGE_FALL = GPTIMER_C0CFG_EDGE_FALL,
    GPTimerWFF3_CH_EDGE_BOTH = GPTIMER_C0CFG_EDGE_BOTH,
} GPTimerWFF3_ChannelInputEdge;

/*!
 *  @brief
 *  Definitions for supported GPTimer counting modes.
 *  @cond NODOC
 *  New modes must not be added to the below description without
 *  also updating the driver.
 *  @endcond
 *
 */
typedef enum
{
    /*! Disable timer. Updates to counter and events are stopped. */
    GPTimerWFF3_CTL_MODE_DIS       = GPTIMER_CTL_MODE_DIS,
    /*! Count up one-shot. The timer increments from 0 to target value, then
     *  stops and sets MODE to GPTimerWFF3_CTL_MODE_DIS.
     */
    GPTimerWFF3_CTL_MODE_UP_ONCE   = GPTIMER_CTL_MODE_UP_ONCE,
    /*! Count up periodically. The timer increments from 0 to target value,
     * repeatedly.
     */
    GPTimerWFF3_CTL_MODE_UP_PER    = GPTIMER_CTL_MODE_UP_PER,
    /*! Count up and down periodically. The timer counts from 0 to target value
     * and back to 0, repeatedly.
     */
    GPTimerWFF3_CTL_MODE_UPDWN_PER = GPTIMER_CTL_MODE_UPDWN_PER,
} GPTimerWFF3_Mode;

/*!
 *  @brief
 *  Definitions for supported GPTimer interrupts. GPTimerWFF3_IntMask
 *  arguments should be a bit vector containing these definitions.
 */
typedef enum
{
    /*! Timer counter target interrupt */
    GPTimerWFF3_INT_TGT            = 1 << GPTIMER_RIS_TGT_S,
    /*! Timer counter zero interrupt */
    GPTimerWFF3_INT_ZERO           = 1 << GPTIMER_RIS_ZERO_S,
    /*! Timer counter increment/decrement interrupt */
    GPTimerWFF3_INT_COUNTER_CHANGE = 1 << GPTIMER_RIS_CNTRCHNG_S,
    /*! Timer counter direction change interrupt */
    GPTimerWFF3_INT_DIR_CHANGE     = 1 << GPTIMER_RIS_DIRCHNG_S,
    /*! Channel 0 capture or compare interrupt */
    GPTimerWFF3_INT_CH0_CC         = 1 << GPTIMER_RIS_C0CC_S,
    /*! Channel 1 capture or compare interrupt */
    GPTimerWFF3_INT_CH1_CC         = 1 << GPTIMER_RIS_C1CC_S,
    /*! Channel 2 capture or compare interrupt */
    GPTimerWFF3_INT_CH2_CC         = 1 << GPTIMER_RIS_C2CC_S,
    /*! Channel 3 capture or compare interrupt */
    GPTimerWFF3_INT_CH3_CC         = 1 << GPTIMER_RIS_C3CC_S,
} GPTimerWFF3_Interrupt;

/*!
 *  @brief
 *  Definitions for controlling timer debug stall mode
 */
typedef enum
{
    /*! The GPT is not halted when CPU is halted in debug */
    GPTimerWFF3_DEBUG_STALL_OFF       = GPTIMER_EMU_HALT_DIS,
    /*! Halt GPT immediatly when CPU is halted in debug */
    GPTimerWFF3_DEBUG_STALL_IMMEDIATE = (GPTIMER_EMU_HALT_EN | GPTIMER_EMU_CTL_IMMEDIATE),
    /*! Halt GPT when counter equals 0 while CPU is halted in debug */
    GPTimerWFF3_DEBUG_STALL_ON_ZERO   = (GPTIMER_EMU_HALT_EN | GPTIMER_EMU_CTL_ZERCOND),
} GPTimerWFF3_DebugMode;

/*!
 *  @brief
 *  Definitions for which direction the timer counter must have in order to
 *  set channel compare interrupt status flag.
 */
typedef enum
{
    /*! Channel compare interrupt status flag is set on up count and down count. */
    GPTimerWFF3_CH_COMPARE_COUNTER_DIR_BOTH = GPTIMER_CTL_CMPDIR_BOTH,
    /*! Channel compare interrupt status flag is only set on up count */
    GPTimerWFF3_CH_COMPARE_COUNTER_DIR_UP   = GPTIMER_CTL_CMPDIR_UP,
    /*! Channel compare interrupt status flag is only set on down count */
    GPTimerWFF3_CH_COMPARE_COUNTER_DIR_DOWN = GPTIMER_CTL_CMPDIR_DOWN,
} GPTimerWFF3_ChannelCmpDir;

/*!
 *  @brief
 *  Definitions for supported GPTimer channel actions.
 *
 */
typedef enum
{
    /*! Channel disabled */
    GPTimerWFF3_CH_DISABLE = GPTIMER_C0CFG_CCACT_DIS,

    /***************************************************************************
     *                        Channel compare actions.                         *
     *                                                                         *
     * The following list of channel compare actions will force the channel to *
     * be configured as an output.                                             *
     ***************************************************************************/
    /*! Toggle on compare repeatedly.
     *
     * Toggle channel output when the timer counter equals the compare value set
     * by either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     */
    GPTimerWFF3_CH_TOGGLE_ON_COMPARE_PERIODIC = GPTIMER_C0CFG_CCACT_TGL_ON_CMP,

    /*! Toggle on compare, and then disable channel.
     *
     * Toggle channel output when the timer counter equals the compare value set
     * by #GPTimerWFF3_setInitialChannelCompVal().
     */
    GPTimerWFF3_CH_TOGGLE_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_TGL_ON_CMP_DIS,

    /*! Set on compare repeatedly.
     *
     * Set channel output when the timer counter equals the compare value set by
     * either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     */
    GPTimerWFF3_CH_SET_ON_COMPARE_PERIODIC = GPTIMER_C0CFG_CCACT_SET_ON_CMP,

    /*! Set on compare, and then disable channel.
     *
     * Set channel output when the timer counter equals the compare value set by
     * #GPTimerWFF3_setInitialChannelCompVal().
     */
    GPTimerWFF3_CH_SET_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_SET_ON_CMP_DIS,

    /*! Clear on compare repeatedly.
     *
     * Clear channel output when the timer counter equals the compare value set
     * by either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     */
    GPTimerWFF3_CH_CLEAR_ON_COMPARE_PERIODIC = GPTIMER_C0CFG_CCACT_CLR_ON_CMP,

    /*! Clear on compare, and then disable channel.
     *
     * Clear channel output when the timer counter equals the compare value set
     * by #GPTimerWFF3_setInitialChannelCompVal().
     */
    GPTimerWFF3_CH_CLEAR_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_CLR_ON_CMP_DIS,

    /*! Set on zero, toggle on compare repeatedly.
     *
     * Set channel output when timer counter value equals zero.
     * Toggle channel output when the timer counter equals the compare value set
     * by either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     */
    GPTimerWFF3_CH_SET_ON_0_TOGGLE_ON_CMP_PERIODIC = GPTIMER_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP,

    /*! Set on zero, toggle on compare, and then disable channel.
     *
     * Set channel output when timer counter equals zero.
     * Toggle channel output when the timer counter equals the compare value set
     * by #GPTimerWFF3_setInitialChannelCompVal().
     */
    GPTimerWFF3_CH_SET_ON_0_TOGGLE_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_SET_ON_0_TGL_ON_CMP_DIS,

    /*! Clear on zero, toggle on compare repeatedly.
     *
     * Clear channel output when timer counter equals zero.
     * Toggle channel output when the timer counter equals the compare value set
     * by either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     */
    GPTimerWFF3_CH_CLR_ON_0_TOGGLE_ON_COMPARE_PERIODIC = GPTIMER_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP,

    /*! Clear on zero, toggle on compare, and then disable channel.
     *
     * Clear channel output when timer counter equals zero.
     * Toggle channel output when the timer counter equals the compare value set
     * by #GPTimerWFF3_setInitialChannelCompVal().
     */
    GPTimerWFF3_CH_CLR_ON_0_TOGGLE_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_CLR_ON_0_TGL_ON_CMP_DIS,

    /*! Pulse on compare repeatedly.
     *
     * Pulse channel output when the timer counter equals the compare value set
     * by either #GPTimerWFF3_setInitialChannelCompVal() or
     * #GPTimerWFF3_setNextChannelCompVal().
     * The channel output is high for two timer clock periods.
     */
    GPTimerWFF3_CH_PULSE_ON_COMPARE_PERIODIC = GPTIMER_C0CFG_CCACT_PULSE_ON_CMP,

    /*! Pulse on compare, and then disable channel.
     *
     * Pulse channel output when the timer counter equals the compare value set
     * by #GPTimerWFF3_setInitialChannelCompVal().
     * The channel output is high for two timer clock periods.
     */
    GPTimerWFF3_CH_PULSE_ON_COMPARE_ONCE = GPTIMER_C0CFG_CCACT_PULSE_ON_CMP_DIS,

    /**************************************************************************
     *                     Channel capture actions.                           *
     *                                                                        *
     * The following list of channel actions will force the channel to be     *
     * configured as an input.                                                *
     * The counter value will be captured and the captured value can be read  *
     * by the #GPTimerWFF3_getChCompareVal() and                              *
     * #GPTimerWFF3_getNextChCompareVal() functions.                          *
     **************************************************************************/
    /*! Set on capture repeatedly.
     *
     * The channel number dependent interrupt status flag (#GPTimerWFF3_INT_CH0_CC
     * for channel number #GPTimerWFF3_CH_NO_0) will be set when the signal edge
     * selected by the chxInputEdge element in the GPTimerWFF3_Params structure,
     * is detected on the channel input signal.
     */
    GPTimerWFF3_CH_SET_ON_CAPTURE_PERIODIC = GPTIMER_C0CFG_CCACT_SET_ON_CAPT,

    /*! Set on capture, and then disable channel.
     *
     * The channel number dependent interrupt status flag (#GPTimerWFF3_INT_CH0_CC
     * for channel number #GPTimerWFF3_CH_NO_0) will be set when the signal edge
     * selected by the ch<x>InputEdge element in the GPTimerWFF3_Params structure,
     * is detected on the channel input signal.
     */
    GPTimerWFF3_CH_SET_ON_CAPTURE_ONCE = GPTIMER_C0CFG_CCACT_SET_ON_CAPT_DIS,

    /*! Period and pulse width measurement.
     *
     * Continuously capture period and pulse width of the channel input signal
     * relative to the signal edge selected by the ch<x>InputEdge element in the
     * GPTimerWFF3_Params structure.
     * The channel number dependent interrupt status flag (#GPTimerWFF3_INT_CH0_CC
     * for channel number #GPTimerWFF3_CH_NO_0) will be set when the signal
     * period and pulse width have been captured. The period and pulse width are
     * reported in numbers of counter ticks. The #GPTimerWFF3_getChCompareVal()
     * function returns the measured period and the
     * #GPTimerWFF3_getNextChCompareVal() functions returns the measured pulse
     * width.
     *
     * @note
     * Note that when selecting this channel action, #GPTimerWFF3_start() function
     * must be called with either #GPTimerWFF3_CTL_MODE_UP_ONCE or
     * #GPTimerWFF3_CTL_MODE_UP_PER as function argument.
     *
     * @note
     * Note that the timer counter restarts regularly when this action is used,
     * so other channel actions must be chosen with this in mind. The timer
     * counter restarts when the period of the channel input signal has been
     * captured.
     *
     * @note
     * If multiple channels are configured with this channel action, the
     * measurements are not performed simultaneously on the channels.
     * The measurements are done in a time-interleaved manner between the
     * channels.
     *
     * Signal property requirements for this channel action:
     * - Signal Period >= 2 * (1 + params.prescalerDiv) * system clock period.
     * - Signal Period <= MAX(timer counter) * (1 + params.prescalerDiv) * system clock period.
     * - Signal low and high phase >= (1 + params.prescalerDiv) * system clock period.
     */
    GPTimerWFF3_CH_PULSE_WIDTH_MEASURE = GPTIMER_C0CFG_CCACT_PER_PULSE_WIDTH_MEAS,
} GPTimerWFF3_ChannelAction;

/* Forward declaration of GPTimer configuration */
typedef struct GPTimerWFF3_Config GPTimerWFF3_Config;

/* GPTimer handle is pointer to configuration structure */
typedef GPTimerWFF3_Config *GPTimerWFF3_Handle;

/* Interrupt bit vector. See GPTimerWFF3_Interrupt for available interrupts */
typedef uint16_t GPTimerWFF3_IntMask;

/*!
 *  @brief      The definition of a callback function used by the GPTimer driver.
 *
 *  @param[in]  handle                  A GPTimer handle
 *
 *  @param[in]  interruptMask           GPTimer interrupt mask
 *
 */
typedef void (*GPTimerWFF3_HwiFxn)(GPTimerWFF3_Handle handle, GPTimerWFF3_IntMask interruptMask);

/*!
 *  @brief GPTimerWFF3 channel dependent properties struct.
 *
 *  GPTimer struct used by the #GPTimerWFF3_Params.
 *
 */
typedef struct GPTimerWFF3_ChannelProp
{
    /*! Channel action */
    GPTimerWFF3_ChannelAction action;
    /*! Channel input edge type required for triggering a channel action of
     * capture type
     */
    GPTimerWFF3_ChannelInputEdge inputEdge;
} GPTimerWFF3_ChannelProp;

/*!
 *  @brief GPTimerWFF3 Parameters
 *
 *  GPTimer parameters are used by the #GPTimerWFF3_open() call.
 *  Default values for these parameters are set using #GPTimerWFF3_Params_init().
 *
 * @note
 *  The prescalerDiv parameter determines the division factor of the
 *  system clock being input to the timer counter:
 *  - 0x00: Divide by 1
 *  - 0x01: Divide by 2
 *  - ...
 *  - 0xFF: Divide by 256
 *
 * @note
 *  The intPhaseLate parameter which determines if the #GPTimerWFF3_INT_TGT
 *  and #GPTimerWFF3_INT_ZERO interrupt status flags will be set early or late, is
 *  specified as follows:
 *  - false: Interrupt status flags are set one system clock cycle after
 *           counter = TARGET/ZERO.
 *  - true : Interrupt status flags are set one timer clock cycle after
 *           counter = TARGET/ZERO.
 *
 *  Please note that if the value of the intPhaseLate parameter is set to false
 *  while the prescalerDiv parameter value is high and either the
 *  #GPTimerWFF3_INT_TGT or #GPTimerWFF3_INT_ZERO interrupts are enabled, these
 *  interrupts might occur multiple times back-to-back when the interrupts are
 *  first triggered.
 *  While the counter is active, the timer will hold the state of the counter
 *  for one clock period of the timer clock before the counter gets updated.
 *  When the timer clock frequency is configured low by a high prescalerDiv
 *  parameter value, this hold time might be longer than it takes for the
 *  interrupt service routine to clear the interrupt status. This will cause a
 *  new interrupt to be immediatly generated. In order to avoid this situation,
 *  the intPhaseLate parameter value needs to be set to true. Then the interrupt
 *  will occur one timer clock cycle after the counter has reached the
 *  TARGET/ZERO value, meaning that the described hold time is reduced to 0.
 *
 *
 *  @sa     #GPTimerWFF3_Params_init()
 */
typedef struct GPTimerWFF3_Params
{
    /*! Hardware interrupt callback function.
     *  This pointer is optional and is only required if
     *  #GPTimerWFF3_enableInterrupt() is called.
     */
    GPTimerWFF3_HwiFxn hwiCallbackFxn;
    /*! Interrupt phase early or late for TGT and ZERO interrupts */
    bool intPhaseLate;
    /*! Prescaler division factor */
    uint8_t prescalerDiv;
    /*! Timer debug stall mode */
    GPTimerWFF3_DebugMode debugStallMode;
    /*! Timer counter direction for channel compare. Covers all channels */
    GPTimerWFF3_ChannelCmpDir counterDirChCompare;
    /*! Channel action and input edge type required for triggering a channel
     * action of capture type
     */
    GPTimerWFF3_ChannelProp channelProperty[NO_OF_GPT_CHANNELS];
} GPTimerWFF3_Params;

/*!
 *  @brief GPTimerWFF3 channel dependent pin configuration struct.
 *
 *  GPTimer struct used by the #GPTimerWFF3_HWAttrs.
 *
 */
typedef struct GPTimerWFF3_ChannelConf
{
    /*! Channel pin */
    uint8_t pin;
    /*! Channel pin mux */
    uint8_t pinMux;
    /*! Complementary channel pin */
    uint8_t nPin;
    /*! Complementary channel pin mux */
    uint8_t nPinMux;
} GPTimerWFF3_ChannelConf;

/*!
 *  @brief  GPTimerWFF3 Hardware attributes
 *
 *  These fields are used by the driver to set up underlying GPTimer
 *  driver statically. A sample structure is shown below making use
 *  of channel 2 in GPTIMER1:
 *
 *  @code
 *  // GPTimer hardware attributes, one per supported GPT peripheral
 *  const GPTimerWFF3_HWAttrs GPTimerWFF3HWAttrs[] = {
 *      {
 *           .baseAddr     = GPTIMER1_BASE,
 *           .intNum       = INT_GPTIMER_1,
 *           .intPriority  = (~0),
 *           .powerId      = PowerWFF3_PERIPH_GPTIMER1,
 *
 *           .channelConfig[0] = {
 *               .pin     = GPIO_INVALID_INDEX,
 *               .pinMux  = GPIO_MUX_GPIO_INTERNAL,
 *               .nPin    = GPIO_INVALID_INDEX,
 *               .nPinMux = GPIO_MUX_GPIO_INTERNAL,
 *           },
 *           .channelConfig[1] = {
 *               .pin     = GPIO_INVALID_INDEX,
 *               .pinMux  = GPIO_MUX_GPIO_INTERNAL,
 *               .nPin    = GPIO_INVALID_INDEX,
 *               .nPinMux = GPIO_MUX_GPIO_INTERNAL,
 *           },
 *           .channelConfig[2] = {
 *               .pin     = CONFIG_GPIO_GPTIMER_1_CH2,
 *               .pinMux  = 9,
 *               .nPin    = GPIO_INVALID_INDEX,
 *               .nPinMux = GPIO_MUX_GPIO_INTERNAL,
 *           },
 *           .channelConfig[3] = {
 *               .pin     = GPIO_INVALID_INDEX,
 *               .pinMux  = GPIO_MUX_GPIO_INTERNAL,
 *               .nPin    = GPIO_INVALID_INDEX,
 *               .nPinMux = GPIO_MUX_GPIO_INTERNAL,
 *           },
 *      },
 *  };
 *  @endcode
 */
typedef struct GPTimerWFF3_HWAttrs
{
    /*! GPTimer peripheral base address */
    uint32_t baseAddr;
    /*! GPTimer peripheral's power resource ID */
    PowerWFF3_Resource powerID;
    /*! GPTimer peripheral channel selection for for pin and pin mux */
    GPTimerWFF3_ChannelConf channelConfig[NO_OF_GPT_CHANNELS];
    /*! GPTimer peripheral interrupt vector */
    uint8_t intNum;
    /*! GPTimer peripheral's interrupt priority */
    uint8_t intPriority;
} GPTimerWFF3_HWAttrs;

/*!
 *  @brief  GPTimerWFF3 Object
 *
 * These fields are used by the driver to store and modify GPTimer
 * configuration during run-time.
 * The application must not edit any member variables of this structure.
 * Appplications should also not access member variables of this structure
 * as backwards compatibility is not guaranteed. An example structure is shown
 * below:
 * @code
 * // GPTimer objects, one per GPT peripheral (GPTIMER0, GPTIMER1..)
 * GPTimerWFF3_Object GPTimerWFF3Objects[];
 * @endcode
 */
typedef struct GPTimerWFF3_Object
{
    /*! Hardware interrupt struct */
    HwiP_Struct hwi;
    /*! Hardware interrupt callback function */
    GPTimerWFF3_HwiFxn hwiCallbackFxn;
    /*! For Sleep reconfiguration */
    Power_NotifyObj postNotify;
    /*! Arbritrary Argument */
    uintptr_t arg;
    /*! Object is opened flag */
    bool isOpen;
    /*! Interrupt phase early or late for TGT and ZERO interrupts */
    bool intPhaseLate;
    /*! Prescaler division factor */
    uint8_t prescalerDiv;
    /*! Bitmask of channels opened via GPTimerWFF3_openChannel(). Bit N is set
     *  while channel N is active. The peripheral is de-initialized only when
     *  all bits are cleared. Zero when the peripheral was opened exclusively
     *  via GPTimerWFF3_open() or has not been opened.
     */
    uint8_t openChannelMask;
    /*! Timer debug stall mode */
    GPTimerWFF3_DebugMode debugStallMode;
    /*! Counter direction required for triggering a channel compare */
    GPTimerWFF3_ChannelCmpDir counterDirChCompare;
    /*! Channel dependent properties */
    GPTimerWFF3_ChannelProp channelProperty[NO_OF_GPT_CHANNELS];
} GPTimerWFF3_Object;

/*!
 *  @brief  GPTimer Global configuration
 *
 *  The #GPTimerWFF3_Config structure contains a set of pointers used to
 *  characterize the GPTimer driver implementation. An example is shown below:
 *  @code
 *  // GPTimer configuration (used as GPTimer_Handle by driver and application)
 *  const GPTimerWFF3_Config GPTimerWFF3_config[] = {
 *      { &GPTimerWFF3Objects[0], &GPTimerWFF3HWAttrs[0]},
 *      { &GPTimerWFF3Objects[1], &GPTimerWFF3HWAttrs[1]},
 *  };
 *  @endcode
 */
struct GPTimerWFF3_Config
{
    GPTimerWFF3_Object *object;
    const GPTimerWFF3_HWAttrs *hwAttrs;
};

/*!
 *  @brief  Function that initializes the GPTimerWFF3_Params struct to
 *          its default values.
 *
 *  @param[in]  params  An pointer to GPTimerWFF3_Params structure for
 *                      initialization
 *
 *  Default values:
 * | Parameter              | Default value                            |
 * |------------------------|------------------------------------------|
 * | Interrupt callback fxn | \c NULL                                  |
 * | Interrupt phase late   | \c true                                  |
 * | Prescaler division     | \c 0                                     |
 * | Timer debug stall mode | #GPTimerWFF3_DEBUG_STALL_OFF             |
 * | Counter dir ch cmp     | #GPTimerWFF3_CH_COMPARE_COUNTER_DIR_BOTH |
 * | Channel 0 action       | #GPTimerWFF3_CH_DISABLE                  |
 * | Channel 0 input edge   | #GPTimerWFF3_CH_EDGE_NONE                |
 * | Channel 1 action       | #GPTimerWFF3_CH_DISABLE                  |
 * | Channel 1 input edge   | #GPTimerWFF3_CH_EDGE_NONE                |
 * | Channel 2 action       | #GPTimerWFF3_CH_DISABLE                  |
 * | Channel 2 input edge   | #GPTimerWFF3_CH_EDGE_NONE                |
 * | Channel 3 action       | #GPTimerWFF3_CH_DISABLE                  |
 * | Channel 3 input edge   | #GPTimerWFF3_CH_EDGE_NONE                |
 */
extern void GPTimerWFF3_Params_init(GPTimerWFF3_Params *params);

/*!
 *  @brief  Function that opens a driver for the given GPT peripheral. Will set
 *          power dependency on timer and configure it into specified
 *          configuration.
 *
 *  @param[in]  index     Index in the GPTimerWFF3_config table.
 *
 *  @param[in]  params    Pointer to a parameter block. If NULL, it will use
 *                        default values.
 *
 *  @return A #GPTimerWFF3_Handle on success or NULL on an error or if it has
 *          been opened already. If NULL is returned, further GPTimerWFF3 API
 *          calls will result in undefined behaviour.
 *
 *  @sa     #GPTimerWFF3_close()
 */
extern GPTimerWFF3_Handle GPTimerWFF3_open(uint_least8_t index, const GPTimerWFF3_Params *params);

/*!
 *  @brief  Function that closes a GPTimer driver specified by the GPTimer
 *          handle. Closing GPTimer driver will release power dependency on
 *          timer and clear configuration.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first.
 *  @pre    #GPTimerWFF3_stop() should to be called first if GPTimer is started.
 *
 *  @param[in]  handle A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_start()
 *  @sa     #GPTimerWFF3_stop()
 */
extern void GPTimerWFF3_close(GPTimerWFF3_Handle handle);

/*!
 *  @brief  Open a single channel on a GPTimer peripheral, allowing other channels
 *          on the same peripheral to be opened independently by other callers.
 *          The first channel open performs full hardware initialization; subsequent
 *          channels configure only their own channel without disturbing others.
 *
 *  @param[in]  index   Index in the GPTimerWFF3_config table.
 *  @param[in]  chNo    Channel to claim (#GPTimerWFF3_CH_NO_0 .. #GPTimerWFF3_CH_NO_3).
 *  @param[in]  params  Pointer to parameters. For a subsequent (non-first) channel
 *                      open, only params->channelProperty[chNo] is applied; all
 *                      other fields are ignored.
 *
 *  @return A #GPTimerWFF3_Handle on success, NULL if the channel is already open
 *          or the peripheral was opened via #GPTimerWFF3_open().
 *
 *  @sa     #GPTimerWFF3_closeChannel()
 *
 */
extern GPTimerWFF3_Handle GPTimerWFF3_openChannel(uint_least8_t index,
                                                  GPTimerWFF3_ChannelNo chNo,
                                                  const GPTimerWFF3_Params *params);

/*!
 *  @brief  Release a single channel previously opened with #GPTimerWFF3_openChannel().
 *          The peripheral is de-initialized when all allocated channels have been released.
 *
 *  @pre    #GPTimerWFF3_openChannel() has to be called first successfully.
 *
 *  @param[in]  handle  A #GPTimerWFF3_Handle returned from #GPTimerWFF3_openChannel().
 *  @param[in]  chNo    Channel to release.
 *
 *  @sa     #GPTimerWFF3_openChannel()
 */
extern void GPTimerWFF3_closeChannel(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo);

/*!
 *  @brief  Function that starts the timer counter of the specified GPTimer
 *          handle with current settings and specified timer counter mode.
 *
 *  @note  When signal measurement (#GPTimerWFF3_CH_PULSE_WIDTH_MEASURE) has
 *         been selected for one or more channels, the value of mode must be
 *         either #GPTimerWFF3_CTL_MODE_UP_ONCE or
 *         #GPTimerWFF3_CTL_MODE_UP_PER.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open().
 *  @param[in]  mode      The timer counter mode.
 *
 *  @post   #GPTimerWFF3_stop()
 */
extern void GPTimerWFF3_start(GPTimerWFF3_Handle handle, GPTimerWFF3_Mode mode);

/*!
 *  @brief  Function that stops the timer counter of the specified GPTimer driver.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_start()
 */
extern void GPTimerWFF3_stop(GPTimerWFF3_Handle handle);

/*!
 *  @brief  Function that sets the initial timer counter target on the specified
 *          GPTimer. This function must be called before the timer is started.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  value      Initial target value of the timer counter.
 *                         Max value: @ref ti_drivers_GPTimerWFF3_PeripheralProperties
 *                         "GPT peripheral properties"
 *                         The number of counter ticks required to reach target
 *                         value is value + 1.
 *                         Note that if either #GPTimerWFF3_CTL_MODE_UP_ONCE or
 *                         #GPTimerWFF3_CTL_MODE_UP_PER counter modes are used
 *                         for generating a PWM signal, the signal period equals
 *                         value + 1.
 *                         Note that if #GPTimerWFF3_CTL_MODE_UPDWN_PER counter
 *                         mode is used for generating a PWM signal, the signal
 *                         period equals value * 2.
 *  @param[in]  intFlagClr Controls if the #GPTimerWFF3_INT_TGT and
 *                         #GPTimerWFF3_INT_ZERO interrupt status flags are
 *                         cleared or not when this function is executed.
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_start()
 */
extern void GPTimerWFF3_setInitialCounterTarget(GPTimerWFF3_Handle handle, uint32_t value, bool intFlagClr);

/*!
 *  @brief  Function that sets the timer counter target for the next counter
 *          period on the specified GPTimer. The specified target value will be
 *          valid as timer counter target on the upcoming zero crossing. When
 *          counting repeatedly upwards a zero crossing is regarded as when the
 *          timer counter restarts counting from 0. This function can be called
 *          after the timer has started. Timer counter width is 32-bits.
 *          (see @ref ti_drivers_GPTimerWFF3_PeripheralProperties
 *           "GPT peripheral properties").
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  value      Next target value of the timer counter.
 *                         Max value: @ref ti_drivers_GPTimerWFF3_PeripheralProperties
 *                        "GPT peripheral properties"
 *                         The number of counter ticks required to reach target
 *                         value on the next counter period is value + 1.
 *                         Note that if either #GPTimerWFF3_CTL_MODE_UP_ONCE or
 *                         #GPTimerWFF3_CTL_MODE_UP_PER counter modes are used
 *                         for generating a PWM signal, the signal period equals
 *                         value + 1.
 *                         Note that if #GPTimerWFF3_CTL_MODE_UPDWN_PER counter
 *                         mode is used for generating a PWM signal, the signal
 *                         period equals value * 2.
 *
 *  @param[in]  intFlagClr Controls if the #GPTimerWFF3_INT_TGT and
 *                         #GPTimerWFF3_INT_ZERO interrupt status flags are
 *                        cleared or not when this function is executed.
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_start()
 */
extern void GPTimerWFF3_setNextCounterTarget(GPTimerWFF3_Handle handle, uint32_t value, bool intFlagClr);

/*!
 *  @brief  Function that returns the current timer counter value.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *
 *  @return  The current timer counter value
 *
 *  @sa     #GPTimerWFF3_open()
 */
extern uint32_t GPTimerWFF3_getCounter(GPTimerWFF3_Handle handle);

/*!
 *  @brief  Function to get a custom argument.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setArg() has to be called first
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *
 *  @return  The custom argument
 *
 *  @sa     #GPTimerWFF3_setArg()
 *  @sa     #GPTimerWFF3_open()
 */
extern uintptr_t GPTimerWFF3_getArg(GPTimerWFF3_Handle handle);

/*!
 *  @brief  Function to set a custom argument.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  arg       Custom argument
 *
 *  @sa     #GPTimerWFF3_getArg()
 *  @sa     #GPTimerWFF3_open()
 */
extern void GPTimerWFF3_setArg(GPTimerWFF3_Handle handle, uintptr_t arg);

/*!
 *  @brief  Enable interrupt source for the GPTimer handle.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 * @param[in]  handle    A #GPTimerWFF3_Handle returned from GPTimerWFF3_open()
 * @param[in]  intMask   A bit mask of interrupt flags to enable
 *
 */
void GPTimerWFF3_enableInterrupt(GPTimerWFF3_Handle handle, GPTimerWFF3_IntMask intMask);

/*!
 *  @brief  Disable interrupt source for the GPTimer handle.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_enableInterrupt() has to be called first
 *
 * @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 * @param[in]  intMask   A bit mask of interrupt flags to disable
 *
 */
void GPTimerWFF3_disableInterrupt(GPTimerWFF3_Handle handle, GPTimerWFF3_IntMask intMask);

/*!
 *  @brief  Function that sets the initial channel compare value on the
 *          specified GPTimer and channel. The compare value for the specified
 *          channel will be used by any compare type channel action
 *          #GPTimerWFF3_ChannelAction specified by the GPTimer params. The
 *          channel number dependent interrupt status flag
 *          (#GPTimerWFF3_INT_CH0_CC for channel number #GPTimerWFF3_CH_NO_0)
 *          will be set when the timer counter equals the channel compare value.
 *          This function must be called prior to #GPTimerWFF3_start(). Timer
 *          compare value width is 32 bits
 *          (see @ref ti_drivers_GPTimerWFF3_PeripheralProperties
 *           "GPT peripheral properties").
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo       Channel number
 *  @param[in]  value      Channel compare value for specified channel number
 *
 *  @param[in]  intFlagClr Controls if the channel number dependent
 *                         compare/capture interrupt status flag is cleared or
 *                         not when this function is executed.
 *
 *  @sa     #GPTimerWFF3_open()
 */
void GPTimerWFF3_setInitialChannelCompVal(GPTimerWFF3_Handle handle,
                                          GPTimerWFF3_ChannelNo chNo,
                                          uint32_t value,
                                          bool intFlagClr);

/*!
 *  @brief  Function that sets the channel compare value on the specified
 *          GPTimer for the next cycle of the already started timer counter.
 *          The compare value for the specified channel is valid for any compare
 *          type channel action #GPTimerWFF3_ChannelAction specified by the
 *          GPTimer params. The channel number dependent interrupt status flag
 *          (#GPTimerWFF3_INT_CH0_CC for channel number #GPTimerWFF3_CH_NO_0)
 *          will be set when the timer counter equals the channel compare value
 *          in the next and following timer counter cycles. This function can be
 *          called while the timer is active.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setInitialChannelCompVal() has to be called first successfully
 *  @pre    #GPTimerWFF3_start() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo       Channel number
 *  @param[in]  value      Channel compare value for specified channel number.
 *                         Width value is 32 bits
 *                         (see @ref ti_drivers_GPTimerWFF3_PeripheralProperties
 *                          "GPT peripheral properties").
 *
 *  @param[in]  intFlagClr Controls if the channel number dependent
 *                         compare/capture interrupt status flag is cleared or
 *                         not when this function is executed.
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_setInitialChannelCompVal()
 */
void GPTimerWFF3_setNextChannelCompVal(GPTimerWFF3_Handle handle,
                                       GPTimerWFF3_ChannelNo chNo,
                                       uint32_t value,
                                       bool intFlagClr);

/*!
 *  @brief  Function that manually sets the current channel output level high or
 *          low. Manual update of a channel output takes priority over automatic
 *          channel updates to the same output when occurring at the same time.
 *          The complementary channel output will be set to the complementary
 *          level of the specified level.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo       Channel number
 *  @param[in]  level      Channel level for specified channel number
 *
 *
 *  @sa     #GPTimerWFF3_open()
 */
void GPTimerWFF3_setChannelOutputLevel(GPTimerWFF3_Handle handle,
                                       GPTimerWFF3_ChannelNo chNo,
                                       GPTimerWFF3_ChannelLevel level);

/*!
 *  @brief  Function to get the channel compare value or channel-updated capture
 *          value. Dependent on the selected channel action for the specified
 *          channel, the function will return either the current channel compare
 *          value or the channel-updated capture value. The channel-updated
 *          capture value is returned if a successful channel capture event, as
 *          specified by the channel action, has occured on the specified
 *          channel. For a channel action of
 *          #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the returned value after a
 *          successful channel capture event, represents the measured period of
 *          the selected channel input signal.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setInitialChannelCompVal() has to be called first when
 *          channel compare action type is used.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo      Channel number
 *
 *  @return  The compare value or input signal pulse width
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_setInitialChannelCompVal()
 */
uint32_t GPTimerWFF3_getChCompareVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo);

/*!
 *  @brief  Function to get the channel compare value or channel-updated capture
 *          value. Dependent on the selected channel action for the specified
 *          channel, the function will return either the current channel compare
 *          value or the channel-updated capture value. The channel-updated
 *          capture value is returned if a successful channel capture event, as
 *          specified by the channel action, has occured on the specified
 *          channel. For a channel action of
 *          #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the returned value after a
 *          successful channel capture event, represents the measured period of
 *          the selected channel input signal.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setInitialChannelCompVal() has to be called first when
 *          channel compare action type is used.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo      Channel number
 *
 *  @return  The compare value or input signal pulse width
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_setInitialChannelCompVal()
 */
uint32_t GPTimerWFF3_getChCaptureVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo);

/*!
 *  @brief  Function to get the channel compare value for the next counter cycle
 *          or the channel-updated capture value. Dependent on the selected
 *          channel action for the specified channel, the function will return
 *          either the channel compare value for the next counter cycle or the
 *          channel-updated capture value. For a channel action mode of
 *          #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the returned value after a
 *          successful capture event will be the width of the low or high phase
 *          of the selected channel input signal. The phase is specified by
 *          #GPTimerWFF3_ChannelInputEdge parameter for the selected channel.
 *          In order to get the channel-updated capture value for other capture
 *          channel actions than #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the
 *          function #GPTimerWFF3_getChCompareVal should be used.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setInitialChannelCompVal() has to be called first when
 *          channel compare action type is used.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo      Channel number
 *
 *  @return  The custom argument
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_setInitialChannelCompVal()
 */
uint32_t GPTimerWFF3_getNextChCompareVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo);

/*!
 *  @brief  Function to get the channel compare value for the next counter cycle
 *          or the channel-updated capture value. Dependent on the selected
 *          channel action for the specified channel, the function will return
 *          either the channel compare value for the next counter cycle or the
 *          channel-updated capture value. For a channel action mode of
 *          #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the returned value after a
 *          successful capture event will be the width of the low or high phase
 *          of the selected channel input signal. The phase is specified by
 *          #GPTimerWFF3_ChannelInputEdge parameter for the selected channel.
 *          In order to get the channel-updated capture value for other capture
 *          channel actions than #GPTimerWFF3_CH_PULSE_WIDTH_MEASURE, the
 *          function #GPTimerWFF3_getChCompareVal() should be used.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *  @pre    #GPTimerWFF3_setInitialChannelCompVal() has to be called first when
 *          channel compare action type is used.
 *
 *  @param[in]  handle    A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *  @param[in]  chNo      Channel number
 *
 *  @return  The custom argument
 *
 *  @sa     #GPTimerWFF3_open()
 *  @sa     #GPTimerWFF3_setInitialChannelCompVal()
 */
uint32_t GPTimerWFF3_getNextChCaptureVal(GPTimerWFF3_Handle handle, GPTimerWFF3_ChannelNo chNo);

/*!
 *  @brief  Function to get the width of the timer counter in number of bits.
 *
 *  @pre    #GPTimerWFF3_open() has to be called first successfully
 *
 *  @param[in]  handle     A #GPTimerWFF3_Handle returned from #GPTimerWFF3_open()
 *
 *  @return  The timer counter width in number of bits
 *
 *  @sa     #GPTimerWFF3_open()
 */
uint32_t GPTimerWFF3_getCounterWidth(GPTimerWFF3_Handle handle);

#ifdef __cplusplus
}
#endif
#endif /* ti_drivers_timer_GPTimerWFF3__include */
