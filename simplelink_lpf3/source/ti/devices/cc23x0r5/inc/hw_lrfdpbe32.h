/******************************************************************************
*  Filename:       hw_lrfdpbe32.h
******************************************************************************
*  Copyright (c) 2021-2025 Texas Instruments Incorporated. All rights reserved.
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

#ifndef __HW_LRFDPBE32_H__
#define __HW_LRFDPBE32_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDPBE32 component
//
//*****************************************************************************
// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FWSRC_ENABLE                                    0x00000000U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_STROBES0_INIT                                   0x00000004U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_EVT0_IRQ                                        0x00000008U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_EVTMSK0_EVT1                                    0x0000000CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_EVTCLR0_EVTMSK1                                 0x00000010U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_PDREQ_EVTCLR1                                   0x00000014U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MCEDATOUT0_API                                  0x00000018U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MCECMDOUT_MCEDATIN0                             0x0000001CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMAPI_MCECMDIN                                 0x00000020U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FREQ_MDMMSGBOX                                  0x00000024U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFEDATOUT0_MDMLQI                               0x00000028U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFECMDOUT_RFEDATIN0                             0x0000002CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFEAPI_RFECMDIN                                 0x00000030U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFECMDPAR1_RFECMDPAR0                           0x00000034U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFERSSI_RFEMSGBOX                               0x00000038U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RFERFGAIN_RFERSSIMAX                            0x0000003CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMSYNCA                                        0x00000040U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMSYNCB                                        0x00000044U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMCMDPAR1_MDMCMDPAR0                           0x00000048U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMCMDPAR2                                      0x0000004CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_POLY0                                           0x00000050U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_POLY1                                           0x00000054U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FCFG0_PHACFG                                    0x00000058U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FCFG2_FCFG1                                     0x0000005CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FCFG4_FCFG3                                     0x00000060U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFWBTHRS_FCFG5                                 0x00000064U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFWBTHRS_RXFRBTHRS                             0x00000068U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TIMCTL_TXFRBTHRS                                0x0000006CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TIMPER0_TIMPRE                                  0x00000070U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TIMCAPT0_TIMPER1                                0x00000074U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TIMCAPT1                                        0x00000078U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TRCSTAT_TRCCTL                                  0x00000080U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TRCPAR0_TRCCMD                                  0x00000084U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_GPOCTRL_TRCPAR1                                 0x00000088U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMFRD_MDMFWR                                   0x0000008CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMFRDCTL_MDMFWRCTL                             0x00000090U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_MDMFSTA_MDMFCFG                                 0x00000094U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_PHASTA                                          0x00000098U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR0                                           0x0000009CU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR0BR                                         0x000000A0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR1                                           0x000000A4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR1BR                                         0x000000A8U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR0N_LFSR0INL                                 0x000000ACU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_PHAOUT0_LFSR0INM                                0x000000B0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_LFSR1N_LFSR1INL                                 0x000000B4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_PHAOUT0BR_LFSR1INM                              0x000000B8U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_SYSTIM0                                         0x000000C0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_SYSTIM1                                         0x000000C4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_SYSTIM2                                         0x000000C8U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_GPI                                             0x000000CCU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_FSTAT_FCMD                                      0x000000D0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFRP_RXFWP                                     0x000000D4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFSRP_RXFSWP                                   0x000000D8U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFRP_TXFWP                                     0x000000DCU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFSRP_TXFSWP                                   0x000000E0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFREADABLE_RXFWRITABLE                         0x000000E4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFREADABLE_TXFWRITABLE                         0x000000E8U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFBWR_RXFBRD                                   0x000000ECU

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFBWR_TXFBRD                                   0x000000F0U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_RXFHWR_RXFHRD                                   0x000000F4U

// Internal. Only to be used through TI provided API.
#define LRFDPBE32_O_TXFHWR_TXFHRD                                   0x000000F8U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FWSRC_ENABLE
//
//*****************************************************************************
// Field:    [18] DATARAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// PBERAM                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_DATARAM                              0x00040000U
#define LRFDPBE32_FWSRC_ENABLE_DATARAM_M                            0x00040000U
#define LRFDPBE32_FWSRC_ENABLE_DATARAM_S                                    18U
#define LRFDPBE32_FWSRC_ENABLE_DATARAM_S2RRAM                       0x00040000U
#define LRFDPBE32_FWSRC_ENABLE_DATARAM_PBERAM                       0x00000000U

// Field:    [17] FWRAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// PBERAM                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_FWRAM                                0x00020000U
#define LRFDPBE32_FWSRC_ENABLE_FWRAM_M                              0x00020000U
#define LRFDPBE32_FWSRC_ENABLE_FWRAM_S                                      17U
#define LRFDPBE32_FWSRC_ENABLE_FWRAM_S2RRAM                         0x00020000U
#define LRFDPBE32_FWSRC_ENABLE_FWRAM_PBERAM                         0x00000000U

// Field:    [16] BANK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_BANK                                 0x00010000U
#define LRFDPBE32_FWSRC_ENABLE_BANK_M                               0x00010000U
#define LRFDPBE32_FWSRC_ENABLE_BANK_S                                       16U
#define LRFDPBE32_FWSRC_ENABLE_BANK_ONE                             0x00010000U
#define LRFDPBE32_FWSRC_ENABLE_BANK_ZERO                            0x00000000U

// Field:     [2] MDMF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_MDMF                                 0x00000004U
#define LRFDPBE32_FWSRC_ENABLE_MDMF_M                               0x00000004U
#define LRFDPBE32_FWSRC_ENABLE_MDMF_S                                        2U
#define LRFDPBE32_FWSRC_ENABLE_MDMF_EN                              0x00000004U
#define LRFDPBE32_FWSRC_ENABLE_MDMF_DIS                             0x00000000U

// Field:     [1] LOCTIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_LOCTIM                               0x00000002U
#define LRFDPBE32_FWSRC_ENABLE_LOCTIM_M                             0x00000002U
#define LRFDPBE32_FWSRC_ENABLE_LOCTIM_S                                      1U
#define LRFDPBE32_FWSRC_ENABLE_LOCTIM_EN                            0x00000002U
#define LRFDPBE32_FWSRC_ENABLE_LOCTIM_DIS                           0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FWSRC_ENABLE_TOPSM                                0x00000001U
#define LRFDPBE32_FWSRC_ENABLE_TOPSM_M                              0x00000001U
#define LRFDPBE32_FWSRC_ENABLE_TOPSM_S                                       0U
#define LRFDPBE32_FWSRC_ENABLE_TOPSM_EN                             0x00000001U
#define LRFDPBE32_FWSRC_ENABLE_TOPSM_DIS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_STROBES0_INIT
//
//*****************************************************************************
// Field:    [22] TIMCAPT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_TIMCAPT1                            0x00400000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT1_M                          0x00400000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT1_S                                  22U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT1_ONE                        0x00400000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT1_ZERO                       0x00000000U

// Field:    [21] TIMCAPT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_TIMCAPT0                            0x00200000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT0_M                          0x00200000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT0_S                                  21U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT0_ONE                        0x00200000U
#define LRFDPBE32_STROBES0_INIT_TIMCAPT0_ZERO                       0x00000000U

// Field:    [20] S2RTRIG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ARM                      Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_S2RTRIG                             0x00100000U
#define LRFDPBE32_STROBES0_INIT_S2RTRIG_M                           0x00100000U
#define LRFDPBE32_STROBES0_INIT_S2RTRIG_S                                   20U
#define LRFDPBE32_STROBES0_INIT_S2RTRIG_ARM                         0x00100000U
#define LRFDPBE32_STROBES0_INIT_S2RTRIG_NO_EFFECT                   0x00000000U

// Field:    [19] DMATRIG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ARM                      Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_DMATRIG                             0x00080000U
#define LRFDPBE32_STROBES0_INIT_DMATRIG_M                           0x00080000U
#define LRFDPBE32_STROBES0_INIT_DMATRIG_S                                   19U
#define LRFDPBE32_STROBES0_INIT_DMATRIG_ARM                         0x00080000U
#define LRFDPBE32_STROBES0_INIT_DMATRIG_NO_EFFECT                   0x00000000U

// Field:    [18] SYSTCAPT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT2                           0x00040000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT2_M                         0x00040000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT2_S                                 18U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT2_ONE                       0x00040000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT2_ZERO                      0x00000000U

// Field:    [17] SYSTCAPT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT1                           0x00020000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT1_M                         0x00020000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT1_S                                 17U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT1_ONE                       0x00020000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT1_ZERO                      0x00000000U

// Field:    [16] SYSTCAPT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT0                           0x00010000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT0_M                         0x00010000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT0_S                                 16U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT0_ONE                       0x00010000U
#define LRFDPBE32_STROBES0_INIT_SYSTCAPT0_ZERO                      0x00000000U

// Field:     [4] RFE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_RFE                                 0x00000010U
#define LRFDPBE32_STROBES0_INIT_RFE_M                               0x00000010U
#define LRFDPBE32_STROBES0_INIT_RFE_S                                        4U
#define LRFDPBE32_STROBES0_INIT_RFE_RESET                           0x00000010U
#define LRFDPBE32_STROBES0_INIT_RFE_NO_EFFECT                       0x00000000U

// Field:     [3] MDM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_MDM                                 0x00000008U
#define LRFDPBE32_STROBES0_INIT_MDM_M                               0x00000008U
#define LRFDPBE32_STROBES0_INIT_MDM_S                                        3U
#define LRFDPBE32_STROBES0_INIT_MDM_RESET                           0x00000008U
#define LRFDPBE32_STROBES0_INIT_MDM_NO_EFFECT                       0x00000000U

// Field:     [2] MDMF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_MDMF                                0x00000004U
#define LRFDPBE32_STROBES0_INIT_MDMF_M                              0x00000004U
#define LRFDPBE32_STROBES0_INIT_MDMF_S                                       2U
#define LRFDPBE32_STROBES0_INIT_MDMF_RESET                          0x00000004U
#define LRFDPBE32_STROBES0_INIT_MDMF_NO_EFFECT                      0x00000000U

// Field:     [1] LOCTIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_LOCTIM                              0x00000002U
#define LRFDPBE32_STROBES0_INIT_LOCTIM_M                            0x00000002U
#define LRFDPBE32_STROBES0_INIT_LOCTIM_S                                     1U
#define LRFDPBE32_STROBES0_INIT_LOCTIM_RESET                        0x00000002U
#define LRFDPBE32_STROBES0_INIT_LOCTIM_NO_EFFECT                    0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDPBE32_STROBES0_INIT_TOPSM                               0x00000001U
#define LRFDPBE32_STROBES0_INIT_TOPSM_M                             0x00000001U
#define LRFDPBE32_STROBES0_INIT_TOPSM_S                                      0U
#define LRFDPBE32_STROBES0_INIT_TOPSM_RESET                         0x00000001U
#define LRFDPBE32_STROBES0_INIT_TOPSM_NO_EFFECT                     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_EVT0_IRQ
//
//*****************************************************************************
// Field:    [31] MDMFAEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_MDMFAEMPTY                               0x80000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAEMPTY_M                             0x80000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAEMPTY_S                                     31U
#define LRFDPBE32_EVT0_IRQ_MDMFAEMPTY_ONE                           0x80000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAEMPTY_ZERO                          0x00000000U

// Field:    [30] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_S2RSTOP                                  0x40000000U
#define LRFDPBE32_EVT0_IRQ_S2RSTOP_M                                0x40000000U
#define LRFDPBE32_EVT0_IRQ_S2RSTOP_S                                        30U
#define LRFDPBE32_EVT0_IRQ_S2RSTOP_ONE                              0x40000000U
#define LRFDPBE32_EVT0_IRQ_S2RSTOP_ZERO                             0x00000000U

// Field:    [29] FIFOERR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_FIFOERR                                  0x20000000U
#define LRFDPBE32_EVT0_IRQ_FIFOERR_M                                0x20000000U
#define LRFDPBE32_EVT0_IRQ_FIFOERR_S                                        29U
#define LRFDPBE32_EVT0_IRQ_FIFOERR_ONE                              0x20000000U
#define LRFDPBE32_EVT0_IRQ_FIFOERR_ZERO                             0x00000000U

// Field:    [28] MDMFAFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_MDMFAFULL                                0x10000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAFULL_M                              0x10000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAFULL_S                                      28U
#define LRFDPBE32_EVT0_IRQ_MDMFAFULL_ONE                            0x10000000U
#define LRFDPBE32_EVT0_IRQ_MDMFAFULL_ZERO                           0x00000000U

// Field:    [27] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SYSTCMP2                                 0x08000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP2_M                               0x08000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP2_S                                       27U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP2_ONE                             0x08000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP2_ZERO                            0x00000000U

// Field:    [26] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SYSTCMP1                                 0x04000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP1_M                               0x04000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP1_S                                       26U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP1_ONE                             0x04000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP1_ZERO                            0x00000000U

// Field:    [25] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SYSTCMP0                                 0x02000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP0_M                               0x02000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP0_S                                       25U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP0_ONE                             0x02000000U
#define LRFDPBE32_EVT0_IRQ_SYSTCMP0_ZERO                            0x00000000U

// Field:    [24] MDMMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_MDMMSGBOX                                0x01000000U
#define LRFDPBE32_EVT0_IRQ_MDMMSGBOX_M                              0x01000000U
#define LRFDPBE32_EVT0_IRQ_MDMMSGBOX_S                                      24U
#define LRFDPBE32_EVT0_IRQ_MDMMSGBOX_ONE                            0x01000000U
#define LRFDPBE32_EVT0_IRQ_MDMMSGBOX_ZERO                           0x00000000U

// Field:    [23] RFEMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_RFEMSGBOX                                0x00800000U
#define LRFDPBE32_EVT0_IRQ_RFEMSGBOX_M                              0x00800000U
#define LRFDPBE32_EVT0_IRQ_RFEMSGBOX_S                                      23U
#define LRFDPBE32_EVT0_IRQ_RFEMSGBOX_ONE                            0x00800000U
#define LRFDPBE32_EVT0_IRQ_RFEMSGBOX_ZERO                           0x00000000U

// Field:    [22] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_RFEDAT                                   0x00400000U
#define LRFDPBE32_EVT0_IRQ_RFEDAT_M                                 0x00400000U
#define LRFDPBE32_EVT0_IRQ_RFEDAT_S                                         22U
#define LRFDPBE32_EVT0_IRQ_RFEDAT_ONE                               0x00400000U
#define LRFDPBE32_EVT0_IRQ_RFEDAT_ZERO                              0x00000000U

// Field:    [21] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_RFECMD                                   0x00200000U
#define LRFDPBE32_EVT0_IRQ_RFECMD_M                                 0x00200000U
#define LRFDPBE32_EVT0_IRQ_RFECMD_S                                         21U
#define LRFDPBE32_EVT0_IRQ_RFECMD_ONE                               0x00200000U
#define LRFDPBE32_EVT0_IRQ_RFECMD_ZERO                              0x00000000U

// Field:    [20] MDMDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_MDMDAT                                   0x00100000U
#define LRFDPBE32_EVT0_IRQ_MDMDAT_M                                 0x00100000U
#define LRFDPBE32_EVT0_IRQ_MDMDAT_S                                         20U
#define LRFDPBE32_EVT0_IRQ_MDMDAT_ONE                               0x00100000U
#define LRFDPBE32_EVT0_IRQ_MDMDAT_ZERO                              0x00000000U

// Field:    [19] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_MDMCMD                                   0x00080000U
#define LRFDPBE32_EVT0_IRQ_MDMCMD_M                                 0x00080000U
#define LRFDPBE32_EVT0_IRQ_MDMCMD_S                                         19U
#define LRFDPBE32_EVT0_IRQ_MDMCMD_ONE                               0x00080000U
#define LRFDPBE32_EVT0_IRQ_MDMCMD_ZERO                              0x00000000U

// Field:    [18] TIMER1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_TIMER1                                   0x00040000U
#define LRFDPBE32_EVT0_IRQ_TIMER1_M                                 0x00040000U
#define LRFDPBE32_EVT0_IRQ_TIMER1_S                                         18U
#define LRFDPBE32_EVT0_IRQ_TIMER1_ONE                               0x00040000U
#define LRFDPBE32_EVT0_IRQ_TIMER1_ZERO                              0x00000000U

// Field:    [17] TIMER0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_TIMER0                                   0x00020000U
#define LRFDPBE32_EVT0_IRQ_TIMER0_M                                 0x00020000U
#define LRFDPBE32_EVT0_IRQ_TIMER0_S                                         17U
#define LRFDPBE32_EVT0_IRQ_TIMER0_ONE                               0x00020000U
#define LRFDPBE32_EVT0_IRQ_TIMER0_ZERO                              0x00000000U

// Field:    [16] PBEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_PBEAPI                                   0x00010000U
#define LRFDPBE32_EVT0_IRQ_PBEAPI_M                                 0x00010000U
#define LRFDPBE32_EVT0_IRQ_PBEAPI_S                                         16U
#define LRFDPBE32_EVT0_IRQ_PBEAPI_ONE                               0x00010000U
#define LRFDPBE32_EVT0_IRQ_PBEAPI_ZERO                              0x00000000U

// Field:    [15] SOFT15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT15                                   0x00008000U
#define LRFDPBE32_EVT0_IRQ_SOFT15_M                                 0x00008000U
#define LRFDPBE32_EVT0_IRQ_SOFT15_S                                         15U
#define LRFDPBE32_EVT0_IRQ_SOFT15_ON                                0x00008000U
#define LRFDPBE32_EVT0_IRQ_SOFT15_OFF                               0x00000000U

// Field:    [14] SOFT14
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT14                                   0x00004000U
#define LRFDPBE32_EVT0_IRQ_SOFT14_M                                 0x00004000U
#define LRFDPBE32_EVT0_IRQ_SOFT14_S                                         14U
#define LRFDPBE32_EVT0_IRQ_SOFT14_ON                                0x00004000U
#define LRFDPBE32_EVT0_IRQ_SOFT14_OFF                               0x00000000U

// Field:    [13] SOFT13
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT13                                   0x00002000U
#define LRFDPBE32_EVT0_IRQ_SOFT13_M                                 0x00002000U
#define LRFDPBE32_EVT0_IRQ_SOFT13_S                                         13U
#define LRFDPBE32_EVT0_IRQ_SOFT13_ON                                0x00002000U
#define LRFDPBE32_EVT0_IRQ_SOFT13_OFF                               0x00000000U

// Field:    [12] SOFT12
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT12                                   0x00001000U
#define LRFDPBE32_EVT0_IRQ_SOFT12_M                                 0x00001000U
#define LRFDPBE32_EVT0_IRQ_SOFT12_S                                         12U
#define LRFDPBE32_EVT0_IRQ_SOFT12_ON                                0x00001000U
#define LRFDPBE32_EVT0_IRQ_SOFT12_OFF                               0x00000000U

// Field:    [11] SOFT11
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT11                                   0x00000800U
#define LRFDPBE32_EVT0_IRQ_SOFT11_M                                 0x00000800U
#define LRFDPBE32_EVT0_IRQ_SOFT11_S                                         11U
#define LRFDPBE32_EVT0_IRQ_SOFT11_ON                                0x00000800U
#define LRFDPBE32_EVT0_IRQ_SOFT11_OFF                               0x00000000U

// Field:    [10] SOFT10
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT10                                   0x00000400U
#define LRFDPBE32_EVT0_IRQ_SOFT10_M                                 0x00000400U
#define LRFDPBE32_EVT0_IRQ_SOFT10_S                                         10U
#define LRFDPBE32_EVT0_IRQ_SOFT10_ON                                0x00000400U
#define LRFDPBE32_EVT0_IRQ_SOFT10_OFF                               0x00000000U

// Field:     [9] SOFT9
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT9                                    0x00000200U
#define LRFDPBE32_EVT0_IRQ_SOFT9_M                                  0x00000200U
#define LRFDPBE32_EVT0_IRQ_SOFT9_S                                           9U
#define LRFDPBE32_EVT0_IRQ_SOFT9_ON                                 0x00000200U
#define LRFDPBE32_EVT0_IRQ_SOFT9_OFF                                0x00000000U

// Field:     [8] SOFT8
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT8                                    0x00000100U
#define LRFDPBE32_EVT0_IRQ_SOFT8_M                                  0x00000100U
#define LRFDPBE32_EVT0_IRQ_SOFT8_S                                           8U
#define LRFDPBE32_EVT0_IRQ_SOFT8_ON                                 0x00000100U
#define LRFDPBE32_EVT0_IRQ_SOFT8_OFF                                0x00000000U

// Field:     [7] SOFT7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT7                                    0x00000080U
#define LRFDPBE32_EVT0_IRQ_SOFT7_M                                  0x00000080U
#define LRFDPBE32_EVT0_IRQ_SOFT7_S                                           7U
#define LRFDPBE32_EVT0_IRQ_SOFT7_ON                                 0x00000080U
#define LRFDPBE32_EVT0_IRQ_SOFT7_OFF                                0x00000000U

// Field:     [6] SOFT6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT6                                    0x00000040U
#define LRFDPBE32_EVT0_IRQ_SOFT6_M                                  0x00000040U
#define LRFDPBE32_EVT0_IRQ_SOFT6_S                                           6U
#define LRFDPBE32_EVT0_IRQ_SOFT6_ON                                 0x00000040U
#define LRFDPBE32_EVT0_IRQ_SOFT6_OFF                                0x00000000U

// Field:     [5] SOFT5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT5                                    0x00000020U
#define LRFDPBE32_EVT0_IRQ_SOFT5_M                                  0x00000020U
#define LRFDPBE32_EVT0_IRQ_SOFT5_S                                           5U
#define LRFDPBE32_EVT0_IRQ_SOFT5_ON                                 0x00000020U
#define LRFDPBE32_EVT0_IRQ_SOFT5_OFF                                0x00000000U

// Field:     [4] SOFT4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT4                                    0x00000010U
#define LRFDPBE32_EVT0_IRQ_SOFT4_M                                  0x00000010U
#define LRFDPBE32_EVT0_IRQ_SOFT4_S                                           4U
#define LRFDPBE32_EVT0_IRQ_SOFT4_ON                                 0x00000010U
#define LRFDPBE32_EVT0_IRQ_SOFT4_OFF                                0x00000000U

// Field:     [3] SOFT3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT3                                    0x00000008U
#define LRFDPBE32_EVT0_IRQ_SOFT3_M                                  0x00000008U
#define LRFDPBE32_EVT0_IRQ_SOFT3_S                                           3U
#define LRFDPBE32_EVT0_IRQ_SOFT3_ON                                 0x00000008U
#define LRFDPBE32_EVT0_IRQ_SOFT3_OFF                                0x00000000U

// Field:     [2] SOFT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT2                                    0x00000004U
#define LRFDPBE32_EVT0_IRQ_SOFT2_M                                  0x00000004U
#define LRFDPBE32_EVT0_IRQ_SOFT2_S                                           2U
#define LRFDPBE32_EVT0_IRQ_SOFT2_ON                                 0x00000004U
#define LRFDPBE32_EVT0_IRQ_SOFT2_OFF                                0x00000000U

// Field:     [1] SOFT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT1                                    0x00000002U
#define LRFDPBE32_EVT0_IRQ_SOFT1_M                                  0x00000002U
#define LRFDPBE32_EVT0_IRQ_SOFT1_S                                           1U
#define LRFDPBE32_EVT0_IRQ_SOFT1_ON                                 0x00000002U
#define LRFDPBE32_EVT0_IRQ_SOFT1_OFF                                0x00000000U

// Field:     [0] SOFT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVT0_IRQ_SOFT0                                    0x00000001U
#define LRFDPBE32_EVT0_IRQ_SOFT0_M                                  0x00000001U
#define LRFDPBE32_EVT0_IRQ_SOFT0_S                                           0U
#define LRFDPBE32_EVT0_IRQ_SOFT0_ON                                 0x00000001U
#define LRFDPBE32_EVT0_IRQ_SOFT0_OFF                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_EVTMSK0_EVT1
//
//*****************************************************************************
// Field:    [31] MDMFAEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAEMPTY                           0x80000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAEMPTY_M                         0x80000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAEMPTY_S                                 31U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAEMPTY_EN                        0x80000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAEMPTY_DIS                       0x00000000U

// Field:    [30] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_S2RSTOP                              0x40000000U
#define LRFDPBE32_EVTMSK0_EVT1_S2RSTOP_M                            0x40000000U
#define LRFDPBE32_EVTMSK0_EVT1_S2RSTOP_S                                    30U
#define LRFDPBE32_EVTMSK0_EVT1_S2RSTOP_EN                           0x40000000U
#define LRFDPBE32_EVTMSK0_EVT1_S2RSTOP_DIS                          0x00000000U

// Field:    [29] FIFOERR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_FIFOERR                              0x20000000U
#define LRFDPBE32_EVTMSK0_EVT1_FIFOERR_M                            0x20000000U
#define LRFDPBE32_EVTMSK0_EVT1_FIFOERR_S                                    29U
#define LRFDPBE32_EVTMSK0_EVT1_FIFOERR_EN                           0x20000000U
#define LRFDPBE32_EVTMSK0_EVT1_FIFOERR_DIS                          0x00000000U

// Field:    [28] MDMFAFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAFULL                            0x10000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAFULL_M                          0x10000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAFULL_S                                  28U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAFULL_EN                         0x10000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMFAFULL_DIS                        0x00000000U

// Field:    [27] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP2                             0x08000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP2_M                           0x08000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP2_S                                   27U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP2_EN                          0x08000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP2_DIS                         0x00000000U

// Field:    [26] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP1                             0x04000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP1_M                           0x04000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP1_S                                   26U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP1_EN                          0x04000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP1_DIS                         0x00000000U

// Field:    [25] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP0                             0x02000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP0_M                           0x02000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP0_S                                   25U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP0_EN                          0x02000000U
#define LRFDPBE32_EVTMSK0_EVT1_SYSTCMP0_DIS                         0x00000000U

// Field:    [24] MDMMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMMSGBOX                            0x01000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMMSGBOX_M                          0x01000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMMSGBOX_S                                  24U
#define LRFDPBE32_EVTMSK0_EVT1_MDMMSGBOX_EN                         0x01000000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMMSGBOX_DIS                        0x00000000U

// Field:    [23] RFEMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_RFEMSGBOX                            0x00800000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEMSGBOX_M                          0x00800000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEMSGBOX_S                                  23U
#define LRFDPBE32_EVTMSK0_EVT1_RFEMSGBOX_EN                         0x00800000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEMSGBOX_DIS                        0x00000000U

// Field:    [22] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_RFEDAT                               0x00400000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEDAT_M                             0x00400000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEDAT_S                                     22U
#define LRFDPBE32_EVTMSK0_EVT1_RFEDAT_EN                            0x00400000U
#define LRFDPBE32_EVTMSK0_EVT1_RFEDAT_DIS                           0x00000000U

// Field:    [21] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_RFECMD                               0x00200000U
#define LRFDPBE32_EVTMSK0_EVT1_RFECMD_M                             0x00200000U
#define LRFDPBE32_EVTMSK0_EVT1_RFECMD_S                                     21U
#define LRFDPBE32_EVTMSK0_EVT1_RFECMD_EN                            0x00200000U
#define LRFDPBE32_EVTMSK0_EVT1_RFECMD_DIS                           0x00000000U

// Field:    [20] MDMDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMDAT                               0x00100000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMDAT_M                             0x00100000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMDAT_S                                     20U
#define LRFDPBE32_EVTMSK0_EVT1_MDMDAT_EN                            0x00100000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMDAT_DIS                           0x00000000U

// Field:    [19] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMCMD                               0x00080000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMCMD_M                             0x00080000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMCMD_S                                     19U
#define LRFDPBE32_EVTMSK0_EVT1_MDMCMD_EN                            0x00080000U
#define LRFDPBE32_EVTMSK0_EVT1_MDMCMD_DIS                           0x00000000U

// Field:    [18] TIMER1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_TIMER1                               0x00040000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER1_M                             0x00040000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER1_S                                     18U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER1_EN                            0x00040000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER1_DIS                           0x00000000U

// Field:    [17] TIMER0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_TIMER0                               0x00020000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER0_M                             0x00020000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER0_S                                     17U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER0_EN                            0x00020000U
#define LRFDPBE32_EVTMSK0_EVT1_TIMER0_DIS                           0x00000000U

// Field:    [16] PBEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEAPI                               0x00010000U
#define LRFDPBE32_EVTMSK0_EVT1_PBEAPI_M                             0x00010000U
#define LRFDPBE32_EVTMSK0_EVT1_PBEAPI_S                                     16U
#define LRFDPBE32_EVTMSK0_EVT1_PBEAPI_EN                            0x00010000U
#define LRFDPBE32_EVTMSK0_EVT1_PBEAPI_DIS                           0x00000000U

// Field:    [12] TXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MET                      Internal. Only to be used through TI provided API.
// BELOW                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_TXRDBTHR                             0x00001000U
#define LRFDPBE32_EVTMSK0_EVT1_TXRDBTHR_M                           0x00001000U
#define LRFDPBE32_EVTMSK0_EVT1_TXRDBTHR_S                                   12U
#define LRFDPBE32_EVTMSK0_EVT1_TXRDBTHR_MET                         0x00001000U
#define LRFDPBE32_EVTMSK0_EVT1_TXRDBTHR_BELOW                       0x00000000U

// Field:    [11] TXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MET                      Internal. Only to be used through TI provided API.
// BELOW                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_TXWRBTHR                             0x00000800U
#define LRFDPBE32_EVTMSK0_EVT1_TXWRBTHR_M                           0x00000800U
#define LRFDPBE32_EVTMSK0_EVT1_TXWRBTHR_S                                   11U
#define LRFDPBE32_EVTMSK0_EVT1_TXWRBTHR_MET                         0x00000800U
#define LRFDPBE32_EVTMSK0_EVT1_TXWRBTHR_BELOW                       0x00000000U

// Field:    [10] RXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MET                      Internal. Only to be used through TI provided API.
// BELOW                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_RXRDBTHR                             0x00000400U
#define LRFDPBE32_EVTMSK0_EVT1_RXRDBTHR_M                           0x00000400U
#define LRFDPBE32_EVTMSK0_EVT1_RXRDBTHR_S                                   10U
#define LRFDPBE32_EVTMSK0_EVT1_RXRDBTHR_MET                         0x00000400U
#define LRFDPBE32_EVTMSK0_EVT1_RXRDBTHR_BELOW                       0x00000000U

// Field:     [9] RXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MET                      Internal. Only to be used through TI provided API.
// BELOW                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_RXWRBTHR                             0x00000200U
#define LRFDPBE32_EVTMSK0_EVT1_RXWRBTHR_M                           0x00000200U
#define LRFDPBE32_EVTMSK0_EVT1_RXWRBTHR_S                                    9U
#define LRFDPBE32_EVTMSK0_EVT1_RXWRBTHR_MET                         0x00000200U
#define LRFDPBE32_EVTMSK0_EVT1_RXWRBTHR_BELOW                       0x00000000U

// Field:     [8] MDMPROG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_MDMPROG                              0x00000100U
#define LRFDPBE32_EVTMSK0_EVT1_MDMPROG_M                            0x00000100U
#define LRFDPBE32_EVTMSK0_EVT1_MDMPROG_S                                     8U
#define LRFDPBE32_EVTMSK0_EVT1_MDMPROG_ONE                          0x00000100U
#define LRFDPBE32_EVTMSK0_EVT1_MDMPROG_ZERO                         0x00000000U

// Field:     [7] PBEGPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI7                              0x00000080U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI7_M                            0x00000080U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI7_S                                     7U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI7_ONE                          0x00000080U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI7_ZERO                         0x00000000U

// Field:     [6] PBEGPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI6                              0x00000040U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI6_M                            0x00000040U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI6_S                                     6U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI6_ONE                          0x00000040U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI6_ZERO                         0x00000000U

// Field:     [5] PBEGPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI5                              0x00000020U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI5_M                            0x00000020U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI5_S                                     5U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI5_ONE                          0x00000020U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI5_ZERO                         0x00000000U

// Field:     [4] PBEGPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI4                              0x00000010U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI4_M                            0x00000010U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI4_S                                     4U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI4_ONE                          0x00000010U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI4_ZERO                         0x00000000U

// Field:     [3] PBEGPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI3                              0x00000008U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI3_M                            0x00000008U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI3_S                                     3U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI3_ONE                          0x00000008U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI3_ZERO                         0x00000000U

// Field:     [2] PBEGPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI2                              0x00000004U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI2_M                            0x00000004U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI2_S                                     2U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI2_ONE                          0x00000004U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI2_ZERO                         0x00000000U

// Field:     [1] PBEGPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI1                              0x00000002U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI1_M                            0x00000002U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI1_S                                     1U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI1_ONE                          0x00000002U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI1_ZERO                         0x00000000U

// Field:     [0] PBEGPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI0                              0x00000001U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI0_M                            0x00000001U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI0_S                                     0U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI0_ONE                          0x00000001U
#define LRFDPBE32_EVTMSK0_EVT1_PBEGPI0_ZERO                         0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_EVTCLR0_EVTMSK1
//
//*****************************************************************************
// Field:    [31] MDMFAEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAEMPTY                        0x80000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAEMPTY_M                      0x80000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAEMPTY_S                              31U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAEMPTY_CLEAR                  0x80000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAEMPTY_RETAIN                 0x00000000U

// Field:    [30] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_S2RSTOP                           0x40000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_S2RSTOP_M                         0x40000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_S2RSTOP_S                                 30U
#define LRFDPBE32_EVTCLR0_EVTMSK1_S2RSTOP_CLEAR                     0x40000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_S2RSTOP_RETAIN                    0x00000000U

// Field:    [29] FIFOERR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_FIFOERR                           0x20000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_FIFOERR_M                         0x20000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_FIFOERR_S                                 29U
#define LRFDPBE32_EVTCLR0_EVTMSK1_FIFOERR_CLEAR                     0x20000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_FIFOERR_RETAIN                    0x00000000U

// Field:    [28] MDMFAFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAFULL                         0x10000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAFULL_M                       0x10000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAFULL_S                               28U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAFULL_CLEAR                   0x10000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMFAFULL_RETAIN                  0x00000000U

// Field:    [27] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP2                          0x08000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP2_M                        0x08000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP2_S                                27U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP2_CLEAR                    0x08000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP2_RETAIN                   0x00000000U

// Field:    [26] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP1                          0x04000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP1_M                        0x04000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP1_S                                26U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP1_CLEAR                    0x04000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP1_RETAIN                   0x00000000U

// Field:    [25] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP0                          0x02000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP0_M                        0x02000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP0_S                                25U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP0_CLEAR                    0x02000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_SYSTCMP0_RETAIN                   0x00000000U

// Field:    [24] MDMMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMMSGBOX                         0x01000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMMSGBOX_M                       0x01000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMMSGBOX_S                               24U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMMSGBOX_CLEAR                   0x01000000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMMSGBOX_RETAIN                  0x00000000U

// Field:    [23] RFEMSGBOX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEMSGBOX                         0x00800000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEMSGBOX_M                       0x00800000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEMSGBOX_S                               23U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEMSGBOX_CLEAR                   0x00800000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEMSGBOX_RETAIN                  0x00000000U

// Field:    [22] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEDAT                            0x00400000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEDAT_M                          0x00400000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEDAT_S                                  22U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEDAT_CLEAR                      0x00400000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFEDAT_RETAIN                     0x00000000U

// Field:    [21] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFECMD                            0x00200000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFECMD_M                          0x00200000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFECMD_S                                  21U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFECMD_CLEAR                      0x00200000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RFECMD_RETAIN                     0x00000000U

// Field:    [20] MDMDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMDAT                            0x00100000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMDAT_M                          0x00100000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMDAT_S                                  20U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMDAT_CLEAR                      0x00100000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMDAT_RETAIN                     0x00000000U

// Field:    [19] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMCMD                            0x00080000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMCMD_M                          0x00080000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMCMD_S                                  19U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMCMD_CLEAR                      0x00080000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMCMD_RETAIN                     0x00000000U

// Field:    [18] TIMER1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER1                            0x00040000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER1_M                          0x00040000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER1_S                                  18U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER1_CLEAR                      0x00040000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER1_RETAIN                     0x00000000U

// Field:    [17] TIMER0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER0                            0x00020000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER0_M                          0x00020000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER0_S                                  17U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER0_CLEAR                      0x00020000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TIMER0_RETAIN                     0x00000000U

// Field:    [16] PBEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEAPI                            0x00010000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEAPI_M                          0x00010000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEAPI_S                                  16U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEAPI_CLEAR                      0x00010000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEAPI_RETAIN                     0x00000000U

// Field:    [12] TXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXRDBTHR                          0x00001000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXRDBTHR_M                        0x00001000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXRDBTHR_S                                12U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXRDBTHR_EN                       0x00001000U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXRDBTHR_DIS                      0x00000000U

// Field:    [11] TXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXWRBTHR                          0x00000800U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXWRBTHR_M                        0x00000800U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXWRBTHR_S                                11U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXWRBTHR_EN                       0x00000800U
#define LRFDPBE32_EVTCLR0_EVTMSK1_TXWRBTHR_DIS                      0x00000000U

// Field:    [10] RXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXRDBTHR                          0x00000400U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXRDBTHR_M                        0x00000400U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXRDBTHR_S                                10U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXRDBTHR_EN                       0x00000400U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXRDBTHR_DIS                      0x00000000U

// Field:     [9] RXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXWRBTHR                          0x00000200U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXWRBTHR_M                        0x00000200U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXWRBTHR_S                                 9U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXWRBTHR_EN                       0x00000200U
#define LRFDPBE32_EVTCLR0_EVTMSK1_RXWRBTHR_DIS                      0x00000000U

// Field:     [8] MDMPROG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMPROG                           0x00000100U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMPROG_M                         0x00000100U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMPROG_S                                  8U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMPROG_EN                        0x00000100U
#define LRFDPBE32_EVTCLR0_EVTMSK1_MDMPROG_DIS                       0x00000000U

// Field:     [7] PBEGPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI7                           0x00000080U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI7_M                         0x00000080U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI7_S                                  7U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI7_EN                        0x00000080U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI7_DIS                       0x00000000U

// Field:     [6] PBEGPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI6                           0x00000040U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI6_M                         0x00000040U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI6_S                                  6U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI6_EN                        0x00000040U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI6_DIS                       0x00000000U

// Field:     [5] PBEGPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI5                           0x00000020U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI5_M                         0x00000020U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI5_S                                  5U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI5_EN                        0x00000020U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI5_DIS                       0x00000000U

// Field:     [4] PBEGPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI4                           0x00000010U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI4_M                         0x00000010U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI4_S                                  4U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI4_EN                        0x00000010U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI4_DIS                       0x00000000U

// Field:     [3] PBEGPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI3                           0x00000008U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI3_M                         0x00000008U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI3_S                                  3U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI3_EN                        0x00000008U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI3_DIS                       0x00000000U

// Field:     [2] PBEGPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI2                           0x00000004U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI2_M                         0x00000004U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI2_S                                  2U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI2_EN                        0x00000004U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI2_DIS                       0x00000000U

// Field:     [1] PBEGPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI1                           0x00000002U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI1_M                         0x00000002U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI1_S                                  1U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI1_EN                        0x00000002U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI1_DIS                       0x00000000U

// Field:     [0] PBEGPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI0                           0x00000001U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI0_M                         0x00000001U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI0_S                                  0U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI0_EN                        0x00000001U
#define LRFDPBE32_EVTCLR0_EVTMSK1_PBEGPI0_DIS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_PDREQ_EVTCLR1
//
//*****************************************************************************
// Field:    [16] TOPSMPDREQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_TOPSMPDREQ                          0x00010000U
#define LRFDPBE32_PDREQ_EVTCLR1_TOPSMPDREQ_M                        0x00010000U
#define LRFDPBE32_PDREQ_EVTCLR1_TOPSMPDREQ_S                                16U
#define LRFDPBE32_PDREQ_EVTCLR1_TOPSMPDREQ_ON                       0x00010000U
#define LRFDPBE32_PDREQ_EVTCLR1_TOPSMPDREQ_OFF                      0x00000000U

// Field:    [12] TXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_TXRDBTHR                            0x00001000U
#define LRFDPBE32_PDREQ_EVTCLR1_TXRDBTHR_M                          0x00001000U
#define LRFDPBE32_PDREQ_EVTCLR1_TXRDBTHR_S                                  12U
#define LRFDPBE32_PDREQ_EVTCLR1_TXRDBTHR_CLEAR                      0x00001000U
#define LRFDPBE32_PDREQ_EVTCLR1_TXRDBTHR_RETAIN                     0x00000000U

// Field:    [11] TXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_TXWRBTHR                            0x00000800U
#define LRFDPBE32_PDREQ_EVTCLR1_TXWRBTHR_M                          0x00000800U
#define LRFDPBE32_PDREQ_EVTCLR1_TXWRBTHR_S                                  11U
#define LRFDPBE32_PDREQ_EVTCLR1_TXWRBTHR_CLEAR                      0x00000800U
#define LRFDPBE32_PDREQ_EVTCLR1_TXWRBTHR_RETAIN                     0x00000000U

// Field:    [10] RXRDBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_RXRDBTHR                            0x00000400U
#define LRFDPBE32_PDREQ_EVTCLR1_RXRDBTHR_M                          0x00000400U
#define LRFDPBE32_PDREQ_EVTCLR1_RXRDBTHR_S                                  10U
#define LRFDPBE32_PDREQ_EVTCLR1_RXRDBTHR_CLEAR                      0x00000400U
#define LRFDPBE32_PDREQ_EVTCLR1_RXRDBTHR_RETAIN                     0x00000000U

// Field:     [9] RXWRBTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_RXWRBTHR                            0x00000200U
#define LRFDPBE32_PDREQ_EVTCLR1_RXWRBTHR_M                          0x00000200U
#define LRFDPBE32_PDREQ_EVTCLR1_RXWRBTHR_S                                   9U
#define LRFDPBE32_PDREQ_EVTCLR1_RXWRBTHR_CLEAR                      0x00000200U
#define LRFDPBE32_PDREQ_EVTCLR1_RXWRBTHR_RETAIN                     0x00000000U

// Field:     [8] MDMPROG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_MDMPROG                             0x00000100U
#define LRFDPBE32_PDREQ_EVTCLR1_MDMPROG_M                           0x00000100U
#define LRFDPBE32_PDREQ_EVTCLR1_MDMPROG_S                                    8U
#define LRFDPBE32_PDREQ_EVTCLR1_MDMPROG_CLEAR                       0x00000100U
#define LRFDPBE32_PDREQ_EVTCLR1_MDMPROG_RETAIN                      0x00000000U

// Field:     [7] PBEGPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI7                             0x00000080U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI7_M                           0x00000080U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI7_S                                    7U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI7_CLEAR                       0x00000080U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI7_RETAIN                      0x00000000U

// Field:     [6] PBEGPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI6                             0x00000040U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI6_M                           0x00000040U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI6_S                                    6U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI6_CLEAR                       0x00000040U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI6_RETAIN                      0x00000000U

// Field:     [5] PBEGPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI5                             0x00000020U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI5_M                           0x00000020U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI5_S                                    5U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI5_CLEAR                       0x00000020U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI5_RETAIN                      0x00000000U

// Field:     [4] PBEGPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI4                             0x00000010U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI4_M                           0x00000010U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI4_S                                    4U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI4_CLEAR                       0x00000010U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI4_RETAIN                      0x00000000U

// Field:     [3] PBEGPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI3                             0x00000008U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI3_M                           0x00000008U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI3_S                                    3U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI3_CLEAR                       0x00000008U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI3_RETAIN                      0x00000000U

// Field:     [2] PBEGPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI2                             0x00000004U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI2_M                           0x00000004U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI2_S                                    2U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI2_CLEAR                       0x00000004U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI2_RETAIN                      0x00000000U

// Field:     [1] PBEGPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI1                             0x00000002U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI1_M                           0x00000002U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI1_S                                    1U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI1_CLEAR                       0x00000002U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI1_RETAIN                      0x00000000U

// Field:     [0] PBEGPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI0                             0x00000001U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI0_M                           0x00000001U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI0_S                                    0U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI0_CLEAR                       0x00000001U
#define LRFDPBE32_PDREQ_EVTCLR1_PBEGPI0_RETAIN                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MCEDATOUT0_API
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MCEDATOUT0_API_VAL_W                                      16U
#define LRFDPBE32_MCEDATOUT0_API_VAL_M                              0xFFFF0000U
#define LRFDPBE32_MCEDATOUT0_API_VAL_S                                      16U
#define LRFDPBE32_MCEDATOUT0_API_VAL_ALLONES                        0xFFFF0000U
#define LRFDPBE32_MCEDATOUT0_API_VAL_ALLZEROS                       0x00000000U

// Field:   [4:0] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MCEDATOUT0_API_PBECMD_W                                    5U
#define LRFDPBE32_MCEDATOUT0_API_PBECMD_M                           0x0000001FU
#define LRFDPBE32_MCEDATOUT0_API_PBECMD_S                                    0U
#define LRFDPBE32_MCEDATOUT0_API_PBECMD_ALLONES                     0x0000001FU
#define LRFDPBE32_MCEDATOUT0_API_PBECMD_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MCECMDOUT_MCEDATIN0
//
//*****************************************************************************
// Field: [19:16] MCECMDOUT_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCECMDOUT_VAL_W                        4U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCECMDOUT_VAL_M               0x000F0000U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCECMDOUT_VAL_S                       16U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCECMDOUT_VAL_ALLONES         0x000F0000U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCECMDOUT_VAL_ALLZEROS        0x00000000U

// Field:  [15:0] MCEDATIN0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCEDATIN0_VAL_W                       16U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCEDATIN0_VAL_M               0x0000FFFFU
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCEDATIN0_VAL_S                        0U
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCEDATIN0_VAL_ALLONES         0x0000FFFFU
#define LRFDPBE32_MCECMDOUT_MCEDATIN0_MCEDATIN0_VAL_ALLZEROS        0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMAPI_MCECMDIN
//
//*****************************************************************************
// Field: [23:20] PROTOCOLID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMAPI_MCECMDIN_PROTOCOLID_W                               4U
#define LRFDPBE32_MDMAPI_MCECMDIN_PROTOCOLID_M                      0x00F00000U
#define LRFDPBE32_MDMAPI_MCECMDIN_PROTOCOLID_S                              20U
#define LRFDPBE32_MDMAPI_MCECMDIN_PROTOCOLID_ALLONES                0x00F00000U
#define LRFDPBE32_MDMAPI_MCECMDIN_PROTOCOLID_ALLZEROS               0x00000000U

// Field: [19:16] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMAPI_MCECMDIN_MDMCMD_W                                   4U
#define LRFDPBE32_MDMAPI_MCECMDIN_MDMCMD_M                          0x000F0000U
#define LRFDPBE32_MDMAPI_MCECMDIN_MDMCMD_S                                  16U
#define LRFDPBE32_MDMAPI_MCECMDIN_MDMCMD_ALLONES                    0x000F0000U
#define LRFDPBE32_MDMAPI_MCECMDIN_MDMCMD_ALLZEROS                   0x00000000U

// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMAPI_MCECMDIN_VAL_W                                      4U
#define LRFDPBE32_MDMAPI_MCECMDIN_VAL_M                             0x0000000FU
#define LRFDPBE32_MDMAPI_MCECMDIN_VAL_S                                      0U
#define LRFDPBE32_MDMAPI_MCECMDIN_VAL_ALLONES                       0x0000000FU
#define LRFDPBE32_MDMAPI_MCECMDIN_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FREQ_MDMMSGBOX
//
//*****************************************************************************
// Field: [31:16] OFFSET
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_FREQ_MDMMSGBOX_OFFSET_W                                   16U
#define LRFDPBE32_FREQ_MDMMSGBOX_OFFSET_M                           0xFFFF0000U
#define LRFDPBE32_FREQ_MDMMSGBOX_OFFSET_S                                   16U
#define LRFDPBE32_FREQ_MDMMSGBOX_OFFSET_ALLONES                     0xFFFF0000U
#define LRFDPBE32_FREQ_MDMMSGBOX_OFFSET_ALLZEROS                    0x00000000U

// Field:   [7:0] VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_FREQ_MDMMSGBOX_VALUE_W                                     8U
#define LRFDPBE32_FREQ_MDMMSGBOX_VALUE_M                            0x000000FFU
#define LRFDPBE32_FREQ_MDMMSGBOX_VALUE_S                                     0U
#define LRFDPBE32_FREQ_MDMMSGBOX_VALUE_ALLONES                      0x000000FFU
#define LRFDPBE32_FREQ_MDMMSGBOX_VALUE_ALLZEROS                     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFEDATOUT0_MDMLQI
//
//*****************************************************************************
// Field: [31:16] RFEDATOUT0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFEDATOUT0_MDMLQI_RFEDATOUT0_VAL_W                        16U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_RFEDATOUT0_VAL_M                0xFFFF0000U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_RFEDATOUT0_VAL_S                        16U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_RFEDATOUT0_VAL_ALLONES          0xFFFF0000U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_RFEDATOUT0_VAL_ALLZEROS         0x00000000U

// Field:   [7:0] MDMLQI_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFEDATOUT0_MDMLQI_MDMLQI_VAL_W                             8U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_MDMLQI_VAL_M                    0x000000FFU
#define LRFDPBE32_RFEDATOUT0_MDMLQI_MDMLQI_VAL_S                             0U
#define LRFDPBE32_RFEDATOUT0_MDMLQI_MDMLQI_VAL_ALLONES              0x000000FFU
#define LRFDPBE32_RFEDATOUT0_MDMLQI_MDMLQI_VAL_ALLZEROS             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFECMDOUT_RFEDATIN0
//
//*****************************************************************************
// Field: [19:16] RFECMDOUT_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFECMDOUT_VAL_W                        4U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFECMDOUT_VAL_M               0x000F0000U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFECMDOUT_VAL_S                       16U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFECMDOUT_VAL_ALLONES         0x000F0000U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFECMDOUT_VAL_ALLZEROS        0x00000000U

// Field:  [15:0] RFEDATIN0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFEDATIN0_VAL_W                       16U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFEDATIN0_VAL_M               0x0000FFFFU
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFEDATIN0_VAL_S                        0U
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFEDATIN0_VAL_ALLONES         0x0000FFFFU
#define LRFDPBE32_RFECMDOUT_RFEDATIN0_RFEDATIN0_VAL_ALLZEROS        0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFEAPI_RFECMDIN
//
//*****************************************************************************
// Field: [23:20] PROTOCOLID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFEAPI_RFECMDIN_PROTOCOLID_W                               4U
#define LRFDPBE32_RFEAPI_RFECMDIN_PROTOCOLID_M                      0x00F00000U
#define LRFDPBE32_RFEAPI_RFECMDIN_PROTOCOLID_S                              20U
#define LRFDPBE32_RFEAPI_RFECMDIN_PROTOCOLID_ALLONES                0x00F00000U
#define LRFDPBE32_RFEAPI_RFECMDIN_PROTOCOLID_ALLZEROS               0x00000000U

// Field: [19:16] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFEAPI_RFECMDIN_RFECMD_W                                   4U
#define LRFDPBE32_RFEAPI_RFECMDIN_RFECMD_M                          0x000F0000U
#define LRFDPBE32_RFEAPI_RFECMDIN_RFECMD_S                                  16U
#define LRFDPBE32_RFEAPI_RFECMDIN_RFECMD_ALLONES                    0x000F0000U
#define LRFDPBE32_RFEAPI_RFECMDIN_RFECMD_ALLZEROS                   0x00000000U

// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFEAPI_RFECMDIN_VAL_W                                      4U
#define LRFDPBE32_RFEAPI_RFECMDIN_VAL_M                             0x0000000FU
#define LRFDPBE32_RFEAPI_RFECMDIN_VAL_S                                      0U
#define LRFDPBE32_RFEAPI_RFECMDIN_VAL_ALLONES                       0x0000000FU
#define LRFDPBE32_RFEAPI_RFECMDIN_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFECMDPAR1_RFECMDPAR0
//
//*****************************************************************************
// Field: [31:16] RFECMDPAR1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR1_VAL_W                    16U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR1_VAL_M            0xFFFF0000U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR1_VAL_S                    16U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR1_VAL_ALLONES      0xFFFF0000U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR1_VAL_ALLZEROS     0x00000000U

// Field:  [15:0] RFECMDPAR0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR0_VAL_W                    16U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR0_VAL_M            0x0000FFFFU
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR0_VAL_S                     0U
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR0_VAL_ALLONES      0x0000FFFFU
#define LRFDPBE32_RFECMDPAR1_RFECMDPAR0_RFECMDPAR0_VAL_ALLZEROS     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFERSSI_RFEMSGBOX
//
//*****************************************************************************
// Field: [23:16] RFERSSI_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFERSSI_VAL_W                            8U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFERSSI_VAL_M                   0x00FF0000U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFERSSI_VAL_S                           16U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFERSSI_VAL_ALLONES             0x00FF0000U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFERSSI_VAL_ALLZEROS            0x00000000U

// Field:   [7:0] RFEMSGBOX_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFEMSGBOX_VAL_W                          8U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFEMSGBOX_VAL_M                 0x000000FFU
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFEMSGBOX_VAL_S                          0U
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFEMSGBOX_VAL_ALLONES           0x000000FFU
#define LRFDPBE32_RFERSSI_RFEMSGBOX_RFEMSGBOX_VAL_ALLZEROS          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RFERFGAIN_RFERSSIMAX
//
//*****************************************************************************
// Field: [23:16] DBGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_DBGAIN_W                              8U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_DBGAIN_M                     0x00FF0000U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_DBGAIN_S                             16U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_DBGAIN_ALLONES               0x00FF0000U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_DBGAIN_ALLZEROS              0x00000000U

// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_VAL_W                                 8U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_VAL_M                        0x000000FFU
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_VAL_S                                 0U
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_VAL_ALLONES                  0x000000FFU
#define LRFDPBE32_RFERFGAIN_RFERSSIMAX_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMSYNCA
//
//*****************************************************************************
// Field:  [31:0] SWA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMSYNCA_SWA_W                                            32U
#define LRFDPBE32_MDMSYNCA_SWA_M                                    0xFFFFFFFFU
#define LRFDPBE32_MDMSYNCA_SWA_S                                             0U
#define LRFDPBE32_MDMSYNCA_SWA_ALLONES                              0x0000FFFFU
#define LRFDPBE32_MDMSYNCA_SWA_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMSYNCB
//
//*****************************************************************************
// Field:  [31:0] SWB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMSYNCB_SWB_W                                            32U
#define LRFDPBE32_MDMSYNCB_SWB_M                                    0xFFFFFFFFU
#define LRFDPBE32_MDMSYNCB_SWB_S                                             0U
#define LRFDPBE32_MDMSYNCB_SWB_ALLONES                              0x0000FFFFU
#define LRFDPBE32_MDMSYNCB_SWB_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMCMDPAR1_MDMCMDPAR0
//
//*****************************************************************************
// Field: [31:16] MDMCMDPAR1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR1_VAL_W                    16U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR1_VAL_M            0xFFFF0000U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR1_VAL_S                    16U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR1_VAL_ALLONES      0xFFFF0000U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR1_VAL_ALLZEROS     0x00000000U

// Field:  [15:0] MDMCMDPAR0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR0_VAL_W                    16U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR0_VAL_M            0x0000FFFFU
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR0_VAL_S                     0U
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR0_VAL_ALLONES      0x0000FFFFU
#define LRFDPBE32_MDMCMDPAR1_MDMCMDPAR0_MDMCMDPAR0_VAL_ALLZEROS     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMCMDPAR2
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMCMDPAR2_VAL_W                                          16U
#define LRFDPBE32_MDMCMDPAR2_VAL_M                                  0x0000FFFFU
#define LRFDPBE32_MDMCMDPAR2_VAL_S                                           0U
#define LRFDPBE32_MDMCMDPAR2_VAL_ALLONES                            0x0000FFFFU
#define LRFDPBE32_MDMCMDPAR2_VAL_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_POLY0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_POLY0_VAL_W                                               32U
#define LRFDPBE32_POLY0_VAL_M                                       0xFFFFFFFFU
#define LRFDPBE32_POLY0_VAL_S                                                0U
#define LRFDPBE32_POLY0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE32_POLY0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_POLY1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_POLY1_VAL_W                                               32U
#define LRFDPBE32_POLY1_VAL_M                                       0xFFFFFFFFU
#define LRFDPBE32_POLY1_VAL_S                                                0U
#define LRFDPBE32_POLY1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE32_POLY1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FCFG0_PHACFG
//
//*****************************************************************************
// Field:    [23] TXIRQMET
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TXRDBTHR                 Internal. Only to be used through TI provided API.
// TXWRBTHR                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_TXIRQMET                             0x00800000U
#define LRFDPBE32_FCFG0_PHACFG_TXIRQMET_M                           0x00800000U
#define LRFDPBE32_FCFG0_PHACFG_TXIRQMET_S                                   23U
#define LRFDPBE32_FCFG0_PHACFG_TXIRQMET_TXRDBTHR                    0x00800000U
#define LRFDPBE32_FCFG0_PHACFG_TXIRQMET_TXWRBTHR                    0x00000000U

// Field:    [22] RXIRQMET
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RXWRBTHR                 Internal. Only to be used through TI provided API.
// RXRDBTHR                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_RXIRQMET                             0x00400000U
#define LRFDPBE32_FCFG0_PHACFG_RXIRQMET_M                           0x00400000U
#define LRFDPBE32_FCFG0_PHACFG_RXIRQMET_S                                   22U
#define LRFDPBE32_FCFG0_PHACFG_RXIRQMET_RXWRBTHR                    0x00400000U
#define LRFDPBE32_FCFG0_PHACFG_RXIRQMET_RXRDBTHR                    0x00000000U

// Field:    [21] TXACOM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_TXACOM                               0x00200000U
#define LRFDPBE32_FCFG0_PHACFG_TXACOM_M                             0x00200000U
#define LRFDPBE32_FCFG0_PHACFG_TXACOM_S                                     21U
#define LRFDPBE32_FCFG0_PHACFG_TXACOM_EN                            0x00200000U
#define LRFDPBE32_FCFG0_PHACFG_TXACOM_DIS                           0x00000000U

// Field:    [20] TXADEAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_TXADEAL                              0x00100000U
#define LRFDPBE32_FCFG0_PHACFG_TXADEAL_M                            0x00100000U
#define LRFDPBE32_FCFG0_PHACFG_TXADEAL_S                                    20U
#define LRFDPBE32_FCFG0_PHACFG_TXADEAL_EN                           0x00100000U
#define LRFDPBE32_FCFG0_PHACFG_TXADEAL_DIS                          0x00000000U

// Field:    [17] RXACOM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_RXACOM                               0x00020000U
#define LRFDPBE32_FCFG0_PHACFG_RXACOM_M                             0x00020000U
#define LRFDPBE32_FCFG0_PHACFG_RXACOM_S                                     17U
#define LRFDPBE32_FCFG0_PHACFG_RXACOM_EN                            0x00020000U
#define LRFDPBE32_FCFG0_PHACFG_RXACOM_DIS                           0x00000000U

// Field:    [16] RXADEAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_RXADEAL                              0x00010000U
#define LRFDPBE32_FCFG0_PHACFG_RXADEAL_M                            0x00010000U
#define LRFDPBE32_FCFG0_PHACFG_RXADEAL_S                                    16U
#define LRFDPBE32_FCFG0_PHACFG_RXADEAL_EN                           0x00010000U
#define LRFDPBE32_FCFG0_PHACFG_RXADEAL_DIS                          0x00000000U

// Field:   [2:1] MODE1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PARAL                    Internal. Only to be used through TI provided API.
// CASC                     Internal. Only to be used through TI provided API.
// INDEP                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_MODE1_W                                       2U
#define LRFDPBE32_FCFG0_PHACFG_MODE1_M                              0x00000006U
#define LRFDPBE32_FCFG0_PHACFG_MODE1_S                                       1U
#define LRFDPBE32_FCFG0_PHACFG_MODE1_PARAL                          0x00000004U
#define LRFDPBE32_FCFG0_PHACFG_MODE1_CASC                           0x00000002U
#define LRFDPBE32_FCFG0_PHACFG_MODE1_INDEP                          0x00000000U

// Field:     [0] MODE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// WHITE                    Internal. Only to be used through TI provided API.
// CRC                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG0_PHACFG_MODE0                                0x00000001U
#define LRFDPBE32_FCFG0_PHACFG_MODE0_M                              0x00000001U
#define LRFDPBE32_FCFG0_PHACFG_MODE0_S                                       0U
#define LRFDPBE32_FCFG0_PHACFG_MODE0_WHITE                          0x00000001U
#define LRFDPBE32_FCFG0_PHACFG_MODE0_CRC                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FCFG2_FCFG1
//
//*****************************************************************************
// Field: [26:24] TXHSIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// WORD                     Internal. Only to be used through TI provided API.
// HALFW                    Internal. Only to be used through TI provided API.
// BYTE                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_W                                      3U
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_M                             0x07000000U
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_S                                     24U
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_WORD                          0x02000000U
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_HALFW                         0x01000000U
#define LRFDPBE32_FCFG2_FCFG1_TXHSIZE_BYTE                          0x00000000U

// Field: [23:16] TXSIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG2_FCFG1_TXSIZE_W                                       8U
#define LRFDPBE32_FCFG2_FCFG1_TXSIZE_M                              0x00FF0000U
#define LRFDPBE32_FCFG2_FCFG1_TXSIZE_S                                      16U
#define LRFDPBE32_FCFG2_FCFG1_TXSIZE_ONES                           0x00FF0000U
#define LRFDPBE32_FCFG2_FCFG1_TXSIZE_ZEROS                          0x00000000U

// Field:   [8:0] TXSTRT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG2_FCFG1_TXSTRT_W                                       9U
#define LRFDPBE32_FCFG2_FCFG1_TXSTRT_M                              0x000001FFU
#define LRFDPBE32_FCFG2_FCFG1_TXSTRT_S                                       0U
#define LRFDPBE32_FCFG2_FCFG1_TXSTRT_ONES                           0x000001FFU
#define LRFDPBE32_FCFG2_FCFG1_TXSTRT_ZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FCFG4_FCFG3
//
//*****************************************************************************
// Field: [26:24] RXHSIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// WORD                     Internal. Only to be used through TI provided API.
// HALFW                    Internal. Only to be used through TI provided API.
// BYTE                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_W                                      3U
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_M                             0x07000000U
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_S                                     24U
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_WORD                          0x02000000U
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_HALFW                         0x01000000U
#define LRFDPBE32_FCFG4_FCFG3_RXHSIZE_BYTE                          0x00000000U

// Field: [23:16] RXSIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG4_FCFG3_RXSIZE_W                                       8U
#define LRFDPBE32_FCFG4_FCFG3_RXSIZE_M                              0x00FF0000U
#define LRFDPBE32_FCFG4_FCFG3_RXSIZE_S                                      16U
#define LRFDPBE32_FCFG4_FCFG3_RXSIZE_ONES                           0x00FF0000U
#define LRFDPBE32_FCFG4_FCFG3_RXSIZE_ZEROS                          0x00000000U

// Field:   [8:0] RXSTRT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FCFG4_FCFG3_RXSTRT_W                                       9U
#define LRFDPBE32_FCFG4_FCFG3_RXSTRT_M                              0x000001FFU
#define LRFDPBE32_FCFG4_FCFG3_RXSTRT_S                                       0U
#define LRFDPBE32_FCFG4_FCFG3_RXSTRT_ONES                           0x000001FFU
#define LRFDPBE32_FCFG4_FCFG3_RXSTRT_ZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFWBTHRS_FCFG5
//
//*****************************************************************************
// Field: [25:16] BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFWBTHRS_FCFG5_BYTES_W                                   10U
#define LRFDPBE32_RXFWBTHRS_FCFG5_BYTES_M                           0x03FF0000U
#define LRFDPBE32_RXFWBTHRS_FCFG5_BYTES_S                                   16U
#define LRFDPBE32_RXFWBTHRS_FCFG5_BYTES_ALLONES                     0x03FF0000U
#define LRFDPBE32_RXFWBTHRS_FCFG5_BYTES_ALLZEROS                    0x00000000U

// Field:   [8:6] DMASREQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TXFIFOFREE               Internal. Only to be used through TI provided API.
// TXFIFOMD                 Internal. Only to be used through TI provided API.
// RXFIFOFREE               Internal. Only to be used through TI provided API.
// RXFIFOMD                 Internal. Only to be used through TI provided API.
// NONE                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_W                                  3U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_M                         0x000001C0U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_S                                  6U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_TXFIFOFREE                0x00000100U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_TXFIFOMD                  0x000000C0U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_RXFIFOFREE                0x00000080U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_RXFIFOMD                  0x00000040U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMASREQ_NONE                      0x00000000U

// Field:   [4:0] DMAREQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TXFIFO_COMMIT            Internal. Only to be used through TI provided API.
// TXFIFO_DISCARD           Internal. Only to be used through TI provided API.
// TXFIFO_RETRY             Internal. Only to be used through TI provided API.
// TXFIFO_DEALLOC           Internal. Only to be used through TI provided API.
// TXFIFO_RESET             Internal. Only to be used through TI provided API.
// TXWRBTHR_MET             Internal. Only to be used through TI provided API.
// TXRDBTHR_MET             Internal. Only to be used through TI provided API.
// RXFIFO_COMMIT            Internal. Only to be used through TI provided API.
// RXFIFO_DISCARD           Internal. Only to be used through TI provided API.
// RXFIFO_RETRY             Internal. Only to be used through TI provided API.
// RXFIFO_DEALLOC           Internal. Only to be used through TI provided API.
// RXFIFO_RESET             Internal. Only to be used through TI provided API.
// RXWRBTHR_MET             Internal. Only to be used through TI provided API.
// RXRDBTHR_MET             Internal. Only to be used through TI provided API.
// NONE                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_W                                   5U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_M                          0x0000001FU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_S                                   0U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXFIFO_COMMIT              0x0000000FU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXFIFO_DISCARD             0x0000000EU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXFIFO_RETRY               0x0000000DU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXFIFO_DEALLOC             0x0000000CU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXFIFO_RESET               0x0000000BU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXWRBTHR_MET               0x0000000AU
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_TXRDBTHR_MET               0x00000009U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXFIFO_COMMIT              0x00000007U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXFIFO_DISCARD             0x00000006U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXFIFO_RETRY               0x00000005U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXFIFO_DEALLOC             0x00000004U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXFIFO_RESET               0x00000003U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXWRBTHR_MET               0x00000002U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_RXRDBTHR_MET               0x00000001U
#define LRFDPBE32_RXFWBTHRS_FCFG5_DMAREQ_NONE                       0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFWBTHRS_RXFRBTHRS
//
//*****************************************************************************
// Field: [25:16] TXFWBTHRS_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_TXFWBTHRS_BYTES_W                     10U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_TXFWBTHRS_BYTES_M             0x03FF0000U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_TXFWBTHRS_BYTES_S                     16U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_TXFWBTHRS_BYTES_ALLONES       0x03FF0000U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_TXFWBTHRS_BYTES_ALLZEROS      0x00000000U

// Field:   [9:0] RXFRBTHRS_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_RXFRBTHRS_BYTES_W                     10U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_RXFRBTHRS_BYTES_M             0x000003FFU
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_RXFRBTHRS_BYTES_S                      0U
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_RXFRBTHRS_BYTES_ALLONES       0x000003FFU
#define LRFDPBE32_TXFWBTHRS_RXFRBTHRS_RXFRBTHRS_BYTES_ALLZEROS      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TIMCTL_TXFRBTHRS
//
//*****************************************************************************
// Field: [31:27] CPTSRC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC1_W                                 5U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC1_M                        0xF8000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC1_S                                27U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC1_ALLONES                  0xF8000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC1_ALLZEROS                 0x00000000U

// Field:    [26] ENCPT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT1                           0x04000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT1_M                         0x04000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT1_S                                 26U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT1_ON                        0x04000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT1_OFF                       0x00000000U

// Field:    [25] SRC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PRE1                     Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC1                             0x02000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC1_M                           0x02000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC1_S                                   25U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC1_PRE1                        0x02000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC1_CLK                         0x00000000U

// Field:    [24] EN1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN1                              0x01000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN1_M                            0x01000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN1_S                                    24U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN1_ON                           0x01000000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN1_OFF                          0x00000000U

// Field: [23:19] CPTSRC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC0_W                                 5U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC0_M                        0x00F80000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC0_S                                19U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC0_ALLONES                  0x00F80000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_CPTSRC0_ALLZEROS                 0x00000000U

// Field:    [18] ENCPT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT0                           0x00040000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT0_M                         0x00040000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT0_S                                 18U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT0_ON                        0x00040000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_ENCPT0_OFF                       0x00000000U

// Field:    [17] SRC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PRE0                     Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC0                             0x00020000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC0_M                           0x00020000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC0_S                                   17U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC0_PRE0                        0x00020000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_SRC0_CLK                         0x00000000U

// Field:    [16] EN0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN0                              0x00010000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN0_M                            0x00010000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN0_S                                    16U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN0_ON                           0x00010000U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_EN0_OFF                          0x00000000U

// Field:   [9:0] BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCTL_TXFRBTHRS_BYTES_W                                  10U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_BYTES_M                          0x000003FFU
#define LRFDPBE32_TIMCTL_TXFRBTHRS_BYTES_S                                   0U
#define LRFDPBE32_TIMCTL_TXFRBTHRS_BYTES_ALLONES                    0x000003FFU
#define LRFDPBE32_TIMCTL_TXFRBTHRS_BYTES_ALLZEROS                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TIMPER0_TIMPRE
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMPER0_TIMPRE_VAL_W                                      16U
#define LRFDPBE32_TIMPER0_TIMPRE_VAL_M                              0xFFFF0000U
#define LRFDPBE32_TIMPER0_TIMPRE_VAL_S                                      16U
#define LRFDPBE32_TIMPER0_TIMPRE_VAL_ALLONES                        0xFFFF0000U
#define LRFDPBE32_TIMPER0_TIMPRE_VAL_ALLZEROS                       0x00000000U

// Field:  [13:8] PRE1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV64                    Internal. Only to be used through TI provided API.
// NO_DIV                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMPER0_TIMPRE_PRE1_W                                      6U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE1_M                             0x00003F00U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE1_S                                      8U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE1_DIV64                         0x00003F00U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE1_NO_DIV                        0x00000000U

// Field:   [5:0] PRE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV64                    Internal. Only to be used through TI provided API.
// NO_DIV                   Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMPER0_TIMPRE_PRE0_W                                      6U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE0_M                             0x0000003FU
#define LRFDPBE32_TIMPER0_TIMPRE_PRE0_S                                      0U
#define LRFDPBE32_TIMPER0_TIMPRE_PRE0_DIV64                         0x0000003FU
#define LRFDPBE32_TIMPER0_TIMPRE_PRE0_NO_DIV                        0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TIMCAPT0_TIMPER1
//
//*****************************************************************************
// Field: [31:16] VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCAPT0_TIMPER1_VALUE_W                                  16U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VALUE_M                          0xFFFF0000U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VALUE_S                                  16U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VALUE_ALLONES                    0xFFFF0000U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VALUE_ALLZEROS                   0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCAPT0_TIMPER1_VAL_W                                    16U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VAL_M                            0x0000FFFFU
#define LRFDPBE32_TIMCAPT0_TIMPER1_VAL_S                                     0U
#define LRFDPBE32_TIMCAPT0_TIMPER1_VAL_ALLONES                      0x0000FFFFU
#define LRFDPBE32_TIMCAPT0_TIMPER1_VAL_ALLZEROS                     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TIMCAPT1
//
//*****************************************************************************
// Field:  [15:0] VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TIMCAPT1_VALUE_W                                          16U
#define LRFDPBE32_TIMCAPT1_VALUE_M                                  0x0000FFFFU
#define LRFDPBE32_TIMCAPT1_VALUE_S                                           0U
#define LRFDPBE32_TIMCAPT1_VALUE_ALLONES                            0x0000FFFFU
#define LRFDPBE32_TIMCAPT1_VALUE_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TRCSTAT_TRCCTL
//
//*****************************************************************************
// Field:    [16] BUSY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_TRCSTAT_TRCCTL_BUSY                               0x00010000U
#define LRFDPBE32_TRCSTAT_TRCCTL_BUSY_M                             0x00010000U
#define LRFDPBE32_TRCSTAT_TRCCTL_BUSY_S                                     16U
#define LRFDPBE32_TRCSTAT_TRCCTL_BUSY_ONE                           0x00010000U
#define LRFDPBE32_TRCSTAT_TRCCTL_BUSY_ZERO                          0x00000000U

// Field:     [0] SEND
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_TRCSTAT_TRCCTL_SEND                               0x00000001U
#define LRFDPBE32_TRCSTAT_TRCCTL_SEND_M                             0x00000001U
#define LRFDPBE32_TRCSTAT_TRCCTL_SEND_S                                      0U
#define LRFDPBE32_TRCSTAT_TRCCTL_SEND_ONE                           0x00000001U
#define LRFDPBE32_TRCSTAT_TRCCTL_SEND_ZERO                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TRCPAR0_TRCCMD
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TRCPAR0_TRCCMD_VAL_W                                      16U
#define LRFDPBE32_TRCPAR0_TRCCMD_VAL_M                              0xFFFF0000U
#define LRFDPBE32_TRCPAR0_TRCCMD_VAL_S                                      16U
#define LRFDPBE32_TRCPAR0_TRCCMD_VAL_ALLONES                        0xFFFF0000U
#define LRFDPBE32_TRCPAR0_TRCCMD_VAL_ALLZEROS                       0x00000000U

// Field:   [9:8] PARCNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TRCPAR0_TRCCMD_PARCNT_W                                    2U
#define LRFDPBE32_TRCPAR0_TRCCMD_PARCNT_M                           0x00000300U
#define LRFDPBE32_TRCPAR0_TRCCMD_PARCNT_S                                    8U
#define LRFDPBE32_TRCPAR0_TRCCMD_PARCNT_ALLONES                     0x00000300U
#define LRFDPBE32_TRCPAR0_TRCCMD_PARCNT_ALLZEROS                    0x00000000U

// Field:   [7:0] PKTHDR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TRCPAR0_TRCCMD_PKTHDR_W                                    8U
#define LRFDPBE32_TRCPAR0_TRCCMD_PKTHDR_M                           0x000000FFU
#define LRFDPBE32_TRCPAR0_TRCCMD_PKTHDR_S                                    0U
#define LRFDPBE32_TRCPAR0_TRCCMD_PKTHDR_ALLONES                     0x000000FFU
#define LRFDPBE32_TRCPAR0_TRCCMD_PKTHDR_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_GPOCTRL_TRCPAR1
//
//*****************************************************************************
// Field:    [23] GPO7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO7                              0x00800000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO7_M                            0x00800000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO7_S                                    23U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO7_ONE                          0x00800000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO7_ZERO                         0x00000000U

// Field:    [22] GPO6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO6                              0x00400000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO6_M                            0x00400000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO6_S                                    22U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO6_ONE                          0x00400000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO6_ZERO                         0x00000000U

// Field:    [21] GPO5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO5                              0x00200000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO5_M                            0x00200000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO5_S                                    21U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO5_ONE                          0x00200000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO5_ZERO                         0x00000000U

// Field:    [20] GPO4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO4                              0x00100000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO4_M                            0x00100000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO4_S                                    20U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO4_ONE                          0x00100000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO4_ZERO                         0x00000000U

// Field:    [19] GPO3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO3                              0x00080000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO3_M                            0x00080000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO3_S                                    19U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO3_ONE                          0x00080000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO3_ZERO                         0x00000000U

// Field:    [18] GPO2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO2                              0x00040000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO2_M                            0x00040000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO2_S                                    18U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO2_ONE                          0x00040000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO2_ZERO                         0x00000000U

// Field:    [17] GPO1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO1                              0x00020000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO1_M                            0x00020000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO1_S                                    17U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO1_ONE                          0x00020000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO1_ZERO                         0x00000000U

// Field:    [16] GPO0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO0                              0x00010000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO0_M                            0x00010000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO0_S                                    16U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO0_ONE                          0x00010000U
#define LRFDPBE32_GPOCTRL_TRCPAR1_GPO0_ZERO                         0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPOCTRL_TRCPAR1_VAL_W                                     16U
#define LRFDPBE32_GPOCTRL_TRCPAR1_VAL_M                             0x0000FFFFU
#define LRFDPBE32_GPOCTRL_TRCPAR1_VAL_S                                      0U
#define LRFDPBE32_GPOCTRL_TRCPAR1_VAL_ALLONES                       0x0000FFFFU
#define LRFDPBE32_GPOCTRL_TRCPAR1_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMFRD_MDMFWR
//
//*****************************************************************************
// Field: [31:16] PAYLOADOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADOUT_W                                16U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADOUT_M                        0xFFFF0000U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADOUT_S                                16U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADOUT_ALLONES                  0xFFFF0000U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADOUT_ALLZEROS                 0x00000000U

// Field:  [15:0] PAYLOADIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADIN_W                                 16U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADIN_M                         0x0000FFFFU
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADIN_S                                  0U
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADIN_ALLONES                   0x0000FFFFU
#define LRFDPBE32_MDMFRD_MDMFWR_PAYLOADIN_ALLZEROS                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMFRDCTL_MDMFWRCTL
//
//*****************************************************************************
// Field: [19:16] WORDSZRD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BITS16                   Internal. Only to be used through TI provided API.
// BITS15                   Internal. Only to be used through TI provided API.
// BITS14                   Internal. Only to be used through TI provided API.
// BITS13                   Internal. Only to be used through TI provided API.
// BITS12                   Internal. Only to be used through TI provided API.
// BITS11                   Internal. Only to be used through TI provided API.
// BITS10                   Internal. Only to be used through TI provided API.
// BITS9                    Internal. Only to be used through TI provided API.
// BITS8                    Internal. Only to be used through TI provided API.
// BITS7                    Internal. Only to be used through TI provided API.
// BITS6                    Internal. Only to be used through TI provided API.
// BITS5                    Internal. Only to be used through TI provided API.
// BITS4                    Internal. Only to be used through TI provided API.
// BITS3                    Internal. Only to be used through TI provided API.
// BITS2                    Internal. Only to be used through TI provided API.
// BITS1                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_W                             4U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_M                    0x000F0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_S                            16U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS16               0x000F0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS15               0x000E0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS14               0x000D0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS13               0x000C0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS12               0x000B0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS11               0x000A0000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS10               0x00090000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS9                0x00080000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS8                0x00070000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS7                0x00060000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS6                0x00050000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS5                0x00040000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS4                0x00030000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS3                0x00020000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS2                0x00010000U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZRD_BITS1                0x00000000U

// Field:   [3:0] WORDSZWR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BITS16                   Internal. Only to be used through TI provided API.
// BITS15                   Internal. Only to be used through TI provided API.
// BITS14                   Internal. Only to be used through TI provided API.
// BITS13                   Internal. Only to be used through TI provided API.
// BITS12                   Internal. Only to be used through TI provided API.
// BITS11                   Internal. Only to be used through TI provided API.
// BITS10                   Internal. Only to be used through TI provided API.
// BITS9                    Internal. Only to be used through TI provided API.
// BITS8                    Internal. Only to be used through TI provided API.
// BITS7                    Internal. Only to be used through TI provided API.
// BITS6                    Internal. Only to be used through TI provided API.
// BITS5                    Internal. Only to be used through TI provided API.
// BITS4                    Internal. Only to be used through TI provided API.
// BITS3                    Internal. Only to be used through TI provided API.
// BITS2                    Internal. Only to be used through TI provided API.
// BITS1                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_W                             4U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_M                    0x0000000FU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_S                             0U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS16               0x0000000FU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS15               0x0000000EU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS14               0x0000000DU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS13               0x0000000CU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS12               0x0000000BU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS11               0x0000000AU
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS10               0x00000009U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS9                0x00000008U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS8                0x00000007U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS7                0x00000006U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS6                0x00000005U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS5                0x00000004U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS4                0x00000003U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS3                0x00000002U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS2                0x00000001U
#define LRFDPBE32_MDMFRDCTL_MDMFWRCTL_WORDSZWR_BITS1                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_MDMFSTA_MDMFCFG
//
//*****************************************************************************
// Field:    [21] OVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_OVFL                              0x00200000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_OVFL_M                            0x00200000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_OVFL_S                                    21U
#define LRFDPBE32_MDMFSTA_MDMFCFG_OVFL_ONE                          0x00200000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_OVFL_ZERO                         0x00000000U

// Field:    [20] ALMOSTFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTFULL                        0x00100000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTFULL_M                      0x00100000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTFULL_S                              20U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTFULL_ONE                    0x00100000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTFULL_ZERO                   0x00000000U

// Field:    [19] ALMOSTEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTEMPTY                       0x00080000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTEMPTY_M                     0x00080000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTEMPTY_S                             19U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTEMPTY_ONE                   0x00080000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_ALMOSTEMPTY_ZERO                  0x00000000U

// Field:    [18] UNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_UNFL                              0x00040000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_UNFL_M                            0x00040000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_UNFL_S                                    18U
#define LRFDPBE32_MDMFSTA_MDMFCFG_UNFL_ONE                          0x00040000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_UNFL_ZERO                         0x00000000U

// Field:    [17] RXVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_RXVALID                           0x00020000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_RXVALID_M                         0x00020000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_RXVALID_S                                 17U
#define LRFDPBE32_MDMFSTA_MDMFCFG_RXVALID_ONE                       0x00020000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_RXVALID_ZERO                      0x00000000U

// Field:    [16] TXREADY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_TXREADY                           0x00010000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_TXREADY_M                         0x00010000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_TXREADY_S                                 16U
#define LRFDPBE32_MDMFSTA_MDMFCFG_TXREADY_ONE                       0x00010000U
#define LRFDPBE32_MDMFSTA_MDMFCFG_TXREADY_ZERO                      0x00000000U

// Field:  [15:8] AFULLTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_AFULLTHR_W                                 8U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AFULLTHR_M                        0x0000FF00U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AFULLTHR_S                                 8U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AFULLTHR_ALLONES                  0x0000FF00U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AFULLTHR_ALLZEROS                 0x00000000U

// Field:   [7:0] AEMPTYTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_MDMFSTA_MDMFCFG_AEMPTYTHR_W                                8U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AEMPTYTHR_M                       0x000000FFU
#define LRFDPBE32_MDMFSTA_MDMFCFG_AEMPTYTHR_S                                0U
#define LRFDPBE32_MDMFSTA_MDMFCFG_AEMPTYTHR_ALLONES                 0x000000FFU
#define LRFDPBE32_MDMFSTA_MDMFCFG_AEMPTYTHR_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_PHASTA
//
//*****************************************************************************
// Field: [17:16] BUSY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BUSY                     Internal. Only to be used through TI provided API.
// IDLE                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_PHASTA_BUSY_W                                              2U
#define LRFDPBE32_PHASTA_BUSY_M                                     0x00030000U
#define LRFDPBE32_PHASTA_BUSY_S                                             16U
#define LRFDPBE32_PHASTA_BUSY_BUSY                                  0x00010000U
#define LRFDPBE32_PHASTA_BUSY_IDLE                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR0_VAL_W                                               32U
#define LRFDPBE32_LFSR0_VAL_M                                       0xFFFFFFFFU
#define LRFDPBE32_LFSR0_VAL_S                                                0U
#define LRFDPBE32_LFSR0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE32_LFSR0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR0BR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR0BR_VAL_W                                             32U
#define LRFDPBE32_LFSR0BR_VAL_M                                     0xFFFFFFFFU
#define LRFDPBE32_LFSR0BR_VAL_S                                              0U
#define LRFDPBE32_LFSR0BR_VAL_ALLONES                               0x0000FFFFU
#define LRFDPBE32_LFSR0BR_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR1_VAL_W                                               32U
#define LRFDPBE32_LFSR1_VAL_M                                       0xFFFFFFFFU
#define LRFDPBE32_LFSR1_VAL_S                                                0U
#define LRFDPBE32_LFSR1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE32_LFSR1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR1BR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR1BR_VAL_W                                             32U
#define LRFDPBE32_LFSR1BR_VAL_M                                     0xFFFFFFFFU
#define LRFDPBE32_LFSR1BR_VAL_S                                              0U
#define LRFDPBE32_LFSR1BR_VAL_ALLONES                               0x0000FFFFU
#define LRFDPBE32_LFSR1BR_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR0N_LFSR0INL
//
//*****************************************************************************
// Field: [19:16] SIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR0N_LFSR0INL_SIZE_W                                     4U
#define LRFDPBE32_LFSR0N_LFSR0INL_SIZE_M                            0x000F0000U
#define LRFDPBE32_LFSR0N_LFSR0INL_SIZE_S                                    16U
#define LRFDPBE32_LFSR0N_LFSR0INL_SIZE_ALLONES                      0x000F0000U
#define LRFDPBE32_LFSR0N_LFSR0INL_SIZE_ALLZEROS                     0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR0N_LFSR0INL_VAL_W                                     16U
#define LRFDPBE32_LFSR0N_LFSR0INL_VAL_M                             0x0000FFFFU
#define LRFDPBE32_LFSR0N_LFSR0INL_VAL_S                                      0U
#define LRFDPBE32_LFSR0N_LFSR0INL_VAL_ALLONES                       0x00000003U
#define LRFDPBE32_LFSR0N_LFSR0INL_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_PHAOUT0_LFSR0INM
//
//*****************************************************************************
// Field: [31:16] PHAOUT0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_PHAOUT0_LFSR0INM_PHAOUT0_VAL_W                            16U
#define LRFDPBE32_PHAOUT0_LFSR0INM_PHAOUT0_VAL_M                    0xFFFF0000U
#define LRFDPBE32_PHAOUT0_LFSR0INM_PHAOUT0_VAL_S                            16U
#define LRFDPBE32_PHAOUT0_LFSR0INM_PHAOUT0_VAL_ALLONES              0xDCD70000U
#define LRFDPBE32_PHAOUT0_LFSR0INM_PHAOUT0_VAL_ALLZEROS             0x00000000U

// Field:  [15:0] LFSR0INM_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_PHAOUT0_LFSR0INM_LFSR0INM_VAL_W                           16U
#define LRFDPBE32_PHAOUT0_LFSR0INM_LFSR0INM_VAL_M                   0x0000FFFFU
#define LRFDPBE32_PHAOUT0_LFSR0INM_LFSR0INM_VAL_S                            0U
#define LRFDPBE32_PHAOUT0_LFSR0INM_LFSR0INM_VAL_ONE                 0x00000001U
#define LRFDPBE32_PHAOUT0_LFSR0INM_LFSR0INM_VAL_ZERO                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_LFSR1N_LFSR1INL
//
//*****************************************************************************
// Field: [19:16] SIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR1N_LFSR1INL_SIZE_W                                     4U
#define LRFDPBE32_LFSR1N_LFSR1INL_SIZE_M                            0x000F0000U
#define LRFDPBE32_LFSR1N_LFSR1INL_SIZE_S                                    16U
#define LRFDPBE32_LFSR1N_LFSR1INL_SIZE_ALLONES                      0x000F0000U
#define LRFDPBE32_LFSR1N_LFSR1INL_SIZE_ALLZEROS                     0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_LFSR1N_LFSR1INL_VAL_W                                     16U
#define LRFDPBE32_LFSR1N_LFSR1INL_VAL_M                             0x0000FFFFU
#define LRFDPBE32_LFSR1N_LFSR1INL_VAL_S                                      0U
#define LRFDPBE32_LFSR1N_LFSR1INL_VAL_ALLONES                       0x00000003U
#define LRFDPBE32_LFSR1N_LFSR1INL_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_PHAOUT0BR_LFSR1INM
//
//*****************************************************************************
// Field: [31:16] PHAOUT0BR_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_PHAOUT0BR_VAL_W                        16U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_PHAOUT0BR_VAL_M                0xFFFF0000U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_PHAOUT0BR_VAL_S                        16U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_PHAOUT0BR_VAL_ALLONES          0xFFFF0000U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_PHAOUT0BR_VAL_ALLZEROS         0x00000000U

// Field:  [15:0] LFSR1INM_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_LFSR1INM_VAL_W                         16U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_LFSR1INM_VAL_M                 0x0000FFFFU
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_LFSR1INM_VAL_S                          0U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_LFSR1INM_VAL_ONE               0x00000001U
#define LRFDPBE32_PHAOUT0BR_LFSR1INM_LFSR1INM_VAL_ZERO              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_SYSTIM0
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_SYSTIM0_VAL_W                                             32U
#define LRFDPBE32_SYSTIM0_VAL_M                                     0xFFFFFFFFU
#define LRFDPBE32_SYSTIM0_VAL_S                                              0U
#define LRFDPBE32_SYSTIM0_VAL_ONE                                   0x00000001U
#define LRFDPBE32_SYSTIM0_VAL_ZERO                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_SYSTIM1
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_SYSTIM1_VAL_W                                             32U
#define LRFDPBE32_SYSTIM1_VAL_M                                     0xFFFFFFFFU
#define LRFDPBE32_SYSTIM1_VAL_S                                              0U
#define LRFDPBE32_SYSTIM1_VAL_ONE                                   0x00000001U
#define LRFDPBE32_SYSTIM1_VAL_ZERO                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_SYSTIM2
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_SYSTIM2_VAL_W                                             32U
#define LRFDPBE32_SYSTIM2_VAL_M                                     0xFFFFFFFFU
#define LRFDPBE32_SYSTIM2_VAL_S                                              0U
#define LRFDPBE32_SYSTIM2_VAL_ONE                                   0x00000001U
#define LRFDPBE32_SYSTIM2_VAL_ZERO                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_GPI
//
//*****************************************************************************
// Field:     [7] GPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI7                                          0x00000080U
#define LRFDPBE32_GPI_GPI7_M                                        0x00000080U
#define LRFDPBE32_GPI_GPI7_S                                                 7U
#define LRFDPBE32_GPI_GPI7_ONE                                      0x00000080U
#define LRFDPBE32_GPI_GPI7_ZERO                                     0x00000000U

// Field:     [6] GPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI6                                          0x00000040U
#define LRFDPBE32_GPI_GPI6_M                                        0x00000040U
#define LRFDPBE32_GPI_GPI6_S                                                 6U
#define LRFDPBE32_GPI_GPI6_ONE                                      0x00000040U
#define LRFDPBE32_GPI_GPI6_ZERO                                     0x00000000U

// Field:     [5] GPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI5                                          0x00000020U
#define LRFDPBE32_GPI_GPI5_M                                        0x00000020U
#define LRFDPBE32_GPI_GPI5_S                                                 5U
#define LRFDPBE32_GPI_GPI5_ONE                                      0x00000020U
#define LRFDPBE32_GPI_GPI5_ZERO                                     0x00000000U

// Field:     [4] GPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI4                                          0x00000010U
#define LRFDPBE32_GPI_GPI4_M                                        0x00000010U
#define LRFDPBE32_GPI_GPI4_S                                                 4U
#define LRFDPBE32_GPI_GPI4_ONE                                      0x00000010U
#define LRFDPBE32_GPI_GPI4_ZERO                                     0x00000000U

// Field:     [3] GPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI3                                          0x00000008U
#define LRFDPBE32_GPI_GPI3_M                                        0x00000008U
#define LRFDPBE32_GPI_GPI3_S                                                 3U
#define LRFDPBE32_GPI_GPI3_ONE                                      0x00000008U
#define LRFDPBE32_GPI_GPI3_ZERO                                     0x00000000U

// Field:     [2] GPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI2                                          0x00000004U
#define LRFDPBE32_GPI_GPI2_M                                        0x00000004U
#define LRFDPBE32_GPI_GPI2_S                                                 2U
#define LRFDPBE32_GPI_GPI2_ONE                                      0x00000004U
#define LRFDPBE32_GPI_GPI2_ZERO                                     0x00000000U

// Field:     [1] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI1                                          0x00000002U
#define LRFDPBE32_GPI_GPI1_M                                        0x00000002U
#define LRFDPBE32_GPI_GPI1_S                                                 1U
#define LRFDPBE32_GPI_GPI1_ONE                                      0x00000002U
#define LRFDPBE32_GPI_GPI1_ZERO                                     0x00000000U

// Field:     [0] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDPBE32_GPI_GPI0                                          0x00000001U
#define LRFDPBE32_GPI_GPI0_M                                        0x00000001U
#define LRFDPBE32_GPI_GPI0_S                                                 0U
#define LRFDPBE32_GPI_GPI0_ONE                                      0x00000001U
#define LRFDPBE32_GPI_GPI0_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_FSTAT_FCMD
//
//*****************************************************************************
// Field:    [27] TXUNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_TXUNFL                                 0x08000000U
#define LRFDPBE32_FSTAT_FCMD_TXUNFL_M                               0x08000000U
#define LRFDPBE32_FSTAT_FCMD_TXUNFL_S                                       27U
#define LRFDPBE32_FSTAT_FCMD_TXUNFL_TRUE                            0x08000000U
#define LRFDPBE32_FSTAT_FCMD_TXUNFL_FALSE                           0x00000000U

// Field:    [26] TXOVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_TXOVFL                                 0x04000000U
#define LRFDPBE32_FSTAT_FCMD_TXOVFL_M                               0x04000000U
#define LRFDPBE32_FSTAT_FCMD_TXOVFL_S                                       26U
#define LRFDPBE32_FSTAT_FCMD_TXOVFL_TRUE                            0x04000000U
#define LRFDPBE32_FSTAT_FCMD_TXOVFL_FALSE                           0x00000000U

// Field:    [25] TXEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_TXEMPTY                                0x02000000U
#define LRFDPBE32_FSTAT_FCMD_TXEMPTY_M                              0x02000000U
#define LRFDPBE32_FSTAT_FCMD_TXEMPTY_S                                      25U
#define LRFDPBE32_FSTAT_FCMD_TXEMPTY_TRUE                           0x02000000U
#define LRFDPBE32_FSTAT_FCMD_TXEMPTY_FALSE                          0x00000000U

// Field:    [24] TXFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_TXFULL                                 0x01000000U
#define LRFDPBE32_FSTAT_FCMD_TXFULL_M                               0x01000000U
#define LRFDPBE32_FSTAT_FCMD_TXFULL_S                                       24U
#define LRFDPBE32_FSTAT_FCMD_TXFULL_TRUE                            0x01000000U
#define LRFDPBE32_FSTAT_FCMD_TXFULL_FALSE                           0x00000000U

// Field:    [19] RXUNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_RXUNFL                                 0x00080000U
#define LRFDPBE32_FSTAT_FCMD_RXUNFL_M                               0x00080000U
#define LRFDPBE32_FSTAT_FCMD_RXUNFL_S                                       19U
#define LRFDPBE32_FSTAT_FCMD_RXUNFL_TRUE                            0x00080000U
#define LRFDPBE32_FSTAT_FCMD_RXUNFL_FALSE                           0x00000000U

// Field:    [18] RXOVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_RXOVFL                                 0x00040000U
#define LRFDPBE32_FSTAT_FCMD_RXOVFL_M                               0x00040000U
#define LRFDPBE32_FSTAT_FCMD_RXOVFL_S                                       18U
#define LRFDPBE32_FSTAT_FCMD_RXOVFL_TRUE                            0x00040000U
#define LRFDPBE32_FSTAT_FCMD_RXOVFL_FALSE                           0x00000000U

// Field:    [17] RXEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_RXEMPTY                                0x00020000U
#define LRFDPBE32_FSTAT_FCMD_RXEMPTY_M                              0x00020000U
#define LRFDPBE32_FSTAT_FCMD_RXEMPTY_S                                      17U
#define LRFDPBE32_FSTAT_FCMD_RXEMPTY_TRUE                           0x00020000U
#define LRFDPBE32_FSTAT_FCMD_RXEMPTY_FALSE                          0x00000000U

// Field:    [16] RXFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TRUE                     Internal. Only to be used through TI provided API.
// FALSE                    Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_RXFULL                                 0x00010000U
#define LRFDPBE32_FSTAT_FCMD_RXFULL_M                               0x00010000U
#define LRFDPBE32_FSTAT_FCMD_RXFULL_S                                       16U
#define LRFDPBE32_FSTAT_FCMD_RXFULL_TRUE                            0x00010000U
#define LRFDPBE32_FSTAT_FCMD_RXFULL_FALSE                           0x00000000U

// Field:   [7:0] DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FIFO_COMMIT              Internal. Only to be used through TI provided API.
// FIFO_DISCARD             Internal. Only to be used through TI provided API.
// FIFO_RETRY               Internal. Only to be used through TI provided API.
// FIFO_DEALLOC             Internal. Only to be used through TI provided API.
// FIFO_RESET               Internal. Only to be used through TI provided API.
// RXFIFO_RETRY             Internal. Only to be used through TI provided API.
// RXFIFO_DISCARD           Internal. Only to be used through TI provided API.
// RXFIFO_COMMIT            Internal. Only to be used through TI provided API.
// TXFIFO_RESET             Internal. Only to be used through TI provided API.
// TXFIFO_DEALLOC           Internal. Only to be used through TI provided API.
// TXFIFO_RETRY             Internal. Only to be used through TI provided API.
// TXFIFO_DISCARD           Internal. Only to be used through TI provided API.
// TXFIFO_COMMIT            Internal. Only to be used through TI provided API.
// RXFIFO_DEALLOC           Internal. Only to be used through TI provided API.
// RXFIFO_RESET             Internal. Only to be used through TI provided API.
#define LRFDPBE32_FSTAT_FCMD_DATA_W                                          8U
#define LRFDPBE32_FSTAT_FCMD_DATA_M                                 0x000000FFU
#define LRFDPBE32_FSTAT_FCMD_DATA_S                                          0U
#define LRFDPBE32_FSTAT_FCMD_DATA_FIFO_COMMIT                       0x0000000FU
#define LRFDPBE32_FSTAT_FCMD_DATA_FIFO_DISCARD                      0x0000000EU
#define LRFDPBE32_FSTAT_FCMD_DATA_FIFO_RETRY                        0x0000000DU
#define LRFDPBE32_FSTAT_FCMD_DATA_FIFO_DEALLOC                      0x0000000CU
#define LRFDPBE32_FSTAT_FCMD_DATA_FIFO_RESET                        0x0000000BU
#define LRFDPBE32_FSTAT_FCMD_DATA_RXFIFO_RETRY                      0x0000000AU
#define LRFDPBE32_FSTAT_FCMD_DATA_RXFIFO_DISCARD                    0x00000009U
#define LRFDPBE32_FSTAT_FCMD_DATA_RXFIFO_COMMIT                     0x00000008U
#define LRFDPBE32_FSTAT_FCMD_DATA_TXFIFO_RESET                      0x00000007U
#define LRFDPBE32_FSTAT_FCMD_DATA_TXFIFO_DEALLOC                    0x00000006U
#define LRFDPBE32_FSTAT_FCMD_DATA_TXFIFO_RETRY                      0x00000005U
#define LRFDPBE32_FSTAT_FCMD_DATA_TXFIFO_DISCARD                    0x00000004U
#define LRFDPBE32_FSTAT_FCMD_DATA_TXFIFO_COMMIT                     0x00000003U
#define LRFDPBE32_FSTAT_FCMD_DATA_RXFIFO_DEALLOC                    0x00000002U
#define LRFDPBE32_FSTAT_FCMD_DATA_RXFIFO_RESET                      0x00000001U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFRP_RXFWP
//
//*****************************************************************************
// Field: [25:16] RXFRP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFRP_RXFWP_RXFRP_PTR_W                                   10U
#define LRFDPBE32_RXFRP_RXFWP_RXFRP_PTR_M                           0x03FF0000U
#define LRFDPBE32_RXFRP_RXFWP_RXFRP_PTR_S                                   16U
#define LRFDPBE32_RXFRP_RXFWP_RXFRP_PTR_ALLONES                     0x03FF0000U
#define LRFDPBE32_RXFRP_RXFWP_RXFRP_PTR_ALLZEROS                    0x00000000U

// Field:   [9:0] RXFWP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFRP_RXFWP_RXFWP_PTR_W                                   10U
#define LRFDPBE32_RXFRP_RXFWP_RXFWP_PTR_M                           0x000003FFU
#define LRFDPBE32_RXFRP_RXFWP_RXFWP_PTR_S                                    0U
#define LRFDPBE32_RXFRP_RXFWP_RXFWP_PTR_ALLONES                     0x000003FFU
#define LRFDPBE32_RXFRP_RXFWP_RXFWP_PTR_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFSRP_RXFSWP
//
//*****************************************************************************
// Field: [25:16] RXFSRP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSRP_PTR_W                                10U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSRP_PTR_M                        0x03FF0000U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSRP_PTR_S                                16U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSRP_PTR_ALLONES                  0x03FF0000U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSRP_PTR_ALLZEROS                 0x00000000U

// Field:   [9:0] RXFSWP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSWP_PTR_W                                10U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSWP_PTR_M                        0x000003FFU
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSWP_PTR_S                                 0U
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSWP_PTR_ALLONES                  0x000003FFU
#define LRFDPBE32_RXFSRP_RXFSWP_RXFSWP_PTR_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFRP_TXFWP
//
//*****************************************************************************
// Field: [25:16] TXFRP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFRP_TXFWP_TXFRP_PTR_W                                   10U
#define LRFDPBE32_TXFRP_TXFWP_TXFRP_PTR_M                           0x03FF0000U
#define LRFDPBE32_TXFRP_TXFWP_TXFRP_PTR_S                                   16U
#define LRFDPBE32_TXFRP_TXFWP_TXFRP_PTR_ALLONES                     0x03FF0000U
#define LRFDPBE32_TXFRP_TXFWP_TXFRP_PTR_ALLZEROS                    0x00000000U

// Field:   [9:0] TXFWP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFRP_TXFWP_TXFWP_PTR_W                                   10U
#define LRFDPBE32_TXFRP_TXFWP_TXFWP_PTR_M                           0x000003FFU
#define LRFDPBE32_TXFRP_TXFWP_TXFWP_PTR_S                                    0U
#define LRFDPBE32_TXFRP_TXFWP_TXFWP_PTR_ALLONES                     0x000003FFU
#define LRFDPBE32_TXFRP_TXFWP_TXFWP_PTR_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFSRP_TXFSWP
//
//*****************************************************************************
// Field: [25:16] TXFSRP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES_2                Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSRP_PTR_W                                10U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSRP_PTR_M                        0x03FF0000U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSRP_PTR_S                                16U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSRP_PTR_ALLONES_2                0x03FF0000U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSRP_PTR_ALLZEROS                 0x00000000U

// Field:   [9:0] TXFSWP_PTR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSWP_PTR_W                                10U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSWP_PTR_M                        0x000003FFU
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSWP_PTR_S                                 0U
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSWP_PTR_ALLONES                  0x000003FFU
#define LRFDPBE32_TXFSRP_TXFSWP_TXFSWP_PTR_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFREADABLE_RXFWRITABLE
//
//*****************************************************************************
// Field: [25:16] RXFREADABLE_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFREADABLE_BYTES_W               10U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFREADABLE_BYTES_M       0x03FF0000U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFREADABLE_BYTES_S               16U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFREADABLE_BYTES_ALLONES  \
                                                                    0x03FF0000U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFREADABLE_BYTES_ALLZEROS \
                                                                    0x00000000U

// Field:   [9:0] RXFWRITABLE_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFWRITABLE_BYTES_W               10U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFWRITABLE_BYTES_M       0x000003FFU
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFWRITABLE_BYTES_S                0U
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFWRITABLE_BYTES_ALLONES  \
                                                                    0x000003FFU
#define LRFDPBE32_RXFREADABLE_RXFWRITABLE_RXFWRITABLE_BYTES_ALLZEROS \
                                                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFREADABLE_TXFWRITABLE
//
//*****************************************************************************
// Field: [25:16] TXFREADABLE_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFREADABLE_BYTES_W               10U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFREADABLE_BYTES_M       0x03FF0000U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFREADABLE_BYTES_S               16U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFREADABLE_BYTES_ALLONES  \
                                                                    0x03FF0000U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFREADABLE_BYTES_ALLZEROS \
                                                                    0x00000000U

// Field:   [9:0] TXFWRITABLE_BYTES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFWRITABLE_BYTES_W               10U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFWRITABLE_BYTES_M       0x000003FFU
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFWRITABLE_BYTES_S                0U
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFWRITABLE_BYTES_ALLONES  \
                                                                    0x000003FFU
#define LRFDPBE32_TXFREADABLE_TXFWRITABLE_TXFWRITABLE_BYTES_ALLZEROS \
                                                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFBWR_RXFBRD
//
//*****************************************************************************
// Field: [23:16] RXFBWR_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBWR_DATA_W                                8U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBWR_DATA_M                       0x00FF0000U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBWR_DATA_S                               16U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBWR_DATA_ALLONES                 0x00FF0000U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBWR_DATA_ALLZEROS                0x00000000U

// Field:   [7:0] RXFBRD_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBRD_DATA_W                                8U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBRD_DATA_M                       0x000000FFU
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBRD_DATA_S                                0U
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBRD_DATA_ALLONES                 0x000000FFU
#define LRFDPBE32_RXFBWR_RXFBRD_RXFBRD_DATA_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFBWR_TXFBRD
//
//*****************************************************************************
// Field: [23:16] TXFBWR_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBWR_DATA_W                                8U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBWR_DATA_M                       0x00FF0000U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBWR_DATA_S                               16U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBWR_DATA_ALLONES                 0x00FF0000U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBWR_DATA_ALLZEROS                0x00000000U

// Field:   [7:0] TXFBRD_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBRD_DATA_W                                8U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBRD_DATA_M                       0x000000FFU
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBRD_DATA_S                                0U
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBRD_DATA_ALLONES                 0x000000FFU
#define LRFDPBE32_TXFBWR_TXFBRD_TXFBRD_DATA_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_RXFHWR_RXFHRD
//
//*****************************************************************************
// Field: [31:16] RXFHWR_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHWR_DATA_W                               16U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHWR_DATA_M                       0xFFFF0000U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHWR_DATA_S                               16U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHWR_DATA_ALLONES                 0xFFFF0000U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHWR_DATA_ALLZEROS                0x00000000U

// Field:  [15:0] RXFHRD_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHRD_DATA_W                               16U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHRD_DATA_M                       0x0000FFFFU
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHRD_DATA_S                                0U
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHRD_DATA_ALLONES                 0x0000FFFFU
#define LRFDPBE32_RXFHWR_RXFHRD_RXFHRD_DATA_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE32_O_TXFHWR_TXFHRD
//
//*****************************************************************************
// Field: [31:16] TXFHWR_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHWR_DATA_W                               16U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHWR_DATA_M                       0xFFFF0000U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHWR_DATA_S                               16U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHWR_DATA_ALLONES                 0xFFFF0000U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHWR_DATA_ALLZEROS                0x00000000U

// Field:  [15:0] TXFHRD_DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHRD_DATA_W                               16U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHRD_DATA_M                       0x0000FFFFU
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHRD_DATA_S                                0U
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHRD_DATA_ALLONES                 0x0000FFFFU
#define LRFDPBE32_TXFHWR_TXFHRD_TXFHRD_DATA_ALLZEROS                0x00000000U


#endif // __LRFDPBE32__
