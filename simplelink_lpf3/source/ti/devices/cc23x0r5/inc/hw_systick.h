/******************************************************************************
*  Filename:       hw_systick_h
******************************************************************************
*  Copyright (c) 2021 Texas Instruments Incorporated. All rights reserved.
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
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
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
******************************************************************************/

#ifndef __HW_SYSTICK_H__
#define __HW_SYSTICK_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SYSTICK component
//
//*****************************************************************************
// SysTick Control and Status Register
#define SYSTICK_O_CSR                                               0x00000000U

// SysTick Reload Value Register
#define SYSTICK_O_RVR                                               0x00000004U

// SysTick Current Value Register
#define SYSTICK_O_CVR                                               0x00000008U

// SysTick Calibration Value Register
#define SYSTICK_O_CALIB                                             0x0000000CU

//*****************************************************************************
//
// Register: SYSTICK_O_CSR
//
//*****************************************************************************
// Field:    [16] COUNTFLAG
//
// Returns 1 if timer counted to 0 since last time this was read. Clears on
// read by application or debugger.
#define SYSTICK_CSR_COUNTFLAG                                       0x00010000U
#define SYSTICK_CSR_COUNTFLAG_M                                     0x00010000U
#define SYSTICK_CSR_COUNTFLAG_S                                             16U

// Field:     [2] CLKSOURCE
//
// SysTick clock source. Always reads as one if STCALIB reports NOREF.
// 0x0:Systick driven by external reference clock.
// 0x1:Systick driven by processor clock
#define SYSTICK_CSR_CLKSOURCE                                       0x00000004U
#define SYSTICK_CSR_CLKSOURCE_M                                     0x00000004U
#define SYSTICK_CSR_CLKSOURCE_S                                              2U

// Field:     [1] TICKINT
//
//
// 0x0:Counting down to zero does not pend the systick handler. software can
// use countflag to determine if the systick handler has ever counted to zero.
// 0x1:Counting down to zero pends the systick handler.
#define SYSTICK_CSR_TICKINT                                         0x00000002U
#define SYSTICK_CSR_TICKINT_M                                       0x00000002U
#define SYSTICK_CSR_TICKINT_S                                                1U

// Field:     [0] ENABLE
//
// Enable SysTick counter
// 0x0:Counter disabled
// 0x1:Counter operates in a multi-shot way. that is, counter loads with the
// reload value and then begins counting down. on reaching 0, it sets the
// countflag to 1 and optionally pends the systick handler, based on tickint.
// it then loads the reload value again, and begins counting.
#define SYSTICK_CSR_ENABLE                                          0x00000001U
#define SYSTICK_CSR_ENABLE_M                                        0x00000001U
#define SYSTICK_CSR_ENABLE_S                                                 0U

//*****************************************************************************
//
// Register: SYSTICK_O_RVR
//
//*****************************************************************************
// Field:  [23:0] RELOAD
//
// Value to load into the SysTick Current Value Register when the counter
// reaches 0.
#define SYSTICK_RVR_RELOAD_W                                                24U
#define SYSTICK_RVR_RELOAD_M                                        0x00FFFFFFU
#define SYSTICK_RVR_RELOAD_S                                                 0U

//*****************************************************************************
//
// Register: SYSTICK_O_CVR
//
//*****************************************************************************
// Field:  [23:0] CURRENT
//
// Reads return the current value of the SysTick counter. This register is
// write-clear. Writing to it with any value clears the register to 0. Clearing
// this register also clears the COUNTFLAG bit of the SysTick Control and
// Status Register.
#define SYSTICK_CVR_CURRENT_W                                               24U
#define SYSTICK_CVR_CURRENT_M                                       0x00FFFFFFU
#define SYSTICK_CVR_CURRENT_S                                                0U

//*****************************************************************************
//
// Register: SYSTICK_O_CALIB
//
//*****************************************************************************
// Field:    [31] NOREF
//
// If reads as 1, the Reference clock is not provided - the CLKSOURCE bit of
// the SysTick Control and Status register will be forced to 1 and cannot be
// cleared to 0.
#define SYSTICK_CALIB_NOREF                                         0x80000000U
#define SYSTICK_CALIB_NOREF_M                                       0x80000000U
#define SYSTICK_CALIB_NOREF_S                                               31U

// Field:    [30] SKEW
//
// If reads as 1, the calibration value for 10ms is inexact (due to clock
// frequency).
#define SYSTICK_CALIB_SKEW                                          0x40000000U
#define SYSTICK_CALIB_SKEW_M                                        0x40000000U
#define SYSTICK_CALIB_SKEW_S                                                30U

// Field:  [23:0] TENMS
//
// An optional Reload value to be used for 10ms (100Hz) timing, subject to
// system clock skew errors. If the value reads as 0, the calibration value is
// not known.
#define SYSTICK_CALIB_TENMS_W                                               24U
#define SYSTICK_CALIB_TENMS_M                                       0x00FFFFFFU
#define SYSTICK_CALIB_TENMS_S                                                0U


#endif // __SYSTICK__
