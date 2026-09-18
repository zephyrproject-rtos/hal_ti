/******************************************************************************
 *  Filename:       clkctl.h
 *
 *  Description:    Defines and prototypes for the CLKCTL module.
 *
 *  Copyright (c) 2025-2026 Texas Instruments Incorporated
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

#ifndef __CLKCTL_H__
#define __CLKCTL_H__

//*****************************************************************************
//
//! \addtogroup system_control_group
//! @{
//! \addtogroup clkctl_api
//! @{
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

#include <stdbool.h>
#include <stdint.h>

#include "../inc/hw_ints.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../inc/hw_clkctl.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// Values that can be passed to CLKCTLEnable() and CLKCTLDisable().
//
//*****************************************************************************
#define CLKCTL_LGPT3 CLKCTL_CLKENSET0_LGPT3 //!< Configure LGPT3 clock enable
#define CLKCTL_LGPT2 CLKCTL_CLKENSET0_LGPT2 //!< Configure LGPT2 clock enable
#define CLKCTL_LGPT1 CLKCTL_CLKENSET0_LGPT1 //!< Configure LGPT1 clock enable
#define CLKCTL_LGPT0 CLKCTL_CLKENSET0_LGPT0 //!< Configure LGPT0 clock enable
#define CLKCTL_DMA   CLKCTL_CLKENSET0_DMA   //!< Configure DMA clock enable
#define CLKCTL_LAES  CLKCTL_CLKENSET0_LAES  //!< Configure LAES clock enable
#define CLKCTL_ADC0  CLKCTL_CLKENSET0_ADC0  //!< Configure ADC0 clock enable
#define CLKCTL_SPI0  CLKCTL_CLKENSET0_SPI0  //!< Configure SPI0 clock enable
#define CLKCTL_I2C0  CLKCTL_CLKENSET0_I2C0  //!< Configure I2C0 clock enable
#define CLKCTL_UART0 CLKCTL_CLKENSET0_UART0 //!< Configure UART0 clock enable
#define CLKCTL_LRFD  CLKCTL_CLKENSET0_LRFD  //!< Configure LRFD clock enable
#define CLKCTL_GPIO  CLKCTL_CLKENSET0_GPIO  //!< Configure GPIO clock enable

//*****************************************************************************
//
// API Functions and prototypes.
//
//*****************************************************************************

#ifdef DRIVERLIB_DEBUG
//*****************************************************************************
//
//! \internal
//!
//! \brief Checks clock control base address.
//!
//! This function determines if a clock controle base address is valid.
//!
//! \param base specifies the clock control base address.
//!
//! \return Returns \c true if the base address is valid and \c false
//! otherwise.
//
//*****************************************************************************
static bool CLKCTLBaseValid(uint32_t base)
{
    return (base == CLKCTL_BASE);
}
#endif

//*****************************************************************************
//
//! \brief Enables the clock for a peripheral.
//!
//! This function enables the clock for a peripheral.
//!
//! \param base specifies the clock control base address.
//! \param peripheral specifies the peripheral.
//! The parameter can be one of the following values:
//! - \ref CLKCTL_LGPT3
//! - \ref CLKCTL_LGPT2
//! - \ref CLKCTL_LGPT1
//! - \ref CLKCTL_LGPT0
//! - \ref CLKCTL_DMA
//! - \ref CLKCTL_LAES
//! - \ref CLKCTL_ADC0
//! - \ref CLKCTL_SPI0
//! - \ref CLKCTL_I2C0
//! - \ref CLKCTL_UART0
//! - \ref CLKCTL_LRFD
//! - \ref CLKCTL_GPIO
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLEnable(uint32_t base, uint32_t peripheral)
{
    // Check the arguments
    ASSERT(CLKCTLBaseValid(base));

    // Write the set bit
    HWREG(base + CLKCTL_O_CLKENSET0) = peripheral;
}

//*****************************************************************************
//
//! \brief Disables the clock for a peripheral.
//!
//! This function disables the clock for a peripheral.
//!
//! \param base specifies the clock control base address.
//! \param peripheral specifies the peripheral.
//! The parameter can be one of the following values:
//! - \ref CLKCTL_LGPT3
//! - \ref CLKCTL_LGPT2
//! - \ref CLKCTL_LGPT1
//! - \ref CLKCTL_LGPT0
//! - \ref CLKCTL_DMA
//! - \ref CLKCTL_LAES
//! - \ref CLKCTL_ADC0
//! - \ref CLKCTL_SPI0
//! - \ref CLKCTL_I2C0
//! - \ref CLKCTL_UART0
//! - \ref CLKCTL_LRFD
//! - \ref CLKCTL_GPIO
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLDisable(uint32_t base, uint32_t peripheral)
{
    // Check the arguments
    ASSERT(CLKCTLBaseValid(base));

    // Write the clear bit
    HWREG(base + CLKCTL_O_CLKENCLR0) = peripheral;
}

//*****************************************************************************
//
//! \brief Enable clock for LRFD
//!
//! \warning This API is only meant to be used by the LRFD driverlib module and
//! should not be used directly.
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLEnableLrfdClock(void)
{
    // Enable LRFD module clock
    HWREG(CLKCTL_BASE + CLKCTL_O_CLKENSET0) = CLKCTL_CLKENSET0_LRFD;

    // Wait for LRFD clock to be enabled. It is not expected that the LRFD clock
    // will ever be disabled, but this will add sufficient delay before
    // potentially using LRFD directly after this function.
    while ((HWREG(CLKCTL_BASE + CLKCTL_O_CLKCFG0) & CLKCTL_CLKCFG0_LRFD_M) != CLKCTL_CLKCFG0_LRFD_CLK_EN) {}
}

//*****************************************************************************
//
//! \brief Disable clock for LRFD
//!
//! \note This API is only meant to be used by the LRFD driverlib module and
//! should not be used directly.
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLDisableLrfdClock(void)
{
    HWREG(CLKCTL_BASE + CLKCTL_O_CLKENCLR0) = CLKCTL_CLKENCLR0_LRFD;
}

//*****************************************************************************
//
//! \brief Enable Flash LDO to be off in IDLE
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLEnableFlashLdoOffInIdle(void)
{
    HWREG( CLKCTL_BASE + CLKCTL_O_IDLECFG ) = CLKCTL_IDLECFG_MODE_LDO_OFF;
}

//*****************************************************************************
//
//! \brief Disable Flash LDO to be off in IDLE
//
//*****************************************************************************
__STATIC_INLINE void CLKCTLDisableFlashLdoOffInIdle(void)
{
    HWREG( CLKCTL_BASE + CLKCTL_O_IDLECFG ) = CLKCTL_IDLECFG_MODE_LDO_ON;
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
//! @}
//! @}
//
//*****************************************************************************

#endif // __CLKCTL_H__
