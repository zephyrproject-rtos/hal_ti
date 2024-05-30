/******************************************************************************
 *  Filename:       lrfd.c
 *
 *  Description:    Driver for LRFD
 *
 *  Copyright (c) 2023-2024 Texas Instruments Incorporated
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

#include "lrfd.h"

#include <stdbool.h>
#include "../inc/hw_types.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_clkctl.h"
#include "../inc/hw_lrfddbell.h"

#include "../driverlib/interrupt.h"

static uint16_t lrfdClockDependencySets[LRFD_NUM_CLK_DEP];

//*****************************************************************************
//
// Set clock dependency on a set of modules in LRFD.
//
//*****************************************************************************
void LRFDSetClockDependency(uint16_t mask, uint8_t dependencySetId)
{
    if (dependencySetId < LRFD_NUM_CLK_DEP)
    {
        lrfdClockDependencySets[dependencySetId] |= mask;
    }
    LRFDApplyClockDependencies();
}

//*****************************************************************************
//
// Release clock dependency on a set of modules in LRFD.
//
//*****************************************************************************
void LRFDReleaseClockDependency(uint16_t mask, uint8_t dependencySetId)
{
    if (dependencySetId < LRFD_NUM_CLK_DEP)
    {
        lrfdClockDependencySets[dependencySetId] &= ~mask;
    }
    LRFDApplyClockDependencies();
}

//*****************************************************************************
//
// Apply the currently set clock dependencies.
//
//*****************************************************************************
void LRFDApplyClockDependencies(void)
{
    uint16_t clkctl  = 0;
    bool lrfdClocked = (HWREG(CLKCTL_BASE + CLKCTL_O_CLKCFG0) & CLKCTL_CLKCFG0_LRFD_M) == CLKCTL_CLKCFG0_LRFD_CLK_EN;
    for (int i = 0; i < LRFD_NUM_CLK_DEP; i++)
    {
        clkctl |= lrfdClockDependencySets[i];
    }

    if (lrfdClocked)
    {
        // BRIDGE bit should not be needed, as hardware will automatically
        // enable the clock when needed. The bit should be always be 0 in the
        // HW, and is thus cleared.
        HWREG(LRFDDBELL_BASE + LRFDDBELL_O_CLKCTL) = clkctl & ~LRFDDBELL_CLKCTL_BRIDGE_M;

        if (clkctl == 0)
        {
            // Disable LRFD module clock
            HWREG( CLKCTL_BASE + CLKCTL_O_CLKENCLR0 ) = CLKCTL_CLKENCLR0_LRFD;
            lrfdClocked                               = false;
        }
    }
    else
    {
        if (clkctl != 0)
        {
            // Enable LRFD module clock
            HWREG( CLKCTL_BASE + CLKCTL_O_CLKENSET0 ) = CLKCTL_CLKENSET0_LRFD;

            // Wait for LRFD clock to be enabled. It is not expected that the
            // LRFD clock will ever not be enabled, but this will add sufficient
            // delay before enabling the internal LRFD clocks below.
            while ((HWREG(CLKCTL_BASE + CLKCTL_O_CLKCFG0) & CLKCTL_CLKCFG0_LRFD_M) != CLKCTL_CLKCFG0_LRFD_CLK_EN) {}

            // BRIDGE bit should not be needed, as hardware will automatically
            // enable the clock when needed. The bit should be always be 0 in
            // the HW, and is thus cleared. The bit can be used in the input to
            // indicate the need for the LRFD module clock to be enabled, but no
            // internal LRFD clocks.
            HWREG(LRFDDBELL_BASE + LRFDDBELL_O_CLKCTL) = clkctl & ~LRFDDBELL_CLKCTL_BRIDGE_M;
        }
    }
}