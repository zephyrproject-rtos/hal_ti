/******************************************************************************
 *  Filename:       interrupt.h
 *
 *  Description:    Defines and prototypes for the NVIC Interrupt Controller
 *
 *  Copyright (c) 2022-2023 Texas Instruments Incorporated
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

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

//*****************************************************************************
//
//! \addtogroup system_cpu_group
//! @{
//! \addtogroup interrupt_api
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
#include "../inc/hw_types.h"

#include "../cmsis/cc23x0r5.h"
#include "../cmsis/core/core_cm0plus.h"

#include "cpu.h"

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Registers a function as an interrupt handler in the dynamic vector table.
//!
//! \note Only use this function if you want to use the dynamic vector table (in SRAM)!
//!
//! This function writes a function pointer to the dynamic interrupt vector table
//! in SRAM to register the function as an interrupt handler (ISR). When the corresponding
//! interrupt occurs, and it has been enabled (see \ref IntEnable()), the function
//! pointer is fetched from the dynamic vector table, and the System CPU will
//! execute the interrupt handler.
//!
//! \note The first call to this function (directly or indirectly via a peripheral
//! driver interrupt register function) copies the interrupt vector table from
//! Flash to SRAM. NVIC uses the static vector table (in Flash) until this function
//! is called.
//!
//! \param intNum specifies the index in the vector table to modify.
//! - System exceptions:
//!   - INT_NMI_FAULT
//!   - INT_HARD_FAULT
//!   - INT_SVCALL
//!   - INT_PENDSV
//!   - INT_SYSTICK
//! - Interrupts:
//!   - INT_CPUIRQ0
//!   - INT_CPUIRQ1
//!   - INT_CPUIRQ2
//!   - INT_CPUIRQ3
//!   - INT_CPUIRQ4
//!   - INT_GPIO_COMB
//!   - INT_LRFD_IRQ0
//!   - INT_LRFD_IRQ1
//!   - INT_DMA_DONE_COMB
//!   - INT_AES_COMB
//!   - INT_SPI0_COMB
//!   - INT_UART0_COMB
//!   - INT_I2C0_IRQ
//!   - INT_LGPT0_COMB
//!   - INT_LGPT1_COMB
//!   - INT_ADC_COMB
//!   - INT_CPUIRQ16
//!   - INT_LGPT2_COMB
//!   - INT_LGPT3_COMB
//!
//! \param handler is a pointer to the function to register as interrupt handler.
//!
//! \return None.
//!
//! \sa \ref IntUnregister(), \ref IntEnable()
//
//*****************************************************************************
extern void IntRegister(uint32_t intNum, void (*handler)(void));

//*****************************************************************************
//
//! \brief Unregisters an interrupt handler in the dynamic vector table.
//!
//! This function removes an interrupt handler from the dynamic vector table and
//! replaces it with the default interrupt handler \ref IntDefaultHandler().
//!
//! \note Remember to disable the interrupt before removing its interrupt handler
//! from the vector table.
//!
//! \param intNum specifies the index in the vector table to modify.
//! - See \ref IntRegister() for list of valid arguments.
//!
//! \return None.
//!
//! \sa \ref IntRegister(), \ref IntDisable()
//
//*****************************************************************************
extern void IntUnregister(uint32_t intNum);

//*****************************************************************************
//
//! \brief Sets the priority of an interrupt.
//!
//! This function sets the priority of an interrupt, including system exceptions.
//! When multiple interrupts are asserted simultaneously, the ones with the highest
//! priority are processed before the lower priority interrupts. Smaller numbers
//! correspond to higher interrupt priorities thus priority 0 is the highest
//! interrupt priority.
//!
//! \warning On Cortex M0+, changing interrupt priorities dynamically is not
//! supported. In order to change the priority of an interrupt, after it has
//! been enabled, the following steps must be followed:
//! - Disable the interrupt whose priority needs to be changed
//! - Change the priority
//! - Re-enable the interrupt
//! This is taken care of by the IntSetPriority function.
//!
//! \warning It is possible to lose an interrupt while its priority is being
//! changed, since that interrupt needs to be disabled to be able change its
//! priority.
//!
//! \warning This function does not support setting priority of interrupt
//! vectors one through three which are:
//! - 1: Reset handler
//! - 2: NMI handler
//! - 3: Hard fault handler
//!
//! \param intNum specifies the index in the vector table to change priority for.
//! - System exceptions:
//!   - INT_SVCALL
//!   - INT_PENDSV
//!   - INT_SYSTICK
//! - Interrupts:
//!   - INT_CPUIRQ0
//!   - INT_CPUIRQ1
//!   - INT_CPUIRQ2
//!   - INT_CPUIRQ3
//!   - INT_CPUIRQ4
//!   - INT_GPIO_COMB
//!   - INT_LRFD_IRQ0
//!   - INT_LRFD_IRQ1
//!   - INT_DMA_DONE_COMB
//!   - INT_AES_COMB
//!   - INT_SPI0_COMB
//!   - INT_UART0_COMB
//!   - INT_I2C0_IRQ
//!   - INT_LGPT0_COMB
//!   - INT_LGPT1_COMB
//!   - INT_ADC_COMB
//!   - INT_CPUIRQ16
//!   - INT_LGPT2_COMB
//!   - INT_LGPT3_COMB
//!
//! \param priority specifies the priority of the interrupt.
//! - \ref INT_PRI_LEVEL0 : Highest priority.
//! - \ref INT_PRI_LEVEL1
//! - \ref INT_PRI_LEVEL2
//! - \ref INT_PRI_LEVEL3 : Lowest priority.
//!
//! \return None
//
//*****************************************************************************
extern void IntSetPriority(uint32_t intNum, uint8_t priority);

//*****************************************************************************
//
//! \brief Gets the priority of an interrupt.
//!
//! This function gets the priority of an interrupt.
//!
//! \warning This function does not support getting priority of interrupt vectors
//! one through three which are:
//! - 1: Reset handler
//! - 2: NMI handler
//! - 3: Hard fault handler
//!
//! \param intNum specifies the index in the vector table to read priority of.
//! - See \ref IntSetPriority() for list of valid arguments.
//!
//! \return Returns the interrupt priority:
//! - \ref INT_PRI_LEVEL0 : Highest priority.
//! - \ref INT_PRI_LEVEL1
//! - \ref INT_PRI_LEVEL2
//! - \ref INT_PRI_LEVEL3 : Lowest priority.
//
//*****************************************************************************
extern int32_t IntGetPriority(uint32_t intNum);

//*****************************************************************************
//
//! \brief Check whether an interrupt is enabled.
//!
//! This function checks whether an interrupt is enabled in the NVIC.
//!
//! \param intNum specifies the index in the vector table to check.
//!
//! \return Whether the interrupt is enabled or not
//!
//! \sa \ref IntDisable()
//! \sa \ref IntEnable()
//
//*****************************************************************************
extern bool IntIsEnabled(uint32_t intNum);

//*****************************************************************************
//
//! \brief Enables an interrupt or system exception.
//!
//! This function enables the specified interrupt in the interrupt controller.
//!
//! \note If a fault condition occurs while the corresponding system exception
//! is disabled, the fault is treated as a Hard Fault.
//!
//! \param intNum specifies the index in the vector table to enable.
//!
//! \return None
//!
//! \sa \ref IntDisable()
//
//*****************************************************************************
extern void IntEnable(uint32_t intNum);

//*****************************************************************************
//
//! \brief Disables an interrupt or system exception.
//!
//! This function disables the specified interrupt in the interrupt controller.
//!
//! \param intNum specifies the index in the vector table to disable.
//! - See \ref IntEnable() for list of valid arguments.
//!
//! \return None
//!
//! \sa \ref IntEnable()
//
//*****************************************************************************
extern void IntDisable(uint32_t intNum);

//*****************************************************************************
//
//! \brief Pends an interrupt.
//!
//! This function pends the specified interrupt in the interrupt controller.
//! This causes the interrupt controller to execute the corresponding interrupt
//! handler at the next available time, based on the current interrupt state
//! priorities.
//!
//! This interrupt controller automatically clears the pending interrupt once the
//! interrupt handler is executed.
//!
//! \param intNum specifies the index in the vector table to pend.
//!
//! \return None
//!
//! \sa \ref IntEnable()
//
//*****************************************************************************
extern void IntSetPend(uint32_t intNum);

//*****************************************************************************
//
//! \brief Checks if an interrupt is pending.
//!
//! This function checks the interrupt controller to see if an interrupt is pending.
//!
//! The interrupt must be enabled in order for the corresponding interrupt handler
//! to be executed, so an interrupt can be pending waiting to be enabled or waiting
//! for an interrupt of higher priority to be done executing.
//!
//! \note This function does not support reading pending status for system exceptions
//! (vector table indexes <16).
//!
//! \param intNum specifies the index in the vector table to check pending
//! status for.
//! - See \ref IntSetPend() for list of valid arguments (except system exceptions).
//!
//! \return Returns:
//! - \c true  : Specified interrupt is pending.
//! - \c false : Specified interrupt is not pending.
//
//*****************************************************************************
extern bool IntGetPend(uint32_t intNum);

//*****************************************************************************
//
//! \brief Unpends an interrupt.
//!
//! This function unpends the specified interrupt in the interrupt controller.
//! This causes any previously generated interrupts that have not been handled yet
//! (due to higher priority interrupts or the interrupt no having been enabled
//! yet) to be discarded.
//!
//! \note It is not possible to unpend the NMI because it takes effect
//! immediately when being pended.
//!
//! \param intNum specifies the index in the vector table to unpend.
//! - See \ref IntSetPend() for list of valid arguments (except NMI).
//!
//! \return None
//
//*****************************************************************************
extern void IntClearPend(uint32_t intNum);

//*****************************************************************************
//
//! \brief Enables the CPU interrupt.
//!
//! Allows the CPU to respond to interrupts.
//!
//! \return Returns:
//! - \c true  : Interrupts were disabled and are now enabled.
//! - \c false : Interrupts were already enabled when the function was called.
//
//*****************************************************************************
__STATIC_INLINE bool IntEnableMaster(void)
{
    uint32_t interruptsDisabled = __get_PRIMASK();
    // Enable CPU interrupts.
    __enable_irq();
    return (interruptsDisabled);
}

//*****************************************************************************
//
//! \brief Disables the CPU interrupts with configurable priority.
//!
//! Prevents the CPU from receiving interrupts except NMI and hard fault. This
//! does not affect the set of interrupts enabled in the interrupt controller;
//! it just gates the interrupt from the interrupt controller to the CPU.
//!
//! \return Returns:
//! - \c true  : Interrupts were already disabled when the function was called.
//! - \c false : Interrupts were enabled and are now disabled.
//
//*****************************************************************************
__STATIC_INLINE bool IntDisableMaster(void)
{
    uint32_t interruptsDisabled = __get_PRIMASK();
    // Disable CPU interrupts.
    __disable_irq();
    return (interruptsDisabled);
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

#endif // __INTERRUPT_H__
