/******************************************************************************
 *  Filename:       systick.h
 *
 *  Description:    Prototypes for the SysTick driver.
 *
 *  Copyright (c) 2022 Texas Instruments Incorporated
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

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

//*****************************************************************************
//
//! \addtogroup system_cpu_group
//! @{
//! \addtogroup systick_api
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
#include "../inc/hw_ints.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_systick.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// API Functions and Prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Enables the SysTick counter.
//!
//! This will start the SysTick counter. If an interrupt handler has been
//! registered, it will be called when the SysTick counter rolls over.
//!
//! \note Calling this function will cause the SysTick counter to (re)commence
//! counting from its current value. The counter is not automatically reloaded
//! with the period as specified in a previous call to \ref SysTickSetPeriod().
//! If an immediate reload is required, the SYSTICK_O_CVR register must be
//! written to force this. Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the supplied period on the next
//! clock.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTickEnable(void)
{
    // Enable SysTick.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) |= (SYSTICK_CSR_CLKSOURCE | SYSTICK_CSR_ENABLE);
}

//*****************************************************************************
//
//! \brief Disables the SysTick counter.
//!
//! This will stop the SysTick counter. If an interrupt handler has been
//! registered, it will no longer be called until SysTick is restarted.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTickDisable(void)
{
    // Disable SysTick.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) &= ~(SYSTICK_CSR_ENABLE);
}

//*****************************************************************************
//
//! \brief Registers an interrupt handler for the SysTick interrupt in the dynamic interrupt table.
//!
//! \note Only use this function if you want to use the dynamic vector table (in SRAM)!
//!
//! This function registers a function as the interrupt handler for a specific
//! interrupt and enables the corresponding interrupt in the interrupt controller.
//!
//! \param pfnHandler is a pointer to the function to be called when the
//! SysTick interrupt occurs.
//!
//! \return None
//!
//! \sa \ref IntRegister() for important information about registering interrupt
//! handlers.
//
//*****************************************************************************
__STATIC_INLINE void SysTickRegisterInt(void (*pfnHandler)(void))
{
    // Register the interrupt handler, returning an error if an error occurs.
    IntRegister(INT_SYSTICK, pfnHandler);

    // Enable the SysTick interrupt.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) |= SYSTICK_CSR_TICKINT;
}

//*****************************************************************************
//
//! \brief Unregisters the interrupt handler for the SysTick interrupt in the dynamic interrupt table.
//!
//! This function will clear the handler to be called when a SysTick interrupt
//! occurs.
//!
//! \return None
//!
//! \sa \ref IntRegister() for important information about registering interrupt
//! handlers.
//
//*****************************************************************************
__STATIC_INLINE void SysTickUnregisterInt(void)
{
    // Disable the SysTick interrupt.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) &= ~(SYSTICK_CSR_TICKINT);

    // Unregister the interrupt handler.
    IntUnregister(INT_SYSTICK);
}

//*****************************************************************************
//
//! \brief Enables the SysTick interrupt.
//!
//! This function will enable the SysTick interrupt, allowing it to be
//! reflected to the processor.
//!
//! \note The SysTick interrupt handler does not need to clear the SysTick
//! interrupt source as this is done automatically when the interrupt handler
//! is called.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTickEnableInt(void)
{
    // Enable the SysTick interrupt.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) |= SYSTICK_CSR_TICKINT;
}

//*****************************************************************************
//
//! \brief Disables the SysTick interrupt.
//!
//! This function will disable the SysTick interrupt, preventing it from being
//! reflected to the processor.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTickDisableInt(void)
{
    // Disable the SysTick interrupt.
    HWREG(SYSTICK_BASE + SYSTICK_O_CSR) &= ~(SYSTICK_CSR_TICKINT);
}

//*****************************************************************************
//
//! \brief Sets the period of the SysTick counter.
//!
//! This function sets the rate at which the SysTick counter wraps; this
//! equals to the number of processor clocks between interrupts.
//!
//! \note Calling this function does not cause the SysTick counter to reload

//! immediately. If an immediate reload is required, the SYSTICK_O_CVR
//! register must be written. Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the \c period supplied here
//! on the next clock after the SysTick is enabled.
//!
//! \param period is the number of clock ticks in each period of the
//! SysTick counter; must be between 1 and 16,777,216 (0x1000000), both included.
//!
//! \return None
//
//*****************************************************************************
__STATIC_INLINE void SysTickSetPeriod(uint32_t period)
{
    // Check the arguments.
    ASSERT((period > 0) && (period <= 16777216));

    // Set the period of the SysTick counter.
    HWREG(SYSTICK_BASE + SYSTICK_O_RVR) = period - 1;
}

//*****************************************************************************
//
//! \brief Gets the period of the SysTick counter.
//!
//! This function returns the rate at which the SysTick counter wraps; this
//! equals to the number of processor clocks between interrupts.
//!
//! \return Returns the period of the SysTick counter.
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTickGetPeriod(void)
{
    // Return the period of the SysTick counter.
    return (HWREG(SYSTICK_BASE + SYSTICK_O_RVR) + 1);
}

//*****************************************************************************
//
//! \brief Gets the current value of the SysTick counter.
//!
//! This function returns the current value of the SysTick counter; this will
//! be a value between the (period - 1) and zero, both included.
//!
//! \return Returns the current value of the SysTick counter
//
//*****************************************************************************
__STATIC_INLINE uint32_t SysTickGetValue(void)
{
    // Return the current value of the SysTick counter.
    return (HWREG(SYSTICK_BASE + SYSTICK_O_CVR));
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
//! Close the Doxygen group
//! @}
//! @}
//
//*****************************************************************************

#endif // __SYSTICK_H__
