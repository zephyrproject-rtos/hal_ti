/*
 * Copyright (c) 2021-2026, Texas Instruments Incorporated
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
/*! ============================================================================
 *  @file       GPIOLPF3.h
 *
 *  @brief      GPIO driver implementation for Low Power F3 devices
 *
 *  The GPIO header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/GPIO.h>
 *  #include <ti/drivers/gpio/GPIOLPF3.h>
 *  @endcode
 *
 *  Refer to @ref GPIO.h for a complete description of the GPIO
 *  driver APIs provided and examples of their use.
 *
 *  Most definitions in this file should not be used directly. All GPIO_CFG
 *  macros should be used as-is from GPIO.h. The only definitions in this file
 *  that can be used directly are the mux options that can be found in
 *  @ref gpiolpf3_mux_options.
 *
 *  There are no additional configuration values or platform-specific
 *  functions for GPIOLPF3.
 */

#ifndef ti_drivers_GPIOLPF3__include
#define ti_drivers_GPIOLPF3__include

#include <ti/drivers/GPIO.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/ioc.h)

#ifdef __cplusplus
extern "C" {
#endif

/* Do not configure this pin. */
#define GPIO_CFG_DO_NOT_CONFIG_INTERNAL (0x80000000U)

/** @name GPIO Mux options
 *  @anchor gpiolpf3_mux_options
 *  @brief Mux options for LPF3 devices
 *
 *  @details Mux options to be passed to the @c mux parameter of
 *  #GPIO_setConfigAndMux().
 *  @{
 */
//! \hideinitializer GPIO function. Do not use directly, use @ref GPIO_MUX_GPIO
//! instead.
#define GPIO_MUX_GPIO_INTERNAL (IOC_MUX_GPIO)
/*! Digital Test Bus (DTB) function */
#define GPIO_MUX_DTB           (IOC_MUX_DTB)
/*! \hideinitializer Analog function */
#define GPIO_MUX_ANALOG        (IOC_MUX_ANALOG)
/*! \hideinitializer Digital Peripheral Function 1 */
#define GPIO_MUX_PERIPH_FUNC1  (IOC_MUX_PERIPH_FUNC1)
/*! \hideinitializer Digital Peripheral Function 2 */
#define GPIO_MUX_PERIPH_FUNC2  (IOC_MUX_PERIPH_FUNC2)
/*! \hideinitializer Digital Peripheral Function 3 */
#define GPIO_MUX_PERIPH_FUNC3  (IOC_MUX_PERIPH_FUNC3)
/*! \hideinitializer Digital Peripheral Function 4 */
#define GPIO_MUX_PERIPH_FUNC4  (IOC_MUX_PERIPH_FUNC4)
/*! \hideinitializer Digital Peripheral Function 5 */
#define GPIO_MUX_PERIPH_FUNC5  (IOC_MUX_PERIPH_FUNC5)
/** @} */

/* Numeric PORTCFG defines for backwards compatibility */
#define GPIO_MUX_PORTCFG_PFUNC7 GPIO_MUX_DTB
#define GPIO_MUX_PORTCFG_PFUNC6 GPIO_MUX_ANALOG
#define GPIO_MUX_PORTCFG_PFUNC5 GPIO_MUX_PERIPH_FUNC5
#define GPIO_MUX_PORTCFG_PFUNC4 GPIO_MUX_PERIPH_FUNC4
#define GPIO_MUX_PORTCFG_PFUNC3 GPIO_MUX_PERIPH_FUNC3
#define GPIO_MUX_PORTCFG_PFUNC2 GPIO_MUX_PERIPH_FUNC2
#define GPIO_MUX_PORTCFG_PFUNC1 GPIO_MUX_PERIPH_FUNC1

/* We don't define this value on purpose - any unsupported values will cause a
 * compile-time error. If your compiler tells you that this macro is missing,
 * you are trying to use an unsupported option.
 *
 * See below for which options are unsupported.
 */
#undef GPIOLPF3_CFG_OPTION_NOT_SUPPORTED

/* Most configuration values are directly mapped to fields in the IOCn
 * registers, but the mux bits are reserved for configuration options that
 * cannot be directly mapped to the IOCn registers. The define below is the
 * mask used by the GPIO driver to mask off the non-IOC configuration values.
 */
#define GPIOLPF3_CFG_IOC_M (IOC_CONFIG_ALL_M)

/* Low and high value interrupts are not available on Low Power F3 devices */
#define GPIO_CFG_INT_LOW_INTERNAL  GPIOLPF3_CFG_OPTION_NOT_SUPPORTED
#define GPIO_CFG_INT_HIGH_INTERNAL GPIOLPF3_CFG_OPTION_NOT_SUPPORTED

/* General options */
#define GPIO_CFG_NO_DIR_INTERNAL (IOC_CONFIG_IO_MODE_NORMAL | GPIOLPF3_CFG_PIN_IS_INPUT_INTERNAL)
/* Hysteresis is enabled by default for all input pins due the specific hardware
 * implementation on these devices. This may impact pin response by 1-2ns, but
 * creates significantly more stable environments for high-speed use cases like
 * SPI.
 */
#define GPIO_CFG_INPUT_INTERNAL                                                                        \
    (IOC_CONFIG_IO_MODE_NORMAL | IOC_CONFIG_INPUT_BUFFER_ENABLED | IOC_CONFIG_STANDBY_WAKEUP_ENABLED | \
     IOC_CONFIG_HYSTERESIS_ENABLED | GPIOLPF3_CFG_PIN_IS_INPUT_INTERNAL)
#define GPIO_CFG_OUTPUT_INTERNAL \
    (IOC_CONFIG_IO_MODE_NORMAL | IOC_CONFIG_INPUT_BUFFER_ENABLED | GPIOLPF3_CFG_PIN_IS_OUTPUT_INTERNAL)
#define GPIO_CFG_OUTPUT_OPEN_DRAIN_INTERNAL \
    (IOC_CONFIG_IO_MODE_OPEN_DRAIN | IOC_CONFIG_INPUT_BUFFER_ENABLED | GPIOLPF3_CFG_PIN_IS_OUTPUT_INTERNAL)
#define GPIO_CFG_OUT_OPEN_SOURCE_INTERNAL \
    (IOC_CONFIG_IO_MODE_OPEN_SOURCE | IOC_CONFIG_INPUT_BUFFER_ENABLED | GPIOLPF3_CFG_PIN_IS_OUTPUT_INTERNAL)

#define GPIO_CFG_PULL_NONE_INTERNAL (IOC_CONFIG_PULL_CONTROL_NONE)
#define GPIO_CFG_PULL_UP_INTERNAL   (IOC_CONFIG_PULL_CONTROL_UP)
#define GPIO_CFG_PULL_DOWN_INTERNAL (IOC_CONFIG_PULL_CONTROL_DOWN)

#define GPIO_CFG_INT_NONE_INTERNAL       (IOC_CONFIG_EDGE_DETECT_DISABLED)
#define GPIO_CFG_INT_FALLING_INTERNAL    (IOC_CONFIG_EDGE_DETECT_FALLING)
#define GPIO_CFG_INT_RISING_INTERNAL     (IOC_CONFIG_EDGE_DETECT_RISING)
#define GPIO_CFG_INT_BOTH_EDGES_INTERNAL (IOC_CONFIG_EDGE_DETECT_BOTH)

/* We can feed this into the low bit of IOMODE, and it can then be ORed with output/input/OD/OS */
#define GPIO_CFG_INVERT_OFF_INTERNAL (IOC_CONFIG_INVERT_DISABLED)
#define GPIO_CFG_INVERT_ON_INTERNAL  (IOC_CONFIG_INVERT_ENABLED)

#define GPIO_CFG_HYSTERESIS_OFF_INTERNAL (IOC_CONFIG_HYSTERESIS_DISABLED)
#define GPIO_CFG_HYSTERESIS_ON_INTERNAL  (IOC_CONFIG_HYSTERESIS_ENABLED)

#define GPIO_CFG_SHUTDOWN_WAKE_OFF_INTERNAL  (IOC_CONFIG_SHUTDOWN_WAKEUP_DISABLED)
#define GPIO_CFG_SHUTDOWN_WAKE_HIGH_INTERNAL (IOC_CONFIG_SHUTDOWN_WAKEUP_HIGH)
#define GPIO_CFG_SHUTDOWN_WAKE_LOW_INTERNAL  (IOC_CONFIG_SHUTDOWN_WAKEUP_LOW)

/* Slew limits and drive strength are only supported on specific pins: pin 12, pins 16-19, and pin 24 */
#define GPIO_CFG_SLEW_NORMAL_INTERNAL  (IOC_CONFIG_SLEW_RATE_NORMAL)
#define GPIO_CFG_SLEW_REDUCED_INTERNAL (IOC_CONFIG_SLEW_RATE_REDUCED)

#define GPIO_CFG_DRVSTR_LOW_INTERNAL  (IOC_CONFIG_DRIVE_STRENGTH_2MA)
#define GPIO_CFG_DRVSTR_MED_INTERNAL  (IOC_CONFIG_DRIVE_STRENGTH_4MA)
#define GPIO_CFG_DRVSTR_HIGH_INTERNAL (IOC_CONFIG_DRIVE_STRENGTH_8MA)

/* Configuration values stored in mux bits. Any configuration options not
 * directly handled by IOC need to be stored inside the mux bits (lowest 3 bits
 * on Low Power F3 devices). These are masked out by GPIO_init(),
 * GPIO_setConfig(), GPIO_setConfigAndMux() and GPIO_getConfig() using
 * GPIOLPF3_CFG_IOC_M.
 */

/* Default output value */
#define GPIO_CFG_OUTPUT_DEFAULT_HIGH_INTERNAL (0x1U)
#define GPIO_CFG_OUTPUT_DEFAULT_LOW_INTERNAL  (0x0U)

/* Whether GPIO hardware should have the output enable bit set for this pin */
#define GPIOLPF3_CFG_PIN_IS_INPUT_INTERNAL  (0x2U)
#define GPIOLPF3_CFG_PIN_IS_OUTPUT_INTERNAL (0x0U)

/* Interrupt enable is in the GPIO module */
#define GPIO_CFG_INT_ENABLE_INTERNAL  (0x4U)
#define GPIO_CFG_INT_DISABLE_INTERNAL (0x0U)

#if GPIOLPF3_CFG_IOC_M & (GPIO_CFG_INT_ENABLE_INTERNAL | GPIOLPF3_CFG_PIN_IS_INPUT_INTERNAL | \
                          GPIO_CFG_OUTPUT_DEFAULT_HIGH_INTERNAL | GPIO_CFG_DO_NOT_CONFIG_INTERNAL)
    #error "Error in GPIOLPF3 implementation: Internally used config bits are overlapping with IOC config bits"
#endif

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_GPIOLPF3__include */
