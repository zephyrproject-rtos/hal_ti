/******************************************************************************
 *  Filename:       dcache.h
 *
 *  Description:    Defines and prototypes for the DCache.
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

#ifndef ti_devices_dcache__include
#define ti_devices_dcache__include

//*****************************************************************************
//
//! \addtogroup system_cpu_group
//! @{
//! \addtogroup dcache_api
//! @{
//
//*****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Flush the entire D-Cache to memory.
//!
//! This function flushes all dirty cache lines to memory. CC35xx only supports
//! a full cache flush; no address-range operation is available.
//!
//! Call this function before a UDMA write to PSRAM to ensure that data
//! modified by the CPU is visible to the DMA engine.
//!
//! \return None
//
//*****************************************************************************
extern void DCacheFlush(void);

//*****************************************************************************
//
//! \brief Invalidate the entire D-Cache.
//!
//! This function discards all cached data without writing it back to memory.
//! CC35xx only supports a full cache invalidate; no address-range operation is
//! available.
//!
//! Call this function after a UDMA read from PSRAM to ensure that subsequent
//! CPU accesses fetch fresh data from memory rather than stale cache lines.
//!
//! \return None
//
//*****************************************************************************
extern void DCacheInvalidate(void);

//*****************************************************************************
//
//! \brief Disable the D-Cache.
//!
//! This function disables the D-Cache so that all memory accesses bypass the
//! cache. It must be called with interrupts disabled. The function busy-waits
//! until the cache signals that it is fully stopped (OK_TO_GO clears).
//!
//! \return None
//
//*****************************************************************************
extern void DCacheDisable(void);

//*****************************************************************************
//
//! \brief Enable the D-Cache.
//!
//! This function enables the D-Cache to resume normal cached memory accesses.
//! It must be called with interrupts disabled. The function busy-waits until
//! the cache signals that it is ready (OK_TO_GO sets).
//!
//! \return None
//
//*****************************************************************************
extern void DCacheEnable(void);

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

#endif // ti_devices_dcache__include
