/******************************************************************************
 *  Filename:       rtc.h
 *
 *  Description:    Defines and prototypes for the RTC module.
 *
 *  Copyright (c) 2025 Texas Instruments Incorporated
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

#ifndef __RTC_H__
#define __RTC_H__

//*****************************************************************************
//
//! \addtogroup system_control_group
//! @{
//! \addtogroup rtc_api
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
#include "../inc/hw_rtc.h"

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the current 32 bit time from the RTC.
//!
//! Since the unit is 8 us and the the output is 32 bit, overflow will occur
//! with a period of 9h 32m 39.73836s
//!
//! \return The current 32 bit time in units of 8 us.
//
//*****************************************************************************
__STATIC_INLINE uint32_t RTCGet32BitTime8Us(void)
{
    return HWREG(RTC_BASE + RTC_O_TIME8U);
}

//*****************************************************************************
//
//! \brief Get the current 48 bit time from the RTC, in units of 8 us.
//!
//! Since the unit is 8 us and the the output is 48 bit, overflow will occur
//! after approximately 71 years 147 days 11h 56m 53s
//!
//! \return The current 48 bit time in units of 8 us.
//
//*****************************************************************************
__STATIC_INLINE uint64_t RTCGet48BitTime8Us(void)
{
    // Read RTC_O_TIME524M first.
    uint32_t time524ms = HWREG(RTC_BASE + RTC_O_TIME524M);

    // Read RTC_O_TIME8U.
    uint32_t time8us = HWREG(RTC_BASE + RTC_O_TIME8U);

    // RTC_O_TIME524M and RTC_O_TIME8U overlap by 16 bytes.
    // Check if the overlapping bits are different. This is in case
    // RTC_O_TIME524M is read just before it is updated, and it updates after
    // reading RTC_O_TIME524M but before reading RTC_O_TIME8U. If that is the
    // case then the two values will not match, and we need to read
    // RTC_O_TIME524M again. It is assumed a new check is not needed since the
    // next update will be ~524ms in the future.
    //
    // Example:
    // The current 48 bit time is 0x0000FFFFFFFF
    // RTC_O_TIME524M is read as 0x0000FFFF
    // The time then updates to 0x000100000000
    // RTC_O_TIME8U is read as 0x00000000
    // The combined value will be
    // ((0x0000FFFF & 0xFFFF0000) << 16) | 0x00000000 = 0x000000000000 (WRONG)
    //
    // But if we detect that the upper bits of RTC_O_TIME8U are not the same as
    // the lower bits of RTC_O_TIME524M, then we can read RTC_O_TIME524M again
    // as 0x00010000 and the combined value will be
    // ((0x00010000 & 0xFFFF0000) << 16) | 0x00000000 = 0x000000000000 (CORRECT)
    if ((time8us >> 6U) != (time524ms & 0xFFFFU))
    {
        // Read RTC_O_TIME524M again.
        time524ms = HWREG(RTC_BASE + RTC_O_TIME524M);
    }

    // Combine the two values.
    return ((uint64_t)(time524ms & 0xFFFF0000) << 16) | (uint64_t)time8us;
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

#endif // __RTC_H__
