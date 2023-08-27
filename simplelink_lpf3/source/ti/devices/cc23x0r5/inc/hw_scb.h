/******************************************************************************
*  Filename:       hw_scb_h
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

#ifndef __HW_SCB_H__
#define __HW_SCB_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SCB component
//
//*****************************************************************************
// CPUID Base Register
#define SCB_O_CPUID                                                 0x00000000U

// Interrupt Control State Register
#define SCB_O_ICSR                                                  0x00000004U

// Vector Table Offset Register
#define SCB_O_VTOR                                                  0x00000008U

// Application Interrupt and Reset Control Register
#define SCB_O_AIRCR                                                 0x0000000CU

// System Control Register
#define SCB_O_SCR                                                   0x00000010U

// Configuration and Control Register
#define SCB_O_CCR                                                   0x00000014U

// System Handler Priority Register 2
#define SCB_O_SHPR2                                                 0x0000001CU

// System Handler Priority Register 3
#define SCB_O_SHPR3                                                 0x00000020U

// System Handler Control and State Register
#define SCB_O_SHCSR                                                 0x00000024U

//*****************************************************************************
//
// Register: SCB_O_CPUID
//
//*****************************************************************************
// Field: [31:24] IMPLEMENTER
//
// Implementor code: 0x41 = ARM
#define SCB_CPUID_IMPLEMENTER_W                                              8U
#define SCB_CPUID_IMPLEMENTER_M                                     0xFF000000U
#define SCB_CPUID_IMPLEMENTER_S                                             24U

// Field: [23:20] VARIANT
//
// Implementation defined variant number: 0x0 (for r0)
#define SCB_CPUID_VARIANT_W                                                  4U
#define SCB_CPUID_VARIANT_M                                         0x00F00000U
#define SCB_CPUID_VARIANT_S                                                 20U

// Field: [19:16] CONSTANT
//
// Reads as 0xC
#define SCB_CPUID_CONSTANT_W                                                 4U
#define SCB_CPUID_CONSTANT_M                                        0x000F0000U
#define SCB_CPUID_CONSTANT_S                                                16U

// Field:  [15:4] PARTNO
//
// Number of processor within family: 0xC20
#define SCB_CPUID_PARTNO_W                                                  12U
#define SCB_CPUID_PARTNO_M                                          0x0000FFF0U
#define SCB_CPUID_PARTNO_S                                                   4U

// Field:   [3:0] REVISION
//
// Implementation defined revision number: 0x1 = processor p1 revision.
#define SCB_CPUID_REVISION_W                                                 4U
#define SCB_CPUID_REVISION_M                                        0x0000000FU
#define SCB_CPUID_REVISION_S                                                 0U

//*****************************************************************************
//
// Register: SCB_O_ICSR
//
//*****************************************************************************
// Field:    [31] NMIPENDSET
//
// Setting this bit will activate an NMI. Since NMI is the highest priority
// exception, it will activate as soon as it is registered. Reads back with
// current state (1 if Pending, 0 if not).
// 0x0:No effect
// 0x1:Set pending nmi
#define SCB_ICSR_NMIPENDSET                                         0x80000000U
#define SCB_ICSR_NMIPENDSET_M                                       0x80000000U
#define SCB_ICSR_NMIPENDSET_S                                               31U

// Field:    [28] PENDSVSET
//
// Set pending PendSV bit. On reads this bit returns the pending state of
// PendSV
// 0x0:No effect
// 0x1:Set pending pendsv
#define SCB_ICSR_PENDSVSET                                          0x10000000U
#define SCB_ICSR_PENDSVSET_M                                        0x10000000U
#define SCB_ICSR_PENDSVSET_S                                                28U

// Field:    [27] PENDSVCLR
//
// Clear pending PendSV bit
// 0x0:No effect
// 0x1:Clear pending pendsv
#define SCB_ICSR_PENDSVCLR                                          0x08000000U
#define SCB_ICSR_PENDSVCLR_M                                        0x08000000U
#define SCB_ICSR_PENDSVCLR_S                                                27U

// Field:    [26] PENDSTSET
//
// Set a pending SysTick bit. On reads this bit returns the pending state of
// SysTick.
// 0x0:No effect
// 0x1:Set pending systick
#define SCB_ICSR_PENDSTSET                                          0x04000000U
#define SCB_ICSR_PENDSTSET_M                                        0x04000000U
#define SCB_ICSR_PENDSTSET_S                                                26U

// Field:    [25] PENDSTCLR
//
// Clear pending SysTick bit
// 0x0:No effect
// 0x1:Clear pending systick
#define SCB_ICSR_PENDSTCLR                                          0x02000000U
#define SCB_ICSR_PENDSTCLR_M                                        0x02000000U
#define SCB_ICSR_PENDSTCLR_S                                                25U

// Field:    [23] ISRPREEMPT
//
// The system can only access this bit when the core is halted. It indicates
// that a pending interrupt is to be taken in the next running cycle. If
// C_MASKINTS is clear in the Debug Halting Control and Status Register, the
// interrupt is serviced.
// 0x0:A pending exception is not serviced.
// 0x1:A pending exception is serviced on exit from the debug halt state
#define SCB_ICSR_ISRPREEMPT                                         0x00800000U
#define SCB_ICSR_ISRPREEMPT_M                                       0x00800000U
#define SCB_ICSR_ISRPREEMPT_S                                               23U

// Field:    [22] ISRPENDING
//
// External interrupt pending flag
// 0x0:Interrupt not pending
// 0x1:Interrupt pending
#define SCB_ICSR_ISRPENDING                                         0x00400000U
#define SCB_ICSR_ISRPENDING_M                                       0x00400000U
#define SCB_ICSR_ISRPENDING_S                                               22U

// Field: [20:12] VECTPENDING
//
// Indicates the exception number for the highest priority pending exception: 0
// = no pending exceptions. Non zero = The pending state includes the effect of
// memory-mapped enable and mask registers. It does not include the PRIMASK
// special-purpose register qualifier.
#define SCB_ICSR_VECTPENDING_W                                               9U
#define SCB_ICSR_VECTPENDING_M                                      0x001FF000U
#define SCB_ICSR_VECTPENDING_S                                              12U

// Field:   [8:0] VECTACTIVE
//
// Active exception number field. Reset clears the VECTACTIVE field.
#define SCB_ICSR_VECTACTIVE_W                                                9U
#define SCB_ICSR_VECTACTIVE_M                                       0x000001FFU
#define SCB_ICSR_VECTACTIVE_S                                                0U

//*****************************************************************************
//
// Register: SCB_O_VTOR
//
//*****************************************************************************
// Field:  [31:8] TBLOFF
//
// Bits [31:8] of the indicate the vector table offset address.
#define SCB_VTOR_TBLOFF_W                                                   24U
#define SCB_VTOR_TBLOFF_M                                           0xFFFFFF00U
#define SCB_VTOR_TBLOFF_S                                                    8U

//*****************************************************************************
//
// Register: SCB_O_AIRCR
//
//*****************************************************************************
// Field: [31:16] VECTKEY
//
// Register key. To write to other parts of this register, you must ensure
// 0x5FA is written into the VECTKEY field.
#define SCB_AIRCR_VECTKEY_W                                                 16U
#define SCB_AIRCR_VECTKEY_M                                         0xFFFF0000U
#define SCB_AIRCR_VECTKEY_S                                                 16U

// Field:    [15] ENDIANESS
//
// Data endianness bit. The read value depends on the endian configuration
// implemented
// 0x0:Little endian
// 0x1:Be-8 big-endian
#define SCB_AIRCR_ENDIANESS                                         0x00008000U
#define SCB_AIRCR_ENDIANESS_M                                       0x00008000U
#define SCB_AIRCR_ENDIANESS_S                                               15U

// Field:     [2] SYSRESETREQ
//
// Writing 1 to this bit causes the SYSRESETREQ signal to the outer system to
// be asserted to request a reset. The intention is to force a large system
// reset of all major components except for debug. The C_HALT bit in the DHCSR
// is cleared as a result of the system reset requested. The debugger does not
// lose contact with the device.
#define SCB_AIRCR_SYSRESETREQ                                       0x00000004U
#define SCB_AIRCR_SYSRESETREQ_M                                     0x00000004U
#define SCB_AIRCR_SYSRESETREQ_S                                              2U

// Field:     [1] VECTCLRACTIVE
//
// Clears all active state information for fixed and configurable exceptions.
// This bit: is self-clearing, can only be set by the DAP when the core is
// halted.  When set: clears all active exception status of the processor,
// forces a return to Thread mode, forces an IPSR of 0. A debugger must
// re-initialize the stack.
#define SCB_AIRCR_VECTCLRACTIVE                                     0x00000002U
#define SCB_AIRCR_VECTCLRACTIVE_M                                   0x00000002U
#define SCB_AIRCR_VECTCLRACTIVE_S                                            1U

//*****************************************************************************
//
// Register: SCB_O_SCR
//
//*****************************************************************************
// Field:     [4] SEVONPEND
//
// When enabled, this causes WFE to wake up when an interrupt moves from
// inactive to pended. Otherwise, WFE only wakes up from an event signal,
// external and SEV instruction generated. The event input, RXEV, is registered
// even when not waiting for an event, and so effects the next WFE.
#define SCB_SCR_SEVONPEND                                           0x00000010U
#define SCB_SCR_SEVONPEND_M                                         0x00000010U
#define SCB_SCR_SEVONPEND_S                                                  4U

// Field:     [2] SLEEPDEEP
//
// Sleep deep bit.
// ENUMs:
// DSLP_EN                  indicates to the system that Cortex-M0 clock can
//                          be stopped. Setting this bit causes the
//                          SLEEPDEEP port to be asserted when the
//                          processor can be stopped.
// DSLP_DIS                 not OK to turn off system clock
#define SCB_SCR_SLEEPDEEP                                           0x00000004U
#define SCB_SCR_SLEEPDEEP_M                                         0x00000004U
#define SCB_SCR_SLEEPDEEP_S                                                  2U
#define SCB_SCR_SLEEPDEEP_DSLP_EN                                   0x00000004U
#define SCB_SCR_SLEEPDEEP_DSLP_DIS                                  0x00000000U

// Field:     [1] SLEEPONEXIT
//
// Sleep on exit when returning from Handler mode to Thread mode. Enables
// interrupt driven applications to avoid returning to empty main application.
// ENUMs:
// SLP_EN                   Sleep on return to thread mode
// SLP_DIS                  Do not sleep when returning to thread mode
#define SCB_SCR_SLEEPONEXIT                                         0x00000002U
#define SCB_SCR_SLEEPONEXIT_M                                       0x00000002U
#define SCB_SCR_SLEEPONEXIT_S                                                1U
#define SCB_SCR_SLEEPONEXIT_SLP_EN                                  0x00000002U
#define SCB_SCR_SLEEPONEXIT_SLP_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: SCB_O_CCR
//
//*****************************************************************************
// Field:     [9] STKALIGN
//
// Always set to 1. On exception entry, all exceptions are entered with 8-byte
// stack alignment and the context to restore it is saved. The SP is restored
// on the associated exception return.
#define SCB_CCR_STKALIGN                                            0x00000200U
#define SCB_CCR_STKALIGN_M                                          0x00000200U
#define SCB_CCR_STKALIGN_S                                                   9U

// Field:     [3] UNALIGN_TRP
//
// Indicates that all unaligned accesses results in a Hard Fault. Trap for
// unaligned access is fixed at 1.
#define SCB_CCR_UNALIGN_TRP                                         0x00000008U
#define SCB_CCR_UNALIGN_TRP_M                                       0x00000008U
#define SCB_CCR_UNALIGN_TRP_S                                                3U

//*****************************************************************************
//
// Register: SCB_O_SHPR2
//
//*****************************************************************************
// Field: [31:30] PRI_11
//
// Priority of system handler 11, SVCall
#define SCB_SHPR2_PRI_11_W                                                   2U
#define SCB_SHPR2_PRI_11_M                                          0xC0000000U
#define SCB_SHPR2_PRI_11_S                                                  30U

//*****************************************************************************
//
// Register: SCB_O_SHPR3
//
//*****************************************************************************
// Field: [31:30] PRI_15
//
// Priority of system handler 15, SysTick
#define SCB_SHPR3_PRI_15_W                                                   2U
#define SCB_SHPR3_PRI_15_M                                          0xC0000000U
#define SCB_SHPR3_PRI_15_S                                                  30U

// Field: [23:22] PRI_14
//
// Priority of system handler 14, PendSV
#define SCB_SHPR3_PRI_14_W                                                   2U
#define SCB_SHPR3_PRI_14_M                                          0x00C00000U
#define SCB_SHPR3_PRI_14_S                                                  22U

//*****************************************************************************
//
// Register: SCB_O_SHCSR
//
//*****************************************************************************
// Field:    [15] SVCALLPENDED
//
// Reads as 1 if SVCall is Pending.  Write 1 to set pending SVCall, write 0 to
// clear pending SVCall.
#define SCB_SHCSR_SVCALLPENDED                                      0x00008000U
#define SCB_SHCSR_SVCALLPENDED_M                                    0x00008000U
#define SCB_SHCSR_SVCALLPENDED_S                                            15U


#endif // __SCB__
