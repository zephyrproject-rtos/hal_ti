/*
 * Copyright (c) 2021-2024, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       PowerCC23X0.h
 *
 *  @brief      Power manager interface for CC23X0 devices
 *
 *  The Power header file should be included in an application by including the
 *  top level header file as follows:
 *  @code
 *  #include <ti/drivers/Power.h>
 *  @endcode
 *
 *  Refer to @ref Power.h for a complete description of APIs.
 *
 *  ## Implementation ##
 *  This header file defines the power resources, constraints, events, sleep
 *  states and transition latencies for CC23X0.
 *
 *  @anchor ti_drivers_PowerCC23X0_HFXT_Amplitude_Compensation
 *  ## HFXT Amplitude Compensation ##
 *  The CC23X0 Power driver will configure the HFXT amplitude to the highest
 *  possible value at boot (in #Power_init()). Each time the device
 *  enters standby the HFXT amplitude will be updated to ensure the optimal
 *  amplitude is used. It will take up to 5 iterations (5 standby entries)
 *  after boot until the optimal amplitude has been found. This process will
 *  ensure that the amplitude is kept in an optimal range if the operating
 *  conditions change, as long as the device regularly enters standby.
 *
 *  ### Applications that rarely enters standby ###
 *  The amplitude adjustments done at standby entry is sufficient for
 *  applications that regularly enters standby, but if the application does not
 *  regularly enter standby, then #PowerLPF3_getHfxtAmpAdjustment() and
 *  #PowerLPF3_adjustHfxtAmp() can be used to check if an adjustment is needed,
 *  and perform the adjustment if needed.
 *
 *  @anchor ti_drivers_PowerCC23X0_Initial_HFXT_Amplitude_Compensation
 *  ### Initial HFXT Amplitude Compensation ###
 *  If the application requires that the HFXT amplitude is already in the
 *  optimal range after boot, then Initial HFXT Amplitude Compensation can be
 *  enabled with #PowerCC23X0_Config.startInitialHfxtAmpCompFxn.
 *  If initial HFXT amplitude compensation is enabled, the optimal amplitude
 *  will be found at/after boot, meaning it will take longer before HFXT is
 *  ready after boot, but when it is ready the amplitude will already be in the
 *  optimal range. This process is done asynchronously, so the application can
 *  do other stuff while waiting for HFXT to be ready.
 *
 *  Enabling initial HFXT amplitude compensation will result in more flash usage
 *  and longer time from boot to the first RF operation.
 *
 *
 *  ============================================================================
 */

#ifndef ti_drivers_power_PowerCC23X0_
#define ti_drivers_power_PowerCC23X0_

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_pmctl.h)
#include DeviceFamily_constructPath(inc/hw_clkctl.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/pmctl.h)

