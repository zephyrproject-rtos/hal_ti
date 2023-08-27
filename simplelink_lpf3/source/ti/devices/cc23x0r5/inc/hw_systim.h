/******************************************************************************
*  Filename:       hw_systim_h
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

#ifndef __HW_SYSTIM_H__
#define __HW_SYSTIM_H__

//*****************************************************************************
//
// This section defines the register offsets of
// SYSTIM component
//
//*****************************************************************************
// Module Description
#define SYSTIM_O_DESC                                               0x00000000U

// Interrupt mask
#define SYSTIM_O_IMASK                                              0x00000044U

// Raw interrupt status
#define SYSTIM_O_RIS                                                0x00000048U

// Masked interrupt status
#define SYSTIM_O_MIS                                                0x0000004CU

// Interrupt set
#define SYSTIM_O_ISET                                               0x00000050U

// Interrupt clear
#define SYSTIM_O_ICLR                                               0x00000054U

// Interrupt mask set
#define SYSTIM_O_IMSET                                              0x00000058U

// Interrupt mask clear
#define SYSTIM_O_IMCLR                                              0x0000005CU

// Emulation
#define SYSTIM_O_EMU                                                0x00000060U

// Systime Count Value [31:0]
#define SYSTIM_O_TIME250N                                           0x00000100U

// Systime Count Value [33:2]
#define SYSTIM_O_TIME1U                                             0x00000104U

// channel's Ouput Value
#define SYSTIM_O_OUT                                                0x00000108U

// channel0 Configuration.
#define SYSTIM_O_CH0CFG                                             0x0000010CU

// channel1 Configuration.
#define SYSTIM_O_CH1CFG                                             0x00000110U

// channel2 Configuration.
#define SYSTIM_O_CH2CFG                                             0x00000114U

// channel3 Configuration.
#define SYSTIM_O_CH3CFG                                             0x00000118U

// channel4 Configuration.
#define SYSTIM_O_CH4CFG                                             0x0000011CU

// Channel 0 Capture/Compare Value
#define SYSTIM_O_CH0CC                                              0x00000120U

// Channel 1 Capture/Compare Value
#define SYSTIM_O_CH1CC                                              0x00000124U

// Channel 2 Capture/Compare Value
#define SYSTIM_O_CH2CC                                              0x00000128U

// Channel 3 Capture/Compare Value
#define SYSTIM_O_CH3CC                                              0x0000012CU

// Channel 4 Capture/Compare Value
#define SYSTIM_O_CH4CC                                              0x00000130U

// Systimer's Time bit
#define SYSTIM_O_TIMEBIT                                            0x00000134U

// Timer Status
#define SYSTIM_O_STATUS                                             0x00000140U

// Channel arming set
#define SYSTIM_O_ARMSET                                             0x00000144U

// Channel Arming clear
#define SYSTIM_O_ARMCLR                                             0x00000148U

// Channel 0 Save/Restore Value
#define SYSTIM_O_CH0CCSR                                            0x0000014CU

// Channel 1 Save/Restore Value
#define SYSTIM_O_CH1CCSR                                            0x00000150U

// Channel 2 Save/Restore Value
#define SYSTIM_O_CH2CCSR                                            0x00000154U

// Channel 3 Save/Restore Value
#define SYSTIM_O_CH3CCSR                                            0x00000158U

// Channel 4 Save/Restore Value
#define SYSTIM_O_CH4CCSR                                            0x0000015CU

//*****************************************************************************
//
// Register: SYSTIM_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define SYSTIM_DESC_MODID_W                                                 16U
#define SYSTIM_DESC_MODID_M                                         0xFFFF0000U
#define SYSTIM_DESC_MODID_S                                                 16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define SYSTIM_DESC_STDIPOFF_W                                               4U
#define SYSTIM_DESC_STDIPOFF_M                                      0x0000F000U
#define SYSTIM_DESC_STDIPOFF_S                                              12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exists in SOC, this field
// can identify the instance number 0-15
#define SYSTIM_DESC_INSTIDX_W                                                4U
#define SYSTIM_DESC_INSTIDX_M                                       0x00000F00U
#define SYSTIM_DESC_INSTIDX_S                                                8U

// Field:   [7:4] MAJREV
//
// Major revision of IP 0-15
#define SYSTIM_DESC_MAJREV_W                                                 4U
#define SYSTIM_DESC_MAJREV_M                                        0x000000F0U
#define SYSTIM_DESC_MAJREV_S                                                 4U

// Field:   [3:0] MINREV
//
// Minor revision of IP 0-15.
#define SYSTIM_DESC_MINREV_W                                                 4U
#define SYSTIM_DESC_MINREV_M                                        0x0000000FU
#define SYSTIM_DESC_MINREV_S                                                 0U

//*****************************************************************************
//
// Register: SYSTIM_O_IMASK
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Systimer counter overflow event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_OVFL                                           0x00000020U
#define SYSTIM_IMASK_OVFL_M                                         0x00000020U
#define SYSTIM_IMASK_OVFL_S                                                  5U
#define SYSTIM_IMASK_OVFL_EN                                        0x00000020U
#define SYSTIM_IMASK_OVFL_DIS                                       0x00000000U

// Field:     [4] EV4
//
// Systimer channel 4 event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_EV4                                            0x00000010U
#define SYSTIM_IMASK_EV4_M                                          0x00000010U
#define SYSTIM_IMASK_EV4_S                                                   4U
#define SYSTIM_IMASK_EV4_EN                                         0x00000010U
#define SYSTIM_IMASK_EV4_DIS                                        0x00000000U

// Field:     [3] EV3
//
// Systimer channel 3 event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_EV3                                            0x00000008U
#define SYSTIM_IMASK_EV3_M                                          0x00000008U
#define SYSTIM_IMASK_EV3_S                                                   3U
#define SYSTIM_IMASK_EV3_EN                                         0x00000008U
#define SYSTIM_IMASK_EV3_DIS                                        0x00000000U

// Field:     [2] EV2
//
// Systimer channel 2 event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_EV2                                            0x00000004U
#define SYSTIM_IMASK_EV2_M                                          0x00000004U
#define SYSTIM_IMASK_EV2_S                                                   2U
#define SYSTIM_IMASK_EV2_EN                                         0x00000004U
#define SYSTIM_IMASK_EV2_DIS                                        0x00000000U

// Field:     [1] EV1
//
// Systimer channel 1 event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_EV1                                            0x00000002U
#define SYSTIM_IMASK_EV1_M                                          0x00000002U
#define SYSTIM_IMASK_EV1_S                                                   1U
#define SYSTIM_IMASK_EV1_EN                                         0x00000002U
#define SYSTIM_IMASK_EV1_DIS                                        0x00000000U

// Field:     [0] EV0
//
// Systimer channel 0 event interrupt mask.
// ENUMs:
// EN                       Enable Interrrupt Mask
// DIS                      Disable Interrupt Mask
#define SYSTIM_IMASK_EV0                                            0x00000001U
#define SYSTIM_IMASK_EV0_M                                          0x00000001U
#define SYSTIM_IMASK_EV0_S                                                   0U
#define SYSTIM_IMASK_EV0_EN                                         0x00000001U
#define SYSTIM_IMASK_EV0_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_RIS
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Raw interrupt status for Systimer counter overflow event.
// This bit is set to 1 when an event is received on SysTimer Overflow occurs.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_OVFL                                             0x00000020U
#define SYSTIM_RIS_OVFL_M                                           0x00000020U
#define SYSTIM_RIS_OVFL_S                                                    5U
#define SYSTIM_RIS_OVFL_SET                                         0x00000020U
#define SYSTIM_RIS_OVFL_CLR                                         0x00000000U

// Field:     [4] EV4
//
// Raw interrupt status for channel 4 event.
// This bit is set to 1 when a CAPTURE or COMPARE event is received on channel
// 4.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_EV4                                              0x00000010U
#define SYSTIM_RIS_EV4_M                                            0x00000010U
#define SYSTIM_RIS_EV4_S                                                     4U
#define SYSTIM_RIS_EV4_SET                                          0x00000010U
#define SYSTIM_RIS_EV4_CLR                                          0x00000000U

// Field:     [3] EV3
//
// Raw interrupt status for channel 3 event.
// This bit is set to 1 when a CAPTURE or COMPARE event is received on channel
// 3.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_EV3                                              0x00000008U
#define SYSTIM_RIS_EV3_M                                            0x00000008U
#define SYSTIM_RIS_EV3_S                                                     3U
#define SYSTIM_RIS_EV3_SET                                          0x00000008U
#define SYSTIM_RIS_EV3_CLR                                          0x00000000U

// Field:     [2] EV2
//
// Raw interrupt status for channel 2 Event.
// This bit is set to 1 when a CAPTURE or COMPARE event is received on channel
// 2.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_EV2                                              0x00000004U
#define SYSTIM_RIS_EV2_M                                            0x00000004U
#define SYSTIM_RIS_EV2_S                                                     2U
#define SYSTIM_RIS_EV2_SET                                          0x00000004U
#define SYSTIM_RIS_EV2_CLR                                          0x00000000U

// Field:     [1] EV1
//
// Raw interrupt status for channel 1 event.
// This bit is set to 1 when a CAPTURE or COMPARE event is received on channel
// 1.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_EV1                                              0x00000002U
#define SYSTIM_RIS_EV1_M                                            0x00000002U
#define SYSTIM_RIS_EV1_S                                                     1U
#define SYSTIM_RIS_EV1_SET                                          0x00000002U
#define SYSTIM_RIS_EV1_CLR                                          0x00000000U

// Field:     [0] EV0
//
// Raw interrupt status for channel 0 event.
// This bit is set to 1 when a CAPTURE or COMPARE event is received on channel
// 0.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_RIS_EV0                                              0x00000001U
#define SYSTIM_RIS_EV0_M                                            0x00000001U
#define SYSTIM_RIS_EV0_S                                                     0U
#define SYSTIM_RIS_EV0_SET                                          0x00000001U
#define SYSTIM_RIS_EV0_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_MIS
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Mask Interrupt status for Systimer counter overflow Event in MIS register.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_OVFL                                             0x00000020U
#define SYSTIM_MIS_OVFL_M                                           0x00000020U
#define SYSTIM_MIS_OVFL_S                                                    5U
#define SYSTIM_MIS_OVFL_SET                                         0x00000020U
#define SYSTIM_MIS_OVFL_CLR                                         0x00000000U

// Field:     [4] EV4
//
// Mask interrupt status for channel 4 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_EV4                                              0x00000010U
#define SYSTIM_MIS_EV4_M                                            0x00000010U
#define SYSTIM_MIS_EV4_S                                                     4U
#define SYSTIM_MIS_EV4_SET                                          0x00000010U
#define SYSTIM_MIS_EV4_CLR                                          0x00000000U

// Field:     [3] EV3
//
// Mask interrupt status for channel 3 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_EV3                                              0x00000008U
#define SYSTIM_MIS_EV3_M                                            0x00000008U
#define SYSTIM_MIS_EV3_S                                                     3U
#define SYSTIM_MIS_EV3_SET                                          0x00000008U
#define SYSTIM_MIS_EV3_CLR                                          0x00000000U

// Field:     [2] EV2
//
// Mask interrupt status for channel 2 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_EV2                                              0x00000004U
#define SYSTIM_MIS_EV2_M                                            0x00000004U
#define SYSTIM_MIS_EV2_S                                                     2U
#define SYSTIM_MIS_EV2_SET                                          0x00000004U
#define SYSTIM_MIS_EV2_CLR                                          0x00000000U

// Field:     [1] EV1
//
// Mask interrupt status for channel 1 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_EV1                                              0x00000002U
#define SYSTIM_MIS_EV1_M                                            0x00000002U
#define SYSTIM_MIS_EV1_S                                                     1U
#define SYSTIM_MIS_EV1_SET                                          0x00000002U
#define SYSTIM_MIS_EV1_CLR                                          0x00000000U

// Field:     [0] EV0
//
// Mask interrupt status for channel 0 event.
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define SYSTIM_MIS_EV0                                              0x00000001U
#define SYSTIM_MIS_EV0_M                                            0x00000001U
#define SYSTIM_MIS_EV0_S                                                     0U
#define SYSTIM_MIS_EV0_SET                                          0x00000001U
#define SYSTIM_MIS_EV0_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_ISET
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Sets Systimer counter overflow  interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_OVFL                                            0x00000020U
#define SYSTIM_ISET_OVFL_M                                          0x00000020U
#define SYSTIM_ISET_OVFL_S                                                   5U
#define SYSTIM_ISET_OVFL_SET                                        0x00000020U
#define SYSTIM_ISET_OVFL_NOEFF                                      0x00000000U

// Field:     [4] EV4
//
// Sets channel 4 interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_EV4                                             0x00000010U
#define SYSTIM_ISET_EV4_M                                           0x00000010U
#define SYSTIM_ISET_EV4_S                                                    4U
#define SYSTIM_ISET_EV4_SET                                         0x00000010U
#define SYSTIM_ISET_EV4_NOEFF                                       0x00000000U

// Field:     [3] EV3
//
// Sets channel 3 interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_EV3                                             0x00000008U
#define SYSTIM_ISET_EV3_M                                           0x00000008U
#define SYSTIM_ISET_EV3_S                                                    3U
#define SYSTIM_ISET_EV3_SET                                         0x00000008U
#define SYSTIM_ISET_EV3_NOEFF                                       0x00000000U

// Field:     [2] EV2
//
// Sets channel 2 interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_EV2                                             0x00000004U
#define SYSTIM_ISET_EV2_M                                           0x00000004U
#define SYSTIM_ISET_EV2_S                                                    2U
#define SYSTIM_ISET_EV2_SET                                         0x00000004U
#define SYSTIM_ISET_EV2_NOEFF                                       0x00000000U

// Field:     [1] EV1
//
// Sets channel 1 interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_EV1                                             0x00000002U
#define SYSTIM_ISET_EV1_M                                           0x00000002U
#define SYSTIM_ISET_EV1_S                                                    1U
#define SYSTIM_ISET_EV1_SET                                         0x00000002U
#define SYSTIM_ISET_EV1_NOEFF                                       0x00000000U

// Field:     [0] EV0
//
// Sets channel 0 interrupt.
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ISET_EV0                                             0x00000001U
#define SYSTIM_ISET_EV0_M                                           0x00000001U
#define SYSTIM_ISET_EV0_S                                                    0U
#define SYSTIM_ISET_EV0_SET                                         0x00000001U
#define SYSTIM_ISET_EV0_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_ICLR
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Clears Systimer counter overflow  interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_OVFL                                            0x00000020U
#define SYSTIM_ICLR_OVFL_M                                          0x00000020U
#define SYSTIM_ICLR_OVFL_S                                                   5U
#define SYSTIM_ICLR_OVFL_CLR                                        0x00000020U
#define SYSTIM_ICLR_OVFL_NOEFF                                      0x00000000U

// Field:     [4] EV4
//
// Clears channel 4 interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_EV4                                             0x00000010U
#define SYSTIM_ICLR_EV4_M                                           0x00000010U
#define SYSTIM_ICLR_EV4_S                                                    4U
#define SYSTIM_ICLR_EV4_CLR                                         0x00000010U
#define SYSTIM_ICLR_EV4_NOEFF                                       0x00000000U

// Field:     [3] EV3
//
// Clears channel 3 interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_EV3                                             0x00000008U
#define SYSTIM_ICLR_EV3_M                                           0x00000008U
#define SYSTIM_ICLR_EV3_S                                                    3U
#define SYSTIM_ICLR_EV3_CLR                                         0x00000008U
#define SYSTIM_ICLR_EV3_NOEFF                                       0x00000000U

// Field:     [2] EV2
//
// Clears channel 2 interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_EV2                                             0x00000004U
#define SYSTIM_ICLR_EV2_M                                           0x00000004U
#define SYSTIM_ICLR_EV2_S                                                    2U
#define SYSTIM_ICLR_EV2_CLR                                         0x00000004U
#define SYSTIM_ICLR_EV2_NOEFF                                       0x00000000U

// Field:     [1] EV1
//
// Clears channel 1 interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_EV1                                             0x00000002U
#define SYSTIM_ICLR_EV1_M                                           0x00000002U
#define SYSTIM_ICLR_EV1_S                                                    1U
#define SYSTIM_ICLR_EV1_CLR                                         0x00000002U
#define SYSTIM_ICLR_EV1_NOEFF                                       0x00000000U

// Field:     [0] EV0
//
// Clears channel 0 interrupt.
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define SYSTIM_ICLR_EV0                                             0x00000001U
#define SYSTIM_ICLR_EV0_M                                           0x00000001U
#define SYSTIM_ICLR_EV0_S                                                    0U
#define SYSTIM_ICLR_EV0_CLR                                         0x00000001U
#define SYSTIM_ICLR_EV0_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_IMSET
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Sets Timer Overflow Event Interrupt Mask.
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_OVFL                                           0x00000020U
#define SYSTIM_IMSET_OVFL_M                                         0x00000020U
#define SYSTIM_IMSET_OVFL_S                                                  5U
#define SYSTIM_IMSET_OVFL_SET                                       0x00000020U
#define SYSTIM_IMSET_OVFL_NOEFF                                     0x00000000U

// Field:     [4] EV4
//
// Sets channel4 Event Interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_EV4                                            0x00000010U
#define SYSTIM_IMSET_EV4_M                                          0x00000010U
#define SYSTIM_IMSET_EV4_S                                                   4U
#define SYSTIM_IMSET_EV4_SET                                        0x00000010U
#define SYSTIM_IMSET_EV4_NOEFF                                      0x00000000U

// Field:     [3] EV3
//
// Sets channel3 Event Interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_EV3                                            0x00000008U
#define SYSTIM_IMSET_EV3_M                                          0x00000008U
#define SYSTIM_IMSET_EV3_S                                                   3U
#define SYSTIM_IMSET_EV3_SET                                        0x00000008U
#define SYSTIM_IMSET_EV3_NOEFF                                      0x00000000U

// Field:     [2] EV2
//
// Sets channel2 Event Interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_EV2                                            0x00000004U
#define SYSTIM_IMSET_EV2_M                                          0x00000004U
#define SYSTIM_IMSET_EV2_S                                                   2U
#define SYSTIM_IMSET_EV2_SET                                        0x00000004U
#define SYSTIM_IMSET_EV2_NOEFF                                      0x00000000U

// Field:     [1] EV1
//
// Sets channel1 Event Interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_EV1                                            0x00000002U
#define SYSTIM_IMSET_EV1_M                                          0x00000002U
#define SYSTIM_IMSET_EV1_S                                                   1U
#define SYSTIM_IMSET_EV1_SET                                        0x00000002U
#define SYSTIM_IMSET_EV1_NOEFF                                      0x00000000U

// Field:     [0] EV0
//
// Sets channel0 Event Interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMSET_EV0                                            0x00000001U
#define SYSTIM_IMSET_EV0_M                                          0x00000001U
#define SYSTIM_IMSET_EV0_S                                                   0U
#define SYSTIM_IMSET_EV0_SET                                        0x00000001U
#define SYSTIM_IMSET_EV0_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_IMCLR
//
//*****************************************************************************
// Field:     [5] OVFL
//
// Clears Timer Overflow Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_OVFL                                           0x00000020U
#define SYSTIM_IMCLR_OVFL_M                                         0x00000020U
#define SYSTIM_IMCLR_OVFL_S                                                  5U
#define SYSTIM_IMCLR_OVFL_CLR                                       0x00000020U
#define SYSTIM_IMCLR_OVFL_NOEFF                                     0x00000000U

// Field:     [4] EV4
//
// Clears channel4 Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_EV4                                            0x00000010U
#define SYSTIM_IMCLR_EV4_M                                          0x00000010U
#define SYSTIM_IMCLR_EV4_S                                                   4U
#define SYSTIM_IMCLR_EV4_CLR                                        0x00000010U
#define SYSTIM_IMCLR_EV4_NOEFF                                      0x00000000U

// Field:     [3] EV3
//
// Clears channel3 Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_EV3                                            0x00000008U
#define SYSTIM_IMCLR_EV3_M                                          0x00000008U
#define SYSTIM_IMCLR_EV3_S                                                   3U
#define SYSTIM_IMCLR_EV3_CLR                                        0x00000008U
#define SYSTIM_IMCLR_EV3_NOEFF                                      0x00000000U

// Field:     [2] EV2
//
// Clears channel2 Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_EV2                                            0x00000004U
#define SYSTIM_IMCLR_EV2_M                                          0x00000004U
#define SYSTIM_IMCLR_EV2_S                                                   2U
#define SYSTIM_IMCLR_EV2_CLR                                        0x00000004U
#define SYSTIM_IMCLR_EV2_NOEFF                                      0x00000000U

// Field:     [1] EV1
//
// Clears channel1 Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_EV1                                            0x00000002U
#define SYSTIM_IMCLR_EV1_M                                          0x00000002U
#define SYSTIM_IMCLR_EV1_S                                                   1U
#define SYSTIM_IMCLR_EV1_CLR                                        0x00000002U
#define SYSTIM_IMCLR_EV1_NOEFF                                      0x00000000U

// Field:     [0] EV0
//
// Clears channel0 Event Interrupt Mask.
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define SYSTIM_IMCLR_EV0                                            0x00000001U
#define SYSTIM_IMCLR_EV0_M                                          0x00000001U
#define SYSTIM_IMCLR_EV0_S                                                   0U
#define SYSTIM_IMCLR_EV0_CLR                                        0x00000001U
#define SYSTIM_IMCLR_EV0_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_EMU
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
#define SYSTIM_EMU_HALT                                             0x00000001U
#define SYSTIM_EMU_HALT_M                                           0x00000001U
#define SYSTIM_EMU_HALT_S                                                    0U
#define SYSTIM_EMU_HALT_STOP                                        0x00000001U
#define SYSTIM_EMU_HALT_RUN                                         0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_TIME250N
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// 32-bit counter value [31:0]. This will provide a 250ns resolution and a
// range of 17.9m.
#define SYSTIM_TIME250N_VAL_W                                               32U
#define SYSTIM_TIME250N_VAL_M                                       0xFFFFFFFFU
#define SYSTIM_TIME250N_VAL_S                                                0U

//*****************************************************************************
//
// Register: SYSTIM_O_TIME1U
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// 32-bit counter value [33:2]. This will provide a resolution of 1us and a
// range of 1hr and 11m.
#define SYSTIM_TIME1U_VAL_W                                                 32U
#define SYSTIM_TIME1U_VAL_M                                         0xFFFFFFFFU
#define SYSTIM_TIME1U_VAL_S                                                  0U

//*****************************************************************************
//
// Register: SYSTIM_O_OUT
//
//*****************************************************************************
// Field:     [4] OUT4
//
// Output Value of channel 4.
// ENUMs:
// SET                      Event occured
// CLR                      Event did not occur.
#define SYSTIM_OUT_OUT4                                             0x00000010U
#define SYSTIM_OUT_OUT4_M                                           0x00000010U
#define SYSTIM_OUT_OUT4_S                                                    4U
#define SYSTIM_OUT_OUT4_SET                                         0x00000010U
#define SYSTIM_OUT_OUT4_CLR                                         0x00000000U

// Field:     [3] OUT3
//
// Output Value of channel 3.
// ENUMs:
// SET                      Event occured
// CLR                      Event did not occur.
#define SYSTIM_OUT_OUT3                                             0x00000008U
#define SYSTIM_OUT_OUT3_M                                           0x00000008U
#define SYSTIM_OUT_OUT3_S                                                    3U
#define SYSTIM_OUT_OUT3_SET                                         0x00000008U
#define SYSTIM_OUT_OUT3_CLR                                         0x00000000U

// Field:     [2] OUT2
//
// Output Value of channel 2.
// ENUMs:
// SET                      Event occured
// CLR                      Event did not occur.
#define SYSTIM_OUT_OUT2                                             0x00000004U
#define SYSTIM_OUT_OUT2_M                                           0x00000004U
#define SYSTIM_OUT_OUT2_S                                                    2U
#define SYSTIM_OUT_OUT2_SET                                         0x00000004U
#define SYSTIM_OUT_OUT2_CLR                                         0x00000000U

// Field:     [1] OUT1
//
// Output Value of channel 1.
// ENUMs:
// SET                      Event occured
// CLR                      Event did not occur.
#define SYSTIM_OUT_OUT1                                             0x00000002U
#define SYSTIM_OUT_OUT1_M                                           0x00000002U
#define SYSTIM_OUT_OUT1_S                                                    1U
#define SYSTIM_OUT_OUT1_SET                                         0x00000002U
#define SYSTIM_OUT_OUT1_CLR                                         0x00000000U

// Field:     [0] OUT0
//
// Output Value of channel 0.
// ENUMs:
// SET                      Event occured
// CLR                      Event did not occur.
#define SYSTIM_OUT_OUT0                                             0x00000001U
#define SYSTIM_OUT_OUT0_M                                           0x00000001U
#define SYSTIM_OUT_OUT0_S                                                    0U
#define SYSTIM_OUT_OUT0_SET                                         0x00000001U
#define SYSTIM_OUT_OUT0_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH0CFG
//
//*****************************************************************************
// Field:     [4] RES
//
// This bit decides the RESOLUTION of the channel that will be used.
// ENUMs:
// NS                       channel Works in Timer's 250ns resolution
// US                       channel Works in Timer's 1us Resolution.
#define SYSTIM_CH0CFG_RES                                           0x00000010U
#define SYSTIM_CH0CFG_RES_M                                         0x00000010U
#define SYSTIM_CH0CFG_RES_S                                                  4U
#define SYSTIM_CH0CFG_RES_NS                                        0x00000010U
#define SYSTIM_CH0CFG_RES_US                                        0x00000000U

// Field:     [3] REARM
//
// When Rearm is enabled the channel remains in continous capture mode.
// Otherwise it'll be in one shot capture mode. Rearm is only valid for capture
// mode.
// ENUMs:
// EN                       Re arm is enabled
// DIS                      Re Arm is disabled
#define SYSTIM_CH0CFG_REARM                                         0x00000008U
#define SYSTIM_CH0CFG_REARM_M                                       0x00000008U
#define SYSTIM_CH0CFG_REARM_S                                                3U
#define SYSTIM_CH0CFG_REARM_EN                                      0x00000008U
#define SYSTIM_CH0CFG_REARM_DIS                                     0x00000000U

// Field:   [2:1] INP
//
// Decides the channel input signal's mode. Setting the Value as 2'b11 selects
// the Rise Function.
// ENUMs:
// BOTH                     Capture on both Edge
// FALL                     Capture on Falling Edge
// RISE                     Capture on rising edge
#define SYSTIM_CH0CFG_INP_W                                                  2U
#define SYSTIM_CH0CFG_INP_M                                         0x00000006U
#define SYSTIM_CH0CFG_INP_S                                                  1U
#define SYSTIM_CH0CFG_INP_BOTH                                      0x00000004U
#define SYSTIM_CH0CFG_INP_FALL                                      0x00000002U
#define SYSTIM_CH0CFG_INP_RISE                                      0x00000000U

// Field:     [0] MODE
//
// Decides the channel mode.
// ENUMs:
// CAPT                     channel is in capture mode
// DIS                      channel is disabled
#define SYSTIM_CH0CFG_MODE                                          0x00000001U
#define SYSTIM_CH0CFG_MODE_M                                        0x00000001U
#define SYSTIM_CH0CFG_MODE_S                                                 0U
#define SYSTIM_CH0CFG_MODE_CAPT                                     0x00000001U
#define SYSTIM_CH0CFG_MODE_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH1CFG
//
//*****************************************************************************
// Field:     [3] REARM
//
// When Rearm is enabled the channel remains in continous capture mode.
// Otherwise it'll be in one shot capture mode. Rearm is only valid for capture
// mode.
// ENUMs:
// EN                       Re arm is enabled
// DIS                      Re Arm is disabled
#define SYSTIM_CH1CFG_REARM                                         0x00000008U
#define SYSTIM_CH1CFG_REARM_M                                       0x00000008U
#define SYSTIM_CH1CFG_REARM_S                                                3U
#define SYSTIM_CH1CFG_REARM_EN                                      0x00000008U
#define SYSTIM_CH1CFG_REARM_DIS                                     0x00000000U

// Field:   [2:1] INP
//
// Decides the channel input signal's mode. Setting the Value as 2'b11 selects
// the Rise Function
// ENUMs:
// BOTH                     Capture on both Edge
// FALL                     Capture on Falling Edge
// RISE                     Capture on rising edge
#define SYSTIM_CH1CFG_INP_W                                                  2U
#define SYSTIM_CH1CFG_INP_M                                         0x00000006U
#define SYSTIM_CH1CFG_INP_S                                                  1U
#define SYSTIM_CH1CFG_INP_BOTH                                      0x00000004U
#define SYSTIM_CH1CFG_INP_FALL                                      0x00000002U
#define SYSTIM_CH1CFG_INP_RISE                                      0x00000000U

// Field:     [0] MODE
//
// Decides the channel mode.
// ENUMs:
// CAPT                     channel is in capture mode
// DIS                      channel is disabled
#define SYSTIM_CH1CFG_MODE                                          0x00000001U
#define SYSTIM_CH1CFG_MODE_M                                        0x00000001U
#define SYSTIM_CH1CFG_MODE_S                                                 0U
#define SYSTIM_CH1CFG_MODE_CAPT                                     0x00000001U
#define SYSTIM_CH1CFG_MODE_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH2CFG
//
//*****************************************************************************
// Field:     [3] REARM
//
// When Rearm is enabled the channel remains in continous capture mode.
// Otherwise it'll be in one shot capture mode. Rearm is only valid for capture
// mode.
// ENUMs:
// EN                       Re arm is enabled
// DIS                      Re Arm is disabled
#define SYSTIM_CH2CFG_REARM                                         0x00000008U
#define SYSTIM_CH2CFG_REARM_M                                       0x00000008U
#define SYSTIM_CH2CFG_REARM_S                                                3U
#define SYSTIM_CH2CFG_REARM_EN                                      0x00000008U
#define SYSTIM_CH2CFG_REARM_DIS                                     0x00000000U

// Field:   [2:1] INP
//
// Decides the channel input signal's mode. Setting the Value as 2'b11 selects
// the Rise Function
// ENUMs:
// BOTH                     Capture on both Edge
// FALL                     Capture on Falling Edge
// RISE                     Capture on rising edge
#define SYSTIM_CH2CFG_INP_W                                                  2U
#define SYSTIM_CH2CFG_INP_M                                         0x00000006U
#define SYSTIM_CH2CFG_INP_S                                                  1U
#define SYSTIM_CH2CFG_INP_BOTH                                      0x00000004U
#define SYSTIM_CH2CFG_INP_FALL                                      0x00000002U
#define SYSTIM_CH2CFG_INP_RISE                                      0x00000000U

// Field:     [0] MODE
//
// Decides the channel mode.
// ENUMs:
// CAPT                     channel is in capture mode
// DIS                      channel is disabled
#define SYSTIM_CH2CFG_MODE                                          0x00000001U
#define SYSTIM_CH2CFG_MODE_M                                        0x00000001U
#define SYSTIM_CH2CFG_MODE_S                                                 0U
#define SYSTIM_CH2CFG_MODE_CAPT                                     0x00000001U
#define SYSTIM_CH2CFG_MODE_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH3CFG
//
//*****************************************************************************
// Field:     [3] REARM
//
// When Rearm is enabled the channel remains in continous capture mode.
// Otherwise it'll be in one shot capture mode. Rearm is only valid for capture
// mode.
// ENUMs:
// EN                       Re arm is enabled
// DIS                      Re Arm is disabled
#define SYSTIM_CH3CFG_REARM                                         0x00000008U
#define SYSTIM_CH3CFG_REARM_M                                       0x00000008U
#define SYSTIM_CH3CFG_REARM_S                                                3U
#define SYSTIM_CH3CFG_REARM_EN                                      0x00000008U
#define SYSTIM_CH3CFG_REARM_DIS                                     0x00000000U

// Field:   [2:1] INP
//
// Decides the channel input signal's mode. Setting the Value as 2'b11 selects
// the Rise Function
// ENUMs:
// BOTH                     Capture on both Edge
// FALL                     Capture on Falling Edge
// RISE                     Capture on rising edge
#define SYSTIM_CH3CFG_INP_W                                                  2U
#define SYSTIM_CH3CFG_INP_M                                         0x00000006U
#define SYSTIM_CH3CFG_INP_S                                                  1U
#define SYSTIM_CH3CFG_INP_BOTH                                      0x00000004U
#define SYSTIM_CH3CFG_INP_FALL                                      0x00000002U
#define SYSTIM_CH3CFG_INP_RISE                                      0x00000000U

// Field:     [0] MODE
//
// Decides the channel mode.
// ENUMs:
// CAPT                     channel is in capture mode
// DIS                      channel is disabled
#define SYSTIM_CH3CFG_MODE                                          0x00000001U
#define SYSTIM_CH3CFG_MODE_M                                        0x00000001U
#define SYSTIM_CH3CFG_MODE_S                                                 0U
#define SYSTIM_CH3CFG_MODE_CAPT                                     0x00000001U
#define SYSTIM_CH3CFG_MODE_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH4CFG
//
//*****************************************************************************
// Field:     [3] REARM
//
// When Rearm is enabled the channel remains in continous capture mode.
// Otherwise it'll be in one shot capture mode. Rearm is only valid for capture
// mode.
// ENUMs:
// EN                       Re arm is enabled
// DIS                      Re Arm is disabled
#define SYSTIM_CH4CFG_REARM                                         0x00000008U
#define SYSTIM_CH4CFG_REARM_M                                       0x00000008U
#define SYSTIM_CH4CFG_REARM_S                                                3U
#define SYSTIM_CH4CFG_REARM_EN                                      0x00000008U
#define SYSTIM_CH4CFG_REARM_DIS                                     0x00000000U

// Field:   [2:1] INP
//
// Decides the channel input signal's mode. Setting the Value as 2'b11 selects
// the Rise Function
// ENUMs:
// BOTH                     Capture on both Edge
// FALL                     Capture on Falling Edge
// RISE                     Capture on rising edge
#define SYSTIM_CH4CFG_INP_W                                                  2U
#define SYSTIM_CH4CFG_INP_M                                         0x00000006U
#define SYSTIM_CH4CFG_INP_S                                                  1U
#define SYSTIM_CH4CFG_INP_BOTH                                      0x00000004U
#define SYSTIM_CH4CFG_INP_FALL                                      0x00000002U
#define SYSTIM_CH4CFG_INP_RISE                                      0x00000000U

// Field:     [0] MODE
//
// Decides the channel mode.
// ENUMs:
// CAPT                     channel is in capture mode
// DIS                      channel is disabled
#define SYSTIM_CH4CFG_MODE                                          0x00000001U
#define SYSTIM_CH4CFG_MODE_M                                        0x00000001U
#define SYSTIM_CH4CFG_MODE_S                                                 0U
#define SYSTIM_CH4CFG_MODE_CAPT                                     0x00000001U
#define SYSTIM_CH4CFG_MODE_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH0CC
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH0CC_VAL_W                                                  32U
#define SYSTIM_CH0CC_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_CH0CC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH1CC
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH1CC_VAL_W                                                  32U
#define SYSTIM_CH1CC_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_CH1CC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH2CC
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH2CC_VAL_W                                                  32U
#define SYSTIM_CH2CC_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_CH2CC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH3CC
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH3CC_VAL_W                                                  32U
#define SYSTIM_CH3CC_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_CH3CC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH4CC
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH4CC_VAL_W                                                  32U
#define SYSTIM_CH4CC_VAL_M                                          0xFFFFFFFFU
#define SYSTIM_CH4CC_VAL_S                                                   0U

//*****************************************************************************
//
// Register: SYSTIM_O_TIMEBIT
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// The corresponding bit will have value '1' rest should be '0'. If more than
// one bit is asserted, output is "or" of all the bits.
// ENUMs:
// BIT17                    Bit17 is forwarded to the event fabric.
// BIT16                    Bit16 is forwarded to the event fabric.
// BIT15                    Bit15 is forwarded to the event fabric.
// BIT14                    Bit14 is forwarded to the event fabric.
// BIT13                    Bit13 is forwarded to the event fabric.
// BIT12                    Bit12 is forwarded to the event fabric.
// BIT11                    Bit11 is forwarded to the event fabric.
// BIT10                    Bit10 is forwarded to the event fabric.
// BIT9                     Bit9 is forwarded to the event fabric.
// BIT8                     Bit8 is forwarded to the event fabric.
// BIT7                     Bit7 is forwarded to the event fabric.
// BIT6                     Bit6 is forwarded to the event fabric.
// BIT5                     Bit5 is forwarded to the event fabric.
// BIT4                     Bit4 is forwarded to the event fabric.
// BIT3                     Bit3 is forwarded to the event fabric.
// BIT2                     Bit2 is forwarded to the event fabric.
// NOBIT                    No bit is forwarded to the event fabric.
#define SYSTIM_TIMEBIT_VAL_W                                                16U
#define SYSTIM_TIMEBIT_VAL_M                                        0x0000FFFFU
#define SYSTIM_TIMEBIT_VAL_S                                                 0U
#define SYSTIM_TIMEBIT_VAL_BIT17                                    0x00008000U
#define SYSTIM_TIMEBIT_VAL_BIT16                                    0x00004000U
#define SYSTIM_TIMEBIT_VAL_BIT15                                    0x00002000U
#define SYSTIM_TIMEBIT_VAL_BIT14                                    0x00001000U
#define SYSTIM_TIMEBIT_VAL_BIT13                                    0x00000800U
#define SYSTIM_TIMEBIT_VAL_BIT12                                    0x00000400U
#define SYSTIM_TIMEBIT_VAL_BIT11                                    0x00000200U
#define SYSTIM_TIMEBIT_VAL_BIT10                                    0x00000100U
#define SYSTIM_TIMEBIT_VAL_BIT9                                     0x00000080U
#define SYSTIM_TIMEBIT_VAL_BIT8                                     0x00000040U
#define SYSTIM_TIMEBIT_VAL_BIT7                                     0x00000020U
#define SYSTIM_TIMEBIT_VAL_BIT6                                     0x00000010U
#define SYSTIM_TIMEBIT_VAL_BIT5                                     0x00000008U
#define SYSTIM_TIMEBIT_VAL_BIT4                                     0x00000004U
#define SYSTIM_TIMEBIT_VAL_BIT3                                     0x00000002U
#define SYSTIM_TIMEBIT_VAL_BIT2                                     0x00000001U
#define SYSTIM_TIMEBIT_VAL_NOBIT                                    0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_STATUS
//
//*****************************************************************************
// Field:     [4] SYNCUP
//
// This bit indicates sync status of Systimer with RTC. The bitfield has a
// reset value of '1', which gets cleared to '0' after the Systimer
// synchronizes with RTC on the first LFTICK edge. A write to this bit
// resynchronizes the Systimer with RTC on the next LFTICK edge. A read value
// of '1'  indicates the synchronization is ongoing and a read of '0' indicates
// the synchronization is done.
#define SYSTIM_STATUS_SYNCUP                                        0x00000010U
#define SYSTIM_STATUS_SYNCUP_M                                      0x00000010U
#define SYSTIM_STATUS_SYNCUP_S                                               4U

// Field:     [0] VAL
//
//  This bit indicates if the system time is initialized and running.
// ENUMs:
// RUN                      system timer is running
// STOP                     system timer is not running.
#define SYSTIM_STATUS_VAL                                           0x00000001U
#define SYSTIM_STATUS_VAL_M                                         0x00000001U
#define SYSTIM_STATUS_VAL_S                                                  0U
#define SYSTIM_STATUS_VAL_RUN                                       0x00000001U
#define SYSTIM_STATUS_VAL_STOP                                      0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_ARMSET
//
//*****************************************************************************
// Field:     [4] CH4
//
// Arming channel 4 for either compare or capture operation.
// ENUMs:
// SET                      if channel 4 is in CAPTURE state then no effect on
//                          the channel else it can set channel in COMPARE
//                          mode using existing CH4CC.VAL value.
// NOEFF                    No effect on the channel
#define SYSTIM_ARMSET_CH4                                           0x00000010U
#define SYSTIM_ARMSET_CH4_M                                         0x00000010U
#define SYSTIM_ARMSET_CH4_S                                                  4U
#define SYSTIM_ARMSET_CH4_SET                                       0x00000010U
#define SYSTIM_ARMSET_CH4_NOEFF                                     0x00000000U

// Field:     [3] CH3
//
// Arming channel 3 for either compare or capture operation.
// ENUMs:
// SET                      if channel 3 is in CAPTURE state then no effect on
//                          the channel else it can set channel in COMPARE
//                          mode using existing CH3CC.VAL value
// NOEFF                    No effect on the channel
#define SYSTIM_ARMSET_CH3                                           0x00000008U
#define SYSTIM_ARMSET_CH3_M                                         0x00000008U
#define SYSTIM_ARMSET_CH3_S                                                  3U
#define SYSTIM_ARMSET_CH3_SET                                       0x00000008U
#define SYSTIM_ARMSET_CH3_NOEFF                                     0x00000000U

// Field:     [2] CH2
//
// Arming channel 2 for either compare or capture operation.
// ENUMs:
// SET                      if channel 2 is in CAPTURE state then no effect on
//                          the channel else it can set channel in COMPARE
//                          mode using existing CH2CC.VAL value
// NOEFF                    No effect on the channel
#define SYSTIM_ARMSET_CH2                                           0x00000004U
#define SYSTIM_ARMSET_CH2_M                                         0x00000004U
#define SYSTIM_ARMSET_CH2_S                                                  2U
#define SYSTIM_ARMSET_CH2_SET                                       0x00000004U
#define SYSTIM_ARMSET_CH2_NOEFF                                     0x00000000U

// Field:     [1] CH1
//
// Arming channel 1 for either compare or capture operation.
// ENUMs:
// SET                      if channel 1 is in CAPTURE state then no effect on
//                          the channel else it can Set channel in COMPARE
//                          mode using existing CH1CC.VAL value
// NOEFF                    No effect on the channel
#define SYSTIM_ARMSET_CH1                                           0x00000002U
#define SYSTIM_ARMSET_CH1_M                                         0x00000002U
#define SYSTIM_ARMSET_CH1_S                                                  1U
#define SYSTIM_ARMSET_CH1_SET                                       0x00000002U
#define SYSTIM_ARMSET_CH1_NOEFF                                     0x00000000U

// Field:     [0] CH0
//
// Arming channel 0 for either compare or capture operation.
// ENUMs:
// SET                      if channel 0 is in CAPTURE state then no effect on
//                          the channel else it can set channel in COMPARE
//                          mode using existing CH0CC.VAL value
// NOEFF                    No effect on the channel
#define SYSTIM_ARMSET_CH0                                           0x00000001U
#define SYSTIM_ARMSET_CH0_M                                         0x00000001U
#define SYSTIM_ARMSET_CH0_S                                                  0U
#define SYSTIM_ARMSET_CH0_SET                                       0x00000001U
#define SYSTIM_ARMSET_CH0_NOEFF                                     0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_ARMCLR
//
//*****************************************************************************
// Field:     [4] CH4
//
// Disarming channel 4
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare/capture event happens in
//                          the same cycle
// NOEFF                    No effect on the channel
#define SYSTIM_ARMCLR_CH4                                           0x00000010U
#define SYSTIM_ARMCLR_CH4_M                                         0x00000010U
#define SYSTIM_ARMCLR_CH4_S                                                  4U
#define SYSTIM_ARMCLR_CH4_CLR                                       0x00000010U
#define SYSTIM_ARMCLR_CH4_NOEFF                                     0x00000000U

// Field:     [3] CH3
//
// Disarming channel 3
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare/capture event happens in
//                          the same cycle
// NOEFF                    No effect on the channel
#define SYSTIM_ARMCLR_CH3                                           0x00000008U
#define SYSTIM_ARMCLR_CH3_M                                         0x00000008U
#define SYSTIM_ARMCLR_CH3_S                                                  3U
#define SYSTIM_ARMCLR_CH3_CLR                                       0x00000008U
#define SYSTIM_ARMCLR_CH3_NOEFF                                     0x00000000U

// Field:     [2] CH2
//
// Disarming channel 2
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare/capture event happens in
//                          the same cycle
// NOEFF                    No effect on the channel
#define SYSTIM_ARMCLR_CH2                                           0x00000004U
#define SYSTIM_ARMCLR_CH2_M                                         0x00000004U
#define SYSTIM_ARMCLR_CH2_S                                                  2U
#define SYSTIM_ARMCLR_CH2_CLR                                       0x00000004U
#define SYSTIM_ARMCLR_CH2_NOEFF                                     0x00000000U

// Field:     [1] CH1
//
// Disarming channel 1
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare/capture event happens in
//                          the same cycle
// NOEFF                    No effect on the channel
#define SYSTIM_ARMCLR_CH1                                           0x00000002U
#define SYSTIM_ARMCLR_CH1_M                                         0x00000002U
#define SYSTIM_ARMCLR_CH1_S                                                  1U
#define SYSTIM_ARMCLR_CH1_CLR                                       0x00000002U
#define SYSTIM_ARMCLR_CH1_NOEFF                                     0x00000000U

// Field:     [0] CH0
//
// Disarming channel 0
// ENUMs:
// CLR                      Set channel in UNARMED state without triggering
//                          event unless a compare/capture event happens in
//                          the same cycle
// NOEFF                    No effect on the channel
#define SYSTIM_ARMCLR_CH0                                           0x00000001U
#define SYSTIM_ARMCLR_CH0_M                                         0x00000001U
#define SYSTIM_ARMCLR_CH0_S                                                  0U
#define SYSTIM_ARMCLR_CH0_CLR                                       0x00000001U
#define SYSTIM_ARMCLR_CH0_NOEFF                                     0x00000000U

//*****************************************************************************
//
// Register: SYSTIM_O_CH0CCSR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH0CCSR_VAL_W                                                32U
#define SYSTIM_CH0CCSR_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_CH0CCSR_VAL_S                                                 0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH1CCSR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH1CCSR_VAL_W                                                32U
#define SYSTIM_CH1CCSR_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_CH1CCSR_VAL_S                                                 0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH2CCSR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH2CCSR_VAL_W                                                32U
#define SYSTIM_CH2CCSR_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_CH2CCSR_VAL_S                                                 0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH3CCSR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH3CCSR_VAL_W                                                32U
#define SYSTIM_CH3CCSR_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_CH3CCSR_VAL_S                                                 0U

//*****************************************************************************
//
// Register: SYSTIM_O_CH4CCSR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Capture/compare value
#define SYSTIM_CH4CCSR_VAL_W                                                32U
#define SYSTIM_CH4CCSR_VAL_M                                        0xFFFFFFFFU
#define SYSTIM_CH4CCSR_VAL_S                                                 0U


#endif // __SYSTIM__
