/******************************************************************************
*  Filename:       hw_evtull_h
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

#ifndef __HW_EVTULL_H__
#define __HW_EVTULL_H__

//*****************************************************************************
//
// This section defines the register offsets of
// EVTULL component
//
//*****************************************************************************
// Description
#define EVTULL_O_DESC                                               0x00000000U

// Extended Description
#define EVTULL_O_DESCEX                                             0x00000004U

// Digital test bus control register
#define EVTULL_O_DTB                                                0x00000064U

// Output Selection for CPU NMI Exception
#define EVTULL_O_NMISEL                                             0x00000400U

// Output Selection for RTCCPT
#define EVTULL_O_RTCCPTSEL                                          0x00000404U

// WAKEUP Mask
#define EVTULL_O_WKUPMASK                                           0x00000800U

//*****************************************************************************
//
// Register: EVTULL_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define EVTULL_DESC_MODID_W                                                 16U
#define EVTULL_DESC_MODID_M                                         0xFFFF0000U
#define EVTULL_DESC_MODID_S                                                 16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
// 0: Standard IP MMRs do not exist
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define EVTULL_DESC_STDIPOFF_W                                               4U
#define EVTULL_DESC_STDIPOFF_M                                      0x0000F000U
#define EVTULL_DESC_STDIPOFF_S                                              12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define EVTULL_DESC_INSTIDX_W                                                4U
#define EVTULL_DESC_INSTIDX_M                                       0x00000F00U
#define EVTULL_DESC_INSTIDX_S                                                8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define EVTULL_DESC_MAJREV_W                                                 4U
#define EVTULL_DESC_MAJREV_M                                        0x000000F0U
#define EVTULL_DESC_MAJREV_S                                                 4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define EVTULL_DESC_MINREV_W                                                 4U
#define EVTULL_DESC_MINREV_M                                        0x0000000FU
#define EVTULL_DESC_MINREV_S                                                 0U

//*****************************************************************************
//
// Register: EVTULL_O_DESCEX
//
//*****************************************************************************
// Field: [31:22] IDMA
//
// Number of DMA input channels
#define EVTULL_DESCEX_IDMA_W                                                10U
#define EVTULL_DESCEX_IDMA_M                                        0xFFC00000U
#define EVTULL_DESCEX_IDMA_S                                                22U

// Field: [21:17] NDMA
//
// Number of DMA output channels
#define EVTULL_DESCEX_NDMA_W                                                 5U
#define EVTULL_DESCEX_NDMA_M                                        0x003E0000U
#define EVTULL_DESCEX_NDMA_S                                                17U

// Field:    [16] PD
//
// Power Domain.
// 0 : SVT
//  1 : ULL
#define EVTULL_DESCEX_PD                                            0x00010000U
#define EVTULL_DESCEX_PD_M                                          0x00010000U
#define EVTULL_DESCEX_PD_S                                                  16U

// Field:  [15:8] NSUB
//
// Number of Subscribers
#define EVTULL_DESCEX_NSUB_W                                                 8U
#define EVTULL_DESCEX_NSUB_M                                        0x0000FF00U
#define EVTULL_DESCEX_NSUB_S                                                 8U

// Field:   [7:0] NPUB
//
// Number of Publishers
#define EVTULL_DESCEX_NPUB_W                                                 8U
#define EVTULL_DESCEX_NPUB_M                                        0x000000FFU
#define EVTULL_DESCEX_NPUB_S                                                 0U

//*****************************************************************************
//
// Register: EVTULL_O_DTB
//
//*****************************************************************************
// Field:     [0] SEL
//
// Digital test bus selection mux control
//
//             Non-zero select values output a 16 bit selected group of signals
// per value.
// ENUMs:
// DIS                      All 16 observation signals are set to zero.
#define EVTULL_DTB_SEL                                              0x00000001U
#define EVTULL_DTB_SEL_M                                            0x00000001U
#define EVTULL_DTB_SEL_S                                                     0U
#define EVTULL_DTB_SEL_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: EVTULL_O_NMISEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// AON_IOC_COMB             IOC synchronous combined event, controlled by
//                          IOC:EVTCFG
// AON_LPMCMP_IRQ           AON LPCMP interrupt, controlled by SYS0:LPCMPCFG
// AON_DBG_COMB             DebugSS combined interrupt, interrupt flags can be
//                          found here DBGSS:MIS
// AON_RTC_COMB             AON_RTC event, controlled by the RTC:IMASK setting
// AON_CKM_COMB             CKMD combined interrupt request, interrupt flags
//                          can be found here CKMD:MIS
// AON_PMU_COMB             PMU combined interrupt request for BATMON,
//                          interrupt flags can be found here PMUD:EVENT
// NONE                     Always inactive
#define EVTULL_NMISEL_PUBID_W                                                6U
#define EVTULL_NMISEL_PUBID_M                                       0x0000003FU
#define EVTULL_NMISEL_PUBID_S                                                0U
#define EVTULL_NMISEL_PUBID_AON_IOC_COMB                            0x00000007U
#define EVTULL_NMISEL_PUBID_AON_LPMCMP_IRQ                          0x00000006U
#define EVTULL_NMISEL_PUBID_AON_DBG_COMB                            0x00000005U
#define EVTULL_NMISEL_PUBID_AON_RTC_COMB                            0x00000004U
#define EVTULL_NMISEL_PUBID_AON_CKM_COMB                            0x00000003U
#define EVTULL_NMISEL_PUBID_AON_PMU_COMB                            0x00000002U
#define EVTULL_NMISEL_PUBID_NONE                                    0x00000000U

//*****************************************************************************
//
// Register: EVTULL_O_RTCCPTSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// AON_IOC_COMB             IOC synchronous combined event, controlled by
//                          IOC:EVTCFG
// AON_LPMCMP_IRQ           AON LPCMP interrupt, controlled by SYS0:LPCMPCFG
// AON_DBG_COMB             DebugSS combined interrupt, interrupt flags can be
//                          found here DBGSS:MIS
// AON_RTC_COMB             AON_RTC event, controlled by the RTC:IMASK setting
// AON_CKM_COMB             CKMD combined interrupt request, interrupt flags
//                          can be found here CKMD:MIS
// AON_PMU_COMB             PMU combined interrupt request for BATMON,
//                          interrupt flags can be found here PMUD:EVENT
// NONE                     Always inactive
#define EVTULL_RTCCPTSEL_PUBID_W                                             6U
#define EVTULL_RTCCPTSEL_PUBID_M                                    0x0000003FU
#define EVTULL_RTCCPTSEL_PUBID_S                                             0U
#define EVTULL_RTCCPTSEL_PUBID_AON_IOC_COMB                         0x00000007U
#define EVTULL_RTCCPTSEL_PUBID_AON_LPMCMP_IRQ                       0x00000006U
#define EVTULL_RTCCPTSEL_PUBID_AON_DBG_COMB                         0x00000005U
#define EVTULL_RTCCPTSEL_PUBID_AON_RTC_COMB                         0x00000004U
#define EVTULL_RTCCPTSEL_PUBID_AON_CKM_COMB                         0x00000003U
#define EVTULL_RTCCPTSEL_PUBID_AON_PMU_COMB                         0x00000002U
#define EVTULL_RTCCPTSEL_PUBID_NONE                                 0x00000000U

//*****************************************************************************
//
// Register: EVTULL_O_WKUPMASK
//
//*****************************************************************************
// Field:     [7] AON_IOC_COMB
//
// Wake-up mask for AON_IOC_COMB.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_IOC_COMB                                0x00000080U
#define EVTULL_WKUPMASK_AON_IOC_COMB_M                              0x00000080U
#define EVTULL_WKUPMASK_AON_IOC_COMB_S                                       7U

// Field:     [6] AON_LPMCMP_IRQ
//
// Wake-up mask for AON_LPMCMP_IRQ.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_LPMCMP_IRQ                              0x00000040U
#define EVTULL_WKUPMASK_AON_LPMCMP_IRQ_M                            0x00000040U
#define EVTULL_WKUPMASK_AON_LPMCMP_IRQ_S                                     6U

// Field:     [5] AON_DBG_COMB
//
// Wake-up mask for AON_DBG_COMB.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_DBG_COMB                                0x00000020U
#define EVTULL_WKUPMASK_AON_DBG_COMB_M                              0x00000020U
#define EVTULL_WKUPMASK_AON_DBG_COMB_S                                       5U

// Field:     [4] AON_RTC_COMB
//
// Wake-up mask for AON_RTC_COMB.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_RTC_COMB                                0x00000010U
#define EVTULL_WKUPMASK_AON_RTC_COMB_M                              0x00000010U
#define EVTULL_WKUPMASK_AON_RTC_COMB_S                                       4U

// Field:     [3] AON_CKM_COMB
//
// Wake-up mask for AON_CKM_COMB.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_CKM_COMB                                0x00000008U
#define EVTULL_WKUPMASK_AON_CKM_COMB_M                              0x00000008U
#define EVTULL_WKUPMASK_AON_CKM_COMB_S                                       3U

// Field:     [2] AON_PMU_COMB
//
// Wake-up mask for AON_PMU_COMB.
// 0 - Wakeup Disabled
// 1 - Wakeup Enabled
#define EVTULL_WKUPMASK_AON_PMU_COMB                                0x00000004U
#define EVTULL_WKUPMASK_AON_PMU_COMB_M                              0x00000004U
#define EVTULL_WKUPMASK_AON_PMU_COMB_S                                       2U


#endif // __EVTULL__
