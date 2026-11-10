/******************************************************************************
 *  Filename:       dcache.c
 *
 *  Description:    Driver for the DCache
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

#include "../inc/hw_dcache.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"

#include "../cmsis/device.h"

#include "dcache.h"

//*****************************************************************************
//
// DCacheFlush
// Flush ENTIRE D-Cache to ensure all cached data is written to memory
// CC35xx only supports full cache flush - no address-range operation available
// Used before UDMA writes to PSRAM to ensure CPU-modified data is visible to DMA
//
//*****************************************************************************
void DCacheFlush(void)
{
    // Flush entire D-Cache
    HWREG(DCACHE_BASE + DCACHE_O_CTRL1) |= DCACHE_CTRL1_FLUSH_M;

    // Wait for flush to complete (bit self-clears when done)
    while (HWREG(DCACHE_BASE + DCACHE_O_CTRL1) & DCACHE_CTRL1_FLUSH_M)
    {
        // Busy wait
    }

    // Memory barriers to ensure flush completes before continuing
    __DSB(); // Data Synchronization Barrier
    __ISB(); // Instruction Synchronization Barrier
}

//*****************************************************************************
//
// DCacheInvalidate
// Invalidate ENTIRE D-Cache to discard all cached data
// CC35xx only supports full cache invalidate - no address-range operation available
// Used after UDMA reads from PSRAM to ensure CPU sees fresh data from memory
//
//*****************************************************************************
void DCacheInvalidate(void)
{
    // Invalidate entire D-Cache - discards ALL cached data
    HWREG(DCACHE_BASE + DCACHE_O_CTRL1) |= DCACHE_CTRL1_INVALIDATE_M;

    // Wait for invalidate to complete (bit self-clears when done)
    while (HWREG(DCACHE_BASE + DCACHE_O_CTRL1) & DCACHE_CTRL1_INVALIDATE_M) {}

    // Memory barriers to ensure invalidate completes before continuing
    __DSB(); // Data Synchronization Barrier
    __ISB(); // Instruction Synchronization Barrier
}

//*****************************************************************************
//
// DCacheDisable
// Disable D-Cache - all memory accesses bypass cache
// Must be called with interrupts disabled
// Waits for OK_TO_GO to clear indicating cache is fully stopped
//
//*****************************************************************************
void DCacheDisable(void)
{
    if (HWREG(DCACHE_BASE + DCACHE_O_CTRL) & DCACHE_CTRL_CENABLE_M)
    {
        HWREG(DCACHE_BASE + DCACHE_O_CTRL) &= ~DCACHE_CTRL_CENABLE_M;
    }

    while ((HWREG(DCACHE_BASE + DCACHE_O_STS) & DCACHE_STS_OK_TO_GO_M) != 0)
    {
        // Busy wait
    }

    __DSB();
    __ISB();
}

//*****************************************************************************
//
// DCacheEnable
// Enable D-Cache - resume normal cached memory accesses
// Must be called with interrupts disabled
// Waits for OK_TO_GO indicating cache is ready
//
//*****************************************************************************
void DCacheEnable(void)
{
    HWREG(DCACHE_BASE + DCACHE_O_CTRL) |= (1U << DCACHE_CTRL_CENABLE_S);

    while ((HWREG(DCACHE_BASE + DCACHE_O_STS) & DCACHE_STS_OK_TO_GO_M) == 0)
    {
        // Busy wait
    }

    __DSB();
    __ISB();
}
