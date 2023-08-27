/******************************************************************************
*  Filename:       hw_adc_h
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

#ifndef __HW_ADC_H__
#define __HW_ADC_H__

//*****************************************************************************
//
// This section defines the register offsets of
// ADC component
//
//*****************************************************************************
// Interrupt mask
#define ADC_O_IMASK0                                                0x00000028U

// Raw interrupt status
#define ADC_O_RIS0                                                  0x00000030U

// Masked interrupt status
#define ADC_O_MIS0                                                  0x00000038U

// Interrupt set
#define ADC_O_ISET0                                                 0x00000040U

// Interrupt clear
#define ADC_O_ICLR0                                                 0x00000048U

// Interrupt mask
#define ADC_O_IMASK1                                                0x00000058U

// Raw interrupt status
#define ADC_O_RIS1                                                  0x00000060U

// Masked interrupt status
#define ADC_O_MIS1                                                  0x00000068U

// Interrupt set
#define ADC_O_ISET1                                                 0x00000070U

// Interrupt clear
#define ADC_O_ICLR1                                                 0x00000078U

// Interrupt mask
#define ADC_O_IMASK2                                                0x00000088U

// Raw interrupt status
#define ADC_O_RIS2                                                  0x00000090U

// Masked interrupt status
#define ADC_O_MIS2                                                  0x00000098U

// Interrupt set
#define ADC_O_ISET2                                                 0x000000A0U

// Interrupt clear
#define ADC_O_ICLR2                                                 0x000000A8U

// Control Register 0
#define ADC_O_CTL0                                                  0x00000100U

// Control Register 1
#define ADC_O_CTL1                                                  0x00000104U

// Control Register 2
#define ADC_O_CTL2                                                  0x00000108U

// Control Register 3
#define ADC_O_CTL3                                                  0x0000010CU

// Sample Time Compare 0 Register
#define ADC_O_SCOMP0                                                0x00000114U

// Sample Time Compare 1 Register
#define ADC_O_SCOMP1                                                0x00000118U

// Reference Buffer Configuration Register
#define ADC_O_REFCFG                                                0x0000011CU

// Window Comparator Low Threshold Register
#define ADC_O_WCLOW                                                 0x00000148U

// Window Comparator High Threshold Register
#define ADC_O_WCHIGH                                                0x00000150U

// FIFO Data Register
#define ADC_O_FIFODATA                                              0x00000160U

// ASC Result Register
#define ADC_O_ASCRES                                                0x00000170U

// Conversion Memory Control Register 0
#define ADC_O_MEMCTL0                                               0x00000180U

// Conversion Memory Control Register 1
#define ADC_O_MEMCTL1                                               0x00000184U

// Conversion Memory Control Register 2
#define ADC_O_MEMCTL2                                               0x00000188U

// Conversion Memory Control Register 3
#define ADC_O_MEMCTL3                                               0x0000018CU

// Memory Result Register 0
#define ADC_O_MEMRES0                                               0x00000280U

// Memory Result Register 1
#define ADC_O_MEMRES1                                               0x00000284U

// Memory Result Register 2
#define ADC_O_MEMRES2                                               0x00000288U

// Memory Result Register 3
#define ADC_O_MEMRES3                                               0x0000028CU

// Status Register
#define ADC_O_STA                                                   0x00000340U

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST0                                                 0x00000E00U

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST2                                                 0x00000E08U

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST3                                                 0x00000E0CU

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST4                                                 0x00000E10U

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST5                                                 0x00000E14U

// Internal. Only to be used through TI provided API.
#define ADC_O_TEST6                                                 0x00000E18U

// Internal. Only to be used through TI provided API.
#define ADC_O_DEBUG1                                                0x00000E20U

// Internal. Only to be used through TI provided API.
#define ADC_O_DEBUG2                                                0x00000E24U

// Internal. Only to be used through TI provided API.
#define ADC_O_DEBUG3                                                0x00000E28U

// Internal. Only to be used through TI provided API.
#define ADC_O_DEBUG4                                                0x00000E2CU

//*****************************************************************************
//
// Register: ADC_O_IMASK0
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// MEMRES3 conversion result interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_MEMRESIFG3                                       0x00000800U
#define ADC_IMASK0_MEMRESIFG3_M                                     0x00000800U
#define ADC_IMASK0_MEMRESIFG3_S                                             11U
#define ADC_IMASK0_MEMRESIFG3_EN                                    0x00000800U
#define ADC_IMASK0_MEMRESIFG3_DIS                                   0x00000000U

// Field:    [10] MEMRESIFG2
//
// MEMRES2 conversion result interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_MEMRESIFG2                                       0x00000400U
#define ADC_IMASK0_MEMRESIFG2_M                                     0x00000400U
#define ADC_IMASK0_MEMRESIFG2_S                                             10U
#define ADC_IMASK0_MEMRESIFG2_EN                                    0x00000400U
#define ADC_IMASK0_MEMRESIFG2_DIS                                   0x00000000U

// Field:     [9] MEMRESIFG1
//
// MEMRES1 conversion result interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_MEMRESIFG1                                       0x00000200U
#define ADC_IMASK0_MEMRESIFG1_M                                     0x00000200U
#define ADC_IMASK0_MEMRESIFG1_S                                              9U
#define ADC_IMASK0_MEMRESIFG1_EN                                    0x00000200U
#define ADC_IMASK0_MEMRESIFG1_DIS                                   0x00000000U

// Field:     [8] MEMRESIFG0
//
// MEMRES0 conversion result interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_MEMRESIFG0                                       0x00000100U
#define ADC_IMASK0_MEMRESIFG0_M                                     0x00000100U
#define ADC_IMASK0_MEMRESIFG0_S                                              8U
#define ADC_IMASK0_MEMRESIFG0_EN                                    0x00000100U
#define ADC_IMASK0_MEMRESIFG0_DIS                                   0x00000000U

// Field:     [7] ASCDONE
//
// Mask for ASC done raw interrupt flag.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_ASCDONE                                          0x00000080U
#define ADC_IMASK0_ASCDONE_M                                        0x00000080U
#define ADC_IMASK0_ASCDONE_S                                                 7U
#define ADC_IMASK0_ASCDONE_EN                                       0x00000080U
#define ADC_IMASK0_ASCDONE_DIS                                      0x00000000U

// Field:     [6] UVIFG
//
// Conversion underflow interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_UVIFG                                            0x00000040U
#define ADC_IMASK0_UVIFG_M                                          0x00000040U
#define ADC_IMASK0_UVIFG_S                                                   6U
#define ADC_IMASK0_UVIFG_EN                                         0x00000040U
#define ADC_IMASK0_UVIFG_DIS                                        0x00000000U

// Field:     [5] DMADONE
//
// DMA done interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_DMADONE                                          0x00000020U
#define ADC_IMASK0_DMADONE_M                                        0x00000020U
#define ADC_IMASK0_DMADONE_S                                                 5U
#define ADC_IMASK0_DMADONE_EN                                       0x00000020U
#define ADC_IMASK0_DMADONE_DIS                                      0x00000000U

// Field:     [4] INIFG
//
// In-range comparator interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_INIFG                                            0x00000010U
#define ADC_IMASK0_INIFG_M                                          0x00000010U
#define ADC_IMASK0_INIFG_S                                                   4U
#define ADC_IMASK0_INIFG_EN                                         0x00000010U
#define ADC_IMASK0_INIFG_DIS                                        0x00000000U

// Field:     [3] LOWIFG
//
// Low threshold compare interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_LOWIFG                                           0x00000008U
#define ADC_IMASK0_LOWIFG_M                                         0x00000008U
#define ADC_IMASK0_LOWIFG_S                                                  3U
#define ADC_IMASK0_LOWIFG_EN                                        0x00000008U
#define ADC_IMASK0_LOWIFG_DIS                                       0x00000000U

// Field:     [2] HIGHIFG
//
// High threshold compare interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_HIGHIFG                                          0x00000004U
#define ADC_IMASK0_HIGHIFG_M                                        0x00000004U
#define ADC_IMASK0_HIGHIFG_S                                                 2U
#define ADC_IMASK0_HIGHIFG_EN                                       0x00000004U
#define ADC_IMASK0_HIGHIFG_DIS                                      0x00000000U

// Field:     [1] TOVIFG
//
// Sequence conversion time overflow interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_TOVIFG                                           0x00000002U
#define ADC_IMASK0_TOVIFG_M                                         0x00000002U
#define ADC_IMASK0_TOVIFG_S                                                  1U
#define ADC_IMASK0_TOVIFG_EN                                        0x00000002U
#define ADC_IMASK0_TOVIFG_DIS                                       0x00000000U

// Field:     [0] OVIFG
//
// Conversion overflow interrupt mask.
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define ADC_IMASK0_OVIFG                                            0x00000001U
#define ADC_IMASK0_OVIFG_M                                          0x00000001U
#define ADC_IMASK0_OVIFG_S                                                   0U
#define ADC_IMASK0_OVIFG_EN                                         0x00000001U
#define ADC_IMASK0_OVIFG_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: ADC_O_RIS0
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Raw interrupt status for MEMRES3.
// This bit is set to 1 when MEMRES3 is loaded with a new
// conversion result.
// Reading MEMRES3 register will clear this bit, or when the
// corresponding bit in ICLR0 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS0_MEMRESIFG3                                         0x00000800U
#define ADC_RIS0_MEMRESIFG3_M                                       0x00000800U
#define ADC_RIS0_MEMRESIFG3_S                                               11U
#define ADC_RIS0_MEMRESIFG3_SET                                     0x00000800U
#define ADC_RIS0_MEMRESIFG3_CLR                                     0x00000000U

// Field:    [10] MEMRESIFG2
//
// Raw interrupt status for MEMRES2.
// This bit is set to 1 when MEMRES2 is loaded with a new
// conversion result.
// Reading MEMRES2 register will clear this bit, or when the
// corresponding bit in ICLR0 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS0_MEMRESIFG2                                         0x00000400U
#define ADC_RIS0_MEMRESIFG2_M                                       0x00000400U
#define ADC_RIS0_MEMRESIFG2_S                                               10U
#define ADC_RIS0_MEMRESIFG2_SET                                     0x00000400U
#define ADC_RIS0_MEMRESIFG2_CLR                                     0x00000000U

// Field:     [9] MEMRESIFG1
//
// Raw interrupt status for MEMRES1.
// This bit is set to 1 when MEMRES1 is loaded with a new
// conversion result.
// Reading MEMRES1 register will clear this bit, or when the
// corresponding bit in ICLR0 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS0_MEMRESIFG1                                         0x00000200U
#define ADC_RIS0_MEMRESIFG1_M                                       0x00000200U
#define ADC_RIS0_MEMRESIFG1_S                                                9U
#define ADC_RIS0_MEMRESIFG1_SET                                     0x00000200U
#define ADC_RIS0_MEMRESIFG1_CLR                                     0x00000000U

// Field:     [8] MEMRESIFG0
//
// Raw interrupt status for MEMRES0.
// This bit is set to 1 when MEMRES0 is loaded with a new
// conversion result.
// Reading MEMRES0 register will clear this bit, or when the
// corresponding bit in ICLR0 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS0_MEMRESIFG0                                         0x00000100U
#define ADC_RIS0_MEMRESIFG0_M                                       0x00000100U
#define ADC_RIS0_MEMRESIFG0_S                                                8U
#define ADC_RIS0_MEMRESIFG0_SET                                     0x00000100U
#define ADC_RIS0_MEMRESIFG0_CLR                                     0x00000000U

// Field:     [7] ASCDONE
//
// Raw interrupt flag for ASC done.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_ASCDONE                                            0x00000080U
#define ADC_RIS0_ASCDONE_M                                          0x00000080U
#define ADC_RIS0_ASCDONE_S                                                   7U
#define ADC_RIS0_ASCDONE_SET                                        0x00000080U
#define ADC_RIS0_ASCDONE_CLR                                        0x00000000U

// Field:     [6] UVIFG
//
// Raw interrupt flag for MEMRESx underflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_UVIFG                                              0x00000040U
#define ADC_RIS0_UVIFG_M                                            0x00000040U
#define ADC_RIS0_UVIFG_S                                                     6U
#define ADC_RIS0_UVIFG_SET                                          0x00000040U
#define ADC_RIS0_UVIFG_CLR                                          0x00000000U

// Field:     [5] DMADONE
//
// Raw interrupt flag for DMADONE.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_DMADONE                                            0x00000020U
#define ADC_RIS0_DMADONE_M                                          0x00000020U
#define ADC_RIS0_DMADONE_S                                                   5U
#define ADC_RIS0_DMADONE_SET                                        0x00000020U
#define ADC_RIS0_DMADONE_CLR                                        0x00000000U

// Field:     [4] INIFG
//
// Raw interrupt status for In-range comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_INIFG                                              0x00000010U
#define ADC_RIS0_INIFG_M                                            0x00000010U
#define ADC_RIS0_INIFG_S                                                     4U
#define ADC_RIS0_INIFG_SET                                          0x00000010U
#define ADC_RIS0_INIFG_CLR                                          0x00000000U

// Field:     [3] LOWIFG
//
// Raw interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_LOWIFG                                             0x00000008U
#define ADC_RIS0_LOWIFG_M                                           0x00000008U
#define ADC_RIS0_LOWIFG_S                                                    3U
#define ADC_RIS0_LOWIFG_SET                                         0x00000008U
#define ADC_RIS0_LOWIFG_CLR                                         0x00000000U

// Field:     [2] HIGHIFG
//
// Raw interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_HIGHIFG                                            0x00000004U
#define ADC_RIS0_HIGHIFG_M                                          0x00000004U
#define ADC_RIS0_HIGHIFG_S                                                   2U
#define ADC_RIS0_HIGHIFG_SET                                        0x00000004U
#define ADC_RIS0_HIGHIFG_CLR                                        0x00000000U

// Field:     [1] TOVIFG
//
// Raw interrupt flag for sequence conversion trigger overflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_TOVIFG                                             0x00000002U
#define ADC_RIS0_TOVIFG_M                                           0x00000002U
#define ADC_RIS0_TOVIFG_S                                                    1U
#define ADC_RIS0_TOVIFG_SET                                         0x00000002U
#define ADC_RIS0_TOVIFG_CLR                                         0x00000000U

// Field:     [0] OVIFG
//
// Raw interrupt flag for MEMRESx overflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS0_OVIFG                                              0x00000001U
#define ADC_RIS0_OVIFG_M                                            0x00000001U
#define ADC_RIS0_OVIFG_S                                                     0U
#define ADC_RIS0_OVIFG_SET                                          0x00000001U
#define ADC_RIS0_OVIFG_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MIS0
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Masked interrupt status for MEMRES3.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS0_MEMRESIFG3                                         0x00000800U
#define ADC_MIS0_MEMRESIFG3_M                                       0x00000800U
#define ADC_MIS0_MEMRESIFG3_S                                               11U
#define ADC_MIS0_MEMRESIFG3_SET                                     0x00000800U
#define ADC_MIS0_MEMRESIFG3_CLR                                     0x00000000U

// Field:    [10] MEMRESIFG2
//
// Masked interrupt status for MEMRES2.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS0_MEMRESIFG2                                         0x00000400U
#define ADC_MIS0_MEMRESIFG2_M                                       0x00000400U
#define ADC_MIS0_MEMRESIFG2_S                                               10U
#define ADC_MIS0_MEMRESIFG2_SET                                     0x00000400U
#define ADC_MIS0_MEMRESIFG2_CLR                                     0x00000000U

// Field:     [9] MEMRESIFG1
//
// Masked interrupt status for MEMRES1.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS0_MEMRESIFG1                                         0x00000200U
#define ADC_MIS0_MEMRESIFG1_M                                       0x00000200U
#define ADC_MIS0_MEMRESIFG1_S                                                9U
#define ADC_MIS0_MEMRESIFG1_SET                                     0x00000200U
#define ADC_MIS0_MEMRESIFG1_CLR                                     0x00000000U

// Field:     [8] MEMRESIFG0
//
// Masked interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS0_MEMRESIFG0                                         0x00000100U
#define ADC_MIS0_MEMRESIFG0_M                                       0x00000100U
#define ADC_MIS0_MEMRESIFG0_S                                                8U
#define ADC_MIS0_MEMRESIFG0_SET                                     0x00000100U
#define ADC_MIS0_MEMRESIFG0_CLR                                     0x00000000U

// Field:     [7] ASCDONE
//
// Masked interrupt status for ASC done.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_ASCDONE                                            0x00000080U
#define ADC_MIS0_ASCDONE_M                                          0x00000080U
#define ADC_MIS0_ASCDONE_S                                                   7U
#define ADC_MIS0_ASCDONE_SET                                        0x00000080U
#define ADC_MIS0_ASCDONE_CLR                                        0x00000000U

// Field:     [6] UVIFG
//
// Masked interrupt flag for MEMRESx underflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_UVIFG                                              0x00000040U
#define ADC_MIS0_UVIFG_M                                            0x00000040U
#define ADC_MIS0_UVIFG_S                                                     6U
#define ADC_MIS0_UVIFG_SET                                          0x00000040U
#define ADC_MIS0_UVIFG_CLR                                          0x00000000U

// Field:     [5] DMADONE
//
// Masked interrupt flag for DMADONE.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_DMADONE                                            0x00000020U
#define ADC_MIS0_DMADONE_M                                          0x00000020U
#define ADC_MIS0_DMADONE_S                                                   5U
#define ADC_MIS0_DMADONE_SET                                        0x00000020U
#define ADC_MIS0_DMADONE_CLR                                        0x00000000U

// Field:     [4] INIFG
//
// Mask INIFG in MIS0 register.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_INIFG                                              0x00000010U
#define ADC_MIS0_INIFG_M                                            0x00000010U
#define ADC_MIS0_INIFG_S                                                     4U
#define ADC_MIS0_INIFG_SET                                          0x00000010U
#define ADC_MIS0_INIFG_CLR                                          0x00000000U

// Field:     [3] LOWIFG
//
// Masked interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_LOWIFG                                             0x00000008U
#define ADC_MIS0_LOWIFG_M                                           0x00000008U
#define ADC_MIS0_LOWIFG_S                                                    3U
#define ADC_MIS0_LOWIFG_SET                                         0x00000008U
#define ADC_MIS0_LOWIFG_CLR                                         0x00000000U

// Field:     [2] HIGHIFG
//
// Masked interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_HIGHIFG                                            0x00000004U
#define ADC_MIS0_HIGHIFG_M                                          0x00000004U
#define ADC_MIS0_HIGHIFG_S                                                   2U
#define ADC_MIS0_HIGHIFG_SET                                        0x00000004U
#define ADC_MIS0_HIGHIFG_CLR                                        0x00000000U

// Field:     [1] TOVIFG
//
// Masked interrupt flag for sequence conversion timeout overflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_TOVIFG                                             0x00000002U
#define ADC_MIS0_TOVIFG_M                                           0x00000002U
#define ADC_MIS0_TOVIFG_S                                                    1U
#define ADC_MIS0_TOVIFG_SET                                         0x00000002U
#define ADC_MIS0_TOVIFG_CLR                                         0x00000000U

// Field:     [0] OVIFG
//
// Masked interrupt flag for MEMRESx overflow.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS0_OVIFG                                              0x00000001U
#define ADC_MIS0_OVIFG_M                                            0x00000001U
#define ADC_MIS0_OVIFG_S                                                     0U
#define ADC_MIS0_OVIFG_SET                                          0x00000001U
#define ADC_MIS0_OVIFG_CLR                                          0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ISET0
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Set interrupt status for MEMRES3.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET0_MEMRESIFG3                                        0x00000800U
#define ADC_ISET0_MEMRESIFG3_M                                      0x00000800U
#define ADC_ISET0_MEMRESIFG3_S                                              11U
#define ADC_ISET0_MEMRESIFG3_SET                                    0x00000800U
#define ADC_ISET0_MEMRESIFG3_NO_EFFECT                              0x00000000U

// Field:    [10] MEMRESIFG2
//
// Set interrupt status for MEMRES2.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET0_MEMRESIFG2                                        0x00000400U
#define ADC_ISET0_MEMRESIFG2_M                                      0x00000400U
#define ADC_ISET0_MEMRESIFG2_S                                              10U
#define ADC_ISET0_MEMRESIFG2_SET                                    0x00000400U
#define ADC_ISET0_MEMRESIFG2_NO_EFFECT                              0x00000000U

// Field:     [9] MEMRESIFG1
//
// Set interrupt status for MEMRES1.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET0_MEMRESIFG1                                        0x00000200U
#define ADC_ISET0_MEMRESIFG1_M                                      0x00000200U
#define ADC_ISET0_MEMRESIFG1_S                                               9U
#define ADC_ISET0_MEMRESIFG1_SET                                    0x00000200U
#define ADC_ISET0_MEMRESIFG1_NO_EFFECT                              0x00000000U

// Field:     [8] MEMRESIFG0
//
// Set Interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET0_MEMRESIFG0                                        0x00000100U
#define ADC_ISET0_MEMRESIFG0_M                                      0x00000100U
#define ADC_ISET0_MEMRESIFG0_S                                               8U
#define ADC_ISET0_MEMRESIFG0_SET                                    0x00000100U
#define ADC_ISET0_MEMRESIFG0_NO_EFFECT                              0x00000000U

// Field:     [7] ASCDONE
//
// Set interrupt for ASC done.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_ASCDONE                                           0x00000080U
#define ADC_ISET0_ASCDONE_M                                         0x00000080U
#define ADC_ISET0_ASCDONE_S                                                  7U
#define ADC_ISET0_ASCDONE_SET                                       0x00000080U
#define ADC_ISET0_ASCDONE_NO_EFFECT                                 0x00000000U

// Field:     [6] UVIFG
//
// Set interrupt for MEMRESx underflow.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_UVIFG                                             0x00000040U
#define ADC_ISET0_UVIFG_M                                           0x00000040U
#define ADC_ISET0_UVIFG_S                                                    6U
#define ADC_ISET0_UVIFG_SET                                         0x00000040U
#define ADC_ISET0_UVIFG_NO_EFFECT                                   0x00000000U

// Field:     [5] DMADONE
//
// Set interrupt for DMADONE.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_DMADONE                                           0x00000020U
#define ADC_ISET0_DMADONE_M                                         0x00000020U
#define ADC_ISET0_DMADONE_S                                                  5U
#define ADC_ISET0_DMADONE_SET                                       0x00000020U
#define ADC_ISET0_DMADONE_NO_EFFECT                                 0x00000000U

// Field:     [4] INIFG
//
// Set INIFG interrupt register.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_INIFG                                             0x00000010U
#define ADC_ISET0_INIFG_M                                           0x00000010U
#define ADC_ISET0_INIFG_S                                                    4U
#define ADC_ISET0_INIFG_SET                                         0x00000010U
#define ADC_ISET0_INIFG_NO_EFFECT                                   0x00000000U

// Field:     [3] LOWIFG
//
// Set interrupt for MEMRESx result register being below than the WCLOWx
// threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_LOWIFG                                            0x00000008U
#define ADC_ISET0_LOWIFG_M                                          0x00000008U
#define ADC_ISET0_LOWIFG_S                                                   3U
#define ADC_ISET0_LOWIFG_SET                                        0x00000008U
#define ADC_ISET0_LOWIFG_NO_EFFECT                                  0x00000000U

// Field:     [2] HIGHIFG
//
// Set Interrupt for the MEMRESx result register being higher than the WCHIGHx
// threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_HIGHIFG                                           0x00000004U
#define ADC_ISET0_HIGHIFG_M                                         0x00000004U
#define ADC_ISET0_HIGHIFG_S                                                  2U
#define ADC_ISET0_HIGHIFG_SET                                       0x00000004U
#define ADC_ISET0_HIGHIFG_NO_EFFECT                                 0x00000000U

// Field:     [1] TOVIFG
//
// Set interrupt for sequence conversion timeout overflow.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_TOVIFG                                            0x00000002U
#define ADC_ISET0_TOVIFG_M                                          0x00000002U
#define ADC_ISET0_TOVIFG_S                                                   1U
#define ADC_ISET0_TOVIFG_SET                                        0x00000002U
#define ADC_ISET0_TOVIFG_NO_EFFECT                                  0x00000000U

// Field:     [0] OVIFG
//
// Set Interrupt for MEMRESx overflow.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET0_OVIFG                                             0x00000001U
#define ADC_ISET0_OVIFG_M                                           0x00000001U
#define ADC_ISET0_OVIFG_S                                                    0U
#define ADC_ISET0_OVIFG_SET                                         0x00000001U
#define ADC_ISET0_OVIFG_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ICLR0
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Clear interrupt status for MEMRES3.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR0_MEMRESIFG3                                        0x00000800U
#define ADC_ICLR0_MEMRESIFG3_M                                      0x00000800U
#define ADC_ICLR0_MEMRESIFG3_S                                              11U
#define ADC_ICLR0_MEMRESIFG3_CLR                                    0x00000800U
#define ADC_ICLR0_MEMRESIFG3_NO_EFFECT                              0x00000000U

// Field:    [10] MEMRESIFG2
//
// Clear interrupt status for MEMRES2.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR0_MEMRESIFG2                                        0x00000400U
#define ADC_ICLR0_MEMRESIFG2_M                                      0x00000400U
#define ADC_ICLR0_MEMRESIFG2_S                                              10U
#define ADC_ICLR0_MEMRESIFG2_CLR                                    0x00000400U
#define ADC_ICLR0_MEMRESIFG2_NO_EFFECT                              0x00000000U

// Field:     [9] MEMRESIFG1
//
// Clear interrupt status for MEMRES1.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR0_MEMRESIFG1                                        0x00000200U
#define ADC_ICLR0_MEMRESIFG1_M                                      0x00000200U
#define ADC_ICLR0_MEMRESIFG1_S                                               9U
#define ADC_ICLR0_MEMRESIFG1_CLR                                    0x00000200U
#define ADC_ICLR0_MEMRESIFG1_NO_EFFECT                              0x00000000U

// Field:     [8] MEMRESIFG0
//
// Clear interrupt status for MEMRES0.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR0_MEMRESIFG0                                        0x00000100U
#define ADC_ICLR0_MEMRESIFG0_M                                      0x00000100U
#define ADC_ICLR0_MEMRESIFG0_S                                               8U
#define ADC_ICLR0_MEMRESIFG0_CLR                                    0x00000100U
#define ADC_ICLR0_MEMRESIFG0_NO_EFFECT                              0x00000000U

// Field:     [7] ASCDONE
//
// Clear ASC done flag in RIS.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_ASCDONE                                           0x00000080U
#define ADC_ICLR0_ASCDONE_M                                         0x00000080U
#define ADC_ICLR0_ASCDONE_S                                                  7U
#define ADC_ICLR0_ASCDONE_CLR                                       0x00000080U
#define ADC_ICLR0_ASCDONE_NO_EFFECT                                 0x00000000U

// Field:     [6] UVIFG
//
// Clear interrupt flag for MEMRESx underflow.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_UVIFG                                             0x00000040U
#define ADC_ICLR0_UVIFG_M                                           0x00000040U
#define ADC_ICLR0_UVIFG_S                                                    6U
#define ADC_ICLR0_UVIFG_CLR                                         0x00000040U
#define ADC_ICLR0_UVIFG_NO_EFFECT                                   0x00000000U

// Field:     [5] DMADONE
//
// Clear interrupt flag for DMADONE.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_DMADONE                                           0x00000020U
#define ADC_ICLR0_DMADONE_M                                         0x00000020U
#define ADC_ICLR0_DMADONE_S                                                  5U
#define ADC_ICLR0_DMADONE_CLR                                       0x00000020U
#define ADC_ICLR0_DMADONE_NO_EFFECT                                 0x00000000U

// Field:     [4] INIFG
//
// Clear INIFG in MIS0 register.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_INIFG                                             0x00000010U
#define ADC_ICLR0_INIFG_M                                           0x00000010U
#define ADC_ICLR0_INIFG_S                                                    4U
#define ADC_ICLR0_INIFG_CLR                                         0x00000010U
#define ADC_ICLR0_INIFG_NO_EFFECT                                   0x00000000U

// Field:     [3] LOWIFG
//
// Clear interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_LOWIFG                                            0x00000008U
#define ADC_ICLR0_LOWIFG_M                                          0x00000008U
#define ADC_ICLR0_LOWIFG_S                                                   3U
#define ADC_ICLR0_LOWIFG_CLR                                        0x00000008U
#define ADC_ICLR0_LOWIFG_NO_EFFECT                                  0x00000000U

// Field:     [2] HIGHIFG
//
// Clear interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_HIGHIFG                                           0x00000004U
#define ADC_ICLR0_HIGHIFG_M                                         0x00000004U
#define ADC_ICLR0_HIGHIFG_S                                                  2U
#define ADC_ICLR0_HIGHIFG_CLR                                       0x00000004U
#define ADC_ICLR0_HIGHIFG_NO_EFFECT                                 0x00000000U

// Field:     [1] TOVIFG
//
// Clear interrupt flag for sequence conversion timeout overflow.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_TOVIFG                                            0x00000002U
#define ADC_ICLR0_TOVIFG_M                                          0x00000002U
#define ADC_ICLR0_TOVIFG_S                                                   1U
#define ADC_ICLR0_TOVIFG_CLR                                        0x00000002U
#define ADC_ICLR0_TOVIFG_NO_EFFECT                                  0x00000000U

// Field:     [0] OVIFG
//
// Clear interrupt flag for MEMRESx overflow.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR0_OVIFG                                             0x00000001U
#define ADC_ICLR0_OVIFG_M                                           0x00000001U
#define ADC_ICLR0_OVIFG_S                                                    0U
#define ADC_ICLR0_OVIFG_CLR                                         0x00000001U
#define ADC_ICLR0_OVIFG_NO_EFFECT                                   0x00000000U

//*****************************************************************************
//
// Register: ADC_O_IMASK1
//
//*****************************************************************************
// Field:     [8] MEMRESIFG0
//
// MEMRES0 conversion result interrupt mask.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_IMASK1_MEMRESIFG0                                       0x00000100U
#define ADC_IMASK1_MEMRESIFG0_M                                     0x00000100U
#define ADC_IMASK1_MEMRESIFG0_S                                              8U
#define ADC_IMASK1_MEMRESIFG0_SET                                   0x00000100U
#define ADC_IMASK1_MEMRESIFG0_CLR                                   0x00000000U

// Field:     [4] INIFG
//
// In-range comparator interrupt mask.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_IMASK1_INIFG                                            0x00000010U
#define ADC_IMASK1_INIFG_M                                          0x00000010U
#define ADC_IMASK1_INIFG_S                                                   4U
#define ADC_IMASK1_INIFG_SET                                        0x00000010U
#define ADC_IMASK1_INIFG_CLR                                        0x00000000U

// Field:     [3] LOWIFG
//
// Low threshold compare interrupt mask.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_IMASK1_LOWIFG                                           0x00000008U
#define ADC_IMASK1_LOWIFG_M                                         0x00000008U
#define ADC_IMASK1_LOWIFG_S                                                  3U
#define ADC_IMASK1_LOWIFG_SET                                       0x00000008U
#define ADC_IMASK1_LOWIFG_CLR                                       0x00000000U

// Field:     [2] HIGHIFG
//
// High threshold compare interrupt mask.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_IMASK1_HIGHIFG                                          0x00000004U
#define ADC_IMASK1_HIGHIFG_M                                        0x00000004U
#define ADC_IMASK1_HIGHIFG_S                                                 2U
#define ADC_IMASK1_HIGHIFG_SET                                      0x00000004U
#define ADC_IMASK1_HIGHIFG_CLR                                      0x00000000U

//*****************************************************************************
//
// Register: ADC_O_RIS1
//
//*****************************************************************************
// Field:     [8] MEMRESIFG0
//
// Raw interrupt status for MEMRES0.
// This bit is set to 1 when MEMRES0 is loaded with a new
// conversion result.
// Reading MEMRES0 register will clear this bit, or when the
// corresponding bit in ICLR1 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS1_MEMRESIFG0                                         0x00000100U
#define ADC_RIS1_MEMRESIFG0_M                                       0x00000100U
#define ADC_RIS1_MEMRESIFG0_S                                                8U
#define ADC_RIS1_MEMRESIFG0_SET                                     0x00000100U
#define ADC_RIS1_MEMRESIFG0_CLR                                     0x00000000U

// Field:     [4] INIFG
//
// Raw interrupt status for In-range comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS1_INIFG                                              0x00000010U
#define ADC_RIS1_INIFG_M                                            0x00000010U
#define ADC_RIS1_INIFG_S                                                     4U
#define ADC_RIS1_INIFG_SET                                          0x00000010U
#define ADC_RIS1_INIFG_CLR                                          0x00000000U

// Field:     [3] LOWIFG
//
// Raw interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS1_LOWIFG                                             0x00000008U
#define ADC_RIS1_LOWIFG_M                                           0x00000008U
#define ADC_RIS1_LOWIFG_S                                                    3U
#define ADC_RIS1_LOWIFG_SET                                         0x00000008U
#define ADC_RIS1_LOWIFG_CLR                                         0x00000000U

// Field:     [2] HIGHIFG
//
// Raw interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_RIS1_HIGHIFG                                            0x00000004U
#define ADC_RIS1_HIGHIFG_M                                          0x00000004U
#define ADC_RIS1_HIGHIFG_S                                                   2U
#define ADC_RIS1_HIGHIFG_SET                                        0x00000004U
#define ADC_RIS1_HIGHIFG_CLR                                        0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MIS1
//
//*****************************************************************************
// Field:     [8] MEMRESIFG0
//
// Masked interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS1_MEMRESIFG0                                         0x00000100U
#define ADC_MIS1_MEMRESIFG0_M                                       0x00000100U
#define ADC_MIS1_MEMRESIFG0_S                                                8U
#define ADC_MIS1_MEMRESIFG0_SET                                     0x00000100U
#define ADC_MIS1_MEMRESIFG0_CLR                                     0x00000000U

// Field:     [4] INIFG
//
// Mask INIFG in MIS1 register.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS1_INIFG                                              0x00000010U
#define ADC_MIS1_INIFG_M                                            0x00000010U
#define ADC_MIS1_INIFG_S                                                     4U
#define ADC_MIS1_INIFG_SET                                          0x00000010U
#define ADC_MIS1_INIFG_CLR                                          0x00000000U

// Field:     [3] LOWIFG
//
// Masked interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS1_LOWIFG                                             0x00000008U
#define ADC_MIS1_LOWIFG_M                                           0x00000008U
#define ADC_MIS1_LOWIFG_S                                                    3U
#define ADC_MIS1_LOWIFG_SET                                         0x00000008U
#define ADC_MIS1_LOWIFG_CLR                                         0x00000000U

// Field:     [2] HIGHIFG
//
// Masked interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// CLR                      Interrupt is not pending.
#define ADC_MIS1_HIGHIFG                                            0x00000004U
#define ADC_MIS1_HIGHIFG_M                                          0x00000004U
#define ADC_MIS1_HIGHIFG_S                                                   2U
#define ADC_MIS1_HIGHIFG_SET                                        0x00000004U
#define ADC_MIS1_HIGHIFG_CLR                                        0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ISET1
//
//*****************************************************************************
// Field:     [8] MEMRESIFG0
//
// Set Interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET1_MEMRESIFG0                                        0x00000100U
#define ADC_ISET1_MEMRESIFG0_M                                      0x00000100U
#define ADC_ISET1_MEMRESIFG0_S                                               8U
#define ADC_ISET1_MEMRESIFG0_SET                                    0x00000100U
#define ADC_ISET1_MEMRESIFG0_NO_EFFECT                              0x00000000U

// Field:     [4] INIFG
//
// Set INIFG interrupt register.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET1_INIFG                                             0x00000010U
#define ADC_ISET1_INIFG_M                                           0x00000010U
#define ADC_ISET1_INIFG_S                                                    4U
#define ADC_ISET1_INIFG_SET                                         0x00000010U
#define ADC_ISET1_INIFG_NO_EFFECT                                   0x00000000U

// Field:     [3] LOWIFG
//
// Set interrupt for MEMRESx result register being below than the WCLOWx
// threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET1_LOWIFG                                            0x00000008U
#define ADC_ISET1_LOWIFG_M                                          0x00000008U
#define ADC_ISET1_LOWIFG_S                                                   3U
#define ADC_ISET1_LOWIFG_SET                                        0x00000008U
#define ADC_ISET1_LOWIFG_NO_EFFECT                                  0x00000000U

// Field:     [2] HIGHIFG
//
// Set Interrupt for the MEMRESx result register being higher than the WCHIGHx
// threshold of the window comparator.
// ENUMs:
// SET                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ISET1_HIGHIFG                                           0x00000004U
#define ADC_ISET1_HIGHIFG_M                                         0x00000004U
#define ADC_ISET1_HIGHIFG_S                                                  2U
#define ADC_ISET1_HIGHIFG_SET                                       0x00000004U
#define ADC_ISET1_HIGHIFG_NO_EFFECT                                 0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ICLR1
//
//*****************************************************************************
// Field:     [8] MEMRESIFG0
//
// Clear interrupt status for MEMRES0.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR1_MEMRESIFG0                                        0x00000100U
#define ADC_ICLR1_MEMRESIFG0_M                                      0x00000100U
#define ADC_ICLR1_MEMRESIFG0_S                                               8U
#define ADC_ICLR1_MEMRESIFG0_CLR                                    0x00000100U
#define ADC_ICLR1_MEMRESIFG0_NO_EFFECT                              0x00000000U

// Field:     [4] INIFG
//
// Clear INIFG in MIS1 register.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR1_INIFG                                             0x00000010U
#define ADC_ICLR1_INIFG_M                                           0x00000010U
#define ADC_ICLR1_INIFG_S                                                    4U
#define ADC_ICLR1_INIFG_CLR                                         0x00000010U
#define ADC_ICLR1_INIFG_NO_EFFECT                                   0x00000000U

// Field:     [3] LOWIFG
//
// Clear interrupt flag for the MEMRESx result register being below than the
// WCLOWx threshold of the window comparator.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR1_LOWIFG                                            0x00000008U
#define ADC_ICLR1_LOWIFG_M                                          0x00000008U
#define ADC_ICLR1_LOWIFG_S                                                   3U
#define ADC_ICLR1_LOWIFG_CLR                                        0x00000008U
#define ADC_ICLR1_LOWIFG_NO_EFFECT                                  0x00000000U

// Field:     [2] HIGHIFG
//
// Clear interrupt flag for the MEMRESx result register being higher than the
// WCHIGHx threshold of the window comparator.
// ENUMs:
// CLR                      Interrupt is pending.
// NO_EFFECT                Interrupt is not pending.
#define ADC_ICLR1_HIGHIFG                                           0x00000004U
#define ADC_ICLR1_HIGHIFG_M                                         0x00000004U
#define ADC_ICLR1_HIGHIFG_S                                                  2U
#define ADC_ICLR1_HIGHIFG_CLR                                       0x00000004U
#define ADC_ICLR1_HIGHIFG_NO_EFFECT                                 0x00000000U

//*****************************************************************************
//
// Register: ADC_O_IMASK2
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// MEMRES3 conversion result interrupt mask.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_IMASK2_MEMRESIFG3                                       0x00000800U
#define ADC_IMASK2_MEMRESIFG3_M                                     0x00000800U
#define ADC_IMASK2_MEMRESIFG3_S                                             11U
#define ADC_IMASK2_MEMRESIFG3_SET                                   0x00000800U
#define ADC_IMASK2_MEMRESIFG3_CLR                                   0x00000000U

// Field:    [10] MEMRESIFG2
//
// MEMRES2 conversion result interrupt mask.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_IMASK2_MEMRESIFG2                                       0x00000400U
#define ADC_IMASK2_MEMRESIFG2_M                                     0x00000400U
#define ADC_IMASK2_MEMRESIFG2_S                                             10U
#define ADC_IMASK2_MEMRESIFG2_SET                                   0x00000400U
#define ADC_IMASK2_MEMRESIFG2_CLR                                   0x00000000U

// Field:     [9] MEMRESIFG1
//
// MEMRES1 conversion result interrupt mask.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_IMASK2_MEMRESIFG1                                       0x00000200U
#define ADC_IMASK2_MEMRESIFG1_M                                     0x00000200U
#define ADC_IMASK2_MEMRESIFG1_S                                              9U
#define ADC_IMASK2_MEMRESIFG1_SET                                   0x00000200U
#define ADC_IMASK2_MEMRESIFG1_CLR                                   0x00000000U

// Field:     [8] MEMRESIFG0
//
// MEMRES0 conversion result interrupt mask.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_IMASK2_MEMRESIFG0                                       0x00000100U
#define ADC_IMASK2_MEMRESIFG0_M                                     0x00000100U
#define ADC_IMASK2_MEMRESIFG0_S                                              8U
#define ADC_IMASK2_MEMRESIFG0_SET                                   0x00000100U
#define ADC_IMASK2_MEMRESIFG0_CLR                                   0x00000000U

//*****************************************************************************
//
// Register: ADC_O_RIS2
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Raw interrupt status for MEMRES3.
// This bit is set to 1 when MEMRES3 is loaded with a new
// conversion result.
// Reading MEMRES3 register will clear this bit, or when the
// corresponding bit in ICLR2 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS2_MEMRESIFG3                                         0x00000800U
#define ADC_RIS2_MEMRESIFG3_M                                       0x00000800U
#define ADC_RIS2_MEMRESIFG3_S                                               11U
#define ADC_RIS2_MEMRESIFG3_SET                                     0x00000800U
#define ADC_RIS2_MEMRESIFG3_CLR                                     0x00000000U

// Field:    [10] MEMRESIFG2
//
// Raw interrupt status for MEMRES2.
// This bit is set to 1 when MEMRES2 is loaded with a new
// conversion result.
// Reading MEMRES2 register will clear this bit, or when the
// corresponding bit in ICLR2 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS2_MEMRESIFG2                                         0x00000400U
#define ADC_RIS2_MEMRESIFG2_M                                       0x00000400U
#define ADC_RIS2_MEMRESIFG2_S                                               10U
#define ADC_RIS2_MEMRESIFG2_SET                                     0x00000400U
#define ADC_RIS2_MEMRESIFG2_CLR                                     0x00000000U

// Field:     [9] MEMRESIFG1
//
// Raw interrupt status for MEMRES1.
// This bit is set to 1 when MEMRES1 is loaded with a new
// conversion result.
// Reading MEMRES1 register will clear this bit, or when the
// corresponding bit in ICLR2 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS2_MEMRESIFG1                                         0x00000200U
#define ADC_RIS2_MEMRESIFG1_M                                       0x00000200U
#define ADC_RIS2_MEMRESIFG1_S                                                9U
#define ADC_RIS2_MEMRESIFG1_SET                                     0x00000200U
#define ADC_RIS2_MEMRESIFG1_CLR                                     0x00000000U

// Field:     [8] MEMRESIFG0
//
// Raw interrupt status for MEMRES0.
// This bit is set to 1 when MEMRES0 is loaded with a new
// conversion result.
// Reading MEMRES0 register will clear this bit, or when the
// corresponding bit in ICLR2 is set to 1
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_RIS2_MEMRESIFG0                                         0x00000100U
#define ADC_RIS2_MEMRESIFG0_M                                       0x00000100U
#define ADC_RIS2_MEMRESIFG0_S                                                8U
#define ADC_RIS2_MEMRESIFG0_SET                                     0x00000100U
#define ADC_RIS2_MEMRESIFG0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MIS2
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Masked interrupt status for MEMRES3.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS2_MEMRESIFG3                                         0x00000800U
#define ADC_MIS2_MEMRESIFG3_M                                       0x00000800U
#define ADC_MIS2_MEMRESIFG3_S                                               11U
#define ADC_MIS2_MEMRESIFG3_SET                                     0x00000800U
#define ADC_MIS2_MEMRESIFG3_CLR                                     0x00000000U

// Field:    [10] MEMRESIFG2
//
// Masked interrupt status for MEMRES2.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS2_MEMRESIFG2                                         0x00000400U
#define ADC_MIS2_MEMRESIFG2_M                                       0x00000400U
#define ADC_MIS2_MEMRESIFG2_S                                               10U
#define ADC_MIS2_MEMRESIFG2_SET                                     0x00000400U
#define ADC_MIS2_MEMRESIFG2_CLR                                     0x00000000U

// Field:     [9] MEMRESIFG1
//
// Masked interrupt status for MEMRES1.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS2_MEMRESIFG1                                         0x00000200U
#define ADC_MIS2_MEMRESIFG1_M                                       0x00000200U
#define ADC_MIS2_MEMRESIFG1_S                                                9U
#define ADC_MIS2_MEMRESIFG1_SET                                     0x00000200U
#define ADC_MIS2_MEMRESIFG1_CLR                                     0x00000000U

// Field:     [8] MEMRESIFG0
//
// Masked interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// CLR                      No new data ready.
#define ADC_MIS2_MEMRESIFG0                                         0x00000100U
#define ADC_MIS2_MEMRESIFG0_M                                       0x00000100U
#define ADC_MIS2_MEMRESIFG0_S                                                8U
#define ADC_MIS2_MEMRESIFG0_SET                                     0x00000100U
#define ADC_MIS2_MEMRESIFG0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ISET2
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Set interrupt status for MEMRES3.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET2_MEMRESIFG3                                        0x00000800U
#define ADC_ISET2_MEMRESIFG3_M                                      0x00000800U
#define ADC_ISET2_MEMRESIFG3_S                                              11U
#define ADC_ISET2_MEMRESIFG3_SET                                    0x00000800U
#define ADC_ISET2_MEMRESIFG3_NO_EFFECT                              0x00000000U

// Field:    [10] MEMRESIFG2
//
// Set interrupt status for MEMRES2.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET2_MEMRESIFG2                                        0x00000400U
#define ADC_ISET2_MEMRESIFG2_M                                      0x00000400U
#define ADC_ISET2_MEMRESIFG2_S                                              10U
#define ADC_ISET2_MEMRESIFG2_SET                                    0x00000400U
#define ADC_ISET2_MEMRESIFG2_NO_EFFECT                              0x00000000U

// Field:     [9] MEMRESIFG1
//
// Set interrupt status for MEMRES1.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET2_MEMRESIFG1                                        0x00000200U
#define ADC_ISET2_MEMRESIFG1_M                                      0x00000200U
#define ADC_ISET2_MEMRESIFG1_S                                               9U
#define ADC_ISET2_MEMRESIFG1_SET                                    0x00000200U
#define ADC_ISET2_MEMRESIFG1_NO_EFFECT                              0x00000000U

// Field:     [8] MEMRESIFG0
//
// Set Interrupt status for MEMRES0.
// ENUMs:
// SET                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ISET2_MEMRESIFG0                                        0x00000100U
#define ADC_ISET2_MEMRESIFG0_M                                      0x00000100U
#define ADC_ISET2_MEMRESIFG0_S                                               8U
#define ADC_ISET2_MEMRESIFG0_SET                                    0x00000100U
#define ADC_ISET2_MEMRESIFG0_NO_EFFECT                              0x00000000U

//*****************************************************************************
//
// Register: ADC_O_ICLR2
//
//*****************************************************************************
// Field:    [11] MEMRESIFG3
//
// Clear interrupt status for MEMRES3.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR2_MEMRESIFG3                                        0x00000800U
#define ADC_ICLR2_MEMRESIFG3_M                                      0x00000800U
#define ADC_ICLR2_MEMRESIFG3_S                                              11U
#define ADC_ICLR2_MEMRESIFG3_CLR                                    0x00000800U
#define ADC_ICLR2_MEMRESIFG3_NO_EFFECT                              0x00000000U

// Field:    [10] MEMRESIFG2
//
// Clear interrupt status for MEMRES2.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR2_MEMRESIFG2                                        0x00000400U
#define ADC_ICLR2_MEMRESIFG2_M                                      0x00000400U
#define ADC_ICLR2_MEMRESIFG2_S                                              10U
#define ADC_ICLR2_MEMRESIFG2_CLR                                    0x00000400U
#define ADC_ICLR2_MEMRESIFG2_NO_EFFECT                              0x00000000U

// Field:     [9] MEMRESIFG1
//
// Clear interrupt status for MEMRES1.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR2_MEMRESIFG1                                        0x00000200U
#define ADC_ICLR2_MEMRESIFG1_M                                      0x00000200U
#define ADC_ICLR2_MEMRESIFG1_S                                               9U
#define ADC_ICLR2_MEMRESIFG1_CLR                                    0x00000200U
#define ADC_ICLR2_MEMRESIFG1_NO_EFFECT                              0x00000000U

// Field:     [8] MEMRESIFG0
//
// Clear interrupt status for MEMRES0.
// ENUMs:
// CLR                      A new data is ready to be read.
// NO_EFFECT                No new data ready.
#define ADC_ICLR2_MEMRESIFG0                                        0x00000100U
#define ADC_ICLR2_MEMRESIFG0_M                                      0x00000100U
#define ADC_ICLR2_MEMRESIFG0_S                                               8U
#define ADC_ICLR2_MEMRESIFG0_CLR                                    0x00000100U
#define ADC_ICLR2_MEMRESIFG0_NO_EFFECT                              0x00000000U

//*****************************************************************************
//
// Register: ADC_O_CTL0
//
//*****************************************************************************
// Field: [26:24] SCLKDIV
//
// Sample clock divider
// ENUMs:
// DIV_BY_48                Divide clock source by 48
// DIV_BY_32                Divide clock source by 32
// DIV_BY_24                Divide clock source by 24
// DIV_BY_16                Divide clock source by 16
// DIV_BY_8                 Divide clock source by 8
// DIV_BY_4                 Divide clock source by 4
// DIV_BY_2                 Divide clock source by 2
// DIV_BY_1                 Do not divide clock source
#define ADC_CTL0_SCLKDIV_W                                                   3U
#define ADC_CTL0_SCLKDIV_M                                          0x07000000U
#define ADC_CTL0_SCLKDIV_S                                                  24U
#define ADC_CTL0_SCLKDIV_DIV_BY_48                                  0x07000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_32                                  0x06000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_24                                  0x05000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_16                                  0x04000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_8                                   0x03000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_4                                   0x02000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_2                                   0x01000000U
#define ADC_CTL0_SCLKDIV_DIV_BY_1                                   0x00000000U

// Field:    [16] PWRDN
//
// Power down policy
// ENUMs:
// MANUAL                   ADC remains powered on as long as it is enabled
//                          through software.
// AUTO                     ADC is powered down on completion of a conversion
//                          if there is no pending trigger
#define ADC_CTL0_PWRDN                                              0x00010000U
#define ADC_CTL0_PWRDN_M                                            0x00010000U
#define ADC_CTL0_PWRDN_S                                                    16U
#define ADC_CTL0_PWRDN_MANUAL                                       0x00010000U
#define ADC_CTL0_PWRDN_AUTO                                         0x00000000U

// Field:     [0] ENC
//
// Enable conversion
// ENUMs:
// ON                       Conversion enabled. ADC sequencer waits for the
//                          programmed trigger (software or hardware).
// OFF                      Conversion disabled. ENC change from ON to OFF
//                          will abort single or repeat sequence on a
//                          MEMCTLx boundary. The current conversion will
//                          finish and result stored in corresponding
//                          MEMRESx.
#define ADC_CTL0_ENC                                                0x00000001U
#define ADC_CTL0_ENC_M                                              0x00000001U
#define ADC_CTL0_ENC_S                                                       0U
#define ADC_CTL0_ENC_ON                                             0x00000001U
#define ADC_CTL0_ENC_OFF                                            0x00000000U

//*****************************************************************************
//
// Register: ADC_O_CTL1
//
//*****************************************************************************
// Field:    [20] SAMPMODE
//
// Sample mode. This bit selects the source of the sampling signal.
// MANUAL option is not applicable when TRIGSRC is selected as hardware event
// trigger.
// ENUMs:
// MANUAL                   Software trigger is used as sample signal
// AUTO                     Sample timer high phase is used as sample signal
#define ADC_CTL1_SAMPMODE                                           0x00100000U
#define ADC_CTL1_SAMPMODE_M                                         0x00100000U
#define ADC_CTL1_SAMPMODE_S                                                 20U
#define ADC_CTL1_SAMPMODE_MANUAL                                    0x00100000U
#define ADC_CTL1_SAMPMODE_AUTO                                      0x00000000U

// Field: [17:16] CONSEQ
//
// Conversion sequence mode
// ENUMs:
// REPEATSEQUENCE           ADC channel sequence pointed by STARTADD and
//                          ENDADD will be converted repeatedly
// REPEATSINGLE             ADC channel in MEMCTLx pointed by STARTADD will be
//                          converted repeatedly
// SEQUENCE                 ADC channel sequence pointed by STARTADD and
//                          ENDADD will be converted once
// SINGLE                   ADC channel in MEMCTLx pointed by STARTADD will be
//                          converted once
#define ADC_CTL1_CONSEQ_W                                                    2U
#define ADC_CTL1_CONSEQ_M                                           0x00030000U
#define ADC_CTL1_CONSEQ_S                                                   16U
#define ADC_CTL1_CONSEQ_REPEATSEQUENCE                              0x00030000U
#define ADC_CTL1_CONSEQ_REPEATSINGLE                                0x00020000U
#define ADC_CTL1_CONSEQ_SEQUENCE                                    0x00010000U
#define ADC_CTL1_CONSEQ_SINGLE                                      0x00000000U

// Field:     [8] SC
//
// Start of conversion
// ENUMs:
// START                    When SAMPMODE is set to MANUAL, setting this bit
//                          will start the sample phase. Sample phase will
//                          last as long as this bit is set.
//                          When SAMPMODE is set to
//                          AUTO, setting this bit will trigger the timer
//                          based sample time.
// STOP                     When SAMPMODE is set to MANUAL, clearing this bit
//                          will end the sample phase and the conversion
//                          phase will start.
//                          When SAMPMODE is set to
//                          AUTO, writing 0 has no effect.
#define ADC_CTL1_SC                                                 0x00000100U
#define ADC_CTL1_SC_M                                               0x00000100U
#define ADC_CTL1_SC_S                                                        8U
#define ADC_CTL1_SC_START                                           0x00000100U
#define ADC_CTL1_SC_STOP                                            0x00000000U

// Field:     [0] TRIGSRC
//
// Sample trigger source
// ENUMs:
// EVENT                    Hardware event trigger
// SOFTWARE                 Software trigger
#define ADC_CTL1_TRIGSRC                                            0x00000001U
#define ADC_CTL1_TRIGSRC_M                                          0x00000001U
#define ADC_CTL1_TRIGSRC_S                                                   0U
#define ADC_CTL1_TRIGSRC_EVENT                                      0x00000001U
#define ADC_CTL1_TRIGSRC_SOFTWARE                                   0x00000000U

//*****************************************************************************
//
// Register: ADC_O_CTL2
//
//*****************************************************************************
// Field: [28:24] ENDADD
//
// Sequence end address. These bits select which MEMCTLx is the last one for
// the sequence mode.
// The value of ENDADD is 0x00 to 0x03 corresponding to MEMRES0 to MEMRES3.
// ENUMs:
// ADDR_03                  MEMCTL3 is selected as end address of sequence.
// ADDR_02                  MEMCTL2 is selected as end address of sequence.
// ADDR_01                  MEMCTL1 is selected as end address of sequence.
// ADDR_00                  MEMCTL0 is selected as end address of sequence.
#define ADC_CTL2_ENDADD_W                                                    5U
#define ADC_CTL2_ENDADD_M                                           0x1F000000U
#define ADC_CTL2_ENDADD_S                                                   24U
#define ADC_CTL2_ENDADD_ADDR_03                                     0x03000000U
#define ADC_CTL2_ENDADD_ADDR_02                                     0x02000000U
#define ADC_CTL2_ENDADD_ADDR_01                                     0x01000000U
#define ADC_CTL2_ENDADD_ADDR_00                                     0x00000000U

// Field: [20:16] STARTADD
//
// Sequencer start address. These bits select which MEMCTLx is used for single
// conversion or as first MEMCTL for sequence mode.
// The value of STARTADD is 0x00 to 0x17, corresponding to MEMRES0 to MEMRES23.
// ENUMs:
// ADDR_03                  MEMCTL3 is selected as start address of a sequence
//                          or for a single conversion.
// ADDR_02                  MEMCTL2 is selected as start address of a sequence
//                          or for a single conversion.
// ADDR_01                  MEMCTL1 is selected as start address of a sequence
//                          or for a single conversion.
// ADDR_00                  MEMCTL0 is selected as start address of a sequence
//                          or for a single conversion.
#define ADC_CTL2_STARTADD_W                                                  5U
#define ADC_CTL2_STARTADD_M                                         0x001F0000U
#define ADC_CTL2_STARTADD_S                                                 16U
#define ADC_CTL2_STARTADD_ADDR_03                                   0x00030000U
#define ADC_CTL2_STARTADD_ADDR_02                                   0x00020000U
#define ADC_CTL2_STARTADD_ADDR_01                                   0x00010000U
#define ADC_CTL2_STARTADD_ADDR_00                                   0x00000000U

// Field:    [10] FIFOEN
//
// Enable FIFO based operation
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_CTL2_FIFOEN                                             0x00000400U
#define ADC_CTL2_FIFOEN_M                                           0x00000400U
#define ADC_CTL2_FIFOEN_S                                                   10U
#define ADC_CTL2_FIFOEN_EN                                          0x00000400U
#define ADC_CTL2_FIFOEN_DIS                                         0x00000000U

// Field:     [8] DMAEN
//
// Enable DMA trigger for data transfer.
// Note: DMAEN bit is cleared by hardware based on DMA done signal at the end
// of data transfer. Software has to re-enable DMAEN bit for ADC to generate
// DMA triggers.
// ENUMs:
// EN                       DMA trigger enabled
// DIS                      DMA trigger not enabled
#define ADC_CTL2_DMAEN                                              0x00000100U
#define ADC_CTL2_DMAEN_M                                            0x00000100U
#define ADC_CTL2_DMAEN_S                                                     8U
#define ADC_CTL2_DMAEN_EN                                           0x00000100U
#define ADC_CTL2_DMAEN_DIS                                          0x00000000U

// Field:   [2:1] RES
//
// Resolution. These bits define the resolutoin of ADC conversion result.
// Note : A value of 3 defaults to 12-bits resolution.
// ENUMs:
// BIT_8                    8-bits resolution
// BIT_10                   10-bits resolution
// BIT_12                   12-bits resolution
#define ADC_CTL2_RES_W                                                       2U
#define ADC_CTL2_RES_M                                              0x00000006U
#define ADC_CTL2_RES_S                                                       1U
#define ADC_CTL2_RES_BIT_8                                          0x00000004U
#define ADC_CTL2_RES_BIT_10                                         0x00000002U
#define ADC_CTL2_RES_BIT_12                                         0x00000000U

// Field:     [0] DF
//
// Data read-back format. Data is always stored in binary unsigned format.
// ENUMs:
// SIGNED                   Digital result reads Signed Binary. (2s
//                          complement), left aligned.
// UNSIGNED                 Digital result reads as Binary Unsigned.
#define ADC_CTL2_DF                                                 0x00000001U
#define ADC_CTL2_DF_M                                               0x00000001U
#define ADC_CTL2_DF_S                                                        0U
#define ADC_CTL2_DF_SIGNED                                          0x00000001U
#define ADC_CTL2_DF_UNSIGNED                                        0x00000000U

//*****************************************************************************
//
// Register: ADC_O_CTL3
//
//*****************************************************************************
// Field: [13:12] ASCVRSEL
//
// Selects voltage reference for ASC operation. AREF- must be connected to
// on-board ground when external reference option is selected.
// Note: Writing value 0x3 defaults to INTREF.
// ENUMs:
// INTREF                   Internal reference
// EXTREF                   External reference from AREF+/AREF- pins
// VDDS                     VDDS reference
#define ADC_CTL3_ASCVRSEL_W                                                  2U
#define ADC_CTL3_ASCVRSEL_M                                         0x00003000U
#define ADC_CTL3_ASCVRSEL_S                                                 12U
#define ADC_CTL3_ASCVRSEL_INTREF                                    0x00002000U
#define ADC_CTL3_ASCVRSEL_EXTREF                                    0x00001000U
#define ADC_CTL3_ASCVRSEL_VDDS                                      0x00000000U

// Field:     [8] ASCSTIME
//
// ASC sample time compare value select. This is used to select between SCOMP0
// and SCOMP1 registers for ASC operation.
// ENUMs:
// SEL_SCOMP1               Select SCOMP1
// SEL_SCOMP0               Select SCOMP0
#define ADC_CTL3_ASCSTIME                                           0x00000100U
#define ADC_CTL3_ASCSTIME_M                                         0x00000100U
#define ADC_CTL3_ASCSTIME_S                                                  8U
#define ADC_CTL3_ASCSTIME_SEL_SCOMP1                                0x00000100U
#define ADC_CTL3_ASCSTIME_SEL_SCOMP0                                0x00000000U

// Field:   [4:0] ASCCHSEL
//
// ASC channel select
// ENUMs:
// CHAN_15                  Selects channel 15
// CHAN_14                  Selects channel 14
// CHAN_13                  Selects channel 13
// CHAN_12                  Selects channel 12
// CHAN_11                  Selects channel 11
// CHAN_10                  Selects channel 10
// CHAN_9                   Selects channel 9
// CHAN_8                   Selects channel 8
// CHAN_7                   Selects channel 7
// CHAN_6                   Selects channel 6
// CHAN_5                   Selects channel 5
// CHAN_4                   Selects channel 4
// CHAN_3                   Selects channel 3
// CHAN_2                   Selects channel 2
// CHAN_1                   Selects channel 1
// CHAN_0                   Selects channel 0
#define ADC_CTL3_ASCCHSEL_W                                                  5U
#define ADC_CTL3_ASCCHSEL_M                                         0x0000001FU
#define ADC_CTL3_ASCCHSEL_S                                                  0U
#define ADC_CTL3_ASCCHSEL_CHAN_15                                   0x0000000FU
#define ADC_CTL3_ASCCHSEL_CHAN_14                                   0x0000000EU
#define ADC_CTL3_ASCCHSEL_CHAN_13                                   0x0000000DU
#define ADC_CTL3_ASCCHSEL_CHAN_12                                   0x0000000CU
#define ADC_CTL3_ASCCHSEL_CHAN_11                                   0x0000000BU
#define ADC_CTL3_ASCCHSEL_CHAN_10                                   0x0000000AU
#define ADC_CTL3_ASCCHSEL_CHAN_9                                    0x00000009U
#define ADC_CTL3_ASCCHSEL_CHAN_8                                    0x00000008U
#define ADC_CTL3_ASCCHSEL_CHAN_7                                    0x00000007U
#define ADC_CTL3_ASCCHSEL_CHAN_6                                    0x00000006U
#define ADC_CTL3_ASCCHSEL_CHAN_5                                    0x00000005U
#define ADC_CTL3_ASCCHSEL_CHAN_4                                    0x00000004U
#define ADC_CTL3_ASCCHSEL_CHAN_3                                    0x00000003U
#define ADC_CTL3_ASCCHSEL_CHAN_2                                    0x00000002U
#define ADC_CTL3_ASCCHSEL_CHAN_1                                    0x00000001U
#define ADC_CTL3_ASCCHSEL_CHAN_0                                    0x00000000U

//*****************************************************************************
//
// Register: ADC_O_SCOMP0
//
//*****************************************************************************
// Field:   [9:0] VAL
//
// Specifies the number of sample clocks.
// When VAL = 0 or 1, number of sample clocks = Sample clock divide value.
// When VAL > 1, number of sample clocks = VAL x Sample clock divide value.
// Note: Sample clock divide value is not the value written to SCLKDIV but the
// actual divide value (SCLKDIV = 2 implies divide value is 4).
// Example: VAL = 4, SCLKDIV = 3 implies 32 sample clock cycles.
#define ADC_SCOMP0_VAL_W                                                    10U
#define ADC_SCOMP0_VAL_M                                            0x000003FFU
#define ADC_SCOMP0_VAL_S                                                     0U

//*****************************************************************************
//
// Register: ADC_O_SCOMP1
//
//*****************************************************************************
// Field:   [9:0] VAL
//
// Specifies the number of sample clocks.
// When VAL = 0 or 1, number of sample clocks = Sample clock divide value.
// When VAL > 1, number of sample clocks = VAL x Sample clock divide value.
// Note: Sample clock divide value is not the value written to SCLKDIV but the
// actual divide value (SCLKDIV = 2 implies divide value is 4).
// Example: VAL = 4, SCLKDIV = 3 implies 32 sample clock cycles.
#define ADC_SCOMP1_VAL_W                                                    10U
#define ADC_SCOMP1_VAL_M                                            0x000003FFU
#define ADC_SCOMP1_VAL_S                                                     0U

//*****************************************************************************
//
// Register: ADC_O_REFCFG
//
//*****************************************************************************
// Field:   [4:3] IBPROG
//
// Configures reference buffer bias current output value
// ENUMs:
// VAL3                     0.67uA
// VAL2
// VAL1                     0.5uA
// VAL0
#define ADC_REFCFG_IBPROG_W                                                  2U
#define ADC_REFCFG_IBPROG_M                                         0x00000018U
#define ADC_REFCFG_IBPROG_S                                                  3U
#define ADC_REFCFG_IBPROG_VAL3                                      0x00000018U
#define ADC_REFCFG_IBPROG_VAL2                                      0x00000010U
#define ADC_REFCFG_IBPROG_VAL1                                      0x00000008U
#define ADC_REFCFG_IBPROG_VAL0                                      0x00000000U

// Field:     [2] SPARE
//
// Spare bit
#define ADC_REFCFG_SPARE                                            0x00000004U
#define ADC_REFCFG_SPARE_M                                          0x00000004U
#define ADC_REFCFG_SPARE_S                                                   2U

// Field:     [1] REFVSEL
//
// Configures reference buffer output voltage
// ENUMs:
// V1P4                     REFBUF generates 1.4V output
// V2P5                     REFBUF generates 2.5V output
#define ADC_REFCFG_REFVSEL                                          0x00000002U
#define ADC_REFCFG_REFVSEL_M                                        0x00000002U
#define ADC_REFCFG_REFVSEL_S                                                 1U
#define ADC_REFCFG_REFVSEL_V1P4                                     0x00000002U
#define ADC_REFCFG_REFVSEL_V2P5                                     0x00000000U

// Field:     [0] REFEN
//
// Reference buffer enable
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_REFCFG_REFEN                                            0x00000001U
#define ADC_REFCFG_REFEN_M                                          0x00000001U
#define ADC_REFCFG_REFEN_S                                                   0U
#define ADC_REFCFG_REFEN_EN                                         0x00000001U
#define ADC_REFCFG_REFEN_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: ADC_O_WCLOW
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary format has to be used.
// The value based on the resolution has to be right aligned with the MSB on
// the left.
// For 10-bits and 8-bits resolution, unused bits have to be 0s.
//
// If DF = 1, 2s-complement format has to be used.
// The value based on the resolution has to be left aligned with the LSB on the
// right.
// For 10-bits and 8-bits resolution, unused bits have to be 0s.
#define ADC_WCLOW_DATA_W                                                    16U
#define ADC_WCLOW_DATA_M                                            0x0000FFFFU
#define ADC_WCLOW_DATA_S                                                     0U

//*****************************************************************************
//
// Register: ADC_O_WCHIGH
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary format has to be used.
// The threshold value has to be right aligned, with the MSB on the left.
// For 10-bits and 8-bits resolution, unused bit have to be 0s.
//
// If DF = 1, 2s-complement format has to be used.
// The value based on the resolution has to be left aligned with the LSB on the
// right.
// For 10-bits and 8-bits resolution, unused bit have to be 0s.
#define ADC_WCHIGH_DATA_W                                                   16U
#define ADC_WCHIGH_DATA_M                                           0x0000FFFFU
#define ADC_WCHIGH_DATA_S                                                    0U

//*****************************************************************************
//
// Register: ADC_O_FIFODATA
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// Read from this data field returns the ADC sample from FIFO.
#define ADC_FIFODATA_DATA_W                                                 32U
#define ADC_FIFODATA_DATA_M                                         0xFFFFFFFFU
#define ADC_FIFODATA_DATA_S                                                  0U

//*****************************************************************************
//
// Register: ADC_O_ASCRES
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// Result of ADC ad-hoc single conversion.
// If DF = 0, unsigned binary:
// The conversion result is right aligned. In 10 and 8 bit modes, the unused
// MSB bits are forced to 0.
// If DF = 1, 2s-complement format:
// The conversion result is left aligned. In 10 and 8 bit modes, the unused LSB
// bits are forced to 0.
// The data is stored in the right-justified format and is converted to the
// left-justified 2s-complement format during read back.
#define ADC_ASCRES_DATA_W                                                   16U
#define ADC_ASCRES_DATA_M                                           0x0000FFFFU
#define ADC_ASCRES_DATA_S                                                    0U

//*****************************************************************************
//
// Register: ADC_O_MEMCTL0
//
//*****************************************************************************
// Field:    [28] WINCOMP
//
// Enable window comparator.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_MEMCTL0_WINCOMP                                         0x10000000U
#define ADC_MEMCTL0_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL0_WINCOMP_S                                               28U
#define ADC_MEMCTL0_WINCOMP_EN                                      0x10000000U
#define ADC_MEMCTL0_WINCOMP_DIS                                     0x00000000U

// Field:    [24] TRG
//
// Trigger policy. Indicates if a trigger will be needed to step to the next
// MEMCTL in the sequence or to perform next conversion in the case of repeat
// single channel conversions.
// ENUMs:
// TRIGGER_NEXT             Next conversion requires a trigger
// AUTO_NEXT                Next conversion is automatic
#define ADC_MEMCTL0_TRG                                             0x01000000U
#define ADC_MEMCTL0_TRG_M                                           0x01000000U
#define ADC_MEMCTL0_TRG_S                                                   24U
#define ADC_MEMCTL0_TRG_TRIGGER_NEXT                                0x01000000U
#define ADC_MEMCTL0_TRG_AUTO_NEXT                                   0x00000000U

// Field:    [12] STIME
//
// Selects the source of sample timer period between SCOMP0 and SCOMP1.
// ENUMs:
// SEL_SCOMP1               Select SCOMP1
// SEL_SCOMP0               Select SCOMP0
#define ADC_MEMCTL0_STIME                                           0x00001000U
#define ADC_MEMCTL0_STIME_M                                         0x00001000U
#define ADC_MEMCTL0_STIME_S                                                 12U
#define ADC_MEMCTL0_STIME_SEL_SCOMP1                                0x00001000U
#define ADC_MEMCTL0_STIME_SEL_SCOMP0                                0x00000000U

// Field:   [9:8] VRSEL
//
// Voltage reference selection. AREF- must be connected to on-board ground when
// external reference option is selected.
// Note: Writing value 0x3 defaults to INTREF.
// ENUMs:
// INTREF                   Internal reference
// EXTREF                   External reference from AREF+/AREF- pins
// VDDS                     VDDS reference
#define ADC_MEMCTL0_VRSEL_W                                                  2U
#define ADC_MEMCTL0_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL0_VRSEL_S                                                  8U
#define ADC_MEMCTL0_VRSEL_INTREF                                    0x00000200U
#define ADC_MEMCTL0_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL0_VRSEL_VDDS                                      0x00000000U

// Field:   [4:0] CHANSEL
//
// Input channel select.
// ENUMs:
// CHAN_15                  Selects channel 15
// CHAN_14                  Selects channel 14
// CHAN_13                  Selects channel 13
// CHAN_12                  Selects channel 12
// CHAN_11                  Selects channel 11
// CHAN_10                  Selects channel 10
// CHAN_9                   Selects channel 9
// CHAN_8                   Selects channel 8
// CHAN_7                   Selects channel 7
// CHAN_6                   Selects channel 6
// CHAN_5                   Selects channel 5
// CHAN_4                   Selects channel 4
// CHAN_3                   Selects channel 3
// CHAN_2                   Selects channel 2
// CHAN_1                   Selects channel 1
// CHAN_0                   Selects channel 0
#define ADC_MEMCTL0_CHANSEL_W                                                5U
#define ADC_MEMCTL0_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL0_CHANSEL_S                                                0U
#define ADC_MEMCTL0_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL0_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL0_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL0_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL0_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL0_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL0_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL0_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL0_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL0_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL0_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL0_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL0_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL0_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL0_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL0_CHANSEL_CHAN_0                                  0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MEMCTL1
//
//*****************************************************************************
// Field:    [28] WINCOMP
//
// Enable window comparator.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_MEMCTL1_WINCOMP                                         0x10000000U
#define ADC_MEMCTL1_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL1_WINCOMP_S                                               28U
#define ADC_MEMCTL1_WINCOMP_EN                                      0x10000000U
#define ADC_MEMCTL1_WINCOMP_DIS                                     0x00000000U

// Field:    [24] TRG
//
// Trigger policy. Indicates if a trigger will be needed to step to the next
// MEMCTL in the sequence or to perform next conversion in the case of repeat
// single channel conversions.
// ENUMs:
// TRIGGER_NEXT             Next conversion requires a trigger
// AUTO_NEXT                Next conversion is automatic
#define ADC_MEMCTL1_TRG                                             0x01000000U
#define ADC_MEMCTL1_TRG_M                                           0x01000000U
#define ADC_MEMCTL1_TRG_S                                                   24U
#define ADC_MEMCTL1_TRG_TRIGGER_NEXT                                0x01000000U
#define ADC_MEMCTL1_TRG_AUTO_NEXT                                   0x00000000U

// Field:    [12] STIME
//
// Selects the source of sample timer period between SCOMP0 and SCOMP1.
// ENUMs:
// SEL_SCOMP1               Select SCOMP1
// SEL_SCOMP0               Select SCOMP0
#define ADC_MEMCTL1_STIME                                           0x00001000U
#define ADC_MEMCTL1_STIME_M                                         0x00001000U
#define ADC_MEMCTL1_STIME_S                                                 12U
#define ADC_MEMCTL1_STIME_SEL_SCOMP1                                0x00001000U
#define ADC_MEMCTL1_STIME_SEL_SCOMP0                                0x00000000U

// Field:   [9:8] VRSEL
//
// Voltage reference selection. AREF- must be connected to on-board ground when
// external reference option is selected.
// Note: Writing value 0x3 defaults to INTREF.
// ENUMs:
// INTREF                   Internal reference
// EXTREF                   External reference from AREF+/AREF- pins
// VDDS                     VDDS reference
#define ADC_MEMCTL1_VRSEL_W                                                  2U
#define ADC_MEMCTL1_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL1_VRSEL_S                                                  8U
#define ADC_MEMCTL1_VRSEL_INTREF                                    0x00000200U
#define ADC_MEMCTL1_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL1_VRSEL_VDDS                                      0x00000000U

// Field:   [4:0] CHANSEL
//
// Input channel select.
// ENUMs:
// CHAN_15                  Selects channel 15
// CHAN_14                  Selects channel 14
// CHAN_13                  Selects channel 13
// CHAN_12                  Selects channel 12
// CHAN_11                  Selects channel 11
// CHAN_10                  Selects channel 10
// CHAN_9                   Selects channel 9
// CHAN_8                   Selects channel 8
// CHAN_7                   Selects channel 7
// CHAN_6                   Selects channel 6
// CHAN_5                   Selects channel 5
// CHAN_4                   Selects channel 4
// CHAN_3                   Selects channel 3
// CHAN_2                   Selects channel 2
// CHAN_1                   Selects channel 1
// CHAN_0                   Selects channel 0
#define ADC_MEMCTL1_CHANSEL_W                                                5U
#define ADC_MEMCTL1_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL1_CHANSEL_S                                                0U
#define ADC_MEMCTL1_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL1_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL1_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL1_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL1_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL1_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL1_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL1_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL1_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL1_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL1_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL1_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL1_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL1_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL1_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL1_CHANSEL_CHAN_0                                  0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MEMCTL2
//
//*****************************************************************************
// Field:    [28] WINCOMP
//
// Enable window comparator.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_MEMCTL2_WINCOMP                                         0x10000000U
#define ADC_MEMCTL2_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL2_WINCOMP_S                                               28U
#define ADC_MEMCTL2_WINCOMP_EN                                      0x10000000U
#define ADC_MEMCTL2_WINCOMP_DIS                                     0x00000000U

// Field:    [24] TRG
//
// Trigger policy. Indicates if a trigger will be needed to step to the next
// MEMCTL in the sequence or to perform next conversion in the case of repeat
// single channel conversions.
// ENUMs:
// TRIGGER_NEXT             Next conversion requires a trigger
// AUTO_NEXT                Next conversion is automatic
#define ADC_MEMCTL2_TRG                                             0x01000000U
#define ADC_MEMCTL2_TRG_M                                           0x01000000U
#define ADC_MEMCTL2_TRG_S                                                   24U
#define ADC_MEMCTL2_TRG_TRIGGER_NEXT                                0x01000000U
#define ADC_MEMCTL2_TRG_AUTO_NEXT                                   0x00000000U

// Field:    [12] STIME
//
// Selects the source of sample timer period between SCOMP0 and SCOMP1.
// ENUMs:
// SEL_SCOMP1               Select SCOMP1
// SEL_SCOMP0               Select SCOMP0
#define ADC_MEMCTL2_STIME                                           0x00001000U
#define ADC_MEMCTL2_STIME_M                                         0x00001000U
#define ADC_MEMCTL2_STIME_S                                                 12U
#define ADC_MEMCTL2_STIME_SEL_SCOMP1                                0x00001000U
#define ADC_MEMCTL2_STIME_SEL_SCOMP0                                0x00000000U

// Field:   [9:8] VRSEL
//
// Voltage reference selection. AREF- must be connected to on-board ground when
// external reference option is selected.
// Note: Writing value 0x3 defaults to INTREF.
// ENUMs:
// INTREF                   Internal reference
// EXTREF                   External reference from AREF+/AREF- pins
// VDDS                     VDDS reference
#define ADC_MEMCTL2_VRSEL_W                                                  2U
#define ADC_MEMCTL2_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL2_VRSEL_S                                                  8U
#define ADC_MEMCTL2_VRSEL_INTREF                                    0x00000200U
#define ADC_MEMCTL2_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL2_VRSEL_VDDS                                      0x00000000U

// Field:   [4:0] CHANSEL
//
// Input channel select.
// ENUMs:
// CHAN_15                  Selects channel 15
// CHAN_14                  Selects channel 14
// CHAN_13                  Selects channel 13
// CHAN_12                  Selects channel 12
// CHAN_11                  Selects channel 11
// CHAN_10                  Selects channel 10
// CHAN_9                   Selects channel 9
// CHAN_8                   Selects channel 8
// CHAN_7                   Selects channel 7
// CHAN_6                   Selects channel 6
// CHAN_5                   Selects channel 5
// CHAN_4                   Selects channel 4
// CHAN_3                   Selects channel 3
// CHAN_2                   Selects channel 2
// CHAN_1                   Selects channel 1
// CHAN_0                   Selects channel 0
#define ADC_MEMCTL2_CHANSEL_W                                                5U
#define ADC_MEMCTL2_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL2_CHANSEL_S                                                0U
#define ADC_MEMCTL2_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL2_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL2_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL2_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL2_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL2_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL2_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL2_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL2_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL2_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL2_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL2_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL2_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL2_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL2_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL2_CHANSEL_CHAN_0                                  0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MEMCTL3
//
//*****************************************************************************
// Field:    [28] WINCOMP
//
// Enable window comparator.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define ADC_MEMCTL3_WINCOMP                                         0x10000000U
#define ADC_MEMCTL3_WINCOMP_M                                       0x10000000U
#define ADC_MEMCTL3_WINCOMP_S                                               28U
#define ADC_MEMCTL3_WINCOMP_EN                                      0x10000000U
#define ADC_MEMCTL3_WINCOMP_DIS                                     0x00000000U

// Field:    [24] TRG
//
// Trigger policy. Indicates if a trigger will be needed to step to the next
// MEMCTL in the sequence or to perform next conversion in the case of repeat
// single channel conversions.
// ENUMs:
// TRIGGER_NEXT             Next conversion requires a trigger
// AUTO_NEXT                Next conversion is automatic
#define ADC_MEMCTL3_TRG                                             0x01000000U
#define ADC_MEMCTL3_TRG_M                                           0x01000000U
#define ADC_MEMCTL3_TRG_S                                                   24U
#define ADC_MEMCTL3_TRG_TRIGGER_NEXT                                0x01000000U
#define ADC_MEMCTL3_TRG_AUTO_NEXT                                   0x00000000U

// Field:    [12] STIME
//
// Selects the source of sample timer period between SCOMP0 and SCOMP1.
// ENUMs:
// SEL_SCOMP1               Select SCOMP1
// SEL_SCOMP0               Select SCOMP0
#define ADC_MEMCTL3_STIME                                           0x00001000U
#define ADC_MEMCTL3_STIME_M                                         0x00001000U
#define ADC_MEMCTL3_STIME_S                                                 12U
#define ADC_MEMCTL3_STIME_SEL_SCOMP1                                0x00001000U
#define ADC_MEMCTL3_STIME_SEL_SCOMP0                                0x00000000U

// Field:   [9:8] VRSEL
//
// Voltage reference selection. AREF- must be connected to on-board ground when
// external reference option is selected.
// Note: Writing value 0x3 defaults to INTREF.
// ENUMs:
// INTREF                   Internal reference
// EXTREF                   External reference from AREF+/AREF- pins
// VDDS                     VDDS reference
#define ADC_MEMCTL3_VRSEL_W                                                  2U
#define ADC_MEMCTL3_VRSEL_M                                         0x00000300U
#define ADC_MEMCTL3_VRSEL_S                                                  8U
#define ADC_MEMCTL3_VRSEL_INTREF                                    0x00000200U
#define ADC_MEMCTL3_VRSEL_EXTREF                                    0x00000100U
#define ADC_MEMCTL3_VRSEL_VDDS                                      0x00000000U

// Field:   [4:0] CHANSEL
//
// Input channel select.
// ENUMs:
// CHAN_15                  Selects channel 15
// CHAN_14                  Selects channel 14
// CHAN_13                  Selects channel 13
// CHAN_12                  Selects channel 12
// CHAN_11                  Selects channel 11
// CHAN_10                  Selects channel 10
// CHAN_9                   Selects channel 9
// CHAN_8                   Selects channel 8
// CHAN_7                   Selects channel 7
// CHAN_6                   Selects channel 6
// CHAN_5                   Selects channel 5
// CHAN_4                   Selects channel 4
// CHAN_3                   Selects channel 3
// CHAN_2                   Selects channel 2
// CHAN_1                   Selects channel 1
// CHAN_0                   Selects channel 0
#define ADC_MEMCTL3_CHANSEL_W                                                5U
#define ADC_MEMCTL3_CHANSEL_M                                       0x0000001FU
#define ADC_MEMCTL3_CHANSEL_S                                                0U
#define ADC_MEMCTL3_CHANSEL_CHAN_15                                 0x0000000FU
#define ADC_MEMCTL3_CHANSEL_CHAN_14                                 0x0000000EU
#define ADC_MEMCTL3_CHANSEL_CHAN_13                                 0x0000000DU
#define ADC_MEMCTL3_CHANSEL_CHAN_12                                 0x0000000CU
#define ADC_MEMCTL3_CHANSEL_CHAN_11                                 0x0000000BU
#define ADC_MEMCTL3_CHANSEL_CHAN_10                                 0x0000000AU
#define ADC_MEMCTL3_CHANSEL_CHAN_9                                  0x00000009U
#define ADC_MEMCTL3_CHANSEL_CHAN_8                                  0x00000008U
#define ADC_MEMCTL3_CHANSEL_CHAN_7                                  0x00000007U
#define ADC_MEMCTL3_CHANSEL_CHAN_6                                  0x00000006U
#define ADC_MEMCTL3_CHANSEL_CHAN_5                                  0x00000005U
#define ADC_MEMCTL3_CHANSEL_CHAN_4                                  0x00000004U
#define ADC_MEMCTL3_CHANSEL_CHAN_3                                  0x00000003U
#define ADC_MEMCTL3_CHANSEL_CHAN_2                                  0x00000002U
#define ADC_MEMCTL3_CHANSEL_CHAN_1                                  0x00000001U
#define ADC_MEMCTL3_CHANSEL_CHAN_0                                  0x00000000U

//*****************************************************************************
//
// Register: ADC_O_MEMRES0
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary:
// The conversion results are right aligned. In 10 and 8 bit modes, the unused
// MSB bits are forced to 0.
// If DF = 1, 2s-complement format:
// The conversion results are left aligned. In 10 and 8 bit modes, the unused
// LSB bits are forced to 0.
// The data is stored in the right-justified format and is converted to the
// left-justified 2s-complement format during read back.
//
#define ADC_MEMRES0_DATA_W                                                  16U
#define ADC_MEMRES0_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES0_DATA_S                                                   0U

//*****************************************************************************
//
// Register: ADC_O_MEMRES1
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary:
// The conversion results are right aligned. In 10 and 8 bit modes, the unused
// MSB bits are forced to 0.
// If DF = 1, 2s-complement format:
// The conversion results are left aligned. In 10 and 8 bit modes, the unused
// LSB bits are forced to 0.
// The data is stored in the right-justified format and is converted to the
// left-justified 2s-complement format during read back.
//
#define ADC_MEMRES1_DATA_W                                                  16U
#define ADC_MEMRES1_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES1_DATA_S                                                   0U

//*****************************************************************************
//
// Register: ADC_O_MEMRES2
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary:
// The conversion results are right aligned. In 10 and 8 bit modes, the unused
// MSB bits are forced to 0.
// If DF = 1, 2s-complement format:
// The conversion results are left aligned. In 10 and 8 bit modes, the unused
// LSB bits are forced to 0.
// The data is stored in the right-justified format and is converted to the
// left-justified 2s-complement format during read back.
//
#define ADC_MEMRES2_DATA_W                                                  16U
#define ADC_MEMRES2_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES2_DATA_S                                                   0U

//*****************************************************************************
//
// Register: ADC_O_MEMRES3
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// If DF = 0, unsigned binary:
// The conversion results are right aligned. In 10 and 8 bit modes, the unused
// MSB bits are forced to 0.
// If DF = 1, 2s-complement format:
// The conversion results are left aligned. In 10 and 8 bit modes, the unused
// LSB bits are forced to 0.
// The data is stored in the right-justified format and is converted to the
// left-justified 2s-complement format during read back.
//
#define ADC_MEMRES3_DATA_W                                                  16U
#define ADC_MEMRES3_DATA_M                                          0x0000FFFFU
#define ADC_MEMRES3_DATA_S                                                   0U

//*****************************************************************************
//
// Register: ADC_O_STA
//
//*****************************************************************************
// Field:     [2] ASCACT
//
// ASC active
// ENUMs:
// ACTIVE                   ASC active
// IDLE                     Idle or done
#define ADC_STA_ASCACT                                              0x00000004U
#define ADC_STA_ASCACT_M                                            0x00000004U
#define ADC_STA_ASCACT_S                                                     2U
#define ADC_STA_ASCACT_ACTIVE                                       0x00000004U
#define ADC_STA_ASCACT_IDLE                                         0x00000000U

// Field:     [0] BUSY
//
// Busy. This bit indicates that an active ADC sample or conversion operation
// is in progress.
// ENUMs:
// ACTIVE                   ADC sampling or conversion is in progress.
// IDLE                     No ADC sampling or conversion in progress.
#define ADC_STA_BUSY                                                0x00000001U
#define ADC_STA_BUSY_M                                              0x00000001U
#define ADC_STA_BUSY_S                                                       0U
#define ADC_STA_BUSY_ACTIVE                                         0x00000001U
#define ADC_STA_BUSY_IDLE                                           0x00000000U

//*****************************************************************************
//
// Register: ADC_O_TEST0
//
//*****************************************************************************
// Field:    [30] ATEST0_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define ADC_TEST0_ATEST0_EN                                         0x40000000U
#define ADC_TEST0_ATEST0_EN_M                                       0x40000000U
#define ADC_TEST0_ATEST0_EN_S                                               30U
#define ADC_TEST0_ATEST0_EN_EN                                      0x40000000U
#define ADC_TEST0_ATEST0_EN_DIS                                     0x00000000U

// Field:    [29] ATEST1_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define ADC_TEST0_ATEST1_EN                                         0x20000000U
#define ADC_TEST0_ATEST1_EN_M                                       0x20000000U
#define ADC_TEST0_ATEST1_EN_S                                               29U
#define ADC_TEST0_ATEST1_EN_EN                                      0x20000000U
#define ADC_TEST0_ATEST1_EN_DIS                                     0x00000000U

// Field:  [12:8] ATEST1_MUXSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL16                    Internal. Only to be used through TI provided API.
// VAL8                     Internal. Only to be used through TI provided API.
// VAL4                     Internal. Only to be used through TI provided API.
// VAL2                     Internal. Only to be used through TI provided API.
// VAL1                     Internal. Only to be used through TI provided API.
#define ADC_TEST0_ATEST1_MUXSEL_W                                            5U
#define ADC_TEST0_ATEST1_MUXSEL_M                                   0x00001F00U
#define ADC_TEST0_ATEST1_MUXSEL_S                                            8U
#define ADC_TEST0_ATEST1_MUXSEL_VAL16                               0x00001000U
#define ADC_TEST0_ATEST1_MUXSEL_VAL8                                0x00000800U
#define ADC_TEST0_ATEST1_MUXSEL_VAL4                                0x00000400U
#define ADC_TEST0_ATEST1_MUXSEL_VAL2                                0x00000200U
#define ADC_TEST0_ATEST1_MUXSEL_VAL1                                0x00000100U

// Field:   [4:0] ATEST0_MUXSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL16                    Internal. Only to be used through TI provided API.
// VAL8                     Internal. Only to be used through TI provided API.
// VAL4                     Internal. Only to be used through TI provided API.
// VAL2                     Internal. Only to be used through TI provided API.
// VAL1                     Internal. Only to be used through TI provided API.
#define ADC_TEST0_ATEST0_MUXSEL_W                                            5U
#define ADC_TEST0_ATEST0_MUXSEL_M                                   0x0000001FU
#define ADC_TEST0_ATEST0_MUXSEL_S                                            0U
#define ADC_TEST0_ATEST0_MUXSEL_VAL16                               0x00000010U
#define ADC_TEST0_ATEST0_MUXSEL_VAL8                                0x00000008U
#define ADC_TEST0_ATEST0_MUXSEL_VAL4                                0x00000004U
#define ADC_TEST0_ATEST0_MUXSEL_VAL2                                0x00000002U
#define ADC_TEST0_ATEST0_MUXSEL_VAL1                                0x00000001U

//*****************************************************************************
//
// Register: ADC_O_TEST2
//
//*****************************************************************************
// Field:    [31] CDAC_OVST_EN
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST2_CDAC_OVST_EN                                      0x80000000U
#define ADC_TEST2_CDAC_OVST_EN_M                                    0x80000000U
#define ADC_TEST2_CDAC_OVST_EN_S                                            31U

// Field:    [24] LATCH_TRIM_EN
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST2_LATCH_TRIM_EN                                     0x01000000U
#define ADC_TEST2_LATCH_TRIM_EN_M                                   0x01000000U
#define ADC_TEST2_LATCH_TRIM_EN_S                                           24U

// Field:    [20] COMP_GAIN_TRIM
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST2_COMP_GAIN_TRIM                                    0x00100000U
#define ADC_TEST2_COMP_GAIN_TRIM_M                                  0x00100000U
#define ADC_TEST2_COMP_GAIN_TRIM_S                                          20U

// Field:     [8] MUX_TEST_SEL
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST2_MUX_TEST_SEL                                      0x00000100U
#define ADC_TEST2_MUX_TEST_SEL_M                                    0x00000100U
#define ADC_TEST2_MUX_TEST_SEL_S                                             8U

//*****************************************************************************
//
// Register: ADC_O_TEST3
//
//*****************************************************************************
// Field:  [31:0] CAL_ACUML
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST3_CAL_ACUML_W                                               32U
#define ADC_TEST3_CAL_ACUML_M                                       0xFFFFFFFFU
#define ADC_TEST3_CAL_ACUML_S                                                0U

//*****************************************************************************
//
// Register: ADC_O_TEST4
//
//*****************************************************************************
// Field:    [31] HW_STEP_SEL_DIS
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST4_HW_STEP_SEL_DIS                                   0x80000000U
#define ADC_TEST4_HW_STEP_SEL_DIS_M                                 0x80000000U
#define ADC_TEST4_HW_STEP_SEL_DIS_S                                         31U

// Field:    [24] CAL_MODE_EN
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST4_CAL_MODE_EN                                       0x01000000U
#define ADC_TEST4_CAL_MODE_EN_M                                     0x01000000U
#define ADC_TEST4_CAL_MODE_EN_S                                             24U

// Field: [21:16] CAL_STEP_SEL
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST4_CAL_STEP_SEL_W                                             6U
#define ADC_TEST4_CAL_STEP_SEL_M                                    0x003F0000U
#define ADC_TEST4_CAL_STEP_SEL_S                                            16U

//*****************************************************************************
//
// Register: ADC_O_TEST5
//
//*****************************************************************************
// Field:   [9:0] CAL_CAP_CTL
//
// Internal. Only to be used through TI provided API.
#define ADC_TEST5_CAL_CAP_CTL_W                                             10U
#define ADC_TEST5_CAL_CAP_CTL_M                                     0x000003FFU
#define ADC_TEST5_CAL_CAP_CTL_S                                              0U

//*****************************************************************************
//
// Register: ADC_O_TEST6
//
//*****************************************************************************
// Field:   [3:0] ATESTSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAL8                     Internal. Only to be used through TI provided API.
// VAL4                     Internal. Only to be used through TI provided API.
// VAL2                     Internal. Only to be used through TI provided API.
// VAL1                     Internal. Only to be used through TI provided API.
// VAL0                     Internal. Only to be used through TI provided API.
#define ADC_TEST6_ATESTSEL_W                                                 4U
#define ADC_TEST6_ATESTSEL_M                                        0x0000000FU
#define ADC_TEST6_ATESTSEL_S                                                 0U
#define ADC_TEST6_ATESTSEL_VAL8                                     0x00000008U
#define ADC_TEST6_ATESTSEL_VAL4                                     0x00000004U
#define ADC_TEST6_ATESTSEL_VAL2                                     0x00000002U
#define ADC_TEST6_ATESTSEL_VAL1                                     0x00000001U
#define ADC_TEST6_ATESTSEL_VAL0                                     0x00000000U

//*****************************************************************************
//
// Register: ADC_O_DEBUG1
//
//*****************************************************************************
// Field:  [31:0] CTRL
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG1_CTRL_W                                                   32U
#define ADC_DEBUG1_CTRL_M                                           0xFFFFFFFFU
#define ADC_DEBUG1_CTRL_S                                                    0U

//*****************************************************************************
//
// Register: ADC_O_DEBUG2
//
//*****************************************************************************
// Field: [29:28] VTOI_CTRL
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG2_VTOI_CTRL_W                                               2U
#define ADC_DEBUG2_VTOI_CTRL_M                                      0x30000000U
#define ADC_DEBUG2_VTOI_CTRL_S                                              28U

// Field:    [24] VTOI_TESTMODE_EN
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG2_VTOI_TESTMODE_EN                                 0x01000000U
#define ADC_DEBUG2_VTOI_TESTMODE_EN_M                               0x01000000U
#define ADC_DEBUG2_VTOI_TESTMODE_EN_S                                       24U

//*****************************************************************************
//
// Register: ADC_O_DEBUG3
//
//*****************************************************************************
// Field:     [5] DEC1_DIS
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG3_DEC1_DIS                                         0x00000020U
#define ADC_DEBUG3_DEC1_DIS_M                                       0x00000020U
#define ADC_DEBUG3_DEC1_DIS_S                                                5U

// Field:     [4] DEC0_DIS
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG3_DEC0_DIS                                         0x00000010U
#define ADC_DEBUG3_DEC0_DIS_M                                       0x00000010U
#define ADC_DEBUG3_DEC0_DIS_S                                                4U

// Field:     [0] BOOST_ENZ
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG3_BOOST_ENZ                                        0x00000001U
#define ADC_DEBUG3_BOOST_ENZ_M                                      0x00000001U
#define ADC_DEBUG3_BOOST_ENZ_S                                               0U

//*****************************************************************************
//
// Register: ADC_O_DEBUG4
//
//*****************************************************************************
// Field:  [15:0] ADC_CTRL0
//
// Internal. Only to be used through TI provided API.
#define ADC_DEBUG4_ADC_CTRL0_W                                              16U
#define ADC_DEBUG4_ADC_CTRL0_M                                      0x0000FFFFU
#define ADC_DEBUG4_ADC_CTRL0_S                                               0U


#endif // __ADC__
