/******************************************************************************
 *  Filename:       interrupt.c
 *
 *  Description:    Utility functions to interact with interrupts and the NVIC
 *
 *  Copyright (c) 2022-2025 Texas Instruments Incorporated
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

#include "interrupt.h"
#include "debug.h"

#include "../inc/hw_ints.h"
#include "../inc/hw_types.h"

#include "../cmsis/cc35xx.h"
#include "../cmsis/core/core_cm33.h"

//*****************************************************************************
//
// Define vector table alignment, and check that the alignment matches the
// requirements:
//  - A power of 2
//  - A minimum of 128 bytes
//  - A minimum of 4*<N>, where <N> is the number of exceptions supported.
//
//*****************************************************************************
#define VTOR_ALIGNMENT 512
#if ((VTOR_ALIGNMENT & (VTOR_ALIGNMENT - 1)) != 0) || (VTOR_ALIGNMENT < 128) || (VTOR_ALIGNMENT < NUM_INTERRUPTS * 4)
    #error "Vector table alignment is not compatible with the size of the vector table"
#endif

//*****************************************************************************
//
//! \brief The default interrupt handler.
//!
//! This is the default interrupt handler for all interrupts. It simply loops
//! forever so that the system state is preserved for observation by a
//! debugger. Since interrupts should be disabled before unregistering the
//! corresponding handler, this should never be called.
//!
//! \return None
//
//*****************************************************************************
static void IntDefaultHandler(void)
{
    // Go into an infinite loop.
    while (1) {}
}

//*****************************************************************************
//
//! \brief Global pointer to the (dynamic) interrupt vector table when placed in
//!        CRAM.
//!
//! Interrupt vector table is placed at ".ramVecs" defined in the linker file
//! provided by Texas Instruments.
//!
//! \note See \ref interrupt.c for compiler specific implementation!
//
//*****************************************************************************
#if defined(DOXYGEN)
// Dummy void pointer used as placeholder to generate Doxygen documentation.
void (*ramVectorTable[NUM_INTERRUPTS])(void);
#elif defined(__IAR_SYSTEMS_ICC__)
    #pragma data_alignment = VTOR_ALIGNMENT
static __no_init void (*ramVectorTable[NUM_INTERRUPTS])(void) @ ".ramVecs";
#elif defined(__clang__)
static __attribute__((section(".ramVecs"), aligned(VTOR_ALIGNMENT))) void (*ramVectorTable[NUM_INTERRUPTS])(void);
#elif defined(__GNUC__)
static __attribute__((section(".ramVecs"), aligned(VTOR_ALIGNMENT))) void (*ramVectorTable[NUM_INTERRUPTS])(void);
#else
    #error "Unsupported toolchain!"
#endif

//*****************************************************************************
//
// Registers a function to be called when an interrupt occurs.
//
//*****************************************************************************
void IntRegister(uint32_t intNum, void (*handler)(void))
{
    uint32_t idx;
    uint32_t tmpVtor;

    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Make sure that the RAM vector table is correctly aligned.
    ASSERT(((uint32_t)ramVectorTable & 0x000000ff) == 0);

    // See if the RAM vector table has been initialized.
    if (SCB->VTOR != (uint32_t)ramVectorTable)
    {
        // Copy the vector table from the beginning of FLASH to the RAM vector
        // table.
        tmpVtor = SCB->VTOR;
        for (idx = 0; idx < NUM_INTERRUPTS; idx++)
        {
            ramVectorTable[idx] = (void (*)(void))HWREG((idx * 4) + tmpVtor);
        }

        // Point NVIC at the RAM vector table.
        SCB->VTOR = (uint32_t)ramVectorTable;
    }

    // Save the interrupt handler.
    ramVectorTable[intNum] = handler;
}

//*****************************************************************************
//
// Unregisters the function to be called when an interrupt occurs.
//
//*****************************************************************************
void IntUnregister(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Reset the interrupt handler.
    ramVectorTable[intNum] = IntDefaultHandler;
}

//*****************************************************************************
//
// Sets the priority of an interrupt
//
//*****************************************************************************
void IntSetPriority(uint32_t intNum, uint8_t priority)
{
    // Check the arguments.
    ASSERT((intNum >= 4) && (intNum < NUM_INTERRUPTS));
    ASSERT((intNum != 8) && (intNum != 9) && (intNum != 10) && (intNum != 13));
    ASSERT(priority <= INT_PRI_LEVEL15);

    if (intNum < 16)
    {
        /* System exception priorities are set in the SHPR registers.
         * Byte indexing is used, and index 0 correspond to intNum = 4 (SHPR1.PRI_4)
         */
        SCB->SHPR[intNum - 4] = (priority & INT_PRIORITY_MASK);
    }
    else
    {
        /* User interrupt (id >= 16) priorities are set in the IPR registers
         * Byte indexing is used, and index 0 correspond to intNum = 16 (IPR0.IP_0)
         */
        NVIC->IPR[intNum - 16] = (priority & INT_PRIORITY_MASK);
    }
}

