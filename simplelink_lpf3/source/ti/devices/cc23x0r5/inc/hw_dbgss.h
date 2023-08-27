/******************************************************************************
*  Filename:       hw_dbgss_h
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

#ifndef __HW_DBGSS_H__
#define __HW_DBGSS_H__

//*****************************************************************************
//
// This section defines the register offsets of
// DBGSS component
//
//*****************************************************************************
// Module Description
#define DBGSS_O_DESC                                                0x00000000U

// Interrupt mask
#define DBGSS_O_IMASK                                               0x00000044U

// Raw interrupt status
#define DBGSS_O_RIS                                                 0x0000004CU

// Masked interrupt status
#define DBGSS_O_MIS                                                 0x00000054U

// Interrupt set
#define DBGSS_O_ISET                                                0x0000005CU

// Interrupt clear
#define DBGSS_O_ICLR                                                0x00000064U

// Set Interupt Mask in IMASK
#define DBGSS_O_IMSET                                               0x0000006CU

// Clear Interupt Mask in IMASK
#define DBGSS_O_IMCLR                                               0x00000074U

// Transmit data register
#define DBGSS_O_TXD                                                 0x00000100U

// Transmit control register
#define DBGSS_O_TXCTL                                               0x00000104U

// Receive data register
#define DBGSS_O_RXD                                                 0x00000108U

// Receive control register
#define DBGSS_O_RXCTL                                               0x0000010CU

// Transmit Data Peek Register
#define DBGSS_O_TXDPEEK                                             0x00000110U

// Receive Data Peek Register
#define DBGSS_O_RXDPEEK                                             0x00000114U

// Special enable authorization register
#define DBGSS_O_SPECIAL_AUTH                                        0x00000200U

// Special enable authorization set register
#define DBGSS_O_SPECIAL_AUTH_SET                                    0x00000204U

// Special enable authorization clear register
#define DBGSS_O_SPECIAL_AUTH_CLR                                    0x00000208U

// Application authorization register
#define DBGSS_O_APP_AUTH                                            0x00000210U

// Application authorization set register
#define DBGSS_O_APP_AUTH_SET                                        0x00000214U

// Application authorization clear register
#define DBGSS_O_APP_AUTH_CLR                                        0x00000218U

// Debug control register
#define DBGSS_O_DBGCTL                                              0x0000021CU

//*****************************************************************************
//
// Register: DBGSS_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODULEID
//
// Module identifier used to uniquely identify this IP.
// ENUMs:
// MAX                      Maximum possible value
// MIN                      Minimum value
#define DBGSS_DESC_MODULEID_W                                               16U
#define DBGSS_DESC_MODULEID_M                                       0xFFFF0000U
#define DBGSS_DESC_MODULEID_S                                               16U
#define DBGSS_DESC_MODULEID_MAX                                     0xFFFF0000U
#define DBGSS_DESC_MODULEID_MIN                                     0x00000000U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
//
// 0: STDIP MMRs do not exist
// 0x1-0xF: These MMRs begin at offset 64*STDIPOFF from IP base address
// ENUMs:
// MAX                      Maximum possible value
// MIN                      Minimum Value
#define DBGSS_DESC_STDIPOFF_W                                                4U
#define DBGSS_DESC_STDIPOFF_M                                       0x0000F000U
#define DBGSS_DESC_STDIPOFF_S                                               12U
#define DBGSS_DESC_STDIPOFF_MAX                                     0x0000F000U
#define DBGSS_DESC_STDIPOFF_MIN                                     0x00000000U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
// ENUMs:
// MAX                      Maximum possible value
// MIN                      Minimum Value
#define DBGSS_DESC_INSTIDX_W                                                 4U
#define DBGSS_DESC_INSTIDX_M                                        0x00000F00U
#define DBGSS_DESC_INSTIDX_S                                                 8U
#define DBGSS_DESC_INSTIDX_MAX                                      0x00000F00U
#define DBGSS_DESC_INSTIDX_MIN                                      0x00000000U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
// ENUMs:
// MAX                      Maximum possible value
// MIN                      Minimum Value
#define DBGSS_DESC_MAJREV_W                                                  4U
#define DBGSS_DESC_MAJREV_M                                         0x000000F0U
#define DBGSS_DESC_MAJREV_S                                                  4U
#define DBGSS_DESC_MAJREV_MAX                                       0x000000F0U
#define DBGSS_DESC_MAJREV_MIN                                       0x00000000U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
// ENUMs:
// MAX                      Maximum possible value
// MIN                      Minimum Value
#define DBGSS_DESC_MINREV_W                                                  4U
#define DBGSS_DESC_MINREV_M                                         0x0000000FU
#define DBGSS_DESC_MINREV_S                                                  0U
#define DBGSS_DESC_MINREV_MAX                                       0x0000000FU
#define DBGSS_DESC_MINREV_MIN                                       0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_IMASK
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// PWRDWNIFG interrupt mask
// ENUMs:
// SET                      Interrupt will request an interrupt service
//                          routine and corresponding bit in MIS will be
//                          set
// CLR                      Interrupt is masked out
#define DBGSS_IMASK_PWRDWNIFG                                       0x00000008U
#define DBGSS_IMASK_PWRDWNIFG_M                                     0x00000008U
#define DBGSS_IMASK_PWRDWNIFG_S                                              3U
#define DBGSS_IMASK_PWRDWNIFG_SET                                   0x00000008U
#define DBGSS_IMASK_PWRDWNIFG_CLR                                   0x00000000U

// Field:     [2] PWRUPIFG
//
// PWRUPIFG interrupt mask
// ENUMs:
// SET                      Interrupt will request an interrupt service
//                          routine and corresponding bit in MIS will be
//                          set
// CLR                      Interrupt is masked out
#define DBGSS_IMASK_PWRUPIFG                                        0x00000004U
#define DBGSS_IMASK_PWRUPIFG_M                                      0x00000004U
#define DBGSS_IMASK_PWRUPIFG_S                                               2U
#define DBGSS_IMASK_PWRUPIFG_SET                                    0x00000004U
#define DBGSS_IMASK_PWRUPIFG_CLR                                    0x00000000U

// Field:     [1] RXIFG
//
// RXIFG interrupt mask
// ENUMs:
// SET                      Interrupt will request an interrupt service
//                          routine and corresponding bit in MIS will be
//                          set
// CLR                      Interrupt is masked out
#define DBGSS_IMASK_RXIFG                                           0x00000002U
#define DBGSS_IMASK_RXIFG_M                                         0x00000002U
#define DBGSS_IMASK_RXIFG_S                                                  1U
#define DBGSS_IMASK_RXIFG_SET                                       0x00000002U
#define DBGSS_IMASK_RXIFG_CLR                                       0x00000000U

// Field:     [0] TXIFG
//
// TXIFG interrupt mask
// ENUMs:
// EN                       Enable Interrupt Mask
// DIS                      Disable Interrupt Mask
#define DBGSS_IMASK_TXIFG                                           0x00000001U
#define DBGSS_IMASK_TXIFG_M                                         0x00000001U
#define DBGSS_IMASK_TXIFG_S                                                  0U
#define DBGSS_IMASK_TXIFG_EN                                        0x00000001U
#define DBGSS_IMASK_TXIFG_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_RIS
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Raw interrupt status for PWRDWNIFG
// ENUMs:
// SET                      PWRDWNIFG occurred
// CLR                      PWRDWNIFG did not occur
#define DBGSS_RIS_PWRDWNIFG                                         0x00000008U
#define DBGSS_RIS_PWRDWNIFG_M                                       0x00000008U
#define DBGSS_RIS_PWRDWNIFG_S                                                3U
#define DBGSS_RIS_PWRDWNIFG_SET                                     0x00000008U
#define DBGSS_RIS_PWRDWNIFG_CLR                                     0x00000000U

// Field:     [2] PWRUPIFG
//
// Raw interrupt status for PWRUPIFG
// ENUMs:
// SET                      PWRUPIFG occurred
// CLR                      PWRUPIFG did not occur
#define DBGSS_RIS_PWRUPIFG                                          0x00000004U
#define DBGSS_RIS_PWRUPIFG_M                                        0x00000004U
#define DBGSS_RIS_PWRUPIFG_S                                                 2U
#define DBGSS_RIS_PWRUPIFG_SET                                      0x00000004U
#define DBGSS_RIS_PWRUPIFG_CLR                                      0x00000000U

// Field:     [1] RXIFG
//
// Raw interrupt status for RXIFG
// ENUMs:
// SET                      RXIFG occurred
// CLR                      RXIFG did not occur
#define DBGSS_RIS_RXIFG                                             0x00000002U
#define DBGSS_RIS_RXIFG_M                                           0x00000002U
#define DBGSS_RIS_RXIFG_S                                                    1U
#define DBGSS_RIS_RXIFG_SET                                         0x00000002U
#define DBGSS_RIS_RXIFG_CLR                                         0x00000000U

// Field:     [0] TXIFG
//
// Raw interrupt status for TXIFG
// ENUMs:
// SET                      TXIFG occurred
// CLR                      TXIFG did not occur
#define DBGSS_RIS_TXIFG                                             0x00000001U
#define DBGSS_RIS_TXIFG_M                                           0x00000001U
#define DBGSS_RIS_TXIFG_S                                                    0U
#define DBGSS_RIS_TXIFG_SET                                         0x00000001U
#define DBGSS_RIS_TXIFG_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_MIS
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Masked interrupt status for PWRDWNIFG
// ENUMs:
// SET                      PWRDWNIFG requests an interrupt service routine
// CLR                      PWRDWNIFG did not request an interrupt service
//                          routine
#define DBGSS_MIS_PWRDWNIFG                                         0x00000008U
#define DBGSS_MIS_PWRDWNIFG_M                                       0x00000008U
#define DBGSS_MIS_PWRDWNIFG_S                                                3U
#define DBGSS_MIS_PWRDWNIFG_SET                                     0x00000008U
#define DBGSS_MIS_PWRDWNIFG_CLR                                     0x00000000U

// Field:     [2] PWRUPIFG
//
// Masked interrupt status for PWRUPIFG
// ENUMs:
// SET                      PWRUPIFG requests an interrupt service routine
// CLR                      PWRUPIFG did not request an interrupt service
//                          routine
#define DBGSS_MIS_PWRUPIFG                                          0x00000004U
#define DBGSS_MIS_PWRUPIFG_M                                        0x00000004U
#define DBGSS_MIS_PWRUPIFG_S                                                 2U
#define DBGSS_MIS_PWRUPIFG_SET                                      0x00000004U
#define DBGSS_MIS_PWRUPIFG_CLR                                      0x00000000U

// Field:     [1] RXIFG
//
// Masked interrupt status for RXIFG
// ENUMs:
// SET                      RXIFG requests an interrupt service routine
// CLR                      RXIFG did not request an interrupt service routine
#define DBGSS_MIS_RXIFG                                             0x00000002U
#define DBGSS_MIS_RXIFG_M                                           0x00000002U
#define DBGSS_MIS_RXIFG_S                                                    1U
#define DBGSS_MIS_RXIFG_SET                                         0x00000002U
#define DBGSS_MIS_RXIFG_CLR                                         0x00000000U

// Field:     [0] TXIFG
//
// Masked interrupt status for TXIFG
// ENUMs:
// SET                      TXIFG requests an interrupt service routine
// CLR                      TXIFG did not request an interrupt service routine
#define DBGSS_MIS_TXIFG                                             0x00000001U
#define DBGSS_MIS_TXIFG_M                                           0x00000001U
#define DBGSS_MIS_TXIFG_S                                                    0U
#define DBGSS_MIS_TXIFG_SET                                         0x00000001U
#define DBGSS_MIS_TXIFG_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_ISET
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Sets PWRDWNIFG in RIS register
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ISET_PWRDWNIFG                                        0x00000008U
#define DBGSS_ISET_PWRDWNIFG_M                                      0x00000008U
#define DBGSS_ISET_PWRDWNIFG_S                                               3U
#define DBGSS_ISET_PWRDWNIFG_SET                                    0x00000008U
#define DBGSS_ISET_PWRDWNIFG_NOEFF                                  0x00000000U

// Field:     [2] PWRUPIFG
//
// Sets PWRUPIFG in RIS register
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ISET_PWRUPIFG                                         0x00000004U
#define DBGSS_ISET_PWRUPIFG_M                                       0x00000004U
#define DBGSS_ISET_PWRUPIFG_S                                                2U
#define DBGSS_ISET_PWRUPIFG_SET                                     0x00000004U
#define DBGSS_ISET_PWRUPIFG_NOEFF                                   0x00000000U

// Field:     [1] RXIFG
//
// Sets RXIFG in RIS register
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ISET_RXIFG                                            0x00000002U
#define DBGSS_ISET_RXIFG_M                                          0x00000002U
#define DBGSS_ISET_RXIFG_S                                                   1U
#define DBGSS_ISET_RXIFG_SET                                        0x00000002U
#define DBGSS_ISET_RXIFG_NOEFF                                      0x00000000U

// Field:     [0] TXIFG
//
// Sets TXIFG in RIS register
// ENUMs:
// SET                      Set interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ISET_TXIFG                                            0x00000001U
#define DBGSS_ISET_TXIFG_M                                          0x00000001U
#define DBGSS_ISET_TXIFG_S                                                   0U
#define DBGSS_ISET_TXIFG_SET                                        0x00000001U
#define DBGSS_ISET_TXIFG_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_ICLR
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Clears PWRDWNIFG interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ICLR_PWRDWNIFG                                        0x00000008U
#define DBGSS_ICLR_PWRDWNIFG_M                                      0x00000008U
#define DBGSS_ICLR_PWRDWNIFG_S                                               3U
#define DBGSS_ICLR_PWRDWNIFG_CLR                                    0x00000008U
#define DBGSS_ICLR_PWRDWNIFG_NOEFF                                  0x00000000U

// Field:     [2] PWRUPIFG
//
// Clears PWRUPIFG interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ICLR_PWRUPIFG                                         0x00000004U
#define DBGSS_ICLR_PWRUPIFG_M                                       0x00000004U
#define DBGSS_ICLR_PWRUPIFG_S                                                2U
#define DBGSS_ICLR_PWRUPIFG_CLR                                     0x00000004U
#define DBGSS_ICLR_PWRUPIFG_NOEFF                                   0x00000000U

// Field:     [1] RXIFG
//
// Clears RXIFG interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ICLR_RXIFG                                            0x00000002U
#define DBGSS_ICLR_RXIFG_M                                          0x00000002U
#define DBGSS_ICLR_RXIFG_S                                                   1U
#define DBGSS_ICLR_RXIFG_CLR                                        0x00000002U
#define DBGSS_ICLR_RXIFG_NOEFF                                      0x00000000U

// Field:     [0] TXIFG
//
// Clears TXIFG interrupt
// ENUMs:
// CLR                      Clear interrupt
// NOEFF                    Writing a 0 has no effect
#define DBGSS_ICLR_TXIFG                                            0x00000001U
#define DBGSS_ICLR_TXIFG_M                                          0x00000001U
#define DBGSS_ICLR_TXIFG_S                                                   0U
#define DBGSS_ICLR_TXIFG_CLR                                        0x00000001U
#define DBGSS_ICLR_TXIFG_NOEFF                                      0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_IMSET
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Set PWRDWNIFG interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing a 0 has no effect
#define DBGSS_IMSET_PWRDWNIFG                                       0x00000008U
#define DBGSS_IMSET_PWRDWNIFG_M                                     0x00000008U
#define DBGSS_IMSET_PWRDWNIFG_S                                              3U
#define DBGSS_IMSET_PWRDWNIFG_SET                                   0x00000008U
#define DBGSS_IMSET_PWRDWNIFG_NOEFF                                 0x00000000U

// Field:     [2] PWRUPIFG
//
// Set PWRUPIFG interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing a 0 has no effect
#define DBGSS_IMSET_PWRUPIFG                                        0x00000004U
#define DBGSS_IMSET_PWRUPIFG_M                                      0x00000004U
#define DBGSS_IMSET_PWRUPIFG_S                                               2U
#define DBGSS_IMSET_PWRUPIFG_SET                                    0x00000004U
#define DBGSS_IMSET_PWRUPIFG_NOEFF                                  0x00000000U

// Field:     [1] RXIFG
//
// Set RXIFG interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing a 0 has no effect
#define DBGSS_IMSET_RXIFG                                           0x00000002U
#define DBGSS_IMSET_RXIFG_M                                         0x00000002U
#define DBGSS_IMSET_RXIFG_S                                                  1U
#define DBGSS_IMSET_RXIFG_SET                                       0x00000002U
#define DBGSS_IMSET_RXIFG_NOEFF                                     0x00000000U

// Field:     [0] TXIFG
//
// Set TXIFG interrupt mask
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing a 0 has no effect
#define DBGSS_IMSET_TXIFG                                           0x00000001U
#define DBGSS_IMSET_TXIFG_M                                         0x00000001U
#define DBGSS_IMSET_TXIFG_S                                                  0U
#define DBGSS_IMSET_TXIFG_SET                                       0x00000001U
#define DBGSS_IMSET_TXIFG_NOEFF                                     0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_IMCLR
//
//*****************************************************************************
// Field:     [3] PWRDWNIFG
//
// Clears PWRDWNIFG interrupt mask
// ENUMs:
// CLR                      IMASK bit corresponding to PWRDWNIFG is cleared
// NO_EFFECT                Writing a 0 has no effect
#define DBGSS_IMCLR_PWRDWNIFG                                       0x00000008U
#define DBGSS_IMCLR_PWRDWNIFG_M                                     0x00000008U
#define DBGSS_IMCLR_PWRDWNIFG_S                                              3U
#define DBGSS_IMCLR_PWRDWNIFG_CLR                                   0x00000008U
#define DBGSS_IMCLR_PWRDWNIFG_NO_EFFECT                             0x00000000U

// Field:     [2] PWRUPIFG
//
// Clears PWRUPIFG interrupt mask
// ENUMs:
// CLR                      IMASK bit corresponding to PWRUPIFG is cleared
// NO_EFFECT                Writing a 0 has no effect
#define DBGSS_IMCLR_PWRUPIFG                                        0x00000004U
#define DBGSS_IMCLR_PWRUPIFG_M                                      0x00000004U
#define DBGSS_IMCLR_PWRUPIFG_S                                               2U
#define DBGSS_IMCLR_PWRUPIFG_CLR                                    0x00000004U
#define DBGSS_IMCLR_PWRUPIFG_NO_EFFECT                              0x00000000U

// Field:     [1] RXIFG
//
// Clears RXIFG interrupt mask
// ENUMs:
// CLR                      IMASK bit corresponding to RXIFG is cleared
// NO_EFFECT                Writing a 0 has no effect
#define DBGSS_IMCLR_RXIFG                                           0x00000002U
#define DBGSS_IMCLR_RXIFG_M                                         0x00000002U
#define DBGSS_IMCLR_RXIFG_S                                                  1U
#define DBGSS_IMCLR_RXIFG_CLR                                       0x00000002U
#define DBGSS_IMCLR_RXIFG_NO_EFFECT                                 0x00000000U

// Field:     [0] TXIFG
//
// Clears TXIFG interrupt mask
// ENUMs:
// CLR                      IMASK bit corresponding to TXIFG is cleared
// NO_EFFECT                Writing a 0 has no effect
#define DBGSS_IMCLR_TXIFG                                           0x00000001U
#define DBGSS_IMCLR_TXIFG_M                                         0x00000001U
#define DBGSS_IMCLR_TXIFG_S                                                  0U
#define DBGSS_IMCLR_TXIFG_CLR                                       0x00000001U
#define DBGSS_IMCLR_TXIFG_NO_EFFECT                                 0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_TXD
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// SACI command/parameter word. Valid value when TXCTL.TXDSTA=1. TXCTL.TXDSTA
// gets automatically cleared upon read.
#define DBGSS_TXD_VAL_W                                                     32U
#define DBGSS_TXD_VAL_M                                             0xFFFFFFFFU
#define DBGSS_TXD_VAL_S                                                      0U

//*****************************************************************************
//
// Register: DBGSS_O_TXCTL
//
//*****************************************************************************
// Field:   [7:1] FLAGS
//
// Software defined flags that are used by the SACI protocol (host to device).
#define DBGSS_TXCTL_FLAGS_W                                                  7U
#define DBGSS_TXCTL_FLAGS_M                                         0x000000FEU
#define DBGSS_TXCTL_FLAGS_S                                                  1U

// Field:     [0] TXDSTA
//
// Indicates whether the host has written a word to the TXD register, which can
// be read by the device:
// TXDSTA is automatically set upon write to TXD register in SECAP and
// automatically gets cleared upon read from TXD
// ENUMs:
// FULL                     The TXD register contains a new SACI parameter
//                          word from the host, which can be read by the
//                          device.
// EMPTY                     The TXD register does not contain a new SACI
//                          parameter word from the host, and should not be
//                          read by the device.
#define DBGSS_TXCTL_TXDSTA                                          0x00000001U
#define DBGSS_TXCTL_TXDSTA_M                                        0x00000001U
#define DBGSS_TXCTL_TXDSTA_S                                                 0U
#define DBGSS_TXCTL_TXDSTA_FULL                                     0x00000001U
#define DBGSS_TXCTL_TXDSTA_EMPTY                                    0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_RXD
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// SACI command response word. RXCTL.RXDSTA automatically set upon write.
// RXCTL.RXDSTA automatically cleared upon read (flush operation).
#define DBGSS_RXD_VAL_W                                                     32U
#define DBGSS_RXD_VAL_M                                             0xFFFFFFFFU
#define DBGSS_RXD_VAL_S                                                      0U

//*****************************************************************************
//
// Register: DBGSS_O_RXCTL
//
//*****************************************************************************
// Field:   [7:1] FLAGS
//
// Software defined flags that are used by the SACI protocol (device to host).
#define DBGSS_RXCTL_FLAGS_W                                                  7U
#define DBGSS_RXCTL_FLAGS_M                                         0x000000FEU
#define DBGSS_RXCTL_FLAGS_S                                                  1U

// Field:     [0] RXDSTA
//
// Indicates whether the device has written a word to the RXD register, which
// can be read by the host:
// RXDSTA is automatically set upon write to RXD and automatically cleared upon
// read from RXD register of SECAP or  RXD.
// ENUMs:
// FULL                     The RXD register contains a new SACI response word
//                          from the device, which can be read by the host.
// EMPTY                    The RXD register does not contain a new SACI
//                          response word from the device, and should not
//                          be read by the host.
#define DBGSS_RXCTL_RXDSTA                                          0x00000001U
#define DBGSS_RXCTL_RXDSTA_M                                        0x00000001U
#define DBGSS_RXCTL_RXDSTA_S                                                 0U
#define DBGSS_RXCTL_RXDSTA_FULL                                     0x00000001U
#define DBGSS_RXCTL_RXDSTA_EMPTY                                    0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_TXDPEEK
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Transmit Data Peek Register. SACI command parameter word. TXCTL.TXDSTA not
// affected by read of TXDPEEK
#define DBGSS_TXDPEEK_VAL_W                                                 32U
#define DBGSS_TXDPEEK_VAL_M                                         0xFFFFFFFFU
#define DBGSS_TXDPEEK_VAL_S                                                  0U

//*****************************************************************************
//
// Register: DBGSS_O_RXDPEEK
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Receive Data Peek Register. SACI command response word. RXCTL.RXDSTA not
// affected by read of RXDPEEK
#define DBGSS_RXDPEEK_VAL_W                                                 32U
#define DBGSS_RXDPEEK_VAL_M                                         0xFFFFFFFFU
#define DBGSS_RXDPEEK_VAL_S                                                  0U

//*****************************************************************************
//
// Register: DBGSS_O_SPECIAL_AUTH
//
//*****************************************************************************
// Field:     [6] DBGDIS
//
// Indicates status of DBGDIS.
// ENUMs:
// DIS                      Disables debugging capability
// EN                       Enables debugging capability.
#define DBGSS_SPECIAL_AUTH_DBGDIS                                   0x00000040U
#define DBGSS_SPECIAL_AUTH_DBGDIS_M                                 0x00000040U
#define DBGSS_SPECIAL_AUTH_DBGDIS_S                                          6U
#define DBGSS_SPECIAL_AUTH_DBGDIS_DIS                               0x00000040U
#define DBGSS_SPECIAL_AUTH_DBGDIS_EN                                0x00000000U

// Field:     [5] AHBAPEN
//
// Indicates status of AHBAPEN
// ENUMs:
// EN                       Enable AHB-AP
// DIS                      Disable AHB-AP
#define DBGSS_SPECIAL_AUTH_AHBAPEN                                  0x00000020U
#define DBGSS_SPECIAL_AUTH_AHBAPEN_M                                0x00000020U
#define DBGSS_SPECIAL_AUTH_AHBAPEN_S                                         5U
#define DBGSS_SPECIAL_AUTH_AHBAPEN_EN                               0x00000020U
#define DBGSS_SPECIAL_AUTH_AHBAPEN_DIS                              0x00000000U

// Field:     [4] CFGAPEN
//
// Indicates status of CFGAPEN
// ENUMs:
// EN                       Enable CFG-AP
// DIS                      Disable CFG-AP
#define DBGSS_SPECIAL_AUTH_CFGAPEN                                  0x00000010U
#define DBGSS_SPECIAL_AUTH_CFGAPEN_M                                0x00000010U
#define DBGSS_SPECIAL_AUTH_CFGAPEN_S                                         4U
#define DBGSS_SPECIAL_AUTH_CFGAPEN_EN                               0x00000010U
#define DBGSS_SPECIAL_AUTH_CFGAPEN_DIS                              0x00000000U

// Field:     [2] DFTAPEN
//
// Indicates status of DFTAPEN
// ENUMs:
// EN                       Enable DFT-TAP
// DIS                      Disable DFT-TAP
#define DBGSS_SPECIAL_AUTH_DFTAPEN                                  0x00000004U
#define DBGSS_SPECIAL_AUTH_DFTAPEN_M                                0x00000004U
#define DBGSS_SPECIAL_AUTH_DFTAPEN_S                                         2U
#define DBGSS_SPECIAL_AUTH_DFTAPEN_EN                               0x00000004U
#define DBGSS_SPECIAL_AUTH_DFTAPEN_DIS                              0x00000000U

// Field:     [0] SECAPEN
//
// Indicates status of SECAP
// ENUMs:
// EN                       Enable SEC-AP
// DIS                      Disable SEC-AP
#define DBGSS_SPECIAL_AUTH_SECAPEN                                  0x00000001U
#define DBGSS_SPECIAL_AUTH_SECAPEN_M                                0x00000001U
#define DBGSS_SPECIAL_AUTH_SECAPEN_S                                         0U
#define DBGSS_SPECIAL_AUTH_SECAPEN_EN                               0x00000001U
#define DBGSS_SPECIAL_AUTH_SECAPEN_DIS                              0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_SPECIAL_AUTH_SET
//
//*****************************************************************************
// Field: [31:24] KEY
//
// This field must be configured with 0xA5 in order to access this register.
// ENUMs:
// _to_unlock_w_            This field must be written with 0xA5 to be able to
//                          set any of the enable bits
#define DBGSS_SPECIAL_AUTH_SET_KEY_W                                         8U
#define DBGSS_SPECIAL_AUTH_SET_KEY_M                                0xFF000000U
#define DBGSS_SPECIAL_AUTH_SET_KEY_S                                        24U
#define DBGSS_SPECIAL_AUTH_SET_KEY__TO_UNLOCK_W_                    0xA5000000U

// Field:     [6] DBGDIS
//
// This bit sets DBGDIS in SPECIAL_AUTH register.
// ENUMs:
// SET                      SET DBGDIS
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_SET_DBGDIS                               0x00000040U
#define DBGSS_SPECIAL_AUTH_SET_DBGDIS_M                             0x00000040U
#define DBGSS_SPECIAL_AUTH_SET_DBGDIS_S                                      6U
#define DBGSS_SPECIAL_AUTH_SET_DBGDIS_SET                           0x00000040U
#define DBGSS_SPECIAL_AUTH_SET_DBGDIS_NOEFF                         0x00000000U

// Field:     [5] AHBAPEN
//
// This bit sets AHBAPEN in SPECIAL_AUTH register.
// ENUMs:
// SET                      SET AHB-AP
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_SET_AHBAPEN                              0x00000020U
#define DBGSS_SPECIAL_AUTH_SET_AHBAPEN_M                            0x00000020U
#define DBGSS_SPECIAL_AUTH_SET_AHBAPEN_S                                     5U
#define DBGSS_SPECIAL_AUTH_SET_AHBAPEN_SET                          0x00000020U
#define DBGSS_SPECIAL_AUTH_SET_AHBAPEN_NOEFF                        0x00000000U

// Field:     [4] CFGAPEN
//
// This bit sets CFGAPEN in SPECIAL_AUTH register.
// ENUMs:
// SET                      Set  CFGAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_SET_CFGAPEN                              0x00000010U
#define DBGSS_SPECIAL_AUTH_SET_CFGAPEN_M                            0x00000010U
#define DBGSS_SPECIAL_AUTH_SET_CFGAPEN_S                                     4U
#define DBGSS_SPECIAL_AUTH_SET_CFGAPEN_SET                          0x00000010U
#define DBGSS_SPECIAL_AUTH_SET_CFGAPEN_NOEFF                        0x00000000U

// Field:     [2] DFTAPEN
//
// This bit sets DFTAPEN in SPECIAL_AUTH register.
// ENUMs:
// SET                      Set DFTAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_SET_DFTAPEN                              0x00000004U
#define DBGSS_SPECIAL_AUTH_SET_DFTAPEN_M                            0x00000004U
#define DBGSS_SPECIAL_AUTH_SET_DFTAPEN_S                                     2U
#define DBGSS_SPECIAL_AUTH_SET_DFTAPEN_SET                          0x00000004U
#define DBGSS_SPECIAL_AUTH_SET_DFTAPEN_NOEFF                        0x00000000U

// Field:     [0] SECAPEN
//
// This bit sets SECAPEN bit in SPECIAL_AUTH register.
// ENUMs:
// SET                      Set SECAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_SET_SECAPEN                              0x00000001U
#define DBGSS_SPECIAL_AUTH_SET_SECAPEN_M                            0x00000001U
#define DBGSS_SPECIAL_AUTH_SET_SECAPEN_S                                     0U
#define DBGSS_SPECIAL_AUTH_SET_SECAPEN_SET                          0x00000001U
#define DBGSS_SPECIAL_AUTH_SET_SECAPEN_NOEFF                        0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_SPECIAL_AUTH_CLR
//
//*****************************************************************************
// Field: [31:24] KEY
//
// This field must be configured with 0x22 in order to access this register.
// ENUMs:
// _to_unlock_w_            This field must be written with 0x22 to be able to
//                          clear any of the enable bits
#define DBGSS_SPECIAL_AUTH_CLR_KEY_W                                         8U
#define DBGSS_SPECIAL_AUTH_CLR_KEY_M                                0xFF000000U
#define DBGSS_SPECIAL_AUTH_CLR_KEY_S                                        24U
#define DBGSS_SPECIAL_AUTH_CLR_KEY__TO_UNLOCK_W_                    0x22000000U

// Field:     [6] DBGDIS
//
// This bit clears DBGDIS in SPECIAL_AUTH register.
// ENUMs:
// CLR                      Clear DBGDIS
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_CLR_DBGDIS                               0x00000040U
#define DBGSS_SPECIAL_AUTH_CLR_DBGDIS_M                             0x00000040U
#define DBGSS_SPECIAL_AUTH_CLR_DBGDIS_S                                      6U
#define DBGSS_SPECIAL_AUTH_CLR_DBGDIS_CLR                           0x00000040U
#define DBGSS_SPECIAL_AUTH_CLR_DBGDIS_NOEFF                         0x00000000U

// Field:     [5] AHBAPEN
//
// This bit clears AHBAPEN in SPECIAL_AUTH register.
// ENUMs:
// CLR                      Clear AHBAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_CLR_AHBAPEN                              0x00000020U
#define DBGSS_SPECIAL_AUTH_CLR_AHBAPEN_M                            0x00000020U
#define DBGSS_SPECIAL_AUTH_CLR_AHBAPEN_S                                     5U
#define DBGSS_SPECIAL_AUTH_CLR_AHBAPEN_CLR                          0x00000020U
#define DBGSS_SPECIAL_AUTH_CLR_AHBAPEN_NOEFF                        0x00000000U

// Field:     [4] CFGAPEN
//
// This bit clears CFGAPEN in SPECIAL_AUTH register.
// ENUMs:
// CLR                      Clear CFGAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_CLR_CFGAPEN                              0x00000010U
#define DBGSS_SPECIAL_AUTH_CLR_CFGAPEN_M                            0x00000010U
#define DBGSS_SPECIAL_AUTH_CLR_CFGAPEN_S                                     4U
#define DBGSS_SPECIAL_AUTH_CLR_CFGAPEN_CLR                          0x00000010U
#define DBGSS_SPECIAL_AUTH_CLR_CFGAPEN_NOEFF                        0x00000000U

// Field:     [2] DFTAPEN
//
// This bit clears DFTAPEN in SPECIAL_AUTH register.
// ENUMs:
// CLR                      Clear DFTAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_CLR_DFTAPEN                              0x00000004U
#define DBGSS_SPECIAL_AUTH_CLR_DFTAPEN_M                            0x00000004U
#define DBGSS_SPECIAL_AUTH_CLR_DFTAPEN_S                                     2U
#define DBGSS_SPECIAL_AUTH_CLR_DFTAPEN_CLR                          0x00000004U
#define DBGSS_SPECIAL_AUTH_CLR_DFTAPEN_NOEFF                        0x00000000U

// Field:     [0] SECAPEN
//
// This bit clears SECAPEN in SPECIAL_AUTH register.
// ENUMs:
// CLR                      Clear SECAPEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_SPECIAL_AUTH_CLR_SECAPEN                              0x00000001U
#define DBGSS_SPECIAL_AUTH_CLR_SECAPEN_M                            0x00000001U
#define DBGSS_SPECIAL_AUTH_CLR_SECAPEN_S                                     0U
#define DBGSS_SPECIAL_AUTH_CLR_SECAPEN_CLR                          0x00000001U
#define DBGSS_SPECIAL_AUTH_CLR_SECAPEN_NOEFF                        0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_APP_AUTH
//
//*****************************************************************************
// Field:     [1] NIDEN
//
// Controls non-invasive debug enable.
// ENUMs:
// EN                       Non-invasive debug enabled
// DIS                      Non-invasive debug disabled
#define DBGSS_APP_AUTH_NIDEN                                        0x00000002U
#define DBGSS_APP_AUTH_NIDEN_M                                      0x00000002U
#define DBGSS_APP_AUTH_NIDEN_S                                               1U
#define DBGSS_APP_AUTH_NIDEN_EN                                     0x00000002U
#define DBGSS_APP_AUTH_NIDEN_DIS                                    0x00000000U

// Field:     [0] DBGEN
//
// Controls invasive debug enable.
// ENUMs:
// EN                       Invasive debug enabled
// DIS                      Invasive debug disabled
#define DBGSS_APP_AUTH_DBGEN                                        0x00000001U
#define DBGSS_APP_AUTH_DBGEN_M                                      0x00000001U
#define DBGSS_APP_AUTH_DBGEN_S                                               0U
#define DBGSS_APP_AUTH_DBGEN_EN                                     0x00000001U
#define DBGSS_APP_AUTH_DBGEN_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_APP_AUTH_SET
//
//*****************************************************************************
// Field: [31:24] KEY
//
// This field must be configured with 0x39 in order to access this register.
// ENUMs:
// _to_unlock_w_            Write this value 0x39 to unlock writing to the
//                          APP_AUTH_SET register
#define DBGSS_APP_AUTH_SET_KEY_W                                             8U
#define DBGSS_APP_AUTH_SET_KEY_M                                    0xFF000000U
#define DBGSS_APP_AUTH_SET_KEY_S                                            24U
#define DBGSS_APP_AUTH_SET_KEY__TO_UNLOCK_W_                        0x39000000U

// Field:     [1] NIDEN
//
// Sets NIDEN bit in [APP_AUTH ]register.
// ENUMs:
// SET                      Sets NIDEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_APP_AUTH_SET_NIDEN                                    0x00000002U
#define DBGSS_APP_AUTH_SET_NIDEN_M                                  0x00000002U
#define DBGSS_APP_AUTH_SET_NIDEN_S                                           1U
#define DBGSS_APP_AUTH_SET_NIDEN_SET                                0x00000002U
#define DBGSS_APP_AUTH_SET_NIDEN_NOEFF                              0x00000000U

// Field:     [0] DBGEN
//
// Sets DBGEN bit in APP_AUTH register.
// ENUMs:
// SET                      Sets DBGEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_APP_AUTH_SET_DBGEN                                    0x00000001U
#define DBGSS_APP_AUTH_SET_DBGEN_M                                  0x00000001U
#define DBGSS_APP_AUTH_SET_DBGEN_S                                           0U
#define DBGSS_APP_AUTH_SET_DBGEN_SET                                0x00000001U
#define DBGSS_APP_AUTH_SET_DBGEN_NOEFF                              0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_APP_AUTH_CLR
//
//*****************************************************************************
// Field: [31:24] KEY
//
// This field must be configured with 0x7D in order to access this register.
// ENUMs:
// _to_unlock_w_            Write this value 0x7D to unlock writing to the
//                          APP_AUTH_CLR register
#define DBGSS_APP_AUTH_CLR_KEY_W                                             8U
#define DBGSS_APP_AUTH_CLR_KEY_M                                    0xFF000000U
#define DBGSS_APP_AUTH_CLR_KEY_S                                            24U
#define DBGSS_APP_AUTH_CLR_KEY__TO_UNLOCK_W_                        0x7D000000U

// Field:     [1] NIDEN
//
// Clears NIDEN bit in APP_AUTH register.
// ENUMs:
// CLR                      Clears NIDEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_APP_AUTH_CLR_NIDEN                                    0x00000002U
#define DBGSS_APP_AUTH_CLR_NIDEN_M                                  0x00000002U
#define DBGSS_APP_AUTH_CLR_NIDEN_S                                           1U
#define DBGSS_APP_AUTH_CLR_NIDEN_CLR                                0x00000002U
#define DBGSS_APP_AUTH_CLR_NIDEN_NOEFF                              0x00000000U

// Field:     [0] DBGEN
//
// Clears DBGEN bit in APP_AUTH register.
// ENUMs:
// CLR                      Clears DBGEN
// NOEFF                    Writing 0 has no effect
#define DBGSS_APP_AUTH_CLR_DBGEN                                    0x00000001U
#define DBGSS_APP_AUTH_CLR_DBGEN_M                                  0x00000001U
#define DBGSS_APP_AUTH_CLR_DBGEN_S                                           0U
#define DBGSS_APP_AUTH_CLR_DBGEN_CLR                                0x00000001U
#define DBGSS_APP_AUTH_CLR_DBGEN_NOEFF                              0x00000000U

//*****************************************************************************
//
// Register: DBGSS_O_DBGCTL
//
//*****************************************************************************
// Field:     [5] SWDCEN
//
// This bit is used to enable connection between SWD pads and IceMelter (wakeup
// circuit used for detecting debug probe)
// ENUMs:
// EN                       Connection enabled
// DIS                      Connection disabled
#define DBGSS_DBGCTL_SWDCEN                                         0x00000020U
#define DBGSS_DBGCTL_SWDCEN_M                                       0x00000020U
#define DBGSS_DBGCTL_SWDCEN_S                                                5U
#define DBGSS_DBGCTL_SWDCEN_EN                                      0x00000020U
#define DBGSS_DBGCTL_SWDCEN_DIS                                     0x00000000U

// Field:     [4] DBGPWRUPACK
//
// This bit field specifies the status of dbgpwrupack from pmctl.
// ENUMs:
// EN                       dbgpwrupreq is acknowledged.
// DIS                      dbgpwrupreq is not acknowledged
#define DBGSS_DBGCTL_DBGPWRUPACK                                    0x00000010U
#define DBGSS_DBGCTL_DBGPWRUPACK_M                                  0x00000010U
#define DBGSS_DBGCTL_DBGPWRUPACK_S                                           4U
#define DBGSS_DBGCTL_DBGPWRUPACK_EN                                 0x00000010U
#define DBGSS_DBGCTL_DBGPWRUPACK_DIS                                0x00000000U

// Field:     [3] SYSPWRUPACK
//
// This bit field specify the status of syspwrupack from pmctl.
// ENUMs:
// EN                       syspwrupreq is acknowledged
// DIS                      syspwrupreq is not acknowledged
#define DBGSS_DBGCTL_SYSPWRUPACK                                    0x00000008U
#define DBGSS_DBGCTL_SYSPWRUPACK_M                                  0x00000008U
#define DBGSS_DBGCTL_SYSPWRUPACK_S                                           3U
#define DBGSS_DBGCTL_SYSPWRUPACK_EN                                 0x00000008U
#define DBGSS_DBGCTL_SYSPWRUPACK_DIS                                0x00000000U

// Field:     [2] JTAGSEL
//
// This bit field specifies the status of JTAG MODE for TEST TAP.
// ENUMs:
// EN                       TEST TAP enabled
// DIS                      TEST TAP disabled
#define DBGSS_DBGCTL_JTAGSEL                                        0x00000004U
#define DBGSS_DBGCTL_JTAGSEL_M                                      0x00000004U
#define DBGSS_DBGCTL_JTAGSEL_S                                               2U
#define DBGSS_DBGCTL_JTAGSEL_EN                                     0x00000004U
#define DBGSS_DBGCTL_JTAGSEL_DIS                                    0x00000000U

// Field:     [1] SWDSEL
//
// This bit field specifies the status of  SWD MODE  for connection.
// ENUMs:
// EN                       debug connection enabled.
// DIS                      debug connection disabled.
#define DBGSS_DBGCTL_SWDSEL                                         0x00000002U
#define DBGSS_DBGCTL_SWDSEL_M                                       0x00000002U
#define DBGSS_DBGCTL_SWDSEL_S                                                1U
#define DBGSS_DBGCTL_SWDSEL_EN                                      0x00000002U
#define DBGSS_DBGCTL_SWDSEL_DIS                                     0x00000000U

// Field:     [0] SWDOVR
//
// This bit is used for connecting to IO pads to SWCLK/IO on SW-DP through a
// software request and establish SWD connection without IceMelter trigger for
// debug purpose.
// ENUMs:
// DBGENA                   Force 1 or debug enable mode in which SWD
//                          connection is established bypassing IceMelter
//                          sequence
// TRNSPRT                  Transparent mode in which SWD connection is
//                          established via IceMelter Sequence.
#define DBGSS_DBGCTL_SWDOVR                                         0x00000001U
#define DBGSS_DBGCTL_SWDOVR_M                                       0x00000001U
#define DBGSS_DBGCTL_SWDOVR_S                                                0U
#define DBGSS_DBGCTL_SWDOVR_DBGENA                                  0x00000001U
#define DBGSS_DBGCTL_SWDOVR_TRNSPRT                                 0x00000000U


#endif // __DBGSS__
