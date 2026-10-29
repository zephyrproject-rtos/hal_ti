/******************************************************************************
*  Filename:       hw_lrfdrfe.h
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

#ifndef __HW_LRFDRFE_H__
#define __HW_LRFDRFE_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDRFE component
//
//*****************************************************************************
// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_ENABLE                                            0x00000000U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_FWSRC                                             0x00000004U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_INIT                                              0x00000008U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PDREQ                                             0x0000000CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVT0                                              0x00000010U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVT1                                              0x00000014U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVTMSK0                                           0x00000018U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVTMSK1                                           0x0000001CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVTCLR0                                           0x00000020U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_EVTCLR1                                           0x00000024U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_HFXTSTAT                                          0x00000028U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RFSTATE                                           0x00000030U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_API                                               0x00000048U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CMDPAR0                                           0x0000004CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CMDPAR1                                           0x00000050U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MSGBOX                                            0x00000054U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MCEDATOUT0                                        0x00000058U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MCEDATIN0                                         0x0000005CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MCECMDOUT                                         0x00000060U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MCECMDIN                                          0x00000064U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PBEDATOUT0                                        0x00000068U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PBEDATIN0                                         0x0000006CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PBECMDOUT                                         0x00000070U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PBECMDIN                                          0x00000074U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_STRB                                              0x00000078U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNTHRCFG                                        0x00000080U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNTHR                                           0x00000084U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RSSIOFFSET                                        0x00000088U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_GAINCTL                                           0x0000008CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNCTL0                                          0x00000090U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNCTL1                                          0x00000094U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE0                                            0x00000098U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE1                                            0x0000009CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE2                                            0x000000A0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE3                                            0x000000A4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE4                                            0x000000A8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_SPARE5                                            0x000000ACU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_LNA                                               0x000000B0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFAMPRFLDO                                        0x000000B4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PA0                                               0x000000B8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PA1                                               0x000000BCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_ULNA                                              0x000000C0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADC0                                            0x000000C4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADC1                                            0x000000C8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCLF                                           0x000000CCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCQUANT                                        0x000000D0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCALDO                                         0x000000D4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCDLDO                                         0x000000D8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCTST                                          0x000000DCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_ATSTREFL                                          0x000000E0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_ATSTREFH                                          0x000000E4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DCO                                               0x000000E8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIV                                               0x000000ECU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVLDO                                            0x000000F0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TDCLDO                                            0x000000F4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DCOLDO0                                           0x000000F8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DCOLDO1                                           0x000000FCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRE0                                              0x00000100U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRE1                                              0x00000104U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRE2                                              0x00000108U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRE3                                              0x0000010CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CAL0                                              0x00000110U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CAL1                                              0x00000114U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CAL2                                              0x00000118U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CAL3                                              0x0000011CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MISC0                                             0x00000120U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MISC1                                             0x00000124U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_LF0                                               0x00000128U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_LF1                                               0x0000012CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PHEDISC                                           0x00000130U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PHINIT                                            0x00000134U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLMON0                                           0x00000138U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLMON1                                           0x0000013CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MOD0                                              0x00000140U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MOD1                                              0x00000144U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX0                                              0x00000148U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX1                                              0x0000014CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX2                                              0x00000150U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX3                                              0x00000154U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX4                                              0x00000158U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX5                                              0x0000015CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX6                                              0x00000160U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX7                                              0x00000164U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX8                                              0x00000168U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX9                                              0x0000016CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX10                                             0x00000170U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTX11                                             0x00000174U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLM0L                                            0x00000178U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLM0H                                            0x0000017CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLM1L                                            0x00000180U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PLLM1H                                            0x00000184U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CALMCRS                                           0x00000188U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CALMMID                                           0x0000018CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_REFDIV                                            0x00000190U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DLOCTL0                                           0x00000198U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DLOCTL1                                           0x000001A0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DCOOVR0                                           0x000001A8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DCOOVR1                                           0x000001ACU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTST                                              0x000001B0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DLOEV                                             0x000001B4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DTSTRD                                            0x000001B8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_FDCOSPANLSB                                       0x000001BCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_FDCOSPANMSB                                       0x000001C0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TDCCAL                                            0x000001C4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_CALRES                                            0x000001C8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_GPI                                               0x000001CCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MATHACCELIN                                       0x000001D0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_LIN2LOGOUT                                        0x000001D4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVBY3OUT                                         0x000001D8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TIMCTL                                            0x000001DCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TIMINC                                            0x000001E0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TIMPER                                            0x000001E4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TIMCNT                                            0x000001E8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TIMCAPT                                           0x000001ECU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TRCCTRL                                           0x000001F0U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TRCSTAT                                           0x000001F4U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TRCCMD                                            0x000001F8U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TRCPAR0                                           0x000001FCU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_TRCPAR1                                           0x00000200U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_GPOCTL                                            0x00000204U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_ANAISOCTL                                         0x00000208U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVCTL                                            0x0000020CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RXCTRL                                            0x00000210U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNACC0                                          0x00000214U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MAGNACC1                                          0x00000218U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RSSI                                              0x0000021CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RSSIMAX                                           0x00000220U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_RFGAIN                                            0x00000224U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_IFADCSTAT                                         0x00000228U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVSTA                                            0x0000022CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVIDENDL                                         0x00000230U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVIDENDH                                         0x00000234U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVISORL                                          0x00000238U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_DIVISORH                                          0x0000023CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_QUOTIENTL                                         0x00000240U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_QUOTIENTH                                         0x00000244U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRODUCTL                                          0x00000248U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_PRODUCTH                                          0x0000024CU

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MULTSTA                                           0x00000250U

// Internal. Only to be used through TI provided API.
#define LRFDRFE_O_MULTCFG                                           0x00000258U

//*****************************************************************************
//
// Register: LRFDRFE_O_ENABLE
//
//*****************************************************************************
// Field:     [3] ACC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ENABLE_ACC1                                         0x00000008U
#define LRFDRFE_ENABLE_ACC1_M                                       0x00000008U
#define LRFDRFE_ENABLE_ACC1_S                                                3U
#define LRFDRFE_ENABLE_ACC1_EN                                      0x00000008U
#define LRFDRFE_ENABLE_ACC1_DIS                                     0x00000000U

// Field:     [2] ACC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ENABLE_ACC0                                         0x00000004U
#define LRFDRFE_ENABLE_ACC0_M                                       0x00000004U
#define LRFDRFE_ENABLE_ACC0_S                                                2U
#define LRFDRFE_ENABLE_ACC0_EN                                      0x00000004U
#define LRFDRFE_ENABLE_ACC0_DIS                                     0x00000000U

// Field:     [1] LOCTIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ENABLE_LOCTIM                                       0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_M                                     0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_S                                              1U
#define LRFDRFE_ENABLE_LOCTIM_EN                                    0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_DIS                                   0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ENABLE_TOPSM                                        0x00000001U
#define LRFDRFE_ENABLE_TOPSM_M                                      0x00000001U
#define LRFDRFE_ENABLE_TOPSM_S                                               0U
#define LRFDRFE_ENABLE_TOPSM_EN                                     0x00000001U
#define LRFDRFE_ENABLE_TOPSM_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_FWSRC
//
//*****************************************************************************
// Field:     [2] DATARAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// RFERAM                   Internal. Only to be used through TI provided API.
#define LRFDRFE_FWSRC_DATARAM                                       0x00000004U
#define LRFDRFE_FWSRC_DATARAM_M                                     0x00000004U
#define LRFDRFE_FWSRC_DATARAM_S                                              2U
#define LRFDRFE_FWSRC_DATARAM_S2RRAM                                0x00000004U
#define LRFDRFE_FWSRC_DATARAM_RFERAM                                0x00000000U

// Field:     [1] FWRAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// RFERAM                   Internal. Only to be used through TI provided API.
#define LRFDRFE_FWSRC_FWRAM                                         0x00000002U
#define LRFDRFE_FWSRC_FWRAM_M                                       0x00000002U
#define LRFDRFE_FWSRC_FWRAM_S                                                1U
#define LRFDRFE_FWSRC_FWRAM_S2RRAM                                  0x00000002U
#define LRFDRFE_FWSRC_FWRAM_RFERAM                                  0x00000000U

// Field:     [0] BANK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_FWSRC_BANK                                          0x00000001U
#define LRFDRFE_FWSRC_BANK_M                                        0x00000001U
#define LRFDRFE_FWSRC_BANK_S                                                 0U
#define LRFDRFE_FWSRC_BANK_ONE                                      0x00000001U
#define LRFDRFE_FWSRC_BANK_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_INIT
//
//*****************************************************************************
// Field:     [3] ACC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDRFE_INIT_ACC1                                           0x00000008U
#define LRFDRFE_INIT_ACC1_M                                         0x00000008U
#define LRFDRFE_INIT_ACC1_S                                                  3U
#define LRFDRFE_INIT_ACC1_RESET                                     0x00000008U
#define LRFDRFE_INIT_ACC1_NO_EFFECT                                 0x00000000U

// Field:     [2] ACC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDRFE_INIT_ACC0                                           0x00000004U
#define LRFDRFE_INIT_ACC0_M                                         0x00000004U
#define LRFDRFE_INIT_ACC0_S                                                  2U
#define LRFDRFE_INIT_ACC0_RESET                                     0x00000004U
#define LRFDRFE_INIT_ACC0_NO_EFFECT                                 0x00000000U

// Field:     [1] LOCTIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDRFE_INIT_LOCTIM                                         0x00000002U
#define LRFDRFE_INIT_LOCTIM_M                                       0x00000002U
#define LRFDRFE_INIT_LOCTIM_S                                                1U
#define LRFDRFE_INIT_LOCTIM_RESET                                   0x00000002U
#define LRFDRFE_INIT_LOCTIM_NO_EFFECT                               0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDRFE_INIT_TOPSM                                          0x00000001U
#define LRFDRFE_INIT_TOPSM_M                                        0x00000001U
#define LRFDRFE_INIT_TOPSM_S                                                 0U
#define LRFDRFE_INIT_TOPSM_RESET                                    0x00000001U
#define LRFDRFE_INIT_TOPSM_NO_EFFECT                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PDREQ
//
//*****************************************************************************
// Field:     [0] TOPSMPDREQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_PDREQ_TOPSMPDREQ                                    0x00000001U
#define LRFDRFE_PDREQ_TOPSMPDREQ_M                                  0x00000001U
#define LRFDRFE_PDREQ_TOPSMPDREQ_S                                           0U
#define LRFDRFE_PDREQ_TOPSMPDREQ_ONE                                0x00000001U
#define LRFDRFE_PDREQ_TOPSMPDREQ_ZERO                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVT0
//
//*****************************************************************************
// Field:    [14] MAGNTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_MAGNTHR                                        0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_M                                      0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_S                                              14U
#define LRFDRFE_EVT0_MAGNTHR_ONE                                    0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_ZERO                                   0x00000000U

// Field:    [13] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_S2RSTOP                                        0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_M                                      0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_S                                              13U
#define LRFDRFE_EVT0_S2RSTOP_ONE                                    0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_ZERO                                   0x00000000U

// Field:    [12] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_SYSTCMP2                                       0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_M                                     0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_S                                             12U
#define LRFDRFE_EVT0_SYSTCMP2_ONE                                   0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_ZERO                                  0x00000000U

// Field:    [11] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_SYSTCMP1                                       0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_M                                     0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_S                                             11U
#define LRFDRFE_EVT0_SYSTCMP1_ONE                                   0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_ZERO                                  0x00000000U

// Field:    [10] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_SYSTCMP0                                       0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_M                                     0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_S                                             10U
#define LRFDRFE_EVT0_SYSTCMP0_ONE                                   0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_ZERO                                  0x00000000U

// Field:     [9] PBERFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_PBERFEDAT                                      0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_M                                    0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_S                                             9U
#define LRFDRFE_EVT0_PBERFEDAT_ONE                                  0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_ZERO                                 0x00000000U

// Field:     [8] MDMRFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_MDMRFEDAT                                      0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_M                                    0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_S                                             8U
#define LRFDRFE_EVT0_MDMRFEDAT_ONE                                  0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_ZERO                                 0x00000000U

// Field:     [7] DLO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_DLO                                            0x00000080U
#define LRFDRFE_EVT0_DLO_M                                          0x00000080U
#define LRFDRFE_EVT0_DLO_S                                                   7U
#define LRFDRFE_EVT0_DLO_ONE                                        0x00000080U
#define LRFDRFE_EVT0_DLO_ZERO                                       0x00000000U

// Field:     [6] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_PBECMD                                         0x00000040U
#define LRFDRFE_EVT0_PBECMD_M                                       0x00000040U
#define LRFDRFE_EVT0_PBECMD_S                                                6U
#define LRFDRFE_EVT0_PBECMD_ONE                                     0x00000040U
#define LRFDRFE_EVT0_PBECMD_ZERO                                    0x00000000U

// Field:     [5] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_COUNTER                                        0x00000020U
#define LRFDRFE_EVT0_COUNTER_M                                      0x00000020U
#define LRFDRFE_EVT0_COUNTER_S                                               5U
#define LRFDRFE_EVT0_COUNTER_ONE                                    0x00000020U
#define LRFDRFE_EVT0_COUNTER_ZERO                                   0x00000000U

// Field:     [4] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_MDMCMD                                         0x00000010U
#define LRFDRFE_EVT0_MDMCMD_M                                       0x00000010U
#define LRFDRFE_EVT0_MDMCMD_S                                                4U
#define LRFDRFE_EVT0_MDMCMD_ONE                                     0x00000010U
#define LRFDRFE_EVT0_MDMCMD_ZERO                                    0x00000000U

// Field:     [3] ACC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_ACC1                                           0x00000008U
#define LRFDRFE_EVT0_ACC1_M                                         0x00000008U
#define LRFDRFE_EVT0_ACC1_S                                                  3U
#define LRFDRFE_EVT0_ACC1_ONE                                       0x00000008U
#define LRFDRFE_EVT0_ACC1_ZERO                                      0x00000000U

// Field:     [2] ACC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_ACC0                                           0x00000004U
#define LRFDRFE_EVT0_ACC0_M                                         0x00000004U
#define LRFDRFE_EVT0_ACC0_S                                                  2U
#define LRFDRFE_EVT0_ACC0_ONE                                       0x00000004U
#define LRFDRFE_EVT0_ACC0_ZERO                                      0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_TIMER                                          0x00000002U
#define LRFDRFE_EVT0_TIMER_M                                        0x00000002U
#define LRFDRFE_EVT0_TIMER_S                                                 1U
#define LRFDRFE_EVT0_TIMER_ONE                                      0x00000002U
#define LRFDRFE_EVT0_TIMER_ZERO                                     0x00000000U

// Field:     [0] RFEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT0_RFEAPI                                         0x00000001U
#define LRFDRFE_EVT0_RFEAPI_M                                       0x00000001U
#define LRFDRFE_EVT0_RFEAPI_S                                                0U
#define LRFDRFE_EVT0_RFEAPI_ONE                                     0x00000001U
#define LRFDRFE_EVT0_RFEAPI_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVT1
//
//*****************************************************************************
// Field:    [13] PREREFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_PREREFCLK                                      0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_M                                    0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_S                                            13U
#define LRFDRFE_EVT1_PREREFCLK_ONE                                  0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_ZERO                                 0x00000000U

// Field:    [12] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_REFCLK                                         0x00001000U
#define LRFDRFE_EVT1_REFCLK_M                                       0x00001000U
#define LRFDRFE_EVT1_REFCLK_S                                               12U
#define LRFDRFE_EVT1_REFCLK_ONE                                     0x00001000U
#define LRFDRFE_EVT1_REFCLK_ZERO                                    0x00000000U

// Field:    [11] FBLWTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_FBLWTHR                                        0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_M                                      0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_S                                              11U
#define LRFDRFE_EVT1_FBLWTHR_ONE                                    0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_ZERO                                   0x00000000U

// Field:    [10] FABVTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_FABVTHR                                        0x00000400U
#define LRFDRFE_EVT1_FABVTHR_M                                      0x00000400U
#define LRFDRFE_EVT1_FABVTHR_S                                              10U
#define LRFDRFE_EVT1_FABVTHR_ONE                                    0x00000400U
#define LRFDRFE_EVT1_FABVTHR_ZERO                                   0x00000000U

// Field:     [9] LOCK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_LOCK                                           0x00000200U
#define LRFDRFE_EVT1_LOCK_M                                         0x00000200U
#define LRFDRFE_EVT1_LOCK_S                                                  9U
#define LRFDRFE_EVT1_LOCK_ONE                                       0x00000200U
#define LRFDRFE_EVT1_LOCK_ZERO                                      0x00000000U

// Field:     [8] LOL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_LOL                                            0x00000100U
#define LRFDRFE_EVT1_LOL_M                                          0x00000100U
#define LRFDRFE_EVT1_LOL_S                                                   8U
#define LRFDRFE_EVT1_LOL_ONE                                        0x00000100U
#define LRFDRFE_EVT1_LOL_ZERO                                       0x00000000U

// Field:     [7] GPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI7                                           0x00000080U
#define LRFDRFE_EVT1_GPI7_M                                         0x00000080U
#define LRFDRFE_EVT1_GPI7_S                                                  7U
#define LRFDRFE_EVT1_GPI7_ONE                                       0x00000080U
#define LRFDRFE_EVT1_GPI7_ZERO                                      0x00000000U

// Field:     [6] GPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI6                                           0x00000040U
#define LRFDRFE_EVT1_GPI6_M                                         0x00000040U
#define LRFDRFE_EVT1_GPI6_S                                                  6U
#define LRFDRFE_EVT1_GPI6_ONE                                       0x00000040U
#define LRFDRFE_EVT1_GPI6_ZERO                                      0x00000000U

// Field:     [5] GPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI5                                           0x00000020U
#define LRFDRFE_EVT1_GPI5_M                                         0x00000020U
#define LRFDRFE_EVT1_GPI5_S                                                  5U
#define LRFDRFE_EVT1_GPI5_ONE                                       0x00000020U
#define LRFDRFE_EVT1_GPI5_ZERO                                      0x00000000U

// Field:     [4] GPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI4                                           0x00000010U
#define LRFDRFE_EVT1_GPI4_M                                         0x00000010U
#define LRFDRFE_EVT1_GPI4_S                                                  4U
#define LRFDRFE_EVT1_GPI4_ONE                                       0x00000010U
#define LRFDRFE_EVT1_GPI4_ZERO                                      0x00000000U

// Field:     [3] GPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI3                                           0x00000008U
#define LRFDRFE_EVT1_GPI3_M                                         0x00000008U
#define LRFDRFE_EVT1_GPI3_S                                                  3U
#define LRFDRFE_EVT1_GPI3_ONE                                       0x00000008U
#define LRFDRFE_EVT1_GPI3_ZERO                                      0x00000000U

// Field:     [2] GPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI2                                           0x00000004U
#define LRFDRFE_EVT1_GPI2_M                                         0x00000004U
#define LRFDRFE_EVT1_GPI2_S                                                  2U
#define LRFDRFE_EVT1_GPI2_ONE                                       0x00000004U
#define LRFDRFE_EVT1_GPI2_ZERO                                      0x00000000U

// Field:     [1] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI1                                           0x00000002U
#define LRFDRFE_EVT1_GPI1_M                                         0x00000002U
#define LRFDRFE_EVT1_GPI1_S                                                  1U
#define LRFDRFE_EVT1_GPI1_ONE                                       0x00000002U
#define LRFDRFE_EVT1_GPI1_ZERO                                      0x00000000U

// Field:     [0] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVT1_GPI0                                           0x00000001U
#define LRFDRFE_EVT1_GPI0_M                                         0x00000001U
#define LRFDRFE_EVT1_GPI0_S                                                  0U
#define LRFDRFE_EVT1_GPI0_ONE                                       0x00000001U
#define LRFDRFE_EVT1_GPI0_ZERO                                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVTMSK0
//
//*****************************************************************************
// Field:    [14] MAGNTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_MAGNTHR                                     0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_M                                   0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_S                                           14U
#define LRFDRFE_EVTMSK0_MAGNTHR_EN                                  0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_DIS                                 0x00000000U

// Field:    [13] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_S2RSTOP                                     0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_M                                   0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_S                                           13U
#define LRFDRFE_EVTMSK0_S2RSTOP_EN                                  0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_DIS                                 0x00000000U

// Field:    [12] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_SYSTCMP2                                    0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_M                                  0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_S                                          12U
#define LRFDRFE_EVTMSK0_SYSTCMP2_EN                                 0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_DIS                                0x00000000U

// Field:    [11] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_SYSTCMP1                                    0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_M                                  0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_S                                          11U
#define LRFDRFE_EVTMSK0_SYSTCMP1_EN                                 0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_DIS                                0x00000000U

// Field:    [10] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_SYSTCMP0                                    0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_M                                  0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_S                                          10U
#define LRFDRFE_EVTMSK0_SYSTCMP0_EN                                 0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_DIS                                0x00000000U

// Field:     [9] PBERFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_PBERFEDAT                                   0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_M                                 0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_S                                          9U
#define LRFDRFE_EVTMSK0_PBERFEDAT_EN                                0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_DIS                               0x00000000U

// Field:     [8] MDMRFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_MDMRFEDAT                                   0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_M                                 0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_S                                          8U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_EN                                0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_DIS                               0x00000000U

// Field:     [7] DLO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_DLO                                         0x00000080U
#define LRFDRFE_EVTMSK0_DLO_M                                       0x00000080U
#define LRFDRFE_EVTMSK0_DLO_S                                                7U
#define LRFDRFE_EVTMSK0_DLO_EN                                      0x00000080U
#define LRFDRFE_EVTMSK0_DLO_DIS                                     0x00000000U

// Field:     [6] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_PBECMD                                      0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_M                                    0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_S                                             6U
#define LRFDRFE_EVTMSK0_PBECMD_EN                                   0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_DIS                                  0x00000000U

// Field:     [5] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_COUNTER                                     0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_M                                   0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_S                                            5U
#define LRFDRFE_EVTMSK0_COUNTER_EN                                  0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_DIS                                 0x00000000U

// Field:     [4] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_MDMCMD                                      0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_M                                    0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_S                                             4U
#define LRFDRFE_EVTMSK0_MDMCMD_EN                                   0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_DIS                                  0x00000000U

// Field:     [3] ACC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_ACC1                                        0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_M                                      0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_S                                               3U
#define LRFDRFE_EVTMSK0_ACC1_EN                                     0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_DIS                                    0x00000000U

// Field:     [2] ACC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_ACC0                                        0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_M                                      0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_S                                               2U
#define LRFDRFE_EVTMSK0_ACC0_EN                                     0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_DIS                                    0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_TIMER                                       0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_M                                     0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_S                                              1U
#define LRFDRFE_EVTMSK0_TIMER_EN                                    0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_DIS                                   0x00000000U

// Field:     [0] RFEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK0_RFEAPI                                      0x00000001U
#define LRFDRFE_EVTMSK0_RFEAPI_M                                    0x00000001U
#define LRFDRFE_EVTMSK0_RFEAPI_S                                             0U
#define LRFDRFE_EVTMSK0_RFEAPI_EN                                   0x00000001U
#define LRFDRFE_EVTMSK0_RFEAPI_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVTMSK1
//
//*****************************************************************************
// Field:    [13] PREREFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_PREREFCLK                                   0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_M                                 0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_S                                         13U
#define LRFDRFE_EVTMSK1_PREREFCLK_EN                                0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_DIS                               0x00000000U

// Field:    [12] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_REFCLK                                      0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_M                                    0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_S                                            12U
#define LRFDRFE_EVTMSK1_REFCLK_EN                                   0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_DIS                                  0x00000000U

// Field:    [11] FBLWTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_FBLWTHR                                     0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_M                                   0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_S                                           11U
#define LRFDRFE_EVTMSK1_FBLWTHR_EN                                  0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_DIS                                 0x00000000U

// Field:    [10] FABVTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_FABVTHR                                     0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_M                                   0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_S                                           10U
#define LRFDRFE_EVTMSK1_FABVTHR_EN                                  0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_DIS                                 0x00000000U

// Field:     [9] LOCK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_LOCK                                        0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_M                                      0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_S                                               9U
#define LRFDRFE_EVTMSK1_LOCK_EN                                     0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_DIS                                    0x00000000U

// Field:     [8] LOL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_LOL                                         0x00000100U
#define LRFDRFE_EVTMSK1_LOL_M                                       0x00000100U
#define LRFDRFE_EVTMSK1_LOL_S                                                8U
#define LRFDRFE_EVTMSK1_LOL_EN                                      0x00000100U
#define LRFDRFE_EVTMSK1_LOL_DIS                                     0x00000000U

// Field:     [7] GPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI7                                        0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_M                                      0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_S                                               7U
#define LRFDRFE_EVTMSK1_GPI7_EN                                     0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_DIS                                    0x00000000U

// Field:     [6] GPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI6                                        0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_M                                      0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_S                                               6U
#define LRFDRFE_EVTMSK1_GPI6_EN                                     0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_DIS                                    0x00000000U

// Field:     [5] GPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI5                                        0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_M                                      0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_S                                               5U
#define LRFDRFE_EVTMSK1_GPI5_EN                                     0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_DIS                                    0x00000000U

// Field:     [4] GPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI4                                        0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_M                                      0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_S                                               4U
#define LRFDRFE_EVTMSK1_GPI4_EN                                     0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_DIS                                    0x00000000U

// Field:     [3] GPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI3                                        0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_M                                      0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_S                                               3U
#define LRFDRFE_EVTMSK1_GPI3_EN                                     0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_DIS                                    0x00000000U

// Field:     [2] GPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI2                                        0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_M                                      0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_S                                               2U
#define LRFDRFE_EVTMSK1_GPI2_EN                                     0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_DIS                                    0x00000000U

// Field:     [1] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI1                                        0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_M                                      0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_S                                               1U
#define LRFDRFE_EVTMSK1_GPI1_EN                                     0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_DIS                                    0x00000000U

// Field:     [0] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTMSK1_GPI0                                        0x00000001U
#define LRFDRFE_EVTMSK1_GPI0_M                                      0x00000001U
#define LRFDRFE_EVTMSK1_GPI0_S                                               0U
#define LRFDRFE_EVTMSK1_GPI0_EN                                     0x00000001U
#define LRFDRFE_EVTMSK1_GPI0_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVTCLR0
//
//*****************************************************************************
// Field:    [14] MAGNTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_MAGNTHR                                     0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_M                                   0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_S                                           14U
#define LRFDRFE_EVTCLR0_MAGNTHR_ONE                                 0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_ZERO                                0x00000000U

// Field:    [13] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_S2RSTOP                                     0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_M                                   0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_S                                           13U
#define LRFDRFE_EVTCLR0_S2RSTOP_ONE                                 0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_ZERO                                0x00000000U

// Field:    [12] SYSTCMP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_SYSTCMP2                                    0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_M                                  0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_S                                          12U
#define LRFDRFE_EVTCLR0_SYSTCMP2_ONE                                0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_ZERO                               0x00000000U

// Field:    [11] SYSTCMP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_SYSTCMP1                                    0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_M                                  0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_S                                          11U
#define LRFDRFE_EVTCLR0_SYSTCMP1_ONE                                0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_ZERO                               0x00000000U

// Field:    [10] SYSTCMP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_SYSTCMP0                                    0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_M                                  0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_S                                          10U
#define LRFDRFE_EVTCLR0_SYSTCMP0_ONE                                0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_ZERO                               0x00000000U

// Field:     [9] PBERFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_PBERFEDAT                                   0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_M                                 0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_S                                          9U
#define LRFDRFE_EVTCLR0_PBERFEDAT_ONE                               0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_ZERO                              0x00000000U

// Field:     [8] MDMRFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_MDMRFEDAT                                   0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_M                                 0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_S                                          8U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_ONE                               0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_ZERO                              0x00000000U

// Field:     [7] DLO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_DLO                                         0x00000080U
#define LRFDRFE_EVTCLR0_DLO_M                                       0x00000080U
#define LRFDRFE_EVTCLR0_DLO_S                                                7U
#define LRFDRFE_EVTCLR0_DLO_ONE                                     0x00000080U
#define LRFDRFE_EVTCLR0_DLO_ZERO                                    0x00000000U

// Field:     [6] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_PBECMD                                      0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_M                                    0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_S                                             6U
#define LRFDRFE_EVTCLR0_PBECMD_ONE                                  0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_ZERO                                 0x00000000U

// Field:     [5] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_COUNTER                                     0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_M                                   0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_S                                            5U
#define LRFDRFE_EVTCLR0_COUNTER_ONE                                 0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_ZERO                                0x00000000U

// Field:     [4] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_MDMCMD                                      0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_M                                    0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_S                                             4U
#define LRFDRFE_EVTCLR0_MDMCMD_ONE                                  0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_ZERO                                 0x00000000U

// Field:     [3] ACC1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_ACC1                                        0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_M                                      0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_S                                               3U
#define LRFDRFE_EVTCLR0_ACC1_ONE                                    0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_ZERO                                   0x00000000U

// Field:     [2] ACC0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_ACC0                                        0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_M                                      0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_S                                               2U
#define LRFDRFE_EVTCLR0_ACC0_ONE                                    0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_ZERO                                   0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_TIMER                                       0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_M                                     0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_S                                              1U
#define LRFDRFE_EVTCLR0_TIMER_ONE                                   0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_ZERO                                  0x00000000U

// Field:     [0] RFEAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR0_RFEAPI                                      0x00000001U
#define LRFDRFE_EVTCLR0_RFEAPI_M                                    0x00000001U
#define LRFDRFE_EVTCLR0_RFEAPI_S                                             0U
#define LRFDRFE_EVTCLR0_RFEAPI_ONE                                  0x00000001U
#define LRFDRFE_EVTCLR0_RFEAPI_ZERO                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_EVTCLR1
//
//*****************************************************************************
// Field:    [13] PREREFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_PREREFCLK                                   0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_M                                 0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_S                                         13U
#define LRFDRFE_EVTCLR1_PREREFCLK_ONE                               0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_ZERO                              0x00000000U

// Field:    [12] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_REFCLK                                      0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_M                                    0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_S                                            12U
#define LRFDRFE_EVTCLR1_REFCLK_ONE                                  0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_ZERO                                 0x00000000U

// Field:    [11] FBLWTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_FBLWTHR                                     0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_M                                   0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_S                                           11U
#define LRFDRFE_EVTCLR1_FBLWTHR_ONE                                 0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_ZERO                                0x00000000U

// Field:    [10] FABVTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_FABVTHR                                     0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_M                                   0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_S                                           10U
#define LRFDRFE_EVTCLR1_FABVTHR_ONE                                 0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_ZERO                                0x00000000U

// Field:     [9] LOCK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_LOCK                                        0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_M                                      0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_S                                               9U
#define LRFDRFE_EVTCLR1_LOCK_ONE                                    0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_ZERO                                   0x00000000U

// Field:     [8] LOL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_LOL                                         0x00000100U
#define LRFDRFE_EVTCLR1_LOL_M                                       0x00000100U
#define LRFDRFE_EVTCLR1_LOL_S                                                8U
#define LRFDRFE_EVTCLR1_LOL_ONE                                     0x00000100U
#define LRFDRFE_EVTCLR1_LOL_ZERO                                    0x00000000U

// Field:     [7] GPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI7                                        0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_M                                      0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_S                                               7U
#define LRFDRFE_EVTCLR1_GPI7_ONE                                    0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_ZERO                                   0x00000000U

// Field:     [6] GPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI6                                        0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_M                                      0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_S                                               6U
#define LRFDRFE_EVTCLR1_GPI6_ONE                                    0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_ZERO                                   0x00000000U

// Field:     [5] GPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI5                                        0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_M                                      0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_S                                               5U
#define LRFDRFE_EVTCLR1_GPI5_ONE                                    0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_ZERO                                   0x00000000U

// Field:     [4] GPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI4                                        0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_M                                      0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_S                                               4U
#define LRFDRFE_EVTCLR1_GPI4_ONE                                    0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_ZERO                                   0x00000000U

// Field:     [3] GPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI3                                        0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_M                                      0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_S                                               3U
#define LRFDRFE_EVTCLR1_GPI3_ONE                                    0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_ZERO                                   0x00000000U

// Field:     [2] GPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI2                                        0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_M                                      0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_S                                               2U
#define LRFDRFE_EVTCLR1_GPI2_ONE                                    0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_ZERO                                   0x00000000U

// Field:     [1] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI1                                        0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_M                                      0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_S                                               1U
#define LRFDRFE_EVTCLR1_GPI1_ONE                                    0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_ZERO                                   0x00000000U

// Field:     [0] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_EVTCLR1_GPI0                                        0x00000001U
#define LRFDRFE_EVTCLR1_GPI0_M                                      0x00000001U
#define LRFDRFE_EVTCLR1_GPI0_S                                               0U
#define LRFDRFE_EVTCLR1_GPI0_ONE                                    0x00000001U
#define LRFDRFE_EVTCLR1_GPI0_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_HFXTSTAT
//
//*****************************************************************************
// Field:     [0] STAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// QUAL                     Internal. Only to be used through TI provided API.
// NONQUAL                  Internal. Only to be used through TI provided API.
#define LRFDRFE_HFXTSTAT_STAT                                       0x00000001U
#define LRFDRFE_HFXTSTAT_STAT_M                                     0x00000001U
#define LRFDRFE_HFXTSTAT_STAT_S                                              0U
#define LRFDRFE_HFXTSTAT_STAT_QUAL                                  0x00000001U
#define LRFDRFE_HFXTSTAT_STAT_NONQUAL                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RFSTATE
//
//*****************************************************************************
// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RX                       Internal. Only to be used through TI provided API.
// TX                       Internal. Only to be used through TI provided API.
// SYNTH                    Internal. Only to be used through TI provided API.
// IDLE                     Internal. Only to be used through TI provided API.
#define LRFDRFE_RFSTATE_VAL_W                                                4U
#define LRFDRFE_RFSTATE_VAL_M                                       0x0000000FU
#define LRFDRFE_RFSTATE_VAL_S                                                0U
#define LRFDRFE_RFSTATE_VAL_RX                                      0x00000003U
#define LRFDRFE_RFSTATE_VAL_TX                                      0x00000002U
#define LRFDRFE_RFSTATE_VAL_SYNTH                                   0x00000001U
#define LRFDRFE_RFSTATE_VAL_IDLE                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_API
//
//*****************************************************************************
// Field:   [7:4] PROTOCOLID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_API_PROTOCOLID_W                                             4U
#define LRFDRFE_API_PROTOCOLID_M                                    0x000000F0U
#define LRFDRFE_API_PROTOCOLID_S                                             4U
#define LRFDRFE_API_PROTOCOLID_ALLONES                              0x000000F0U
#define LRFDRFE_API_PROTOCOLID_ALLZEROS                             0x00000000U

// Field:   [3:0] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_API_RFECMD_W                                                 4U
#define LRFDRFE_API_RFECMD_M                                        0x0000000FU
#define LRFDRFE_API_RFECMD_S                                                 0U
#define LRFDRFE_API_RFECMD_ALLONES                                  0x0000000FU
#define LRFDRFE_API_RFECMD_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CMDPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CMDPAR0_VAL_W                                               16U
#define LRFDRFE_CMDPAR0_VAL_M                                       0x0000FFFFU
#define LRFDRFE_CMDPAR0_VAL_S                                                0U
#define LRFDRFE_CMDPAR0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_CMDPAR0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CMDPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CMDPAR1_VAL_W                                               16U
#define LRFDRFE_CMDPAR1_VAL_M                                       0x0000FFFFU
#define LRFDRFE_CMDPAR1_VAL_S                                                0U
#define LRFDRFE_CMDPAR1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_CMDPAR1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MSGBOX
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MSGBOX_VAL_W                                                 8U
#define LRFDRFE_MSGBOX_VAL_M                                        0x000000FFU
#define LRFDRFE_MSGBOX_VAL_S                                                 0U
#define LRFDRFE_MSGBOX_VAL_ALLONES                                  0x000000FFU
#define LRFDRFE_MSGBOX_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MCEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MCEDATOUT0_VAL_W                                            16U
#define LRFDRFE_MCEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDRFE_MCEDATOUT0_VAL_S                                             0U
#define LRFDRFE_MCEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDRFE_MCEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MCEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MCEDATIN0_VAL_W                                             16U
#define LRFDRFE_MCEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDRFE_MCEDATIN0_VAL_S                                              0U
#define LRFDRFE_MCEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDRFE_MCEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MCECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MCECMDOUT_VAL_W                                              4U
#define LRFDRFE_MCECMDOUT_VAL_M                                     0x0000000FU
#define LRFDRFE_MCECMDOUT_VAL_S                                              0U
#define LRFDRFE_MCECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDRFE_MCECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MCECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MCECMDIN_VAL_W                                               4U
#define LRFDRFE_MCECMDIN_VAL_M                                      0x0000000FU
#define LRFDRFE_MCECMDIN_VAL_S                                               0U
#define LRFDRFE_MCECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDRFE_MCECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PBEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PBEDATOUT0_VAL_W                                            16U
#define LRFDRFE_PBEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDRFE_PBEDATOUT0_VAL_S                                             0U
#define LRFDRFE_PBEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDRFE_PBEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PBEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PBEDATIN0_VAL_W                                             16U
#define LRFDRFE_PBEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDRFE_PBEDATIN0_VAL_S                                              0U
#define LRFDRFE_PBEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDRFE_PBEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PBECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PBECMDOUT_VAL_W                                              4U
#define LRFDRFE_PBECMDOUT_VAL_M                                     0x0000000FU
#define LRFDRFE_PBECMDOUT_VAL_S                                              0U
#define LRFDRFE_PBECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDRFE_PBECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PBECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PBECMDIN_VAL_W                                               4U
#define LRFDRFE_PBECMDIN_VAL_M                                      0x0000000FU
#define LRFDRFE_PBECMDIN_VAL_S                                               0U
#define LRFDRFE_PBECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDRFE_PBECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_STRB
//
//*****************************************************************************
// Field:     [7] S2RTRG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_S2RTRG                                         0x00000080U
#define LRFDRFE_STRB_S2RTRG_M                                       0x00000080U
#define LRFDRFE_STRB_S2RTRG_S                                                7U
#define LRFDRFE_STRB_S2RTRG_ONE                                     0x00000080U
#define LRFDRFE_STRB_S2RTRG_ZERO                                    0x00000000U

// Field:     [6] DMATRG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_DMATRG                                         0x00000040U
#define LRFDRFE_STRB_DMATRG_M                                       0x00000040U
#define LRFDRFE_STRB_DMATRG_S                                                6U
#define LRFDRFE_STRB_DMATRG_ONE                                     0x00000040U
#define LRFDRFE_STRB_DMATRG_ZERO                                    0x00000000U

// Field:     [5] SYSTCPT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_SYSTCPT2                                       0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_M                                     0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_S                                              5U
#define LRFDRFE_STRB_SYSTCPT2_ONE                                   0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_ZERO                                  0x00000000U

// Field:     [4] SYSTCPT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_SYSTCPT1                                       0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_M                                     0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_S                                              4U
#define LRFDRFE_STRB_SYSTCPT1_ONE                                   0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_ZERO                                  0x00000000U

// Field:     [3] SYSTCPT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_SYSTCPT0                                       0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_M                                     0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_S                                              3U
#define LRFDRFE_STRB_SYSTCPT0_ONE                                   0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_ZERO                                  0x00000000U

// Field:     [2] EVT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_EVT1                                           0x00000004U
#define LRFDRFE_STRB_EVT1_M                                         0x00000004U
#define LRFDRFE_STRB_EVT1_S                                                  2U
#define LRFDRFE_STRB_EVT1_ONE                                       0x00000004U
#define LRFDRFE_STRB_EVT1_ZERO                                      0x00000000U

// Field:     [1] EVT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_EVT0                                           0x00000002U
#define LRFDRFE_STRB_EVT0_M                                         0x00000002U
#define LRFDRFE_STRB_EVT0_S                                                  1U
#define LRFDRFE_STRB_EVT0_ONE                                       0x00000002U
#define LRFDRFE_STRB_EVT0_ZERO                                      0x00000000U

// Field:     [0] CMDDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// YES                      Internal. Only to be used through TI provided API.
// NO                       Internal. Only to be used through TI provided API.
#define LRFDRFE_STRB_CMDDONE                                        0x00000001U
#define LRFDRFE_STRB_CMDDONE_M                                      0x00000001U
#define LRFDRFE_STRB_CMDDONE_S                                               0U
#define LRFDRFE_STRB_CMDDONE_YES                                    0x00000001U
#define LRFDRFE_STRB_CMDDONE_NO                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNTHRCFG
//
//*****************************************************************************
// Field:     [1] SEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAGNACC1                 Internal. Only to be used through TI provided API.
// MAGNACC0                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNTHRCFG_SEL                                      0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_M                                    0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_S                                             1U
#define LRFDRFE_MAGNTHRCFG_SEL_MAGNACC1                             0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_MAGNACC0                             0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNTHRCFG_CTL                                      0x00000001U
#define LRFDRFE_MAGNTHRCFG_CTL_M                                    0x00000001U
#define LRFDRFE_MAGNTHRCFG_CTL_S                                             0U
#define LRFDRFE_MAGNTHRCFG_CTL_EN                                   0x00000001U
#define LRFDRFE_MAGNTHRCFG_CTL_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNTHR
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNTHR_VAL_W                                                8U
#define LRFDRFE_MAGNTHR_VAL_M                                       0x000000FFU
#define LRFDRFE_MAGNTHR_VAL_S                                                0U
#define LRFDRFE_MAGNTHR_VAL_ALLONES                                 0x000000FFU
#define LRFDRFE_MAGNTHR_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RSSIOFFSET
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_RSSIOFFSET_VAL_W                                             8U
#define LRFDRFE_RSSIOFFSET_VAL_M                                    0x000000FFU
#define LRFDRFE_RSSIOFFSET_VAL_S                                             0U
#define LRFDRFE_RSSIOFFSET_VAL_ALLONES                              0x000000FFU
#define LRFDRFE_RSSIOFFSET_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_GAINCTL
//
//*****************************************************************************
// Field:   [3:2] BDE2DVGA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GAIN8                    Internal. Only to be used through TI provided API.
// GAIN4                    Internal. Only to be used through TI provided API.
// GAIN2                    Internal. Only to be used through TI provided API.
// GAIN1                    Internal. Only to be used through TI provided API.
#define LRFDRFE_GAINCTL_BDE2DVGA_W                                           2U
#define LRFDRFE_GAINCTL_BDE2DVGA_M                                  0x0000000CU
#define LRFDRFE_GAINCTL_BDE2DVGA_S                                           2U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN8                              0x0000000CU
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN4                              0x00000008U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN2                              0x00000004U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN1                              0x00000000U

// Field:   [1:0] BDE1DVGA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GAIN8                    Internal. Only to be used through TI provided API.
// GAIN4                    Internal. Only to be used through TI provided API.
// GAIN2                    Internal. Only to be used through TI provided API.
// GAIN1                    Internal. Only to be used through TI provided API.
#define LRFDRFE_GAINCTL_BDE1DVGA_W                                           2U
#define LRFDRFE_GAINCTL_BDE1DVGA_M                                  0x00000003U
#define LRFDRFE_GAINCTL_BDE1DVGA_S                                           0U
#define LRFDRFE_GAINCTL_BDE1DVGA_GAIN8                              0x00000003U
#define LRFDRFE_GAINCTL_BDE1DVGA_GAIN4                              0x00000002U
#define LRFDRFE_GAINCTL_BDE1DVGA_GAIN2                              0x00000001U
#define LRFDRFE_GAINCTL_BDE1DVGA_GAIN1                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNCTL0
//
//*****************************************************************************
// Field:    [12] PERMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PERIODIC                 Internal. Only to be used through TI provided API.
// ONESHOT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL0_PERMODE                                    0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_M                                  0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_S                                          12U
#define LRFDRFE_MAGNCTL0_PERMODE_PERIODIC                           0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_ONESHOT                            0x00000000U

// Field:  [11:8] SCL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV256                   Internal. Only to be used through TI provided API.
// DIV128                   Internal. Only to be used through TI provided API.
// DIV64                    Internal. Only to be used through TI provided API.
// DIV32                    Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
// DIV8                     Internal. Only to be used through TI provided API.
// DIV4                     Internal. Only to be used through TI provided API.
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL0_SCL_W                                               4U
#define LRFDRFE_MAGNCTL0_SCL_M                                      0x00000F00U
#define LRFDRFE_MAGNCTL0_SCL_S                                               8U
#define LRFDRFE_MAGNCTL0_SCL_DIV256                                 0x00000800U
#define LRFDRFE_MAGNCTL0_SCL_DIV128                                 0x00000700U
#define LRFDRFE_MAGNCTL0_SCL_DIV64                                  0x00000600U
#define LRFDRFE_MAGNCTL0_SCL_DIV32                                  0x00000500U
#define LRFDRFE_MAGNCTL0_SCL_DIV16                                  0x00000400U
#define LRFDRFE_MAGNCTL0_SCL_DIV8                                   0x00000300U
#define LRFDRFE_MAGNCTL0_SCL_DIV4                                   0x00000200U
#define LRFDRFE_MAGNCTL0_SCL_DIV2                                   0x00000100U
#define LRFDRFE_MAGNCTL0_SCL_DIV1                                   0x00000000U

// Field:   [7:0] PER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL0_PER_W                                               8U
#define LRFDRFE_MAGNCTL0_PER_M                                      0x000000FFU
#define LRFDRFE_MAGNCTL0_PER_S                                               0U
#define LRFDRFE_MAGNCTL0_PER_ALLONES                                0x000000FFU
#define LRFDRFE_MAGNCTL0_PER_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNCTL1
//
//*****************************************************************************
// Field:    [12] PERMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PERIODIC                 Internal. Only to be used through TI provided API.
// ONESHOT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL1_PERMODE                                    0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_M                                  0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_S                                          12U
#define LRFDRFE_MAGNCTL1_PERMODE_PERIODIC                           0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_ONESHOT                            0x00000000U

// Field:  [11:8] SCL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV256                   Internal. Only to be used through TI provided API.
// DIV128                   Internal. Only to be used through TI provided API.
// DIV64                    Internal. Only to be used through TI provided API.
// DIV32                    Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
// DIV8                     Internal. Only to be used through TI provided API.
// DIV4                     Internal. Only to be used through TI provided API.
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL1_SCL_W                                               4U
#define LRFDRFE_MAGNCTL1_SCL_M                                      0x00000F00U
#define LRFDRFE_MAGNCTL1_SCL_S                                               8U
#define LRFDRFE_MAGNCTL1_SCL_DIV256                                 0x00000800U
#define LRFDRFE_MAGNCTL1_SCL_DIV128                                 0x00000700U
#define LRFDRFE_MAGNCTL1_SCL_DIV64                                  0x00000600U
#define LRFDRFE_MAGNCTL1_SCL_DIV32                                  0x00000500U
#define LRFDRFE_MAGNCTL1_SCL_DIV16                                  0x00000400U
#define LRFDRFE_MAGNCTL1_SCL_DIV8                                   0x00000300U
#define LRFDRFE_MAGNCTL1_SCL_DIV4                                   0x00000200U
#define LRFDRFE_MAGNCTL1_SCL_DIV2                                   0x00000100U
#define LRFDRFE_MAGNCTL1_SCL_DIV1                                   0x00000000U

// Field:   [7:0] PER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNCTL1_PER_W                                               8U
#define LRFDRFE_MAGNCTL1_PER_M                                      0x000000FFU
#define LRFDRFE_MAGNCTL1_PER_S                                               0U
#define LRFDRFE_MAGNCTL1_PER_ALLONES                                0x000000FFU
#define LRFDRFE_MAGNCTL1_PER_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE0_VAL_W                                                16U
#define LRFDRFE_SPARE0_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE0_VAL_S                                                 0U
#define LRFDRFE_SPARE0_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE0_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE1
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE1_VAL_W                                                16U
#define LRFDRFE_SPARE1_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE1_VAL_S                                                 0U
#define LRFDRFE_SPARE1_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE1_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE2
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE2_VAL_W                                                16U
#define LRFDRFE_SPARE2_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE2_VAL_S                                                 0U
#define LRFDRFE_SPARE2_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE2_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE3
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE3_VAL_W                                                16U
#define LRFDRFE_SPARE3_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE3_VAL_S                                                 0U
#define LRFDRFE_SPARE3_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE3_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE4
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE4_VAL_W                                                16U
#define LRFDRFE_SPARE4_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE4_VAL_S                                                 0U
#define LRFDRFE_SPARE4_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE4_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_SPARE5
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_SPARE5_VAL_W                                                16U
#define LRFDRFE_SPARE5_VAL_M                                        0x0000FFFFU
#define LRFDRFE_SPARE5_VAL_S                                                 0U
#define LRFDRFE_SPARE5_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_SPARE5_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_LNA
//
//*****************************************************************************
// Field:  [15:8] SPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_LNA_SPARE_W                                                  8U
#define LRFDRFE_LNA_SPARE_M                                         0x0000FF00U
#define LRFDRFE_LNA_SPARE_S                                                  8U
#define LRFDRFE_LNA_SPARE_EN                                        0x00000100U
#define LRFDRFE_LNA_SPARE_DIS                                       0x00000000U

// Field:   [7:4] TRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_LNA_TRIM_W                                                   4U
#define LRFDRFE_LNA_TRIM_M                                          0x000000F0U
#define LRFDRFE_LNA_TRIM_S                                                   4U
#define LRFDRFE_LNA_TRIM_ONES                                       0x000000F0U
#define LRFDRFE_LNA_TRIM_ZEROS                                      0x00000000U

// Field:     [3] BIAS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// INT                      Internal. Only to be used through TI provided API.
// BGAP                     Internal. Only to be used through TI provided API.
#define LRFDRFE_LNA_BIAS                                            0x00000008U
#define LRFDRFE_LNA_BIAS_M                                          0x00000008U
#define LRFDRFE_LNA_BIAS_S                                                   3U
#define LRFDRFE_LNA_BIAS_INT                                        0x00000008U
#define LRFDRFE_LNA_BIAS_BGAP                                       0x00000000U

// Field:   [2:1] IB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_LNA_IB_W                                                     2U
#define LRFDRFE_LNA_IB_M                                            0x00000006U
#define LRFDRFE_LNA_IB_S                                                     1U
#define LRFDRFE_LNA_IB_MAX                                          0x00000006U
#define LRFDRFE_LNA_IB_MIN                                          0x00000000U

// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDRFE_LNA_EN                                              0x00000001U
#define LRFDRFE_LNA_EN_M                                            0x00000001U
#define LRFDRFE_LNA_EN_S                                                     0U
#define LRFDRFE_LNA_EN_ON                                           0x00000001U
#define LRFDRFE_LNA_EN_OFF                                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFAMPRFLDO
//
//*****************************************************************************
// Field:  [15:9] TRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BYPASS                   Internal. Only to be used through TI provided API.
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFAMPRFLDO_TRIM_W                                            7U
#define LRFDRFE_IFAMPRFLDO_TRIM_M                                   0x0000FE00U
#define LRFDRFE_IFAMPRFLDO_TRIM_S                                            9U
#define LRFDRFE_IFAMPRFLDO_TRIM_BYPASS                              0x0000FE00U
#define LRFDRFE_IFAMPRFLDO_TRIM_MAX                                 0x0000FC00U
#define LRFDRFE_IFAMPRFLDO_TRIM_MIN                                 0x00000000U

// Field:     [8] EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFAMPRFLDO_EN                                       0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_M                                     0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_S                                              8U
#define LRFDRFE_IFAMPRFLDO_EN_EN                                    0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_DIS                                   0x00000000U

// Field:   [7:4] AAFCAP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFAMPRFLDO_AAFCAP_W                                          4U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_M                                 0x000000F0U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_S                                          4U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_MAX                               0x000000F0U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_MIN                               0x00000000U

// Field:   [3:1] IFAMPIB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_W                                         3U
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_M                                0x0000000EU
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_S                                         1U
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_MAX                              0x0000000EU
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_MIN                              0x00000000U

// Field:     [0] IFAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFAMPRFLDO_IFAMP                                    0x00000001U
#define LRFDRFE_IFAMPRFLDO_IFAMP_M                                  0x00000001U
#define LRFDRFE_IFAMPRFLDO_IFAMP_S                                           0U
#define LRFDRFE_IFAMPRFLDO_IFAMP_EN                                 0x00000001U
#define LRFDRFE_IFAMPRFLDO_IFAMP_DIS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PA0
//
//*****************************************************************************
// Field:    [15] SPARE15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_PA0_SPARE15                                         0x00008000U
#define LRFDRFE_PA0_SPARE15_M                                       0x00008000U
#define LRFDRFE_PA0_SPARE15_S                                               15U
#define LRFDRFE_PA0_SPARE15_ONE                                     0x00008000U
#define LRFDRFE_PA0_SPARE15_ZERO                                    0x00000000U

// Field:    [14] MODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HIGH                     Internal. Only to be used through TI provided API.
// LOW                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA0_MODE                                            0x00004000U
#define LRFDRFE_PA0_MODE_M                                          0x00004000U
#define LRFDRFE_PA0_MODE_S                                                  14U
#define LRFDRFE_PA0_MODE_HIGH                                       0x00004000U
#define LRFDRFE_PA0_MODE_LOW                                        0x00000000U

// Field: [13:11] GAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA0_GAIN_W                                                   3U
#define LRFDRFE_PA0_GAIN_M                                          0x00003800U
#define LRFDRFE_PA0_GAIN_S                                                  11U
#define LRFDRFE_PA0_GAIN_MAX                                        0x00003800U
#define LRFDRFE_PA0_GAIN_MIN                                        0x00000000U

// Field:  [10:5] IB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA0_IB_W                                                     6U
#define LRFDRFE_PA0_IB_M                                            0x000007E0U
#define LRFDRFE_PA0_IB_S                                                     5U
#define LRFDRFE_PA0_IB_MAX                                          0x000007E0U
#define LRFDRFE_PA0_IB_MIN                                          0x00000000U

// Field:   [4:0] TRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA0_TRIM_W                                                   5U
#define LRFDRFE_PA0_TRIM_M                                          0x0000001FU
#define LRFDRFE_PA0_TRIM_S                                                   0U
#define LRFDRFE_PA0_TRIM_MAX                                        0x0000001FU
#define LRFDRFE_PA0_TRIM_MIN                                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PA1
//
//*****************************************************************************
// Field:  [15:7] SPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_SPARE_W                                                  9U
#define LRFDRFE_PA1_SPARE_M                                         0x0000FF80U
#define LRFDRFE_PA1_SPARE_S                                                  7U
#define LRFDRFE_PA1_SPARE_MAX                                       0x00000180U
#define LRFDRFE_PA1_SPARE_MIN                                       0x00000000U

// Field:     [6] MIXATST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_MIXATST                                         0x00000040U
#define LRFDRFE_PA1_MIXATST_M                                       0x00000040U
#define LRFDRFE_PA1_MIXATST_S                                                6U
#define LRFDRFE_PA1_MIXATST_EN                                      0x00000040U
#define LRFDRFE_PA1_MIXATST_DIS                                     0x00000000U

// Field:     [5] LDOITST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_LDOITST                                         0x00000020U
#define LRFDRFE_PA1_LDOITST_M                                       0x00000020U
#define LRFDRFE_PA1_LDOITST_S                                                5U
#define LRFDRFE_PA1_LDOITST_EN                                      0x00000020U
#define LRFDRFE_PA1_LDOITST_DIS                                     0x00000000U

// Field:     [4] LDOATST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_LDOATST                                         0x00000010U
#define LRFDRFE_PA1_LDOATST_M                                       0x00000010U
#define LRFDRFE_PA1_LDOATST_S                                                4U
#define LRFDRFE_PA1_LDOATST_EN                                      0x00000010U
#define LRFDRFE_PA1_LDOATST_DIS                                     0x00000000U

// Field:   [3:2] RC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_RC_W                                                     2U
#define LRFDRFE_PA1_RC_M                                            0x0000000CU
#define LRFDRFE_PA1_RC_S                                                     2U
#define LRFDRFE_PA1_RC_MAX                                          0x0000000CU
#define LRFDRFE_PA1_RC_MIN                                          0x00000000U

// Field:     [1] RAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// UP                       Internal. Only to be used through TI provided API.
// DOWN                     Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_RAMP                                            0x00000002U
#define LRFDRFE_PA1_RAMP_M                                          0x00000002U
#define LRFDRFE_PA1_RAMP_S                                                   1U
#define LRFDRFE_PA1_RAMP_UP                                         0x00000002U
#define LRFDRFE_PA1_RAMP_DOWN                                       0x00000000U

// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_PA1_EN                                              0x00000001U
#define LRFDRFE_PA1_EN_M                                            0x00000001U
#define LRFDRFE_PA1_EN_S                                                     0U
#define LRFDRFE_PA1_EN_EN                                           0x00000001U
#define LRFDRFE_PA1_EN_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_ULNA
//
//*****************************************************************************
// Field:  [15:0] SPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_ULNA_SPARE_W                                                16U
#define LRFDRFE_ULNA_SPARE_M                                        0x0000FFFFU
#define LRFDRFE_ULNA_SPARE_S                                                 0U
#define LRFDRFE_ULNA_SPARE_ALLONES                                  0x0000FFFFU
#define LRFDRFE_ULNA_SPARE_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADC0
//
//*****************************************************************************
// Field:    [15] EXTCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_EXTCLK                                       0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_M                                     0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_S                                             15U
#define LRFDRFE_IFADC0_EXTCLK_EN                                    0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_DIS                                   0x00000000U

// Field: [14:12] DITHERTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_DITHERTRIM_W                                          3U
#define LRFDRFE_IFADC0_DITHERTRIM_M                                 0x00007000U
#define LRFDRFE_IFADC0_DITHERTRIM_S                                         12U
#define LRFDRFE_IFADC0_DITHERTRIM_ONES                              0x00007000U
#define LRFDRFE_IFADC0_DITHERTRIM_ZEROS                             0x00000000U

// Field: [11:10] DITHEREN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ENG                      Internal. Only to be used through TI provided API.
// ENSD                     Internal. Only to be used through TI provided API.
// ENS                      Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_DITHEREN_W                                            2U
#define LRFDRFE_IFADC0_DITHEREN_M                                   0x00000C00U
#define LRFDRFE_IFADC0_DITHEREN_S                                           10U
#define LRFDRFE_IFADC0_DITHEREN_ENG                                 0x00000C00U
#define LRFDRFE_IFADC0_DITHEREN_ENSD                                0x00000800U
#define LRFDRFE_IFADC0_DITHEREN_ENS                                 0x00000400U
#define LRFDRFE_IFADC0_DITHEREN_DIS                                 0x00000000U

// Field:     [9] ADCIEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_ADCIEN                                       0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_M                                     0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_S                                              9U
#define LRFDRFE_IFADC0_ADCIEN_EN                                    0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_DIS                                   0x00000000U

// Field:     [8] ADCQEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_ADCQEN                                       0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_M                                     0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_S                                              8U
#define LRFDRFE_IFADC0_ADCQEN_EN                                    0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_DIS                                   0x00000000U

// Field:   [7:4] INT2ADJ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_INT2ADJ_W                                             4U
#define LRFDRFE_IFADC0_INT2ADJ_M                                    0x000000F0U
#define LRFDRFE_IFADC0_INT2ADJ_S                                             4U
#define LRFDRFE_IFADC0_INT2ADJ_ONES                                 0x000000F0U
#define LRFDRFE_IFADC0_INT2ADJ_ZEROS                                0x00000000U

// Field:   [3:2] AAFCAP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ENG                      Internal. Only to be used through TI provided API.
// ENSD                     Internal. Only to be used through TI provided API.
// ENS                      Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC0_AAFCAP_W                                              2U
#define LRFDRFE_IFADC0_AAFCAP_M                                     0x0000000CU
#define LRFDRFE_IFADC0_AAFCAP_S                                              2U
#define LRFDRFE_IFADC0_AAFCAP_ENG                                   0x0000000CU
#define LRFDRFE_IFADC0_AAFCAP_ENSD                                  0x00000008U
#define LRFDRFE_IFADC0_AAFCAP_ENS                                   0x00000004U
#define LRFDRFE_IFADC0_AAFCAP_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADC1
//
//*****************************************************************************
// Field:    [15] NRZ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_NRZ                                          0x00008000U
#define LRFDRFE_IFADC1_NRZ_M                                        0x00008000U
#define LRFDRFE_IFADC1_NRZ_S                                                15U
#define LRFDRFE_IFADC1_NRZ_EN                                       0x00008000U
#define LRFDRFE_IFADC1_NRZ_DIS                                      0x00000000U

// Field:  [14:9] TRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_TRIM_W                                                6U
#define LRFDRFE_IFADC1_TRIM_M                                       0x00007E00U
#define LRFDRFE_IFADC1_TRIM_S                                                9U
#define LRFDRFE_IFADC1_TRIM_ONES                                    0x00007E00U
#define LRFDRFE_IFADC1_TRIM_ZEROS                                   0x00000000U

// Field:     [7] RSTN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIS                      Internal. Only to be used through TI provided API.
// EN                       Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_RSTN                                         0x00000080U
#define LRFDRFE_IFADC1_RSTN_M                                       0x00000080U
#define LRFDRFE_IFADC1_RSTN_S                                                7U
#define LRFDRFE_IFADC1_RSTN_DIS                                     0x00000080U
#define LRFDRFE_IFADC1_RSTN_EN                                      0x00000000U

// Field:     [6] CLKGEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_CLKGEN                                       0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_M                                     0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_S                                              6U
#define LRFDRFE_IFADC1_CLKGEN_EN                                    0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_DIS                                   0x00000000U

// Field:     [5] ADCDIGCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_ADCDIGCLK                                    0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_M                                  0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_S                                           5U
#define LRFDRFE_IFADC1_ADCDIGCLK_EN                                 0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_DIS                                0x00000000U

// Field:     [4] ADCLFSROUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_ADCLFSROUT                                   0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_M                                 0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_S                                          4U
#define LRFDRFE_IFADC1_ADCLFSROUT_EN                                0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_DIS                               0x00000000U

// Field:   [3:1] LPFTSTMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_LPFTSTMODE_W                                          3U
#define LRFDRFE_IFADC1_LPFTSTMODE_M                                 0x0000000EU
#define LRFDRFE_IFADC1_LPFTSTMODE_S                                          1U
#define LRFDRFE_IFADC1_LPFTSTMODE_EN                                0x00000002U
#define LRFDRFE_IFADC1_LPFTSTMODE_DIS                               0x00000000U

// Field:     [0] INVCLKOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADC1_INVCLKOUT                                    0x00000001U
#define LRFDRFE_IFADC1_INVCLKOUT_M                                  0x00000001U
#define LRFDRFE_IFADC1_INVCLKOUT_S                                           0U
#define LRFDRFE_IFADC1_INVCLKOUT_EN                                 0x00000001U
#define LRFDRFE_IFADC1_INVCLKOUT_DIS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCLF
//
//*****************************************************************************
// Field: [15:12] FF3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCLF_FF3_W                                                4U
#define LRFDRFE_IFADCLF_FF3_M                                       0x0000F000U
#define LRFDRFE_IFADCLF_FF3_S                                               12U
#define LRFDRFE_IFADCLF_FF3_ONES                                    0x0000F000U
#define LRFDRFE_IFADCLF_FF3_ZEROS                                   0x00000000U

// Field:  [11:8] FF2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCLF_FF2_W                                                4U
#define LRFDRFE_IFADCLF_FF2_M                                       0x00000F00U
#define LRFDRFE_IFADCLF_FF2_S                                                8U
#define LRFDRFE_IFADCLF_FF2_ONES                                    0x00000F00U
#define LRFDRFE_IFADCLF_FF2_ZEROS                                   0x00000000U

// Field:   [7:4] FF1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCLF_FF1_W                                                4U
#define LRFDRFE_IFADCLF_FF1_M                                       0x000000F0U
#define LRFDRFE_IFADCLF_FF1_S                                                4U
#define LRFDRFE_IFADCLF_FF1_ONES                                    0x000000F0U
#define LRFDRFE_IFADCLF_FF1_ZEROS                                   0x00000000U

// Field:   [3:0] INT3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCLF_INT3_W                                               4U
#define LRFDRFE_IFADCLF_INT3_M                                      0x0000000FU
#define LRFDRFE_IFADCLF_INT3_S                                               0U
#define LRFDRFE_IFADCLF_INT3_ONES                                   0x0000000FU
#define LRFDRFE_IFADCLF_INT3_ZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCQUANT
//
//*****************************************************************************
// Field: [15:14] CLKDLYTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_W                                      2U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_M                             0x0000C000U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_S                                     14U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_ONES                          0x0000C000U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_ZEROS                         0x00000000U

// Field:  [13:9] DBGCALVALIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_W                                     5U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_M                            0x00003E00U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_S                                     9U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_ONES                         0x00003E00U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_ZEROS                        0x00000000U

// Field:     [8] DBGCALLEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// NEG                      Internal. Only to be used through TI provided API.
// POS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_DBGCALLEG                                0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_M                              0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_S                                       8U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_NEG                            0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_POS                            0x00000000U

// Field:   [7:6] DBGCALMQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DBGCAL_QMODB             Internal. Only to be used through TI provided API.
// DBGCAL_QMODP             Internal. Only to be used through TI provided API.
// DBGCAL_QMODN             Internal. Only to be used through TI provided API.
// DBGCAL_QMODZ             Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_DBGCALMQ_W                                        2U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_M                               0x000000C0U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_S                                        6U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODB                    0x000000C0U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODP                    0x00000080U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODN                    0x00000040U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODZ                    0x00000000U

// Field:   [5:4] DBGCALMI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DBGCAL_IMODB             Internal. Only to be used through TI provided API.
// DBGCAL_IMODP             Internal. Only to be used through TI provided API.
// DBGCAL_IMODN             Internal. Only to be used through TI provided API.
// DBGCAL_IMODZ             Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_DBGCALMI_W                                        2U
#define LRFDRFE_IFADCQUANT_DBGCALMI_M                               0x00000030U
#define LRFDRFE_IFADCQUANT_DBGCALMI_S                                        4U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODB                    0x00000030U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODP                    0x00000020U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODN                    0x00000010U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODZ                    0x00000000U

// Field:     [3] AUTOCAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_AUTOCAL                                  0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_M                                0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_S                                         3U
#define LRFDRFE_IFADCQUANT_AUTOCAL_EN                               0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_DIS                              0x00000000U

// Field:   [2:0] QUANTTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCQUANT_QUANTTHR_W                                        3U
#define LRFDRFE_IFADCQUANT_QUANTTHR_M                               0x00000007U
#define LRFDRFE_IFADCQUANT_QUANTTHR_S                                        0U
#define LRFDRFE_IFADCQUANT_QUANTTHR_ONES                            0x00000007U
#define LRFDRFE_IFADCQUANT_QUANTTHR_ZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCALDO
//
//*****************************************************************************
// Field:    [15] ATESTVSSANA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_ATESTVSSANA                               0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_M                             0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_S                                     15U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_EN                            0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_DIS                           0x00000000U

// Field:  [13:8] TRIMOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_TRIMOUT_W                                          6U
#define LRFDRFE_IFADCALDO_TRIMOUT_M                                 0x00003F00U
#define LRFDRFE_IFADCALDO_TRIMOUT_S                                          8U
#define LRFDRFE_IFADCALDO_TRIMOUT_ONES                              0x00003F00U
#define LRFDRFE_IFADCALDO_TRIMOUT_ZEROS                             0x00000000U

// Field:     [7] DUMMY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_DUMMY                                     0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_M                                   0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_S                                            7U
#define LRFDRFE_IFADCALDO_DUMMY_EN                                  0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_DIS                                 0x00000000U

// Field:     [6] ATESTOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_ATESTOUT                                  0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_M                                0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_S                                         6U
#define LRFDRFE_IFADCALDO_ATESTOUT_EN                               0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_DIS                              0x00000000U

// Field:     [5] ATSTLDOFB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_ATSTLDOFB                                 0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_M                               0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_S                                        5U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_EN                              0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_DIS                             0x00000000U

// Field:     [4] ATESTERRAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_ATESTERRAMP                               0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_M                             0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_S                                      4U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_EN                            0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_DIS                           0x00000000U

// Field:     [3] ITEST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_ITEST                                     0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_M                                   0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_S                                            3U
#define LRFDRFE_IFADCALDO_ITEST_EN                                  0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_DIS                                 0x00000000U

// Field:     [2] BYPASS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_BYPASS                                    0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_M                                  0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_S                                           2U
#define LRFDRFE_IFADCALDO_BYPASS_EN                                 0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_DIS                                0x00000000U

// Field:     [1] CLAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_CLAMP                                     0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_M                                   0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_S                                            1U
#define LRFDRFE_IFADCALDO_CLAMP_EN                                  0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_DIS                                 0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCALDO_CTL                                       0x00000001U
#define LRFDRFE_IFADCALDO_CTL_M                                     0x00000001U
#define LRFDRFE_IFADCALDO_CTL_S                                              0U
#define LRFDRFE_IFADCALDO_CTL_EN                                    0x00000001U
#define LRFDRFE_IFADCALDO_CTL_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCDLDO
//
//*****************************************************************************
// Field:  [13:8] TRIMOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_TRIMOUT_W                                          6U
#define LRFDRFE_IFADCDLDO_TRIMOUT_M                                 0x00003F00U
#define LRFDRFE_IFADCDLDO_TRIMOUT_S                                          8U
#define LRFDRFE_IFADCDLDO_TRIMOUT_ONES                              0x00003F00U
#define LRFDRFE_IFADCDLDO_TRIMOUT_ZEROS                             0x00000000U

// Field:     [7] DUMMY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_DUMMY                                     0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_M                                   0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_S                                            7U
#define LRFDRFE_IFADCDLDO_DUMMY_EN                                  0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_DIS                                 0x00000000U

// Field:     [6] ATESTOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_ATESTOUT                                  0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_M                                0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_S                                         6U
#define LRFDRFE_IFADCDLDO_ATESTOUT_EN                               0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_DIS                              0x00000000U

// Field:     [5] ATSTBGP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_ATSTBGP                                   0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_M                                 0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_S                                          5U
#define LRFDRFE_IFADCDLDO_ATSTBGP_EN                                0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_DIS                               0x00000000U

// Field:     [4] ATESTERRAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_ATESTERRAMP                               0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_M                             0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_S                                      4U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_EN                            0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_DIS                           0x00000000U

// Field:     [3] ITEST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_ITEST                                     0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_M                                   0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_S                                            3U
#define LRFDRFE_IFADCDLDO_ITEST_EN                                  0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_DIS                                 0x00000000U

// Field:     [2] BYPASS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_BYPASS                                    0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_M                                  0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_S                                           2U
#define LRFDRFE_IFADCDLDO_BYPASS_EN                                 0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_DIS                                0x00000000U

// Field:     [1] CLAMP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_CLAMP                                     0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_M                                   0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_S                                            1U
#define LRFDRFE_IFADCDLDO_CLAMP_EN                                  0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_DIS                                 0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCDLDO_CTL                                       0x00000001U
#define LRFDRFE_IFADCDLDO_CTL_M                                     0x00000001U
#define LRFDRFE_IFADCDLDO_CTL_S                                              0U
#define LRFDRFE_IFADCDLDO_CTL_EN                                    0x00000001U
#define LRFDRFE_IFADCDLDO_CTL_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCTST
//
//*****************************************************************************
// Field:     [7] EXTCURR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCTST_EXTCURR                                    0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_M                                  0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_S                                           7U
#define LRFDRFE_IFADCTST_EXTCURR_EN                                 0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_DIS                                0x00000000U

// Field:     [6] QCALDBIQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// COMP1                    Internal. Only to be used through TI provided API.
// COMP0                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCTST_QCALDBIQ                                   0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_M                                 0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_S                                          6U
#define LRFDRFE_IFADCTST_QCALDBIQ_COMP1                             0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_COMP0                             0x00000000U

// Field:     [5] QCALDBC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// COMP1                    Internal. Only to be used through TI provided API.
// COMP0                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCTST_QCALDBC                                    0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_M                                  0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_S                                           5U
#define LRFDRFE_IFADCTST_QCALDBC_COMP1                              0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_COMP0                              0x00000000U

// Field:   [4:0] SEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EXTCLKN1                 Internal. Only to be used through TI provided API.
// NONE                     Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCTST_SEL_W                                               5U
#define LRFDRFE_IFADCTST_SEL_M                                      0x0000001FU
#define LRFDRFE_IFADCTST_SEL_S                                               0U
#define LRFDRFE_IFADCTST_SEL_EXTCLKN1                               0x0000001FU
#define LRFDRFE_IFADCTST_SEL_NONE                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_ATSTREFL
//
//*****************************************************************************
// Field:  [15:0] MUXLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// IFADC_ATB                Internal. Only to be used through TI provided API.
// LDO_VTEST                Internal. Only to be used through TI provided API.
// LDO_ITEST                Internal. Only to be used through TI provided API.
// PA_PEAK_OUTN             Internal. Only to be used through TI provided API.
// PA_PEAK_OUTP             Internal. Only to be used through TI provided API.
// MIX_OUTQN                Internal. Only to be used through TI provided API.
// MIX_OUTQP                Internal. Only to be used through TI provided API.
// MIX_OUTIN                Internal. Only to be used through TI provided API.
// MIX_OUTIP                Internal. Only to be used through TI provided API.
// FE_OUTIN_2               Internal. Only to be used through TI provided API.
// FE_OUTIP_2               Internal. Only to be used through TI provided API.
// FE_OUTQN                 Internal. Only to be used through TI provided API.
// FE_OUTQP                 Internal. Only to be used through TI provided API.
// FE_OUTIN                 Internal. Only to be used through TI provided API.
// FE_OUTIP                 Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFL_MUXLSB_W                                           16U
#define LRFDRFE_ATSTREFL_MUXLSB_M                                   0x0000FFFFU
#define LRFDRFE_ATSTREFL_MUXLSB_S                                            0U
#define LRFDRFE_ATSTREFL_MUXLSB_IFADC_ATB                           0x00008000U
#define LRFDRFE_ATSTREFL_MUXLSB_LDO_VTEST                           0x00004000U
#define LRFDRFE_ATSTREFL_MUXLSB_LDO_ITEST                           0x00002000U
#define LRFDRFE_ATSTREFL_MUXLSB_PA_PEAK_OUTN                        0x00000800U
#define LRFDRFE_ATSTREFL_MUXLSB_PA_PEAK_OUTP                        0x00000400U
#define LRFDRFE_ATSTREFL_MUXLSB_MIX_OUTQN                           0x00000200U
#define LRFDRFE_ATSTREFL_MUXLSB_MIX_OUTQP                           0x00000100U
#define LRFDRFE_ATSTREFL_MUXLSB_MIX_OUTIN                           0x00000080U
#define LRFDRFE_ATSTREFL_MUXLSB_MIX_OUTIP                           0x00000040U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTIN_2                          0x00000020U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTIP_2                          0x00000010U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTQN                            0x00000008U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTQP                            0x00000004U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTIN                            0x00000002U
#define LRFDRFE_ATSTREFL_MUXLSB_FE_OUTIP                            0x00000001U
#define LRFDRFE_ATSTREFL_MUXLSB_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_ATSTREFH
//
//*****************************************************************************
// Field:    [15] VREFBPDIS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BPDIS                    Internal. Only to be used through TI provided API.
// BPEN                     Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_VREFBPDIS                                  0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_M                                0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_S                                        15U
#define LRFDRFE_ATSTREFH_VREFBPDIS_BPDIS                            0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_BPEN                             0x00000000U

// Field: [14:10] IREFTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_IREFTRIM_W                                          5U
#define LRFDRFE_ATSTREFH_IREFTRIM_M                                 0x00007C00U
#define LRFDRFE_ATSTREFH_IREFTRIM_S                                         10U
#define LRFDRFE_ATSTREFH_IREFTRIM_ONES                              0x00007C00U
#define LRFDRFE_ATSTREFH_IREFTRIM_ZEROS                             0x00000000U

// Field:     [9] BIAS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_BIAS                                       0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_M                                     0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_S                                              9U
#define LRFDRFE_ATSTREFH_BIAS_EN                                    0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_DIS                                   0x00000000U

// Field:     [8] OUTPUT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_OUTPUT2                                    0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_M                                  0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_S                                           8U
#define LRFDRFE_ATSTREFH_OUTPUT2_EN                                 0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_DIS                                0x00000000U

// Field:     [7] OUTPUT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_OUTPUT1                                    0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_M                                  0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_S                                           7U
#define LRFDRFE_ATSTREFH_OUTPUT1_EN                                 0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_DIS                                0x00000000U

// Field:   [6:0] MUXMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIVBUF_NMOS_BIAS         Internal. Only to be used through TI provided API.
// DIVBUF_PMOS_BIAS         Internal. Only to be used through TI provided API.
// REFSYS_IREF              Internal. Only to be used through TI provided API.
// IFADC_ATB                Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_ATSTREFH_MUXMSB_W                                            7U
#define LRFDRFE_ATSTREFH_MUXMSB_M                                   0x0000007FU
#define LRFDRFE_ATSTREFH_MUXMSB_S                                            0U
#define LRFDRFE_ATSTREFH_MUXMSB_DIVBUF_NMOS_BIAS                    0x00000010U
#define LRFDRFE_ATSTREFH_MUXMSB_DIVBUF_PMOS_BIAS                    0x00000008U
#define LRFDRFE_ATSTREFH_MUXMSB_REFSYS_IREF                         0x00000004U
#define LRFDRFE_ATSTREFH_MUXMSB_IFADC_ATB                           0x00000001U
#define LRFDRFE_ATSTREFH_MUXMSB_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DCO
//
//*****************************************************************************
// Field:  [10:9] MTDCSPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIS                      Internal. Only to be used through TI provided API.
// EN                       Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_MTDCSPARE_W                                              2U
#define LRFDRFE_DCO_MTDCSPARE_M                                     0x00000600U
#define LRFDRFE_DCO_MTDCSPARE_S                                              9U
#define LRFDRFE_DCO_MTDCSPARE_DIS                                   0x00000200U
#define LRFDRFE_DCO_MTDCSPARE_EN                                    0x00000000U

// Field:   [8:7] SPARE7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_SPARE7_W                                                 2U
#define LRFDRFE_DCO_SPARE7_M                                        0x00000180U
#define LRFDRFE_DCO_SPARE7_S                                                 7U
#define LRFDRFE_DCO_SPARE7_ONE                                      0x00000080U
#define LRFDRFE_DCO_SPARE7_ZERO                                     0x00000000U

// Field:   [6:3] TAILRESTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_TAILRESTRIM_W                                            4U
#define LRFDRFE_DCO_TAILRESTRIM_M                                   0x00000078U
#define LRFDRFE_DCO_TAILRESTRIM_S                                            3U
#define LRFDRFE_DCO_TAILRESTRIM_ALLONES                             0x00000078U
#define LRFDRFE_DCO_TAILRESTRIM_ALLZEROS                            0x00000000U

// Field:     [2] RTRIMCAP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_RTRIMCAP                                        0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_M                                      0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_S                                               2U
#define LRFDRFE_DCO_RTRIMCAP_EN                                     0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_DIS                                    0x00000000U

// Field:     [1] CNRCAP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// _50MHZ                   Internal. Only to be used through TI provided API.
// DEFAULT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_CNRCAP                                          0x00000002U
#define LRFDRFE_DCO_CNRCAP_M                                        0x00000002U
#define LRFDRFE_DCO_CNRCAP_S                                                 1U
#define LRFDRFE_DCO_CNRCAP__50MHZ                                   0x00000002U
#define LRFDRFE_DCO_CNRCAP_DEFAULT                                  0x00000000U

// Field:     [0] CRSCAPCM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// REDUCED                  Internal. Only to be used through TI provided API.
// DEFAULT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_DCO_CRSCAPCM                                        0x00000001U
#define LRFDRFE_DCO_CRSCAPCM_M                                      0x00000001U
#define LRFDRFE_DCO_CRSCAPCM_S                                               0U
#define LRFDRFE_DCO_CRSCAPCM_REDUCED                                0x00000001U
#define LRFDRFE_DCO_CRSCAPCM_DEFAULT                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIV
//
//*****************************************************************************
// Field:    [15] PDET
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_PDET                                            0x00008000U
#define LRFDRFE_DIV_PDET_M                                          0x00008000U
#define LRFDRFE_DIV_PDET_S                                                  15U
#define LRFDRFE_DIV_PDET_EN                                         0x00008000U
#define LRFDRFE_DIV_PDET_DIS                                        0x00000000U

// Field: [14:12] NMIREFTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_NMIREFTRIM_W                                             3U
#define LRFDRFE_DIV_NMIREFTRIM_M                                    0x00007000U
#define LRFDRFE_DIV_NMIREFTRIM_S                                            12U
#define LRFDRFE_DIV_NMIREFTRIM_ALLONES                              0x00007000U
#define LRFDRFE_DIV_NMIREFTRIM_ALLZEROS                             0x00000000U

// Field:  [11:9] PMIREFTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_PMIREFTRIM_W                                             3U
#define LRFDRFE_DIV_PMIREFTRIM_M                                    0x00000E00U
#define LRFDRFE_DIV_PMIREFTRIM_S                                             9U
#define LRFDRFE_DIV_PMIREFTRIM_ALLONES                              0x00000E00U
#define LRFDRFE_DIV_PMIREFTRIM_ALLZEROS                             0x00000000U

// Field:     [8] TXBBOOST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// INCREASED                Internal. Only to be used through TI provided API.
// DEFAULT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_TXBBOOST                                        0x00000100U
#define LRFDRFE_DIV_TXBBOOST_M                                      0x00000100U
#define LRFDRFE_DIV_TXBBOOST_S                                               8U
#define LRFDRFE_DIV_TXBBOOST_INCREASED                              0x00000100U
#define LRFDRFE_DIV_TXBBOOST_DEFAULT                                0x00000000U

// Field:     [7] S1GFRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_S1GFRC                                          0x00000080U
#define LRFDRFE_DIV_S1GFRC_M                                        0x00000080U
#define LRFDRFE_DIV_S1GFRC_S                                                 7U
#define LRFDRFE_DIV_S1GFRC_EN                                       0x00000080U
#define LRFDRFE_DIV_S1GFRC_DIS                                      0x00000000U

// Field:   [6:5] BUFGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// _60_PST                  Internal. Only to be used through TI provided API.
// DONT_USE                 Internal. Only to be used through TI provided API.
// _80_PST                  Internal. Only to be used through TI provided API.
// MAX                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_BUFGAIN_W                                                2U
#define LRFDRFE_DIV_BUFGAIN_M                                       0x00000060U
#define LRFDRFE_DIV_BUFGAIN_S                                                5U
#define LRFDRFE_DIV_BUFGAIN__60_PST                                 0x00000060U
#define LRFDRFE_DIV_BUFGAIN_DONT_USE                                0x00000040U
#define LRFDRFE_DIV_BUFGAIN__80_PST                                 0x00000020U
#define LRFDRFE_DIV_BUFGAIN_MAX                                     0x00000000U

// Field:     [4] BIAS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DEFAULT                  Internal. Only to be used through TI provided API.
// ALTERNATIVE              Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_BIAS                                            0x00000010U
#define LRFDRFE_DIV_BIAS_M                                          0x00000010U
#define LRFDRFE_DIV_BIAS_S                                                   4U
#define LRFDRFE_DIV_BIAS_DEFAULT                                    0x00000010U
#define LRFDRFE_DIV_BIAS_ALTERNATIVE                                0x00000000U

// Field:     [3] OUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FE_2G4                   Internal. Only to be used through TI provided API.
// FE_S1G                   Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_OUT                                             0x00000008U
#define LRFDRFE_DIV_OUT_M                                           0x00000008U
#define LRFDRFE_DIV_OUT_S                                                    3U
#define LRFDRFE_DIV_OUT_FE_2G4                                      0x00000008U
#define LRFDRFE_DIV_OUT_FE_S1G                                      0x00000000U

// Field:   [2:0] RATIO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV30                    Internal. Only to be used through TI provided API.
// DIV15                    Internal. Only to be used through TI provided API.
// DIV10                    Internal. Only to be used through TI provided API.
// DIV5                     Internal. Only to be used through TI provided API.
// DIV12                    Internal. Only to be used through TI provided API.
// DIV6                     Internal. Only to be used through TI provided API.
// DIV4                     Internal. Only to be used through TI provided API.
// DIV2                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIV_RATIO_W                                                  3U
#define LRFDRFE_DIV_RATIO_M                                         0x00000007U
#define LRFDRFE_DIV_RATIO_S                                                  0U
#define LRFDRFE_DIV_RATIO_DIV30                                     0x00000007U
#define LRFDRFE_DIV_RATIO_DIV15                                     0x00000006U
#define LRFDRFE_DIV_RATIO_DIV10                                     0x00000005U
#define LRFDRFE_DIV_RATIO_DIV5                                      0x00000004U
#define LRFDRFE_DIV_RATIO_DIV12                                     0x00000003U
#define LRFDRFE_DIV_RATIO_DIV6                                      0x00000002U
#define LRFDRFE_DIV_RATIO_DIV4                                      0x00000001U
#define LRFDRFE_DIV_RATIO_DIV2                                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVLDO
//
//*****************************************************************************
// Field:    [15] SPARE15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_SPARE15                                      0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_M                                    0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_S                                            15U
#define LRFDRFE_DIVLDO_SPARE15_ONES                                 0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_ZEROS                                0x00000000U

// Field:  [14:8] VOUTTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_VOUTTRIM_W                                            7U
#define LRFDRFE_DIVLDO_VOUTTRIM_M                                   0x00007F00U
#define LRFDRFE_DIVLDO_VOUTTRIM_S                                            8U
#define LRFDRFE_DIVLDO_VOUTTRIM_ONES                                0x00007F00U
#define LRFDRFE_DIVLDO_VOUTTRIM_ZEROS                               0x00000000U

// Field:     [7] ITST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_ITST                                         0x00000080U
#define LRFDRFE_DIVLDO_ITST_M                                       0x00000080U
#define LRFDRFE_DIVLDO_ITST_S                                                7U
#define LRFDRFE_DIVLDO_ITST_EN                                      0x00000080U
#define LRFDRFE_DIVLDO_ITST_DIS                                     0x00000000U

// Field:   [6:4] TMUX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VDDR                     Internal. Only to be used through TI provided API.
// LDO_OUT                  Internal. Only to be used through TI provided API.
// GND                      Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_TMUX_W                                                3U
#define LRFDRFE_DIVLDO_TMUX_M                                       0x00000070U
#define LRFDRFE_DIVLDO_TMUX_S                                                4U
#define LRFDRFE_DIVLDO_TMUX_VDDR                                    0x00000040U
#define LRFDRFE_DIVLDO_TMUX_LDO_OUT                                 0x00000020U
#define LRFDRFE_DIVLDO_TMUX_GND                                     0x00000010U
#define LRFDRFE_DIVLDO_TMUX_OFF                                     0x00000000U

// Field:     [3] SPARE3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_SPARE3                                       0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_M                                     0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_S                                              3U
#define LRFDRFE_DIVLDO_SPARE3_ONE                                   0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_ZERO                                  0x00000000U

// Field:     [2] MODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FAST                     Internal. Only to be used through TI provided API.
// NORM                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_MODE                                         0x00000004U
#define LRFDRFE_DIVLDO_MODE_M                                       0x00000004U
#define LRFDRFE_DIVLDO_MODE_S                                                2U
#define LRFDRFE_DIVLDO_MODE_FAST                                    0x00000004U
#define LRFDRFE_DIVLDO_MODE_NORM                                    0x00000000U

// Field:     [1] BYPASS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_BYPASS                                       0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_M                                     0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_S                                              1U
#define LRFDRFE_DIVLDO_BYPASS_EN                                    0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_DIS                                   0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVLDO_CTL                                          0x00000001U
#define LRFDRFE_DIVLDO_CTL_M                                        0x00000001U
#define LRFDRFE_DIVLDO_CTL_S                                                 0U
#define LRFDRFE_DIVLDO_CTL_EN                                       0x00000001U
#define LRFDRFE_DIVLDO_CTL_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TDCLDO
//
//*****************************************************************************
// Field:    [15] ITESTCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_ITESTCTL                                     0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_M                                   0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_S                                           15U
#define LRFDRFE_TDCLDO_ITESTCTL_EN                                  0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_DIS                                 0x00000000U

// Field:  [14:8] VOUTTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_VOUTTRIM_W                                            7U
#define LRFDRFE_TDCLDO_VOUTTRIM_M                                   0x00007F00U
#define LRFDRFE_TDCLDO_VOUTTRIM_S                                            8U
#define LRFDRFE_TDCLDO_VOUTTRIM_ONES                                0x00007F00U
#define LRFDRFE_TDCLDO_VOUTTRIM_ZEROS                               0x00000000U

// Field:     [7] ITESTBUFCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_ITESTBUFCTL                                  0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_M                                0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_S                                         7U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_EN                               0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_DIS                              0x00000000U

// Field:   [6:4] TMUX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VSSA                     Internal. Only to be used through TI provided API.
// LDO_OUT                  Internal. Only to be used through TI provided API.
// VDDA                     Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_TMUX_W                                                3U
#define LRFDRFE_TDCLDO_TMUX_M                                       0x00000070U
#define LRFDRFE_TDCLDO_TMUX_S                                                4U
#define LRFDRFE_TDCLDO_TMUX_VSSA                                    0x00000040U
#define LRFDRFE_TDCLDO_TMUX_LDO_OUT                                 0x00000020U
#define LRFDRFE_TDCLDO_TMUX_VDDA                                    0x00000010U
#define LRFDRFE_TDCLDO_TMUX_OFF                                     0x00000000U

// Field:     [3] PDSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIODE                    Internal. Only to be used through TI provided API.
// R                        Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_PDSEL                                        0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_M                                      0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_S                                               3U
#define LRFDRFE_TDCLDO_PDSEL_DIODE                                  0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_R                                      0x00000000U

// Field:     [2] MODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FAST                     Internal. Only to be used through TI provided API.
// NORM                     Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_MODE                                         0x00000004U
#define LRFDRFE_TDCLDO_MODE_M                                       0x00000004U
#define LRFDRFE_TDCLDO_MODE_S                                                2U
#define LRFDRFE_TDCLDO_MODE_FAST                                    0x00000004U
#define LRFDRFE_TDCLDO_MODE_NORM                                    0x00000000U

// Field:     [1] BYPASS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_BYPASS                                       0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_M                                     0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_S                                              1U
#define LRFDRFE_TDCLDO_BYPASS_EN                                    0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_DIS                                   0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCLDO_CTL                                          0x00000001U
#define LRFDRFE_TDCLDO_CTL_M                                        0x00000001U
#define LRFDRFE_TDCLDO_CTL_S                                                 0U
#define LRFDRFE_TDCLDO_CTL_EN                                       0x00000001U
#define LRFDRFE_TDCLDO_CTL_DIS                                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DCOLDO0
//
//*****************************************************************************
// Field: [15:14] ITST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BOTH                     Internal. Only to be used through TI provided API.
// SECOND                   Internal. Only to be used through TI provided API.
// FIRST                    Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_ITST_W                                               2U
#define LRFDRFE_DCOLDO0_ITST_M                                      0x0000C000U
#define LRFDRFE_DCOLDO0_ITST_S                                              14U
#define LRFDRFE_DCOLDO0_ITST_BOTH                                   0x0000C000U
#define LRFDRFE_DCOLDO0_ITST_SECOND                                 0x00008000U
#define LRFDRFE_DCOLDO0_ITST_FIRST                                  0x00004000U
#define LRFDRFE_DCOLDO0_ITST_DIS                                    0x00000000U

// Field:  [13:8] SECONDTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_SECONDTRIM_W                                         6U
#define LRFDRFE_DCOLDO0_SECONDTRIM_M                                0x00003F00U
#define LRFDRFE_DCOLDO0_SECONDTRIM_S                                         8U
#define LRFDRFE_DCOLDO0_SECONDTRIM_ONES                             0x00003F00U
#define LRFDRFE_DCOLDO0_SECONDTRIM_ZEROS                            0x00000000U

// Field:   [7:4] FIRSTTRIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_FIRSTTRIM_W                                          4U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_M                                 0x000000F0U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_S                                          4U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_ONES                              0x000000F0U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_ZEROS                             0x00000000U

// Field:     [3] PDN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_PDN                                         0x00000008U
#define LRFDRFE_DCOLDO0_PDN_M                                       0x00000008U
#define LRFDRFE_DCOLDO0_PDN_S                                                3U
#define LRFDRFE_DCOLDO0_PDN_EN                                      0x00000008U
#define LRFDRFE_DCOLDO0_PDN_DIS                                     0x00000000U

// Field:     [2] BYPFIRST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_BYPFIRST                                    0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_M                                  0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_S                                           2U
#define LRFDRFE_DCOLDO0_BYPFIRST_EN                                 0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_DIS                                0x00000000U

// Field:     [1] BYPBOTH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_BYPBOTH                                     0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_M                                   0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_S                                            1U
#define LRFDRFE_DCOLDO0_BYPBOTH_EN                                  0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_DIS                                 0x00000000U

// Field:     [0] CTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO0_CTL                                         0x00000001U
#define LRFDRFE_DCOLDO0_CTL_M                                       0x00000001U
#define LRFDRFE_DCOLDO0_CTL_S                                                0U
#define LRFDRFE_DCOLDO0_CTL_EN                                      0x00000001U
#define LRFDRFE_DCOLDO0_CTL_DIS                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DCOLDO1
//
//*****************************************************************************
// Field:    [10] REFSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BAW                      Internal. Only to be used through TI provided API.
// XTAL                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO1_REFSRC                                      0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_M                                    0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_S                                            10U
#define LRFDRFE_DCOLDO1_REFSRC_BAW                                  0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_XTAL                                 0x00000000U

// Field:   [9:8] DIVATST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO1_DIVATST_W                                            2U
#define LRFDRFE_DCOLDO1_DIVATST_M                                   0x00000300U
#define LRFDRFE_DCOLDO1_DIVATST_S                                            8U
#define LRFDRFE_DCOLDO1_DIVATST_ONES                                0x00000300U
#define LRFDRFE_DCOLDO1_DIVATST_ZEROS                               0x00000000U

// Field:     [7] PERFM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO1_PERFM                                       0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_M                                     0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_S                                              7U
#define LRFDRFE_DCOLDO1_PERFM_EN                                    0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_DIS                                   0x00000000U

// Field:     [6] CHRGFILT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO1_CHRGFILT                                    0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_M                                  0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_S                                           6U
#define LRFDRFE_DCOLDO1_CHRGFILT_EN                                 0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_DIS                                0x00000000U

// Field:   [5:0] ATST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VSSANA                   Internal. Only to be used through TI provided API.
// FIRST_OUT                Internal. Only to be used through TI provided API.
// LDO_OUT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOLDO1_ATST_W                                               6U
#define LRFDRFE_DCOLDO1_ATST_M                                      0x0000003FU
#define LRFDRFE_DCOLDO1_ATST_S                                               0U
#define LRFDRFE_DCOLDO1_ATST_VSSANA                                 0x00000020U
#define LRFDRFE_DCOLDO1_ATST_FIRST_OUT                              0x00000001U
#define LRFDRFE_DCOLDO1_ATST_LDO_OUT                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRE0
//
//*****************************************************************************
// Field: [15:14] SPARE14
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE0_SPARE14_W                                               2U
#define LRFDRFE_PRE0_SPARE14_M                                      0x0000C000U
#define LRFDRFE_PRE0_SPARE14_S                                              14U
#define LRFDRFE_PRE0_SPARE14_ALLONES                                0x0000C000U
#define LRFDRFE_PRE0_SPARE14_ALLZEROS                               0x00000000U

// Field:  [13:8] PLLDIV1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE0_PLLDIV1_W                                               6U
#define LRFDRFE_PRE0_PLLDIV1_M                                      0x00003F00U
#define LRFDRFE_PRE0_PLLDIV1_S                                               8U
#define LRFDRFE_PRE0_PLLDIV1_ALLONES                                0x00003F00U
#define LRFDRFE_PRE0_PLLDIV1_ALLZEROS                               0x00000000U

// Field:   [7:6] SPARE6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE0_SPARE6_W                                                2U
#define LRFDRFE_PRE0_SPARE6_M                                       0x000000C0U
#define LRFDRFE_PRE0_SPARE6_S                                                6U
#define LRFDRFE_PRE0_SPARE6_ALLONES                                 0x000000C0U
#define LRFDRFE_PRE0_SPARE6_ALLZEROS                                0x00000000U

// Field:   [5:0] PLLDIV0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE0_PLLDIV0_W                                               6U
#define LRFDRFE_PRE0_PLLDIV0_M                                      0x0000003FU
#define LRFDRFE_PRE0_PLLDIV0_S                                               0U
#define LRFDRFE_PRE0_PLLDIV0_ALLONES                                0x0000003FU
#define LRFDRFE_PRE0_PLLDIV0_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRE1
//
//*****************************************************************************
// Field: [15:14] IIRBW
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// K16                      Internal. Only to be used through TI provided API.
// K8                       Internal. Only to be used through TI provided API.
// K4                       Internal. Only to be used through TI provided API.
// K2                       Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE1_IIRBW_W                                                 2U
#define LRFDRFE_PRE1_IIRBW_M                                        0x0000C000U
#define LRFDRFE_PRE1_IIRBW_S                                                14U
#define LRFDRFE_PRE1_IIRBW_K16                                      0x0000C000U
#define LRFDRFE_PRE1_IIRBW_K8                                       0x00008000U
#define LRFDRFE_PRE1_IIRBW_K4                                       0x00004000U
#define LRFDRFE_PRE1_IIRBW_K2                                       0x00000000U

// Field:    [13] IIRORD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SECOND                   Internal. Only to be used through TI provided API.
// FIRST                    Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE1_IIRORD                                         0x00002000U
#define LRFDRFE_PRE1_IIRORD_M                                       0x00002000U
#define LRFDRFE_PRE1_IIRORD_S                                               13U
#define LRFDRFE_PRE1_IIRORD_SECOND                                  0x00002000U
#define LRFDRFE_PRE1_IIRORD_FIRST                                   0x00000000U

// Field:  [12:8] IIRDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE1_IIRDIV_W                                                5U
#define LRFDRFE_PRE1_IIRDIV_M                                       0x00001F00U
#define LRFDRFE_PRE1_IIRDIV_S                                                8U
#define LRFDRFE_PRE1_IIRDIV_ALLONES                                 0x00001F00U
#define LRFDRFE_PRE1_IIRDIV_ALLZEROS                                0x00000000U

// Field:     [6] CALHSDDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GATE                     Internal. Only to be used through TI provided API.
// NOGATE                   Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE1_CALHSDDC                                       0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_M                                     0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_S                                              6U
#define LRFDRFE_PRE1_CALHSDDC_GATE                                  0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_NOGATE                                0x00000000U

// Field:   [5:0] HSDDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE1_HSDDC_W                                                 6U
#define LRFDRFE_PRE1_HSDDC_M                                        0x0000003FU
#define LRFDRFE_PRE1_HSDDC_S                                                 0U
#define LRFDRFE_PRE1_HSDDC_ALLONES                                  0x0000003FU
#define LRFDRFE_PRE1_HSDDC_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRE2
//
//*****************************************************************************
// Field: [15:12] MIDCALDIVLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE2_MIDCALDIVLSB_W                                          4U
#define LRFDRFE_PRE2_MIDCALDIVLSB_M                                 0x0000F000U
#define LRFDRFE_PRE2_MIDCALDIVLSB_S                                         12U
#define LRFDRFE_PRE2_MIDCALDIVLSB_ALLONES                           0x0000F000U
#define LRFDRFE_PRE2_MIDCALDIVLSB_ALLZEROS                          0x00000000U

// Field:  [11:6] CRSCALDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE2_CRSCALDIV_W                                             6U
#define LRFDRFE_PRE2_CRSCALDIV_M                                    0x00000FC0U
#define LRFDRFE_PRE2_CRSCALDIV_S                                             6U
#define LRFDRFE_PRE2_CRSCALDIV_ALLONES                              0x00000FC0U
#define LRFDRFE_PRE2_CRSCALDIV_ALLZEROS                             0x00000000U

// Field:   [5:0] FSMDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE2_FSMDIV_W                                                6U
#define LRFDRFE_PRE2_FSMDIV_M                                       0x0000003FU
#define LRFDRFE_PRE2_FSMDIV_S                                                0U
#define LRFDRFE_PRE2_FSMDIV_ALLONES                                 0x0000003FU
#define LRFDRFE_PRE2_FSMDIV_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRE3
//
//*****************************************************************************
// Field:  [15:5] FINECALDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE3_FINECALDIV_W                                           11U
#define LRFDRFE_PRE3_FINECALDIV_M                                   0x0000FFE0U
#define LRFDRFE_PRE3_FINECALDIV_S                                            5U
#define LRFDRFE_PRE3_FINECALDIV_ALLONES                             0x0000FFE0U
#define LRFDRFE_PRE3_FINECALDIV_ALLZEROS                            0x00000000U

// Field:   [4:0] MIDCALDIVMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRE3_MIDCALDIVMSB_W                                          5U
#define LRFDRFE_PRE3_MIDCALDIVMSB_M                                 0x0000001FU
#define LRFDRFE_PRE3_MIDCALDIVMSB_S                                          0U
#define LRFDRFE_PRE3_MIDCALDIVMSB_ALLONES                           0x0000001FU
#define LRFDRFE_PRE3_MIDCALDIVMSB_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CAL0
//
//*****************************************************************************
// Field:    [15] SPARE15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_SPARE15                                        0x00008000U
#define LRFDRFE_CAL0_SPARE15_M                                      0x00008000U
#define LRFDRFE_CAL0_SPARE15_S                                              15U
#define LRFDRFE_CAL0_SPARE15_ONE                                    0x00008000U
#define LRFDRFE_CAL0_SPARE15_ZERO                                   0x00000000U

// Field:  [14:8] FCSTART
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_FCSTART_W                                               7U
#define LRFDRFE_CAL0_FCSTART_M                                      0x00007F00U
#define LRFDRFE_CAL0_FCSTART_S                                               8U
#define LRFDRFE_CAL0_FCSTART_ALLONES                                0x00007F00U
#define LRFDRFE_CAL0_FCSTART_ALLZEROS                               0x00000000U

// Field:     [7] CRS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_CRS                                            0x00000080U
#define LRFDRFE_CAL0_CRS_M                                          0x00000080U
#define LRFDRFE_CAL0_CRS_S                                                   7U
#define LRFDRFE_CAL0_CRS_EN                                         0x00000080U
#define LRFDRFE_CAL0_CRS_DIS                                        0x00000000U

// Field:     [6] MID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_MID                                            0x00000040U
#define LRFDRFE_CAL0_MID_M                                          0x00000040U
#define LRFDRFE_CAL0_MID_S                                                   6U
#define LRFDRFE_CAL0_MID_EN                                         0x00000040U
#define LRFDRFE_CAL0_MID_DIS                                        0x00000000U

// Field:     [5] KTDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_KTDC                                           0x00000020U
#define LRFDRFE_CAL0_KTDC_M                                         0x00000020U
#define LRFDRFE_CAL0_KTDC_S                                                  5U
#define LRFDRFE_CAL0_KTDC_EN                                        0x00000020U
#define LRFDRFE_CAL0_KTDC_DIS                                       0x00000000U

// Field:     [4] KDCO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_KDCO                                           0x00000010U
#define LRFDRFE_CAL0_KDCO_M                                         0x00000010U
#define LRFDRFE_CAL0_KDCO_S                                                  4U
#define LRFDRFE_CAL0_KDCO_EN                                        0x00000010U
#define LRFDRFE_CAL0_KDCO_DIS                                       0x00000000U

// Field:   [3:2] TDCAVG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// REPEAT_8_TIMES           Internal. Only to be used through TI provided API.
// REPEAT_4_TIMES           Internal. Only to be used through TI provided API.
// REPEAT_2_TIMES           Internal. Only to be used through TI provided API.
// REPEAT_1_TIME            Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_TDCAVG_W                                                2U
#define LRFDRFE_CAL0_TDCAVG_M                                       0x0000000CU
#define LRFDRFE_CAL0_TDCAVG_S                                                2U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_8_TIMES                          0x0000000CU
#define LRFDRFE_CAL0_TDCAVG_REPEAT_4_TIMES                          0x00000008U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_2_TIMES                          0x00000004U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_1_TIME                           0x00000000U

// Field:   [1:0] TDC_SPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL0_TDC_SPARE_W                                             2U
#define LRFDRFE_CAL0_TDC_SPARE_M                                    0x00000003U
#define LRFDRFE_CAL0_TDC_SPARE_S                                             0U
#define LRFDRFE_CAL0_TDC_SPARE_ALLONES                              0x00000003U
#define LRFDRFE_CAL0_TDC_SPARE_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CAL1
//
//*****************************************************************************
// Field:    [15] SPARE15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL1_SPARE15                                        0x00008000U
#define LRFDRFE_CAL1_SPARE15_M                                      0x00008000U
#define LRFDRFE_CAL1_SPARE15_S                                              15U
#define LRFDRFE_CAL1_SPARE15_ONE                                    0x00008000U
#define LRFDRFE_CAL1_SPARE15_ZERO                                   0x00000000U

// Field:  [14:8] FCTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL1_FCTOP_W                                                 7U
#define LRFDRFE_CAL1_FCTOP_M                                        0x00007F00U
#define LRFDRFE_CAL1_FCTOP_S                                                 8U
#define LRFDRFE_CAL1_FCTOP_ALLONES                                  0x00007F00U
#define LRFDRFE_CAL1_FCTOP_ALLZEROS                                 0x00000000U

// Field:     [7] SPARE7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL1_SPARE7                                         0x00000080U
#define LRFDRFE_CAL1_SPARE7_M                                       0x00000080U
#define LRFDRFE_CAL1_SPARE7_S                                                7U
#define LRFDRFE_CAL1_SPARE7_ONE                                     0x00000080U
#define LRFDRFE_CAL1_SPARE7_ZERO                                    0x00000000U

// Field:   [6:0] FCBOT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL1_FCBOT_W                                                 7U
#define LRFDRFE_CAL1_FCBOT_M                                        0x0000007FU
#define LRFDRFE_CAL1_FCBOT_S                                                 0U
#define LRFDRFE_CAL1_FCBOT_ALLONES                                  0x0000007FU
#define LRFDRFE_CAL1_FCBOT_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CAL2
//
//*****************************************************************************
// Field:  [15:0] KTDCINV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL2_KTDCINV_W                                              16U
#define LRFDRFE_CAL2_KTDCINV_M                                      0x0000FFFFU
#define LRFDRFE_CAL2_KTDCINV_S                                               0U
#define LRFDRFE_CAL2_KTDCINV_ALLONES                                0x0000FFFFU
#define LRFDRFE_CAL2_KTDCINV_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CAL3
//
//*****************************************************************************
// Field:  [15:0] DTXGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CAL3_DTXGAIN_W                                              16U
#define LRFDRFE_CAL3_DTXGAIN_M                                      0x0000FFFFU
#define LRFDRFE_CAL3_DTXGAIN_S                                               0U
#define LRFDRFE_CAL3_DTXGAIN_ALLONES                                0x0000FFFFU
#define LRFDRFE_CAL3_DTXGAIN_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MISC0
//
//*****************************************************************************
// Field:    [13] PHCPT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ASYNC                    Internal. Only to be used through TI provided API.
// SYNC                     Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_PHCPT                                         0x00002000U
#define LRFDRFE_MISC0_PHCPT_M                                       0x00002000U
#define LRFDRFE_MISC0_PHCPT_S                                               13U
#define LRFDRFE_MISC0_PHCPT_ASYNC                                   0x00002000U
#define LRFDRFE_MISC0_PHCPT_SYNC                                    0x00000000U

// Field:    [12] TDCCALCORR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_TDCCALCORR                                    0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_M                                  0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_S                                          12U
#define LRFDRFE_MISC0_TDCCALCORR_EN                                 0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_DIS                                0x00000000U

// Field:    [11] TDCMSBCORR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_TDCMSBCORR                                    0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_M                                  0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_S                                          11U
#define LRFDRFE_MISC0_TDCMSBCORR_EN                                 0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_DIS                                0x00000000U

// Field:    [10] SDMDEM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_SDMDEM                                        0x00000400U
#define LRFDRFE_MISC0_SDMDEM_M                                      0x00000400U
#define LRFDRFE_MISC0_SDMDEM_S                                              10U
#define LRFDRFE_MISC0_SDMDEM_EN                                     0x00000400U
#define LRFDRFE_MISC0_SDMDEM_DIS                                    0x00000000U

// Field:   [9:8] DLYSDM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD16_3_PER             Internal. Only to be used through TI provided API.
// CKVD16_2_PER             Internal. Only to be used through TI provided API.
// CKVD16_1_PER             Internal. Only to be used through TI provided API.
// CKVD16_0_PER             Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_DLYSDM_W                                               2U
#define LRFDRFE_MISC0_DLYSDM_M                                      0x00000300U
#define LRFDRFE_MISC0_DLYSDM_S                                               8U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_3_PER                           0x00000300U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_2_PER                           0x00000200U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_1_PER                           0x00000100U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_0_PER                           0x00000000U

// Field:     [6] DLYPHVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD16_1_PER             Internal. Only to be used through TI provided API.
// CKVD16_0_PER             Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_DLYPHVALID                                    0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_M                                  0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_S                                           6U
#define LRFDRFE_MISC0_DLYPHVALID_CKVD16_1_PER                       0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_CKVD16_0_PER                       0x00000000U

// Field:   [5:4] DLYCANCRS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD64_3_PER             Internal. Only to be used through TI provided API.
// CKVD64_2_PER             Internal. Only to be used through TI provided API.
// CKVD64_1_PER             Internal. Only to be used through TI provided API.
// CKVD64_0_PER             Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_DLYCANCRS_W                                            2U
#define LRFDRFE_MISC0_DLYCANCRS_M                                   0x00000030U
#define LRFDRFE_MISC0_DLYCANCRS_S                                            4U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_3_PER                        0x00000030U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_2_PER                        0x00000020U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_1_PER                        0x00000010U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_0_PER                        0x00000000U

// Field:   [3:2] DLYCANFINE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD16_4_PER             Internal. Only to be used through TI provided API.
// CKVD16_3_PER             Internal. Only to be used through TI provided API.
// CKVD16_2_PER             Internal. Only to be used through TI provided API.
// CKVD16_1_PER             Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_DLYCANFINE_W                                           2U
#define LRFDRFE_MISC0_DLYCANFINE_M                                  0x0000000CU
#define LRFDRFE_MISC0_DLYCANFINE_S                                           2U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_4_PER                       0x0000000CU
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_3_PER                       0x00000008U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_2_PER                       0x00000004U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_1_PER                       0x00000000U

// Field:   [1:0] DLYADD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD64_3_PER             Internal. Only to be used through TI provided API.
// CKVD64_2_PER             Internal. Only to be used through TI provided API.
// CKVD64_1_PER             Internal. Only to be used through TI provided API.
// CKVD64_0_PER             Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC0_DLYADD_W                                               2U
#define LRFDRFE_MISC0_DLYADD_M                                      0x00000003U
#define LRFDRFE_MISC0_DLYADD_S                                               0U
#define LRFDRFE_MISC0_DLYADD_CKVD64_3_PER                           0x00000003U
#define LRFDRFE_MISC0_DLYADD_CKVD64_2_PER                           0x00000002U
#define LRFDRFE_MISC0_DLYADD_CKVD64_1_PER                           0x00000001U
#define LRFDRFE_MISC0_DLYADD_CKVD64_0_PER                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MISC1
//
//*****************************************************************************
// Field:    [14] FCDEMCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CKVD64                   Internal. Only to be used through TI provided API.
// CKCD16                   Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_FCDEMCLK                                      0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_M                                    0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_S                                            14U
#define LRFDRFE_MISC1_FCDEMCLK_CKVD64                               0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_CKCD16                               0x00000000U

// Field: [13:12] FCDEMUPD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SDM_XOR_PH_ERR           Internal. Only to be used through TI provided API.
// SDM                      Internal. Only to be used through TI provided API.
// PH_ERR                   Internal. Only to be used through TI provided API.
// DEFAULT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_FCDEMUPD_W                                             2U
#define LRFDRFE_MISC1_FCDEMUPD_M                                    0x00003000U
#define LRFDRFE_MISC1_FCDEMUPD_S                                            12U
#define LRFDRFE_MISC1_FCDEMUPD_SDM_XOR_PH_ERR                       0x00003000U
#define LRFDRFE_MISC1_FCDEMUPD_SDM                                  0x00002000U
#define LRFDRFE_MISC1_FCDEMUPD_PH_ERR                               0x00001000U
#define LRFDRFE_MISC1_FCDEMUPD_DEFAULT                              0x00000000U

// Field:  [11:6] TDCINL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_TDCINL_W                                               6U
#define LRFDRFE_MISC1_TDCINL_M                                      0x00000FC0U
#define LRFDRFE_MISC1_TDCINL_S                                               6U
#define LRFDRFE_MISC1_TDCINL_ONES                                   0x00000FC0U
#define LRFDRFE_MISC1_TDCINL_ZEROS                                  0x00000000U

// Field:     [5] TDCINLCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_TDCINLCTL                                     0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_M                                   0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_S                                            5U
#define LRFDRFE_MISC1_TDCINLCTL_EN                                  0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_DIS                                 0x00000000U

// Field:     [4] PHINIT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// UNKNOWN                  Internal. Only to be used through TI provided API.
// KNOWN                    Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_PHINIT                                        0x00000010U
#define LRFDRFE_MISC1_PHINIT_M                                      0x00000010U
#define LRFDRFE_MISC1_PHINIT_S                                               4U
#define LRFDRFE_MISC1_PHINIT_UNKNOWN                                0x00000010U
#define LRFDRFE_MISC1_PHINIT_KNOWN                                  0x00000000U

// Field:     [3] SDMOOVRCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_SDMOOVRCTL                                    0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_M                                  0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_S                                           3U
#define LRFDRFE_MISC1_SDMOOVRCTL_EN                                 0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_DIS                                0x00000000U

// Field:   [2:0] SDMOOVR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MISC1_SDMOOVR_W                                              3U
#define LRFDRFE_MISC1_SDMOOVR_M                                     0x00000007U
#define LRFDRFE_MISC1_SDMOOVR_S                                              0U
#define LRFDRFE_MISC1_SDMOOVR_ALLONES                               0x00000007U
#define LRFDRFE_MISC1_SDMOOVR_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_LF0
//
//*****************************************************************************
// Field:    [12] KIPREC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HIGH                     Internal. Only to be used through TI provided API.
// LOW                      Internal. Only to be used through TI provided API.
#define LRFDRFE_LF0_KIPREC                                          0x00001000U
#define LRFDRFE_LF0_KIPREC_M                                        0x00001000U
#define LRFDRFE_LF0_KIPREC_S                                                12U
#define LRFDRFE_LF0_KIPREC_HIGH                                     0x00001000U
#define LRFDRFE_LF0_KIPREC_LOW                                      0x00000000U

// Field:  [11:0] KI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_LF0_KI_W                                                    12U
#define LRFDRFE_LF0_KI_M                                            0x00000FFFU
#define LRFDRFE_LF0_KI_S                                                     0U
#define LRFDRFE_LF0_KI_ALLONES                                      0x00000FFFU
#define LRFDRFE_LF0_KI_ALLZEROS                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_LF1
//
//*****************************************************************************
// Field:  [13:0] KP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_LF1_KP_W                                                    14U
#define LRFDRFE_LF1_KP_M                                            0x00003FFFU
#define LRFDRFE_LF1_KP_S                                                     0U
#define LRFDRFE_LF1_KP_ALLONES                                      0x00003FFFU
#define LRFDRFE_LF1_KP_ALLZEROS                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PHEDISC
//
//*****************************************************************************
// Field: [13:10] CNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PHEDISC_CNT_W                                                4U
#define LRFDRFE_PHEDISC_CNT_M                                       0x00003C00U
#define LRFDRFE_PHEDISC_CNT_S                                               10U
#define LRFDRFE_PHEDISC_CNT_ALLONES                                 0x00003C00U
#define LRFDRFE_PHEDISC_CNT_ALLZEROS                                0x00000000U

// Field:   [9:0] THR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PHEDISC_THR_W                                               10U
#define LRFDRFE_PHEDISC_THR_M                                       0x000003FFU
#define LRFDRFE_PHEDISC_THR_S                                                0U
#define LRFDRFE_PHEDISC_THR_ALLONES                                 0x000003FFU
#define LRFDRFE_PHEDISC_THR_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PHINIT
//
//*****************************************************************************
// Field:   [7:0] OFF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PHINIT_OFF_W                                                 8U
#define LRFDRFE_PHINIT_OFF_M                                        0x000000FFU
#define LRFDRFE_PHINIT_OFF_S                                                 0U
#define LRFDRFE_PHINIT_OFF_ALLONES                                  0x000000FFU
#define LRFDRFE_PHINIT_OFF_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLMON0
//
//*****************************************************************************
// Field: [15:14] PHELOLCNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// REFCLK_128_PER           Internal. Only to be used through TI provided API.
// REFCLK_64_PER            Internal. Only to be used through TI provided API.
// REFCLK_32_PER            Internal. Only to be used through TI provided API.
// REFCLK_16_PER            Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLMON0_PHELOLCNT_W                                          2U
#define LRFDRFE_PLLMON0_PHELOLCNT_M                                 0x0000C000U
#define LRFDRFE_PLLMON0_PHELOLCNT_S                                         14U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_128_PER                    0x0000C000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_64_PER                     0x00008000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_32_PER                     0x00004000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_16_PER                     0x00000000U

// Field:  [13:8] PHELOLTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLMON0_PHELOLTHR_W                                          6U
#define LRFDRFE_PLLMON0_PHELOLTHR_M                                 0x00003F00U
#define LRFDRFE_PLLMON0_PHELOLTHR_S                                          8U
#define LRFDRFE_PLLMON0_PHELOLTHR_ALLONES                           0x00003F00U
#define LRFDRFE_PLLMON0_PHELOLTHR_ALLZEROS                          0x00000000U

// Field:   [6:0] FCTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLMON0_FCTHR_W                                              7U
#define LRFDRFE_PLLMON0_FCTHR_M                                     0x0000007FU
#define LRFDRFE_PLLMON0_FCTHR_S                                              0U
#define LRFDRFE_PLLMON0_FCTHR_ALLONES                               0x0000007FU
#define LRFDRFE_PLLMON0_FCTHR_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLMON1
//
//*****************************************************************************
// Field:  [12:8] PHELOCKCNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLMON1_PHELOCKCNT_W                                         5U
#define LRFDRFE_PLLMON1_PHELOCKCNT_M                                0x00001F00U
#define LRFDRFE_PLLMON1_PHELOCKCNT_S                                         8U
#define LRFDRFE_PLLMON1_PHELOCKCNT_ALLONES                          0x00001F00U
#define LRFDRFE_PLLMON1_PHELOCKCNT_ALLZEROS                         0x00000000U

// Field:   [7:0] PHELOCKTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLMON1_PHELOCKTHR_W                                         8U
#define LRFDRFE_PLLMON1_PHELOCKTHR_M                                0x000000FFU
#define LRFDRFE_PLLMON1_PHELOCKTHR_S                                         0U
#define LRFDRFE_PLLMON1_PHELOCKTHR_ALLONES                          0x000000FFU
#define LRFDRFE_PLLMON1_PHELOCKTHR_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MOD0
//
//*****************************************************************************
// Field: [12:11] SCHEME
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TWO_POINT_MOD_FRF        Internal. Only to be used through TI provided API.
// INLOOP_MOD_FRF           Internal. Only to be used through TI provided API.
// INLOOP_MOD_FREF          Internal. Only to be used through TI provided API.
// NC                       Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD0_SCHEME_W                                                2U
#define LRFDRFE_MOD0_SCHEME_M                                       0x00001800U
#define LRFDRFE_MOD0_SCHEME_S                                               11U
#define LRFDRFE_MOD0_SCHEME_TWO_POINT_MOD_FRF                       0x00001800U
#define LRFDRFE_MOD0_SCHEME_INLOOP_MOD_FRF                          0x00001000U
#define LRFDRFE_MOD0_SCHEME_INLOOP_MOD_FREF                         0x00000800U
#define LRFDRFE_MOD0_SCHEME_NC                                      0x00000000U

// Field:  [10:8] SYMSHP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CHIRP                    Internal. Only to be used through TI provided API.
// SHAPEDZIGBEE             Internal. Only to be used through TI provided API.
// PCWSPSK                  Internal. Only to be used through TI provided API.
// ZIGBEE                   Internal. Only to be used through TI provided API.
// SHAPEDFSK                Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD0_SYMSHP_W                                                3U
#define LRFDRFE_MOD0_SYMSHP_M                                       0x00000700U
#define LRFDRFE_MOD0_SYMSHP_S                                                8U
#define LRFDRFE_MOD0_SYMSHP_CHIRP                                   0x00000400U
#define LRFDRFE_MOD0_SYMSHP_SHAPEDZIGBEE                            0x00000300U
#define LRFDRFE_MOD0_SYMSHP_PCWSPSK                                 0x00000200U
#define LRFDRFE_MOD0_SYMSHP_ZIGBEE                                  0x00000100U
#define LRFDRFE_MOD0_SYMSHP_SHAPEDFSK                               0x00000000U

// Field:   [7:6] CANPTHGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// TWO_POW_M_18             Internal. Only to be used through TI provided API.
// TWO_POW_M_17             Internal. Only to be used through TI provided API.
// TWO_POW_M_16             Internal. Only to be used through TI provided API.
// TWO_POW_M_15             Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD0_CANPTHGAIN_W                                            2U
#define LRFDRFE_MOD0_CANPTHGAIN_M                                   0x000000C0U
#define LRFDRFE_MOD0_CANPTHGAIN_S                                            6U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_18                        0x000000C0U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_17                        0x00000080U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_16                        0x00000040U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_15                        0x00000000U

// Field:   [5:4] SHPGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// X8                       Internal. Only to be used through TI provided API.
// X4                       Internal. Only to be used through TI provided API.
// X2                       Internal. Only to be used through TI provided API.
// X1                       Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD0_SHPGAIN_W                                               2U
#define LRFDRFE_MOD0_SHPGAIN_M                                      0x00000030U
#define LRFDRFE_MOD0_SHPGAIN_S                                               4U
#define LRFDRFE_MOD0_SHPGAIN_X8                                     0x00000030U
#define LRFDRFE_MOD0_SHPGAIN_X4                                     0x00000020U
#define LRFDRFE_MOD0_SHPGAIN_X2                                     0x00000010U
#define LRFDRFE_MOD0_SHPGAIN_X1                                     0x00000000U

// Field:   [3:2] INTPFACT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ILLEGAL1                 Internal. Only to be used through TI provided API.
// INTP_BY_32               Internal. Only to be used through TI provided API.
// INTP_BY_16               Internal. Only to be used through TI provided API.
// ILLEGAL0                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD0_INTPFACT_W                                              2U
#define LRFDRFE_MOD0_INTPFACT_M                                     0x0000000CU
#define LRFDRFE_MOD0_INTPFACT_S                                              2U
#define LRFDRFE_MOD0_INTPFACT_ILLEGAL1                              0x0000000CU
#define LRFDRFE_MOD0_INTPFACT_INTP_BY_32                            0x00000008U
#define LRFDRFE_MOD0_INTPFACT_INTP_BY_16                            0x00000004U
#define LRFDRFE_MOD0_INTPFACT_ILLEGAL0                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MOD1
//
//*****************************************************************************
// Field:  [11:0] FOFF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MOD1_FOFF_W                                                 12U
#define LRFDRFE_MOD1_FOFF_M                                         0x00000FFFU
#define LRFDRFE_MOD1_FOFF_S                                                  0U
#define LRFDRFE_MOD1_FOFF_ALLONES                                   0x00000FFFU
#define LRFDRFE_MOD1_FOFF_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX0
//
//*****************************************************************************
// Field:  [15:8] SHP1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX0_SHP1_W                                                  8U
#define LRFDRFE_DTX0_SHP1_M                                         0x0000FF00U
#define LRFDRFE_DTX0_SHP1_S                                                  8U
#define LRFDRFE_DTX0_SHP1_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX0_SHP1_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX0_SHP0_W                                                  8U
#define LRFDRFE_DTX0_SHP0_M                                         0x000000FFU
#define LRFDRFE_DTX0_SHP0_S                                                  0U
#define LRFDRFE_DTX0_SHP0_ALLONES                                   0x000000FFU
#define LRFDRFE_DTX0_SHP0_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX1
//
//*****************************************************************************
// Field:  [15:8] SHP3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX1_SHP3_W                                                  8U
#define LRFDRFE_DTX1_SHP3_M                                         0x0000FF00U
#define LRFDRFE_DTX1_SHP3_S                                                  8U
#define LRFDRFE_DTX1_SHP3_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX1_SHP3_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX1_SHP2_W                                                  8U
#define LRFDRFE_DTX1_SHP2_M                                         0x000000FFU
#define LRFDRFE_DTX1_SHP2_S                                                  0U
#define LRFDRFE_DTX1_SHP2_ALLONES                                   0x000000FFU
#define LRFDRFE_DTX1_SHP2_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX2
//
//*****************************************************************************
// Field:  [15:8] SHP5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX2_SHP5_W                                                  8U
#define LRFDRFE_DTX2_SHP5_M                                         0x0000FF00U
#define LRFDRFE_DTX2_SHP5_S                                                  8U
#define LRFDRFE_DTX2_SHP5_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX2_SHP5_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX2_SHP4_W                                                  8U
#define LRFDRFE_DTX2_SHP4_M                                         0x000000FFU
#define LRFDRFE_DTX2_SHP4_S                                                  0U
#define LRFDRFE_DTX2_SHP4_ALLONES                                   0x000000FFU
#define LRFDRFE_DTX2_SHP4_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX3
//
//*****************************************************************************
// Field:  [15:8] SHP7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX3_SHP7_W                                                  8U
#define LRFDRFE_DTX3_SHP7_M                                         0x0000FF00U
#define LRFDRFE_DTX3_SHP7_S                                                  8U
#define LRFDRFE_DTX3_SHP7_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX3_SHP7_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX3_SHP6_W                                                  8U
#define LRFDRFE_DTX3_SHP6_M                                         0x000000FFU
#define LRFDRFE_DTX3_SHP6_S                                                  0U
#define LRFDRFE_DTX3_SHP6_ALLONES                                   0x000000FFU
#define LRFDRFE_DTX3_SHP6_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX4
//
//*****************************************************************************
// Field:  [15:8] SHP9
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX4_SHP9_W                                                  8U
#define LRFDRFE_DTX4_SHP9_M                                         0x0000FF00U
#define LRFDRFE_DTX4_SHP9_S                                                  8U
#define LRFDRFE_DTX4_SHP9_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX4_SHP9_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP8
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX4_SHP8_W                                                  8U
#define LRFDRFE_DTX4_SHP8_M                                         0x000000FFU
#define LRFDRFE_DTX4_SHP8_S                                                  0U
#define LRFDRFE_DTX4_SHP8_ALLONES                                   0x000000FFU
#define LRFDRFE_DTX4_SHP8_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX5
//
//*****************************************************************************
// Field:  [15:8] SHP11
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX5_SHP11_W                                                 8U
#define LRFDRFE_DTX5_SHP11_M                                        0x0000FF00U
#define LRFDRFE_DTX5_SHP11_S                                                 8U
#define LRFDRFE_DTX5_SHP11_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX5_SHP11_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP10
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX5_SHP10_W                                                 8U
#define LRFDRFE_DTX5_SHP10_M                                        0x000000FFU
#define LRFDRFE_DTX5_SHP10_S                                                 0U
#define LRFDRFE_DTX5_SHP10_ALLONES                                  0x000000FFU
#define LRFDRFE_DTX5_SHP10_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX6
//
//*****************************************************************************
// Field:  [15:8] SHP13
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX6_SHP13_W                                                 8U
#define LRFDRFE_DTX6_SHP13_M                                        0x0000FF00U
#define LRFDRFE_DTX6_SHP13_S                                                 8U
#define LRFDRFE_DTX6_SHP13_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX6_SHP13_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP12
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX6_SHP12_W                                                 8U
#define LRFDRFE_DTX6_SHP12_M                                        0x000000FFU
#define LRFDRFE_DTX6_SHP12_S                                                 0U
#define LRFDRFE_DTX6_SHP12_ALLONES                                  0x000000FFU
#define LRFDRFE_DTX6_SHP12_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX7
//
//*****************************************************************************
// Field:  [15:8] SHP15
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX7_SHP15_W                                                 8U
#define LRFDRFE_DTX7_SHP15_M                                        0x0000FF00U
#define LRFDRFE_DTX7_SHP15_S                                                 8U
#define LRFDRFE_DTX7_SHP15_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX7_SHP15_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP14
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX7_SHP14_W                                                 8U
#define LRFDRFE_DTX7_SHP14_M                                        0x000000FFU
#define LRFDRFE_DTX7_SHP14_S                                                 0U
#define LRFDRFE_DTX7_SHP14_ALLONES                                  0x000000FFU
#define LRFDRFE_DTX7_SHP14_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX8
//
//*****************************************************************************
// Field:  [15:8] SHP17
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX8_SHP17_W                                                 8U
#define LRFDRFE_DTX8_SHP17_M                                        0x0000FF00U
#define LRFDRFE_DTX8_SHP17_S                                                 8U
#define LRFDRFE_DTX8_SHP17_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX8_SHP17_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX8_SHP16_W                                                 8U
#define LRFDRFE_DTX8_SHP16_M                                        0x000000FFU
#define LRFDRFE_DTX8_SHP16_S                                                 0U
#define LRFDRFE_DTX8_SHP16_ALLONES                                  0x000000FFU
#define LRFDRFE_DTX8_SHP16_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX9
//
//*****************************************************************************
// Field:  [15:8] SHP19
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX9_SHP19_W                                                 8U
#define LRFDRFE_DTX9_SHP19_M                                        0x0000FF00U
#define LRFDRFE_DTX9_SHP19_S                                                 8U
#define LRFDRFE_DTX9_SHP19_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX9_SHP19_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP18
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX9_SHP18_W                                                 8U
#define LRFDRFE_DTX9_SHP18_M                                        0x000000FFU
#define LRFDRFE_DTX9_SHP18_S                                                 0U
#define LRFDRFE_DTX9_SHP18_ALLONES                                  0x000000FFU
#define LRFDRFE_DTX9_SHP18_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX10
//
//*****************************************************************************
// Field:  [15:8] SHP21
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX10_SHP21_W                                                8U
#define LRFDRFE_DTX10_SHP21_M                                       0x0000FF00U
#define LRFDRFE_DTX10_SHP21_S                                                8U
#define LRFDRFE_DTX10_SHP21_ALLONES                                 0x0000FF00U
#define LRFDRFE_DTX10_SHP21_ALLZEROS                                0x00000000U

// Field:   [7:0] SHP20
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX10_SHP20_W                                                8U
#define LRFDRFE_DTX10_SHP20_M                                       0x000000FFU
#define LRFDRFE_DTX10_SHP20_S                                                0U
#define LRFDRFE_DTX10_SHP20_ALLONES                                 0x000000FFU
#define LRFDRFE_DTX10_SHP20_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTX11
//
//*****************************************************************************
// Field:  [15:8] SHP23
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX11_SHP23_W                                                8U
#define LRFDRFE_DTX11_SHP23_M                                       0x0000FF00U
#define LRFDRFE_DTX11_SHP23_S                                                8U
#define LRFDRFE_DTX11_SHP23_ALLONES                                 0x0000FF00U
#define LRFDRFE_DTX11_SHP23_ALLZEROS                                0x00000000U

// Field:   [7:0] SHP22
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTX11_SHP22_W                                                8U
#define LRFDRFE_DTX11_SHP22_M                                       0x000000FFU
#define LRFDRFE_DTX11_SHP22_S                                                0U
#define LRFDRFE_DTX11_SHP22_ALLONES                                 0x000000FFU
#define LRFDRFE_DTX11_SHP22_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLM0L
//
//*****************************************************************************
// Field:  [15:2] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM0L_VALLSB_W                                             14U
#define LRFDRFE_PLLM0L_VALLSB_M                                     0x0000FFFCU
#define LRFDRFE_PLLM0L_VALLSB_S                                              2U
#define LRFDRFE_PLLM0L_VALLSB_ALLONES                               0x0000FFFCU
#define LRFDRFE_PLLM0L_VALLSB_ALLZEROS                              0x00000000U

// Field:   [1:0] SPARE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM0L_SPARE0_W                                              2U
#define LRFDRFE_PLLM0L_SPARE0_M                                     0x00000003U
#define LRFDRFE_PLLM0L_SPARE0_S                                              0U
#define LRFDRFE_PLLM0L_SPARE0_ALLONES                               0x00000003U
#define LRFDRFE_PLLM0L_SPARE0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLM0H
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM0H_VALMSB_W                                             16U
#define LRFDRFE_PLLM0H_VALMSB_M                                     0x0000FFFFU
#define LRFDRFE_PLLM0H_VALMSB_S                                              0U
#define LRFDRFE_PLLM0H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDRFE_PLLM0H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLM1L
//
//*****************************************************************************
// Field:  [15:2] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM1L_VALLSB_W                                             14U
#define LRFDRFE_PLLM1L_VALLSB_M                                     0x0000FFFCU
#define LRFDRFE_PLLM1L_VALLSB_S                                              2U
#define LRFDRFE_PLLM1L_VALLSB_ALLONES                               0x0000FFFCU
#define LRFDRFE_PLLM1L_VALLSB_ALLZEROS                              0x00000000U

// Field:   [1:0] SPARE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM1L_SPARE0_W                                              2U
#define LRFDRFE_PLLM1L_SPARE0_M                                     0x00000003U
#define LRFDRFE_PLLM1L_SPARE0_S                                              0U
#define LRFDRFE_PLLM1L_SPARE0_ALLONES                               0x00000003U
#define LRFDRFE_PLLM1L_SPARE0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PLLM1H
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PLLM1H_VALMSB_W                                             16U
#define LRFDRFE_PLLM1H_VALMSB_M                                     0x0000FFFFU
#define LRFDRFE_PLLM1H_VALMSB_S                                              0U
#define LRFDRFE_PLLM1H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDRFE_PLLM1H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CALMCRS
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CALMCRS_VAL_W                                               16U
#define LRFDRFE_CALMCRS_VAL_M                                       0x0000FFFFU
#define LRFDRFE_CALMCRS_VAL_S                                                0U
#define LRFDRFE_CALMCRS_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_CALMCRS_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CALMMID
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CALMMID_VAL_W                                               16U
#define LRFDRFE_CALMMID_VAL_M                                       0x0000FFFFU
#define LRFDRFE_CALMMID_VAL_S                                                0U
#define LRFDRFE_CALMMID_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_CALMMID_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_REFDIV
//
//*****************************************************************************
// Field:  [15:0] LOAD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_REFDIV_LOAD_W                                               16U
#define LRFDRFE_REFDIV_LOAD_M                                       0x0000FFFFU
#define LRFDRFE_REFDIV_LOAD_S                                                0U
#define LRFDRFE_REFDIV_LOAD_ALLONES                                 0x0000FFFFU
#define LRFDRFE_REFDIV_LOAD_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DLOCTL0
//
//*****************************************************************************
// Field:  [10:8] TDCSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// OPEN                     Internal. Only to be used through TI provided API.
// CLOSED                   Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_TDCSTOP_W                                            3U
#define LRFDRFE_DLOCTL0_TDCSTOP_M                                   0x00000700U
#define LRFDRFE_DLOCTL0_TDCSTOP_S                                            8U
#define LRFDRFE_DLOCTL0_TDCSTOP_OPEN                                0x00000100U
#define LRFDRFE_DLOCTL0_TDCSTOP_CLOSED                              0x00000000U

// Field:     [7] DTSTXTAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_DTSTXTAL                                    0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_M                                  0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_S                                           7U
#define LRFDRFE_DLOCTL0_DTSTXTAL_ONE                                0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_ZERO                               0x00000000U

// Field:   [6:4] LOOPUPD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALT                      Internal. Only to be used through TI provided API.
// DEF                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_LOOPUPD_W                                            3U
#define LRFDRFE_DLOCTL0_LOOPUPD_M                                   0x00000070U
#define LRFDRFE_DLOCTL0_LOOPUPD_S                                            4U
#define LRFDRFE_DLOCTL0_LOOPUPD_ALT                                 0x00000010U
#define LRFDRFE_DLOCTL0_LOOPUPD_DEF                                 0x00000000U

// Field:     [3] PH3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// START                    Internal. Only to be used through TI provided API.
// HALT                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_PH3                                         0x00000008U
#define LRFDRFE_DLOCTL0_PH3_M                                       0x00000008U
#define LRFDRFE_DLOCTL0_PH3_S                                                3U
#define LRFDRFE_DLOCTL0_PH3_START                                   0x00000008U
#define LRFDRFE_DLOCTL0_PH3_HALT                                    0x00000000U

// Field:     [2] PH2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// START                    Internal. Only to be used through TI provided API.
// HALT                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_PH2                                         0x00000004U
#define LRFDRFE_DLOCTL0_PH2_M                                       0x00000004U
#define LRFDRFE_DLOCTL0_PH2_S                                                2U
#define LRFDRFE_DLOCTL0_PH2_START                                   0x00000004U
#define LRFDRFE_DLOCTL0_PH2_HALT                                    0x00000000U

// Field:     [1] LOOPMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// OPEN                     Internal. Only to be used through TI provided API.
// CLOSED                   Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_LOOPMODE                                    0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_M                                  0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_S                                           1U
#define LRFDRFE_DLOCTL0_LOOPMODE_OPEN                               0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_CLOSED                             0x00000000U

// Field:     [0] RSTN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACTIVE                   Internal. Only to be used through TI provided API.
// RESET                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL0_RSTN                                        0x00000001U
#define LRFDRFE_DLOCTL0_RSTN_M                                      0x00000001U
#define LRFDRFE_DLOCTL0_RSTN_S                                               0U
#define LRFDRFE_DLOCTL0_RSTN_ACTIVE                                 0x00000001U
#define LRFDRFE_DLOCTL0_RSTN_RESET                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DLOCTL1
//
//*****************************************************************************
// Field:    [15] DCO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_DCO                                         0x00008000U
#define LRFDRFE_DLOCTL1_DCO_M                                       0x00008000U
#define LRFDRFE_DLOCTL1_DCO_S                                               15U
#define LRFDRFE_DLOCTL1_DCO_EN                                      0x00008000U
#define LRFDRFE_DLOCTL1_DCO_DIS                                     0x00000000U

// Field:     [7] FCDEM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_FCDEM                                       0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_M                                     0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_S                                              7U
#define LRFDRFE_DLOCTL1_FCDEM_EN                                    0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_DIS                                   0x00000000U

// Field:     [6] DTSTCKVD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_DTSTCKVD                                    0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_M                                  0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_S                                           6U
#define LRFDRFE_DLOCTL1_DTSTCKVD_ONE                                0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_ZERO                               0x00000000U

// Field:     [5] PHEDISC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_PHEDISC                                     0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_M                                   0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_S                                            5U
#define LRFDRFE_DLOCTL1_PHEDISC_EN                                  0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_DIS                                 0x00000000U

// Field:     [4] PLLMON
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_PLLMON                                      0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_M                                    0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_S                                             4U
#define LRFDRFE_DLOCTL1_PLLMON_EN                                   0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_DIS                                  0x00000000U

// Field:     [3] IIR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_IIR                                         0x00000008U
#define LRFDRFE_DLOCTL1_IIR_M                                       0x00000008U
#define LRFDRFE_DLOCTL1_IIR_S                                                3U
#define LRFDRFE_DLOCTL1_IIR_EN                                      0x00000008U
#define LRFDRFE_DLOCTL1_IIR_DIS                                     0x00000000U

// Field:     [2] MOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_MOD                                         0x00000004U
#define LRFDRFE_DLOCTL1_MOD_M                                       0x00000004U
#define LRFDRFE_DLOCTL1_MOD_S                                                2U
#define LRFDRFE_DLOCTL1_MOD_EN                                      0x00000004U
#define LRFDRFE_DLOCTL1_MOD_DIS                                     0x00000000U

// Field:     [1] MODINIT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACTIVATE                 Internal. Only to be used through TI provided API.
// DEACTIVATE               Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_MODINIT                                     0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_M                                   0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_S                                            1U
#define LRFDRFE_DLOCTL1_MODINIT_ACTIVATE                            0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_DEACTIVATE                          0x00000000U

// Field:     [0] MTDCRSTN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACTIVE                   Internal. Only to be used through TI provided API.
// RESET                    Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOCTL1_MTDCRSTN                                    0x00000001U
#define LRFDRFE_DLOCTL1_MTDCRSTN_M                                  0x00000001U
#define LRFDRFE_DLOCTL1_MTDCRSTN_S                                           0U
#define LRFDRFE_DLOCTL1_MTDCRSTN_ACTIVE                             0x00000001U
#define LRFDRFE_DLOCTL1_MTDCRSTN_RESET                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DCOOVR0
//
//*****************************************************************************
// Field:  [13:8] MIDCODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_MIDCODE_W                                            6U
#define LRFDRFE_DCOOVR0_MIDCODE_M                                   0x00003F00U
#define LRFDRFE_DCOOVR0_MIDCODE_S                                            8U
#define LRFDRFE_DCOOVR0_MIDCODE_ALLONES                             0x00003F00U
#define LRFDRFE_DCOOVR0_MIDCODE_ALLZEROS                            0x00000000U

// Field:   [7:4] CRSCODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_CRSCODE_W                                            4U
#define LRFDRFE_DCOOVR0_CRSCODE_M                                   0x000000F0U
#define LRFDRFE_DCOOVR0_CRSCODE_S                                            4U
#define LRFDRFE_DCOOVR0_CRSCODE_ALLONES                             0x000000F0U
#define LRFDRFE_DCOOVR0_CRSCODE_ALLZEROS                            0x00000000U

// Field:     [3] FINECTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_FINECTL                                     0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_M                                   0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_S                                            3U
#define LRFDRFE_DCOOVR0_FINECTL_EN                                  0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_DIS                                 0x00000000U

// Field:     [2] SDMICTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_SDMICTL                                     0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_M                                   0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_S                                            2U
#define LRFDRFE_DCOOVR0_SDMICTL_EN                                  0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_DIS                                 0x00000000U

// Field:     [1] MIDCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_MIDCTL                                      0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_M                                    0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_S                                             1U
#define LRFDRFE_DCOOVR0_MIDCTL_EN                                   0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_DIS                                  0x00000000U

// Field:     [0] CRSCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR0_CRSCTL                                      0x00000001U
#define LRFDRFE_DCOOVR0_CRSCTL_M                                    0x00000001U
#define LRFDRFE_DCOOVR0_CRSCTL_S                                             0U
#define LRFDRFE_DCOOVR0_CRSCTL_EN                                   0x00000001U
#define LRFDRFE_DCOOVR0_CRSCTL_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DCOOVR1
//
//*****************************************************************************
// Field:  [14:8] FINECODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR1_FINECODE_W                                           7U
#define LRFDRFE_DCOOVR1_FINECODE_M                                  0x00007F00U
#define LRFDRFE_DCOOVR1_FINECODE_S                                           8U
#define LRFDRFE_DCOOVR1_FINECODE_ALLONES                            0x00007F00U
#define LRFDRFE_DCOOVR1_FINECODE_ALLZEROS                           0x00000000U

// Field:   [7:0] SDMICODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DCOOVR1_SDMICODE_W                                           8U
#define LRFDRFE_DCOOVR1_SDMICODE_M                                  0x000000FFU
#define LRFDRFE_DCOOVR1_SDMICODE_S                                           0U
#define LRFDRFE_DCOOVR1_SDMICODE_ALLONES                            0x000000FFU
#define LRFDRFE_DCOOVR1_SDMICODE_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTST
//
//*****************************************************************************
// Field: [14:11] SPARE11
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_SPARE11_W                                               4U
#define LRFDRFE_DTST_SPARE11_M                                      0x00007800U
#define LRFDRFE_DTST_SPARE11_S                                              11U
#define LRFDRFE_DTST_SPARE11_ALLONES                                0x00007800U
#define LRFDRFE_DTST_SPARE11_ALLZEROS                               0x00000000U

// Field:  [10:8] VARTGLDLY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLK_7_PER                Internal. Only to be used through TI provided API.
// CLK_6_PER                Internal. Only to be used through TI provided API.
// CLK_5_PER                Internal. Only to be used through TI provided API.
// CLK_4_PER                Internal. Only to be used through TI provided API.
// CLK_3_PER                Internal. Only to be used through TI provided API.
// CLK_2_PER                Internal. Only to be used through TI provided API.
// CLK_1_PER                Internal. Only to be used through TI provided API.
// CLK_0_PER                Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_VARTGLDLY_W                                             3U
#define LRFDRFE_DTST_VARTGLDLY_M                                    0x00000700U
#define LRFDRFE_DTST_VARTGLDLY_S                                             8U
#define LRFDRFE_DTST_VARTGLDLY_CLK_7_PER                            0x00000700U
#define LRFDRFE_DTST_VARTGLDLY_CLK_6_PER                            0x00000600U
#define LRFDRFE_DTST_VARTGLDLY_CLK_5_PER                            0x00000500U
#define LRFDRFE_DTST_VARTGLDLY_CLK_4_PER                            0x00000400U
#define LRFDRFE_DTST_VARTGLDLY_CLK_3_PER                            0x00000300U
#define LRFDRFE_DTST_VARTGLDLY_CLK_2_PER                            0x00000200U
#define LRFDRFE_DTST_VARTGLDLY_CLK_1_PER                            0x00000100U
#define LRFDRFE_DTST_VARTGLDLY_CLK_0_PER                            0x00000000U

// Field:     [7] REFTGLDLY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLK_1_PER                Internal. Only to be used through TI provided API.
// CLK_0_PER                Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_REFTGLDLY                                      0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_M                                    0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_S                                             7U
#define LRFDRFE_DTST_REFTGLDLY_CLK_1_PER                            0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_CLK_0_PER                            0x00000000U

// Field:     [6] TRNSEQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_TRNSEQ                                         0x00000040U
#define LRFDRFE_DTST_TRNSEQ_M                                       0x00000040U
#define LRFDRFE_DTST_TRNSEQ_S                                                6U
#define LRFDRFE_DTST_TRNSEQ_EN                                      0x00000040U
#define LRFDRFE_DTST_TRNSEQ_DIS                                     0x00000000U

// Field:     [5] SPARE5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_SPARE5                                         0x00000020U
#define LRFDRFE_DTST_SPARE5_M                                       0x00000020U
#define LRFDRFE_DTST_SPARE5_S                                                5U
#define LRFDRFE_DTST_SPARE5_ONE                                     0x00000020U
#define LRFDRFE_DTST_SPARE5_ZERO                                    0x00000000U

// Field:   [4:0] SIG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VAR_NC_15                Internal. Only to be used through TI provided API.
// VAR_NC_14                Internal. Only to be used through TI provided API.
// VAR_NC_13                Internal. Only to be used through TI provided API.
// VAR_NC_12                Internal. Only to be used through TI provided API.
// VAR_NC_11                Internal. Only to be used through TI provided API.
// VAR_LOOP_UPD_FINECODE    Internal. Only to be used through TI provided API.
// VAR_LOCK_FINECODE        Internal. Only to be used through TI provided API.
// VAR_MPX_CAN              Internal. Only to be used through TI provided API.
// VAR_TDCSTOP_STATUS_TDC   Internal. Only to be used through TI provided API.
// VAR_TDCSTOP_PHERR        Internal. Only to be used through TI provided API.
// VAR_PH_COMP_PHERR_TDCSTOPInternal. Only to be used through TI provided API.
// VAR_PH_TDCCORR           Internal. Only to be used through TI provided API.
// VAR_PH_RAW               Internal. Only to be used through TI provided API.
// VAR_PHERR_LOWER          Internal. Only to be used through TI provided API.
// VAR_PHERR_UPPER          Internal. Only to be used through TI provided API.
// VAR_NC_0                 Internal. Only to be used through TI provided API.
// REF_NC_15                Internal. Only to be used through TI provided API.
// REF_NC_14                Internal. Only to be used through TI provided API.
// REF_NC_13                Internal. Only to be used through TI provided API.
// REF_NC_12                Internal. Only to be used through TI provided API.
// REF_NC_11                Internal. Only to be used through TI provided API.
// REF_NC_10                Internal. Only to be used through TI provided API.
// REF_NC_9                 Internal. Only to be used through TI provided API.
// REF_NC_8                 Internal. Only to be used through TI provided API.
// REF_NC_7                 Internal. Only to be used through TI provided API.
// REF_NC_6                 Internal. Only to be used through TI provided API.
// REF_NC_5                 Internal. Only to be used through TI provided API.
// REF_NC_4                 Internal. Only to be used through TI provided API.
// REF_NC_3                 Internal. Only to be used through TI provided API.
// REF_FERR_MAG             Internal. Only to be used through TI provided API.
// REF_FSMCAL               Internal. Only to be used through TI provided API.
// REF_NC_0                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTST_SIG_W                                                   5U
#define LRFDRFE_DTST_SIG_M                                          0x0000001FU
#define LRFDRFE_DTST_SIG_S                                                   0U
#define LRFDRFE_DTST_SIG_VAR_NC_15                                  0x0000001FU
#define LRFDRFE_DTST_SIG_VAR_NC_14                                  0x0000001EU
#define LRFDRFE_DTST_SIG_VAR_NC_13                                  0x0000001DU
#define LRFDRFE_DTST_SIG_VAR_NC_12                                  0x0000001CU
#define LRFDRFE_DTST_SIG_VAR_NC_11                                  0x0000001BU
#define LRFDRFE_DTST_SIG_VAR_LOOP_UPD_FINECODE                      0x0000001AU
#define LRFDRFE_DTST_SIG_VAR_LOCK_FINECODE                          0x00000019U
#define LRFDRFE_DTST_SIG_VAR_MPX_CAN                                0x00000018U
#define LRFDRFE_DTST_SIG_VAR_TDCSTOP_STATUS_TDC                     0x00000017U
#define LRFDRFE_DTST_SIG_VAR_TDCSTOP_PHERR                          0x00000016U
#define LRFDRFE_DTST_SIG_VAR_PH_COMP_PHERR_TDCSTOP                  0x00000015U
#define LRFDRFE_DTST_SIG_VAR_PH_TDCCORR                             0x00000014U
#define LRFDRFE_DTST_SIG_VAR_PH_RAW                                 0x00000013U
#define LRFDRFE_DTST_SIG_VAR_PHERR_LOWER                            0x00000012U
#define LRFDRFE_DTST_SIG_VAR_PHERR_UPPER                            0x00000011U
#define LRFDRFE_DTST_SIG_VAR_NC_0                                   0x00000010U
#define LRFDRFE_DTST_SIG_REF_NC_15                                  0x0000000FU
#define LRFDRFE_DTST_SIG_REF_NC_14                                  0x0000000EU
#define LRFDRFE_DTST_SIG_REF_NC_13                                  0x0000000DU
#define LRFDRFE_DTST_SIG_REF_NC_12                                  0x0000000CU
#define LRFDRFE_DTST_SIG_REF_NC_11                                  0x0000000BU
#define LRFDRFE_DTST_SIG_REF_NC_10                                  0x0000000AU
#define LRFDRFE_DTST_SIG_REF_NC_9                                   0x00000009U
#define LRFDRFE_DTST_SIG_REF_NC_8                                   0x00000008U
#define LRFDRFE_DTST_SIG_REF_NC_7                                   0x00000007U
#define LRFDRFE_DTST_SIG_REF_NC_6                                   0x00000006U
#define LRFDRFE_DTST_SIG_REF_NC_5                                   0x00000005U
#define LRFDRFE_DTST_SIG_REF_NC_4                                   0x00000004U
#define LRFDRFE_DTST_SIG_REF_NC_3                                   0x00000003U
#define LRFDRFE_DTST_SIG_REF_FERR_MAG                               0x00000002U
#define LRFDRFE_DTST_SIG_REF_FSMCAL                                 0x00000001U
#define LRFDRFE_DTST_SIG_REF_NC_0                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DLOEV
//
//*****************************************************************************
// Field:     [7] LOCK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOEV_LOCK                                          0x00000080U
#define LRFDRFE_DLOEV_LOCK_M                                        0x00000080U
#define LRFDRFE_DLOEV_LOCK_S                                                 7U
#define LRFDRFE_DLOEV_LOCK_ONE                                      0x00000080U
#define LRFDRFE_DLOEV_LOCK_ZERO                                     0x00000000U

// Field:     [6] LOL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOEV_LOL                                           0x00000040U
#define LRFDRFE_DLOEV_LOL_M                                         0x00000040U
#define LRFDRFE_DLOEV_LOL_S                                                  6U
#define LRFDRFE_DLOEV_LOL_ONE                                       0x00000040U
#define LRFDRFE_DLOEV_LOL_ZERO                                      0x00000000U

// Field:     [5] FCABVTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOEV_FCABVTHR                                      0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_M                                    0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_S                                             5U
#define LRFDRFE_DLOEV_FCABVTHR_ONE                                  0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_ZERO                                 0x00000000U

// Field:     [4] FCBLWTHR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOEV_FCBLWTHR                                      0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_M                                    0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_S                                             4U
#define LRFDRFE_DLOEV_FCBLWTHR_ONE                                  0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_ZERO                                 0x00000000U

// Field:   [3:0] STATE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DLOEV_STATE_W                                                4U
#define LRFDRFE_DLOEV_STATE_M                                       0x0000000FU
#define LRFDRFE_DLOEV_STATE_S                                                0U
#define LRFDRFE_DLOEV_STATE_ALLONES                                 0x0000000FU
#define LRFDRFE_DLOEV_STATE_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DTSTRD
//
//*****************************************************************************
// Field:  [15:0] DATA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DTSTRD_DATA_W                                               16U
#define LRFDRFE_DTSTRD_DATA_M                                       0x0000FFFFU
#define LRFDRFE_DTSTRD_DATA_S                                                0U
#define LRFDRFE_DTSTRD_DATA_ALLONES                                 0x0000FFFFU
#define LRFDRFE_DTSTRD_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_FDCOSPANLSB
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_FDCOSPANLSB_VAL_W                                           16U
#define LRFDRFE_FDCOSPANLSB_VAL_M                                   0x0000FFFFU
#define LRFDRFE_FDCOSPANLSB_VAL_S                                            0U
#define LRFDRFE_FDCOSPANLSB_VAL_ALLONES                             0x0000FFFFU
#define LRFDRFE_FDCOSPANLSB_VAL_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_FDCOSPANMSB
//
//*****************************************************************************
// Field:   [2:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_FDCOSPANMSB_VAL_W                                            3U
#define LRFDRFE_FDCOSPANMSB_VAL_M                                   0x00000007U
#define LRFDRFE_FDCOSPANMSB_VAL_S                                            0U
#define LRFDRFE_FDCOSPANMSB_VAL_ALLONES                             0x00000007U
#define LRFDRFE_FDCOSPANMSB_VAL_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TDCCAL
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TDCCAL_VAL_W                                                16U
#define LRFDRFE_TDCCAL_VAL_M                                        0x0000FFFFU
#define LRFDRFE_TDCCAL_VAL_S                                                 0U
#define LRFDRFE_TDCCAL_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_TDCCAL_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_CALRES
//
//*****************************************************************************
// Field:   [9:4] MIDCODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CALRES_MIDCODE_W                                             6U
#define LRFDRFE_CALRES_MIDCODE_M                                    0x000003F0U
#define LRFDRFE_CALRES_MIDCODE_S                                             4U
#define LRFDRFE_CALRES_MIDCODE_ALLONES                              0x000003F0U
#define LRFDRFE_CALRES_MIDCODE_ALLZEROS                             0x00000000U

// Field:   [3:0] CRSCODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_CALRES_CRSCODE_W                                             4U
#define LRFDRFE_CALRES_CRSCODE_M                                    0x0000000FU
#define LRFDRFE_CALRES_CRSCODE_S                                             0U
#define LRFDRFE_CALRES_CRSCODE_ALLONES                              0x0000000FU
#define LRFDRFE_CALRES_CRSCODE_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_GPI
//
//*****************************************************************************
// Field:     [7] GPI7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI7                                            0x00000080U
#define LRFDRFE_GPI_GPI7_M                                          0x00000080U
#define LRFDRFE_GPI_GPI7_S                                                   7U
#define LRFDRFE_GPI_GPI7_ONE                                        0x00000080U
#define LRFDRFE_GPI_GPI7_ZERO                                       0x00000000U

// Field:     [6] GPI6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI6                                            0x00000040U
#define LRFDRFE_GPI_GPI6_M                                          0x00000040U
#define LRFDRFE_GPI_GPI6_S                                                   6U
#define LRFDRFE_GPI_GPI6_ONE                                        0x00000040U
#define LRFDRFE_GPI_GPI6_ZERO                                       0x00000000U

// Field:     [5] GPI5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI5                                            0x00000020U
#define LRFDRFE_GPI_GPI5_M                                          0x00000020U
#define LRFDRFE_GPI_GPI5_S                                                   5U
#define LRFDRFE_GPI_GPI5_ONE                                        0x00000020U
#define LRFDRFE_GPI_GPI5_ZERO                                       0x00000000U

// Field:     [4] GPI4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI4                                            0x00000010U
#define LRFDRFE_GPI_GPI4_M                                          0x00000010U
#define LRFDRFE_GPI_GPI4_S                                                   4U
#define LRFDRFE_GPI_GPI4_ONE                                        0x00000010U
#define LRFDRFE_GPI_GPI4_ZERO                                       0x00000000U

// Field:     [3] GPI3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI3                                            0x00000008U
#define LRFDRFE_GPI_GPI3_M                                          0x00000008U
#define LRFDRFE_GPI_GPI3_S                                                   3U
#define LRFDRFE_GPI_GPI3_ONE                                        0x00000008U
#define LRFDRFE_GPI_GPI3_ZERO                                       0x00000000U

// Field:     [2] GPI2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI2                                            0x00000004U
#define LRFDRFE_GPI_GPI2_M                                          0x00000004U
#define LRFDRFE_GPI_GPI2_S                                                   2U
#define LRFDRFE_GPI_GPI2_ONE                                        0x00000004U
#define LRFDRFE_GPI_GPI2_ZERO                                       0x00000000U

// Field:     [1] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI1                                            0x00000002U
#define LRFDRFE_GPI_GPI1_M                                          0x00000002U
#define LRFDRFE_GPI_GPI1_S                                                   1U
#define LRFDRFE_GPI_GPI1_ONE                                        0x00000002U
#define LRFDRFE_GPI_GPI1_ZERO                                       0x00000000U

// Field:     [0] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPI_GPI0                                            0x00000001U
#define LRFDRFE_GPI_GPI0_M                                          0x00000001U
#define LRFDRFE_GPI_GPI0_S                                                   0U
#define LRFDRFE_GPI_GPI0_ONE                                        0x00000001U
#define LRFDRFE_GPI_GPI0_ZERO                                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MATHACCELIN
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MATHACCELIN_VAL_W                                           16U
#define LRFDRFE_MATHACCELIN_VAL_M                                   0x0000FFFFU
#define LRFDRFE_MATHACCELIN_VAL_S                                            0U
#define LRFDRFE_MATHACCELIN_VAL_ALLONES                             0x0000FFFFU
#define LRFDRFE_MATHACCELIN_VAL_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_LIN2LOGOUT
//
//*****************************************************************************
// Field:   [6:0] LOGVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_LIN2LOGOUT_LOGVAL_W                                          7U
#define LRFDRFE_LIN2LOGOUT_LOGVAL_M                                 0x0000007FU
#define LRFDRFE_LIN2LOGOUT_LOGVAL_S                                          0U
#define LRFDRFE_LIN2LOGOUT_LOGVAL_ALLONES                           0x0000007FU
#define LRFDRFE_LIN2LOGOUT_LOGVAL_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVBY3OUT
//
//*****************************************************************************
// Field:   [3:0] DIV3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVBY3OUT_DIV3_W                                             4U
#define LRFDRFE_DIVBY3OUT_DIV3_M                                    0x0000000FU
#define LRFDRFE_DIVBY3OUT_DIV3_S                                             0U
#define LRFDRFE_DIVBY3OUT_DIV3_ALLONES                              0x0000000FU
#define LRFDRFE_DIVBY3OUT_DIV3_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TIMCTL
//
//*****************************************************************************
// Field:  [13:8] CPTSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_CPTSRC_W                                              6U
#define LRFDRFE_TIMCTL_CPTSRC_M                                     0x00003F00U
#define LRFDRFE_TIMCTL_CPTSRC_S                                              8U
#define LRFDRFE_TIMCTL_CPTSRC_ALLONES                               0x00003F00U
#define LRFDRFE_TIMCTL_CPTSRC_ALLZEROS                              0x00000000U

// Field:     [7] CPTCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_CPTCTL                                       0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_M                                     0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_S                                              7U
#define LRFDRFE_TIMCTL_CPTCTL_EN                                    0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_DIS                                   0x00000000U

// Field:   [6:5] CNTRSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FREF                     Internal. Only to be used through TI provided API.
// MAGN1                    Internal. Only to be used through TI provided API.
// MAGN0                    Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_CNTRSRC_W                                             2U
#define LRFDRFE_TIMCTL_CNTRSRC_M                                    0x00000060U
#define LRFDRFE_TIMCTL_CNTRSRC_S                                             5U
#define LRFDRFE_TIMCTL_CNTRSRC_FREF                                 0x00000060U
#define LRFDRFE_TIMCTL_CNTRSRC_MAGN1                                0x00000040U
#define LRFDRFE_TIMCTL_CNTRSRC_MAGN0                                0x00000020U
#define LRFDRFE_TIMCTL_CNTRSRC_CLK                                  0x00000000U

// Field:     [4] CNTRCLR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_CNTRCLR                                      0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_M                                    0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_S                                             4U
#define LRFDRFE_TIMCTL_CNTRCLR_ONE                                  0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_ZERO                                 0x00000000U

// Field:     [3] CNTRCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_CNTRCTL                                      0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_M                                    0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_S                                             3U
#define LRFDRFE_TIMCTL_CNTRCTL_EN                                   0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_DIS                                  0x00000000U

// Field:   [2:1] TIMSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FREF                     Internal. Only to be used through TI provided API.
// MAGN1                    Internal. Only to be used through TI provided API.
// MAGN0                    Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_TIMSRC_W                                              2U
#define LRFDRFE_TIMCTL_TIMSRC_M                                     0x00000006U
#define LRFDRFE_TIMCTL_TIMSRC_S                                              1U
#define LRFDRFE_TIMCTL_TIMSRC_FREF                                  0x00000006U
#define LRFDRFE_TIMCTL_TIMSRC_MAGN1                                 0x00000004U
#define LRFDRFE_TIMCTL_TIMSRC_MAGN0                                 0x00000002U
#define LRFDRFE_TIMCTL_TIMSRC_CLK                                   0x00000000U

// Field:     [0] TIMCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCTL_TIMCTL                                       0x00000001U
#define LRFDRFE_TIMCTL_TIMCTL_M                                     0x00000001U
#define LRFDRFE_TIMCTL_TIMCTL_S                                              0U
#define LRFDRFE_TIMCTL_TIMCTL_EN                                    0x00000001U
#define LRFDRFE_TIMCTL_TIMCTL_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TIMINC
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMINC_VAL_W                                                16U
#define LRFDRFE_TIMINC_VAL_M                                        0x0000FFFFU
#define LRFDRFE_TIMINC_VAL_S                                                 0U
#define LRFDRFE_TIMINC_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_TIMINC_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TIMPER
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMPER_VAL_W                                                16U
#define LRFDRFE_TIMPER_VAL_M                                        0x0000FFFFU
#define LRFDRFE_TIMPER_VAL_S                                                 0U
#define LRFDRFE_TIMPER_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_TIMPER_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TIMCNT
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCNT_VAL_W                                                16U
#define LRFDRFE_TIMCNT_VAL_M                                        0x0000FFFFU
#define LRFDRFE_TIMCNT_VAL_S                                                 0U
#define LRFDRFE_TIMCNT_VAL_ALLONES                                  0x0000FFFFU
#define LRFDRFE_TIMCNT_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TIMCAPT
//
//*****************************************************************************
// Field:  [15:0] VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TIMCAPT_VALUE_W                                             16U
#define LRFDRFE_TIMCAPT_VALUE_M                                     0x0000FFFFU
#define LRFDRFE_TIMCAPT_VALUE_S                                              0U
#define LRFDRFE_TIMCAPT_VALUE_ALLONES                               0x0000FFFFU
#define LRFDRFE_TIMCAPT_VALUE_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TRCCTRL
//
//*****************************************************************************
// Field:     [0] SEND
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCCTRL_SEND                                        0x00000001U
#define LRFDRFE_TRCCTRL_SEND_M                                      0x00000001U
#define LRFDRFE_TRCCTRL_SEND_S                                               0U
#define LRFDRFE_TRCCTRL_SEND_ONE                                    0x00000001U
#define LRFDRFE_TRCCTRL_SEND_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TRCSTAT
//
//*****************************************************************************
// Field:     [0] BUSY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCSTAT_BUSY                                        0x00000001U
#define LRFDRFE_TRCSTAT_BUSY_M                                      0x00000001U
#define LRFDRFE_TRCSTAT_BUSY_S                                               0U
#define LRFDRFE_TRCSTAT_BUSY_ONE                                    0x00000001U
#define LRFDRFE_TRCSTAT_BUSY_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TRCCMD
//
//*****************************************************************************
// Field:   [9:8] PARCNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCCMD_PARCNT_W                                              2U
#define LRFDRFE_TRCCMD_PARCNT_M                                     0x00000300U
#define LRFDRFE_TRCCMD_PARCNT_S                                              8U
#define LRFDRFE_TRCCMD_PARCNT_ALLONES                               0x00000300U
#define LRFDRFE_TRCCMD_PARCNT_ALLZEROS                              0x00000000U

// Field:   [7:0] PKTHDR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCCMD_PKTHDR_W                                              8U
#define LRFDRFE_TRCCMD_PKTHDR_M                                     0x000000FFU
#define LRFDRFE_TRCCMD_PKTHDR_S                                              0U
#define LRFDRFE_TRCCMD_PKTHDR_ALLONES                               0x000000FFU
#define LRFDRFE_TRCCMD_PKTHDR_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TRCPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCPAR0_VAL_W                                               16U
#define LRFDRFE_TRCPAR0_VAL_M                                       0x0000FFFFU
#define LRFDRFE_TRCPAR0_VAL_S                                                0U
#define LRFDRFE_TRCPAR0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_TRCPAR0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_TRCPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_TRCPAR1_VAL_W                                               16U
#define LRFDRFE_TRCPAR1_VAL_M                                       0x0000FFFFU
#define LRFDRFE_TRCPAR1_VAL_S                                                0U
#define LRFDRFE_TRCPAR1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDRFE_TRCPAR1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_GPOCTL
//
//*****************************************************************************
// Field:    [15] SEL7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL7                                         0x00008000U
#define LRFDRFE_GPOCTL_SEL7_M                                       0x00008000U
#define LRFDRFE_GPOCTL_SEL7_S                                               15U
#define LRFDRFE_GPOCTL_SEL7_HW                                      0x00008000U
#define LRFDRFE_GPOCTL_SEL7_SW                                      0x00000000U

// Field:    [14] SEL6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL6                                         0x00004000U
#define LRFDRFE_GPOCTL_SEL6_M                                       0x00004000U
#define LRFDRFE_GPOCTL_SEL6_S                                               14U
#define LRFDRFE_GPOCTL_SEL6_HW                                      0x00004000U
#define LRFDRFE_GPOCTL_SEL6_SW                                      0x00000000U

// Field:    [13] SEL5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL5                                         0x00002000U
#define LRFDRFE_GPOCTL_SEL5_M                                       0x00002000U
#define LRFDRFE_GPOCTL_SEL5_S                                               13U
#define LRFDRFE_GPOCTL_SEL5_HW                                      0x00002000U
#define LRFDRFE_GPOCTL_SEL5_SW                                      0x00000000U

// Field:    [12] SEL4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL4                                         0x00001000U
#define LRFDRFE_GPOCTL_SEL4_M                                       0x00001000U
#define LRFDRFE_GPOCTL_SEL4_S                                               12U
#define LRFDRFE_GPOCTL_SEL4_HW                                      0x00001000U
#define LRFDRFE_GPOCTL_SEL4_SW                                      0x00000000U

// Field:    [11] SEL3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL3                                         0x00000800U
#define LRFDRFE_GPOCTL_SEL3_M                                       0x00000800U
#define LRFDRFE_GPOCTL_SEL3_S                                               11U
#define LRFDRFE_GPOCTL_SEL3_HW                                      0x00000800U
#define LRFDRFE_GPOCTL_SEL3_SW                                      0x00000000U

// Field:    [10] SEL2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL2                                         0x00000400U
#define LRFDRFE_GPOCTL_SEL2_M                                       0x00000400U
#define LRFDRFE_GPOCTL_SEL2_S                                               10U
#define LRFDRFE_GPOCTL_SEL2_HW                                      0x00000400U
#define LRFDRFE_GPOCTL_SEL2_SW                                      0x00000000U

// Field:     [9] SEL1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL1                                         0x00000200U
#define LRFDRFE_GPOCTL_SEL1_M                                       0x00000200U
#define LRFDRFE_GPOCTL_SEL1_S                                                9U
#define LRFDRFE_GPOCTL_SEL1_HW                                      0x00000200U
#define LRFDRFE_GPOCTL_SEL1_SW                                      0x00000000U

// Field:     [8] SEL0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// HW                       Internal. Only to be used through TI provided API.
// SW                       Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_SEL0                                         0x00000100U
#define LRFDRFE_GPOCTL_SEL0_M                                       0x00000100U
#define LRFDRFE_GPOCTL_SEL0_S                                                8U
#define LRFDRFE_GPOCTL_SEL0_HW                                      0x00000100U
#define LRFDRFE_GPOCTL_SEL0_SW                                      0x00000000U

// Field:     [7] GPO7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO7                                         0x00000080U
#define LRFDRFE_GPOCTL_GPO7_M                                       0x00000080U
#define LRFDRFE_GPOCTL_GPO7_S                                                7U
#define LRFDRFE_GPOCTL_GPO7_ONE                                     0x00000080U
#define LRFDRFE_GPOCTL_GPO7_ZERO                                    0x00000000U

// Field:     [6] GPO6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO6                                         0x00000040U
#define LRFDRFE_GPOCTL_GPO6_M                                       0x00000040U
#define LRFDRFE_GPOCTL_GPO6_S                                                6U
#define LRFDRFE_GPOCTL_GPO6_ONE                                     0x00000040U
#define LRFDRFE_GPOCTL_GPO6_ZERO                                    0x00000000U

// Field:     [5] GPO5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO5                                         0x00000020U
#define LRFDRFE_GPOCTL_GPO5_M                                       0x00000020U
#define LRFDRFE_GPOCTL_GPO5_S                                                5U
#define LRFDRFE_GPOCTL_GPO5_ONE                                     0x00000020U
#define LRFDRFE_GPOCTL_GPO5_ZERO                                    0x00000000U

// Field:     [4] GPO4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO4                                         0x00000010U
#define LRFDRFE_GPOCTL_GPO4_M                                       0x00000010U
#define LRFDRFE_GPOCTL_GPO4_S                                                4U
#define LRFDRFE_GPOCTL_GPO4_ONE                                     0x00000010U
#define LRFDRFE_GPOCTL_GPO4_ZERO                                    0x00000000U

// Field:     [3] GPO3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO3                                         0x00000008U
#define LRFDRFE_GPOCTL_GPO3_M                                       0x00000008U
#define LRFDRFE_GPOCTL_GPO3_S                                                3U
#define LRFDRFE_GPOCTL_GPO3_ONE                                     0x00000008U
#define LRFDRFE_GPOCTL_GPO3_ZERO                                    0x00000000U

// Field:     [2] GPO2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO2                                         0x00000004U
#define LRFDRFE_GPOCTL_GPO2_M                                       0x00000004U
#define LRFDRFE_GPOCTL_GPO2_S                                                2U
#define LRFDRFE_GPOCTL_GPO2_ONE                                     0x00000004U
#define LRFDRFE_GPOCTL_GPO2_ZERO                                    0x00000000U

// Field:     [1] GPO1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO1                                         0x00000002U
#define LRFDRFE_GPOCTL_GPO1_M                                       0x00000002U
#define LRFDRFE_GPOCTL_GPO1_S                                                1U
#define LRFDRFE_GPOCTL_GPO1_ONE                                     0x00000002U
#define LRFDRFE_GPOCTL_GPO1_ZERO                                    0x00000000U

// Field:     [0] GPO0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_GPOCTL_GPO0                                         0x00000001U
#define LRFDRFE_GPOCTL_GPO0_M                                       0x00000001U
#define LRFDRFE_GPOCTL_GPO0_S                                                0U
#define LRFDRFE_GPOCTL_GPO0_ONE                                     0x00000001U
#define LRFDRFE_GPOCTL_GPO0_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_ANAISOCTL
//
//*****************************************************************************
// Field:     [4] ADCDIGRSTN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACTIVE                   Internal. Only to be used through TI provided API.
// RESET                    Internal. Only to be used through TI provided API.
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN                                0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_M                              0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_S                                       4U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_ACTIVE                         0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_RESET                          0x00000000U

// Field:     [3] IFADC2SVTISO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ISOLATE                  Internal. Only to be used through TI provided API.
// CONNECT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO                              0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_M                            0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_S                                     3U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_ISOLATE                      0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_CONNECT                      0x00000000U

// Field:     [2] DIV2IFADCISO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ISOLATE                  Internal. Only to be used through TI provided API.
// CONNECT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO                              0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_M                            0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_S                                     2U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_ISOLATE                      0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_CONNECT                      0x00000000U

// Field:     [1] MTDC2SVTISO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ISOLATE                  Internal. Only to be used through TI provided API.
// CONNECT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO                               0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_M                             0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_S                                      1U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_ISOLATE                       0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_CONNECT                       0x00000000U

// Field:     [0] DIV2MTDCISO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ISOLATE                  Internal. Only to be used through TI provided API.
// CONNECT                  Internal. Only to be used through TI provided API.
#define LRFDRFE_ANAISOCTL_DIV2MTDCISO                               0x00000001U
#define LRFDRFE_ANAISOCTL_DIV2MTDCISO_M                             0x00000001U
#define LRFDRFE_ANAISOCTL_DIV2MTDCISO_S                                      0U
#define LRFDRFE_ANAISOCTL_DIV2MTDCISO_ISOLATE                       0x00000001U
#define LRFDRFE_ANAISOCTL_DIV2MTDCISO_CONNECT                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVCTL
//
//*****************************************************************************
// Field:    [15] DIV2PH180
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_DIV2PH180                                    0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_M                                  0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_S                                          15U
#define LRFDRFE_DIVCTL_DIV2PH180_EN                                 0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_DIS                                0x00000000U

// Field:    [14] DIV2PH0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_DIV2PH0                                      0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_M                                    0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_S                                            14U
#define LRFDRFE_DIVCTL_DIV2PH0_EN                                   0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_DIS                                  0x00000000U

// Field:    [13] DIV2PH270
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_DIV2PH270                                    0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_M                                  0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_S                                          13U
#define LRFDRFE_DIVCTL_DIV2PH270_EN                                 0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_DIS                                0x00000000U

// Field:    [12] DIV2PH90
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_DIV2PH90                                     0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_M                                   0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_S                                           12U
#define LRFDRFE_DIVCTL_DIV2PH90_EN                                  0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_DIS                                 0x00000000U

// Field:    [11] SPARE11
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_SPARE11                                      0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_M                                    0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_S                                            11U
#define LRFDRFE_DIVCTL_SPARE11_ONE                                  0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_ZERO                                 0x00000000U

// Field:    [10] S1G20DBMMUX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DISABLE                  Internal. Only to be used through TI provided API.
// ENABLEN                  Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_S1G20DBMMUX                                  0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_M                                0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_S                                        10U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_DISABLE                          0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_ENABLEN                          0x00000000U

// Field:     [9] ADCDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_ADCDIV                                       0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_M                                     0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_S                                              9U
#define LRFDRFE_DIVCTL_ADCDIV_EN                                    0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_DIS                                   0x00000000U

// Field:     [8] ENSYNTH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_ENSYNTH                                      0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_M                                    0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_S                                             8U
#define LRFDRFE_DIVCTL_ENSYNTH_EN                                   0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_DIS                                  0x00000000U

// Field:     [7] TXPH18020DBMDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV                              0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_M                            0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_S                                     7U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_EN                           0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_DIS                          0x00000000U

// Field:     [6] TXPH020DBMDIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_TXPH020DBMDIV                                0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_M                              0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_S                                       6U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_EN                             0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_DIS                            0x00000000U

// Field:     [5] TXPH180DIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_TXPH180DIV                                   0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_M                                 0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_S                                          5U
#define LRFDRFE_DIVCTL_TXPH180DIV_EN                                0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_DIS                               0x00000000U

// Field:     [4] TXPH0DIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_TXPH0DIV                                     0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_M                                   0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_S                                            4U
#define LRFDRFE_DIVCTL_TXPH0DIV_EN                                  0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_DIS                                 0x00000000U

// Field:     [3] RXPH90DIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_RXPH90DIV                                    0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_M                                  0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_S                                           3U
#define LRFDRFE_DIVCTL_RXPH90DIV_EN                                 0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_DIS                                0x00000000U

// Field:     [2] RXPH0DIV
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_RXPH0DIV                                     0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_M                                   0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_S                                            2U
#define LRFDRFE_DIVCTL_RXPH0DIV_EN                                  0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_DIS                                 0x00000000U

// Field:     [1] Spare1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_SPARE1                                       0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_M                                     0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_S                                              1U
#define LRFDRFE_DIVCTL_SPARE1_ONE                                   0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_ZERO                                  0x00000000U

// Field:     [0] EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVCTL_EN                                           0x00000001U
#define LRFDRFE_DIVCTL_EN_M                                         0x00000001U
#define LRFDRFE_DIVCTL_EN_S                                                  0U
#define LRFDRFE_DIVCTL_EN_ON                                        0x00000001U
#define LRFDRFE_DIVCTL_EN_OFF                                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RXCTRL
//
//*****************************************************************************
// Field:    [12] SPARE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDRFE_RXCTRL_SPARE                                        0x00001000U
#define LRFDRFE_RXCTRL_SPARE_M                                      0x00001000U
#define LRFDRFE_RXCTRL_SPARE_S                                              12U
#define LRFDRFE_RXCTRL_SPARE_ONE                                    0x00001000U
#define LRFDRFE_RXCTRL_SPARE_ZERO                                   0x00000000U

// Field:  [11:9] ATTN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// _21DB                    Internal. Only to be used through TI provided API.
// _18DB                    Internal. Only to be used through TI provided API.
// _15DB                    Internal. Only to be used through TI provided API.
// _12DB                    Internal. Only to be used through TI provided API.
// _9DB                     Internal. Only to be used through TI provided API.
// _6DB                     Internal. Only to be used through TI provided API.
// _3DB                     Internal. Only to be used through TI provided API.
// NOATT                    Internal. Only to be used through TI provided API.
#define LRFDRFE_RXCTRL_ATTN_W                                                3U
#define LRFDRFE_RXCTRL_ATTN_M                                       0x00000E00U
#define LRFDRFE_RXCTRL_ATTN_S                                                9U
#define LRFDRFE_RXCTRL_ATTN__21DB                                   0x00000E00U
#define LRFDRFE_RXCTRL_ATTN__18DB                                   0x00000C00U
#define LRFDRFE_RXCTRL_ATTN__15DB                                   0x00000A00U
#define LRFDRFE_RXCTRL_ATTN__12DB                                   0x00000800U
#define LRFDRFE_RXCTRL_ATTN__9DB                                    0x00000600U
#define LRFDRFE_RXCTRL_ATTN__6DB                                    0x00000400U
#define LRFDRFE_RXCTRL_ATTN__3DB                                    0x00000200U
#define LRFDRFE_RXCTRL_ATTN_NOATT                                   0x00000000U

// Field:   [8:4] IFAMPGC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN3DB                   Internal. Only to be used through TI provided API.
// MIN6DB                   Internal. Only to be used through TI provided API.
// MIN9DB                   Internal. Only to be used through TI provided API.
// MIN12DB                  Internal. Only to be used through TI provided API.
// MIN15DB                  Internal. Only to be used through TI provided API.
#define LRFDRFE_RXCTRL_IFAMPGC_W                                             5U
#define LRFDRFE_RXCTRL_IFAMPGC_M                                    0x000001F0U
#define LRFDRFE_RXCTRL_IFAMPGC_S                                             4U
#define LRFDRFE_RXCTRL_IFAMPGC_MAX                                  0x000001F0U
#define LRFDRFE_RXCTRL_IFAMPGC_MIN3DB                               0x000000F0U
#define LRFDRFE_RXCTRL_IFAMPGC_MIN6DB                               0x00000070U
#define LRFDRFE_RXCTRL_IFAMPGC_MIN9DB                               0x00000030U
#define LRFDRFE_RXCTRL_IFAMPGC_MIN12DB                              0x00000010U
#define LRFDRFE_RXCTRL_IFAMPGC_MIN15DB                              0x00000000U

// Field:   [3:0] LNAGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAX                      Internal. Only to be used through TI provided API.
// MIN3DB                   Internal. Only to be used through TI provided API.
// MIN6DB                   Internal. Only to be used through TI provided API.
// MIN9DB                   Internal. Only to be used through TI provided API.
// MIN12DB                  Internal. Only to be used through TI provided API.
#define LRFDRFE_RXCTRL_LNAGAIN_W                                             4U
#define LRFDRFE_RXCTRL_LNAGAIN_M                                    0x0000000FU
#define LRFDRFE_RXCTRL_LNAGAIN_S                                             0U
#define LRFDRFE_RXCTRL_LNAGAIN_MAX                                  0x0000000FU
#define LRFDRFE_RXCTRL_LNAGAIN_MIN3DB                               0x00000007U
#define LRFDRFE_RXCTRL_LNAGAIN_MIN6DB                               0x00000003U
#define LRFDRFE_RXCTRL_LNAGAIN_MIN9DB                               0x00000001U
#define LRFDRFE_RXCTRL_LNAGAIN_MIN12DB                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNACC0
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNACC0_VAL_W                                              16U
#define LRFDRFE_MAGNACC0_VAL_M                                      0x0000FFFFU
#define LRFDRFE_MAGNACC0_VAL_S                                               0U
#define LRFDRFE_MAGNACC0_VAL_ALLONES                                0x0000FFFFU
#define LRFDRFE_MAGNACC0_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MAGNACC1
//
//*****************************************************************************
// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MAGNACC1_VAL_W                                              16U
#define LRFDRFE_MAGNACC1_VAL_M                                      0x0000FFFFU
#define LRFDRFE_MAGNACC1_VAL_S                                               0U
#define LRFDRFE_MAGNACC1_VAL_ALLONES                                0x0000FFFFU
#define LRFDRFE_MAGNACC1_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RSSI
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_RSSI_VAL_W                                                   8U
#define LRFDRFE_RSSI_VAL_M                                          0x000000FFU
#define LRFDRFE_RSSI_VAL_S                                                   0U
#define LRFDRFE_RSSI_VAL_ALLONES                                    0x000000FFU
#define LRFDRFE_RSSI_VAL_ALLZEROS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RSSIMAX
//
//*****************************************************************************
// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_RSSIMAX_VAL_W                                                8U
#define LRFDRFE_RSSIMAX_VAL_M                                       0x000000FFU
#define LRFDRFE_RSSIMAX_VAL_S                                                0U
#define LRFDRFE_RSSIMAX_VAL_ALLONES                                 0x000000FFU
#define LRFDRFE_RSSIMAX_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_RFGAIN
//
//*****************************************************************************
// Field:   [7:0] DBGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_RFGAIN_DBGAIN_W                                              8U
#define LRFDRFE_RFGAIN_DBGAIN_M                                     0x000000FFU
#define LRFDRFE_RFGAIN_DBGAIN_S                                              0U
#define LRFDRFE_RFGAIN_DBGAIN_ALLONES                               0x000000FFU
#define LRFDRFE_RFGAIN_DBGAIN_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_IFADCSTAT
//
//*****************************************************************************
// Field:   [6:2] QUANTCALVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// COMP1                    Internal. Only to be used through TI provided API.
// COMP0                    Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_W                                      5U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_M                             0x0000007CU
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_S                                      2U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_COMP1                         0x00000004U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_COMP0                         0x00000000U

// Field:     [1] QUANTCALDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// READY                    Internal. Only to be used through TI provided API.
// NOT_READY                Internal. Only to be used through TI provided API.
#define LRFDRFE_IFADCSTAT_QUANTCALDONE                              0x00000002U
#define LRFDRFE_IFADCSTAT_QUANTCALDONE_M                            0x00000002U
#define LRFDRFE_IFADCSTAT_QUANTCALDONE_S                                     1U
#define LRFDRFE_IFADCSTAT_QUANTCALDONE_READY                        0x00000002U
#define LRFDRFE_IFADCSTAT_QUANTCALDONE_NOT_READY                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVSTA
//
//*****************************************************************************
// Field:     [0] STAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BUSY                     Internal. Only to be used through TI provided API.
// IDLE                     Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVSTA_STAT                                         0x00000001U
#define LRFDRFE_DIVSTA_STAT_M                                       0x00000001U
#define LRFDRFE_DIVSTA_STAT_S                                                0U
#define LRFDRFE_DIVSTA_STAT_BUSY                                    0x00000001U
#define LRFDRFE_DIVSTA_STAT_IDLE                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVIDENDL
//
//*****************************************************************************
// Field:  [15:0] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVIDENDL_VALLSB_W                                          16U
#define LRFDRFE_DIVIDENDL_VALLSB_M                                  0x0000FFFFU
#define LRFDRFE_DIVIDENDL_VALLSB_S                                           0U
#define LRFDRFE_DIVIDENDL_VALLSB_ALLONES                            0x0000FFFFU
#define LRFDRFE_DIVIDENDL_VALLSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVIDENDH
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVIDENDH_VALMSB_W                                          16U
#define LRFDRFE_DIVIDENDH_VALMSB_M                                  0x0000FFFFU
#define LRFDRFE_DIVIDENDH_VALMSB_S                                           0U
#define LRFDRFE_DIVIDENDH_VALMSB_ALLONES                            0x0000FFFFU
#define LRFDRFE_DIVIDENDH_VALMSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVISORL
//
//*****************************************************************************
// Field:  [15:0] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVISORL_VALLSB_W                                           16U
#define LRFDRFE_DIVISORL_VALLSB_M                                   0x0000FFFFU
#define LRFDRFE_DIVISORL_VALLSB_S                                            0U
#define LRFDRFE_DIVISORL_VALLSB_ALLONES                             0x0000FFFFU
#define LRFDRFE_DIVISORL_VALLSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_DIVISORH
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_DIVISORH_VALMSB_W                                           16U
#define LRFDRFE_DIVISORH_VALMSB_M                                   0x0000FFFFU
#define LRFDRFE_DIVISORH_VALMSB_S                                            0U
#define LRFDRFE_DIVISORH_VALMSB_ALLONES                             0x0000FFFFU
#define LRFDRFE_DIVISORH_VALMSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_QUOTIENTL
//
//*****************************************************************************
// Field:  [15:0] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_QUOTIENTL_VALLSB_W                                          16U
#define LRFDRFE_QUOTIENTL_VALLSB_M                                  0x0000FFFFU
#define LRFDRFE_QUOTIENTL_VALLSB_S                                           0U
#define LRFDRFE_QUOTIENTL_VALLSB_ALLONES                            0x0000FFFFU
#define LRFDRFE_QUOTIENTL_VALLSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_QUOTIENTH
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_QUOTIENTH_VALMSB_W                                          16U
#define LRFDRFE_QUOTIENTH_VALMSB_M                                  0x0000FFFFU
#define LRFDRFE_QUOTIENTH_VALMSB_S                                           0U
#define LRFDRFE_QUOTIENTH_VALMSB_ALLONES                            0x0000FFFFU
#define LRFDRFE_QUOTIENTH_VALMSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRODUCTL
//
//*****************************************************************************
// Field:  [15:0] VALLSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRODUCTL_VALLSB_W                                           16U
#define LRFDRFE_PRODUCTL_VALLSB_M                                   0x0000FFFFU
#define LRFDRFE_PRODUCTL_VALLSB_S                                            0U
#define LRFDRFE_PRODUCTL_VALLSB_ALLONES                             0x0000FFFFU
#define LRFDRFE_PRODUCTL_VALLSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_PRODUCTH
//
//*****************************************************************************
// Field:  [15:0] VALMSB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDRFE_PRODUCTH_VALMSB_W                                           16U
#define LRFDRFE_PRODUCTH_VALMSB_M                                   0x0000FFFFU
#define LRFDRFE_PRODUCTH_VALMSB_S                                            0U
#define LRFDRFE_PRODUCTH_VALMSB_ALLONES                             0x0000FFFFU
#define LRFDRFE_PRODUCTH_VALMSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MULTSTA
//
//*****************************************************************************
// Field:     [0] STAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BUSY                     Internal. Only to be used through TI provided API.
// IDLE                     Internal. Only to be used through TI provided API.
#define LRFDRFE_MULTSTA_STAT                                        0x00000001U
#define LRFDRFE_MULTSTA_STAT_M                                      0x00000001U
#define LRFDRFE_MULTSTA_STAT_S                                               0U
#define LRFDRFE_MULTSTA_STAT_BUSY                                   0x00000001U
#define LRFDRFE_MULTSTA_STAT_IDLE                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE_O_MULTCFG
//
//*****************************************************************************
// Field:     [0] MODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SIGNED                   Internal. Only to be used through TI provided API.
// UNSIGNED                 Internal. Only to be used through TI provided API.
#define LRFDRFE_MULTCFG_MODE                                        0x00000001U
#define LRFDRFE_MULTCFG_MODE_M                                      0x00000001U
#define LRFDRFE_MULTCFG_MODE_S                                               0U
#define LRFDRFE_MULTCFG_MODE_SIGNED                                 0x00000001U
#define LRFDRFE_MULTCFG_MODE_UNSIGNED                               0x00000000U


#endif // __LRFDRFE__
