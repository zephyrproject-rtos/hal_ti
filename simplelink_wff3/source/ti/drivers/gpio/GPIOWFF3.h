/*
 * Copyright (c) 2021-2025, Texas Instruments Incorporated
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
 *  @file       GPIOWFF3.h
 *
 *  @brief      GPIO driver implementation for WiFi F3 devices
 *
 *  # Overview #
 *
 *  The GPIO header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/GPIO.h>
 *  #include <ti/drivers/gpio/GPIOWFF3.h>
 *  @endcode
 *
 *  Refer to @ref GPIO.h for a complete description of the GPIO
 *  driver APIs provided and examples of their use.
 *
 *  There are some WiFi F3 device-specific configuration values that can be used
 *  when calling @ref GPIO_setConfig or @ref GPIO_setConfigAndMux, listed below.
 *  All other macros should be used directly from GPIO.h.
 *
 *  There are some WiFi F3 device-specific mux values that can be used
 *  when calling @ref GPIO_setConfigAndMux listed below.
 *
 *  # IO Multiplexing #
 *  If an IO is multiplexed to an output signal or an analog signal, the IO must
 *  be configured with @ref GPIO_CFG_NO_DIR. The output will automatically be
 *  enabled when needed.
 *  If an IO is multiplexed to a digital input or bi-directional signal, the IO
 *  must be configured as an input using @ref GPIO_CFG_INPUT,
 *  @ref GPIO_CFG_IN_PU etc. to ensure that the input buffer of the IO is
 *  enabled.
 *
 *  For IOs supporting analog signals, an additional mux setting
 *  @ref GPIOWFF3_MUX_ANALOG can be used with @ref GPIO_setConfigAndMux().
 *
 *  # Software Controlled IO #
 *  Independently of the muxing, the IO can also be controlled/overriden by
 *  software. This means that if the IO is configured as an output (for example
 *  using @ref GPIO_CFG_OUTPUT), then the output state of the IO is controlled by
 *  the software. The signal the IO is muxed to is ignored. This is useful for
 *  some scenarios, for example setting the sleep state of the IO before
 *  entering sleep.
 *  When the IO is only intended to be used as a software controlled IO, it is
 *  recommended to use the @ref GPIO_MUX_GPIO mux setting.
 */

#ifndef ti_drivers_GPIOWFF3__include
#define ti_drivers_GPIOWFF3__include

#include <ti/drivers/GPIO.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_iomux.h)

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @name WiFi F3 Device-Specific Mux Macros
 *  @{
 */

/** @hideinitializer
 *
 *  @brief Mux IO to analog signal.
 *
 *  Each IO supporting analog signals has a single analog signal associated with
 *  it. With this mux setting, the IO will be muxed to that analog signal.
 *
 *  @warning The IO must be configured as @ref GPIO_CFG_NO_DIR when using this
 *  mux setting.
 *
 *  @warning Only use this mux setting for IOs supporting analog signals.
 *
 *  @note Only the least significant bits are written to the IOMUX registers to
 *  select the muxing. This results in the digital IO being muxed to "Hi-Z" as
 *  if @ref GPIO_MUX_GPIO is used.
 *  Bit 8 is used to inform the GPIO driver that the analog switch of the IO
 *  shall be controlled by the analog peripheral.
 */
#define GPIOWFF3_MUX_ANALOG (GPIOWFF3_MUX_ANALOG_INTERNAL | GPIO_MUX_GPIO_INTERNAL)

/** @} */

/**
 *  @name WiFi F3 Device-Specific GPIO_PinConfig Macros
 *  @{
 */
/** @hideinitializer
 *
 *  @brief Do not configure this pin.
 *
 *  @ref GPIO_setConfig and @ref GPIO_setConfigAndMux calls will return immediately.
 */
#define GPIOWFF3_DO_NOT_CONFIG 0x80000000

/** @} */

/**
 *  @name Macros Used Internally by WiFi F3 GPIO Driver.
 *
 *  Do not use any of these macros.
 *  @{
 */

/* Do not configure this pin. */
#define GPIO_CFG_DO_NOT_CONFIG_INTERNAL GPIOWFF3_DO_NOT_CONFIG

#define GPIO_MUX_GPIO_INTERNAL       (0x0D)
#define GPIOWFF3_MUX_ANALOG_INTERNAL (0x100)

/* We don't define this value on purpose - any unsupported values will cause a
 * compile-time error. If your compiler tells you that this macro is missing,
 * you are trying to use an unsupported option.
 *
 * See below for which options are unsupported.
 */
#undef GPIOWFF3_CFG_OPTION_NOT_SUPPORTED

/* The IO configuration for WiFi F3 devices are split between multiple
 * registers. The below mask and shift defines are used to split the
 * configuration data between registers.
 * Note: Most bitmasks are from GPIO2, but some GPIOs has additional fields,
 * and the bitmask from these fields are from a different GPIO. For example
 * GPIO20 is used for the drive strength bitmask.
 */
#define GPIOWFF3_CFG_CFG_S (0)
#define GPIOWFF3_CFG_CFG_M                                                                                    \
    ((IOMUX_GPIO2CFG_IE_M | IOMUX_GPIO2CFG_OUTDIS_M | IOMUX_GPIO2CFG_OUTDISOVREN_M | IOMUX_GPIO20CFG_IOSTR_M) \
     << GPIOWFF3_CFG_CFG_S)

#define GPIOWFF3_CFG_PULLCTL_S (0)
#define GPIOWFF3_CFG_PULLCTL_M ((IOMUX_GPIO2PCTL_CTL_M) << GPIOWFF3_CFG_PULLCTL_S)

#define GPIOWFF3_CFG_CTL_S (0)
#define GPIOWFF3_CFG_CTL_M ((IOMUX_GPIO2CTL_OUTOVREN_M | IOMUX_GPIO2CTL_OUT_M) << GPIOWFF3_CFG_CTL_S)

#define GPIOWFF3_CFG_EVTCTL_S (16)
#define GPIOWFF3_CFG_EVTCTL_M ((IOMUX_GPIO37ECTL_EVTDETCFG_M | IOMUX_GPIO2ECTL_TRGLVL_M) << GPIOWFF3_CFG_EVTCTL_S)

#define GPIOWFF3_CFG_IOMUX_COMB_M \
    (GPIOWFF3_CFG_CFG_M | GPIOWFF3_CFG_PULLCTL_M | GPIOWFF3_CFG_CTL_M | GPIOWFF3_CFG_EVTCTL_M)

/* Throw an error if above masks are overlapping */
#if ((GPIOWFF3_CFG_CFG_M + GPIOWFF3_CFG_PULLCTL_M + GPIOWFF3_CFG_CTL_M + GPIOWFF3_CFG_EVTCTL_M) != \
     GPIOWFF3_CFG_IOMUX_COMB_M)
    #error \
        "GPIOWFF3_CFG_CFG_M, GPIOWFF3_CFG_PULLCTL_M, GPIOWFF3_CFG_CTL_M and GPIOWFF3_CFG_EVTCTL_M have overlapping bits"