//*****************************************************************************
//
// Gets the priority of an interrupt
//
//*****************************************************************************
int32_t IntGetPriority(uint32_t intNum)
{
    // Check the arguments.
    ASSERT((intNum >= 4) && (intNum < NUM_INTERRUPTS));
    ASSERT((intNum != 8) && (intNum != 9) && (intNum != 10) && (intNum != 13));

    if (intNum < 16)
    {
        /* System exception priorities are set in the SHPR registers.
         * Byte indexing is used, and index 0 correspond to intNum = 4 (SHPR1.PRI_4)
         */
        return SCB->SHPR[intNum - 4] & INT_PRIORITY_MASK;
    }
    else
    {
        /* User interrupt (id >= 16) priorities are set in the IPR registers
         * Byte indexing is used, and index 0 correspond to intNum = 16 (IPR0.IP_0)
         */
        return NVIC->IPR[intNum - 16] & INT_PRIORITY_MASK;
    }
}

//*****************************************************************************
//
// Enables an interrupt
//
//*****************************************************************************
void IntEnable(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Determine the interrupt to enable.
    if (intNum == INT_SYSTICK)
    {
        // Enable the System Tick interrupt.
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    }
    else if ((intNum >= 16) && (intNum < NUM_INTERRUPTS))
    {
        // Subtract lower 16 irq vectors
        intNum -= 16;

        // Enable the general interrupt.
        NVIC->ISER[intNum >> 5] = 1 << (intNum & 0x1F);
    }
}

//*****************************************************************************
//
// Disables an interrupt
//
//*****************************************************************************
void IntDisable(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Determine the interrupt to disable.
    if (intNum == INT_SYSTICK)
    {
        // Disable the System Tick interrupt.
        SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    }
    else if ((intNum >= 16) && (intNum < NUM_INTERRUPTS))
    {
        // Subtract lower 16 irq vectors
        intNum -= 16;

        // Disable the general interrupt.
        NVIC->ICER[intNum >> 5] = 1 << (intNum & 0x1F);
    }
}

//*****************************************************************************
//
// Pends an interrupt
//
//*****************************************************************************
void IntSetPend(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Determine the interrupt to pend.
    if ((intNum >= 16) && (intNum < NUM_INTERRUPTS))
    {
        // Subtract lower 16 irq vectors
        intNum -= 16;

        // Pend the general interrupt.
        NVIC->ISPR[intNum >> 5] = 1 << (intNum & 0x1F);
    }
    else if (intNum == INT_NMI_FAULT)
    {
        // Pend the NMI interrupt.
        SCB->ICSR |= SCB_ICSR_NMIPENDSET_Msk;
    }
    else if (intNum == INT_PENDSV)
    {
        // Pend the PendSV interrupt.
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
    else if (intNum == INT_SYSTICK)
    {
        // Pend the SysTick interrupt.
        SCB->ICSR |= SCB_ICSR_PENDSTSET_Msk;
    }
}

//*****************************************************************************
//
// Query whether an interrupt is pending
//
//*****************************************************************************
bool IntGetPend(uint32_t intNum)
{
    uint32_t intPending;

    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Assume no interrupts are pending.
    intPending = 0;

    // The lower 16 IRQ vectors are unsupported by this function
    if (intNum < 16)
    {
        return false;
    }

    // Subtract lower 16 irq vectors
    intNum -= 16;

    // Check if the interrupt is pending
    intPending = NVIC->ISPR[intNum >> 5] & (1 << (intNum & 0x1F));

    return intPending ? true : false;
}

//*****************************************************************************
//
// Unpends an interrupt
//
//*****************************************************************************
void IntClearPend(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    // Determine the interrupt to unpend.
    if (intNum == INT_PENDSV)
    {
        // Unpend the PendSV interrupt.
        SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;
    }
    else if (intNum == INT_SYSTICK)
    {
        // Unpend the SysTick interrupt.
        SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;
    }
    else if ((intNum >= 16) && (intNum < NUM_INTERRUPTS))
    {
        // Subtract lower 16 irq vectors
        intNum -= 16;

        // Unpend the general interrupt.
        NVIC->ICPR[intNum >> 5] = 1 << (intNum & 0x1F);
    }
}
