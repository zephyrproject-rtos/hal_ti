/******************************************************************************
 *  Filename:       ioc.h
 *
 *  Description:    Defines and prototypes for IOC.
 *
 *  Copyright (c) 2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef __IOC_H__
#define __IOC_H__

//*****************************************************************************
//
//! \addtogroup peripheral_group
//! \{
//! \addtogroup ioc_api
//! \{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_ioc.h"
#include "debug.h"

//! \name IOC Config masks
//! \{
//! These are masks for each config field.

//! \hideinitializer \brief Bit mask for the drive strength field
//! \details Valid options are described in
//! \ref ioc_config_drive_strength_options "IOC Config drive strength options"
#define IOC_CONFIG_DRIVE_STRENGTH_M (IOC_IOC12_IOCURR_M)

//! \hideinitializer \brief Bit mask for the slew rate field
//! \details Valid options are described in \ref ioc_config_slew_rate_options
//! "IOC Config slew rate options"
#define IOC_CONFIG_SLEW_RATE_M (IOC_IOC12_SLEWRED_M)

//! \hideinitializer \brief Bit mask for the pull control field
//! \details Valid options are described in \ref ioc_config_pull_control_options
//! "IOC Config pull control options"
#define IOC_CONFIG_PULL_CONTROL_M (IOC_IOC12_PULLCTL_M)

//! \hideinitializer \brief Bit mask for the edge detection field
//! \details Valid options are described in
//! \ref ioc_config_edge_detection_options "IOC Config edge detection options"
#define IOC_CONFIG_EDGE_DETECT_M (IOC_IOC12_EDGEDET_M)

//! \hideinitializer \brief Bit mask for the standby wakeup field
//! \details Valid options are described in
//! \ref ioc_config_standby_wakeup_options "IOC Config standby wakeup options"
#define IOC_CONFIG_STANDBY_WAKEUP_M (IOC_IOC12_WUENSB_M)

//! \hideinitializer \brief Bit mask for the shutdown wakeup field
//! \details Valid options are described in
//! \ref ioc_config_shutdown_wakeup_options "IOC Config shutdown wakeup options"
#define IOC_CONFIG_SHUTDOWN_WAKEUP_M (IOC_IOC12_WUCFGSD_M)

//! \hideinitializer \brief Bit mask for the IO invert field
//! \details Valid options are described in \ref ioc_config_io_invert_options
//! "IOC Config IO invert options"
#define IOC_CONFIG_INVERT_M (0x1UL << IOC_IOC12_IOMODE_S)

//! \hideinitializer \brief Bit mask for the IO mode field
//! \details Valid options are described in \ref ioc_config_io_mode_options
//! "IOC Config IO mode options"
#define IOC_CONFIG_IO_MODE_M (IOC_IOC12_IOMODE_M & (~IOC_CONFIG_INVERT_M))

//! \hideinitializer \brief Bit mask for the input buffer field
//! \details Valid options are described in \ref ioc_config_input_buffer_options
//! "IOC Config input buffer options"
#define IOC_CONFIG_INPUT_BUFFER_M (IOC_IOC12_INPEN_M)

//! \hideinitializer \brief Bit mask for the hysteresis field
//! \details Valid options are described in \ref ioc_config_hysteresis_options
//! "IOC Config hysteresis options"
#define IOC_CONFIG_HYSTERESIS_M (IOC_IOC12_HYSTEN_M)

//! \brief Bit mask for all IOC config options
#define IOC_CONFIG_ALL_M                                                                                           \
    (IOC_CONFIG_DRIVE_STRENGTH_M | IOC_CONFIG_SLEW_RATE_M | IOC_CONFIG_PULL_CONTROL_M | IOC_CONFIG_EDGE_DETECT_M | \
     IOC_CONFIG_STANDBY_WAKEUP_M | IOC_CONFIG_SHUTDOWN_WAKEUP_M | IOC_CONFIG_INVERT_M | IOC_CONFIG_IO_MODE_M |     \
     IOC_CONFIG_INPUT_BUFFER_M | IOC_CONFIG_HYSTERESIS_M)
//! \}

//! \name IOC Config drive strength options
//! \anchor ioc_config_drive_strength_options
//! \{

//! \hideinitializer Manual mode, 8 mA drive strength
#define IOC_CONFIG_DRIVE_STRENGTH_8MA (IOC_IOC12_IOCURR_CUR_8MA)
//! \hideinitializer Manual mode, 4 mA drive strength
#define IOC_CONFIG_DRIVE_STRENGTH_4MA (IOC_IOC12_IOCURR_CUR_4MA)
//! \hideinitializer Manual mode, 2 mA drive strength
#define IOC_CONFIG_DRIVE_STRENGTH_2MA (IOC_IOC12_IOCURR_CUR_2MA)
// Automatic mode is not supported on this device
#undef IOC_CONFIG_DRIVE_STRENGTH_AUTO
//! \}

//! \name IOC Config slew rate options
//! \anchor ioc_config_slew_rate_options
//! \{

//! \hideinitializer Normal slew rate
#define IOC_CONFIG_SLEW_RATE_NORMAL  (IOC_IOC12_SLEWRED_NORMAL)
//! \hideinitializer Reduced slew rate
#define IOC_CONFIG_SLEW_RATE_REDUCED (IOC_IOC12_SLEWRED_REDUCED)
//! \}

//! \name IOC Config pull control options
//! \anchor ioc_config_pull_control_options
//! \{

//! \hideinitializer No pull
#define IOC_CONFIG_PULL_CONTROL_NONE (IOC_IOC12_PULLCTL_PULL_DIS)
//! \hideinitializer Pull up
#define IOC_CONFIG_PULL_CONTROL_UP   (IOC_IOC12_PULLCTL_PULL_UP)
//! \hideinitializer Pull down
#define IOC_CONFIG_PULL_CONTROL_DOWN (IOC_IOC12_PULLCTL_PULL_DOWN)
//! \}

//! \name IOC Config edge detection options
//! \anchor ioc_config_edge_detection_options
//! \{

//! \hideinitializer Edge detection disabled
#define IOC_CONFIG_EDGE_DETECT_DISABLED (IOC_IOC12_EDGEDET_EDGE_DIS)
//! \hideinitializer Detect falling edge
#define IOC_CONFIG_EDGE_DETECT_FALLING  (IOC_IOC12_EDGEDET_EDGE_NEG)
//! \hideinitializer Detect rising edge
#define IOC_CONFIG_EDGE_DETECT_RISING   (IOC_IOC12_EDGEDET_EDGE_POS)
//! \hideinitializer Detect falling and rising edges
#define IOC_CONFIG_EDGE_DETECT_BOTH     (IOC_IOC12_EDGEDET_EDGE_BOTH)
//! \}

//! \name IOC Config standby wakeup options
//! \anchor ioc_config_standby_wakeup_options
//! \{

//! \hideinitializer Standby wakeup disabled
#define IOC_CONFIG_STANDBY_WAKEUP_DISABLED (IOC_IOC12_WUENSB_DIS)
//! \hideinitializer Standby wakeup enabled. The configured edge detection is
//! used as the wakeup source.
#define IOC_CONFIG_STANDBY_WAKEUP_ENABLED  (IOC_IOC12_WUENSB_EN)
//! \}

//! \name IOC Config shutdown wakeup options
//! \anchor ioc_config_shutdown_wakeup_options
//! \{

//! \hideinitializer Shutdown wakeup disabled
#define IOC_CONFIG_SHUTDOWN_WAKEUP_DISABLED (IOC_IOC12_WUCFGSD_DIS_0)
//! \hideinitializer Shutdown wakeup enabled. Wake up triggered when the pin
//! level is high.
#define IOC_CONFIG_SHUTDOWN_WAKEUP_HIGH     (IOC_IOC12_WUCFGSD_WAKE_HIGH)
//! \hideinitializer Shutdown wakeup enabled. Wake up triggered when the pin
//! level is low.
#define IOC_CONFIG_SHUTDOWN_WAKEUP_LOW      (IOC_IOC12_WUCFGSD_WAKE_LOW)
//! \}

//! \name IOC Config IO invert options
//! \anchor ioc_config_io_invert_options
//! \{

//! \hideinitializer Input/output values are inverted
#define IOC_CONFIG_INVERT_ENABLED  (IOC_IOC12_IOMODE_INVERTED & IOC_CONFIG_INVERT_M)
//! \hideinitializer Input/output values are normal (default)
#define IOC_CONFIG_INVERT_DISABLED (IOC_IOC12_IOMODE_NORMAL & IOC_CONFIG_INVERT_M)
//! \}

//! \name IOC Config IO mode options
//! \anchor ioc_config_io_mode_options
//! \{

//! \hideinitializer Normal IO mode
#define IOC_CONFIG_IO_MODE_NORMAL      (IOC_IOC12_IOMODE_NORMAL & IOC_CONFIG_IO_MODE_M)
//! \hideinitializer Open drain IO mode
#define IOC_CONFIG_IO_MODE_OPEN_DRAIN  (IOC_IOC12_IOMODE_OPEND & IOC_CONFIG_IO_MODE_M)
//! \hideinitializer Open source IO mode
#define IOC_CONFIG_IO_MODE_OPEN_SOURCE (IOC_IOC12_IOMODE_OPENS & IOC_CONFIG_IO_MODE_M)
//! \}

//! \name IOC Config input buffer options
//! \anchor ioc_config_input_buffer_options
//! \{

//! \hideinitializer Input buffer is disabled
#define IOC_CONFIG_INPUT_BUFFER_DISABLED (IOC_IOC12_INPEN_DIS)
//! \hideinitializer Input buffer is enabled
#define IOC_CONFIG_INPUT_BUFFER_ENABLED  (IOC_IOC12_INPEN_EN)
//! \}

//! \name IOC Config hysteresis options
//! \anchor ioc_config_hysteresis_options
//! \{

//! \hideinitializer Hysteresis is disabled
#define IOC_CONFIG_HYSTERESIS_DISABLED (IOC_IOC12_HYSTEN_DIS)
//! \hideinitializer Hysteresis is enabled
#define IOC_CONFIG_HYSTERESIS_ENABLED  (IOC_IOC12_HYSTEN_EN)
//! \}

//! \brief IOC register spacing
//! \details Each IOC register is 4 bytes (32 bits) apart in memory. This is
//! used to calculate the register address for a given DIO number.
#define IOC_REG_SPACING 4U

//*****************************************************************************
//
// The following values define the possible mux options for a DIO
//
//*****************************************************************************
//! \name IOC Mux options
//! \{
//!

// We don't define this value on purpose - any unsupported values will cause a
// compile-time error. If your compiler tells you that this macro is missing,
// you are trying to use an unsupported option.
//
// See below for which options are unsupported.
//
#undef IOC_MUX_OPTION_NOT_SUPPORTED

//! \hideinitializer GPIO function
#define IOC_MUX_GPIO (IOC_IOC12_PORTCFG_BASE)

//! Digital Test Bus (DTB) function
#define IOC_MUX_DTB (IOC_IOC12_PORTCFG_DTB)

//! \hideinitializer Analog function
#define IOC_MUX_ANALOG (IOC_IOC12_PORTCFG_ANA)

//! \hideinitializer Digital peripheral function 1
#define IOC_MUX_PERIPH_FUNC1 (IOC_IOC12_PORTCFG_PFUNC1)

//! \hideinitializer Digital peripheral function 2
#define IOC_MUX_PERIPH_FUNC2 (IOC_IOC12_PORTCFG_PFUNC2)

//! \hideinitializer Digital peripheral function 3
#define IOC_MUX_PERIPH_FUNC3 (IOC_IOC12_PORTCFG_PFUNC3)

//! \hideinitializer Digital peripheral function 4
#define IOC_MUX_PERIPH_FUNC4 (IOC_IOC12_PORTCFG_PFUNC4)

//! \hideinitializer Digital peripheral function 5
#define IOC_MUX_PERIPH_FUNC5 (IOC_IOC12_PORTCFG_PFUNC5)
//! \}

//*****************************************************************************
//
// Check for legal range of variable dioNumber
//
//*****************************************************************************
#ifdef DRIVERLIB_DEBUG

static bool dioNumberLegal(uint32_t dioNumber)
{
    // TODO: Implement properly
    // Get number of DIOs supported by platform. Number of DIOs is NUMDIO + 1.
    // Actual number available may be less for some package types.
    uint32_t numDio = 1 + ((HWREG(IOC_BASE + IOC_O_DESCEX) & IOC_DESCEX_NUMDIO_M) >> IOC_DESCEX_NUMDIO_S);
    return (dioNumber < numDio);
}
#endif

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Set the configuration and mux option for a specific DIO.
//!
//! \param dioNumber specifies the DIO to configure (0-25).
//!
//! \param config The configuration to apply. This is a bitwise OR of
//!  - One of the \ref ioc_config_drive_strength_options
//!    "IOC Config drive strength options"
//!  - One of the \ref ioc_config_slew_rate_options
//!    "IOC Config slew rate options"
//!  - One of the \ref ioc_config_pull_control_options
//!    "IOC Config pull control options"
//!  - One of the \ref ioc_config_edge_detection_options
//!    "IOC Config edge detection options"
//!  - One of the \ref ioc_config_standby_wakeup_options
//!    "IOC Config standby wakeup options"
//!  - One of the \ref ioc_config_shutdown_wakeup_options
//!    "IOC Config shutdown wakeup options"
//!  - One of the \ref ioc_config_io_invert_options
//!    "IOC Config IO invert options"
//!  - One of the \ref ioc_config_io_mode_options "IOC Config IO mode options"
//!  - One of the \ref ioc_config_input_buffer_options
//!    "IOC Config input buffer options"
//!  - And one of the \ref ioc_config_hysteresis_options
//!    "IOC Config hysteresis options"
//!
//! \param mux Selects the function of the DIO. It must be one of the following:
//!  - \ref IOC_MUX_GPIO
//!  - \ref IOC_MUX_DTB
//!  - \ref IOC_MUX_ANALOG
//!  - \ref IOC_MUX_PERIPH_FUNC1
//!  - \ref IOC_MUX_PERIPH_FUNC2
//!  - \ref IOC_MUX_PERIPH_FUNC3
//!  - \ref IOC_MUX_PERIPH_FUNC4
//!  - \ref IOC_MUX_PERIPH_FUNC5
//
//*****************************************************************************
__STATIC_INLINE void IOCSetConfigAndMux(uint32_t dioNumber, uint32_t config, uint32_t mux)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));
    ASSERT((config & IOC_CONFIG_ALL_M) == config);
    ASSERT((mux & IOC_IOC0_PORTCFG_M) == mux);

    // Set the config and mux option for the specified DIO.
    HWREG(IOC_BASE + IOC_O_IOC0 + dioNumber * IOC_REG_SPACING) = config | mux;
}

//*****************************************************************************
//
//! \brief Get the current mux option for a specific DIO.
//!
//! \param dioNumber specifies the DIO to get the mux option for (0-25).
//!
//! \note This only returns the mux option for the DIO, and does not take into
//!       account the shuffle network.
//!
//! \return One of the following:
//!  - \ref IOC_MUX_GPIO
//!  - \ref IOC_MUX_DTB
//!  - \ref IOC_MUX_ANALOG
//!  - \ref IOC_MUX_PERIPH_FUNC1
//!  - \ref IOC_MUX_PERIPH_FUNC2
//!  - \ref IOC_MUX_PERIPH_FUNC3
//!  - \ref IOC_MUX_PERIPH_FUNC4
//!  - \ref IOC_MUX_PERIPH_FUNC5
//
//*****************************************************************************
__STATIC_INLINE uint32_t IOCGetMux(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Return the mux option of the specified DIO.
    return (HWREG(IOC_BASE + IOC_O_IOC0 + dioNumber * IOC_REG_SPACING) & IOC_IOC0_PORTCFG_M) >> IOC_IOC0_PORTCFG_S;
}

//*****************************************************************************
//
//! \brief Get the current configuration for a specific DIO.
//!
//! The following masks can be used to retrieve specific configuration options
//! from the return value:
//!  - \ref IOC_CONFIG_DRIVE_STRENGTH_M
//!  - \ref IOC_CONFIG_SLEW_RATE_M
//!  - \ref IOC_CONFIG_PULL_CONTROL_M
//!  - \ref IOC_CONFIG_EDGE_DETECT_M
//!  - \ref IOC_CONFIG_STANDBY_WAKEUP_M
//!  - \ref IOC_CONFIG_SHUTDOWN_WAKEUP_M
//!  - \ref IOC_CONFIG_INVERT_M
//!  - \ref IOC_CONFIG_IO_MODE_M
//!  - \ref IOC_CONFIG_INPUT_BUFFER_M
//!  - \ref IOC_CONFIG_HYSTERESIS_M
//!  - \ref IOC_CONFIG_ALL_M
//!
//! \param dioNumber specifies the DIO to get the configuration for (0-25).
//!
//! \return A bitwise OR of:
//!  - One of the \ref ioc_config_drive_strength_options
//!    "IOC Config drive strength options"
//!  - One of the \ref ioc_config_slew_rate_options
//!    "IOC Config slew rate options"
//!  - One of the \ref ioc_config_pull_control_options
//!    "IOC Config pull control options"
//!  - One of the \ref ioc_config_edge_detection_options
//!    "IOC Config edge detection options"
//!  - One of the \ref ioc_config_standby_wakeup_options
//!    "IOC Config standby wakeup options"
//!  - One of the \ref ioc_config_shutdown_wakeup_options
//!    "IOC Config shutdown wakeup options"
//!  - One of the \ref ioc_config_io_invert_options
//!    "IOC Config IO invert options"
//!  - One of the \ref ioc_config_io_mode_options "IOC Config IO mode options"
//!  - One of the \ref ioc_config_input_buffer_options
//!    "IOC Config input buffer options"
//!  - And one of the \ref ioc_config_hysteresis_options
//!    "IOC Config hysteresis options"
//
//*****************************************************************************
__STATIC_INLINE uint32_t IOCGetConfig(uint32_t dioNumber)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));

    // Set the config and mux option for the specified DIO.
    return HWREG(IOC_BASE + IOC_O_IOC0 + dioNumber * IOC_REG_SPACING) & IOC_CONFIG_ALL_M;
}

//*****************************************************************************
//
//! \brief Set the edge detect configuration for a specific DIO, while keeping
//!        all other configs the same.
//!
//! \note This is a read-modify-write operation and is therefore not atomic.
//!
//! \param dioNumber specifies the DIO to set the edge detect configuration for
//!                  (0-25).
//!
//! \param edgeDetectConfig the edge detect configuration to set. Must be one of
//!                         the following:
//!  - \ref IOC_CONFIG_EDGE_DETECT_DISABLED
//!  - \ref IOC_CONFIG_EDGE_DETECT_FALLING
//!  - \ref IOC_CONFIG_EDGE_DETECT_RISING
//!  - \ref IOC_CONFIG_EDGE_DETECT_BOTH
//
//*****************************************************************************
__STATIC_INLINE void IOCSetEdgeDetectConfig(uint32_t dioNumber, uint32_t edgeDetectConfig)
{
    // Check the arguments.
    ASSERT(dioNumberLegal(dioNumber));
    ASSERT((edgeDetectConfig & IOC_CONFIG_EDGE_DETECT_M) == edgeDetectConfig);

    // Check assumption.
#if (IOC_CONFIG_EDGE_DETECT_M & 0x00FF0000) != IOC_CONFIG_EDGE_DETECT_M
    #error The implementation of IOCSetEdgeDetectConfig assumes that the edge \
           detect bits are in byte 2 of the IOCx register, which is not \
           the case.
#endif

    // Compute address of the byte to access. Which is byte 2 of the IOCx
    // register.
    uint32_t cfgRegByte2Addr = IOC_BASE + IOC_O_IOC0 + dioNumber * IOC_REG_SPACING + 2;

    // Shift config and mask to match byte 2 in the IOCx register.
    uint8_t shiftedConfig = edgeDetectConfig >> 16;
    uint8_t shiftedMask   = IOC_CONFIG_EDGE_DETECT_M >> 16;

    // Read byte 2 of the IOCx register.
    uint8_t tmpCfgRegByte2 = HWREGB(cfgRegByte2Addr);

    // Clear the edge detect bits.
    tmpCfgRegByte2 &= ~shiftedMask;

    // Set the new edge detect bits
    tmpCfgRegByte2 |= shiftedConfig;

    // Write the new value back.
    HWREGB(cfgRegByte2Addr) = tmpCfgRegByte2;
}

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
//! Close the Doxygen group.
//! \}
//! \}
//
//*****************************************************************************

#endif // __IOC_H__