#endif

/* The remaining unused bits will be used for configuration options not directly
 * handled by IOMUX.
 */
#define GPIOWFF3_CFG_INTERNAL_M ~GPIOWFF3_CFG_IOMUX_COMB_M

/* - Disable output disable override (IP can control OUTDIS)
 * - Disable input
 */
#define GPIO_CFG_NO_DIR_INTERNAL \
    ((IOMUX_GPIO2CFG_OUTDISOVREN_DISABLE << GPIOWFF3_CFG_CFG_S) | (IOMUX_GPIO2CFG_IE_DISABLE << GPIOWFF3_CFG_CFG_S))

/* - Disable output disable override (IP can control OUTDIS)
 * - Enable input
 */
#define GPIO_CFG_INPUT_INTERNAL \
    ((IOMUX_GPIO2CFG_OUTDISOVREN_DISABLE << GPIOWFF3_CFG_CFG_S) | (IOMUX_GPIO2CFG_IE_ENABLE << GPIOWFF3_CFG_CFG_S))

/* - Enable output disable override (IP cannot control OUTDIS)
 * - Enable output (clear OUTDIS, which ENABLEs the pad)
 * - Enable input (to be able to read the current pin output value)
 * - Enable output override
 */
#define GPIO_CFG_OUTPUT_INTERNAL                                                                               \
    ((IOMUX_GPIO2CFG_OUTDISOVREN_ENABLE << GPIOWFF3_CFG_CFG_S) |                                               \
     (IOMUX_GPIO2CFG_OUTDIS_ENABLE << GPIOWFF3_CFG_CFG_S) | (IOMUX_GPIO2CFG_IE_ENABLE << GPIOWFF3_CFG_CFG_S) | \
     (IOMUX_GPIO2CTL_OUTOVREN_ENABLE << GPIOWFF3_CFG_CTL_S))

/* Default output value (only has an affect if output override is enabled) */
#define GPIO_CFG_OUTPUT_DEFAULT_HIGH_INTERNAL (IOMUX_GPIO2CTL_OUT_HIGH << GPIOWFF3_CFG_CTL_S)
#define GPIO_CFG_OUTPUT_DEFAULT_LOW_INTERNAL  (IOMUX_GPIO2CTL_OUT_LOW << GPIOWFF3_CFG_CTL_S)

