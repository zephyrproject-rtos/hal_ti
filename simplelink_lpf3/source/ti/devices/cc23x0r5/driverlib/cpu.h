/******************************************************************************
 *  Filename:       cpu.h
 *
 *  Description:    Defines and prototypes for the CPU instruction wrapper
 *                  functions.
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

#ifndef __CPU_H__
#define __CPU_H__

//*****************************************************************************
//
//! \addtogroup system_cpu_group
//! @{
//! \addtogroup cpu_api
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

//*****************************************************************************
//
// API Functions and prototypes
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Provide a small non-zero delay using a simple loop counter.
//!
//! This function provides means for generating a constant length delay. It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! \note It is not recommended using this function for long delays.
//!
//! Notice that interrupts can affect the delay if not manually disabled in advance.
//!
//! The delay depends on where code resides and the path for code fetching:
//! - Code in flash, cache enabled, prefetch enabled  : 4 cycles per loop (Default)
//! - Code in flash, cache enabled, prefetch disabled : 5 cycles per loop
//! - Code in flash, cache disabled                   : 7 cycles per loop
//! - Code in SRAM                                    : 6 cycles per loop
//! - Code in GPRAM                                   : 3 cycles per loop
//!
//! \note If using an RTOS, consider using RTOS provided delay functions because
//! these will not block task scheduling and will potentially save power.
//!
//! Calculate delay count based on the wanted delay in microseconds (us):
//! - count = [delay in us] * [CPU clock in MHz] / [cycles per loop]
//!
//! Example: 250 us delay with code in flash and with cache and prefetch enabled:
//! - count = 250 * 48 / 4 = 3000
//!
//! \param count is the number of delay loop iterations to perform. Number must be greater than zero.
//!
//! \return None
//
//*****************************************************************************
extern void CPUDelay(uint32_t count);

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

#endif // __CPU_H__
