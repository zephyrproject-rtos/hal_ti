/******************************************************************************
*  Filename:       hw_dcb_h
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

#ifndef __HW_DCB_H__
#define __HW_DCB_H__

//*****************************************************************************
//
// This section defines the register offsets of
// DCB component
//
//*****************************************************************************
// Debug Fault Status Register
#define DCB_O_DFSR                                                  0x00000000U

// Debug Halting Control and Status Register
#define DCB_O_DHCSR                                                 0x000000C0U

// Debug Core Register Selector Register
#define DCB_O_DCRSR                                                 0x000000C4U

// Debug Core Register Data Register
#define DCB_O_DCRDR                                                 0x000000C8U

// Debug Exception and Monitor Control Register
#define DCB_O_DEMCR                                                 0x000000CCU

//*****************************************************************************
//
// Register: DCB_O_DFSR
//
//*****************************************************************************
// Field:     [4] EXTERNAL
//
// External debug request flag
// 0x0:No edbgrq external debug request occurred
// 0x1:Edbgrq has halted the core
#define DCB_DFSR_EXTERNAL                                           0x00000010U
#define DCB_DFSR_EXTERNAL_M                                         0x00000010U
#define DCB_DFSR_EXTERNAL_S                                                  4U

// Field:     [3] VCATCH
//
// Vector catch flag. When the VCATCH flag is set, a flag in the Debug
// Exception and Monitor Control Register is also set to indicate the type of
// vector catch.
// 0x0:No vector catch occurred
// 0x1:Vector catch occurred
#define DCB_DFSR_VCATCH                                             0x00000008U
#define DCB_DFSR_VCATCH_M                                           0x00000008U
#define DCB_DFSR_VCATCH_S                                                    3U

// Field:     [2] DWTRAP
//
// Data Watchpoint (DW) flag.
// 0x0:No dw match
// 0x1:Dw match
#define DCB_DFSR_DWTRAP                                             0x00000004U
#define DCB_DFSR_DWTRAP_M                                           0x00000004U
#define DCB_DFSR_DWTRAP_S                                                    2U

// Field:     [1] BKPT
//
// The BKPT flag is set by the execution of the BKPT instruction or on an
// instruction whose address triggered the breakpoint comparator match. When
// the processor has halted, the return PC points to the address of the
// breakpointed instruction.
// 0x0:No bkpt instruction or hardware breakpoint match
// 0x1:Bkpt instruction or hardware breakpoint match
#define DCB_DFSR_BKPT                                               0x00000002U
#define DCB_DFSR_BKPT_M                                             0x00000002U
#define DCB_DFSR_BKPT_S                                                      1U

// Field:     [0] HALTED
//
// Halt request flag
// 0x0:No halt request
// 0x1:Halt requested by dap access to c_halt or halted with c_step asserted
#define DCB_DFSR_HALTED                                             0x00000001U
#define DCB_DFSR_HALTED_M                                           0x00000001U
#define DCB_DFSR_HALTED_S                                                    0U

//*****************************************************************************
//
// Register: DCB_O_DHCSR
//
//*****************************************************************************
// Field:    [25] S_RESET_ST
//
// Indicates that the core has been reset, or is now being reset, since the
// last time this bit was read. This a sticky bit that clears on read. So,
// reading twice and getting 1 then 0 means it was reset in the past. Reading
// twice and getting 1 both times means that it is currently reset and held in
// reset.
#define DCB_DHCSR_S_RESET_ST                                        0x02000000U
#define DCB_DHCSR_S_RESET_ST_M                                      0x02000000U
#define DCB_DHCSR_S_RESET_ST_S                                              25U

// Field:    [24] S_RETIRE_ST
//
// Core has retired at least part of an instruction since last read. This is a
// sticky bit that clears on read.
#define DCB_DHCSR_S_RETIRE_ST                                       0x01000000U
#define DCB_DHCSR_S_RETIRE_ST_M                                     0x01000000U
#define DCB_DHCSR_S_RETIRE_ST_S                                             24U

// Field:    [17] S_HALT
//
// The core is halted in debug state only if S_HALT is set.
#define DCB_DHCSR_S_HALT                                            0x00020000U
#define DCB_DHCSR_S_HALT_M                                          0x00020000U
#define DCB_DHCSR_S_HALT_S                                                  17U

// Field:    [16] S_REGRDY
//
// Register Read/Write to the Debug Core Register Selector Register is
// available. Set in response to a successful register access.
#define DCB_DHCSR_S_REGRDY                                          0x00010000U
#define DCB_DHCSR_S_REGRDY_M                                        0x00010000U
#define DCB_DHCSR_S_REGRDY_S                                                16U

// Field:     [3] C_MASKINTS
//
// When this bit is set and debug is enabled, external interrupts, SysTick, and
// PendSV are masked. Does not affect NMI, Hard Fault or SVCall. When C_DEBUGEN
// = 0, this bit has no effect.
#define DCB_DHCSR_C_MASKINTS                                        0x00000008U
#define DCB_DHCSR_C_MASKINTS_M                                      0x00000008U
#define DCB_DHCSR_C_MASKINTS_S                                               3U

// Field:     [2] C_STEP
//
// Causes a debug event on any instruction or exception being executed,
// resulting in the core single stepping.
#define DCB_DHCSR_C_STEP                                            0x00000004U
#define DCB_DHCSR_C_STEP_M                                          0x00000004U
#define DCB_DHCSR_C_STEP_S                                                   2U

// Field:     [1] C_HALT
//
// Halts the core. This bit is set automatically when the core triggers a debug
// event, for example, on a breakpoint. This bit clears on core reset. When
// C_DEBUGEN = 0, this bit has no effect.
#define DCB_DHCSR_C_HALT                                            0x00000002U
#define DCB_DHCSR_C_HALT_M                                          0x00000002U
#define DCB_DHCSR_C_HALT_S                                                   1U

// Field:     [0] C_DEBUGEN
//
// Enables or disable debug
// ENUMs:
// DBG_EN                   Debug enabled
// DBG_DIS                  Debug disabled
#define DCB_DHCSR_C_DEBUGEN                                         0x00000001U
#define DCB_DHCSR_C_DEBUGEN_M                                       0x00000001U
#define DCB_DHCSR_C_DEBUGEN_S                                                0U
#define DCB_DHCSR_C_DEBUGEN_DBG_EN                                  0x00000001U
#define DCB_DHCSR_C_DEBUGEN_DBG_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: DCB_O_DCRSR
//
//*****************************************************************************
// Field:    [16] REGWnR
//
// Register Write-not-Read
// 0x0:Read
// 0x1:Write
#define DCB_DCRSR_REGWNR                                            0x00010000U
#define DCB_DCRSR_REGWNR_M                                          0x00010000U
#define DCB_DCRSR_REGWNR_S                                                  16U

// Field:   [4:0] REGSEL
//
// Select processor register
// 0x00:R0
// 0x01:R1
// 0x02:R2
// 0x03:R3
// 0x04:R4
// 0x05:R5
// 0x06:R6
// 0x07:R7
// 0x08:R8
// 0x09:R9
// 0x0a:R10
// 0x0b:R11
// 0x0c:R12
// 0x0d:Current sp
// 0x0e:Lr
// 0x0f:Debug Return Address
// 0x10:Xpsr flags, execution number, and state information
// 0x11:Msp (main sp)
// 0x12:Psp (process sp)
// 0x14:Control (dcrdr[25:24]), primask (dcrdr[0])
#define DCB_DCRSR_REGSEL_W                                                   5U
#define DCB_DCRSR_REGSEL_M                                          0x0000001FU
#define DCB_DCRSR_REGSEL_S                                                   0U

//*****************************************************************************
//
// Register: DCB_O_DCRDR
//
//*****************************************************************************
// Field:  [31:0] DBGTMP
//
// Data temporary cache, for reading and writing registers.
#define DCB_DCRDR_DBGTMP_W                                                  32U
#define DCB_DCRDR_DBGTMP_M                                          0xFFFFFFFFU
#define DCB_DCRDR_DBGTMP_S                                                   0U

//*****************************************************************************
//
// Register: DCB_O_DEMCR
//
//*****************************************************************************
// Field:    [24] DWTENA
//
// Global enable or disable for the DW unit
// 0x0:Dw unit disabled. watchpoint cannot halt the core. the dw pcsr reads as
// oxffffffff.
// 0x1:Dw unit enabled
#define DCB_DEMCR_DWTENA                                            0x01000000U
#define DCB_DEMCR_DWTENA_M                                          0x01000000U
#define DCB_DEMCR_DWTENA_S                                                  24U

// Field:    [10] VC_HARDERR
//
// Debug trap on a Hard Fault
#define DCB_DEMCR_VC_HARDERR                                        0x00000400U
#define DCB_DEMCR_VC_HARDERR_M                                      0x00000400U
#define DCB_DEMCR_VC_HARDERR_S                                              10U

// Field:     [0] VC_CORERESET
//
// Reset Vector Catch. Halt running system if HRESETn is asserted
#define DCB_DEMCR_VC_CORERESET                                      0x00000001U
#define DCB_DEMCR_VC_CORERESET_M                                    0x00000001U
#define DCB_DEMCR_VC_CORERESET_S                                             0U


#endif // __DCB__