/* Use IP Pull Control (TODO: Determine if this is a good solution and if it will work at all) */
#define GPIO_CFG_PULL_NONE_INTERNAL (IOMUX_GPIO2PCTL_CTL_IPCTRL << GPIOWFF3_CFG_PULLCTL_S)

/* Override IP pull control to pull up/down */
#define GPIO_CFG_PULL_UP_INTERNAL   (IOMUX_GPIO2PCTL_CTL_UP << GPIOWFF3_CFG_PULLCTL_S)
#define GPIO_CFG_PULL_DOWN_INTERNAL (IOMUX_GPIO2PCTL_CTL_DOWN << GPIOWFF3_CFG_PULLCTL_S)

/* Interrupt configurations*/
#define GPIO_CFG_INT_NONE_INTERNAL 0

/* - Enable edge detection
 * - Set edge direction to falling
 */
#define GPIO_CFG_INT_FALLING_INTERNAL (IOMUX_GPIO2ECTL_EVTDETCFG_NEG_EDGE << GPIOWFF3_CFG_EVTCTL_S)

/* - Enable edge detection
 * - Set edge direction to rising
 */
#define GPIO_CFG_INT_RISING_INTERNAL (IOMUX_GPIO2ECTL_EVTDETCFG_POS_EDGE << GPIOWFF3_CFG_EVTCTL_S)

/* - Enable level detection
 * - Trigger event when IO level is low
 */
#define GPIO_CFG_INT_LOW_INTERNAL \
    ((IOMUX_GPIO2ECTL_EVTDETCFG_LEVEL << GPIOWFF3_CFG_EVTCTL_S) | (IOMUX_GPIO2ECTL_TRGLVL_LOW << GPIOWFF3_CFG_EVTCTL_S))

/* - Enable level detection
 * - Trigger event when IO level is high
 */
#define GPIO_CFG_INT_HIGH_INTERNAL                                \
    ((IOMUX_GPIO2ECTL_EVTDETCFG_LEVEL << GPIOWFF3_CFG_EVTCTL_S) | \
     (IOMUX_GPIO2ECTL_TRGLVL_HIGH << GPIOWFF3_CFG_EVTCTL_S))

/* Drive strengths configurations
 * Note: GPIO20 is used instead of GPIO2, because GPIO2 do not have a drive
 * strength field.
 */
#define GPIO_CFG_DRVSTR_LOW_INTERNAL  (IOMUX_GPIO20CFG_IOSTR_LOW << GPIOWFF3_CFG_CFG_S)
#define GPIO_CFG_DRVSTR_HIGH_INTERNAL (IOMUX_GPIO20CFG_IOSTR_HIGH << GPIOWFF3_CFG_CFG_S)

/* TODO: Implement shutdown wake up (if supported) */
#define GPIO_CFG_SHUTDOWN_WAKE_OFF_INTERNAL  0
#define GPIO_CFG_SHUTDOWN_WAKE_HIGH_INTERNAL 0
#define GPIO_CFG_SHUTDOWN_WAKE_LOW_INTERNAL  0

/* Configuration values stored in internally used bits. Any configuration
 * options not directly handled by IOMUX need to be stored inside the internal
 * bits (\ref GPIOWFF3_CFG_INTERNAL_MASK)
 */

/* Interrupt enable is in the GPIO module */
#define GPIO_CFG_INT_ENABLE_INTERNAL  0x10
#define GPIO_CFG_INT_DISABLE_INTERNAL 0

/* Make sure configuration options not directly handled by IOMUX is only stored
 * in the internally used bits.
 */
#if (((GPIO_CFG_INT_ENABLE_INTERNAL | GPIOWFF3_DO_NOT_CONFIG) | GPIOWFF3_CFG_INTERNAL_M) != GPIOWFF3_CFG_INTERNAL_M)
    #error "Internal configurations values are not stored in GPIOWFF3_CFG_INTERNAL_M"
#endif

/* Not supported features */
#define GPIO_CFG_OUTPUT_OPEN_DRAIN_INTERNAL GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_OUT_OPEN_SOURCE_INTERNAL   GPIOWFF3_CFG_OPTION_NOT_SUPPORTED

#define GPIO_CFG_INT_BOTH_EDGES_INTERNAL GPIOWFF3_CFG_OPTION_NOT_SUPPORTED

#define GPIO_CFG_DRVSTR_MED_INTERNAL GPIOWFF3_CFG_OPTION_NOT_SUPPORTED

#define GPIO_CFG_INVERT_OFF_INTERNAL     GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_INVERT_ON_INTERNAL      GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_HYSTERESIS_OFF_INTERNAL GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_HYSTERESIS_ON_INTERNAL  GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_SLEW_NORMAL_INTERNAL    GPIOWFF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_SLEW_REDUCED_INTERNAL   GPIOWFF3_CFG_OPTION_NOT_SUPPORTED

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_GPIOWFF3__include */