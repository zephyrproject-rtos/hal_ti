/******************************************************************************
 *  Filename:       interrupt.c
 *
 *  Description:    Utility functions to interact with interrupts and the NVIC
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

#include "interrupt.h"
#include "cpu.h"
#include "debug.h"

#include "../inc/hw_ints.h"
#include "../inc/hw_types.h"

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
//! \brief Global pointer to the (dynamic) interrupt vector table when placed in SRAM.
//!
//! Interrupt vector table is placed at ".ramVecs" defined in the linker file
//! provided by Texas Instruments.
//!
//! \note See \ti_code{interrupt.c} for compiler specific implementation!
//
//*****************************************************************************
#if defined(DOXYGEN)
// Dummy void pointer used as placeholder to generate Doxygen documentation.
void (*ramVectorTable[NUM_INTERRUPTS])(void);
#elif defined(__IAR_SYSTEMS_ICC__)
    #pragma data_alignment = 256
static __no_init void (*ramVectorTable[NUM_INTERRUPTS])(void) @ ".ramVecs";
#elif defined(__clang__)
static __attribute__((section(".ramVecs"), aligned(256))) void (*ramVectorTable[NUM_INTERRUPTS])(void);
#else
static __attribute__((section(".ramVecs"), aligned(256))) void (*ramVectorTable[NUM_INTERRUPTS])(void);
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
    ASSERT((intNum >= 11) && (intNum < NUM_INTERRUPTS));
    ASSERT((intNum != 12) && (intNum != 13));
    ASSERT(priority <= INT_PRI_LEVEL3);

    uint32_t ipr;
    uint32_t mask;
    uint32_t shift;
    uint32_t offset;
    bool intNumWasEnabled;
    uint32_t priorityRegIndex;
    volatile uint32_t *address;

    // System exception priorities are set in the SHPR registers.
    // Indexing starts at SHPR2 (8 <= intNum <= 11)
    if (intNum < 16)
    {
        address          = SCB->SHPR;
        priorityRegIndex = intNum - 8;
    }

    // User interrupt (id >= 16) priorities are set in the IPR registers
    // Indexing starts at IPR0 (16 <= intNum <= 19)
    else
    {
        address          = NVIC->IPR;
        priorityRegIndex = intNum - 16;
    }

    offset = priorityRegIndex >> 2;
    shift  = (priorityRegIndex & 0x3) * 8;
    mask   = 0xff << shift;

    intNumWasEnabled = IntIsEnabled(intNum);

    // Disable the interrupt before changing it's priority
    IntDisable(intNum);

    ipr = address[offset] & ~mask;
    ipr |= (priority & INT_PRIORITY_MASK) << shift;
    address[offset] = ipr;

    if (intNumWasEnabled)
    {
        // Re-enable the interrupt
        IntEnable(intNum);
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
    ASSERT((intNum >= 11) && (intNum < NUM_INTERRUPTS));
    ASSERT((intNum != 12) && (intNum != 13));

    uint32_t index = intNum >> 2;

    if (intNum < 16)
    {
        /* System exception priorities are set in the SHPR registers.
         * Indexing starts at SHPR2 (8 <= intNum <= 11)
         */
        return ((SCB->SHPR[index - 2] >> (8 * (intNum & 3))) & INT_PRIORITY_MASK);
    }
    else
    {
        /* User interrupt (id >= 16) priorities are set in the IPR registers
         * Indexing starts at IPR0 (16 <= intNum <= 19)
         */
        return ((NVIC->IPR[index - 4] >> (8 * (intNum & 3))) & INT_PRIORITY_MASK);
    }
}

//*****************************************************************************
//
// Checks whether an interrupt is enabled
//
//*****************************************************************************
bool IntIsEnabled(uint32_t intNum)
{
    // Check the arguments.
    ASSERT(intNum < NUM_INTERRUPTS);

    bool isEnabled = false;

    // Determine the interrupt to check.
    if (intNum == INT_SYSTICK)
    {
        // Check the System Tick interrupt.
        isEnabled = SysTick->CTRL & SysTick_CTRL_TICKINT_Msk ? true : false;
    }
    else if ((intNum >= 16) && (intNum <= 47))
    {
        // Check the general interrupt.
        isEnabled = (NVIC->ISER[0] & (1 << (intNum - 16))) ? true : false;
    }

    return isEnabled;
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
    else if ((intNum >= 16) && (intNum <= 47))
    {
        // Enable the general interrupt.
        NVIC->ISER[0] = 1 << (intNum - 16);
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
    else if ((intNum >= 16) && (intNum <= 47))
    {
        // Disable the general interrupt.
        NVIC->ICER[0] = 1 << (intNum - 16);
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
    if ((intNum >= 16) && (intNum <= 47))
    {
        // Pend the general interrupt.
        NVIC->ISPR[0] = 1 << (intNum - 16);
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
    intPending = NVIC->ISPR[0] & (1 << intNum);

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
    else if ((intNum >= 16) && (intNum <= 47))
    {
        // Unpend the general interrupt.
        NVIC->ICPR[0] = 1 << (intNum - 16);
    }
}
