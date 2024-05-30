/******************************************************************************
 *  Filename:       pmctl.h
 *
 *  Description:    Defines and prototypes for the PMCTL module.
 *
 *  Copyright (c) 2022-2024 Texas Instruments Incorporated
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

#ifndef __PMCTL_H__
#define __PMCTL_H__

//*****************************************************************************
//
//! \addtogroup system_control_group
//! @{
//! \addtogroup pmctl_api
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

#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_pmctl.h"

#include "../cmsis/cc23x0r5.h"
#include "../cmsis/core/core_cm0plus.h"

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//! \name PMCTLGetResetReason() return values
//@{
//*****************************************************************************
//! Device woke up from shutdown due to an IO event
#define PMCTL_RESET_SHUTDOWN_IO        (PMCTL_RSTSTA_SDDET | PMCTL_RSTSTA_IOWUSD)
//! Device woke up from shutdown due to an SWD event
#define PMCTL_RESET_SHUTDOWN_SWD       PMCTL_RSTSTA_SDDET
//! Device reset because of a watchdog timeout.
#define PMCTL_RESET_WATCHDOG           (PMCTL_RSTSTA_SYSSRC_WDTEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by software writing to RSTCTL.SYSRST
#define PMCTL_RESET_SYSTEM             (PMCTL_RSTSTA_SYSSRC_SYSRSTEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by CPU reset event
#define PMCTL_RESET_CPU                (PMCTL_RSTSTA_SYSSRC_CPURSTEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by CPU lockup event
#define PMCTL_RESET_LOCKUP             (PMCTL_RSTSTA_SYSSRC_LOCKUPEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by Analog FSM timeout event
#define PMCTL_RESET_ANALOG_FSM_TIMEOUT (PMCTL_RSTSTA_SYSSRC_AFSMEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by Analog Error reset event
#define PMCTL_RESET_ANALOG_ERROR       (PMCTL_RSTSTA_SYSSRC_AERREV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by Digital Error reset event
#define PMCTL_RESET_DIGITAL_ERROR      (PMCTL_RSTSTA_SYSSRC_DERREV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset triggered by Serial Wire Debug reset event
#define PMCTL_RESET_SWD                (PMCTL_RSTSTA_SYSSRC_SWDRSTEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device reset due to LFXT clock loss
#define PMCTL_RESET_LFXT               (PMCTL_RSTSTA_SYSSRC_LFLOSSEV | PMCTL_RSTSTA_RESETSRC_SYSRESET)
//! Device woke up from thermal shutdown after temperature drop
#define PMCTL_RESET_TSD                (PMCTL_RSTSTA_TSDEV | PMCTL_RSTSTA_RESETSRC_PINRESET)
//! Device reset due to VDDR brownout event
#define PMCTL_RESET_VDDR               PMCTL_RSTSTA_RESETSRC_VDDRLOSS
//! Device reset due to VDDS brownout event
#define PMCTL_RESET_VDDS               PMCTL_RSTSTA_RESETSRC_VDDSLOSS
//! Device reset due to pin reset
#define PMCTL_RESET_PIN                PMCTL_RSTSTA_RESETSRC_PINRESET
//! Device booted due to power on reset
#define PMCTL_RESET_POR                PMCTL_RSTSTA_RESETSRC_PWRON
//@}

//*****************************************************************************
//! \name PMCTLSetVoltageRegulator() inputs and PMCTLGetVoltageRegulator() return values
//@{
//*****************************************************************************
//! DCDC voltage regulator
#define PMCTL_VOLTAGE_REGULATOR_DCDC PMCTL_VDDRCTL_SELECT_DCDC
//! GLDO voltage regulator
#define PMCTL_VOLTAGE_REGULATOR_GLDO PMCTL_VDDRCTL_SELECT_GLDO
//@}

//*****************************************************************************
//
//! \brief Get the reason for the system reset.
//!
//! This function will return the reason the device reset.
//!
//! \return Returns the reset source.
//! - \ref PMCTL_RESET_SHUTDOWN_IO
//! - \ref PMCTL_RESET_SHUTDOWN_SWD
//! - \ref PMCTL_RESET_WATCHDOG
//! - \ref PMCTL_RESET_SYSTEM
//! - \ref PMCTL_RESET_CPU
//! - \ref PMCTL_RESET_LOCKUP
//! - \ref PMCTL_RESET_ANALOG_FSM_TIMEOUT
//! - \ref PMCTL_RESET_ANALOG_ERROR
//! - \ref PMCTL_RESET_DIGITAL_ERROR
//! - \ref PMCTL_RESET_SWD
//! - \ref PMCTL_RESET_LFXT
//! - \ref PMCTL_RESET_TSD
//! - \ref PMCTL_RESET_VDDR
//! - \ref PMCTL_RESET_VDDS
//! - \ref PMCTL_RESET_PIN
//! - \ref PMCTL_RESET_POR
//
//*****************************************************************************
__STATIC_INLINE uint32_t PMCTLGetResetReason(void)
{
    return HWREG(PMCTL_BASE + PMCTL_O_RSTSTA);
}

//*****************************************************************************
//
//! \brief Issue a system reset.
//!
//! This function issues a system reset. This will cause the device to reboot.
//! After rebooting, #PMCTLGetResetReason() will return #PMCTL_RESET_SYSTEM.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void PMCTLResetSystem(void)
{
    // Disable interrupts
    __disable_irq();

    // Write reset register
    HWREG(PMCTL_BASE + PMCTL_O_RSTCTL) |= PMCTL_RSTCTL_SYSRST_SET;

    // Should never return from this function
    while (1) {}
}

//*****************************************************************************
//
//! \brief Set the VDDR regulator
//!
//! This function sets the VDDR regulator to use in active, idle, and standby
//! modes.
//!
//! \param regulator The voltage regulator to switch to.
//! - \ref PMCTL_VOLTAGE_REGULATOR_DCDC
//! - \ref PMCTL_VOLTAGE_REGULATOR_GLDO
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void PMCTLSetVoltageRegulator(uint32_t regulator)
{
    // Write to VDDR regulator register while preserving other configuration
    // fields
    uint32_t tmp                        = HWREG(PMCTL_BASE + PMCTL_O_VDDRCTL) & ~PMCTL_VDDRCTL_SELECT_M;
    HWREG(PMCTL_BASE + PMCTL_O_VDDRCTL) = tmp | regulator;
}

//*****************************************************************************
//
//! \brief Get the current VDDR regulator
//!
//! This function gets the VDDR regulator currently in use.
//!
//! \return Current voltage regulator
//! - PMCTL_VOLTAGE_REGULATOR_DCDC
//! - PMCTL_VOLTAGE_REGULATOR_GLDO
//
//*****************************************************************************
__STATIC_INLINE uint32_t PMCTLGetVoltageRegulator(void)
{
    return (HWREG(PMCTL_BASE + PMCTL_O_VDDRCTL) & PMCTL_VDDRCTL_SELECT_M);
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

#endif // __PMCTL_H__
