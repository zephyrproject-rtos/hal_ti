/******************************************************************************
*  Filename:       hw_lrfdrfe32_h
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

#ifndef __HW_LRFDRFE32_H__
#define __HW_LRFDRFE32_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDRFE32 component
//
//*****************************************************************************
// RF Engine Enable Register 
#define LRFDRFE32_O_FWSRC_ENABLE                                    0x00000000U

// RF Engine Initialization Register 
#define LRFDRFE32_O_PDREQ_INIT                                      0x00000004U

// RFE Event Flag Register 0 
#define LRFDRFE32_O_EVT1_EVT0                                       0x00000008U

// RFE Event Mask Register 0 
#define LRFDRFE32_O_EVTMSK1_EVTMSK0                                 0x0000000CU

// RFE Event Clear Register 0 
#define LRFDRFE32_O_EVTCLR1_EVTCLR0                                 0x00000010U

// Status of the HFXT 
#define LRFDRFE32_O_HFXTSTAT                                        0x00000014U

// RF state indication 
#define LRFDRFE32_O_RFSTATE                                         0x00000018U

// RFE API Command Register 
#define LRFDRFE32_O_CMDPAR0_API                                     0x00000024U

// RFE Command Parameter 1 
#define LRFDRFE32_O_MSGBOX_CMDPAR1                                  0x00000028U

// RFE-to-MCE Send Data Register 
#define LRFDRFE32_O_MCEDATIN0_MCEDATOUT0                            0x0000002CU

// RFE-to-MCE Send Command Register 
#define LRFDRFE32_O_MCECMDIN_MCECMDOUT                              0x00000030U

// RFE-to-PBE Send Data Register 
#define LRFDRFE32_O_PBEDATIN0_PBEDATOUT0                            0x00000034U

// RFE-to-PBE Send Command Register 
#define LRFDRFE32_O_PBECMDIN_PBECMDOUT                              0x00000038U

// RFE FW Strobe Register 
#define LRFDRFE32_O_STRB                                            0x0000003CU

// Controls automatic comparison of magnitude with threshold 
#define LRFDRFE32_O_MAGNTHR_MAGNTHRCFG                              0x00000040U

// RSSI Offset Adjustment Register 
#define LRFDRFE32_O_GAINCTL_RSSIOFFSET                              0x00000044U

// Magnitude estimator 0 control register 
#define LRFDRFE32_O_MAGNCTL1_MAGNCTL0                               0x00000048U

// Spare Value 
#define LRFDRFE32_O_SPARE1_SPARE0                                   0x0000004CU

// Spare Value 
#define LRFDRFE32_O_SPARE3_SPARE2                                   0x00000050U

// Spare Value 
#define LRFDRFE32_O_SPARE5_SPARE4                                   0x00000054U

// LNA control 
#define LRFDRFE32_O_IFAMPRFLDO_LNA                                  0x00000058U

// PA control register 
#define LRFDRFE32_O_PA1_PA0                                         0x0000005CU

// ULNA control, TRX only 
#define LRFDRFE32_O_IFADC0_ULNA                                     0x00000060U

// IFADC configuration register 
#define LRFDRFE32_O_IFADCLF_IFADC1                                  0x00000064U

// IFADC configuration register 
#define LRFDRFE32_O_IFADCALDO_IFADCQUANT                            0x00000068U

// IFADCLDO configuration register 
#define LRFDRFE32_O_IFADCTST_IFADCDLDO                              0x0000006CU

// Analog test register 
#define LRFDRFE32_O_ATSTREF                                         0x00000070U

// DCO Control 
#define LRFDRFE32_O_DIV_DCO                                         0x00000074U

// LDO control 
#define LRFDRFE32_O_TDCLDO_DIVLDO                                   0x00000078U

// LDO control 
#define LRFDRFE32_O_DCOLDO1_DCOLDO0                                 0x0000007CU

// Predivider configuration 
#define LRFDRFE32_O_PRE1_PRE0                                       0x00000080U

// Predivider configuration 
#define LRFDRFE32_O_PRE3_PRE2                                       0x00000084U

// Calibration Configuration 0 
#define LRFDRFE32_O_CAL1_CAL0                                       0x00000088U

// Calibration Configuration 2 
#define LRFDRFE32_O_CAL3_CAL2                                       0x0000008CU

// SDM and Delay Configuration 
#define LRFDRFE32_O_MISC1_MISC0                                     0x00000090U

// Loop Filter Configuration 
#define LRFDRFE32_O_LF1_LF0                                         0x00000094U

// Phase Configuration 
#define LRFDRFE32_O_PHINIT_PHEDISC                                  0x00000098U

// PLL Monitor Configuration 
#define LRFDRFE32_O_PLLMON1_PLLMON0                                 0x0000009CU

// Modulator Configuration 
#define LRFDRFE32_O_MOD1_MOD0                                       0x000000A0U

// Digital TX Configuration 0 
#define LRFDRFE32_O_DTX1_DTX0                                       0x000000A4U

// Digital TX Configuration 2 
#define LRFDRFE32_O_DTX3_DTX2                                       0x000000A8U

// Digital TX Configuration 4 
#define LRFDRFE32_O_DTX5_DTX4                                       0x000000ACU

// Digital TX Configuration 6 
#define LRFDRFE32_O_DTX7_DTX6                                       0x000000B0U

// Digital TX Configuration 8 
#define LRFDRFE32_O_DTX9_DTX8                                       0x000000B4U

// Digital TX Configuration 10 
#define LRFDRFE32_O_DTX11_DTX10                                     0x000000B8U

// PLL M0 
#define LRFDRFE32_O_PLLM0                                           0x000000BCU

// PLL M1 
#define LRFDRFE32_O_PLLM1                                           0x000000C0U

// Calibration M 
#define LRFDRFE32_O_CALMMID_CALMCRS                                 0x000000C4U

// REFCLK Prescaler Load Value 
#define LRFDRFE32_O_REFDIV                                          0x000000C8U

// DLO control register 0 
#define LRFDRFE32_O_DLOCTL0                                         0x000000CCU

// DLO control register 1 
#define LRFDRFE32_O_DLOCTL1                                         0x000000D0U

// DCO Override 
#define LRFDRFE32_O_DCOOVR1_DCOOVR0                                 0x000000D4U

// Data test 
#define LRFDRFE32_O_DLOEV_DTST                                      0x000000D8U

// DTST read 
#define LRFDRFE32_O_FDCOSPANLSB_DTSTRD                              0x000000DCU

// DCO frequency span 
#define LRFDRFE32_O_TDCCAL_FDCOSPANMSB                              0x000000E0U

// Calibration Code 
#define LRFDRFE32_O_GPI_CALRES                                      0x000000E4U

// Math accellerator input value 
#define LRFDRFE32_O_LIN2LOGOUT_MATHACCELIN                          0x000000E8U

// Divide by three output register 
#define LRFDRFE32_O_TIMCTL_DIVBY3OUT                                0x000000ECU

// RFE Counter Increment Configuration 
#define LRFDRFE32_O_TIMPER_TIMINC                                   0x000000F0U

// RFE Counter Value 
#define LRFDRFE32_O_TIMCAPT_TIMCNT                                  0x000000F4U

// RFE Tracer Send Trigger Register 
#define LRFDRFE32_O_TRCSTAT_TRCCTRL                                 0x000000F8U

// RFE Tracer Commmand Register 
#define LRFDRFE32_O_TRCPAR0_TRCCMD                                  0x000000FCU

// RFE Tracer Command Parameter Register 1 
#define LRFDRFE32_O_GPOCTL_TRCPAR1                                  0x00000100U

// Analog Isolation Control 
#define LRFDRFE32_O_DIVCTL_ANAISOCTL                                0x00000104U

// RX Frontend control register 
#define LRFDRFE32_O_MAGNACC0_RXCTRL                                 0x00000108U

// Magnitude estimator 1 accumulator value 
#define LRFDRFE32_O_RSSI_MAGNACC1                                   0x0000010CU

// RSSI Maximum Value Register 
#define LRFDRFE32_O_RFGAIN_RSSIMAX                                  0x00000110U

// IFADC status 
#define LRFDRFE32_O_DIVSTA_IFADCSTAT                                0x00000114U

// Serial Divider Dividend Register 
#define LRFDRFE32_O_DIVIDEND                                        0x00000118U

// Serial Divider Divisor Register 
#define LRFDRFE32_O_DIVISOR                                         0x0000011CU

// Serial Divider Quotient Register 
#define LRFDRFE32_O_QUOTIENT                                        0x00000120U

// Product of DIVISORL_VAL_LSB and DIVISORH_VAL_MSB 
#define LRFDRFE32_O_PRODUCT                                         0x00000124U

// Serial Multiplier Status Register 
#define LRFDRFE32_O_MULTSTA                                         0x00000128U

// Serial Multiplier Control Register 
#define LRFDRFE32_O_MULTCFG                                         0x0000012CU

//*****************************************************************************
//
// Register: LRFDRFE32_O_FWSRC_ENABLE
//
//*****************************************************************************
// Field:    [18] DATARAM 
//
// ENUMs: 
// S2RRAM                   Use S2RRAM for data 
// RFERAM                   Use RFERAM for data 
#define LRFDRFE32_FWSRC_ENABLE_DATARAM                              0x00040000U
#define LRFDRFE32_FWSRC_ENABLE_DATARAM_M                            0x00040000U
#define LRFDRFE32_FWSRC_ENABLE_DATARAM_S                                    18U
#define LRFDRFE32_FWSRC_ENABLE_DATARAM_S2RRAM                       0x00040000U
#define LRFDRFE32_FWSRC_ENABLE_DATARAM_RFERAM                       0x00000000U

// Field:    [17] FWRAM 
//
// ENUMs: 
// S2RRAM                   Run code from S2RRAM 
// RFERAM                   Run code from RFERAM 
#define LRFDRFE32_FWSRC_ENABLE_FWRAM                                0x00020000U
#define LRFDRFE32_FWSRC_ENABLE_FWRAM_M                              0x00020000U
#define LRFDRFE32_FWSRC_ENABLE_FWRAM_S                                      17U
#define LRFDRFE32_FWSRC_ENABLE_FWRAM_S2RRAM                         0x00020000U
#define LRFDRFE32_FWSRC_ENABLE_FWRAM_RFERAM                         0x00000000U

// Field:    [16] BANK 
//
// ENUMs: 
// ONE                      Run code from bank 1 
// ZERO                     Run code from bank 0 
#define LRFDRFE32_FWSRC_ENABLE_BANK                                 0x00010000U
#define LRFDRFE32_FWSRC_ENABLE_BANK_M                               0x00010000U
#define LRFDRFE32_FWSRC_ENABLE_BANK_S                                       16U
#define LRFDRFE32_FWSRC_ENABLE_BANK_ONE                             0x00010000U
#define LRFDRFE32_FWSRC_ENABLE_BANK_ZERO                            0x00000000U

// Field:     [3] ACC1 
//
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE32_FWSRC_ENABLE_ACC1                                 0x00000008U
#define LRFDRFE32_FWSRC_ENABLE_ACC1_M                               0x00000008U
#define LRFDRFE32_FWSRC_ENABLE_ACC1_S                                        3U
#define LRFDRFE32_FWSRC_ENABLE_ACC1_EN                              0x00000008U
#define LRFDRFE32_FWSRC_ENABLE_ACC1_DIS                             0x00000000U

// Field:     [2] ACC0 
//
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE32_FWSRC_ENABLE_ACC0                                 0x00000004U
#define LRFDRFE32_FWSRC_ENABLE_ACC0_M                               0x00000004U
#define LRFDRFE32_FWSRC_ENABLE_ACC0_S                                        2U
#define LRFDRFE32_FWSRC_ENABLE_ACC0_EN                              0x00000004U
#define LRFDRFE32_FWSRC_ENABLE_ACC0_DIS                             0x00000000U

// Field:     [1] LOCTIM 
//
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE32_FWSRC_ENABLE_LOCTIM                               0x00000002U
#define LRFDRFE32_FWSRC_ENABLE_LOCTIM_M                             0x00000002U
#define LRFDRFE32_FWSRC_ENABLE_LOCTIM_S                                      1U
#define LRFDRFE32_FWSRC_ENABLE_LOCTIM_EN                            0x00000002U
#define LRFDRFE32_FWSRC_ENABLE_LOCTIM_DIS                           0x00000000U

// Field:     [0] TOPSM 
//
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE32_FWSRC_ENABLE_TOPSM                                0x00000001U
#define LRFDRFE32_FWSRC_ENABLE_TOPSM_M                              0x00000001U
#define LRFDRFE32_FWSRC_ENABLE_TOPSM_S                                       0U
#define LRFDRFE32_FWSRC_ENABLE_TOPSM_EN                             0x00000001U
#define LRFDRFE32_FWSRC_ENABLE_TOPSM_DIS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PDREQ_INIT
//
//*****************************************************************************
// Field:    [16] TOPSMPDREQ 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_PDREQ_INIT_TOPSMPDREQ                             0x00010000U
#define LRFDRFE32_PDREQ_INIT_TOPSMPDREQ_M                           0x00010000U
#define LRFDRFE32_PDREQ_INIT_TOPSMPDREQ_S                                   16U
#define LRFDRFE32_PDREQ_INIT_TOPSMPDREQ_ONE                         0x00010000U
#define LRFDRFE32_PDREQ_INIT_TOPSMPDREQ_ZERO                        0x00000000U

// Field:     [3] ACC1 
//
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE32_PDREQ_INIT_ACC1                                   0x00000008U
#define LRFDRFE32_PDREQ_INIT_ACC1_M                                 0x00000008U
#define LRFDRFE32_PDREQ_INIT_ACC1_S                                          3U
#define LRFDRFE32_PDREQ_INIT_ACC1_RESET                             0x00000008U
#define LRFDRFE32_PDREQ_INIT_ACC1_NO_EFFECT                         0x00000000U

// Field:     [2] ACC0 
//
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE32_PDREQ_INIT_ACC0                                   0x00000004U
#define LRFDRFE32_PDREQ_INIT_ACC0_M                                 0x00000004U
#define LRFDRFE32_PDREQ_INIT_ACC0_S                                          2U
#define LRFDRFE32_PDREQ_INIT_ACC0_RESET                             0x00000004U
#define LRFDRFE32_PDREQ_INIT_ACC0_NO_EFFECT                         0x00000000U

// Field:     [1] LOCTIM 
//
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE32_PDREQ_INIT_LOCTIM                                 0x00000002U
#define LRFDRFE32_PDREQ_INIT_LOCTIM_M                               0x00000002U
#define LRFDRFE32_PDREQ_INIT_LOCTIM_S                                        1U
#define LRFDRFE32_PDREQ_INIT_LOCTIM_RESET                           0x00000002U
#define LRFDRFE32_PDREQ_INIT_LOCTIM_NO_EFFECT                       0x00000000U

// Field:     [0] TOPSM 
//
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE32_PDREQ_INIT_TOPSM                                  0x00000001U
#define LRFDRFE32_PDREQ_INIT_TOPSM_M                                0x00000001U
#define LRFDRFE32_PDREQ_INIT_TOPSM_S                                         0U
#define LRFDRFE32_PDREQ_INIT_TOPSM_RESET                            0x00000001U
#define LRFDRFE32_PDREQ_INIT_TOPSM_NO_EFFECT                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_EVT1_EVT0
//
//*****************************************************************************
// Field:    [29] PREREFCLK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_PREREFCLK                               0x20000000U
#define LRFDRFE32_EVT1_EVT0_PREREFCLK_M                             0x20000000U
#define LRFDRFE32_EVT1_EVT0_PREREFCLK_S                                     29U
#define LRFDRFE32_EVT1_EVT0_PREREFCLK_ONE                           0x20000000U
#define LRFDRFE32_EVT1_EVT0_PREREFCLK_ZERO                          0x00000000U

// Field:    [28] REFCLK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_REFCLK                                  0x10000000U
#define LRFDRFE32_EVT1_EVT0_REFCLK_M                                0x10000000U
#define LRFDRFE32_EVT1_EVT0_REFCLK_S                                        28U
#define LRFDRFE32_EVT1_EVT0_REFCLK_ONE                              0x10000000U
#define LRFDRFE32_EVT1_EVT0_REFCLK_ZERO                             0x00000000U

// Field:    [27] FBLWTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_FBLWTHR                                 0x08000000U
#define LRFDRFE32_EVT1_EVT0_FBLWTHR_M                               0x08000000U
#define LRFDRFE32_EVT1_EVT0_FBLWTHR_S                                       27U
#define LRFDRFE32_EVT1_EVT0_FBLWTHR_ONE                             0x08000000U
#define LRFDRFE32_EVT1_EVT0_FBLWTHR_ZERO                            0x00000000U

// Field:    [26] FABVTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_FABVTHR                                 0x04000000U
#define LRFDRFE32_EVT1_EVT0_FABVTHR_M                               0x04000000U
#define LRFDRFE32_EVT1_EVT0_FABVTHR_S                                       26U
#define LRFDRFE32_EVT1_EVT0_FABVTHR_ONE                             0x04000000U
#define LRFDRFE32_EVT1_EVT0_FABVTHR_ZERO                            0x00000000U

// Field:    [25] LOCK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_LOCK                                    0x02000000U
#define LRFDRFE32_EVT1_EVT0_LOCK_M                                  0x02000000U
#define LRFDRFE32_EVT1_EVT0_LOCK_S                                          25U
#define LRFDRFE32_EVT1_EVT0_LOCK_ONE                                0x02000000U
#define LRFDRFE32_EVT1_EVT0_LOCK_ZERO                               0x00000000U

// Field:    [24] LOL 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_LOL                                     0x01000000U
#define LRFDRFE32_EVT1_EVT0_LOL_M                                   0x01000000U
#define LRFDRFE32_EVT1_EVT0_LOL_S                                           24U
#define LRFDRFE32_EVT1_EVT0_LOL_ONE                                 0x01000000U
#define LRFDRFE32_EVT1_EVT0_LOL_ZERO                                0x00000000U

// Field:    [23] GPI7 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI7                                    0x00800000U
#define LRFDRFE32_EVT1_EVT0_GPI7_M                                  0x00800000U
#define LRFDRFE32_EVT1_EVT0_GPI7_S                                          23U
#define LRFDRFE32_EVT1_EVT0_GPI7_ONE                                0x00800000U
#define LRFDRFE32_EVT1_EVT0_GPI7_ZERO                               0x00000000U

// Field:    [22] GPI6 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI6                                    0x00400000U
#define LRFDRFE32_EVT1_EVT0_GPI6_M                                  0x00400000U
#define LRFDRFE32_EVT1_EVT0_GPI6_S                                          22U
#define LRFDRFE32_EVT1_EVT0_GPI6_ONE                                0x00400000U
#define LRFDRFE32_EVT1_EVT0_GPI6_ZERO                               0x00000000U

// Field:    [21] GPI5 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI5                                    0x00200000U
#define LRFDRFE32_EVT1_EVT0_GPI5_M                                  0x00200000U
#define LRFDRFE32_EVT1_EVT0_GPI5_S                                          21U
#define LRFDRFE32_EVT1_EVT0_GPI5_ONE                                0x00200000U
#define LRFDRFE32_EVT1_EVT0_GPI5_ZERO                               0x00000000U

// Field:    [20] GPI4 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI4                                    0x00100000U
#define LRFDRFE32_EVT1_EVT0_GPI4_M                                  0x00100000U
#define LRFDRFE32_EVT1_EVT0_GPI4_S                                          20U
#define LRFDRFE32_EVT1_EVT0_GPI4_ONE                                0x00100000U
#define LRFDRFE32_EVT1_EVT0_GPI4_ZERO                               0x00000000U

// Field:    [19] GPI3 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI3                                    0x00080000U
#define LRFDRFE32_EVT1_EVT0_GPI3_M                                  0x00080000U
#define LRFDRFE32_EVT1_EVT0_GPI3_S                                          19U
#define LRFDRFE32_EVT1_EVT0_GPI3_ONE                                0x00080000U
#define LRFDRFE32_EVT1_EVT0_GPI3_ZERO                               0x00000000U

// Field:    [18] GPI2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI2                                    0x00040000U
#define LRFDRFE32_EVT1_EVT0_GPI2_M                                  0x00040000U
#define LRFDRFE32_EVT1_EVT0_GPI2_S                                          18U
#define LRFDRFE32_EVT1_EVT0_GPI2_ONE                                0x00040000U
#define LRFDRFE32_EVT1_EVT0_GPI2_ZERO                               0x00000000U

// Field:    [17] GPI1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI1                                    0x00020000U
#define LRFDRFE32_EVT1_EVT0_GPI1_M                                  0x00020000U
#define LRFDRFE32_EVT1_EVT0_GPI1_S                                          17U
#define LRFDRFE32_EVT1_EVT0_GPI1_ONE                                0x00020000U
#define LRFDRFE32_EVT1_EVT0_GPI1_ZERO                               0x00000000U

// Field:    [16] GPI0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_GPI0                                    0x00010000U
#define LRFDRFE32_EVT1_EVT0_GPI0_M                                  0x00010000U
#define LRFDRFE32_EVT1_EVT0_GPI0_S                                          16U
#define LRFDRFE32_EVT1_EVT0_GPI0_ONE                                0x00010000U
#define LRFDRFE32_EVT1_EVT0_GPI0_ZERO                               0x00000000U

// Field:    [14] MAGNTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_MAGNTHR                                 0x00004000U
#define LRFDRFE32_EVT1_EVT0_MAGNTHR_M                               0x00004000U
#define LRFDRFE32_EVT1_EVT0_MAGNTHR_S                                       14U
#define LRFDRFE32_EVT1_EVT0_MAGNTHR_ONE                             0x00004000U
#define LRFDRFE32_EVT1_EVT0_MAGNTHR_ZERO                            0x00000000U

// Field:    [13] S2RSTOP 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_S2RSTOP                                 0x00002000U
#define LRFDRFE32_EVT1_EVT0_S2RSTOP_M                               0x00002000U
#define LRFDRFE32_EVT1_EVT0_S2RSTOP_S                                       13U
#define LRFDRFE32_EVT1_EVT0_S2RSTOP_ONE                             0x00002000U
#define LRFDRFE32_EVT1_EVT0_S2RSTOP_ZERO                            0x00000000U

// Field:    [12] SYSTCMP2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_SYSTCMP2                                0x00001000U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP2_M                              0x00001000U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP2_S                                      12U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP2_ONE                            0x00001000U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP2_ZERO                           0x00000000U

// Field:    [11] SYSTCMP1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_SYSTCMP1                                0x00000800U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP1_M                              0x00000800U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP1_S                                      11U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP1_ONE                            0x00000800U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP1_ZERO                           0x00000000U

// Field:    [10] SYSTCMP0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_SYSTCMP0                                0x00000400U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP0_M                              0x00000400U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP0_S                                      10U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP0_ONE                            0x00000400U
#define LRFDRFE32_EVT1_EVT0_SYSTCMP0_ZERO                           0x00000000U

// Field:     [9] PBERFEDAT 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_PBERFEDAT                               0x00000200U
#define LRFDRFE32_EVT1_EVT0_PBERFEDAT_M                             0x00000200U
#define LRFDRFE32_EVT1_EVT0_PBERFEDAT_S                                      9U
#define LRFDRFE32_EVT1_EVT0_PBERFEDAT_ONE                           0x00000200U
#define LRFDRFE32_EVT1_EVT0_PBERFEDAT_ZERO                          0x00000000U

// Field:     [8] MDMRFEDAT 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_MDMRFEDAT                               0x00000100U
#define LRFDRFE32_EVT1_EVT0_MDMRFEDAT_M                             0x00000100U
#define LRFDRFE32_EVT1_EVT0_MDMRFEDAT_S                                      8U
#define LRFDRFE32_EVT1_EVT0_MDMRFEDAT_ONE                           0x00000100U
#define LRFDRFE32_EVT1_EVT0_MDMRFEDAT_ZERO                          0x00000000U

// Field:     [7] DLO 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_DLO                                     0x00000080U
#define LRFDRFE32_EVT1_EVT0_DLO_M                                   0x00000080U
#define LRFDRFE32_EVT1_EVT0_DLO_S                                            7U
#define LRFDRFE32_EVT1_EVT0_DLO_ONE                                 0x00000080U
#define LRFDRFE32_EVT1_EVT0_DLO_ZERO                                0x00000000U

// Field:     [6] PBECMD 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_PBECMD                                  0x00000040U
#define LRFDRFE32_EVT1_EVT0_PBECMD_M                                0x00000040U
#define LRFDRFE32_EVT1_EVT0_PBECMD_S                                         6U
#define LRFDRFE32_EVT1_EVT0_PBECMD_ONE                              0x00000040U
#define LRFDRFE32_EVT1_EVT0_PBECMD_ZERO                             0x00000000U

// Field:     [5] COUNTER 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_COUNTER                                 0x00000020U
#define LRFDRFE32_EVT1_EVT0_COUNTER_M                               0x00000020U
#define LRFDRFE32_EVT1_EVT0_COUNTER_S                                        5U
#define LRFDRFE32_EVT1_EVT0_COUNTER_ONE                             0x00000020U
#define LRFDRFE32_EVT1_EVT0_COUNTER_ZERO                            0x00000000U

// Field:     [4] MDMCMD 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_MDMCMD                                  0x00000010U
#define LRFDRFE32_EVT1_EVT0_MDMCMD_M                                0x00000010U
#define LRFDRFE32_EVT1_EVT0_MDMCMD_S                                         4U
#define LRFDRFE32_EVT1_EVT0_MDMCMD_ONE                              0x00000010U
#define LRFDRFE32_EVT1_EVT0_MDMCMD_ZERO                             0x00000000U

// Field:     [3] ACC1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_ACC1                                    0x00000008U
#define LRFDRFE32_EVT1_EVT0_ACC1_M                                  0x00000008U
#define LRFDRFE32_EVT1_EVT0_ACC1_S                                           3U
#define LRFDRFE32_EVT1_EVT0_ACC1_ONE                                0x00000008U
#define LRFDRFE32_EVT1_EVT0_ACC1_ZERO                               0x00000000U

// Field:     [2] ACC0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_ACC0                                    0x00000004U
#define LRFDRFE32_EVT1_EVT0_ACC0_M                                  0x00000004U
#define LRFDRFE32_EVT1_EVT0_ACC0_S                                           2U
#define LRFDRFE32_EVT1_EVT0_ACC0_ONE                                0x00000004U
#define LRFDRFE32_EVT1_EVT0_ACC0_ZERO                               0x00000000U

// Field:     [1] TIMER 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_TIMER                                   0x00000002U
#define LRFDRFE32_EVT1_EVT0_TIMER_M                                 0x00000002U
#define LRFDRFE32_EVT1_EVT0_TIMER_S                                          1U
#define LRFDRFE32_EVT1_EVT0_TIMER_ONE                               0x00000002U
#define LRFDRFE32_EVT1_EVT0_TIMER_ZERO                              0x00000000U

// Field:     [0] RFEAPI 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVT1_EVT0_RFEAPI                                  0x00000001U
#define LRFDRFE32_EVT1_EVT0_RFEAPI_M                                0x00000001U
#define LRFDRFE32_EVT1_EVT0_RFEAPI_S                                         0U
#define LRFDRFE32_EVT1_EVT0_RFEAPI_ONE                              0x00000001U
#define LRFDRFE32_EVT1_EVT0_RFEAPI_ZERO                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_EVTMSK1_EVTMSK0
//
//*****************************************************************************
// Field:    [29] PREREFCLK 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_PREREFCLK                         0x20000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PREREFCLK_M                       0x20000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PREREFCLK_S                               29U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PREREFCLK_EN                      0x20000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PREREFCLK_DIS                     0x00000000U

// Field:    [28] REFCLK 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_REFCLK                            0x10000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_REFCLK_M                          0x10000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_REFCLK_S                                  28U
#define LRFDRFE32_EVTMSK1_EVTMSK0_REFCLK_EN                         0x10000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_REFCLK_DIS                        0x00000000U

// Field:    [27] FBLWTHR 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_FBLWTHR                           0x08000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FBLWTHR_M                         0x08000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FBLWTHR_S                                 27U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FBLWTHR_EN                        0x08000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FBLWTHR_DIS                       0x00000000U

// Field:    [26] FABVTHR 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_FABVTHR                           0x04000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FABVTHR_M                         0x04000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FABVTHR_S                                 26U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FABVTHR_EN                        0x04000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_FABVTHR_DIS                       0x00000000U

// Field:    [25] LOCK 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOCK                              0x02000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOCK_M                            0x02000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOCK_S                                    25U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOCK_EN                           0x02000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOCK_DIS                          0x00000000U

// Field:    [24] LOL 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOL                               0x01000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOL_M                             0x01000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOL_S                                     24U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOL_EN                            0x01000000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_LOL_DIS                           0x00000000U

// Field:    [23] GPI7 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI7                              0x00800000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI7_M                            0x00800000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI7_S                                    23U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI7_EN                           0x00800000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI7_DIS                          0x00000000U

// Field:    [22] GPI6 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI6                              0x00400000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI6_M                            0x00400000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI6_S                                    22U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI6_EN                           0x00400000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI6_DIS                          0x00000000U

// Field:    [21] GPI5 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI5                              0x00200000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI5_M                            0x00200000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI5_S                                    21U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI5_EN                           0x00200000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI5_DIS                          0x00000000U

// Field:    [20] GPI4 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI4                              0x00100000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI4_M                            0x00100000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI4_S                                    20U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI4_EN                           0x00100000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI4_DIS                          0x00000000U

// Field:    [19] GPI3 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI3                              0x00080000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI3_M                            0x00080000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI3_S                                    19U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI3_EN                           0x00080000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI3_DIS                          0x00000000U

// Field:    [18] GPI2 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI2                              0x00040000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI2_M                            0x00040000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI2_S                                    18U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI2_EN                           0x00040000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI2_DIS                          0x00000000U

// Field:    [17] GPI1 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI1                              0x00020000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI1_M                            0x00020000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI1_S                                    17U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI1_EN                           0x00020000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI1_DIS                          0x00000000U

// Field:    [16] GPI0 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI0                              0x00010000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI0_M                            0x00010000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI0_S                                    16U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI0_EN                           0x00010000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_GPI0_DIS                          0x00000000U

// Field:    [14] MAGNTHR 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_MAGNTHR                           0x00004000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MAGNTHR_M                         0x00004000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MAGNTHR_S                                 14U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MAGNTHR_EN                        0x00004000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MAGNTHR_DIS                       0x00000000U

// Field:    [13] S2RSTOP 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_S2RSTOP                           0x00002000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_S2RSTOP_M                         0x00002000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_S2RSTOP_S                                 13U
#define LRFDRFE32_EVTMSK1_EVTMSK0_S2RSTOP_EN                        0x00002000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_S2RSTOP_DIS                       0x00000000U

// Field:    [12] SYSTCMP2 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP2                          0x00001000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP2_M                        0x00001000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP2_S                                12U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP2_EN                       0x00001000U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP2_DIS                      0x00000000U

// Field:    [11] SYSTCMP1 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP1                          0x00000800U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP1_M                        0x00000800U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP1_S                                11U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP1_EN                       0x00000800U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP1_DIS                      0x00000000U

// Field:    [10] SYSTCMP0 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP0                          0x00000400U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP0_M                        0x00000400U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP0_S                                10U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP0_EN                       0x00000400U
#define LRFDRFE32_EVTMSK1_EVTMSK0_SYSTCMP0_DIS                      0x00000000U

// Field:     [9] PBERFEDAT 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBERFEDAT                         0x00000200U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBERFEDAT_M                       0x00000200U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBERFEDAT_S                                9U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBERFEDAT_EN                      0x00000200U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBERFEDAT_DIS                     0x00000000U

// Field:     [8] MDMRFEDAT 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMRFEDAT                         0x00000100U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMRFEDAT_M                       0x00000100U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMRFEDAT_S                                8U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMRFEDAT_EN                      0x00000100U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMRFEDAT_DIS                     0x00000000U

// Field:     [7] DLO 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_DLO                               0x00000080U
#define LRFDRFE32_EVTMSK1_EVTMSK0_DLO_M                             0x00000080U
#define LRFDRFE32_EVTMSK1_EVTMSK0_DLO_S                                      7U
#define LRFDRFE32_EVTMSK1_EVTMSK0_DLO_EN                            0x00000080U
#define LRFDRFE32_EVTMSK1_EVTMSK0_DLO_DIS                           0x00000000U

// Field:     [6] PBECMD 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBECMD                            0x00000040U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBECMD_M                          0x00000040U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBECMD_S                                   6U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBECMD_EN                         0x00000040U
#define LRFDRFE32_EVTMSK1_EVTMSK0_PBECMD_DIS                        0x00000000U

// Field:     [5] COUNTER 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_COUNTER                           0x00000020U
#define LRFDRFE32_EVTMSK1_EVTMSK0_COUNTER_M                         0x00000020U
#define LRFDRFE32_EVTMSK1_EVTMSK0_COUNTER_S                                  5U
#define LRFDRFE32_EVTMSK1_EVTMSK0_COUNTER_EN                        0x00000020U
#define LRFDRFE32_EVTMSK1_EVTMSK0_COUNTER_DIS                       0x00000000U

// Field:     [4] MDMCMD 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMCMD                            0x00000010U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMCMD_M                          0x00000010U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMCMD_S                                   4U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMCMD_EN                         0x00000010U
#define LRFDRFE32_EVTMSK1_EVTMSK0_MDMCMD_DIS                        0x00000000U

// Field:     [3] ACC1 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC1                              0x00000008U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC1_M                            0x00000008U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC1_S                                     3U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC1_EN                           0x00000008U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC1_DIS                          0x00000000U

// Field:     [2] ACC0 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC0                              0x00000004U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC0_M                            0x00000004U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC0_S                                     2U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC0_EN                           0x00000004U
#define LRFDRFE32_EVTMSK1_EVTMSK0_ACC0_DIS                          0x00000000U

// Field:     [1] TIMER 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_TIMER                             0x00000002U
#define LRFDRFE32_EVTMSK1_EVTMSK0_TIMER_M                           0x00000002U
#define LRFDRFE32_EVTMSK1_EVTMSK0_TIMER_S                                    1U
#define LRFDRFE32_EVTMSK1_EVTMSK0_TIMER_EN                          0x00000002U
#define LRFDRFE32_EVTMSK1_EVTMSK0_TIMER_DIS                         0x00000000U

// Field:     [0] RFEAPI 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_EVTMSK1_EVTMSK0_RFEAPI                            0x00000001U
#define LRFDRFE32_EVTMSK1_EVTMSK0_RFEAPI_M                          0x00000001U
#define LRFDRFE32_EVTMSK1_EVTMSK0_RFEAPI_S                                   0U
#define LRFDRFE32_EVTMSK1_EVTMSK0_RFEAPI_EN                         0x00000001U
#define LRFDRFE32_EVTMSK1_EVTMSK0_RFEAPI_DIS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_EVTCLR1_EVTCLR0
//
//*****************************************************************************
// Field:    [29] PREREFCLK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_PREREFCLK                         0x20000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PREREFCLK_M                       0x20000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PREREFCLK_S                               29U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PREREFCLK_ONE                     0x20000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PREREFCLK_ZERO                    0x00000000U

// Field:    [28] REFCLK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_REFCLK                            0x10000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_REFCLK_M                          0x10000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_REFCLK_S                                  28U
#define LRFDRFE32_EVTCLR1_EVTCLR0_REFCLK_ONE                        0x10000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_REFCLK_ZERO                       0x00000000U

// Field:    [27] FBLWTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_FBLWTHR                           0x08000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FBLWTHR_M                         0x08000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FBLWTHR_S                                 27U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FBLWTHR_ONE                       0x08000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FBLWTHR_ZERO                      0x00000000U

// Field:    [26] FABVTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_FABVTHR                           0x04000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FABVTHR_M                         0x04000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FABVTHR_S                                 26U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FABVTHR_ONE                       0x04000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_FABVTHR_ZERO                      0x00000000U

// Field:    [25] LOCK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOCK                              0x02000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOCK_M                            0x02000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOCK_S                                    25U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOCK_ONE                          0x02000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOCK_ZERO                         0x00000000U

// Field:    [24] LOL 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOL                               0x01000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOL_M                             0x01000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOL_S                                     24U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOL_ONE                           0x01000000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_LOL_ZERO                          0x00000000U

// Field:    [23] GPI7 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI7                              0x00800000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI7_M                            0x00800000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI7_S                                    23U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI7_ONE                          0x00800000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI7_ZERO                         0x00000000U

// Field:    [22] GPI6 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI6                              0x00400000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI6_M                            0x00400000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI6_S                                    22U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI6_ONE                          0x00400000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI6_ZERO                         0x00000000U

// Field:    [21] GPI5 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI5                              0x00200000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI5_M                            0x00200000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI5_S                                    21U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI5_ONE                          0x00200000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI5_ZERO                         0x00000000U

// Field:    [20] GPI4 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI4                              0x00100000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI4_M                            0x00100000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI4_S                                    20U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI4_ONE                          0x00100000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI4_ZERO                         0x00000000U

// Field:    [19] GPI3 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI3                              0x00080000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI3_M                            0x00080000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI3_S                                    19U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI3_ONE                          0x00080000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI3_ZERO                         0x00000000U

// Field:    [18] GPI2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI2                              0x00040000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI2_M                            0x00040000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI2_S                                    18U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI2_ONE                          0x00040000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI2_ZERO                         0x00000000U

// Field:    [17] GPI1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI1                              0x00020000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI1_M                            0x00020000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI1_S                                    17U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI1_ONE                          0x00020000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI1_ZERO                         0x00000000U

// Field:    [16] GPI0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI0                              0x00010000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI0_M                            0x00010000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI0_S                                    16U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI0_ONE                          0x00010000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_GPI0_ZERO                         0x00000000U

// Field:    [14] MAGNTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_MAGNTHR                           0x00004000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MAGNTHR_M                         0x00004000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MAGNTHR_S                                 14U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MAGNTHR_ONE                       0x00004000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MAGNTHR_ZERO                      0x00000000U

// Field:    [13] S2RSTOP 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_S2RSTOP                           0x00002000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_S2RSTOP_M                         0x00002000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_S2RSTOP_S                                 13U
#define LRFDRFE32_EVTCLR1_EVTCLR0_S2RSTOP_ONE                       0x00002000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_S2RSTOP_ZERO                      0x00000000U

// Field:    [12] SYSTCMP2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP2                          0x00001000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP2_M                        0x00001000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP2_S                                12U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP2_ONE                      0x00001000U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP2_ZERO                     0x00000000U

// Field:    [11] SYSTCMP1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP1                          0x00000800U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP1_M                        0x00000800U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP1_S                                11U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP1_ONE                      0x00000800U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP1_ZERO                     0x00000000U

// Field:    [10] SYSTCMP0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP0                          0x00000400U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP0_M                        0x00000400U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP0_S                                10U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP0_ONE                      0x00000400U
#define LRFDRFE32_EVTCLR1_EVTCLR0_SYSTCMP0_ZERO                     0x00000000U

// Field:     [9] PBERFEDAT 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBERFEDAT                         0x00000200U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBERFEDAT_M                       0x00000200U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBERFEDAT_S                                9U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBERFEDAT_ONE                     0x00000200U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBERFEDAT_ZERO                    0x00000000U

// Field:     [8] MDMRFEDAT 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMRFEDAT                         0x00000100U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMRFEDAT_M                       0x00000100U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMRFEDAT_S                                8U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMRFEDAT_ONE                     0x00000100U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMRFEDAT_ZERO                    0x00000000U

// Field:     [7] DLO 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_DLO                               0x00000080U
#define LRFDRFE32_EVTCLR1_EVTCLR0_DLO_M                             0x00000080U
#define LRFDRFE32_EVTCLR1_EVTCLR0_DLO_S                                      7U
#define LRFDRFE32_EVTCLR1_EVTCLR0_DLO_ONE                           0x00000080U
#define LRFDRFE32_EVTCLR1_EVTCLR0_DLO_ZERO                          0x00000000U

// Field:     [6] PBECMD 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBECMD                            0x00000040U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBECMD_M                          0x00000040U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBECMD_S                                   6U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBECMD_ONE                        0x00000040U
#define LRFDRFE32_EVTCLR1_EVTCLR0_PBECMD_ZERO                       0x00000000U

// Field:     [5] COUNTER 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_COUNTER                           0x00000020U
#define LRFDRFE32_EVTCLR1_EVTCLR0_COUNTER_M                         0x00000020U
#define LRFDRFE32_EVTCLR1_EVTCLR0_COUNTER_S                                  5U
#define LRFDRFE32_EVTCLR1_EVTCLR0_COUNTER_ONE                       0x00000020U
#define LRFDRFE32_EVTCLR1_EVTCLR0_COUNTER_ZERO                      0x00000000U

// Field:     [4] MDMCMD 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMCMD                            0x00000010U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMCMD_M                          0x00000010U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMCMD_S                                   4U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMCMD_ONE                        0x00000010U
#define LRFDRFE32_EVTCLR1_EVTCLR0_MDMCMD_ZERO                       0x00000000U

// Field:     [3] ACC1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC1                              0x00000008U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC1_M                            0x00000008U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC1_S                                     3U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC1_ONE                          0x00000008U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC1_ZERO                         0x00000000U

// Field:     [2] ACC0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC0                              0x00000004U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC0_M                            0x00000004U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC0_S                                     2U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC0_ONE                          0x00000004U
#define LRFDRFE32_EVTCLR1_EVTCLR0_ACC0_ZERO                         0x00000000U

// Field:     [1] TIMER 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_TIMER                             0x00000002U
#define LRFDRFE32_EVTCLR1_EVTCLR0_TIMER_M                           0x00000002U
#define LRFDRFE32_EVTCLR1_EVTCLR0_TIMER_S                                    1U
#define LRFDRFE32_EVTCLR1_EVTCLR0_TIMER_ONE                         0x00000002U
#define LRFDRFE32_EVTCLR1_EVTCLR0_TIMER_ZERO                        0x00000000U

// Field:     [0] RFEAPI 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_EVTCLR1_EVTCLR0_RFEAPI                            0x00000001U
#define LRFDRFE32_EVTCLR1_EVTCLR0_RFEAPI_M                          0x00000001U
#define LRFDRFE32_EVTCLR1_EVTCLR0_RFEAPI_S                                   0U
#define LRFDRFE32_EVTCLR1_EVTCLR0_RFEAPI_ONE                        0x00000001U
#define LRFDRFE32_EVTCLR1_EVTCLR0_RFEAPI_ZERO                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_HFXTSTAT
//
//*****************************************************************************
// Field:     [0] STAT 
//
// ENUMs: 
// QUAL                     Clock signal is qualified 
// NONQUAL                  Clock signal is not qualified 
#define LRFDRFE32_HFXTSTAT_STAT                                     0x00000001U
#define LRFDRFE32_HFXTSTAT_STAT_M                                   0x00000001U
#define LRFDRFE32_HFXTSTAT_STAT_S                                            0U
#define LRFDRFE32_HFXTSTAT_STAT_QUAL                                0x00000001U
#define LRFDRFE32_HFXTSTAT_STAT_NONQUAL                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_RFSTATE
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// ENUMs: 
// RX                       RX is active 
// TX                       TX is active 
// SYNTH                    Synth is running 
// IDLE                     Radio is idle 
#define LRFDRFE32_RFSTATE_VAL_W                                              4U
#define LRFDRFE32_RFSTATE_VAL_M                                     0x0000000FU
#define LRFDRFE32_RFSTATE_VAL_S                                              0U
#define LRFDRFE32_RFSTATE_VAL_RX                                    0x00000003U
#define LRFDRFE32_RFSTATE_VAL_TX                                    0x00000002U
#define LRFDRFE32_RFSTATE_VAL_SYNTH                                 0x00000001U
#define LRFDRFE32_RFSTATE_VAL_IDLE                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_CMDPAR0_API
//
//*****************************************************************************
// Field: [31:16] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CMDPAR0_API_VAL_W                                         16U
#define LRFDRFE32_CMDPAR0_API_VAL_M                                 0xFFFF0000U
#define LRFDRFE32_CMDPAR0_API_VAL_S                                         16U
#define LRFDRFE32_CMDPAR0_API_VAL_ALLONES                           0xFFFF0000U
#define LRFDRFE32_CMDPAR0_API_VAL_ALLZEROS                          0x00000000U

// Field:   [7:4] PROTOCOLID 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CMDPAR0_API_PROTOCOLID_W                                   4U
#define LRFDRFE32_CMDPAR0_API_PROTOCOLID_M                          0x000000F0U
#define LRFDRFE32_CMDPAR0_API_PROTOCOLID_S                                   4U
#define LRFDRFE32_CMDPAR0_API_PROTOCOLID_ALLONES                    0x000000F0U
#define LRFDRFE32_CMDPAR0_API_PROTOCOLID_ALLZEROS                   0x00000000U

// Field:   [3:0] RFECMD 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All bits are 0 
#define LRFDRFE32_CMDPAR0_API_RFECMD_W                                       4U
#define LRFDRFE32_CMDPAR0_API_RFECMD_M                              0x0000000FU
#define LRFDRFE32_CMDPAR0_API_RFECMD_S                                       0U
#define LRFDRFE32_CMDPAR0_API_RFECMD_ALLONES                        0x0000000FU
#define LRFDRFE32_CMDPAR0_API_RFECMD_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MSGBOX_CMDPAR1
//
//*****************************************************************************
// Field: [23:16] MSGBOX_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MSGBOX_CMDPAR1_MSGBOX_VAL_W                                8U
#define LRFDRFE32_MSGBOX_CMDPAR1_MSGBOX_VAL_M                       0x00FF0000U
#define LRFDRFE32_MSGBOX_CMDPAR1_MSGBOX_VAL_S                               16U
#define LRFDRFE32_MSGBOX_CMDPAR1_MSGBOX_VAL_ALLONES                 0x00FF0000U
#define LRFDRFE32_MSGBOX_CMDPAR1_MSGBOX_VAL_ALLZEROS                0x00000000U

// Field:  [15:0] CMDPAR1_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MSGBOX_CMDPAR1_CMDPAR1_VAL_W                              16U
#define LRFDRFE32_MSGBOX_CMDPAR1_CMDPAR1_VAL_M                      0x0000FFFFU
#define LRFDRFE32_MSGBOX_CMDPAR1_CMDPAR1_VAL_S                               0U
#define LRFDRFE32_MSGBOX_CMDPAR1_CMDPAR1_VAL_ALLONES                0x0000FFFFU
#define LRFDRFE32_MSGBOX_CMDPAR1_CMDPAR1_VAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MCEDATIN0_MCEDATOUT0
//
//*****************************************************************************
// Field: [31:16] MCEDATIN0_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATIN0_VAL_W                      16U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATIN0_VAL_M              0xFFFF0000U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATIN0_VAL_S                      16U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATIN0_VAL_ALLONES        0xFFFF0000U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATIN0_VAL_ALLZEROS       0x00000000U

// Field:  [15:0] MCEDATOUT0_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATOUT0_VAL_W                     16U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATOUT0_VAL_M             0x0000FFFFU
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATOUT0_VAL_S                      0U
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATOUT0_VAL_ALLONES       0x0000FFFFU
#define LRFDRFE32_MCEDATIN0_MCEDATOUT0_MCEDATOUT0_VAL_ALLZEROS      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MCECMDIN_MCECMDOUT
//
//*****************************************************************************
// Field: [19:16] MCECMDIN_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDIN_VAL_W                          4U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDIN_VAL_M                 0x000F0000U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDIN_VAL_S                         16U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDIN_VAL_ALLONES           0x000F0000U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDIN_VAL_ALLZEROS          0x00000000U

// Field:   [3:0] MCECMDOUT_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDOUT_VAL_W                         4U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDOUT_VAL_M                0x0000000FU
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDOUT_VAL_S                         0U
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDOUT_VAL_ALLONES          0x0000000FU
#define LRFDRFE32_MCECMDIN_MCECMDOUT_MCECMDOUT_VAL_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PBEDATIN0_PBEDATOUT0
//
//*****************************************************************************
// Field: [31:16] PBEDATIN0_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_W                      16U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_M              0xFFFF0000U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_S                      16U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_ALLONES        0xFFFF0000U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATIN0_VAL_ALLZEROS       0x00000000U

// Field:  [15:0] PBEDATOUT0_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_W                     16U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_M             0x0000FFFFU
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_S                      0U
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_ALLONES       0x0000FFFFU
#define LRFDRFE32_PBEDATIN0_PBEDATOUT0_PBEDATOUT0_VAL_ALLZEROS      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PBECMDIN_PBECMDOUT
//
//*****************************************************************************
// Field: [19:16] PBECMDIN_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_W                          4U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_M                 0x000F0000U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_S                         16U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_ALLONES           0x000F0000U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDIN_VAL_ALLZEROS          0x00000000U

// Field:   [3:0] PBECMDOUT_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_W                         4U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_M                0x0000000FU
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_S                         0U
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_ALLONES          0x0000000FU
#define LRFDRFE32_PBECMDIN_PBECMDOUT_PBECMDOUT_VAL_ALLZEROS         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_STRB
//
//*****************************************************************************
// Field:     [7] S2RTRG 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_S2RTRG                                       0x00000080U
#define LRFDRFE32_STRB_S2RTRG_M                                     0x00000080U
#define LRFDRFE32_STRB_S2RTRG_S                                              7U
#define LRFDRFE32_STRB_S2RTRG_ONE                                   0x00000080U
#define LRFDRFE32_STRB_S2RTRG_ZERO                                  0x00000000U

// Field:     [6] DMATRG 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_DMATRG                                       0x00000040U
#define LRFDRFE32_STRB_DMATRG_M                                     0x00000040U
#define LRFDRFE32_STRB_DMATRG_S                                              6U
#define LRFDRFE32_STRB_DMATRG_ONE                                   0x00000040U
#define LRFDRFE32_STRB_DMATRG_ZERO                                  0x00000000U

// Field:     [5] SYSTCPT2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_SYSTCPT2                                     0x00000020U
#define LRFDRFE32_STRB_SYSTCPT2_M                                   0x00000020U
#define LRFDRFE32_STRB_SYSTCPT2_S                                            5U
#define LRFDRFE32_STRB_SYSTCPT2_ONE                                 0x00000020U
#define LRFDRFE32_STRB_SYSTCPT2_ZERO                                0x00000000U

// Field:     [4] SYSTCPT1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_SYSTCPT1                                     0x00000010U
#define LRFDRFE32_STRB_SYSTCPT1_M                                   0x00000010U
#define LRFDRFE32_STRB_SYSTCPT1_S                                            4U
#define LRFDRFE32_STRB_SYSTCPT1_ONE                                 0x00000010U
#define LRFDRFE32_STRB_SYSTCPT1_ZERO                                0x00000000U

// Field:     [3] SYSTCPT0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_SYSTCPT0                                     0x00000008U
#define LRFDRFE32_STRB_SYSTCPT0_M                                   0x00000008U
#define LRFDRFE32_STRB_SYSTCPT0_S                                            3U
#define LRFDRFE32_STRB_SYSTCPT0_ONE                                 0x00000008U
#define LRFDRFE32_STRB_SYSTCPT0_ZERO                                0x00000000U

// Field:     [2] EVT1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_EVT1                                         0x00000004U
#define LRFDRFE32_STRB_EVT1_M                                       0x00000004U
#define LRFDRFE32_STRB_EVT1_S                                                2U
#define LRFDRFE32_STRB_EVT1_ONE                                     0x00000004U
#define LRFDRFE32_STRB_EVT1_ZERO                                    0x00000000U

// Field:     [1] EVT0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_STRB_EVT0                                         0x00000002U
#define LRFDRFE32_STRB_EVT0_M                                       0x00000002U
#define LRFDRFE32_STRB_EVT0_S                                                1U
#define LRFDRFE32_STRB_EVT0_ONE                                     0x00000002U
#define LRFDRFE32_STRB_EVT0_ZERO                                    0x00000000U

// Field:     [0] CMDDONE 
//
// ENUMs: 
// YES                      The bit is 1 
// NO                       The bit is 0 
#define LRFDRFE32_STRB_CMDDONE                                      0x00000001U
#define LRFDRFE32_STRB_CMDDONE_M                                    0x00000001U
#define LRFDRFE32_STRB_CMDDONE_S                                             0U
#define LRFDRFE32_STRB_CMDDONE_YES                                  0x00000001U
#define LRFDRFE32_STRB_CMDDONE_NO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MAGNTHR_MAGNTHRCFG
//
//*****************************************************************************
// Field: [23:16] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_VAL_W                                   8U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_VAL_M                          0x00FF0000U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_VAL_S                                  16U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_VAL_ALLONES                    0x00FF0000U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_VAL_ALLZEROS                   0x00000000U

// Field:     [1] SEL 
//
// ENUMs: 
// MAGNACC1                 Use MAGNACC1 in the compare against the theshold 
//                          in MANGTHR 
// MAGNACC0                 Use MAGNACC0 in the compare against the theshold 
//                          in MANGTHR 
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_SEL                            0x00000002U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_SEL_M                          0x00000002U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_SEL_S                                   1U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_SEL_MAGNACC1                   0x00000002U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_SEL_MAGNACC0                   0x00000000U

// Field:     [0] CTL 
//
// ENUMs: 
// EN                       Enable automatic comparison of magntude with 
//                          threshold (input of lin2log is driven by HW) 
// DIS                      Disable automatic comparison with threshold (input 
//                          of lin2log is driven by FW) 
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_CTL                            0x00000001U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_CTL_M                          0x00000001U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_CTL_S                                   0U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_CTL_EN                         0x00000001U
#define LRFDRFE32_MAGNTHR_MAGNTHRCFG_CTL_DIS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_GAINCTL_RSSIOFFSET
//
//*****************************************************************************
// Field: [19:18] BDE2DVGA 
//
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_W                              2U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_M                     0x000C0000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_S                             18U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_GAIN8                 0x000C0000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_GAIN4                 0x00080000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_GAIN2                 0x00040000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE2DVGA_GAIN1                 0x00000000U

// Field: [17:16] BDE1DVGA 
//
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_W                              2U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_M                     0x00030000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_S                             16U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_GAIN8                 0x00030000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_GAIN4                 0x00020000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_GAIN2                 0x00010000U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_BDE1DVGA_GAIN1                 0x00000000U

// Field:   [7:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_GAINCTL_RSSIOFFSET_VAL_W                                   8U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_VAL_M                          0x000000FFU
#define LRFDRFE32_GAINCTL_RSSIOFFSET_VAL_S                                   0U
#define LRFDRFE32_GAINCTL_RSSIOFFSET_VAL_ALLONES                    0x000000FFU
#define LRFDRFE32_GAINCTL_RSSIOFFSET_VAL_ALLZEROS                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MAGNCTL1_MAGNCTL0
//
//*****************************************************************************
// Field:    [28] MAGNCTL1_PERMODE 
//
// ENUMs: 
// PERIODIC                 Periodic mode 
// ONESHOT                  One-shot mode 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PERMODE                0x10000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PERMODE_M              0x10000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PERMODE_S                      28U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PERMODE_PERIODIC       0x10000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PERMODE_ONESHOT        0x00000000U

// Field: [27:24] MAGNCTL1_SCL 
//
// ENUMs: 
// DIV256                   1/256 
// DIV128                   1/128 
// DIV64                    1/64 
// DIV32                    1/32 
// DIV16                    1/16 
// DIV8 
// DIV4 
// DIV2 
// DIV1                     1/1 (no scaling) 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_W                           4U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_M                  0x0F000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_S                          24U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV256             0x08000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV128             0x07000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV64              0x06000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV32              0x05000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV16              0x04000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV8               0x03000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV4               0x02000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV2               0x01000000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_SCL_DIV1               0x00000000U

// Field: [23:16] MAGNCTL1_PER 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PER_W                           8U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PER_M                  0x00FF0000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PER_S                          16U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PER_ALLONES            0x00FF0000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL1_PER_ALLZEROS           0x00000000U

// Field:    [12] MAGNCTL0_PERMODE 
//
// ENUMs: 
// PERIODIC                 Periodic mode 
// ONESHOT                  One-shot mode 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PERMODE                0x00001000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PERMODE_M              0x00001000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PERMODE_S                      12U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PERMODE_PERIODIC       0x00001000U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PERMODE_ONESHOT        0x00000000U

// Field:  [11:8] MAGNCTL0_SCL 
//
// ENUMs: 
// DIV256                   1/256 
// DIV128                   1/128 
// DIV64                    1/64 
// DIV32                    1/32 
// DIV16                    1/16 
// DIV8 
// DIV4 
// DIV2 
// DIV1                     1/1 (no scaling) 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_W                           4U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_M                  0x00000F00U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_S                           8U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV256             0x00000800U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV128             0x00000700U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV64              0x00000600U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV32              0x00000500U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV16              0x00000400U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV8               0x00000300U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV4               0x00000200U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV2               0x00000100U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_SCL_DIV1               0x00000000U

// Field:   [7:0] MAGNCTL0_PER 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PER_W                           8U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PER_M                  0x000000FFU
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PER_S                           0U
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PER_ALLONES            0x000000FFU
#define LRFDRFE32_MAGNCTL1_MAGNCTL0_MAGNCTL0_PER_ALLZEROS           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_SPARE1_SPARE0
//
//*****************************************************************************
// Field: [31:16] SPARE1_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE1_SPARE0_SPARE1_VAL_W                                16U
#define LRFDRFE32_SPARE1_SPARE0_SPARE1_VAL_M                        0xFFFF0000U
#define LRFDRFE32_SPARE1_SPARE0_SPARE1_VAL_S                                16U
#define LRFDRFE32_SPARE1_SPARE0_SPARE1_VAL_ALLONES                  0xFFFF0000U
#define LRFDRFE32_SPARE1_SPARE0_SPARE1_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] SPARE0_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE1_SPARE0_SPARE0_VAL_W                                16U
#define LRFDRFE32_SPARE1_SPARE0_SPARE0_VAL_M                        0x0000FFFFU
#define LRFDRFE32_SPARE1_SPARE0_SPARE0_VAL_S                                 0U
#define LRFDRFE32_SPARE1_SPARE0_SPARE0_VAL_ALLONES                  0x0000FFFFU
#define LRFDRFE32_SPARE1_SPARE0_SPARE0_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_SPARE3_SPARE2
//
//*****************************************************************************
// Field: [31:16] SPARE3_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE3_SPARE2_SPARE3_VAL_W                                16U
#define LRFDRFE32_SPARE3_SPARE2_SPARE3_VAL_M                        0xFFFF0000U
#define LRFDRFE32_SPARE3_SPARE2_SPARE3_VAL_S                                16U
#define LRFDRFE32_SPARE3_SPARE2_SPARE3_VAL_ALLONES                  0xFFFF0000U
#define LRFDRFE32_SPARE3_SPARE2_SPARE3_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] SPARE2_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE3_SPARE2_SPARE2_VAL_W                                16U
#define LRFDRFE32_SPARE3_SPARE2_SPARE2_VAL_M                        0x0000FFFFU
#define LRFDRFE32_SPARE3_SPARE2_SPARE2_VAL_S                                 0U
#define LRFDRFE32_SPARE3_SPARE2_SPARE2_VAL_ALLONES                  0x0000FFFFU
#define LRFDRFE32_SPARE3_SPARE2_SPARE2_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_SPARE5_SPARE4
//
//*****************************************************************************
// Field: [31:16] SPARE5_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE5_SPARE4_SPARE5_VAL_W                                16U
#define LRFDRFE32_SPARE5_SPARE4_SPARE5_VAL_M                        0xFFFF0000U
#define LRFDRFE32_SPARE5_SPARE4_SPARE5_VAL_S                                16U
#define LRFDRFE32_SPARE5_SPARE4_SPARE5_VAL_ALLONES                  0xFFFF0000U
#define LRFDRFE32_SPARE5_SPARE4_SPARE5_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] SPARE4_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_SPARE5_SPARE4_SPARE4_VAL_W                                16U
#define LRFDRFE32_SPARE5_SPARE4_SPARE4_VAL_M                        0x0000FFFFU
#define LRFDRFE32_SPARE5_SPARE4_SPARE4_VAL_S                                 0U
#define LRFDRFE32_SPARE5_SPARE4_SPARE4_VAL_ALLONES                  0x0000FFFFU
#define LRFDRFE32_SPARE5_SPARE4_SPARE4_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_IFAMPRFLDO_LNA
//
//*****************************************************************************
// Field: [31:25] IFAMPRFLDO_TRIM 
//
// ENUMs: 
// BYPASS                   Regulator is in bypass mode 
// MAX                      Maximum output voltage 
// MIN                      Minimum output voltage 
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_W                           7U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_M                  0xFE000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_S                          25U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_BYPASS             0xFE000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_MAX                0xFC000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_TRIM_MIN                0x00000000U

// Field:    [24] IFAMPRFLDO_EN 
//
// ENUMs: 
// EN                       Enable regulator 
// DIS                      Disable regulator 
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_EN                      0x01000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_EN_M                    0x01000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_EN_S                            24U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_EN_EN                   0x01000000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_EN_DIS                  0x00000000U

// Field: [23:20] IFAMPRFLDO_AAFCAP 
//
// ENUMs: 
// MAX                      Largest capacitance on IFAMP output. Low BW 
// MIN                      Smallest capacitance on IFAMP output. High BW. 
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_AAFCAP_W                         4U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_AAFCAP_M                0x00F00000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_AAFCAP_S                        20U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_AAFCAP_MAX              0x00F00000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_AAFCAP_MIN              0x00000000U

// Field: [19:17] IFAMPRFLDO_IFAMPIB 
//
// ENUMs: 
// MAX                      Max IB 
// MIN                      Minimum IB 
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMPIB_W                        3U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMPIB_M               0x000E0000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMPIB_S                       17U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMPIB_MAX             0x000E0000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMPIB_MIN             0x00000000U

// Field:    [16] IFAMPRFLDO_IFAMP 
//
// ENUMs: 
// EN                       Enable IFAMP 
// DIS                      Disable IFAMP 
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMP                   0x00010000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMP_M                 0x00010000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMP_S                         16U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMP_EN                0x00010000U
#define LRFDRFE32_IFAMPRFLDO_LNA_IFAMPRFLDO_IFAMP_DIS               0x00000000U

// Field:  [15:8] LNA_SPARE 
//
// ENUMs: 
// EN                       Enable IFAMP 
// DIS                      Disable IFAMP 
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_SPARE_W                                 8U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_SPARE_M                        0x0000FF00U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_SPARE_S                                 8U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_SPARE_EN                       0x00000100U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_SPARE_DIS                      0x00000000U

// Field:   [7:4] LNA_TRIM 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_TRIM_W                                  4U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_TRIM_M                         0x000000F0U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_TRIM_S                                  4U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_TRIM_ONES                      0x000000F0U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_TRIM_ZEROS                     0x00000000U

// Field:     [3] LNA_BIAS 
//
// ENUMs: 
// INT                      IPTAT bias currents are from bias circuit inside 
//                          LRF_FRONTEND 
// BGAP                     IPTAT bias currents are from bandgap 
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_BIAS                           0x00000008U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_BIAS_M                         0x00000008U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_BIAS_S                                  3U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_BIAS_INT                       0x00000008U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_BIAS_BGAP                      0x00000000U

// Field:   [2:1] LNA_IB 
//
// ENUMs: 
// MAX                      Maximum IB 
// MIN                      Minimum IB 
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_IB_W                                    2U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_IB_M                           0x00000006U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_IB_S                                    1U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_IB_MAX                         0x00000006U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_IB_MIN                         0x00000000U

// Field:     [0] LNA_EN 
//
// ENUMs: 
// ON                       Enable LNA 
// OFF                      Disable LNA 
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_EN                             0x00000001U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_EN_M                           0x00000001U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_EN_S                                    0U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_EN_ON                          0x00000001U
#define LRFDRFE32_IFAMPRFLDO_LNA_LNA_EN_OFF                         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PA1_PA0
//
//*****************************************************************************
// Field: [31:23] SPARE 
//
// ENUMs: 
// MAX                      Longest ramp time 
// MIN                      Shortest ramp time 
#define LRFDRFE32_PA1_PA0_SPARE_W                                            9U
#define LRFDRFE32_PA1_PA0_SPARE_M                                   0xFF800000U
#define LRFDRFE32_PA1_PA0_SPARE_S                                           23U
#define LRFDRFE32_PA1_PA0_SPARE_MAX                                 0x01800000U
#define LRFDRFE32_PA1_PA0_SPARE_MIN                                 0x00000000U

// Field:    [22] MIXATST 
//
// ENUMs: 
// EN                       Mixers are available on ATEST 
// DIS                      Mixers are not available on ATEST 
#define LRFDRFE32_PA1_PA0_MIXATST                                   0x00400000U
#define LRFDRFE32_PA1_PA0_MIXATST_M                                 0x00400000U
#define LRFDRFE32_PA1_PA0_MIXATST_S                                         22U
#define LRFDRFE32_PA1_PA0_MIXATST_EN                                0x00400000U
#define LRFDRFE32_PA1_PA0_MIXATST_DIS                               0x00000000U

// Field:    [21] LDOITST 
//
// ENUMs: 
// EN                       Current test signal is available through ITEST 
// DIS                      Current test signal not available through ITEST 
#define LRFDRFE32_PA1_PA0_LDOITST                                   0x00200000U
#define LRFDRFE32_PA1_PA0_LDOITST_M                                 0x00200000U
#define LRFDRFE32_PA1_PA0_LDOITST_S                                         21U
#define LRFDRFE32_PA1_PA0_LDOITST_EN                                0x00200000U
#define LRFDRFE32_PA1_PA0_LDOITST_DIS                               0x00000000U

// Field:    [20] LDOATST 
//
// ENUMs: 
// EN                       LDO output voltage is available through ATEST 
// DIS                      LDO output voltage not available through ATEST 
#define LRFDRFE32_PA1_PA0_LDOATST                                   0x00100000U
#define LRFDRFE32_PA1_PA0_LDOATST_M                                 0x00100000U
#define LRFDRFE32_PA1_PA0_LDOATST_S                                         20U
#define LRFDRFE32_PA1_PA0_LDOATST_EN                                0x00100000U
#define LRFDRFE32_PA1_PA0_LDOATST_DIS                               0x00000000U

// Field: [19:18] RC 
//
// ENUMs: 
// MAX                      Longest ramp time 
// MIN                      Shortest ramp time 
#define LRFDRFE32_PA1_PA0_RC_W                                               2U
#define LRFDRFE32_PA1_PA0_RC_M                                      0x000C0000U
#define LRFDRFE32_PA1_PA0_RC_S                                              18U
#define LRFDRFE32_PA1_PA0_RC_MAX                                    0x000C0000U
#define LRFDRFE32_PA1_PA0_RC_MIN                                    0x00000000U

// Field:    [17] RAMP 
//
// ENUMs: 
// UP                       Ramp up 
// DOWN                     Ramp down 
#define LRFDRFE32_PA1_PA0_RAMP                                      0x00020000U
#define LRFDRFE32_PA1_PA0_RAMP_M                                    0x00020000U
#define LRFDRFE32_PA1_PA0_RAMP_S                                            17U
#define LRFDRFE32_PA1_PA0_RAMP_UP                                   0x00020000U
#define LRFDRFE32_PA1_PA0_RAMP_DOWN                                 0x00000000U

// Field:    [16] EN 
//
// ENUMs: 
// EN                       Enable PA 
// DIS                      Disable PA 
#define LRFDRFE32_PA1_PA0_EN                                        0x00010000U
#define LRFDRFE32_PA1_PA0_EN_M                                      0x00010000U
#define LRFDRFE32_PA1_PA0_EN_S                                              16U
#define LRFDRFE32_PA1_PA0_EN_EN                                     0x00010000U
#define LRFDRFE32_PA1_PA0_EN_DIS                                    0x00000000U

// Field:    [15] SPARE15 
//
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is 0 
#define LRFDRFE32_PA1_PA0_SPARE15                                   0x00008000U
#define LRFDRFE32_PA1_PA0_SPARE15_M                                 0x00008000U
#define LRFDRFE32_PA1_PA0_SPARE15_S                                         15U
#define LRFDRFE32_PA1_PA0_SPARE15_ONE                               0x00008000U
#define LRFDRFE32_PA1_PA0_SPARE15_ZERO                              0x00000000U

// Field:    [14] MODE 
//
// ENUMs: 
// HIGH                     High power mode, max 8 dBm 
// LOW                      Low power mode, max 3 dBm 
#define LRFDRFE32_PA1_PA0_MODE                                      0x00004000U
#define LRFDRFE32_PA1_PA0_MODE_M                                    0x00004000U
#define LRFDRFE32_PA1_PA0_MODE_S                                            14U
#define LRFDRFE32_PA1_PA0_MODE_HIGH                                 0x00004000U
#define LRFDRFE32_PA1_PA0_MODE_LOW                                  0x00000000U

// Field: [13:11] GAIN 
//
// ENUMs: 
// MAX                      Maximum gain 
// MIN                      Minimum gain 
#define LRFDRFE32_PA1_PA0_GAIN_W                                             3U
#define LRFDRFE32_PA1_PA0_GAIN_M                                    0x00003800U
#define LRFDRFE32_PA1_PA0_GAIN_S                                            11U
#define LRFDRFE32_PA1_PA0_GAIN_MAX                                  0x00003800U
#define LRFDRFE32_PA1_PA0_GAIN_MIN                                  0x00000000U

// Field:  [10:5] IB 
//
// ENUMs: 
// MAX                      Maximum output power 
// MIN                      Minimum output power 
#define LRFDRFE32_PA1_PA0_IB_W                                               6U
#define LRFDRFE32_PA1_PA0_IB_M                                      0x000007E0U
#define LRFDRFE32_PA1_PA0_IB_S                                               5U
#define LRFDRFE32_PA1_PA0_IB_MAX                                    0x000007E0U
#define LRFDRFE32_PA1_PA0_IB_MIN                                    0x00000000U

// Field:   [4:0] TRIM 
//
// ENUMs: 
// MAX                      Maximum bias current 
// MIN                      Minimum bias current 
#define LRFDRFE32_PA1_PA0_TRIM_W                                             5U
#define LRFDRFE32_PA1_PA0_TRIM_M                                    0x0000001FU
#define LRFDRFE32_PA1_PA0_TRIM_S                                             0U
#define LRFDRFE32_PA1_PA0_TRIM_MAX                                  0x0000001FU
#define LRFDRFE32_PA1_PA0_TRIM_MIN                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_IFADC0_ULNA
//
//*****************************************************************************
// Field:    [31] EXTCLK 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_IFADC0_ULNA_EXTCLK                                0x80000000U
#define LRFDRFE32_IFADC0_ULNA_EXTCLK_M                              0x80000000U
#define LRFDRFE32_IFADC0_ULNA_EXTCLK_S                                      31U
#define LRFDRFE32_IFADC0_ULNA_EXTCLK_EN                             0x80000000U
#define LRFDRFE32_IFADC0_ULNA_EXTCLK_DIS                            0x00000000U

// Field: [30:28] DITHERTRIM 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADC0_ULNA_DITHERTRIM_W                                   3U
#define LRFDRFE32_IFADC0_ULNA_DITHERTRIM_M                          0x70000000U
#define LRFDRFE32_IFADC0_ULNA_DITHERTRIM_S                                  28U
#define LRFDRFE32_IFADC0_ULNA_DITHERTRIM_ONES                       0x70000000U
#define LRFDRFE32_IFADC0_ULNA_DITHERTRIM_ZEROS                      0x00000000U

// Field: [27:26] DITHEREN 
//
// ENUMs: 
// ENG                      All the bits are 1 
// ENSD                     All the bits are 1 
// ENS                      All the bits are 1 
// DIS                      All the bits are 0 
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_W                                     2U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_M                            0x0C000000U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_S                                    26U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_ENG                          0x0C000000U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_ENSD                         0x08000000U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_ENS                          0x04000000U
#define LRFDRFE32_IFADC0_ULNA_DITHEREN_DIS                          0x00000000U

// Field:    [25] ADCIEN 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_IFADC0_ULNA_ADCIEN                                0x02000000U
#define LRFDRFE32_IFADC0_ULNA_ADCIEN_M                              0x02000000U
#define LRFDRFE32_IFADC0_ULNA_ADCIEN_S                                      25U
#define LRFDRFE32_IFADC0_ULNA_ADCIEN_EN                             0x02000000U
#define LRFDRFE32_IFADC0_ULNA_ADCIEN_DIS                            0x00000000U

// Field:    [24] ADCQEN 
//
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE32_IFADC0_ULNA_ADCQEN                                0x01000000U
#define LRFDRFE32_IFADC0_ULNA_ADCQEN_M                              0x01000000U
#define LRFDRFE32_IFADC0_ULNA_ADCQEN_S                                      24U
#define LRFDRFE32_IFADC0_ULNA_ADCQEN_EN                             0x01000000U
#define LRFDRFE32_IFADC0_ULNA_ADCQEN_DIS                            0x00000000U

// Field: [23:20] INT2ADJ 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADC0_ULNA_INT2ADJ_W                                      4U
#define LRFDRFE32_IFADC0_ULNA_INT2ADJ_M                             0x00F00000U
#define LRFDRFE32_IFADC0_ULNA_INT2ADJ_S                                     20U
#define LRFDRFE32_IFADC0_ULNA_INT2ADJ_ONES                          0x00F00000U
#define LRFDRFE32_IFADC0_ULNA_INT2ADJ_ZEROS                         0x00000000U

// Field: [19:18] AAFCAP 
//
// ENUMs: 
// ENG                      All the bits are 1 
// ENSD                     All the bits are 1 
// ENS                      All the bits are 1 
// DIS                      All the bits are 0 
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_W                                       2U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_M                              0x000C0000U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_S                                      18U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_ENG                            0x000C0000U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_ENSD                           0x00080000U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_ENS                            0x00040000U
#define LRFDRFE32_IFADC0_ULNA_AAFCAP_DIS                            0x00000000U

// Field:  [15:0] SPARE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_IFADC0_ULNA_SPARE_W                                       16U
#define LRFDRFE32_IFADC0_ULNA_SPARE_M                               0x0000FFFFU
#define LRFDRFE32_IFADC0_ULNA_SPARE_S                                        0U
#define LRFDRFE32_IFADC0_ULNA_SPARE_ALLONES                         0x0000FFFFU
#define LRFDRFE32_IFADC0_ULNA_SPARE_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_IFADCLF_IFADC1
//
//*****************************************************************************
// Field: [31:28] FF3 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_FF3_W                                       4U
#define LRFDRFE32_IFADCLF_IFADC1_FF3_M                              0xF0000000U
#define LRFDRFE32_IFADCLF_IFADC1_FF3_S                                      28U
#define LRFDRFE32_IFADCLF_IFADC1_FF3_ONES                           0xF0000000U
#define LRFDRFE32_IFADCLF_IFADC1_FF3_ZEROS                          0x00000000U

// Field: [27:24] FF2 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_FF2_W                                       4U
#define LRFDRFE32_IFADCLF_IFADC1_FF2_M                              0x0F000000U
#define LRFDRFE32_IFADCLF_IFADC1_FF2_S                                      24U
#define LRFDRFE32_IFADCLF_IFADC1_FF2_ONES                           0x0F000000U
#define LRFDRFE32_IFADCLF_IFADC1_FF2_ZEROS                          0x00000000U

// Field: [23:20] FF1 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_FF1_W                                       4U
#define LRFDRFE32_IFADCLF_IFADC1_FF1_M                              0x00F00000U
#define LRFDRFE32_IFADCLF_IFADC1_FF1_S                                      20U
#define LRFDRFE32_IFADCLF_IFADC1_FF1_ONES                           0x00F00000U
#define LRFDRFE32_IFADCLF_IFADC1_FF1_ZEROS                          0x00000000U

// Field: [19:16] INT3 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_INT3_W                                      4U
#define LRFDRFE32_IFADCLF_IFADC1_INT3_M                             0x000F0000U
#define LRFDRFE32_IFADCLF_IFADC1_INT3_S                                     16U
#define LRFDRFE32_IFADCLF_IFADC1_INT3_ONES                          0x000F0000U
#define LRFDRFE32_IFADCLF_IFADC1_INT3_ZEROS                         0x00000000U

// Field:    [15] NRZ 
//
// ENUMs: 
// EN                       The feedback DAC uses NRZ mode. (Default) 
// DIS                      The feedback DAC uses RZ mode 
#define LRFDRFE32_IFADCLF_IFADC1_NRZ                                0x00008000U
#define LRFDRFE32_IFADCLF_IFADC1_NRZ_M                              0x00008000U
#define LRFDRFE32_IFADCLF_IFADC1_NRZ_S                                      15U
#define LRFDRFE32_IFADCLF_IFADC1_NRZ_EN                             0x00008000U
#define LRFDRFE32_IFADCLF_IFADC1_NRZ_DIS                            0x00000000U

// Field:  [14:9] TRIM 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_TRIM_W                                      6U
#define LRFDRFE32_IFADCLF_IFADC1_TRIM_M                             0x00007E00U
#define LRFDRFE32_IFADCLF_IFADC1_TRIM_S                                      9U
#define LRFDRFE32_IFADCLF_IFADC1_TRIM_ONES                          0x00007E00U
#define LRFDRFE32_IFADCLF_IFADC1_TRIM_ZEROS                         0x00000000U

// Field:     [7] RSTN 
//
// ENUMs: 
// DIS                      DTCs are not reset 
// EN                       DTCs are reset 
#define LRFDRFE32_IFADCLF_IFADC1_RSTN                               0x00000080U
#define LRFDRFE32_IFADCLF_IFADC1_RSTN_M                             0x00000080U
#define LRFDRFE32_IFADCLF_IFADC1_RSTN_S                                      7U
#define LRFDRFE32_IFADCLF_IFADC1_RSTN_DIS                           0x00000080U
#define LRFDRFE32_IFADCLF_IFADC1_RSTN_EN                            0x00000000U

// Field:     [6] CLKGEN 
//
// ENUMs: 
// EN                       Internal clock generator module is enabled 
// DIS                      Internal clock generator module is disabled 
#define LRFDRFE32_IFADCLF_IFADC1_CLKGEN                             0x00000040U
#define LRFDRFE32_IFADCLF_IFADC1_CLKGEN_M                           0x00000040U
#define LRFDRFE32_IFADCLF_IFADC1_CLKGEN_S                                    6U
#define LRFDRFE32_IFADCLF_IFADC1_CLKGEN_EN                          0x00000040U
#define LRFDRFE32_IFADCLF_IFADC1_CLKGEN_DIS                         0x00000000U

// Field:     [5] ADCDIGCLK 
//
// ENUMs: 
// EN                       Clock to decimator enabled 
// DIS                      Clock to decimator disabled 
#define LRFDRFE32_IFADCLF_IFADC1_ADCDIGCLK                          0x00000020U
#define LRFDRFE32_IFADCLF_IFADC1_ADCDIGCLK_M                        0x00000020U
#define LRFDRFE32_IFADCLF_IFADC1_ADCDIGCLK_S                                 5U
#define LRFDRFE32_IFADCLF_IFADC1_ADCDIGCLK_EN                       0x00000020U
#define LRFDRFE32_IFADCLF_IFADC1_ADCDIGCLK_DIS                      0x00000000U

// Field:     [4] ADCLFSROUT 
//
// ENUMs: 
// EN                       The LFSR test output is connected to the ADC 
//                          output 
// DIS                      The quantizer output is connected to the ADC 
//                          output 
#define LRFDRFE32_IFADCLF_IFADC1_ADCLFSROUT                         0x00000010U
#define LRFDRFE32_IFADCLF_IFADC1_ADCLFSROUT_M                       0x00000010U
#define LRFDRFE32_IFADCLF_IFADC1_ADCLFSROUT_S                                4U
#define LRFDRFE32_IFADCLF_IFADC1_ADCLFSROUT_EN                      0x00000010U
#define LRFDRFE32_IFADCLF_IFADC1_ADCLFSROUT_DIS                     0x00000000U

// Field:   [3:1] LPFTSTMODE 
//
// ENUMs: 
// EN                       All the bits are 1 
// DIS                      All the bits are 0 
#define LRFDRFE32_IFADCLF_IFADC1_LPFTSTMODE_W                                3U
#define LRFDRFE32_IFADCLF_IFADC1_LPFTSTMODE_M                       0x0000000EU
#define LRFDRFE32_IFADCLF_IFADC1_LPFTSTMODE_S                                1U
#define LRFDRFE32_IFADCLF_IFADC1_LPFTSTMODE_EN                      0x00000002U
#define LRFDRFE32_IFADCLF_IFADC1_LPFTSTMODE_DIS                     0x00000000U

// Field:     [0] INVCLKOUT 
//
// ENUMs: 
// EN                       Invert IFADC output clock phase (default) 
// DIS                      Keep default IFADC output clock phase 
#define LRFDRFE32_IFADCLF_IFADC1_INVCLKOUT                          0x00000001U
#define LRFDRFE32_IFADCLF_IFADC1_INVCLKOUT_M                        0x00000001U
#define LRFDRFE32_IFADCLF_IFADC1_INVCLKOUT_S                                 0U
#define LRFDRFE32_IFADCLF_IFADC1_INVCLKOUT_EN                       0x00000001U
#define LRFDRFE32_IFADCLF_IFADC1_INVCLKOUT_DIS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_IFADCALDO_IFADCQUANT
//
//*****************************************************************************
// Field:    [31] ATESTVSSANA 
//
// ENUMs: 
// EN                       Connected 
// DIS                      Not connected 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTVSSANA                  0x80000000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTVSSANA_M                0x80000000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTVSSANA_S                        31U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTVSSANA_EN               0x80000000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTVSSANA_DIS              0x00000000U

// Field: [29:24] TRIMOUT 
//
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_TRIMOUT_W                             6U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_TRIMOUT_M                    0x3F000000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_TRIMOUT_S                            24U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_TRIMOUT_ONES                 0x3F000000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_TRIMOUT_ZEROS                0x00000000U

// Field:    [23] DUMMY 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DUMMY                        0x00800000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DUMMY_M                      0x00800000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DUMMY_S                              23U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DUMMY_EN                     0x00800000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DUMMY_DIS                    0x00000000U

// Field:    [22] ATESTOUT 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTOUT                     0x00400000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTOUT_M                   0x00400000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTOUT_S                           22U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTOUT_EN                  0x00400000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTOUT_DIS                 0x00000000U

// Field:    [21] ATSTLDOFB 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATSTLDOFB                    0x00200000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATSTLDOFB_M                  0x00200000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATSTLDOFB_S                          21U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATSTLDOFB_EN                 0x00200000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATSTLDOFB_DIS                0x00000000U

// Field:    [20] ATESTERRAMP 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTERRAMP                  0x00100000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTERRAMP_M                0x00100000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTERRAMP_S                        20U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTERRAMP_EN               0x00100000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ATESTERRAMP_DIS              0x00000000U

// Field:    [19] ITEST 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ITEST                        0x00080000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ITEST_M                      0x00080000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ITEST_S                              19U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ITEST_EN                     0x00080000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_ITEST_DIS                    0x00000000U

// Field:    [18] BYPASS 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_BYPASS                       0x00040000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_BYPASS_M                     0x00040000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_BYPASS_S                             18U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_BYPASS_EN                    0x00040000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_BYPASS_DIS                   0x00000000U

// Field:    [17] CLAMP 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled. The LDO output is shorted to ground when 
//                          disabled. 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLAMP                        0x00020000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLAMP_M                      0x00020000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLAMP_S                              17U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLAMP_EN                     0x00020000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLAMP_DIS                    0x00000000U

// Field:    [16] CTL 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CTL                          0x00010000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CTL_M                        0x00010000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CTL_S                                16U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CTL_EN                       0x00010000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CTL_DIS                      0x00000000U

// Field: [15:14] CLKDLYTRIM 
//
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLKDLYTRIM_W                          2U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLKDLYTRIM_M                 0x0000C000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLKDLYTRIM_S                         14U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLKDLYTRIM_ONES              0x0000C000U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_CLKDLYTRIM_ZEROS             0x00000000U

// Field:  [13:9] DBGCALVALIN 
//
// ENUMs: 
// ONES                     All the bits are ONES 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALVALIN_W                         5U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALVALIN_M                0x00003E00U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALVALIN_S                         9U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALVALIN_ONES             0x00003E00U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALVALIN_ZEROS            0x00000000U

// Field:     [8] DBGCALLEG 
//
// ENUMs: 
// NEG                      Negative leg 
// POS                      Positive leg 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALLEG                    0x00000100U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALLEG_M                  0x00000100U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALLEG_S                           8U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALLEG_NEG                0x00000100U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALLEG_POS                0x00000000U

// Field:   [7:6] DBGCALMQ 
//
// ENUMs: 
// DBGCAL_QMODB             UNCLEAR_Enable quantizer calibration mode. 
// DBGCAL_QMODP             Enable quantizer calibration mode for Positive 
//                          comparator in Q modulator. 
// DBGCAL_QMODN             Enable quantizer calibration mode for Negative 
//                          comparator in Q modulator. 
// DBGCAL_QMODZ             Disable quantizer calibration mode.(Default) 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_W                            2U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_M                   0x000000C0U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_S                            6U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_DBGCAL_QMODB        0x000000C0U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_DBGCAL_QMODP        0x00000080U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_DBGCAL_QMODN        0x00000040U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMQ_DBGCAL_QMODZ        0x00000000U

// Field:   [5:4] DBGCALMI 
//
// ENUMs: 
// DBGCAL_IMODB             UNCLEAR_Enable quantizer calibration mode. 
// DBGCAL_IMODP             Enable quantizer calibration mode for Positive 
//                          comparator in I modulator. 
// DBGCAL_IMODN             Enable quantizer calibration mode for Negative 
//                          comparator in I modulator. 
// DBGCAL_IMODZ             Disable quantizer calibration mode.(Default) 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_W                            2U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_M                   0x00000030U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_S                            4U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_DBGCAL_IMODB        0x00000030U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_DBGCAL_IMODP        0x00000020U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_DBGCAL_IMODN        0x00000010U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_DBGCALMI_DBGCAL_IMODZ        0x00000000U

// Field:     [3] AUTOCAL 
//
// ENUMs: 
// EN                       Enable the auto calibration logic (Default) 
// DIS                      Disable the auto calibration logic 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_AUTOCAL                      0x00000008U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_AUTOCAL_M                    0x00000008U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_AUTOCAL_S                             3U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_AUTOCAL_EN                   0x00000008U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_AUTOCAL_DIS                  0x00000000U

// Field:   [2:0] QUANTTHR 
//
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE32_IFADCALDO_IFADCQUANT_QUANTTHR_W                            3U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_QUANTTHR_M                   0x00000007U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_QUANTTHR_S                            0U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_QUANTTHR_ONES                0x00000007U
#define LRFDRFE32_IFADCALDO_IFADCQUANT_QUANTTHR_ZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_IFADCTST_IFADCDLDO
//
//*****************************************************************************
// Field:    [23] EXTCURR 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_EXTCURR                        0x00800000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_EXTCURR_M                      0x00800000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_EXTCURR_S                              23U
#define LRFDRFE32_IFADCTST_IFADCDLDO_EXTCURR_EN                     0x00800000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_EXTCURR_DIS                    0x00000000U

// Field:    [22] QCALDBIQ 
//
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBIQ                       0x00400000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBIQ_M                     0x00400000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBIQ_S                             22U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBIQ_COMP1                 0x00400000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBIQ_COMP0                 0x00000000U

// Field:    [21] QCALDBC 
//
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBC                        0x00200000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBC_M                      0x00200000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBC_S                              21U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBC_COMP1                  0x00200000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_QCALDBC_COMP0                  0x00000000U

// Field: [20:16] SEL 
//
// ENUMs: 
// EXTCLKN1                 External ADC clock through ADC_TEST_N (N1 
//                          internally). The the clock should be a 200MHz 
//                          sine wave (it is divided internally to 100MHz). 
// NONE                     ADC_TEST_P and ADC_TEST_N tristated (Default) 
#define LRFDRFE32_IFADCTST_IFADCDLDO_SEL_W                                   5U
#define LRFDRFE32_IFADCTST_IFADCDLDO_SEL_M                          0x001F0000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_SEL_S                                  16U
#define LRFDRFE32_IFADCTST_IFADCDLDO_SEL_EXTCLKN1                   0x001F0000U
#define LRFDRFE32_IFADCTST_IFADCDLDO_SEL_NONE                       0x00000000U

// Field:  [13:8] TRIMOUT 
//
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE32_IFADCTST_IFADCDLDO_TRIMOUT_W                               6U
#define LRFDRFE32_IFADCTST_IFADCDLDO_TRIMOUT_M                      0x00003F00U
#define LRFDRFE32_IFADCTST_IFADCDLDO_TRIMOUT_S                               8U
#define LRFDRFE32_IFADCTST_IFADCDLDO_TRIMOUT_ONES                   0x00003F00U
#define LRFDRFE32_IFADCTST_IFADCDLDO_TRIMOUT_ZEROS                  0x00000000U

// Field:     [7] DUMMY 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_DUMMY                          0x00000080U
#define LRFDRFE32_IFADCTST_IFADCDLDO_DUMMY_M                        0x00000080U
#define LRFDRFE32_IFADCTST_IFADCDLDO_DUMMY_S                                 7U
#define LRFDRFE32_IFADCTST_IFADCDLDO_DUMMY_EN                       0x00000080U
#define LRFDRFE32_IFADCTST_IFADCDLDO_DUMMY_DIS                      0x00000000U

// Field:     [6] ATESTOUT 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTOUT                       0x00000040U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTOUT_M                     0x00000040U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTOUT_S                              6U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTOUT_EN                    0x00000040U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTOUT_DIS                   0x00000000U

// Field:     [5] ATSTBGP 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATSTBGP                        0x00000020U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATSTBGP_M                      0x00000020U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATSTBGP_S                               5U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATSTBGP_EN                     0x00000020U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATSTBGP_DIS                    0x00000000U

// Field:     [4] ATESTERRAMP 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTERRAMP                    0x00000010U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTERRAMP_M                  0x00000010U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTERRAMP_S                           4U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTERRAMP_EN                 0x00000010U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ATESTERRAMP_DIS                0x00000000U

// Field:     [3] ITEST 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_ITEST                          0x00000008U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ITEST_M                        0x00000008U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ITEST_S                                 3U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ITEST_EN                       0x00000008U
#define LRFDRFE32_IFADCTST_IFADCDLDO_ITEST_DIS                      0x00000000U

// Field:     [2] BYPASS 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_BYPASS                         0x00000004U
#define LRFDRFE32_IFADCTST_IFADCDLDO_BYPASS_M                       0x00000004U
#define LRFDRFE32_IFADCTST_IFADCDLDO_BYPASS_S                                2U
#define LRFDRFE32_IFADCTST_IFADCDLDO_BYPASS_EN                      0x00000004U
#define LRFDRFE32_IFADCTST_IFADCDLDO_BYPASS_DIS                     0x00000000U

// Field:     [1] CLAMP 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled. The LDO output is shorted to ground when 
//                          disabled. 
#define LRFDRFE32_IFADCTST_IFADCDLDO_CLAMP                          0x00000002U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CLAMP_M                        0x00000002U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CLAMP_S                                 1U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CLAMP_EN                       0x00000002U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CLAMP_DIS                      0x00000000U

// Field:     [0] CTL 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_IFADCTST_IFADCDLDO_CTL                            0x00000001U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CTL_M                          0x00000001U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CTL_S                                   0U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CTL_EN                         0x00000001U
#define LRFDRFE32_IFADCTST_IFADCDLDO_CTL_DIS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_ATSTREF
//
//*****************************************************************************
// Field:    [31] VREFBPDIS 
//
// ENUMs: 
// BPDIS                    Bandgap reference bypass disabled 
// BPEN                     Bandgap reference bypass enabled. 
#define LRFDRFE32_ATSTREF_VREFBPDIS                                 0x80000000U
#define LRFDRFE32_ATSTREF_VREFBPDIS_M                               0x80000000U
#define LRFDRFE32_ATSTREF_VREFBPDIS_S                                       31U
#define LRFDRFE32_ATSTREF_VREFBPDIS_BPDIS                           0x80000000U
#define LRFDRFE32_ATSTREF_VREFBPDIS_BPEN                            0x00000000U

// Field: [30:26] IREFTRIM 
//
// ENUMs: 
// ONES                     All bits are ones 
// ZEROS                    All bits are zero 
#define LRFDRFE32_ATSTREF_IREFTRIM_W                                         5U
#define LRFDRFE32_ATSTREF_IREFTRIM_M                                0x7C000000U
#define LRFDRFE32_ATSTREF_IREFTRIM_S                                        26U
#define LRFDRFE32_ATSTREF_IREFTRIM_ONES                             0x7C000000U
#define LRFDRFE32_ATSTREF_IREFTRIM_ZEROS                            0x00000000U

// Field:    [25] BIAS 
//
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE32_ATSTREF_BIAS                                      0x02000000U
#define LRFDRFE32_ATSTREF_BIAS_M                                    0x02000000U
#define LRFDRFE32_ATSTREF_BIAS_S                                            25U
#define LRFDRFE32_ATSTREF_BIAS_EN                                   0x02000000U
#define LRFDRFE32_ATSTREF_BIAS_DIS                                  0x00000000U

// Field:    [24] OUTPUT2 
//
// ENUMs: 
// EN                       The output is enabled 
// DIS                      Output is disabled 
#define LRFDRFE32_ATSTREF_OUTPUT2                                   0x01000000U
#define LRFDRFE32_ATSTREF_OUTPUT2_M                                 0x01000000U
#define LRFDRFE32_ATSTREF_OUTPUT2_S                                         24U
#define LRFDRFE32_ATSTREF_OUTPUT2_EN                                0x01000000U
#define LRFDRFE32_ATSTREF_OUTPUT2_DIS                               0x00000000U

// Field:    [23] OUTPUT1 
//
// ENUMs: 
// EN                       The output is enabled 
// DIS                      Output is disabled 
#define LRFDRFE32_ATSTREF_OUTPUT1                                   0x00800000U
#define LRFDRFE32_ATSTREF_OUTPUT1_M                                 0x00800000U
#define LRFDRFE32_ATSTREF_OUTPUT1_S                                         23U
#define LRFDRFE32_ATSTREF_OUTPUT1_EN                                0x00800000U
#define LRFDRFE32_ATSTREF_OUTPUT1_DIS                               0x00000000U

// Field:  [22:0] MUX 
//
// ENUMs: 
// IFADC_ATB                IFADC ATB 
// LDO_VTEST                LDO_VTEST vtest out, current 
// LDO_ITEST                LDO_ITEST itest out, current 
// PA_PEAK_OUTN             PA peak detector output n 
// PA_PEAK_OUTP             PA peak detector output p 
// MIX_OUTQN                MIX outqn, voltage 
// MIX_OUTQP                MIX outqp, voltage 
// MIX_OUTIN                MIX outin, voltage 
// MIX_OUTIP                MIX outip, voltage 
// FE_OUTIN_2               Frontend IF outin, voltage 
// FE_OUTIP_2               Frontend IF outip, voltage 
// FE_OUTQN                 Frontend IF outqn, voltage 
// FE_OUTQP                 Frontend IF outqp, voltage 
// FE_OUTIN                 Frontend IF outin, voltage 
// FE_OUTIP                 Frontend IF outip, voltage 
// DIS                      No atest selected 
#define LRFDRFE32_ATSTREF_MUX_W                                             23U
#define LRFDRFE32_ATSTREF_MUX_M                                     0x007FFFFFU
#define LRFDRFE32_ATSTREF_MUX_S                                              0U
#define LRFDRFE32_ATSTREF_MUX_IFADC_ATB                             0x00008000U
#define LRFDRFE32_ATSTREF_MUX_LDO_VTEST                             0x00004000U
#define LRFDRFE32_ATSTREF_MUX_LDO_ITEST                             0x00002000U
#define LRFDRFE32_ATSTREF_MUX_PA_PEAK_OUTN                          0x00000800U
#define LRFDRFE32_ATSTREF_MUX_PA_PEAK_OUTP                          0x00000400U
#define LRFDRFE32_ATSTREF_MUX_MIX_OUTQN                             0x00000200U
#define LRFDRFE32_ATSTREF_MUX_MIX_OUTQP                             0x00000100U
#define LRFDRFE32_ATSTREF_MUX_MIX_OUTIN                             0x00000080U
#define LRFDRFE32_ATSTREF_MUX_MIX_OUTIP                             0x00000040U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTIN_2                            0x00000020U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTIP_2                            0x00000010U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTQN                              0x00000008U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTQP                              0x00000004U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTIN                              0x00000002U
#define LRFDRFE32_ATSTREF_MUX_FE_OUTIP                              0x00000001U
#define LRFDRFE32_ATSTREF_MUX_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DIV_DCO
//
//*****************************************************************************
// Field:    [31] PDET 
//
// ENUMs: 
// EN                       Peak detektor mode enabled, used in production 
//                          test 
// DIS                      Peak detector mode disabled, normal functional 
//                          mode 
#define LRFDRFE32_DIV_DCO_PDET                                      0x80000000U
#define LRFDRFE32_DIV_DCO_PDET_M                                    0x80000000U
#define LRFDRFE32_DIV_DCO_PDET_S                                            31U
#define LRFDRFE32_DIV_DCO_PDET_EN                                   0x80000000U
#define LRFDRFE32_DIV_DCO_PDET_DIS                                  0x00000000U

// Field: [30:28] NMIREFTRIM 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DIV_DCO_NMIREFTRIM_W                                       3U
#define LRFDRFE32_DIV_DCO_NMIREFTRIM_M                              0x70000000U
#define LRFDRFE32_DIV_DCO_NMIREFTRIM_S                                      28U
#define LRFDRFE32_DIV_DCO_NMIREFTRIM_ALLONES                        0x70000000U
#define LRFDRFE32_DIV_DCO_NMIREFTRIM_ALLZEROS                       0x00000000U

// Field: [27:25] PMIREFTRIM 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DIV_DCO_PMIREFTRIM_W                                       3U
#define LRFDRFE32_DIV_DCO_PMIREFTRIM_M                              0x0E000000U
#define LRFDRFE32_DIV_DCO_PMIREFTRIM_S                                      25U
#define LRFDRFE32_DIV_DCO_PMIREFTRIM_ALLONES                        0x0E000000U
#define LRFDRFE32_DIV_DCO_PMIREFTRIM_ALLZEROS                       0x00000000U

// Field:    [24] TXBBOOST 
//
// ENUMs: 
// INCREASED                High drive strength 
// DEFAULT                  Default drive strength 
#define LRFDRFE32_DIV_DCO_TXBBOOST                                  0x01000000U
#define LRFDRFE32_DIV_DCO_TXBBOOST_M                                0x01000000U
#define LRFDRFE32_DIV_DCO_TXBBOOST_S                                        24U
#define LRFDRFE32_DIV_DCO_TXBBOOST_INCREASED                        0x01000000U
#define LRFDRFE32_DIV_DCO_TXBBOOST_DEFAULT                          0x00000000U

// Field:    [23] S1GFRC 
//
// ENUMs: 
// EN                       Enable force S1G power switch 
// DIS                      Disable force S1G power switch 
#define LRFDRFE32_DIV_DCO_S1GFRC                                    0x00800000U
#define LRFDRFE32_DIV_DCO_S1GFRC_M                                  0x00800000U
#define LRFDRFE32_DIV_DCO_S1GFRC_S                                          23U
#define LRFDRFE32_DIV_DCO_S1GFRC_EN                                 0x00800000U
#define LRFDRFE32_DIV_DCO_S1GFRC_DIS                                0x00000000U

// Field: [22:21] BUFGAIN 
//
// ENUMs: 
// _60_PST                  60% of maximum gain 
// DONT_USE                 Same as _80_PST 
// _80_PST                  80% of maximum gain 
// MAX                      Maximum gain (default) 
#define LRFDRFE32_DIV_DCO_BUFGAIN_W                                          2U
#define LRFDRFE32_DIV_DCO_BUFGAIN_M                                 0x00600000U
#define LRFDRFE32_DIV_DCO_BUFGAIN_S                                         21U
#define LRFDRFE32_DIV_DCO_BUFGAIN__60_PST                           0x00600000U
#define LRFDRFE32_DIV_DCO_BUFGAIN_DONT_USE                          0x00400000U
#define LRFDRFE32_DIV_DCO_BUFGAIN__80_PST                           0x00200000U
#define LRFDRFE32_DIV_DCO_BUFGAIN_MAX                               0x00000000U

// Field:    [20] BIAS 
//
// ENUMs: 
// DEFAULT                  Default bias 
// ALTERNATIVE              Alternative bias (for test purposes) 
#define LRFDRFE32_DIV_DCO_BIAS                                      0x00100000U
#define LRFDRFE32_DIV_DCO_BIAS_M                                    0x00100000U
#define LRFDRFE32_DIV_DCO_BIAS_S                                            20U
#define LRFDRFE32_DIV_DCO_BIAS_DEFAULT                              0x00100000U
#define LRFDRFE32_DIV_DCO_BIAS_ALTERNATIVE                          0x00000000U

// Field:    [19] OUT 
//
// ENUMs: 
// FE_2G4                   Enable outputs going to 2.4GHz front-end 
// FE_S1G                   Enable outputs going to sub-1GHz front-end 
#define LRFDRFE32_DIV_DCO_OUT                                       0x00080000U
#define LRFDRFE32_DIV_DCO_OUT_M                                     0x00080000U
#define LRFDRFE32_DIV_DCO_OUT_S                                             19U
#define LRFDRFE32_DIV_DCO_OUT_FE_2G4                                0x00080000U
#define LRFDRFE32_DIV_DCO_OUT_FE_S1G                                0x00000000U

// Field: [18:16] RATIO 
//
// ENUMs: 
// DIV30                    DIVIDER = 30 
// DIV15                    DIVIDER = 15 
// DIV10                    DIVIDER = 10 
// DIV5                     DIVIDER = 5 
// DIV12                    DIVIDER = 12 
// DIV6                     DIVIDER = 6 
// DIV4                     DIVIDER = 4 (for test purposes only) 
// DIV2                     DIVIDER = 2 
#define LRFDRFE32_DIV_DCO_RATIO_W                                            3U
#define LRFDRFE32_DIV_DCO_RATIO_M                                   0x00070000U
#define LRFDRFE32_DIV_DCO_RATIO_S                                           16U
#define LRFDRFE32_DIV_DCO_RATIO_DIV30                               0x00070000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV15                               0x00060000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV10                               0x00050000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV5                                0x00040000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV12                               0x00030000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV6                                0x00020000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV4                                0x00010000U
#define LRFDRFE32_DIV_DCO_RATIO_DIV2                                0x00000000U

// Field:  [10:9] MTDCSPARE 
//
// ENUMs: 
// DIS                      DIVIDER = 4 (for test purposes only) 
// EN                       DIVIDER = 2 
#define LRFDRFE32_DIV_DCO_MTDCSPARE_W                                        2U
#define LRFDRFE32_DIV_DCO_MTDCSPARE_M                               0x00000600U
#define LRFDRFE32_DIV_DCO_MTDCSPARE_S                                        9U
#define LRFDRFE32_DIV_DCO_MTDCSPARE_DIS                             0x00000200U
#define LRFDRFE32_DIV_DCO_MTDCSPARE_EN                              0x00000000U

// Field:   [8:7] SPARE7 
//
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is zero 
#define LRFDRFE32_DIV_DCO_SPARE7_W                                           2U
#define LRFDRFE32_DIV_DCO_SPARE7_M                                  0x00000180U
#define LRFDRFE32_DIV_DCO_SPARE7_S                                           7U
#define LRFDRFE32_DIV_DCO_SPARE7_ONE                                0x00000080U
#define LRFDRFE32_DIV_DCO_SPARE7_ZERO                               0x00000000U

// Field:   [6:3] TAILRESTRIM 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DIV_DCO_TAILRESTRIM_W                                      4U
#define LRFDRFE32_DIV_DCO_TAILRESTRIM_M                             0x00000078U
#define LRFDRFE32_DIV_DCO_TAILRESTRIM_S                                      3U
#define LRFDRFE32_DIV_DCO_TAILRESTRIM_ALLONES                       0x00000078U
#define LRFDRFE32_DIV_DCO_TAILRESTRIM_ALLZEROS                      0x00000000U

// Field:     [2] RTRIMCAP 
//
// ENUMs: 
// EN                       Enable 
// DIS                      Disable(default) 
#define LRFDRFE32_DIV_DCO_RTRIMCAP                                  0x00000004U
#define LRFDRFE32_DIV_DCO_RTRIMCAP_M                                0x00000004U
#define LRFDRFE32_DIV_DCO_RTRIMCAP_S                                         2U
#define LRFDRFE32_DIV_DCO_RTRIMCAP_EN                               0x00000004U
#define LRFDRFE32_DIV_DCO_RTRIMCAP_DIS                              0x00000000U

// Field:     [1] CNRCAP 
//
// ENUMs: 
// _50MHZ                   50 MHz 
// DEFAULT                  Default 
#define LRFDRFE32_DIV_DCO_CNRCAP                                    0x00000002U
#define LRFDRFE32_DIV_DCO_CNRCAP_M                                  0x00000002U
#define LRFDRFE32_DIV_DCO_CNRCAP_S                                           1U
#define LRFDRFE32_DIV_DCO_CNRCAP__50MHZ                             0x00000002U
#define LRFDRFE32_DIV_DCO_CNRCAP_DEFAULT                            0x00000000U

// Field:     [0] CRSCAPCM 
//
// ENUMs: 
// REDUCED                  Reduced common mode for greater reliability 
// DEFAULT                  Default 
#define LRFDRFE32_DIV_DCO_CRSCAPCM                                  0x00000001U
#define LRFDRFE32_DIV_DCO_CRSCAPCM_M                                0x00000001U
#define LRFDRFE32_DIV_DCO_CRSCAPCM_S                                         0U
#define LRFDRFE32_DIV_DCO_CRSCAPCM_REDUCED                          0x00000001U
#define LRFDRFE32_DIV_DCO_CRSCAPCM_DEFAULT                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TDCLDO_DIVLDO
//
//*****************************************************************************
// Field:    [31] TDCLDO_ITESTCTL 
//
// ENUMs: 
// EN                       ITEST enabled 
// DIS                      ITEST Disabled 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTCTL                     0x80000000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTCTL_M                   0x80000000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTCTL_S                           31U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTCTL_EN                  0x80000000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTCTL_DIS                 0x00000000U

// Field: [30:24] TDCLDO_VOUTTRIM 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_VOUTTRIM_W                            7U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_VOUTTRIM_M                   0x7F000000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_VOUTTRIM_S                           24U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_VOUTTRIM_ONES                0x7F000000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_VOUTTRIM_ZEROS               0x00000000U

// Field:    [23] TDCLDO_ITESTBUFCTL 
//
// ENUMs: 
// EN                       ITEST mode in buffer is enabled 
// DIS                      ITEST mode in buffer is disabled 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTBUFCTL                  0x00800000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTBUFCTL_M                0x00800000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTBUFCTL_S                        23U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTBUFCTL_EN               0x00800000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_ITESTBUFCTL_DIS              0x00000000U

// Field: [22:20] TDCLDO_TMUX 
//
// ENUMs: 
// VSSA                     ATEST output is VSSA 
// LDO_OUT                  ATEST output is LDO output 
// VDDA                     ATEST output is VDDA 
// OFF                      Normal mode 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_W                                3U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_M                       0x00700000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_S                               20U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_VSSA                    0x00400000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_LDO_OUT                 0x00200000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_VDDA                    0x00100000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_TMUX_OFF                     0x00000000U

// Field:    [19] TDCLDO_PDSEL 
//
// ENUMs: 
// DIODE                    Diode stack 
// R                        R (default) 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_PDSEL                        0x00080000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_PDSEL_M                      0x00080000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_PDSEL_S                              19U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_PDSEL_DIODE                  0x00080000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_PDSEL_R                      0x00000000U

// Field:    [18] TDCLDO_MODE 
//
// ENUMs: 
// FAST                     Regulator in high bandwidth mode 
// NORM                     Regular low bandwidth of LDO 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_MODE                         0x00040000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_MODE_M                       0x00040000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_MODE_S                               18U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_MODE_FAST                    0x00040000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_MODE_NORM                    0x00000000U

// Field:    [17] TDCLDO_BYPASS 
//
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_BYPASS                       0x00020000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_BYPASS_M                     0x00020000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_BYPASS_S                             17U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_BYPASS_EN                    0x00020000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_BYPASS_DIS                   0x00000000U

// Field:    [16] TDCLDO_CTL 
//
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_CTL                          0x00010000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_CTL_M                        0x00010000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_CTL_S                                16U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_CTL_EN                       0x00010000U
#define LRFDRFE32_TDCLDO_DIVLDO_TDCLDO_CTL_DIS                      0x00000000U

// Field:    [15] DIVLDO_SPARE15 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE15                      0x00008000U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE15_M                    0x00008000U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE15_S                            15U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE15_ONES                 0x00008000U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE15_ZEROS                0x00000000U

// Field:  [14:8] DIVLDO_VOUTTRIM 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_VOUTTRIM_W                            7U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_VOUTTRIM_M                   0x00007F00U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_VOUTTRIM_S                            8U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_VOUTTRIM_ONES                0x00007F00U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_VOUTTRIM_ZEROS               0x00000000U

// Field:     [7] DIVLDO_ITST 
//
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_ITST                         0x00000080U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_ITST_M                       0x00000080U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_ITST_S                                7U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_ITST_EN                      0x00000080U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_ITST_DIS                     0x00000000U

// Field:   [6:4] DIVLDO_TMUX 
//
// ENUMs: 
// VDDR                     ATEST output is VDDR 
// LDO_OUT                  ATEST output is LDO output 
// GND                      ATEST output is grounded 
// OFF                      Normal mode 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_W                                3U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_M                       0x00000070U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_S                                4U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_VDDR                    0x00000040U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_LDO_OUT                 0x00000020U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_GND                     0x00000010U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_TMUX_OFF                     0x00000000U

// Field:     [3] DIVLDO_SPARE3 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE3                       0x00000008U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE3_M                     0x00000008U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE3_S                              3U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE3_ONE                   0x00000008U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_SPARE3_ZERO                  0x00000000U

// Field:     [2] DIVLDO_MODE 
//
// ENUMs: 
// FAST                     Regulator in high bandwidth mode 
// NORM                     Regular low bandwidth of LDO 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_MODE                         0x00000004U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_MODE_M                       0x00000004U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_MODE_S                                2U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_MODE_FAST                    0x00000004U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_MODE_NORM                    0x00000000U

// Field:     [1] DIVLDO_BYPASS 
//
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_BYPASS                       0x00000002U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_BYPASS_M                     0x00000002U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_BYPASS_S                              1U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_BYPASS_EN                    0x00000002U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_BYPASS_DIS                   0x00000000U

// Field:     [0] DIVLDO_CTL 
//
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_CTL                          0x00000001U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_CTL_M                        0x00000001U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_CTL_S                                 0U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_CTL_EN                       0x00000001U
#define LRFDRFE32_TDCLDO_DIVLDO_DIVLDO_CTL_DIS                      0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DCOLDO1_DCOLDO0
//
//*****************************************************************************
// Field:    [26] REFSRC 
//
// ENUMs: 
// BAW                      PLL clock source is BAW 
// XTAL                     PLL clock source is XTAL 
#define LRFDRFE32_DCOLDO1_DCOLDO0_REFSRC                            0x04000000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_REFSRC_M                          0x04000000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_REFSRC_S                                  26U
#define LRFDRFE32_DCOLDO1_DCOLDO0_REFSRC_BAW                        0x04000000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_REFSRC_XTAL                       0x00000000U

// Field: [25:24] DIVATST 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_DCOLDO1_DCOLDO0_DIVATST_W                                  2U
#define LRFDRFE32_DCOLDO1_DCOLDO0_DIVATST_M                         0x03000000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_DIVATST_S                                 24U
#define LRFDRFE32_DCOLDO1_DCOLDO0_DIVATST_ONES                      0x03000000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_DIVATST_ZEROS                     0x00000000U

// Field:    [23] PERFM 
//
// ENUMs: 
// EN                       Enabled (performance) 
// DIS                      Disabled (normal) 
#define LRFDRFE32_DCOLDO1_DCOLDO0_PERFM                             0x00800000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PERFM_M                           0x00800000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PERFM_S                                   23U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PERFM_EN                          0x00800000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PERFM_DIS                         0x00000000U

// Field:    [22] CHRGFILT 
//
// ENUMs: 
// EN                       Charging enabled 
// DIS                      Charging disabled, normal operation 
#define LRFDRFE32_DCOLDO1_DCOLDO0_CHRGFILT                          0x00400000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CHRGFILT_M                        0x00400000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CHRGFILT_S                                22U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CHRGFILT_EN                       0x00400000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CHRGFILT_DIS                      0x00000000U

// Field: [21:16] ATST 
//
// ENUMs: 
// VSSANA                   VSSANA 
// FIRST_OUT                First LDO output 
// LDO_OUT                  LDO output 
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_W                                     6U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_M                            0x003F0000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_S                                    16U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_VSSANA                       0x00200000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_FIRST_OUT                    0x00010000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ATST_LDO_OUT                      0x00000000U

// Field: [15:14] ITST 
//
// ENUMs: 
// BOTH                     Enable both pass transistors 
// SECOND                   Enable second pass transistor 
// FIRST                    Enable first pass transistor 
// DIS                      Regulator is disabled 
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_W                                     2U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_M                            0x0000C000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_S                                    14U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_BOTH                         0x0000C000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_SECOND                       0x00008000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_FIRST                        0x00004000U
#define LRFDRFE32_DCOLDO1_DCOLDO0_ITST_DIS                          0x00000000U

// Field:  [13:8] SECONDTRIM 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_DCOLDO1_DCOLDO0_SECONDTRIM_W                               6U
#define LRFDRFE32_DCOLDO1_DCOLDO0_SECONDTRIM_M                      0x00003F00U
#define LRFDRFE32_DCOLDO1_DCOLDO0_SECONDTRIM_S                               8U
#define LRFDRFE32_DCOLDO1_DCOLDO0_SECONDTRIM_ONES                   0x00003F00U
#define LRFDRFE32_DCOLDO1_DCOLDO0_SECONDTRIM_ZEROS                  0x00000000U

// Field:   [7:4] FIRSTTRIM 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_DCOLDO1_DCOLDO0_FIRSTTRIM_W                                4U
#define LRFDRFE32_DCOLDO1_DCOLDO0_FIRSTTRIM_M                       0x000000F0U
#define LRFDRFE32_DCOLDO1_DCOLDO0_FIRSTTRIM_S                                4U
#define LRFDRFE32_DCOLDO1_DCOLDO0_FIRSTTRIM_ONES                    0x000000F0U
#define LRFDRFE32_DCOLDO1_DCOLDO0_FIRSTTRIM_ZEROS                   0x00000000U

// Field:     [3] PDN 
//
// ENUMs: 
// EN                       Pulldown 
// DIS                      No Pulldown 
#define LRFDRFE32_DCOLDO1_DCOLDO0_PDN                               0x00000008U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PDN_M                             0x00000008U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PDN_S                                      3U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PDN_EN                            0x00000008U
#define LRFDRFE32_DCOLDO1_DCOLDO0_PDN_DIS                           0x00000000U

// Field:     [2] BYPFIRST 
//
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPFIRST                          0x00000004U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPFIRST_M                        0x00000004U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPFIRST_S                                 2U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPFIRST_EN                       0x00000004U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPFIRST_DIS                      0x00000000U

// Field:     [1] BYPBOTH 
//
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPBOTH                           0x00000002U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPBOTH_M                         0x00000002U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPBOTH_S                                  1U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPBOTH_EN                        0x00000002U
#define LRFDRFE32_DCOLDO1_DCOLDO0_BYPBOTH_DIS                       0x00000000U

// Field:     [0] CTL 
//
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
#define LRFDRFE32_DCOLDO1_DCOLDO0_CTL                               0x00000001U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CTL_M                             0x00000001U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CTL_S                                      0U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CTL_EN                            0x00000001U
#define LRFDRFE32_DCOLDO1_DCOLDO0_CTL_DIS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PRE1_PRE0
//
//*****************************************************************************
// Field: [31:30] IIRBW 
//
// ENUMs: 
// K16                      K=16 
// K8 
// K4 
// K2 
#define LRFDRFE32_PRE1_PRE0_IIRBW_W                                          2U
#define LRFDRFE32_PRE1_PRE0_IIRBW_M                                 0xC0000000U
#define LRFDRFE32_PRE1_PRE0_IIRBW_S                                         30U
#define LRFDRFE32_PRE1_PRE0_IIRBW_K16                               0xC0000000U
#define LRFDRFE32_PRE1_PRE0_IIRBW_K8                                0x80000000U
#define LRFDRFE32_PRE1_PRE0_IIRBW_K4                                0x40000000U
#define LRFDRFE32_PRE1_PRE0_IIRBW_K2                                0x00000000U

// Field:    [29] IIRORD 
//
// ENUMs: 
// SECOND                   Select second order IIR filter 
// FIRST                    Select first order IIR filter 
#define LRFDRFE32_PRE1_PRE0_IIRORD                                  0x20000000U
#define LRFDRFE32_PRE1_PRE0_IIRORD_M                                0x20000000U
#define LRFDRFE32_PRE1_PRE0_IIRORD_S                                        29U
#define LRFDRFE32_PRE1_PRE0_IIRORD_SECOND                           0x20000000U
#define LRFDRFE32_PRE1_PRE0_IIRORD_FIRST                            0x00000000U

// Field: [28:24] IIRDIV 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_IIRDIV_W                                         5U
#define LRFDRFE32_PRE1_PRE0_IIRDIV_M                                0x1F000000U
#define LRFDRFE32_PRE1_PRE0_IIRDIV_S                                        24U
#define LRFDRFE32_PRE1_PRE0_IIRDIV_ALLONES                          0x1F000000U
#define LRFDRFE32_PRE1_PRE0_IIRDIV_ALLZEROS                         0x00000000U

// Field:    [22] CALHSDDC 
//
// ENUMs: 
// GATE                     Duty-cycling given by HSDDC 
// NOGATE                   No duty-cycling 
#define LRFDRFE32_PRE1_PRE0_CALHSDDC                                0x00400000U
#define LRFDRFE32_PRE1_PRE0_CALHSDDC_M                              0x00400000U
#define LRFDRFE32_PRE1_PRE0_CALHSDDC_S                                      22U
#define LRFDRFE32_PRE1_PRE0_CALHSDDC_GATE                           0x00400000U
#define LRFDRFE32_PRE1_PRE0_CALHSDDC_NOGATE                         0x00000000U

// Field: [21:16] HSDDC 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_HSDDC_W                                          6U
#define LRFDRFE32_PRE1_PRE0_HSDDC_M                                 0x003F0000U
#define LRFDRFE32_PRE1_PRE0_HSDDC_S                                         16U
#define LRFDRFE32_PRE1_PRE0_HSDDC_ALLONES                           0x003F0000U
#define LRFDRFE32_PRE1_PRE0_HSDDC_ALLZEROS                          0x00000000U

// Field: [15:14] SPARE14 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_SPARE14_W                                        2U
#define LRFDRFE32_PRE1_PRE0_SPARE14_M                               0x0000C000U
#define LRFDRFE32_PRE1_PRE0_SPARE14_S                                       14U
#define LRFDRFE32_PRE1_PRE0_SPARE14_ALLONES                         0x0000C000U
#define LRFDRFE32_PRE1_PRE0_SPARE14_ALLZEROS                        0x00000000U

// Field:  [13:8] PLLDIV1 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_PLLDIV1_W                                        6U
#define LRFDRFE32_PRE1_PRE0_PLLDIV1_M                               0x00003F00U
#define LRFDRFE32_PRE1_PRE0_PLLDIV1_S                                        8U
#define LRFDRFE32_PRE1_PRE0_PLLDIV1_ALLONES                         0x00003F00U
#define LRFDRFE32_PRE1_PRE0_PLLDIV1_ALLZEROS                        0x00000000U

// Field:   [7:6] SPARE6 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_SPARE6_W                                         2U
#define LRFDRFE32_PRE1_PRE0_SPARE6_M                                0x000000C0U
#define LRFDRFE32_PRE1_PRE0_SPARE6_S                                         6U
#define LRFDRFE32_PRE1_PRE0_SPARE6_ALLONES                          0x000000C0U
#define LRFDRFE32_PRE1_PRE0_SPARE6_ALLZEROS                         0x00000000U

// Field:   [5:0] PLLDIV0 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE1_PRE0_PLLDIV0_W                                        6U
#define LRFDRFE32_PRE1_PRE0_PLLDIV0_M                               0x0000003FU
#define LRFDRFE32_PRE1_PRE0_PLLDIV0_S                                        0U
#define LRFDRFE32_PRE1_PRE0_PLLDIV0_ALLONES                         0x0000003FU
#define LRFDRFE32_PRE1_PRE0_PLLDIV0_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PRE3_PRE2
//
//*****************************************************************************
// Field: [31:21] FINECALDIV 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE3_PRE2_FINECALDIV_W                                    11U
#define LRFDRFE32_PRE3_PRE2_FINECALDIV_M                            0xFFE00000U
#define LRFDRFE32_PRE3_PRE2_FINECALDIV_S                                    21U
#define LRFDRFE32_PRE3_PRE2_FINECALDIV_ALLONES                      0xFFE00000U
#define LRFDRFE32_PRE3_PRE2_FINECALDIV_ALLZEROS                     0x00000000U

// Field: [20:16] MIDCALDIVMSB 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_W                                   5U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_M                          0x001F0000U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_S                                  16U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_ALLONES                    0x001F0000U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVMSB_ALLZEROS                   0x00000000U

// Field: [15:12] MIDCALDIVLSB 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_W                                   4U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_M                          0x0000F000U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_S                                  12U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_ALLONES                    0x0000F000U
#define LRFDRFE32_PRE3_PRE2_MIDCALDIVLSB_ALLZEROS                   0x00000000U

// Field:  [11:6] CRSCALDIV 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE3_PRE2_CRSCALDIV_W                                      6U
#define LRFDRFE32_PRE3_PRE2_CRSCALDIV_M                             0x00000FC0U
#define LRFDRFE32_PRE3_PRE2_CRSCALDIV_S                                      6U
#define LRFDRFE32_PRE3_PRE2_CRSCALDIV_ALLONES                       0x00000FC0U
#define LRFDRFE32_PRE3_PRE2_CRSCALDIV_ALLZEROS                      0x00000000U

// Field:   [5:0] FSMDIV 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRE3_PRE2_FSMDIV_W                                         6U
#define LRFDRFE32_PRE3_PRE2_FSMDIV_M                                0x0000003FU
#define LRFDRFE32_PRE3_PRE2_FSMDIV_S                                         0U
#define LRFDRFE32_PRE3_PRE2_FSMDIV_ALLONES                          0x0000003FU
#define LRFDRFE32_PRE3_PRE2_FSMDIV_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_CAL1_CAL0
//
//*****************************************************************************
// Field:    [31] CAL1_SPARE15 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE15                            0x80000000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE15_M                          0x80000000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE15_S                                  31U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE15_ONE                        0x80000000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE15_ZERO                       0x00000000U

// Field: [30:24] CAL1_FCTOP 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL1_CAL0_CAL1_FCTOP_W                                     7U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCTOP_M                            0x7F000000U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCTOP_S                                    24U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCTOP_ALLONES                      0x7F000000U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCTOP_ALLZEROS                     0x00000000U

// Field:    [23] CAL1_SPARE7 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE7                             0x00800000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE7_M                           0x00800000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE7_S                                   23U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE7_ONE                         0x00800000U
#define LRFDRFE32_CAL1_CAL0_CAL1_SPARE7_ZERO                        0x00000000U

// Field: [22:16] CAL1_FCBOT 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL1_CAL0_CAL1_FCBOT_W                                     7U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCBOT_M                            0x007F0000U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCBOT_S                                    16U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCBOT_ALLONES                      0x007F0000U
#define LRFDRFE32_CAL1_CAL0_CAL1_FCBOT_ALLZEROS                     0x00000000U

// Field:    [15] CAL0_SPARE15 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_CAL1_CAL0_CAL0_SPARE15                            0x00008000U
#define LRFDRFE32_CAL1_CAL0_CAL0_SPARE15_M                          0x00008000U
#define LRFDRFE32_CAL1_CAL0_CAL0_SPARE15_S                                  15U
#define LRFDRFE32_CAL1_CAL0_CAL0_SPARE15_ONE                        0x00008000U
#define LRFDRFE32_CAL1_CAL0_CAL0_SPARE15_ZERO                       0x00000000U

// Field:  [14:8] CAL0_FCSTART 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL1_CAL0_CAL0_FCSTART_W                                   7U
#define LRFDRFE32_CAL1_CAL0_CAL0_FCSTART_M                          0x00007F00U
#define LRFDRFE32_CAL1_CAL0_CAL0_FCSTART_S                                   8U
#define LRFDRFE32_CAL1_CAL0_CAL0_FCSTART_ALLONES                    0x00007F00U
#define LRFDRFE32_CAL1_CAL0_CAL0_FCSTART_ALLZEROS                   0x00000000U

// Field:     [7] CAL0_CRS 
//
// ENUMs: 
// EN                       Enable coarse calibration 
// DIS                      Disable coarse calibration 
#define LRFDRFE32_CAL1_CAL0_CAL0_CRS                                0x00000080U
#define LRFDRFE32_CAL1_CAL0_CAL0_CRS_M                              0x00000080U
#define LRFDRFE32_CAL1_CAL0_CAL0_CRS_S                                       7U
#define LRFDRFE32_CAL1_CAL0_CAL0_CRS_EN                             0x00000080U
#define LRFDRFE32_CAL1_CAL0_CAL0_CRS_DIS                            0x00000000U

// Field:     [6] CAL0_MID 
//
// ENUMs: 
// EN                       Enable mid calibration 
// DIS                      Disable mid calibration 
#define LRFDRFE32_CAL1_CAL0_CAL0_MID                                0x00000040U
#define LRFDRFE32_CAL1_CAL0_CAL0_MID_M                              0x00000040U
#define LRFDRFE32_CAL1_CAL0_CAL0_MID_S                                       6U
#define LRFDRFE32_CAL1_CAL0_CAL0_MID_EN                             0x00000040U
#define LRFDRFE32_CAL1_CAL0_CAL0_MID_DIS                            0x00000000U

// Field:     [5] CAL0_KTDC 
//
// ENUMs: 
// EN                       Enable TDC estimation 
// DIS                      Disable TDC estimation 
#define LRFDRFE32_CAL1_CAL0_CAL0_KTDC                               0x00000020U
#define LRFDRFE32_CAL1_CAL0_CAL0_KTDC_M                             0x00000020U
#define LRFDRFE32_CAL1_CAL0_CAL0_KTDC_S                                      5U
#define LRFDRFE32_CAL1_CAL0_CAL0_KTDC_EN                            0x00000020U
#define LRFDRFE32_CAL1_CAL0_CAL0_KTDC_DIS                           0x00000000U

// Field:     [4] CAL0_KDCO 
//
// ENUMs: 
// EN                       Enable KDCO estimation 
// DIS                      Disable KDCO estimation 
#define LRFDRFE32_CAL1_CAL0_CAL0_KDCO                               0x00000010U
#define LRFDRFE32_CAL1_CAL0_CAL0_KDCO_M                             0x00000010U
#define LRFDRFE32_CAL1_CAL0_CAL0_KDCO_S                                      4U
#define LRFDRFE32_CAL1_CAL0_CAL0_KDCO_EN                            0x00000010U
#define LRFDRFE32_CAL1_CAL0_CAL0_KDCO_DIS                           0x00000000U

// Field:   [3:2] CAL0_TDCAVG 
//
// ENUMs: 
// REPEAT_8_TIMES           Repeat measurement 8 times 
// REPEAT_4_TIMES           Repeat measurement 4 times 
// REPEAT_2_TIMES           Repeat measurement 2 times 
// REPEAT_1_TIME            Repeat measurement 1 time 
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_W                                    2U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_M                           0x0000000CU
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_S                                    2U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_REPEAT_8_TIMES              0x0000000CU
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_REPEAT_4_TIMES              0x00000008U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_REPEAT_2_TIMES              0x00000004U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDCAVG_REPEAT_1_TIME               0x00000000U

// Field:   [1:0] CAL0_TDC_SPARE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL1_CAL0_CAL0_TDC_SPARE_W                                 2U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDC_SPARE_M                        0x00000003U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDC_SPARE_S                                 0U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDC_SPARE_ALLONES                  0x00000003U
#define LRFDRFE32_CAL1_CAL0_CAL0_TDC_SPARE_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_CAL3_CAL2
//
//*****************************************************************************
// Field: [31:16] DTXGAIN 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL3_CAL2_DTXGAIN_W                                       16U
#define LRFDRFE32_CAL3_CAL2_DTXGAIN_M                               0xFFFF0000U
#define LRFDRFE32_CAL3_CAL2_DTXGAIN_S                                       16U
#define LRFDRFE32_CAL3_CAL2_DTXGAIN_ALLONES                         0xFFFF0000U
#define LRFDRFE32_CAL3_CAL2_DTXGAIN_ALLZEROS                        0x00000000U

// Field:  [15:0] KTDCINV 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CAL3_CAL2_KTDCINV_W                                       16U
#define LRFDRFE32_CAL3_CAL2_KTDCINV_M                               0x0000FFFFU
#define LRFDRFE32_CAL3_CAL2_KTDCINV_S                                        0U
#define LRFDRFE32_CAL3_CAL2_KTDCINV_ALLONES                         0x0000FFFFU
#define LRFDRFE32_CAL3_CAL2_KTDCINV_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MISC1_MISC0
//
//*****************************************************************************
// Field:    [30] FCDEMCLK 
//
// ENUMs: 
// CKVD64                   ckvd64 clock used for update upper and lower DWA 
//                          DEM 
// CKCD16                   ckvd16 clock used for update upper and lower DWA 
//                          DEM 
#define LRFDRFE32_MISC1_MISC0_FCDEMCLK                              0x40000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMCLK_M                            0x40000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMCLK_S                                    30U
#define LRFDRFE32_MISC1_MISC0_FCDEMCLK_CKVD64                       0x40000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMCLK_CKCD16                       0x00000000U

// Field: [29:28] FCDEMUPD 
//
// ENUMs: 
// SDM_XOR_PH_ERR           phase_error[0] xor SDM[1] 
// SDM                      SDM[1] (this value depends on DEM for SDM) 
// PH_ERR                   phase_error[0]. (Phase error is 6.11s ) 
// DEFAULT                  Default: Update both DWAs always at rising edge of 
//                          selected clock 
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_W                                     2U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_M                            0x30000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_S                                    28U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_SDM_XOR_PH_ERR               0x30000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_SDM                          0x20000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_PH_ERR                       0x10000000U
#define LRFDRFE32_MISC1_MISC0_FCDEMUPD_DEFAULT                      0x00000000U

// Field: [27:22] TDCINL 
//
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE32_MISC1_MISC0_TDCINL_W                                       6U
#define LRFDRFE32_MISC1_MISC0_TDCINL_M                              0x0FC00000U
#define LRFDRFE32_MISC1_MISC0_TDCINL_S                                      22U
#define LRFDRFE32_MISC1_MISC0_TDCINL_ONES                           0x0FC00000U
#define LRFDRFE32_MISC1_MISC0_TDCINL_ZEROS                          0x00000000U

// Field:    [21] TDCINLCTL 
//
// ENUMs: 
// EN                       Enables INL correction of TDC 
// DIS                      Disabled INL correction 
#define LRFDRFE32_MISC1_MISC0_TDCINLCTL                             0x00200000U
#define LRFDRFE32_MISC1_MISC0_TDCINLCTL_M                           0x00200000U
#define LRFDRFE32_MISC1_MISC0_TDCINLCTL_S                                   21U
#define LRFDRFE32_MISC1_MISC0_TDCINLCTL_EN                          0x00200000U
#define LRFDRFE32_MISC1_MISC0_TDCINLCTL_DIS                         0x00000000U

// Field:    [20] PHINIT 
//
// ENUMs: 
// UNKNOWN                  Unknown phase 
// KNOWN                    Known phase 
#define LRFDRFE32_MISC1_MISC0_PHINIT                                0x00100000U
#define LRFDRFE32_MISC1_MISC0_PHINIT_M                              0x00100000U
#define LRFDRFE32_MISC1_MISC0_PHINIT_S                                      20U
#define LRFDRFE32_MISC1_MISC0_PHINIT_UNKNOWN                        0x00100000U
#define LRFDRFE32_MISC1_MISC0_PHINIT_KNOWN                          0x00000000U

// Field:    [19] SDMOOVRCTL 
//
// ENUMs: 
// EN                       Enable SDM output override 
// DIS                      Disable SDM output override 
#define LRFDRFE32_MISC1_MISC0_SDMOOVRCTL                            0x00080000U
#define LRFDRFE32_MISC1_MISC0_SDMOOVRCTL_M                          0x00080000U
#define LRFDRFE32_MISC1_MISC0_SDMOOVRCTL_S                                  19U
#define LRFDRFE32_MISC1_MISC0_SDMOOVRCTL_EN                         0x00080000U
#define LRFDRFE32_MISC1_MISC0_SDMOOVRCTL_DIS                        0x00000000U

// Field: [18:16] SDMOOVR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MISC1_MISC0_SDMOOVR_W                                      3U
#define LRFDRFE32_MISC1_MISC0_SDMOOVR_M                             0x00070000U
#define LRFDRFE32_MISC1_MISC0_SDMOOVR_S                                     16U
#define LRFDRFE32_MISC1_MISC0_SDMOOVR_ALLONES                       0x00070000U
#define LRFDRFE32_MISC1_MISC0_SDMOOVR_ALLZEROS                      0x00000000U

// Field:    [13] PHCPT 
//
// ENUMs: 
// ASYNC                    Phase capture mode is asyncrhonous 
// SYNC                     Phase capture mode is synchronous 
#define LRFDRFE32_MISC1_MISC0_PHCPT                                 0x00002000U
#define LRFDRFE32_MISC1_MISC0_PHCPT_M                               0x00002000U
#define LRFDRFE32_MISC1_MISC0_PHCPT_S                                       13U
#define LRFDRFE32_MISC1_MISC0_PHCPT_ASYNC                           0x00002000U
#define LRFDRFE32_MISC1_MISC0_PHCPT_SYNC                            0x00000000U

// Field:    [12] TDCCALCORR 
//
// ENUMs: 
// EN                       Enable TDC error correction inside DLO. 
// DIS                      Disable TDC error correction inside DLO. 
#define LRFDRFE32_MISC1_MISC0_TDCCALCORR                            0x00001000U
#define LRFDRFE32_MISC1_MISC0_TDCCALCORR_M                          0x00001000U
#define LRFDRFE32_MISC1_MISC0_TDCCALCORR_S                                  12U
#define LRFDRFE32_MISC1_MISC0_TDCCALCORR_EN                         0x00001000U
#define LRFDRFE32_MISC1_MISC0_TDCCALCORR_DIS                        0x00000000U

// Field:    [11] TDCMSBCORR 
//
// ENUMs: 
// EN                       Enable TDC error correction inside DLO. 
// DIS                      Disable TDC error correction inside DLO. 
#define LRFDRFE32_MISC1_MISC0_TDCMSBCORR                            0x00000800U
#define LRFDRFE32_MISC1_MISC0_TDCMSBCORR_M                          0x00000800U
#define LRFDRFE32_MISC1_MISC0_TDCMSBCORR_S                                  11U
#define LRFDRFE32_MISC1_MISC0_TDCMSBCORR_EN                         0x00000800U
#define LRFDRFE32_MISC1_MISC0_TDCMSBCORR_DIS                        0x00000000U

// Field:    [10] SDMDEM 
//
// ENUMs: 
// EN                       Enable dynamic element matching (recommended) 
// DIS                      Disable dynamic element matching 
#define LRFDRFE32_MISC1_MISC0_SDMDEM                                0x00000400U
#define LRFDRFE32_MISC1_MISC0_SDMDEM_M                              0x00000400U
#define LRFDRFE32_MISC1_MISC0_SDMDEM_S                                      10U
#define LRFDRFE32_MISC1_MISC0_SDMDEM_EN                             0x00000400U
#define LRFDRFE32_MISC1_MISC0_SDMDEM_DIS                            0x00000000U

// Field:   [9:8] DLYSDM 
//
// ENUMs: 
// CKVD16_3_PER             Delay integer fine code by 3 CKVD16 clock periods 
// CKVD16_2_PER             Delay integer fine code by 2 CKVD16 clock periods 
// CKVD16_1_PER             Delay integer fine code by 1 CKVD16 clock period 
// CKVD16_0_PER             Delay integer fine code by 0 CKVD16 clock periods 
#define LRFDRFE32_MISC1_MISC0_DLYSDM_W                                       2U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_M                              0x00000300U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_S                                       8U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_CKVD16_3_PER                   0x00000300U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_CKVD16_2_PER                   0x00000200U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_CKVD16_1_PER                   0x00000100U
#define LRFDRFE32_MISC1_MISC0_DLYSDM_CKVD16_0_PER                   0x00000000U

// Field:     [6] DLYPHVALID 
//
// ENUMs: 
// CKVD16_1_PER             Delays the variable phase capture and hence the 
//                          phase error calculation with 1 CKVD16 clock 
//                          period. 
// CKVD16_0_PER             No additional delay on variable phase capture. 
#define LRFDRFE32_MISC1_MISC0_DLYPHVALID                            0x00000040U
#define LRFDRFE32_MISC1_MISC0_DLYPHVALID_M                          0x00000040U
#define LRFDRFE32_MISC1_MISC0_DLYPHVALID_S                                   6U
#define LRFDRFE32_MISC1_MISC0_DLYPHVALID_CKVD16_1_PER               0x00000040U
#define LRFDRFE32_MISC1_MISC0_DLYPHVALID_CKVD16_0_PER               0x00000000U

// Field:   [5:4] DLYCANCRS 
//
// ENUMs: 
// CKVD64_3_PER             Delay by 3 CKVD64 clock periods 
// CKVD64_2_PER             Delay by 2 CKVD64 clock periods 
// CKVD64_1_PER             Delay by 1 CKVD64 clock period 
// CKVD64_0_PER             Delay by 0 CKVD64 clock periods 
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_W                                    2U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_M                           0x00000030U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_S                                    4U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_CKVD64_3_PER                0x00000030U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_CKVD64_2_PER                0x00000020U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_CKVD64_1_PER                0x00000010U
#define LRFDRFE32_MISC1_MISC0_DLYCANCRS_CKVD64_0_PER                0x00000000U

// Field:   [3:2] DLYCANFINE 
//
// ENUMs: 
// CKVD16_4_PER             Delay by 4 CKVD16 clock periods 
// CKVD16_3_PER             Delay by 3 CKVD16 clock periods 
// CKVD16_2_PER             Delay by 2 CKVD16 clock period 
// CKVD16_1_PER             Delay by 1 CKVD16 clock periods 
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_W                                   2U
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_M                          0x0000000CU
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_S                                   2U
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_CKVD16_4_PER               0x0000000CU
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_CKVD16_3_PER               0x00000008U
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_CKVD16_2_PER               0x00000004U
#define LRFDRFE32_MISC1_MISC0_DLYCANFINE_CKVD16_1_PER               0x00000000U

// Field:   [1:0] DLYADD 
//
// ENUMs: 
// CKVD64_3_PER             Delay by 3 CKVD64 clock periods 
// CKVD64_2_PER             Delay by 2 CKVD64 clock periods 
// CKVD64_1_PER             Delay by 1 CKVD64 clock period 
// CKVD64_0_PER             Delay by 0 CKVD64 clock periods 
#define LRFDRFE32_MISC1_MISC0_DLYADD_W                                       2U
#define LRFDRFE32_MISC1_MISC0_DLYADD_M                              0x00000003U
#define LRFDRFE32_MISC1_MISC0_DLYADD_S                                       0U
#define LRFDRFE32_MISC1_MISC0_DLYADD_CKVD64_3_PER                   0x00000003U
#define LRFDRFE32_MISC1_MISC0_DLYADD_CKVD64_2_PER                   0x00000002U
#define LRFDRFE32_MISC1_MISC0_DLYADD_CKVD64_1_PER                   0x00000001U
#define LRFDRFE32_MISC1_MISC0_DLYADD_CKVD64_0_PER                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_LF1_LF0
//
//*****************************************************************************
// Field: [29:16] KP 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_LF1_LF0_KP_W                                              14U
#define LRFDRFE32_LF1_LF0_KP_M                                      0x3FFF0000U
#define LRFDRFE32_LF1_LF0_KP_S                                              16U
#define LRFDRFE32_LF1_LF0_KP_ALLONES                                0x3FFF0000U
#define LRFDRFE32_LF1_LF0_KP_ALLZEROS                               0x00000000U

// Field:    [12] KIPREC 
//
// ENUMs: 
// HIGH                     KI encoding is <4.08> 
// LOW                      KI encoding is <12.0u> 
#define LRFDRFE32_LF1_LF0_KIPREC                                    0x00001000U
#define LRFDRFE32_LF1_LF0_KIPREC_M                                  0x00001000U
#define LRFDRFE32_LF1_LF0_KIPREC_S                                          12U
#define LRFDRFE32_LF1_LF0_KIPREC_HIGH                               0x00001000U
#define LRFDRFE32_LF1_LF0_KIPREC_LOW                                0x00000000U

// Field:  [11:0] KI 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_LF1_LF0_KI_W                                              12U
#define LRFDRFE32_LF1_LF0_KI_M                                      0x00000FFFU
#define LRFDRFE32_LF1_LF0_KI_S                                               0U
#define LRFDRFE32_LF1_LF0_KI_ALLONES                                0x00000FFFU
#define LRFDRFE32_LF1_LF0_KI_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PHINIT_PHEDISC
//
//*****************************************************************************
// Field: [23:16] OFF 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PHINIT_PHEDISC_OFF_W                                       8U
#define LRFDRFE32_PHINIT_PHEDISC_OFF_M                              0x00FF0000U
#define LRFDRFE32_PHINIT_PHEDISC_OFF_S                                      16U
#define LRFDRFE32_PHINIT_PHEDISC_OFF_ALLONES                        0x00FF0000U
#define LRFDRFE32_PHINIT_PHEDISC_OFF_ALLZEROS                       0x00000000U

// Field: [13:10] CNT 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PHINIT_PHEDISC_CNT_W                                       4U
#define LRFDRFE32_PHINIT_PHEDISC_CNT_M                              0x00003C00U
#define LRFDRFE32_PHINIT_PHEDISC_CNT_S                                      10U
#define LRFDRFE32_PHINIT_PHEDISC_CNT_ALLONES                        0x00003C00U
#define LRFDRFE32_PHINIT_PHEDISC_CNT_ALLZEROS                       0x00000000U

// Field:   [9:0] THR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PHINIT_PHEDISC_THR_W                                      10U
#define LRFDRFE32_PHINIT_PHEDISC_THR_M                              0x000003FFU
#define LRFDRFE32_PHINIT_PHEDISC_THR_S                                       0U
#define LRFDRFE32_PHINIT_PHEDISC_THR_ALLONES                        0x000003FFU
#define LRFDRFE32_PHINIT_PHEDISC_THR_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PLLMON1_PLLMON0
//
//*****************************************************************************
// Field: [28:24] PHELOCKCNT 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKCNT_W                               5U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKCNT_M                      0x1F000000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKCNT_S                              24U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKCNT_ALLONES                0x1F000000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKCNT_ALLZEROS               0x00000000U

// Field: [23:16] PHELOCKTHR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKTHR_W                               8U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKTHR_M                      0x00FF0000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKTHR_S                              16U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKTHR_ALLONES                0x00FF0000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOCKTHR_ALLZEROS               0x00000000U

// Field: [15:14] PHELOLCNT 
//
// ENUMs: 
// REFCLK_128_PER           Threshold count is 128 REFCLK periods 
// REFCLK_64_PER            Threshold count is 64 REFCLK periods 
// REFCLK_32_PER            Threshold count is 32 REFCLK periods 
// REFCLK_16_PER            Threshold count is 16 REFCLK periods 
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_W                                2U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_M                       0x0000C000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_S                               14U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_REFCLK_128_PER          0x0000C000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_REFCLK_64_PER           0x00008000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_REFCLK_32_PER           0x00004000U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLCNT_REFCLK_16_PER           0x00000000U

// Field:  [13:8] PHELOLTHR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLTHR_W                                6U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLTHR_M                       0x00003F00U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLTHR_S                                8U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLTHR_ALLONES                 0x00003F00U
#define LRFDRFE32_PLLMON1_PLLMON0_PHELOLTHR_ALLZEROS                0x00000000U

// Field:   [6:0] FCTHR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLMON1_PLLMON0_FCTHR_W                                    7U
#define LRFDRFE32_PLLMON1_PLLMON0_FCTHR_M                           0x0000007FU
#define LRFDRFE32_PLLMON1_PLLMON0_FCTHR_S                                    0U
#define LRFDRFE32_PLLMON1_PLLMON0_FCTHR_ALLONES                     0x0000007FU
#define LRFDRFE32_PLLMON1_PLLMON0_FCTHR_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MOD1_MOD0
//
//*****************************************************************************
// Field: [27:16] FOFF 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MOD1_MOD0_FOFF_W                                          12U
#define LRFDRFE32_MOD1_MOD0_FOFF_M                                  0x0FFF0000U
#define LRFDRFE32_MOD1_MOD0_FOFF_S                                          16U
#define LRFDRFE32_MOD1_MOD0_FOFF_ALLONES                            0x0FFF0000U
#define LRFDRFE32_MOD1_MOD0_FOFF_ALLZEROS                           0x00000000U

// Field: [12:11] SCHEME 
//
// ENUMs: 
// TWO_POINT_MOD_FRF        2-point modulation with FRF resolution MOD_RES = 
//                          FRF / 2^(21+CANPTHGAIN) Scheme supports both 
//                          open -and closed-loop operation. Scheme allows 
//                          wider modulation bandwiths than INLOOP_MOD_FRF. 
// INLOOP_MOD_FRF           In-loop modulation with FRF resolution MOD_RES = 
//                          FRF / 2^(21+CANPTHGAIN) 
// INLOOP_MOD_FREF          In-loop modulation with FREF resolution MOD_RES = 
//                          FREF / (DIVIDER/2) / 2^(15+CANPTHGAIN) 
//                          DIV.RATIO determines DIVIDER configuration. 
//                          Scheme only supports closed-loop operation. 
// NC                       No connect Modulator output does not add to 
//                          frequencey control word from PLL. 
#define LRFDRFE32_MOD1_MOD0_SCHEME_W                                         2U
#define LRFDRFE32_MOD1_MOD0_SCHEME_M                                0x00001800U
#define LRFDRFE32_MOD1_MOD0_SCHEME_S                                        11U
#define LRFDRFE32_MOD1_MOD0_SCHEME_TWO_POINT_MOD_FRF                0x00001800U
#define LRFDRFE32_MOD1_MOD0_SCHEME_INLOOP_MOD_FRF                   0x00001000U
#define LRFDRFE32_MOD1_MOD0_SCHEME_INLOOP_MOD_FREF                  0x00000800U
#define LRFDRFE32_MOD1_MOD0_SCHEME_NC                               0x00000000U

// Field:  [10:8] SYMSHP 
//
// ENUMs: 
// CHIRP                    Chirp modulation 
// SHAPEDZIGBEE             Use Shaped 802.15.4 modulation 
// PCWSPSK                  Use piecewise linear PSK shaper defined by 
//                          SHAPECFG* registers. 
// ZIGBEE                   Use unshaped zigbee 
// SHAPEDFSK                Use generic 3 symbol shaper defined by SHAPECFG* 
//                          registers. 
#define LRFDRFE32_MOD1_MOD0_SYMSHP_W                                         3U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_M                                0x00000700U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_S                                         8U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_CHIRP                            0x00000400U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_SHAPEDZIGBEE                     0x00000300U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_PCWSPSK                          0x00000200U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_ZIGBEE                           0x00000100U
#define LRFDRFE32_MOD1_MOD0_SYMSHP_SHAPEDFSK                        0x00000000U

// Field:   [7:6] CANPTHGAIN 
//
// ENUMs: 
// TWO_POW_M_18             POW(2,-18) 
// TWO_POW_M_17             POW(2,-17) 
// TWO_POW_M_16             POW(2,-16) 
// TWO_POW_M_15             POW(2,-15) 
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_W                                     2U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_M                            0x000000C0U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_S                                     6U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_TWO_POW_M_18                 0x000000C0U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_TWO_POW_M_17                 0x00000080U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_TWO_POW_M_16                 0x00000040U
#define LRFDRFE32_MOD1_MOD0_CANPTHGAIN_TWO_POW_M_15                 0x00000000U

// Field:   [5:4] SHPGAIN 
//
// ENUMs: 
// X8                       Shape gain = 8 
// X4                       Shape gain = 4 
// X2                       Shape gain = 2 
// X1                       Shape gain = 1 
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_W                                        2U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_M                               0x00000030U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_S                                        4U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_X8                              0x00000030U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_X4                              0x00000020U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_X2                              0x00000010U
#define LRFDRFE32_MOD1_MOD0_SHPGAIN_X1                              0x00000000U

// Field:   [3:2] INTPFACT 
//
// ENUMs: 
// ILLEGAL1                 Illegal, unsupported setting 
// INTP_BY_32               Interpolate by 32 
// INTP_BY_16               Interpolate by 16 
// ILLEGAL0                 Illegal, unsupported setting 
#define LRFDRFE32_MOD1_MOD0_INTPFACT_W                                       2U
#define LRFDRFE32_MOD1_MOD0_INTPFACT_M                              0x0000000CU
#define LRFDRFE32_MOD1_MOD0_INTPFACT_S                                       2U
#define LRFDRFE32_MOD1_MOD0_INTPFACT_ILLEGAL1                       0x0000000CU
#define LRFDRFE32_MOD1_MOD0_INTPFACT_INTP_BY_32                     0x00000008U
#define LRFDRFE32_MOD1_MOD0_INTPFACT_INTP_BY_16                     0x00000004U
#define LRFDRFE32_MOD1_MOD0_INTPFACT_ILLEGAL0                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX1_DTX0
//
//*****************************************************************************
// Field: [31:24] SHP3 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX1_DTX0_SHP3_W                                           8U
#define LRFDRFE32_DTX1_DTX0_SHP3_M                                  0xFF000000U
#define LRFDRFE32_DTX1_DTX0_SHP3_S                                          24U
#define LRFDRFE32_DTX1_DTX0_SHP3_ALLONES                            0xFF000000U
#define LRFDRFE32_DTX1_DTX0_SHP3_ALLZEROS                           0x00000000U

// Field: [23:16] SHP2 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX1_DTX0_SHP2_W                                           8U
#define LRFDRFE32_DTX1_DTX0_SHP2_M                                  0x00FF0000U
#define LRFDRFE32_DTX1_DTX0_SHP2_S                                          16U
#define LRFDRFE32_DTX1_DTX0_SHP2_ALLONES                            0x00FF0000U
#define LRFDRFE32_DTX1_DTX0_SHP2_ALLZEROS                           0x00000000U

// Field:  [15:8] SHP1 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX1_DTX0_SHP1_W                                           8U
#define LRFDRFE32_DTX1_DTX0_SHP1_M                                  0x0000FF00U
#define LRFDRFE32_DTX1_DTX0_SHP1_S                                           8U
#define LRFDRFE32_DTX1_DTX0_SHP1_ALLONES                            0x0000FF00U
#define LRFDRFE32_DTX1_DTX0_SHP1_ALLZEROS                           0x00000000U

// Field:   [7:0] SHP0 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX1_DTX0_SHP0_W                                           8U
#define LRFDRFE32_DTX1_DTX0_SHP0_M                                  0x000000FFU
#define LRFDRFE32_DTX1_DTX0_SHP0_S                                           0U
#define LRFDRFE32_DTX1_DTX0_SHP0_ALLONES                            0x000000FFU
#define LRFDRFE32_DTX1_DTX0_SHP0_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX3_DTX2
//
//*****************************************************************************
// Field: [31:24] SHP7 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX3_DTX2_SHP7_W                                           8U
#define LRFDRFE32_DTX3_DTX2_SHP7_M                                  0xFF000000U
#define LRFDRFE32_DTX3_DTX2_SHP7_S                                          24U
#define LRFDRFE32_DTX3_DTX2_SHP7_ALLONES                            0xFF000000U
#define LRFDRFE32_DTX3_DTX2_SHP7_ALLZEROS                           0x00000000U

// Field: [23:16] SHP6 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX3_DTX2_SHP6_W                                           8U
#define LRFDRFE32_DTX3_DTX2_SHP6_M                                  0x00FF0000U
#define LRFDRFE32_DTX3_DTX2_SHP6_S                                          16U
#define LRFDRFE32_DTX3_DTX2_SHP6_ALLONES                            0x00FF0000U
#define LRFDRFE32_DTX3_DTX2_SHP6_ALLZEROS                           0x00000000U

// Field:  [15:8] SHP5 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX3_DTX2_SHP5_W                                           8U
#define LRFDRFE32_DTX3_DTX2_SHP5_M                                  0x0000FF00U
#define LRFDRFE32_DTX3_DTX2_SHP5_S                                           8U
#define LRFDRFE32_DTX3_DTX2_SHP5_ALLONES                            0x0000FF00U
#define LRFDRFE32_DTX3_DTX2_SHP5_ALLZEROS                           0x00000000U

// Field:   [7:0] SHP4 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX3_DTX2_SHP4_W                                           8U
#define LRFDRFE32_DTX3_DTX2_SHP4_M                                  0x000000FFU
#define LRFDRFE32_DTX3_DTX2_SHP4_S                                           0U
#define LRFDRFE32_DTX3_DTX2_SHP4_ALLONES                            0x000000FFU
#define LRFDRFE32_DTX3_DTX2_SHP4_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX5_DTX4
//
//*****************************************************************************
// Field: [31:24] SHP11 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX5_DTX4_SHP11_W                                          8U
#define LRFDRFE32_DTX5_DTX4_SHP11_M                                 0xFF000000U
#define LRFDRFE32_DTX5_DTX4_SHP11_S                                         24U
#define LRFDRFE32_DTX5_DTX4_SHP11_ALLONES                           0xFF000000U
#define LRFDRFE32_DTX5_DTX4_SHP11_ALLZEROS                          0x00000000U

// Field: [23:16] SHP10 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX5_DTX4_SHP10_W                                          8U
#define LRFDRFE32_DTX5_DTX4_SHP10_M                                 0x00FF0000U
#define LRFDRFE32_DTX5_DTX4_SHP10_S                                         16U
#define LRFDRFE32_DTX5_DTX4_SHP10_ALLONES                           0x00FF0000U
#define LRFDRFE32_DTX5_DTX4_SHP10_ALLZEROS                          0x00000000U

// Field:  [15:8] SHP9 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX5_DTX4_SHP9_W                                           8U
#define LRFDRFE32_DTX5_DTX4_SHP9_M                                  0x0000FF00U
#define LRFDRFE32_DTX5_DTX4_SHP9_S                                           8U
#define LRFDRFE32_DTX5_DTX4_SHP9_ALLONES                            0x0000FF00U
#define LRFDRFE32_DTX5_DTX4_SHP9_ALLZEROS                           0x00000000U

// Field:   [7:0] SHP8 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX5_DTX4_SHP8_W                                           8U
#define LRFDRFE32_DTX5_DTX4_SHP8_M                                  0x000000FFU
#define LRFDRFE32_DTX5_DTX4_SHP8_S                                           0U
#define LRFDRFE32_DTX5_DTX4_SHP8_ALLONES                            0x000000FFU
#define LRFDRFE32_DTX5_DTX4_SHP8_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX7_DTX6
//
//*****************************************************************************
// Field: [31:24] SHP15 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX7_DTX6_SHP15_W                                          8U
#define LRFDRFE32_DTX7_DTX6_SHP15_M                                 0xFF000000U
#define LRFDRFE32_DTX7_DTX6_SHP15_S                                         24U
#define LRFDRFE32_DTX7_DTX6_SHP15_ALLONES                           0xFF000000U
#define LRFDRFE32_DTX7_DTX6_SHP15_ALLZEROS                          0x00000000U

// Field: [23:16] SHP14 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX7_DTX6_SHP14_W                                          8U
#define LRFDRFE32_DTX7_DTX6_SHP14_M                                 0x00FF0000U
#define LRFDRFE32_DTX7_DTX6_SHP14_S                                         16U
#define LRFDRFE32_DTX7_DTX6_SHP14_ALLONES                           0x00FF0000U
#define LRFDRFE32_DTX7_DTX6_SHP14_ALLZEROS                          0x00000000U

// Field:  [15:8] SHP13 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX7_DTX6_SHP13_W                                          8U
#define LRFDRFE32_DTX7_DTX6_SHP13_M                                 0x0000FF00U
#define LRFDRFE32_DTX7_DTX6_SHP13_S                                          8U
#define LRFDRFE32_DTX7_DTX6_SHP13_ALLONES                           0x0000FF00U
#define LRFDRFE32_DTX7_DTX6_SHP13_ALLZEROS                          0x00000000U

// Field:   [7:0] SHP12 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX7_DTX6_SHP12_W                                          8U
#define LRFDRFE32_DTX7_DTX6_SHP12_M                                 0x000000FFU
#define LRFDRFE32_DTX7_DTX6_SHP12_S                                          0U
#define LRFDRFE32_DTX7_DTX6_SHP12_ALLONES                           0x000000FFU
#define LRFDRFE32_DTX7_DTX6_SHP12_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX9_DTX8
//
//*****************************************************************************
// Field: [31:24] SHP19 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX9_DTX8_SHP19_W                                          8U
#define LRFDRFE32_DTX9_DTX8_SHP19_M                                 0xFF000000U
#define LRFDRFE32_DTX9_DTX8_SHP19_S                                         24U
#define LRFDRFE32_DTX9_DTX8_SHP19_ALLONES                           0xFF000000U
#define LRFDRFE32_DTX9_DTX8_SHP19_ALLZEROS                          0x00000000U

// Field: [23:16] SHP18 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX9_DTX8_SHP18_W                                          8U
#define LRFDRFE32_DTX9_DTX8_SHP18_M                                 0x00FF0000U
#define LRFDRFE32_DTX9_DTX8_SHP18_S                                         16U
#define LRFDRFE32_DTX9_DTX8_SHP18_ALLONES                           0x00FF0000U
#define LRFDRFE32_DTX9_DTX8_SHP18_ALLZEROS                          0x00000000U

// Field:  [15:8] SHP17 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX9_DTX8_SHP17_W                                          8U
#define LRFDRFE32_DTX9_DTX8_SHP17_M                                 0x0000FF00U
#define LRFDRFE32_DTX9_DTX8_SHP17_S                                          8U
#define LRFDRFE32_DTX9_DTX8_SHP17_ALLONES                           0x0000FF00U
#define LRFDRFE32_DTX9_DTX8_SHP17_ALLZEROS                          0x00000000U

// Field:   [7:0] SHP16 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX9_DTX8_SHP16_W                                          8U
#define LRFDRFE32_DTX9_DTX8_SHP16_M                                 0x000000FFU
#define LRFDRFE32_DTX9_DTX8_SHP16_S                                          0U
#define LRFDRFE32_DTX9_DTX8_SHP16_ALLONES                           0x000000FFU
#define LRFDRFE32_DTX9_DTX8_SHP16_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DTX11_DTX10
//
//*****************************************************************************
// Field: [31:24] SHP23 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX11_DTX10_SHP23_W                                        8U
#define LRFDRFE32_DTX11_DTX10_SHP23_M                               0xFF000000U
#define LRFDRFE32_DTX11_DTX10_SHP23_S                                       24U
#define LRFDRFE32_DTX11_DTX10_SHP23_ALLONES                         0xFF000000U
#define LRFDRFE32_DTX11_DTX10_SHP23_ALLZEROS                        0x00000000U

// Field: [23:16] SHP22 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX11_DTX10_SHP22_W                                        8U
#define LRFDRFE32_DTX11_DTX10_SHP22_M                               0x00FF0000U
#define LRFDRFE32_DTX11_DTX10_SHP22_S                                       16U
#define LRFDRFE32_DTX11_DTX10_SHP22_ALLONES                         0x00FF0000U
#define LRFDRFE32_DTX11_DTX10_SHP22_ALLZEROS                        0x00000000U

// Field:  [15:8] SHP21 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX11_DTX10_SHP21_W                                        8U
#define LRFDRFE32_DTX11_DTX10_SHP21_M                               0x0000FF00U
#define LRFDRFE32_DTX11_DTX10_SHP21_S                                        8U
#define LRFDRFE32_DTX11_DTX10_SHP21_ALLONES                         0x0000FF00U
#define LRFDRFE32_DTX11_DTX10_SHP21_ALLZEROS                        0x00000000U

// Field:   [7:0] SHP20 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DTX11_DTX10_SHP20_W                                        8U
#define LRFDRFE32_DTX11_DTX10_SHP20_M                               0x000000FFU
#define LRFDRFE32_DTX11_DTX10_SHP20_S                                        0U
#define LRFDRFE32_DTX11_DTX10_SHP20_ALLONES                         0x000000FFU
#define LRFDRFE32_DTX11_DTX10_SHP20_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PLLM0
//
//*****************************************************************************
// Field:  [31:2] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLM0_VAL_W                                               30U
#define LRFDRFE32_PLLM0_VAL_M                                       0xFFFFFFFCU
#define LRFDRFE32_PLLM0_VAL_S                                                2U
#define LRFDRFE32_PLLM0_VAL_ALLONES                                 0x0000FFFCU
#define LRFDRFE32_PLLM0_VAL_ALLZEROS                                0x00000000U

// Field:   [1:0] SPARE0 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLM0_SPARE0_W                                             2U
#define LRFDRFE32_PLLM0_SPARE0_M                                    0x00000003U
#define LRFDRFE32_PLLM0_SPARE0_S                                             0U
#define LRFDRFE32_PLLM0_SPARE0_ALLONES                              0x00000003U
#define LRFDRFE32_PLLM0_SPARE0_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PLLM1
//
//*****************************************************************************
// Field:  [31:2] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLM1_VAL_W                                               30U
#define LRFDRFE32_PLLM1_VAL_M                                       0xFFFFFFFCU
#define LRFDRFE32_PLLM1_VAL_S                                                2U
#define LRFDRFE32_PLLM1_VAL_ALLONES                                 0x0000FFFCU
#define LRFDRFE32_PLLM1_VAL_ALLZEROS                                0x00000000U

// Field:   [1:0] SPARE0 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PLLM1_SPARE0_W                                             2U
#define LRFDRFE32_PLLM1_SPARE0_M                                    0x00000003U
#define LRFDRFE32_PLLM1_SPARE0_S                                             0U
#define LRFDRFE32_PLLM1_SPARE0_ALLONES                              0x00000003U
#define LRFDRFE32_PLLM1_SPARE0_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_CALMMID_CALMCRS
//
//*****************************************************************************
// Field: [31:16] CALMMID_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_W                             16U
#define LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_M                     0xFFFF0000U
#define LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_S                             16U
#define LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_ALLONES               0xFFFF0000U
#define LRFDRFE32_CALMMID_CALMCRS_CALMMID_VAL_ALLZEROS              0x00000000U

// Field:  [15:0] CALMCRS_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_W                             16U
#define LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_M                     0x0000FFFFU
#define LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_S                              0U
#define LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_ALLONES               0x0000FFFFU
#define LRFDRFE32_CALMMID_CALMCRS_CALMCRS_VAL_ALLZEROS              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_REFDIV
//
//*****************************************************************************
// Field:  [15:0] LOAD 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_REFDIV_LOAD_W                                             16U
#define LRFDRFE32_REFDIV_LOAD_M                                     0x0000FFFFU
#define LRFDRFE32_REFDIV_LOAD_S                                              0U
#define LRFDRFE32_REFDIV_LOAD_ALLONES                               0x0000FFFFU
#define LRFDRFE32_REFDIV_LOAD_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DLOCTL0
//
//*****************************************************************************
// Field:  [10:8] TDCSTOP 
//
// ENUMs: 
// OPEN                     Open-loop operation 
// CLOSED                   Closed-loop operation 
#define LRFDRFE32_DLOCTL0_TDCSTOP_W                                          3U
#define LRFDRFE32_DLOCTL0_TDCSTOP_M                                 0x00000700U
#define LRFDRFE32_DLOCTL0_TDCSTOP_S                                          8U
#define LRFDRFE32_DLOCTL0_TDCSTOP_OPEN                              0x00000100U
#define LRFDRFE32_DLOCTL0_TDCSTOP_CLOSED                            0x00000000U

// Field:     [7] DTSTXTAL 
//
// ENUMs: 
// ONE                      Enable XTALBAW DTST interface 
// ZERO                     Disable XTALBAW DTST interface 
#define LRFDRFE32_DLOCTL0_DTSTXTAL                                  0x00000080U
#define LRFDRFE32_DLOCTL0_DTSTXTAL_M                                0x00000080U
#define LRFDRFE32_DLOCTL0_DTSTXTAL_S                                         7U
#define LRFDRFE32_DLOCTL0_DTSTXTAL_ONE                              0x00000080U
#define LRFDRFE32_DLOCTL0_DTSTXTAL_ZERO                             0x00000000U

// Field:   [6:4] LOOPUPD 
//
// ENUMs: 
// ALT                      Use alternate REF (PLLM1) 
// DEF                      Use default FREF (PLLM0) 
#define LRFDRFE32_DLOCTL0_LOOPUPD_W                                          3U
#define LRFDRFE32_DLOCTL0_LOOPUPD_M                                 0x00000070U
#define LRFDRFE32_DLOCTL0_LOOPUPD_S                                          4U
#define LRFDRFE32_DLOCTL0_LOOPUPD_ALT                               0x00000010U
#define LRFDRFE32_DLOCTL0_LOOPUPD_DEF                               0x00000000U

// Field:     [3] PH3 
//
// ENUMs: 
// START                    Close the loop to aquire phase lock, i.e. phase 3 
//                          of calibration routine. 
// HALT                     Halt DLO FSM after DCO frequency span measurement 
//                          When DLO and RFE runs KDCO estimation, RFE must 
//                          compute KDCO from the frequency span, and 
//                          calculate loop filter settings to use before 
//                          lock aquisition. 
#define LRFDRFE32_DLOCTL0_PH3                                       0x00000008U
#define LRFDRFE32_DLOCTL0_PH3_M                                     0x00000008U
#define LRFDRFE32_DLOCTL0_PH3_S                                              3U
#define LRFDRFE32_DLOCTL0_PH3_START                                 0x00000008U
#define LRFDRFE32_DLOCTL0_PH3_HALT                                  0x00000000U

// Field:     [2] PH2 
//
// ENUMs: 
// START                    Start KDCO estimation, i.e. phase 2 of calibration 
//                          routine. 
// HALT                     Halt DLO FSM after TDC calibration measurement 
//                          When DLO and RFE runs TDC calibration, RFE must 
//                          use calibration measurement to calculcate 
//                          CAL2.KTDCINV. 
#define LRFDRFE32_DLOCTL0_PH2                                       0x00000004U
#define LRFDRFE32_DLOCTL0_PH2_M                                     0x00000004U
#define LRFDRFE32_DLOCTL0_PH2_S                                              2U
#define LRFDRFE32_DLOCTL0_PH2_START                                 0x00000004U
#define LRFDRFE32_DLOCTL0_PH2_HALT                                  0x00000000U

// Field:     [1] LOOPMODE 
//
// ENUMs: 
// OPEN                     Open-loop operation 
// CLOSED                   Closed-loop operation 
#define LRFDRFE32_DLOCTL0_LOOPMODE                                  0x00000002U
#define LRFDRFE32_DLOCTL0_LOOPMODE_M                                0x00000002U
#define LRFDRFE32_DLOCTL0_LOOPMODE_S                                         1U
#define LRFDRFE32_DLOCTL0_LOOPMODE_OPEN                             0x00000002U
#define LRFDRFE32_DLOCTL0_LOOPMODE_CLOSED                           0x00000000U

// Field:     [0] RSTN 
//
// ENUMs: 
// ACTIVE                   DLO is not held in reset 
// RESET                    DLO is reset 
#define LRFDRFE32_DLOCTL0_RSTN                                      0x00000001U
#define LRFDRFE32_DLOCTL0_RSTN_M                                    0x00000001U
#define LRFDRFE32_DLOCTL0_RSTN_S                                             0U
#define LRFDRFE32_DLOCTL0_RSTN_ACTIVE                               0x00000001U
#define LRFDRFE32_DLOCTL0_RSTN_RESET                                0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DLOCTL1
//
//*****************************************************************************
// Field:    [15] DCO 
//
// ENUMs: 
// EN                       Enable DCO 
// DIS                      Disable DCO 
#define LRFDRFE32_DLOCTL1_DCO                                       0x00008000U
#define LRFDRFE32_DLOCTL1_DCO_M                                     0x00008000U
#define LRFDRFE32_DLOCTL1_DCO_S                                             15U
#define LRFDRFE32_DLOCTL1_DCO_EN                                    0x00008000U
#define LRFDRFE32_DLOCTL1_DCO_DIS                                   0x00000000U

// Field:     [7] FCDEM 
//
// ENUMs: 
// EN                       Enable DEM 
// DIS                      Disable DEM 
#define LRFDRFE32_DLOCTL1_FCDEM                                     0x00000080U
#define LRFDRFE32_DLOCTL1_FCDEM_M                                   0x00000080U
#define LRFDRFE32_DLOCTL1_FCDEM_S                                            7U
#define LRFDRFE32_DLOCTL1_FCDEM_EN                                  0x00000080U
#define LRFDRFE32_DLOCTL1_FCDEM_DIS                                 0x00000000U

// Field:     [6] DTSTCKVD 
//
// ENUMs: 
// ONE                      Enable CKVD DTST interface 
// ZERO                     Disable CKVD DTST interface 
#define LRFDRFE32_DLOCTL1_DTSTCKVD                                  0x00000040U
#define LRFDRFE32_DLOCTL1_DTSTCKVD_M                                0x00000040U
#define LRFDRFE32_DLOCTL1_DTSTCKVD_S                                         6U
#define LRFDRFE32_DLOCTL1_DTSTCKVD_ONE                              0x00000040U
#define LRFDRFE32_DLOCTL1_DTSTCKVD_ZERO                             0x00000000U

// Field:     [5] PHEDISC 
//
// ENUMs: 
// EN                       Enable phase error discard function 
// DIS                      Disable phase error discard function 
#define LRFDRFE32_DLOCTL1_PHEDISC                                   0x00000020U
#define LRFDRFE32_DLOCTL1_PHEDISC_M                                 0x00000020U
#define LRFDRFE32_DLOCTL1_PHEDISC_S                                          5U
#define LRFDRFE32_DLOCTL1_PHEDISC_EN                                0x00000020U
#define LRFDRFE32_DLOCTL1_PHEDISC_DIS                               0x00000000U

// Field:     [4] PLLMON 
//
// ENUMs: 
// EN                       Enable PLL monitor 
// DIS                      Disable and reset PLL monitor 
#define LRFDRFE32_DLOCTL1_PLLMON                                    0x00000010U
#define LRFDRFE32_DLOCTL1_PLLMON_M                                  0x00000010U
#define LRFDRFE32_DLOCTL1_PLLMON_S                                           4U
#define LRFDRFE32_DLOCTL1_PLLMON_EN                                 0x00000010U
#define LRFDRFE32_DLOCTL1_PLLMON_DIS                                0x00000000U

// Field:     [3] IIR 
//
// ENUMs: 
// EN                       Enable IIR filter 
// DIS                      Disable IIR filter 
#define LRFDRFE32_DLOCTL1_IIR                                       0x00000008U
#define LRFDRFE32_DLOCTL1_IIR_M                                     0x00000008U
#define LRFDRFE32_DLOCTL1_IIR_S                                              3U
#define LRFDRFE32_DLOCTL1_IIR_EN                                    0x00000008U
#define LRFDRFE32_DLOCTL1_IIR_DIS                                   0x00000000U

// Field:     [2] MOD 
//
// ENUMs: 
// EN                       Enable MODISF 
// DIS                      Disable MODISF 
#define LRFDRFE32_DLOCTL1_MOD                                       0x00000004U
#define LRFDRFE32_DLOCTL1_MOD_M                                     0x00000004U
#define LRFDRFE32_DLOCTL1_MOD_S                                              2U
#define LRFDRFE32_DLOCTL1_MOD_EN                                    0x00000004U
#define LRFDRFE32_DLOCTL1_MOD_DIS                                   0x00000000U

// Field:     [1] MODINIT 
//
// ENUMs: 
// ACTIVATE                 Activate MODISF initialization 
// DEACTIVATE               Deactivate MODISF initialization 
#define LRFDRFE32_DLOCTL1_MODINIT                                   0x00000002U
#define LRFDRFE32_DLOCTL1_MODINIT_M                                 0x00000002U
#define LRFDRFE32_DLOCTL1_MODINIT_S                                          1U
#define LRFDRFE32_DLOCTL1_MODINIT_ACTIVATE                          0x00000002U
#define LRFDRFE32_DLOCTL1_MODINIT_DEACTIVATE                        0x00000000U

// Field:     [0] MTDCRSTN 
//
// ENUMs: 
// ACTIVE                   Release MTDC reset 
// RESET                    Reset MTDC 
#define LRFDRFE32_DLOCTL1_MTDCRSTN                                  0x00000001U
#define LRFDRFE32_DLOCTL1_MTDCRSTN_M                                0x00000001U
#define LRFDRFE32_DLOCTL1_MTDCRSTN_S                                         0U
#define LRFDRFE32_DLOCTL1_MTDCRSTN_ACTIVE                           0x00000001U
#define LRFDRFE32_DLOCTL1_MTDCRSTN_RESET                            0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DCOOVR1_DCOOVR0
//
//*****************************************************************************
// Field: [30:24] FINECODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECODE_W                                 7U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECODE_M                        0x7F000000U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECODE_S                                24U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECODE_ALLONES                  0x7F000000U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECODE_ALLZEROS                 0x00000000U

// Field: [23:16] SDMICODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICODE_W                                 8U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICODE_M                        0x00FF0000U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICODE_S                                16U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICODE_ALLONES                  0x00FF0000U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICODE_ALLZEROS                 0x00000000U

// Field:  [13:8] MIDCODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCODE_W                                  6U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCODE_M                         0x00003F00U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCODE_S                                  8U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCODE_ALLONES                   0x00003F00U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCODE_ALLZEROS                  0x00000000U

// Field:   [7:4] CRSCODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCODE_W                                  4U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCODE_M                         0x000000F0U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCODE_S                                  4U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCODE_ALLONES                   0x000000F0U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCODE_ALLZEROS                  0x00000000U

// Field:     [3] FINECTL 
//
// ENUMs: 
// EN                       Enable fine code override 
// DIS                      Disable fine code override 
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECTL                           0x00000008U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECTL_M                         0x00000008U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECTL_S                                  3U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECTL_EN                        0x00000008U
#define LRFDRFE32_DCOOVR1_DCOOVR0_FINECTL_DIS                       0x00000000U

// Field:     [2] SDMICTL 
//
// ENUMs: 
// EN                       Enable SDM input code override 
// DIS                      Disable SDM input code override 
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICTL                           0x00000004U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICTL_M                         0x00000004U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICTL_S                                  2U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICTL_EN                        0x00000004U
#define LRFDRFE32_DCOOVR1_DCOOVR0_SDMICTL_DIS                       0x00000000U

// Field:     [1] MIDCTL 
//
// ENUMs: 
// EN                       Enable mid code override 
// DIS                      Disable mid code override 
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCTL                            0x00000002U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCTL_M                          0x00000002U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCTL_S                                   1U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCTL_EN                         0x00000002U
#define LRFDRFE32_DCOOVR1_DCOOVR0_MIDCTL_DIS                        0x00000000U

// Field:     [0] CRSCTL 
//
// ENUMs: 
// EN                       Enable coarse code override 
// DIS                      Disable coarse code override 
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCTL                            0x00000001U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCTL_M                          0x00000001U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCTL_S                                   0U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCTL_EN                         0x00000001U
#define LRFDRFE32_DCOOVR1_DCOOVR0_CRSCTL_DIS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DLOEV_DTST
//
//*****************************************************************************
// Field:    [23] LOCK 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DLOEV_DTST_LOCK                                   0x00800000U
#define LRFDRFE32_DLOEV_DTST_LOCK_M                                 0x00800000U
#define LRFDRFE32_DLOEV_DTST_LOCK_S                                         23U
#define LRFDRFE32_DLOEV_DTST_LOCK_ONE                               0x00800000U
#define LRFDRFE32_DLOEV_DTST_LOCK_ZERO                              0x00000000U

// Field:    [22] LOL 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DLOEV_DTST_LOL                                    0x00400000U
#define LRFDRFE32_DLOEV_DTST_LOL_M                                  0x00400000U
#define LRFDRFE32_DLOEV_DTST_LOL_S                                          22U
#define LRFDRFE32_DLOEV_DTST_LOL_ONE                                0x00400000U
#define LRFDRFE32_DLOEV_DTST_LOL_ZERO                               0x00000000U

// Field:    [21] FCABVTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DLOEV_DTST_FCABVTHR                               0x00200000U
#define LRFDRFE32_DLOEV_DTST_FCABVTHR_M                             0x00200000U
#define LRFDRFE32_DLOEV_DTST_FCABVTHR_S                                     21U
#define LRFDRFE32_DLOEV_DTST_FCABVTHR_ONE                           0x00200000U
#define LRFDRFE32_DLOEV_DTST_FCABVTHR_ZERO                          0x00000000U

// Field:    [20] FCBLWTHR 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DLOEV_DTST_FCBLWTHR                               0x00100000U
#define LRFDRFE32_DLOEV_DTST_FCBLWTHR_M                             0x00100000U
#define LRFDRFE32_DLOEV_DTST_FCBLWTHR_S                                     20U
#define LRFDRFE32_DLOEV_DTST_FCBLWTHR_ONE                           0x00100000U
#define LRFDRFE32_DLOEV_DTST_FCBLWTHR_ZERO                          0x00000000U

// Field: [19:16] STATE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DLOEV_DTST_STATE_W                                         4U
#define LRFDRFE32_DLOEV_DTST_STATE_M                                0x000F0000U
#define LRFDRFE32_DLOEV_DTST_STATE_S                                        16U
#define LRFDRFE32_DLOEV_DTST_STATE_ALLONES                          0x000F0000U
#define LRFDRFE32_DLOEV_DTST_STATE_ALLZEROS                         0x00000000U

// Field: [14:11] SPARE11 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DLOEV_DTST_SPARE11_W                                       4U
#define LRFDRFE32_DLOEV_DTST_SPARE11_M                              0x00007800U
#define LRFDRFE32_DLOEV_DTST_SPARE11_S                                      11U
#define LRFDRFE32_DLOEV_DTST_SPARE11_ALLONES                        0x00007800U
#define LRFDRFE32_DLOEV_DTST_SPARE11_ALLZEROS                       0x00000000U

// Field:  [10:8] VARTGLDLY 
//
// ENUMs: 
// CLK_7_PER                Toggle lags data by 7 CKVD16 periods. 
// CLK_6_PER                Toggle lags data by 6 CKVD16 periods. 
// CLK_5_PER                Toggle lags data by 5 CKVD16 periods. 
// CLK_4_PER                Toggle lags data by 4 CKVD16 periods. 
// CLK_3_PER                Toggle lags data by 3 CKVD16 periods. 
// CLK_2_PER                Toggle lags data by 2 CKVD16 periods. 
// CLK_1_PER                Toggle lags data by 1 CKVD16 periods. 
// CLK_0_PER                Toggle lags data by 0 CKVD16 periods. 
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_W                                     3U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_M                            0x00000700U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_S                                     8U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_7_PER                    0x00000700U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_6_PER                    0x00000600U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_5_PER                    0x00000500U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_4_PER                    0x00000400U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_3_PER                    0x00000300U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_2_PER                    0x00000200U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_1_PER                    0x00000100U
#define LRFDRFE32_DLOEV_DTST_VARTGLDLY_CLK_0_PER                    0x00000000U

// Field:     [7] REFTGLDLY 
//
// ENUMs: 
// CLK_1_PER                Toggle lags data by 1 HFXT/BAW periods. 
// CLK_0_PER                Toggle lags data by 0 HFXT/BAW periods. 
#define LRFDRFE32_DLOEV_DTST_REFTGLDLY                              0x00000080U
#define LRFDRFE32_DLOEV_DTST_REFTGLDLY_M                            0x00000080U
#define LRFDRFE32_DLOEV_DTST_REFTGLDLY_S                                     7U
#define LRFDRFE32_DLOEV_DTST_REFTGLDLY_CLK_1_PER                    0x00000080U
#define LRFDRFE32_DLOEV_DTST_REFTGLDLY_CLK_0_PER                    0x00000000U

// Field:     [6] TRNSEQ 
//
// ENUMs: 
// EN                       Enable trainer sequence 
// DIS                      Disable trainer sequence 
#define LRFDRFE32_DLOEV_DTST_TRNSEQ                                 0x00000040U
#define LRFDRFE32_DLOEV_DTST_TRNSEQ_M                               0x00000040U
#define LRFDRFE32_DLOEV_DTST_TRNSEQ_S                                        6U
#define LRFDRFE32_DLOEV_DTST_TRNSEQ_EN                              0x00000040U
#define LRFDRFE32_DLOEV_DTST_TRNSEQ_DIS                             0x00000000U

// Field:     [5] SPARE5 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DLOEV_DTST_SPARE5                                 0x00000020U
#define LRFDRFE32_DLOEV_DTST_SPARE5_M                               0x00000020U
#define LRFDRFE32_DLOEV_DTST_SPARE5_S                                        5U
#define LRFDRFE32_DLOEV_DTST_SPARE5_ONE                             0x00000020U
#define LRFDRFE32_DLOEV_DTST_SPARE5_ZERO                            0x00000000U

// Field:   [4:0] SIG 
//
// ENUMs: 
// VAR_NC_15                dtst_data = 0x0000 
// VAR_NC_14                dtst_data = 0x0000 
// VAR_NC_13                dtst_data = 0x0000 
// VAR_NC_12                dtst_data = 0x0000 
// VAR_NC_11                dtst_data = 0x0000 
// VAR_LOOP_UPD_FINECODE    dtst_data : [15] : (u_pll/pll_loop_update) [14:0] 
//                          : u_pll/po_ckvd16_finecode_pll 
// VAR_LOCK_FINECODE        dtst_data : [15] : (u_pll/po_ckvd48_pllmon_lock 
//                          XOR u_pll/po_ckvd48_pllmon_lol) [14:0] : 
//                          u_pll/po_ckvd16_finecode_pll 
// VAR_MPX_CAN              dtst_data : [15] : u_mpx/freq_can[16] [14:0] : 
//                          u_mpx/freq_can[14:0] Format is 1.15s. This 
//                          field holds how much phase DTX adds to DCO per 
//                          reference frequency. This is a slice of the 
//                          signals that goes to u_pll which is 3.18s. 
//                          Hence, wrapping can occur. 
// VAR_TDCSTOP_STATUS_TDC   dtst_data : [15:14] : po_tdc_stop_dly_sel [13] : 
//                          u_pll/pi_tdc_msb_error [12] : 
//                          u_pll/pll_loop_update [11] : 
//                          (u_pll/po_ckvd48_pllmon_lock XOR 
//                          u_pll/po_ckvd48_pllmon_lol) [10:0]: 
//                          u_pll/pi_tdc_data Note that [12:11] are samples 
//                          from previous reference clock edge. 
// VAR_TDCSTOP_PHERR        dtst_data : [15:14] : po_tdc_stop_dly_sel [13] 
//                          u_pll/phase_error[16] [12:0]: 
//                          u_pll/phase_error[12:0] [13:0] : phase_error. 
//                          Format is 3.11s. 
// VAR_PH_COMP_PHERR_TDCSTOPdtst_data : [15:14] : po_tdc_stop_dly_sel [13] : 
//                          u_pll/phase_error[16] [12:9]: 
//                          u_pll/phase_error[11:8] [8:0] : 
//                          u_pll/var_phase[14: 6] [13:9] : phase error. 
//                          Format is 2.3s. [8:0] : variable phase. Format 
//                          is 4.5u. 
// VAR_PH_TDCCORR           dtst_data : [15] ; u_pll/pi_tdc_msb_error [14:11] 
//                          : u_pll/pi_pi_cnt_lsb [10:0] : 
//                          u_pll/tdc_data_corr 
// VAR_PH_RAW               dtst_data : [15] ; u_pll/pi_tdc_msb_error [14:11] 
//                          : u_pll/pi_pi_cnt_lsb [10:0] : 
//                          u_pll/pi_tdc_data 
// VAR_PHERR_LOWER          dtst_data : [15] : u_pll/phase_error[16] [14:0] : 
//                          u_pll/phase_error[14:0] Format is 5.11s. Phase 
//                          error wraps if if too large. 
// VAR_PHERR_UPPER          dtst_data = u_pll/phase_error[16:1] Format is 
//                          6.10s. 
// VAR_NC_0                 dtst_data = 0x0000 
// REF_NC_15                dtst_data = 0x0000 
// REF_NC_14                dtst_data = 0x0000 
// REF_NC_13                dtst_data = 0x0000 
// REF_NC_12                dtst_data = 0x0000 
// REF_NC_11                dtst_data = 0x0000 
// REF_NC_10                dtst_data = 0x0000 
// REF_NC_9                 dtst_data = 0x0000 
// REF_NC_8                 dtst_data = 0x0000 
// REF_NC_7                 dtst_data = 0x0000 
// REF_NC_6                 dtst_data = 0x0000 
// REF_NC_5                 dtst_data = 0x0000 
// REF_NC_4                 dtst_data = 0x0000 
// REF_NC_3                 dtst_data = 0x0000 
// REF_FERR_MAG             dtst_data = u_fsm/po_dtst_fsm_ferr_mag Format 
//                          is14.2u. The signal is only updated for 
//                          frequency measurements that affect the 
//                          calibration result. 
// REF_FSMCAL               dtst_data : [15] : '0' [14] : 
//                          u_fsm/pi_pll_lock_ind [13:10] : 
//                          u_fsm/po_dsts_fsm_state [9:6] : 
//                          u_fsm/po_dtst_fsm_coarse [5:0] : 
//                          u_fsm/po_dtst_fsm_mid 
// REF_NC_0                 dtst_data = 0x0000 
#define LRFDRFE32_DLOEV_DTST_SIG_W                                           5U
#define LRFDRFE32_DLOEV_DTST_SIG_M                                  0x0000001FU
#define LRFDRFE32_DLOEV_DTST_SIG_S                                           0U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_15                          0x0000001FU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_14                          0x0000001EU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_13                          0x0000001DU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_12                          0x0000001CU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_11                          0x0000001BU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_LOOP_UPD_FINECODE              0x0000001AU
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_LOCK_FINECODE                  0x00000019U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_MPX_CAN                        0x00000018U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_TDCSTOP_STATUS_TDC             0x00000017U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_TDCSTOP_PHERR                  0x00000016U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_PH_COMP_PHERR_TDCSTOP          0x00000015U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_PH_TDCCORR                     0x00000014U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_PH_RAW                         0x00000013U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_PHERR_LOWER                    0x00000012U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_PHERR_UPPER                    0x00000011U
#define LRFDRFE32_DLOEV_DTST_SIG_VAR_NC_0                           0x00000010U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_15                          0x0000000FU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_14                          0x0000000EU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_13                          0x0000000DU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_12                          0x0000000CU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_11                          0x0000000BU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_10                          0x0000000AU
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_9                           0x00000009U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_8                           0x00000008U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_7                           0x00000007U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_6                           0x00000006U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_5                           0x00000005U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_4                           0x00000004U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_3                           0x00000003U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_FERR_MAG                       0x00000002U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_FSMCAL                         0x00000001U
#define LRFDRFE32_DLOEV_DTST_SIG_REF_NC_0                           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_FDCOSPANLSB_DTSTRD
//
//*****************************************************************************
// Field: [31:16] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_VAL_W                                  16U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_VAL_M                          0xFFFF0000U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_VAL_S                                  16U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_VAL_ALLONES                    0xFFFF0000U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_VAL_ALLZEROS                   0x00000000U

// Field:  [15:0] DATA 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_DATA_W                                 16U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_DATA_M                         0x0000FFFFU
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_DATA_S                                  0U
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_DATA_ALLONES                   0x0000FFFFU
#define LRFDRFE32_FDCOSPANLSB_DTSTRD_DATA_ALLZEROS                  0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TDCCAL_FDCOSPANMSB
//
//*****************************************************************************
// Field: [31:16] TDCCAL_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_TDCCAL_VAL_W                           16U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_TDCCAL_VAL_M                   0xFFFF0000U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_TDCCAL_VAL_S                           16U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_TDCCAL_VAL_ALLONES             0xFFFF0000U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_TDCCAL_VAL_ALLZEROS            0x00000000U

// Field:   [2:0] FDCOSPANMSB_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_FDCOSPANMSB_VAL_W                       3U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_FDCOSPANMSB_VAL_M              0x00000007U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_FDCOSPANMSB_VAL_S                       0U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_FDCOSPANMSB_VAL_ALLONES        0x00000007U
#define LRFDRFE32_TDCCAL_FDCOSPANMSB_FDCOSPANMSB_VAL_ALLZEROS       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_GPI_CALRES
//
//*****************************************************************************
// Field:    [23] GPI7 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI7                                   0x00800000U
#define LRFDRFE32_GPI_CALRES_GPI7_M                                 0x00800000U
#define LRFDRFE32_GPI_CALRES_GPI7_S                                         23U
#define LRFDRFE32_GPI_CALRES_GPI7_ONE                               0x00800000U
#define LRFDRFE32_GPI_CALRES_GPI7_ZERO                              0x00000000U

// Field:    [22] GPI6 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI6                                   0x00400000U
#define LRFDRFE32_GPI_CALRES_GPI6_M                                 0x00400000U
#define LRFDRFE32_GPI_CALRES_GPI6_S                                         22U
#define LRFDRFE32_GPI_CALRES_GPI6_ONE                               0x00400000U
#define LRFDRFE32_GPI_CALRES_GPI6_ZERO                              0x00000000U

// Field:    [21] GPI5 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI5                                   0x00200000U
#define LRFDRFE32_GPI_CALRES_GPI5_M                                 0x00200000U
#define LRFDRFE32_GPI_CALRES_GPI5_S                                         21U
#define LRFDRFE32_GPI_CALRES_GPI5_ONE                               0x00200000U
#define LRFDRFE32_GPI_CALRES_GPI5_ZERO                              0x00000000U

// Field:    [20] GPI4 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI4                                   0x00100000U
#define LRFDRFE32_GPI_CALRES_GPI4_M                                 0x00100000U
#define LRFDRFE32_GPI_CALRES_GPI4_S                                         20U
#define LRFDRFE32_GPI_CALRES_GPI4_ONE                               0x00100000U
#define LRFDRFE32_GPI_CALRES_GPI4_ZERO                              0x00000000U

// Field:    [19] GPI3 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI3                                   0x00080000U
#define LRFDRFE32_GPI_CALRES_GPI3_M                                 0x00080000U
#define LRFDRFE32_GPI_CALRES_GPI3_S                                         19U
#define LRFDRFE32_GPI_CALRES_GPI3_ONE                               0x00080000U
#define LRFDRFE32_GPI_CALRES_GPI3_ZERO                              0x00000000U

// Field:    [18] GPI2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI2                                   0x00040000U
#define LRFDRFE32_GPI_CALRES_GPI2_M                                 0x00040000U
#define LRFDRFE32_GPI_CALRES_GPI2_S                                         18U
#define LRFDRFE32_GPI_CALRES_GPI2_ONE                               0x00040000U
#define LRFDRFE32_GPI_CALRES_GPI2_ZERO                              0x00000000U

// Field:    [17] GPI1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI1                                   0x00020000U
#define LRFDRFE32_GPI_CALRES_GPI1_M                                 0x00020000U
#define LRFDRFE32_GPI_CALRES_GPI1_S                                         17U
#define LRFDRFE32_GPI_CALRES_GPI1_ONE                               0x00020000U
#define LRFDRFE32_GPI_CALRES_GPI1_ZERO                              0x00000000U

// Field:    [16] GPI0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPI_CALRES_GPI0                                   0x00010000U
#define LRFDRFE32_GPI_CALRES_GPI0_M                                 0x00010000U
#define LRFDRFE32_GPI_CALRES_GPI0_S                                         16U
#define LRFDRFE32_GPI_CALRES_GPI0_ONE                               0x00010000U
#define LRFDRFE32_GPI_CALRES_GPI0_ZERO                              0x00000000U

// Field:   [9:4] MIDCODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_GPI_CALRES_MIDCODE_W                                       6U
#define LRFDRFE32_GPI_CALRES_MIDCODE_M                              0x000003F0U
#define LRFDRFE32_GPI_CALRES_MIDCODE_S                                       4U
#define LRFDRFE32_GPI_CALRES_MIDCODE_ALLONES                        0x000003F0U
#define LRFDRFE32_GPI_CALRES_MIDCODE_ALLZEROS                       0x00000000U

// Field:   [3:0] CRSCODE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_GPI_CALRES_CRSCODE_W                                       4U
#define LRFDRFE32_GPI_CALRES_CRSCODE_M                              0x0000000FU
#define LRFDRFE32_GPI_CALRES_CRSCODE_S                                       0U
#define LRFDRFE32_GPI_CALRES_CRSCODE_ALLONES                        0x0000000FU
#define LRFDRFE32_GPI_CALRES_CRSCODE_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_LIN2LOGOUT_MATHACCELIN
//
//*****************************************************************************
// Field: [22:16] LOGVAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_LOGVAL_W                            7U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_LOGVAL_M                   0x007F0000U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_LOGVAL_S                           16U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_LOGVAL_ALLONES             0x007F0000U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_LOGVAL_ALLZEROS            0x00000000U

// Field:  [15:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_VAL_W                              16U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_VAL_M                      0x0000FFFFU
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_VAL_S                               0U
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_VAL_ALLONES                0x0000FFFFU
#define LRFDRFE32_LIN2LOGOUT_MATHACCELIN_VAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TIMCTL_DIVBY3OUT
//
//*****************************************************************************
// Field: [29:24] CPTSRC 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTSRC_W                                  6U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTSRC_M                         0x3F000000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTSRC_S                                 24U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTSRC_ALLONES                   0x3F000000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTSRC_ALLZEROS                  0x00000000U

// Field:    [23] CPTCTL 
//
// ENUMs: 
// EN                       Enable counter capture mode 
// DIS                      Disable counter capture mode 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTCTL                           0x00800000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTCTL_M                         0x00800000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTCTL_S                                 23U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTCTL_EN                        0x00800000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CPTCTL_DIS                       0x00000000U

// Field: [22:21] CNTRSRC 
//
// ENUMs: 
// FREF                     Count FREF ticks 
// MAGN1                    Use magnitude estimator 1 data enable 
// MAGN0                    Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_W                                 2U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_M                        0x00600000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_S                                21U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_FREF                     0x00600000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_MAGN1                    0x00400000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_MAGN0                    0x00200000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRSRC_CLK                      0x00000000U

// Field:    [20] CNTRCLR 
//
// ENUMs: 
// ONE                      Clear counter value 
// ZERO                     No action 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCLR                          0x00100000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCLR_M                        0x00100000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCLR_S                                20U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCLR_ONE                      0x00100000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCLR_ZERO                     0x00000000U

// Field:    [19] CNTRCTL 
//
// ENUMs: 
// EN                       Enable counter 
// DIS                      Disable counter 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCTL                          0x00080000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCTL_M                        0x00080000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCTL_S                                19U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCTL_EN                       0x00080000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_CNTRCTL_DIS                      0x00000000U

// Field: [18:17] TIMSRC 
//
// ENUMs: 
// FREF                     Count FREF ticks 
// MAGN1                    Use magnitude estimator 1 data enable 
// MAGN0                    Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_W                                  2U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_M                         0x00060000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_S                                 17U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_FREF                      0x00060000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_MAGN1                     0x00040000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_MAGN0                     0x00020000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMSRC_CLK                       0x00000000U

// Field:    [16] TIMCTL 
//
// ENUMs: 
// EN                       Enable timer 
// DIS                      Disable timer and clear internal timer value 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMCTL                           0x00010000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMCTL_M                         0x00010000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMCTL_S                                 16U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMCTL_EN                        0x00010000U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_TIMCTL_DIS                       0x00000000U

// Field:   [3:0] DIV3 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMCTL_DIVBY3OUT_DIV3_W                                    4U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_DIV3_M                           0x0000000FU
#define LRFDRFE32_TIMCTL_DIVBY3OUT_DIV3_S                                    0U
#define LRFDRFE32_TIMCTL_DIVBY3OUT_DIV3_ALLONES                     0x0000000FU
#define LRFDRFE32_TIMCTL_DIVBY3OUT_DIV3_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TIMPER_TIMINC
//
//*****************************************************************************
// Field: [31:16] TIMPER_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMPER_TIMINC_TIMPER_VAL_W                                16U
#define LRFDRFE32_TIMPER_TIMINC_TIMPER_VAL_M                        0xFFFF0000U
#define LRFDRFE32_TIMPER_TIMINC_TIMPER_VAL_S                                16U
#define LRFDRFE32_TIMPER_TIMINC_TIMPER_VAL_ALLONES                  0xFFFF0000U
#define LRFDRFE32_TIMPER_TIMINC_TIMPER_VAL_ALLZEROS                 0x00000000U

// Field:  [15:0] TIMINC_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMPER_TIMINC_TIMINC_VAL_W                                16U
#define LRFDRFE32_TIMPER_TIMINC_TIMINC_VAL_M                        0x0000FFFFU
#define LRFDRFE32_TIMPER_TIMINC_TIMINC_VAL_S                                 0U
#define LRFDRFE32_TIMPER_TIMINC_TIMINC_VAL_ALLONES                  0x0000FFFFU
#define LRFDRFE32_TIMPER_TIMINC_TIMINC_VAL_ALLZEROS                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TIMCAPT_TIMCNT
//
//*****************************************************************************
// Field: [31:16] VALUE 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMCAPT_TIMCNT_VALUE_W                                    16U
#define LRFDRFE32_TIMCAPT_TIMCNT_VALUE_M                            0xFFFF0000U
#define LRFDRFE32_TIMCAPT_TIMCNT_VALUE_S                                    16U
#define LRFDRFE32_TIMCAPT_TIMCNT_VALUE_ALLONES                      0xFFFF0000U
#define LRFDRFE32_TIMCAPT_TIMCNT_VALUE_ALLZEROS                     0x00000000U

// Field:  [15:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TIMCAPT_TIMCNT_VAL_W                                      16U
#define LRFDRFE32_TIMCAPT_TIMCNT_VAL_M                              0x0000FFFFU
#define LRFDRFE32_TIMCAPT_TIMCNT_VAL_S                                       0U
#define LRFDRFE32_TIMCAPT_TIMCNT_VAL_ALLONES                        0x0000FFFFU
#define LRFDRFE32_TIMCAPT_TIMCNT_VAL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TRCSTAT_TRCCTRL
//
//*****************************************************************************
// Field:    [16] BUSY 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_TRCSTAT_TRCCTRL_BUSY                              0x00010000U
#define LRFDRFE32_TRCSTAT_TRCCTRL_BUSY_M                            0x00010000U
#define LRFDRFE32_TRCSTAT_TRCCTRL_BUSY_S                                    16U
#define LRFDRFE32_TRCSTAT_TRCCTRL_BUSY_ONE                          0x00010000U
#define LRFDRFE32_TRCSTAT_TRCCTRL_BUSY_ZERO                         0x00000000U

// Field:     [0] SEND 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_TRCSTAT_TRCCTRL_SEND                              0x00000001U
#define LRFDRFE32_TRCSTAT_TRCCTRL_SEND_M                            0x00000001U
#define LRFDRFE32_TRCSTAT_TRCCTRL_SEND_S                                     0U
#define LRFDRFE32_TRCSTAT_TRCCTRL_SEND_ONE                          0x00000001U
#define LRFDRFE32_TRCSTAT_TRCCTRL_SEND_ZERO                         0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_TRCPAR0_TRCCMD
//
//*****************************************************************************
// Field: [31:16] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TRCPAR0_TRCCMD_VAL_W                                      16U
#define LRFDRFE32_TRCPAR0_TRCCMD_VAL_M                              0xFFFF0000U
#define LRFDRFE32_TRCPAR0_TRCCMD_VAL_S                                      16U
#define LRFDRFE32_TRCPAR0_TRCCMD_VAL_ALLONES                        0xFFFF0000U
#define LRFDRFE32_TRCPAR0_TRCCMD_VAL_ALLZEROS                       0x00000000U

// Field:   [9:8] PARCNT 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TRCPAR0_TRCCMD_PARCNT_W                                    2U
#define LRFDRFE32_TRCPAR0_TRCCMD_PARCNT_M                           0x00000300U
#define LRFDRFE32_TRCPAR0_TRCCMD_PARCNT_S                                    8U
#define LRFDRFE32_TRCPAR0_TRCCMD_PARCNT_ALLONES                     0x00000300U
#define LRFDRFE32_TRCPAR0_TRCCMD_PARCNT_ALLZEROS                    0x00000000U

// Field:   [7:0] PKTHDR 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_TRCPAR0_TRCCMD_PKTHDR_W                                    8U
#define LRFDRFE32_TRCPAR0_TRCCMD_PKTHDR_M                           0x000000FFU
#define LRFDRFE32_TRCPAR0_TRCCMD_PKTHDR_S                                    0U
#define LRFDRFE32_TRCPAR0_TRCCMD_PKTHDR_ALLONES                     0x000000FFU
#define LRFDRFE32_TRCPAR0_TRCCMD_PKTHDR_ALLZEROS                    0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_GPOCTL_TRCPAR1
//
//*****************************************************************************
// Field:    [31] SEL7 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO7 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL7                               0x80000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL7_M                             0x80000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL7_S                                     31U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL7_HW                            0x80000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL7_SW                            0x00000000U

// Field:    [30] SEL6 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO6 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL6                               0x40000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL6_M                             0x40000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL6_S                                     30U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL6_HW                            0x40000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL6_SW                            0x00000000U

// Field:    [29] SEL5 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO5 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL5                               0x20000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL5_M                             0x20000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL5_S                                     29U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL5_HW                            0x20000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL5_SW                            0x00000000U

// Field:    [28] SEL4 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO4 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL4                               0x10000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL4_M                             0x10000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL4_S                                     28U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL4_HW                            0x10000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL4_SW                            0x00000000U

// Field:    [27] SEL3 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO3 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL3                               0x08000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL3_M                             0x08000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL3_S                                     27U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL3_HW                            0x08000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL3_SW                            0x00000000U

// Field:    [26] SEL2 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO2 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL2                               0x04000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL2_M                             0x04000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL2_S                                     26U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL2_HW                            0x04000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL2_SW                            0x00000000U

// Field:    [25] SEL1 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO1 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL1                               0x02000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL1_M                             0x02000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL1_S                                     25U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL1_HW                            0x02000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL1_SW                            0x00000000U

// Field:    [24] SEL0 
//
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO0 
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL0                               0x01000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL0_M                             0x01000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL0_S                                     24U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL0_HW                            0x01000000U
#define LRFDRFE32_GPOCTL_TRCPAR1_SEL0_SW                            0x00000000U

// Field:    [23] GPO7 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO7                               0x00800000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO7_M                             0x00800000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO7_S                                     23U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO7_ONE                           0x00800000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO7_ZERO                          0x00000000U

// Field:    [22] GPO6 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO6                               0x00400000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO6_M                             0x00400000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO6_S                                     22U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO6_ONE                           0x00400000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO6_ZERO                          0x00000000U

// Field:    [21] GPO5 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO5                               0x00200000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO5_M                             0x00200000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO5_S                                     21U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO5_ONE                           0x00200000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO5_ZERO                          0x00000000U

// Field:    [20] GPO4 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO4                               0x00100000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO4_M                             0x00100000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO4_S                                     20U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO4_ONE                           0x00100000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO4_ZERO                          0x00000000U

// Field:    [19] GPO3 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO3                               0x00080000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO3_M                             0x00080000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO3_S                                     19U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO3_ONE                           0x00080000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO3_ZERO                          0x00000000U

// Field:    [18] GPO2 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO2                               0x00040000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO2_M                             0x00040000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO2_S                                     18U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO2_ONE                           0x00040000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO2_ZERO                          0x00000000U

// Field:    [17] GPO1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO1                               0x00020000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO1_M                             0x00020000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO1_S                                     17U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO1_ONE                           0x00020000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO1_ZERO                          0x00000000U

// Field:    [16] GPO0 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO0                               0x00010000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO0_M                             0x00010000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO0_S                                     16U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO0_ONE                           0x00010000U
#define LRFDRFE32_GPOCTL_TRCPAR1_GPO0_ZERO                          0x00000000U

// Field:  [15:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_GPOCTL_TRCPAR1_VAL_W                                      16U
#define LRFDRFE32_GPOCTL_TRCPAR1_VAL_M                              0x0000FFFFU
#define LRFDRFE32_GPOCTL_TRCPAR1_VAL_S                                       0U
#define LRFDRFE32_GPOCTL_TRCPAR1_VAL_ALLONES                        0x0000FFFFU
#define LRFDRFE32_GPOCTL_TRCPAR1_VAL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DIVCTL_ANAISOCTL
//
//*****************************************************************************
// Field:    [31] DIV2PH180 
//
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH180                        0x80000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH180_M                      0x80000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH180_S                              31U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH180_EN                     0x80000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH180_DIS                    0x00000000U

// Field:    [30] DIV2PH0 
//
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH0                          0x40000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH0_M                        0x40000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH0_S                                30U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH0_EN                       0x40000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH0_DIS                      0x00000000U

// Field:    [29] DIV2PH270 
//
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH270                        0x20000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH270_M                      0x20000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH270_S                              29U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH270_EN                     0x20000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH270_DIS                    0x00000000U

// Field:    [28] DIV2PH90 
//
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH90                         0x10000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH90_M                       0x10000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH90_S                               28U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH90_EN                      0x10000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2PH90_DIS                     0x00000000U

// Field:    [27] SPARE11 
//
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is 0 
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE11                          0x08000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE11_M                        0x08000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE11_S                                27U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE11_ONE                      0x08000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE11_ZERO                     0x00000000U

// Field:    [26] S1G20DBMMUX 
//
// ENUMs: 
// DISABLE                  Disable mux 
// ENABLEN                  Enable mux 
#define LRFDRFE32_DIVCTL_ANAISOCTL_S1G20DBMMUX                      0x04000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_S1G20DBMMUX_M                    0x04000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_S1G20DBMMUX_S                            26U
#define LRFDRFE32_DIVCTL_ANAISOCTL_S1G20DBMMUX_DISABLE              0x04000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_S1G20DBMMUX_ENABLEN              0x00000000U

// Field:    [25] ADCDIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIV                           0x02000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIV_M                         0x02000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIV_S                                 25U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIV_EN                        0x02000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIV_DIS                       0x00000000U

// Field:    [24] ENSYNTH 
//
// ENUMs: 
// EN                       Clock is enabled 
// DIS                      Clock is disabled 
#define LRFDRFE32_DIVCTL_ANAISOCTL_ENSYNTH                          0x01000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ENSYNTH_M                        0x01000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ENSYNTH_S                                24U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ENSYNTH_EN                       0x01000000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ENSYNTH_DIS                      0x00000000U

// Field:    [23] TXPH18020DBMDIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH18020DBMDIV                  0x00800000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH18020DBMDIV_M                0x00800000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH18020DBMDIV_S                        23U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH18020DBMDIV_EN               0x00800000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH18020DBMDIV_DIS              0x00000000U

// Field:    [22] TXPH020DBMDIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH020DBMDIV                    0x00400000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH020DBMDIV_M                  0x00400000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH020DBMDIV_S                          22U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH020DBMDIV_EN                 0x00400000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH020DBMDIV_DIS                0x00000000U

// Field:    [21] TXPH180DIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH180DIV                       0x00200000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH180DIV_M                     0x00200000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH180DIV_S                             21U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH180DIV_EN                    0x00200000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH180DIV_DIS                   0x00000000U

// Field:    [20] TXPH0DIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH0DIV                         0x00100000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH0DIV_M                       0x00100000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH0DIV_S                               20U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH0DIV_EN                      0x00100000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_TXPH0DIV_DIS                     0x00000000U

// Field:    [19] RXPH90DIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH90DIV                        0x00080000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH90DIV_M                      0x00080000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH90DIV_S                              19U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH90DIV_EN                     0x00080000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH90DIV_DIS                    0x00000000U

// Field:    [18] RXPH0DIV 
//
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH0DIV                         0x00040000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH0DIV_M                       0x00040000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH0DIV_S                               18U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH0DIV_EN                      0x00040000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_RXPH0DIV_DIS                     0x00000000U

// Field:    [17] Spare1 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE1                           0x00020000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE1_M                         0x00020000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE1_S                                 17U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE1_ONE                       0x00020000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_SPARE1_ZERO                      0x00000000U

// Field:    [16] EN 
//
// ENUMs: 
// ON                       Enable divider 
// OFF                      Disable divider 
#define LRFDRFE32_DIVCTL_ANAISOCTL_EN                               0x00010000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_EN_M                             0x00010000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_EN_S                                     16U
#define LRFDRFE32_DIVCTL_ANAISOCTL_EN_ON                            0x00010000U
#define LRFDRFE32_DIVCTL_ANAISOCTL_EN_OFF                           0x00000000U

// Field:     [4] ADCDIGRSTN 
//
// ENUMs: 
// ACTIVE                   Don't reset 
// RESET                    Reset 
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIGRSTN                       0x00000010U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIGRSTN_M                     0x00000010U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIGRSTN_S                              4U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIGRSTN_ACTIVE                0x00000010U
#define LRFDRFE32_DIVCTL_ANAISOCTL_ADCDIGRSTN_RESET                 0x00000000U

// Field:     [3] IFADC2SVTISO 
//
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE32_DIVCTL_ANAISOCTL_IFADC2SVTISO                     0x00000008U
#define LRFDRFE32_DIVCTL_ANAISOCTL_IFADC2SVTISO_M                   0x00000008U
#define LRFDRFE32_DIVCTL_ANAISOCTL_IFADC2SVTISO_S                            3U
#define LRFDRFE32_DIVCTL_ANAISOCTL_IFADC2SVTISO_ISOLATE             0x00000008U
#define LRFDRFE32_DIVCTL_ANAISOCTL_IFADC2SVTISO_CONNECT             0x00000000U

// Field:     [2] DIV2IFADCISO 
//
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2IFADCISO                     0x00000004U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2IFADCISO_M                   0x00000004U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2IFADCISO_S                            2U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2IFADCISO_ISOLATE             0x00000004U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2IFADCISO_CONNECT             0x00000000U

// Field:     [1] MTDC2SVTISO 
//
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE32_DIVCTL_ANAISOCTL_MTDC2SVTISO                      0x00000002U
#define LRFDRFE32_DIVCTL_ANAISOCTL_MTDC2SVTISO_M                    0x00000002U
#define LRFDRFE32_DIVCTL_ANAISOCTL_MTDC2SVTISO_S                             1U
#define LRFDRFE32_DIVCTL_ANAISOCTL_MTDC2SVTISO_ISOLATE              0x00000002U
#define LRFDRFE32_DIVCTL_ANAISOCTL_MTDC2SVTISO_CONNECT              0x00000000U

// Field:     [0] DIV2MTDCISO 
//
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2MTDCISO                      0x00000001U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2MTDCISO_M                    0x00000001U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2MTDCISO_S                             0U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2MTDCISO_ISOLATE              0x00000001U
#define LRFDRFE32_DIVCTL_ANAISOCTL_DIV2MTDCISO_CONNECT              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MAGNACC0_RXCTRL
//
//*****************************************************************************
// Field: [31:16] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_MAGNACC0_RXCTRL_VAL_W                                     16U
#define LRFDRFE32_MAGNACC0_RXCTRL_VAL_M                             0xFFFF0000U
#define LRFDRFE32_MAGNACC0_RXCTRL_VAL_S                                     16U
#define LRFDRFE32_MAGNACC0_RXCTRL_VAL_ALLONES                       0xFFFF0000U
#define LRFDRFE32_MAGNACC0_RXCTRL_VAL_ALLZEROS                      0x00000000U

// Field:    [12] SPARE 
//
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE32_MAGNACC0_RXCTRL_SPARE                             0x00001000U
#define LRFDRFE32_MAGNACC0_RXCTRL_SPARE_M                           0x00001000U
#define LRFDRFE32_MAGNACC0_RXCTRL_SPARE_S                                   12U
#define LRFDRFE32_MAGNACC0_RXCTRL_SPARE_ONE                         0x00001000U
#define LRFDRFE32_MAGNACC0_RXCTRL_SPARE_ZERO                        0x00000000U

// Field:  [11:9] ATTN 
//
// ENUMs: 
// _21DB                    21dB attenuation 
// _18DB                    18dB attenuation 
// _15DB                    15dB attenuation 
// _12DB                    12dB attenuation 
// _9DB                     9dB attenuation 
// _6DB                     6dB attenuation 
// _3DB                     3dB attenuation 
// NOATT                    No attenuation 
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN_W                                     3U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN_M                            0x00000E00U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN_S                                     9U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__21DB                        0x00000E00U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__18DB                        0x00000C00U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__15DB                        0x00000A00U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__12DB                        0x00000800U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__9DB                         0x00000600U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__6DB                         0x00000400U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN__3DB                         0x00000200U
#define LRFDRFE32_MAGNACC0_RXCTRL_ATTN_NOATT                        0x00000000U

// Field:   [8:4] IFAMPGC 
//
// ENUMs: 
// MAX                      Set IFAMP gain to MAX 
// MIN3DB                   Set gain to MAX - 3 dB 
// MIN6DB                   Set gain to MAX - 6 dB 
// MIN9DB                   Set gain to MAX - 9 dB 
// MIN12DB                  Set gain to MAX - 12 dB 
// MIN15DB                  Set gain to MAX - 15 dB 
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_W                                  5U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_M                         0x000001F0U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_S                                  4U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MAX                       0x000001F0U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MIN3DB                    0x000000F0U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MIN6DB                    0x00000070U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MIN9DB                    0x00000030U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MIN12DB                   0x00000010U
#define LRFDRFE32_MAGNACC0_RXCTRL_IFAMPGC_MIN15DB                   0x00000000U

// Field:   [3:0] LNAGAIN 
//
// ENUMs: 
// MAX                      Set gain to MAX 
// MIN3DB                   Set gain to MAX - 3 dB 
// MIN6DB                   Set gain to MAX - 6 dB 
// MIN9DB                   Set gain to MAX - 9 dB 
// MIN12DB                  Set gain to MAX - 12 dB 
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_W                                  4U
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_M                         0x0000000FU
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_S                                  0U
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_MAX                       0x0000000FU
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_MIN3DB                    0x00000007U
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_MIN6DB                    0x00000003U
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_MIN9DB                    0x00000001U
#define LRFDRFE32_MAGNACC0_RXCTRL_LNAGAIN_MIN12DB                   0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_RSSI_MAGNACC1
//
//*****************************************************************************
// Field: [23:16] RSSI_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_RSSI_MAGNACC1_RSSI_VAL_W                                   8U
#define LRFDRFE32_RSSI_MAGNACC1_RSSI_VAL_M                          0x00FF0000U
#define LRFDRFE32_RSSI_MAGNACC1_RSSI_VAL_S                                  16U
#define LRFDRFE32_RSSI_MAGNACC1_RSSI_VAL_ALLONES                    0x00FF0000U
#define LRFDRFE32_RSSI_MAGNACC1_RSSI_VAL_ALLZEROS                   0x00000000U

// Field:  [15:0] MAGNACC1_VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_RSSI_MAGNACC1_MAGNACC1_VAL_W                              16U
#define LRFDRFE32_RSSI_MAGNACC1_MAGNACC1_VAL_M                      0x0000FFFFU
#define LRFDRFE32_RSSI_MAGNACC1_MAGNACC1_VAL_S                               0U
#define LRFDRFE32_RSSI_MAGNACC1_MAGNACC1_VAL_ALLONES                0x0000FFFFU
#define LRFDRFE32_RSSI_MAGNACC1_MAGNACC1_VAL_ALLZEROS               0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_RFGAIN_RSSIMAX
//
//*****************************************************************************
// Field: [23:16] DBGAIN 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_RFGAIN_RSSIMAX_DBGAIN_W                                    8U
#define LRFDRFE32_RFGAIN_RSSIMAX_DBGAIN_M                           0x00FF0000U
#define LRFDRFE32_RFGAIN_RSSIMAX_DBGAIN_S                                   16U
#define LRFDRFE32_RFGAIN_RSSIMAX_DBGAIN_ALLONES                     0x00FF0000U
#define LRFDRFE32_RFGAIN_RSSIMAX_DBGAIN_ALLZEROS                    0x00000000U

// Field:   [7:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_RFGAIN_RSSIMAX_VAL_W                                       8U
#define LRFDRFE32_RFGAIN_RSSIMAX_VAL_M                              0x000000FFU
#define LRFDRFE32_RFGAIN_RSSIMAX_VAL_S                                       0U
#define LRFDRFE32_RFGAIN_RSSIMAX_VAL_ALLONES                        0x000000FFU
#define LRFDRFE32_RFGAIN_RSSIMAX_VAL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DIVSTA_IFADCSTAT
//
//*****************************************************************************
// Field:    [16] STAT 
//
// ENUMs: 
// BUSY                     Serial divider is busy and result is not available 
//                          yet 
// IDLE                     Serial divider is idle 
#define LRFDRFE32_DIVSTA_IFADCSTAT_STAT                             0x00010000U
#define LRFDRFE32_DIVSTA_IFADCSTAT_STAT_M                           0x00010000U
#define LRFDRFE32_DIVSTA_IFADCSTAT_STAT_S                                   16U
#define LRFDRFE32_DIVSTA_IFADCSTAT_STAT_BUSY                        0x00010000U
#define LRFDRFE32_DIVSTA_IFADCSTAT_STAT_IDLE                        0x00000000U

// Field:   [6:2] QUANTCALVAL 
//
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALVAL_W                             5U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALVAL_M                    0x0000007CU
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALVAL_S                             2U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALVAL_COMP1                0x00000004U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALVAL_COMP0                0x00000000U

// Field:     [1] QUANTCALDONE 
//
// ENUMs: 
// READY                    Calibration is complete 
// NOT_READY                Calibration is not finished 
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALDONE                     0x00000002U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALDONE_M                   0x00000002U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALDONE_S                            1U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALDONE_READY               0x00000002U
#define LRFDRFE32_DIVSTA_IFADCSTAT_QUANTCALDONE_NOT_READY           0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DIVIDEND
//
//*****************************************************************************
// Field:  [31:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DIVIDEND_VAL_W                                            32U
#define LRFDRFE32_DIVIDEND_VAL_M                                    0xFFFFFFFFU
#define LRFDRFE32_DIVIDEND_VAL_S                                             0U
#define LRFDRFE32_DIVIDEND_VAL_ALLONES                              0x0000FFFFU
#define LRFDRFE32_DIVIDEND_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_DIVISOR
//
//*****************************************************************************
// Field:  [31:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_DIVISOR_VAL_W                                             32U
#define LRFDRFE32_DIVISOR_VAL_M                                     0xFFFFFFFFU
#define LRFDRFE32_DIVISOR_VAL_S                                              0U
#define LRFDRFE32_DIVISOR_VAL_ALLONES                               0x0000FFFFU
#define LRFDRFE32_DIVISOR_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_QUOTIENT
//
//*****************************************************************************
// Field:  [31:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_QUOTIENT_VAL_W                                            32U
#define LRFDRFE32_QUOTIENT_VAL_M                                    0xFFFFFFFFU
#define LRFDRFE32_QUOTIENT_VAL_S                                             0U
#define LRFDRFE32_QUOTIENT_VAL_ALLONES                              0x0000FFFFU
#define LRFDRFE32_QUOTIENT_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_PRODUCT
//
//*****************************************************************************
// Field:  [31:0] VAL 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE32_PRODUCT_VAL_W                                             32U
#define LRFDRFE32_PRODUCT_VAL_M                                     0xFFFFFFFFU
#define LRFDRFE32_PRODUCT_VAL_S                                              0U
#define LRFDRFE32_PRODUCT_VAL_ALLONES                               0x0000FFFFU
#define LRFDRFE32_PRODUCT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MULTSTA
//
//*****************************************************************************
// Field:     [0] STAT 
//
// ENUMs: 
// BUSY                     Multiplier is busy, result is not ready yet 
// IDLE                     Multiplier is idle 
#define LRFDRFE32_MULTSTA_STAT                                      0x00000001U
#define LRFDRFE32_MULTSTA_STAT_M                                    0x00000001U
#define LRFDRFE32_MULTSTA_STAT_S                                             0U
#define LRFDRFE32_MULTSTA_STAT_BUSY                                 0x00000001U
#define LRFDRFE32_MULTSTA_STAT_IDLE                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDRFE32_O_MULTCFG
//
//*****************************************************************************
// Field:     [0] MODE 
//
// ENUMs: 
// SIGNED                   Multiplier assumes inputs are signed numbers 
// UNSIGNED                 Multiplier assumes inputs are unsigned numbers 
#define LRFDRFE32_MULTCFG_MODE                                      0x00000001U
#define LRFDRFE32_MULTCFG_MODE_M                                    0x00000001U
#define LRFDRFE32_MULTCFG_MODE_S                                             0U
#define LRFDRFE32_MULTCFG_MODE_SIGNED                               0x00000001U
#define LRFDRFE32_MULTCFG_MODE_UNSIGNED                             0x00000000U


#endif // __LRFDRFE32__
