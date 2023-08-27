/******************************************************************************
*  Filename:       hw_ckmd_h
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

#ifndef __HW_CKMD_H__
#define __HW_CKMD_H__

//*****************************************************************************
//
// This section defines the register offsets of
// CKMD component
//
//*****************************************************************************
// Description Register.
#define CKMD_O_DESC                                                 0x00000000U

// Interrupt mask.
#define CKMD_O_IMASK                                                0x00000044U

// Raw interrupt status.
#define CKMD_O_RIS                                                  0x00000048U

// Masked interrupt status.
#define CKMD_O_MIS                                                  0x0000004CU

// Interrupt set register.
#define CKMD_O_ISET                                                 0x00000050U

// Interrupt clear register.
#define CKMD_O_ICLR                                                 0x00000054U

// Interrupt mask set register.
#define CKMD_O_IMSET                                                0x00000058U

// Interrupt mask clear register.
#define CKMD_O_IMCLR                                                0x0000005CU

// Internal. Only to be used through TI provided API.
#define CKMD_O_HFOSCCTL                                             0x00000080U

// High frequency crystal control
#define CKMD_O_HFXTCTL                                              0x00000084U

// Low frequency oscillator control
#define CKMD_O_LFOSCCTL                                             0x0000008CU

// Low frequency crystal control
#define CKMD_O_LFXTCTL                                              0x00000090U

// Low frequency clock qualification control
#define CKMD_O_LFQUALCTL                                            0x00000094U

// Low frequency time increment control
#define CKMD_O_LFINCCTL                                             0x00000098U

// Low frequency time increment override control
#define CKMD_O_LFINCOVR                                             0x0000009CU

// Internal. Only to be used through TI provided API.
#define CKMD_O_AMPADCCTL                                            0x000000A0U

// High frequency tracking loop control
#define CKMD_O_HFTRACKCTL                                           0x000000A4U

// Internal. Only to be used through TI provided API.
#define CKMD_O_LDOCTL                                               0x000000A8U

// Nanoamp-bias control
#define CKMD_O_NABIASCTL                                            0x000000ACU

// Low-frequency clock-monitor control
#define CKMD_O_LFMONCTL                                             0x000000B0U

// Low frequency clock selection
#define CKMD_O_LFCLKSEL                                             0x000000C0U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCCLKSEL                                            0x000000C4U

// ADC clock selection
#define CKMD_O_ADCCLKSEL                                            0x000000C8U

// Low-frequency clock status
#define CKMD_O_LFCLKSTAT                                            0x000000E0U

// HFXT status information
#define CKMD_O_HFXTSTAT                                             0x000000E4U

// Internal. Only to be used through TI provided API.
#define CKMD_O_AMPADCSTAT                                           0x000000E8U

// HFOSC tracking loop status information
#define CKMD_O_TRACKSTAT                                            0x000000ECU

// HFXT Amplitude Compensation Status
#define CKMD_O_AMPSTAT                                              0x000000F0U

// Internal. Only to be used through TI provided API.
#define CKMD_O_ATBCTL0                                              0x00000100U

// Internal. Only to be used through TI provided API.
#define CKMD_O_ATBCTL1                                              0x00000104U

// Digital test bus mux control
#define CKMD_O_DTBCTL                                               0x00000108U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TRIM0                                                0x00000110U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TRIM1                                                0x00000114U

// Initial values for HFXT ramping
#define CKMD_O_HFXTINIT                                             0x00000118U

// Target values for HFXT ramping
#define CKMD_O_HFXTTARG                                             0x0000011CU

// Alternative target values for HFXT configuration
#define CKMD_O_HFXTDYN                                              0x00000120U

// Amplitude Compensation Configuration 0
#define CKMD_O_AMPCFG0                                              0x00000124U

// Amplitude Compensation Configuration 1
#define CKMD_O_AMPCFG1                                              0x00000128U

// Configuration Register for the Tracking Loop
#define CKMD_O_LOOPCFG                                              0x0000012CU

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCCTL                                               0x00000200U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCSTAT                                              0x00000204U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCRESULT                                            0x00000208U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCSATCFG                                            0x0000020CU

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCTRIGSRC                                           0x00000210U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCTRIGCNT                                           0x00000214U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCTRIGCNTLOAD                                       0x00000218U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCTRIGCNTCFG                                        0x0000021CU

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCPRECTL                                            0x00000220U

// Internal. Only to be used through TI provided API.
#define CKMD_O_TDCPRECNTR                                           0x00000224U

// WDT counter value register
#define CKMD_O_WDTCNT                                               0x00000300U

// WDT test mode register
#define CKMD_O_WDTTEST                                              0x00000304U

// WDT lock register
#define CKMD_O_WDTLOCK                                              0x00000308U

//*****************************************************************************
//
// Register: CKMD_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define CKMD_DESC_MODID_W                                                   16U
#define CKMD_DESC_MODID_M                                           0xFFFF0000U
#define CKMD_DESC_MODID_S                                                   16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
// 0: Standard IP MMRs do not exist
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
//
// NOTE: This IP does not have DTB as part of the Standard IP MMRs. It uses
// DTBCTL instead.
#define CKMD_DESC_STDIPOFF_W                                                 4U
#define CKMD_DESC_STDIPOFF_M                                        0x0000F000U
#define CKMD_DESC_STDIPOFF_S                                                12U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define CKMD_DESC_MAJREV_W                                                   4U
#define CKMD_DESC_MAJREV_M                                          0x000000F0U
#define CKMD_DESC_MAJREV_S                                                   4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define CKMD_DESC_MINREV_W                                                   4U
#define CKMD_DESC_MINREV_M                                          0x0000000FU
#define CKMD_DESC_MINREV_S                                                   0U

//*****************************************************************************
//
// Register: CKMD_O_IMASK
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_IMASK_LFTICK                                           0x00020000U
#define CKMD_IMASK_LFTICK_M                                         0x00020000U
#define CKMD_IMASK_LFTICK_S                                                 17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_IMASK_LFGEARRSTRT                                      0x00010000U
#define CKMD_IMASK_LFGEARRSTRT_M                                    0x00010000U
#define CKMD_IMASK_LFGEARRSTRT_S                                            16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_IMASK_AMPSETTLED                                       0x00008000U
#define CKMD_IMASK_AMPSETTLED_M                                     0x00008000U
#define CKMD_IMASK_AMPSETTLED_S                                             15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_IMASK_AMPCTRLATTARG                                    0x00004000U
#define CKMD_IMASK_AMPCTRLATTARG_M                                  0x00004000U
#define CKMD_IMASK_AMPCTRLATTARG_S                                          14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_IMASK_PRELFEDGE                                        0x00002000U
#define CKMD_IMASK_PRELFEDGE_M                                      0x00002000U
#define CKMD_IMASK_PRELFEDGE_S                                              13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_IMASK_LFCLKLOSS                                        0x00001000U
#define CKMD_IMASK_LFCLKLOSS_M                                      0x00001000U
#define CKMD_IMASK_LFCLKLOSS_S                                              12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_IMASK_LFCLKOOR                                         0x00000800U
#define CKMD_IMASK_LFCLKOOR_M                                       0x00000800U
#define CKMD_IMASK_LFCLKOOR_S                                               11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_IMASK_LFCLKGOOD                                        0x00000400U
#define CKMD_IMASK_LFCLKGOOD_M                                      0x00000400U
#define CKMD_IMASK_LFCLKGOOD_S                                              10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_IMASK_LFINCUPD                                         0x00000200U
#define CKMD_IMASK_LFINCUPD_M                                       0x00000200U
#define CKMD_IMASK_LFINCUPD_S                                                9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_IMASK_TDCDONE                                          0x00000100U
#define CKMD_IMASK_TDCDONE_M                                        0x00000100U
#define CKMD_IMASK_TDCDONE_S                                                 8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_IMASK_ADCPEAKUPD                                       0x00000080U
#define CKMD_IMASK_ADCPEAKUPD_M                                     0x00000080U
#define CKMD_IMASK_ADCPEAKUPD_S                                              7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_IMASK_ADCBIASUPD                                       0x00000040U
#define CKMD_IMASK_ADCBIASUPD_M                                     0x00000040U
#define CKMD_IMASK_ADCBIASUPD_S                                              6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_IMASK_ADCCOMPUPD                                       0x00000020U
#define CKMD_IMASK_ADCCOMPUPD_M                                     0x00000020U
#define CKMD_IMASK_ADCCOMPUPD_S                                              5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_IMASK_TRACKREFOOR                                      0x00000010U
#define CKMD_IMASK_TRACKREFOOR_M                                    0x00000010U
#define CKMD_IMASK_TRACKREFOOR_S                                             4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_IMASK_TRACKREFLOSS                                     0x00000008U
#define CKMD_IMASK_TRACKREFLOSS_M                                   0x00000008U
#define CKMD_IMASK_TRACKREFLOSS_S                                            3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_IMASK_HFXTAMPGOOD                                      0x00000004U
#define CKMD_IMASK_HFXTAMPGOOD_M                                    0x00000004U
#define CKMD_IMASK_HFXTAMPGOOD_S                                             2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_IMASK_HFXTFAULT                                        0x00000002U
#define CKMD_IMASK_HFXTFAULT_M                                      0x00000002U
#define CKMD_IMASK_HFXTFAULT_S                                               1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_IMASK_HFXTGOOD                                         0x00000001U
#define CKMD_IMASK_HFXTGOOD_M                                       0x00000001U
#define CKMD_IMASK_HFXTGOOD_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_RIS
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_RIS_LFTICK                                             0x00020000U
#define CKMD_RIS_LFTICK_M                                           0x00020000U
#define CKMD_RIS_LFTICK_S                                                   17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_RIS_LFGEARRSTRT                                        0x00010000U
#define CKMD_RIS_LFGEARRSTRT_M                                      0x00010000U
#define CKMD_RIS_LFGEARRSTRT_S                                              16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_RIS_AMPSETTLED                                         0x00008000U
#define CKMD_RIS_AMPSETTLED_M                                       0x00008000U
#define CKMD_RIS_AMPSETTLED_S                                               15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_RIS_AMPCTRLATTARG                                      0x00004000U
#define CKMD_RIS_AMPCTRLATTARG_M                                    0x00004000U
#define CKMD_RIS_AMPCTRLATTARG_S                                            14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_RIS_PRELFEDGE                                          0x00002000U
#define CKMD_RIS_PRELFEDGE_M                                        0x00002000U
#define CKMD_RIS_PRELFEDGE_S                                                13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_RIS_LFCLKLOSS                                          0x00001000U
#define CKMD_RIS_LFCLKLOSS_M                                        0x00001000U
#define CKMD_RIS_LFCLKLOSS_S                                                12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_RIS_LFCLKOOR                                           0x00000800U
#define CKMD_RIS_LFCLKOOR_M                                         0x00000800U
#define CKMD_RIS_LFCLKOOR_S                                                 11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_RIS_LFCLKGOOD                                          0x00000400U
#define CKMD_RIS_LFCLKGOOD_M                                        0x00000400U
#define CKMD_RIS_LFCLKGOOD_S                                                10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_RIS_LFINCUPD                                           0x00000200U
#define CKMD_RIS_LFINCUPD_M                                         0x00000200U
#define CKMD_RIS_LFINCUPD_S                                                  9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_RIS_TDCDONE                                            0x00000100U
#define CKMD_RIS_TDCDONE_M                                          0x00000100U
#define CKMD_RIS_TDCDONE_S                                                   8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_RIS_ADCPEAKUPD                                         0x00000080U
#define CKMD_RIS_ADCPEAKUPD_M                                       0x00000080U
#define CKMD_RIS_ADCPEAKUPD_S                                                7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_RIS_ADCBIASUPD                                         0x00000040U
#define CKMD_RIS_ADCBIASUPD_M                                       0x00000040U
#define CKMD_RIS_ADCBIASUPD_S                                                6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_RIS_ADCCOMPUPD                                         0x00000020U
#define CKMD_RIS_ADCCOMPUPD_M                                       0x00000020U
#define CKMD_RIS_ADCCOMPUPD_S                                                5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_RIS_TRACKREFOOR                                        0x00000010U
#define CKMD_RIS_TRACKREFOOR_M                                      0x00000010U
#define CKMD_RIS_TRACKREFOOR_S                                               4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_RIS_TRACKREFLOSS                                       0x00000008U
#define CKMD_RIS_TRACKREFLOSS_M                                     0x00000008U
#define CKMD_RIS_TRACKREFLOSS_S                                              3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_RIS_HFXTAMPGOOD                                        0x00000004U
#define CKMD_RIS_HFXTAMPGOOD_M                                      0x00000004U
#define CKMD_RIS_HFXTAMPGOOD_S                                               2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_RIS_HFXTFAULT                                          0x00000002U
#define CKMD_RIS_HFXTFAULT_M                                        0x00000002U
#define CKMD_RIS_HFXTFAULT_S                                                 1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_RIS_HFXTGOOD                                           0x00000001U
#define CKMD_RIS_HFXTGOOD_M                                         0x00000001U
#define CKMD_RIS_HFXTGOOD_S                                                  0U

//*****************************************************************************
//
// Register: CKMD_O_MIS
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_MIS_LFTICK                                             0x00020000U
#define CKMD_MIS_LFTICK_M                                           0x00020000U
#define CKMD_MIS_LFTICK_S                                                   17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_MIS_LFGEARRSTRT                                        0x00010000U
#define CKMD_MIS_LFGEARRSTRT_M                                      0x00010000U
#define CKMD_MIS_LFGEARRSTRT_S                                              16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_MIS_AMPSETTLED                                         0x00008000U
#define CKMD_MIS_AMPSETTLED_M                                       0x00008000U
#define CKMD_MIS_AMPSETTLED_S                                               15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_MIS_AMPCTRLATTARG                                      0x00004000U
#define CKMD_MIS_AMPCTRLATTARG_M                                    0x00004000U
#define CKMD_MIS_AMPCTRLATTARG_S                                            14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_MIS_PRELFEDGE                                          0x00002000U
#define CKMD_MIS_PRELFEDGE_M                                        0x00002000U
#define CKMD_MIS_PRELFEDGE_S                                                13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_MIS_LFCLKLOSS                                          0x00001000U
#define CKMD_MIS_LFCLKLOSS_M                                        0x00001000U
#define CKMD_MIS_LFCLKLOSS_S                                                12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_MIS_LFCLKOOR                                           0x00000800U
#define CKMD_MIS_LFCLKOOR_M                                         0x00000800U
#define CKMD_MIS_LFCLKOOR_S                                                 11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_MIS_LFCLKGOOD                                          0x00000400U
#define CKMD_MIS_LFCLKGOOD_M                                        0x00000400U
#define CKMD_MIS_LFCLKGOOD_S                                                10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_MIS_LFINCUPD                                           0x00000200U
#define CKMD_MIS_LFINCUPD_M                                         0x00000200U
#define CKMD_MIS_LFINCUPD_S                                                  9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_MIS_TDCDONE                                            0x00000100U
#define CKMD_MIS_TDCDONE_M                                          0x00000100U
#define CKMD_MIS_TDCDONE_S                                                   8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_MIS_ADCPEAKUPD                                         0x00000080U
#define CKMD_MIS_ADCPEAKUPD_M                                       0x00000080U
#define CKMD_MIS_ADCPEAKUPD_S                                                7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_MIS_ADCBIASUPD                                         0x00000040U
#define CKMD_MIS_ADCBIASUPD_M                                       0x00000040U
#define CKMD_MIS_ADCBIASUPD_S                                                6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_MIS_ADCCOMPUPD                                         0x00000020U
#define CKMD_MIS_ADCCOMPUPD_M                                       0x00000020U
#define CKMD_MIS_ADCCOMPUPD_S                                                5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_MIS_TRACKREFOOR                                        0x00000010U
#define CKMD_MIS_TRACKREFOOR_M                                      0x00000010U
#define CKMD_MIS_TRACKREFOOR_S                                               4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_MIS_TRACKREFLOSS                                       0x00000008U
#define CKMD_MIS_TRACKREFLOSS_M                                     0x00000008U
#define CKMD_MIS_TRACKREFLOSS_S                                              3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_MIS_HFXTAMPGOOD                                        0x00000004U
#define CKMD_MIS_HFXTAMPGOOD_M                                      0x00000004U
#define CKMD_MIS_HFXTAMPGOOD_S                                               2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_MIS_HFXTFAULT                                          0x00000002U
#define CKMD_MIS_HFXTFAULT_M                                        0x00000002U
#define CKMD_MIS_HFXTFAULT_S                                                 1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_MIS_HFXTGOOD                                           0x00000001U
#define CKMD_MIS_HFXTGOOD_M                                         0x00000001U
#define CKMD_MIS_HFXTGOOD_S                                                  0U

//*****************************************************************************
//
// Register: CKMD_O_ISET
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_ISET_LFTICK                                            0x00020000U
#define CKMD_ISET_LFTICK_M                                          0x00020000U
#define CKMD_ISET_LFTICK_S                                                  17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_ISET_LFGEARRSTRT                                       0x00010000U
#define CKMD_ISET_LFGEARRSTRT_M                                     0x00010000U
#define CKMD_ISET_LFGEARRSTRT_S                                             16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_ISET_AMPSETTLED                                        0x00008000U
#define CKMD_ISET_AMPSETTLED_M                                      0x00008000U
#define CKMD_ISET_AMPSETTLED_S                                              15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG.Q1CAP,
// HFXTTARG.Q2CAP and HFXTTARG.IREF or HFXTDYN.Q1CAP, HFXTDYN.Q2CAP and
// HFXTDYN.IREF are reached.
#define CKMD_ISET_AMPCTRLATTARG                                     0x00004000U
#define CKMD_ISET_AMPCTRLATTARG_M                                   0x00004000U
#define CKMD_ISET_AMPCTRLATTARG_S                                           14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_ISET_PRELFEDGE                                         0x00002000U
#define CKMD_ISET_PRELFEDGE_M                                       0x00002000U
#define CKMD_ISET_PRELFEDGE_S                                               13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_ISET_LFCLKLOSS                                         0x00001000U
#define CKMD_ISET_LFCLKLOSS_M                                       0x00001000U
#define CKMD_ISET_LFCLKLOSS_S                                               12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_ISET_LFCLKOOR                                          0x00000800U
#define CKMD_ISET_LFCLKOOR_M                                        0x00000800U
#define CKMD_ISET_LFCLKOOR_S                                                11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_ISET_LFCLKGOOD                                         0x00000400U
#define CKMD_ISET_LFCLKGOOD_M                                       0x00000400U
#define CKMD_ISET_LFCLKGOOD_S                                               10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_ISET_LFINCUPD                                          0x00000200U
#define CKMD_ISET_LFINCUPD_M                                        0x00000200U
#define CKMD_ISET_LFINCUPD_S                                                 9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_ISET_TDCDONE                                           0x00000100U
#define CKMD_ISET_TDCDONE_M                                         0x00000100U
#define CKMD_ISET_TDCDONE_S                                                  8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_ISET_ADCPEAKUPD                                        0x00000080U
#define CKMD_ISET_ADCPEAKUPD_M                                      0x00000080U
#define CKMD_ISET_ADCPEAKUPD_S                                               7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_ISET_ADCBIASUPD                                        0x00000040U
#define CKMD_ISET_ADCBIASUPD_M                                      0x00000040U
#define CKMD_ISET_ADCBIASUPD_S                                               6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_ISET_ADCCOMPUPD                                        0x00000020U
#define CKMD_ISET_ADCCOMPUPD_M                                      0x00000020U
#define CKMD_ISET_ADCCOMPUPD_S                                               5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_ISET_TRACKREFOOR                                       0x00000010U
#define CKMD_ISET_TRACKREFOOR_M                                     0x00000010U
#define CKMD_ISET_TRACKREFOOR_S                                              4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_ISET_TRACKREFLOSS                                      0x00000008U
#define CKMD_ISET_TRACKREFLOSS_M                                    0x00000008U
#define CKMD_ISET_TRACKREFLOSS_S                                             3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_ISET_HFXTAMPGOOD                                       0x00000004U
#define CKMD_ISET_HFXTAMPGOOD_M                                     0x00000004U
#define CKMD_ISET_HFXTAMPGOOD_S                                              2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_ISET_HFXTFAULT                                         0x00000002U
#define CKMD_ISET_HFXTFAULT_M                                       0x00000002U
#define CKMD_ISET_HFXTFAULT_S                                                1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_ISET_HFXTGOOD                                          0x00000001U
#define CKMD_ISET_HFXTGOOD_M                                        0x00000001U
#define CKMD_ISET_HFXTGOOD_S                                                 0U

//*****************************************************************************
//
// Register: CKMD_O_ICLR
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_ICLR_LFTICK                                            0x00020000U
#define CKMD_ICLR_LFTICK_M                                          0x00020000U
#define CKMD_ICLR_LFTICK_S                                                  17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_ICLR_LFGEARRSTRT                                       0x00010000U
#define CKMD_ICLR_LFGEARRSTRT_M                                     0x00010000U
#define CKMD_ICLR_LFGEARRSTRT_S                                             16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_ICLR_AMPSETTLED                                        0x00008000U
#define CKMD_ICLR_AMPSETTLED_M                                      0x00008000U
#define CKMD_ICLR_AMPSETTLED_S                                              15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_ICLR_AMPCTRLATTARG                                     0x00004000U
#define CKMD_ICLR_AMPCTRLATTARG_M                                   0x00004000U
#define CKMD_ICLR_AMPCTRLATTARG_S                                           14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_ICLR_PRELFEDGE                                         0x00002000U
#define CKMD_ICLR_PRELFEDGE_M                                       0x00002000U
#define CKMD_ICLR_PRELFEDGE_S                                               13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_ICLR_LFCLKLOSS                                         0x00001000U
#define CKMD_ICLR_LFCLKLOSS_M                                       0x00001000U
#define CKMD_ICLR_LFCLKLOSS_S                                               12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_ICLR_LFCLKOOR                                          0x00000800U
#define CKMD_ICLR_LFCLKOOR_M                                        0x00000800U
#define CKMD_ICLR_LFCLKOOR_S                                                11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_ICLR_LFCLKGOOD                                         0x00000400U
#define CKMD_ICLR_LFCLKGOOD_M                                       0x00000400U
#define CKMD_ICLR_LFCLKGOOD_S                                               10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_ICLR_LFINCUPD                                          0x00000200U
#define CKMD_ICLR_LFINCUPD_M                                        0x00000200U
#define CKMD_ICLR_LFINCUPD_S                                                 9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_ICLR_TDCDONE                                           0x00000100U
#define CKMD_ICLR_TDCDONE_M                                         0x00000100U
#define CKMD_ICLR_TDCDONE_S                                                  8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_ICLR_ADCPEAKUPD                                        0x00000080U
#define CKMD_ICLR_ADCPEAKUPD_M                                      0x00000080U
#define CKMD_ICLR_ADCPEAKUPD_S                                               7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_ICLR_ADCBIASUPD                                        0x00000040U
#define CKMD_ICLR_ADCBIASUPD_M                                      0x00000040U
#define CKMD_ICLR_ADCBIASUPD_S                                               6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_ICLR_ADCCOMPUPD                                        0x00000020U
#define CKMD_ICLR_ADCCOMPUPD_M                                      0x00000020U
#define CKMD_ICLR_ADCCOMPUPD_S                                               5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_ICLR_TRACKREFOOR                                       0x00000010U
#define CKMD_ICLR_TRACKREFOOR_M                                     0x00000010U
#define CKMD_ICLR_TRACKREFOOR_S                                              4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_ICLR_TRACKREFLOSS                                      0x00000008U
#define CKMD_ICLR_TRACKREFLOSS_M                                    0x00000008U
#define CKMD_ICLR_TRACKREFLOSS_S                                             3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_ICLR_HFXTAMPGOOD                                       0x00000004U
#define CKMD_ICLR_HFXTAMPGOOD_M                                     0x00000004U
#define CKMD_ICLR_HFXTAMPGOOD_S                                              2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_ICLR_HFXTFAULT                                         0x00000002U
#define CKMD_ICLR_HFXTFAULT_M                                       0x00000002U
#define CKMD_ICLR_HFXTFAULT_S                                                1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_ICLR_HFXTGOOD                                          0x00000001U
#define CKMD_ICLR_HFXTGOOD_M                                        0x00000001U
#define CKMD_ICLR_HFXTGOOD_S                                                 0U

//*****************************************************************************
//
// Register: CKMD_O_IMSET
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_IMSET_LFTICK                                           0x00020000U
#define CKMD_IMSET_LFTICK_M                                         0x00020000U
#define CKMD_IMSET_LFTICK_S                                                 17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_IMSET_LFGEARRSTRT                                      0x00010000U
#define CKMD_IMSET_LFGEARRSTRT_M                                    0x00010000U
#define CKMD_IMSET_LFGEARRSTRT_S                                            16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_IMSET_AMPSETTLED                                       0x00008000U
#define CKMD_IMSET_AMPSETTLED_M                                     0x00008000U
#define CKMD_IMSET_AMPSETTLED_S                                             15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_IMSET_AMPCTRLATTARG                                    0x00004000U
#define CKMD_IMSET_AMPCTRLATTARG_M                                  0x00004000U
#define CKMD_IMSET_AMPCTRLATTARG_S                                          14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_IMSET_PRELFEDGE                                        0x00002000U
#define CKMD_IMSET_PRELFEDGE_M                                      0x00002000U
#define CKMD_IMSET_PRELFEDGE_S                                              13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_IMSET_LFCLKLOSS                                        0x00001000U
#define CKMD_IMSET_LFCLKLOSS_M                                      0x00001000U
#define CKMD_IMSET_LFCLKLOSS_S                                              12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_IMSET_LFCLKOOR                                         0x00000800U
#define CKMD_IMSET_LFCLKOOR_M                                       0x00000800U
#define CKMD_IMSET_LFCLKOOR_S                                               11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_IMSET_LFCLKGOOD                                        0x00000400U
#define CKMD_IMSET_LFCLKGOOD_M                                      0x00000400U
#define CKMD_IMSET_LFCLKGOOD_S                                              10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_IMSET_LFINCUPD                                         0x00000200U
#define CKMD_IMSET_LFINCUPD_M                                       0x00000200U
#define CKMD_IMSET_LFINCUPD_S                                                9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_IMSET_TDCDONE                                          0x00000100U
#define CKMD_IMSET_TDCDONE_M                                        0x00000100U
#define CKMD_IMSET_TDCDONE_S                                                 8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_IMSET_ADCPEAKUPD                                       0x00000080U
#define CKMD_IMSET_ADCPEAKUPD_M                                     0x00000080U
#define CKMD_IMSET_ADCPEAKUPD_S                                              7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_IMSET_ADCBIASUPD                                       0x00000040U
#define CKMD_IMSET_ADCBIASUPD_M                                     0x00000040U
#define CKMD_IMSET_ADCBIASUPD_S                                              6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_IMSET_ADCCOMPUPD                                       0x00000020U
#define CKMD_IMSET_ADCCOMPUPD_M                                     0x00000020U
#define CKMD_IMSET_ADCCOMPUPD_S                                              5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_IMSET_TRACKREFOOR                                      0x00000010U
#define CKMD_IMSET_TRACKREFOOR_M                                    0x00000010U
#define CKMD_IMSET_TRACKREFOOR_S                                             4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_IMSET_TRACKREFLOSS                                     0x00000008U
#define CKMD_IMSET_TRACKREFLOSS_M                                   0x00000008U
#define CKMD_IMSET_TRACKREFLOSS_S                                            3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_IMSET_HFXTAMPGOOD                                      0x00000004U
#define CKMD_IMSET_HFXTAMPGOOD_M                                    0x00000004U
#define CKMD_IMSET_HFXTAMPGOOD_S                                             2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_IMSET_HFXTFAULT                                        0x00000002U
#define CKMD_IMSET_HFXTFAULT_M                                      0x00000002U
#define CKMD_IMSET_HFXTFAULT_S                                               1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_IMSET_HFXTGOOD                                         0x00000001U
#define CKMD_IMSET_HFXTGOOD_M                                       0x00000001U
#define CKMD_IMSET_HFXTGOOD_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_IMCLR
//
//*****************************************************************************
// Field:    [17] LFTICK
//
// 32kHz TICK to RTC and WDT.
//
// Either derived from selected LFCLK or generated from CLKULL in absence of
// LFCLK.
#define CKMD_IMCLR_LFTICK                                           0x00020000U
#define CKMD_IMCLR_LFTICK_M                                         0x00020000U
#define CKMD_IMCLR_LFTICK_S                                                 17U

// Field:    [16] LFGEARRSTRT
//
// LFINC filter gearing restart.
//
// Indicates that the LFINC filter restarted gearing. Subsequent LFINC
// estimates may have higher variation.
#define CKMD_IMCLR_LFGEARRSTRT                                      0x00010000U
#define CKMD_IMCLR_LFGEARRSTRT_M                                    0x00010000U
#define CKMD_IMCLR_LFGEARRSTRT_S                                            16U

// Field:    [15] AMPSETTLED
//
// HFXT Amplitude compensation - settled
//
// Indicates that the amplitude compensation FSM has reached the SETTLED or
// TCXOMODE state,
// and the controls configured in HFXTTARG or HFXTDYN are reached.
#define CKMD_IMCLR_AMPSETTLED                                       0x00008000U
#define CKMD_IMCLR_AMPSETTLED_M                                     0x00008000U
#define CKMD_IMCLR_AMPSETTLED_S                                             15U

// Field:    [14] AMPCTRLATTARG
//
// HFXT Amplitude compensation - controls at target
//
// Indicates that the control values configured in HFXTTARG or HFXTDYN are
// reached.
// Applies to Q1CAP, Q2CAP and IREF.
#define CKMD_IMCLR_AMPCTRLATTARG                                    0x00004000U
#define CKMD_IMCLR_AMPCTRLATTARG_M                                  0x00004000U
#define CKMD_IMCLR_AMPCTRLATTARG_S                                          14U

// Field:    [13] PRELFEDGE
//
// Pre-LF clock edge detect.
//
// Indicates that a positive edge occured on the selected pre-LF clock
// LFCLKSEL.PRE.
// Can be used by software to confirm that a LF clock source is running and
// within the expected frequency,
// before selecting it as the main LF clock source.
#define CKMD_IMCLR_PRELFEDGE                                        0x00002000U
#define CKMD_IMCLR_PRELFEDGE_M                                      0x00002000U
#define CKMD_IMCLR_PRELFEDGE_S                                              13U

// Field:    [12] LFCLKLOSS
//
// LF clock is lost.
//
// Indicates that no LF clock edge occured for ~49us (~1.6 times nominal
// period).
// The system will automatically fall-back to generating LFTICK based on
// CLKULL,
// to avoid timing corruption.
// Note that this signal is NOT related to the analog LF clock-loss detector
// which can reset the device during STANDBY.
#define CKMD_IMCLR_LFCLKLOSS                                        0x00001000U
#define CKMD_IMCLR_LFCLKLOSS_M                                      0x00001000U
#define CKMD_IMCLR_LFCLKLOSS_S                                              12U

// Field:    [11] LFCLKOOR
//
// LF clock period out-of-range.
//
// Indicates that a LF clock period was measured to be out-of-range,
// according to LFQUALCTL.MAXERR.
#define CKMD_IMCLR_LFCLKOOR                                         0x00000800U
#define CKMD_IMCLR_LFCLKOOR_M                                       0x00000800U
#define CKMD_IMCLR_LFCLKOOR_S                                               11U

// Field:    [10] LFCLKGOOD
//
// LF clock good.
//
// Indicates that the LF clock is good, according to the configuration in
// LFQUALCTL.
#define CKMD_IMCLR_LFCLKGOOD                                        0x00000400U
#define CKMD_IMCLR_LFCLKGOOD_M                                      0x00000400U
#define CKMD_IMCLR_LFCLKGOOD_S                                              10U

// Field:     [9] LFINCUPD
//
// LFINC updated.
//
// Indicates that a new LFINC measurement value is available in
// LFCLKSTAT.LFINC.
#define CKMD_IMCLR_LFINCUPD                                         0x00000200U
#define CKMD_IMCLR_LFINCUPD_M                                       0x00000200U
#define CKMD_IMCLR_LFINCUPD_S                                                9U

// Field:     [8] TDCDONE
//
// TDC done event.
//
// Indicates that the TDC measurement is done.
#define CKMD_IMCLR_TDCDONE                                          0x00000100U
#define CKMD_IMCLR_TDCDONE_M                                        0x00000100U
#define CKMD_IMCLR_TDCDONE_S                                                 8U

// Field:     [7] ADCPEAKUPD
//
// HFXT-ADC PEAK measurement update event.
//
// Indicates that the HFXT-ADC PEAK measurement is done.
#define CKMD_IMCLR_ADCPEAKUPD                                       0x00000080U
#define CKMD_IMCLR_ADCPEAKUPD_M                                     0x00000080U
#define CKMD_IMCLR_ADCPEAKUPD_S                                              7U

// Field:     [6] ADCBIASUPD
//
// HFXT-ADC BIAS measurement update event.
//
// Indicates that the HFXT-ADC BIAS measurement is done.
#define CKMD_IMCLR_ADCBIASUPD                                       0x00000040U
#define CKMD_IMCLR_ADCBIASUPD_M                                     0x00000040U
#define CKMD_IMCLR_ADCBIASUPD_S                                              6U

// Field:     [5] ADCCOMPUPD
//
// HFXT-ADC comparison update event.
//
// Indicates that the HFXT-ADC comparison is done.
#define CKMD_IMCLR_ADCCOMPUPD                                       0x00000020U
#define CKMD_IMCLR_ADCCOMPUPD_M                                     0x00000020U
#define CKMD_IMCLR_ADCCOMPUPD_S                                              5U

// Field:     [4] TRACKREFOOR
//
// Out-of-range indication from the tracking loop.
//
// Indicates that the selected reference clock frequency of the tracking loop
// is out-of-range.
#define CKMD_IMCLR_TRACKREFOOR                                      0x00000010U
#define CKMD_IMCLR_TRACKREFOOR_M                                    0x00000010U
#define CKMD_IMCLR_TRACKREFOOR_S                                             4U

// Field:     [3] TRACKREFLOSS
//
// Clock loss indication from the tracking loop.
//
// Indicates that the selected reference clock of the tracking loop is lost.
#define CKMD_IMCLR_TRACKREFLOSS                                     0x00000008U
#define CKMD_IMCLR_TRACKREFLOSS_M                                   0x00000008U
#define CKMD_IMCLR_TRACKREFLOSS_S                                            3U

// Field:     [2] HFXTAMPGOOD
//
// HFXT amplitude good indication.
#define CKMD_IMCLR_HFXTAMPGOOD                                      0x00000004U
#define CKMD_IMCLR_HFXTAMPGOOD_M                                    0x00000004U
#define CKMD_IMCLR_HFXTAMPGOOD_S                                             2U

// Field:     [1] HFXTFAULT
//
// HFXT fault indication.
//
// Indicates that HFXT did not start correctly, or its frequency is too low.
// HFXT will not recover from this fault and has to be restarted.
// This is only a one-time check at HFXT startup.
#define CKMD_IMCLR_HFXTFAULT                                        0x00000002U
#define CKMD_IMCLR_HFXTFAULT_M                                      0x00000002U
#define CKMD_IMCLR_HFXTFAULT_S                                               1U

// Field:     [0] HFXTGOOD
//
// HFXT good indication.
//
// Indicates that HFXT started correctly. The frequency is not necessarily good
// enough for radio operation.
// This is only a one-time check at HFXT startup.
#define CKMD_IMCLR_HFXTGOOD                                         0x00000001U
#define CKMD_IMCLR_HFXTGOOD_M                                       0x00000001U
#define CKMD_IMCLR_HFXTGOOD_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_HFOSCCTL
//
//*****************************************************************************
// Field: [31:24] PW
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFOSCCTL_PW_W                                                   8U
#define CKMD_HFOSCCTL_PW_M                                          0xFF000000U
#define CKMD_HFOSCCTL_PW_S                                                  24U

// Field:     [8] CLKSVTOVR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HFXT                     Internal. Only to be used through TI provided API.
// HFOSC                    Internal. Only to be used through TI provided API.
#define CKMD_HFOSCCTL_CLKSVTOVR                                     0x00000100U
#define CKMD_HFOSCCTL_CLKSVTOVR_M                                   0x00000100U
#define CKMD_HFOSCCTL_CLKSVTOVR_S                                            8U
#define CKMD_HFOSCCTL_CLKSVTOVR_HFXT                                0x00000100U
#define CKMD_HFOSCCTL_CLKSVTOVR_HFOSC                               0x00000000U

// Field:     [1] FORCEOFF
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFOSCCTL_FORCEOFF                                      0x00000002U
#define CKMD_HFOSCCTL_FORCEOFF_M                                    0x00000002U
#define CKMD_HFOSCCTL_FORCEOFF_S                                             1U

// Field:     [0] QUALBYP
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFOSCCTL_QUALBYP                                       0x00000001U
#define CKMD_HFOSCCTL_QUALBYP_M                                     0x00000001U
#define CKMD_HFOSCCTL_QUALBYP_S                                              0U

//*****************************************************************************
//
// Register: CKMD_O_HFXTCTL
//
//*****************************************************************************
// Field:    [31] AMPOVR
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_AMPOVR                                         0x80000000U
#define CKMD_HFXTCTL_AMPOVR_M                                       0x80000000U
#define CKMD_HFXTCTL_AMPOVR_S                                               31U

// Field:    [26] BIASEN
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_BIASEN                                         0x04000000U
#define CKMD_HFXTCTL_BIASEN_M                                       0x04000000U
#define CKMD_HFXTCTL_BIASEN_S                                               26U

// Field:    [25] LPBUFEN
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_LPBUFEN                                        0x02000000U
#define CKMD_HFXTCTL_LPBUFEN_M                                      0x02000000U
#define CKMD_HFXTCTL_LPBUFEN_S                                              25U

// Field:    [24] INJECT
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_INJECT                                         0x01000000U
#define CKMD_HFXTCTL_INJECT_M                                       0x01000000U
#define CKMD_HFXTCTL_INJECT_S                                               24U

// Field:    [23] QUALBYP
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_QUALBYP                                        0x00800000U
#define CKMD_HFXTCTL_QUALBYP_M                                      0x00800000U
#define CKMD_HFXTCTL_QUALBYP_S                                              23U

// Field:  [19:8] QUALDLY
//
// Skip potentially unstable clock cycles after enabling HFXT.
// Number of cycles skipped is 8*QUALDLY.
#define CKMD_HFXTCTL_QUALDLY_W                                              12U
#define CKMD_HFXTCTL_QUALDLY_M                                      0x000FFF00U
#define CKMD_HFXTCTL_QUALDLY_S                                               8U

// Field:     [7] TCXOMODE
//
// Temperature compensated crystal oscillator mode.
//
// Set this bit if a TXCO is connected.
#define CKMD_HFXTCTL_TCXOMODE                                       0x00000080U
#define CKMD_HFXTCTL_TCXOMODE_M                                     0x00000080U
#define CKMD_HFXTCTL_TCXOMODE_S                                              7U

// Field:     [6] TCXOTYPE
//
// Type of temperature compensated crystal used.
//
// Only has effect if TCXOMODE is set.
// ENUMs:
// CMOS                     Use with CMOS TCXO
// CLIPPEDSINE              Use with clipped-sine TCXO
#define CKMD_HFXTCTL_TCXOTYPE                                       0x00000040U
#define CKMD_HFXTCTL_TCXOTYPE_M                                     0x00000040U
#define CKMD_HFXTCTL_TCXOTYPE_S                                              6U
#define CKMD_HFXTCTL_TCXOTYPE_CMOS                                  0x00000040U
#define CKMD_HFXTCTL_TCXOTYPE_CLIPPEDSINE                           0x00000000U

// Field:     [2] AUTOEN
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_AUTOEN                                         0x00000004U
#define CKMD_HFXTCTL_AUTOEN_M                                       0x00000004U
#define CKMD_HFXTCTL_AUTOEN_S                                                2U

// Field:     [1] HPBUFEN
//
// High performance clock buffer enable.
//
// This bit controls the clock output for the RF PLL.
// It is required for radio operation.
#define CKMD_HFXTCTL_HPBUFEN                                        0x00000002U
#define CKMD_HFXTCTL_HPBUFEN_M                                      0x00000002U
#define CKMD_HFXTCTL_HPBUFEN_S                                               1U

// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
#define CKMD_HFXTCTL_EN                                             0x00000001U
#define CKMD_HFXTCTL_EN_M                                           0x00000001U
#define CKMD_HFXTCTL_EN_S                                                    0U

//*****************************************************************************
//
// Register: CKMD_O_LFOSCCTL
//
//*****************************************************************************
// Field:     [0] EN
//
// LFOSC enable
#define CKMD_LFOSCCTL_EN                                            0x00000001U
#define CKMD_LFOSCCTL_EN_M                                          0x00000001U
#define CKMD_LFOSCCTL_EN_S                                                   0U

//*****************************************************************************
//
// Register: CKMD_O_LFXTCTL
//
//*****************************************************************************
// Field: [14:13] LEAKCOMP
//
// Leakage compensation control
// ENUMs:
// OFF                      No leakage compensation
// HALF                     Half leakage compensation
// FULL                     Full leakage compensation
#define CKMD_LFXTCTL_LEAKCOMP_W                                              2U
#define CKMD_LFXTCTL_LEAKCOMP_M                                     0x00006000U
#define CKMD_LFXTCTL_LEAKCOMP_S                                             13U
#define CKMD_LFXTCTL_LEAKCOMP_OFF                                   0x00006000U
#define CKMD_LFXTCTL_LEAKCOMP_HALF                                  0x00002000U
#define CKMD_LFXTCTL_LEAKCOMP_FULL                                  0x00000000U

// Field:    [12] BUFBIAS
//
// Control the BIAS current of the input amp in LP buffer
// ENUMs:
// MAX                      Maximum bias current: 50nA
// MIN                      Minimum bias current: 25nA
#define CKMD_LFXTCTL_BUFBIAS                                        0x00001000U
#define CKMD_LFXTCTL_BUFBIAS_M                                      0x00001000U
#define CKMD_LFXTCTL_BUFBIAS_S                                              12U
#define CKMD_LFXTCTL_BUFBIAS_MAX                                    0x00001000U
#define CKMD_LFXTCTL_BUFBIAS_MIN                                    0x00000000U

// Field:  [11:8] AMPBIAS
//
// Adjust current mirror ratio into oscillator core. This value is depending on
// crystal and is set by FW. This field uses a 2's complement encoding.
#define CKMD_LFXTCTL_AMPBIAS_W                                               4U
#define CKMD_LFXTCTL_AMPBIAS_M                                      0x00000F00U
#define CKMD_LFXTCTL_AMPBIAS_S                                               8U

// Field:   [7:6] BIASBOOST
//
// Boost oscillator amplitude
//
// This value depends on the crystal and needs to be configured by Firmware.
#define CKMD_LFXTCTL_BIASBOOST_W                                             2U
#define CKMD_LFXTCTL_BIASBOOST_M                                    0x000000C0U
#define CKMD_LFXTCTL_BIASBOOST_S                                             6U

// Field:   [5:4] REGBIAS
//
// Regulation loop bias resistor value
//
// This value depends on the crystal and needs to be configured by Firmware.
#define CKMD_LFXTCTL_REGBIAS_W                                               2U
#define CKMD_LFXTCTL_REGBIAS_M                                      0x00000030U
#define CKMD_LFXTCTL_REGBIAS_S                                               4U

// Field:     [2] HPBUFEN
//
// Control the buffer used. In normal operation, low-power buffer is used in
// all device modes. The high-performance buffer is only used for test
// purposes.
#define CKMD_LFXTCTL_HPBUFEN                                        0x00000004U
#define CKMD_LFXTCTL_HPBUFEN_M                                      0x00000004U
#define CKMD_LFXTCTL_HPBUFEN_S                                               2U

// Field:     [1] AMPREGMODE
//
// Amplitude regulation mode
// ENUMs:
// LOOPDIS                  Amplitude control loop disabled
// LOOPEN                   Amplitude control loop enabled
#define CKMD_LFXTCTL_AMPREGMODE                                     0x00000002U
#define CKMD_LFXTCTL_AMPREGMODE_M                                   0x00000002U
#define CKMD_LFXTCTL_AMPREGMODE_S                                            1U
#define CKMD_LFXTCTL_AMPREGMODE_LOOPDIS                             0x00000002U
#define CKMD_LFXTCTL_AMPREGMODE_LOOPEN                              0x00000000U

// Field:     [0] EN
//
// LFXT enable
#define CKMD_LFXTCTL_EN                                             0x00000001U
#define CKMD_LFXTCTL_EN_M                                           0x00000001U
#define CKMD_LFXTCTL_EN_S                                                    0U

//*****************************************************************************
//
// Register: CKMD_O_LFQUALCTL
//
//*****************************************************************************
// Field:  [13:8] MAXERR
//
// Maximum LFCLK period error.
//
// Value given in microseconds, 3 integer bits + 3 fractional bits.
#define CKMD_LFQUALCTL_MAXERR_W                                              6U
#define CKMD_LFQUALCTL_MAXERR_M                                     0x00003F00U
#define CKMD_LFQUALCTL_MAXERR_S                                              8U

// Field:   [7:0] CONSEC
//
// Number of consecutive times the LFCLK period error has to be
// smaller than MAXERR to be considered "good".
// Setting this value to 0 will bypass clock qualification,
// and the "good" indicator will always be 1.
#define CKMD_LFQUALCTL_CONSEC_W                                              8U
#define CKMD_LFQUALCTL_CONSEC_M                                     0x000000FFU
#define CKMD_LFQUALCTL_CONSEC_S                                              0U

//*****************************************************************************
//
// Register: CKMD_O_LFINCCTL
//
//*****************************************************************************
// Field:    [31] PREVENTSTBY
//
// Controls if the LFINC filter prevents STANBY entry until settled.
// ENUMs:
// ON                       Enable. Prevent STANDBY entry.
// OFF                      Disable. Do not prevent STANDBY entry.
#define CKMD_LFINCCTL_PREVENTSTBY                                   0x80000000U
#define CKMD_LFINCCTL_PREVENTSTBY_M                                 0x80000000U
#define CKMD_LFINCCTL_PREVENTSTBY_S                                         31U
#define CKMD_LFINCCTL_PREVENTSTBY_ON                                0x80000000U
#define CKMD_LFINCCTL_PREVENTSTBY_OFF                               0x00000000U

// Field:  [29:8] INT
//
// Integral part of the LFINC filter.
//
// This value is updated by Hardware to reflect the current state of the
// filter.
// It can also be written to change the current state.
#define CKMD_LFINCCTL_INT_W                                                 22U
#define CKMD_LFINCCTL_INT_M                                         0x3FFFFF00U
#define CKMD_LFINCCTL_INT_S                                                  8U

// Field:     [7] STOPGEAR
//
// Controls the final gear of the LFINC filter.
// ENUMs:
// HIGH                     Highest final gear. Best dynamic frequency
//                          tracking, but higher variation in filter value.
// LOW                      Lowest final gear. Best settling, but less dynamic
//                          frequency tracking.
#define CKMD_LFINCCTL_STOPGEAR                                      0x00000080U
#define CKMD_LFINCCTL_STOPGEAR_M                                    0x00000080U
#define CKMD_LFINCCTL_STOPGEAR_S                                             7U
#define CKMD_LFINCCTL_STOPGEAR_HIGH                                 0x00000080U
#define CKMD_LFINCCTL_STOPGEAR_LOW                                  0x00000000U

// Field:   [6:5] ERRTHR
//
// Controls the threshold for gearing restart of the LFINC filter.
//
// Only effective if GEARRSTRT is not ONETHR or TWOTHR.
// ENUMs:
// SMALL                    Restart gearing on small error. Potentially more
//                          false restarts, faster response on small
//                          frequency shifts.
// MIDSMALL                 Middle value towards SMALL.
// MIDLARGE                 Middle value towards LARGE.
// LARGE                    Restart gearing on large error. Fewer false
//                          restarts, slower response on small frequency
//                          shifts.
#define CKMD_LFINCCTL_ERRTHR_W                                               2U
#define CKMD_LFINCCTL_ERRTHR_M                                      0x00000060U
#define CKMD_LFINCCTL_ERRTHR_S                                               5U
#define CKMD_LFINCCTL_ERRTHR_SMALL                                  0x00000060U
#define CKMD_LFINCCTL_ERRTHR_MIDSMALL                               0x00000040U
#define CKMD_LFINCCTL_ERRTHR_MIDLARGE                               0x00000020U
#define CKMD_LFINCCTL_ERRTHR_LARGE                                  0x00000000U

// Field:   [4:3] GEARRSTRT
//
// Controls gearing restart of the LFINC filter.
// ENUMs:
// TWOTHR                   Restart gearing when the error accumulator crosses
//                          the threshold twice in a row.
// ONETHR                   Restart gearing when the error accumulator crosses
//                          the threshold once.
// NEVER                    Never restart gearing. Very stable filter value,
//                          but very slow response on frequency changes.
#define CKMD_LFINCCTL_GEARRSTRT_W                                            2U
#define CKMD_LFINCCTL_GEARRSTRT_M                                   0x00000018U
#define CKMD_LFINCCTL_GEARRSTRT_S                                            3U
#define CKMD_LFINCCTL_GEARRSTRT_TWOTHR                              0x00000010U
#define CKMD_LFINCCTL_GEARRSTRT_ONETHR                              0x00000008U
#define CKMD_LFINCCTL_GEARRSTRT_NEVER                               0x00000000U

// Field:     [2] SOFTRSTRT
//
// Use a higher gear after re-enabling / wakeup.
//
// The filter will require 16-24 LFCLK periods to settle (depending on
// STOPGEAR), but may respond faster to frequency changes during STANDBY.
// ENUMs:
// ON                       Use soft gearing restarts
// OFF                      Don't use soft gearing restarts
#define CKMD_LFINCCTL_SOFTRSTRT                                     0x00000004U
#define CKMD_LFINCCTL_SOFTRSTRT_M                                   0x00000004U
#define CKMD_LFINCCTL_SOFTRSTRT_S                                            2U
#define CKMD_LFINCCTL_SOFTRSTRT_ON                                  0x00000004U
#define CKMD_LFINCCTL_SOFTRSTRT_OFF                                 0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_LFINCOVR
//
//*****************************************************************************
// Field:    [31] OVERRIDE
//
// Override LF increment
//
// Use the value provided in LFINC instead of the value calculated by Hardware.
#define CKMD_LFINCOVR_OVERRIDE                                      0x80000000U
#define CKMD_LFINCOVR_OVERRIDE_M                                    0x80000000U
#define CKMD_LFINCOVR_OVERRIDE_S                                            31U

// Field:  [21:0] LFINC
//
// LF increment value
//
// This value is used when OVERRIDE is set to 1.
// Otherwise the value is calculated automatically.
#define CKMD_LFINCOVR_LFINC_W                                               22U
#define CKMD_LFINCOVR_LFINC_M                                       0x003FFFFFU
#define CKMD_LFINCOVR_LFINC_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_AMPADCCTL
//
//*****************************************************************************
// Field:    [31] SWOVR
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_SWOVR                                        0x80000000U
#define CKMD_AMPADCCTL_SWOVR_M                                      0x80000000U
#define CKMD_AMPADCCTL_SWOVR_S                                              31U

// Field:    [17] PEAKDETEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ENABLE                   Internal. Only to be used through TI provided API.
// DISABLE                  Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_PEAKDETEN                                    0x00020000U
#define CKMD_AMPADCCTL_PEAKDETEN_M                                  0x00020000U
#define CKMD_AMPADCCTL_PEAKDETEN_S                                          17U
#define CKMD_AMPADCCTL_PEAKDETEN_ENABLE                             0x00020000U
#define CKMD_AMPADCCTL_PEAKDETEN_DISABLE                            0x00000000U

// Field:    [16] ADCEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ENABLE                   Internal. Only to be used through TI provided API.
// DISABLE                  Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_ADCEN                                        0x00010000U
#define CKMD_AMPADCCTL_ADCEN_M                                      0x00010000U
#define CKMD_AMPADCCTL_ADCEN_S                                              16U
#define CKMD_AMPADCCTL_ADCEN_ENABLE                                 0x00010000U
#define CKMD_AMPADCCTL_ADCEN_DISABLE                                0x00000000U

// Field:  [14:8] COMPVAL
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_COMPVAL_W                                             7U
#define CKMD_AMPADCCTL_COMPVAL_M                                    0x00007F00U
#define CKMD_AMPADCCTL_COMPVAL_S                                             8U

// Field:     [4] SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PEAK                     Internal. Only to be used through TI provided API.
// BIAS                     Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_SRCSEL                                       0x00000010U
#define CKMD_AMPADCCTL_SRCSEL_M                                     0x00000010U
#define CKMD_AMPADCCTL_SRCSEL_S                                              4U
#define CKMD_AMPADCCTL_SRCSEL_PEAK                                  0x00000010U
#define CKMD_AMPADCCTL_SRCSEL_BIAS                                  0x00000000U

// Field:     [1] COMPSTRT
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_COMPSTRT                                     0x00000002U
#define CKMD_AMPADCCTL_COMPSTRT_M                                   0x00000002U
#define CKMD_AMPADCCTL_COMPSTRT_S                                            1U

// Field:     [0] SARSTRT
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCCTL_SARSTRT                                      0x00000001U
#define CKMD_AMPADCCTL_SARSTRT_M                                    0x00000001U
#define CKMD_AMPADCCTL_SARSTRT_S                                             0U

//*****************************************************************************
//
// Register: CKMD_O_HFTRACKCTL
//
//*****************************************************************************
// Field:    [31] EN
//
// Enable tracking loop.
#define CKMD_HFTRACKCTL_EN                                          0x80000000U
#define CKMD_HFTRACKCTL_EN_M                                        0x80000000U
#define CKMD_HFTRACKCTL_EN_S                                                31U

// Field:    [30] DSMBYP
//
// Bypass Delta-Sigma-Modulation of fine trim.
#define CKMD_HFTRACKCTL_DSMBYP                                      0x40000000U
#define CKMD_HFTRACKCTL_DSMBYP_M                                    0x40000000U
#define CKMD_HFTRACKCTL_DSMBYP_S                                            30U

// Field: [27:26] REFCLK
//
// Select the reference clock for the tracking loop.
// Change only while the tracking loop is disabled.
// ENUMs:
// GPI                      Select GPI as reference clock.
// LRF                      Select LRF reference clock.
// HFXT                     Select HFXT as reference clock.
#define CKMD_HFTRACKCTL_REFCLK_W                                             2U
#define CKMD_HFTRACKCTL_REFCLK_M                                    0x0C000000U
#define CKMD_HFTRACKCTL_REFCLK_S                                            26U
#define CKMD_HFTRACKCTL_REFCLK_GPI                                  0x08000000U
#define CKMD_HFTRACKCTL_REFCLK_LRF                                  0x04000000U
#define CKMD_HFTRACKCTL_REFCLK_HFXT                                 0x00000000U

// Field:  [25:0] RATIO
//
// Reference clock ratio.
//
// RATIO = 24MHz / (2*reference-frequency) * 2^24
// Commonly used reference clock frequencies are provided as enumerations.
// ENUMs:
// REF4M                    Use for 4MHz reference clock
// REF8M                    Use for 8MHz reference clock
// REF48M                   Use for 48MHz reference clock
#define CKMD_HFTRACKCTL_RATIO_W                                             26U
#define CKMD_HFTRACKCTL_RATIO_M                                     0x03FFFFFFU
#define CKMD_HFTRACKCTL_RATIO_S                                              0U
#define CKMD_HFTRACKCTL_RATIO_REF4M                                 0x03000000U
#define CKMD_HFTRACKCTL_RATIO_REF8M                                 0x01800000U
#define CKMD_HFTRACKCTL_RATIO_REF48M                                0x00400000U

//*****************************************************************************
//
// Register: CKMD_O_LDOCTL
//
//*****************************************************************************
// Field:    [31] SWOVR
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_SWOVR                                           0x80000000U
#define CKMD_LDOCTL_SWOVR_M                                         0x80000000U
#define CKMD_LDOCTL_SWOVR_S                                                 31U

// Field:     [4] HFXTLVLEN
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_HFXTLVLEN                                       0x00000010U
#define CKMD_LDOCTL_HFXTLVLEN_M                                     0x00000010U
#define CKMD_LDOCTL_HFXTLVLEN_S                                              4U

// Field:     [3] STARTCTL
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_STARTCTL                                        0x00000008U
#define CKMD_LDOCTL_STARTCTL_M                                      0x00000008U
#define CKMD_LDOCTL_STARTCTL_S                                               3U

// Field:     [2] START
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_START                                           0x00000004U
#define CKMD_LDOCTL_START_M                                         0x00000004U
#define CKMD_LDOCTL_START_S                                                  2U

// Field:     [1] BYPASS
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_BYPASS                                          0x00000002U
#define CKMD_LDOCTL_BYPASS_M                                        0x00000002U
#define CKMD_LDOCTL_BYPASS_S                                                 1U

// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
#define CKMD_LDOCTL_EN                                              0x00000001U
#define CKMD_LDOCTL_EN_M                                            0x00000001U
#define CKMD_LDOCTL_EN_S                                                     0U

//*****************************************************************************
//
// Register: CKMD_O_NABIASCTL
//
//*****************************************************************************
// Field:     [0] EN
//
// Enable nanoamp-bias
#define CKMD_NABIASCTL_EN                                           0x00000001U
#define CKMD_NABIASCTL_EN_M                                         0x00000001U
#define CKMD_NABIASCTL_EN_S                                                  0U

//*****************************************************************************
//
// Register: CKMD_O_LFMONCTL
//
//*****************************************************************************
// Field:     [0] EN
//
// Enable LFMONITOR.
// Enable only after a LF clock source has been selected, enabled and is
// stable.
// If LFMONITOR detects a clock loss, the system will be reset.
#define CKMD_LFMONCTL_EN                                            0x00000001U
#define CKMD_LFMONCTL_EN_M                                          0x00000001U
#define CKMD_LFMONCTL_EN_S                                                   0U

//*****************************************************************************
//
// Register: CKMD_O_LFCLKSEL
//
//*****************************************************************************
// Field:   [3:2] PRE
//
// Select low frequency clock source for the PRELFCLK interrupt.
//
// Can be used by Software to confirm that the clock is running and it's
// frequency is good, before selecting it in MAIN.
// ENUMs:
// EXTLF                    External LF clock through GPI.
// LFXT                     Low frequency crystal oscillator
// LFOSC                    Low frequency on-chip oscillator
// NONE                     No clock. Output will be tied low.
#define CKMD_LFCLKSEL_PRE_W                                                  2U
#define CKMD_LFCLKSEL_PRE_M                                         0x0000000CU
#define CKMD_LFCLKSEL_PRE_S                                                  2U
#define CKMD_LFCLKSEL_PRE_EXTLF                                     0x0000000CU
#define CKMD_LFCLKSEL_PRE_LFXT                                      0x00000008U
#define CKMD_LFCLKSEL_PRE_LFOSC                                     0x00000004U
#define CKMD_LFCLKSEL_PRE_NONE                                      0x00000000U

// Field:   [1:0] MAIN
//
// Select the main low frequency clock source.
//
// If running, this clock will be used to generate LFTICK and as CLKULL during
// STANDBY.
// If not running, LFTICK will be generated from HFOSC and STANDBY entry will
// be prevented.
// ENUMs:
// EXTLF                    External LF clock through GPI.
// LFXT                     Low frequency crystal oscillator
// LFOSC                    Low frequency on-chip oscillator
// FAKE                     No LF clock selected. LFTICK will be generated
//                          from HFOSC, STANDBY entry will be prevented.
#define CKMD_LFCLKSEL_MAIN_W                                                 2U
#define CKMD_LFCLKSEL_MAIN_M                                        0x00000003U
#define CKMD_LFCLKSEL_MAIN_S                                                 0U
#define CKMD_LFCLKSEL_MAIN_EXTLF                                    0x00000003U
#define CKMD_LFCLKSEL_MAIN_LFXT                                     0x00000002U
#define CKMD_LFCLKSEL_MAIN_LFOSC                                    0x00000001U
#define CKMD_LFCLKSEL_MAIN_FAKE                                     0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCCLKSEL
//
//*****************************************************************************
// Field:   [1:0] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GPI                      Internal. Only to be used through TI provided API.
// CLKULL                   Internal. Only to be used through TI provided API.
// CLKSVT                   Internal. Only to be used through TI provided API.
// NONE                     Internal. Only to be used through TI provided API.
#define CKMD_TDCCLKSEL_REFCLK_W                                              2U
#define CKMD_TDCCLKSEL_REFCLK_M                                     0x00000003U
#define CKMD_TDCCLKSEL_REFCLK_S                                              0U
#define CKMD_TDCCLKSEL_REFCLK_GPI                                   0x00000003U
#define CKMD_TDCCLKSEL_REFCLK_CLKULL                                0x00000002U
#define CKMD_TDCCLKSEL_REFCLK_CLKSVT                                0x00000001U
#define CKMD_TDCCLKSEL_REFCLK_NONE                                  0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_ADCCLKSEL
//
//*****************************************************************************
// Field:   [1:0] SRC
//
// Select ADC clock source
//
// Change only while ADC is disabled.
// ENUMs:
// HFXT                     48MHz HFXT
// CLKSVT                   48MHz CLKSVT
#define CKMD_ADCCLKSEL_SRC_W                                                 2U
#define CKMD_ADCCLKSEL_SRC_M                                        0x00000003U
#define CKMD_ADCCLKSEL_SRC_S                                                 0U
#define CKMD_ADCCLKSEL_SRC_HFXT                                     0x00000001U
#define CKMD_ADCCLKSEL_SRC_CLKSVT                                   0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_LFCLKSTAT
//
//*****************************************************************************
// Field:    [31] GOOD
//
// Low frequency clock good
//
// Note: This is only a coarse frequency check based on LFQUALCTL. The clock
// may not be accurate enough for timing purposes.
#define CKMD_LFCLKSTAT_GOOD                                         0x80000000U
#define CKMD_LFCLKSTAT_GOOD_M                                       0x80000000U
#define CKMD_LFCLKSTAT_GOOD_S                                               31U

// Field:    [25] FLTSETTLED
//
// LFINC filter is running and settled.
#define CKMD_LFCLKSTAT_FLTSETTLED                                   0x02000000U
#define CKMD_LFCLKSTAT_FLTSETTLED_M                                 0x02000000U
#define CKMD_LFCLKSTAT_FLTSETTLED_S                                         25U

// Field:    [24] LFTICKSRC
//
// Source of LFTICK.
// ENUMs:
// FAKE                     LFTICK generated from CLKULL (LFCLK not available)
// LFCLK                    LFTICK generated from the selected LFCLK
#define CKMD_LFCLKSTAT_LFTICKSRC                                    0x01000000U
#define CKMD_LFCLKSTAT_LFTICKSRC_M                                  0x01000000U
#define CKMD_LFCLKSTAT_LFTICKSRC_S                                          24U
#define CKMD_LFCLKSTAT_LFTICKSRC_FAKE                               0x01000000U
#define CKMD_LFCLKSTAT_LFTICKSRC_LFCLK                              0x00000000U

// Field: [23:22] LFINCSRC
//
// Source of LFINC used by the RTC.
//
// This value depends on LFINCOVR.OVERRIDE, LF clock availability, HF tracking
// loop status and the device state (ACTIVE/STANDBY).
// ENUMs:
// FAKE                     Using FAKE LFTICKs with corresponding LFINC value.
// OVERRIDE                 Using override value from LFINCOVR.LFINC
// AVG                      Using filtered / average value.
//                          This value is updated by
//                          hardware and can be read and updated in
//                          LFINCCTL.INT.
// MEAS                     Using measured value.
//                          This value is updated by
//                          hardware and can be read from LFINC.
#define CKMD_LFCLKSTAT_LFINCSRC_W                                            2U
#define CKMD_LFCLKSTAT_LFINCSRC_M                                   0x00C00000U
#define CKMD_LFCLKSTAT_LFINCSRC_S                                           22U
#define CKMD_LFCLKSTAT_LFINCSRC_FAKE                                0x00C00000U
#define CKMD_LFCLKSTAT_LFINCSRC_OVERRIDE                            0x00800000U
#define CKMD_LFCLKSTAT_LFINCSRC_AVG                                 0x00400000U
#define CKMD_LFCLKSTAT_LFINCSRC_MEAS                                0x00000000U

// Field:  [21:0] LFINC
//
// Measured value of LFINC.
//
// Given in microseconds with 16 fractional bits.
// This value is calculated by Hardware.
// It is the LFCLK period according to CLKULL cycles.
#define CKMD_LFCLKSTAT_LFINC_W                                              22U
#define CKMD_LFCLKSTAT_LFINC_M                                      0x003FFFFFU
#define CKMD_LFCLKSTAT_LFINC_S                                               0U

//*****************************************************************************
//
// Register: CKMD_O_HFXTSTAT
//
//*****************************************************************************
// Field: [30:16] STARTUPTIME
//
// HFXT startup time
//
// Can be used by software to plan starting HFXT ahead in time.
// Measured whenever HFXT is enabled in CLKULL periods (24MHz), from HFXTCTL.EN
// until the clock is good for radio operation (amplitude compensation is
// settled).
#define CKMD_HFXTSTAT_STARTUPTIME_W                                         15U
#define CKMD_HFXTSTAT_STARTUPTIME_M                                 0x7FFF0000U
#define CKMD_HFXTSTAT_STARTUPTIME_S                                         16U

// Field:     [1] FAULT
//
// HFXT clock fault
//
// Indicates a lower than expected HFXT frequency.
// HFXT will not recover from this fault, disabling and re-enabling HFXT is
// required.
#define CKMD_HFXTSTAT_FAULT                                         0x00000002U
#define CKMD_HFXTSTAT_FAULT_M                                       0x00000002U
#define CKMD_HFXTSTAT_FAULT_S                                                1U

// Field:     [0] GOOD
//
// HFXT clock available.
//
// The frequency is not necessarily good enough for radio operation.
#define CKMD_HFXTSTAT_GOOD                                          0x00000001U
#define CKMD_HFXTSTAT_GOOD_M                                        0x00000001U
#define CKMD_HFXTSTAT_GOOD_S                                                 0U

//*****************************************************************************
//
// Register: CKMD_O_AMPADCSTAT
//
//*****************************************************************************
// Field:    [24] COMPOUT
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCSTAT_COMPOUT                                     0x01000000U
#define CKMD_AMPADCSTAT_COMPOUT_M                                   0x01000000U
#define CKMD_AMPADCSTAT_COMPOUT_S                                           24U

// Field: [22:16] PEAKRAW
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCSTAT_PEAKRAW_W                                            7U
#define CKMD_AMPADCSTAT_PEAKRAW_M                                   0x007F0000U
#define CKMD_AMPADCSTAT_PEAKRAW_S                                           16U

// Field:  [15:8] PEAK
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCSTAT_PEAK_W                                               8U
#define CKMD_AMPADCSTAT_PEAK_M                                      0x0000FF00U
#define CKMD_AMPADCSTAT_PEAK_S                                               8U

// Field:   [6:0] BIAS
//
// Internal. Only to be used through TI provided API.
#define CKMD_AMPADCSTAT_BIAS_W                                               7U
#define CKMD_AMPADCSTAT_BIAS_M                                      0x0000007FU
#define CKMD_AMPADCSTAT_BIAS_S                                               0U

//*****************************************************************************
//
// Register: CKMD_O_TRACKSTAT
//
//*****************************************************************************
// Field:    [31] LOOPERRVLD
//
// Current HFOSC tracking error valid
//
// This bit is one if the tracking loop is running and the error value is
// valid.
#define CKMD_TRACKSTAT_LOOPERRVLD                                   0x80000000U
#define CKMD_TRACKSTAT_LOOPERRVLD_M                                 0x80000000U
#define CKMD_TRACKSTAT_LOOPERRVLD_S                                         31U

// Field: [29:16] LOOPERR
//
// Current HFOSC tracking error
#define CKMD_TRACKSTAT_LOOPERR_W                                            14U
#define CKMD_TRACKSTAT_LOOPERR_M                                    0x3FFF0000U
#define CKMD_TRACKSTAT_LOOPERR_S                                            16U

// Field:  [12:0] FINETRIM
//
// Current HFOSC Fine-trim value
//
// This field uses the internal fractional representation (sign, 4 integer
// bits, 8 fractional bits).
// The actual trim value applied to the oscillator is delta-sigma modulated 5
// bits non-signed
// (inverted sign bit + integer bits).
#define CKMD_TRACKSTAT_FINETRIM_W                                           13U
#define CKMD_TRACKSTAT_FINETRIM_M                                   0x00001FFFU
#define CKMD_TRACKSTAT_FINETRIM_S                                            0U

//*****************************************************************************
//
// Register: CKMD_O_AMPSTAT
//
//*****************************************************************************
// Field: [28:25] STATE
//
// Current AMPCOMP FSM state.
// ENUMs:
// SETTLED                  Settled state
// UPDATEUP                 Amplitude up correction
// TXCOMODE                 TCXO settled state
// SHUTDN0                  First shutdown state
// INJWAIT                  Post injection settle wait
// UPDATEDN                 Amplitude down correction
// RAMP0                    Initial amplitude ramping with HFXTINIT values
// RAMP1                    Transition to HFXTTARG values
// INJECT                   Injecting HFOSC for fast startup
// SHUTDN1                  Second shutdown state
// LDOSTART                 Starting LDO
// IDLE                     FSM in idle state
#define CKMD_AMPSTAT_STATE_W                                                 4U
#define CKMD_AMPSTAT_STATE_M                                        0x1E000000U
#define CKMD_AMPSTAT_STATE_S                                                25U
#define CKMD_AMPSTAT_STATE_SETTLED                                  0x1E000000U
#define CKMD_AMPSTAT_STATE_UPDATEUP                                 0x1C000000U
#define CKMD_AMPSTAT_STATE_TXCOMODE                                 0x18000000U
#define CKMD_AMPSTAT_STATE_SHUTDN0                                  0x14000000U
#define CKMD_AMPSTAT_STATE_INJWAIT                                  0x0E000000U
#define CKMD_AMPSTAT_STATE_UPDATEDN                                 0x0C000000U
#define CKMD_AMPSTAT_STATE_RAMP0                                    0x0A000000U
#define CKMD_AMPSTAT_STATE_RAMP1                                    0x08000000U
#define CKMD_AMPSTAT_STATE_INJECT                                   0x06000000U
#define CKMD_AMPSTAT_STATE_SHUTDN1                                  0x04000000U
#define CKMD_AMPSTAT_STATE_LDOSTART                                 0x02000000U
#define CKMD_AMPSTAT_STATE_IDLE                                     0x00000000U

// Field: [24:18] IDAC
//
// Current IDAC control value.
#define CKMD_AMPSTAT_IDAC_W                                                  7U
#define CKMD_AMPSTAT_IDAC_M                                         0x01FC0000U
#define CKMD_AMPSTAT_IDAC_S                                                 18U

// Field: [17:14] IREF
//
// Current IREF control value.
#define CKMD_AMPSTAT_IREF_W                                                  4U
#define CKMD_AMPSTAT_IREF_M                                         0x0003C000U
#define CKMD_AMPSTAT_IREF_S                                                 14U

// Field:  [13:8] Q2CAP
//
// Current Q2CAP control value.
#define CKMD_AMPSTAT_Q2CAP_W                                                 6U
#define CKMD_AMPSTAT_Q2CAP_M                                        0x00003F00U
#define CKMD_AMPSTAT_Q2CAP_S                                                 8U

// Field:   [7:2] Q1CAP
//
// Current Q1CAP control value.
#define CKMD_AMPSTAT_Q1CAP_W                                                 6U
#define CKMD_AMPSTAT_Q1CAP_M                                        0x000000FCU
#define CKMD_AMPSTAT_Q1CAP_S                                                 2U

// Field:     [1] CTRLATTARGET
//
// HFXT control values match target values.
//
// This applies to IREF, Q1CAP, Q2CAP values.
#define CKMD_AMPSTAT_CTRLATTARGET                                   0x00000002U
#define CKMD_AMPSTAT_CTRLATTARGET_M                                 0x00000002U
#define CKMD_AMPSTAT_CTRLATTARGET_S                                          1U

// Field:     [0] AMPGOOD
//
// HFXT amplitude good
#define CKMD_AMPSTAT_AMPGOOD                                        0x00000001U
#define CKMD_AMPSTAT_AMPGOOD_M                                      0x00000001U
#define CKMD_AMPSTAT_AMPGOOD_S                                               0U

//*****************************************************************************
//
// Register: CKMD_O_ATBCTL0
//
//*****************************************************************************
// Field:  [18:0] SEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// LFXTTESTCLK              Internal. Only to be used through TI provided API.
// LFOSCTESTCLK             Internal. Only to be used through TI provided API.
// HFXTTESTCLK              Internal. Only to be used through TI provided API.
// HFOSCTESTCLK             Internal. Only to be used through TI provided API.
// LFMONVTEST               Internal. Only to be used through TI provided API.
// LFOSCVDDL                Internal. Only to be used through TI provided API.
// HFOSCIBIAS               Internal. Only to be used through TI provided API.
// HFOSCVDDL                Internal. Only to be used through TI provided API.
// HFOSCVREF                Internal. Only to be used through TI provided API.
// NABIASITEST              Internal. Only to be used through TI provided API.
// ADCDACOUT                Internal. Only to be used through TI provided API.
// ADCCOMPIN                Internal. Only to be used through TI provided API.
// ADCCOMPOUT               Internal. Only to be used through TI provided API.
// LFXTANA                  Internal. Only to be used through TI provided API.
// LDOITEST                 Internal. Only to be used through TI provided API.
// VDDCKM                   Internal. Only to be used through TI provided API.
// HFXTANA                  Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL0_SEL_W                                                  19U
#define CKMD_ATBCTL0_SEL_M                                          0x0007FFFFU
#define CKMD_ATBCTL0_SEL_S                                                   0U
#define CKMD_ATBCTL0_SEL_LFXTTESTCLK                                0x00070000U
#define CKMD_ATBCTL0_SEL_LFOSCTESTCLK                               0x00050000U
#define CKMD_ATBCTL0_SEL_HFXTTESTCLK                                0x00030000U
#define CKMD_ATBCTL0_SEL_HFOSCTESTCLK                               0x00010000U
#define CKMD_ATBCTL0_SEL_LFMONVTEST                                 0x00001000U
#define CKMD_ATBCTL0_SEL_LFOSCVDDL                                  0x00000800U
#define CKMD_ATBCTL0_SEL_HFOSCIBIAS                                 0x00000400U
#define CKMD_ATBCTL0_SEL_HFOSCVDDL                                  0x00000200U
#define CKMD_ATBCTL0_SEL_HFOSCVREF                                  0x00000100U
#define CKMD_ATBCTL0_SEL_NABIASITEST                                0x00000080U
#define CKMD_ATBCTL0_SEL_ADCDACOUT                                  0x00000040U
#define CKMD_ATBCTL0_SEL_ADCCOMPIN                                  0x00000020U
#define CKMD_ATBCTL0_SEL_ADCCOMPOUT                                 0x00000010U
#define CKMD_ATBCTL0_SEL_LFXTANA                                    0x00000008U
#define CKMD_ATBCTL0_SEL_LDOITEST                                   0x00000004U
#define CKMD_ATBCTL0_SEL_VDDCKM                                     0x00000002U
#define CKMD_ATBCTL0_SEL_HFXTANA                                    0x00000001U
#define CKMD_ATBCTL0_SEL_OFF                                        0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_ATBCTL1
//
//*****************************************************************************
// Field: [14:13] LFOSC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BOTH                     Internal. Only to be used through TI provided API.
// VDDLOCAL                 Internal. Only to be used through TI provided API.
// TESTCLK                  Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_LFOSC_W                                                 2U
#define CKMD_ATBCTL1_LFOSC_M                                        0x00006000U
#define CKMD_ATBCTL1_LFOSC_S                                                13U
#define CKMD_ATBCTL1_LFOSC_BOTH                                     0x00006000U
#define CKMD_ATBCTL1_LFOSC_VDDLOCAL                                 0x00004000U
#define CKMD_ATBCTL1_LFOSC_TESTCLK                                  0x00002000U
#define CKMD_ATBCTL1_LFOSC_OFF                                      0x00000000U

// Field:    [12] NABIAS
//
// Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_NABIAS                                         0x00001000U
#define CKMD_ATBCTL1_NABIAS_M                                       0x00001000U
#define CKMD_ATBCTL1_NABIAS_S                                               12U

// Field:    [10] LFXT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TESTCLK                  Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_LFXT                                           0x00000400U
#define CKMD_ATBCTL1_LFXT_M                                         0x00000400U
#define CKMD_ATBCTL1_LFXT_S                                                 10U
#define CKMD_ATBCTL1_LFXT_TESTCLK                                   0x00000400U
#define CKMD_ATBCTL1_LFXT_OFF                                       0x00000000U

// Field:   [9:8] LFMON
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TEST2                    Internal. Only to be used through TI provided API.
// TEST1                    Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_LFMON_W                                                 2U
#define CKMD_ATBCTL1_LFMON_M                                        0x00000300U
#define CKMD_ATBCTL1_LFMON_S                                                 8U
#define CKMD_ATBCTL1_LFMON_TEST2                                    0x00000200U
#define CKMD_ATBCTL1_LFMON_TEST1                                    0x00000100U
#define CKMD_ATBCTL1_LFMON_OFF                                      0x00000000U

// Field:     [7] HFXT
//
// Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_HFXT                                           0x00000080U
#define CKMD_ATBCTL1_HFXT_M                                         0x00000080U
#define CKMD_ATBCTL1_HFXT_S                                                  7U

// Field:     [0] HFOSC
//
// Internal. Only to be used through TI provided API.
#define CKMD_ATBCTL1_HFOSC                                          0x00000001U
#define CKMD_ATBCTL1_HFOSC_M                                        0x00000001U
#define CKMD_ATBCTL1_HFOSC_S                                                 0U

//*****************************************************************************
//
// Register: CKMD_O_DTBCTL
//
//*****************************************************************************
// Field: [22:18] DSEL2
//
// Internal. Only to be used through TI provided API.
#define CKMD_DTBCTL_DSEL2_W                                                  5U
#define CKMD_DTBCTL_DSEL2_M                                         0x007C0000U
#define CKMD_DTBCTL_DSEL2_S                                                 18U

// Field: [17:13] DSEL1
//
// Internal. Only to be used through TI provided API.
#define CKMD_DTBCTL_DSEL1_W                                                  5U
#define CKMD_DTBCTL_DSEL1_M                                         0x0003E000U
#define CKMD_DTBCTL_DSEL1_S                                                 13U

// Field:  [12:8] DSEL0
//
// Internal. Only to be used through TI provided API.
#define CKMD_DTBCTL_DSEL0_W                                                  5U
#define CKMD_DTBCTL_DSEL0_M                                         0x00001F00U
#define CKMD_DTBCTL_DSEL0_S                                                  8U

// Field:   [7:4] CLKSEL
//
// Select clock to output on DTB[0]
// ENUMs:
// LFXT                     Select LFXT
// LFOSC                    Select LFOSC
// HFXT                     Select HFXT
// HFXTBY8                  Select HFXT divided by 8
// HFOSC                    Select HFOSC after qualification
// LFCLK                    Select LFCLK (selected by LFCLKSEL.MAIN)
// TRACKREF                 Select tracking loop reference clock
// CLKADC                   Select CLKADC (48 MHz)
// CLKSVT                   Select CLKSVT (48 MHz)
// CLKULL                   Select CLKULL (24 MHz during ACTIVE, 32kHz during
//                          STANDBY)
#define CKMD_DTBCTL_CLKSEL_W                                                 4U
#define CKMD_DTBCTL_CLKSEL_M                                        0x000000F0U
#define CKMD_DTBCTL_CLKSEL_S                                                 4U
#define CKMD_DTBCTL_CLKSEL_LFXT                                     0x000000F0U
#define CKMD_DTBCTL_CLKSEL_LFOSC                                    0x000000E0U
#define CKMD_DTBCTL_CLKSEL_HFXT                                     0x000000D0U
#define CKMD_DTBCTL_CLKSEL_HFXTBY8                                  0x000000C0U
#define CKMD_DTBCTL_CLKSEL_HFOSC                                    0x000000A0U
#define CKMD_DTBCTL_CLKSEL_LFCLK                                    0x00000070U
#define CKMD_DTBCTL_CLKSEL_TRACKREF                                 0x00000040U
#define CKMD_DTBCTL_CLKSEL_CLKADC                                   0x00000020U
#define CKMD_DTBCTL_CLKSEL_CLKSVT                                   0x00000010U
#define CKMD_DTBCTL_CLKSEL_CLKULL                                   0x00000000U

// Field:     [0] EN
//
// Enable DTB output
#define CKMD_DTBCTL_EN                                              0x00000001U
#define CKMD_DTBCTL_EN_M                                            0x00000001U
#define CKMD_DTBCTL_EN_S                                                     0U

//*****************************************************************************
//
// Register: CKMD_O_TRIM0
//
//*****************************************************************************
// Field:   [8:5] HFOSC_CAP
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM0_HFOSC_CAP_W                                               4U
#define CKMD_TRIM0_HFOSC_CAP_M                                      0x000001E0U
#define CKMD_TRIM0_HFOSC_CAP_S                                               5U

// Field:   [4:0] HFOSC_COARSE
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM0_HFOSC_COARSE_W                                            5U
#define CKMD_TRIM0_HFOSC_COARSE_M                                   0x0000001FU
#define CKMD_TRIM0_HFOSC_COARSE_S                                            0U

//*****************************************************************************
//
// Register: CKMD_O_TRIM1
//
//*****************************************************************************
// Field: [31:30] HFXTSLICER
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_HFXTSLICER_W                                              2U
#define CKMD_TRIM1_HFXTSLICER_M                                     0xC0000000U
#define CKMD_TRIM1_HFXTSLICER_S                                             30U

// Field: [29:28] PEAKIBIAS
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_PEAKIBIAS_W                                               2U
#define CKMD_TRIM1_PEAKIBIAS_M                                      0x30000000U
#define CKMD_TRIM1_PEAKIBIAS_S                                              28U

// Field:    [27] NABIAS_UDIGLDO
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_NABIAS_UDIGLDO                                   0x08000000U
#define CKMD_TRIM1_NABIAS_UDIGLDO_M                                 0x08000000U
#define CKMD_TRIM1_NABIAS_UDIGLDO_S                                         27U

// Field: [26:24] LDOBW
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_LDOBW_W                                                   3U
#define CKMD_TRIM1_LDOBW_M                                          0x07000000U
#define CKMD_TRIM1_LDOBW_S                                                  24U

// Field: [23:20] LDOFB
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_LDOFB_W                                                   4U
#define CKMD_TRIM1_LDOFB_M                                          0x00F00000U
#define CKMD_TRIM1_LDOFB_S                                                  20U

// Field: [19:16] LFDLY
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_LFDLY_W                                                   4U
#define CKMD_TRIM1_LFDLY_M                                          0x000F0000U
#define CKMD_TRIM1_LFDLY_S                                                  16U

// Field:    [15] NABIAS_LFOSC
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_NABIAS_LFOSC                                     0x00008000U
#define CKMD_TRIM1_NABIAS_LFOSC_M                                   0x00008000U
#define CKMD_TRIM1_NABIAS_LFOSC_S                                           15U

// Field:  [14:8] NABIAS_RES
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_NABIAS_RES_W                                              7U
#define CKMD_TRIM1_NABIAS_RES_M                                     0x00007F00U
#define CKMD_TRIM1_NABIAS_RES_S                                              8U

// Field:   [7:0] LFOSC_CAP
//
// Internal. Only to be used through TI provided API.
#define CKMD_TRIM1_LFOSC_CAP_W                                               8U
#define CKMD_TRIM1_LFOSC_CAP_M                                      0x000000FFU
#define CKMD_TRIM1_LFOSC_CAP_S                                               0U

//*****************************************************************************
//
// Register: CKMD_O_HFXTINIT
//
//*****************************************************************************
// Field: [29:23] AMPTHR
//
// Amplitude threshold during HFXT ramping
#define CKMD_HFXTINIT_AMPTHR_W                                               7U
#define CKMD_HFXTINIT_AMPTHR_M                                      0x3F800000U
#define CKMD_HFXTINIT_AMPTHR_S                                              23U

// Field: [22:16] IDAC
//
// Initial HFXT IDAC current
#define CKMD_HFXTINIT_IDAC_W                                                 7U
#define CKMD_HFXTINIT_IDAC_M                                        0x007F0000U
#define CKMD_HFXTINIT_IDAC_S                                                16U

// Field: [15:12] IREF
//
// Initial HFXT IREF current
#define CKMD_HFXTINIT_IREF_W                                                 4U
#define CKMD_HFXTINIT_IREF_M                                        0x0000F000U
#define CKMD_HFXTINIT_IREF_S                                                12U

// Field:  [11:6] Q2CAP
//
// Initial HFXT Q2 cap trim
#define CKMD_HFXTINIT_Q2CAP_W                                                6U
#define CKMD_HFXTINIT_Q2CAP_M                                       0x00000FC0U
#define CKMD_HFXTINIT_Q2CAP_S                                                6U

// Field:   [5:0] Q1CAP
//
// Initial HFXT Q1 cap trim
#define CKMD_HFXTINIT_Q1CAP_W                                                6U
#define CKMD_HFXTINIT_Q1CAP_M                                       0x0000003FU
#define CKMD_HFXTINIT_Q1CAP_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_HFXTTARG
//
//*****************************************************************************
// Field: [31:30] AMPHYST
//
// ADC hysteresis used during IDAC updates.
//
// Every AMPCFG1.INTERVAL, IDAC will be regulated
// - up as long as ADC < AMPTHR
// - down as long as ADC > AMPTHR+AMPHYST
#define CKMD_HFXTTARG_AMPHYST_W                                              2U
#define CKMD_HFXTTARG_AMPHYST_M                                     0xC0000000U
#define CKMD_HFXTTARG_AMPHYST_S                                             30U

// Field: [29:23] AMPTHR
//
// Minimum HFXT amplitude
#define CKMD_HFXTTARG_AMPTHR_W                                               7U
#define CKMD_HFXTTARG_AMPTHR_M                                      0x3F800000U
#define CKMD_HFXTTARG_AMPTHR_S                                              23U

// Field: [22:16] IDAC
//
// Minimum IDAC current
#define CKMD_HFXTTARG_IDAC_W                                                 7U
#define CKMD_HFXTTARG_IDAC_M                                        0x007F0000U
#define CKMD_HFXTTARG_IDAC_S                                                16U

// Field: [15:12] IREF
//
// Target HFXT IREF current
#define CKMD_HFXTTARG_IREF_W                                                 4U
#define CKMD_HFXTTARG_IREF_M                                        0x0000F000U
#define CKMD_HFXTTARG_IREF_S                                                12U

// Field:  [11:6] Q2CAP
//
// Target HFXT Q2 cap trim
#define CKMD_HFXTTARG_Q2CAP_W                                                6U
#define CKMD_HFXTTARG_Q2CAP_M                                       0x00000FC0U
#define CKMD_HFXTTARG_Q2CAP_S                                                6U

// Field:   [5:0] Q1CAP
//
// Target HFXT Q1 cap trim
#define CKMD_HFXTTARG_Q1CAP_W                                                6U
#define CKMD_HFXTTARG_Q1CAP_M                                       0x0000003FU
#define CKMD_HFXTTARG_Q1CAP_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_HFXTDYN
//
//*****************************************************************************
// Field:    [31] SEL
//
// Select the dynamic configuration.
//
// Amplitude ramping will always happen using the values in HFXTINIT, and
// HFXTTARG.
// Afterwards, this bit can be used to select between HFXTTARG and HFXTDYN.
// Hardware will ensure a smooth transition of analog control signals.
// ENUMs:
// DYNAMIC                  Select configuration in HFXTDYN.
// TARGET                   Select configuration in HFXTTARG.
#define CKMD_HFXTDYN_SEL                                            0x80000000U
#define CKMD_HFXTDYN_SEL_M                                          0x80000000U
#define CKMD_HFXTDYN_SEL_S                                                  31U
#define CKMD_HFXTDYN_SEL_DYNAMIC                                    0x80000000U
#define CKMD_HFXTDYN_SEL_TARGET                                     0x00000000U

// Field: [29:23] AMPTHR
//
// Minimum HFXT amplitude
#define CKMD_HFXTDYN_AMPTHR_W                                                7U
#define CKMD_HFXTDYN_AMPTHR_M                                       0x3F800000U
#define CKMD_HFXTDYN_AMPTHR_S                                               23U

// Field: [22:16] IDAC
//
// Minimum IDAC current
#define CKMD_HFXTDYN_IDAC_W                                                  7U
#define CKMD_HFXTDYN_IDAC_M                                         0x007F0000U
#define CKMD_HFXTDYN_IDAC_S                                                 16U

// Field: [15:12] IREF
//
// Target HFXT IREF current
#define CKMD_HFXTDYN_IREF_W                                                  4U
#define CKMD_HFXTDYN_IREF_M                                         0x0000F000U
#define CKMD_HFXTDYN_IREF_S                                                 12U

// Field:  [11:6] Q2CAP
//
// Target HFXT Q2 cap trim
#define CKMD_HFXTDYN_Q2CAP_W                                                 6U
#define CKMD_HFXTDYN_Q2CAP_M                                        0x00000FC0U
#define CKMD_HFXTDYN_Q2CAP_S                                                 6U

// Field:   [5:0] Q1CAP
//
// Target HFXT Q1 cap trim
#define CKMD_HFXTDYN_Q1CAP_W                                                 6U
#define CKMD_HFXTDYN_Q1CAP_M                                        0x0000003FU
#define CKMD_HFXTDYN_Q1CAP_S                                                 0U

//*****************************************************************************
//
// Register: CKMD_O_AMPCFG0
//
//*****************************************************************************
// Field: [31:28] Q2DLY
//
// Q2CAP change delay.
//
// Number of clock cycles to wait before changing Q2CAP by one step.
// Clock frequency defined in FSMRATE.
#define CKMD_AMPCFG0_Q2DLY_W                                                 4U
#define CKMD_AMPCFG0_Q2DLY_M                                        0xF0000000U
#define CKMD_AMPCFG0_Q2DLY_S                                                28U

// Field: [27:24] Q1DLY
//
// Q1CAP change delay.
//
// Number of clock cycles to wait before changing Q1CAP by one step.
// Clock frequency defined in FSMRATE.
#define CKMD_AMPCFG0_Q1DLY_W                                                 4U
#define CKMD_AMPCFG0_Q1DLY_M                                        0x0F000000U
#define CKMD_AMPCFG0_Q1DLY_S                                                24U

// Field: [23:20] ADCDLY
//
// ADC and PEAKDET startup time.
//
// Number of clock cycles to wait after enabling the PEAKDET and ADC before the
// first measurement.
// Clock frequency defined in FSMRATE.
#define CKMD_AMPCFG0_ADCDLY_W                                                4U
#define CKMD_AMPCFG0_ADCDLY_M                                       0x00F00000U
#define CKMD_AMPCFG0_ADCDLY_S                                               20U

// Field: [19:15] LDOSTART
//
// LDO startup time.
//
// Number of clock cycles to bypass the LDO resistors for faster startup.
// Clock frequency defined in FSMRATE.
#define CKMD_AMPCFG0_LDOSTART_W                                              5U
#define CKMD_AMPCFG0_LDOSTART_M                                     0x000F8000U
#define CKMD_AMPCFG0_LDOSTART_S                                             15U

// Field: [14:10] INJWAIT
//
// Inject HFOSC for faster HFXT startup.
//
// This value specifies the number of clock cycles to wait after injection is
// done.
// The clock speed is defined in FSMRATE.
#define CKMD_AMPCFG0_INJWAIT_W                                               5U
#define CKMD_AMPCFG0_INJWAIT_M                                      0x00007C00U
#define CKMD_AMPCFG0_INJWAIT_S                                              10U

// Field:   [9:5] INJTIME
//
// Inject HFOSC for faster HFXT startup.
//
// This value specifies the number of clock cycles the injection is enabled.
// The clock speed is defined in FSMRATE.
// Set to 0 to disable injection.
#define CKMD_AMPCFG0_INJTIME_W                                               5U
#define CKMD_AMPCFG0_INJTIME_M                                      0x000003E0U
#define CKMD_AMPCFG0_INJTIME_S                                               5U

// Field:   [4:0] FSMRATE
//
// Update rate for the AMPCOMP update rate.
// Also affects the clock rate for the Amplitude ADC.
//
// The update rate is 6MHz / (FSMRATE+1).
// ENUMs:
// _250K                    250 kHz
// _500K                    500 kHz
// _1M                      1 MHz
// _2M                      2 MHz
// _3M                      3 MHz
// _6M                      6 MHz
#define CKMD_AMPCFG0_FSMRATE_W                                               5U
#define CKMD_AMPCFG0_FSMRATE_M                                      0x0000001FU
#define CKMD_AMPCFG0_FSMRATE_S                                               0U
#define CKMD_AMPCFG0_FSMRATE__250K                                  0x00000017U
#define CKMD_AMPCFG0_FSMRATE__500K                                  0x0000000BU
#define CKMD_AMPCFG0_FSMRATE__1M                                    0x00000005U
#define CKMD_AMPCFG0_FSMRATE__2M                                    0x00000002U
#define CKMD_AMPCFG0_FSMRATE__3M                                    0x00000001U
#define CKMD_AMPCFG0_FSMRATE__6M                                    0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_AMPCFG1
//
//*****************************************************************************
// Field: [31:28] IDACDLY
//
// IDAC change delay.
//
// Time to wait before changing IDAC by one step.
// This time needs to be long enough for the crystal to settle.
// The number of clock cycles to wait is IDACDLY<<4 + 15.
// Clock frequency defined in AMPCFG0.FSMRATE.
#define CKMD_AMPCFG1_IDACDLY_W                                               4U
#define CKMD_AMPCFG1_IDACDLY_M                                      0xF0000000U
#define CKMD_AMPCFG1_IDACDLY_S                                              28U

// Field: [27:24] IREFDLY
//
// IREF change delay.
//
// Number of clock cycles to wait before changing IREF by one step.
// Clock frequency defined in AMPCFG0.FSMRATE.
#define CKMD_AMPCFG1_IREFDLY_W                                               4U
#define CKMD_AMPCFG1_IREFDLY_M                                      0x0F000000U
#define CKMD_AMPCFG1_IREFDLY_S                                              24U

// Field: [23:12] BIASLT
//
// Lifetime of the amplitude ADC bias value.
// This value specifies the number of adjustment intervals,
// until the ADC bias value has to be measured again.
// Set to 0 to disable automatic bias measurements.
#define CKMD_AMPCFG1_BIASLT_W                                               12U
#define CKMD_AMPCFG1_BIASLT_M                                       0x00FFF000U
#define CKMD_AMPCFG1_BIASLT_S                                               12U

// Field:  [11:0] INTERVAL
//
// Interval for amplitude adjustments.
// Set to 0 to disable periodic adjustments.
//
// This value specifies the number of clock cycles between adjustments.
// The clock speed is defined in AMPCFG0.FSMRATE.
#define CKMD_AMPCFG1_INTERVAL_W                                             12U
#define CKMD_AMPCFG1_INTERVAL_M                                     0x00000FFFU
#define CKMD_AMPCFG1_INTERVAL_S                                              0U

//*****************************************************************************
//
// Register: CKMD_O_LOOPCFG
//
//*****************************************************************************
// Field: [31:26] FINETRIM_INIT
//
// Initial value for the resistor fine trim
#define CKMD_LOOPCFG_FINETRIM_INIT_W                                         6U
#define CKMD_LOOPCFG_FINETRIM_INIT_M                                0xFC000000U
#define CKMD_LOOPCFG_FINETRIM_INIT_S                                        26U

// Field: [25:21] BOOST_TARGET
//
// Number of error-updates using BOOST values, before using KI/KP
#define CKMD_LOOPCFG_BOOST_TARGET_W                                          5U
#define CKMD_LOOPCFG_BOOST_TARGET_M                                 0x03E00000U
#define CKMD_LOOPCFG_BOOST_TARGET_S                                         21U

// Field: [20:18] KP_BOOST
//
// Proportional loop coefficient during BOOST
#define CKMD_LOOPCFG_KP_BOOST_W                                              3U
#define CKMD_LOOPCFG_KP_BOOST_M                                     0x001C0000U
#define CKMD_LOOPCFG_KP_BOOST_S                                             18U

// Field: [17:15] KI_BOOST
//
// Integral loop coefficient during BOOST
#define CKMD_LOOPCFG_KI_BOOST_W                                              3U
#define CKMD_LOOPCFG_KI_BOOST_M                                     0x00038000U
#define CKMD_LOOPCFG_KI_BOOST_S                                             15U

// Field: [14:10] SETTLED_TARGET
//
// Number of updates before HFOSC is considered "settled"
#define CKMD_LOOPCFG_SETTLED_TARGET_W                                        5U
#define CKMD_LOOPCFG_SETTLED_TARGET_M                               0x00007C00U
#define CKMD_LOOPCFG_SETTLED_TARGET_S                                       10U

// Field:   [9:6] OOR_LIMIT
//
// Out-of-range threshold
#define CKMD_LOOPCFG_OOR_LIMIT_W                                             4U
#define CKMD_LOOPCFG_OOR_LIMIT_M                                    0x000003C0U
#define CKMD_LOOPCFG_OOR_LIMIT_S                                             6U

// Field:   [5:3] KP
//
// Proportional loop coefficient
#define CKMD_LOOPCFG_KP_W                                                    3U
#define CKMD_LOOPCFG_KP_M                                           0x00000038U
#define CKMD_LOOPCFG_KP_S                                                    3U

// Field:   [2:0] KI
//
// Integral loop coefficient
#define CKMD_LOOPCFG_KI_W                                                    3U
#define CKMD_LOOPCFG_KI_M                                           0x00000007U
#define CKMD_LOOPCFG_KI_S                                                    0U

//*****************************************************************************
//
// Register: CKMD_O_TDCCTL
//
//*****************************************************************************
// Field:   [1:0] CMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ABORT                    Internal. Only to be used through TI provided API.
// RUN                      Internal. Only to be used through TI provided API.
// RUN_SYNC_START           Internal. Only to be used through TI provided API.
// CLR_RESULT               Internal. Only to be used through TI provided API.
#define CKMD_TDCCTL_CMD_W                                                    2U
#define CKMD_TDCCTL_CMD_M                                           0x00000003U
#define CKMD_TDCCTL_CMD_S                                                    0U
#define CKMD_TDCCTL_CMD_ABORT                                       0x00000003U
#define CKMD_TDCCTL_CMD_RUN                                         0x00000002U
#define CKMD_TDCCTL_CMD_RUN_SYNC_START                              0x00000001U
#define CKMD_TDCCTL_CMD_CLR_RESULT                                  0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCSTAT
//
//*****************************************************************************
// Field:     [9] STOP_BF
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCSTAT_STOP_BF                                        0x00000200U
#define CKMD_TDCSTAT_STOP_BF_M                                      0x00000200U
#define CKMD_TDCSTAT_STOP_BF_S                                               9U

// Field:     [8] START_BF
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCSTAT_START_BF                                       0x00000100U
#define CKMD_TDCSTAT_START_BF_M                                     0x00000100U
#define CKMD_TDCSTAT_START_BF_S                                              8U

// Field:     [7] SAT
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCSTAT_SAT                                            0x00000080U
#define CKMD_TDCSTAT_SAT_M                                          0x00000080U
#define CKMD_TDCSTAT_SAT_S                                                   7U

// Field:     [6] DONE
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCSTAT_DONE                                           0x00000040U
#define CKMD_TDCSTAT_DONE_M                                         0x00000040U
#define CKMD_TDCSTAT_DONE_S                                                  6U

// Field:   [5:0] STATE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FORCE_STOP               Internal. Only to be used through TI provided API.
// START_FALL               Internal. Only to be used through TI provided API.
// WAIT_CLR_CNT_DONE        Internal. Only to be used through TI provided API.
// POR                      Internal. Only to be used through TI provided API.
// GET_RESULT               Internal. Only to be used through TI provided API.
// WAIT_STOP_CNTDWN         Internal. Only to be used through TI provided API.
// WAIT_STOP                Internal. Only to be used through TI provided API.
// CLR_CNT                  Internal. Only to be used through TI provided API.
// IDLE                     Internal. Only to be used through TI provided API.
// WAIT_START_STOP_CNT_EN   Internal. Only to be used through TI provided API.
// WAIT_START               Internal. Only to be used through TI provided API.
#define CKMD_TDCSTAT_STATE_W                                                 6U
#define CKMD_TDCSTAT_STATE_M                                        0x0000003FU
#define CKMD_TDCSTAT_STATE_S                                                 0U
#define CKMD_TDCSTAT_STATE_FORCE_STOP                               0x0000002EU
#define CKMD_TDCSTAT_STATE_START_FALL                               0x0000001EU
#define CKMD_TDCSTAT_STATE_WAIT_CLR_CNT_DONE                        0x00000016U
#define CKMD_TDCSTAT_STATE_POR                                      0x0000000FU
#define CKMD_TDCSTAT_STATE_GET_RESULT                               0x0000000EU
#define CKMD_TDCSTAT_STATE_WAIT_STOP_CNTDWN                         0x0000000CU
#define CKMD_TDCSTAT_STATE_WAIT_STOP                                0x00000008U
#define CKMD_TDCSTAT_STATE_CLR_CNT                                  0x00000007U
#define CKMD_TDCSTAT_STATE_IDLE                                     0x00000006U
#define CKMD_TDCSTAT_STATE_WAIT_START_STOP_CNT_EN                   0x00000004U
#define CKMD_TDCSTAT_STATE_WAIT_START                               0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCRESULT
//
//*****************************************************************************
// Field:  [31:0] VALUE
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCRESULT_VALUE_W                                              32U
#define CKMD_TDCRESULT_VALUE_M                                      0xFFFFFFFFU
#define CKMD_TDCRESULT_VALUE_S                                               0U

//*****************************************************************************
//
// Register: CKMD_O_TDCSATCFG
//
//*****************************************************************************
// Field:   [4:0] LIMIT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// R30                      Internal. Only to be used through TI provided API.
// R29                      Internal. Only to be used through TI provided API.
// R28                      Internal. Only to be used through TI provided API.
// R27                      Internal. Only to be used through TI provided API.
// R26                      Internal. Only to be used through TI provided API.
// R25                      Internal. Only to be used through TI provided API.
// R24                      Internal. Only to be used through TI provided API.
// R23                      Internal. Only to be used through TI provided API.
// R22                      Internal. Only to be used through TI provided API.
// R21                      Internal. Only to be used through TI provided API.
// R20                      Internal. Only to be used through TI provided API.
// R19                      Internal. Only to be used through TI provided API.
// R18                      Internal. Only to be used through TI provided API.
// R17                      Internal. Only to be used through TI provided API.
// R16                      Internal. Only to be used through TI provided API.
// R15                      Internal. Only to be used through TI provided API.
// R14                      Internal. Only to be used through TI provided API.
// R13                      Internal. Only to be used through TI provided API.
// R12                      Internal. Only to be used through TI provided API.
// NONE                     Internal. Only to be used through TI provided API.
#define CKMD_TDCSATCFG_LIMIT_W                                               5U
#define CKMD_TDCSATCFG_LIMIT_M                                      0x0000001FU
#define CKMD_TDCSATCFG_LIMIT_S                                               0U
#define CKMD_TDCSATCFG_LIMIT_R30                                    0x00000015U
#define CKMD_TDCSATCFG_LIMIT_R29                                    0x00000014U
#define CKMD_TDCSATCFG_LIMIT_R28                                    0x00000013U
#define CKMD_TDCSATCFG_LIMIT_R27                                    0x00000012U
#define CKMD_TDCSATCFG_LIMIT_R26                                    0x00000011U
#define CKMD_TDCSATCFG_LIMIT_R25                                    0x00000010U
#define CKMD_TDCSATCFG_LIMIT_R24                                    0x0000000FU
#define CKMD_TDCSATCFG_LIMIT_R23                                    0x0000000EU
#define CKMD_TDCSATCFG_LIMIT_R22                                    0x0000000DU
#define CKMD_TDCSATCFG_LIMIT_R21                                    0x0000000CU
#define CKMD_TDCSATCFG_LIMIT_R20                                    0x0000000BU
#define CKMD_TDCSATCFG_LIMIT_R19                                    0x0000000AU
#define CKMD_TDCSATCFG_LIMIT_R18                                    0x00000009U
#define CKMD_TDCSATCFG_LIMIT_R17                                    0x00000008U
#define CKMD_TDCSATCFG_LIMIT_R16                                    0x00000007U
#define CKMD_TDCSATCFG_LIMIT_R15                                    0x00000006U
#define CKMD_TDCSATCFG_LIMIT_R14                                    0x00000005U
#define CKMD_TDCSATCFG_LIMIT_R13                                    0x00000004U
#define CKMD_TDCSATCFG_LIMIT_R12                                    0x00000003U
#define CKMD_TDCSATCFG_LIMIT_NONE                                   0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCTRIGSRC
//
//*****************************************************************************
// Field:    [15] STOP_POL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// LOW                      Internal. Only to be used through TI provided API.
// HIGH                     Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGSRC_STOP_POL                                    0x00008000U
#define CKMD_TDCTRIGSRC_STOP_POL_M                                  0x00008000U
#define CKMD_TDCTRIGSRC_STOP_POL_S                                          15U
#define CKMD_TDCTRIGSRC_STOP_POL_LOW                                0x00008000U
#define CKMD_TDCTRIGSRC_STOP_POL_HIGH                               0x00000000U

// Field:  [12:8] STOP_SRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TDC_PRE                  Internal. Only to be used through TI provided API.
// DTB15                    Internal. Only to be used through TI provided API.
// DTB14                    Internal. Only to be used through TI provided API.
// DTB13                    Internal. Only to be used through TI provided API.
// DTB12                    Internal. Only to be used through TI provided API.
// DTB11                    Internal. Only to be used through TI provided API.
// DTB10                    Internal. Only to be used through TI provided API.
// DTB9                     Internal. Only to be used through TI provided API.
// DTB8                     Internal. Only to be used through TI provided API.
// DTB7                     Internal. Only to be used through TI provided API.
// DTB6                     Internal. Only to be used through TI provided API.
// DTB5                     Internal. Only to be used through TI provided API.
// DTB4                     Internal. Only to be used through TI provided API.
// DTB3                     Internal. Only to be used through TI provided API.
// DTB2                     Internal. Only to be used through TI provided API.
// DTB1                     Internal. Only to be used through TI provided API.
// DTB0                     Internal. Only to be used through TI provided API.
// GPI                      Internal. Only to be used through TI provided API.
// LFCLK_DLY                Internal. Only to be used through TI provided API.
// LFXT                     Internal. Only to be used through TI provided API.
// LFOSC                    Internal. Only to be used through TI provided API.
// LFTICK                   Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGSRC_STOP_SRC_W                                           5U
#define CKMD_TDCTRIGSRC_STOP_SRC_M                                  0x00001F00U
#define CKMD_TDCTRIGSRC_STOP_SRC_S                                           8U
#define CKMD_TDCTRIGSRC_STOP_SRC_TDC_PRE                            0x00001F00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB15                              0x00001400U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB14                              0x00001300U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB13                              0x00001200U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB12                              0x00001100U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB11                              0x00001000U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB10                              0x00000F00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB9                               0x00000E00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB8                               0x00000D00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB7                               0x00000C00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB6                               0x00000B00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB5                               0x00000A00U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB4                               0x00000900U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB3                               0x00000800U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB2                               0x00000700U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB1                               0x00000600U
#define CKMD_TDCTRIGSRC_STOP_SRC_DTB0                               0x00000500U
#define CKMD_TDCTRIGSRC_STOP_SRC_GPI                                0x00000400U
#define CKMD_TDCTRIGSRC_STOP_SRC_LFCLK_DLY                          0x00000300U
#define CKMD_TDCTRIGSRC_STOP_SRC_LFXT                               0x00000200U
#define CKMD_TDCTRIGSRC_STOP_SRC_LFOSC                              0x00000100U
#define CKMD_TDCTRIGSRC_STOP_SRC_LFTICK                             0x00000000U

// Field:     [7] START_POL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// LOW                      Internal. Only to be used through TI provided API.
// HIGH                     Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGSRC_START_POL                                   0x00000080U
#define CKMD_TDCTRIGSRC_START_POL_M                                 0x00000080U
#define CKMD_TDCTRIGSRC_START_POL_S                                          7U
#define CKMD_TDCTRIGSRC_START_POL_LOW                               0x00000080U
#define CKMD_TDCTRIGSRC_START_POL_HIGH                              0x00000000U

// Field:   [4:0] START_SRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TDC_PRE                  Internal. Only to be used through TI provided API.
// DTB15                    Internal. Only to be used through TI provided API.
// DTB14                    Internal. Only to be used through TI provided API.
// DTB13                    Internal. Only to be used through TI provided API.
// DTB12                    Internal. Only to be used through TI provided API.
// DTB11                    Internal. Only to be used through TI provided API.
// DTB10                    Internal. Only to be used through TI provided API.
// DTB9                     Internal. Only to be used through TI provided API.
// DTB8                     Internal. Only to be used through TI provided API.
// DTB7                     Internal. Only to be used through TI provided API.
// DTB6                     Internal. Only to be used through TI provided API.
// DTB5                     Internal. Only to be used through TI provided API.
// DTB4                     Internal. Only to be used through TI provided API.
// DTB3                     Internal. Only to be used through TI provided API.
// DTB2                     Internal. Only to be used through TI provided API.
// DTB1                     Internal. Only to be used through TI provided API.
// DTB0                     Internal. Only to be used through TI provided API.
// GPI                      Internal. Only to be used through TI provided API.
// LFCLK_DLY                Internal. Only to be used through TI provided API.
// LFXT                     Internal. Only to be used through TI provided API.
// LFOSC                    Internal. Only to be used through TI provided API.
// LFTICK                   Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGSRC_START_SRC_W                                          5U
#define CKMD_TDCTRIGSRC_START_SRC_M                                 0x0000001FU
#define CKMD_TDCTRIGSRC_START_SRC_S                                          0U
#define CKMD_TDCTRIGSRC_START_SRC_TDC_PRE                           0x0000001FU
#define CKMD_TDCTRIGSRC_START_SRC_DTB15                             0x00000014U
#define CKMD_TDCTRIGSRC_START_SRC_DTB14                             0x00000013U
#define CKMD_TDCTRIGSRC_START_SRC_DTB13                             0x00000012U
#define CKMD_TDCTRIGSRC_START_SRC_DTB12                             0x00000011U
#define CKMD_TDCTRIGSRC_START_SRC_DTB11                             0x00000010U
#define CKMD_TDCTRIGSRC_START_SRC_DTB10                             0x0000000FU
#define CKMD_TDCTRIGSRC_START_SRC_DTB9                              0x0000000EU
#define CKMD_TDCTRIGSRC_START_SRC_DTB8                              0x0000000DU
#define CKMD_TDCTRIGSRC_START_SRC_DTB7                              0x0000000CU
#define CKMD_TDCTRIGSRC_START_SRC_DTB6                              0x0000000BU
#define CKMD_TDCTRIGSRC_START_SRC_DTB5                              0x0000000AU
#define CKMD_TDCTRIGSRC_START_SRC_DTB4                              0x00000009U
#define CKMD_TDCTRIGSRC_START_SRC_DTB3                              0x00000008U
#define CKMD_TDCTRIGSRC_START_SRC_DTB2                              0x00000007U
#define CKMD_TDCTRIGSRC_START_SRC_DTB1                              0x00000006U
#define CKMD_TDCTRIGSRC_START_SRC_DTB0                              0x00000005U
#define CKMD_TDCTRIGSRC_START_SRC_GPI                               0x00000004U
#define CKMD_TDCTRIGSRC_START_SRC_LFCLK_DLY                         0x00000003U
#define CKMD_TDCTRIGSRC_START_SRC_LFXT                              0x00000002U
#define CKMD_TDCTRIGSRC_START_SRC_LFOSC                             0x00000001U
#define CKMD_TDCTRIGSRC_START_SRC_LFTICK                            0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCTRIGCNT
//
//*****************************************************************************
// Field:  [15:0] CNT
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGCNT_CNT_W                                               16U
#define CKMD_TDCTRIGCNT_CNT_M                                       0x0000FFFFU
#define CKMD_TDCTRIGCNT_CNT_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_TDCTRIGCNTLOAD
//
//*****************************************************************************
// Field:  [15:0] CNT
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGCNTLOAD_CNT_W                                           16U
#define CKMD_TDCTRIGCNTLOAD_CNT_M                                   0x0000FFFFU
#define CKMD_TDCTRIGCNTLOAD_CNT_S                                            0U

//*****************************************************************************
//
// Register: CKMD_O_TDCTRIGCNTCFG
//
//*****************************************************************************
// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCTRIGCNTCFG_EN                                       0x00000001U
#define CKMD_TDCTRIGCNTCFG_EN_M                                     0x00000001U
#define CKMD_TDCTRIGCNTCFG_EN_S                                              0U

//*****************************************************************************
//
// Register: CKMD_O_TDCPRECTL
//
//*****************************************************************************
// Field:     [7] RESET_N
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCPRECTL_RESET_N                                      0x00000080U
#define CKMD_TDCPRECTL_RESET_N_M                                    0x00000080U
#define CKMD_TDCPRECTL_RESET_N_S                                             7U

// Field:     [6] RATIO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV64                    Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
#define CKMD_TDCPRECTL_RATIO                                        0x00000040U
#define CKMD_TDCPRECTL_RATIO_M                                      0x00000040U
#define CKMD_TDCPRECTL_RATIO_S                                               6U
#define CKMD_TDCPRECTL_RATIO_DIV64                                  0x00000040U
#define CKMD_TDCPRECTL_RATIO_DIV16                                  0x00000000U

// Field:   [4:0] SRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HFXT                     Internal. Only to be used through TI provided API.
// HFOSC                    Internal. Only to be used through TI provided API.
// DTB15                    Internal. Only to be used through TI provided API.
// DTB14                    Internal. Only to be used through TI provided API.
// DTB13                    Internal. Only to be used through TI provided API.
// DTB12                    Internal. Only to be used through TI provided API.
// DTB11                    Internal. Only to be used through TI provided API.
// DTB10                    Internal. Only to be used through TI provided API.
// DTB9                     Internal. Only to be used through TI provided API.
// DTB8                     Internal. Only to be used through TI provided API.
// DTB7                     Internal. Only to be used through TI provided API.
// DTB6                     Internal. Only to be used through TI provided API.
// DTB5                     Internal. Only to be used through TI provided API.
// DTB4                     Internal. Only to be used through TI provided API.
// DTB3                     Internal. Only to be used through TI provided API.
// DTB2                     Internal. Only to be used through TI provided API.
// DTB1                     Internal. Only to be used through TI provided API.
// DTB0                     Internal. Only to be used through TI provided API.
// GPI                      Internal. Only to be used through TI provided API.
// LFCLK_DLY                Internal. Only to be used through TI provided API.
// LFXT                     Internal. Only to be used through TI provided API.
// LFOSC                    Internal. Only to be used through TI provided API.
// LFTICK                   Internal. Only to be used through TI provided API.
#define CKMD_TDCPRECTL_SRC_W                                                 5U
#define CKMD_TDCPRECTL_SRC_M                                        0x0000001FU
#define CKMD_TDCPRECTL_SRC_S                                                 0U
#define CKMD_TDCPRECTL_SRC_HFXT                                     0x00000016U
#define CKMD_TDCPRECTL_SRC_HFOSC                                    0x00000015U
#define CKMD_TDCPRECTL_SRC_DTB15                                    0x00000014U
#define CKMD_TDCPRECTL_SRC_DTB14                                    0x00000013U
#define CKMD_TDCPRECTL_SRC_DTB13                                    0x00000012U
#define CKMD_TDCPRECTL_SRC_DTB12                                    0x00000011U
#define CKMD_TDCPRECTL_SRC_DTB11                                    0x00000010U
#define CKMD_TDCPRECTL_SRC_DTB10                                    0x0000000FU
#define CKMD_TDCPRECTL_SRC_DTB9                                     0x0000000EU
#define CKMD_TDCPRECTL_SRC_DTB8                                     0x0000000DU
#define CKMD_TDCPRECTL_SRC_DTB7                                     0x0000000CU
#define CKMD_TDCPRECTL_SRC_DTB6                                     0x0000000BU
#define CKMD_TDCPRECTL_SRC_DTB5                                     0x0000000AU
#define CKMD_TDCPRECTL_SRC_DTB4                                     0x00000009U
#define CKMD_TDCPRECTL_SRC_DTB3                                     0x00000008U
#define CKMD_TDCPRECTL_SRC_DTB2                                     0x00000007U
#define CKMD_TDCPRECTL_SRC_DTB1                                     0x00000006U
#define CKMD_TDCPRECTL_SRC_DTB0                                     0x00000005U
#define CKMD_TDCPRECTL_SRC_GPI                                      0x00000004U
#define CKMD_TDCPRECTL_SRC_LFCLK_DLY                                0x00000003U
#define CKMD_TDCPRECTL_SRC_LFXT                                     0x00000002U
#define CKMD_TDCPRECTL_SRC_LFOSC                                    0x00000001U
#define CKMD_TDCPRECTL_SRC_LFTICK                                   0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_TDCPRECNTR
//
//*****************************************************************************
// Field:    [16] CAPT
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCPRECNTR_CAPT                                        0x00010000U
#define CKMD_TDCPRECNTR_CAPT_M                                      0x00010000U
#define CKMD_TDCPRECNTR_CAPT_S                                              16U

// Field:  [15:0] CNT
//
// Internal. Only to be used through TI provided API.
#define CKMD_TDCPRECNTR_CNT_W                                               16U
#define CKMD_TDCPRECNTR_CNT_M                                       0x0000FFFFU
#define CKMD_TDCPRECNTR_CNT_S                                                0U

//*****************************************************************************
//
// Register: CKMD_O_WDTCNT
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Counter value.
//
// A write to this field immediately starts (or restarts) the counter. It will
// count down from the written value.
// If the counter reaches 0, a reset will be generated.
// A write value of 0 immediately generates a reset.
//
// This field is only writable if not locked. See WDTLOCK register.
// Writing this field will automatically activate the lock.
//
// A read returns the current value of the counter.
#define CKMD_WDTCNT_VAL_W                                                   32U
#define CKMD_WDTCNT_VAL_M                                           0xFFFFFFFFU
#define CKMD_WDTCNT_VAL_S                                                    0U

//*****************************************************************************
//
// Register: CKMD_O_WDTTEST
//
//*****************************************************************************
// Field:     [0] STALLEN
//
// WDT stall enable
//
// This field is only writable if not locked. See WDTLOCK register.
// ENUMs:
// EN                       ENABLE
//
//                          WDT stops counting while
//                          the CPU is stopped by a debugger.
// DIS                      DISABLE
//
//                          WDT continues counting
//                          while the CPU is stopped by a debugger.
#define CKMD_WDTTEST_STALLEN                                        0x00000001U
#define CKMD_WDTTEST_STALLEN_M                                      0x00000001U
#define CKMD_WDTTEST_STALLEN_S                                               0U
#define CKMD_WDTTEST_STALLEN_EN                                     0x00000001U
#define CKMD_WDTTEST_STALLEN_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: CKMD_O_WDTLOCK
//
//*****************************************************************************
// Field:  [31:0] STAT
//
// A write with value 0x1ACCE551 unlocks the watchdog registers for write
// access.
// A write with any other value locks the watchdog registers for write access.
// Writing the WDTCNT register will also lock the watchdog registers.
//
// A read of this field returns the state of the lock (0=unlocked, 1=locked).
#define CKMD_WDTLOCK_STAT_W                                                 32U
#define CKMD_WDTLOCK_STAT_M                                         0xFFFFFFFFU
#define CKMD_WDTLOCK_STAT_S                                                  0U


#endif // __CKMD__
