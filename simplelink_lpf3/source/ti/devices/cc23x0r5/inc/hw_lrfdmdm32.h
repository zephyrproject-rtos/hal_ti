/******************************************************************************
*  Filename:       hw_lrfdmdm32.h
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

#ifndef __HW_LRFDMDM32_H__
#define __HW_LRFDMDM32_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDMDM32 component
//
//*****************************************************************************
// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FWSRC_ENABLE                                    0x00000000U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_INIT                                            0x00000004U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMENABLE1_DEMENABLE0                           0x00000008U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMINIT1_DEMINIT0                               0x0000000CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_STRB1_STRB0                                     0x00000010U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVT1_EVT0                                       0x00000014U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVT2                                            0x00000018U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVTMSK1_EVTMSK0                                 0x0000001CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVTMSK2                                         0x00000020U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVTCLR1_EVTCLR0                                 0x00000024U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_EVTCLR2                                         0x00000028U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_API_PDREQ                                       0x0000002CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_CMDPAR1_CMDPAR0                                 0x00000030U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MSGBOX_CMDPAR2                                  0x00000034U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FIFOWR_FREQ                                     0x00000038U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FIFORD                                          0x0000003CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FIFORDCTRL_FIFOWRCTRL                           0x00000040U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FIFOSTA                                         0x00000044U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_RFEDATIN0_RFEDATOUT0                            0x00000048U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_RFECMDIN_RFECMDOUT                              0x0000004CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_PBEDATIN0_PBEDATOUT0                            0x00000050U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_PBECMDIN_PBECMDOUT                              0x00000054U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_PBEEVTMUX_LQIEST                                0x00000058U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SYSTIMEVTMUX1_SYSTIMEVTMUX0                     0x0000005CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MODPRECTRL_ADCDIGCONF                           0x00000060U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MODSYMMAP1_MODSYMMAP0                           0x00000064U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_BAUD_MODSOFTTX                                  0x00000068U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MODMAIN_BAUDPRE                                 0x0000006CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMMISC1_DEMMISC0                               0x00000070U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMMISC3_DEMMISC2                               0x00000074U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMDSBU_DEMIQMC0                                0x00000078U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMFIDC0_DEMCODC0                               0x0000007CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMDSXB0_DEMFEXB0                               0x00000080U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMMAFI0_DEMFIFE0                               0x00000084U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMMAFI2_DEMMAFI1                               0x00000088U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMC1BE1_DEMC1BE0                               0x0000008CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SPARE0_DEMC1BE2                                 0x00000090U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SPARE2_SPARE1                                   0x00000094U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMSWQU0_SPARE3                                 0x00000098U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMC1BEREF1_DEMC1BEREF0                         0x0000009CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMC1BEREF3_DEMC1BEREF2                         0x000000A0U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MODPREAMBLE_MODCTRL                             0x000000A4U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMFRAC1_DEMFRAC0                               0x000000A8U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMFRAC3_DEMFRAC2                               0x000000ACU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMCODC2_DEMCODC1                               0x000000B0U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMFIDC2_DEMFIDC1                               0x000000B4U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMMAFC0_DEMFIFE1                               0x000000B8U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMSWIMBAL_DEMMAFI4                             0x000000BCU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMDEBUG_DEMSOFTPDIFF                           0x000000C0U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_VITCOMPUTE_VITCTRL                              0x000000C4U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_VITSTATE_VITAPMRDBACK                           0x000000C8U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_VITBRMETRIC32_VITBRMETRIC10                     0x000000CCU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_VITBRMETRIC76_VITBRMETRIC54                     0x000000D0U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_TIMCTL                                          0x000000F0U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_TIMPER_TIMINC                                   0x000000F4U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_TIMCAPT_TIMCNT                                  0x000000F8U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_COUNT1IN_TIMEBASE                               0x000000FCU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_COUNT1RES                                       0x00000100U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_BRMACC2_BRMACC1                                 0x00000104U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MCETRCSTAT_MCETRCCTRL                           0x00000108U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_MCETRCPAR0_MCETRCCMD                            0x0000010CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_RDCAPT0_MCETRCPAR1                              0x00000110U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_FECAPT0_RDCAPT1                                 0x00000114U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DSCAPT0_FECAPT1                                 0x00000118U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DSCAPT2_DSCAPT1                                 0x0000011CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_DEMSWQU1_DSCAPT3                                0x00000120U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_GPOCTRL1_GPOCTRL0                               0x00000124U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_RFEMAXRSSI_RFERSSI                              0x00000128U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SYNC0_RFEDBGAIN                                 0x0000012CU

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SYNC2_SYNC1                                     0x00000130U

// Internal. Only to be used through TI provided API.
#define LRFDMDM32_O_SYNC3                                           0x00000134U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FWSRC_ENABLE
//
//*****************************************************************************
// Field:    [18] DATARAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// MDMRAM                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_DATARAM                              0x00040000U
#define LRFDMDM32_FWSRC_ENABLE_DATARAM_M                            0x00040000U
#define LRFDMDM32_FWSRC_ENABLE_DATARAM_S                                    18U
#define LRFDMDM32_FWSRC_ENABLE_DATARAM_S2RRAM                       0x00040000U
#define LRFDMDM32_FWSRC_ENABLE_DATARAM_MDMRAM                       0x00000000U

// Field:    [17] FWRAM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// S2RRAM                   Internal. Only to be used through TI provided API.
// MDMRAM                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_FWRAM                                0x00020000U
#define LRFDMDM32_FWSRC_ENABLE_FWRAM_M                              0x00020000U
#define LRFDMDM32_FWSRC_ENABLE_FWRAM_S                                      17U
#define LRFDMDM32_FWSRC_ENABLE_FWRAM_S2RRAM                         0x00020000U
#define LRFDMDM32_FWSRC_ENABLE_FWRAM_MDMRAM                         0x00000000U

// Field:    [16] BANK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_BANK                                 0x00010000U
#define LRFDMDM32_FWSRC_ENABLE_BANK_M                               0x00010000U
#define LRFDMDM32_FWSRC_ENABLE_BANK_S                                       16U
#define LRFDMDM32_FWSRC_ENABLE_BANK_ONE                             0x00010000U
#define LRFDMDM32_FWSRC_ENABLE_BANK_ZERO                            0x00000000U

// Field:     [5] ADCDIG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_ADCDIG                               0x00000020U
#define LRFDMDM32_FWSRC_ENABLE_ADCDIG_M                             0x00000020U
#define LRFDMDM32_FWSRC_ENABLE_ADCDIG_S                                      5U
#define LRFDMDM32_FWSRC_ENABLE_ADCDIG_EN                            0x00000020U
#define LRFDMDM32_FWSRC_ENABLE_ADCDIG_DIS                           0x00000000U

// Field:     [4] DEMODULATOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_DEMODULATOR                          0x00000010U
#define LRFDMDM32_FWSRC_ENABLE_DEMODULATOR_M                        0x00000010U
#define LRFDMDM32_FWSRC_ENABLE_DEMODULATOR_S                                 4U
#define LRFDMDM32_FWSRC_ENABLE_DEMODULATOR_EN                       0x00000010U
#define LRFDMDM32_FWSRC_ENABLE_DEMODULATOR_DIS                      0x00000000U

// Field:     [3] MODULATOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_MODULATOR                            0x00000008U
#define LRFDMDM32_FWSRC_ENABLE_MODULATOR_M                          0x00000008U
#define LRFDMDM32_FWSRC_ENABLE_MODULATOR_S                                   3U
#define LRFDMDM32_FWSRC_ENABLE_MODULATOR_EN                         0x00000008U
#define LRFDMDM32_FWSRC_ENABLE_MODULATOR_DIS                        0x00000000U

// Field:     [2] TIMEBASE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_TIMEBASE                             0x00000004U
#define LRFDMDM32_FWSRC_ENABLE_TIMEBASE_M                           0x00000004U
#define LRFDMDM32_FWSRC_ENABLE_TIMEBASE_S                                    2U
#define LRFDMDM32_FWSRC_ENABLE_TIMEBASE_EN                          0x00000004U
#define LRFDMDM32_FWSRC_ENABLE_TIMEBASE_DIS                         0x00000000U

// Field:     [1] TXRXFIFO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_TXRXFIFO                             0x00000002U
#define LRFDMDM32_FWSRC_ENABLE_TXRXFIFO_M                           0x00000002U
#define LRFDMDM32_FWSRC_ENABLE_TXRXFIFO_S                                    1U
#define LRFDMDM32_FWSRC_ENABLE_TXRXFIFO_EN                          0x00000002U
#define LRFDMDM32_FWSRC_ENABLE_TXRXFIFO_DIS                         0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_FWSRC_ENABLE_TOPSM                                0x00000001U
#define LRFDMDM32_FWSRC_ENABLE_TOPSM_M                              0x00000001U
#define LRFDMDM32_FWSRC_ENABLE_TOPSM_S                                       0U
#define LRFDMDM32_FWSRC_ENABLE_TOPSM_EN                             0x00000001U
#define LRFDMDM32_FWSRC_ENABLE_TOPSM_DIS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_INIT
//
//*****************************************************************************
// Field:     [5] ADCDIG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_ADCDIG                                       0x00000020U
#define LRFDMDM32_INIT_ADCDIG_M                                     0x00000020U
#define LRFDMDM32_INIT_ADCDIG_S                                              5U
#define LRFDMDM32_INIT_ADCDIG_RESET                                 0x00000020U
#define LRFDMDM32_INIT_ADCDIG_NO_EFFECT                             0x00000000U

// Field:     [4] DEMODULATOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_DEMODULATOR                                  0x00000010U
#define LRFDMDM32_INIT_DEMODULATOR_M                                0x00000010U
#define LRFDMDM32_INIT_DEMODULATOR_S                                         4U
#define LRFDMDM32_INIT_DEMODULATOR_RESET                            0x00000010U
#define LRFDMDM32_INIT_DEMODULATOR_NO_EFFECT                        0x00000000U

// Field:     [3] MODULATOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_MODULATOR                                    0x00000008U
#define LRFDMDM32_INIT_MODULATOR_M                                  0x00000008U
#define LRFDMDM32_INIT_MODULATOR_S                                           3U
#define LRFDMDM32_INIT_MODULATOR_RESET                              0x00000008U
#define LRFDMDM32_INIT_MODULATOR_NO_EFFECT                          0x00000000U

// Field:     [2] TIMEBASE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_TIMEBASE                                     0x00000004U
#define LRFDMDM32_INIT_TIMEBASE_M                                   0x00000004U
#define LRFDMDM32_INIT_TIMEBASE_S                                            2U
#define LRFDMDM32_INIT_TIMEBASE_RESET                               0x00000004U
#define LRFDMDM32_INIT_TIMEBASE_NO_EFFECT                           0x00000000U

// Field:     [1] TXRXFIFO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_TXRXFIFO                                     0x00000002U
#define LRFDMDM32_INIT_TXRXFIFO_M                                   0x00000002U
#define LRFDMDM32_INIT_TXRXFIFO_S                                            1U
#define LRFDMDM32_INIT_TXRXFIFO_RESET                               0x00000002U
#define LRFDMDM32_INIT_TXRXFIFO_NO_EFFECT                           0x00000000U

// Field:     [0] TOPSM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_INIT_TOPSM                                        0x00000001U
#define LRFDMDM32_INIT_TOPSM_M                                      0x00000001U
#define LRFDMDM32_INIT_TOPSM_S                                               0U
#define LRFDMDM32_INIT_TOPSM_RESET                                  0x00000001U
#define LRFDMDM32_INIT_TOPSM_NO_EFFECT                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMENABLE1_DEMENABLE0
//
//*****************************************************************************
// Field:    [29] VITE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_VITE                        0x20000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_VITE_M                      0x20000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_VITE_S                              29U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_VITE_EN                     0x20000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_VITE_DIS                    0x00000000U

// Field:    [28] MLSE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MLSE                        0x10000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MLSE_M                      0x10000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MLSE_S                              28U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MLSE_EN                     0x10000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MLSE_DIS                    0x00000000U

// Field:    [27] SOFD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SOFD                        0x08000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SOFD_M                      0x08000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SOFD_S                              27U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SOFD_EN                     0x08000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SOFD_DIS                    0x00000000U

// Field:    [26] SWQU
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SWQU                        0x04000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SWQU_M                      0x04000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SWQU_S                              26U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SWQU_EN                     0x04000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_SWQU_DIS                    0x00000000U

// Field:    [25] MAFC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFC                        0x02000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFC_M                      0x02000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFC_S                              25U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFC_EN                     0x02000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFC_DIS                    0x00000000U

// Field:    [24] MAFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFI                        0x01000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFI_M                      0x01000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFI_S                              24U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFI_EN                     0x01000000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MAFI_DIS                    0x00000000U

// Field:    [23] FIFE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIFE                        0x00800000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIFE_M                      0x00800000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIFE_S                              23U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIFE_EN                     0x00800000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIFE_DIS                    0x00000000U

// Field:    [22] PDIF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_PDIF                        0x00400000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_PDIF_M                      0x00400000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_PDIF_S                              22U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_PDIF_EN                     0x00400000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_PDIF_DIS                    0x00000000U

// Field:    [21] CA2P
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CA2P                        0x00200000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CA2P_M                      0x00200000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CA2P_S                              21U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CA2P_EN                     0x00200000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CA2P_DIS                    0x00000000U

// Field:    [20] C1BE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_C1BE                        0x00100000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_C1BE_M                      0x00100000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_C1BE_S                              20U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_C1BE_EN                     0x00100000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_C1BE_DIS                    0x00000000U

// Field:    [19] LQIE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_LQIE                        0x00080000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_LQIE_M                      0x00080000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_LQIE_S                              19U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_LQIE_EN                     0x00080000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_LQIE_DIS                    0x00000000U

// Field:    [18] F4BA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_F4BA                        0x00040000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_F4BA_M                      0x00040000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_F4BA_S                              18U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_F4BA_EN                     0x00040000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_F4BA_DIS                    0x00000000U

// Field:    [17] STIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_STIM                        0x00020000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_STIM_M                      0x00020000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_STIM_S                              17U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_STIM_EN                     0x00020000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_STIM_DIS                    0x00000000U

// Field:    [16] DSBU
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_DSBU                        0x00010000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_DSBU_M                      0x00010000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_DSBU_S                              16U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_DSBU_EN                     0x00010000U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_DSBU_DIS                    0x00000000U

// Field:     [8] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FRAC                        0x00000100U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FRAC_M                      0x00000100U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FRAC_S                               8U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FRAC_EN                     0x00000100U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FRAC_DIS                    0x00000000U

// Field:     [7] FIDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIDC                        0x00000080U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIDC_M                      0x00000080U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIDC_S                               7U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIDC_EN                     0x00000080U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_FIDC_DIS                    0x00000000U

// Field:     [6] CHFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CHFI                        0x00000040U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CHFI_M                      0x00000040U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CHFI_S                               6U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CHFI_EN                     0x00000040U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CHFI_DIS                    0x00000000U

// Field:     [5] BDEC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_BDEC                        0x00000020U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_BDEC_M                      0x00000020U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_BDEC_S                               5U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_BDEC_EN                     0x00000020U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_BDEC_DIS                    0x00000000U

// Field:     [4] IQMC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_IQMC                        0x00000010U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_IQMC_M                      0x00000010U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_IQMC_S                               4U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_IQMC_EN                     0x00000010U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_IQMC_DIS                    0x00000000U

// Field:     [3] MGE1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE1                        0x00000008U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE1_M                      0x00000008U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE1_S                               3U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE1_EN                     0x00000008U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE1_DIS                    0x00000000U

// Field:     [2] MGE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE0                        0x00000004U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE0_M                      0x00000004U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE0_S                               2U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE0_EN                     0x00000004U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_MGE0_DIS                    0x00000000U

// Field:     [1] CODC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CODC                        0x00000002U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CODC_M                      0x00000002U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CODC_S                               1U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CODC_EN                     0x00000002U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CODC_DIS                    0x00000000U

// Field:     [0] CMIX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CMIX                        0x00000001U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CMIX_M                      0x00000001U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CMIX_S                               0U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CMIX_EN                     0x00000001U
#define LRFDMDM32_DEMENABLE1_DEMENABLE0_CMIX_DIS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMINIT1_DEMINIT0
//
//*****************************************************************************
// Field:    [29] VITE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_VITE                            0x20000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_VITE_M                          0x20000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_VITE_S                                  29U
#define LRFDMDM32_DEMINIT1_DEMINIT0_VITE_RESET                      0x20000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_VITE_NO_EFFECT                  0x00000000U

// Field:    [28] MLSE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_MLSE                            0x10000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MLSE_M                          0x10000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MLSE_S                                  28U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MLSE_RESET                      0x10000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MLSE_NO_EFFECT                  0x00000000U

// Field:    [27] SOFD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_SOFD                            0x08000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SOFD_M                          0x08000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SOFD_S                                  27U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SOFD_RESET                      0x08000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SOFD_NO_EFFECT                  0x00000000U

// Field:    [26] SWQU
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_SWQU                            0x04000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SWQU_M                          0x04000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SWQU_S                                  26U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SWQU_RESET                      0x04000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_SWQU_NO_EFFECT                  0x00000000U

// Field:    [25] MAFC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFC                            0x02000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFC_M                          0x02000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFC_S                                  25U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFC_RESET                      0x02000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFC_NO_EFFECT                  0x00000000U

// Field:    [24] MAFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFI                            0x01000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFI_M                          0x01000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFI_S                                  24U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFI_RESET                      0x01000000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MAFI_NO_EFFECT                  0x00000000U

// Field:    [23] FIFE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIFE                            0x00800000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIFE_M                          0x00800000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIFE_S                                  23U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIFE_RESET                      0x00800000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIFE_NO_EFFECT                  0x00000000U

// Field:    [22] PDIF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_PDIF                            0x00400000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_PDIF_M                          0x00400000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_PDIF_S                                  22U
#define LRFDMDM32_DEMINIT1_DEMINIT0_PDIF_RESET                      0x00400000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_PDIF_NO_EFFECT                  0x00000000U

// Field:    [21] CA2P
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_CA2P                            0x00200000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CA2P_M                          0x00200000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CA2P_S                                  21U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CA2P_RESET                      0x00200000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CA2P_NO_EFFECT                  0x00000000U

// Field:    [20] C1BE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_C1BE                            0x00100000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_C1BE_M                          0x00100000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_C1BE_S                                  20U
#define LRFDMDM32_DEMINIT1_DEMINIT0_C1BE_RESET                      0x00100000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_C1BE_NO_EFFECT                  0x00000000U

// Field:    [19] LQIE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_LQIE                            0x00080000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_LQIE_M                          0x00080000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_LQIE_S                                  19U
#define LRFDMDM32_DEMINIT1_DEMINIT0_LQIE_RESET                      0x00080000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_LQIE_NO_EFFECT                  0x00000000U

// Field:    [18] F4BA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_F4BA                            0x00040000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_F4BA_M                          0x00040000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_F4BA_S                                  18U
#define LRFDMDM32_DEMINIT1_DEMINIT0_F4BA_RESET                      0x00040000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_F4BA_NO_EFFECT                  0x00000000U

// Field:    [17] STIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_STIM                            0x00020000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_STIM_M                          0x00020000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_STIM_S                                  17U
#define LRFDMDM32_DEMINIT1_DEMINIT0_STIM_RESET                      0x00020000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_STIM_NO_EFFECT                  0x00000000U

// Field:    [16] DSBU
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_DSBU                            0x00010000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_DSBU_M                          0x00010000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_DSBU_S                                  16U
#define LRFDMDM32_DEMINIT1_DEMINIT0_DSBU_RESET                      0x00010000U
#define LRFDMDM32_DEMINIT1_DEMINIT0_DSBU_NO_EFFECT                  0x00000000U

// Field:     [8] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_FRAC                            0x00000100U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FRAC_M                          0x00000100U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FRAC_S                                   8U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FRAC_RESET                      0x00000100U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FRAC_NO_EFFECT                  0x00000000U

// Field:     [7] FIDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIDC                            0x00000080U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIDC_M                          0x00000080U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIDC_S                                   7U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIDC_RESET                      0x00000080U
#define LRFDMDM32_DEMINIT1_DEMINIT0_FIDC_NO_EFFECT                  0x00000000U

// Field:     [6] CHFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_CHFI                            0x00000040U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CHFI_M                          0x00000040U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CHFI_S                                   6U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CHFI_RESET                      0x00000040U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CHFI_NO_EFFECT                  0x00000000U

// Field:     [5] BDEC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_BDEC                            0x00000020U
#define LRFDMDM32_DEMINIT1_DEMINIT0_BDEC_M                          0x00000020U
#define LRFDMDM32_DEMINIT1_DEMINIT0_BDEC_S                                   5U
#define LRFDMDM32_DEMINIT1_DEMINIT0_BDEC_RESET                      0x00000020U
#define LRFDMDM32_DEMINIT1_DEMINIT0_BDEC_NO_EFFECT                  0x00000000U

// Field:     [4] IQMC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_IQMC                            0x00000010U
#define LRFDMDM32_DEMINIT1_DEMINIT0_IQMC_M                          0x00000010U
#define LRFDMDM32_DEMINIT1_DEMINIT0_IQMC_S                                   4U
#define LRFDMDM32_DEMINIT1_DEMINIT0_IQMC_RESET                      0x00000010U
#define LRFDMDM32_DEMINIT1_DEMINIT0_IQMC_NO_EFFECT                  0x00000000U

// Field:     [3] MGE1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE1                            0x00000008U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE1_M                          0x00000008U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE1_S                                   3U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE1_RESET                      0x00000008U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE1_NO_EFFECT                  0x00000000U

// Field:     [2] MGE0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE0                            0x00000004U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE0_M                          0x00000004U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE0_S                                   2U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE0_RESET                      0x00000004U
#define LRFDMDM32_DEMINIT1_DEMINIT0_MGE0_NO_EFFECT                  0x00000000U

// Field:     [1] CODC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_CODC                            0x00000002U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CODC_M                          0x00000002U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CODC_S                                   1U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CODC_RESET                      0x00000002U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CODC_NO_EFFECT                  0x00000000U

// Field:     [0] CMIX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESET                    Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMINIT1_DEMINIT0_CMIX                            0x00000001U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CMIX_M                          0x00000001U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CMIX_S                                   0U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CMIX_RESET                      0x00000001U
#define LRFDMDM32_DEMINIT1_DEMINIT0_CMIX_NO_EFFECT                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_STRB1_STRB0
//
//*****************************************************************************
// Field:    [29] S2RTRG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_S2RTRG                                0x20000000U
#define LRFDMDM32_STRB1_STRB0_S2RTRG_M                              0x20000000U
#define LRFDMDM32_STRB1_STRB0_S2RTRG_S                                      29U
#define LRFDMDM32_STRB1_STRB0_S2RTRG_ONE                            0x20000000U
#define LRFDMDM32_STRB1_STRB0_S2RTRG_ZERO                           0x00000000U

// Field:    [28] DMATRG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_DMATRG                                0x10000000U
#define LRFDMDM32_STRB1_STRB0_DMATRG_M                              0x10000000U
#define LRFDMDM32_STRB1_STRB0_DMATRG_S                                      28U
#define LRFDMDM32_STRB1_STRB0_DMATRG_ONE                            0x10000000U
#define LRFDMDM32_STRB1_STRB0_DMATRG_ZERO                           0x00000000U

// Field:    [27] SYSTCAPT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT2                             0x08000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT2_M                           0x08000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT2_S                                   27U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT2_ONE                         0x08000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT2_ZERO                        0x00000000U

// Field:    [26] SYSTCAPT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT1                             0x04000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT1_M                           0x04000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT1_S                                   26U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT1_ONE                         0x04000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT1_ZERO                        0x00000000U

// Field:    [25] SYSTCAPT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT0                             0x02000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT0_M                           0x02000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT0_S                                   25U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT0_ONE                         0x02000000U
#define LRFDMDM32_STRB1_STRB0_SYSTCAPT0_ZERO                        0x00000000U

// Field:    [24] C1BEPEAKAB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKAB                            0x01000000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKAB_M                          0x01000000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKAB_S                                  24U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKAB_ONE                        0x01000000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKAB_ZERO                       0x00000000U

// Field:    [23] C1BEPEAKC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKC                             0x00800000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKC_M                           0x00800000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKC_S                                   23U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKC_ONE                         0x00800000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKC_ZERO                        0x00000000U

// Field:    [22] C1BEPEAKB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKB                             0x00400000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKB_M                           0x00400000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKB_S                                   22U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKB_ONE                         0x00400000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKB_ZERO                        0x00000000U

// Field:    [21] C1BEPEAKA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKA                             0x00200000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKA_M                           0x00200000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKA_S                                   21U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKA_ONE                         0x00200000U
#define LRFDMDM32_STRB1_STRB0_C1BEPEAKA_ZERO                        0x00000000U

// Field:    [20] C1BEADVANCE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEADVANCE                           0x00100000U
#define LRFDMDM32_STRB1_STRB0_C1BEADVANCE_M                         0x00100000U
#define LRFDMDM32_STRB1_STRB0_C1BEADVANCE_S                                 20U
#define LRFDMDM32_STRB1_STRB0_C1BEADVANCE_ONE                       0x00100000U
#define LRFDMDM32_STRB1_STRB0_C1BEADVANCE_ZERO                      0x00000000U

// Field:    [19] C1BESTALL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BESTALL                             0x00080000U
#define LRFDMDM32_STRB1_STRB0_C1BESTALL_M                           0x00080000U
#define LRFDMDM32_STRB1_STRB0_C1BESTALL_S                                   19U
#define LRFDMDM32_STRB1_STRB0_C1BESTALL_ONE                         0x00080000U
#define LRFDMDM32_STRB1_STRB0_C1BESTALL_ZERO                        0x00000000U

// Field: [18:17] C1BEROT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ROT16R                   Internal. Only to be used through TI provided API.
// ROT1L                    Internal. Only to be used through TI provided API.
// ROT1R                    Internal. Only to be used through TI provided API.
// ROT0                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BEROT_W                                      2U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_M                             0x00060000U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_S                                     17U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_ROT16R                        0x00060000U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_ROT1L                         0x00040000U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_ROT1R                         0x00020000U
#define LRFDMDM32_STRB1_STRB0_C1BEROT_ROT0                          0x00000000U

// Field:    [16] C1BECOPY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_C1BECOPY                              0x00010000U
#define LRFDMDM32_STRB1_STRB0_C1BECOPY_M                            0x00010000U
#define LRFDMDM32_STRB1_STRB0_C1BECOPY_S                                    16U
#define LRFDMDM32_STRB1_STRB0_C1BECOPY_ONE                          0x00010000U
#define LRFDMDM32_STRB1_STRB0_C1BECOPY_ZERO                         0x00000000U

// Field:    [11] TIMBADVANCE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_TIMBADVANCE                           0x00000800U
#define LRFDMDM32_STRB1_STRB0_TIMBADVANCE_M                         0x00000800U
#define LRFDMDM32_STRB1_STRB0_TIMBADVANCE_S                                 11U
#define LRFDMDM32_STRB1_STRB0_TIMBADVANCE_ON                        0x00000800U
#define LRFDMDM32_STRB1_STRB0_TIMBADVANCE_NO_EFFECT                 0x00000000U

// Field:    [10] TIMBSTALL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_TIMBSTALL                             0x00000400U
#define LRFDMDM32_STRB1_STRB0_TIMBSTALL_M                           0x00000400U
#define LRFDMDM32_STRB1_STRB0_TIMBSTALL_S                                   10U
#define LRFDMDM32_STRB1_STRB0_TIMBSTALL_ON                          0x00000400U
#define LRFDMDM32_STRB1_STRB0_TIMBSTALL_NO_EFFECT                   0x00000000U

// Field:     [9] EVT5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT5                                  0x00000200U
#define LRFDMDM32_STRB1_STRB0_EVT5_M                                0x00000200U
#define LRFDMDM32_STRB1_STRB0_EVT5_S                                         9U
#define LRFDMDM32_STRB1_STRB0_EVT5_ONE                              0x00000200U
#define LRFDMDM32_STRB1_STRB0_EVT5_ZERO                             0x00000000U

// Field:     [8] EVT4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT4                                  0x00000100U
#define LRFDMDM32_STRB1_STRB0_EVT4_M                                0x00000100U
#define LRFDMDM32_STRB1_STRB0_EVT4_S                                         8U
#define LRFDMDM32_STRB1_STRB0_EVT4_ONE                              0x00000100U
#define LRFDMDM32_STRB1_STRB0_EVT4_ZERO                             0x00000000U

// Field:     [7] MLSETERM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_MLSETERM                              0x00000080U
#define LRFDMDM32_STRB1_STRB0_MLSETERM_M                            0x00000080U
#define LRFDMDM32_STRB1_STRB0_MLSETERM_S                                     7U
#define LRFDMDM32_STRB1_STRB0_MLSETERM_ON                           0x00000080U
#define LRFDMDM32_STRB1_STRB0_MLSETERM_OFF                          0x00000000U

// Field:     [6] EVT3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT3                                  0x00000040U
#define LRFDMDM32_STRB1_STRB0_EVT3_M                                0x00000040U
#define LRFDMDM32_STRB1_STRB0_EVT3_S                                         6U
#define LRFDMDM32_STRB1_STRB0_EVT3_ONE                              0x00000040U
#define LRFDMDM32_STRB1_STRB0_EVT3_ZERO                             0x00000000U

// Field:     [5] EVT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT2                                  0x00000020U
#define LRFDMDM32_STRB1_STRB0_EVT2_M                                0x00000020U
#define LRFDMDM32_STRB1_STRB0_EVT2_S                                         5U
#define LRFDMDM32_STRB1_STRB0_EVT2_ONE                              0x00000020U
#define LRFDMDM32_STRB1_STRB0_EVT2_ZERO                             0x00000000U

// Field:     [4] EVT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT1                                  0x00000010U
#define LRFDMDM32_STRB1_STRB0_EVT1_M                                0x00000010U
#define LRFDMDM32_STRB1_STRB0_EVT1_S                                         4U
#define LRFDMDM32_STRB1_STRB0_EVT1_ONE                              0x00000010U
#define LRFDMDM32_STRB1_STRB0_EVT1_ZERO                             0x00000000U

// Field:     [3] EVT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_EVT0                                  0x00000008U
#define LRFDMDM32_STRB1_STRB0_EVT0_M                                0x00000008U
#define LRFDMDM32_STRB1_STRB0_EVT0_S                                         3U
#define LRFDMDM32_STRB1_STRB0_EVT0_ONE                              0x00000008U
#define LRFDMDM32_STRB1_STRB0_EVT0_ZERO                             0x00000000U

// Field:     [2] TIMBALIGN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_TIMBALIGN                             0x00000004U
#define LRFDMDM32_STRB1_STRB0_TIMBALIGN_M                           0x00000004U
#define LRFDMDM32_STRB1_STRB0_TIMBALIGN_S                                    2U
#define LRFDMDM32_STRB1_STRB0_TIMBALIGN_ON                          0x00000004U
#define LRFDMDM32_STRB1_STRB0_TIMBALIGN_NO_EFFECT                   0x00000000U

// Field:     [1] DSBURST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// RESTART                  Internal. Only to be used through TI provided API.
// NO_EFFECT                Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_DSBURST                               0x00000002U
#define LRFDMDM32_STRB1_STRB0_DSBURST_M                             0x00000002U
#define LRFDMDM32_STRB1_STRB0_DSBURST_S                                      1U
#define LRFDMDM32_STRB1_STRB0_DSBURST_RESTART                       0x00000002U
#define LRFDMDM32_STRB1_STRB0_DSBURST_NO_EFFECT                     0x00000000U

// Field:     [0] CMDDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// YES                      Internal. Only to be used through TI provided API.
// NO                       Internal. Only to be used through TI provided API.
#define LRFDMDM32_STRB1_STRB0_CMDDONE                               0x00000001U
#define LRFDMDM32_STRB1_STRB0_CMDDONE_M                             0x00000001U
#define LRFDMDM32_STRB1_STRB0_CMDDONE_S                                      0U
#define LRFDMDM32_STRB1_STRB0_CMDDONE_YES                           0x00000001U
#define LRFDMDM32_STRB1_STRB0_CMDDONE_NO                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVT1_EVT0
//
//*****************************************************************************
// Field:    [24] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_REFCLK                                  0x01000000U
#define LRFDMDM32_EVT1_EVT0_REFCLK_M                                0x01000000U
#define LRFDMDM32_EVT1_EVT0_REFCLK_S                                        24U
#define LRFDMDM32_EVT1_EVT0_REFCLK_ONE                              0x01000000U
#define LRFDMDM32_EVT1_EVT0_REFCLK_ZERO                             0x00000000U

// Field:    [23] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_S2RSTOP                                 0x00800000U
#define LRFDMDM32_EVT1_EVT0_S2RSTOP_M                               0x00800000U
#define LRFDMDM32_EVT1_EVT0_S2RSTOP_S                                       23U
#define LRFDMDM32_EVT1_EVT0_S2RSTOP_ONE                             0x00800000U
#define LRFDMDM32_EVT1_EVT0_S2RSTOP_ZERO                            0x00000000U

// Field:    [22] SWQUFALSESYNC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_SWQUFALSESYNC                           0x00400000U
#define LRFDMDM32_EVT1_EVT0_SWQUFALSESYNC_M                         0x00400000U
#define LRFDMDM32_EVT1_EVT0_SWQUFALSESYNC_S                                 22U
#define LRFDMDM32_EVT1_EVT0_SWQUFALSESYNC_ONE                       0x00400000U
#define LRFDMDM32_EVT1_EVT0_SWQUFALSESYNC_ZERO                      0x00000000U

// Field:    [21] SWQUSYNCED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_SWQUSYNCED                              0x00200000U
#define LRFDMDM32_EVT1_EVT0_SWQUSYNCED_M                            0x00200000U
#define LRFDMDM32_EVT1_EVT0_SWQUSYNCED_S                                    21U
#define LRFDMDM32_EVT1_EVT0_SWQUSYNCED_ONE                          0x00200000U
#define LRFDMDM32_EVT1_EVT0_SWQUSYNCED_ZERO                         0x00000000U

// Field:    [20] CLKENBAUDF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_CLKENBAUDF                              0x00100000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUDF_M                            0x00100000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUDF_S                                    20U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUDF_ONE                          0x00100000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUDF_ZERO                         0x00000000U

// Field:    [19] FIFORVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FIFORVALID                              0x00080000U
#define LRFDMDM32_EVT1_EVT0_FIFORVALID_M                            0x00080000U
#define LRFDMDM32_EVT1_EVT0_FIFORVALID_S                                    19U
#define LRFDMDM32_EVT1_EVT0_FIFORVALID_ONE                          0x00080000U
#define LRFDMDM32_EVT1_EVT0_FIFORVALID_ZERO                         0x00000000U

// Field:    [18] FIFOWREADY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FIFOWREADY                              0x00040000U
#define LRFDMDM32_EVT1_EVT0_FIFOWREADY_M                            0x00040000U
#define LRFDMDM32_EVT1_EVT0_FIFOWREADY_S                                    18U
#define LRFDMDM32_EVT1_EVT0_FIFOWREADY_ONE                          0x00040000U
#define LRFDMDM32_EVT1_EVT0_FIFOWREADY_ZERO                         0x00000000U

// Field:    [17] CLKENBAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_CLKENBAUD                               0x00020000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUD_M                             0x00020000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUD_S                                     17U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUD_ONE                           0x00020000U
#define LRFDMDM32_EVT1_EVT0_CLKENBAUD_ZERO                          0x00000000U

// Field:    [16] PREAMBLEDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_PREAMBLEDONE                            0x00010000U
#define LRFDMDM32_EVT1_EVT0_PREAMBLEDONE_M                          0x00010000U
#define LRFDMDM32_EVT1_EVT0_PREAMBLEDONE_S                                  16U
#define LRFDMDM32_EVT1_EVT0_PREAMBLEDONE_ONE                        0x00010000U
#define LRFDMDM32_EVT1_EVT0_PREAMBLEDONE_ZERO                       0x00000000U

// Field:    [15] PBEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_PBEDAT                                  0x00008000U
#define LRFDMDM32_EVT1_EVT0_PBEDAT_M                                0x00008000U
#define LRFDMDM32_EVT1_EVT0_PBEDAT_S                                        15U
#define LRFDMDM32_EVT1_EVT0_PBEDAT_ONE                              0x00008000U
#define LRFDMDM32_EVT1_EVT0_PBEDAT_ZERO                             0x00000000U

// Field:    [14] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_PBECMD                                  0x00004000U
#define LRFDMDM32_EVT1_EVT0_PBECMD_M                                0x00004000U
#define LRFDMDM32_EVT1_EVT0_PBECMD_S                                        14U
#define LRFDMDM32_EVT1_EVT0_PBECMD_ONE                              0x00004000U
#define LRFDMDM32_EVT1_EVT0_PBECMD_ZERO                             0x00000000U

// Field:    [13] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_RFEDAT                                  0x00002000U
#define LRFDMDM32_EVT1_EVT0_RFEDAT_M                                0x00002000U
#define LRFDMDM32_EVT1_EVT0_RFEDAT_S                                        13U
#define LRFDMDM32_EVT1_EVT0_RFEDAT_ONE                              0x00002000U
#define LRFDMDM32_EVT1_EVT0_RFEDAT_ZERO                             0x00000000U

// Field:    [12] BDEC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_BDEC                                    0x00001000U
#define LRFDMDM32_EVT1_EVT0_BDEC_M                                  0x00001000U
#define LRFDMDM32_EVT1_EVT0_BDEC_S                                          12U
#define LRFDMDM32_EVT1_EVT0_BDEC_ONE                                0x00001000U
#define LRFDMDM32_EVT1_EVT0_BDEC_ZERO                               0x00000000U

// Field:    [11] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FRAC                                    0x00000800U
#define LRFDMDM32_EVT1_EVT0_FRAC_M                                  0x00000800U
#define LRFDMDM32_EVT1_EVT0_FRAC_S                                          11U
#define LRFDMDM32_EVT1_EVT0_FRAC_ONE                                0x00000800U
#define LRFDMDM32_EVT1_EVT0_FRAC_ZERO                               0x00000000U

// Field:    [10] SYSTIMEVT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT2                              0x00000400U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT2_M                            0x00000400U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT2_S                                    10U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT2_ONE                          0x00000400U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT2_ZERO                         0x00000000U

// Field:     [9] SYSTIMEVT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT1                              0x00000200U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT1_M                            0x00000200U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT1_S                                     9U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT1_ONE                          0x00000200U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT1_ZERO                         0x00000000U

// Field:     [8] SYSTIMEVT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT0                              0x00000100U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT0_M                            0x00000100U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT0_S                                     8U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT0_ONE                          0x00000100U
#define LRFDMDM32_EVT1_EVT0_SYSTIMEVT0_ZERO                         0x00000000U

// Field:     [7] FIFOWR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FIFOWR                                  0x00000080U
#define LRFDMDM32_EVT1_EVT0_FIFOWR_M                                0x00000080U
#define LRFDMDM32_EVT1_EVT0_FIFOWR_S                                         7U
#define LRFDMDM32_EVT1_EVT0_FIFOWR_ONE                              0x00000080U
#define LRFDMDM32_EVT1_EVT0_FIFOWR_ZERO                             0x00000000U

// Field:     [6] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_COUNTER                                 0x00000040U
#define LRFDMDM32_EVT1_EVT0_COUNTER_M                               0x00000040U
#define LRFDMDM32_EVT1_EVT0_COUNTER_S                                        6U
#define LRFDMDM32_EVT1_EVT0_COUNTER_ONE                             0x00000040U
#define LRFDMDM32_EVT1_EVT0_COUNTER_ZERO                            0x00000000U

// Field:     [5] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_RFECMD                                  0x00000020U
#define LRFDMDM32_EVT1_EVT0_RFECMD_M                                0x00000020U
#define LRFDMDM32_EVT1_EVT0_RFECMD_S                                         5U
#define LRFDMDM32_EVT1_EVT0_RFECMD_ONE                              0x00000020U
#define LRFDMDM32_EVT1_EVT0_RFECMD_ZERO                             0x00000000U

// Field:     [4] FIFOOVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FIFOOVFL                                0x00000010U
#define LRFDMDM32_EVT1_EVT0_FIFOOVFL_M                              0x00000010U
#define LRFDMDM32_EVT1_EVT0_FIFOOVFL_S                                       4U
#define LRFDMDM32_EVT1_EVT0_FIFOOVFL_ONE                            0x00000010U
#define LRFDMDM32_EVT1_EVT0_FIFOOVFL_ZERO                           0x00000000U

// Field:     [3] FIFOUNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_FIFOUNFL                                0x00000008U
#define LRFDMDM32_EVT1_EVT0_FIFOUNFL_M                              0x00000008U
#define LRFDMDM32_EVT1_EVT0_FIFOUNFL_S                                       3U
#define LRFDMDM32_EVT1_EVT0_FIFOUNFL_ONE                            0x00000008U
#define LRFDMDM32_EVT1_EVT0_FIFOUNFL_ZERO                           0x00000000U

// Field:     [2] CLKEN4BAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_CLKEN4BAUD                              0x00000004U
#define LRFDMDM32_EVT1_EVT0_CLKEN4BAUD_M                            0x00000004U
#define LRFDMDM32_EVT1_EVT0_CLKEN4BAUD_S                                     2U
#define LRFDMDM32_EVT1_EVT0_CLKEN4BAUD_ONE                          0x00000004U
#define LRFDMDM32_EVT1_EVT0_CLKEN4BAUD_ZERO                         0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_TIMER                                   0x00000002U
#define LRFDMDM32_EVT1_EVT0_TIMER_M                                 0x00000002U
#define LRFDMDM32_EVT1_EVT0_TIMER_S                                          1U
#define LRFDMDM32_EVT1_EVT0_TIMER_ONE                               0x00000002U
#define LRFDMDM32_EVT1_EVT0_TIMER_ZERO                              0x00000000U

// Field:     [0] MDMAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT1_EVT0_MDMAPI                                  0x00000001U
#define LRFDMDM32_EVT1_EVT0_MDMAPI_M                                0x00000001U
#define LRFDMDM32_EVT1_EVT0_MDMAPI_S                                         0U
#define LRFDMDM32_EVT1_EVT0_MDMAPI_ONE                              0x00000001U
#define LRFDMDM32_EVT1_EVT0_MDMAPI_ZERO                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVT2
//
//*****************************************************************************
// Field:    [15] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_GPI1                                         0x00008000U
#define LRFDMDM32_EVT2_GPI1_M                                       0x00008000U
#define LRFDMDM32_EVT2_GPI1_S                                               15U
#define LRFDMDM32_EVT2_GPI1_ONE                                     0x00008000U
#define LRFDMDM32_EVT2_GPI1_ZERO                                    0x00000000U

// Field:    [14] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_GPI0                                         0x00004000U
#define LRFDMDM32_EVT2_GPI0_M                                       0x00004000U
#define LRFDMDM32_EVT2_GPI0_S                                               14U
#define LRFDMDM32_EVT2_GPI0_ONE                                     0x00004000U
#define LRFDMDM32_EVT2_GPI0_ZERO                                    0x00000000U

// Field:    [12] C1BEBLOADED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEBLOADED                                  0x00001000U
#define LRFDMDM32_EVT2_C1BEBLOADED_M                                0x00001000U
#define LRFDMDM32_EVT2_C1BEBLOADED_S                                        12U
#define LRFDMDM32_EVT2_C1BEBLOADED_ONE                              0x00001000U
#define LRFDMDM32_EVT2_C1BEBLOADED_ZERO                             0x00000000U

// Field:    [11] C1BECMBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECMBANY                                   0x00000800U
#define LRFDMDM32_EVT2_C1BECMBANY_M                                 0x00000800U
#define LRFDMDM32_EVT2_C1BECMBANY_S                                         11U
#define LRFDMDM32_EVT2_C1BECMBANY_ONE                               0x00000800U
#define LRFDMDM32_EVT2_C1BECMBANY_ZERO                              0x00000000U

// Field:    [10] C1BECMBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECMBNEG                                   0x00000400U
#define LRFDMDM32_EVT2_C1BECMBNEG_M                                 0x00000400U
#define LRFDMDM32_EVT2_C1BECMBNEG_S                                         10U
#define LRFDMDM32_EVT2_C1BECMBNEG_ONE                               0x00000400U
#define LRFDMDM32_EVT2_C1BECMBNEG_ZERO                              0x00000000U

// Field:     [9] C1BECMBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECMBPOS                                   0x00000200U
#define LRFDMDM32_EVT2_C1BECMBPOS_M                                 0x00000200U
#define LRFDMDM32_EVT2_C1BECMBPOS_S                                          9U
#define LRFDMDM32_EVT2_C1BECMBPOS_ONE                               0x00000200U
#define LRFDMDM32_EVT2_C1BECMBPOS_ZERO                              0x00000000U

// Field:     [8] C1BECANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECANY                                     0x00000100U
#define LRFDMDM32_EVT2_C1BECANY_M                                   0x00000100U
#define LRFDMDM32_EVT2_C1BECANY_S                                            8U
#define LRFDMDM32_EVT2_C1BECANY_ONE                                 0x00000100U
#define LRFDMDM32_EVT2_C1BECANY_ZERO                                0x00000000U

// Field:     [7] C1BECNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECNEG                                     0x00000080U
#define LRFDMDM32_EVT2_C1BECNEG_M                                   0x00000080U
#define LRFDMDM32_EVT2_C1BECNEG_S                                            7U
#define LRFDMDM32_EVT2_C1BECNEG_ONE                                 0x00000080U
#define LRFDMDM32_EVT2_C1BECNEG_ZERO                                0x00000000U

// Field:     [6] C1BECPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BECPOS                                     0x00000040U
#define LRFDMDM32_EVT2_C1BECPOS_M                                   0x00000040U
#define LRFDMDM32_EVT2_C1BECPOS_S                                            6U
#define LRFDMDM32_EVT2_C1BECPOS_ONE                                 0x00000040U
#define LRFDMDM32_EVT2_C1BECPOS_ZERO                                0x00000000U

// Field:     [5] C1BEBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEBANY                                     0x00000020U
#define LRFDMDM32_EVT2_C1BEBANY_M                                   0x00000020U
#define LRFDMDM32_EVT2_C1BEBANY_S                                            5U
#define LRFDMDM32_EVT2_C1BEBANY_ONE                                 0x00000020U
#define LRFDMDM32_EVT2_C1BEBANY_ZERO                                0x00000000U

// Field:     [4] C1BEBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEBNEG                                     0x00000010U
#define LRFDMDM32_EVT2_C1BEBNEG_M                                   0x00000010U
#define LRFDMDM32_EVT2_C1BEBNEG_S                                            4U
#define LRFDMDM32_EVT2_C1BEBNEG_ONE                                 0x00000010U
#define LRFDMDM32_EVT2_C1BEBNEG_ZERO                                0x00000000U

// Field:     [3] C1BEBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEBPOS                                     0x00000008U
#define LRFDMDM32_EVT2_C1BEBPOS_M                                   0x00000008U
#define LRFDMDM32_EVT2_C1BEBPOS_S                                            3U
#define LRFDMDM32_EVT2_C1BEBPOS_ONE                                 0x00000008U
#define LRFDMDM32_EVT2_C1BEBPOS_ZERO                                0x00000000U

// Field:     [2] C1BEAANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEAANY                                     0x00000004U
#define LRFDMDM32_EVT2_C1BEAANY_M                                   0x00000004U
#define LRFDMDM32_EVT2_C1BEAANY_S                                            2U
#define LRFDMDM32_EVT2_C1BEAANY_ONE                                 0x00000004U
#define LRFDMDM32_EVT2_C1BEAANY_ZERO                                0x00000000U

// Field:     [1] C1BEANEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEANEG                                     0x00000002U
#define LRFDMDM32_EVT2_C1BEANEG_M                                   0x00000002U
#define LRFDMDM32_EVT2_C1BEANEG_S                                            1U
#define LRFDMDM32_EVT2_C1BEANEG_ONE                                 0x00000002U
#define LRFDMDM32_EVT2_C1BEANEG_ZERO                                0x00000000U

// Field:     [0] C1BEAPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVT2_C1BEAPOS                                     0x00000001U
#define LRFDMDM32_EVT2_C1BEAPOS_M                                   0x00000001U
#define LRFDMDM32_EVT2_C1BEAPOS_S                                            0U
#define LRFDMDM32_EVT2_C1BEAPOS_ONE                                 0x00000001U
#define LRFDMDM32_EVT2_C1BEAPOS_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVTMSK1_EVTMSK0
//
//*****************************************************************************
// Field:    [24] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_REFCLK                            0x01000000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_REFCLK_M                          0x01000000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_REFCLK_S                                  24U
#define LRFDMDM32_EVTMSK1_EVTMSK0_REFCLK_EN                         0x01000000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_REFCLK_DIS                        0x00000000U

// Field:    [23] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_S2RSTOP                           0x00800000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_S2RSTOP_M                         0x00800000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_S2RSTOP_S                                 23U
#define LRFDMDM32_EVTMSK1_EVTMSK0_S2RSTOP_EN                        0x00800000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_S2RSTOP_DIS                       0x00000000U

// Field:    [22] SWQUFALSESYNC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUFALSESYNC                     0x00400000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUFALSESYNC_M                   0x00400000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUFALSESYNC_S                           22U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUFALSESYNC_EN                  0x00400000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUFALSESYNC_DIS                 0x00000000U

// Field:    [21] SWQUSYNCED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUSYNCED                        0x00200000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUSYNCED_M                      0x00200000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUSYNCED_S                              21U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUSYNCED_EN                     0x00200000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SWQUSYNCED_DIS                    0x00000000U

// Field:    [20] CLKENBAUDF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUDF                        0x00100000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUDF_M                      0x00100000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUDF_S                              20U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUDF_EN                     0x00100000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUDF_DIS                    0x00000000U

// Field:    [19] FIFORVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFORVALID                        0x00080000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFORVALID_M                      0x00080000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFORVALID_S                              19U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFORVALID_EN                     0x00080000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFORVALID_DIS                    0x00000000U

// Field:    [18] FIFOWREADY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWREADY                        0x00040000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWREADY_M                      0x00040000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWREADY_S                              18U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWREADY_EN                     0x00040000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWREADY_DIS                    0x00000000U

// Field:    [17] CLKENBAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUD                         0x00020000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUD_M                       0x00020000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUD_S                               17U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUD_EN                      0x00020000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKENBAUD_DIS                     0x00000000U

// Field:    [16] PREAMBLEDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_PREAMBLEDONE                      0x00010000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PREAMBLEDONE_M                    0x00010000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PREAMBLEDONE_S                            16U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PREAMBLEDONE_EN                   0x00010000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PREAMBLEDONE_DIS                  0x00000000U

// Field:    [15] PBEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBEDAT                            0x00008000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBEDAT_M                          0x00008000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBEDAT_S                                  15U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBEDAT_EN                         0x00008000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBEDAT_DIS                        0x00000000U

// Field:    [14] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBECMD                            0x00004000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBECMD_M                          0x00004000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBECMD_S                                  14U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBECMD_EN                         0x00004000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_PBECMD_DIS                        0x00000000U

// Field:    [13] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFEDAT                            0x00002000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFEDAT_M                          0x00002000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFEDAT_S                                  13U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFEDAT_EN                         0x00002000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFEDAT_DIS                        0x00000000U

// Field:    [12] BDEC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_BDEC                              0x00001000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_BDEC_M                            0x00001000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_BDEC_S                                    12U
#define LRFDMDM32_EVTMSK1_EVTMSK0_BDEC_EN                           0x00001000U
#define LRFDMDM32_EVTMSK1_EVTMSK0_BDEC_DIS                          0x00000000U

// Field:    [11] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FRAC                              0x00000800U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FRAC_M                            0x00000800U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FRAC_S                                    11U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FRAC_EN                           0x00000800U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FRAC_DIS                          0x00000000U

// Field:    [10] SYSTIMEVT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT2                        0x00000400U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT2_M                      0x00000400U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT2_S                              10U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT2_EN                     0x00000400U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT2_DIS                    0x00000000U

// Field:     [9] SYSTIMEVT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT1                        0x00000200U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT1_M                      0x00000200U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT1_S                               9U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT1_EN                     0x00000200U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT1_DIS                    0x00000000U

// Field:     [8] SYSTIMEVT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT0                        0x00000100U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT0_M                      0x00000100U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT0_S                               8U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT0_EN                     0x00000100U
#define LRFDMDM32_EVTMSK1_EVTMSK0_SYSTIMEVT0_DIS                    0x00000000U

// Field:     [7] FIFOWR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWR                            0x00000080U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWR_M                          0x00000080U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWR_S                                   7U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWR_EN                         0x00000080U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOWR_DIS                        0x00000000U

// Field:     [6] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_COUNTER                           0x00000040U
#define LRFDMDM32_EVTMSK1_EVTMSK0_COUNTER_M                         0x00000040U
#define LRFDMDM32_EVTMSK1_EVTMSK0_COUNTER_S                                  6U
#define LRFDMDM32_EVTMSK1_EVTMSK0_COUNTER_EN                        0x00000040U
#define LRFDMDM32_EVTMSK1_EVTMSK0_COUNTER_DIS                       0x00000000U

// Field:     [5] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFECMD                            0x00000020U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFECMD_M                          0x00000020U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFECMD_S                                   5U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFECMD_EN                         0x00000020U
#define LRFDMDM32_EVTMSK1_EVTMSK0_RFECMD_DIS                        0x00000000U

// Field:     [4] FIFOOVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOOVFL                          0x00000010U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOOVFL_M                        0x00000010U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOOVFL_S                                 4U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOOVFL_EN                       0x00000010U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOOVFL_DIS                      0x00000000U

// Field:     [3] FIFOUNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOUNFL                          0x00000008U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOUNFL_M                        0x00000008U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOUNFL_S                                 3U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOUNFL_EN                       0x00000008U
#define LRFDMDM32_EVTMSK1_EVTMSK0_FIFOUNFL_DIS                      0x00000000U

// Field:     [2] CLKEN4BAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKEN4BAUD                        0x00000004U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKEN4BAUD_M                      0x00000004U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKEN4BAUD_S                               2U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKEN4BAUD_EN                     0x00000004U
#define LRFDMDM32_EVTMSK1_EVTMSK0_CLKEN4BAUD_DIS                    0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_TIMER                             0x00000002U
#define LRFDMDM32_EVTMSK1_EVTMSK0_TIMER_M                           0x00000002U
#define LRFDMDM32_EVTMSK1_EVTMSK0_TIMER_S                                    1U
#define LRFDMDM32_EVTMSK1_EVTMSK0_TIMER_EN                          0x00000002U
#define LRFDMDM32_EVTMSK1_EVTMSK0_TIMER_DIS                         0x00000000U

// Field:     [0] MDMAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK1_EVTMSK0_MDMAPI                            0x00000001U
#define LRFDMDM32_EVTMSK1_EVTMSK0_MDMAPI_M                          0x00000001U
#define LRFDMDM32_EVTMSK1_EVTMSK0_MDMAPI_S                                   0U
#define LRFDMDM32_EVTMSK1_EVTMSK0_MDMAPI_EN                         0x00000001U
#define LRFDMDM32_EVTMSK1_EVTMSK0_MDMAPI_DIS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVTMSK2
//
//*****************************************************************************
// Field:    [15] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_GPI1                                      0x00008000U
#define LRFDMDM32_EVTMSK2_GPI1_M                                    0x00008000U
#define LRFDMDM32_EVTMSK2_GPI1_S                                            15U
#define LRFDMDM32_EVTMSK2_GPI1_EN                                   0x00008000U
#define LRFDMDM32_EVTMSK2_GPI1_DIS                                  0x00000000U

// Field:    [14] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_GPI0                                      0x00004000U
#define LRFDMDM32_EVTMSK2_GPI0_M                                    0x00004000U
#define LRFDMDM32_EVTMSK2_GPI0_S                                            14U
#define LRFDMDM32_EVTMSK2_GPI0_EN                                   0x00004000U
#define LRFDMDM32_EVTMSK2_GPI0_DIS                                  0x00000000U

// Field:    [12] C1BEBLOADED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEBLOADED                               0x00001000U
#define LRFDMDM32_EVTMSK2_C1BEBLOADED_M                             0x00001000U
#define LRFDMDM32_EVTMSK2_C1BEBLOADED_S                                     12U
#define LRFDMDM32_EVTMSK2_C1BEBLOADED_EN                            0x00001000U
#define LRFDMDM32_EVTMSK2_C1BEBLOADED_DIS                           0x00000000U

// Field:    [11] C1BECMBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECMBANY                                0x00000800U
#define LRFDMDM32_EVTMSK2_C1BECMBANY_M                              0x00000800U
#define LRFDMDM32_EVTMSK2_C1BECMBANY_S                                      11U
#define LRFDMDM32_EVTMSK2_C1BECMBANY_EN                             0x00000800U
#define LRFDMDM32_EVTMSK2_C1BECMBANY_DIS                            0x00000000U

// Field:    [10] C1BECMBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECMBNEG                                0x00000400U
#define LRFDMDM32_EVTMSK2_C1BECMBNEG_M                              0x00000400U
#define LRFDMDM32_EVTMSK2_C1BECMBNEG_S                                      10U
#define LRFDMDM32_EVTMSK2_C1BECMBNEG_EN                             0x00000400U
#define LRFDMDM32_EVTMSK2_C1BECMBNEG_DIS                            0x00000000U

// Field:     [9] C1BECMBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECMBPOS                                0x00000200U
#define LRFDMDM32_EVTMSK2_C1BECMBPOS_M                              0x00000200U
#define LRFDMDM32_EVTMSK2_C1BECMBPOS_S                                       9U
#define LRFDMDM32_EVTMSK2_C1BECMBPOS_EN                             0x00000200U
#define LRFDMDM32_EVTMSK2_C1BECMBPOS_DIS                            0x00000000U

// Field:     [8] C1BECANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECANY                                  0x00000100U
#define LRFDMDM32_EVTMSK2_C1BECANY_M                                0x00000100U
#define LRFDMDM32_EVTMSK2_C1BECANY_S                                         8U
#define LRFDMDM32_EVTMSK2_C1BECANY_EN                               0x00000100U
#define LRFDMDM32_EVTMSK2_C1BECANY_DIS                              0x00000000U

// Field:     [7] C1BECNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECNEG                                  0x00000080U
#define LRFDMDM32_EVTMSK2_C1BECNEG_M                                0x00000080U
#define LRFDMDM32_EVTMSK2_C1BECNEG_S                                         7U
#define LRFDMDM32_EVTMSK2_C1BECNEG_EN                               0x00000080U
#define LRFDMDM32_EVTMSK2_C1BECNEG_DIS                              0x00000000U

// Field:     [6] C1BECPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BECPOS                                  0x00000040U
#define LRFDMDM32_EVTMSK2_C1BECPOS_M                                0x00000040U
#define LRFDMDM32_EVTMSK2_C1BECPOS_S                                         6U
#define LRFDMDM32_EVTMSK2_C1BECPOS_EN                               0x00000040U
#define LRFDMDM32_EVTMSK2_C1BECPOS_DIS                              0x00000000U

// Field:     [5] C1BEBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEBANY                                  0x00000020U
#define LRFDMDM32_EVTMSK2_C1BEBANY_M                                0x00000020U
#define LRFDMDM32_EVTMSK2_C1BEBANY_S                                         5U
#define LRFDMDM32_EVTMSK2_C1BEBANY_EN                               0x00000020U
#define LRFDMDM32_EVTMSK2_C1BEBANY_DIS                              0x00000000U

// Field:     [4] C1BEBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEBNEG                                  0x00000010U
#define LRFDMDM32_EVTMSK2_C1BEBNEG_M                                0x00000010U
#define LRFDMDM32_EVTMSK2_C1BEBNEG_S                                         4U
#define LRFDMDM32_EVTMSK2_C1BEBNEG_EN                               0x00000010U
#define LRFDMDM32_EVTMSK2_C1BEBNEG_DIS                              0x00000000U

// Field:     [3] C1BEBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEBPOS                                  0x00000008U
#define LRFDMDM32_EVTMSK2_C1BEBPOS_M                                0x00000008U
#define LRFDMDM32_EVTMSK2_C1BEBPOS_S                                         3U
#define LRFDMDM32_EVTMSK2_C1BEBPOS_EN                               0x00000008U
#define LRFDMDM32_EVTMSK2_C1BEBPOS_DIS                              0x00000000U

// Field:     [2] C1BEAANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEAANY                                  0x00000004U
#define LRFDMDM32_EVTMSK2_C1BEAANY_M                                0x00000004U
#define LRFDMDM32_EVTMSK2_C1BEAANY_S                                         2U
#define LRFDMDM32_EVTMSK2_C1BEAANY_EN                               0x00000004U
#define LRFDMDM32_EVTMSK2_C1BEAANY_DIS                              0x00000000U

// Field:     [1] C1BEANEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEANEG                                  0x00000002U
#define LRFDMDM32_EVTMSK2_C1BEANEG_M                                0x00000002U
#define LRFDMDM32_EVTMSK2_C1BEANEG_S                                         1U
#define LRFDMDM32_EVTMSK2_C1BEANEG_EN                               0x00000002U
#define LRFDMDM32_EVTMSK2_C1BEANEG_DIS                              0x00000000U

// Field:     [0] C1BEAPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTMSK2_C1BEAPOS                                  0x00000001U
#define LRFDMDM32_EVTMSK2_C1BEAPOS_M                                0x00000001U
#define LRFDMDM32_EVTMSK2_C1BEAPOS_S                                         0U
#define LRFDMDM32_EVTMSK2_C1BEAPOS_EN                               0x00000001U
#define LRFDMDM32_EVTMSK2_C1BEAPOS_DIS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVTCLR1_EVTCLR0
//
//*****************************************************************************
// Field:    [24] REFCLK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_REFCLK                            0x01000000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_REFCLK_M                          0x01000000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_REFCLK_S                                  24U
#define LRFDMDM32_EVTCLR1_EVTCLR0_REFCLK_CLEAR                      0x01000000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_REFCLK_RETAIN                     0x00000000U

// Field:    [23] S2RSTOP
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_S2RSTOP                           0x00800000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_S2RSTOP_M                         0x00800000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_S2RSTOP_S                                 23U
#define LRFDMDM32_EVTCLR1_EVTCLR0_S2RSTOP_CLEAR                     0x00800000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_S2RSTOP_RETAIN                    0x00000000U

// Field:    [22] SWQUFALSESYNC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUFALSESYNC                     0x00400000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUFALSESYNC_M                   0x00400000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUFALSESYNC_S                           22U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUFALSESYNC_CLEAR               0x00400000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUFALSESYNC_RETAIN              0x00000000U

// Field:    [21] SWQUSYNCED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUSYNCED                        0x00200000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUSYNCED_M                      0x00200000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUSYNCED_S                              21U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUSYNCED_CLEAR                  0x00200000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SWQUSYNCED_RETAIN                 0x00000000U

// Field:    [20] CLKENBAUDF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUDF                        0x00100000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUDF_M                      0x00100000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUDF_S                              20U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUDF_CLEAR                  0x00100000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUDF_RETAIN                 0x00000000U

// Field:    [19] FIFORVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFORVALID                        0x00080000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFORVALID_M                      0x00080000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFORVALID_S                              19U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFORVALID_CLEAR                  0x00080000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFORVALID_RETAIN                 0x00000000U

// Field:    [18] FIFOWREADY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWREADY                        0x00040000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWREADY_M                      0x00040000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWREADY_S                              18U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWREADY_CLEAR                  0x00040000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWREADY_RETAIN                 0x00000000U

// Field:    [17] CLKENBAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUD                         0x00020000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUD_M                       0x00020000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUD_S                               17U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUD_CLEAR                   0x00020000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKENBAUD_RETAIN                  0x00000000U

// Field:    [16] PREAMBLEDONE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_PREAMBLEDONE                      0x00010000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PREAMBLEDONE_M                    0x00010000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PREAMBLEDONE_S                            16U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PREAMBLEDONE_CLEAR                0x00010000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PREAMBLEDONE_RETAIN               0x00000000U

// Field:    [15] PBEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBEDAT                            0x00008000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBEDAT_M                          0x00008000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBEDAT_S                                  15U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBEDAT_CLEAR                      0x00008000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBEDAT_RETAIN                     0x00000000U

// Field:    [14] PBECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBECMD                            0x00004000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBECMD_M                          0x00004000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBECMD_S                                  14U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBECMD_CLEAR                      0x00004000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_PBECMD_RETAIN                     0x00000000U

// Field:    [13] RFEDAT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFEDAT                            0x00002000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFEDAT_M                          0x00002000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFEDAT_S                                  13U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFEDAT_CLEAR                      0x00002000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFEDAT_RETAIN                     0x00000000U

// Field:    [12] BDEC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_BDEC                              0x00001000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_BDEC_M                            0x00001000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_BDEC_S                                    12U
#define LRFDMDM32_EVTCLR1_EVTCLR0_BDEC_CLEAR                        0x00001000U
#define LRFDMDM32_EVTCLR1_EVTCLR0_BDEC_RETAIN                       0x00000000U

// Field:    [11] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FRAC                              0x00000800U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FRAC_M                            0x00000800U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FRAC_S                                    11U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FRAC_CLEAR                        0x00000800U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FRAC_RETAIN                       0x00000000U

// Field:    [10] SYSTIMEVT2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT2                        0x00000400U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT2_M                      0x00000400U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT2_S                              10U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT2_CLEAR                  0x00000400U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT2_RETAIN                 0x00000000U

// Field:     [9] SYSTIMEVT1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT1                        0x00000200U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT1_M                      0x00000200U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT1_S                               9U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT1_CLEAR                  0x00000200U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT1_RETAIN                 0x00000000U

// Field:     [8] SYSTIMEVT0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT0                        0x00000100U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT0_M                      0x00000100U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT0_S                               8U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT0_CLEAR                  0x00000100U
#define LRFDMDM32_EVTCLR1_EVTCLR0_SYSTIMEVT0_RETAIN                 0x00000000U

// Field:     [7] FIFOWR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWR                            0x00000080U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWR_M                          0x00000080U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWR_S                                   7U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWR_CLEAR                      0x00000080U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOWR_RETAIN                     0x00000000U

// Field:     [6] COUNTER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_COUNTER                           0x00000040U
#define LRFDMDM32_EVTCLR1_EVTCLR0_COUNTER_M                         0x00000040U
#define LRFDMDM32_EVTCLR1_EVTCLR0_COUNTER_S                                  6U
#define LRFDMDM32_EVTCLR1_EVTCLR0_COUNTER_CLEAR                     0x00000040U
#define LRFDMDM32_EVTCLR1_EVTCLR0_COUNTER_RETAIN                    0x00000000U

// Field:     [5] RFECMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFECMD                            0x00000020U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFECMD_M                          0x00000020U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFECMD_S                                   5U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFECMD_CLEAR                      0x00000020U
#define LRFDMDM32_EVTCLR1_EVTCLR0_RFECMD_RETAIN                     0x00000000U

// Field:     [4] FIFOOVFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOOVFL                          0x00000010U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOOVFL_M                        0x00000010U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOOVFL_S                                 4U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOOVFL_CLEAR                    0x00000010U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOOVFL_RETAIN                   0x00000000U

// Field:     [3] FIFOUNFL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOUNFL                          0x00000008U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOUNFL_M                        0x00000008U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOUNFL_S                                 3U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOUNFL_CLEAR                    0x00000008U
#define LRFDMDM32_EVTCLR1_EVTCLR0_FIFOUNFL_RETAIN                   0x00000000U

// Field:     [2] CLKEN4BAUD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKEN4BAUD                        0x00000004U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKEN4BAUD_M                      0x00000004U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKEN4BAUD_S                               2U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKEN4BAUD_CLEAR                  0x00000004U
#define LRFDMDM32_EVTCLR1_EVTCLR0_CLKEN4BAUD_RETAIN                 0x00000000U

// Field:     [1] TIMER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_TIMER                             0x00000002U
#define LRFDMDM32_EVTCLR1_EVTCLR0_TIMER_M                           0x00000002U
#define LRFDMDM32_EVTCLR1_EVTCLR0_TIMER_S                                    1U
#define LRFDMDM32_EVTCLR1_EVTCLR0_TIMER_CLEAR                       0x00000002U
#define LRFDMDM32_EVTCLR1_EVTCLR0_TIMER_RETAIN                      0x00000000U

// Field:     [0] MDMAPI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR1_EVTCLR0_MDMAPI                            0x00000001U
#define LRFDMDM32_EVTCLR1_EVTCLR0_MDMAPI_M                          0x00000001U
#define LRFDMDM32_EVTCLR1_EVTCLR0_MDMAPI_S                                   0U
#define LRFDMDM32_EVTCLR1_EVTCLR0_MDMAPI_CLEAR                      0x00000001U
#define LRFDMDM32_EVTCLR1_EVTCLR0_MDMAPI_RETAIN                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_EVTCLR2
//
//*****************************************************************************
// Field:    [15] GPI1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_GPI1                                      0x00008000U
#define LRFDMDM32_EVTCLR2_GPI1_M                                    0x00008000U
#define LRFDMDM32_EVTCLR2_GPI1_S                                            15U
#define LRFDMDM32_EVTCLR2_GPI1_CLEAR                                0x00008000U
#define LRFDMDM32_EVTCLR2_GPI1_RETAIN                               0x00000000U

// Field:    [14] GPI0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_GPI0                                      0x00004000U
#define LRFDMDM32_EVTCLR2_GPI0_M                                    0x00004000U
#define LRFDMDM32_EVTCLR2_GPI0_S                                            14U
#define LRFDMDM32_EVTCLR2_GPI0_CLEAR                                0x00004000U
#define LRFDMDM32_EVTCLR2_GPI0_RETAIN                               0x00000000U

// Field:    [12] C1BEBLOADED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEBLOADED                               0x00001000U
#define LRFDMDM32_EVTCLR2_C1BEBLOADED_M                             0x00001000U
#define LRFDMDM32_EVTCLR2_C1BEBLOADED_S                                     12U
#define LRFDMDM32_EVTCLR2_C1BEBLOADED_CLEAR                         0x00001000U
#define LRFDMDM32_EVTCLR2_C1BEBLOADED_RETAIN                        0x00000000U

// Field:    [11] C1BECMBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECMBANY                                0x00000800U
#define LRFDMDM32_EVTCLR2_C1BECMBANY_M                              0x00000800U
#define LRFDMDM32_EVTCLR2_C1BECMBANY_S                                      11U
#define LRFDMDM32_EVTCLR2_C1BECMBANY_CLEAR                          0x00000800U
#define LRFDMDM32_EVTCLR2_C1BECMBANY_RETAIN                         0x00000000U

// Field:    [10] C1BECMBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECMBNEG                                0x00000400U
#define LRFDMDM32_EVTCLR2_C1BECMBNEG_M                              0x00000400U
#define LRFDMDM32_EVTCLR2_C1BECMBNEG_S                                      10U
#define LRFDMDM32_EVTCLR2_C1BECMBNEG_CLEAR                          0x00000400U
#define LRFDMDM32_EVTCLR2_C1BECMBNEG_RETAIN                         0x00000000U

// Field:     [9] C1BECMBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECMBPOS                                0x00000200U
#define LRFDMDM32_EVTCLR2_C1BECMBPOS_M                              0x00000200U
#define LRFDMDM32_EVTCLR2_C1BECMBPOS_S                                       9U
#define LRFDMDM32_EVTCLR2_C1BECMBPOS_CLEAR                          0x00000200U
#define LRFDMDM32_EVTCLR2_C1BECMBPOS_RETAIN                         0x00000000U

// Field:     [8] C1BECANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECANY                                  0x00000100U
#define LRFDMDM32_EVTCLR2_C1BECANY_M                                0x00000100U
#define LRFDMDM32_EVTCLR2_C1BECANY_S                                         8U
#define LRFDMDM32_EVTCLR2_C1BECANY_CLEAR                            0x00000100U
#define LRFDMDM32_EVTCLR2_C1BECANY_RETAIN                           0x00000000U

// Field:     [7] C1BECNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECNEG                                  0x00000080U
#define LRFDMDM32_EVTCLR2_C1BECNEG_M                                0x00000080U
#define LRFDMDM32_EVTCLR2_C1BECNEG_S                                         7U
#define LRFDMDM32_EVTCLR2_C1BECNEG_CLEAR                            0x00000080U
#define LRFDMDM32_EVTCLR2_C1BECNEG_RETAIN                           0x00000000U

// Field:     [6] C1BECPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BECPOS                                  0x00000040U
#define LRFDMDM32_EVTCLR2_C1BECPOS_M                                0x00000040U
#define LRFDMDM32_EVTCLR2_C1BECPOS_S                                         6U
#define LRFDMDM32_EVTCLR2_C1BECPOS_CLEAR                            0x00000040U
#define LRFDMDM32_EVTCLR2_C1BECPOS_RETAIN                           0x00000000U

// Field:     [5] C1BEBANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEBANY                                  0x00000020U
#define LRFDMDM32_EVTCLR2_C1BEBANY_M                                0x00000020U
#define LRFDMDM32_EVTCLR2_C1BEBANY_S                                         5U
#define LRFDMDM32_EVTCLR2_C1BEBANY_CLEAR                            0x00000020U
#define LRFDMDM32_EVTCLR2_C1BEBANY_RETAIN                           0x00000000U

// Field:     [4] C1BEBNEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEBNEG                                  0x00000010U
#define LRFDMDM32_EVTCLR2_C1BEBNEG_M                                0x00000010U
#define LRFDMDM32_EVTCLR2_C1BEBNEG_S                                         4U
#define LRFDMDM32_EVTCLR2_C1BEBNEG_CLEAR                            0x00000010U
#define LRFDMDM32_EVTCLR2_C1BEBNEG_RETAIN                           0x00000000U

// Field:     [3] C1BEBPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEBPOS                                  0x00000008U
#define LRFDMDM32_EVTCLR2_C1BEBPOS_M                                0x00000008U
#define LRFDMDM32_EVTCLR2_C1BEBPOS_S                                         3U
#define LRFDMDM32_EVTCLR2_C1BEBPOS_CLEAR                            0x00000008U
#define LRFDMDM32_EVTCLR2_C1BEBPOS_RETAIN                           0x00000000U

// Field:     [2] C1BEAANY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEAANY                                  0x00000004U
#define LRFDMDM32_EVTCLR2_C1BEAANY_M                                0x00000004U
#define LRFDMDM32_EVTCLR2_C1BEAANY_S                                         2U
#define LRFDMDM32_EVTCLR2_C1BEAANY_CLEAR                            0x00000004U
#define LRFDMDM32_EVTCLR2_C1BEAANY_RETAIN                           0x00000000U

// Field:     [1] C1BEANEG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEANEG                                  0x00000002U
#define LRFDMDM32_EVTCLR2_C1BEANEG_M                                0x00000002U
#define LRFDMDM32_EVTCLR2_C1BEANEG_S                                         1U
#define LRFDMDM32_EVTCLR2_C1BEANEG_CLEAR                            0x00000002U
#define LRFDMDM32_EVTCLR2_C1BEANEG_RETAIN                           0x00000000U

// Field:     [0] C1BEAPOS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLEAR                    Internal. Only to be used through TI provided API.
// RETAIN                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_EVTCLR2_C1BEAPOS                                  0x00000001U
#define LRFDMDM32_EVTCLR2_C1BEAPOS_M                                0x00000001U
#define LRFDMDM32_EVTCLR2_C1BEAPOS_S                                         0U
#define LRFDMDM32_EVTCLR2_C1BEAPOS_CLEAR                            0x00000001U
#define LRFDMDM32_EVTCLR2_C1BEAPOS_RETAIN                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_API_PDREQ
//
//*****************************************************************************
// Field: [23:20] PROTOCOLID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_API_PDREQ_PROTOCOLID_W                                     4U
#define LRFDMDM32_API_PDREQ_PROTOCOLID_M                            0x00F00000U
#define LRFDMDM32_API_PDREQ_PROTOCOLID_S                                    20U
#define LRFDMDM32_API_PDREQ_PROTOCOLID_ALLONES                      0x00F00000U
#define LRFDMDM32_API_PDREQ_PROTOCOLID_ALLZEROS                     0x00000000U

// Field: [19:16] MDMCMD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_API_PDREQ_MDMCMD_W                                         4U
#define LRFDMDM32_API_PDREQ_MDMCMD_M                                0x000F0000U
#define LRFDMDM32_API_PDREQ_MDMCMD_S                                        16U
#define LRFDMDM32_API_PDREQ_MDMCMD_ALLONES                          0x000F0000U
#define LRFDMDM32_API_PDREQ_MDMCMD_ALLZEROS                         0x00000000U

// Field:     [0] TOPSMPDREQ
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_API_PDREQ_TOPSMPDREQ                              0x00000001U
#define LRFDMDM32_API_PDREQ_TOPSMPDREQ_M                            0x00000001U
#define LRFDMDM32_API_PDREQ_TOPSMPDREQ_S                                     0U
#define LRFDMDM32_API_PDREQ_TOPSMPDREQ_ON                           0x00000001U
#define LRFDMDM32_API_PDREQ_TOPSMPDREQ_OFF                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_CMDPAR1_CMDPAR0
//
//*****************************************************************************
// Field: [31:16] CMDPAR1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR1_VAL_W                             16U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR1_VAL_M                     0xFFFF0000U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR1_VAL_S                             16U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR1_VAL_ALLONES               0xFFFF0000U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR1_VAL_ALLZEROS              0x00000000U

// Field:  [15:0] CMDPAR0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR0_VAL_W                             16U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR0_VAL_M                     0x0000FFFFU
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR0_VAL_S                              0U
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR0_VAL_ALLONES               0x0000FFFFU
#define LRFDMDM32_CMDPAR1_CMDPAR0_CMDPAR0_VAL_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MSGBOX_CMDPAR2
//
//*****************************************************************************
// Field: [23:16] MSGBOX_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MSGBOX_CMDPAR2_MSGBOX_VAL_W                                8U
#define LRFDMDM32_MSGBOX_CMDPAR2_MSGBOX_VAL_M                       0x00FF0000U
#define LRFDMDM32_MSGBOX_CMDPAR2_MSGBOX_VAL_S                               16U
#define LRFDMDM32_MSGBOX_CMDPAR2_MSGBOX_VAL_ALLONES                 0x00FF0000U
#define LRFDMDM32_MSGBOX_CMDPAR2_MSGBOX_VAL_ALLZEROS                0x00000000U

// Field:  [15:0] CMDPAR2_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MSGBOX_CMDPAR2_CMDPAR2_VAL_W                              16U
#define LRFDMDM32_MSGBOX_CMDPAR2_CMDPAR2_VAL_M                      0x0000FFFFU
#define LRFDMDM32_MSGBOX_CMDPAR2_CMDPAR2_VAL_S                               0U
#define LRFDMDM32_MSGBOX_CMDPAR2_CMDPAR2_VAL_ALLONES                0x0000FFFFU
#define LRFDMDM32_MSGBOX_CMDPAR2_CMDPAR2_VAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FIFOWR_FREQ
//
//*****************************************************************************
// Field: [31:16] PAYLOADIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOWR_FREQ_PAYLOADIN_W                                   16U
#define LRFDMDM32_FIFOWR_FREQ_PAYLOADIN_M                           0xFFFF0000U
#define LRFDMDM32_FIFOWR_FREQ_PAYLOADIN_S                                   16U
#define LRFDMDM32_FIFOWR_FREQ_PAYLOADIN_ALLONES                     0xFFFF0000U
#define LRFDMDM32_FIFOWR_FREQ_PAYLOADIN_ALLZEROS                    0x00000000U

// Field:  [15:0] OFFSET
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOWR_FREQ_OFFSET_W                                      16U
#define LRFDMDM32_FIFOWR_FREQ_OFFSET_M                              0x0000FFFFU
#define LRFDMDM32_FIFOWR_FREQ_OFFSET_S                                       0U
#define LRFDMDM32_FIFOWR_FREQ_OFFSET_ALLONES                        0x0000FFFFU
#define LRFDMDM32_FIFOWR_FREQ_OFFSET_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FIFORD
//
//*****************************************************************************
// Field:  [15:0] PAYLOADOUT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFORD_PAYLOADOUT_W                                       16U
#define LRFDMDM32_FIFORD_PAYLOADOUT_M                               0x0000FFFFU
#define LRFDMDM32_FIFORD_PAYLOADOUT_S                                        0U
#define LRFDMDM32_FIFORD_PAYLOADOUT_ALLONES                         0x0000FFFFU
#define LRFDMDM32_FIFORD_PAYLOADOUT_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FIFORDCTRL_FIFOWRCTRL
//
//*****************************************************************************
// Field: [21:20] FIFORDPORT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PBE                      Internal. Only to be used through TI provided API.
// MODEM                    Internal. Only to be used through TI provided API.
// MDMFIFORD                Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_W                         2U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_M                0x00300000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_S                        20U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_PBE              0x00200000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_MODEM            0x00100000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFORDPORT_MDMFIFORD        0x00000000U

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
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_W                           4U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_M                  0x000F0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_S                          16U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS16             0x000F0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS15             0x000E0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS14             0x000D0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS13             0x000C0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS12             0x000B0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS11             0x000A0000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS10             0x00090000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS9              0x00080000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS8              0x00070000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS7              0x00060000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS6              0x00050000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS5              0x00040000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS4              0x00030000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS3              0x00020000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS2              0x00010000U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZRD_BITS1              0x00000000U

// Field:   [5:4] FIFOWRPORT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PBE                      Internal. Only to be used through TI provided API.
// MODEM                    Internal. Only to be used through TI provided API.
// MDMFIFOWR                Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_W                         2U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_M                0x00000030U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_S                         4U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_PBE              0x00000020U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_MODEM            0x00000010U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_FIFOWRPORT_MDMFIFOWR        0x00000000U

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
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_W                           4U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_M                  0x0000000FU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_S                           0U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS16             0x0000000FU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS15             0x0000000EU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS14             0x0000000DU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS13             0x0000000CU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS12             0x0000000BU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS11             0x0000000AU
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS10             0x00000009U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS9              0x00000008U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS8              0x00000007U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS7              0x00000006U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS6              0x00000005U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS5              0x00000004U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS4              0x00000003U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS3              0x00000002U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS2              0x00000001U
#define LRFDMDM32_FIFORDCTRL_FIFOWRCTRL_WORDSZWR_BITS1              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FIFOSTA
//
//*****************************************************************************
// Field:    [21] OVERFLOW
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_OVERFLOW                                  0x00200000U
#define LRFDMDM32_FIFOSTA_OVERFLOW_M                                0x00200000U
#define LRFDMDM32_FIFOSTA_OVERFLOW_S                                        21U
#define LRFDMDM32_FIFOSTA_OVERFLOW_ONE                              0x00200000U
#define LRFDMDM32_FIFOSTA_OVERFLOW_ZERO                             0x00000000U

// Field:    [20] ALMOSTFULL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_ALMOSTFULL                                0x00100000U
#define LRFDMDM32_FIFOSTA_ALMOSTFULL_M                              0x00100000U
#define LRFDMDM32_FIFOSTA_ALMOSTFULL_S                                      20U
#define LRFDMDM32_FIFOSTA_ALMOSTFULL_ONE                            0x00100000U
#define LRFDMDM32_FIFOSTA_ALMOSTFULL_ZERO                           0x00000000U

// Field:    [19] ALMOSTEMPTY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_ALMOSTEMPTY                               0x00080000U
#define LRFDMDM32_FIFOSTA_ALMOSTEMPTY_M                             0x00080000U
#define LRFDMDM32_FIFOSTA_ALMOSTEMPTY_S                                     19U
#define LRFDMDM32_FIFOSTA_ALMOSTEMPTY_ONE                           0x00080000U
#define LRFDMDM32_FIFOSTA_ALMOSTEMPTY_ZERO                          0x00000000U

// Field:    [18] UNDERFLOW
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_UNDERFLOW                                 0x00040000U
#define LRFDMDM32_FIFOSTA_UNDERFLOW_M                               0x00040000U
#define LRFDMDM32_FIFOSTA_UNDERFLOW_S                                       18U
#define LRFDMDM32_FIFOSTA_UNDERFLOW_ONE                             0x00040000U
#define LRFDMDM32_FIFOSTA_UNDERFLOW_ZERO                            0x00000000U

// Field:    [17] RXVALID
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_RXVALID                                   0x00020000U
#define LRFDMDM32_FIFOSTA_RXVALID_M                                 0x00020000U
#define LRFDMDM32_FIFOSTA_RXVALID_S                                         17U
#define LRFDMDM32_FIFOSTA_RXVALID_ONE                               0x00020000U
#define LRFDMDM32_FIFOSTA_RXVALID_ZERO                              0x00000000U

// Field:    [16] TXREADY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FIFOSTA_TXREADY                                   0x00010000U
#define LRFDMDM32_FIFOSTA_TXREADY_M                                 0x00010000U
#define LRFDMDM32_FIFOSTA_TXREADY_S                                         16U
#define LRFDMDM32_FIFOSTA_TXREADY_ONE                               0x00010000U
#define LRFDMDM32_FIFOSTA_TXREADY_ZERO                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_RFEDATIN0_RFEDATOUT0
//
//*****************************************************************************
// Field: [31:16] RFEDATIN0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATIN0_VAL_W                      16U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATIN0_VAL_M              0xFFFF0000U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATIN0_VAL_S                      16U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATIN0_VAL_ALLONES        0xFFFF0000U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATIN0_VAL_ALLZEROS       0x00000000U

// Field:  [15:0] RFEDATOUT0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATOUT0_VAL_W                     16U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATOUT0_VAL_M             0x0000FFFFU
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATOUT0_VAL_S                      0U
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATOUT0_VAL_ALLONES       0x0000FFFFU
#define LRFDMDM32_RFEDATIN0_RFEDATOUT0_RFEDATOUT0_VAL_ALLZEROS      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_RFECMDIN_RFECMDOUT
//
//*****************************************************************************
// Field: [19:16] RFECMDIN_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDIN_VAL_W                          4U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDIN_VAL_M                 0x000F0000U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDIN_VAL_S                         16U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDIN_VAL_ALLONES           0x000F0000U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDIN_VAL_ALLZEROS          0x00000000U

// Field:   [3:0] RFECMDOUT_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDOUT_VAL_W                         4U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDOUT_VAL_M                0x0000000FU
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDOUT_VAL_S                         0U
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDOUT_VAL_ALLONES          0x0000000FU
#define LRFDMDM32_RFECMDIN_RFECMDOUT_RFECMDOUT_VAL_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_PBEDATIN0_PBEDATOUT0
//
//*****************************************************************************
// Field: [31:16] PBEDATIN0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_W                      16U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_M              0xFFFF0000U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_S                      16U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_ALLONES        0xFFFF0000U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_ALLZEROS       0x00000000U

// Field:  [15:0] PBEDATOUT0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_W                     16U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_M             0x0000FFFFU
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_S                      0U
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_ALLONES       0x0000FFFFU
#define LRFDMDM32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_ALLZEROS      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_PBECMDIN_PBECMDOUT
//
//*****************************************************************************
// Field: [19:16] PBECMDIN_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_W                          4U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_M                 0x000F0000U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_S                         16U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_ALLONES           0x000F0000U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_ALLZEROS          0x00000000U

// Field:   [3:0] PBECMDOUT_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_W                         4U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_M                0x0000000FU
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_S                         0U
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_ALLONES          0x0000000FU
#define LRFDMDM32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_PBEEVTMUX_LQIEST
//
//*****************************************************************************
// Field: [21:16] SEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBEEVTMUX_LQIEST_SEL_W                                     6U
#define LRFDMDM32_PBEEVTMUX_LQIEST_SEL_M                            0x003F0000U
#define LRFDMDM32_PBEEVTMUX_LQIEST_SEL_S                                    16U
#define LRFDMDM32_PBEEVTMUX_LQIEST_SEL_ALLONES                      0x003F0000U
#define LRFDMDM32_PBEEVTMUX_LQIEST_SEL_ALLZEROS                     0x00000000U

// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_PBEEVTMUX_LQIEST_VAL_W                                     8U
#define LRFDMDM32_PBEEVTMUX_LQIEST_VAL_M                            0x000000FFU
#define LRFDMDM32_PBEEVTMUX_LQIEST_VAL_S                                     0U
#define LRFDMDM32_PBEEVTMUX_LQIEST_VAL_ALLONES                      0x000000FFU
#define LRFDMDM32_PBEEVTMUX_LQIEST_VAL_ALLZEROS                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SYSTIMEVTMUX1_SYSTIMEVTMUX0
//
//*****************************************************************************
// Field: [21:16] SEL2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL2_W                         6U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL2_M                0x003F0000U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL2_S                        16U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL2_ALLONES          0x003F0000U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL2_ALLZEROS         0x00000000U

// Field:  [11:6] SEL1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL1_W                         6U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL1_M                0x00000FC0U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL1_S                         6U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL1_ALLONES          0x00000FC0U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL1_ALLZEROS         0x00000000U

// Field:   [5:0] SEL0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL0_W                         6U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL0_M                0x0000003FU
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL0_S                         0U
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL0_ALLONES          0x0000003FU
#define LRFDMDM32_SYSTIMEVTMUX1_SYSTIMEVTMUX0_SEL0_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MODPRECTRL_ADCDIGCONF
//
//*****************************************************************************
// Field: [23:20] REPS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// REPS16                   Internal. Only to be used through TI provided API.
// REPS15                   Internal. Only to be used through TI provided API.
// REPS14                   Internal. Only to be used through TI provided API.
// REPS13                   Internal. Only to be used through TI provided API.
// REPS12                   Internal. Only to be used through TI provided API.
// REPS11                   Internal. Only to be used through TI provided API.
// REPS10                   Internal. Only to be used through TI provided API.
// REPS9                    Internal. Only to be used through TI provided API.
// REPS8                    Internal. Only to be used through TI provided API.
// REPS7                    Internal. Only to be used through TI provided API.
// REPS6                    Internal. Only to be used through TI provided API.
// REPS5                    Internal. Only to be used through TI provided API.
// REPS4                    Internal. Only to be used through TI provided API.
// REPS3                    Internal. Only to be used through TI provided API.
// REPS2                    Internal. Only to be used through TI provided API.
// REPS1                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_W                               4U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_M                      0x00F00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_S                              20U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS16                 0x00F00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS15                 0x00E00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS14                 0x00D00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS13                 0x00C00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS12                 0x00B00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS11                 0x00A00000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS10                 0x00900000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS9                  0x00800000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS8                  0x00700000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS7                  0x00600000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS6                  0x00500000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS5                  0x00400000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS4                  0x00300000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS3                  0x00200000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS2                  0x00100000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_REPS_REPS1                  0x00000000U

// Field: [19:16] SIZE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BITS16                   Internal. Only to be used through TI provided API.
// BITS8                    Internal. Only to be used through TI provided API.
// BITS4                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_W                               4U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_M                      0x000F0000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_S                              16U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_BITS16                 0x000F0000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_BITS8                  0x00070000U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_SIZE_BITS4                  0x00030000U

// Field:     [1] QBRANCHEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_QBRANCHEN                   0x00000002U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_QBRANCHEN_M                 0x00000002U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_QBRANCHEN_S                          1U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_QBRANCHEN_ON                0x00000002U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_QBRANCHEN_OFF               0x00000000U

// Field:     [0] IBRANCHEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_IBRANCHEN                   0x00000001U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_IBRANCHEN_M                 0x00000001U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_IBRANCHEN_S                          0U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_IBRANCHEN_ON                0x00000001U
#define LRFDMDM32_MODPRECTRL_ADCDIGCONF_IBRANCHEN_OFF               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MODSYMMAP1_MODSYMMAP0
//
//*****************************************************************************
// Field: [31:28] SYM7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM7_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM7_M                      0xF0000000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM7_S                              28U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM7_ALLONES                0xF0000000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM7_ALLZEROS               0x00000000U

// Field: [27:24] SYM6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM6_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM6_M                      0x0F000000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM6_S                              24U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM6_ALLONES                0x0F000000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM6_ALLZEROS               0x00000000U

// Field: [23:20] SYM5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM5_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM5_M                      0x00F00000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM5_S                              20U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM5_ALLONES                0x00F00000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM5_ALLZEROS               0x00000000U

// Field: [19:16] SYM4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM4_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM4_M                      0x000F0000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM4_S                              16U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM4_ALLONES                0x000F0000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM4_ALLZEROS               0x00000000U

// Field: [15:12] SYM3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM3_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM3_M                      0x0000F000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM3_S                              12U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM3_ALLONES                0x0000F000U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM3_ALLZEROS               0x00000000U

// Field:  [11:8] SYM2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM2_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM2_M                      0x00000F00U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM2_S                               8U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM2_ALLONES                0x00000F00U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM2_ALLZEROS               0x00000000U

// Field:   [7:4] SYM1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM1_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM1_M                      0x000000F0U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM1_S                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM1_ALLONES                0x000000F0U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM1_ALLZEROS               0x00000000U

// Field:   [3:0] SYM0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM0_W                               4U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM0_M                      0x0000000FU
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM0_S                               0U
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM0_ALLONES                0x0000000FU
#define LRFDMDM32_MODSYMMAP1_MODSYMMAP0_SYM0_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_BAUD_MODSOFTTX
//
//*****************************************************************************
// Field: [31:16] RATEWORD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BAUD_MODSOFTTX_RATEWORD_W                                 16U
#define LRFDMDM32_BAUD_MODSOFTTX_RATEWORD_M                         0xFFFF0000U
#define LRFDMDM32_BAUD_MODSOFTTX_RATEWORD_S                                 16U
#define LRFDMDM32_BAUD_MODSOFTTX_RATEWORD_ALLONES                   0xFFFF0000U
#define LRFDMDM32_BAUD_MODSOFTTX_RATEWORD_ALLZEROS                  0x00000000U

// Field:   [3:0] SOFTSYMBOL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BAUD_MODSOFTTX_SOFTSYMBOL_W                                4U
#define LRFDMDM32_BAUD_MODSOFTTX_SOFTSYMBOL_M                       0x0000000FU
#define LRFDMDM32_BAUD_MODSOFTTX_SOFTSYMBOL_S                                0U
#define LRFDMDM32_BAUD_MODSOFTTX_SOFTSYMBOL_ALLONES                 0x0000000FU
#define LRFDMDM32_BAUD_MODSOFTTX_SOFTSYMBOL_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MODMAIN_BAUDPRE
//
//*****************************************************************************
// Field: [19:18] FECSELECT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BLR                      Internal. Only to be used through TI provided API.
// RESERVED                 Internal. Only to be used through TI provided API.
// IEEE15_4                 Internal. Only to be used through TI provided API.
// NOSEL                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_W                                2U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_M                       0x000C0000U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_S                               18U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_BLR                     0x000C0000U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_RESERVED                0x00080000U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_IEEE15_4                0x00040000U
#define LRFDMDM32_MODMAIN_BAUDPRE_FECSELECT_NOSEL                   0x00000000U

// Field: [17:16] MODLEVELS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// LVL8                     Internal. Only to be used through TI provided API.
// LVL4                     Internal. Only to be used through TI provided API.
// LVL2                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_W                                2U
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_M                       0x00030000U
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_S                               16U
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_LVL8                    0x00020000U
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_LVL4                    0x00010000U
#define LRFDMDM32_MODMAIN_BAUDPRE_MODLEVELS_LVL2                    0x00000000U

// Field: [15:13] ALIGNVALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODMAIN_BAUDPRE_ALIGNVALUE_W                               3U
#define LRFDMDM32_MODMAIN_BAUDPRE_ALIGNVALUE_M                      0x0000E000U
#define LRFDMDM32_MODMAIN_BAUDPRE_ALIGNVALUE_S                              13U
#define LRFDMDM32_MODMAIN_BAUDPRE_ALIGNVALUE_ALLONES                0x0000E000U
#define LRFDMDM32_MODMAIN_BAUDPRE_ALIGNVALUE_ALLZEROS               0x00000000U

// Field:  [12:8] EXTRATEWORD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODMAIN_BAUDPRE_EXTRATEWORD_W                              5U
#define LRFDMDM32_MODMAIN_BAUDPRE_EXTRATEWORD_M                     0x00001F00U
#define LRFDMDM32_MODMAIN_BAUDPRE_EXTRATEWORD_S                              8U
#define LRFDMDM32_MODMAIN_BAUDPRE_EXTRATEWORD_ALLONES               0x00001F00U
#define LRFDMDM32_MODMAIN_BAUDPRE_EXTRATEWORD_ALLZEROS              0x00000000U

// Field:   [7:0] PRESCALER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODMAIN_BAUDPRE_PRESCALER_W                                8U
#define LRFDMDM32_MODMAIN_BAUDPRE_PRESCALER_M                       0x000000FFU
#define LRFDMDM32_MODMAIN_BAUDPRE_PRESCALER_S                                0U
#define LRFDMDM32_MODMAIN_BAUDPRE_PRESCALER_ALLONES                 0x000000FFU
#define LRFDMDM32_MODMAIN_BAUDPRE_PRESCALER_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMMISC1_DEMMISC0
//
//*****************************************************************************
// Field: [28:24] CDCTGAINMA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINMA_W                             5U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINMA_M                    0x1F000000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINMA_S                            24U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINMA_ALLONES              0x1F000000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINMA_ALLZEROS             0x00000000U

// Field: [23:21] CDCTGAINEX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINEX_W                             3U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINEX_M                    0x00E00000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINEX_S                            21U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINEX_ALLONES              0x00E00000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCTGAINEX_ALLZEROS             0x00000000U

// Field:    [20] CDCCOLRST
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCCOLRST                       0x00100000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCCOLRST_M                     0x00100000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCCOLRST_S                             20U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCCOLRST_EN                    0x00100000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CDCCOLRST_DIS                   0x00000000U

// Field: [19:18] MGE1SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CHFI                     Internal. Only to be used through TI provided API.
// FEXB1                    Internal. Only to be used through TI provided API.
// FIDC                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_W                             2U
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_M                    0x000C0000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_S                            18U
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_CHFI                 0x00080000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_FEXB1                0x00040000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_MGE1SRCSEL_FIDC                 0x00000000U

// Field: [17:16] CHFIBW
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BW0_29                   Internal. Only to be used through TI provided API.
// BW0_41667                Internal. Only to be used through TI provided API.
// BW0_3333                 Internal. Only to be used through TI provided API.
// BW0_5                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_W                                 2U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_M                        0x00030000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_S                                16U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_BW0_29                   0x00030000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_BW0_41667                0x00020000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_BW0_3333                 0x00010000U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CHFIBW_BW0_5                    0x00000000U

// Field:   [9:0] CMIXN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC1_DEMMISC0_CMIXN_W                                 10U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CMIXN_M                         0x000003FFU
#define LRFDMDM32_DEMMISC1_DEMMISC0_CMIXN_S                                  0U
#define LRFDMDM32_DEMMISC1_DEMMISC0_CMIXN_ALLONES                   0x000003FFU
#define LRFDMDM32_DEMMISC1_DEMMISC0_CMIXN_ALLZEROS                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMMISC3_DEMMISC2
//
//*****************************************************************************
// Field: [30:29] BDE2DVGA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GAIN8                    Internal. Only to be used through TI provided API.
// GAIN4                    Internal. Only to be used through TI provided API.
// GAIN2                    Internal. Only to be used through TI provided API.
// GAIN1                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_W                               2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_M                      0x60000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_S                              29U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_GAIN8                  0x60000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_GAIN4                  0x40000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_GAIN2                  0x20000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DVGA_GAIN1                  0x00000000U

// Field:    [28] BDE1FILTMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1FILTMODE                    0x10000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1FILTMODE_M                  0x10000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1FILTMODE_S                          28U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1FILTMODE_DIV2               0x10000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1FILTMODE_DIV1               0x00000000U

// Field: [27:26] LQIPERIOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SYM1024                  Internal. Only to be used through TI provided API.
// SYM256                   Internal. Only to be used through TI provided API.
// SYM64                    Internal. Only to be used through TI provided API.
// SYM16                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_W                              2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_M                     0x0C000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_S                             26U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_SYM1024               0x0C000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_SYM256                0x08000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_SYM64                 0x04000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_LQIPERIOD_SYM16                 0x00000000U

// Field: [25:24] BDE1DVGA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GAIN8                    Internal. Only to be used through TI provided API.
// GAIN4                    Internal. Only to be used through TI provided API.
// GAIN2                    Internal. Only to be used through TI provided API.
// GAIN1                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_W                               2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_M                      0x03000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_S                              24U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_GAIN8                  0x03000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_GAIN4                  0x02000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_GAIN2                  0x01000000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1DVGA_GAIN1                  0x00000000U

// Field:    [23] BDE1NUMSTAGES
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1NUMSTAGES                   0x00800000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1NUMSTAGES_M                 0x00800000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1NUMSTAGES_S                         23U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1NUMSTAGES_DIV2              0x00800000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE1NUMSTAGES_DIV1              0x00000000U

// Field: [22:21] PDIFDECIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV4                     Internal. Only to be used through TI provided API.
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_W                              2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_M                     0x00600000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_S                             21U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_DIV4                  0x00400000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_DIV2                  0x00200000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDECIM_DIV1                  0x00000000U

// Field: [20:16] BDE2DECRATIO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV8                     Internal. Only to be used through TI provided API.
// DIV4                     Internal. Only to be used through TI provided API.
// DIV2                     Internal. Only to be used through TI provided API.
// DIV1                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_W                           5U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_M                  0x001F0000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_S                          16U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_DIV8               0x00030000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_DIV4               0x00020000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_DIV2               0x00010000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_BDE2DECRATIO_DIV1               0x00000000U

// Field:    [14] MLSERUN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_MLSERUN                         0x00004000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MLSERUN_M                       0x00004000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MLSERUN_S                               14U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MLSERUN_EN                      0x00004000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MLSERUN_DIS                     0x00000000U

// Field: [13:12] MAFCGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_MAFCGAIN_W                               2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MAFCGAIN_M                      0x00003000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MAFCGAIN_S                              12U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MAFCGAIN_ALLONES                0x00003000U
#define LRFDMDM32_DEMMISC3_DEMMISC2_MAFCGAIN_ALLZEROS               0x00000000U

// Field:    [11] STIMBYPASS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMBYPASS                      0x00000800U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMBYPASS_M                    0x00000800U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMBYPASS_S                            11U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMBYPASS_EN                   0x00000800U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMBYPASS_DIS                  0x00000000U

// Field:    [10] STIMESTONLY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMESTONLY                     0x00000400U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMESTONLY_M                   0x00000400U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMESTONLY_S                           10U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMESTONLY_EN                  0x00000400U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMESTONLY_DIS                 0x00000000U

// Field:   [9:7] STIMTEAPERIOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SYM128                   Internal. Only to be used through TI provided API.
// SYM64                    Internal. Only to be used through TI provided API.
// SYM32                    Internal. Only to be used through TI provided API.
// SYM16                    Internal. Only to be used through TI provided API.
// SYM8                     Internal. Only to be used through TI provided API.
// SYM4                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_W                          3U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_M                 0x00000380U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_S                          7U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM128            0x00000280U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM64             0x00000200U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM32             0x00000180U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM16             0x00000100U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM8              0x00000080U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAPERIOD_SYM4              0x00000000U

// Field:   [6:4] STIMTEAGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV4                     Internal. Only to be used through TI provided API.
// DIV8                     Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
// DIV32                    Internal. Only to be used through TI provided API.
// DIV64                    Internal. Only to be used through TI provided API.
// DIV128                   Internal. Only to be used through TI provided API.
// DIV256                   Internal. Only to be used through TI provided API.
// DIV512                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_W                            3U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_M                   0x00000070U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_S                            4U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV4                0x00000070U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV8                0x00000060U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV16               0x00000050U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV32               0x00000040U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV64               0x00000030U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV128              0x00000020U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV256              0x00000010U
#define LRFDMDM32_DEMMISC3_DEMMISC2_STIMTEAGAIN_DIV512              0x00000000U

// Field:     [3] PDIFLINPREDEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLINPREDEN                   0x00000008U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLINPREDEN_M                 0x00000008U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLINPREDEN_S                          3U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLINPREDEN_ON                0x00000008U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLINPREDEN_OFF               0x00000000U

// Field:     [2] PDIFDESPECK
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDESPECK                     0x00000004U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDESPECK_M                   0x00000004U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDESPECK_S                            2U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDESPECK_EN                  0x00000004U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFDESPECK_DIS                 0x00000000U

// Field:     [1] PDIFIQCONJEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFIQCONJEN                    0x00000002U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFIQCONJEN_M                  0x00000002U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFIQCONJEN_S                           1U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFIQCONJEN_ON                 0x00000002U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFIQCONJEN_OFF                0x00000000U

// Field:     [0] PDIFLIMITRANGE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLIMITRANGE                  0x00000001U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLIMITRANGE_M                0x00000001U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLIMITRANGE_S                         0U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLIMITRANGE_EN               0x00000001U
#define LRFDMDM32_DEMMISC3_DEMMISC2_PDIFLIMITRANGE_DIS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMDSBU_DEMIQMC0
//
//*****************************************************************************
// Field: [31:24] DSBUAVGLENGTH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUAVGLENGTH_W                           8U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUAVGLENGTH_M                  0xFF000000U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUAVGLENGTH_S                          24U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUAVGLENGTH_ALLONES            0xFF000000U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUAVGLENGTH_ALLZEROS           0x00000000U

// Field: [23:16] DSBUDELAY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUDELAY_W                               8U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUDELAY_M                      0x00FF0000U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUDELAY_S                              16U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUDELAY_ALLONES                0x00FF0000U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_DSBUDELAY_ALLZEROS               0x00000000U

// Field:  [15:8] GAINFACTOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSBU_DEMIQMC0_GAINFACTOR_W                              8U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_GAINFACTOR_M                     0x0000FF00U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_GAINFACTOR_S                              8U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_GAINFACTOR_ALLONES               0x0000FF00U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_GAINFACTOR_ALLZEROS              0x00000000U

// Field:   [7:0] PHASEFACTOR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSBU_DEMIQMC0_PHASEFACTOR_W                             8U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_PHASEFACTOR_M                    0x000000FFU
#define LRFDMDM32_DEMDSBU_DEMIQMC0_PHASEFACTOR_S                             0U
#define LRFDMDM32_DEMDSBU_DEMIQMC0_PHASEFACTOR_ALLONES              0x000000FFU
#define LRFDMDM32_DEMDSBU_DEMIQMC0_PHASEFACTOR_ALLZEROS             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMFIDC0_DEMCODC0
//
//*****************************************************************************
// Field: [21:20] DEMFIDC0_COMPSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACC                      Internal. Only to be used through TI provided API.
// MANUAL                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_COMPSEL_W                       2U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_COMPSEL_M              0x00300000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_COMPSEL_S                      20U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_COMPSEL_ACC            0x00200000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_COMPSEL_MANUAL         0x00000000U

// Field: [19:18] DEMFIDC0_ACCPERIOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SMPL512                  Internal. Only to be used through TI provided API.
// SMPL128                  Internal. Only to be used through TI provided API.
// SMPL32                   Internal. Only to be used through TI provided API.
// SMPL8                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_W                     2U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_M            0x000C0000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_S                    18U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_SMPL512      0x000C0000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_SMPL128      0x00080000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_SMPL32       0x00040000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCPERIOD_SMPL8        0x00000000U

// Field:    [17] DEMFIDC0_ACCMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CONT                     Internal. Only to be used through TI provided API.
// SINGLE                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCMODE                0x00020000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCMODE_M              0x00020000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCMODE_S                      17U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCMODE_CONT           0x00020000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCMODE_SINGLE         0x00000000U

// Field:    [16] DEMFIDC0_ACCEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCEN                  0x00010000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCEN_M                0x00010000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCEN_S                        16U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCEN_ON               0x00010000U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMFIDC0_ACCEN_OFF              0x00000000U

// Field:    [11] DEMCODC0_ESTSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// IIR                      Internal. Only to be used through TI provided API.
// ACC                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ESTSEL                 0x00000800U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ESTSEL_M               0x00000800U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ESTSEL_S                       11U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ESTSEL_IIR             0x00000800U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ESTSEL_ACC             0x00000000U

// Field:  [10:9] DEMCODC0_COMPSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// IIR                      Internal. Only to be used through TI provided API.
// ACC                      Internal. Only to be used through TI provided API.
// MANUAL                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_W                       2U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_M              0x00000600U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_S                       9U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_IIR            0x00000600U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_ACC            0x00000400U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_COMPSEL_MANUAL         0x00000000U

// Field:     [8] DEMCODC0_IIRUSEINITIAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRUSEINITIAL          0x00000100U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRUSEINITIAL_M        0x00000100U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRUSEINITIAL_S                 8U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRUSEINITIAL_EN       0x00000100U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRUSEINITIAL_DIS      0x00000000U

// Field:   [7:5] DEMCODC0_IIRGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV1024                  Internal. Only to be used through TI provided API.
// DIV512                   Internal. Only to be used through TI provided API.
// DIV256                   Internal. Only to be used through TI provided API.
// DIV128                   Internal. Only to be used through TI provided API.
// DIV64                    Internal. Only to be used through TI provided API.
// DIV32                    Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_W                       3U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_M              0x000000E0U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_S                       5U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV1024        0x000000E0U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV512         0x000000C0U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV256         0x000000A0U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV128         0x00000080U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV64          0x00000060U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV32          0x00000040U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_DIV16          0x00000020U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIRGAIN_OFF            0x00000000U

// Field:     [4] DEMCODC0_IIREN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIREN                  0x00000010U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIREN_M                0x00000010U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIREN_S                         4U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIREN_ON               0x00000010U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_IIREN_OFF              0x00000000U

// Field:     [3] DEMCODC0_ACCMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CONT                     Internal. Only to be used through TI provided API.
// SINGLE                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCMODE                0x00000008U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCMODE_M              0x00000008U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCMODE_S                       3U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCMODE_CONT           0x00000008U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCMODE_SINGLE         0x00000000U

// Field:   [2:1] DEMCODC0_ACCPERIOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SMPL512                  Internal. Only to be used through TI provided API.
// SMPL128                  Internal. Only to be used through TI provided API.
// SMPL32                   Internal. Only to be used through TI provided API.
// SMPL8                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_W                     2U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_M            0x00000006U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_S                     1U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_SMPL512      0x00000006U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_SMPL128      0x00000004U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_SMPL32       0x00000002U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCPERIOD_SMPL8        0x00000000U

// Field:     [0] DEMCODC0_ACCEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCEN                  0x00000001U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCEN_M                0x00000001U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCEN_S                         0U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCEN_ON               0x00000001U
#define LRFDMDM32_DEMFIDC0_DEMCODC0_DEMCODC0_ACCEN_OFF              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMDSXB0_DEMFEXB0
//
//*****************************************************************************
// Field:    [21] DEMDSXB0_OUT2PASSTHROUGH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT2PASSTHROUGH        0x00200000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT2PASSTHROUGH_M      0x00200000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT2PASSTHROUGH_S              21U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT2PASSTHROUGH_ONE     \
                                                                    0x00200000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT2PASSTHROUGH_ZERO    \
                                                                    0x00000000U

// Field:    [20] DEMDSXB0_OUT1PASSTHROUGH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT1PASSTHROUGH        0x00100000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT1PASSTHROUGH_M      0x00100000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT1PASSTHROUGH_S              20U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT1PASSTHROUGH_ONE     \
                                                                    0x00100000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUT1PASSTHROUGH_ZERO    \
                                                                    0x00000000U

// Field:    [19] DEMDSXB0_OUTSRCSEL2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAFI                     Internal. Only to be used through TI provided API.
// FIFE                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL2             0x00080000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL2_M           0x00080000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL2_S                   19U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL2_MAFI        0x00080000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL2_FIFE        0x00000000U

// Field:    [18] DEMDSXB0_OUTSRCSEL1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAFI                     Internal. Only to be used through TI provided API.
// FIFE                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL1             0x00040000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL1_M           0x00040000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL1_S                   18U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL1_MAFI        0x00040000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_OUTSRCSEL1_FIFE        0x00000000U

// Field:    [17] DEMDSXB0_B2SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FIFE                     Internal. Only to be used through TI provided API.
// INPUT                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B2SRCSEL               0x00020000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B2SRCSEL_M             0x00020000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B2SRCSEL_S                     17U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B2SRCSEL_FIFE          0x00020000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B2SRCSEL_INPUT         0x00000000U

// Field:    [16] DEMDSXB0_B1SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MAFI                     Internal. Only to be used through TI provided API.
// INPUT                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B1SRCSEL               0x00010000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B1SRCSEL_M             0x00010000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B1SRCSEL_S                     16U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B1SRCSEL_MAFI          0x00010000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMDSXB0_B1SRCSEL_INPUT         0x00000000U

// Field:    [13] DEMFEXB0_OUT2PASSTHROUGH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2PASSTHROUGH        0x00002000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2PASSTHROUGH_M      0x00002000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2PASSTHROUGH_S              13U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2PASSTHROUGH_ONE     \
                                                                    0x00002000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2PASSTHROUGH_ZERO    \
                                                                    0x00000000U

// Field: [12:11] DEMFEXB0_OUT2SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BDE1                     Internal. Only to be used through TI provided API.
// CMIX                     Internal. Only to be used through TI provided API.
// CODC                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_W                    2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_M           0x00001800U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_S                   11U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_BDE1        0x00001000U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_CMIX        0x00000800U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT2SRCSEL_CODC        0x00000000U

// Field:    [10] DEMFEXB0_OUT1PASSTHROUGH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1PASSTHROUGH        0x00000400U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1PASSTHROUGH_M      0x00000400U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1PASSTHROUGH_S              10U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1PASSTHROUGH_ONE     \
                                                                    0x00000400U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1PASSTHROUGH_ZERO    \
                                                                    0x00000000U

// Field:   [9:8] DEMFEXB0_OUT1SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BDE1                     Internal. Only to be used through TI provided API.
// CMIX                     Internal. Only to be used through TI provided API.
// CODC                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_W                    2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_M           0x00000300U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_S                    8U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_BDE1        0x00000200U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_CMIX        0x00000100U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_OUT1SRCSEL_CODC        0x00000000U

// Field:   [7:6] DEMFEXB0_B4SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONES                     Internal. Only to be used through TI provided API.
// ZEROS                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B4SRCSEL_W                      2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B4SRCSEL_M             0x000000C0U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B4SRCSEL_S                      6U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B4SRCSEL_ONES          0x000000C0U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B4SRCSEL_ZEROS         0x00000000U

// Field:   [5:4] DEMFEXB0_B3SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CMIX                     Internal. Only to be used through TI provided API.
// CODC                     Internal. Only to be used through TI provided API.
// INPUT                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_W                      2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_M             0x00000030U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_S                      4U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_CMIX          0x00000020U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_CODC          0x00000010U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B3SRCSEL_INPUT         0x00000000U

// Field:   [3:2] DEMFEXB0_B2SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BDE1                     Internal. Only to be used through TI provided API.
// CODC                     Internal. Only to be used through TI provided API.
// INPUT                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_W                      2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_M             0x0000000CU
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_S                      2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_BDE1          0x00000008U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_CODC          0x00000004U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B2SRCSEL_INPUT         0x00000000U

// Field:   [1:0] DEMFEXB0_B1SRCSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BDE1                     Internal. Only to be used through TI provided API.
// CMIX                     Internal. Only to be used through TI provided API.
// INPUT                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_W                      2U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_M             0x00000003U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_S                      0U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_BDE1          0x00000002U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_CMIX          0x00000001U
#define LRFDMDM32_DEMDSXB0_DEMFEXB0_DEMFEXB0_B1SRCSEL_INPUT         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMMAFI0_DEMFIFE0
//
//*****************************************************************************
// Field: [31:24] C1C7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C1C7_W                                   8U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C1C7_M                          0xFF000000U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C1C7_S                                  24U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C1C7_ALLONES                    0xFF000000U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C1C7_ALLZEROS                   0x00000000U

// Field: [23:16] C0C8
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C0C8_W                                   8U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C0C8_M                          0x00FF0000U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C0C8_S                                  16U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C0C8_ALLONES                    0x00FF0000U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_C0C8_ALLZEROS                   0x00000000U

// Field:    [11] FINEFOESEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ACC                      Internal. Only to be used through TI provided API.
// IIR                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FINEFOESEL                      0x00000800U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FINEFOESEL_M                    0x00000800U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FINEFOESEL_S                            11U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FINEFOESEL_ACC                  0x00000800U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FINEFOESEL_IIR                  0x00000000U

// Field:  [10:9] FOCFFSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MANUAL                   Internal. Only to be used through TI provided API.
// ACC                      Internal. Only to be used through TI provided API.
// IIR                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_W                               2U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_M                      0x00000600U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_S                               9U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_MANUAL                 0x00000400U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_ACC                    0x00000200U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_FOCFFSEL_IIR                    0x00000000U

// Field:     [8] ACCCNTMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CONT                     Internal. Only to be used through TI provided API.
// SINGLE                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCCNTMODE                      0x00000100U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCCNTMODE_M                    0x00000100U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCCNTMODE_S                             8U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCCNTMODE_CONT                 0x00000100U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCCNTMODE_SINGLE               0x00000000U

// Field:   [7:6] ACCPERIOD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PER512                   Internal. Only to be used through TI provided API.
// PER256                   Internal. Only to be used through TI provided API.
// PER128                   Internal. Only to be used through TI provided API.
// PER64                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_W                              2U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_M                     0x000000C0U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_S                              6U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_PER512                0x000000C0U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_PER256                0x00000080U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_PER128                0x00000040U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCPERIOD_PER64                 0x00000000U

// Field:     [5] ACCEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCEN                           0x00000020U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCEN_M                         0x00000020U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCEN_S                                  5U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCEN_ON                        0x00000020U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_ACCEN_OFF                       0x00000000U

// Field:     [4] IIRUSEINITIAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRUSEINITIAL                   0x00000010U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRUSEINITIAL_M                 0x00000010U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRUSEINITIAL_S                          4U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRUSEINITIAL_EN                0x00000010U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRUSEINITIAL_DIS               0x00000000U

// Field:   [3:1] IIRGAIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// DIV1024                  Internal. Only to be used through TI provided API.
// DIV512                   Internal. Only to be used through TI provided API.
// DIV256                   Internal. Only to be used through TI provided API.
// DIV128                   Internal. Only to be used through TI provided API.
// DIV64                    Internal. Only to be used through TI provided API.
// DIV32                    Internal. Only to be used through TI provided API.
// DIV16                    Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_W                                3U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_M                       0x0000000EU
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_S                                1U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV1024                 0x0000000EU
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV512                  0x0000000CU
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV256                  0x0000000AU
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV128                  0x00000008U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV64                   0x00000006U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV32                   0x00000004U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_DIV16                   0x00000002U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIRGAIN_OFF                     0x00000000U

// Field:     [0] IIREN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIREN                           0x00000001U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIREN_M                         0x00000001U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIREN_S                                  0U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIREN_ON                        0x00000001U
#define LRFDMDM32_DEMMAFI0_DEMFIFE0_IIREN_OFF                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMMAFI2_DEMMAFI1
//
//*****************************************************************************
// Field: [24:16] C4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C4_W                                     9U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C4_M                            0x01FF0000U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C4_S                                    16U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C4_ALLONES                      0x01FF0000U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C4_ALLZEROS                     0x00000000U

// Field:  [15:8] C3C5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C3C5_W                                   8U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C3C5_M                          0x0000FF00U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C3C5_S                                   8U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C3C5_ALLONES                    0x0000FF00U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C3C5_ALLZEROS                   0x00000000U

// Field:   [7:0] C2C6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C2C6_W                                   8U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C2C6_M                          0x000000FFU
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C2C6_S                                   0U
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C2C6_ALLONES                    0x000000FFU
#define LRFDMDM32_DEMMAFI2_DEMMAFI1_C2C6_ALLZEROS                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMC1BE1_DEMC1BE0
//
//*****************************************************************************
// Field: [31:24] THRESHOLDB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDB_W                             8U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDB_M                    0xFF000000U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDB_S                            24U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDB_ALLONES              0xFF000000U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDB_ALLZEROS             0x00000000U

// Field: [23:16] THRESHOLDA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDA_W                             8U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDA_M                    0x00FF0000U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDA_S                            16U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDA_ALLONES              0x00FF0000U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_THRESHOLDA_ALLZEROS             0x00000000U

// Field: [15:11] MASKB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKB_W                                  5U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKB_M                         0x0000F800U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKB_S                                 11U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKB_ALLONES                   0x0000F800U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKB_ALLZEROS                  0x00000000U

// Field:  [10:6] MASKA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKA_W                                  5U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKA_M                         0x000007C0U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKA_S                                  6U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKA_ALLONES                   0x000007C0U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_MASKA_ALLZEROS                  0x00000000U

// Field:   [5:4] CASCCONF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// PARALLEL                 Internal. Only to be used through TI provided API.
// SERIAL                   Internal. Only to be used through TI provided API.
// SINGLE                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_W                               2U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_M                      0x00000030U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_S                               4U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_PARALLEL               0x00000020U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_SERIAL                 0x00000010U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_CASCCONF_SINGLE                 0x00000000U

// Field:   [3:0] COPYCONF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_COPYCONF_W                               4U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_COPYCONF_M                      0x0000000FU
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_COPYCONF_S                               0U
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_COPYCONF_ALLONES                0x0000000FU
#define LRFDMDM32_DEMC1BE1_DEMC1BE0_COPYCONF_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SPARE0_DEMC1BE2
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE0_DEMC1BE2_VAL_W                                     16U
#define LRFDMDM32_SPARE0_DEMC1BE2_VAL_M                             0xFFFF0000U
#define LRFDMDM32_SPARE0_DEMC1BE2_VAL_S                                     16U
#define LRFDMDM32_SPARE0_DEMC1BE2_VAL_ALLONES                       0xFFFF0000U
#define LRFDMDM32_SPARE0_DEMC1BE2_VAL_ALLZEROS                      0x00000000U

// Field:    [10] PARLOADCONF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ATOD                     Internal. Only to be used through TI provided API.
// ATOB                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE0_DEMC1BE2_PARLOADCONF                       0x00000400U
#define LRFDMDM32_SPARE0_DEMC1BE2_PARLOADCONF_M                     0x00000400U
#define LRFDMDM32_SPARE0_DEMC1BE2_PARLOADCONF_S                             10U
#define LRFDMDM32_SPARE0_DEMC1BE2_PARLOADCONF_ATOD                  0x00000400U
#define LRFDMDM32_SPARE0_DEMC1BE2_PARLOADCONF_ATOB                  0x00000000U

// Field:   [9:8] PEAKCONF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BESTAB                   Internal. Only to be used through TI provided API.
// BEST                     Internal. Only to be used through TI provided API.
// THRESH                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_W                                 2U
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_M                        0x00000300U
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_S                                 8U
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_BESTAB                   0x00000200U
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_BEST                     0x00000100U
#define LRFDMDM32_SPARE0_DEMC1BE2_PEAKCONF_THRESH                   0x00000000U

// Field:   [7:0] THRESHOLDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE0_DEMC1BE2_THRESHOLDC_W                               8U
#define LRFDMDM32_SPARE0_DEMC1BE2_THRESHOLDC_M                      0x000000FFU
#define LRFDMDM32_SPARE0_DEMC1BE2_THRESHOLDC_S                               0U
#define LRFDMDM32_SPARE0_DEMC1BE2_THRESHOLDC_ALLONES                0x000000FFU
#define LRFDMDM32_SPARE0_DEMC1BE2_THRESHOLDC_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SPARE2_SPARE1
//
//*****************************************************************************
// Field: [31:16] SPARE2_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE2_SPARE1_SPARE2_VAL_W                                16U
#define LRFDMDM32_SPARE2_SPARE1_SPARE2_VAL_M                        0xFFFF0000U
#define LRFDMDM32_SPARE2_SPARE1_SPARE2_VAL_S                                16U
#define LRFDMDM32_SPARE2_SPARE1_SPARE2_VAL_ALLONES                  0xFFFF0000U
#define LRFDMDM32_SPARE2_SPARE1_SPARE2_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] SPARE1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SPARE2_SPARE1_SPARE1_VAL_W                                16U
#define LRFDMDM32_SPARE2_SPARE1_SPARE1_VAL_M                        0x0000FFFFU
#define LRFDMDM32_SPARE2_SPARE1_SPARE1_VAL_S                                 0U
#define LRFDMDM32_SPARE2_SPARE1_SPARE1_VAL_ALLONES                  0x0000FFFFU
#define LRFDMDM32_SPARE2_SPARE1_SPARE1_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMSWQU0_SPARE3
//
//*****************************************************************************
// Field:    [23] SYNCMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU0_SPARE3_SYNCMODE                          0x00800000U
#define LRFDMDM32_DEMSWQU0_SPARE3_SYNCMODE_M                        0x00800000U
#define LRFDMDM32_DEMSWQU0_SPARE3_SYNCMODE_S                                23U
#define LRFDMDM32_DEMSWQU0_SPARE3_SYNCMODE_ONE                      0x00800000U
#define LRFDMDM32_DEMSWQU0_SPARE3_SYNCMODE_ZERO                     0x00000000U

// Field:    [22] AUTOMAFC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU0_SPARE3_AUTOMAFC                          0x00400000U
#define LRFDMDM32_DEMSWQU0_SPARE3_AUTOMAFC_M                        0x00400000U
#define LRFDMDM32_DEMSWQU0_SPARE3_AUTOMAFC_S                                22U
#define LRFDMDM32_DEMSWQU0_SPARE3_AUTOMAFC_ON                       0x00400000U
#define LRFDMDM32_DEMSWQU0_SPARE3_AUTOMAFC_OFF                      0x00000000U

// Field:    [21] RUN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU0_SPARE3_RUN                               0x00200000U
#define LRFDMDM32_DEMSWQU0_SPARE3_RUN_M                             0x00200000U
#define LRFDMDM32_DEMSWQU0_SPARE3_RUN_S                                     21U
#define LRFDMDM32_DEMSWQU0_SPARE3_RUN_ON                            0x00200000U
#define LRFDMDM32_DEMSWQU0_SPARE3_RUN_OFF                           0x00000000U

// Field: [20:16] REFLEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU0_SPARE3_REFLEN_W                                   5U
#define LRFDMDM32_DEMSWQU0_SPARE3_REFLEN_M                          0x001F0000U
#define LRFDMDM32_DEMSWQU0_SPARE3_REFLEN_S                                  16U
#define LRFDMDM32_DEMSWQU0_SPARE3_REFLEN_ALLONES                    0x001F0000U
#define LRFDMDM32_DEMSWQU0_SPARE3_REFLEN_ALLZEROS                   0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU0_SPARE3_VAL_W                                     16U
#define LRFDMDM32_DEMSWQU0_SPARE3_VAL_M                             0x0000FFFFU
#define LRFDMDM32_DEMSWQU0_SPARE3_VAL_S                                      0U
#define LRFDMDM32_DEMSWQU0_SPARE3_VAL_ALLONES                       0x0000FFFFU
#define LRFDMDM32_DEMSWQU0_SPARE3_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMC1BEREF1_DEMC1BEREF0
//
//*****************************************************************************
// Field: [31:16] CAR31C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR31C16_W                        16U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR31C16_M                0xFFFF0000U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR31C16_S                        16U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR31C16_ALLONES          0xFFFF0000U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR31C16_ALLZEROS         0x00000000U

// Field:  [15:0] CAR15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR15C0_W                         16U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR15C0_M                 0x0000FFFFU
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR15C0_S                          0U
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR15C0_ALLONES           0x0000FFFFU
#define LRFDMDM32_DEMC1BEREF1_DEMC1BEREF0_CAR15C0_ALLZEROS          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMC1BEREF3_DEMC1BEREF2
//
//*****************************************************************************
// Field: [31:16] CBR31C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR31C16_W                        16U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR31C16_M                0xFFFF0000U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR31C16_S                        16U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR31C16_ALLONES          0xFFFF0000U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR31C16_ALLZEROS         0x00000000U

// Field:  [15:0] CBR15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR15C0_W                         16U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR15C0_M                 0x0000FFFFU
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR15C0_S                          0U
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR15C0_ALLONES           0x0000FFFFU
#define LRFDMDM32_DEMC1BEREF3_DEMC1BEREF2_CBR15C0_ALLZEROS          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MODPREAMBLE_MODCTRL
//
//*****************************************************************************
// Field: [31:16] WORD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_WORD_W                                16U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_WORD_M                        0xFFFF0000U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_WORD_S                                16U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_WORD_ALLONES                  0xFFFF0000U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_WORD_ALLZEROS                 0x00000000U

// Field:    [11] DSBUSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_DSBUSEL                       0x00000800U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_DSBUSEL_M                     0x00000800U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_DSBUSEL_S                             11U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_DSBUSEL_ONE                   0x00000800U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_DSBUSEL_ZERO                  0x00000000U

// Field:    [10] HDISMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_HDISMODE                      0x00000400U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_HDISMODE_M                    0x00000400U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_HDISMODE_S                            10U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_HDISMODE_EN                   0x00000400U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_HDISMODE_DIS                  0x00000000U

// Field:     [9] PARBITQUALEN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PARBITQUALEN                  0x00000200U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PARBITQUALEN_M                0x00000200U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PARBITQUALEN_S                         9U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PARBITQUALEN_ON               0x00000200U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PARBITQUALEN_OFF              0x00000000U

// Field:   [8:7] STIMMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EARLY                    Internal. Only to be used through TI provided API.
// LATE                     Internal. Only to be used through TI provided API.
// NORMAL                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_W                             2U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_M                    0x00000180U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_S                             7U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_EARLY                0x00000100U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_LATE                 0x00000080U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_STIMMODE_NORMAL               0x00000000U

// Field:     [6] C1BEMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EARLYLATE                Internal. Only to be used through TI provided API.
// NORMAL                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_C1BEMODE                      0x00000040U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_C1BEMODE_M                    0x00000040U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_C1BEMODE_S                             6U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_C1BEMODE_EARLYLATE            0x00000040U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_C1BEMODE_NORMAL               0x00000000U

// Field:     [5] SOFTPDIFFMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTPDIFFMODE                 0x00000020U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTPDIFFMODE_M               0x00000020U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTPDIFFMODE_S                        5U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTPDIFFMODE_EN              0x00000020U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTPDIFFMODE_DIS             0x00000000U

// Field:     [4] SOFTTXENABLE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTTXENABLE                  0x00000010U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTTXENABLE_M                0x00000010U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTTXENABLE_S                         4U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTTXENABLE_ON               0x00000010U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_SOFTTXENABLE_OFF              0x00000000U

// Field:     [3] FECENABLE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FECENABLE                     0x00000008U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FECENABLE_M                   0x00000008U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FECENABLE_S                            3U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FECENABLE_ON                  0x00000008U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FECENABLE_OFF                 0x00000000U

// Field:     [2] FEC5TERMINATE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ON                       Internal. Only to be used through TI provided API.
// OFF                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FEC5TERMINATE                 0x00000004U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FEC5TERMINATE_M               0x00000004U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FEC5TERMINATE_S                        2U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FEC5TERMINATE_ON              0x00000004U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_FEC5TERMINATE_OFF             0x00000000U

// Field:     [1] TONEINSERT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_TONEINSERT                    0x00000002U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_TONEINSERT_M                  0x00000002U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_TONEINSERT_S                           1U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_TONEINSERT_EN                 0x00000002U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_TONEINSERT_DIS                0x00000000U

// Field:     [0] PREAMBLEINSERT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PREAMBLEINSERT                0x00000001U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PREAMBLEINSERT_M              0x00000001U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PREAMBLEINSERT_S                       0U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PREAMBLEINSERT_EN             0x00000001U
#define LRFDMDM32_MODPREAMBLE_MODCTRL_PREAMBLEINSERT_DIS            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMFRAC1_DEMFRAC0
//
//*****************************************************************************
// Field: [27:16] P27C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P27C16_W                                12U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P27C16_M                        0x0FFF0000U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P27C16_S                                16U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P27C16_ALLONES                  0x0FFF0000U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P27C16_ALLZEROS                 0x00000000U

// Field:  [15:0] P15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P15C0_W                                 16U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P15C0_M                         0x0000FFFFU
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P15C0_S                                  0U
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P15C0_ALLONES                   0x0000FFFFU
#define LRFDMDM32_DEMFRAC1_DEMFRAC0_P15C0_ALLZEROS                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMFRAC3_DEMFRAC2
//
//*****************************************************************************
// Field: [27:16] Q27C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q27C16_W                                12U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q27C16_M                        0x0FFF0000U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q27C16_S                                16U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q27C16_ALLONES                  0x0FFF0000U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q27C16_ALLZEROS                 0x00000000U

// Field:  [15:0] Q15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q15C0_W                                 16U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q15C0_M                         0x0000FFFFU
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q15C0_S                                  0U
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q15C0_ALLONES                   0x0000FFFFU
#define LRFDMDM32_DEMFRAC3_DEMFRAC2_Q15C0_ALLZEROS                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMCODC2_DEMCODC1
//
//*****************************************************************************
// Field: [28:16] COMPQVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPQVAL_W                              13U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPQVAL_M                      0x1FFF0000U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPQVAL_S                              16U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPQVAL_ALLONES                0x1FFF0000U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPQVAL_ALLZEROS               0x00000000U

// Field:  [12:0] COMPIVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPIVAL_W                              13U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPIVAL_M                      0x00001FFFU
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPIVAL_S                               0U
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPIVAL_ALLONES                0x00001FFFU
#define LRFDMDM32_DEMCODC2_DEMCODC1_COMPIVAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMFIDC2_DEMFIDC1
//
//*****************************************************************************
// Field: [28:16] COMPQVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPQVAL_W                              13U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPQVAL_M                      0x1FFF0000U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPQVAL_S                              16U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPQVAL_ALLONES                0x1FFF0000U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPQVAL_ALLZEROS               0x00000000U

// Field:  [12:0] COMPIVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPIVAL_W                              13U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPIVAL_M                      0x00001FFFU
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPIVAL_S                               0U
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPIVAL_ALLONES                0x00001FFFU
#define LRFDMDM32_DEMFIDC2_DEMFIDC1_COMPIVAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMMAFC0_DEMFIFE1
//
//*****************************************************************************
// Field: [23:16] COMPVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_COMPVAL_W                                8U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_COMPVAL_M                       0x00FF0000U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_COMPVAL_S                               16U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_COMPVAL_ALLONES                 0x00FF0000U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_COMPVAL_ALLZEROS                0x00000000U

// Field:   [7:0] FOCFBREGVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_FOCFBREGVAL_W                            8U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_FOCFBREGVAL_M                   0x000000FFU
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_FOCFBREGVAL_S                            0U
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_FOCFBREGVAL_ALLONES             0x000000FFU
#define LRFDMDM32_DEMMAFC0_DEMFIFE1_FOCFBREGVAL_ALLZEROS            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMSWIMBAL_DEMMAFI4
//
//*****************************************************************************
// Field: [31:24] IMBALB
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALB_W                               8U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALB_M                      0xFF000000U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALB_S                              24U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALB_ALLONES                0xFF000000U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALB_ALLZEROS               0x00000000U

// Field: [23:16] IMBALA
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALA_W                               8U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALA_M                      0x00FF0000U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALA_S                              16U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALA_ALLONES                0x00FF0000U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_IMBALA_ALLZEROS               0x00000000U

// Field:   [7:0] TERMVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_TERMVAL_W                              8U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_TERMVAL_M                     0x000000FFU
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_TERMVAL_S                              0U
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_TERMVAL_ALLONES               0x000000FFU
#define LRFDMDM32_DEMSWIMBAL_DEMMAFI4_TERMVAL_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMDEBUG_DEMSOFTPDIFF
//
//*****************************************************************************
// Field: [27:25] LOOPBACKPIN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// GPI7                     Internal. Only to be used through TI provided API.
// GPI6                     Internal. Only to be used through TI provided API.
// GPI5                     Internal. Only to be used through TI provided API.
// GPI4                     Internal. Only to be used through TI provided API.
// GPI3                     Internal. Only to be used through TI provided API.
// GPI2                     Internal. Only to be used through TI provided API.
// GPI1                     Internal. Only to be used through TI provided API.
// GPI0                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_W                        3U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_M               0x0E000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_S                       25U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI7            0x0E000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI6            0x0C000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI5            0x0A000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI4            0x08000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI3            0x06000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI2            0x04000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI1            0x02000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKPIN_GPI0            0x00000000U

// Field:    [24] DECSTAGETRIGGER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGETRIGGER             0x01000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGETRIGGER_M           0x01000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGETRIGGER_S                   24U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGETRIGGER_ONE         0x01000000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGETRIGGER_ZERO        0x00000000U

// Field: [23:21] DECSTAGEDEBUG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SOFD                     Internal. Only to be used through TI provided API.
// STIM                     Internal. Only to be used through TI provided API.
// MAFC                     Internal. Only to be used through TI provided API.
// C1BE                     Internal. Only to be used through TI provided API.
// MAFI                     Internal. Only to be used through TI provided API.
// FIFE                     Internal. Only to be used through TI provided API.
// PDIF                     Internal. Only to be used through TI provided API.
// NOSEL                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_W                      3U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_M             0x00E00000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_S                     21U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_SOFD          0x00E00000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_STIM          0x00C00000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_MAFC          0x00A00000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_C1BE          0x00800000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_MAFI          0x00600000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_FIFE          0x00400000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_PDIF          0x00200000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_DECSTAGEDEBUG_NOSEL         0x00000000U

// Field:    [20] FRONTENDTRIGGER
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDTRIGGER             0x00100000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDTRIGGER_M           0x00100000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDTRIGGER_S                   20U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDTRIGGER_ONE         0x00100000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDTRIGGER_ZERO        0x00000000U

// Field: [19:17] FRONTENDDEBUG
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// FIDC                     Internal. Only to be used through TI provided API.
// FRAC                     Internal. Only to be used through TI provided API.
// CHFI                     Internal. Only to be used through TI provided API.
// BDE2                     Internal. Only to be used through TI provided API.
// FEXB2                    Internal. Only to be used through TI provided API.
// BDE1                     Internal. Only to be used through TI provided API.
// IQMC                     Internal. Only to be used through TI provided API.
// NOSEL                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_W                      3U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_M             0x000E0000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_S                     17U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_FIDC          0x000E0000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_FRAC          0x000C0000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_CHFI          0x000A0000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_BDE2          0x00080000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_FEXB2         0x00060000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_BDE1          0x00040000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_IQMC          0x00020000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_FRONTENDDEBUG_NOSEL         0x00000000U

// Field:    [16] LOOPBACKMODE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKMODE                0x00010000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKMODE_M              0x00010000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKMODE_S                      16U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKMODE_ONE            0x00010000U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_LOOPBACKMODE_ZERO           0x00000000U

// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_VAL_W                                8U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_VAL_M                       0x000000FFU
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_VAL_S                                0U
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_VAL_ALLONES                 0x000000FFU
#define LRFDMDM32_DEMDEBUG_DEMSOFTPDIFF_VAL_ALLZEROS                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_VITCOMPUTE_VITCTRL
//
//*****************************************************************************
// Field:    [16] START
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITCOMPUTE_VITCTRL_START                          0x00010000U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_START_M                        0x00010000U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_START_S                                16U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_START_ONE                      0x00010000U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_START_ZERO                     0x00000000U

// Field:   [7:6] METRSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MLSE                     Internal. Only to be used through TI provided API.
// SOFD                     Internal. Only to be used through TI provided API.
// PHAC                     Internal. Only to be used through TI provided API.
// MET5M                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_W                               2U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_M                      0x000000C0U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_S                               6U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_MLSE                   0x000000C0U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_SOFD                   0x00000080U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_PHAC                   0x00000040U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRSEL_MET5M                  0x00000000U

// Field:   [5:2] APMRDBACKSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// APM7                     Internal. Only to be used through TI provided API.
// APM6                     Internal. Only to be used through TI provided API.
// APM5                     Internal. Only to be used through TI provided API.
// APM4                     Internal. Only to be used through TI provided API.
// APM3                     Internal. Only to be used through TI provided API.
// APM2                     Internal. Only to be used through TI provided API.
// APM1                     Internal. Only to be used through TI provided API.
// APM0                     Internal. Only to be used through TI provided API.
// NOSEL                    Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_W                          4U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_M                 0x0000003CU
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_S                          2U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM7              0x0000003CU
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM6              0x00000038U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM5              0x00000034U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM4              0x00000030U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM3              0x0000002CU
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM2              0x00000028U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM1              0x00000024U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_APM0              0x00000020U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_APMRDBACKSEL_NOSEL             0x00000000U

// Field:     [1] ACSITERATIONS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CODE23                   Internal. Only to be used through TI provided API.
// CODE12                   Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITCOMPUTE_VITCTRL_ACSITERATIONS                  0x00000002U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_ACSITERATIONS_M                0x00000002U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_ACSITERATIONS_S                         1U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_ACSITERATIONS_CODE23           0x00000002U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_ACSITERATIONS_CODE12           0x00000000U

// Field:     [0] METRICS
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// SOFT                     Internal. Only to be used through TI provided API.
// HW                       Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRICS                        0x00000001U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRICS_M                      0x00000001U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRICS_S                               0U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRICS_SOFT                   0x00000001U
#define LRFDMDM32_VITCOMPUTE_VITCTRL_METRICS_HW                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_VITSTATE_VITAPMRDBACK
//
//*****************************************************************************
// Field: [18:16] VITSTATE_VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITSTATE_VALUE_W                     3U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITSTATE_VALUE_M            0x00070000U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITSTATE_VALUE_S                    16U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITSTATE_VALUE_ALLONES      0x00070000U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITSTATE_VALUE_ALLZEROS     0x00000000U

// Field:   [9:0] VITAPMRDBACK_VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITAPMRDBACK_VALUE_W                10U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITAPMRDBACK_VALUE_M        0x000003FFU
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITAPMRDBACK_VALUE_S                 0U
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITAPMRDBACK_VALUE_ALLONES   \
                                                                    0x000003FFU
#define LRFDMDM32_VITSTATE_VITAPMRDBACK_VITAPMRDBACK_VALUE_ALLZEROS  \
                                                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_VITBRMETRIC32_VITBRMETRIC10
//
//*****************************************************************************
// Field: [31:24] MET3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET3_W                         8U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET3_M                0xFF000000U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET3_S                        24U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET3_ALLONES          0xFF000000U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET3_ALLZEROS         0x00000000U

// Field: [23:16] MET2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET2_W                         8U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET2_M                0x00FF0000U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET2_S                        16U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET2_ALLONES          0x00FF0000U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET2_ALLZEROS         0x00000000U

// Field:  [15:8] MET1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET1_W                         8U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET1_M                0x0000FF00U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET1_S                         8U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET1_ALLONES          0x0000FF00U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET1_ALLZEROS         0x00000000U

// Field:   [7:0] MET0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET0_W                         8U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET0_M                0x000000FFU
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET0_S                         0U
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET0_ALLONES          0x000000FFU
#define LRFDMDM32_VITBRMETRIC32_VITBRMETRIC10_MET0_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_VITBRMETRIC76_VITBRMETRIC54
//
//*****************************************************************************
// Field: [31:24] MET7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET7_W                         8U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET7_M                0xFF000000U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET7_S                        24U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET7_ALLONES          0xFF000000U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET7_ALLZEROS         0x00000000U

// Field: [23:16] MET6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET6_W                         8U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET6_M                0x00FF0000U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET6_S                        16U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET6_ALLONES          0x00FF0000U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET6_ALLZEROS         0x00000000U

// Field:  [15:8] MET5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET5_W                         8U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET5_M                0x0000FF00U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET5_S                         8U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET5_ALLONES          0x0000FF00U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET5_ALLZEROS         0x00000000U

// Field:   [7:0] MET4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET4_W                         8U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET4_M                0x000000FFU
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET4_S                         0U
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET4_ALLONES          0x000000FFU
#define LRFDMDM32_VITBRMETRIC76_VITBRMETRIC54_MET4_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_TIMCTL
//
//*****************************************************************************
// Field: [29:24] CPTSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_CPTSRC_W                                            6U
#define LRFDMDM32_TIMCTL_CPTSRC_M                                   0x3F000000U
#define LRFDMDM32_TIMCTL_CPTSRC_S                                           24U
#define LRFDMDM32_TIMCTL_CPTSRC_ALLONES                             0x3F000000U
#define LRFDMDM32_TIMCTL_CPTSRC_ALLZEROS                            0x00000000U

// Field:    [23] CPTCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_CPTCTL                                     0x00800000U
#define LRFDMDM32_TIMCTL_CPTCTL_M                                   0x00800000U
#define LRFDMDM32_TIMCTL_CPTCTL_S                                           23U
#define LRFDMDM32_TIMCTL_CPTCTL_EN                                  0x00800000U
#define LRFDMDM32_TIMCTL_CPTCTL_DIS                                 0x00000000U

// Field: [22:21] CNTRSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLK4BAUDF                Internal. Only to be used through TI provided API.
// CLK4BAUD                 Internal. Only to be used through TI provided API.
// CLKBAUD                  Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_CNTRSRC_W                                           2U
#define LRFDMDM32_TIMCTL_CNTRSRC_M                                  0x00600000U
#define LRFDMDM32_TIMCTL_CNTRSRC_S                                          21U
#define LRFDMDM32_TIMCTL_CNTRSRC_CLK4BAUDF                          0x00600000U
#define LRFDMDM32_TIMCTL_CNTRSRC_CLK4BAUD                           0x00400000U
#define LRFDMDM32_TIMCTL_CNTRSRC_CLKBAUD                            0x00200000U
#define LRFDMDM32_TIMCTL_CNTRSRC_CLK                                0x00000000U

// Field:    [20] CNTRCLR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_CNTRCLR                                    0x00100000U
#define LRFDMDM32_TIMCTL_CNTRCLR_M                                  0x00100000U
#define LRFDMDM32_TIMCTL_CNTRCLR_S                                          20U
#define LRFDMDM32_TIMCTL_CNTRCLR_ONE                                0x00100000U
#define LRFDMDM32_TIMCTL_CNTRCLR_ZERO                               0x00000000U

// Field:    [19] CNTRCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_CNTRCTL                                    0x00080000U
#define LRFDMDM32_TIMCTL_CNTRCTL_M                                  0x00080000U
#define LRFDMDM32_TIMCTL_CNTRCTL_S                                          19U
#define LRFDMDM32_TIMCTL_CNTRCTL_ONE                                0x00080000U
#define LRFDMDM32_TIMCTL_CNTRCTL_ZERO                               0x00000000U

// Field: [18:17] TIMSRC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// CLK4BAUDF                Internal. Only to be used through TI provided API.
// CLK4BAUD                 Internal. Only to be used through TI provided API.
// CLKBAUD                  Internal. Only to be used through TI provided API.
// CLK                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_TIMSRC_W                                            2U
#define LRFDMDM32_TIMCTL_TIMSRC_M                                   0x00060000U
#define LRFDMDM32_TIMCTL_TIMSRC_S                                           17U
#define LRFDMDM32_TIMCTL_TIMSRC_CLK4BAUDF                           0x00060000U
#define LRFDMDM32_TIMCTL_TIMSRC_CLK4BAUD                            0x00040000U
#define LRFDMDM32_TIMCTL_TIMSRC_CLKBAUD                             0x00020000U
#define LRFDMDM32_TIMCTL_TIMSRC_CLK                                 0x00000000U

// Field:    [16] TIMCTL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCTL_TIMCTL                                     0x00010000U
#define LRFDMDM32_TIMCTL_TIMCTL_M                                   0x00010000U
#define LRFDMDM32_TIMCTL_TIMCTL_S                                           16U
#define LRFDMDM32_TIMCTL_TIMCTL_EN                                  0x00010000U
#define LRFDMDM32_TIMCTL_TIMCTL_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_TIMPER_TIMINC
//
//*****************************************************************************
// Field: [31:16] TIMPER_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMPER_TIMINC_TIMPER_VAL_W                                16U
#define LRFDMDM32_TIMPER_TIMINC_TIMPER_VAL_M                        0xFFFF0000U
#define LRFDMDM32_TIMPER_TIMINC_TIMPER_VAL_S                                16U
#define LRFDMDM32_TIMPER_TIMINC_TIMPER_VAL_ALLONES                  0xFFFF0000U
#define LRFDMDM32_TIMPER_TIMINC_TIMPER_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] TIMINC_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMPER_TIMINC_TIMINC_VAL_W                                16U
#define LRFDMDM32_TIMPER_TIMINC_TIMINC_VAL_M                        0x0000FFFFU
#define LRFDMDM32_TIMPER_TIMINC_TIMINC_VAL_S                                 0U
#define LRFDMDM32_TIMPER_TIMINC_TIMINC_VAL_ALLONES                  0x0000FFFFU
#define LRFDMDM32_TIMPER_TIMINC_TIMINC_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_TIMCAPT_TIMCNT
//
//*****************************************************************************
// Field: [31:16] VALUE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCAPT_TIMCNT_VALUE_W                                    16U
#define LRFDMDM32_TIMCAPT_TIMCNT_VALUE_M                            0xFFFF0000U
#define LRFDMDM32_TIMCAPT_TIMCNT_VALUE_S                                    16U
#define LRFDMDM32_TIMCAPT_TIMCNT_VALUE_ALLONES                      0xFFFF0000U
#define LRFDMDM32_TIMCAPT_TIMCNT_VALUE_ALLZEROS                     0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_TIMCAPT_TIMCNT_VAL_W                                      16U
#define LRFDMDM32_TIMCAPT_TIMCNT_VAL_M                              0x0000FFFFU
#define LRFDMDM32_TIMCAPT_TIMCNT_VAL_S                                       0U
#define LRFDMDM32_TIMCAPT_TIMCNT_VAL_ALLONES                        0x0000FFFFU
#define LRFDMDM32_TIMCAPT_TIMCNT_VAL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_COUNT1IN_TIMEBASE
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_COUNT1IN_TIMEBASE_VAL_W                                   16U
#define LRFDMDM32_COUNT1IN_TIMEBASE_VAL_M                           0xFFFF0000U
#define LRFDMDM32_COUNT1IN_TIMEBASE_VAL_S                                   16U
#define LRFDMDM32_COUNT1IN_TIMEBASE_VAL_ALLONES                     0xFFFF0000U
#define LRFDMDM32_COUNT1IN_TIMEBASE_VAL_ALLZEROS                    0x00000000U

// Field:     [0] FLUSH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_COUNT1IN_TIMEBASE_FLUSH                           0x00000001U
#define LRFDMDM32_COUNT1IN_TIMEBASE_FLUSH_M                         0x00000001U
#define LRFDMDM32_COUNT1IN_TIMEBASE_FLUSH_S                                  0U
#define LRFDMDM32_COUNT1IN_TIMEBASE_FLUSH_ONE                       0x00000001U
#define LRFDMDM32_COUNT1IN_TIMEBASE_FLUSH_ZERO                      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_COUNT1RES
//
//*****************************************************************************
// Field:   [4:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_COUNT1RES_VAL_W                                            5U
#define LRFDMDM32_COUNT1RES_VAL_M                                   0x0000001FU
#define LRFDMDM32_COUNT1RES_VAL_S                                            0U
#define LRFDMDM32_COUNT1RES_VAL_ALLONES                             0x0000001FU
#define LRFDMDM32_COUNT1RES_VAL_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_BRMACC2_BRMACC1
//
//*****************************************************************************
// Field: [31:24] METRIC11
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC11_W                                 8U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC11_M                        0xFF000000U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC11_S                                24U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC11_ALLONES                  0xFF000000U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC11_ALLZEROS                 0x00000000U

// Field: [23:16] METRIC10
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC10_W                                 8U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC10_M                        0x00FF0000U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC10_S                                16U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC10_ALLONES                  0x00FF0000U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC10_ALLZEROS                 0x00000000U

// Field:  [15:8] METRIC01
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC01_W                                 8U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC01_M                        0x0000FF00U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC01_S                                 8U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC01_ALLONES                  0x0000FF00U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC01_ALLZEROS                 0x00000000U

// Field:   [7:0] METRIC00
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC00_W                                 8U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC00_M                        0x000000FFU
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC00_S                                 0U
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC00_ALLONES                  0x000000FFU
#define LRFDMDM32_BRMACC2_BRMACC1_METRIC00_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MCETRCSTAT_MCETRCCTRL
//
//*****************************************************************************
// Field:    [16] BUSY
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_BUSY                        0x00010000U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_BUSY_M                      0x00010000U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_BUSY_S                              16U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_BUSY_ONE                    0x00010000U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_BUSY_ZERO                   0x00000000U

// Field:     [0] SEND
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_SEND                        0x00000001U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_SEND_M                      0x00000001U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_SEND_S                               0U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_SEND_ONE                    0x00000001U
#define LRFDMDM32_MCETRCSTAT_MCETRCCTRL_SEND_ZERO                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_MCETRCPAR0_MCETRCCMD
//
//*****************************************************************************
// Field: [31:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_VAL_W                                16U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_VAL_M                        0xFFFF0000U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_VAL_S                                16U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_VAL_ALLONES                  0xFFFF0000U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_VAL_ALLZEROS                 0x00000000U

// Field:   [9:8] PARCNT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PARCNT_W                              2U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PARCNT_M                     0x00000300U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PARCNT_S                              8U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PARCNT_ALLONES               0x00000300U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PARCNT_ALLZEROS              0x00000000U

// Field:   [7:0] PKTHDR
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PKTHDR_W                              8U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PKTHDR_M                     0x000000FFU
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PKTHDR_S                              0U
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PKTHDR_ALLONES               0x000000FFU
#define LRFDMDM32_MCETRCPAR0_MCETRCCMD_PKTHDR_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_RDCAPT0_MCETRCPAR1
//
//*****************************************************************************
// Field:    [21] CHFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CHFI                           0x00200000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CHFI_M                         0x00200000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CHFI_S                                 21U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CHFI_ONE                       0x00200000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CHFI_ZERO                      0x00000000U

// Field:    [20] BDE2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_BDE2                           0x00100000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_BDE2_M                         0x00100000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_BDE2_S                                 20U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_BDE2_ONE                       0x00100000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_BDE2_ZERO                      0x00000000U

// Field:    [19] FIDC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FIDC                           0x00080000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FIDC_M                         0x00080000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FIDC_S                                 19U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FIDC_ONE                       0x00080000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FIDC_ZERO                      0x00000000U

// Field:    [18] FRAC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FRAC                           0x00040000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FRAC_M                         0x00040000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FRAC_S                                 18U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FRAC_ONE                       0x00040000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_FRAC_ZERO                      0x00000000U

// Field:    [17] MGEX
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_MGEX                           0x00020000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_MGEX_M                         0x00020000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_MGEX_S                                 17U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_MGEX_ONE                       0x00020000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_MGEX_ZERO                      0x00000000U

// Field:    [16] CODC
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CODC                           0x00010000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CODC_M                         0x00010000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CODC_S                                 16U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CODC_ONE                       0x00010000U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_CODC_ZERO                      0x00000000U

// Field:  [15:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_VAL_W                                  16U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_VAL_M                          0x0000FFFFU
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_VAL_S                                   0U
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_VAL_ALLONES                    0x0000FFFFU
#define LRFDMDM32_RDCAPT0_MCETRCPAR1_VAL_ALLZEROS                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_FECAPT0_RDCAPT1
//
//*****************************************************************************
// Field: [28:16] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_VAL_W                                     13U
#define LRFDMDM32_FECAPT0_RDCAPT1_VAL_M                             0x1FFF0000U
#define LRFDMDM32_FECAPT0_RDCAPT1_VAL_S                                     16U
#define LRFDMDM32_FECAPT0_RDCAPT1_VAL_ALLONES                       0x1FFF0000U
#define LRFDMDM32_FECAPT0_RDCAPT1_VAL_ALLZEROS                      0x00000000U

// Field:    [11] C1BEX2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX2                            0x00000800U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX2_M                          0x00000800U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX2_S                                  11U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX2_ONE                        0x00000800U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX2_ZERO                       0x00000000U

// Field:    [10] C1BEX1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX1                            0x00000400U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX1_M                          0x00000400U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX1_S                                  10U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX1_ONE                        0x00000400U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX1_ZERO                       0x00000000U

// Field:     [9] C1BEX0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX0                            0x00000200U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX0_M                          0x00000200U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX0_S                                   9U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX0_ONE                        0x00000200U
#define LRFDMDM32_FECAPT0_RDCAPT1_C1BEX0_ZERO                       0x00000000U

// Field:     [8] SOFD
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_SOFD                              0x00000100U
#define LRFDMDM32_FECAPT0_RDCAPT1_SOFD_M                            0x00000100U
#define LRFDMDM32_FECAPT0_RDCAPT1_SOFD_S                                     8U
#define LRFDMDM32_FECAPT0_RDCAPT1_SOFD_ONE                          0x00000100U
#define LRFDMDM32_FECAPT0_RDCAPT1_SOFD_ZERO                         0x00000000U

// Field:     [7] LQIE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_LQIE                              0x00000080U
#define LRFDMDM32_FECAPT0_RDCAPT1_LQIE_M                            0x00000080U
#define LRFDMDM32_FECAPT0_RDCAPT1_LQIE_S                                     7U
#define LRFDMDM32_FECAPT0_RDCAPT1_LQIE_ONE                          0x00000080U
#define LRFDMDM32_FECAPT0_RDCAPT1_LQIE_ZERO                         0x00000000U

// Field:     [6] STIM
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_STIM                              0x00000040U
#define LRFDMDM32_FECAPT0_RDCAPT1_STIM_M                            0x00000040U
#define LRFDMDM32_FECAPT0_RDCAPT1_STIM_S                                     6U
#define LRFDMDM32_FECAPT0_RDCAPT1_STIM_ONE                          0x00000040U
#define LRFDMDM32_FECAPT0_RDCAPT1_STIM_ZERO                         0x00000000U

// Field:     [5] FIFE
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_FIFE                              0x00000020U
#define LRFDMDM32_FECAPT0_RDCAPT1_FIFE_M                            0x00000020U
#define LRFDMDM32_FECAPT0_RDCAPT1_FIFE_S                                     5U
#define LRFDMDM32_FECAPT0_RDCAPT1_FIFE_ONE                          0x00000020U
#define LRFDMDM32_FECAPT0_RDCAPT1_FIFE_ZERO                         0x00000000U

// Field:     [4] PDIF
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_PDIF                              0x00000010U
#define LRFDMDM32_FECAPT0_RDCAPT1_PDIF_M                            0x00000010U
#define LRFDMDM32_FECAPT0_RDCAPT1_PDIF_S                                     4U
#define LRFDMDM32_FECAPT0_RDCAPT1_PDIF_ONE                          0x00000010U
#define LRFDMDM32_FECAPT0_RDCAPT1_PDIF_ZERO                         0x00000000U

// Field:     [3] CA2P
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_CA2P                              0x00000008U
#define LRFDMDM32_FECAPT0_RDCAPT1_CA2P_M                            0x00000008U
#define LRFDMDM32_FECAPT0_RDCAPT1_CA2P_S                                     3U
#define LRFDMDM32_FECAPT0_RDCAPT1_CA2P_ONE                          0x00000008U
#define LRFDMDM32_FECAPT0_RDCAPT1_CA2P_ZERO                         0x00000000U

// Field:     [2] MAFI
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_MAFI                              0x00000004U
#define LRFDMDM32_FECAPT0_RDCAPT1_MAFI_M                            0x00000004U
#define LRFDMDM32_FECAPT0_RDCAPT1_MAFI_S                                     2U
#define LRFDMDM32_FECAPT0_RDCAPT1_MAFI_ONE                          0x00000004U
#define LRFDMDM32_FECAPT0_RDCAPT1_MAFI_ZERO                         0x00000000U

// Field:     [1] DSBU
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_DSBU                              0x00000002U
#define LRFDMDM32_FECAPT0_RDCAPT1_DSBU_M                            0x00000002U
#define LRFDMDM32_FECAPT0_RDCAPT1_DSBU_S                                     1U
#define LRFDMDM32_FECAPT0_RDCAPT1_DSBU_ONE                          0x00000002U
#define LRFDMDM32_FECAPT0_RDCAPT1_DSBU_ZERO                         0x00000000U

// Field:     [0] MLSEBIT
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_FECAPT0_RDCAPT1_MLSEBIT                           0x00000001U
#define LRFDMDM32_FECAPT0_RDCAPT1_MLSEBIT_M                         0x00000001U
#define LRFDMDM32_FECAPT0_RDCAPT1_MLSEBIT_S                                  0U
#define LRFDMDM32_FECAPT0_RDCAPT1_MLSEBIT_ONE                       0x00000001U
#define LRFDMDM32_FECAPT0_RDCAPT1_MLSEBIT_ZERO                      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DSCAPT0_FECAPT1
//
//*****************************************************************************
// Field: [23:16] DSCAPT0_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DSCAPT0_FECAPT1_DSCAPT0_VAL_W                              8U
#define LRFDMDM32_DSCAPT0_FECAPT1_DSCAPT0_VAL_M                     0x00FF0000U
#define LRFDMDM32_DSCAPT0_FECAPT1_DSCAPT0_VAL_S                             16U
#define LRFDMDM32_DSCAPT0_FECAPT1_DSCAPT0_VAL_ALLONES               0x00FF0000U
#define LRFDMDM32_DSCAPT0_FECAPT1_DSCAPT0_VAL_ALLZEROS              0x00000000U

// Field:  [12:0] FECAPT1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DSCAPT0_FECAPT1_FECAPT1_VAL_W                             13U
#define LRFDMDM32_DSCAPT0_FECAPT1_FECAPT1_VAL_M                     0x00001FFFU
#define LRFDMDM32_DSCAPT0_FECAPT1_FECAPT1_VAL_S                              0U
#define LRFDMDM32_DSCAPT0_FECAPT1_FECAPT1_VAL_ALLONES               0x00001FFFU
#define LRFDMDM32_DSCAPT0_FECAPT1_FECAPT1_VAL_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DSCAPT2_DSCAPT1
//
//*****************************************************************************
// Field: [23:16] DSCAPT2_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT2_VAL_W                              8U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT2_VAL_M                     0x00FF0000U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT2_VAL_S                             16U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT2_VAL_ALLONES               0x00FF0000U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT2_VAL_ALLZEROS              0x00000000U

// Field:   [7:0] DSCAPT1_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT1_VAL_W                              8U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT1_VAL_M                     0x000000FFU
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT1_VAL_S                              0U
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT1_VAL_ALLONES               0x000000FFU
#define LRFDMDM32_DSCAPT2_DSCAPT1_DSCAPT1_VAL_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_DEMSWQU1_DSCAPT3
//
//*****************************************************************************
// Field: [25:18] MAFCCOMPVAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU1_DSCAPT3_MAFCCOMPVAL_W                             8U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_MAFCCOMPVAL_M                    0x03FC0000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_MAFCCOMPVAL_S                            18U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_MAFCCOMPVAL_ALLONES              0x03FC0000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_MAFCCOMPVAL_ALLZEROS             0x00000000U

// Field:    [17] SWSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// B                        Internal. Only to be used through TI provided API.
// A                        Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SWSEL                            0x00020000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SWSEL_M                          0x00020000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SWSEL_S                                  17U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SWSEL_B                          0x00020000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SWSEL_A                          0x00000000U

// Field:    [16] SYNCED
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SYNCED                           0x00010000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SYNCED_M                         0x00010000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SYNCED_S                                 16U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SYNCED_ONE                       0x00010000U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_SYNCED_ZERO                      0x00000000U

// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_DEMSWQU1_DSCAPT3_VAL_W                                     8U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_VAL_M                            0x000000FFU
#define LRFDMDM32_DEMSWQU1_DSCAPT3_VAL_S                                     0U
#define LRFDMDM32_DEMSWQU1_DSCAPT3_VAL_ALLONES                      0x000000FFU
#define LRFDMDM32_DEMSWQU1_DSCAPT3_VAL_ALLZEROS                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_GPOCTRL1_GPOCTRL0
//
//*****************************************************************************
// Field: [31:30] HWCLKSTRETCH
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKSTRETCH_W                           2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKSTRETCH_M                  0xC0000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKSTRETCH_S                          30U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKSTRETCH_ONE                0x40000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKSTRETCH_ZERO               0x00000000U

// Field: [29:27] HWCLKMUX1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX1_W                              3U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX1_M                     0x38000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX1_S                             27U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX1_ONE                   0x08000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX1_ZERO                  0x00000000U

// Field: [26:24] HWCLKMUX0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX0_W                              3U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX0_M                     0x07000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX0_S                             24U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX0_ONE                   0x01000000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_HWCLKMUX0_ZERO                  0x00000000U

// Field: [23:16] SW
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ONE                      Internal. Only to be used through TI provided API.
// ZERO                     Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_SW_W                                     8U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_SW_M                            0x00FF0000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_SW_S                                    16U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_SW_ONE                          0x00010000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_SW_ZERO                         0x00000000U

// Field: [15:14] GPO7
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// TOPSM_WAIT               Internal. Only to be used through TI provided API.
// SW7                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_M                          0x0000C000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_S                                  14U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_THREE                      0x0000C000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_TWO                        0x00008000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_TOPSM_WAIT                 0x00004000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO7_SW7                        0x00000000U

// Field: [13:12] GPO6
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// TRANSPARENT_OUT          Internal. Only to be used through TI provided API.
// SW6                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_M                          0x00003000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_S                                  12U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_THREE                      0x00003000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_TWO                        0x00002000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_TRANSPARENT_OUT            0x00001000U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO6_SW6                        0x00000000U

// Field: [11:10] GPO5
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// DEM_OUT_WORD             Internal. Only to be used through TI provided API.
// SW5                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_M                          0x00000C00U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_S                                  10U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_THREE                      0x00000C00U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_TWO                        0x00000800U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_DEM_OUT_WORD               0x00000400U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO5_SW5                        0x00000000U

// Field:   [9:8] GPO4
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// CORR_PEAK_C              Internal. Only to be used through TI provided API.
// SW4                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_M                          0x00000300U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_S                                   8U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_THREE                      0x00000300U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_TWO                        0x00000200U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_CORR_PEAK_C                0x00000100U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO4_SW4                        0x00000000U

// Field:   [7:6] GPO3
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// CORR_PEAK_B              Internal. Only to be used through TI provided API.
// SW3                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_M                          0x000000C0U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_S                                   6U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_THREE                      0x000000C0U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_TWO                        0x00000080U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_CORR_PEAK_B                0x00000040U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO3_SW3                        0x00000000U

// Field:   [5:4] GPO2
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// CORR_PEAK_A              Internal. Only to be used through TI provided API.
// SW2                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_M                          0x00000030U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_S                                   4U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_THREE                      0x00000030U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_TWO                        0x00000020U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_CORR_PEAK_A                0x00000010U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO2_SW2                        0x00000000U

// Field:   [3:2] GPO1
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// TWO                      Internal. Only to be used through TI provided API.
// HWCLK1                   Internal. Only to be used through TI provided API.
// SW1                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_M                          0x0000000CU
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_S                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_THREE                      0x0000000CU
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_TWO                        0x00000008U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_HWCLK1                     0x00000004U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO1_SW1                        0x00000000U

// Field:   [1:0] GPO0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// THREE                    Internal. Only to be used through TI provided API.
// LOOPBACK                 Internal. Only to be used through TI provided API.
// HWCLK0                   Internal. Only to be used through TI provided API.
// SW0                      Internal. Only to be used through TI provided API.
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_W                                   2U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_M                          0x00000003U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_S                                   0U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_THREE                      0x00000003U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_LOOPBACK                   0x00000002U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_HWCLK0                     0x00000001U
#define LRFDMDM32_GPOCTRL1_GPOCTRL0_GPO0_SW0                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_RFEMAXRSSI_RFERSSI
//
//*****************************************************************************
// Field: [23:16] RFEMAXRSSI_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFEMAXRSSI_VAL_W                        8U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFEMAXRSSI_VAL_M               0x00FF0000U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFEMAXRSSI_VAL_S                       16U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFEMAXRSSI_VAL_ALLONES         0x00FF0000U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFEMAXRSSI_VAL_ALLZEROS        0x00000000U

// Field:   [7:0] RFERSSI_VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFERSSI_VAL_W                           8U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFERSSI_VAL_M                  0x000000FFU
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFERSSI_VAL_S                           0U
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFERSSI_VAL_ALLONES            0x000000FFU
#define LRFDMDM32_RFEMAXRSSI_RFERSSI_RFERSSI_VAL_ALLZEROS           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SYNC0_RFEDBGAIN
//
//*****************************************************************************
// Field: [31:16] SWA15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYNC0_RFEDBGAIN_SWA15C0_W                                 16U
#define LRFDMDM32_SYNC0_RFEDBGAIN_SWA15C0_M                         0xFFFF0000U
#define LRFDMDM32_SYNC0_RFEDBGAIN_SWA15C0_S                                 16U
#define LRFDMDM32_SYNC0_RFEDBGAIN_SWA15C0_ALLONES                   0xFFFF0000U
#define LRFDMDM32_SYNC0_RFEDBGAIN_SWA15C0_ALLZEROS                  0x00000000U

// Field:   [7:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYNC0_RFEDBGAIN_VAL_W                                      8U
#define LRFDMDM32_SYNC0_RFEDBGAIN_VAL_M                             0x000000FFU
#define LRFDMDM32_SYNC0_RFEDBGAIN_VAL_S                                      0U
#define LRFDMDM32_SYNC0_RFEDBGAIN_VAL_ALLONES                       0x000000FFU
#define LRFDMDM32_SYNC0_RFEDBGAIN_VAL_ALLZEROS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SYNC2_SYNC1
//
//*****************************************************************************
// Field: [31:16] SWB15C0
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYNC2_SYNC1_SWB15C0_W                                     16U
#define LRFDMDM32_SYNC2_SYNC1_SWB15C0_M                             0xFFFF0000U
#define LRFDMDM32_SYNC2_SYNC1_SWB15C0_S                                     16U
#define LRFDMDM32_SYNC2_SYNC1_SWB15C0_ALLONES                       0xFFFF0000U
#define LRFDMDM32_SYNC2_SYNC1_SWB15C0_ALLZEROS                      0x00000000U

// Field:  [15:0] SWA31C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYNC2_SYNC1_SWA31C16_W                                    16U
#define LRFDMDM32_SYNC2_SYNC1_SWA31C16_M                            0x0000FFFFU
#define LRFDMDM32_SYNC2_SYNC1_SWA31C16_S                                     0U
#define LRFDMDM32_SYNC2_SYNC1_SWA31C16_ALLONES                      0x0000FFFFU
#define LRFDMDM32_SYNC2_SYNC1_SWA31C16_ALLZEROS                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM32_O_SYNC3
//
//*****************************************************************************
// Field:  [15:0] SWB31C16
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// ALLONES                  Internal. Only to be used through TI provided API.
// ALLZEROS                 Internal. Only to be used through TI provided API.
#define LRFDMDM32_SYNC3_SWB31C16_W                                          16U
#define LRFDMDM32_SYNC3_SWB31C16_M                                  0x0000FFFFU
#define LRFDMDM32_SYNC3_SWB31C16_S                                           0U
#define LRFDMDM32_SYNC3_SWB31C16_ALLONES                            0x0000FFFFU
#define LRFDMDM32_SYNC3_SWB31C16_ALLZEROS                           0x00000000U


#endif // __LRFDMDM32__
