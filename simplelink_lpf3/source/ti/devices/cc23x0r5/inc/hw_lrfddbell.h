/******************************************************************************
*  Filename:       hw_lrfddbell_h
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

#ifndef __HW_LRFDDBELL_H__
#define __HW_LRFDDBELL_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDDBELL component
//
//*****************************************************************************
// Description
#define LRFDDBELL_O_DESC                                            0x00000000U

// Clock control
#define LRFDDBELL_O_CLKCTL                                          0x00000004U

// DMA Configuration
#define LRFDDBELL_O_DMACFG                                          0x00000008U

// Systimer Output Event Control Register
#define LRFDDBELL_O_SYSTIMOEV                                       0x0000000CU

// System DMA Trigger
#define LRFDDBELL_O_SYSTDMATRIG                                     0x00000010U

// GPO control
#define LRFDDBELL_O_GPOSEL0                                         0x00000014U

// GPO control
#define LRFDDBELL_O_GPOSEL1                                         0x00000018U

// Interrupt mask
#define LRFDDBELL_O_IMASK0                                          0x00000044U

// Raw interrupt status
#define LRFDDBELL_O_RIS0                                            0x00000048U

// Masked interrupt status
#define LRFDDBELL_O_MIS0                                            0x0000004CU

// Interrupt set
#define LRFDDBELL_O_ISET0                                           0x00000050U

// Interrupt clear
#define LRFDDBELL_O_ICLR0                                           0x00000054U

// Interrupt mask
#define LRFDDBELL_O_IMASK1                                          0x00000084U

// Raw interrupt status
#define LRFDDBELL_O_RIS1                                            0x00000088U

// Masked interrupt status
#define LRFDDBELL_O_MIS1                                            0x0000008CU

// Interrupt set
#define LRFDDBELL_O_ISET1                                           0x00000090U

// Interrupt clear
#define LRFDDBELL_O_ICLR1                                           0x00000094U

// Interrupt mask
#define LRFDDBELL_O_IMASK2                                          0x000000C4U

// Raw interrupt status
#define LRFDDBELL_O_RIS2                                            0x000000C8U

// Masked interrupt status
#define LRFDDBELL_O_MIS2                                            0x000000CCU

// Interrupt set
#define LRFDDBELL_O_ISET2                                           0x000000D0U

// Interrupt clear
#define LRFDDBELL_O_ICLR2                                           0x000000D4U

//*****************************************************************************
//
// Register: LRFDDBELL_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODULEID
//
// Module identifier used to uniquely identify this IP.
#define LRFDDBELL_DESC_MODULEID_W                                           16U
#define LRFDDBELL_DESC_MODULEID_M                                   0xFFFF0000U
#define LRFDDBELL_DESC_MODULEID_S                                           16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
// ENUMs:
// STDIPMMR                 These MMRs begin at offset 64*STDIPOFF from IP
//                          base address
// NO_STDIPMMR              STDIP MMRs do not exist
#define LRFDDBELL_DESC_STDIPOFF_W                                            4U
#define LRFDDBELL_DESC_STDIPOFF_M                                   0x0000F000U
#define LRFDDBELL_DESC_STDIPOFF_S                                           12U
#define LRFDDBELL_DESC_STDIPOFF_STDIPMMR                            0x00001000U
#define LRFDDBELL_DESC_STDIPOFF_NO_STDIPMMR                         0x00000000U

// Field:  [11:8] INSTNUM
//
// IP Instance Number.  If multiple instances of IP exist in the device, this
// field can identify the instance number
#define LRFDDBELL_DESC_INSTNUM_W                                             4U
#define LRFDDBELL_DESC_INSTNUM_M                                    0x00000F00U
#define LRFDDBELL_DESC_INSTNUM_S                                             8U

// Field:   [7:4] MAJREV
//
// Major rev of the IP
#define LRFDDBELL_DESC_MAJREV_W                                              4U
#define LRFDDBELL_DESC_MAJREV_M                                     0x000000F0U
#define LRFDDBELL_DESC_MAJREV_S                                              4U

// Field:   [3:0] MINREV
//
// Minor rev of the IP
#define LRFDDBELL_DESC_MINREV_W                                              4U
#define LRFDDBELL_DESC_MINREV_M                                     0x0000000FU
#define LRFDDBELL_DESC_MINREV_S                                              0U

//*****************************************************************************
//
// Register: LRFDDBELL_O_CLKCTL
//
//*****************************************************************************
// Field:    [13] DEM
//
// Enable the clock to the demodulator. The modem will request this clock
// automatically. This bit is to force the clock to be free running
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_DEM                                        0x00002000U
#define LRFDDBELL_CLKCTL_DEM_M                                      0x00002000U
#define LRFDDBELL_CLKCTL_DEM_S                                              13U
#define LRFDDBELL_CLKCTL_DEM_EN                                     0x00002000U
#define LRFDDBELL_CLKCTL_DEM_DIS                                    0x00000000U

// Field:    [12] MOD
//
// Enable the clock to the modulator. Modem will request this clock
// automatically, this bit is to force the modulator clock to be free running.
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_MOD                                        0x00001000U
#define LRFDDBELL_CLKCTL_MOD_M                                      0x00001000U
#define LRFDDBELL_CLKCTL_MOD_S                                              12U
#define LRFDDBELL_CLKCTL_MOD_EN                                     0x00001000U
#define LRFDDBELL_CLKCTL_MOD_DIS                                    0x00000000U

// Field:    [11] S2RRAM
//
// Enable the clock to the S2R RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_S2RRAM                                     0x00000800U
#define LRFDDBELL_CLKCTL_S2RRAM_M                                   0x00000800U
#define LRFDDBELL_CLKCTL_S2RRAM_S                                           11U
#define LRFDDBELL_CLKCTL_S2RRAM_EN                                  0x00000800U
#define LRFDDBELL_CLKCTL_S2RRAM_DIS                                 0x00000000U

// Field:    [10] BUFRAM
//
// Enable the clock to the BUFRAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_BUFRAM                                     0x00000400U
#define LRFDDBELL_CLKCTL_BUFRAM_M                                   0x00000400U
#define LRFDDBELL_CLKCTL_BUFRAM_S                                           10U
#define LRFDDBELL_CLKCTL_BUFRAM_EN                                  0x00000400U
#define LRFDDBELL_CLKCTL_BUFRAM_DIS                                 0x00000000U

// Field:     [9] DSBRAM
//
// Enable the clock to the DSB RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_DSBRAM                                     0x00000200U
#define LRFDDBELL_CLKCTL_DSBRAM_M                                   0x00000200U
#define LRFDDBELL_CLKCTL_DSBRAM_S                                            9U
#define LRFDDBELL_CLKCTL_DSBRAM_EN                                  0x00000200U
#define LRFDDBELL_CLKCTL_DSBRAM_DIS                                 0x00000000U

// Field:     [8] RFERAM
//
// Enable the clock to the RFE RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_RFERAM                                     0x00000100U
#define LRFDDBELL_CLKCTL_RFERAM_M                                   0x00000100U
#define LRFDDBELL_CLKCTL_RFERAM_S                                            8U
#define LRFDDBELL_CLKCTL_RFERAM_EN                                  0x00000100U
#define LRFDDBELL_CLKCTL_RFERAM_DIS                                 0x00000000U

// Field:     [7] MCERAM
//
// Enable the clock to the MCE RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_MCERAM                                     0x00000080U
#define LRFDDBELL_CLKCTL_MCERAM_M                                   0x00000080U
#define LRFDDBELL_CLKCTL_MCERAM_S                                            7U
#define LRFDDBELL_CLKCTL_MCERAM_EN                                  0x00000080U
#define LRFDDBELL_CLKCTL_MCERAM_DIS                                 0x00000000U

// Field:     [6] PBERAM
//
// Enable the clock to the PBE RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_PBERAM                                     0x00000040U
#define LRFDDBELL_CLKCTL_PBERAM_M                                   0x00000040U
#define LRFDDBELL_CLKCTL_PBERAM_S                                            6U
#define LRFDDBELL_CLKCTL_PBERAM_EN                                  0x00000040U
#define LRFDDBELL_CLKCTL_PBERAM_DIS                                 0x00000000U

// Field:     [5] TRC
//
// Enable the clock to the Tracer
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_TRC                                        0x00000020U
#define LRFDDBELL_CLKCTL_TRC_M                                      0x00000020U
#define LRFDDBELL_CLKCTL_TRC_S                                               5U
#define LRFDDBELL_CLKCTL_TRC_EN                                     0x00000020U
#define LRFDDBELL_CLKCTL_TRC_DIS                                    0x00000000U

// Field:     [4] S2R
//
// Enable the clock to Samples2RAM
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_S2R                                        0x00000010U
#define LRFDDBELL_CLKCTL_S2R_M                                      0x00000010U
#define LRFDDBELL_CLKCTL_S2R_S                                               4U
#define LRFDDBELL_CLKCTL_S2R_EN                                     0x00000010U
#define LRFDDBELL_CLKCTL_S2R_DIS                                    0x00000000U

// Field:     [3] RFE
//
// Enable the clock to the RFE
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_RFE                                        0x00000008U
#define LRFDDBELL_CLKCTL_RFE_M                                      0x00000008U
#define LRFDDBELL_CLKCTL_RFE_S                                               3U
#define LRFDDBELL_CLKCTL_RFE_EN                                     0x00000008U
#define LRFDDBELL_CLKCTL_RFE_DIS                                    0x00000000U

// Field:     [2] MDM
//
// Enable the clock to the Modem
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_MDM                                        0x00000004U
#define LRFDDBELL_CLKCTL_MDM_M                                      0x00000004U
#define LRFDDBELL_CLKCTL_MDM_S                                               2U
#define LRFDDBELL_CLKCTL_MDM_EN                                     0x00000004U
#define LRFDDBELL_CLKCTL_MDM_DIS                                    0x00000000U

// Field:     [1] PBE
//
// Enable the clock to the PBE
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_PBE                                        0x00000002U
#define LRFDDBELL_CLKCTL_PBE_M                                      0x00000002U
#define LRFDDBELL_CLKCTL_PBE_S                                               1U
#define LRFDDBELL_CLKCTL_PBE_EN                                     0x00000002U
#define LRFDDBELL_CLKCTL_PBE_DIS                                    0x00000000U

// Field:     [0] BRIDGE
//
// Clock enable to AHB bridge. The bridge will request it's own clock, this bit
// it to override that feature to have a free running clock.
// ENUMs:
// EN                       Clock is requested
// DIS                      Clock not requested
#define LRFDDBELL_CLKCTL_BRIDGE                                     0x00000001U
#define LRFDDBELL_CLKCTL_BRIDGE_M                                   0x00000001U
#define LRFDDBELL_CLKCTL_BRIDGE_S                                            0U
#define LRFDDBELL_CLKCTL_BRIDGE_EN                                  0x00000001U
#define LRFDDBELL_CLKCTL_BRIDGE_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_DMACFG
//
//*****************************************************************************
// Field:   [2:1] TRIGSRC
//
// Select DMA trigger source
// ENUMs:
// FIFO                     The DMA is triggered from the FIFO. See the FIFO
//                          configration register for what FIFO event will
//                          generate the trigger
// RFEFW                    The DMA is triggered by the MCE FW trigger
// MCEFW                    The DMA is triggered by the MCE FW trigger
// PBEFW                    The DMA is triggered by the PBE FW trigger
#define LRFDDBELL_DMACFG_TRIGSRC_W                                           2U
#define LRFDDBELL_DMACFG_TRIGSRC_M                                  0x00000006U
#define LRFDDBELL_DMACFG_TRIGSRC_S                                           1U
#define LRFDDBELL_DMACFG_TRIGSRC_FIFO                               0x00000006U
#define LRFDDBELL_DMACFG_TRIGSRC_RFEFW                              0x00000004U
#define LRFDDBELL_DMACFG_TRIGSRC_MCEFW                              0x00000002U
#define LRFDDBELL_DMACFG_TRIGSRC_PBEFW                              0x00000000U

// Field:     [0] EN
//
// Enables the DMA interface
// ENUMs:
// ON                       Enable DMA interface. The triggers are able to
//                          give activity on the interface
// OFF                      Disable DMA interface, no activity on interface
#define LRFDDBELL_DMACFG_EN                                         0x00000001U
#define LRFDDBELL_DMACFG_EN_M                                       0x00000001U
#define LRFDDBELL_DMACFG_EN_S                                                0U
#define LRFDDBELL_DMACFG_EN_ON                                      0x00000001U
#define LRFDDBELL_DMACFG_EN_OFF                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_SYSTIMOEV
//
//*****************************************************************************
// Field:  [11:8] SRC2
//
// Select source of systimer output event 2 (capture source)
// ENUMs:
// PBESYSTIM2               PBE FW systimer capture event 2
// PBESYSTIM1               PBE FW systimer capture event 1
// PBESYSTIM0               PBE FW systimer capture event 0
// MDMHW2                   MDM HW event 2
// MDMHW1                   MDM HW event 1
// MDMHW0                   MDM HW event 0
// MCESYSTIM2               MCE FW systimer capture event 2
// MCESYSTIM1               MCE FW systimer capture event 1
// MCESYSTIM0               MCE FW systimer capture event 0
// RFESYSTIM2               RFE FW systimer capture event 2
// RFESYSTIM1               RFE FW systimer capture event 1
// RFESYSTIM0               RFE FW systimer capture event 0
// DIS                      Output not enabled, always 0.
#define LRFDDBELL_SYSTIMOEV_SRC2_W                                           4U
#define LRFDDBELL_SYSTIMOEV_SRC2_M                                  0x00000F00U
#define LRFDDBELL_SYSTIMOEV_SRC2_S                                           8U
#define LRFDDBELL_SYSTIMOEV_SRC2_PBESYSTIM2                         0x00000C00U
#define LRFDDBELL_SYSTIMOEV_SRC2_PBESYSTIM1                         0x00000B00U
#define LRFDDBELL_SYSTIMOEV_SRC2_PBESYSTIM0                         0x00000A00U
#define LRFDDBELL_SYSTIMOEV_SRC2_MDMHW2                             0x00000900U
#define LRFDDBELL_SYSTIMOEV_SRC2_MDMHW1                             0x00000800U
#define LRFDDBELL_SYSTIMOEV_SRC2_MDMHW0                             0x00000700U
#define LRFDDBELL_SYSTIMOEV_SRC2_MCESYSTIM2                         0x00000600U
#define LRFDDBELL_SYSTIMOEV_SRC2_MCESYSTIM1                         0x00000500U
#define LRFDDBELL_SYSTIMOEV_SRC2_MCESYSTIM0                         0x00000400U
#define LRFDDBELL_SYSTIMOEV_SRC2_RFESYSTIM2                         0x00000300U
#define LRFDDBELL_SYSTIMOEV_SRC2_RFESYSTIM1                         0x00000200U
#define LRFDDBELL_SYSTIMOEV_SRC2_RFESYSTIM0                         0x00000100U
#define LRFDDBELL_SYSTIMOEV_SRC2_DIS                                0x00000000U

// Field:   [7:4] SRC1
//
// Select source of systimer output event 1 (capture source)
// ENUMs:
// PBESYSTIM2               PBE FW systimer capture event 2
// PBESYSTIM1               PBE FW systimer capture event 1
// PBESYSTIM0               PBE FW systimer capture event 0
// MDMHW2                   MDM HW event 2
// MDMHW1                   MDM HW event 1
// MDMHW0                   MDM HW event 0
// MCESYSTIM2               MCE FW systimer capture event 2
// MCESYSTIM1               MCE FW systimer capture event 1
// MCESYSTIM0               MCE FW systimer capture event 0
// RFESYSTIM2               RFE FW systimer capture event 2
// RFESYSTIM1               RFE FW systimer capture event 1
// RFESYSTIM0               RFE FW systimer capture event 0
// DIS                      Output not enabled, always 0.
#define LRFDDBELL_SYSTIMOEV_SRC1_W                                           4U
#define LRFDDBELL_SYSTIMOEV_SRC1_M                                  0x000000F0U
#define LRFDDBELL_SYSTIMOEV_SRC1_S                                           4U
#define LRFDDBELL_SYSTIMOEV_SRC1_PBESYSTIM2                         0x000000C0U
#define LRFDDBELL_SYSTIMOEV_SRC1_PBESYSTIM1                         0x000000B0U
#define LRFDDBELL_SYSTIMOEV_SRC1_PBESYSTIM0                         0x000000A0U
#define LRFDDBELL_SYSTIMOEV_SRC1_MDMHW2                             0x00000090U
#define LRFDDBELL_SYSTIMOEV_SRC1_MDMHW1                             0x00000080U
#define LRFDDBELL_SYSTIMOEV_SRC1_MDMHW0                             0x00000070U
#define LRFDDBELL_SYSTIMOEV_SRC1_MCESYSTIM2                         0x00000060U
#define LRFDDBELL_SYSTIMOEV_SRC1_MCESYSTIM1                         0x00000050U
#define LRFDDBELL_SYSTIMOEV_SRC1_MCESYSTIM0                         0x00000040U
#define LRFDDBELL_SYSTIMOEV_SRC1_RFESYSTIM2                         0x00000030U
#define LRFDDBELL_SYSTIMOEV_SRC1_RFESYSTIM1                         0x00000020U
#define LRFDDBELL_SYSTIMOEV_SRC1_RFESYSTIM0                         0x00000010U
#define LRFDDBELL_SYSTIMOEV_SRC1_DIS                                0x00000000U

// Field:   [3:0] SRC0
//
// Select source of systimer output event 0 (capture source)
// ENUMs:
// PBESYSTIM2               PBE FW systimer capture event 2
// PBESYSTIM1               PBE FW systimer capture event 1
// PBESYSTIM0               PBE FW systimer capture event 0
// MDMHW2                   MDM HW event 2
// MDMHW1                   MDM HW event 1
// MDMHW0                   MDM HW event 0
// MCESYSTIM2               MCE FW systimer capture event 2
// MCESYSTIM1               MCE FW systimer capture event 1
// MCESYSTIM0               MCE FW systimer capture event 0
// RFESYSTIM2               RFE FW systimer capture event 2
// RFESYSTIM1               RFE FW systimer capture event 1
// RFESYSTIM0               RFE FW systimer capture event 0
// DIS                      Output not enabled, always 0.
#define LRFDDBELL_SYSTIMOEV_SRC0_W                                           4U
#define LRFDDBELL_SYSTIMOEV_SRC0_M                                  0x0000000FU
#define LRFDDBELL_SYSTIMOEV_SRC0_S                                           0U
#define LRFDDBELL_SYSTIMOEV_SRC0_PBESYSTIM2                         0x0000000CU
#define LRFDDBELL_SYSTIMOEV_SRC0_PBESYSTIM1                         0x0000000BU
#define LRFDDBELL_SYSTIMOEV_SRC0_PBESYSTIM0                         0x0000000AU
#define LRFDDBELL_SYSTIMOEV_SRC0_MDMHW2                             0x00000009U
#define LRFDDBELL_SYSTIMOEV_SRC0_MDMHW1                             0x00000008U
#define LRFDDBELL_SYSTIMOEV_SRC0_MDMHW0                             0x00000007U
#define LRFDDBELL_SYSTIMOEV_SRC0_MCESYSTIM2                         0x00000006U
#define LRFDDBELL_SYSTIMOEV_SRC0_MCESYSTIM1                         0x00000005U
#define LRFDDBELL_SYSTIMOEV_SRC0_MCESYSTIM0                         0x00000004U
#define LRFDDBELL_SYSTIMOEV_SRC0_RFESYSTIM2                         0x00000003U
#define LRFDDBELL_SYSTIMOEV_SRC0_RFESYSTIM1                         0x00000002U
#define LRFDDBELL_SYSTIMOEV_SRC0_RFESYSTIM0                         0x00000001U
#define LRFDDBELL_SYSTIMOEV_SRC0_DIS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_SYSTDMATRIG
//
//*****************************************************************************
// Field:     [3] DMA
//
// Trigger a DMA request from the Radio
// ENUMs:
// TRIG                     DMA request manually triggered
// NOTRIG                   DMA not manually triggered
#define LRFDDBELL_SYSTDMATRIG_DMA                                   0x00000008U
#define LRFDDBELL_SYSTDMATRIG_DMA_M                                 0x00000008U
#define LRFDDBELL_SYSTDMATRIG_DMA_S                                          3U
#define LRFDDBELL_SYSTDMATRIG_DMA_TRIG                              0x00000008U
#define LRFDDBELL_SYSTDMATRIG_DMA_NOTRIG                            0x00000000U

// Field:     [2] SYST2
//
// Trigger a capture event on systimer event 0 from the radio
// ENUMs:
// TRIG                     Capture event triggered
// NOTRIG                   Not capture event triggered
#define LRFDDBELL_SYSTDMATRIG_SYST2                                 0x00000004U
#define LRFDDBELL_SYSTDMATRIG_SYST2_M                               0x00000004U
#define LRFDDBELL_SYSTDMATRIG_SYST2_S                                        2U
#define LRFDDBELL_SYSTDMATRIG_SYST2_TRIG                            0x00000004U
#define LRFDDBELL_SYSTDMATRIG_SYST2_NOTRIG                          0x00000000U

// Field:     [1] SYST1
//
// Trigger a capture event on systimer event 0 from the radio
// ENUMs:
// TRIG                     Capture event triggered
// NOTRIG                   Not capture event triggered
#define LRFDDBELL_SYSTDMATRIG_SYST1                                 0x00000002U
#define LRFDDBELL_SYSTDMATRIG_SYST1_M                               0x00000002U
#define LRFDDBELL_SYSTDMATRIG_SYST1_S                                        1U
#define LRFDDBELL_SYSTDMATRIG_SYST1_TRIG                            0x00000002U
#define LRFDDBELL_SYSTDMATRIG_SYST1_NOTRIG                          0x00000000U

// Field:     [0] SYST0
//
// Trigger a capture event on systimer event 0 from the radio
// ENUMs:
// TRIG                     Capture event triggered
// NOTRIG                   Not capture event triggered
#define LRFDDBELL_SYSTDMATRIG_SYST0                                 0x00000001U
#define LRFDDBELL_SYSTDMATRIG_SYST0_M                               0x00000001U
#define LRFDDBELL_SYSTDMATRIG_SYST0_S                                        0U
#define LRFDDBELL_SYSTDMATRIG_SYST0_TRIG                            0x00000001U
#define LRFDDBELL_SYSTDMATRIG_SYST0_NOTRIG                          0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_GPOSEL0
//
//*****************************************************************************
// Field: [28:24] SRC3
//
// Select source of radio GPO line 3
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 3
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      Output not enabled
#define LRFDDBELL_GPOSEL0_SRC3_W                                             5U
#define LRFDDBELL_GPOSEL0_SRC3_M                                    0x1F000000U
#define LRFDDBELL_GPOSEL0_SRC3_S                                            24U
#define LRFDDBELL_GPOSEL0_SRC3_RFCTRC                               0x19000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO7                              0x18000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO6                              0x17000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO5                              0x16000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO4                              0x15000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO3                              0x14000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO2                              0x13000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO1                              0x12000000U
#define LRFDDBELL_GPOSEL0_SRC3_RFEGPO0                              0x11000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO7                              0x10000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO6                              0x0F000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO5                              0x0E000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO4                              0x0D000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO3                              0x0C000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO2                              0x0B000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO1                              0x0A000000U
#define LRFDDBELL_GPOSEL0_SRC3_MCEGPO0                              0x09000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO7                              0x08000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO6                              0x07000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO5                              0x06000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO4                              0x05000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO3                              0x04000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO2                              0x03000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO1                              0x02000000U
#define LRFDDBELL_GPOSEL0_SRC3_PBEGPO0                              0x01000000U
#define LRFDDBELL_GPOSEL0_SRC3_DIS                                  0x00000000U

// Field: [20:16] SRC2
//
// Select source of radio GPO line 2
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 2
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      Output not enabled
#define LRFDDBELL_GPOSEL0_SRC2_W                                             5U
#define LRFDDBELL_GPOSEL0_SRC2_M                                    0x001F0000U
#define LRFDDBELL_GPOSEL0_SRC2_S                                            16U
#define LRFDDBELL_GPOSEL0_SRC2_RFCTRC                               0x00190000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO7                              0x00180000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO6                              0x00170000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO5                              0x00160000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO4                              0x00150000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO3                              0x00140000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO2                              0x00130000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO1                              0x00120000U
#define LRFDDBELL_GPOSEL0_SRC2_RFEGPO0                              0x00110000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO7                              0x00100000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO6                              0x000F0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO5                              0x000E0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO4                              0x000D0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO3                              0x000C0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO2                              0x000B0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO1                              0x000A0000U
#define LRFDDBELL_GPOSEL0_SRC2_MCEGPO0                              0x00090000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO7                              0x00080000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO6                              0x00070000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO5                              0x00060000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO4                              0x00050000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO3                              0x00040000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO2                              0x00030000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO1                              0x00020000U
#define LRFDDBELL_GPOSEL0_SRC2_PBEGPO0                              0x00010000U
#define LRFDDBELL_GPOSEL0_SRC2_DIS                                  0x00000000U

// Field:  [12:8] SRC1
//
// Select source of radio GPO line 1
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 1
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      Output not enabled
#define LRFDDBELL_GPOSEL0_SRC1_W                                             5U
#define LRFDDBELL_GPOSEL0_SRC1_M                                    0x00001F00U
#define LRFDDBELL_GPOSEL0_SRC1_S                                             8U
#define LRFDDBELL_GPOSEL0_SRC1_RFCTRC                               0x00001900U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO7                              0x00001800U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO6                              0x00001700U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO5                              0x00001600U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO4                              0x00001500U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO3                              0x00001400U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO2                              0x00001300U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO1                              0x00001200U
#define LRFDDBELL_GPOSEL0_SRC1_RFEGPO0                              0x00001100U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO7                              0x00001000U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO6                              0x00000F00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO5                              0x00000E00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO4                              0x00000D00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO3                              0x00000C00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO2                              0x00000B00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO1                              0x00000A00U
#define LRFDDBELL_GPOSEL0_SRC1_MCEGPO0                              0x00000900U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO7                              0x00000800U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO6                              0x00000700U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO5                              0x00000600U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO4                              0x00000500U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO3                              0x00000400U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO2                              0x00000300U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO1                              0x00000200U
#define LRFDDBELL_GPOSEL0_SRC1_PBEGPO0                              0x00000100U
#define LRFDDBELL_GPOSEL0_SRC1_DIS                                  0x00000000U

// Field:   [4:0] SRC0
//
// Select source of radio GPO line 0
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 0
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      Output not enabled
#define LRFDDBELL_GPOSEL0_SRC0_W                                             5U
#define LRFDDBELL_GPOSEL0_SRC0_M                                    0x0000001FU
#define LRFDDBELL_GPOSEL0_SRC0_S                                             0U
#define LRFDDBELL_GPOSEL0_SRC0_RFCTRC                               0x00000019U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO7                              0x00000018U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO6                              0x00000017U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO5                              0x00000016U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO4                              0x00000015U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO3                              0x00000014U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO2                              0x00000013U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO1                              0x00000012U
#define LRFDDBELL_GPOSEL0_SRC0_RFEGPO0                              0x00000011U
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO7                              0x00000010U
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO6                              0x0000000FU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO5                              0x0000000EU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO4                              0x0000000DU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO3                              0x0000000CU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO2                              0x0000000BU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO1                              0x0000000AU
#define LRFDDBELL_GPOSEL0_SRC0_MCEGPO0                              0x00000009U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO7                              0x00000008U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO6                              0x00000007U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO5                              0x00000006U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO4                              0x00000005U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO3                              0x00000004U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO2                              0x00000003U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO1                              0x00000002U
#define LRFDDBELL_GPOSEL0_SRC0_PBEGPO0                              0x00000001U
#define LRFDDBELL_GPOSEL0_SRC0_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_GPOSEL1
//
//*****************************************************************************
// Field: [28:24] SRC7
//
// Select source of radio GPO line 7
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 7
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      No output not enabled
#define LRFDDBELL_GPOSEL1_SRC7_W                                             5U
#define LRFDDBELL_GPOSEL1_SRC7_M                                    0x1F000000U
#define LRFDDBELL_GPOSEL1_SRC7_S                                            24U
#define LRFDDBELL_GPOSEL1_SRC7_RFCTRC                               0x19000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO7                              0x18000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO6                              0x17000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO5                              0x16000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO4                              0x15000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO3                              0x14000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO2                              0x13000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO1                              0x12000000U
#define LRFDDBELL_GPOSEL1_SRC7_RFEGPO0                              0x11000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO7                              0x10000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO6                              0x0F000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO5                              0x0E000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO4                              0x0D000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO3                              0x0C000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO2                              0x0B000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO1                              0x0A000000U
#define LRFDDBELL_GPOSEL1_SRC7_MCEGPO0                              0x09000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO7                              0x08000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO6                              0x07000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO5                              0x06000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO4                              0x05000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO3                              0x04000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO2                              0x03000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO1                              0x02000000U
#define LRFDDBELL_GPOSEL1_SRC7_PBEGPO0                              0x01000000U
#define LRFDDBELL_GPOSEL1_SRC7_DIS                                  0x00000000U

// Field: [20:16] SRC6
//
// Select source of radio GPO line 6
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 6
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Selevt RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      No output not enabled
#define LRFDDBELL_GPOSEL1_SRC6_W                                             5U
#define LRFDDBELL_GPOSEL1_SRC6_M                                    0x001F0000U
#define LRFDDBELL_GPOSEL1_SRC6_S                                            16U
#define LRFDDBELL_GPOSEL1_SRC6_RFCTRC                               0x00190000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO7                              0x00180000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO6                              0x00170000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO5                              0x00160000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO4                              0x00150000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO3                              0x00140000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO2                              0x00130000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO1                              0x00120000U
#define LRFDDBELL_GPOSEL1_SRC6_RFEGPO0                              0x00110000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO7                              0x00100000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO6                              0x000F0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO5                              0x000E0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO4                              0x000D0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO3                              0x000C0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO2                              0x000B0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO1                              0x000A0000U
#define LRFDDBELL_GPOSEL1_SRC6_MCEGPO0                              0x00090000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO7                              0x00080000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO6                              0x00070000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO5                              0x00060000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO4                              0x00050000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO3                              0x00040000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO2                              0x00030000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO1                              0x00020000U
#define LRFDDBELL_GPOSEL1_SRC6_PBEGPO0                              0x00010000U
#define LRFDDBELL_GPOSEL1_SRC6_DIS                                  0x00000000U

// Field:  [12:8] SRC5
//
// Select source of radio GPO line 5
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 5
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      No output not enabled
#define LRFDDBELL_GPOSEL1_SRC5_W                                             5U
#define LRFDDBELL_GPOSEL1_SRC5_M                                    0x00001F00U
#define LRFDDBELL_GPOSEL1_SRC5_S                                             8U
#define LRFDDBELL_GPOSEL1_SRC5_RFCTRC                               0x00001900U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO7                              0x00001800U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO6                              0x00001700U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO5                              0x00001600U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO4                              0x00001500U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO3                              0x00001400U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO2                              0x00001300U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO1                              0x00001200U
#define LRFDDBELL_GPOSEL1_SRC5_RFEGPO0                              0x00001100U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO7                              0x00001000U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO6                              0x00000F00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO5                              0x00000E00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO4                              0x00000D00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO3                              0x00000C00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO2                              0x00000B00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO1                              0x00000A00U
#define LRFDDBELL_GPOSEL1_SRC5_MCEGPO0                              0x00000900U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO7                              0x00000800U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO6                              0x00000700U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO5                              0x00000600U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO4                              0x00000500U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO3                              0x00000400U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO2                              0x00000300U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO1                              0x00000200U
#define LRFDDBELL_GPOSEL1_SRC5_PBEGPO0                              0x00000100U
#define LRFDDBELL_GPOSEL1_SRC5_DIS                                  0x00000000U

// Field:   [4:0] SRC4
//
// Select source of radio GPO line 4
// ENUMs:
// RFCTRC                   Select RFCTRC GPO line 4
// RFEGPO7                  Select RFE GPO line 7
// RFEGPO6                  Select RFE GPO line 6
// RFEGPO5                  Select RFE GPO line 5
// RFEGPO4                  Select RFE GPO line 4
// RFEGPO3                  Select RFE GPO line 3
// RFEGPO2                  Select RFE GPO line 2
// RFEGPO1                  Select RFE GPO line 1
// RFEGPO0                  Select RFE GPO line 0
// MCEGPO7                  Select MCE GPO line 7
// MCEGPO6                  Select MCE GPO line 6
// MCEGPO5                  Select MCE GPO line 5
// MCEGPO4                  Select MCE GPO line 4
// MCEGPO3                  Select MCE GPO line 3
// MCEGPO2                  Select MCE GPO line 2
// MCEGPO1                  Select MCE GPO line 1
// MCEGPO0                  Select MCE GPO line 0
// PBEGPO7                  Select PBE GPO line 7
// PBEGPO6                  Select PBE GPO line 6
// PBEGPO5                  Select PBE GPO line 5
// PBEGPO4                  Select PBE GPO line 4
// PBEGPO3                  Select PBE GPO line 3
// PBEGPO2                  Select PBE GPO line 2
// PBEGPO1                  Select PBE GPO line 1
// PBEGPO0                  Select PBE GPO line 0
// DIS                      No output not enabled
#define LRFDDBELL_GPOSEL1_SRC4_W                                             5U
#define LRFDDBELL_GPOSEL1_SRC4_M                                    0x0000001FU
#define LRFDDBELL_GPOSEL1_SRC4_S                                             0U
#define LRFDDBELL_GPOSEL1_SRC4_RFCTRC                               0x00000019U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO7                              0x00000018U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO6                              0x00000017U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO5                              0x00000016U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO4                              0x00000015U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO3                              0x00000014U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO2                              0x00000013U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO1                              0x00000012U
#define LRFDDBELL_GPOSEL1_SRC4_RFEGPO0                              0x00000011U
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO7                              0x00000010U
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO6                              0x0000000FU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO5                              0x0000000EU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO4                              0x0000000DU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO3                              0x0000000CU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO2                              0x0000000BU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO1                              0x0000000AU
#define LRFDDBELL_GPOSEL1_SRC4_MCEGPO0                              0x00000009U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO7                              0x00000008U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO6                              0x00000007U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO5                              0x00000006U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO4                              0x00000005U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO3                              0x00000004U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO2                              0x00000003U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO1                              0x00000002U
#define LRFDDBELL_GPOSEL1_SRC4_PBEGPO0                              0x00000001U
#define LRFDDBELL_GPOSEL1_SRC4_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_IMASK0
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_SYSTIM2                                    0x80000000U
#define LRFDDBELL_IMASK0_SYSTIM2_M                                  0x80000000U
#define LRFDDBELL_IMASK0_SYSTIM2_S                                          31U
#define LRFDDBELL_IMASK0_SYSTIM2_EN                                 0x80000000U
#define LRFDDBELL_IMASK0_SYSTIM2_DIS                                0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_SYSTIM1                                    0x40000000U
#define LRFDDBELL_IMASK0_SYSTIM1_M                                  0x40000000U
#define LRFDDBELL_IMASK0_SYSTIM1_S                                          30U
#define LRFDDBELL_IMASK0_SYSTIM1_EN                                 0x40000000U
#define LRFDDBELL_IMASK0_SYSTIM1_DIS                                0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_SYSTIM0                                    0x20000000U
#define LRFDDBELL_IMASK0_SYSTIM0_M                                  0x20000000U
#define LRFDDBELL_IMASK0_SYSTIM0_S                                          29U
#define LRFDDBELL_IMASK0_SYSTIM0_EN                                 0x20000000U
#define LRFDDBELL_IMASK0_SYSTIM0_DIS                                0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMDONE                                    0x10000000U
#define LRFDDBELL_IMASK0_MDMDONE_M                                  0x10000000U
#define LRFDDBELL_IMASK0_MDMDONE_S                                          28U
#define LRFDDBELL_IMASK0_MDMDONE_EN                                 0x10000000U
#define LRFDDBELL_IMASK0_MDMDONE_DIS                                0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMIN                                      0x08000000U
#define LRFDDBELL_IMASK0_MDMIN_M                                    0x08000000U
#define LRFDDBELL_IMASK0_MDMIN_S                                            27U
#define LRFDDBELL_IMASK0_MDMIN_EN                                   0x08000000U
#define LRFDDBELL_IMASK0_MDMIN_DIS                                  0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMOUT                                     0x04000000U
#define LRFDDBELL_IMASK0_MDMOUT_M                                   0x04000000U
#define LRFDDBELL_IMASK0_MDMOUT_S                                           26U
#define LRFDDBELL_IMASK0_MDMOUT_EN                                  0x04000000U
#define LRFDDBELL_IMASK0_MDMOUT_DIS                                 0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMSOFT2                                   0x02000000U
#define LRFDDBELL_IMASK0_MDMSOFT2_M                                 0x02000000U
#define LRFDDBELL_IMASK0_MDMSOFT2_S                                         25U
#define LRFDDBELL_IMASK0_MDMSOFT2_EN                                0x02000000U
#define LRFDDBELL_IMASK0_MDMSOFT2_DIS                               0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMSOFT1                                   0x01000000U
#define LRFDDBELL_IMASK0_MDMSOFT1_M                                 0x01000000U
#define LRFDDBELL_IMASK0_MDMSOFT1_S                                         24U
#define LRFDDBELL_IMASK0_MDMSOFT1_EN                                0x01000000U
#define LRFDDBELL_IMASK0_MDMSOFT1_DIS                               0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_MDMSOFT0                                   0x00800000U
#define LRFDDBELL_IMASK0_MDMSOFT0_M                                 0x00800000U
#define LRFDDBELL_IMASK0_MDMSOFT0_S                                         23U
#define LRFDDBELL_IMASK0_MDMSOFT0_EN                                0x00800000U
#define LRFDDBELL_IMASK0_MDMSOFT0_DIS                               0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_RFEDONE                                    0x00400000U
#define LRFDDBELL_IMASK0_RFEDONE_M                                  0x00400000U
#define LRFDDBELL_IMASK0_RFEDONE_S                                          22U
#define LRFDDBELL_IMASK0_RFEDONE_EN                                 0x00400000U
#define LRFDDBELL_IMASK0_RFEDONE_DIS                                0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_RFESOFT1                                   0x00200000U
#define LRFDDBELL_IMASK0_RFESOFT1_M                                 0x00200000U
#define LRFDDBELL_IMASK0_RFESOFT1_S                                         21U
#define LRFDDBELL_IMASK0_RFESOFT1_EN                                0x00200000U
#define LRFDDBELL_IMASK0_RFESOFT1_DIS                               0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_RFESOFT0                                   0x00100000U
#define LRFDDBELL_IMASK0_RFESOFT0_M                                 0x00100000U
#define LRFDDBELL_IMASK0_RFESOFT0_S                                         20U
#define LRFDDBELL_IMASK0_RFESOFT0_EN                                0x00100000U
#define LRFDDBELL_IMASK0_RFESOFT0_DIS                               0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_LOCK                                       0x00080000U
#define LRFDDBELL_IMASK0_LOCK_M                                     0x00080000U
#define LRFDDBELL_IMASK0_LOCK_S                                             19U
#define LRFDDBELL_IMASK0_LOCK_EN                                    0x00080000U
#define LRFDDBELL_IMASK0_LOCK_DIS                                   0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_LOL                                        0x00040000U
#define LRFDDBELL_IMASK0_LOL_M                                      0x00040000U
#define LRFDDBELL_IMASK0_LOL_S                                              18U
#define LRFDDBELL_IMASK0_LOL_EN                                     0x00040000U
#define LRFDDBELL_IMASK0_LOL_DIS                                    0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_TXFIFO                                     0x00020000U
#define LRFDDBELL_IMASK0_TXFIFO_M                                   0x00020000U
#define LRFDDBELL_IMASK0_TXFIFO_S                                           17U
#define LRFDDBELL_IMASK0_TXFIFO_EN                                  0x00020000U
#define LRFDDBELL_IMASK0_TXFIFO_DIS                                 0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_RXFIFO                                     0x00010000U
#define LRFDDBELL_IMASK0_RXFIFO_M                                   0x00010000U
#define LRFDDBELL_IMASK0_RXFIFO_S                                           16U
#define LRFDDBELL_IMASK0_RXFIFO_EN                                  0x00010000U
#define LRFDDBELL_IMASK0_RXFIFO_DIS                                 0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE15                                      0x00008000U
#define LRFDDBELL_IMASK0_PBE15_M                                    0x00008000U
#define LRFDDBELL_IMASK0_PBE15_S                                            15U
#define LRFDDBELL_IMASK0_PBE15_EN                                   0x00008000U
#define LRFDDBELL_IMASK0_PBE15_DIS                                  0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE14                                      0x00004000U
#define LRFDDBELL_IMASK0_PBE14_M                                    0x00004000U
#define LRFDDBELL_IMASK0_PBE14_S                                            14U
#define LRFDDBELL_IMASK0_PBE14_EN                                   0x00004000U
#define LRFDDBELL_IMASK0_PBE14_DIS                                  0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE13                                      0x00002000U
#define LRFDDBELL_IMASK0_PBE13_M                                    0x00002000U
#define LRFDDBELL_IMASK0_PBE13_S                                            13U
#define LRFDDBELL_IMASK0_PBE13_EN                                   0x00002000U
#define LRFDDBELL_IMASK0_PBE13_DIS                                  0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE12                                      0x00001000U
#define LRFDDBELL_IMASK0_PBE12_M                                    0x00001000U
#define LRFDDBELL_IMASK0_PBE12_S                                            12U
#define LRFDDBELL_IMASK0_PBE12_EN                                   0x00001000U
#define LRFDDBELL_IMASK0_PBE12_DIS                                  0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE11                                      0x00000800U
#define LRFDDBELL_IMASK0_PBE11_M                                    0x00000800U
#define LRFDDBELL_IMASK0_PBE11_S                                            11U
#define LRFDDBELL_IMASK0_PBE11_EN                                   0x00000800U
#define LRFDDBELL_IMASK0_PBE11_DIS                                  0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE10                                      0x00000400U
#define LRFDDBELL_IMASK0_PBE10_M                                    0x00000400U
#define LRFDDBELL_IMASK0_PBE10_S                                            10U
#define LRFDDBELL_IMASK0_PBE10_EN                                   0x00000400U
#define LRFDDBELL_IMASK0_PBE10_DIS                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE8                                       0x00000100U
#define LRFDDBELL_IMASK0_PBE8_M                                     0x00000100U
#define LRFDDBELL_IMASK0_PBE8_S                                              8U
#define LRFDDBELL_IMASK0_PBE8_EN                                    0x00000100U
#define LRFDDBELL_IMASK0_PBE8_DIS                                   0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE7                                       0x00000080U
#define LRFDDBELL_IMASK0_PBE7_M                                     0x00000080U
#define LRFDDBELL_IMASK0_PBE7_S                                              7U
#define LRFDDBELL_IMASK0_PBE7_EN                                    0x00000080U
#define LRFDDBELL_IMASK0_PBE7_DIS                                   0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE6                                       0x00000040U
#define LRFDDBELL_IMASK0_PBE6_M                                     0x00000040U
#define LRFDDBELL_IMASK0_PBE6_S                                              6U
#define LRFDDBELL_IMASK0_PBE6_EN                                    0x00000040U
#define LRFDDBELL_IMASK0_PBE6_DIS                                   0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE5                                       0x00000020U
#define LRFDDBELL_IMASK0_PBE5_M                                     0x00000020U
#define LRFDDBELL_IMASK0_PBE5_S                                              5U
#define LRFDDBELL_IMASK0_PBE5_EN                                    0x00000020U
#define LRFDDBELL_IMASK0_PBE5_DIS                                   0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE4                                       0x00000010U
#define LRFDDBELL_IMASK0_PBE4_M                                     0x00000010U
#define LRFDDBELL_IMASK0_PBE4_S                                              4U
#define LRFDDBELL_IMASK0_PBE4_EN                                    0x00000010U
#define LRFDDBELL_IMASK0_PBE4_DIS                                   0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE3                                       0x00000008U
#define LRFDDBELL_IMASK0_PBE3_M                                     0x00000008U
#define LRFDDBELL_IMASK0_PBE3_S                                              3U
#define LRFDDBELL_IMASK0_PBE3_EN                                    0x00000008U
#define LRFDDBELL_IMASK0_PBE3_DIS                                   0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE2                                       0x00000004U
#define LRFDDBELL_IMASK0_PBE2_M                                     0x00000004U
#define LRFDDBELL_IMASK0_PBE2_S                                              2U
#define LRFDDBELL_IMASK0_PBE2_EN                                    0x00000004U
#define LRFDDBELL_IMASK0_PBE2_DIS                                   0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE1                                       0x00000002U
#define LRFDDBELL_IMASK0_PBE1_M                                     0x00000002U
#define LRFDDBELL_IMASK0_PBE1_S                                              1U
#define LRFDDBELL_IMASK0_PBE1_EN                                    0x00000002U
#define LRFDDBELL_IMASK0_PBE1_DIS                                   0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK0_PBE0                                       0x00000001U
#define LRFDDBELL_IMASK0_PBE0_M                                     0x00000001U
#define LRFDDBELL_IMASK0_PBE0_S                                              0U
#define LRFDDBELL_IMASK0_PBE0_EN                                    0x00000001U
#define LRFDDBELL_IMASK0_PBE0_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_RIS0
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_SYSTIM2                                      0x80000000U
#define LRFDDBELL_RIS0_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_RIS0_SYSTIM2_S                                            31U
#define LRFDDBELL_RIS0_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_RIS0_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_SYSTIM1                                      0x40000000U
#define LRFDDBELL_RIS0_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_RIS0_SYSTIM1_S                                            30U
#define LRFDDBELL_RIS0_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_RIS0_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_SYSTIM0                                      0x20000000U
#define LRFDDBELL_RIS0_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_RIS0_SYSTIM0_S                                            29U
#define LRFDDBELL_RIS0_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_RIS0_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMDONE                                      0x10000000U
#define LRFDDBELL_RIS0_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_RIS0_MDMDONE_S                                            28U
#define LRFDDBELL_RIS0_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_RIS0_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMIN                                        0x08000000U
#define LRFDDBELL_RIS0_MDMIN_M                                      0x08000000U
#define LRFDDBELL_RIS0_MDMIN_S                                              27U
#define LRFDDBELL_RIS0_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_RIS0_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMOUT                                       0x04000000U
#define LRFDDBELL_RIS0_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_RIS0_MDMOUT_S                                             26U
#define LRFDDBELL_RIS0_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_RIS0_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_RIS0_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_RIS0_MDMSOFT2_S                                           25U
#define LRFDDBELL_RIS0_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_RIS0_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_RIS0_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_RIS0_MDMSOFT1_S                                           24U
#define LRFDDBELL_RIS0_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_RIS0_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_RIS0_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_RIS0_MDMSOFT0_S                                           23U
#define LRFDDBELL_RIS0_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_RIS0_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_RFEDONE                                      0x00400000U
#define LRFDDBELL_RIS0_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_RIS0_RFEDONE_S                                            22U
#define LRFDDBELL_RIS0_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_RIS0_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_RFESOFT1                                     0x00200000U
#define LRFDDBELL_RIS0_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_RIS0_RFESOFT1_S                                           21U
#define LRFDDBELL_RIS0_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_RIS0_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_RFESOFT0                                     0x00100000U
#define LRFDDBELL_RIS0_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_RIS0_RFESOFT0_S                                           20U
#define LRFDDBELL_RIS0_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_RIS0_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_LOCK                                         0x00080000U
#define LRFDDBELL_RIS0_LOCK_M                                       0x00080000U
#define LRFDDBELL_RIS0_LOCK_S                                               19U
#define LRFDDBELL_RIS0_LOCK_SET                                     0x00080000U
#define LRFDDBELL_RIS0_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_LOL                                          0x00040000U
#define LRFDDBELL_RIS0_LOL_M                                        0x00040000U
#define LRFDDBELL_RIS0_LOL_S                                                18U
#define LRFDDBELL_RIS0_LOL_SET                                      0x00040000U
#define LRFDDBELL_RIS0_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_TXFIFO                                       0x00020000U
#define LRFDDBELL_RIS0_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_RIS0_TXFIFO_S                                             17U
#define LRFDDBELL_RIS0_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_RIS0_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_RXFIFO                                       0x00010000U
#define LRFDDBELL_RIS0_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_RIS0_RXFIFO_S                                             16U
#define LRFDDBELL_RIS0_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_RIS0_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE15                                        0x00008000U
#define LRFDDBELL_RIS0_PBE15_M                                      0x00008000U
#define LRFDDBELL_RIS0_PBE15_S                                              15U
#define LRFDDBELL_RIS0_PBE15_SET                                    0x00008000U
#define LRFDDBELL_RIS0_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE14                                        0x00004000U
#define LRFDDBELL_RIS0_PBE14_M                                      0x00004000U
#define LRFDDBELL_RIS0_PBE14_S                                              14U
#define LRFDDBELL_RIS0_PBE14_SET                                    0x00004000U
#define LRFDDBELL_RIS0_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE13                                        0x00002000U
#define LRFDDBELL_RIS0_PBE13_M                                      0x00002000U
#define LRFDDBELL_RIS0_PBE13_S                                              13U
#define LRFDDBELL_RIS0_PBE13_SET                                    0x00002000U
#define LRFDDBELL_RIS0_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE12                                        0x00001000U
#define LRFDDBELL_RIS0_PBE12_M                                      0x00001000U
#define LRFDDBELL_RIS0_PBE12_S                                              12U
#define LRFDDBELL_RIS0_PBE12_SET                                    0x00001000U
#define LRFDDBELL_RIS0_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE11                                        0x00000800U
#define LRFDDBELL_RIS0_PBE11_M                                      0x00000800U
#define LRFDDBELL_RIS0_PBE11_S                                              11U
#define LRFDDBELL_RIS0_PBE11_SET                                    0x00000800U
#define LRFDDBELL_RIS0_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE10                                        0x00000400U
#define LRFDDBELL_RIS0_PBE10_M                                      0x00000400U
#define LRFDDBELL_RIS0_PBE10_S                                              10U
#define LRFDDBELL_RIS0_PBE10_SET                                    0x00000400U
#define LRFDDBELL_RIS0_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE9                                         0x00000200U
#define LRFDDBELL_RIS0_PBE9_M                                       0x00000200U
#define LRFDDBELL_RIS0_PBE9_S                                                9U
#define LRFDDBELL_RIS0_PBE9_SET                                     0x00000200U
#define LRFDDBELL_RIS0_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE8                                         0x00000100U
#define LRFDDBELL_RIS0_PBE8_M                                       0x00000100U
#define LRFDDBELL_RIS0_PBE8_S                                                8U
#define LRFDDBELL_RIS0_PBE8_SET                                     0x00000100U
#define LRFDDBELL_RIS0_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE7                                         0x00000080U
#define LRFDDBELL_RIS0_PBE7_M                                       0x00000080U
#define LRFDDBELL_RIS0_PBE7_S                                                7U
#define LRFDDBELL_RIS0_PBE7_SET                                     0x00000080U
#define LRFDDBELL_RIS0_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE6                                         0x00000040U
#define LRFDDBELL_RIS0_PBE6_M                                       0x00000040U
#define LRFDDBELL_RIS0_PBE6_S                                                6U
#define LRFDDBELL_RIS0_PBE6_SET                                     0x00000040U
#define LRFDDBELL_RIS0_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE5                                         0x00000020U
#define LRFDDBELL_RIS0_PBE5_M                                       0x00000020U
#define LRFDDBELL_RIS0_PBE5_S                                                5U
#define LRFDDBELL_RIS0_PBE5_SET                                     0x00000020U
#define LRFDDBELL_RIS0_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE4                                         0x00000010U
#define LRFDDBELL_RIS0_PBE4_M                                       0x00000010U
#define LRFDDBELL_RIS0_PBE4_S                                                4U
#define LRFDDBELL_RIS0_PBE4_SET                                     0x00000010U
#define LRFDDBELL_RIS0_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE3                                         0x00000008U
#define LRFDDBELL_RIS0_PBE3_M                                       0x00000008U
#define LRFDDBELL_RIS0_PBE3_S                                                3U
#define LRFDDBELL_RIS0_PBE3_SET                                     0x00000008U
#define LRFDDBELL_RIS0_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE2                                         0x00000004U
#define LRFDDBELL_RIS0_PBE2_M                                       0x00000004U
#define LRFDDBELL_RIS0_PBE2_S                                                2U
#define LRFDDBELL_RIS0_PBE2_SET                                     0x00000004U
#define LRFDDBELL_RIS0_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE1                                         0x00000002U
#define LRFDDBELL_RIS0_PBE1_M                                       0x00000002U
#define LRFDDBELL_RIS0_PBE1_S                                                1U
#define LRFDDBELL_RIS0_PBE1_SET                                     0x00000002U
#define LRFDDBELL_RIS0_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS0_PBE0                                         0x00000001U
#define LRFDDBELL_RIS0_PBE0_M                                       0x00000001U
#define LRFDDBELL_RIS0_PBE0_S                                                0U
#define LRFDDBELL_RIS0_PBE0_SET                                     0x00000001U
#define LRFDDBELL_RIS0_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_MIS0
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_SYSTIM2                                      0x80000000U
#define LRFDDBELL_MIS0_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_MIS0_SYSTIM2_S                                            31U
#define LRFDDBELL_MIS0_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_MIS0_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_SYSTIM1                                      0x40000000U
#define LRFDDBELL_MIS0_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_MIS0_SYSTIM1_S                                            30U
#define LRFDDBELL_MIS0_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_MIS0_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_SYSTIM0                                      0x20000000U
#define LRFDDBELL_MIS0_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_MIS0_SYSTIM0_S                                            29U
#define LRFDDBELL_MIS0_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_MIS0_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMDONE                                      0x10000000U
#define LRFDDBELL_MIS0_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_MIS0_MDMDONE_S                                            28U
#define LRFDDBELL_MIS0_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_MIS0_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMIN                                        0x08000000U
#define LRFDDBELL_MIS0_MDMIN_M                                      0x08000000U
#define LRFDDBELL_MIS0_MDMIN_S                                              27U
#define LRFDDBELL_MIS0_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_MIS0_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMOUT                                       0x04000000U
#define LRFDDBELL_MIS0_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_MIS0_MDMOUT_S                                             26U
#define LRFDDBELL_MIS0_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_MIS0_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_MIS0_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_MIS0_MDMSOFT2_S                                           25U
#define LRFDDBELL_MIS0_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_MIS0_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_MIS0_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_MIS0_MDMSOFT1_S                                           24U
#define LRFDDBELL_MIS0_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_MIS0_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_MIS0_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_MIS0_MDMSOFT0_S                                           23U
#define LRFDDBELL_MIS0_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_MIS0_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_RFEDONE                                      0x00400000U
#define LRFDDBELL_MIS0_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_MIS0_RFEDONE_S                                            22U
#define LRFDDBELL_MIS0_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_MIS0_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_RFESOFT1                                     0x00200000U
#define LRFDDBELL_MIS0_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_MIS0_RFESOFT1_S                                           21U
#define LRFDDBELL_MIS0_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_MIS0_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_RFESOFT0                                     0x00100000U
#define LRFDDBELL_MIS0_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_MIS0_RFESOFT0_S                                           20U
#define LRFDDBELL_MIS0_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_MIS0_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_LOCK                                         0x00080000U
#define LRFDDBELL_MIS0_LOCK_M                                       0x00080000U
#define LRFDDBELL_MIS0_LOCK_S                                               19U
#define LRFDDBELL_MIS0_LOCK_SET                                     0x00080000U
#define LRFDDBELL_MIS0_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_LOL                                          0x00040000U
#define LRFDDBELL_MIS0_LOL_M                                        0x00040000U
#define LRFDDBELL_MIS0_LOL_S                                                18U
#define LRFDDBELL_MIS0_LOL_SET                                      0x00040000U
#define LRFDDBELL_MIS0_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_TXFIFO                                       0x00020000U
#define LRFDDBELL_MIS0_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_MIS0_TXFIFO_S                                             17U
#define LRFDDBELL_MIS0_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_MIS0_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_RXFIFO                                       0x00010000U
#define LRFDDBELL_MIS0_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_MIS0_RXFIFO_S                                             16U
#define LRFDDBELL_MIS0_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_MIS0_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE15                                        0x00008000U
#define LRFDDBELL_MIS0_PBE15_M                                      0x00008000U
#define LRFDDBELL_MIS0_PBE15_S                                              15U
#define LRFDDBELL_MIS0_PBE15_SET                                    0x00008000U
#define LRFDDBELL_MIS0_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE14                                        0x00004000U
#define LRFDDBELL_MIS0_PBE14_M                                      0x00004000U
#define LRFDDBELL_MIS0_PBE14_S                                              14U
#define LRFDDBELL_MIS0_PBE14_SET                                    0x00004000U
#define LRFDDBELL_MIS0_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE13                                        0x00002000U
#define LRFDDBELL_MIS0_PBE13_M                                      0x00002000U
#define LRFDDBELL_MIS0_PBE13_S                                              13U
#define LRFDDBELL_MIS0_PBE13_SET                                    0x00002000U
#define LRFDDBELL_MIS0_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE12                                        0x00001000U
#define LRFDDBELL_MIS0_PBE12_M                                      0x00001000U
#define LRFDDBELL_MIS0_PBE12_S                                              12U
#define LRFDDBELL_MIS0_PBE12_SET                                    0x00001000U
#define LRFDDBELL_MIS0_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE11                                        0x00000800U
#define LRFDDBELL_MIS0_PBE11_M                                      0x00000800U
#define LRFDDBELL_MIS0_PBE11_S                                              11U
#define LRFDDBELL_MIS0_PBE11_SET                                    0x00000800U
#define LRFDDBELL_MIS0_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE10                                        0x00000400U
#define LRFDDBELL_MIS0_PBE10_M                                      0x00000400U
#define LRFDDBELL_MIS0_PBE10_S                                              10U
#define LRFDDBELL_MIS0_PBE10_SET                                    0x00000400U
#define LRFDDBELL_MIS0_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE9                                         0x00000200U
#define LRFDDBELL_MIS0_PBE9_M                                       0x00000200U
#define LRFDDBELL_MIS0_PBE9_S                                                9U
#define LRFDDBELL_MIS0_PBE9_SET                                     0x00000200U
#define LRFDDBELL_MIS0_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE8                                         0x00000100U
#define LRFDDBELL_MIS0_PBE8_M                                       0x00000100U
#define LRFDDBELL_MIS0_PBE8_S                                                8U
#define LRFDDBELL_MIS0_PBE8_SET                                     0x00000100U
#define LRFDDBELL_MIS0_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE7                                         0x00000080U
#define LRFDDBELL_MIS0_PBE7_M                                       0x00000080U
#define LRFDDBELL_MIS0_PBE7_S                                                7U
#define LRFDDBELL_MIS0_PBE7_SET                                     0x00000080U
#define LRFDDBELL_MIS0_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE6                                         0x00000040U
#define LRFDDBELL_MIS0_PBE6_M                                       0x00000040U
#define LRFDDBELL_MIS0_PBE6_S                                                6U
#define LRFDDBELL_MIS0_PBE6_SET                                     0x00000040U
#define LRFDDBELL_MIS0_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE5                                         0x00000020U
#define LRFDDBELL_MIS0_PBE5_M                                       0x00000020U
#define LRFDDBELL_MIS0_PBE5_S                                                5U
#define LRFDDBELL_MIS0_PBE5_SET                                     0x00000020U
#define LRFDDBELL_MIS0_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE4                                         0x00000010U
#define LRFDDBELL_MIS0_PBE4_M                                       0x00000010U
#define LRFDDBELL_MIS0_PBE4_S                                                4U
#define LRFDDBELL_MIS0_PBE4_SET                                     0x00000010U
#define LRFDDBELL_MIS0_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE3                                         0x00000008U
#define LRFDDBELL_MIS0_PBE3_M                                       0x00000008U
#define LRFDDBELL_MIS0_PBE3_S                                                3U
#define LRFDDBELL_MIS0_PBE3_SET                                     0x00000008U
#define LRFDDBELL_MIS0_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE2                                         0x00000004U
#define LRFDDBELL_MIS0_PBE2_M                                       0x00000004U
#define LRFDDBELL_MIS0_PBE2_S                                                2U
#define LRFDDBELL_MIS0_PBE2_SET                                     0x00000004U
#define LRFDDBELL_MIS0_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE1                                         0x00000002U
#define LRFDDBELL_MIS0_PBE1_M                                       0x00000002U
#define LRFDDBELL_MIS0_PBE1_S                                                1U
#define LRFDDBELL_MIS0_PBE1_SET                                     0x00000002U
#define LRFDDBELL_MIS0_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS0_PBE0                                         0x00000001U
#define LRFDDBELL_MIS0_PBE0_M                                       0x00000001U
#define LRFDDBELL_MIS0_PBE0_S                                                0U
#define LRFDDBELL_MIS0_PBE0_SET                                     0x00000001U
#define LRFDDBELL_MIS0_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ISET0
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ISET0_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ISET0_SYSTIM2_S                                           31U
#define LRFDDBELL_ISET0_SYSTIM2_SET                                 0x80000000U
#define LRFDDBELL_ISET0_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ISET0_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ISET0_SYSTIM1_S                                           30U
#define LRFDDBELL_ISET0_SYSTIM1_SET                                 0x40000000U
#define LRFDDBELL_ISET0_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ISET0_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ISET0_SYSTIM0_S                                           29U
#define LRFDDBELL_ISET0_SYSTIM0_SET                                 0x20000000U
#define LRFDDBELL_ISET0_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMDONE                                     0x10000000U
#define LRFDDBELL_ISET0_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ISET0_MDMDONE_S                                           28U
#define LRFDDBELL_ISET0_MDMDONE_SET                                 0x10000000U
#define LRFDDBELL_ISET0_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMIN                                       0x08000000U
#define LRFDDBELL_ISET0_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ISET0_MDMIN_S                                             27U
#define LRFDDBELL_ISET0_MDMIN_SET                                   0x08000000U
#define LRFDDBELL_ISET0_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMOUT                                      0x04000000U
#define LRFDDBELL_ISET0_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ISET0_MDMOUT_S                                            26U
#define LRFDDBELL_ISET0_MDMOUT_SET                                  0x04000000U
#define LRFDDBELL_ISET0_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ISET0_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ISET0_MDMSOFT2_S                                          25U
#define LRFDDBELL_ISET0_MDMSOFT2_SET                                0x02000000U
#define LRFDDBELL_ISET0_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ISET0_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ISET0_MDMSOFT1_S                                          24U
#define LRFDDBELL_ISET0_MDMSOFT1_SET                                0x01000000U
#define LRFDDBELL_ISET0_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ISET0_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ISET0_MDMSOFT0_S                                          23U
#define LRFDDBELL_ISET0_MDMSOFT0_SET                                0x00800000U
#define LRFDDBELL_ISET0_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_RFEDONE                                     0x00400000U
#define LRFDDBELL_ISET0_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ISET0_RFEDONE_S                                           22U
#define LRFDDBELL_ISET0_RFEDONE_SET                                 0x00400000U
#define LRFDDBELL_ISET0_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ISET0_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ISET0_RFESOFT1_S                                          21U
#define LRFDDBELL_ISET0_RFESOFT1_SET                                0x00200000U
#define LRFDDBELL_ISET0_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ISET0_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ISET0_RFESOFT0_S                                          20U
#define LRFDDBELL_ISET0_RFESOFT0_SET                                0x00100000U
#define LRFDDBELL_ISET0_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_LOCK                                        0x00080000U
#define LRFDDBELL_ISET0_LOCK_M                                      0x00080000U
#define LRFDDBELL_ISET0_LOCK_S                                              19U
#define LRFDDBELL_ISET0_LOCK_SET                                    0x00080000U
#define LRFDDBELL_ISET0_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_LOL                                         0x00040000U
#define LRFDDBELL_ISET0_LOL_M                                       0x00040000U
#define LRFDDBELL_ISET0_LOL_S                                               18U
#define LRFDDBELL_ISET0_LOL_SET                                     0x00040000U
#define LRFDDBELL_ISET0_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_TXFIFO                                      0x00020000U
#define LRFDDBELL_ISET0_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ISET0_TXFIFO_S                                            17U
#define LRFDDBELL_ISET0_TXFIFO_SET                                  0x00020000U
#define LRFDDBELL_ISET0_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_RXFIFO                                      0x00010000U
#define LRFDDBELL_ISET0_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ISET0_RXFIFO_S                                            16U
#define LRFDDBELL_ISET0_RXFIFO_SET                                  0x00010000U
#define LRFDDBELL_ISET0_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE15                                       0x00008000U
#define LRFDDBELL_ISET0_PBE15_M                                     0x00008000U
#define LRFDDBELL_ISET0_PBE15_S                                             15U
#define LRFDDBELL_ISET0_PBE15_SET                                   0x00008000U
#define LRFDDBELL_ISET0_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE14                                       0x00004000U
#define LRFDDBELL_ISET0_PBE14_M                                     0x00004000U
#define LRFDDBELL_ISET0_PBE14_S                                             14U
#define LRFDDBELL_ISET0_PBE14_SET                                   0x00004000U
#define LRFDDBELL_ISET0_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE13                                       0x00002000U
#define LRFDDBELL_ISET0_PBE13_M                                     0x00002000U
#define LRFDDBELL_ISET0_PBE13_S                                             13U
#define LRFDDBELL_ISET0_PBE13_SET                                   0x00002000U
#define LRFDDBELL_ISET0_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE12                                       0x00001000U
#define LRFDDBELL_ISET0_PBE12_M                                     0x00001000U
#define LRFDDBELL_ISET0_PBE12_S                                             12U
#define LRFDDBELL_ISET0_PBE12_SET                                   0x00001000U
#define LRFDDBELL_ISET0_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE11                                       0x00000800U
#define LRFDDBELL_ISET0_PBE11_M                                     0x00000800U
#define LRFDDBELL_ISET0_PBE11_S                                             11U
#define LRFDDBELL_ISET0_PBE11_SET                                   0x00000800U
#define LRFDDBELL_ISET0_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE10                                       0x00000400U
#define LRFDDBELL_ISET0_PBE10_M                                     0x00000400U
#define LRFDDBELL_ISET0_PBE10_S                                             10U
#define LRFDDBELL_ISET0_PBE10_SET                                   0x00000400U
#define LRFDDBELL_ISET0_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE9                                        0x00000200U
#define LRFDDBELL_ISET0_PBE9_M                                      0x00000200U
#define LRFDDBELL_ISET0_PBE9_S                                               9U
#define LRFDDBELL_ISET0_PBE9_SET                                    0x00000200U
#define LRFDDBELL_ISET0_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE8                                        0x00000100U
#define LRFDDBELL_ISET0_PBE8_M                                      0x00000100U
#define LRFDDBELL_ISET0_PBE8_S                                               8U
#define LRFDDBELL_ISET0_PBE8_SET                                    0x00000100U
#define LRFDDBELL_ISET0_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE7                                        0x00000080U
#define LRFDDBELL_ISET0_PBE7_M                                      0x00000080U
#define LRFDDBELL_ISET0_PBE7_S                                               7U
#define LRFDDBELL_ISET0_PBE7_SET                                    0x00000080U
#define LRFDDBELL_ISET0_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE6                                        0x00000040U
#define LRFDDBELL_ISET0_PBE6_M                                      0x00000040U
#define LRFDDBELL_ISET0_PBE6_S                                               6U
#define LRFDDBELL_ISET0_PBE6_SET                                    0x00000040U
#define LRFDDBELL_ISET0_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE5                                        0x00000020U
#define LRFDDBELL_ISET0_PBE5_M                                      0x00000020U
#define LRFDDBELL_ISET0_PBE5_S                                               5U
#define LRFDDBELL_ISET0_PBE5_SET                                    0x00000020U
#define LRFDDBELL_ISET0_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE4                                        0x00000010U
#define LRFDDBELL_ISET0_PBE4_M                                      0x00000010U
#define LRFDDBELL_ISET0_PBE4_S                                               4U
#define LRFDDBELL_ISET0_PBE4_SET                                    0x00000010U
#define LRFDDBELL_ISET0_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE3                                        0x00000008U
#define LRFDDBELL_ISET0_PBE3_M                                      0x00000008U
#define LRFDDBELL_ISET0_PBE3_S                                               3U
#define LRFDDBELL_ISET0_PBE3_SET                                    0x00000008U
#define LRFDDBELL_ISET0_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE2                                        0x00000004U
#define LRFDDBELL_ISET0_PBE2_M                                      0x00000004U
#define LRFDDBELL_ISET0_PBE2_S                                               2U
#define LRFDDBELL_ISET0_PBE2_SET                                    0x00000004U
#define LRFDDBELL_ISET0_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE1                                        0x00000002U
#define LRFDDBELL_ISET0_PBE1_M                                      0x00000002U
#define LRFDDBELL_ISET0_PBE1_S                                               1U
#define LRFDDBELL_ISET0_PBE1_SET                                    0x00000002U
#define LRFDDBELL_ISET0_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET0_PBE0                                        0x00000001U
#define LRFDDBELL_ISET0_PBE0_M                                      0x00000001U
#define LRFDDBELL_ISET0_PBE0_S                                               0U
#define LRFDDBELL_ISET0_PBE0_SET                                    0x00000001U
#define LRFDDBELL_ISET0_PBE0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ICLR0
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ICLR0_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ICLR0_SYSTIM2_S                                           31U
#define LRFDDBELL_ICLR0_SYSTIM2_CLR                                 0x80000000U
#define LRFDDBELL_ICLR0_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ICLR0_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ICLR0_SYSTIM1_S                                           30U
#define LRFDDBELL_ICLR0_SYSTIM1_CLR                                 0x40000000U
#define LRFDDBELL_ICLR0_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ICLR0_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ICLR0_SYSTIM0_S                                           29U
#define LRFDDBELL_ICLR0_SYSTIM0_CLR                                 0x20000000U
#define LRFDDBELL_ICLR0_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMDONE                                     0x10000000U
#define LRFDDBELL_ICLR0_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ICLR0_MDMDONE_S                                           28U
#define LRFDDBELL_ICLR0_MDMDONE_CLR                                 0x10000000U
#define LRFDDBELL_ICLR0_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMIN                                       0x08000000U
#define LRFDDBELL_ICLR0_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ICLR0_MDMIN_S                                             27U
#define LRFDDBELL_ICLR0_MDMIN_CLR                                   0x08000000U
#define LRFDDBELL_ICLR0_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMOUT                                      0x04000000U
#define LRFDDBELL_ICLR0_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ICLR0_MDMOUT_S                                            26U
#define LRFDDBELL_ICLR0_MDMOUT_CLR                                  0x04000000U
#define LRFDDBELL_ICLR0_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ICLR0_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ICLR0_MDMSOFT2_S                                          25U
#define LRFDDBELL_ICLR0_MDMSOFT2_CLR                                0x02000000U
#define LRFDDBELL_ICLR0_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ICLR0_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ICLR0_MDMSOFT1_S                                          24U
#define LRFDDBELL_ICLR0_MDMSOFT1_CLR                                0x01000000U
#define LRFDDBELL_ICLR0_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ICLR0_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ICLR0_MDMSOFT0_S                                          23U
#define LRFDDBELL_ICLR0_MDMSOFT0_CLR                                0x00800000U
#define LRFDDBELL_ICLR0_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_RFEDONE                                     0x00400000U
#define LRFDDBELL_ICLR0_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ICLR0_RFEDONE_S                                           22U
#define LRFDDBELL_ICLR0_RFEDONE_CLR                                 0x00400000U
#define LRFDDBELL_ICLR0_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ICLR0_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ICLR0_RFESOFT1_S                                          21U
#define LRFDDBELL_ICLR0_RFESOFT1_CLR                                0x00200000U
#define LRFDDBELL_ICLR0_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ICLR0_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ICLR0_RFESOFT0_S                                          20U
#define LRFDDBELL_ICLR0_RFESOFT0_CLR                                0x00100000U
#define LRFDDBELL_ICLR0_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_LOCK                                        0x00080000U
#define LRFDDBELL_ICLR0_LOCK_M                                      0x00080000U
#define LRFDDBELL_ICLR0_LOCK_S                                              19U
#define LRFDDBELL_ICLR0_LOCK_CLR                                    0x00080000U
#define LRFDDBELL_ICLR0_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_LOL                                         0x00040000U
#define LRFDDBELL_ICLR0_LOL_M                                       0x00040000U
#define LRFDDBELL_ICLR0_LOL_S                                               18U
#define LRFDDBELL_ICLR0_LOL_CLR                                     0x00040000U
#define LRFDDBELL_ICLR0_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_TXFIFO                                      0x00020000U
#define LRFDDBELL_ICLR0_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ICLR0_TXFIFO_S                                            17U
#define LRFDDBELL_ICLR0_TXFIFO_CLR                                  0x00020000U
#define LRFDDBELL_ICLR0_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_RXFIFO                                      0x00010000U
#define LRFDDBELL_ICLR0_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ICLR0_RXFIFO_S                                            16U
#define LRFDDBELL_ICLR0_RXFIFO_CLR                                  0x00010000U
#define LRFDDBELL_ICLR0_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE15                                       0x00008000U
#define LRFDDBELL_ICLR0_PBE15_M                                     0x00008000U
#define LRFDDBELL_ICLR0_PBE15_S                                             15U
#define LRFDDBELL_ICLR0_PBE15_CLR                                   0x00008000U
#define LRFDDBELL_ICLR0_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE14                                       0x00004000U
#define LRFDDBELL_ICLR0_PBE14_M                                     0x00004000U
#define LRFDDBELL_ICLR0_PBE14_S                                             14U
#define LRFDDBELL_ICLR0_PBE14_CLR                                   0x00004000U
#define LRFDDBELL_ICLR0_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE13                                       0x00002000U
#define LRFDDBELL_ICLR0_PBE13_M                                     0x00002000U
#define LRFDDBELL_ICLR0_PBE13_S                                             13U
#define LRFDDBELL_ICLR0_PBE13_CLR                                   0x00002000U
#define LRFDDBELL_ICLR0_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE12                                       0x00001000U
#define LRFDDBELL_ICLR0_PBE12_M                                     0x00001000U
#define LRFDDBELL_ICLR0_PBE12_S                                             12U
#define LRFDDBELL_ICLR0_PBE12_CLR                                   0x00001000U
#define LRFDDBELL_ICLR0_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE11                                       0x00000800U
#define LRFDDBELL_ICLR0_PBE11_M                                     0x00000800U
#define LRFDDBELL_ICLR0_PBE11_S                                             11U
#define LRFDDBELL_ICLR0_PBE11_CLR                                   0x00000800U
#define LRFDDBELL_ICLR0_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE10                                       0x00000400U
#define LRFDDBELL_ICLR0_PBE10_M                                     0x00000400U
#define LRFDDBELL_ICLR0_PBE10_S                                             10U
#define LRFDDBELL_ICLR0_PBE10_CLR                                   0x00000400U
#define LRFDDBELL_ICLR0_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE9                                        0x00000200U
#define LRFDDBELL_ICLR0_PBE9_M                                      0x00000200U
#define LRFDDBELL_ICLR0_PBE9_S                                               9U
#define LRFDDBELL_ICLR0_PBE9_CLR                                    0x00000200U
#define LRFDDBELL_ICLR0_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE8                                        0x00000100U
#define LRFDDBELL_ICLR0_PBE8_M                                      0x00000100U
#define LRFDDBELL_ICLR0_PBE8_S                                               8U
#define LRFDDBELL_ICLR0_PBE8_CLR                                    0x00000100U
#define LRFDDBELL_ICLR0_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE7                                        0x00000080U
#define LRFDDBELL_ICLR0_PBE7_M                                      0x00000080U
#define LRFDDBELL_ICLR0_PBE7_S                                               7U
#define LRFDDBELL_ICLR0_PBE7_CLR                                    0x00000080U
#define LRFDDBELL_ICLR0_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE6                                        0x00000040U
#define LRFDDBELL_ICLR0_PBE6_M                                      0x00000040U
#define LRFDDBELL_ICLR0_PBE6_S                                               6U
#define LRFDDBELL_ICLR0_PBE6_CLR                                    0x00000040U
#define LRFDDBELL_ICLR0_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE5                                        0x00000020U
#define LRFDDBELL_ICLR0_PBE5_M                                      0x00000020U
#define LRFDDBELL_ICLR0_PBE5_S                                               5U
#define LRFDDBELL_ICLR0_PBE5_CLR                                    0x00000020U
#define LRFDDBELL_ICLR0_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE4                                        0x00000010U
#define LRFDDBELL_ICLR0_PBE4_M                                      0x00000010U
#define LRFDDBELL_ICLR0_PBE4_S                                               4U
#define LRFDDBELL_ICLR0_PBE4_CLR                                    0x00000010U
#define LRFDDBELL_ICLR0_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE3                                        0x00000008U
#define LRFDDBELL_ICLR0_PBE3_M                                      0x00000008U
#define LRFDDBELL_ICLR0_PBE3_S                                               3U
#define LRFDDBELL_ICLR0_PBE3_CLR                                    0x00000008U
#define LRFDDBELL_ICLR0_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE2                                        0x00000004U
#define LRFDDBELL_ICLR0_PBE2_M                                      0x00000004U
#define LRFDDBELL_ICLR0_PBE2_S                                               2U
#define LRFDDBELL_ICLR0_PBE2_CLR                                    0x00000004U
#define LRFDDBELL_ICLR0_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE1                                        0x00000002U
#define LRFDDBELL_ICLR0_PBE1_M                                      0x00000002U
#define LRFDDBELL_ICLR0_PBE1_S                                               1U
#define LRFDDBELL_ICLR0_PBE1_CLR                                    0x00000002U
#define LRFDDBELL_ICLR0_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR0_PBE0                                        0x00000001U
#define LRFDDBELL_ICLR0_PBE0_M                                      0x00000001U
#define LRFDDBELL_ICLR0_PBE0_S                                               0U
#define LRFDDBELL_ICLR0_PBE0_CLR                                    0x00000001U
#define LRFDDBELL_ICLR0_PBE0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_IMASK1
//
//*****************************************************************************
// Field:    [30] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_SYSTIM2                                    0x40000000U
#define LRFDDBELL_IMASK1_SYSTIM2_M                                  0x40000000U
#define LRFDDBELL_IMASK1_SYSTIM2_S                                          30U
#define LRFDDBELL_IMASK1_SYSTIM2_EN                                 0x40000000U
#define LRFDDBELL_IMASK1_SYSTIM2_DIS                                0x00000000U

// Field:    [29] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_SYSTIM1                                    0x20000000U
#define LRFDDBELL_IMASK1_SYSTIM1_M                                  0x20000000U
#define LRFDDBELL_IMASK1_SYSTIM1_S                                          29U
#define LRFDDBELL_IMASK1_SYSTIM1_EN                                 0x20000000U
#define LRFDDBELL_IMASK1_SYSTIM1_DIS                                0x00000000U

// Field:    [28] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_SYSTIM0                                    0x10000000U
#define LRFDDBELL_IMASK1_SYSTIM0_M                                  0x10000000U
#define LRFDDBELL_IMASK1_SYSTIM0_S                                          28U
#define LRFDDBELL_IMASK1_SYSTIM0_EN                                 0x10000000U
#define LRFDDBELL_IMASK1_SYSTIM0_DIS                                0x00000000U

// Field:    [27] MDMDONE
//
// MDMDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMDONE                                    0x08000000U
#define LRFDDBELL_IMASK1_MDMDONE_M                                  0x08000000U
#define LRFDDBELL_IMASK1_MDMDONE_S                                          27U
#define LRFDDBELL_IMASK1_MDMDONE_EN                                 0x08000000U
#define LRFDDBELL_IMASK1_MDMDONE_DIS                                0x00000000U

// Field:    [26] MDMIN
//
// MDMIN event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMIN                                      0x04000000U
#define LRFDDBELL_IMASK1_MDMIN_M                                    0x04000000U
#define LRFDDBELL_IMASK1_MDMIN_S                                            26U
#define LRFDDBELL_IMASK1_MDMIN_EN                                   0x04000000U
#define LRFDDBELL_IMASK1_MDMIN_DIS                                  0x00000000U

// Field:    [25] MDMOUT
//
// MDMOUT event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMOUT                                     0x02000000U
#define LRFDDBELL_IMASK1_MDMOUT_M                                   0x02000000U
#define LRFDDBELL_IMASK1_MDMOUT_S                                           25U
#define LRFDDBELL_IMASK1_MDMOUT_EN                                  0x02000000U
#define LRFDDBELL_IMASK1_MDMOUT_DIS                                 0x00000000U

// Field:    [24] MDMSOFT2
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMSOFT2                                   0x01000000U
#define LRFDDBELL_IMASK1_MDMSOFT2_M                                 0x01000000U
#define LRFDDBELL_IMASK1_MDMSOFT2_S                                         24U
#define LRFDDBELL_IMASK1_MDMSOFT2_EN                                0x01000000U
#define LRFDDBELL_IMASK1_MDMSOFT2_DIS                               0x00000000U

// Field:    [23] MDMSOFT1
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMSOFT1                                   0x00800000U
#define LRFDDBELL_IMASK1_MDMSOFT1_M                                 0x00800000U
#define LRFDDBELL_IMASK1_MDMSOFT1_S                                         23U
#define LRFDDBELL_IMASK1_MDMSOFT1_EN                                0x00800000U
#define LRFDDBELL_IMASK1_MDMSOFT1_DIS                               0x00000000U

// Field:    [22] MDMSOFT0
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_MDMSOFT0                                   0x00400000U
#define LRFDDBELL_IMASK1_MDMSOFT0_M                                 0x00400000U
#define LRFDDBELL_IMASK1_MDMSOFT0_S                                         22U
#define LRFDDBELL_IMASK1_MDMSOFT0_EN                                0x00400000U
#define LRFDDBELL_IMASK1_MDMSOFT0_DIS                               0x00000000U

// Field:    [21] RFEDONE
//
// RFEDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_RFEDONE                                    0x00200000U
#define LRFDDBELL_IMASK1_RFEDONE_M                                  0x00200000U
#define LRFDDBELL_IMASK1_RFEDONE_S                                          21U
#define LRFDDBELL_IMASK1_RFEDONE_EN                                 0x00200000U
#define LRFDDBELL_IMASK1_RFEDONE_DIS                                0x00000000U

// Field:    [20] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_RFESOFT1                                   0x00100000U
#define LRFDDBELL_IMASK1_RFESOFT1_M                                 0x00100000U
#define LRFDDBELL_IMASK1_RFESOFT1_S                                         20U
#define LRFDDBELL_IMASK1_RFESOFT1_EN                                0x00100000U
#define LRFDDBELL_IMASK1_RFESOFT1_DIS                               0x00000000U

// Field:    [19] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_RFESOFT0                                   0x00080000U
#define LRFDDBELL_IMASK1_RFESOFT0_M                                 0x00080000U
#define LRFDDBELL_IMASK1_RFESOFT0_S                                         19U
#define LRFDDBELL_IMASK1_RFESOFT0_EN                                0x00080000U
#define LRFDDBELL_IMASK1_RFESOFT0_DIS                               0x00000000U

// Field:    [18] LOCK
//
// LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_LOCK                                       0x00040000U
#define LRFDDBELL_IMASK1_LOCK_M                                     0x00040000U
#define LRFDDBELL_IMASK1_LOCK_S                                             18U
#define LRFDDBELL_IMASK1_LOCK_EN                                    0x00040000U
#define LRFDDBELL_IMASK1_LOCK_DIS                                   0x00000000U

// Field:    [17] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_LOL                                        0x00020000U
#define LRFDDBELL_IMASK1_LOL_M                                      0x00020000U
#define LRFDDBELL_IMASK1_LOL_S                                              17U
#define LRFDDBELL_IMASK1_LOL_EN                                     0x00020000U
#define LRFDDBELL_IMASK1_LOL_DIS                                    0x00000000U

// Field:    [16] TXFIFO
//
// TXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_TXFIFO                                     0x00010000U
#define LRFDDBELL_IMASK1_TXFIFO_M                                   0x00010000U
#define LRFDDBELL_IMASK1_TXFIFO_S                                           16U
#define LRFDDBELL_IMASK1_TXFIFO_EN                                  0x00010000U
#define LRFDDBELL_IMASK1_TXFIFO_DIS                                 0x00000000U

// Field:    [15] RXFIFO
//
// RXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_RXFIFO                                     0x00008000U
#define LRFDDBELL_IMASK1_RXFIFO_M                                   0x00008000U
#define LRFDDBELL_IMASK1_RXFIFO_S                                           15U
#define LRFDDBELL_IMASK1_RXFIFO_EN                                  0x00008000U
#define LRFDDBELL_IMASK1_RXFIFO_DIS                                 0x00000000U

// Field:    [14] PBE15
//
// PBE15 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE15                                      0x00004000U
#define LRFDDBELL_IMASK1_PBE15_M                                    0x00004000U
#define LRFDDBELL_IMASK1_PBE15_S                                            14U
#define LRFDDBELL_IMASK1_PBE15_EN                                   0x00004000U
#define LRFDDBELL_IMASK1_PBE15_DIS                                  0x00000000U

// Field:    [13] PBE14
//
// PBE14 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE14                                      0x00002000U
#define LRFDDBELL_IMASK1_PBE14_M                                    0x00002000U
#define LRFDDBELL_IMASK1_PBE14_S                                            13U
#define LRFDDBELL_IMASK1_PBE14_EN                                   0x00002000U
#define LRFDDBELL_IMASK1_PBE14_DIS                                  0x00000000U

// Field:    [12] PBE13
//
// PBE13 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE13                                      0x00001000U
#define LRFDDBELL_IMASK1_PBE13_M                                    0x00001000U
#define LRFDDBELL_IMASK1_PBE13_S                                            12U
#define LRFDDBELL_IMASK1_PBE13_EN                                   0x00001000U
#define LRFDDBELL_IMASK1_PBE13_DIS                                  0x00000000U

// Field:    [11] PBE12
//
// PBE12 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE12                                      0x00000800U
#define LRFDDBELL_IMASK1_PBE12_M                                    0x00000800U
#define LRFDDBELL_IMASK1_PBE12_S                                            11U
#define LRFDDBELL_IMASK1_PBE12_EN                                   0x00000800U
#define LRFDDBELL_IMASK1_PBE12_DIS                                  0x00000000U

// Field:    [10] PBE11
//
// PBE11 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE11                                      0x00000400U
#define LRFDDBELL_IMASK1_PBE11_M                                    0x00000400U
#define LRFDDBELL_IMASK1_PBE11_S                                            10U
#define LRFDDBELL_IMASK1_PBE11_EN                                   0x00000400U
#define LRFDDBELL_IMASK1_PBE11_DIS                                  0x00000000U

// Field:     [9] PBE10
//
// PBE10 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE10                                      0x00000200U
#define LRFDDBELL_IMASK1_PBE10_M                                    0x00000200U
#define LRFDDBELL_IMASK1_PBE10_S                                             9U
#define LRFDDBELL_IMASK1_PBE10_EN                                   0x00000200U
#define LRFDDBELL_IMASK1_PBE10_DIS                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE8                                       0x00000100U
#define LRFDDBELL_IMASK1_PBE8_M                                     0x00000100U
#define LRFDDBELL_IMASK1_PBE8_S                                              8U
#define LRFDDBELL_IMASK1_PBE8_EN                                    0x00000100U
#define LRFDDBELL_IMASK1_PBE8_DIS                                   0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE7                                       0x00000080U
#define LRFDDBELL_IMASK1_PBE7_M                                     0x00000080U
#define LRFDDBELL_IMASK1_PBE7_S                                              7U
#define LRFDDBELL_IMASK1_PBE7_EN                                    0x00000080U
#define LRFDDBELL_IMASK1_PBE7_DIS                                   0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE6                                       0x00000040U
#define LRFDDBELL_IMASK1_PBE6_M                                     0x00000040U
#define LRFDDBELL_IMASK1_PBE6_S                                              6U
#define LRFDDBELL_IMASK1_PBE6_EN                                    0x00000040U
#define LRFDDBELL_IMASK1_PBE6_DIS                                   0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE5                                       0x00000020U
#define LRFDDBELL_IMASK1_PBE5_M                                     0x00000020U
#define LRFDDBELL_IMASK1_PBE5_S                                              5U
#define LRFDDBELL_IMASK1_PBE5_EN                                    0x00000020U
#define LRFDDBELL_IMASK1_PBE5_DIS                                   0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE4                                       0x00000010U
#define LRFDDBELL_IMASK1_PBE4_M                                     0x00000010U
#define LRFDDBELL_IMASK1_PBE4_S                                              4U
#define LRFDDBELL_IMASK1_PBE4_EN                                    0x00000010U
#define LRFDDBELL_IMASK1_PBE4_DIS                                   0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE3                                       0x00000008U
#define LRFDDBELL_IMASK1_PBE3_M                                     0x00000008U
#define LRFDDBELL_IMASK1_PBE3_S                                              3U
#define LRFDDBELL_IMASK1_PBE3_EN                                    0x00000008U
#define LRFDDBELL_IMASK1_PBE3_DIS                                   0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE2                                       0x00000004U
#define LRFDDBELL_IMASK1_PBE2_M                                     0x00000004U
#define LRFDDBELL_IMASK1_PBE2_S                                              2U
#define LRFDDBELL_IMASK1_PBE2_EN                                    0x00000004U
#define LRFDDBELL_IMASK1_PBE2_DIS                                   0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE1                                       0x00000002U
#define LRFDDBELL_IMASK1_PBE1_M                                     0x00000002U
#define LRFDDBELL_IMASK1_PBE1_S                                              1U
#define LRFDDBELL_IMASK1_PBE1_EN                                    0x00000002U
#define LRFDDBELL_IMASK1_PBE1_DIS                                   0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK1_PBE0                                       0x00000001U
#define LRFDDBELL_IMASK1_PBE0_M                                     0x00000001U
#define LRFDDBELL_IMASK1_PBE0_S                                              0U
#define LRFDDBELL_IMASK1_PBE0_EN                                    0x00000001U
#define LRFDDBELL_IMASK1_PBE0_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_RIS1
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_SYSTIM2                                      0x80000000U
#define LRFDDBELL_RIS1_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_RIS1_SYSTIM2_S                                            31U
#define LRFDDBELL_RIS1_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_RIS1_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_SYSTIM1                                      0x40000000U
#define LRFDDBELL_RIS1_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_RIS1_SYSTIM1_S                                            30U
#define LRFDDBELL_RIS1_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_RIS1_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_SYSTIM0                                      0x20000000U
#define LRFDDBELL_RIS1_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_RIS1_SYSTIM0_S                                            29U
#define LRFDDBELL_RIS1_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_RIS1_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMDONE                                      0x10000000U
#define LRFDDBELL_RIS1_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_RIS1_MDMDONE_S                                            28U
#define LRFDDBELL_RIS1_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_RIS1_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMIN                                        0x08000000U
#define LRFDDBELL_RIS1_MDMIN_M                                      0x08000000U
#define LRFDDBELL_RIS1_MDMIN_S                                              27U
#define LRFDDBELL_RIS1_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_RIS1_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMOUT                                       0x04000000U
#define LRFDDBELL_RIS1_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_RIS1_MDMOUT_S                                             26U
#define LRFDDBELL_RIS1_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_RIS1_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_RIS1_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_RIS1_MDMSOFT2_S                                           25U
#define LRFDDBELL_RIS1_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_RIS1_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_RIS1_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_RIS1_MDMSOFT1_S                                           24U
#define LRFDDBELL_RIS1_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_RIS1_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_RIS1_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_RIS1_MDMSOFT0_S                                           23U
#define LRFDDBELL_RIS1_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_RIS1_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_RFEDONE                                      0x00400000U
#define LRFDDBELL_RIS1_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_RIS1_RFEDONE_S                                            22U
#define LRFDDBELL_RIS1_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_RIS1_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_RFESOFT1                                     0x00200000U
#define LRFDDBELL_RIS1_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_RIS1_RFESOFT1_S                                           21U
#define LRFDDBELL_RIS1_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_RIS1_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_RFESOFT0                                     0x00100000U
#define LRFDDBELL_RIS1_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_RIS1_RFESOFT0_S                                           20U
#define LRFDDBELL_RIS1_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_RIS1_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_LOCK                                         0x00080000U
#define LRFDDBELL_RIS1_LOCK_M                                       0x00080000U
#define LRFDDBELL_RIS1_LOCK_S                                               19U
#define LRFDDBELL_RIS1_LOCK_SET                                     0x00080000U
#define LRFDDBELL_RIS1_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_LOL                                          0x00040000U
#define LRFDDBELL_RIS1_LOL_M                                        0x00040000U
#define LRFDDBELL_RIS1_LOL_S                                                18U
#define LRFDDBELL_RIS1_LOL_SET                                      0x00040000U
#define LRFDDBELL_RIS1_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_TXFIFO                                       0x00020000U
#define LRFDDBELL_RIS1_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_RIS1_TXFIFO_S                                             17U
#define LRFDDBELL_RIS1_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_RIS1_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_RXFIFO                                       0x00010000U
#define LRFDDBELL_RIS1_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_RIS1_RXFIFO_S                                             16U
#define LRFDDBELL_RIS1_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_RIS1_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE15                                        0x00008000U
#define LRFDDBELL_RIS1_PBE15_M                                      0x00008000U
#define LRFDDBELL_RIS1_PBE15_S                                              15U
#define LRFDDBELL_RIS1_PBE15_SET                                    0x00008000U
#define LRFDDBELL_RIS1_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE14                                        0x00004000U
#define LRFDDBELL_RIS1_PBE14_M                                      0x00004000U
#define LRFDDBELL_RIS1_PBE14_S                                              14U
#define LRFDDBELL_RIS1_PBE14_SET                                    0x00004000U
#define LRFDDBELL_RIS1_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE13                                        0x00002000U
#define LRFDDBELL_RIS1_PBE13_M                                      0x00002000U
#define LRFDDBELL_RIS1_PBE13_S                                              13U
#define LRFDDBELL_RIS1_PBE13_SET                                    0x00002000U
#define LRFDDBELL_RIS1_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE12                                        0x00001000U
#define LRFDDBELL_RIS1_PBE12_M                                      0x00001000U
#define LRFDDBELL_RIS1_PBE12_S                                              12U
#define LRFDDBELL_RIS1_PBE12_SET                                    0x00001000U
#define LRFDDBELL_RIS1_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE11                                        0x00000800U
#define LRFDDBELL_RIS1_PBE11_M                                      0x00000800U
#define LRFDDBELL_RIS1_PBE11_S                                              11U
#define LRFDDBELL_RIS1_PBE11_SET                                    0x00000800U
#define LRFDDBELL_RIS1_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE10                                        0x00000400U
#define LRFDDBELL_RIS1_PBE10_M                                      0x00000400U
#define LRFDDBELL_RIS1_PBE10_S                                              10U
#define LRFDDBELL_RIS1_PBE10_SET                                    0x00000400U
#define LRFDDBELL_RIS1_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE9                                         0x00000200U
#define LRFDDBELL_RIS1_PBE9_M                                       0x00000200U
#define LRFDDBELL_RIS1_PBE9_S                                                9U
#define LRFDDBELL_RIS1_PBE9_SET                                     0x00000200U
#define LRFDDBELL_RIS1_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE8                                         0x00000100U
#define LRFDDBELL_RIS1_PBE8_M                                       0x00000100U
#define LRFDDBELL_RIS1_PBE8_S                                                8U
#define LRFDDBELL_RIS1_PBE8_SET                                     0x00000100U
#define LRFDDBELL_RIS1_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE7                                         0x00000080U
#define LRFDDBELL_RIS1_PBE7_M                                       0x00000080U
#define LRFDDBELL_RIS1_PBE7_S                                                7U
#define LRFDDBELL_RIS1_PBE7_SET                                     0x00000080U
#define LRFDDBELL_RIS1_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE6                                         0x00000040U
#define LRFDDBELL_RIS1_PBE6_M                                       0x00000040U
#define LRFDDBELL_RIS1_PBE6_S                                                6U
#define LRFDDBELL_RIS1_PBE6_SET                                     0x00000040U
#define LRFDDBELL_RIS1_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE5                                         0x00000020U
#define LRFDDBELL_RIS1_PBE5_M                                       0x00000020U
#define LRFDDBELL_RIS1_PBE5_S                                                5U
#define LRFDDBELL_RIS1_PBE5_SET                                     0x00000020U
#define LRFDDBELL_RIS1_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE4                                         0x00000010U
#define LRFDDBELL_RIS1_PBE4_M                                       0x00000010U
#define LRFDDBELL_RIS1_PBE4_S                                                4U
#define LRFDDBELL_RIS1_PBE4_SET                                     0x00000010U
#define LRFDDBELL_RIS1_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE3                                         0x00000008U
#define LRFDDBELL_RIS1_PBE3_M                                       0x00000008U
#define LRFDDBELL_RIS1_PBE3_S                                                3U
#define LRFDDBELL_RIS1_PBE3_SET                                     0x00000008U
#define LRFDDBELL_RIS1_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE2                                         0x00000004U
#define LRFDDBELL_RIS1_PBE2_M                                       0x00000004U
#define LRFDDBELL_RIS1_PBE2_S                                                2U
#define LRFDDBELL_RIS1_PBE2_SET                                     0x00000004U
#define LRFDDBELL_RIS1_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE1                                         0x00000002U
#define LRFDDBELL_RIS1_PBE1_M                                       0x00000002U
#define LRFDDBELL_RIS1_PBE1_S                                                1U
#define LRFDDBELL_RIS1_PBE1_SET                                     0x00000002U
#define LRFDDBELL_RIS1_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS1_PBE0                                         0x00000001U
#define LRFDDBELL_RIS1_PBE0_M                                       0x00000001U
#define LRFDDBELL_RIS1_PBE0_S                                                0U
#define LRFDDBELL_RIS1_PBE0_SET                                     0x00000001U
#define LRFDDBELL_RIS1_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_MIS1
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_SYSTIM2                                      0x80000000U
#define LRFDDBELL_MIS1_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_MIS1_SYSTIM2_S                                            31U
#define LRFDDBELL_MIS1_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_MIS1_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_SYSTIM1                                      0x40000000U
#define LRFDDBELL_MIS1_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_MIS1_SYSTIM1_S                                            30U
#define LRFDDBELL_MIS1_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_MIS1_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_SYSTIM0                                      0x20000000U
#define LRFDDBELL_MIS1_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_MIS1_SYSTIM0_S                                            29U
#define LRFDDBELL_MIS1_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_MIS1_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMDONE                                      0x10000000U
#define LRFDDBELL_MIS1_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_MIS1_MDMDONE_S                                            28U
#define LRFDDBELL_MIS1_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_MIS1_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMIN                                        0x08000000U
#define LRFDDBELL_MIS1_MDMIN_M                                      0x08000000U
#define LRFDDBELL_MIS1_MDMIN_S                                              27U
#define LRFDDBELL_MIS1_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_MIS1_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMOUT                                       0x04000000U
#define LRFDDBELL_MIS1_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_MIS1_MDMOUT_S                                             26U
#define LRFDDBELL_MIS1_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_MIS1_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_MIS1_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_MIS1_MDMSOFT2_S                                           25U
#define LRFDDBELL_MIS1_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_MIS1_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_MIS1_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_MIS1_MDMSOFT1_S                                           24U
#define LRFDDBELL_MIS1_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_MIS1_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_MIS1_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_MIS1_MDMSOFT0_S                                           23U
#define LRFDDBELL_MIS1_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_MIS1_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_RFEDONE                                      0x00400000U
#define LRFDDBELL_MIS1_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_MIS1_RFEDONE_S                                            22U
#define LRFDDBELL_MIS1_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_MIS1_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_RFESOFT1                                     0x00200000U
#define LRFDDBELL_MIS1_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_MIS1_RFESOFT1_S                                           21U
#define LRFDDBELL_MIS1_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_MIS1_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_RFESOFT0                                     0x00100000U
#define LRFDDBELL_MIS1_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_MIS1_RFESOFT0_S                                           20U
#define LRFDDBELL_MIS1_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_MIS1_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_LOCK                                         0x00080000U
#define LRFDDBELL_MIS1_LOCK_M                                       0x00080000U
#define LRFDDBELL_MIS1_LOCK_S                                               19U
#define LRFDDBELL_MIS1_LOCK_SET                                     0x00080000U
#define LRFDDBELL_MIS1_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_LOL                                          0x00040000U
#define LRFDDBELL_MIS1_LOL_M                                        0x00040000U
#define LRFDDBELL_MIS1_LOL_S                                                18U
#define LRFDDBELL_MIS1_LOL_SET                                      0x00040000U
#define LRFDDBELL_MIS1_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_TXFIFO                                       0x00020000U
#define LRFDDBELL_MIS1_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_MIS1_TXFIFO_S                                             17U
#define LRFDDBELL_MIS1_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_MIS1_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_RXFIFO                                       0x00010000U
#define LRFDDBELL_MIS1_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_MIS1_RXFIFO_S                                             16U
#define LRFDDBELL_MIS1_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_MIS1_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE15                                        0x00008000U
#define LRFDDBELL_MIS1_PBE15_M                                      0x00008000U
#define LRFDDBELL_MIS1_PBE15_S                                              15U
#define LRFDDBELL_MIS1_PBE15_SET                                    0x00008000U
#define LRFDDBELL_MIS1_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE14                                        0x00004000U
#define LRFDDBELL_MIS1_PBE14_M                                      0x00004000U
#define LRFDDBELL_MIS1_PBE14_S                                              14U
#define LRFDDBELL_MIS1_PBE14_SET                                    0x00004000U
#define LRFDDBELL_MIS1_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE13                                        0x00002000U
#define LRFDDBELL_MIS1_PBE13_M                                      0x00002000U
#define LRFDDBELL_MIS1_PBE13_S                                              13U
#define LRFDDBELL_MIS1_PBE13_SET                                    0x00002000U
#define LRFDDBELL_MIS1_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE12                                        0x00001000U
#define LRFDDBELL_MIS1_PBE12_M                                      0x00001000U
#define LRFDDBELL_MIS1_PBE12_S                                              12U
#define LRFDDBELL_MIS1_PBE12_SET                                    0x00001000U
#define LRFDDBELL_MIS1_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE11                                        0x00000800U
#define LRFDDBELL_MIS1_PBE11_M                                      0x00000800U
#define LRFDDBELL_MIS1_PBE11_S                                              11U
#define LRFDDBELL_MIS1_PBE11_SET                                    0x00000800U
#define LRFDDBELL_MIS1_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE10                                        0x00000400U
#define LRFDDBELL_MIS1_PBE10_M                                      0x00000400U
#define LRFDDBELL_MIS1_PBE10_S                                              10U
#define LRFDDBELL_MIS1_PBE10_SET                                    0x00000400U
#define LRFDDBELL_MIS1_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE9                                         0x00000200U
#define LRFDDBELL_MIS1_PBE9_M                                       0x00000200U
#define LRFDDBELL_MIS1_PBE9_S                                                9U
#define LRFDDBELL_MIS1_PBE9_SET                                     0x00000200U
#define LRFDDBELL_MIS1_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE8                                         0x00000100U
#define LRFDDBELL_MIS1_PBE8_M                                       0x00000100U
#define LRFDDBELL_MIS1_PBE8_S                                                8U
#define LRFDDBELL_MIS1_PBE8_SET                                     0x00000100U
#define LRFDDBELL_MIS1_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE7                                         0x00000080U
#define LRFDDBELL_MIS1_PBE7_M                                       0x00000080U
#define LRFDDBELL_MIS1_PBE7_S                                                7U
#define LRFDDBELL_MIS1_PBE7_SET                                     0x00000080U
#define LRFDDBELL_MIS1_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE6                                         0x00000040U
#define LRFDDBELL_MIS1_PBE6_M                                       0x00000040U
#define LRFDDBELL_MIS1_PBE6_S                                                6U
#define LRFDDBELL_MIS1_PBE6_SET                                     0x00000040U
#define LRFDDBELL_MIS1_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE5                                         0x00000020U
#define LRFDDBELL_MIS1_PBE5_M                                       0x00000020U
#define LRFDDBELL_MIS1_PBE5_S                                                5U
#define LRFDDBELL_MIS1_PBE5_SET                                     0x00000020U
#define LRFDDBELL_MIS1_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE4                                         0x00000010U
#define LRFDDBELL_MIS1_PBE4_M                                       0x00000010U
#define LRFDDBELL_MIS1_PBE4_S                                                4U
#define LRFDDBELL_MIS1_PBE4_SET                                     0x00000010U
#define LRFDDBELL_MIS1_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE3                                         0x00000008U
#define LRFDDBELL_MIS1_PBE3_M                                       0x00000008U
#define LRFDDBELL_MIS1_PBE3_S                                                3U
#define LRFDDBELL_MIS1_PBE3_SET                                     0x00000008U
#define LRFDDBELL_MIS1_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE2                                         0x00000004U
#define LRFDDBELL_MIS1_PBE2_M                                       0x00000004U
#define LRFDDBELL_MIS1_PBE2_S                                                2U
#define LRFDDBELL_MIS1_PBE2_SET                                     0x00000004U
#define LRFDDBELL_MIS1_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE1                                         0x00000002U
#define LRFDDBELL_MIS1_PBE1_M                                       0x00000002U
#define LRFDDBELL_MIS1_PBE1_S                                                1U
#define LRFDDBELL_MIS1_PBE1_SET                                     0x00000002U
#define LRFDDBELL_MIS1_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS1_PBE0                                         0x00000001U
#define LRFDDBELL_MIS1_PBE0_M                                       0x00000001U
#define LRFDDBELL_MIS1_PBE0_S                                                0U
#define LRFDDBELL_MIS1_PBE0_SET                                     0x00000001U
#define LRFDDBELL_MIS1_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ISET1
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ISET1_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ISET1_SYSTIM2_S                                           31U
#define LRFDDBELL_ISET1_SYSTIM2_SET                                 0x80000000U
#define LRFDDBELL_ISET1_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ISET1_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ISET1_SYSTIM1_S                                           30U
#define LRFDDBELL_ISET1_SYSTIM1_SET                                 0x40000000U
#define LRFDDBELL_ISET1_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ISET1_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ISET1_SYSTIM0_S                                           29U
#define LRFDDBELL_ISET1_SYSTIM0_SET                                 0x20000000U
#define LRFDDBELL_ISET1_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMDONE                                     0x10000000U
#define LRFDDBELL_ISET1_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ISET1_MDMDONE_S                                           28U
#define LRFDDBELL_ISET1_MDMDONE_SET                                 0x10000000U
#define LRFDDBELL_ISET1_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMIN                                       0x08000000U
#define LRFDDBELL_ISET1_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ISET1_MDMIN_S                                             27U
#define LRFDDBELL_ISET1_MDMIN_SET                                   0x08000000U
#define LRFDDBELL_ISET1_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMOUT                                      0x04000000U
#define LRFDDBELL_ISET1_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ISET1_MDMOUT_S                                            26U
#define LRFDDBELL_ISET1_MDMOUT_SET                                  0x04000000U
#define LRFDDBELL_ISET1_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ISET1_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ISET1_MDMSOFT2_S                                          25U
#define LRFDDBELL_ISET1_MDMSOFT2_SET                                0x02000000U
#define LRFDDBELL_ISET1_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ISET1_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ISET1_MDMSOFT1_S                                          24U
#define LRFDDBELL_ISET1_MDMSOFT1_SET                                0x01000000U
#define LRFDDBELL_ISET1_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ISET1_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ISET1_MDMSOFT0_S                                          23U
#define LRFDDBELL_ISET1_MDMSOFT0_SET                                0x00800000U
#define LRFDDBELL_ISET1_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_RFEDONE                                     0x00400000U
#define LRFDDBELL_ISET1_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ISET1_RFEDONE_S                                           22U
#define LRFDDBELL_ISET1_RFEDONE_SET                                 0x00400000U
#define LRFDDBELL_ISET1_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ISET1_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ISET1_RFESOFT1_S                                          21U
#define LRFDDBELL_ISET1_RFESOFT1_SET                                0x00200000U
#define LRFDDBELL_ISET1_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ISET1_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ISET1_RFESOFT0_S                                          20U
#define LRFDDBELL_ISET1_RFESOFT0_SET                                0x00100000U
#define LRFDDBELL_ISET1_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_LOCK                                        0x00080000U
#define LRFDDBELL_ISET1_LOCK_M                                      0x00080000U
#define LRFDDBELL_ISET1_LOCK_S                                              19U
#define LRFDDBELL_ISET1_LOCK_SET                                    0x00080000U
#define LRFDDBELL_ISET1_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_LOL                                         0x00040000U
#define LRFDDBELL_ISET1_LOL_M                                       0x00040000U
#define LRFDDBELL_ISET1_LOL_S                                               18U
#define LRFDDBELL_ISET1_LOL_SET                                     0x00040000U
#define LRFDDBELL_ISET1_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_TXFIFO                                      0x00020000U
#define LRFDDBELL_ISET1_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ISET1_TXFIFO_S                                            17U
#define LRFDDBELL_ISET1_TXFIFO_SET                                  0x00020000U
#define LRFDDBELL_ISET1_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_RXFIFO                                      0x00010000U
#define LRFDDBELL_ISET1_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ISET1_RXFIFO_S                                            16U
#define LRFDDBELL_ISET1_RXFIFO_SET                                  0x00010000U
#define LRFDDBELL_ISET1_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE15                                       0x00008000U
#define LRFDDBELL_ISET1_PBE15_M                                     0x00008000U
#define LRFDDBELL_ISET1_PBE15_S                                             15U
#define LRFDDBELL_ISET1_PBE15_SET                                   0x00008000U
#define LRFDDBELL_ISET1_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE14                                       0x00004000U
#define LRFDDBELL_ISET1_PBE14_M                                     0x00004000U
#define LRFDDBELL_ISET1_PBE14_S                                             14U
#define LRFDDBELL_ISET1_PBE14_SET                                   0x00004000U
#define LRFDDBELL_ISET1_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE13                                       0x00002000U
#define LRFDDBELL_ISET1_PBE13_M                                     0x00002000U
#define LRFDDBELL_ISET1_PBE13_S                                             13U
#define LRFDDBELL_ISET1_PBE13_SET                                   0x00002000U
#define LRFDDBELL_ISET1_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE12                                       0x00001000U
#define LRFDDBELL_ISET1_PBE12_M                                     0x00001000U
#define LRFDDBELL_ISET1_PBE12_S                                             12U
#define LRFDDBELL_ISET1_PBE12_SET                                   0x00001000U
#define LRFDDBELL_ISET1_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE11                                       0x00000800U
#define LRFDDBELL_ISET1_PBE11_M                                     0x00000800U
#define LRFDDBELL_ISET1_PBE11_S                                             11U
#define LRFDDBELL_ISET1_PBE11_SET                                   0x00000800U
#define LRFDDBELL_ISET1_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE10                                       0x00000400U
#define LRFDDBELL_ISET1_PBE10_M                                     0x00000400U
#define LRFDDBELL_ISET1_PBE10_S                                             10U
#define LRFDDBELL_ISET1_PBE10_SET                                   0x00000400U
#define LRFDDBELL_ISET1_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE9                                        0x00000200U
#define LRFDDBELL_ISET1_PBE9_M                                      0x00000200U
#define LRFDDBELL_ISET1_PBE9_S                                               9U
#define LRFDDBELL_ISET1_PBE9_SET                                    0x00000200U
#define LRFDDBELL_ISET1_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE8                                        0x00000100U
#define LRFDDBELL_ISET1_PBE8_M                                      0x00000100U
#define LRFDDBELL_ISET1_PBE8_S                                               8U
#define LRFDDBELL_ISET1_PBE8_SET                                    0x00000100U
#define LRFDDBELL_ISET1_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE7                                        0x00000080U
#define LRFDDBELL_ISET1_PBE7_M                                      0x00000080U
#define LRFDDBELL_ISET1_PBE7_S                                               7U
#define LRFDDBELL_ISET1_PBE7_SET                                    0x00000080U
#define LRFDDBELL_ISET1_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE6                                        0x00000040U
#define LRFDDBELL_ISET1_PBE6_M                                      0x00000040U
#define LRFDDBELL_ISET1_PBE6_S                                               6U
#define LRFDDBELL_ISET1_PBE6_SET                                    0x00000040U
#define LRFDDBELL_ISET1_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE5                                        0x00000020U
#define LRFDDBELL_ISET1_PBE5_M                                      0x00000020U
#define LRFDDBELL_ISET1_PBE5_S                                               5U
#define LRFDDBELL_ISET1_PBE5_SET                                    0x00000020U
#define LRFDDBELL_ISET1_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE4                                        0x00000010U
#define LRFDDBELL_ISET1_PBE4_M                                      0x00000010U
#define LRFDDBELL_ISET1_PBE4_S                                               4U
#define LRFDDBELL_ISET1_PBE4_SET                                    0x00000010U
#define LRFDDBELL_ISET1_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE3                                        0x00000008U
#define LRFDDBELL_ISET1_PBE3_M                                      0x00000008U
#define LRFDDBELL_ISET1_PBE3_S                                               3U
#define LRFDDBELL_ISET1_PBE3_SET                                    0x00000008U
#define LRFDDBELL_ISET1_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE2                                        0x00000004U
#define LRFDDBELL_ISET1_PBE2_M                                      0x00000004U
#define LRFDDBELL_ISET1_PBE2_S                                               2U
#define LRFDDBELL_ISET1_PBE2_SET                                    0x00000004U
#define LRFDDBELL_ISET1_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE1                                        0x00000002U
#define LRFDDBELL_ISET1_PBE1_M                                      0x00000002U
#define LRFDDBELL_ISET1_PBE1_S                                               1U
#define LRFDDBELL_ISET1_PBE1_SET                                    0x00000002U
#define LRFDDBELL_ISET1_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET1_PBE0                                        0x00000001U
#define LRFDDBELL_ISET1_PBE0_M                                      0x00000001U
#define LRFDDBELL_ISET1_PBE0_S                                               0U
#define LRFDDBELL_ISET1_PBE0_SET                                    0x00000001U
#define LRFDDBELL_ISET1_PBE0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ICLR1
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ICLR1_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ICLR1_SYSTIM2_S                                           31U
#define LRFDDBELL_ICLR1_SYSTIM2_CLR                                 0x80000000U
#define LRFDDBELL_ICLR1_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ICLR1_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ICLR1_SYSTIM1_S                                           30U
#define LRFDDBELL_ICLR1_SYSTIM1_CLR                                 0x40000000U
#define LRFDDBELL_ICLR1_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ICLR1_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ICLR1_SYSTIM0_S                                           29U
#define LRFDDBELL_ICLR1_SYSTIM0_CLR                                 0x20000000U
#define LRFDDBELL_ICLR1_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMDONE                                     0x10000000U
#define LRFDDBELL_ICLR1_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ICLR1_MDMDONE_S                                           28U
#define LRFDDBELL_ICLR1_MDMDONE_CLR                                 0x10000000U
#define LRFDDBELL_ICLR1_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMIN                                       0x08000000U
#define LRFDDBELL_ICLR1_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ICLR1_MDMIN_S                                             27U
#define LRFDDBELL_ICLR1_MDMIN_CLR                                   0x08000000U
#define LRFDDBELL_ICLR1_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMOUT                                      0x04000000U
#define LRFDDBELL_ICLR1_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ICLR1_MDMOUT_S                                            26U
#define LRFDDBELL_ICLR1_MDMOUT_CLR                                  0x04000000U
#define LRFDDBELL_ICLR1_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ICLR1_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ICLR1_MDMSOFT2_S                                          25U
#define LRFDDBELL_ICLR1_MDMSOFT2_CLR                                0x02000000U
#define LRFDDBELL_ICLR1_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ICLR1_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ICLR1_MDMSOFT1_S                                          24U
#define LRFDDBELL_ICLR1_MDMSOFT1_CLR                                0x01000000U
#define LRFDDBELL_ICLR1_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ICLR1_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ICLR1_MDMSOFT0_S                                          23U
#define LRFDDBELL_ICLR1_MDMSOFT0_CLR                                0x00800000U
#define LRFDDBELL_ICLR1_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_RFEDONE                                     0x00400000U
#define LRFDDBELL_ICLR1_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ICLR1_RFEDONE_S                                           22U
#define LRFDDBELL_ICLR1_RFEDONE_CLR                                 0x00400000U
#define LRFDDBELL_ICLR1_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ICLR1_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ICLR1_RFESOFT1_S                                          21U
#define LRFDDBELL_ICLR1_RFESOFT1_CLR                                0x00200000U
#define LRFDDBELL_ICLR1_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ICLR1_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ICLR1_RFESOFT0_S                                          20U
#define LRFDDBELL_ICLR1_RFESOFT0_CLR                                0x00100000U
#define LRFDDBELL_ICLR1_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_LOCK                                        0x00080000U
#define LRFDDBELL_ICLR1_LOCK_M                                      0x00080000U
#define LRFDDBELL_ICLR1_LOCK_S                                              19U
#define LRFDDBELL_ICLR1_LOCK_CLR                                    0x00080000U
#define LRFDDBELL_ICLR1_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_LOL                                         0x00040000U
#define LRFDDBELL_ICLR1_LOL_M                                       0x00040000U
#define LRFDDBELL_ICLR1_LOL_S                                               18U
#define LRFDDBELL_ICLR1_LOL_CLR                                     0x00040000U
#define LRFDDBELL_ICLR1_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_TXFIFO                                      0x00020000U
#define LRFDDBELL_ICLR1_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ICLR1_TXFIFO_S                                            17U
#define LRFDDBELL_ICLR1_TXFIFO_CLR                                  0x00020000U
#define LRFDDBELL_ICLR1_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_RXFIFO                                      0x00010000U
#define LRFDDBELL_ICLR1_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ICLR1_RXFIFO_S                                            16U
#define LRFDDBELL_ICLR1_RXFIFO_CLR                                  0x00010000U
#define LRFDDBELL_ICLR1_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE15                                       0x00008000U
#define LRFDDBELL_ICLR1_PBE15_M                                     0x00008000U
#define LRFDDBELL_ICLR1_PBE15_S                                             15U
#define LRFDDBELL_ICLR1_PBE15_CLR                                   0x00008000U
#define LRFDDBELL_ICLR1_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE14                                       0x00004000U
#define LRFDDBELL_ICLR1_PBE14_M                                     0x00004000U
#define LRFDDBELL_ICLR1_PBE14_S                                             14U
#define LRFDDBELL_ICLR1_PBE14_CLR                                   0x00004000U
#define LRFDDBELL_ICLR1_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE13                                       0x00002000U
#define LRFDDBELL_ICLR1_PBE13_M                                     0x00002000U
#define LRFDDBELL_ICLR1_PBE13_S                                             13U
#define LRFDDBELL_ICLR1_PBE13_CLR                                   0x00002000U
#define LRFDDBELL_ICLR1_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE12                                       0x00001000U
#define LRFDDBELL_ICLR1_PBE12_M                                     0x00001000U
#define LRFDDBELL_ICLR1_PBE12_S                                             12U
#define LRFDDBELL_ICLR1_PBE12_CLR                                   0x00001000U
#define LRFDDBELL_ICLR1_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE11                                       0x00000800U
#define LRFDDBELL_ICLR1_PBE11_M                                     0x00000800U
#define LRFDDBELL_ICLR1_PBE11_S                                             11U
#define LRFDDBELL_ICLR1_PBE11_CLR                                   0x00000800U
#define LRFDDBELL_ICLR1_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE10                                       0x00000400U
#define LRFDDBELL_ICLR1_PBE10_M                                     0x00000400U
#define LRFDDBELL_ICLR1_PBE10_S                                             10U
#define LRFDDBELL_ICLR1_PBE10_CLR                                   0x00000400U
#define LRFDDBELL_ICLR1_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE9                                        0x00000200U
#define LRFDDBELL_ICLR1_PBE9_M                                      0x00000200U
#define LRFDDBELL_ICLR1_PBE9_S                                               9U
#define LRFDDBELL_ICLR1_PBE9_CLR                                    0x00000200U
#define LRFDDBELL_ICLR1_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE8                                        0x00000100U
#define LRFDDBELL_ICLR1_PBE8_M                                      0x00000100U
#define LRFDDBELL_ICLR1_PBE8_S                                               8U
#define LRFDDBELL_ICLR1_PBE8_CLR                                    0x00000100U
#define LRFDDBELL_ICLR1_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE7                                        0x00000080U
#define LRFDDBELL_ICLR1_PBE7_M                                      0x00000080U
#define LRFDDBELL_ICLR1_PBE7_S                                               7U
#define LRFDDBELL_ICLR1_PBE7_CLR                                    0x00000080U
#define LRFDDBELL_ICLR1_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE6                                        0x00000040U
#define LRFDDBELL_ICLR1_PBE6_M                                      0x00000040U
#define LRFDDBELL_ICLR1_PBE6_S                                               6U
#define LRFDDBELL_ICLR1_PBE6_CLR                                    0x00000040U
#define LRFDDBELL_ICLR1_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE5                                        0x00000020U
#define LRFDDBELL_ICLR1_PBE5_M                                      0x00000020U
#define LRFDDBELL_ICLR1_PBE5_S                                               5U
#define LRFDDBELL_ICLR1_PBE5_CLR                                    0x00000020U
#define LRFDDBELL_ICLR1_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE4                                        0x00000010U
#define LRFDDBELL_ICLR1_PBE4_M                                      0x00000010U
#define LRFDDBELL_ICLR1_PBE4_S                                               4U
#define LRFDDBELL_ICLR1_PBE4_CLR                                    0x00000010U
#define LRFDDBELL_ICLR1_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE3                                        0x00000008U
#define LRFDDBELL_ICLR1_PBE3_M                                      0x00000008U
#define LRFDDBELL_ICLR1_PBE3_S                                               3U
#define LRFDDBELL_ICLR1_PBE3_CLR                                    0x00000008U
#define LRFDDBELL_ICLR1_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE2                                        0x00000004U
#define LRFDDBELL_ICLR1_PBE2_M                                      0x00000004U
#define LRFDDBELL_ICLR1_PBE2_S                                               2U
#define LRFDDBELL_ICLR1_PBE2_CLR                                    0x00000004U
#define LRFDDBELL_ICLR1_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE1                                        0x00000002U
#define LRFDDBELL_ICLR1_PBE1_M                                      0x00000002U
#define LRFDDBELL_ICLR1_PBE1_S                                               1U
#define LRFDDBELL_ICLR1_PBE1_CLR                                    0x00000002U
#define LRFDDBELL_ICLR1_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR1_PBE0                                        0x00000001U
#define LRFDDBELL_ICLR1_PBE0_M                                      0x00000001U
#define LRFDDBELL_ICLR1_PBE0_S                                               0U
#define LRFDDBELL_ICLR1_PBE0_CLR                                    0x00000001U
#define LRFDDBELL_ICLR1_PBE0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_IMASK2
//
//*****************************************************************************
// Field:    [30] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_SYSTIM2                                    0x40000000U
#define LRFDDBELL_IMASK2_SYSTIM2_M                                  0x40000000U
#define LRFDDBELL_IMASK2_SYSTIM2_S                                          30U
#define LRFDDBELL_IMASK2_SYSTIM2_EN                                 0x40000000U
#define LRFDDBELL_IMASK2_SYSTIM2_DIS                                0x00000000U

// Field:    [29] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_SYSTIM1                                    0x20000000U
#define LRFDDBELL_IMASK2_SYSTIM1_M                                  0x20000000U
#define LRFDDBELL_IMASK2_SYSTIM1_S                                          29U
#define LRFDDBELL_IMASK2_SYSTIM1_EN                                 0x20000000U
#define LRFDDBELL_IMASK2_SYSTIM1_DIS                                0x00000000U

// Field:    [28] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_SYSTIM0                                    0x10000000U
#define LRFDDBELL_IMASK2_SYSTIM0_M                                  0x10000000U
#define LRFDDBELL_IMASK2_SYSTIM0_S                                          28U
#define LRFDDBELL_IMASK2_SYSTIM0_EN                                 0x10000000U
#define LRFDDBELL_IMASK2_SYSTIM0_DIS                                0x00000000U

// Field:    [27] MDMDONE
//
// MDMDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMDONE                                    0x08000000U
#define LRFDDBELL_IMASK2_MDMDONE_M                                  0x08000000U
#define LRFDDBELL_IMASK2_MDMDONE_S                                          27U
#define LRFDDBELL_IMASK2_MDMDONE_EN                                 0x08000000U
#define LRFDDBELL_IMASK2_MDMDONE_DIS                                0x00000000U

// Field:    [26] MDMIN
//
// MDMIN event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMIN                                      0x04000000U
#define LRFDDBELL_IMASK2_MDMIN_M                                    0x04000000U
#define LRFDDBELL_IMASK2_MDMIN_S                                            26U
#define LRFDDBELL_IMASK2_MDMIN_EN                                   0x04000000U
#define LRFDDBELL_IMASK2_MDMIN_DIS                                  0x00000000U

// Field:    [25] MDMOUT
//
// MDMOUT event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMOUT                                     0x02000000U
#define LRFDDBELL_IMASK2_MDMOUT_M                                   0x02000000U
#define LRFDDBELL_IMASK2_MDMOUT_S                                           25U
#define LRFDDBELL_IMASK2_MDMOUT_EN                                  0x02000000U
#define LRFDDBELL_IMASK2_MDMOUT_DIS                                 0x00000000U

// Field:    [24] MDMSOFT2
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMSOFT2                                   0x01000000U
#define LRFDDBELL_IMASK2_MDMSOFT2_M                                 0x01000000U
#define LRFDDBELL_IMASK2_MDMSOFT2_S                                         24U
#define LRFDDBELL_IMASK2_MDMSOFT2_EN                                0x01000000U
#define LRFDDBELL_IMASK2_MDMSOFT2_DIS                               0x00000000U

// Field:    [23] MDMSOFT1
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMSOFT1                                   0x00800000U
#define LRFDDBELL_IMASK2_MDMSOFT1_M                                 0x00800000U
#define LRFDDBELL_IMASK2_MDMSOFT1_S                                         23U
#define LRFDDBELL_IMASK2_MDMSOFT1_EN                                0x00800000U
#define LRFDDBELL_IMASK2_MDMSOFT1_DIS                               0x00000000U

// Field:    [22] MDMSOFT0
//
// MDMSOFT2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_MDMSOFT0                                   0x00400000U
#define LRFDDBELL_IMASK2_MDMSOFT0_M                                 0x00400000U
#define LRFDDBELL_IMASK2_MDMSOFT0_S                                         22U
#define LRFDDBELL_IMASK2_MDMSOFT0_EN                                0x00400000U
#define LRFDDBELL_IMASK2_MDMSOFT0_DIS                               0x00000000U

// Field:    [21] RFEDONE
//
// RFEDONE event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_RFEDONE                                    0x00200000U
#define LRFDDBELL_IMASK2_RFEDONE_M                                  0x00200000U
#define LRFDDBELL_IMASK2_RFEDONE_S                                          21U
#define LRFDDBELL_IMASK2_RFEDONE_EN                                 0x00200000U
#define LRFDDBELL_IMASK2_RFEDONE_DIS                                0x00000000U

// Field:    [20] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_RFESOFT1                                   0x00100000U
#define LRFDDBELL_IMASK2_RFESOFT1_M                                 0x00100000U
#define LRFDDBELL_IMASK2_RFESOFT1_S                                         20U
#define LRFDDBELL_IMASK2_RFESOFT1_EN                                0x00100000U
#define LRFDDBELL_IMASK2_RFESOFT1_DIS                               0x00000000U

// Field:    [19] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_RFESOFT0                                   0x00080000U
#define LRFDDBELL_IMASK2_RFESOFT0_M                                 0x00080000U
#define LRFDDBELL_IMASK2_RFESOFT0_S                                         19U
#define LRFDDBELL_IMASK2_RFESOFT0_EN                                0x00080000U
#define LRFDDBELL_IMASK2_RFESOFT0_DIS                               0x00000000U

// Field:    [18] LOCK
//
// LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_LOCK                                       0x00040000U
#define LRFDDBELL_IMASK2_LOCK_M                                     0x00040000U
#define LRFDDBELL_IMASK2_LOCK_S                                             18U
#define LRFDDBELL_IMASK2_LOCK_EN                                    0x00040000U
#define LRFDDBELL_IMASK2_LOCK_DIS                                   0x00000000U

// Field:    [17] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_LOL                                        0x00020000U
#define LRFDDBELL_IMASK2_LOL_M                                      0x00020000U
#define LRFDDBELL_IMASK2_LOL_S                                              17U
#define LRFDDBELL_IMASK2_LOL_EN                                     0x00020000U
#define LRFDDBELL_IMASK2_LOL_DIS                                    0x00000000U

// Field:    [16] TXFIFO
//
// TXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_TXFIFO                                     0x00010000U
#define LRFDDBELL_IMASK2_TXFIFO_M                                   0x00010000U
#define LRFDDBELL_IMASK2_TXFIFO_S                                           16U
#define LRFDDBELL_IMASK2_TXFIFO_EN                                  0x00010000U
#define LRFDDBELL_IMASK2_TXFIFO_DIS                                 0x00000000U

// Field:    [15] RXFIFO
//
// RXFIFO event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_RXFIFO                                     0x00008000U
#define LRFDDBELL_IMASK2_RXFIFO_M                                   0x00008000U
#define LRFDDBELL_IMASK2_RXFIFO_S                                           15U
#define LRFDDBELL_IMASK2_RXFIFO_EN                                  0x00008000U
#define LRFDDBELL_IMASK2_RXFIFO_DIS                                 0x00000000U

// Field:    [14] PBE15
//
// PBE15 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE15                                      0x00004000U
#define LRFDDBELL_IMASK2_PBE15_M                                    0x00004000U
#define LRFDDBELL_IMASK2_PBE15_S                                            14U
#define LRFDDBELL_IMASK2_PBE15_EN                                   0x00004000U
#define LRFDDBELL_IMASK2_PBE15_DIS                                  0x00000000U

// Field:    [13] PBE14
//
// PBE14 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE14                                      0x00002000U
#define LRFDDBELL_IMASK2_PBE14_M                                    0x00002000U
#define LRFDDBELL_IMASK2_PBE14_S                                            13U
#define LRFDDBELL_IMASK2_PBE14_EN                                   0x00002000U
#define LRFDDBELL_IMASK2_PBE14_DIS                                  0x00000000U

// Field:    [12] PBE13
//
// PBE13 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE13                                      0x00001000U
#define LRFDDBELL_IMASK2_PBE13_M                                    0x00001000U
#define LRFDDBELL_IMASK2_PBE13_S                                            12U
#define LRFDDBELL_IMASK2_PBE13_EN                                   0x00001000U
#define LRFDDBELL_IMASK2_PBE13_DIS                                  0x00000000U

// Field:    [11] PBE12
//
// PBE12 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE12                                      0x00000800U
#define LRFDDBELL_IMASK2_PBE12_M                                    0x00000800U
#define LRFDDBELL_IMASK2_PBE12_S                                            11U
#define LRFDDBELL_IMASK2_PBE12_EN                                   0x00000800U
#define LRFDDBELL_IMASK2_PBE12_DIS                                  0x00000000U

// Field:    [10] PBE11
//
// PBE11 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE11                                      0x00000400U
#define LRFDDBELL_IMASK2_PBE11_M                                    0x00000400U
#define LRFDDBELL_IMASK2_PBE11_S                                            10U
#define LRFDDBELL_IMASK2_PBE11_EN                                   0x00000400U
#define LRFDDBELL_IMASK2_PBE11_DIS                                  0x00000000U

// Field:     [9] PBE10
//
// PBE10 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE10                                      0x00000200U
#define LRFDDBELL_IMASK2_PBE10_M                                    0x00000200U
#define LRFDDBELL_IMASK2_PBE10_S                                             9U
#define LRFDDBELL_IMASK2_PBE10_EN                                   0x00000200U
#define LRFDDBELL_IMASK2_PBE10_DIS                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE8                                       0x00000100U
#define LRFDDBELL_IMASK2_PBE8_M                                     0x00000100U
#define LRFDDBELL_IMASK2_PBE8_S                                              8U
#define LRFDDBELL_IMASK2_PBE8_EN                                    0x00000100U
#define LRFDDBELL_IMASK2_PBE8_DIS                                   0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE7                                       0x00000080U
#define LRFDDBELL_IMASK2_PBE7_M                                     0x00000080U
#define LRFDDBELL_IMASK2_PBE7_S                                              7U
#define LRFDDBELL_IMASK2_PBE7_EN                                    0x00000080U
#define LRFDDBELL_IMASK2_PBE7_DIS                                   0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE6                                       0x00000040U
#define LRFDDBELL_IMASK2_PBE6_M                                     0x00000040U
#define LRFDDBELL_IMASK2_PBE6_S                                              6U
#define LRFDDBELL_IMASK2_PBE6_EN                                    0x00000040U
#define LRFDDBELL_IMASK2_PBE6_DIS                                   0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE5                                       0x00000020U
#define LRFDDBELL_IMASK2_PBE5_M                                     0x00000020U
#define LRFDDBELL_IMASK2_PBE5_S                                              5U
#define LRFDDBELL_IMASK2_PBE5_EN                                    0x00000020U
#define LRFDDBELL_IMASK2_PBE5_DIS                                   0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE4                                       0x00000010U
#define LRFDDBELL_IMASK2_PBE4_M                                     0x00000010U
#define LRFDDBELL_IMASK2_PBE4_S                                              4U
#define LRFDDBELL_IMASK2_PBE4_EN                                    0x00000010U
#define LRFDDBELL_IMASK2_PBE4_DIS                                   0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE3                                       0x00000008U
#define LRFDDBELL_IMASK2_PBE3_M                                     0x00000008U
#define LRFDDBELL_IMASK2_PBE3_S                                              3U
#define LRFDDBELL_IMASK2_PBE3_EN                                    0x00000008U
#define LRFDDBELL_IMASK2_PBE3_DIS                                   0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE2                                       0x00000004U
#define LRFDDBELL_IMASK2_PBE2_M                                     0x00000004U
#define LRFDDBELL_IMASK2_PBE2_S                                              2U
#define LRFDDBELL_IMASK2_PBE2_EN                                    0x00000004U
#define LRFDDBELL_IMASK2_PBE2_DIS                                   0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE1                                       0x00000002U
#define LRFDDBELL_IMASK2_PBE1_M                                     0x00000002U
#define LRFDDBELL_IMASK2_PBE1_S                                              1U
#define LRFDDBELL_IMASK2_PBE1_EN                                    0x00000002U
#define LRFDDBELL_IMASK2_PBE1_DIS                                   0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// EN                       Enable interrupt mask
// DIS                      Disable interrupt mask
#define LRFDDBELL_IMASK2_PBE0                                       0x00000001U
#define LRFDDBELL_IMASK2_PBE0_M                                     0x00000001U
#define LRFDDBELL_IMASK2_PBE0_S                                              0U
#define LRFDDBELL_IMASK2_PBE0_EN                                    0x00000001U
#define LRFDDBELL_IMASK2_PBE0_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_RIS2
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_SYSTIM2                                      0x80000000U
#define LRFDDBELL_RIS2_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_RIS2_SYSTIM2_S                                            31U
#define LRFDDBELL_RIS2_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_RIS2_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_SYSTIM1                                      0x40000000U
#define LRFDDBELL_RIS2_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_RIS2_SYSTIM1_S                                            30U
#define LRFDDBELL_RIS2_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_RIS2_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_SYSTIM0                                      0x20000000U
#define LRFDDBELL_RIS2_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_RIS2_SYSTIM0_S                                            29U
#define LRFDDBELL_RIS2_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_RIS2_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMDONE                                      0x10000000U
#define LRFDDBELL_RIS2_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_RIS2_MDMDONE_S                                            28U
#define LRFDDBELL_RIS2_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_RIS2_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMIN                                        0x08000000U
#define LRFDDBELL_RIS2_MDMIN_M                                      0x08000000U
#define LRFDDBELL_RIS2_MDMIN_S                                              27U
#define LRFDDBELL_RIS2_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_RIS2_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMOUT                                       0x04000000U
#define LRFDDBELL_RIS2_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_RIS2_MDMOUT_S                                             26U
#define LRFDDBELL_RIS2_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_RIS2_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_RIS2_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_RIS2_MDMSOFT2_S                                           25U
#define LRFDDBELL_RIS2_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_RIS2_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_RIS2_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_RIS2_MDMSOFT1_S                                           24U
#define LRFDDBELL_RIS2_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_RIS2_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_RIS2_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_RIS2_MDMSOFT0_S                                           23U
#define LRFDDBELL_RIS2_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_RIS2_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_RFEDONE                                      0x00400000U
#define LRFDDBELL_RIS2_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_RIS2_RFEDONE_S                                            22U
#define LRFDDBELL_RIS2_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_RIS2_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_RFESOFT1                                     0x00200000U
#define LRFDDBELL_RIS2_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_RIS2_RFESOFT1_S                                           21U
#define LRFDDBELL_RIS2_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_RIS2_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_RFESOFT0                                     0x00100000U
#define LRFDDBELL_RIS2_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_RIS2_RFESOFT0_S                                           20U
#define LRFDDBELL_RIS2_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_RIS2_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_LOCK                                         0x00080000U
#define LRFDDBELL_RIS2_LOCK_M                                       0x00080000U
#define LRFDDBELL_RIS2_LOCK_S                                               19U
#define LRFDDBELL_RIS2_LOCK_SET                                     0x00080000U
#define LRFDDBELL_RIS2_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_LOL                                          0x00040000U
#define LRFDDBELL_RIS2_LOL_M                                        0x00040000U
#define LRFDDBELL_RIS2_LOL_S                                                18U
#define LRFDDBELL_RIS2_LOL_SET                                      0x00040000U
#define LRFDDBELL_RIS2_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_TXFIFO                                       0x00020000U
#define LRFDDBELL_RIS2_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_RIS2_TXFIFO_S                                             17U
#define LRFDDBELL_RIS2_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_RIS2_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_RXFIFO                                       0x00010000U
#define LRFDDBELL_RIS2_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_RIS2_RXFIFO_S                                             16U
#define LRFDDBELL_RIS2_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_RIS2_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE15                                        0x00008000U
#define LRFDDBELL_RIS2_PBE15_M                                      0x00008000U
#define LRFDDBELL_RIS2_PBE15_S                                              15U
#define LRFDDBELL_RIS2_PBE15_SET                                    0x00008000U
#define LRFDDBELL_RIS2_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE14                                        0x00004000U
#define LRFDDBELL_RIS2_PBE14_M                                      0x00004000U
#define LRFDDBELL_RIS2_PBE14_S                                              14U
#define LRFDDBELL_RIS2_PBE14_SET                                    0x00004000U
#define LRFDDBELL_RIS2_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE13                                        0x00002000U
#define LRFDDBELL_RIS2_PBE13_M                                      0x00002000U
#define LRFDDBELL_RIS2_PBE13_S                                              13U
#define LRFDDBELL_RIS2_PBE13_SET                                    0x00002000U
#define LRFDDBELL_RIS2_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE12                                        0x00001000U
#define LRFDDBELL_RIS2_PBE12_M                                      0x00001000U
#define LRFDDBELL_RIS2_PBE12_S                                              12U
#define LRFDDBELL_RIS2_PBE12_SET                                    0x00001000U
#define LRFDDBELL_RIS2_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE11                                        0x00000800U
#define LRFDDBELL_RIS2_PBE11_M                                      0x00000800U
#define LRFDDBELL_RIS2_PBE11_S                                              11U
#define LRFDDBELL_RIS2_PBE11_SET                                    0x00000800U
#define LRFDDBELL_RIS2_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE10                                        0x00000400U
#define LRFDDBELL_RIS2_PBE10_M                                      0x00000400U
#define LRFDDBELL_RIS2_PBE10_S                                              10U
#define LRFDDBELL_RIS2_PBE10_SET                                    0x00000400U
#define LRFDDBELL_RIS2_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE9                                         0x00000200U
#define LRFDDBELL_RIS2_PBE9_M                                       0x00000200U
#define LRFDDBELL_RIS2_PBE9_S                                                9U
#define LRFDDBELL_RIS2_PBE9_SET                                     0x00000200U
#define LRFDDBELL_RIS2_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE8                                         0x00000100U
#define LRFDDBELL_RIS2_PBE8_M                                       0x00000100U
#define LRFDDBELL_RIS2_PBE8_S                                                8U
#define LRFDDBELL_RIS2_PBE8_SET                                     0x00000100U
#define LRFDDBELL_RIS2_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE7                                         0x00000080U
#define LRFDDBELL_RIS2_PBE7_M                                       0x00000080U
#define LRFDDBELL_RIS2_PBE7_S                                                7U
#define LRFDDBELL_RIS2_PBE7_SET                                     0x00000080U
#define LRFDDBELL_RIS2_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE6                                         0x00000040U
#define LRFDDBELL_RIS2_PBE6_M                                       0x00000040U
#define LRFDDBELL_RIS2_PBE6_S                                                6U
#define LRFDDBELL_RIS2_PBE6_SET                                     0x00000040U
#define LRFDDBELL_RIS2_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE5                                         0x00000020U
#define LRFDDBELL_RIS2_PBE5_M                                       0x00000020U
#define LRFDDBELL_RIS2_PBE5_S                                                5U
#define LRFDDBELL_RIS2_PBE5_SET                                     0x00000020U
#define LRFDDBELL_RIS2_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE4                                         0x00000010U
#define LRFDDBELL_RIS2_PBE4_M                                       0x00000010U
#define LRFDDBELL_RIS2_PBE4_S                                                4U
#define LRFDDBELL_RIS2_PBE4_SET                                     0x00000010U
#define LRFDDBELL_RIS2_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE3                                         0x00000008U
#define LRFDDBELL_RIS2_PBE3_M                                       0x00000008U
#define LRFDDBELL_RIS2_PBE3_S                                                3U
#define LRFDDBELL_RIS2_PBE3_SET                                     0x00000008U
#define LRFDDBELL_RIS2_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE2                                         0x00000004U
#define LRFDDBELL_RIS2_PBE2_M                                       0x00000004U
#define LRFDDBELL_RIS2_PBE2_S                                                2U
#define LRFDDBELL_RIS2_PBE2_SET                                     0x00000004U
#define LRFDDBELL_RIS2_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE1                                         0x00000002U
#define LRFDDBELL_RIS2_PBE1_M                                       0x00000002U
#define LRFDDBELL_RIS2_PBE1_S                                                1U
#define LRFDDBELL_RIS2_PBE1_SET                                     0x00000002U
#define LRFDDBELL_RIS2_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_RIS2_PBE0                                         0x00000001U
#define LRFDDBELL_RIS2_PBE0_M                                       0x00000001U
#define LRFDDBELL_RIS2_PBE0_S                                                0U
#define LRFDDBELL_RIS2_PBE0_SET                                     0x00000001U
#define LRFDDBELL_RIS2_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_MIS2
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_SYSTIM2                                      0x80000000U
#define LRFDDBELL_MIS2_SYSTIM2_M                                    0x80000000U
#define LRFDDBELL_MIS2_SYSTIM2_S                                            31U
#define LRFDDBELL_MIS2_SYSTIM2_SET                                  0x80000000U
#define LRFDDBELL_MIS2_SYSTIM2_CLR                                  0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_SYSTIM1                                      0x40000000U
#define LRFDDBELL_MIS2_SYSTIM1_M                                    0x40000000U
#define LRFDDBELL_MIS2_SYSTIM1_S                                            30U
#define LRFDDBELL_MIS2_SYSTIM1_SET                                  0x40000000U
#define LRFDDBELL_MIS2_SYSTIM1_CLR                                  0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_SYSTIM0                                      0x20000000U
#define LRFDDBELL_MIS2_SYSTIM0_M                                    0x20000000U
#define LRFDDBELL_MIS2_SYSTIM0_S                                            29U
#define LRFDDBELL_MIS2_SYSTIM0_SET                                  0x20000000U
#define LRFDDBELL_MIS2_SYSTIM0_CLR                                  0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMDONE                                      0x10000000U
#define LRFDDBELL_MIS2_MDMDONE_M                                    0x10000000U
#define LRFDDBELL_MIS2_MDMDONE_S                                            28U
#define LRFDDBELL_MIS2_MDMDONE_SET                                  0x10000000U
#define LRFDDBELL_MIS2_MDMDONE_CLR                                  0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMIN                                        0x08000000U
#define LRFDDBELL_MIS2_MDMIN_M                                      0x08000000U
#define LRFDDBELL_MIS2_MDMIN_S                                              27U
#define LRFDDBELL_MIS2_MDMIN_SET                                    0x08000000U
#define LRFDDBELL_MIS2_MDMIN_CLR                                    0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMOUT                                       0x04000000U
#define LRFDDBELL_MIS2_MDMOUT_M                                     0x04000000U
#define LRFDDBELL_MIS2_MDMOUT_S                                             26U
#define LRFDDBELL_MIS2_MDMOUT_SET                                   0x04000000U
#define LRFDDBELL_MIS2_MDMOUT_CLR                                   0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMSOFT2                                     0x02000000U
#define LRFDDBELL_MIS2_MDMSOFT2_M                                   0x02000000U
#define LRFDDBELL_MIS2_MDMSOFT2_S                                           25U
#define LRFDDBELL_MIS2_MDMSOFT2_SET                                 0x02000000U
#define LRFDDBELL_MIS2_MDMSOFT2_CLR                                 0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMSOFT1                                     0x01000000U
#define LRFDDBELL_MIS2_MDMSOFT1_M                                   0x01000000U
#define LRFDDBELL_MIS2_MDMSOFT1_S                                           24U
#define LRFDDBELL_MIS2_MDMSOFT1_SET                                 0x01000000U
#define LRFDDBELL_MIS2_MDMSOFT1_CLR                                 0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_MDMSOFT0                                     0x00800000U
#define LRFDDBELL_MIS2_MDMSOFT0_M                                   0x00800000U
#define LRFDDBELL_MIS2_MDMSOFT0_S                                           23U
#define LRFDDBELL_MIS2_MDMSOFT0_SET                                 0x00800000U
#define LRFDDBELL_MIS2_MDMSOFT0_CLR                                 0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_RFEDONE                                      0x00400000U
#define LRFDDBELL_MIS2_RFEDONE_M                                    0x00400000U
#define LRFDDBELL_MIS2_RFEDONE_S                                            22U
#define LRFDDBELL_MIS2_RFEDONE_SET                                  0x00400000U
#define LRFDDBELL_MIS2_RFEDONE_CLR                                  0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_RFESOFT1                                     0x00200000U
#define LRFDDBELL_MIS2_RFESOFT1_M                                   0x00200000U
#define LRFDDBELL_MIS2_RFESOFT1_S                                           21U
#define LRFDDBELL_MIS2_RFESOFT1_SET                                 0x00200000U
#define LRFDDBELL_MIS2_RFESOFT1_CLR                                 0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_RFESOFT0                                     0x00100000U
#define LRFDDBELL_MIS2_RFESOFT0_M                                   0x00100000U
#define LRFDDBELL_MIS2_RFESOFT0_S                                           20U
#define LRFDDBELL_MIS2_RFESOFT0_SET                                 0x00100000U
#define LRFDDBELL_MIS2_RFESOFT0_CLR                                 0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_LOCK                                         0x00080000U
#define LRFDDBELL_MIS2_LOCK_M                                       0x00080000U
#define LRFDDBELL_MIS2_LOCK_S                                               19U
#define LRFDDBELL_MIS2_LOCK_SET                                     0x00080000U
#define LRFDDBELL_MIS2_LOCK_CLR                                     0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_LOL                                          0x00040000U
#define LRFDDBELL_MIS2_LOL_M                                        0x00040000U
#define LRFDDBELL_MIS2_LOL_S                                                18U
#define LRFDDBELL_MIS2_LOL_SET                                      0x00040000U
#define LRFDDBELL_MIS2_LOL_CLR                                      0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_TXFIFO                                       0x00020000U
#define LRFDDBELL_MIS2_TXFIFO_M                                     0x00020000U
#define LRFDDBELL_MIS2_TXFIFO_S                                             17U
#define LRFDDBELL_MIS2_TXFIFO_SET                                   0x00020000U
#define LRFDDBELL_MIS2_TXFIFO_CLR                                   0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_RXFIFO                                       0x00010000U
#define LRFDDBELL_MIS2_RXFIFO_M                                     0x00010000U
#define LRFDDBELL_MIS2_RXFIFO_S                                             16U
#define LRFDDBELL_MIS2_RXFIFO_SET                                   0x00010000U
#define LRFDDBELL_MIS2_RXFIFO_CLR                                   0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE15                                        0x00008000U
#define LRFDDBELL_MIS2_PBE15_M                                      0x00008000U
#define LRFDDBELL_MIS2_PBE15_S                                              15U
#define LRFDDBELL_MIS2_PBE15_SET                                    0x00008000U
#define LRFDDBELL_MIS2_PBE15_CLR                                    0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE14                                        0x00004000U
#define LRFDDBELL_MIS2_PBE14_M                                      0x00004000U
#define LRFDDBELL_MIS2_PBE14_S                                              14U
#define LRFDDBELL_MIS2_PBE14_SET                                    0x00004000U
#define LRFDDBELL_MIS2_PBE14_CLR                                    0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE13                                        0x00002000U
#define LRFDDBELL_MIS2_PBE13_M                                      0x00002000U
#define LRFDDBELL_MIS2_PBE13_S                                              13U
#define LRFDDBELL_MIS2_PBE13_SET                                    0x00002000U
#define LRFDDBELL_MIS2_PBE13_CLR                                    0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE12                                        0x00001000U
#define LRFDDBELL_MIS2_PBE12_M                                      0x00001000U
#define LRFDDBELL_MIS2_PBE12_S                                              12U
#define LRFDDBELL_MIS2_PBE12_SET                                    0x00001000U
#define LRFDDBELL_MIS2_PBE12_CLR                                    0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE11                                        0x00000800U
#define LRFDDBELL_MIS2_PBE11_M                                      0x00000800U
#define LRFDDBELL_MIS2_PBE11_S                                              11U
#define LRFDDBELL_MIS2_PBE11_SET                                    0x00000800U
#define LRFDDBELL_MIS2_PBE11_CLR                                    0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE10                                        0x00000400U
#define LRFDDBELL_MIS2_PBE10_M                                      0x00000400U
#define LRFDDBELL_MIS2_PBE10_S                                              10U
#define LRFDDBELL_MIS2_PBE10_SET                                    0x00000400U
#define LRFDDBELL_MIS2_PBE10_CLR                                    0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE9                                         0x00000200U
#define LRFDDBELL_MIS2_PBE9_M                                       0x00000200U
#define LRFDDBELL_MIS2_PBE9_S                                                9U
#define LRFDDBELL_MIS2_PBE9_SET                                     0x00000200U
#define LRFDDBELL_MIS2_PBE9_CLR                                     0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE8                                         0x00000100U
#define LRFDDBELL_MIS2_PBE8_M                                       0x00000100U
#define LRFDDBELL_MIS2_PBE8_S                                                8U
#define LRFDDBELL_MIS2_PBE8_SET                                     0x00000100U
#define LRFDDBELL_MIS2_PBE8_CLR                                     0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE7                                         0x00000080U
#define LRFDDBELL_MIS2_PBE7_M                                       0x00000080U
#define LRFDDBELL_MIS2_PBE7_S                                                7U
#define LRFDDBELL_MIS2_PBE7_SET                                     0x00000080U
#define LRFDDBELL_MIS2_PBE7_CLR                                     0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE6                                         0x00000040U
#define LRFDDBELL_MIS2_PBE6_M                                       0x00000040U
#define LRFDDBELL_MIS2_PBE6_S                                                6U
#define LRFDDBELL_MIS2_PBE6_SET                                     0x00000040U
#define LRFDDBELL_MIS2_PBE6_CLR                                     0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE5                                         0x00000020U
#define LRFDDBELL_MIS2_PBE5_M                                       0x00000020U
#define LRFDDBELL_MIS2_PBE5_S                                                5U
#define LRFDDBELL_MIS2_PBE5_SET                                     0x00000020U
#define LRFDDBELL_MIS2_PBE5_CLR                                     0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE4                                         0x00000010U
#define LRFDDBELL_MIS2_PBE4_M                                       0x00000010U
#define LRFDDBELL_MIS2_PBE4_S                                                4U
#define LRFDDBELL_MIS2_PBE4_SET                                     0x00000010U
#define LRFDDBELL_MIS2_PBE4_CLR                                     0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE3                                         0x00000008U
#define LRFDDBELL_MIS2_PBE3_M                                       0x00000008U
#define LRFDDBELL_MIS2_PBE3_S                                                3U
#define LRFDDBELL_MIS2_PBE3_SET                                     0x00000008U
#define LRFDDBELL_MIS2_PBE3_CLR                                     0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE2                                         0x00000004U
#define LRFDDBELL_MIS2_PBE2_M                                       0x00000004U
#define LRFDDBELL_MIS2_PBE2_S                                                2U
#define LRFDDBELL_MIS2_PBE2_SET                                     0x00000004U
#define LRFDDBELL_MIS2_PBE2_CLR                                     0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE1                                         0x00000002U
#define LRFDDBELL_MIS2_PBE1_M                                       0x00000002U
#define LRFDDBELL_MIS2_PBE1_S                                                1U
#define LRFDDBELL_MIS2_PBE1_SET                                     0x00000002U
#define LRFDDBELL_MIS2_PBE1_CLR                                     0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Interrupt occurred
// CLR                      Interrupt did not occur
#define LRFDDBELL_MIS2_PBE0                                         0x00000001U
#define LRFDDBELL_MIS2_PBE0_M                                       0x00000001U
#define LRFDDBELL_MIS2_PBE0_S                                                0U
#define LRFDDBELL_MIS2_PBE0_SET                                     0x00000001U
#define LRFDDBELL_MIS2_PBE0_CLR                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ISET2
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ISET2_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ISET2_SYSTIM2_S                                           31U
#define LRFDDBELL_ISET2_SYSTIM2_SET                                 0x80000000U
#define LRFDDBELL_ISET2_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ISET2_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ISET2_SYSTIM1_S                                           30U
#define LRFDDBELL_ISET2_SYSTIM1_SET                                 0x40000000U
#define LRFDDBELL_ISET2_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ISET2_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ISET2_SYSTIM0_S                                           29U
#define LRFDDBELL_ISET2_SYSTIM0_SET                                 0x20000000U
#define LRFDDBELL_ISET2_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMDONE                                     0x10000000U
#define LRFDDBELL_ISET2_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ISET2_MDMDONE_S                                           28U
#define LRFDDBELL_ISET2_MDMDONE_SET                                 0x10000000U
#define LRFDDBELL_ISET2_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMIN                                       0x08000000U
#define LRFDDBELL_ISET2_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ISET2_MDMIN_S                                             27U
#define LRFDDBELL_ISET2_MDMIN_SET                                   0x08000000U
#define LRFDDBELL_ISET2_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMOUT                                      0x04000000U
#define LRFDDBELL_ISET2_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ISET2_MDMOUT_S                                            26U
#define LRFDDBELL_ISET2_MDMOUT_SET                                  0x04000000U
#define LRFDDBELL_ISET2_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ISET2_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ISET2_MDMSOFT2_S                                          25U
#define LRFDDBELL_ISET2_MDMSOFT2_SET                                0x02000000U
#define LRFDDBELL_ISET2_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ISET2_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ISET2_MDMSOFT1_S                                          24U
#define LRFDDBELL_ISET2_MDMSOFT1_SET                                0x01000000U
#define LRFDDBELL_ISET2_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ISET2_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ISET2_MDMSOFT0_S                                          23U
#define LRFDDBELL_ISET2_MDMSOFT0_SET                                0x00800000U
#define LRFDDBELL_ISET2_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_RFEDONE                                     0x00400000U
#define LRFDDBELL_ISET2_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ISET2_RFEDONE_S                                           22U
#define LRFDDBELL_ISET2_RFEDONE_SET                                 0x00400000U
#define LRFDDBELL_ISET2_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ISET2_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ISET2_RFESOFT1_S                                          21U
#define LRFDDBELL_ISET2_RFESOFT1_SET                                0x00200000U
#define LRFDDBELL_ISET2_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ISET2_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ISET2_RFESOFT0_S                                          20U
#define LRFDDBELL_ISET2_RFESOFT0_SET                                0x00100000U
#define LRFDDBELL_ISET2_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_LOCK                                        0x00080000U
#define LRFDDBELL_ISET2_LOCK_M                                      0x00080000U
#define LRFDDBELL_ISET2_LOCK_S                                              19U
#define LRFDDBELL_ISET2_LOCK_SET                                    0x00080000U
#define LRFDDBELL_ISET2_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_LOL                                         0x00040000U
#define LRFDDBELL_ISET2_LOL_M                                       0x00040000U
#define LRFDDBELL_ISET2_LOL_S                                               18U
#define LRFDDBELL_ISET2_LOL_SET                                     0x00040000U
#define LRFDDBELL_ISET2_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_TXFIFO                                      0x00020000U
#define LRFDDBELL_ISET2_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ISET2_TXFIFO_S                                            17U
#define LRFDDBELL_ISET2_TXFIFO_SET                                  0x00020000U
#define LRFDDBELL_ISET2_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_RXFIFO                                      0x00010000U
#define LRFDDBELL_ISET2_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ISET2_RXFIFO_S                                            16U
#define LRFDDBELL_ISET2_RXFIFO_SET                                  0x00010000U
#define LRFDDBELL_ISET2_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE15                                       0x00008000U
#define LRFDDBELL_ISET2_PBE15_M                                     0x00008000U
#define LRFDDBELL_ISET2_PBE15_S                                             15U
#define LRFDDBELL_ISET2_PBE15_SET                                   0x00008000U
#define LRFDDBELL_ISET2_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE14                                       0x00004000U
#define LRFDDBELL_ISET2_PBE14_M                                     0x00004000U
#define LRFDDBELL_ISET2_PBE14_S                                             14U
#define LRFDDBELL_ISET2_PBE14_SET                                   0x00004000U
#define LRFDDBELL_ISET2_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE13                                       0x00002000U
#define LRFDDBELL_ISET2_PBE13_M                                     0x00002000U
#define LRFDDBELL_ISET2_PBE13_S                                             13U
#define LRFDDBELL_ISET2_PBE13_SET                                   0x00002000U
#define LRFDDBELL_ISET2_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE12                                       0x00001000U
#define LRFDDBELL_ISET2_PBE12_M                                     0x00001000U
#define LRFDDBELL_ISET2_PBE12_S                                             12U
#define LRFDDBELL_ISET2_PBE12_SET                                   0x00001000U
#define LRFDDBELL_ISET2_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE11                                       0x00000800U
#define LRFDDBELL_ISET2_PBE11_M                                     0x00000800U
#define LRFDDBELL_ISET2_PBE11_S                                             11U
#define LRFDDBELL_ISET2_PBE11_SET                                   0x00000800U
#define LRFDDBELL_ISET2_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE10                                       0x00000400U
#define LRFDDBELL_ISET2_PBE10_M                                     0x00000400U
#define LRFDDBELL_ISET2_PBE10_S                                             10U
#define LRFDDBELL_ISET2_PBE10_SET                                   0x00000400U
#define LRFDDBELL_ISET2_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE9                                        0x00000200U
#define LRFDDBELL_ISET2_PBE9_M                                      0x00000200U
#define LRFDDBELL_ISET2_PBE9_S                                               9U
#define LRFDDBELL_ISET2_PBE9_SET                                    0x00000200U
#define LRFDDBELL_ISET2_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE8                                        0x00000100U
#define LRFDDBELL_ISET2_PBE8_M                                      0x00000100U
#define LRFDDBELL_ISET2_PBE8_S                                               8U
#define LRFDDBELL_ISET2_PBE8_SET                                    0x00000100U
#define LRFDDBELL_ISET2_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE7                                        0x00000080U
#define LRFDDBELL_ISET2_PBE7_M                                      0x00000080U
#define LRFDDBELL_ISET2_PBE7_S                                               7U
#define LRFDDBELL_ISET2_PBE7_SET                                    0x00000080U
#define LRFDDBELL_ISET2_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE6                                        0x00000040U
#define LRFDDBELL_ISET2_PBE6_M                                      0x00000040U
#define LRFDDBELL_ISET2_PBE6_S                                               6U
#define LRFDDBELL_ISET2_PBE6_SET                                    0x00000040U
#define LRFDDBELL_ISET2_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE5                                        0x00000020U
#define LRFDDBELL_ISET2_PBE5_M                                      0x00000020U
#define LRFDDBELL_ISET2_PBE5_S                                               5U
#define LRFDDBELL_ISET2_PBE5_SET                                    0x00000020U
#define LRFDDBELL_ISET2_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE4                                        0x00000010U
#define LRFDDBELL_ISET2_PBE4_M                                      0x00000010U
#define LRFDDBELL_ISET2_PBE4_S                                               4U
#define LRFDDBELL_ISET2_PBE4_SET                                    0x00000010U
#define LRFDDBELL_ISET2_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE3                                        0x00000008U
#define LRFDDBELL_ISET2_PBE3_M                                      0x00000008U
#define LRFDDBELL_ISET2_PBE3_S                                               3U
#define LRFDDBELL_ISET2_PBE3_SET                                    0x00000008U
#define LRFDDBELL_ISET2_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE2                                        0x00000004U
#define LRFDDBELL_ISET2_PBE2_M                                      0x00000004U
#define LRFDDBELL_ISET2_PBE2_S                                               2U
#define LRFDDBELL_ISET2_PBE2_SET                                    0x00000004U
#define LRFDDBELL_ISET2_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE1                                        0x00000002U
#define LRFDDBELL_ISET2_PBE1_M                                      0x00000002U
#define LRFDDBELL_ISET2_PBE1_S                                               1U
#define LRFDDBELL_ISET2_PBE1_SET                                    0x00000002U
#define LRFDDBELL_ISET2_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ISET2_PBE0                                        0x00000001U
#define LRFDDBELL_ISET2_PBE0_M                                      0x00000001U
#define LRFDDBELL_ISET2_PBE0_S                                               0U
#define LRFDDBELL_ISET2_PBE0_SET                                    0x00000001U
#define LRFDDBELL_ISET2_PBE0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDDBELL_O_ICLR2
//
//*****************************************************************************
// Field:    [31] SYSTIM2
//
// SYSTIM2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_SYSTIM2                                     0x80000000U
#define LRFDDBELL_ICLR2_SYSTIM2_M                                   0x80000000U
#define LRFDDBELL_ICLR2_SYSTIM2_S                                           31U
#define LRFDDBELL_ICLR2_SYSTIM2_CLR                                 0x80000000U
#define LRFDDBELL_ICLR2_SYSTIM2_NOEFF                               0x00000000U

// Field:    [30] SYSTIM1
//
// SYSTIM1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_SYSTIM1                                     0x40000000U
#define LRFDDBELL_ICLR2_SYSTIM1_M                                   0x40000000U
#define LRFDDBELL_ICLR2_SYSTIM1_S                                           30U
#define LRFDDBELL_ICLR2_SYSTIM1_CLR                                 0x40000000U
#define LRFDDBELL_ICLR2_SYSTIM1_NOEFF                               0x00000000U

// Field:    [29] SYSTIM0
//
// SYSTIM0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_SYSTIM0                                     0x20000000U
#define LRFDDBELL_ICLR2_SYSTIM0_M                                   0x20000000U
#define LRFDDBELL_ICLR2_SYSTIM0_S                                           29U
#define LRFDDBELL_ICLR2_SYSTIM0_CLR                                 0x20000000U
#define LRFDDBELL_ICLR2_SYSTIM0_NOEFF                               0x00000000U

// Field:    [28] MDMDONE
//
// MDMDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMDONE                                     0x10000000U
#define LRFDDBELL_ICLR2_MDMDONE_M                                   0x10000000U
#define LRFDDBELL_ICLR2_MDMDONE_S                                           28U
#define LRFDDBELL_ICLR2_MDMDONE_CLR                                 0x10000000U
#define LRFDDBELL_ICLR2_MDMDONE_NOEFF                               0x00000000U

// Field:    [27] MDMIN
//
// MDMIN event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMIN                                       0x08000000U
#define LRFDDBELL_ICLR2_MDMIN_M                                     0x08000000U
#define LRFDDBELL_ICLR2_MDMIN_S                                             27U
#define LRFDDBELL_ICLR2_MDMIN_CLR                                   0x08000000U
#define LRFDDBELL_ICLR2_MDMIN_NOEFF                                 0x00000000U

// Field:    [26] MDMOUT
//
// MDMOUT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMOUT                                      0x04000000U
#define LRFDDBELL_ICLR2_MDMOUT_M                                    0x04000000U
#define LRFDDBELL_ICLR2_MDMOUT_S                                            26U
#define LRFDDBELL_ICLR2_MDMOUT_CLR                                  0x04000000U
#define LRFDDBELL_ICLR2_MDMOUT_NOEFF                                0x00000000U

// Field:    [25] MDMSOFT2
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMSOFT2                                    0x02000000U
#define LRFDDBELL_ICLR2_MDMSOFT2_M                                  0x02000000U
#define LRFDDBELL_ICLR2_MDMSOFT2_S                                          25U
#define LRFDDBELL_ICLR2_MDMSOFT2_CLR                                0x02000000U
#define LRFDDBELL_ICLR2_MDMSOFT2_NOEFF                              0x00000000U

// Field:    [24] MDMSOFT1
//
// MDMSOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMSOFT1                                    0x01000000U
#define LRFDDBELL_ICLR2_MDMSOFT1_M                                  0x01000000U
#define LRFDDBELL_ICLR2_MDMSOFT1_S                                          24U
#define LRFDDBELL_ICLR2_MDMSOFT1_CLR                                0x01000000U
#define LRFDDBELL_ICLR2_MDMSOFT1_NOEFF                              0x00000000U

// Field:    [23] MDMSOFT0
//
// MDMSOFT event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_MDMSOFT0                                    0x00800000U
#define LRFDDBELL_ICLR2_MDMSOFT0_M                                  0x00800000U
#define LRFDDBELL_ICLR2_MDMSOFT0_S                                          23U
#define LRFDDBELL_ICLR2_MDMSOFT0_CLR                                0x00800000U
#define LRFDDBELL_ICLR2_MDMSOFT0_NOEFF                              0x00000000U

// Field:    [22] RFEDONE
//
// RFEDONE event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_RFEDONE                                     0x00400000U
#define LRFDDBELL_ICLR2_RFEDONE_M                                   0x00400000U
#define LRFDDBELL_ICLR2_RFEDONE_S                                           22U
#define LRFDDBELL_ICLR2_RFEDONE_CLR                                 0x00400000U
#define LRFDDBELL_ICLR2_RFEDONE_NOEFF                               0x00000000U

// Field:    [21] RFESOFT1
//
// RFESOFT1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_RFESOFT1                                    0x00200000U
#define LRFDDBELL_ICLR2_RFESOFT1_M                                  0x00200000U
#define LRFDDBELL_ICLR2_RFESOFT1_S                                          21U
#define LRFDDBELL_ICLR2_RFESOFT1_CLR                                0x00200000U
#define LRFDDBELL_ICLR2_RFESOFT1_NOEFF                              0x00000000U

// Field:    [20] RFESOFT0
//
// RFESOFT0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_RFESOFT0                                    0x00100000U
#define LRFDDBELL_ICLR2_RFESOFT0_M                                  0x00100000U
#define LRFDDBELL_ICLR2_RFESOFT0_S                                          20U
#define LRFDDBELL_ICLR2_RFESOFT0_CLR                                0x00100000U
#define LRFDDBELL_ICLR2_RFESOFT0_NOEFF                              0x00000000U

// Field:    [19] LOCK
//
// LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_LOCK                                        0x00080000U
#define LRFDDBELL_ICLR2_LOCK_M                                      0x00080000U
#define LRFDDBELL_ICLR2_LOCK_S                                              19U
#define LRFDDBELL_ICLR2_LOCK_CLR                                    0x00080000U
#define LRFDDBELL_ICLR2_LOCK_NOEFF                                  0x00000000U

// Field:    [18] LOL
//
// LOSS_OF_LOCK event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_LOL                                         0x00040000U
#define LRFDDBELL_ICLR2_LOL_M                                       0x00040000U
#define LRFDDBELL_ICLR2_LOL_S                                               18U
#define LRFDDBELL_ICLR2_LOL_CLR                                     0x00040000U
#define LRFDDBELL_ICLR2_LOL_NOEFF                                   0x00000000U

// Field:    [17] TXFIFO
//
// TXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_TXFIFO                                      0x00020000U
#define LRFDDBELL_ICLR2_TXFIFO_M                                    0x00020000U
#define LRFDDBELL_ICLR2_TXFIFO_S                                            17U
#define LRFDDBELL_ICLR2_TXFIFO_CLR                                  0x00020000U
#define LRFDDBELL_ICLR2_TXFIFO_NOEFF                                0x00000000U

// Field:    [16] RXFIFO
//
// RXFIFO event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_RXFIFO                                      0x00010000U
#define LRFDDBELL_ICLR2_RXFIFO_M                                    0x00010000U
#define LRFDDBELL_ICLR2_RXFIFO_S                                            16U
#define LRFDDBELL_ICLR2_RXFIFO_CLR                                  0x00010000U
#define LRFDDBELL_ICLR2_RXFIFO_NOEFF                                0x00000000U

// Field:    [15] PBE15
//
// PBE15 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE15                                       0x00008000U
#define LRFDDBELL_ICLR2_PBE15_M                                     0x00008000U
#define LRFDDBELL_ICLR2_PBE15_S                                             15U
#define LRFDDBELL_ICLR2_PBE15_CLR                                   0x00008000U
#define LRFDDBELL_ICLR2_PBE15_NOEFF                                 0x00000000U

// Field:    [14] PBE14
//
// PBE14 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE14                                       0x00004000U
#define LRFDDBELL_ICLR2_PBE14_M                                     0x00004000U
#define LRFDDBELL_ICLR2_PBE14_S                                             14U
#define LRFDDBELL_ICLR2_PBE14_CLR                                   0x00004000U
#define LRFDDBELL_ICLR2_PBE14_NOEFF                                 0x00000000U

// Field:    [13] PBE13
//
// PBE13 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE13                                       0x00002000U
#define LRFDDBELL_ICLR2_PBE13_M                                     0x00002000U
#define LRFDDBELL_ICLR2_PBE13_S                                             13U
#define LRFDDBELL_ICLR2_PBE13_CLR                                   0x00002000U
#define LRFDDBELL_ICLR2_PBE13_NOEFF                                 0x00000000U

// Field:    [12] PBE12
//
// PBE12 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE12                                       0x00001000U
#define LRFDDBELL_ICLR2_PBE12_M                                     0x00001000U
#define LRFDDBELL_ICLR2_PBE12_S                                             12U
#define LRFDDBELL_ICLR2_PBE12_CLR                                   0x00001000U
#define LRFDDBELL_ICLR2_PBE12_NOEFF                                 0x00000000U

// Field:    [11] PBE11
//
// PBE11 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE11                                       0x00000800U
#define LRFDDBELL_ICLR2_PBE11_M                                     0x00000800U
#define LRFDDBELL_ICLR2_PBE11_S                                             11U
#define LRFDDBELL_ICLR2_PBE11_CLR                                   0x00000800U
#define LRFDDBELL_ICLR2_PBE11_NOEFF                                 0x00000000U

// Field:    [10] PBE10
//
// PBE10 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE10                                       0x00000400U
#define LRFDDBELL_ICLR2_PBE10_M                                     0x00000400U
#define LRFDDBELL_ICLR2_PBE10_S                                             10U
#define LRFDDBELL_ICLR2_PBE10_CLR                                   0x00000400U
#define LRFDDBELL_ICLR2_PBE10_NOEFF                                 0x00000000U

// Field:     [9] PBE9
//
// PBE9 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE9                                        0x00000200U
#define LRFDDBELL_ICLR2_PBE9_M                                      0x00000200U
#define LRFDDBELL_ICLR2_PBE9_S                                               9U
#define LRFDDBELL_ICLR2_PBE9_CLR                                    0x00000200U
#define LRFDDBELL_ICLR2_PBE9_NOEFF                                  0x00000000U

// Field:     [8] PBE8
//
// PBE8 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE8                                        0x00000100U
#define LRFDDBELL_ICLR2_PBE8_M                                      0x00000100U
#define LRFDDBELL_ICLR2_PBE8_S                                               8U
#define LRFDDBELL_ICLR2_PBE8_CLR                                    0x00000100U
#define LRFDDBELL_ICLR2_PBE8_NOEFF                                  0x00000000U

// Field:     [7] PBE7
//
// PBE7 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE7                                        0x00000080U
#define LRFDDBELL_ICLR2_PBE7_M                                      0x00000080U
#define LRFDDBELL_ICLR2_PBE7_S                                               7U
#define LRFDDBELL_ICLR2_PBE7_CLR                                    0x00000080U
#define LRFDDBELL_ICLR2_PBE7_NOEFF                                  0x00000000U

// Field:     [6] PBE6
//
// PBE6 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE6                                        0x00000040U
#define LRFDDBELL_ICLR2_PBE6_M                                      0x00000040U
#define LRFDDBELL_ICLR2_PBE6_S                                               6U
#define LRFDDBELL_ICLR2_PBE6_CLR                                    0x00000040U
#define LRFDDBELL_ICLR2_PBE6_NOEFF                                  0x00000000U

// Field:     [5] PBE5
//
// PBE5 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE5                                        0x00000020U
#define LRFDDBELL_ICLR2_PBE5_M                                      0x00000020U
#define LRFDDBELL_ICLR2_PBE5_S                                               5U
#define LRFDDBELL_ICLR2_PBE5_CLR                                    0x00000020U
#define LRFDDBELL_ICLR2_PBE5_NOEFF                                  0x00000000U

// Field:     [4] PBE4
//
// PBE4 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE4                                        0x00000010U
#define LRFDDBELL_ICLR2_PBE4_M                                      0x00000010U
#define LRFDDBELL_ICLR2_PBE4_S                                               4U
#define LRFDDBELL_ICLR2_PBE4_CLR                                    0x00000010U
#define LRFDDBELL_ICLR2_PBE4_NOEFF                                  0x00000000U

// Field:     [3] PBE3
//
// PBE3 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE3                                        0x00000008U
#define LRFDDBELL_ICLR2_PBE3_M                                      0x00000008U
#define LRFDDBELL_ICLR2_PBE3_S                                               3U
#define LRFDDBELL_ICLR2_PBE3_CLR                                    0x00000008U
#define LRFDDBELL_ICLR2_PBE3_NOEFF                                  0x00000000U

// Field:     [2] PBE2
//
// PBE2 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE2                                        0x00000004U
#define LRFDDBELL_ICLR2_PBE2_M                                      0x00000004U
#define LRFDDBELL_ICLR2_PBE2_S                                               2U
#define LRFDDBELL_ICLR2_PBE2_CLR                                    0x00000004U
#define LRFDDBELL_ICLR2_PBE2_NOEFF                                  0x00000000U

// Field:     [1] PBE1
//
// PBE1 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE1                                        0x00000002U
#define LRFDDBELL_ICLR2_PBE1_M                                      0x00000002U
#define LRFDDBELL_ICLR2_PBE1_S                                               1U
#define LRFDDBELL_ICLR2_PBE1_CLR                                    0x00000002U
#define LRFDDBELL_ICLR2_PBE1_NOEFF                                  0x00000000U

// Field:     [0] PBE0
//
// PBE0 event
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define LRFDDBELL_ICLR2_PBE0                                        0x00000001U
#define LRFDDBELL_ICLR2_PBE0_M                                      0x00000001U
#define LRFDDBELL_ICLR2_PBE0_S                                               0U
#define LRFDDBELL_ICLR2_PBE0_CLR                                    0x00000001U
#define LRFDDBELL_ICLR2_PBE0_NOEFF                                  0x00000000U


#endif // __LRFDDBELL__