#ifdef __cplusplus
extern "C" {
#endif

/*! The latency to reserve for resume from STANDBY (usec). */
#define PowerCC23X0_RESUMETIMESTANDBY 400

/*! The total latency to reserve for entry to and exit from STANDBY (usec). */
#define PowerCC23X0_TOTALTIMESTANDBY 500

/*! The initial delay when waking from STANDBY (usec). */
#define PowerCC23X0_WAKEDELAYSTANDBY 185

/* Default lower threshold for when HFXT compensation is enabled */
#define PowerCC23X0_HFXT_THRESHOLD_TEMP_DEFAULT (-40)

/* \cond */
/* The control of the peripherals are split between multiple groups.
 * These defines are used to differentiate between the groups.
 * The bits in the PowerCC23X0_PERIPH_GROUP_M mask is used to store the group id,
 * and the bits in the PowerCC23X0_PERIPH_BIT_INDEX_M mask is used to store the
 * bit index shift value in the register for the given group.
 */
#define PowerCC23X0_PERIPH_GROUP_M       0xFF00
#define PowerCC23X0_PERIPH_GROUP_CLKCTL0 0x0000
#define PowerCC23X0_PERIPH_GROUP_LRFD    0x0100
#define PowerCC23X0_PERIPH_BIT_INDEX_M   0x00FF

/* \endcond */

/* \cond */
typedef uint16_t PowerLPF3_Resource; /* Power resource identifier */
/* \endcond */

/* Resource IDs */

/*! Resource ID: General Purpose I/O */
#define PowerLPF3_PERIPH_GPIO (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_GPIO_S)

/*! Resource ID: UART 0 */
#define PowerLPF3_PERIPH_UART0 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_UART0_S)

/*! Resource ID: I2C 0 */
#define PowerLPF3_PERIPH_I2C0 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_I2C0_S)

/*! Resource ID: SPI 0 */
#define PowerLPF3_PERIPH_SPI0 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_SPI0_S)

/*! Resource ID: ADC */
#define PowerLPF3_PERIPH_ADC0 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_ADC0_S)

/*! Resource ID: AES Security Module */
#define PowerLPF3_PERIPH_AES (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_LAES_S)

/*! Resource ID: uDMA Controller */
#define PowerLPF3_PERIPH_DMA (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_DMA_S)

/*! Resource ID: General Purpose Timer 0 */
#define PowerLPF3_PERIPH_LGPT0 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_LGPT0_S)

/*! Resource ID: General Purpose Timer 1 */
#define PowerLPF3_PERIPH_LGPT1 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_LGPT1_S)

/* The peripherals below are not available on CC23X0R2 devices */
#if !defined(DeviceFamily_CC23X0R2)
    /*! Resource ID: General Purpose Timer 2 */
    #define PowerLPF3_PERIPH_LGPT2 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_LGPT2_S)

    /*! Resource ID: General Purpose Timer 3 */
    #define PowerLPF3_PERIPH_LGPT3 (PowerCC23X0_PERIPH_GROUP_CLKCTL0 | CLKCTL_DESCEX0_LGPT3_S)
#endif

/*! Resource ID: LRFD Tracer */
#define PowerLPF3_PERIPH_LFRD_TRC (PowerCC23X0_PERIPH_GROUP_LRFD | LRFDDBELL_CLKCTL_TRC_S)

/*! Resource ID: LRFD S2R RAM */
#define PowerLPF3_PERIPH_LFRD_S2RRAM (PowerCC23X0_PERIPH_GROUP_LRFD | LRFDDBELL_CLKCTL_S2RRAM_S)

/* \cond */
/* Number of resources in the different resource groups. This is possibly larger
 * than the peripheral instance count on various device variants. This is
 * because some indexes might not be used for a given variant, resulting in a
 * sparse table.
 */
#if defined(DeviceFamily_CC23X0R2)
    #define PowerCC23X0_NUMRESOURCES_CLKCTL0 29
#elif (defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R22))
    #define PowerCC23X0_NUMRESOURCES_CLKCTL0 31
#else
    #error "Unsupported DeviceFamily specified!"
#endif
#define PowerCC23X0_NUMRESOURCES_LRFD 12
/* \endcond */

#define PowerLPF3_STANDBY 0x1 /*!< The STANDBY sleep state */
/* \cond */
/* Internal flags for enabling/disabling resources */
#define PowerLPF3_ENABLE  1
#define PowerLPF3_DISABLE 0
/* \endcond */

/* Constraints
 *
 * Constraints restrict a specific system behavior from occurring or guarantee
 * a specified effect until released.
 */

/*! Constraint: Disallow a transition to the SHUTDOWN state */
#define PowerLPF3_DISALLOW_SHUTDOWN 0

/*! Constraint: Disallow a transition to the STANDBY sleep state */
#define PowerLPF3_DISALLOW_STANDBY 1

/*! Constraint: Disallow a transition to the IDLE sleep state */
#define PowerLPF3_DISALLOW_IDLE 2

/*! Constraint: Flash memory needs to enabled during IDLE */
#define PowerLPF3_NEED_FLASH_IN_IDLE 3

/* \cond */
#define PowerCC23X0_NUMCONSTRAINTS 4 /* Number of constraints supported */
/* \endcond */

/*
 *  Events
 *
 *  Each event must be a power of two and must be sequential
 *  without any gaps.
 */

/*! Power event: The device is entering the STANDBY sleep state */
#define PowerLPF3_ENTERING_STANDBY (1 << 0)

/*! Power event: The device is entering the SHUTDOWN state */
#define PowerLPF3_ENTERING_SHUTDOWN (1 << 1)

/*! Power event: The device is waking up from the STANDBY sleep state */
#define PowerLPF3_AWAKE_STANDBY (1 << 2)

/*! Power event: The high frequency (HF) crystal oscillator is now available
 *   for use (HFXT) by the digital domain
 */
#define PowerLPF3_HFXT_AVAILABLE (1 << 3)

/*! Power event: The system has switched to the low frequency clock source
 *   configured in CCFG
 */
#define PowerLPF3_LFCLK_SWITCHED (1 << 4)

/* \cond */
#define PowerCC23X0_NUMEVENTS 5 /* Number of events supported */
/* \endcond */

/*!
 *  @brief Function pointer to #PowerLPF3_startInitialHfxtAmpComp() or NULL.
 *
 *  This type is only allowed to have the value NULL or be a
 *  pointer to #PowerLPF3_startInitialHfxtAmpComp().
 */
typedef void (*PowerLPF3_StartInitialHfxtAmpCompFxn)(void);

/*! @brief Global configuration structure */
typedef struct
{
    /*!
     *  @brief The Power Policy's initialization function
     *
     *  If the policy does not have an initialization function, 'NULL'
     *  should be specified.
     */
    Power_PolicyInitFxn policyInitFxn;
    /*!
     *  @brief The Power Policy function
     *
     *  When enabled, this function is invoked in the idle loop, to
     *  opportunistically select and activate sleep states.
     *
     *  Two reference policies are provided:
     *
     *    PowerCC23X0_doWFI() - a simple policy that invokes CPU wait for
     *    interrupt (WFI)
     *
     *    PowerCC23X0_standbyPolicy() - an agressive policy that considers
     *    constraints, time until next scheduled work, and sleep state
     *    latencies, and optionally puts the device into the STANDBY state,
     *    the IDLE state, or as a minimum, WFI.
     *
     *  Custom policies can be written, and specified via this function pointer.
     *
     *  In addition to this static selection, the Power Policy can be
     *  dynamically changed at runtime, via the Power_setPolicy() API.
     *
     *  If not NULL, the policy function will be invoked once for each pass
     *  of the idle loop.
     *
     *  The power policy can be dynamically
     *  enabled and disabled at runtime, via the Power_enablePolicy() and
     *  Power_disablePolicy() functions, respectively.
     */
    Power_PolicyFxn policyFxn;

    /*!
     *  @brief Pointer to the function to start the initial HFXT amplitude
               compensation.
     *
     *  This is used to enable/disable the initial HFXT amplitude compensation
     *  feature.
     *
     * The allowed values for this field is:
     *  - NULL: Initial HFXT amplitude compensation is disabled.
     *  - Pointer to #PowerLPF3_startInitialHfxtAmpComp(): Initial HFXT
     *    amplitude compensation is disabled.
     *
     * @sa @ref ti_drivers_PowerCC23X0_Initial_HFXT_Amplitude_Compensation "Initial HFXT Amplitude Compensation"
     */
    PowerLPF3_StartInitialHfxtAmpCompFxn startInitialHfxtAmpCompFxn;
} PowerCC23X0_Config;

/*!
 * @brief Reasons the device has booted or rebooted.
 */
typedef enum
{
    /*! Device woke up from shutdown due to an IO event */
    PowerLPF3_RESET_SHUTDOWN_IO  = PMCTL_RESET_SHUTDOWN_IO,
    /*! Device woke up from shutdown due to an SWD event */
    PowerLPF3_RESET_SHUTDOWN_SWD = PMCTL_RESET_SHUTDOWN_SWD,
    /*! Device reset because of a watchdog timeout. */
    PowerLPF3_RESET_WATCHDOG     = PMCTL_RESET_WATCHDOG,
    /*! Device reset triggered by software writing to RSTCTL.SYSRST */
    PowerLPF3_RESET_SYSTEM       = PMCTL_RESET_SYSTEM,
    /*! Device reset triggered by CPU reset event */
    PowerLPF3_RESET_CPU          = PMCTL_RESET_CPU,
    /*! Device reset triggered by CPU lockup event */
    PowerLPF3_RESET_LOCKUP       = PMCTL_RESET_LOCKUP,
    /*! Device woke up from thermal shutdown after temperature drop */
    PowerLPF3_RESET_TSD          = PMCTL_RESET_TSD,
    /*! Device woke up due to Serial Wire Debug event */
    PowerLPF3_RESET_SWD          = PMCTL_RESET_SWD,
    /*! Device reset due to LFXT clock loss */
    PowerLPF3_RESET_LFXT         = PMCTL_RESET_LFXT,
    /*! Device reset due to VDDR brownout event */
    PowerLPF3_RESET_VDDR         = PMCTL_RESET_VDDR,
    /*! Device reset due to VDDS brownout event */
    PowerLPF3_RESET_VDDS         = PMCTL_RESET_VDDS,
    /*! Device reset due to pin reset */
    PowerLPF3_RESET_PIN          = PMCTL_RESET_PIN,
    /*! Device booted due to power on reset */
    PowerLPF3_RESET_POR          = PMCTL_RESET_POR,
} PowerLPF3_ResetReason;

/*!
 *  @brief  The wait for interrupt (WFI) policy
 *
 *  This is a lightweight Power Policy which simply invokes CPU wait for
 *  interrupt.
 *
 *  This policy can be selected statically via the policyFxn pointer in the
 *  PowerCC23X0_Config structure, or dynamically at runtime, via
 *  Power_setPolicy().
 */
void PowerCC23X0_doWFI(void);

/*!
 * @brief Returns the reason for the most recent reset or wakeup
 *
 * @return #PowerLPF3_ResetReason
 * @pre Power_shutdown()
 * @post PowerLPF3_releaseLatches()
 */
static inline PowerLPF3_ResetReason PowerLPF3_getResetReason(void)
{
    return (PowerLPF3_ResetReason)PMCTLGetResetReason();
}

/*!
 * @brief Unlatch all IOs
 *
 * This function releases the latches on all frozen IOs. This function should be
 * called after waking up from shutdown and reconfiguring the IO state so as not
 * to cause glitches.
 *
 * @note Calling this function will clear the reset reason register if it was
 *       #PowerLPF3_RESET_SHUTDOWN_IO and PowerLPF3_RESET_SHUTDOWN_SWD and
 *       cause PowerLPF3_getResetReason() not to return the true reset reason.
 *
 * @pre Power_shutdown()
 * @pre PowerLPF3_getResetReason()
 */
static inline void PowerLPF3_releaseLatches(void)
{
    HWREG(PMCTL_BASE + PMCTL_O_SLPCTL) = PMCTL_SLPCTL_SLPN_DIS;
}

/*!
 *  @brief  The STANDBY Power Policy
 *
 *  This is an agressive Power Policy, which considers active constraints,
 *  sleep state transition latencies, and time until the next scheduled
 *  work, and automatically transitions the device into the deepest sleep state
 *  possible.
 *
 *  The first goal is to enter STANDBY; if that is not appropriate
 *  given current conditions (e.g., the sleep transition latency is greater
 *  greater than the time until the next scheduled Clock event), then
 *  the secondary goal is the IDLE state; if that is disallowed (e.g., if
 *  the PowerLPF3_DISALLOW_IDLE constraint is declared), then the policy
 *  will fallback and simply invoke WFI, to clock gate the CPU until the next
 *  interrupt.
 *
 *  In order for this policy to run, it must be selected as the Power
 *  Policy (either by being specified as the 'policyFxn' in the
 *  PowerCC23X0_Config structure, or specified at runtime with
 *  Power_setPolicy()), and the Power Policy must be enabled (either via
 *  'enablePolicy' in the PowerCC23X0_Config structure, or via a call to
 *  Power_enablePolicy() at runtime).
 */
void PowerCC23X0_standbyPolicy(void);

/*!
 * @brief Select LFOSC as LFCLK source
 *
 * Turn on the LFOSC and choose it as LFCLK source. Once LFCLK has switched, the
 * #PowerLPF3_LFCLK_SWITCHED notification will be issued and all subscribers to
 * this event will be notified.
 *
 * @warning Dynamic switching between LF clocks is not supported. Once one of
 * PowerLPF3_selectLFOSC(), PowerLPF3_selectLFXT() or PowerLPF3_selectEXTLF()
 * is called in an application, the other two may not be invoked thereafter.
 *
 * @pre Power_init()
 * @sa PowerLPF3_selectLFXT()
 * @sa PowerLPF3_selectEXTLF()
 */
void PowerLPF3_selectLFOSC(void);

/*!
 * @brief Select LFXT as LFCLK source
 *
 * Turn on the LFXT and choose it as LFCLK source. Once LFCLK has switched,
 * the #PowerLPF3_LFCLK_SWITCHED notification will be issued and all
 * subscribers to this event will be notified.
 *
 * @warning Dynamic switching between LF clocks is not supported. Once one of
 * PowerLPF3_selectLFOSC(), PowerLPF3_selectLFXT() or PowerLPF3_selectEXTLF()
 * is called in an application, the other two may not be invoked thereafter.
 *
 * @pre Power_init()
 * @sa PowerLPF3_selectLFOSC()
 * @sa PowerLPF3_selectEXTLF()
 */
void PowerLPF3_selectLFXT(void);

/*!
 * @brief Select EXTLF as LFCLK source
 *
 * Choose an external 31.25 kHz square wave as the LFCLK source as input.
 * Once LFCLK has switched, the #PowerLPF3_LFCLK_SWITCHED notification
 * will be issued and all subscribers to this event will be notified.
 *
 * This function requires the following symbols to be defined.
 *  - \c PowerLPF3_extlfPin (uint8_t): The DIO number of the pin to be used as the EXTLF pin.
 *  - \c PowerLPf3_extlfPinMux (uint8_t): Mux value used to mux the EXTLF signal to \c PowerLPF3_extlfPin.
 * If using SysConfig, the symbols will be defined in ti_drivers_config.c.
 *
 * @warning Dynamic switching between LF clocks is not supported. Once one of
 * PowerLPF3_selectLFOSC(), PowerLPF3_selectLFXT() or PowerLPF3_selectEXTLF()
 * is called in an application, the other two may not be invoked thereafter.
 *
 * @pre Power_init()
 * @sa PowerLPF3_selectLFOSC()
 * @sa PowerLPF3_selectLFXT()
 */
void PowerLPF3_selectEXTLF(void);

/*!
 * @brief Initialise HFXT temperature compensation coefficients
 *
 * Initialise the parameters used for HFXT temperature coefficients. They approximate
 * the ppm offset of the HFXT frequency with the following polynomial as a function of
 * temperature (degC), where P_3 = P3 / 2^shift, P_2 = P2 / 2^shift, etc..
 * ppm(T) = P_3*T^3 + P_2*T^2 + P_1*T + P_0
 *
 * @param[in] P0    0th-order coefficient, multiplied by 2^shift
 * @param[in] P1    1st-order coefficient, multiplied by 2^shift
 * @param[in] P2    2nd-order coefficient, multiplied by 2^shift
 * @param[in] P3    3rd-order coefficient, multiplied by 2^shift
 * @param[in] shift Shift-value for scaling fixed-point coefficients
 * @param[in] fcfgInsertion Boolean used to indicate presence of HFXT FCFG data.
 *
 * @pre Power_init()
 */

void PowerLPF3_initHFXTCompensation(int32_t P0, int32_t P1, int32_t P2, int32_t P3, uint8_t shift, bool fcfgInsertion);

/*!
 * @brief Enable HFXT temperature compensation
 *
 * Enable automatic compensation for temperature-based frequency-drift of HFXT
 *
 * This function should only be called once, but can be invoked again if
 * PowerLPF3_enableHFXTCompensation has been called
 *
 * @param[in] tempThreshold Threshold above which temperature compensation will
 * be performed. This can be useful to save power consumption if HFXT
 * performance is acceptable at low temperatures, and only required at
 * high temperatures. If the threshold is set to for example 80 degrees, then
 * the first compensation will occur once the temperature reaches 81 degrees.
 * Units in degrees Celsius.
 * @param[in] tempDelta Delta describing how much the temperature can drift
 * before compensation is applied. If compensation is performed at 81 degrees,
 * and the delta is set to 5, then a re-compensation is performed at either
 * 76 degrees or 86 degrees, depending on which temperature state occurs first.
 * Units in degrees Celsius.
 *
 * @pre PowerLPF3_initHFXTCompensation()
 */
void PowerLPF3_enableHFXTCompensation(int16_t tempThreshold, int16_t tempDelta);

/*!
 * @brief Disable HFXT temperature compensation
 *
 * Disable automatic compensation for temperature-based frequency-drift of HFXT
 *
 * @note Calling this function will also undo any previous temperature compensation that has been
 * performed in the past, and HFXT will become uncompensated
 *
 * @pre PowerLPF3_enableHFXTCompensation()
 */
void PowerLPF3_disableHFXTCompensation(void);

/*!
 * @brief Start initial compensation of the HFXT amplitude
 *
 * @warning This function must not be called by the application. It is only
 * intended to be specified for #PowerCC23X0_Config.startInitialHfxtAmpCompFxn
 */
void PowerLPF3_startInitialHfxtAmpComp(void);

/*!
 * @brief Check if HFXT amplitude needs to be adjusted
 *
 * The HFXT amplitude needs to regularly be checked and if needed adjusted.
 * The Power driver will check the amplitude and adjust it when the device
 * enters standby. However if the device does not enter standby often enough,
 * then additional checks and adjustments are needed.
 *
 * This function can be used to check if adjustment of the amplitude is needed,
 * and #PowerLPF3_adjustHfxtAmp() can be used to adjust the amplitude if needed.
 *
 * @return
 *  - +1: The amplitude needs to be increased
 *  -  0: No adjustments are needed
 *  - -1: The amplitude needs to be decreased
 *
 * @sa #PowerLPF3_adjustHfxtAmp()
 */
int_fast8_t PowerLPF3_getHfxtAmpAdjustment(void);

/*!
 * @brief Adjust the HFXT amplitude
 *
 * This function is to be used to adjust the HFXT amplitude if an adjustment is
 * needed according to #PowerLPF3_getHfxtAmpAdjustment(). Please refer to the
 * documentation of #PowerLPF3_getHfxtAmpAdjustment() for more details.
 *
 * @note The radio must be disabled when adjusting the HFXT amplitude, and while
 * the amplitude is settling.
 * After this function returns, the caller must wait until the HFXT amplitude
 * has settled.
 *
 * @param adjustment the value returned by #PowerLPF3_getHfxtAmpAdjustment().
 *                   No other value is allowed.
 *
 * @pre #PowerLPF3_getHfxtAmpAdjustment() must be called, and it must return
 * a non-zero value (indicating that adjustment is needed)
 * @sa #PowerLPF3_getHfxtAmpAdjustment()
 */
void PowerLPF3_adjustHfxtAmp(int_fast8_t adjustment);

void PowerCC23X0_schedulerDisable(void);
void PowerCC23X0_schedulerRestore(void);

#ifdef __cplusplus
}
#endif

#endif /* POWER_CC23X0_ */
