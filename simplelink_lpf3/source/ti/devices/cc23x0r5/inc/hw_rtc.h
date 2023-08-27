/******************************************************************************
*  Filename:       hw_rtc_h
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

#ifndef __HW_RTC_H__
#define __HW_RTC_H__

//*****************************************************************************
//
// This section defines the register offsets of
// RTC component
//
//*****************************************************************************
// Module Description
#define RTC_O_DESC                                                  0x00000000U

// RTC control Register
#define RTC_O_CTL                                                   0x00000004U

// Channel Arming Set
#define RTC_O_ARMSET                                                0x00000008U

// Channel Arming Clear
#define RTC_O_ARMCLR                                                0x0000000CU

// RTC Lower Time Slice
#define RTC_O_TIME8U                                                0x00000018U

// RTC Upper Time Slice
#define RTC_O_TIME524M                                              0x0000001CU

// Channel0 compare value
#define RTC_O_CH0CC8U                                               0x00000028U

// Channel1 capture Value
#define RTC_O_CH1CC8U                                               0x00000038U

// channel1 Input Configuration
#define RTC_O_CH1CFG                                                0x0000003CU

// Interrupt mask
#define RTC_O_IMASK                                                 0x00000044U

// Raw interrupt status
#define RTC_O_RIS                                                   0x00000048U

// Masked interrupt status
#define RTC_O_MIS                                                   0x0000004CU

// Interrupt set
#define RTC_O_ISET                                                  0x00000050U

// Interrupt clear
#define RTC_O_ICLR                                                  0x00000054U

// Interrupt mask set
#define RTC_O_IMSET                                                 0x00000058U

// Interrupt clear
#define RTC_O_IMCLR                                                 0x0000005CU

// Emulation
#define RTC_O_EMU                                                   0x00000060U

//*****************************************************************************
//
// Register: RTC_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define RTC_DESC_MODID_W                                                    16U
#define RTC_DESC_MODID_M                                            0xFFFF0000U
#define RTC_DESC_MODID_S                                                    16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define RTC_DESC_STDIPOFF_W                                                  4U
#define RTC_DESC_STDIPOFF_M                                         0x0000F000U
#define RTC_DESC_STDIPOFF_S                                                 12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define RTC_DESC_INSTIDX_W                                                   4U
#define RTC_DESC_INSTIDX_M                                          0x00000F00U
#define RTC_DESC_INSTIDX_S                                                   8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define RTC_DESC_MAJREV_W                                                    4U
#define RTC_DESC_MAJREV_M                                           0x000000F0U
#define RTC_DESC_MAJREV_S                                                    4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define RTC_DESC_MINREV_W                                                    4U
#define RTC_DESC_MINREV_M                                           0x0000000FU
#define RTC_DESC_MINREV_S                                                    0U

//*****************************************************************************
//
// Register: RTC_O_CTL
//
//*****************************************************************************
// Field:     [0] RST
//
// RTC counter reset. Writing 1 to this bit will reset the RTC counter, and
// cause it to resume counting from 0x0
// ENUMs:
// CLR                      Reset the timer.
// NOEFF                    No effect
#define RTC_CTL_RST                                                 0x00000001U
#define RTC_CTL_RST_M                                               0x00000001U
#define RTC_CTL_RST_S                                                        0U
#define RTC_CTL_RST_CLR                                             0x00000001U
#define RTC_CTL_RST_NOEFF                                           0x00000000U

//*****************************************************************************
//
// Register: RTC_O_ARMSET
//
//*****************************************************************************
// Field:     [1] CH1
//
// Arming Channel 1 for capture operation.
// ENUMs:
// SET                      Enable the Channel 1 for capture operation
// NOEFF                    No effect on the channel
#define RTC_ARMSET_CH1                                              0x00000002U
#define RTC_ARMSET_CH1_M                                            0x00000002U
#define RTC_ARMSET_CH1_S                                                     1U
#define RTC_ARMSET_CH1_SET                                          0x00000002U
#define RTC_ARMSET_CH1_NOEFF                                        0x00000000U

// Field:     [0] CH0
//
// No effect on arming the channel. Read will give the status of the Channel 0.
// ENUMs:
// SET                      No effect on the compare channel
// NOEFF                    No effect on the channel
#define RTC_ARMSET_CH0                                              0x00000001U
#define RTC_ARMSET_CH0_M                                            0x00000001U
#define RTC_ARMSET_CH0_S                                                     0U
#define RTC_ARMSET_CH0_SET                                          0x00000001U
#define RTC_ARMSET_CH0_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: RTC_O_ARMCLR
//
//*****************************************************************************
// Field:     [1] CH1
//
// Disarming Channel 1
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a capture event happens in the
//                          same cycle
// NOEFF                    No effect on the channel
#define RTC_ARMCLR_CH1                                              0x00000002U
#define RTC_ARMCLR_CH1_M                                            0x00000002U
#define RTC_ARMCLR_CH1_S                                                     1U
#define RTC_ARMCLR_CH1_CLR                                          0x00000002U
#define RTC_ARMCLR_CH1_NOEFF                                        0x00000000U

// Field:     [0] CH0
//
// Disarming Channel 0
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare event happens in the
//                          same cycle
// NOEFF                    No effect on the channel
#define RTC_ARMCLR_CH0                                              0x00000001U
#define RTC_ARMCLR_CH0_M                                            0x00000001U
#define RTC_ARMCLR_CH0_S                                                     0U
#define RTC_ARMCLR_CH0_CLR                                          0x00000001U
#define RTC_ARMCLR_CH0_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: RTC_O_TIME8U
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Unsigned integer representing [34:3]slice of real time counter.
#define RTC_TIME8U_VAL_W                                                    32U
#define RTC_TIME8U_VAL_M                                            0xFFFFFFFFU
#define RTC_TIME8U_VAL_S                                                     0U

//*****************************************************************************
//
// Register: RTC_O_TIME524M
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Unsigned integer representing. [50:19]slice of real time counter.
#define RTC_TIME524M_VAL_W                                                  32U
#define RTC_TIME524M_VAL_M                                          0xFFFFFFFFU
#define RTC_TIME524M_VAL_S                                                   0U

//*****************************************************************************
//
// Register: RTC_O_CH0CC8U
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// RTC Channel 0 compare value. This value is compared against TIME8U.VAL. A
// Channel 0 event is generated when TIME8U.VAL value reaches or exceeds this
// compare value.
#define RTC_CH0CC8U_VAL_W                                                   32U
#define RTC_CH0CC8U_VAL_M                                           0xFFFFFFFFU
#define RTC_CH0CC8U_VAL_S                                                    0U

//*****************************************************************************
//
// Register: RTC_O_CH1CC8U
//
//*****************************************************************************
// Field:  [20:0] VAL
//
// TIME8U.VAL captured value at the last selected edge of capture event.
#define RTC_CH1CC8U_VAL_W                                                   21U
#define RTC_CH1CC8U_VAL_M                                           0x001FFFFFU
#define RTC_CH1CC8U_VAL_S                                                    0U

//*****************************************************************************
//
// Register: RTC_O_CH1CFG
//
//*****************************************************************************
// Field:     [0] EDGE
//
// Edge detect configuration for capture source
// ENUMs:
// FALL                     Falling Edge.
// RISE                     Rising Edge.
#define RTC_CH1CFG_EDGE                                             0x00000001U
#define RTC_CH1CFG_EDGE_M                                           0x00000001U
#define RTC_CH1CFG_EDGE_S                                                    0U
#define RTC_CH1CFG_EDGE_FALL                                        0x00000001U
#define RTC_CH1CFG_EDGE_RISE                                        0x00000000U

//*****************************************************************************
//
// Register: RTC_O_IMASK
//
//*****************************************************************************
// Field:     [1] EV1
//
// Channel 1 Event Interrupt Mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Clear Interrupt Mask
#define RTC_IMASK_EV1                                               0x00000002U
#define RTC_IMASK_EV1_M                                             0x00000002U
#define RTC_IMASK_EV1_S                                                      1U
#define RTC_IMASK_EV1_EN                                            0x00000002U
#define RTC_IMASK_EV1_DIS                                           0x00000000U

// Field:     [0] EV0
//
// Channel 0 Event Interrupt Mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define RTC_IMASK_EV0                                               0x00000001U
#define RTC_IMASK_EV0_M                                             0x00000001U
#define RTC_IMASK_EV0_S                                                      0U
#define RTC_IMASK_EV0_EN                                            0x00000001U
#define RTC_IMASK_EV0_DIS                                           0x00000000U

//*****************************************************************************
//
// Register: RTC_O_RIS
//
//*****************************************************************************
// Field:     [1] EV1
//
// Raw interrupt status for Channel 1 event.
// This bit is set to 1 when a capture event is received on Channel 1.
// This bit will be cleared when the bit in ICLR.EV1 is set to 1 or when the
// captured time value is read from the CH1CC8U register.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define RTC_RIS_EV1                                                 0x00000002U
#define RTC_RIS_EV1_M                                               0x00000002U
#define RTC_RIS_EV1_S                                                        1U
#define RTC_RIS_EV1_SET                                             0x00000002U
#define RTC_RIS_EV1_CLR                                             0x00000000U

// Field:     [0] EV0
//
// Raw interrupt status for Channel 0 event.
// This bit is set to 1 when a compare event occurs on Channel 0.
// This bit will be cleared. When the corresponding bit in ICLR.EV0 is set to
// 1. Or when a new compare value is written in CH0CC8U register
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define RTC_RIS_EV0                                                 0x00000001U
#define RTC_RIS_EV0_M                                               0x00000001U
#define RTC_RIS_EV0_S                                                        0U
#define RTC_RIS_EV0_SET                                             0x00000001U
#define RTC_RIS_EV0_CLR                                             0x00000000U

//*****************************************************************************
//
// Register: RTC_O_MIS
//
//*****************************************************************************
// Field:     [1] EV1
//
// Masked interrupt status for channel 1 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define RTC_MIS_EV1                                                 0x00000002U
#define RTC_MIS_EV1_M                                               0x00000002U
#define RTC_MIS_EV1_S                                                        1U
#define RTC_MIS_EV1_SET                                             0x00000002U
#define RTC_MIS_EV1_CLR                                             0x00000000U

// Field:     [0] EV0
//
// Masked interrupt status for channel 0 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define RTC_MIS_EV0                                                 0x00000001U
#define RTC_MIS_EV0_M                                               0x00000001U
#define RTC_MIS_EV0_S                                                        0U
#define RTC_MIS_EV0_SET                                             0x00000001U
#define RTC_MIS_EV0_CLR                                             0x00000000U

//*****************************************************************************
//
// Register: RTC_O_ISET
//
//*****************************************************************************
// Field:     [1] EV1
//
// Set Channel 1 event Interrupt.
// ENUMs:
// SET                      Set interrupt
// NO_EFFECT                Writing 0 has no effect
#define RTC_ISET_EV1                                                0x00000002U
#define RTC_ISET_EV1_M                                              0x00000002U
#define RTC_ISET_EV1_S                                                       1U
#define RTC_ISET_EV1_SET                                            0x00000002U
#define RTC_ISET_EV1_NO_EFFECT                                      0x00000000U

// Field:     [0] EV0
//
// Set Channel 0 event Interrupt.
// ENUMs:
// SET                      Set interrupt
// NO_EFFECT                Writing 0 has no effect
#define RTC_ISET_EV0                                                0x00000001U
#define RTC_ISET_EV0_M                                              0x00000001U
#define RTC_ISET_EV0_S                                                       0U
#define RTC_ISET_EV0_SET                                            0x00000001U
#define RTC_ISET_EV0_NO_EFFECT                                      0x00000000U

//*****************************************************************************
//
// Register: RTC_O_ICLR
//
//*****************************************************************************
// Field:     [1] EV1
//
// Clears channel 1 event interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NO_EFF                   Writing 0 has no effect
#define RTC_ICLR_EV1                                                0x00000002U
#define RTC_ICLR_EV1_M                                              0x00000002U
#define RTC_ICLR_EV1_S                                                       1U
#define RTC_ICLR_EV1_CLR                                            0x00000002U
#define RTC_ICLR_EV1_NO_EFF                                         0x00000000U

// Field:     [0] EV0
//
// Clears channel 0 event interrupt.
// ENUMs:
// CLR                      Clear Interrupt.
// NO_EFF                   Writing 0 has no effect
#define RTC_ICLR_EV0                                                0x00000001U
#define RTC_ICLR_EV0_M                                              0x00000001U
#define RTC_ICLR_EV0_S                                                       0U
#define RTC_ICLR_EV0_CLR                                            0x00000001U
#define RTC_ICLR_EV0_NO_EFF                                         0x00000000U

//*****************************************************************************
//
// Register: RTC_O_IMSET
//
//*****************************************************************************
// Field:     [1] EV1
//
// Set channel 1 event interrupt mask.
// ENUMs:
// SET                      Set interrupt mask
// NO_EFF                   Writing 0 has no effect
#define RTC_IMSET_EV1                                               0x00000002U
#define RTC_IMSET_EV1_M                                             0x00000002U
#define RTC_IMSET_EV1_S                                                      1U
#define RTC_IMSET_EV1_SET                                           0x00000002U
#define RTC_IMSET_EV1_NO_EFF                                        0x00000000U

// Field:     [0] EV0
//
// Set channel 0 event interrupt mask.
// ENUMs:
// SET                      Set interrupt mask
// NO_EFF                   Writing 0 has no effect
#define RTC_IMSET_EV0                                               0x00000001U
#define RTC_IMSET_EV0_M                                             0x00000001U
#define RTC_IMSET_EV0_S                                                      0U
#define RTC_IMSET_EV0_SET                                           0x00000001U
#define RTC_IMSET_EV0_NO_EFF                                        0x00000000U

//*****************************************************************************
//
// Register: RTC_O_IMCLR
//
//*****************************************************************************
// Field:     [1] EV1
//
// Clears Channel 1 event interrupt mask.
// ENUMs:
// CLR                      Clear Interrupt Mask
// NO_EFF                   Writing 0 has no effect
#define RTC_IMCLR_EV1                                               0x00000002U
#define RTC_IMCLR_EV1_M                                             0x00000002U
#define RTC_IMCLR_EV1_S                                                      1U
#define RTC_IMCLR_EV1_CLR                                           0x00000002U
#define RTC_IMCLR_EV1_NO_EFF                                        0x00000000U

// Field:     [0] EV0
//
// Clears Channel 0 event interrupt mask.
// ENUMs:
// CLR                      Clear Interrupt Mask
// NO_EFF                   Writing 0 has no effect
#define RTC_IMCLR_EV0                                               0x00000001U
#define RTC_IMCLR_EV0_M                                             0x00000001U
#define RTC_IMCLR_EV0_S                                                      0U
#define RTC_IMCLR_EV0_CLR                                           0x00000001U
#define RTC_IMCLR_EV0_NO_EFF                                        0x00000000U

//*****************************************************************************
//
// Register: RTC_O_EMU
//
//*****************************************************************************
// Field:     [0] HALT
//
// Halt control.
// ENUMs:
// STOP                     Freeze option. The IP freezes functionality when
//                          the core halted input is asserted, and resumes
//                          when it is deasserted. The freeze can either be
//                          immediate or after the IP has reached a
//                          boundary from where it can resume without
//                          corruption.
// RUN                      Free run option. The IP ignores the state of the
//                          core halted input.
#define RTC_EMU_HALT                                                0x00000001U
#define RTC_EMU_HALT_M                                              0x00000001U
#define RTC_EMU_HALT_S                                                       0U
#define RTC_EMU_HALT_STOP                                           0x00000001U
#define RTC_EMU_HALT_RUN                                            0x00000000U


#endif // __RTC__
