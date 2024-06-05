/******************************************************************************
*  Filename:       hw_lrfdrfe_h
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

#ifndef __HW_LRFDRFE_H__
#define __HW_LRFDRFE_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDRFE component
//
//*****************************************************************************
// RF Engine Enable Register 
#define LRFDRFE_O_ENABLE                                            0x00000000U

// RFE Program Source Select Register 
#define LRFDRFE_O_FWSRC                                             0x00000004U

// RF Engine Initialization Register 
#define LRFDRFE_O_INIT                                              0x00000008U

// RF Engine Power-down Register 
#define LRFDRFE_O_PDREQ                                             0x0000000CU

// RFE Event Flag Register 0 
#define LRFDRFE_O_EVT0                                              0x00000010U

// RFE Event Flag Register 1 
#define LRFDRFE_O_EVT1                                              0x00000014U

// RFE Event Mask Register 0 
#define LRFDRFE_O_EVTMSK0                                           0x00000018U

// RFE Event Mask Register 1 
#define LRFDRFE_O_EVTMSK1                                           0x0000001CU

// RFE Event Clear Register 0 
#define LRFDRFE_O_EVTCLR0                                           0x00000020U

// RFE Event Clear Register 1 
#define LRFDRFE_O_EVTCLR1                                           0x00000024U

// Status of the HFXT 
#define LRFDRFE_O_HFXTSTAT                                          0x00000028U

// RF state indication 
#define LRFDRFE_O_RFSTATE                                           0x00000030U

// RFE API Command Register 
#define LRFDRFE_O_API                                               0x00000048U

// RFE Command Parameter 0 
#define LRFDRFE_O_CMDPAR0                                           0x0000004CU

// RFE Command Parameter 1 
#define LRFDRFE_O_CMDPAR1                                           0x00000050U

// RFE Command Status and Message Box Register 
#define LRFDRFE_O_MSGBOX                                            0x00000054U

// RFE-to-MCE Send Data Register 
#define LRFDRFE_O_MCEDATOUT0                                        0x00000058U

// MCE-to-RFE Receive Data Register 
#define LRFDRFE_O_MCEDATIN0                                         0x0000005CU

// RFE-to-MCE Send Command Register 
#define LRFDRFE_O_MCECMDOUT                                         0x00000060U

// MCE-to-RFE Receive Command Register 
#define LRFDRFE_O_MCECMDIN                                          0x00000064U

// RFE-to-PBE Send Data Register 
#define LRFDRFE_O_PBEDATOUT0                                        0x00000068U

// PBE-to-RFE Receive Data Register 
#define LRFDRFE_O_PBEDATIN0                                         0x0000006CU

// RFE-to-PBE Send Command Register 
#define LRFDRFE_O_PBECMDOUT                                         0x00000070U

// PBE-to-RFE Receive Command Register 
#define LRFDRFE_O_PBECMDIN                                          0x00000074U

// RFE FW Strobe Register 
#define LRFDRFE_O_STRB                                              0x00000078U

// Controls automatic comparison of magnitude with threshold 
#define LRFDRFE_O_MAGNTHRCFG                                        0x00000080U

// Threshold to compare the magnacc amplitude with, which accumulator is used 
// in the compare is controled by MAGNTHRCFG 
#define LRFDRFE_O_MAGNTHR                                           0x00000084U

// RSSI Offset Adjustment Register 
#define LRFDRFE_O_RSSIOFFSET                                        0x00000088U

// Gain Control Register 
#define LRFDRFE_O_GAINCTL                                           0x0000008CU

// Magnitude estimator 0 control register 
#define LRFDRFE_O_MAGNCTL0                                          0x00000090U

// Magnitude estimator 1 control register 
#define LRFDRFE_O_MAGNCTL1                                          0x00000094U

// Spare Value 
#define LRFDRFE_O_SPARE0                                            0x00000098U

// Spare Value 
#define LRFDRFE_O_SPARE1                                            0x0000009CU

// Spare Value 
#define LRFDRFE_O_SPARE2                                            0x000000A0U

// Spare Value 
#define LRFDRFE_O_SPARE3                                            0x000000A4U

// Spare Value 
#define LRFDRFE_O_SPARE4                                            0x000000A8U

// Spare Value 
#define LRFDRFE_O_SPARE5                                            0x000000ACU

// LNA control 
#define LRFDRFE_O_LNA                                               0x000000B0U

// IFAMPRFLDO control 
#define LRFDRFE_O_IFAMPRFLDO                                        0x000000B4U

// PA control register 
#define LRFDRFE_O_PA0                                               0x000000B8U

// PA control register 
#define LRFDRFE_O_PA1                                               0x000000BCU

// ULNA control, TRX only 
#define LRFDRFE_O_ULNA                                              0x000000C0U

// IFADC0 configuration register 
#define LRFDRFE_O_IFADC0                                            0x000000C4U

// IFADC configuration register 
#define LRFDRFE_O_IFADC1                                            0x000000C8U

// IFADC configuration register 
#define LRFDRFE_O_IFADCLF                                           0x000000CCU

// IFADC configuration register 
#define LRFDRFE_O_IFADCQUANT                                        0x000000D0U

// IFADC configuration register 
#define LRFDRFE_O_IFADCALDO                                         0x000000D4U

// IFADCLDO configuration register 
#define LRFDRFE_O_IFADCDLDO                                         0x000000D8U

// IFADCTST configuration register 
#define LRFDRFE_O_IFADCTST                                          0x000000DCU

// Analog test register 
#define LRFDRFE_O_ATSTREFL                                          0x000000E0U

// Analog test register 
#define LRFDRFE_O_ATSTREFH                                          0x000000E4U

// DCO Control 
#define LRFDRFE_O_DCO                                               0x000000E8U

// Divider Control 
#define LRFDRFE_O_DIV                                               0x000000ECU

// LDO control 
#define LRFDRFE_O_DIVLDO                                            0x000000F0U

// LDO control 
#define LRFDRFE_O_TDCLDO                                            0x000000F4U

// LDO control 
#define LRFDRFE_O_DCOLDO0                                           0x000000F8U

// LDO control 
#define LRFDRFE_O_DCOLDO1                                           0x000000FCU

// Predivider configuration 
#define LRFDRFE_O_PRE0                                              0x00000100U

// Predivider configuration 
#define LRFDRFE_O_PRE1                                              0x00000104U

// Predivider configuration 
#define LRFDRFE_O_PRE2                                              0x00000108U

// Predivider configuration 
#define LRFDRFE_O_PRE3                                              0x0000010CU

// Calibration Configuration 0 
#define LRFDRFE_O_CAL0                                              0x00000110U

// Calibration Configuration 1 
#define LRFDRFE_O_CAL1                                              0x00000114U

// Calibration Configuration 2 
#define LRFDRFE_O_CAL2                                              0x00000118U

// Calibration Configuration 3 
#define LRFDRFE_O_CAL3                                              0x0000011CU

// SDM and Delay Configuration 
#define LRFDRFE_O_MISC0                                             0x00000120U

// SDM and Delay Configuration 
#define LRFDRFE_O_MISC1                                             0x00000124U

// Loop Filter Configuration 
#define LRFDRFE_O_LF0                                               0x00000128U

// Loop Filter Configuration 
#define LRFDRFE_O_LF1                                               0x0000012CU

// Phase Configuration 
#define LRFDRFE_O_PHEDISC                                           0x00000130U

// Phase Configuration 
#define LRFDRFE_O_PHINIT                                            0x00000134U

// PLL Monitor Configuration 
#define LRFDRFE_O_PLLMON0                                           0x00000138U

// PLL Monitor Configuration 
#define LRFDRFE_O_PLLMON1                                           0x0000013CU

// Modulator Configuration 
#define LRFDRFE_O_MOD0                                              0x00000140U

// Modulator Configuration 
#define LRFDRFE_O_MOD1                                              0x00000144U

// Digital TX Configuration 0 
#define LRFDRFE_O_DTX0                                              0x00000148U

// Digital TX Configuration 1 
#define LRFDRFE_O_DTX1                                              0x0000014CU

// Digital TX Configuration 2 
#define LRFDRFE_O_DTX2                                              0x00000150U

// Digital TX Configuration 3 
#define LRFDRFE_O_DTX3                                              0x00000154U

// Digital TX Configuration 4 
#define LRFDRFE_O_DTX4                                              0x00000158U

// Digital TX Configuration 5 
#define LRFDRFE_O_DTX5                                              0x0000015CU

// Digital TX Configuration 6 
#define LRFDRFE_O_DTX6                                              0x00000160U

// Digital TX Configuration 7 
#define LRFDRFE_O_DTX7                                              0x00000164U

// Digital TX Configuration 8 
#define LRFDRFE_O_DTX8                                              0x00000168U

// Digital TX Configuration 9 
#define LRFDRFE_O_DTX9                                              0x0000016CU

// Digital TX Configuration 10 
#define LRFDRFE_O_DTX10                                             0x00000170U

// Digital TX Configuration 11 
#define LRFDRFE_O_DTX11                                             0x00000174U

// PLL M0 
#define LRFDRFE_O_PLLM0L                                            0x00000178U

// PLL M0 
#define LRFDRFE_O_PLLM0H                                            0x0000017CU

// PLL M1 
#define LRFDRFE_O_PLLM1L                                            0x00000180U

// PLL M1 
#define LRFDRFE_O_PLLM1H                                            0x00000184U

// Calibration M 
#define LRFDRFE_O_CALMCRS                                           0x00000188U

// Calibration M 
#define LRFDRFE_O_CALMMID                                           0x0000018CU

// REFCLK Prescaler Load Value 
#define LRFDRFE_O_REFDIV                                            0x00000190U

// DLO control register 0 
#define LRFDRFE_O_DLOCTL0                                           0x00000198U

// DLO control register 1 
#define LRFDRFE_O_DLOCTL1                                           0x000001A0U

// DCO Override 
#define LRFDRFE_O_DCOOVR0                                           0x000001A8U

// DCO Override 
#define LRFDRFE_O_DCOOVR1                                           0x000001ACU

// Data test 
#define LRFDRFE_O_DTST                                              0x000001B0U

// FSM and IRQ flags 
#define LRFDRFE_O_DLOEV                                             0x000001B4U

// DTST read 
#define LRFDRFE_O_DTSTRD                                            0x000001B8U

// DCO frequency span 
#define LRFDRFE_O_FDCOSPANLSB                                       0x000001BCU

// DCO frequency span 
#define LRFDRFE_O_FDCOSPANMSB                                       0x000001C0U

// TDC Calibration 
#define LRFDRFE_O_TDCCAL                                            0x000001C4U

// Calibration Code 
#define LRFDRFE_O_CALRES                                            0x000001C8U

// RFE Direct GPI Status 
#define LRFDRFE_O_GPI                                               0x000001CCU

// Math accellerator input value 
#define LRFDRFE_O_MATHACCELIN                                       0x000001D0U

// Lin2Log output register 
#define LRFDRFE_O_LIN2LOGOUT                                        0x000001D4U

// Divide by three output register 
#define LRFDRFE_O_DIVBY3OUT                                         0x000001D8U

// RFE Timer and Counter Control Register 
#define LRFDRFE_O_TIMCTL                                            0x000001DCU

// RFE Counter Increment Configuration 
#define LRFDRFE_O_TIMINC                                            0x000001E0U

// RFE Timer/Counter Period Configuration 
#define LRFDRFE_O_TIMPER                                            0x000001E4U

// RFE Counter Value 
#define LRFDRFE_O_TIMCNT                                            0x000001E8U

// RFE Counter Capture Value 
#define LRFDRFE_O_TIMCAPT                                           0x000001ECU

// RFE Tracer Send Trigger Register 
#define LRFDRFE_O_TRCCTRL                                           0x000001F0U

// RFE Tracer Status Register 
#define LRFDRFE_O_TRCSTAT                                           0x000001F4U

// RFE Tracer Commmand Register 
#define LRFDRFE_O_TRCCMD                                            0x000001F8U

// RFE Tracer Command Parameter Register 0 
#define LRFDRFE_O_TRCPAR0                                           0x000001FCU

// RFE Tracer Command Parameter Register 1 
#define LRFDRFE_O_TRCPAR1                                           0x00000200U

// RFE Direct GPO control register 
#define LRFDRFE_O_GPOCTL                                            0x00000204U

// Analog Isolation Control 
#define LRFDRFE_O_ANAISOCTL                                         0x00000208U

// Divider Control 
#define LRFDRFE_O_DIVCTL                                            0x0000020CU

// RX Frontend control register 
#define LRFDRFE_O_RXCTRL                                            0x00000210U

// Magnitude estimator 0 accumulator value 
#define LRFDRFE_O_MAGNACC0                                          0x00000214U

// Magnitude estimator 1 accumulator value 
#define LRFDRFE_O_MAGNACC1                                          0x00000218U

// RSSI Value Register 
#define LRFDRFE_O_RSSI                                              0x0000021CU

// RSSI Maximum Value Register 
#define LRFDRFE_O_RSSIMAX                                           0x00000220U

// RF front-end gain value 
#define LRFDRFE_O_RFGAIN                                            0x00000224U

// IFADC status 
#define LRFDRFE_O_IFADCSTAT                                         0x00000228U

// Serial Divider Status Register 
#define LRFDRFE_O_DIVSTA                                            0x0000022CU

// Serial Divider Dividend Register 
#define LRFDRFE_O_DIVIDENDL                                         0x00000230U

// Serial Divider Dividend Register 
#define LRFDRFE_O_DIVIDENDH                                         0x00000234U

// Serial Divider Divisor Register 
#define LRFDRFE_O_DIVISORL                                          0x00000238U

// Serial Divider Divisor Register 
#define LRFDRFE_O_DIVISORH                                          0x0000023CU

// Serial Divider Quotient Register 
#define LRFDRFE_O_QUOTIENTL                                         0x00000240U

// Serial Divider Quotient Register 
#define LRFDRFE_O_QUOTIENTH                                         0x00000244U

// Product of DIVISORL_VAL_LSB and DIVISORH_VAL_MSB 
#define LRFDRFE_O_PRODUCTL                                          0x00000248U

// Product of DIVISORL_VAL_LSB and DIVISORH_VAL_MSB 
#define LRFDRFE_O_PRODUCTH                                          0x0000024CU

// Serial Multiplier Status Register 
#define LRFDRFE_O_MULTSTA                                           0x00000250U

// Serial Multiplier Control Register 
#define LRFDRFE_O_MULTCFG                                           0x00000258U

//*****************************************************************************
//
// Register: LRFDRFE_O_ENABLE
//
//*****************************************************************************
// Field:     [3] ACC1 
//
// Enables the Magnitude Accumulator 1 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE_ENABLE_ACC1                                         0x00000008U
#define LRFDRFE_ENABLE_ACC1_M                                       0x00000008U
#define LRFDRFE_ENABLE_ACC1_S                                                3U
#define LRFDRFE_ENABLE_ACC1_EN                                      0x00000008U
#define LRFDRFE_ENABLE_ACC1_DIS                                     0x00000000U

// Field:     [2] ACC0 
//
// Enables the Magnitude Accumulator 0 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE_ENABLE_ACC0                                         0x00000004U
#define LRFDRFE_ENABLE_ACC0_M                                       0x00000004U
#define LRFDRFE_ENABLE_ACC0_S                                                2U
#define LRFDRFE_ENABLE_ACC0_EN                                      0x00000004U
#define LRFDRFE_ENABLE_ACC0_DIS                                     0x00000000U

// Field:     [1] LOCTIM 
//
// Enables the Local timer 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDRFE_ENABLE_LOCTIM                                       0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_M                                     0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_S                                              1U
#define LRFDRFE_ENABLE_LOCTIM_EN                                    0x00000002U
#define LRFDRFE_ENABLE_LOCTIM_DIS                                   0x00000000U

// Field:     [0] TOPSM 
//
// Enables the TOPsm (RFE) 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
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
// Selects RAM to use for data storage 
// ENUMs: 
// S2RRAM                   Use S2RRAM for data 
// RFERAM                   Use RFERAM for data 
#define LRFDRFE_FWSRC_DATARAM                                       0x00000004U
#define LRFDRFE_FWSRC_DATARAM_M                                     0x00000004U
#define LRFDRFE_FWSRC_DATARAM_S                                              2U
#define LRFDRFE_FWSRC_DATARAM_S2RRAM                                0x00000004U
#define LRFDRFE_FWSRC_DATARAM_RFERAM                                0x00000000U

// Field:     [1] FWRAM 
//
// Selects RAM to use for program memory 
// ENUMs: 
// S2RRAM                   Run code from S2RRAM 
// RFERAM                   Run code from RFERAM 
#define LRFDRFE_FWSRC_FWRAM                                         0x00000002U
#define LRFDRFE_FWSRC_FWRAM_M                                       0x00000002U
#define LRFDRFE_FWSRC_FWRAM_S                                                1U
#define LRFDRFE_FWSRC_FWRAM_S2RRAM                                  0x00000002U
#define LRFDRFE_FWSRC_FWRAM_RFERAM                                  0x00000000U

// Field:     [0] BANK 
//
// Selects 2K bank within the program memory as FW source. 
// This controls MSB of address line towards program memory. 
// ENUMs: 
// ONE                      Run code from bank 1 
// ZERO                     Run code from bank 0 
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
// Synchronous reset to magnitude accumulator 1 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE_INIT_ACC1                                           0x00000008U
#define LRFDRFE_INIT_ACC1_M                                         0x00000008U
#define LRFDRFE_INIT_ACC1_S                                                  3U
#define LRFDRFE_INIT_ACC1_RESET                                     0x00000008U
#define LRFDRFE_INIT_ACC1_NO_EFFECT                                 0x00000000U

// Field:     [2] ACC0 
//
// Synchronous reset to magnitude accumulator 0 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE_INIT_ACC0                                           0x00000004U
#define LRFDRFE_INIT_ACC0_M                                         0x00000004U
#define LRFDRFE_INIT_ACC0_S                                                  2U
#define LRFDRFE_INIT_ACC0_RESET                                     0x00000004U
#define LRFDRFE_INIT_ACC0_NO_EFFECT                                 0x00000000U

// Field:     [1] LOCTIM 
//
// Synchronous reset to local timer 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDRFE_INIT_LOCTIM                                         0x00000002U
#define LRFDRFE_INIT_LOCTIM_M                                       0x00000002U
#define LRFDRFE_INIT_LOCTIM_S                                                1U
#define LRFDRFE_INIT_LOCTIM_RESET                                   0x00000002U
#define LRFDRFE_INIT_LOCTIM_NO_EFFECT                               0x00000000U

// Field:     [0] TOPSM 
//
// Synchronous reset to TOPsm (RFE) 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
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
// Requests power down for TOPsm core. If the TOPsm has an ongoing memory 
// access, the hardware will safely gate the clock after the transaction has 
// completed. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Magnitude accumulator amplitude is above MAGNTHR theshold 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_MAGNTHR                                        0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_M                                      0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_S                                              14U
#define LRFDRFE_EVT0_MAGNTHR_ONE                                    0x00004000U
#define LRFDRFE_EVT0_MAGNTHR_ZERO                                   0x00000000U

// Field:    [13] S2RSTOP 
//
// S2R has written to LRFDS2R:STOP.ADDR 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_S2RSTOP                                        0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_M                                      0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_S                                              13U
#define LRFDRFE_EVT0_S2RSTOP_ONE                                    0x00002000U
#define LRFDRFE_EVT0_S2RSTOP_ZERO                                   0x00000000U

// Field:    [12] SYSTCMP2 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_SYSTCMP2                                       0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_M                                     0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_S                                             12U
#define LRFDRFE_EVT0_SYSTCMP2_ONE                                   0x00001000U
#define LRFDRFE_EVT0_SYSTCMP2_ZERO                                  0x00000000U

// Field:    [11] SYSTCMP1 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_SYSTCMP1                                       0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_M                                     0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_S                                             11U
#define LRFDRFE_EVT0_SYSTCMP1_ONE                                   0x00000800U
#define LRFDRFE_EVT0_SYSTCMP1_ZERO                                  0x00000000U

// Field:    [10] SYSTCMP0 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_SYSTCMP0                                       0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_M                                     0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_S                                             10U
#define LRFDRFE_EVT0_SYSTCMP0_ONE                                   0x00000400U
#define LRFDRFE_EVT0_SYSTCMP0_ZERO                                  0x00000000U

// Field:     [9] PBERFEDAT 
//
// New data from PBE in PBEDATIN0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_PBERFEDAT                                      0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_M                                    0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_S                                             9U
#define LRFDRFE_EVT0_PBERFEDAT_ONE                                  0x00000200U
#define LRFDRFE_EVT0_PBERFEDAT_ZERO                                 0x00000000U

// Field:     [8] MDMRFEDAT 
//
// New data from MCE in MCEDATIN0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_MDMRFEDAT                                      0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_M                                    0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_S                                             8U
#define LRFDRFE_EVT0_MDMRFEDAT_ONE                                  0x00000100U
#define LRFDRFE_EVT0_MDMRFEDAT_ZERO                                 0x00000000U

// Field:     [7] DLO 
//
// Event from DLO state machine 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_DLO                                            0x00000080U
#define LRFDRFE_EVT0_DLO_M                                          0x00000080U
#define LRFDRFE_EVT0_DLO_S                                                   7U
#define LRFDRFE_EVT0_DLO_ONE                                        0x00000080U
#define LRFDRFE_EVT0_DLO_ZERO                                       0x00000000U

// Field:     [6] PBECMD 
//
// New command from PBE in PBECMDIN 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_PBECMD                                         0x00000040U
#define LRFDRFE_EVT0_PBECMD_M                                       0x00000040U
#define LRFDRFE_EVT0_PBECMD_S                                                6U
#define LRFDRFE_EVT0_PBECMD_ONE                                     0x00000040U
#define LRFDRFE_EVT0_PBECMD_ZERO                                    0x00000000U

// Field:     [5] COUNTER 
//
// Counter value reached in local timer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_COUNTER                                        0x00000020U
#define LRFDRFE_EVT0_COUNTER_M                                      0x00000020U
#define LRFDRFE_EVT0_COUNTER_S                                               5U
#define LRFDRFE_EVT0_COUNTER_ONE                                    0x00000020U
#define LRFDRFE_EVT0_COUNTER_ZERO                                   0x00000000U

// Field:     [4] MDMCMD 
//
// New command from MCE in MCECMDIN 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_MDMCMD                                         0x00000010U
#define LRFDRFE_EVT0_MDMCMD_M                                       0x00000010U
#define LRFDRFE_EVT0_MDMCMD_S                                                4U
#define LRFDRFE_EVT0_MDMCMD_ONE                                     0x00000010U
#define LRFDRFE_EVT0_MDMCMD_ZERO                                    0x00000000U

// Field:     [3] ACC1 
//
// Accumulation period completed in magnitude accumulator 1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_ACC1                                           0x00000008U
#define LRFDRFE_EVT0_ACC1_M                                         0x00000008U
#define LRFDRFE_EVT0_ACC1_S                                                  3U
#define LRFDRFE_EVT0_ACC1_ONE                                       0x00000008U
#define LRFDRFE_EVT0_ACC1_ZERO                                      0x00000000U

// Field:     [2] ACC0 
//
// Accumulation period completed in magnitude accumulator 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_ACC0                                           0x00000004U
#define LRFDRFE_EVT0_ACC0_M                                         0x00000004U
#define LRFDRFE_EVT0_ACC0_S                                                  2U
#define LRFDRFE_EVT0_ACC0_ONE                                       0x00000004U
#define LRFDRFE_EVT0_ACC0_ZERO                                      0x00000000U

// Field:     [1] TIMER 
//
// Timer period expired in local timer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT0_TIMER                                          0x00000002U
#define LRFDRFE_EVT0_TIMER_M                                        0x00000002U
#define LRFDRFE_EVT0_TIMER_S                                                 1U
#define LRFDRFE_EVT0_TIMER_ONE                                      0x00000002U
#define LRFDRFE_EVT0_TIMER_ZERO                                     0x00000000U

// Field:     [0] RFEAPI 
//
// New RFE API availabe in API 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Prescaled REFCLK event, controlled by DCOCTL0.LOOPUPD 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_PREREFCLK                                      0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_M                                    0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_S                                            13U
#define LRFDRFE_EVT1_PREREFCLK_ONE                                  0x00002000U
#define LRFDRFE_EVT1_PREREFCLK_ZERO                                 0x00000000U

// Field:    [12] REFCLK 
//
// REFCLK event from DLO 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_REFCLK                                         0x00001000U
#define LRFDRFE_EVT1_REFCLK_M                                       0x00001000U
#define LRFDRFE_EVT1_REFCLK_S                                               12U
#define LRFDRFE_EVT1_REFCLK_ONE                                     0x00001000U
#define LRFDRFE_EVT1_REFCLK_ZERO                                    0x00000000U

// Field:    [11] FBLWTHR 
//
// Finecode below programmed threshold event from DLO state machine 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_FBLWTHR                                        0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_M                                      0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_S                                              11U
#define LRFDRFE_EVT1_FBLWTHR_ONE                                    0x00000800U
#define LRFDRFE_EVT1_FBLWTHR_ZERO                                   0x00000000U

// Field:    [10] FABVTHR 
//
// Finecode above programmed threshold event from DLO state machine 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_FABVTHR                                        0x00000400U
#define LRFDRFE_EVT1_FABVTHR_M                                      0x00000400U
#define LRFDRFE_EVT1_FABVTHR_S                                              10U
#define LRFDRFE_EVT1_FABVTHR_ONE                                    0x00000400U
#define LRFDRFE_EVT1_FABVTHR_ZERO                                   0x00000000U

// Field:     [9] LOCK 
//
// Lock event from DLO state machine 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_LOCK                                           0x00000200U
#define LRFDRFE_EVT1_LOCK_M                                         0x00000200U
#define LRFDRFE_EVT1_LOCK_S                                                  9U
#define LRFDRFE_EVT1_LOCK_ONE                                       0x00000200U
#define LRFDRFE_EVT1_LOCK_ZERO                                      0x00000000U

// Field:     [8] LOL 
//
// Loss of lock event from DLO state machine 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_LOL                                            0x00000100U
#define LRFDRFE_EVT1_LOL_M                                          0x00000100U
#define LRFDRFE_EVT1_LOL_S                                                   8U
#define LRFDRFE_EVT1_LOL_ONE                                        0x00000100U
#define LRFDRFE_EVT1_LOL_ZERO                                       0x00000000U

// Field:     [7] GPI7 
//
// External input event line GPI7 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI7                                           0x00000080U
#define LRFDRFE_EVT1_GPI7_M                                         0x00000080U
#define LRFDRFE_EVT1_GPI7_S                                                  7U
#define LRFDRFE_EVT1_GPI7_ONE                                       0x00000080U
#define LRFDRFE_EVT1_GPI7_ZERO                                      0x00000000U

// Field:     [6] GPI6 
//
// External input event line GPI6 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI6                                           0x00000040U
#define LRFDRFE_EVT1_GPI6_M                                         0x00000040U
#define LRFDRFE_EVT1_GPI6_S                                                  6U
#define LRFDRFE_EVT1_GPI6_ONE                                       0x00000040U
#define LRFDRFE_EVT1_GPI6_ZERO                                      0x00000000U

// Field:     [5] GPI5 
//
// External input event line GPI5 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI5                                           0x00000020U
#define LRFDRFE_EVT1_GPI5_M                                         0x00000020U
#define LRFDRFE_EVT1_GPI5_S                                                  5U
#define LRFDRFE_EVT1_GPI5_ONE                                       0x00000020U
#define LRFDRFE_EVT1_GPI5_ZERO                                      0x00000000U

// Field:     [4] GPI4 
//
// External input event line GPI4 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI4                                           0x00000010U
#define LRFDRFE_EVT1_GPI4_M                                         0x00000010U
#define LRFDRFE_EVT1_GPI4_S                                                  4U
#define LRFDRFE_EVT1_GPI4_ONE                                       0x00000010U
#define LRFDRFE_EVT1_GPI4_ZERO                                      0x00000000U

// Field:     [3] GPI3 
//
// External input event line GPI3 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI3                                           0x00000008U
#define LRFDRFE_EVT1_GPI3_M                                         0x00000008U
#define LRFDRFE_EVT1_GPI3_S                                                  3U
#define LRFDRFE_EVT1_GPI3_ONE                                       0x00000008U
#define LRFDRFE_EVT1_GPI3_ZERO                                      0x00000000U

// Field:     [2] GPI2 
//
// External input event line GPI2 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI2                                           0x00000004U
#define LRFDRFE_EVT1_GPI2_M                                         0x00000004U
#define LRFDRFE_EVT1_GPI2_S                                                  2U
#define LRFDRFE_EVT1_GPI2_ONE                                       0x00000004U
#define LRFDRFE_EVT1_GPI2_ZERO                                      0x00000000U

// Field:     [1] GPI1 
//
// External input event line GPI1 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVT1_GPI1                                           0x00000002U
#define LRFDRFE_EVT1_GPI1_M                                         0x00000002U
#define LRFDRFE_EVT1_GPI1_S                                                  1U
#define LRFDRFE_EVT1_GPI1_ONE                                       0x00000002U
#define LRFDRFE_EVT1_GPI1_ZERO                                      0x00000000U

// Field:     [0] GPI0 
//
// External input event line GPI0 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Enable mask for event EVT0.MAGNTHR 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_MAGNTHR                                     0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_M                                   0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_S                                           14U
#define LRFDRFE_EVTMSK0_MAGNTHR_EN                                  0x00004000U
#define LRFDRFE_EVTMSK0_MAGNTHR_DIS                                 0x00000000U

// Field:    [13] S2RSTOP 
//
// Enable mask for event EVT0.S2RSTOP 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_S2RSTOP                                     0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_M                                   0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_S                                           13U
#define LRFDRFE_EVTMSK0_S2RSTOP_EN                                  0x00002000U
#define LRFDRFE_EVTMSK0_S2RSTOP_DIS                                 0x00000000U

// Field:    [12] SYSTCMP2 
//
// Enable mask for event EVT0.SYSTCMP2 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_SYSTCMP2                                    0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_M                                  0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_S                                          12U
#define LRFDRFE_EVTMSK0_SYSTCMP2_EN                                 0x00001000U
#define LRFDRFE_EVTMSK0_SYSTCMP2_DIS                                0x00000000U

// Field:    [11] SYSTCMP1 
//
// Enable mask for event EVT0.SYSTCMP1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_SYSTCMP1                                    0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_M                                  0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_S                                          11U
#define LRFDRFE_EVTMSK0_SYSTCMP1_EN                                 0x00000800U
#define LRFDRFE_EVTMSK0_SYSTCMP1_DIS                                0x00000000U

// Field:    [10] SYSTCMP0 
//
// Enable mask for event EVT0.SYSTCMP0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_SYSTCMP0                                    0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_M                                  0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_S                                          10U
#define LRFDRFE_EVTMSK0_SYSTCMP0_EN                                 0x00000400U
#define LRFDRFE_EVTMSK0_SYSTCMP0_DIS                                0x00000000U

// Field:     [9] PBERFEDAT 
//
// Enable mask for event EVT0.PBERFEDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_PBERFEDAT                                   0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_M                                 0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_S                                          9U
#define LRFDRFE_EVTMSK0_PBERFEDAT_EN                                0x00000200U
#define LRFDRFE_EVTMSK0_PBERFEDAT_DIS                               0x00000000U

// Field:     [8] MDMRFEDAT 
//
// Enable mask for event EVT0.MDMRFEDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_MDMRFEDAT                                   0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_M                                 0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_S                                          8U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_EN                                0x00000100U
#define LRFDRFE_EVTMSK0_MDMRFEDAT_DIS                               0x00000000U

// Field:     [7] DLO 
//
// Enable mask for event EVT0.DLO 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_DLO                                         0x00000080U
#define LRFDRFE_EVTMSK0_DLO_M                                       0x00000080U
#define LRFDRFE_EVTMSK0_DLO_S                                                7U
#define LRFDRFE_EVTMSK0_DLO_EN                                      0x00000080U
#define LRFDRFE_EVTMSK0_DLO_DIS                                     0x00000000U

// Field:     [6] PBECMD 
//
// Enable mask for event EVT0.PBECMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_PBECMD                                      0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_M                                    0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_S                                             6U
#define LRFDRFE_EVTMSK0_PBECMD_EN                                   0x00000040U
#define LRFDRFE_EVTMSK0_PBECMD_DIS                                  0x00000000U

// Field:     [5] COUNTER 
//
// Enable mask for event EVT0.COUNTER 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_COUNTER                                     0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_M                                   0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_S                                            5U
#define LRFDRFE_EVTMSK0_COUNTER_EN                                  0x00000020U
#define LRFDRFE_EVTMSK0_COUNTER_DIS                                 0x00000000U

// Field:     [4] MDMCMD 
//
// Enable mask for event EVT0.MDMCMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_MDMCMD                                      0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_M                                    0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_S                                             4U
#define LRFDRFE_EVTMSK0_MDMCMD_EN                                   0x00000010U
#define LRFDRFE_EVTMSK0_MDMCMD_DIS                                  0x00000000U

// Field:     [3] ACC1 
//
// Enable mask for event EVT0.ACC1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_ACC1                                        0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_M                                      0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_S                                               3U
#define LRFDRFE_EVTMSK0_ACC1_EN                                     0x00000008U
#define LRFDRFE_EVTMSK0_ACC1_DIS                                    0x00000000U

// Field:     [2] ACC0 
//
// Enable mask for event EVT0.ACC0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_ACC0                                        0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_M                                      0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_S                                               2U
#define LRFDRFE_EVTMSK0_ACC0_EN                                     0x00000004U
#define LRFDRFE_EVTMSK0_ACC0_DIS                                    0x00000000U

// Field:     [1] TIMER 
//
// Enable mask for event EVT0.TIMER 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK0_TIMER                                       0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_M                                     0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_S                                              1U
#define LRFDRFE_EVTMSK0_TIMER_EN                                    0x00000002U
#define LRFDRFE_EVTMSK0_TIMER_DIS                                   0x00000000U

// Field:     [0] RFEAPI 
//
// Enable mask for event EVT0.RFEAPI 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
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
// Enable mask for event EVT1.PREREFCLK 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_PREREFCLK                                   0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_M                                 0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_S                                         13U
#define LRFDRFE_EVTMSK1_PREREFCLK_EN                                0x00002000U
#define LRFDRFE_EVTMSK1_PREREFCLK_DIS                               0x00000000U

// Field:    [12] REFCLK 
//
// Enable mask for event EVT1.REFCLK 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_REFCLK                                      0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_M                                    0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_S                                            12U
#define LRFDRFE_EVTMSK1_REFCLK_EN                                   0x00001000U
#define LRFDRFE_EVTMSK1_REFCLK_DIS                                  0x00000000U

// Field:    [11] FBLWTHR 
//
// Enable mask for event EVT1.FBLWTHR 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_FBLWTHR                                     0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_M                                   0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_S                                           11U
#define LRFDRFE_EVTMSK1_FBLWTHR_EN                                  0x00000800U
#define LRFDRFE_EVTMSK1_FBLWTHR_DIS                                 0x00000000U

// Field:    [10] FABVTHR 
//
// Enable mask for event EVT1.FABVTHR 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_FABVTHR                                     0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_M                                   0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_S                                           10U
#define LRFDRFE_EVTMSK1_FABVTHR_EN                                  0x00000400U
#define LRFDRFE_EVTMSK1_FABVTHR_DIS                                 0x00000000U

// Field:     [9] LOCK 
//
// Enable mask for event EVT1.LOCK 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_LOCK                                        0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_M                                      0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_S                                               9U
#define LRFDRFE_EVTMSK1_LOCK_EN                                     0x00000200U
#define LRFDRFE_EVTMSK1_LOCK_DIS                                    0x00000000U

// Field:     [8] LOL 
//
// Enable mask for event EVT1.LOL 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_LOL                                         0x00000100U
#define LRFDRFE_EVTMSK1_LOL_M                                       0x00000100U
#define LRFDRFE_EVTMSK1_LOL_S                                                8U
#define LRFDRFE_EVTMSK1_LOL_EN                                      0x00000100U
#define LRFDRFE_EVTMSK1_LOL_DIS                                     0x00000000U

// Field:     [7] GPI7 
//
// Enable mask for event EVT1.GPI7 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI7                                        0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_M                                      0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_S                                               7U
#define LRFDRFE_EVTMSK1_GPI7_EN                                     0x00000080U
#define LRFDRFE_EVTMSK1_GPI7_DIS                                    0x00000000U

// Field:     [6] GPI6 
//
// Enable mask for event EVT1.GPI6 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI6                                        0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_M                                      0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_S                                               6U
#define LRFDRFE_EVTMSK1_GPI6_EN                                     0x00000040U
#define LRFDRFE_EVTMSK1_GPI6_DIS                                    0x00000000U

// Field:     [5] GPI5 
//
// Enable mask for event EVT1.GPI5 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI5                                        0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_M                                      0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_S                                               5U
#define LRFDRFE_EVTMSK1_GPI5_EN                                     0x00000020U
#define LRFDRFE_EVTMSK1_GPI5_DIS                                    0x00000000U

// Field:     [4] GPI4 
//
// Enable mask for event EVT1.GPI4 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI4                                        0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_M                                      0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_S                                               4U
#define LRFDRFE_EVTMSK1_GPI4_EN                                     0x00000010U
#define LRFDRFE_EVTMSK1_GPI4_DIS                                    0x00000000U

// Field:     [3] GPI3 
//
// Enable mask for event EVT1.GPI3 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI3                                        0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_M                                      0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_S                                               3U
#define LRFDRFE_EVTMSK1_GPI3_EN                                     0x00000008U
#define LRFDRFE_EVTMSK1_GPI3_DIS                                    0x00000000U

// Field:     [2] GPI2 
//
// Enable mask for event EVT1.GPI2 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI2                                        0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_M                                      0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_S                                               2U
#define LRFDRFE_EVTMSK1_GPI2_EN                                     0x00000004U
#define LRFDRFE_EVTMSK1_GPI2_DIS                                    0x00000000U

// Field:     [1] GPI1 
//
// Enable mask for event EVT1.GPI1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_EVTMSK1_GPI1                                        0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_M                                      0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_S                                               1U
#define LRFDRFE_EVTMSK1_GPI1_EN                                     0x00000002U
#define LRFDRFE_EVTMSK1_GPI1_DIS                                    0x00000000U

// Field:     [0] GPI0 
//
// Enable mask for event EVT1.GPI0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
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
// Clear event EVT0.MAGNTHR 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_MAGNTHR                                     0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_M                                   0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_S                                           14U
#define LRFDRFE_EVTCLR0_MAGNTHR_ONE                                 0x00004000U
#define LRFDRFE_EVTCLR0_MAGNTHR_ZERO                                0x00000000U

// Field:    [13] S2RSTOP 
//
// Clear event EVT0.S2RSTOP 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_S2RSTOP                                     0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_M                                   0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_S                                           13U
#define LRFDRFE_EVTCLR0_S2RSTOP_ONE                                 0x00002000U
#define LRFDRFE_EVTCLR0_S2RSTOP_ZERO                                0x00000000U

// Field:    [12] SYSTCMP2 
//
// Clear event EVT0.SYSTCMP2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_SYSTCMP2                                    0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_M                                  0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_S                                          12U
#define LRFDRFE_EVTCLR0_SYSTCMP2_ONE                                0x00001000U
#define LRFDRFE_EVTCLR0_SYSTCMP2_ZERO                               0x00000000U

// Field:    [11] SYSTCMP1 
//
// Clear event EVT0.SYSTCMP1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_SYSTCMP1                                    0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_M                                  0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_S                                          11U
#define LRFDRFE_EVTCLR0_SYSTCMP1_ONE                                0x00000800U
#define LRFDRFE_EVTCLR0_SYSTCMP1_ZERO                               0x00000000U

// Field:    [10] SYSTCMP0 
//
// Clear event EVT0.SYSTCMP0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_SYSTCMP0                                    0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_M                                  0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_S                                          10U
#define LRFDRFE_EVTCLR0_SYSTCMP0_ONE                                0x00000400U
#define LRFDRFE_EVTCLR0_SYSTCMP0_ZERO                               0x00000000U

// Field:     [9] PBERFEDAT 
//
// Clear event EVT0.PBERFEDAT 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_PBERFEDAT                                   0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_M                                 0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_S                                          9U
#define LRFDRFE_EVTCLR0_PBERFEDAT_ONE                               0x00000200U
#define LRFDRFE_EVTCLR0_PBERFEDAT_ZERO                              0x00000000U

// Field:     [8] MDMRFEDAT 
//
// Clear event EVT0.MDMRFEDAT 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_MDMRFEDAT                                   0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_M                                 0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_S                                          8U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_ONE                               0x00000100U
#define LRFDRFE_EVTCLR0_MDMRFEDAT_ZERO                              0x00000000U

// Field:     [7] DLO 
//
// Clear event EVT0.DLO 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_DLO                                         0x00000080U
#define LRFDRFE_EVTCLR0_DLO_M                                       0x00000080U
#define LRFDRFE_EVTCLR0_DLO_S                                                7U
#define LRFDRFE_EVTCLR0_DLO_ONE                                     0x00000080U
#define LRFDRFE_EVTCLR0_DLO_ZERO                                    0x00000000U

// Field:     [6] PBECMD 
//
// Clear event EVT0.PBECMD 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_PBECMD                                      0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_M                                    0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_S                                             6U
#define LRFDRFE_EVTCLR0_PBECMD_ONE                                  0x00000040U
#define LRFDRFE_EVTCLR0_PBECMD_ZERO                                 0x00000000U

// Field:     [5] COUNTER 
//
// Clear event EVT0.COUNTER 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_COUNTER                                     0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_M                                   0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_S                                            5U
#define LRFDRFE_EVTCLR0_COUNTER_ONE                                 0x00000020U
#define LRFDRFE_EVTCLR0_COUNTER_ZERO                                0x00000000U

// Field:     [4] MDMCMD 
//
// Clear event EVT0.MDMCMD 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_MDMCMD                                      0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_M                                    0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_S                                             4U
#define LRFDRFE_EVTCLR0_MDMCMD_ONE                                  0x00000010U
#define LRFDRFE_EVTCLR0_MDMCMD_ZERO                                 0x00000000U

// Field:     [3] ACC1 
//
// Clear event EVT0.ACC1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_ACC1                                        0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_M                                      0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_S                                               3U
#define LRFDRFE_EVTCLR0_ACC1_ONE                                    0x00000008U
#define LRFDRFE_EVTCLR0_ACC1_ZERO                                   0x00000000U

// Field:     [2] ACC0 
//
// Clear event EVT0.ACC0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_ACC0                                        0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_M                                      0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_S                                               2U
#define LRFDRFE_EVTCLR0_ACC0_ONE                                    0x00000004U
#define LRFDRFE_EVTCLR0_ACC0_ZERO                                   0x00000000U

// Field:     [1] TIMER 
//
// Clear event EVT0.TIMER 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR0_TIMER                                       0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_M                                     0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_S                                              1U
#define LRFDRFE_EVTCLR0_TIMER_ONE                                   0x00000002U
#define LRFDRFE_EVTCLR0_TIMER_ZERO                                  0x00000000U

// Field:     [0] RFEAPI 
//
// Clear event EVT0.RFEAPI 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Clear event EVT1.PREREFCLK 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_PREREFCLK                                   0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_M                                 0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_S                                         13U
#define LRFDRFE_EVTCLR1_PREREFCLK_ONE                               0x00002000U
#define LRFDRFE_EVTCLR1_PREREFCLK_ZERO                              0x00000000U

// Field:    [12] REFCLK 
//
// Clear event EVT1.REFCLK 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_REFCLK                                      0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_M                                    0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_S                                            12U
#define LRFDRFE_EVTCLR1_REFCLK_ONE                                  0x00001000U
#define LRFDRFE_EVTCLR1_REFCLK_ZERO                                 0x00000000U

// Field:    [11] FBLWTHR 
//
// Clear event EVT1.FBLWTHR 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_FBLWTHR                                     0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_M                                   0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_S                                           11U
#define LRFDRFE_EVTCLR1_FBLWTHR_ONE                                 0x00000800U
#define LRFDRFE_EVTCLR1_FBLWTHR_ZERO                                0x00000000U

// Field:    [10] FABVTHR 
//
// Clear event EVT1.FABVTHR 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_FABVTHR                                     0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_M                                   0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_S                                           10U
#define LRFDRFE_EVTCLR1_FABVTHR_ONE                                 0x00000400U
#define LRFDRFE_EVTCLR1_FABVTHR_ZERO                                0x00000000U

// Field:     [9] LOCK 
//
// Clear event EVT1.LOCK 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_LOCK                                        0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_M                                      0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_S                                               9U
#define LRFDRFE_EVTCLR1_LOCK_ONE                                    0x00000200U
#define LRFDRFE_EVTCLR1_LOCK_ZERO                                   0x00000000U

// Field:     [8] LOL 
//
// Clear event EVT1.LOL 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_LOL                                         0x00000100U
#define LRFDRFE_EVTCLR1_LOL_M                                       0x00000100U
#define LRFDRFE_EVTCLR1_LOL_S                                                8U
#define LRFDRFE_EVTCLR1_LOL_ONE                                     0x00000100U
#define LRFDRFE_EVTCLR1_LOL_ZERO                                    0x00000000U

// Field:     [7] GPI7 
//
// Clear event EVT1.GPI7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI7                                        0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_M                                      0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_S                                               7U
#define LRFDRFE_EVTCLR1_GPI7_ONE                                    0x00000080U
#define LRFDRFE_EVTCLR1_GPI7_ZERO                                   0x00000000U

// Field:     [6] GPI6 
//
// Clear event EVT1.GPI6 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI6                                        0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_M                                      0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_S                                               6U
#define LRFDRFE_EVTCLR1_GPI6_ONE                                    0x00000040U
#define LRFDRFE_EVTCLR1_GPI6_ZERO                                   0x00000000U

// Field:     [5] GPI5 
//
// Clear event EVT1.GPI5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI5                                        0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_M                                      0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_S                                               5U
#define LRFDRFE_EVTCLR1_GPI5_ONE                                    0x00000020U
#define LRFDRFE_EVTCLR1_GPI5_ZERO                                   0x00000000U

// Field:     [4] GPI4 
//
// Clear event EVT1.GPI4 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI4                                        0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_M                                      0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_S                                               4U
#define LRFDRFE_EVTCLR1_GPI4_ONE                                    0x00000010U
#define LRFDRFE_EVTCLR1_GPI4_ZERO                                   0x00000000U

// Field:     [3] GPI3 
//
// Clear event EVT1.GPI3 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI3                                        0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_M                                      0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_S                                               3U
#define LRFDRFE_EVTCLR1_GPI3_ONE                                    0x00000008U
#define LRFDRFE_EVTCLR1_GPI3_ZERO                                   0x00000000U

// Field:     [2] GPI2 
//
// Clear event EVT1.GPI2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI2                                        0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_M                                      0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_S                                               2U
#define LRFDRFE_EVTCLR1_GPI2_ONE                                    0x00000004U
#define LRFDRFE_EVTCLR1_GPI2_ZERO                                   0x00000000U

// Field:     [1] GPI1 
//
// Clear event EVT1.GPI1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_EVTCLR1_GPI1                                        0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_M                                      0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_S                                               1U
#define LRFDRFE_EVTCLR1_GPI1_ONE                                    0x00000002U
#define LRFDRFE_EVTCLR1_GPI1_ZERO                                   0x00000000U

// Field:     [0] GPI0 
//
// Clear event EVT1.GPI0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// HFXT RF qualification 
// ENUMs: 
// QUAL                     Clock signal is qualified 
// NONQUAL                  Clock signal is not qualified 
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
// Radio Status 
// ENUMs: 
// RX                       RX is active 
// TX                       TX is active 
// SYNTH                    Synth is running 
// IDLE                     Radio is idle 
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
// Protocol ID 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_API_PROTOCOLID_W                                             4U
#define LRFDRFE_API_PROTOCOLID_M                                    0x000000F0U
#define LRFDRFE_API_PROTOCOLID_S                                             4U
#define LRFDRFE_API_PROTOCOLID_ALLONES                              0x000000F0U
#define LRFDRFE_API_PROTOCOLID_ALLZEROS                             0x00000000U

// Field:   [3:0] RFECMD 
//
// RFE Command 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All bits are 0 
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
// Parameter 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Parameter 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// RFE status as responser to API execution. 
//
// Field is readable to PBE in LRFDPBE:RFEMSGBOX. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Data to send to MCE. 
//
// Write VAL to send data to MCE. A write triggers an LRFDMDM:EVT0.RFEDAT event 
// in MCE. MCE reads VAL in LRFDMDM:RFEDATIN0. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Data received from MCE. 
//
// Read data that MCE writes to LRFDMDM:RFEDATAOUT0. A write to 
// LRFDMDM:RFEDATAOUT0 sets EVT0.MDMRFEDAT event. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Command to send to the MCE. 
//
// A write to this register tiggers LRFDMDM:EVT1.RFECMD MCE event, and the 
// command becomes readable to MCE in LRFDMDM:RFECMDIN. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Command received from MCE. 
//
// MCE writes LRFDMDM:RFECMDOUT to send a command to RFE. This action sets 
// EVT0.MDMCMD RFE event. RFE reads command from MCECMDIN. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Data to send to PBE. 
//
// Write VAL to send data to PBE. A write triggers an LRFDPBE:EVT0.RFEDAT event 
// in PBE. PBE reads VAL in LRFDPBE:RFEDATIN0. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Data received from PBE. 
//
// Read data that PBE writes to LRFDPBE:RFEDATAOUT0. A write to 
// LRFDPBE:RFEDATAOUT0 sets EVT0.PBERFEDAT event. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Command to send to the PBE. 
//
// A write to this register tiggers LRFDPBE:EVT0.RFECMD PBE event, and the 
// command becomes readable to PBE in LRFDPBE:RFECMDIN. 
//
//
// Command to send to the PBE. Writing to this register will trigger an event 
// in the PBE, and the command value written here will be readable in 
// LRFDPBE:RFECMDIN register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Command received from PBE. 
//
// PBE writes LRFDPBE:RFECMDOUT to send a command to RFE. This action sets 
// EVT0.PBECMD RFE event. RFE reads command from PBECMDIN. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// LRFDS2R arm/trigger 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_S2RTRG                                         0x00000080U
#define LRFDRFE_STRB_S2RTRG_M                                       0x00000080U
#define LRFDRFE_STRB_S2RTRG_S                                                7U
#define LRFDRFE_STRB_S2RTRG_ONE                                     0x00000080U
#define LRFDRFE_STRB_S2RTRG_ZERO                                    0x00000000U

// Field:     [6] DMATRG 
//
// DMA transfer trigger 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_DMATRG                                         0x00000040U
#define LRFDRFE_STRB_DMATRG_M                                       0x00000040U
#define LRFDRFE_STRB_DMATRG_S                                                6U
#define LRFDRFE_STRB_DMATRG_ONE                                     0x00000040U
#define LRFDRFE_STRB_DMATRG_ZERO                                    0x00000000U

// Field:     [5] SYSTCPT2 
//
// Systimer capture event 2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_SYSTCPT2                                       0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_M                                     0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_S                                              5U
#define LRFDRFE_STRB_SYSTCPT2_ONE                                   0x00000020U
#define LRFDRFE_STRB_SYSTCPT2_ZERO                                  0x00000000U

// Field:     [4] SYSTCPT1 
//
// Systimer capture event 1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_SYSTCPT1                                       0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_M                                     0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_S                                              4U
#define LRFDRFE_STRB_SYSTCPT1_ONE                                   0x00000010U
#define LRFDRFE_STRB_SYSTCPT1_ZERO                                  0x00000000U

// Field:     [3] SYSTCPT0 
//
// Systimer capture event 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_SYSTCPT0                                       0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_M                                     0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_S                                              3U
#define LRFDRFE_STRB_SYSTCPT0_ONE                                   0x00000008U
#define LRFDRFE_STRB_SYSTCPT0_ZERO                                  0x00000000U

// Field:     [2] EVT1 
//
// Event 1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_EVT1                                           0x00000004U
#define LRFDRFE_STRB_EVT1_M                                         0x00000004U
#define LRFDRFE_STRB_EVT1_S                                                  2U
#define LRFDRFE_STRB_EVT1_ONE                                       0x00000004U
#define LRFDRFE_STRB_EVT1_ZERO                                      0x00000000U

// Field:     [1] EVT0 
//
// Event 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_STRB_EVT0                                           0x00000002U
#define LRFDRFE_STRB_EVT0_M                                         0x00000002U
#define LRFDRFE_STRB_EVT0_S                                                  1U
#define LRFDRFE_STRB_EVT0_ONE                                       0x00000002U
#define LRFDRFE_STRB_EVT0_ZERO                                      0x00000000U

// Field:     [0] CMDDONE 
//
// Command done indication 
// ENUMs: 
// YES                      The bit is 1 
// NO                       The bit is 0 
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
// Selects what MAGNACC is used in the compare with the threshold in MAGNTHR. 
// ENUMs: 
// MAGNACC1                 Use MAGNACC1 in the compare against the theshold 
//                          in MANGTHR 
// MAGNACC0                 Use MAGNACC0 in the compare against the theshold 
//                          in MANGTHR 
#define LRFDRFE_MAGNTHRCFG_SEL                                      0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_M                                    0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_S                                             1U
#define LRFDRFE_MAGNTHRCFG_SEL_MAGNACC1                             0x00000002U
#define LRFDRFE_MAGNTHRCFG_SEL_MAGNACC0                             0x00000000U

// Field:     [0] CTL 
//
// Controls automatic comparison of magnitude with threshold 
// ENUMs: 
// EN                       Enable automatic comparison of magntude with 
//                          threshold (input of lin2log is driven by HW) 
// DIS                      Disable automatic comparison with threshold (input 
//                          of lin2log is driven by FW) 
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
// Magnitude threshold value 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Offset to convert to dBm (unsigned). This is used by the RFE to adjust its 
// RSSI calculations. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// DVGA settings for BDE2. 
//
// The DVGA control for BDE2 is shared with the MCE in its 
// LRFDMDM:DEMMISC3.BDE2DVGA field. 
// Software should determine who uses them. Please note that if both processors 
// attempt to control it, the resulting setting will be the two settings ORed 
// together. 
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
#define LRFDRFE_GAINCTL_BDE2DVGA_W                                           2U
#define LRFDRFE_GAINCTL_BDE2DVGA_M                                  0x0000000CU
#define LRFDRFE_GAINCTL_BDE2DVGA_S                                           2U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN8                              0x0000000CU
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN4                              0x00000008U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN2                              0x00000004U
#define LRFDRFE_GAINCTL_BDE2DVGA_GAIN1                              0x00000000U

// Field:   [1:0] BDE1DVGA 
//
// DVGA settings for BDE1. 
//
// The DVGA control for BDE1 is shared with the MCE in its 
// LRFDMDM:DEMMISC3.BDE1DVGA field. 
// Software should determine who uses them. Please note that if both processors 
// attempt to control it, the resulting setting will be the two settings ORed 
// together. 
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
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
// Measurement type 
// ENUMs: 
// PERIODIC                 Periodic mode 
// ONESHOT                  One-shot mode 
#define LRFDRFE_MAGNCTL0_PERMODE                                    0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_M                                  0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_S                                          12U
#define LRFDRFE_MAGNCTL0_PERMODE_PERIODIC                           0x00001000U
#define LRFDRFE_MAGNCTL0_PERMODE_ONESHOT                            0x00000000U

// Field:  [11:8] SCL 
//
// Scaling factor 
//
// Scaling factor = 1/2^(SCL). 
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
// Accumulation period in incoming samples 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Measurement type 
// ENUMs: 
// PERIODIC                 Periodic mode 
// ONESHOT                  One-shot mode 
#define LRFDRFE_MAGNCTL1_PERMODE                                    0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_M                                  0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_S                                          12U
#define LRFDRFE_MAGNCTL1_PERMODE_PERIODIC                           0x00001000U
#define LRFDRFE_MAGNCTL1_PERMODE_ONESHOT                            0x00000000U

// Field:  [11:8] SCL 
//
// Scaling factor 
//
// Scaling factor = 1/2^(SCL). 
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
// Accumulation period in incoming samples 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Spare bits to analog reserved for future use 
// ENUMs: 
// EN                       Enable IFAMP 
// DIS                      Disable IFAMP 
#define LRFDRFE_LNA_SPARE_W                                                  8U
#define LRFDRFE_LNA_SPARE_M                                         0x0000FF00U
#define LRFDRFE_LNA_SPARE_S                                                  8U
#define LRFDRFE_LNA_SPARE_EN                                        0x00000100U
#define LRFDRFE_LNA_SPARE_DIS                                       0x00000000U

// Field:   [7:4] TRIM 
//
// LNA trim 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_LNA_TRIM_W                                                   4U
#define LRFDRFE_LNA_TRIM_M                                          0x000000F0U
#define LRFDRFE_LNA_TRIM_S                                                   4U
#define LRFDRFE_LNA_TRIM_ONES                                       0x000000F0U
#define LRFDRFE_LNA_TRIM_ZEROS                                      0x00000000U

// Field:     [3] BIAS 
//
// BIAS current selection 
// ENUMs: 
// INT                      IPTAT bias currents are from bias circuit inside 
//                          LRF_FRONTEND 
// BGAP                     IPTAT bias currents are from bandgap 
#define LRFDRFE_LNA_BIAS                                            0x00000008U
#define LRFDRFE_LNA_BIAS_M                                          0x00000008U
#define LRFDRFE_LNA_BIAS_S                                                   3U
#define LRFDRFE_LNA_BIAS_INT                                        0x00000008U
#define LRFDRFE_LNA_BIAS_BGAP                                       0x00000000U

// Field:   [2:1] IB 
//
// LNA bias current control 
//
// IB is trimmed at probe. Default is 1. 
// ENUMs: 
// MAX                      Maximum IB 
// MIN                      Minimum IB 
#define LRFDRFE_LNA_IB_W                                                     2U
#define LRFDRFE_LNA_IB_M                                            0x00000006U
#define LRFDRFE_LNA_IB_S                                                     1U
#define LRFDRFE_LNA_IB_MAX                                          0x00000006U
#define LRFDRFE_LNA_IB_MIN                                          0x00000000U

// Field:     [0] EN 
//
// LNA enable 
// ENUMs: 
// ON                       Enable LNA 
// OFF                      Disable LNA 
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
// RFLDO output voltage trim 
//
// Default value: 84 (1.3V), 127 = Bypass. 
// ENUMs: 
// BYPASS                   Regulator is in bypass mode 
// MAX                      Maximum output voltage 
// MIN                      Minimum output voltage 
#define LRFDRFE_IFAMPRFLDO_TRIM_W                                            7U
#define LRFDRFE_IFAMPRFLDO_TRIM_M                                   0x0000FE00U
#define LRFDRFE_IFAMPRFLDO_TRIM_S                                            9U
#define LRFDRFE_IFAMPRFLDO_TRIM_BYPASS                              0x0000FE00U
#define LRFDRFE_IFAMPRFLDO_TRIM_MAX                                 0x0000FC00U
#define LRFDRFE_IFAMPRFLDO_TRIM_MIN                                 0x00000000U

// Field:     [8] EN 
//
// Regulator enable 
// ENUMs: 
// EN                       Enable regulator 
// DIS                      Disable regulator 
#define LRFDRFE_IFAMPRFLDO_EN                                       0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_M                                     0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_S                                              8U
#define LRFDRFE_IFAMPRFLDO_EN_EN                                    0x00000100U
#define LRFDRFE_IFAMPRFLDO_EN_DIS                                   0x00000000U

// Field:   [7:4] AAFCAP 
//
// AAF capacitor control 
// ENUMs: 
// MAX                      Largest capacitance on IFAMP output. Low BW 
// MIN                      Smallest capacitance on IFAMP output. High BW. 
#define LRFDRFE_IFAMPRFLDO_AAFCAP_W                                          4U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_M                                 0x000000F0U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_S                                          4U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_MAX                               0x000000F0U
#define LRFDRFE_IFAMPRFLDO_AAFCAP_MIN                               0x00000000U

// Field:   [3:1] IFAMPIB 
//
// IFAMP bias current control 
//
// Default is 2. 
// ENUMs: 
// MAX                      Max IB 
// MIN                      Minimum IB 
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_W                                         3U
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_M                                0x0000000EU
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_S                                         1U
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_MAX                              0x0000000EU
#define LRFDRFE_IFAMPRFLDO_IFAMPIB_MIN                              0x00000000U

// Field:     [0] IFAMP 
//
// IFAMP enable 
// ENUMs: 
// EN                       Enable IFAMP 
// DIS                      Disable IFAMP 
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
// Reserved 
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is 0 
#define LRFDRFE_PA0_SPARE15                                         0x00008000U
#define LRFDRFE_PA0_SPARE15_M                                       0x00008000U
#define LRFDRFE_PA0_SPARE15_S                                               15U
#define LRFDRFE_PA0_SPARE15_ONE                                     0x00008000U
#define LRFDRFE_PA0_SPARE15_ZERO                                    0x00000000U

// Field:    [14] MODE 
//
// PA power mode 
// ENUMs: 
// HIGH                     High power mode, max 8 dBm 
// LOW                      Low power mode, max 3 dBm 
#define LRFDRFE_PA0_MODE                                            0x00004000U
#define LRFDRFE_PA0_MODE_M                                          0x00004000U
#define LRFDRFE_PA0_MODE_S                                                  14U
#define LRFDRFE_PA0_MODE_HIGH                                       0x00004000U
#define LRFDRFE_PA0_MODE_LOW                                        0x00000000U

// Field: [13:11] GAIN 
//
// Gain control in 8dBm PA 1st stage 
// ENUMs: 
// MAX                      Maximum gain 
// MIN                      Minimum gain 
#define LRFDRFE_PA0_GAIN_W                                                   3U
#define LRFDRFE_PA0_GAIN_M                                          0x00003800U
#define LRFDRFE_PA0_GAIN_S                                                  11U
#define LRFDRFE_PA0_GAIN_MAX                                        0x00003800U
#define LRFDRFE_PA0_GAIN_MIN                                        0x00000000U

// Field:  [10:5] IB 
//
// PA power control 
// ENUMs: 
// MAX                      Maximum output power 
// MIN                      Minimum output power 
#define LRFDRFE_PA0_IB_W                                                     6U
#define LRFDRFE_PA0_IB_M                                            0x000007E0U
#define LRFDRFE_PA0_IB_S                                                     5U
#define LRFDRFE_PA0_IB_MAX                                          0x000007E0U
#define LRFDRFE_PA0_IB_MIN                                          0x00000000U

// Field:   [4:0] TRIM 
//
// Bias Current Trim 
//
// Setting shall provide constant output power over process and temperature. 
// Current changes linearily with setting. 
//
// Default value: 16 
// ENUMs: 
// MAX                      Maximum bias current 
// MIN                      Minimum bias current 
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
// Spare bits to analog, reserved for future use. 
// ENUMs: 
// MAX                      Longest ramp time 
// MIN                      Shortest ramp time 
#define LRFDRFE_PA1_SPARE_W                                                  9U
#define LRFDRFE_PA1_SPARE_M                                         0x0000FF80U
#define LRFDRFE_PA1_SPARE_S                                                  7U
#define LRFDRFE_PA1_SPARE_MAX                                       0x00000180U
#define LRFDRFE_PA1_SPARE_MIN                                       0x00000000U

// Field:     [6] MIXATST 
//
// Control of mixer outputs through ATEST 
// ENUMs: 
// EN                       Mixers are available on ATEST 
// DIS                      Mixers are not available on ATEST 
#define LRFDRFE_PA1_MIXATST                                         0x00000040U
#define LRFDRFE_PA1_MIXATST_M                                       0x00000040U
#define LRFDRFE_PA1_MIXATST_S                                                6U
#define LRFDRFE_PA1_MIXATST_EN                                      0x00000040U
#define LRFDRFE_PA1_MIXATST_DIS                                     0x00000000U

// Field:     [5] LDOITST 
//
// Control of current test signal through ITEST 
// ENUMs: 
// EN                       Current test signal is available through ITEST 
// DIS                      Current test signal not available through ITEST 
#define LRFDRFE_PA1_LDOITST                                         0x00000020U
#define LRFDRFE_PA1_LDOITST_M                                       0x00000020U
#define LRFDRFE_PA1_LDOITST_S                                                5U
#define LRFDRFE_PA1_LDOITST_EN                                      0x00000020U
#define LRFDRFE_PA1_LDOITST_DIS                                     0x00000000U

// Field:     [4] LDOATST 
//
// Control of LDO output voltage through ATEST 
// ENUMs: 
// EN                       LDO output voltage is available through ATEST 
// DIS                      LDO output voltage not available through ATEST 
#define LRFDRFE_PA1_LDOATST                                         0x00000010U
#define LRFDRFE_PA1_LDOATST_M                                       0x00000010U
#define LRFDRFE_PA1_LDOATST_S                                                4U
#define LRFDRFE_PA1_LDOATST_EN                                      0x00000010U
#define LRFDRFE_PA1_LDOATST_DIS                                     0x00000000U

// Field:   [3:2] RC 
//
// Adjustment of on/off PA ramp time. 
// ENUMs: 
// MAX                      Longest ramp time 
// MIN                      Shortest ramp time 
#define LRFDRFE_PA1_RC_W                                                     2U
#define LRFDRFE_PA1_RC_M                                            0x0000000CU
#define LRFDRFE_PA1_RC_S                                                     2U
#define LRFDRFE_PA1_RC_MAX                                          0x0000000CU
#define LRFDRFE_PA1_RC_MIN                                          0x00000000U

// Field:     [1] RAMP 
//
// PA RAMP control 
//
// Field can be set together with EN to ramp PA on. 
// Field must be cleared before EN to ramp PA down. 
// ENUMs: 
// UP                       Ramp up 
// DOWN                     Ramp down 
#define LRFDRFE_PA1_RAMP                                            0x00000002U
#define LRFDRFE_PA1_RAMP_M                                          0x00000002U
#define LRFDRFE_PA1_RAMP_S                                                   1U
#define LRFDRFE_PA1_RAMP_UP                                         0x00000002U
#define LRFDRFE_PA1_RAMP_DOWN                                       0x00000000U

// Field:     [0] EN 
//
// PA enable 
// ENUMs: 
// EN                       Enable PA 
// DIS                      Disable PA 
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
// Reserved for future use 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// IFADC external clock control 
//
// IFADC can use external clock from pad. 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_IFADC0_EXTCLK                                       0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_M                                     0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_S                                             15U
#define LRFDRFE_IFADC0_EXTCLK_EN                                    0x00008000U
#define LRFDRFE_IFADC0_EXTCLK_DIS                                   0x00000000U

// Field: [14:12] DITHERTRIM 
//
// Dither current trim 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADC0_DITHERTRIM_W                                          3U
#define LRFDRFE_IFADC0_DITHERTRIM_M                                 0x00007000U
#define LRFDRFE_IFADC0_DITHERTRIM_S                                         12U
#define LRFDRFE_IFADC0_DITHERTRIM_ONES                              0x00007000U
#define LRFDRFE_IFADC0_DITHERTRIM_ZEROS                             0x00000000U

// Field: [11:10] DITHEREN 
//
// Dither control 
//
// Enable a random noise generator to inject weak pseudo random noise into the 
// ADC loop to randomize and smooth out possible idle tones. 
// NOTE: This field may only change during DTC-reset or while the clock is 
// inactive! 
// ENUMs: 
// ENG                      All the bits are 1 
// ENSD                     All the bits are 1 
// ENS                      All the bits are 1 
// DIS                      All the bits are 0 
#define LRFDRFE_IFADC0_DITHEREN_W                                            2U
#define LRFDRFE_IFADC0_DITHEREN_M                                   0x00000C00U
#define LRFDRFE_IFADC0_DITHEREN_S                                           10U
#define LRFDRFE_IFADC0_DITHEREN_ENG                                 0x00000C00U
#define LRFDRFE_IFADC0_DITHEREN_ENSD                                0x00000800U
#define LRFDRFE_IFADC0_DITHEREN_ENS                                 0x00000400U
#define LRFDRFE_IFADC0_DITHEREN_DIS                                 0x00000000U

// Field:     [9] ADCIEN 
//
// I modulator control 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_IFADC0_ADCIEN                                       0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_M                                     0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_S                                              9U
#define LRFDRFE_IFADC0_ADCIEN_EN                                    0x00000200U
#define LRFDRFE_IFADC0_ADCIEN_DIS                                   0x00000000U

// Field:     [8] ADCQEN 
//
// Q modulator control 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDRFE_IFADC0_ADCQEN                                       0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_M                                     0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_S                                              8U
#define LRFDRFE_IFADC0_ADCQEN_EN                                    0x00000100U
#define LRFDRFE_IFADC0_ADCQEN_DIS                                   0x00000000U

// Field:   [7:4] INT2ADJ 
//
// GM trim 
//
// Trims the gm cell for the second integrator. Larger value means lower gm. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADC0_INT2ADJ_W                                             4U
#define LRFDRFE_IFADC0_INT2ADJ_M                                    0x000000F0U
#define LRFDRFE_IFADC0_INT2ADJ_S                                             4U
#define LRFDRFE_IFADC0_INT2ADJ_ONES                                 0x000000F0U
#define LRFDRFE_IFADC0_INT2ADJ_ZEROS                                0x00000000U

// Field:   [3:2] AAFCAP 
//
//  AAF bandwidth trim 
// ENUMs: 
// ENG                      All the bits are 1 
// ENSD                     All the bits are 1 
// ENS                      All the bits are 1 
// DIS                      All the bits are 0 
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
// Internal feedback DAC mode 
// ENUMs: 
// EN                       The feedback DAC uses NRZ mode. (Default) 
// DIS                      The feedback DAC uses RZ mode 
#define LRFDRFE_IFADC1_NRZ                                          0x00008000U
#define LRFDRFE_IFADC1_NRZ_M                                        0x00008000U
#define LRFDRFE_IFADC1_NRZ_S                                                15U
#define LRFDRFE_IFADC1_NRZ_EN                                       0x00008000U
#define LRFDRFE_IFADC1_NRZ_DIS                                      0x00000000U

// Field:  [14:9] TRIM 
//
// Feedback DAC trim 
//
// Larger trim means larger current. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADC1_TRIM_W                                                6U
#define LRFDRFE_IFADC1_TRIM_M                                       0x00007E00U
#define LRFDRFE_IFADC1_TRIM_S                                                9U
#define LRFDRFE_IFADC1_TRIM_ONES                                    0x00007E00U
#define LRFDRFE_IFADC1_TRIM_ZEROS                                   0x00000000U

// Field:     [7] RSTN 
//
// IFADC DTC reset 
// ENUMs: 
// DIS                      DTCs are not reset 
// EN                       DTCs are reset 
#define LRFDRFE_IFADC1_RSTN                                         0x00000080U
#define LRFDRFE_IFADC1_RSTN_M                                       0x00000080U
#define LRFDRFE_IFADC1_RSTN_S                                                7U
#define LRFDRFE_IFADC1_RSTN_DIS                                     0x00000080U
#define LRFDRFE_IFADC1_RSTN_EN                                      0x00000000U

// Field:     [6] CLKGEN 
//
// IFADC clock generator 
// ENUMs: 
// EN                       Internal clock generator module is enabled 
// DIS                      Internal clock generator module is disabled 
#define LRFDRFE_IFADC1_CLKGEN                                       0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_M                                     0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_S                                              6U
#define LRFDRFE_IFADC1_CLKGEN_EN                                    0x00000040U
#define LRFDRFE_IFADC1_CLKGEN_DIS                                   0x00000000U

// Field:     [5] ADCDIGCLK 
//
// IFADC clock to decimator 
// ENUMs: 
// EN                       Clock to decimator enabled 
// DIS                      Clock to decimator disabled 
#define LRFDRFE_IFADC1_ADCDIGCLK                                    0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_M                                  0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_S                                           5U
#define LRFDRFE_IFADC1_ADCDIGCLK_EN                                 0x00000020U
#define LRFDRFE_IFADC1_ADCDIGCLK_DIS                                0x00000000U

// Field:     [4] ADCLFSROUT 
//
// ADC test mode 
// ENUMs: 
// EN                       The LFSR test output is connected to the ADC 
//                          output 
// DIS                      The quantizer output is connected to the ADC 
//                          output 
#define LRFDRFE_IFADC1_ADCLFSROUT                                   0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_M                                 0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_S                                          4U
#define LRFDRFE_IFADC1_ADCLFSROUT_EN                                0x00000010U
#define LRFDRFE_IFADC1_ADCLFSROUT_DIS                               0x00000000U

// Field:   [3:1] LPFTSTMODE 
//
// Currently not in use. For future test mode implementations. 
// ENUMs: 
// EN                       All the bits are 1 
// DIS                      All the bits are 0 
#define LRFDRFE_IFADC1_LPFTSTMODE_W                                          3U
#define LRFDRFE_IFADC1_LPFTSTMODE_M                                 0x0000000EU
#define LRFDRFE_IFADC1_LPFTSTMODE_S                                          1U
#define LRFDRFE_IFADC1_LPFTSTMODE_EN                                0x00000002U
#define LRFDRFE_IFADC1_LPFTSTMODE_DIS                               0x00000000U

// Field:     [0] INVCLKOUT 
//
// Control phase inversion of IFADC clock output 
// ENUMs: 
// EN                       Invert IFADC output clock phase (default) 
// DIS                      Keep default IFADC output clock phase 
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
// GM trim for the third feedforward cell 
//
// Larger trim means lower gm. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADCLF_FF3_W                                                4U
#define LRFDRFE_IFADCLF_FF3_M                                       0x0000F000U
#define LRFDRFE_IFADCLF_FF3_S                                               12U
#define LRFDRFE_IFADCLF_FF3_ONES                                    0x0000F000U
#define LRFDRFE_IFADCLF_FF3_ZEROS                                   0x00000000U

// Field:  [11:8] FF2 
//
// GM trim for the second feedforward cell 
//
// Larger trim means lower gm. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADCLF_FF2_W                                                4U
#define LRFDRFE_IFADCLF_FF2_M                                       0x00000F00U
#define LRFDRFE_IFADCLF_FF2_S                                                8U
#define LRFDRFE_IFADCLF_FF2_ONES                                    0x00000F00U
#define LRFDRFE_IFADCLF_FF2_ZEROS                                   0x00000000U

// Field:   [7:4] FF1 
//
// GM trim for the first feedforward cell 
//
// Larger trim means lower gm. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADCLF_FF1_W                                                4U
#define LRFDRFE_IFADCLF_FF1_M                                       0x000000F0U
#define LRFDRFE_IFADCLF_FF1_S                                                4U
#define LRFDRFE_IFADCLF_FF1_ONES                                    0x000000F0U
#define LRFDRFE_IFADCLF_FF1_ZEROS                                   0x00000000U

// Field:   [3:0] INT3 
//
// GM trim for the third integrator 
//
// Larger trim means lower gm. 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
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
// Currently not in use. 2 bit signal to program the clock delay in the clock 
// generator circuit. 
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_W                                      2U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_M                             0x0000C000U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_S                                     14U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_ONES                          0x0000C000U
#define LRFDRFE_IFADCQUANT_CLKDLYTRIM_ZEROS                         0x00000000U

// Field:  [13:9] DBGCALVALIN 
//
// Input test calibration value to quantizer calibration block, used in debug 
// mode. 
// ENUMs: 
// ONES                     All the bits are ONES 
// ZEROS                    All the bits are 0 
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_W                                     5U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_M                            0x00003E00U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_S                                     9U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_ONES                         0x00003E00U
#define LRFDRFE_IFADCQUANT_DBGCALVALIN_ZEROS                        0x00000000U

// Field:     [8] DBGCALLEG 
//
// Select which leg to observe in calibration debug mode 
// ENUMs: 
// NEG                      Negative leg 
// POS                      Positive leg 
#define LRFDRFE_IFADCQUANT_DBGCALLEG                                0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_M                              0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_S                                       8U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_NEG                            0x00000100U
#define LRFDRFE_IFADCQUANT_DBGCALLEG_POS                            0x00000000U

// Field:   [7:6] DBGCALMQ 
//
// Quantizer calibration mode for Q modulator 
//
// This signal should have a large stability window, and is for internal use 
// only! 
// ENUMs: 
// DBGCAL_QMODB             UNCLEAR_Enable quantizer calibration mode. 
// DBGCAL_QMODP             Enable quantizer calibration mode for Positive 
//                          comparator in Q modulator. 
// DBGCAL_QMODN             Enable quantizer calibration mode for Negative 
//                          comparator in Q modulator. 
// DBGCAL_QMODZ             Disable quantizer calibration mode.(Default) 
#define LRFDRFE_IFADCQUANT_DBGCALMQ_W                                        2U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_M                               0x000000C0U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_S                                        6U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODB                    0x000000C0U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODP                    0x00000080U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODN                    0x00000040U
#define LRFDRFE_IFADCQUANT_DBGCALMQ_DBGCAL_QMODZ                    0x00000000U

// Field:   [5:4] DBGCALMI 
//
// Quantizer calibration mode for I modulator. 
//
// This signal should have a large stability window, and is for internal use 
// only! 
// ENUMs: 
// DBGCAL_IMODB             UNCLEAR_Enable quantizer calibration mode. 
// DBGCAL_IMODP             Enable quantizer calibration mode for Positive 
//                          comparator in I modulator. 
// DBGCAL_IMODN             Enable quantizer calibration mode for Negative 
//                          comparator in I modulator. 
// DBGCAL_IMODZ             Disable quantizer calibration mode.(Default) 
#define LRFDRFE_IFADCQUANT_DBGCALMI_W                                        2U
#define LRFDRFE_IFADCQUANT_DBGCALMI_M                               0x00000030U
#define LRFDRFE_IFADCQUANT_DBGCALMI_S                                        4U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODB                    0x00000030U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODP                    0x00000020U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODN                    0x00000010U
#define LRFDRFE_IFADCQUANT_DBGCALMI_DBGCAL_IMODZ                    0x00000000U

// Field:     [3] AUTOCAL 
//
// Auto calibration 
// ENUMs: 
// EN                       Enable the auto calibration logic (Default) 
// DIS                      Disable the auto calibration logic 
#define LRFDRFE_IFADCQUANT_AUTOCAL                                  0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_M                                0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_S                                         3U
#define LRFDRFE_IFADCQUANT_AUTOCAL_EN                               0x00000008U
#define LRFDRFE_IFADCQUANT_AUTOCAL_DIS                              0x00000000U

// Field:   [2:0] QUANTTHR 
//
// Quantizer treshold voltage trim 
// ENUMs: 
// ONES                     All the bits are 1 
// ZEROS                    All the bits are 0 
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
// Connect VSSANA to atest 
// ENUMs: 
// EN                       Connected 
// DIS                      Not connected 
#define LRFDRFE_IFADCALDO_ATESTVSSANA                               0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_M                             0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_S                                     15U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_EN                            0x00008000U
#define LRFDRFE_IFADCALDO_ATESTVSSANA_DIS                           0x00000000U

// Field:  [13:8] TRIMOUT 
//
// Select which leg to observe in calibration debug mode 
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE_IFADCALDO_TRIMOUT_W                                          6U
#define LRFDRFE_IFADCALDO_TRIMOUT_M                                 0x00003F00U
#define LRFDRFE_IFADCALDO_TRIMOUT_S                                          8U
#define LRFDRFE_IFADCALDO_TRIMOUT_ONES                              0x00003F00U
#define LRFDRFE_IFADCALDO_TRIMOUT_ZEROS                             0x00000000U

// Field:     [7] DUMMY 
//
// Enable dummy load to improve performance for low load currents 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_DUMMY                                     0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_M                                   0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_S                                            7U
#define LRFDRFE_IFADCALDO_DUMMY_EN                                  0x00000080U
#define LRFDRFE_IFADCALDO_DUMMY_DIS                                 0x00000000U

// Field:     [6] ATESTOUT 
//
// Connect LDO output voltage to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_ATESTOUT                                  0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_M                                0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_S                                         6U
#define LRFDRFE_IFADCALDO_ATESTOUT_EN                               0x00000040U
#define LRFDRFE_IFADCALDO_ATESTOUT_DIS                              0x00000000U

// Field:     [5] ATSTLDOFB 
//
// Connect LDO feedback to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_ATSTLDOFB                                 0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_M                               0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_S                                        5U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_EN                              0x00000020U
#define LRFDRFE_IFADCALDO_ATSTLDOFB_DIS                             0x00000000U

// Field:     [4] ATESTERRAMP 
//
// Connect the error amplifier output to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_ATESTERRAMP                               0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_M                             0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_S                                      4U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_EN                            0x00000010U
#define LRFDRFE_IFADCALDO_ATESTERRAMP_DIS                           0x00000000U

// Field:     [3] ITEST 
//
// Connect test current to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_ITEST                                     0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_M                                   0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_S                                            3U
#define LRFDRFE_IFADCALDO_ITEST_EN                                  0x00000008U
#define LRFDRFE_IFADCALDO_ITEST_DIS                                 0x00000000U

// Field:     [2] BYPASS 
//
// Bypass LDO and short LDO output with vddana1p5v. The LDO needs to be enabled 
// to use bypass. 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCALDO_BYPASS                                    0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_M                                  0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_S                                           2U
#define LRFDRFE_IFADCALDO_BYPASS_EN                                 0x00000004U
#define LRFDRFE_IFADCALDO_BYPASS_DIS                                0x00000000U

// Field:     [1] CLAMP 
//
// Clamp the LDO output with diodes to ground 
//
// Not used by analog when CTL or BYPASS are set. 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled. The LDO output is shorted to ground when 
//                          disabled. 
#define LRFDRFE_IFADCALDO_CLAMP                                     0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_M                                   0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_S                                            1U
#define LRFDRFE_IFADCALDO_CLAMP_EN                                  0x00000002U
#define LRFDRFE_IFADCALDO_CLAMP_DIS                                 0x00000000U

// Field:     [0] CTL 
//
// Enable regulator for supplying analog domain of the adc 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
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
// Select which leg to observe in calibration debug mode 
// ENUMs: 
// ONES                     All the bits are one 
// ZEROS                    All the bits are zero 
#define LRFDRFE_IFADCDLDO_TRIMOUT_W                                          6U
#define LRFDRFE_IFADCDLDO_TRIMOUT_M                                 0x00003F00U
#define LRFDRFE_IFADCDLDO_TRIMOUT_S                                          8U
#define LRFDRFE_IFADCDLDO_TRIMOUT_ONES                              0x00003F00U
#define LRFDRFE_IFADCDLDO_TRIMOUT_ZEROS                             0x00000000U

// Field:     [7] DUMMY 
//
// Enable dummy load to improve performance for low load currents 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_DUMMY                                     0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_M                                   0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_S                                            7U
#define LRFDRFE_IFADCDLDO_DUMMY_EN                                  0x00000080U
#define LRFDRFE_IFADCDLDO_DUMMY_DIS                                 0x00000000U

// Field:     [6] ATESTOUT 
//
// Connect LDO output voltage to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_ATESTOUT                                  0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_M                                0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_S                                         6U
#define LRFDRFE_IFADCDLDO_ATESTOUT_EN                               0x00000040U
#define LRFDRFE_IFADCDLDO_ATESTOUT_DIS                              0x00000000U

// Field:     [5] ATSTBGP 
//
// Connect bandgap voltage to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_ATSTBGP                                   0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_M                                 0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_S                                          5U
#define LRFDRFE_IFADCDLDO_ATSTBGP_EN                                0x00000020U
#define LRFDRFE_IFADCDLDO_ATSTBGP_DIS                               0x00000000U

// Field:     [4] ATESTERRAMP 
//
// Connect the error amplifier output to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_ATESTERRAMP                               0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_M                             0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_S                                      4U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_EN                            0x00000010U
#define LRFDRFE_IFADCDLDO_ATESTERRAMP_DIS                           0x00000000U

// Field:     [3] ITEST 
//
// Connect test current to ATEST 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_ITEST                                     0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_M                                   0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_S                                            3U
#define LRFDRFE_IFADCDLDO_ITEST_EN                                  0x00000008U
#define LRFDRFE_IFADCDLDO_ITEST_DIS                                 0x00000000U

// Field:     [2] BYPASS 
//
// Bypass LDO and short LDO output with vddana1p5v. The LDO needs to be enabled 
// to use bypass. 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCDLDO_BYPASS                                    0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_M                                  0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_S                                           2U
#define LRFDRFE_IFADCDLDO_BYPASS_EN                                 0x00000004U
#define LRFDRFE_IFADCDLDO_BYPASS_DIS                                0x00000000U

// Field:     [1] CLAMP 
//
// Clamp the LDO output with diodes to ground 
//
// Not used by analog when CTL or BYPASS are set. 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled. The LDO output is shorted to ground when 
//                          disabled. 
#define LRFDRFE_IFADCDLDO_CLAMP                                     0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_M                                   0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_S                                            1U
#define LRFDRFE_IFADCDLDO_CLAMP_EN                                  0x00000002U
#define LRFDRFE_IFADCDLDO_CLAMP_DIS                                 0x00000000U

// Field:     [0] CTL 
//
// Enable regulator for supplying digital domain of the adc 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
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
// Drive an external current 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_IFADCTST_EXTCURR                                    0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_M                                  0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_S                                           7U
#define LRFDRFE_IFADCTST_EXTCURR_EN                                 0x00000080U
#define LRFDRFE_IFADCTST_EXTCURR_DIS                                0x00000000U

// Field:     [6] QCALDBIQ 
//
// Comparator select for calibration data output 
//
// Also look at the description of IFADCQUANT. 
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE_IFADCTST_QCALDBIQ                                   0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_M                                 0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_S                                          6U
#define LRFDRFE_IFADCTST_QCALDBIQ_COMP1                             0x00000040U
#define LRFDRFE_IFADCTST_QCALDBIQ_COMP0                             0x00000000U

// Field:     [5] QCALDBC 
//
// Select which quantizer comparator to mux out calibration data from 
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE_IFADCTST_QCALDBC                                    0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_M                                  0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_S                                           5U
#define LRFDRFE_IFADCTST_QCALDBC_COMP1                              0x00000020U
#define LRFDRFE_IFADCTST_QCALDBC_COMP0                              0x00000000U

// Field:   [4:0] SEL 
//
// Select which internal net to probe via atb. This bus goes to a 6-32 bit 
// decoder. 
// ENUMs: 
// EXTCLKN1                 External ADC clock through ADC_TEST_N (N1 
//                          internally). The the clock should be a 200MHz 
//                          sine wave (it is divided internally to 100MHz). 
// NONE                     ADC_TEST_P and ADC_TEST_N tristated (Default) 
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
// ATEST mux 0 control 
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
// Bandgap reference bypass control 
// ENUMs: 
// BPDIS                    Bandgap reference bypass disabled 
// BPEN                     Bandgap reference bypass enabled. 
#define LRFDRFE_ATSTREFH_VREFBPDIS                                  0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_M                                0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_S                                        15U
#define LRFDRFE_ATSTREFH_VREFBPDIS_BPDIS                            0x00008000U
#define LRFDRFE_ATSTREFH_VREFBPDIS_BPEN                             0x00000000U

// Field: [14:10] IREFTRIM 
//
// LRF bias current trim 
// ENUMs: 
// ONES                     All bits are ones 
// ZEROS                    All bits are zero 
#define LRFDRFE_ATSTREFH_IREFTRIM_W                                          5U
#define LRFDRFE_ATSTREFH_IREFTRIM_M                                 0x00007C00U
#define LRFDRFE_ATSTREFH_IREFTRIM_S                                         10U
#define LRFDRFE_ATSTREFH_IREFTRIM_ONES                              0x00007C00U
#define LRFDRFE_ATSTREFH_IREFTRIM_ZEROS                             0x00000000U

// Field:     [9] BIAS 
//
// LRF reference system control 
// ENUMs: 
// EN                       Enabled 
// DIS                      Disabled 
#define LRFDRFE_ATSTREFH_BIAS                                       0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_M                                     0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_S                                              9U
#define LRFDRFE_ATSTREFH_BIAS_EN                                    0x00000200U
#define LRFDRFE_ATSTREFH_BIAS_DIS                                   0x00000000U

// Field:     [8] OUTPUT2 
//
// ATEST output 2 control 
// ENUMs: 
// EN                       The output is enabled 
// DIS                      Output is disabled 
#define LRFDRFE_ATSTREFH_OUTPUT2                                    0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_M                                  0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_S                                           8U
#define LRFDRFE_ATSTREFH_OUTPUT2_EN                                 0x00000100U
#define LRFDRFE_ATSTREFH_OUTPUT2_DIS                                0x00000000U

// Field:     [7] OUTPUT1 
//
// ATEST output 1 control 
// ENUMs: 
// EN                       The output is enabled 
// DIS                      Output is disabled 
#define LRFDRFE_ATSTREFH_OUTPUT1                                    0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_M                                  0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_S                                           7U
#define LRFDRFE_ATSTREFH_OUTPUT1_EN                                 0x00000080U
#define LRFDRFE_ATSTREFH_OUTPUT1_DIS                                0x00000000U

// Field:   [6:0] MUXMSB 
//
// ATEST mux 2 control 
// ENUMs: 
// DIVBUF_NMOS_BIAS         DIVBUF DC bias voltage for nmos switches 
// DIVBUF_PMOS_BIAS         DIVBUF DC bias voltage for pmos switches 
// REFSYS_IREF              REFSYS 4 uA output 
// IFADC_ATB                IFADC ATB 
// DIS                      No atest selected 
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
// Spare bits to MTDC 
// ENUMs: 
// DIS                      DIVIDER = 4 (for test purposes only) 
// EN                       DIVIDER = 2 
#define LRFDRFE_DCO_MTDCSPARE_W                                              2U
#define LRFDRFE_DCO_MTDCSPARE_M                                     0x00000600U
#define LRFDRFE_DCO_MTDCSPARE_S                                              9U
#define LRFDRFE_DCO_MTDCSPARE_DIS                                   0x00000200U
#define LRFDRFE_DCO_MTDCSPARE_EN                                    0x00000000U

// Field:   [8:7] SPARE7 
//
// Spare 
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is zero 
#define LRFDRFE_DCO_SPARE7_W                                                 2U
#define LRFDRFE_DCO_SPARE7_M                                        0x00000180U
#define LRFDRFE_DCO_SPARE7_S                                                 7U
#define LRFDRFE_DCO_SPARE7_ONE                                      0x00000080U
#define LRFDRFE_DCO_SPARE7_ZERO                                     0x00000000U

// Field:   [6:3] TAILRESTRIM 
//
// Trim bits to set DCO-amplitude. 
//
// 0x0: Disable DCO 
// 0x1: Min DCO amplitude (min-current) 
// 0xF: Max DCO amplitude  (max current) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DCO_TAILRESTRIM_W                                            4U
#define LRFDRFE_DCO_TAILRESTRIM_M                                   0x00000078U
#define LRFDRFE_DCO_TAILRESTRIM_S                                            3U
#define LRFDRFE_DCO_TAILRESTRIM_ALLONES                             0x00000078U
#define LRFDRFE_DCO_TAILRESTRIM_ALLZEROS                            0x00000000U

// Field:     [2] RTRIMCAP 
//
// RTRIM resistor cap control 
//
// Field enables cap across RTRIM resistor.  This can improve phase-noise in 
// some conditions, but can also result in DCO-instability (Not used). 
//
// INTERNAL NOTE: 
// renamed from EN_BIAS_CAP 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable(default) 
#define LRFDRFE_DCO_RTRIMCAP                                        0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_M                                      0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_S                                               2U
#define LRFDRFE_DCO_RTRIMCAP_EN                                     0x00000004U
#define LRFDRFE_DCO_RTRIMCAP_DIS                                    0x00000000U

// Field:     [1] CNRCAP 
//
// Corner-lots frequency tuning control 
// ENUMs: 
// _50MHZ                   50 MHz 
// DEFAULT                  Default 
#define LRFDRFE_DCO_CNRCAP                                          0x00000002U
#define LRFDRFE_DCO_CNRCAP_M                                        0x00000002U
#define LRFDRFE_DCO_CNRCAP_S                                                 1U
#define LRFDRFE_DCO_CNRCAP__50MHZ                                   0x00000002U
#define LRFDRFE_DCO_CNRCAP_DEFAULT                                  0x00000000U

// Field:     [0] CRSCAPCM 
//
// Coarse cap common mode control 
//
// INTERNAL NOTE: 
// *renamed from CAP_CM 
// ENUMs: 
// REDUCED                  Reduced common mode for greater reliability 
// DEFAULT                  Default 
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
// Adds 50mV to PM and NM bias voltages 
// ENUMs: 
// EN                       Peak detektor mode enabled, used in production 
//                          test 
// DIS                      Peak detector mode disabled, normal functional 
//                          mode 
#define LRFDRFE_DIV_PDET                                            0x00008000U
#define LRFDRFE_DIV_PDET_M                                          0x00008000U
#define LRFDRFE_DIV_PDET_S                                                  15U
#define LRFDRFE_DIV_PDET_EN                                         0x00008000U
#define LRFDRFE_DIV_PDET_DIS                                        0x00000000U

// Field: [14:12] NMIREFTRIM 
//
// Trim code for NMOS-Bias Voltage in the divider. 
//
// 0x0: Min Speed 
// 0x7: Max Speed 
//
// Default value: 0x4 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DIV_NMIREFTRIM_W                                             3U
#define LRFDRFE_DIV_NMIREFTRIM_M                                    0x00007000U
#define LRFDRFE_DIV_NMIREFTRIM_S                                            12U
#define LRFDRFE_DIV_NMIREFTRIM_ALLONES                              0x00007000U
#define LRFDRFE_DIV_NMIREFTRIM_ALLZEROS                             0x00000000U

// Field:  [11:9] PMIREFTRIM 
//
// Trim code for PMOS-Bias Voltage in the divider. 
//
// 0x0: Min Speed 
// 0x7: Max Speed 
//
// Default value: 0x4 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DIV_PMIREFTRIM_W                                             3U
#define LRFDRFE_DIV_PMIREFTRIM_M                                    0x00000E00U
#define LRFDRFE_DIV_PMIREFTRIM_S                                             9U
#define LRFDRFE_DIV_PMIREFTRIM_ALLONES                              0x00000E00U
#define LRFDRFE_DIV_PMIREFTRIM_ALLZEROS                             0x00000000U

// Field:     [8] TXBBOOST 
//
// Not connected 
// ENUMs: 
// INCREASED                High drive strength 
// DEFAULT                  Default drive strength 
#define LRFDRFE_DIV_TXBBOOST                                        0x00000100U
#define LRFDRFE_DIV_TXBBOOST_M                                      0x00000100U
#define LRFDRFE_DIV_TXBBOOST_S                                               8U
#define LRFDRFE_DIV_TXBBOOST_INCREASED                              0x00000100U
#define LRFDRFE_DIV_TXBBOOST_DEFAULT                                0x00000000U

// Field:     [7] S1GFRC 
//
// Not connected 
// ENUMs: 
// EN                       Enable force S1G power switch 
// DIS                      Disable force S1G power switch 
#define LRFDRFE_DIV_S1GFRC                                          0x00000080U
#define LRFDRFE_DIV_S1GFRC_M                                        0x00000080U
#define LRFDRFE_DIV_S1GFRC_S                                                 7U
#define LRFDRFE_DIV_S1GFRC_EN                                       0x00000080U
#define LRFDRFE_DIV_S1GFRC_DIS                                      0x00000000U

// Field:   [6:5] BUFGAIN 
//
// Not connected 
// ENUMs: 
// _60_PST                  60% of maximum gain 
// DONT_USE                 Same as _80_PST 
// _80_PST                  80% of maximum gain 
// MAX                      Maximum gain (default) 
#define LRFDRFE_DIV_BUFGAIN_W                                                2U
#define LRFDRFE_DIV_BUFGAIN_M                                       0x00000060U
#define LRFDRFE_DIV_BUFGAIN_S                                                5U
#define LRFDRFE_DIV_BUFGAIN__60_PST                                 0x00000060U
#define LRFDRFE_DIV_BUFGAIN_DONT_USE                                0x00000040U
#define LRFDRFE_DIV_BUFGAIN__80_PST                                 0x00000020U
#define LRFDRFE_DIV_BUFGAIN_MAX                                     0x00000000U

// Field:     [4] BIAS 
//
// Not connected 
// ENUMs: 
// DEFAULT                  Default bias 
// ALTERNATIVE              Alternative bias (for test purposes) 
#define LRFDRFE_DIV_BIAS                                            0x00000010U
#define LRFDRFE_DIV_BIAS_M                                          0x00000010U
#define LRFDRFE_DIV_BIAS_S                                                   4U
#define LRFDRFE_DIV_BIAS_DEFAULT                                    0x00000010U
#define LRFDRFE_DIV_BIAS_ALTERNATIVE                                0x00000000U

// Field:     [3] OUT 
//
// Divider output 
//
// Enable divider outputs to either sub-1GHz front-end or to 2.4 GHz front-end 
// when any of the following equals ENABLE: 
// - DIVCTL.RXPH0DIV 
// - DIVCTL.RXPH90DIV 
// - DIVCTL.TXPH0DIV 
// - DIVCTL.TXPH180DIV 
// ENUMs: 
// FE_2G4                   Enable outputs going to 2.4GHz front-end 
// FE_S1G                   Enable outputs going to sub-1GHz front-end 
#define LRFDRFE_DIV_OUT                                             0x00000008U
#define LRFDRFE_DIV_OUT_M                                           0x00000008U
#define LRFDRFE_DIV_OUT_S                                                    3U
#define LRFDRFE_DIV_OUT_FE_2G4                                      0x00000008U
#define LRFDRFE_DIV_OUT_FE_S1G                                      0x00000000U

// Field:   [2:0] RATIO 
//
// Divider ratio 
//
// Field sets the divider ratio between DCO frequency, FDCO,  and radio 
// frequency, FRF. 
//
// FRF = FDCO / DIVIDER 
// ENUMs: 
// DIV30                    DIVIDER = 30 
// DIV15                    DIVIDER = 15 
// DIV10                    DIVIDER = 10 
// DIV5                     DIVIDER = 5 
// DIV12                    DIVIDER = 12 
// DIV6                     DIVIDER = 6 
// DIV4                     DIVIDER = 4 (for test purposes only) 
// DIV2                     DIVIDER = 2 
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
// Spare bit 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_DIVLDO_SPARE15                                      0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_M                                    0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_S                                            15U
#define LRFDRFE_DIVLDO_SPARE15_ONES                                 0x00008000U
#define LRFDRFE_DIVLDO_SPARE15_ZEROS                                0x00000000U

// Field:  [14:8] VOUTTRIM 
//
// VOUT trim code 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_DIVLDO_VOUTTRIM_W                                            7U
#define LRFDRFE_DIVLDO_VOUTTRIM_M                                   0x00007F00U
#define LRFDRFE_DIVLDO_VOUTTRIM_S                                            8U
#define LRFDRFE_DIVLDO_VOUTTRIM_ONES                                0x00007F00U
#define LRFDRFE_DIVLDO_VOUTTRIM_ZEROS                               0x00000000U

// Field:     [7] ITST 
//
// ITEST block control 
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
#define LRFDRFE_DIVLDO_ITST                                         0x00000080U
#define LRFDRFE_DIVLDO_ITST_M                                       0x00000080U
#define LRFDRFE_DIVLDO_ITST_S                                                7U
#define LRFDRFE_DIVLDO_ITST_EN                                      0x00000080U
#define LRFDRFE_DIVLDO_ITST_DIS                                     0x00000000U

// Field:   [6:4] TMUX 
//
// TMUX control bits 
// ENUMs: 
// VDDR                     ATEST output is VDDR 
// LDO_OUT                  ATEST output is LDO output 
// GND                      ATEST output is grounded 
// OFF                      Normal mode 
#define LRFDRFE_DIVLDO_TMUX_W                                                3U
#define LRFDRFE_DIVLDO_TMUX_M                                       0x00000070U
#define LRFDRFE_DIVLDO_TMUX_S                                                4U
#define LRFDRFE_DIVLDO_TMUX_VDDR                                    0x00000040U
#define LRFDRFE_DIVLDO_TMUX_LDO_OUT                                 0x00000020U
#define LRFDRFE_DIVLDO_TMUX_GND                                     0x00000010U
#define LRFDRFE_DIVLDO_TMUX_OFF                                     0x00000000U

// Field:     [3] SPARE3 
//
// Spare bit 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DIVLDO_SPARE3                                       0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_M                                     0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_S                                              3U
#define LRFDRFE_DIVLDO_SPARE3_ONE                                   0x00000008U
#define LRFDRFE_DIVLDO_SPARE3_ZERO                                  0x00000000U

// Field:     [2] MODE 
//
// High BW operation control 
// ENUMs: 
// FAST                     Regulator in high bandwidth mode 
// NORM                     Regular low bandwidth of LDO 
#define LRFDRFE_DIVLDO_MODE                                         0x00000004U
#define LRFDRFE_DIVLDO_MODE_M                                       0x00000004U
#define LRFDRFE_DIVLDO_MODE_S                                                2U
#define LRFDRFE_DIVLDO_MODE_FAST                                    0x00000004U
#define LRFDRFE_DIVLDO_MODE_NORM                                    0x00000000U

// Field:     [1] BYPASS 
//
// Regulator bypass 
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE_DIVLDO_BYPASS                                       0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_M                                     0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_S                                              1U
#define LRFDRFE_DIVLDO_BYPASS_EN                                    0x00000002U
#define LRFDRFE_DIVLDO_BYPASS_DIS                                   0x00000000U

// Field:     [0] CTL 
//
// Regulator control 
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
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
// ITEST control 
//
// When enabled, it is possible to check current thorugh PASSFET. Scaled down 
// 110:1 
// ENUMs: 
// EN                       ITEST enabled 
// DIS                      ITEST Disabled 
#define LRFDRFE_TDCLDO_ITESTCTL                                     0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_M                                   0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_S                                           15U
#define LRFDRFE_TDCLDO_ITESTCTL_EN                                  0x00008000U
#define LRFDRFE_TDCLDO_ITESTCTL_DIS                                 0x00000000U

// Field:  [14:8] VOUTTRIM 
//
// VOUT trim code 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_TDCLDO_VOUTTRIM_W                                            7U
#define LRFDRFE_TDCLDO_VOUTTRIM_M                                   0x00007F00U
#define LRFDRFE_TDCLDO_VOUTTRIM_S                                            8U
#define LRFDRFE_TDCLDO_VOUTTRIM_ONES                                0x00007F00U
#define LRFDRFE_TDCLDO_VOUTTRIM_ZEROS                               0x00000000U

// Field:     [7] ITESTBUFCTL 
//
// ITEST BUFF block control 
//
// When enabled, it is possible to check current through buffer, scaled down 
// 12:1. 
// ENUMs: 
// EN                       ITEST mode in buffer is enabled 
// DIS                      ITEST mode in buffer is disabled 
#define LRFDRFE_TDCLDO_ITESTBUFCTL                                  0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_M                                0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_S                                         7U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_EN                               0x00000080U
#define LRFDRFE_TDCLDO_ITESTBUFCTL_DIS                              0x00000000U

// Field:   [6:4] TMUX 
//
// TMUX control bits 
// ENUMs: 
// VSSA                     ATEST output is VSSA 
// LDO_OUT                  ATEST output is LDO output 
// VDDA                     ATEST output is VDDA 
// OFF                      Normal mode 
#define LRFDRFE_TDCLDO_TMUX_W                                                3U
#define LRFDRFE_TDCLDO_TMUX_M                                       0x00000070U
#define LRFDRFE_TDCLDO_TMUX_S                                                4U
#define LRFDRFE_TDCLDO_TMUX_VSSA                                    0x00000040U
#define LRFDRFE_TDCLDO_TMUX_LDO_OUT                                 0x00000020U
#define LRFDRFE_TDCLDO_TMUX_VDDA                                    0x00000010U
#define LRFDRFE_TDCLDO_TMUX_OFF                                     0x00000000U

// Field:     [3] PDSEL 
//
// Selects between resistor or diode stack PD 
// ENUMs: 
// DIODE                    Diode stack 
// R                        R (default) 
#define LRFDRFE_TDCLDO_PDSEL                                        0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_M                                      0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_S                                               3U
#define LRFDRFE_TDCLDO_PDSEL_DIODE                                  0x00000008U
#define LRFDRFE_TDCLDO_PDSEL_R                                      0x00000000U

// Field:     [2] MODE 
//
// High BW operation control 
//
// Increase BW of slow loop (by increasing quiescent current). 
// ENUMs: 
// FAST                     Regulator in high bandwidth mode 
// NORM                     Regular low bandwidth of LDO 
#define LRFDRFE_TDCLDO_MODE                                         0x00000004U
#define LRFDRFE_TDCLDO_MODE_M                                       0x00000004U
#define LRFDRFE_TDCLDO_MODE_S                                                2U
#define LRFDRFE_TDCLDO_MODE_FAST                                    0x00000004U
#define LRFDRFE_TDCLDO_MODE_NORM                                    0x00000000U

// Field:     [1] BYPASS 
//
// Regulator bypass 
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE_TDCLDO_BYPASS                                       0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_M                                     0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_S                                              1U
#define LRFDRFE_TDCLDO_BYPASS_EN                                    0x00000002U
#define LRFDRFE_TDCLDO_BYPASS_DIS                                   0x00000000U

// Field:     [0] CTL 
//
// Regulator control 
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
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
// ITEST block control 
// ENUMs: 
// BOTH                     Enable both pass transistors 
// SECOND                   Enable second pass transistor 
// FIRST                    Enable first pass transistor 
// DIS                      Regulator is disabled 
#define LRFDRFE_DCOLDO0_ITST_W                                               2U
#define LRFDRFE_DCOLDO0_ITST_M                                      0x0000C000U
#define LRFDRFE_DCOLDO0_ITST_S                                              14U
#define LRFDRFE_DCOLDO0_ITST_BOTH                                   0x0000C000U
#define LRFDRFE_DCOLDO0_ITST_SECOND                                 0x00008000U
#define LRFDRFE_DCOLDO0_ITST_FIRST                                  0x00004000U
#define LRFDRFE_DCOLDO0_ITST_DIS                                    0x00000000U

// Field:  [13:8] SECONDTRIM 
//
// Trim for second LDO 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_DCOLDO0_SECONDTRIM_W                                         6U
#define LRFDRFE_DCOLDO0_SECONDTRIM_M                                0x00003F00U
#define LRFDRFE_DCOLDO0_SECONDTRIM_S                                         8U
#define LRFDRFE_DCOLDO0_SECONDTRIM_ONES                             0x00003F00U
#define LRFDRFE_DCOLDO0_SECONDTRIM_ZEROS                            0x00000000U

// Field:   [7:4] FIRSTTRIM 
//
// TRIM for first LDO 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_DCOLDO0_FIRSTTRIM_W                                          4U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_M                                 0x000000F0U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_S                                          4U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_ONES                              0x000000F0U
#define LRFDRFE_DCOLDO0_FIRSTTRIM_ZEROS                             0x00000000U

// Field:     [3] PDN 
//
// Pulldown control 
// ENUMs: 
// EN                       Pulldown 
// DIS                      No Pulldown 
#define LRFDRFE_DCOLDO0_PDN                                         0x00000008U
#define LRFDRFE_DCOLDO0_PDN_M                                       0x00000008U
#define LRFDRFE_DCOLDO0_PDN_S                                                3U
#define LRFDRFE_DCOLDO0_PDN_EN                                      0x00000008U
#define LRFDRFE_DCOLDO0_PDN_DIS                                     0x00000000U

// Field:     [2] BYPFIRST 
//
// Bypass first regulator 
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE_DCOLDO0_BYPFIRST                                    0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_M                                  0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_S                                           2U
#define LRFDRFE_DCOLDO0_BYPFIRST_EN                                 0x00000004U
#define LRFDRFE_DCOLDO0_BYPFIRST_DIS                                0x00000000U

// Field:     [1] BYPBOTH 
//
// Bypass LDO (both) 
// ENUMs: 
// EN                       Regulator is bypassed 
// DIS                      No bypass 
#define LRFDRFE_DCOLDO0_BYPBOTH                                     0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_M                                   0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_S                                            1U
#define LRFDRFE_DCOLDO0_BYPBOTH_EN                                  0x00000002U
#define LRFDRFE_DCOLDO0_BYPBOTH_DIS                                 0x00000000U

// Field:     [0] CTL 
//
// Regulator control 
// ENUMs: 
// EN                       Regulator is enabled 
// DIS                      Regulator is disabled 
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
// Select clock source to PLL 
// ENUMs: 
// BAW                      PLL clock source is BAW 
// XTAL                     PLL clock source is XTAL 
#define LRFDRFE_DCOLDO1_REFSRC                                      0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_M                                    0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_S                                            10U
#define LRFDRFE_DCOLDO1_REFSRC_BAW                                  0x00000400U
#define LRFDRFE_DCOLDO1_REFSRC_XTAL                                 0x00000000U

// Field:   [9:8] DIVATST 
//
// Divider ATEST control 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_DCOLDO1_DIVATST_W                                            2U
#define LRFDRFE_DCOLDO1_DIVATST_M                                   0x00000300U
#define LRFDRFE_DCOLDO1_DIVATST_S                                            8U
#define LRFDRFE_DCOLDO1_DIVATST_ONES                                0x00000300U
#define LRFDRFE_DCOLDO1_DIVATST_ZEROS                               0x00000000U

// Field:     [7] PERFM 
//
// Performance mode control 
//
// When enabled, the LDO uses more current to reduce flicker noise. 
// ENUMs: 
// EN                       Enabled (performance) 
// DIS                      Disabled (normal) 
#define LRFDRFE_DCOLDO1_PERFM                                       0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_M                                     0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_S                                              7U
#define LRFDRFE_DCOLDO1_PERFM_EN                                    0x00000080U
#define LRFDRFE_DCOLDO1_PERFM_DIS                                   0x00000000U

// Field:     [6] CHRGFILT 
//
// Charge the filters 
// ENUMs: 
// EN                       Charging enabled 
// DIS                      Charging disabled, normal operation 
#define LRFDRFE_DCOLDO1_CHRGFILT                                    0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_M                                  0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_S                                           6U
#define LRFDRFE_DCOLDO1_CHRGFILT_EN                                 0x00000040U
#define LRFDRFE_DCOLDO1_CHRGFILT_DIS                                0x00000000U

// Field:   [5:0] ATST 
//
// ATEST block control 
// ENUMs: 
// VSSANA                   VSSANA 
// FIRST_OUT                First LDO output 
// LDO_OUT                  LDO output 
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
// SPARE14 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE0_SPARE14_W                                               2U
#define LRFDRFE_PRE0_SPARE14_M                                      0x0000C000U
#define LRFDRFE_PRE0_SPARE14_S                                              14U
#define LRFDRFE_PRE0_SPARE14_ALLONES                                0x0000C000U
#define LRFDRFE_PRE0_SPARE14_ALLZEROS                               0x00000000U

// Field:  [13:8] PLLDIV1 
//
// PLL reference frequency divider 1 
//
// The value of DLOCTL0.LOOPUPD decides if this reference frequency is used. 
//
// FREFCLK = FXTAL / PLLDIV1 
//
// Examples: 
// 0: Illegal setting 
// 1: Illegal setting 
// 2: Divide by 2 
// ... 
// 63: Divide by 63 
//
// FREFCLK must be higher than or equal to 1 MHz in closed-loop state. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE0_PLLDIV1_W                                               6U
#define LRFDRFE_PRE0_PLLDIV1_M                                      0x00003F00U
#define LRFDRFE_PRE0_PLLDIV1_S                                               8U
#define LRFDRFE_PRE0_PLLDIV1_ALLONES                                0x00003F00U
#define LRFDRFE_PRE0_PLLDIV1_ALLZEROS                               0x00000000U

// Field:   [7:6] SPARE6 
//
// SPARE6 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE0_SPARE6_W                                                2U
#define LRFDRFE_PRE0_SPARE6_M                                       0x000000C0U
#define LRFDRFE_PRE0_SPARE6_S                                                6U
#define LRFDRFE_PRE0_SPARE6_ALLONES                                 0x000000C0U
#define LRFDRFE_PRE0_SPARE6_ALLZEROS                                0x00000000U

// Field:   [5:0] PLLDIV0 
//
// PLL reference frequency divider 0 
//
// The value of DLOCTL0.LOOPUPD decides if this reference frequency is used. 
//
// FREFCLK = FXTAL / PLLDIV0 
//
// Examples: 
// 0: Illegal setting 
// 1: Illegal setting 
// 2: Divide by 2 
// ... 
// 63: Divide by 63 
//
// FREFCLK must be higher than or equal to 1 MHz in closed-loop state. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Loop IIR filter bandwidth 
// ENUMs: 
// K16                      K=16 
// K8 
// K4 
// K2 
#define LRFDRFE_PRE1_IIRBW_W                                                 2U
#define LRFDRFE_PRE1_IIRBW_M                                        0x0000C000U
#define LRFDRFE_PRE1_IIRBW_S                                                14U
#define LRFDRFE_PRE1_IIRBW_K16                                      0x0000C000U
#define LRFDRFE_PRE1_IIRBW_K8                                       0x00008000U
#define LRFDRFE_PRE1_IIRBW_K4                                       0x00004000U
#define LRFDRFE_PRE1_IIRBW_K2                                       0x00000000U

// Field:    [13] IIRORD 
//
// IIR order 
// ENUMs: 
// SECOND                   Select second order IIR filter 
// FIRST                    Select first order IIR filter 
#define LRFDRFE_PRE1_IIRORD                                         0x00002000U
#define LRFDRFE_PRE1_IIRORD_M                                       0x00002000U
#define LRFDRFE_PRE1_IIRORD_S                                               13U
#define LRFDRFE_PRE1_IIRORD_SECOND                                  0x00002000U
#define LRFDRFE_PRE1_IIRORD_FIRST                                   0x00000000U

// Field:  [12:8] IIRDIV 
//
// IIR divider 
//
// FIIRCLK = FCKVD64 / (IIRDIV+1) 
//
// Examples: 
//
// 0: Clock is ckvd64/1 
// 1: Clock is ckvd64/2 
// ... 
// 31: Clock is ckvd64/32 
//
// INTERNAL NOTE: 
// * See the implementation spec for formula. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE1_IIRDIV_W                                                5U
#define LRFDRFE_PRE1_IIRDIV_M                                       0x00001F00U
#define LRFDRFE_PRE1_IIRDIV_S                                                8U
#define LRFDRFE_PRE1_IIRDIV_ALLONES                                 0x00001F00U
#define LRFDRFE_PRE1_IIRDIV_ALLZEROS                                0x00000000U

// Field:     [6] CALHSDDC 
//
// TDC calibration setting for HSDDC 
// ENUMs: 
// GATE                     Duty-cycling given by HSDDC 
// NOGATE                   No duty-cycling 
#define LRFDRFE_PRE1_CALHSDDC                                       0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_M                                     0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_S                                              6U
#define LRFDRFE_PRE1_CALHSDDC_GATE                                  0x00000040U
#define LRFDRFE_PRE1_CALHSDDC_NOGATE                                0x00000000U

// Field:   [5:0] HSDDC 
//
// TDC high-speed digital duty cycle 
//
// The TDC high-speed clock can always run or be duty cycled to save current 
// consumption. The minimum ON-time equals the reference clock source period 
// (PER). In this case, the clock starts to toggle 1/2 * PER before positive 
// edge of reference clock. If the clock runs for two periods, it starts to 
// toggle  1.5 * PER before the positve edge of the reference clock. In any 
// case, it toggles during the high time of reference clock source. 
//
// The field value must not be set higher than the minimum binary value of the 
// active reference clock divider. 
//
// Encoding: 
// 0: Enable clock to TDC always 
// 1: Enable clock to TDC always 
// 2: Enable clock to TDC for 1 PER 
// 3. Enable clock to TDC for 2 PER 
// ... 
// 63: Enable clock to TDC for 62 PER 
//
// INTERNAL NOTE: 
// * Value of 2 shall be used to save current consumption as long as there is 
// no or acceptable power noise/TDC modulation generated by this setting. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Mid calibration divider LSB 
//
// This field determines the reference frequency used during the mid SAR 
// calibration stages, according to: 
//
// FREFCLK = FXTAL / MIDCALDIV 
//
// Field encoding is unsigned integer: 
// 0-7: Illegal setting 
// 8: Divide by 8 
// 9: Divide by 9 
// .. 
// 1023: Divide by 1023 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE2_MIDCALDIVLSB_W                                          4U
#define LRFDRFE_PRE2_MIDCALDIVLSB_M                                 0x0000F000U
#define LRFDRFE_PRE2_MIDCALDIVLSB_S                                         12U
#define LRFDRFE_PRE2_MIDCALDIVLSB_ALLONES                           0x0000F000U
#define LRFDRFE_PRE2_MIDCALDIVLSB_ALLZEROS                          0x00000000U

// Field:  [11:6] CRSCALDIV 
//
// Coarse calibration divider 
//
// This field determines the reference frequency used during the coarse SAR 
// calibration stages, according to: 
//
// FREFCLK = FXTAL / CRSCALDIV 
//
// Field encoding is unsigned integer: 
// 0-7: Illegal setting 
// 8: Divide by 8 
// 9: Divide by 9 
// .. 
// 63: Divide by 63 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE2_CRSCALDIV_W                                             6U
#define LRFDRFE_PRE2_CRSCALDIV_M                                    0x00000FC0U
#define LRFDRFE_PRE2_CRSCALDIV_S                                             6U
#define LRFDRFE_PRE2_CRSCALDIV_ALLONES                              0x00000FC0U
#define LRFDRFE_PRE2_CRSCALDIV_ALLZEROS                             0x00000000U

// Field:   [5:0] FSMDIV 
//
// FSM divider 
//
// This field determines the clock frequency for FSM traversal through states 
// that does not affect calibration, according to: 
//
// FFSM = FXTAL / FSMDIV 
//
// Field encoding is unsigned integer: 
// 0-3: Illegal setting 
// 4: Divide by 4 
// 5: Divide by 5 
// .. 
// 63: Divide by 63 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Fine calibration divider 
//
// This field determines the reference frequency used to measure the DCO gain 
// (KDCO), according to: 
//
// FREFCLK = FXTAL / FINECALDIV 
//
// Field encoding is unsigned integer: 
// 0-7: Illegal setting 
// 8: Divide by 8 
// 9: Divide by 9 
// .. 
// 4095: Divide by 4095 
//
// Use a lower reference frequency to increases the KDCO estimation accuracy at 
// the cost of increased calibration time. The KDCO estimation takes 
// approximately 2 periods of the configured frequency. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PRE3_FINECALDIV_W                                           11U
#define LRFDRFE_PRE3_FINECALDIV_M                                   0x0000FFE0U
#define LRFDRFE_PRE3_FINECALDIV_S                                            5U
#define LRFDRFE_PRE3_FINECALDIV_ALLONES                             0x0000FFE0U
#define LRFDRFE_PRE3_FINECALDIV_ALLZEROS                            0x00000000U

// Field:   [4:0] MIDCALDIVMSB 
//
// Mid calibration divider MSB 
//
// This field determines the reference frequency used during the mid SAR 
// calibration stages, according to: 
//
// FREFCLK = FXTAL / MIDCALDIV 
//
// Field encoding is unsigned integer: 
// 0-7: Illegal setting 
// 8: Divide by 8 
// 9: Divide by 9 
// .. 
// 1023: Divide by 1023 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// SPARE15 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_CAL0_SPARE15                                        0x00008000U
#define LRFDRFE_CAL0_SPARE15_M                                      0x00008000U
#define LRFDRFE_CAL0_SPARE15_S                                              15U
#define LRFDRFE_CAL0_SPARE15_ONE                                    0x00008000U
#define LRFDRFE_CAL0_SPARE15_ZERO                                   0x00000000U

// Field:  [14:8] FCSTART 
//
// Fine code start 
//
// Fine code applied to DCO during all calibration states except during KDCO 
// estimation. The start code is then applied to DCO at start of phase 
// aquisition in state PLL_ST. Ensure that value is the aritmetic mean of 
// CAL1.FCBOT and CAL1.FCTOP. 
//
// Field encoding is <7u>. 
//
// INTERNAL NOTE: 
// * The value specified as start code will not be applied when moving from 
// open-loop to closed-loop PLL mode. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_CAL0_FCSTART_W                                               7U
#define LRFDRFE_CAL0_FCSTART_M                                      0x00007F00U
#define LRFDRFE_CAL0_FCSTART_S                                               8U
#define LRFDRFE_CAL0_FCSTART_ALLONES                                0x00007F00U
#define LRFDRFE_CAL0_FCSTART_ALLZEROS                               0x00000000U

// Field:     [7] CRS 
//
// Coarse calibration control 
// ENUMs: 
// EN                       Enable coarse calibration 
// DIS                      Disable coarse calibration 
#define LRFDRFE_CAL0_CRS                                            0x00000080U
#define LRFDRFE_CAL0_CRS_M                                          0x00000080U
#define LRFDRFE_CAL0_CRS_S                                                   7U
#define LRFDRFE_CAL0_CRS_EN                                         0x00000080U
#define LRFDRFE_CAL0_CRS_DIS                                        0x00000000U

// Field:     [6] MID 
//
// Mid calibration control 
// ENUMs: 
// EN                       Enable mid calibration 
// DIS                      Disable mid calibration 
#define LRFDRFE_CAL0_MID                                            0x00000040U
#define LRFDRFE_CAL0_MID_M                                          0x00000040U
#define LRFDRFE_CAL0_MID_S                                                   6U
#define LRFDRFE_CAL0_MID_EN                                         0x00000040U
#define LRFDRFE_CAL0_MID_DIS                                        0x00000000U

// Field:     [5] KTDC 
//
// KTDC estimation control 
//
// It's necessary to estimate the TDC gain to compute its' inverse, 
// CAL2.KTDCINV. The latter is used to normalize TDC integer result into 
// fractional CKVD periods. 
// ENUMs: 
// EN                       Enable TDC estimation 
// DIS                      Disable TDC estimation 
#define LRFDRFE_CAL0_KTDC                                           0x00000020U
#define LRFDRFE_CAL0_KTDC_M                                         0x00000020U
#define LRFDRFE_CAL0_KTDC_S                                                  5U
#define LRFDRFE_CAL0_KTDC_EN                                        0x00000020U
#define LRFDRFE_CAL0_KTDC_DIS                                       0x00000000U

// Field:     [4] KDCO 
//
// KDCO estimation control 
// ENUMs: 
// EN                       Enable KDCO estimation 
// DIS                      Disable KDCO estimation 
#define LRFDRFE_CAL0_KDCO                                           0x00000010U
#define LRFDRFE_CAL0_KDCO_M                                         0x00000010U
#define LRFDRFE_CAL0_KDCO_S                                                  4U
#define LRFDRFE_CAL0_KDCO_EN                                        0x00000010U
#define LRFDRFE_CAL0_KDCO_DIS                                       0x00000000U

// Field:   [3:2] TDCAVG 
//
// TDC average control 
//
// During TDC calibration the TDC measures a pulse of DLOCTL0.TDCSTOP duration. 
// The measurement is repeated 2^CAL0.TDCAVG times by the FSM and the 
// individual TDC results are accumulated and the final result is available in 
// TDCCAL.VAL. 
// ENUMs: 
// REPEAT_8_TIMES           Repeat measurement 8 times 
// REPEAT_4_TIMES           Repeat measurement 4 times 
// REPEAT_2_TIMES           Repeat measurement 2 times 
// REPEAT_1_TIME            Repeat measurement 1 time 
#define LRFDRFE_CAL0_TDCAVG_W                                                2U
#define LRFDRFE_CAL0_TDCAVG_M                                       0x0000000CU
#define LRFDRFE_CAL0_TDCAVG_S                                                2U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_8_TIMES                          0x0000000CU
#define LRFDRFE_CAL0_TDCAVG_REPEAT_4_TIMES                          0x00000008U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_2_TIMES                          0x00000004U
#define LRFDRFE_CAL0_TDCAVG_REPEAT_1_TIME                           0x00000000U

// Field:   [1:0] TDC_SPARE 
//
// TDC spare bits 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// SPARE15 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_CAL1_SPARE15                                        0x00008000U
#define LRFDRFE_CAL1_SPARE15_M                                      0x00008000U
#define LRFDRFE_CAL1_SPARE15_S                                              15U
#define LRFDRFE_CAL1_SPARE15_ONE                                    0x00008000U
#define LRFDRFE_CAL1_SPARE15_ZERO                                   0x00000000U

// Field:  [14:8] FCTOP 
//
// Fine code top 
//
// Fine code applied to DCO during KDCO estimation in FSM state FINE_TOP_ST. 
// Ensure that CAL0.FCSTART value is the aritmetic mean of CAL1.FCBOT and this 
// value. 
//
// Field encoding is <7u>. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_CAL1_FCTOP_W                                                 7U
#define LRFDRFE_CAL1_FCTOP_M                                        0x00007F00U
#define LRFDRFE_CAL1_FCTOP_S                                                 8U
#define LRFDRFE_CAL1_FCTOP_ALLONES                                  0x00007F00U
#define LRFDRFE_CAL1_FCTOP_ALLZEROS                                 0x00000000U

// Field:     [7] SPARE7 
//
// SPARE7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_CAL1_SPARE7                                         0x00000080U
#define LRFDRFE_CAL1_SPARE7_M                                       0x00000080U
#define LRFDRFE_CAL1_SPARE7_S                                                7U
#define LRFDRFE_CAL1_SPARE7_ONE                                     0x00000080U
#define LRFDRFE_CAL1_SPARE7_ZERO                                    0x00000000U

// Field:   [6:0] FCBOT 
//
// Fine code bottom 
//
// Fine code applied to DCO during KDCO estimation in FSM state FINE_BOT_ST. 
// Ensure that CAL0.FCSTART value is the aritmetic mean of this value and 
// CAL1.FCTOP. 
//
// Field encoding is <7u>. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// KTDC inverse 
//
// FW updates field with the inverse KTDC value before it enables KDCO 
// estimation. KTDC value is availble in TDCCAL.VAL. 
//
// One CKVD clock period is normalized to phase of 2^16, hence FW calculates 
// field value according to: 
//
// KTDCINV = 2^(16+CAL0.TDCAVG+DLOCTL0.TDCSTOP)/TDCCAL.VAL 
//
// Encoding is <0.16u>. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Addition path gain 
//
// The modulator resolution is given by: 
//
// MOD_RES = FRF / 2^(21+MOD0.CANPTHGAIN) Hz/LSB 
//
// This resolution is achieved when DC gain in addition and cancellation paths 
// are equal. To achieve this condition, the addtion path gain must account for 
// the estimated KDCO according to: 
//
// DTXGAIN = 2^14 * MOD_RES / KDCO =  FRF / KDCO / 2^(7+MOD0.CANPTHGAIN) 
//
// Encoding is <2.14u>. 
//
// INTERNAL NOTE: 
// * The shortest calibration time (1 MHz Fref) for KDCO estimation will give 
// around 0.2% uncertainty on the KDCO estimate, worst case. The resolution of 
// this field is 2^-14, and hence resolution is not limiting the quality. For 
// 25 kHz calibration time, the resolution is also better than the uncertainty. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Phase capture mode 
//
// Field decides if the phase capture mechanism is synchronous to phase valid 
// signal or not. Default is synchronous mode (0). 
// ENUMs: 
// ASYNC                    Phase capture mode is asyncrhonous 
// SYNC                     Phase capture mode is synchronous 
#define LRFDRFE_MISC0_PHCPT                                         0x00002000U
#define LRFDRFE_MISC0_PHCPT_M                                       0x00002000U
#define LRFDRFE_MISC0_PHCPT_S                                               13U
#define LRFDRFE_MISC0_PHCPT_ASYNC                                   0x00002000U
#define LRFDRFE_MISC0_PHCPT_SYNC                                    0x00000000U

// Field:    [12] TDCCALCORR 
//
// Detect and correct errors in TDC value during calibration 
//
// Value shall remain static after DLOCTL0.RSTN equals 1. 
// ENUMs: 
// EN                       Enable TDC error correction inside DLO. 
// DIS                      Disable TDC error correction inside DLO. 
#define LRFDRFE_MISC0_TDCCALCORR                                    0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_M                                  0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_S                                          12U
#define LRFDRFE_MISC0_TDCCALCORR_EN                                 0x00001000U
#define LRFDRFE_MISC0_TDCCALCORR_DIS                                0x00000000U

// Field:    [11] TDCMSBCORR 
//
// TDC MSB error correction control 
//
// Value shall remain static after DLOCTL0.RSTN equals 1. 
// ENUMs: 
// EN                       Enable TDC error correction inside DLO. 
// DIS                      Disable TDC error correction inside DLO. 
#define LRFDRFE_MISC0_TDCMSBCORR                                    0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_M                                  0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_S                                          11U
#define LRFDRFE_MISC0_TDCMSBCORR_EN                                 0x00000800U
#define LRFDRFE_MISC0_TDCMSBCORR_DIS                                0x00000000U

// Field:    [10] SDMDEM 
//
// SDM dynamic element matching control 
// ENUMs: 
// EN                       Enable dynamic element matching (recommended) 
// DIS                      Disable dynamic element matching 
#define LRFDRFE_MISC0_SDMDEM                                        0x00000400U
#define LRFDRFE_MISC0_SDMDEM_M                                      0x00000400U
#define LRFDRFE_MISC0_SDMDEM_S                                              10U
#define LRFDRFE_MISC0_SDMDEM_EN                                     0x00000400U
#define LRFDRFE_MISC0_SDMDEM_DIS                                    0x00000000U

// Field:   [9:8] DLYSDM 
//
// SDM delay match configuration 
//
// Fine tune latency for integer part of fine code. The delay should match 
// delay through SDM. 
// ENUMs: 
// CKVD16_3_PER             Delay integer fine code by 3 CKVD16 clock periods 
// CKVD16_2_PER             Delay integer fine code by 2 CKVD16 clock periods 
// CKVD16_1_PER             Delay integer fine code by 1 CKVD16 clock period 
// CKVD16_0_PER             Delay integer fine code by 0 CKVD16 clock periods 
#define LRFDRFE_MISC0_DLYSDM_W                                               2U
#define LRFDRFE_MISC0_DLYSDM_M                                      0x00000300U
#define LRFDRFE_MISC0_DLYSDM_S                                               8U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_3_PER                           0x00000300U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_2_PER                           0x00000200U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_1_PER                           0x00000100U
#define LRFDRFE_MISC0_DLYSDM_CKVD16_0_PER                           0x00000000U

// Field:     [6] DLYPHVALID 
//
// Phase valid delay 
// ENUMs: 
// CKVD16_1_PER             Delays the variable phase capture and hence the 
//                          phase error calculation with 1 CKVD16 clock 
//                          period. 
// CKVD16_0_PER             No additional delay on variable phase capture. 
#define LRFDRFE_MISC0_DLYPHVALID                                    0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_M                                  0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_S                                           6U
#define LRFDRFE_MISC0_DLYPHVALID_CKVD16_1_PER                       0x00000040U
#define LRFDRFE_MISC0_DLYPHVALID_CKVD16_0_PER                       0x00000000U

// Field:   [5:4] DLYCANCRS 
//
// Cancellation path coarse delay 
//
// Coarse tune latency for cancellation path in relation to the addition path 
// (when modulating). The final delay is the sum of coarse delay and fine 
// delay. 
// ENUMs: 
// CKVD64_3_PER             Delay by 3 CKVD64 clock periods 
// CKVD64_2_PER             Delay by 2 CKVD64 clock periods 
// CKVD64_1_PER             Delay by 1 CKVD64 clock period 
// CKVD64_0_PER             Delay by 0 CKVD64 clock periods 
#define LRFDRFE_MISC0_DLYCANCRS_W                                            2U
#define LRFDRFE_MISC0_DLYCANCRS_M                                   0x00000030U
#define LRFDRFE_MISC0_DLYCANCRS_S                                            4U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_3_PER                        0x00000030U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_2_PER                        0x00000020U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_1_PER                        0x00000010U
#define LRFDRFE_MISC0_DLYCANCRS_CKVD64_0_PER                        0x00000000U

// Field:   [3:2] DLYCANFINE 
//
// Cancellation path fine delay 
//
// Fine tune latency for cancellation path in relation to the addition path 
// (when modulating). The final delay is the sum of coarse delay and fine 
// delay. 
// ENUMs: 
// CKVD16_4_PER             Delay by 4 CKVD16 clock periods 
// CKVD16_3_PER             Delay by 3 CKVD16 clock periods 
// CKVD16_2_PER             Delay by 2 CKVD16 clock period 
// CKVD16_1_PER             Delay by 1 CKVD16 clock periods 
#define LRFDRFE_MISC0_DLYCANFINE_W                                           2U
#define LRFDRFE_MISC0_DLYCANFINE_M                                  0x0000000CU
#define LRFDRFE_MISC0_DLYCANFINE_S                                           2U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_4_PER                       0x0000000CU
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_3_PER                       0x00000008U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_2_PER                       0x00000004U
#define LRFDRFE_MISC0_DLYCANFINE_CKVD16_1_PER                       0x00000000U

// Field:   [1:0] DLYADD 
//
// Addition path delay 
//
// Field specifies additional latency on the modulation data towards antenna. 
// ENUMs: 
// CKVD64_3_PER             Delay by 3 CKVD64 clock periods 
// CKVD64_2_PER             Delay by 2 CKVD64 clock periods 
// CKVD64_1_PER             Delay by 1 CKVD64 clock period 
// CKVD64_0_PER             Delay by 0 CKVD64 clock periods 
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
// Bitmask to enable additive terms in INL correction 
//
// See implementation spec for details 
// ENUMs: 
// CKVD64                   ckvd64 clock used for update upper and lower DWA 
//                          DEM 
// CKCD16                   ckvd16 clock used for update upper and lower DWA 
//                          DEM 
#define LRFDRFE_MISC1_FCDEMCLK                                      0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_M                                    0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_S                                            14U
#define LRFDRFE_MISC1_FCDEMCLK_CKVD64                               0x00004000U
#define LRFDRFE_MISC1_FCDEMCLK_CKCD16                               0x00000000U

// Field: [13:12] FCDEMUPD 
//
// Configures dynamic element matching of fine code 
// ENUMs: 
// SDM_XOR_PH_ERR           phase_error[0] xor SDM[1] 
// SDM                      SDM[1] (this value depends on DEM for SDM) 
// PH_ERR                   phase_error[0]. (Phase error is 6.11s ) 
// DEFAULT                  Default: Update both DWAs always at rising edge of 
//                          selected clock 
#define LRFDRFE_MISC1_FCDEMUPD_W                                             2U
#define LRFDRFE_MISC1_FCDEMUPD_M                                    0x00003000U
#define LRFDRFE_MISC1_FCDEMUPD_S                                            12U
#define LRFDRFE_MISC1_FCDEMUPD_SDM_XOR_PH_ERR                       0x00003000U
#define LRFDRFE_MISC1_FCDEMUPD_SDM                                  0x00002000U
#define LRFDRFE_MISC1_FCDEMUPD_PH_ERR                               0x00001000U
#define LRFDRFE_MISC1_FCDEMUPD_DEFAULT                              0x00000000U

// Field:  [11:6] TDCINL 
//
// Bitmask to enable additive terms in INL correction 
//
// See implementation spec for details 
// ENUMs: 
// ONES                     All bits are one 
// ZEROS                    All bits are zero 
#define LRFDRFE_MISC1_TDCINL_W                                               6U
#define LRFDRFE_MISC1_TDCINL_M                                      0x00000FC0U
#define LRFDRFE_MISC1_TDCINL_S                                               6U
#define LRFDRFE_MISC1_TDCINL_ONES                                   0x00000FC0U
#define LRFDRFE_MISC1_TDCINL_ZEROS                                  0x00000000U

// Field:     [5] TDCINLCTL 
//
// Enables INL correction of TDC 
// ENUMs: 
// EN                       Enables INL correction of TDC 
// DIS                      Disabled INL correction 
#define LRFDRFE_MISC1_TDCINLCTL                                     0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_M                                   0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_S                                            5U
#define LRFDRFE_MISC1_TDCINLCTL_EN                                  0x00000020U
#define LRFDRFE_MISC1_TDCINLCTL_DIS                                 0x00000000U

// Field:     [4] PHINIT 
//
// Decides if there is known phase relationship between reference clock and RF 
// ENUMs: 
// UNKNOWN                  Unknown phase 
// KNOWN                    Known phase 
#define LRFDRFE_MISC1_PHINIT                                        0x00000010U
#define LRFDRFE_MISC1_PHINIT_M                                      0x00000010U
#define LRFDRFE_MISC1_PHINIT_S                                               4U
#define LRFDRFE_MISC1_PHINIT_UNKNOWN                                0x00000010U
#define LRFDRFE_MISC1_PHINIT_KNOWN                                  0x00000000U

// Field:     [3] SDMOOVRCTL 
//
// Force SDMOOVR towards DCO 
// ENUMs: 
// EN                       Enable SDM output override 
// DIS                      Disable SDM output override 
#define LRFDRFE_MISC1_SDMOOVRCTL                                    0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_M                                  0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_S                                           3U
#define LRFDRFE_MISC1_SDMOOVRCTL_EN                                 0x00000008U
#define LRFDRFE_MISC1_SDMOOVRCTL_DIS                                0x00000000U

// Field:   [2:0] SDMOOVR 
//
// SDM output code override 
//
// When MISC1.SDMOOVRCTL = EN, field value overrides the 3-bit SDM output to 
// DCO. 
// When MISC1.SDMOOVRCTL = DIS, SDM takes 8-bit input and modulates the 3-bit 
// output to DCO. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// FIR integral gain precision 
//
// When numerical value of KI is lower than 16-1/256, high precision can be 
// enabled. 
// FIR loop filter gets reinitialized with the current value whenever: 
// - DLO moves from calibration operation to closed-loop state. 
// - DLO moves from open-loop operation to closed-loop operation. 
// - DLO is in closed-loop operation and there is a change on loop control set. 
// See DLOCTL0.LOOPUPD. 
// ENUMs: 
// HIGH                     KI encoding is <4.08> 
// LOW                      KI encoding is <12.0u> 
#define LRFDRFE_LF0_KIPREC                                          0x00001000U
#define LRFDRFE_LF0_KIPREC_M                                        0x00001000U
#define LRFDRFE_LF0_KIPREC_S                                                12U
#define LRFDRFE_LF0_KIPREC_HIGH                                     0x00001000U
#define LRFDRFE_LF0_KIPREC_LOW                                      0x00000000U

// Field:  [11:0] KI 
//
// FIR integral gain 
//
// Field sets the integral gain in the FIR loop filter. 
//
// FIR_KI = pi^2 * f3db^2 / (FREF * KDCO * DF^2) 
//
// where DF is the desired damping factor. Lower damping factor gives lower 
// phase margin in the loop. Typically damping factors in the range 0.75 to 1 
// is used. Note that equations above become more accurate when DF > 1. 
//
// Encoding is given by KIPREC setting. Examples: 
//
// When KIPREC = 0: 
//
// 0x000: KI  = 0 
// 0x001: KI  = 1 
// 0xFFF: KI = 4095 
//
// When KIPREC = 1: 
//
// 0x000: KI = 0x0.00 = 0.0 
// 0x001: KI = 0x0.01 = 0.00390625 
// 0x002: KI = 0x0.02 = 0.0078125 
// 0x004: KI = 0x0.40 = 0.25 
// 0x008: KI = 0x0.80 = 0.5 
// 0xFF0: KI = 0xF.F0 = 15.9375 
// 0xFFF: KI = 0xF.FF = 15.99609375 
//
// FIR loop filter gets reinitialized with the current value whenever: 
// - DLO moves from calibration operation to closed-loop state. 
// - DLO moves from open-loop operation to closed-loop operation. 
// - DLO is in closed-loop operation and there is a change on loop control set. 
// See DLOCTL0.LOOPUPD. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// FIR proportional gain 
//
// Field sets the proportional gain in FIR loop filter. 
//
// FIR_KP = 2*pi* f3db / KDCO 
//
// Encoding is <14.0u>: 
// 0x0000: Minimum proportional gain 
// 0x3FFF: Maximum proportional gain 
//
// FIR loop filter gets reinitialized with the current value whenever DLO moves 
// from calibration or open-loop operation to closed-loop operation. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Phase error discard count 
//
// When phase error discarding is enabled, FIR loop filter does not update if: 
//
// abs(phase error) > PHEDISC_THR / 64 
//
// Update loop if this happens for CNT consecutive REFCLK periods. 
//
// Set DLOCTL1.PHEDISC = EN to enable phase error discarding. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PHEDISC_CNT_W                                                4U
#define LRFDRFE_PHEDISC_CNT_M                                       0x00003C00U
#define LRFDRFE_PHEDISC_CNT_S                                               10U
#define LRFDRFE_PHEDISC_CNT_ALLONES                                 0x00003C00U
#define LRFDRFE_PHEDISC_CNT_ALLZEROS                                0x00000000U

// Field:   [9:0] THR 
//
// Phase error discard threshold 
//
// When phase error discarding is enabled, FIR loop filter does not update if: 
//
// abs(phase error) > PHEDISC_THR / 64 
//
// Update loop if this happens for CNT consecutive REFCLK periods. 
//
// Set DLOCTL1.PHEDISC = EN to enable phase error discarding. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Reference phase offset 
//
// Field initializes phase offset between CKVD and reference clock. 
//
// Encoding of field is <0.8u>. 
//
// Examples: 
// 0x40: 25% of CKVD clock period 
// 0x80: 50% of CKVD clock period 
// 0xC0: 75% of CKVD clock period 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Phase error lock loss count 
//
// Loss of lock is indicated when abs(phase error) >  PHELOLTHR / 2: 
//
// - for PHELOLCNT consecutive periods of REFCLK . 
// - and loop filter fincode overflows or underflows. 
//
// When either of these conditions occur DLOEV.LOL flag gets set in REFCLK 
// domain, and synthesizer IRQ to modem is asserted. See DLOCTL1.PLLMON for 
// further description. 
// ENUMs: 
// REFCLK_128_PER           Threshold count is 128 REFCLK periods 
// REFCLK_64_PER            Threshold count is 64 REFCLK periods 
// REFCLK_32_PER            Threshold count is 32 REFCLK periods 
// REFCLK_16_PER            Threshold count is 16 REFCLK periods 
#define LRFDRFE_PLLMON0_PHELOLCNT_W                                          2U
#define LRFDRFE_PLLMON0_PHELOLCNT_M                                 0x0000C000U
#define LRFDRFE_PLLMON0_PHELOLCNT_S                                         14U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_128_PER                    0x0000C000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_64_PER                     0x00008000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_32_PER                     0x00004000U
#define LRFDRFE_PLLMON0_PHELOLCNT_REFCLK_16_PER                     0x00000000U

// Field:  [13:8] PHELOLTHR 
//
// Phase error lock loss threshold 
//
// Loss of lock is indicated when abs(phase error) > PHELOLTHR / 2: 
//
// - for PLLMON0.PHELOLCNT consecutive periods of REFCLK . 
// - and loop filter fincode overflows or underflows. 
//
// When either of these conditions occur DLOEV.LOL flag gets set in REFCLK 
// domain, and synthesizer IRQ to modem is asserted. See DLOCTL1.PLLMON for 
// further description. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PLLMON0_PHELOLTHR_W                                          6U
#define LRFDRFE_PLLMON0_PHELOLTHR_M                                 0x00003F00U
#define LRFDRFE_PLLMON0_PHELOLTHR_S                                          8U
#define LRFDRFE_PLLMON0_PHELOLTHR_ALLONES                           0x00003F00U
#define LRFDRFE_PLLMON0_PHELOLTHR_ALLZEROS                          0x00000000U

// Field:   [6:0] FCTHR 
//
// Fine code threshold 
//
// Field sets two symmetric thresholds, with encoding <7.8u>: 
// FCLWTHR =  {FCTHR, 8'b0} 
// FCUPTHR  =  {8'b0111111 - FCTHR), 8'b1} 
//
// The PLL monitor compares the final 15-bit fine code sent to DCO and SDM to 
// these thresholds: 
//
// When fine code > FCUPTHR, DLOEV.FCABVTHR flag gets set in REFCLK domain. 
// When fine code < FCLWTHR, DLOEV.FCBLWTHR flag gets set in REFCLK domain. 
//
// In both cases synthesizer IRQ to modem is asserted. See DLOCTL1.PLLMON for 
// further description. 
//
// INTERNAL NOTE: 
// * default value should be 0 so that detector is effectively disabled for any 
// fine code. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Phase error lock count 
//
// Declare lock for PLL if: 
//
// abs(phase error) < PHELOCKTHR / 64 
//
// for PHELOCKCNT*4 consecutive periods of default REFCLK. When this happens 
// DLOEV.LOCK flag gets set in REFCLK domain, and synthesizer IRQ to modem is 
// asserted. See DLOCTL1.PLLMON for further description. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PLLMON1_PHELOCKCNT_W                                         5U
#define LRFDRFE_PLLMON1_PHELOCKCNT_M                                0x00001F00U
#define LRFDRFE_PLLMON1_PHELOCKCNT_S                                         8U
#define LRFDRFE_PLLMON1_PHELOCKCNT_ALLONES                          0x00001F00U
#define LRFDRFE_PLLMON1_PHELOCKCNT_ALLZEROS                         0x00000000U

// Field:   [7:0] PHELOCKTHR 
//
// Phase error lock threshold 
//
// Declare lock for PLL if: 
//
// abs(phase error) < PHELOCKTHR / 64 
//
// for PHELOCKCNT *4 consecutive periods of default REFCLK.When this happens 
// DLOEV.LOCK flag gets set in REFCLK domain, and synthesizer IRQ to modem is 
// asserted. See DLOCTL1.PLLMON for further description. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Scheme 
//
// Field sets the modulation scheme of the DLO 
// ENUMs: 
// TWO_POINT_MOD_FRF        2-point modulation with FRF resolution 
//
//                          MOD_RES = FRF / 
//                          2^(21+CANPTHGAIN) 
//
//                          Scheme supports both open 
//                          -and closed-loop operation. Scheme allows wider 
//                          modulation bandwiths than INLOOP_MOD_FRF. 
// INLOOP_MOD_FRF           In-loop modulation with FRF resolution 
//
//                          MOD_RES = FRF / 
//                          2^(21+CANPTHGAIN) 
// INLOOP_MOD_FREF          In-loop modulation with FREF resolution 
//
//                          MOD_RES = FREF / 
//                          (DIVIDER/2) / 2^(15+CANPTHGAIN) 
//
//                          DIV.RATIO determines 
//                          DIVIDER configuration. Scheme only supports 
//                          closed-loop operation. 
// NC                       No connect 
//
//                          Modulator output does not 
//                          add to frequencey control word from PLL. 
#define LRFDRFE_MOD0_SCHEME_W                                                2U
#define LRFDRFE_MOD0_SCHEME_M                                       0x00001800U
#define LRFDRFE_MOD0_SCHEME_S                                               11U
#define LRFDRFE_MOD0_SCHEME_TWO_POINT_MOD_FRF                       0x00001800U
#define LRFDRFE_MOD0_SCHEME_INLOOP_MOD_FRF                          0x00001000U
#define LRFDRFE_MOD0_SCHEME_INLOOP_MOD_FREF                         0x00000800U
#define LRFDRFE_MOD0_SCHEME_NC                                      0x00000000U

// Field:  [10:8] SYMSHP 
//
// Symbol shaper 
// ENUMs: 
// CHIRP                    Chirp modulation 
// SHAPEDZIGBEE             Use Shaped 802.15.4 modulation 
// PCWSPSK                  Use piecewise linear PSK shaper defined by 
//                          SHAPECFG* registers. 
// ZIGBEE                   Use unshaped zigbee 
// SHAPEDFSK                Use generic 3 symbol shaper defined by SHAPECFG* 
//                          registers. 
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
// Cancellation path gain 
//
// The cancellation phase is scaled by a configurable gain, which effectively 
// sets the modulator frequency control word resolution. To calculate the 
// resolution, use the binary value of this field in equations in SCHEME. 
// ENUMs: 
// TWO_POW_M_18             POW(2,-18) 
// TWO_POW_M_17             POW(2,-17) 
// TWO_POW_M_16             POW(2,-16) 
// TWO_POW_M_15             POW(2,-15) 
#define LRFDRFE_MOD0_CANPTHGAIN_W                                            2U
#define LRFDRFE_MOD0_CANPTHGAIN_M                                   0x000000C0U
#define LRFDRFE_MOD0_CANPTHGAIN_S                                            6U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_18                        0x000000C0U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_17                        0x00000080U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_16                        0x00000040U
#define LRFDRFE_MOD0_CANPTHGAIN_TWO_POW_M_15                        0x00000000U

// Field:   [5:4] SHPGAIN 
//
// Shape gain 
//
// Field sets the scaling factor for shape elements in DTX0 - DTX5. Both the 
// scaling factor and shape element values are generated offline for a certain 
// frequency deviation. 
//
// INTERNAL NOTE: 
// * Please refer to 
// https://spsemea.itg.ti.com/sites/lpw/proj/CC26xx/Architecture/Radio%20System/cc26xx_modem_spec.doc 
// for how the SHPGAIN and shape elements together defines the frequency 
// deviation for different modes. 
// * The scaling factor is is really as follows: 
//   X1 = DIV_BY_4 
//   X2 = DIV_BY_2 
//   X4 = DIV_BY_1 
//   X8 = DIV_BY_0P5 
//   Will not update to reflect this as the matlab gain output === SHPGAIN. 
// ENUMs: 
// X8                       Shape gain = 8 
// X4                       Shape gain = 4 
// X2                       Shape gain = 2 
// X1                       Shape gain = 1 
#define LRFDRFE_MOD0_SHPGAIN_W                                               2U
#define LRFDRFE_MOD0_SHPGAIN_M                                      0x00000030U
#define LRFDRFE_MOD0_SHPGAIN_S                                               4U
#define LRFDRFE_MOD0_SHPGAIN_X8                                     0x00000030U
#define LRFDRFE_MOD0_SHPGAIN_X4                                     0x00000020U
#define LRFDRFE_MOD0_SHPGAIN_X2                                     0x00000010U
#define LRFDRFE_MOD0_SHPGAIN_X1                                     0x00000000U

// Field:   [3:2] INTPFACT 
//
// Interpolation factor 
//
// Field sets the interpolation factor of the shape filter. 
//
// INTERNAL NOTE: 
// Please refer to 
// https://spsemea.itg.ti.com/sites/lpw/proj/CC26xx/Architecture/Radio%20System/cc26xx_modem_spec.doc 
// for more detailed description. 
// ENUMs: 
// ILLEGAL1                 Illegal, unsupported setting 
// INTP_BY_32               Interpolate by 32 
// INTP_BY_16               Interpolate by 16 
// ILLEGAL0                 Illegal, unsupported setting 
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
// Frequency Offset 
//
// Field configures the optional intermediate frequency (IF) used in TX or RX. 
//
// IF = FRF / 2^(21+CANPTHGAIN)  * FOFF 
//
// Encoding is <12.0s>. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX0_SHP1_W                                                  8U
#define LRFDRFE_DTX0_SHP1_M                                         0x0000FF00U
#define LRFDRFE_DTX0_SHP1_S                                                  8U
#define LRFDRFE_DTX0_SHP1_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX0_SHP1_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP0 
//
// Shape element 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX1_SHP3_W                                                  8U
#define LRFDRFE_DTX1_SHP3_M                                         0x0000FF00U
#define LRFDRFE_DTX1_SHP3_S                                                  8U
#define LRFDRFE_DTX1_SHP3_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX1_SHP3_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP2 
//
// Shape element 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 5 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX2_SHP5_W                                                  8U
#define LRFDRFE_DTX2_SHP5_M                                         0x0000FF00U
#define LRFDRFE_DTX2_SHP5_S                                                  8U
#define LRFDRFE_DTX2_SHP5_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX2_SHP5_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP4 
//
// Shape element 4 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 7 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX3_SHP7_W                                                  8U
#define LRFDRFE_DTX3_SHP7_M                                         0x0000FF00U
#define LRFDRFE_DTX3_SHP7_S                                                  8U
#define LRFDRFE_DTX3_SHP7_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX3_SHP7_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP6 
//
// Shape element 6 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 9 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX4_SHP9_W                                                  8U
#define LRFDRFE_DTX4_SHP9_M                                         0x0000FF00U
#define LRFDRFE_DTX4_SHP9_S                                                  8U
#define LRFDRFE_DTX4_SHP9_ALLONES                                   0x0000FF00U
#define LRFDRFE_DTX4_SHP9_ALLZEROS                                  0x00000000U

// Field:   [7:0] SHP8 
//
// Shape element 8 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 11 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX5_SHP11_W                                                 8U
#define LRFDRFE_DTX5_SHP11_M                                        0x0000FF00U
#define LRFDRFE_DTX5_SHP11_S                                                 8U
#define LRFDRFE_DTX5_SHP11_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX5_SHP11_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP10 
//
// Shape element 10 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 13 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX6_SHP13_W                                                 8U
#define LRFDRFE_DTX6_SHP13_M                                        0x0000FF00U
#define LRFDRFE_DTX6_SHP13_S                                                 8U
#define LRFDRFE_DTX6_SHP13_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX6_SHP13_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP12 
//
// Shape element 12 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 15 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX7_SHP15_W                                                 8U
#define LRFDRFE_DTX7_SHP15_M                                        0x0000FF00U
#define LRFDRFE_DTX7_SHP15_S                                                 8U
#define LRFDRFE_DTX7_SHP15_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX7_SHP15_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP14 
//
// Shape element 14 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 17 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX8_SHP17_W                                                 8U
#define LRFDRFE_DTX8_SHP17_M                                        0x0000FF00U
#define LRFDRFE_DTX8_SHP17_S                                                 8U
#define LRFDRFE_DTX8_SHP17_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX8_SHP17_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP16 
//
// Shape element 16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 19 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX9_SHP19_W                                                 8U
#define LRFDRFE_DTX9_SHP19_M                                        0x0000FF00U
#define LRFDRFE_DTX9_SHP19_S                                                 8U
#define LRFDRFE_DTX9_SHP19_ALLONES                                  0x0000FF00U
#define LRFDRFE_DTX9_SHP19_ALLZEROS                                 0x00000000U

// Field:   [7:0] SHP18 
//
// Shape element 18 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 21 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX10_SHP21_W                                                8U
#define LRFDRFE_DTX10_SHP21_M                                       0x0000FF00U
#define LRFDRFE_DTX10_SHP21_S                                                8U
#define LRFDRFE_DTX10_SHP21_ALLONES                                 0x0000FF00U
#define LRFDRFE_DTX10_SHP21_ALLZEROS                                0x00000000U

// Field:   [7:0] SHP20 
//
// Shape element 20 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Shape element 23 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTX11_SHP23_W                                                8U
#define LRFDRFE_DTX11_SHP23_M                                       0x0000FF00U
#define LRFDRFE_DTX11_SHP23_S                                                8U
#define LRFDRFE_DTX11_SHP23_ALLONES                                 0x0000FF00U
#define LRFDRFE_DTX11_SHP23_ALLZEROS                                0x00000000U

// Field:   [7:0] SHP22 
//
// Shape element 22 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// PLLM0 value 
//
// Field sets the desired output frequency of the PLL, FRF, using the default 
// PLL reference frequency, according to: 
//
// M-value = FRF * (DIVIDER/2) / FREF0 
//
// Field encoding is <12.18u> 
//
// PRE0.PLLDIV0 determines FREF0. DIV.RATIO determines DIVIDER. 
//
// INTERNAL NOTE: 
// * 2.1 GHz =< FRF * ((DIV.RATIO//2) <= 2.8 GHz 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PLLM0L_VALLSB_W                                             14U
#define LRFDRFE_PLLM0L_VALLSB_M                                     0x0000FFFCU
#define LRFDRFE_PLLM0L_VALLSB_S                                              2U
#define LRFDRFE_PLLM0L_VALLSB_ALLONES                               0x0000FFFCU
#define LRFDRFE_PLLM0L_VALLSB_ALLZEROS                              0x00000000U

// Field:   [1:0] SPARE0 
//
// SPARE0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// PLLM0 value 
//
// Field sets the desired output frequency of the PLL, FRF, using the default 
// PLL reference frequency, according to: 
//
// M-value = FRF * (DIVIDER/2) / FREF0 
//
// Field encoding is <12.18u> 
//
// PRE0.PLLDIV0 determines FREF0. DIV.RATIO determines DIVIDER. 
//
// INTERNAL NOTE: 
// * 2.1 GHz =< FRF * ((DIV.RATIO//2) <= 2.8 GHz 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// PLLM1 value 
//
// Field sets the desired output frequency of the PLL, FRF, using the default 
// PLL reference frequency, according to: 
//
// M-value = FRF * (DIVIDER/2) / FREF1 
//
// Field encoding is <12.18u> 
//
// PRE0.PLLDIV1 determines FREF1. DIV.RATIO determines DIVIDER. 
//
// INTERNAL NOTE: 
// * 2.1 GHz =< FRF * ((DIV.RATIO//2) <= 2.8 GHz 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_PLLM1L_VALLSB_W                                             14U
#define LRFDRFE_PLLM1L_VALLSB_M                                     0x0000FFFCU
#define LRFDRFE_PLLM1L_VALLSB_S                                              2U
#define LRFDRFE_PLLM1L_VALLSB_ALLONES                               0x0000FFFCU
#define LRFDRFE_PLLM1L_VALLSB_ALLZEROS                              0x00000000U

// Field:   [1:0] SPARE0 
//
// SPARE0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// PLLM1 value 
//
// Field sets the desired output frequency of the PLL, FRF, using the default 
// PLL reference frequency, according to: 
//
// M-value = FRF * (DIVIDER/2) / FREF1 
//
// Field encoding is <12.18u> 
//
// PRE0.PLLDIV1 determines FREF1. DIV.RATIO determines DIVIDER. 
//
// INTERNAL NOTE: 
// * 2.1 GHz =< FRF * ((DIV.RATIO//2) <= 2.8 GHz 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Coarse SAR m-value 
//
// Field sets the desired output frequency of the PLL, FRF,  during coarse SAR, 
// according to: 
//
// VAL = FRF * (DIVIDER/2) / COARSE_CALIB_FREF 
//
// Field encoding is <16u>. 
//
// PRE2.CRSCALDIV determines COARSE_CALIB_FREF. DIV.RATIO determines DIVIDER. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Mid SAR m-value 
//
// Field sets the desired output frequency of the PLL, FRF, during mid SAR, 
// according to: 
//
// VAL = FRF * (DIVIDER/2) / MID_CALIB_FREF 
//
// Field encoding is <16u>. 
//
// PRE2.MIDCALDIVLSB and PRE3.MIDCALDIVMSB  determines MID_CALIB_FREF. 
// DIV.RATIO determines DIVIDER. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Load value for 16-bit REFCLK prescaler 
//
// The REFCLK prescaler is used when DLOCTL0.LOOPUPD bit-2 = 1. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// TDC stop configuration 
//
// During TDC calibration the value specifies the pulse duration used to 
// calculate the TDC gain as number of CKVD periods (2 / FDCO). Value 
// effectively sets the resolution of the FW-calculated CAL2.KTDCINV. 
//
// Otherwise, the TDC stop delay is programmable in units of CKVD clock 
// periods. The stop delay is either static or randomly decided per reference 
// clock period. The latter is referred to as TDC stop-time dithering. 
//
// 000: TDC stops when flop 0 becomes 1. During TDC calibration pulse length is 
// 1 CKVD period. 
// 001: TDC stops when flop 1 becomes 1. During TDC calibration pulse length is 
// 2 CKVD periods. 
// 010: TDC stops when flop 2 becomes 1. During TDC calibration pulse length is 
// 3 CKVD periods. 
// 011: TDC stops when flop 3 becomes 1. During TDC calibration pulse length is 
// 4 CKVD periods. 
// 1xx: TDC stops when a randomly chosen flop becomes 1. Do not use for TDC 
// calibration. 
// ENUMs: 
// OPEN                     Open-loop operation 
// CLOSED                   Closed-loop operation 
#define LRFDRFE_DLOCTL0_TDCSTOP_W                                            3U
#define LRFDRFE_DLOCTL0_TDCSTOP_M                                   0x00000700U
#define LRFDRFE_DLOCTL0_TDCSTOP_S                                            8U
#define LRFDRFE_DLOCTL0_TDCSTOP_OPEN                                0x00000100U
#define LRFDRFE_DLOCTL0_TDCSTOP_CLOSED                              0x00000000U

// Field:     [7] DTSTXTAL 
//
// XTALBAW DTST interface control 
//
// Configure DTST interface in DTST when interface is disabled. 
// ENUMs: 
// ONE                      Enable XTALBAW DTST interface 
// ZERO                     Disable XTALBAW DTST interface 
#define LRFDRFE_DLOCTL0_DTSTXTAL                                    0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_M                                  0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_S                                           7U
#define LRFDRFE_DLOCTL0_DTSTXTAL_ONE                                0x00000080U
#define LRFDRFE_DLOCTL0_DTSTXTAL_ZERO                               0x00000000U

// Field:   [6:4] LOOPUPD 
//
// Loop update control 
//
// The PLL frequency and loop dynamics are controlled through a set of 
// configurations of coarse and mid codes, TCD gain, reference clock divider, 
// and feedback divider(PLLM). Registers for PLLM and reference clock dividers 
// are duplicated to support REFCLK dithering, and/or loop BW gearing. These 
// are set 0 and set 1. It is also possible to update all configurations at 
// certain events to move the frequency around in the tuning range, and adjust 
// the loop bandwidth at the same time. Basically: 
// - bit-0: Static control set select (manual switch-FW) 
//     0 : select control set 0. 
//     1 : select control set 1. 
// - bit-1: Dithering select (automatic switch-LFSR) 
//     0: Functionality unused. 
//     1: LFSR single bit output is used to select control set according to 
// bit-0 select rules. Average F_REFCLK to be used in Ki equation is the 
// harmonic mean, F_REFCLK = 2/[1/F_REFCLK0 + 1/F_REFCLK1]. 
// - bit-2: Timer select (automatic switch-prescaler) 
//     0: Functionality unused. 
//     1: On every REFDIV.LOAD REFCLK event DLO toggles the control set select. 
// FW can update the one not used. 
//
// There are restrictions on legal settings and transitions. 
//
// INTERNAL NOTE: 
// See the implementation specification for explicit details and rules when 
// using this register. 
// ENUMs: 
// ALT                      Use alternate REF (PLLM1) 
// DEF                      Use default FREF (PLLM0) 
#define LRFDRFE_DLOCTL0_LOOPUPD_W                                            3U
#define LRFDRFE_DLOCTL0_LOOPUPD_M                                   0x00000070U
#define LRFDRFE_DLOCTL0_LOOPUPD_S                                            4U
#define LRFDRFE_DLOCTL0_LOOPUPD_ALT                                 0x00000010U
#define LRFDRFE_DLOCTL0_LOOPUPD_DEF                                 0x00000000U

// Field:     [3] PH3 
//
// Lock aquisition / calibration phase 3 control 
// ENUMs: 
// START                    Close the loop to aquire phase lock, i.e. phase 3 
//                          of calibration routine. 
// HALT                     Halt DLO FSM after DCO frequency span measurement 
//
//                          When DLO and RFE runs 
//                          KDCO estimation, RFE must compute KDCO from the 
//                          frequency span, and calculate loop filter 
//                          settings to use before lock aquisition. 
#define LRFDRFE_DLOCTL0_PH3                                         0x00000008U
#define LRFDRFE_DLOCTL0_PH3_M                                       0x00000008U
#define LRFDRFE_DLOCTL0_PH3_S                                                3U
#define LRFDRFE_DLOCTL0_PH3_START                                   0x00000008U
#define LRFDRFE_DLOCTL0_PH3_HALT                                    0x00000000U

// Field:     [2] PH2 
//
// KDCO estimation / calibration phase 2 control 
// ENUMs: 
// START                    Start KDCO estimation, i.e. phase 2 of calibration 
//                          routine. 
// HALT                     Halt DLO FSM after TDC calibration measurement 
//
//                          When DLO and RFE runs TDC 
//                          calibration, RFE must use calibration 
//                          measurement to calculcate CAL2.KTDCINV. 
#define LRFDRFE_DLOCTL0_PH2                                         0x00000004U
#define LRFDRFE_DLOCTL0_PH2_M                                       0x00000004U
#define LRFDRFE_DLOCTL0_PH2_S                                                2U
#define LRFDRFE_DLOCTL0_PH2_START                                   0x00000004U
#define LRFDRFE_DLOCTL0_PH2_HALT                                    0x00000000U

// Field:     [1] LOOPMODE 
//
// Loop mode control 
// ENUMs: 
// OPEN                     Open-loop operation 
// CLOSED                   Closed-loop operation 
#define LRFDRFE_DLOCTL0_LOOPMODE                                    0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_M                                  0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_S                                           1U
#define LRFDRFE_DLOCTL0_LOOPMODE_OPEN                               0x00000002U
#define LRFDRFE_DLOCTL0_LOOPMODE_CLOSED                             0x00000000U

// Field:     [0] RSTN 
//
// DLO reset 
//
// DLO active low reset. The DLO has several static inputs that all needs to be 
// set prior to releasing reset. 
//
// INTERNAL NOTE: 
// * Consult with LRFDLO implementation specification to see classification of 
// static, pseudo-static, and dynamic inputs. 
// ENUMs: 
// ACTIVE                   DLO is not held in reset 
// RESET                    DLO is reset 
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
// DCO control 
// ENUMs: 
// EN                       Enable DCO 
// DIS                      Disable DCO 
#define LRFDRFE_DLOCTL1_DCO                                         0x00008000U
#define LRFDRFE_DLOCTL1_DCO_M                                       0x00008000U
#define LRFDRFE_DLOCTL1_DCO_S                                               15U
#define LRFDRFE_DLOCTL1_DCO_EN                                      0x00008000U
#define LRFDRFE_DLOCTL1_DCO_DIS                                     0x00000000U

// Field:     [7] FCDEM 
//
// Finecode dynamic element match control 
// ENUMs: 
// EN                       Enable DEM 
// DIS                      Disable DEM 
#define LRFDRFE_DLOCTL1_FCDEM                                       0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_M                                     0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_S                                              7U
#define LRFDRFE_DLOCTL1_FCDEM_EN                                    0x00000080U
#define LRFDRFE_DLOCTL1_FCDEM_DIS                                   0x00000000U

// Field:     [6] DTSTCKVD 
//
// CKVD DTST interface control 
//
// Configure DTST interface in DTST when interface is disabled. 
// ENUMs: 
// ONE                      Enable CKVD DTST interface 
// ZERO                     Disable CKVD DTST interface 
#define LRFDRFE_DLOCTL1_DTSTCKVD                                    0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_M                                  0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_S                                           6U
#define LRFDRFE_DLOCTL1_DTSTCKVD_ONE                                0x00000040U
#define LRFDRFE_DLOCTL1_DTSTCKVD_ZERO                               0x00000000U

// Field:     [5] PHEDISC 
//
// Phase error discarding control 
//
// Feature discards large phase errors from propagating into the loop filter. 
// PHEDISC configures the behavior. 
// ENUMs: 
// EN                       Enable phase error discard function 
// DIS                      Disable phase error discard function 
#define LRFDRFE_DLOCTL1_PHEDISC                                     0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_M                                   0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_S                                            5U
#define LRFDRFE_DLOCTL1_PHEDISC_EN                                  0x00000020U
#define LRFDRFE_DLOCTL1_PHEDISC_DIS                                 0x00000000U

// Field:     [4] PLLMON 
//
// PLL monitor control 
//
// The PLL monitor detects the following PLL states in the variable clock 
// domain: 
// - Lock (static) 
// - Loss of lock (dynamic) 
// - Fine code above threshold (static) 
// - Fine code below threshold (static) 
//
// The monitor signals the occurence of these conditions to the reference clock 
// domain. This domain does positive edge detection for lock and loss-of-lock 
// events, and synchronizes the threshold events. The IRQ to modem is high 
// whenever reference clock domain events are high. 
//
// The lock and loss-of-lock flags are cleared individually in the reference 
// clock domain. Disable the PLL monitor to reset the all event flags in the 
// variable clock domain. PLL Lock and Loss of Lock flags are automatically 
// cleared in the variable clock domain when transitioning from open-loop to 
// closed-loop operation. 
//
// To clear Lock and Loss of Lock flags using this field, the DLO must operate 
// in closed-loop mode, and a new value must be stable for at least 2 REFCLK 
// periods. 
//
// Keep PLL monitor disabled during the calibration states. 
// ENUMs: 
// EN                       Enable PLL monitor 
// DIS                      Disable and reset PLL monitor 
#define LRFDRFE_DLOCTL1_PLLMON                                      0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_M                                    0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_S                                             4U
#define LRFDRFE_DLOCTL1_PLLMON_EN                                   0x00000010U
#define LRFDRFE_DLOCTL1_PLLMON_DIS                                  0x00000000U

// Field:     [3] IIR 
//
// IIR control 
//
// Do not enable during lock aquisition. 
// ENUMs: 
// EN                       Enable IIR filter 
// DIS                      Disable IIR filter 
#define LRFDRFE_DLOCTL1_IIR                                         0x00000008U
#define LRFDRFE_DLOCTL1_IIR_M                                       0x00000008U
#define LRFDRFE_DLOCTL1_IIR_S                                                3U
#define LRFDRFE_DLOCTL1_IIR_EN                                      0x00000008U
#define LRFDRFE_DLOCTL1_IIR_DIS                                     0x00000000U

// Field:     [2] MOD 
//
// Modulator control 
//
// Enable of MODISF (Modulator's Interpolating Shaping Filter) 
// ENUMs: 
// EN                       Enable MODISF 
// DIS                      Disable MODISF 
#define LRFDRFE_DLOCTL1_MOD                                         0x00000004U
#define LRFDRFE_DLOCTL1_MOD_M                                       0x00000004U
#define LRFDRFE_DLOCTL1_MOD_S                                                2U
#define LRFDRFE_DLOCTL1_MOD_EN                                      0x00000004U
#define LRFDRFE_DLOCTL1_MOD_DIS                                     0x00000000U

// Field:     [1] MODINIT 
//
// Modulator Initialization 
// ENUMs: 
// ACTIVATE                 Activate MODISF initialization 
// DEACTIVATE               Deactivate MODISF initialization 
#define LRFDRFE_DLOCTL1_MODINIT                                     0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_M                                   0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_S                                            1U
#define LRFDRFE_DLOCTL1_MODINIT_ACTIVATE                            0x00000002U
#define LRFDRFE_DLOCTL1_MODINIT_DEACTIVATE                          0x00000000U

// Field:     [0] MTDCRSTN 
//
// MTDC reset 
// ENUMs: 
// ACTIVE                   Release MTDC reset 
// RESET                    Reset MTDC 
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
// Mid code override 
//
// When MIDCTL equals EN, field value overrides the DCO mid code, which sets 
// the DCO mid row and column control. Special encoding: 
// MIDCODE[5:4]: 
// 00: DCO mid row = 15 
// 01: DCO mid row = 7 
// 10: DCO mid row = 3 
// 11: DCO mid row = 1 
//
// DCO mid column = 15-to_integer(MIDCODE[3:0]) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DCOOVR0_MIDCODE_W                                            6U
#define LRFDRFE_DCOOVR0_MIDCODE_M                                   0x00003F00U
#define LRFDRFE_DCOOVR0_MIDCODE_S                                            8U
#define LRFDRFE_DCOOVR0_MIDCODE_ALLONES                             0x00003F00U
#define LRFDRFE_DCOOVR0_MIDCODE_ALLZEROS                            0x00000000U

// Field:   [7:4] CRSCODE 
//
// Coarse code override 
//
// When CRSCTL equals EN, field value overrides the DCO coarse control. This is 
// required during debug and when coarse calibration is skipped, or we want to 
// use other values during startup of ALO. Encoding is <4.0u>: 
//
// 0xFF: min frequency 
// … 
// 0x00: max frequency 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DCOOVR0_CRSCODE_W                                            4U
#define LRFDRFE_DCOOVR0_CRSCODE_M                                   0x000000F0U
#define LRFDRFE_DCOOVR0_CRSCODE_S                                            4U
#define LRFDRFE_DCOOVR0_CRSCODE_ALLONES                             0x000000F0U
#define LRFDRFE_DCOOVR0_CRSCODE_ALLZEROS                            0x00000000U

// Field:     [3] FINECTL 
//
// Fine code override control 
// ENUMs: 
// EN                       Enable fine code override 
// DIS                      Disable fine code override 
#define LRFDRFE_DCOOVR0_FINECTL                                     0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_M                                   0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_S                                            3U
#define LRFDRFE_DCOOVR0_FINECTL_EN                                  0x00000008U
#define LRFDRFE_DCOOVR0_FINECTL_DIS                                 0x00000000U

// Field:     [2] SDMICTL 
//
// SDM input code override control 
// ENUMs: 
// EN                       Enable SDM input code override 
// DIS                      Disable SDM input code override 
#define LRFDRFE_DCOOVR0_SDMICTL                                     0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_M                                   0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_S                                            2U
#define LRFDRFE_DCOOVR0_SDMICTL_EN                                  0x00000004U
#define LRFDRFE_DCOOVR0_SDMICTL_DIS                                 0x00000000U

// Field:     [1] MIDCTL 
//
// Mid code override control 
// ENUMs: 
// EN                       Enable mid code override 
// DIS                      Disable mid code override 
#define LRFDRFE_DCOOVR0_MIDCTL                                      0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_M                                    0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_S                                             1U
#define LRFDRFE_DCOOVR0_MIDCTL_EN                                   0x00000002U
#define LRFDRFE_DCOOVR0_MIDCTL_DIS                                  0x00000000U

// Field:     [0] CRSCTL 
//
// Coarse code override 
// ENUMs: 
// EN                       Enable coarse code override 
// DIS                      Disable coarse code override 
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
// Fine code override 
//
// When DCOOVR0.FINECTL equals EN, field value overrides the integer part of 
// DCO fine code . 
//
// Encoding is <7.0u>: 
// 0x00: Min 
// ... 
// 0x7F: MAX 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DCOOVR1_FINECODE_W                                           7U
#define LRFDRFE_DCOOVR1_FINECODE_M                                  0x00007F00U
#define LRFDRFE_DCOOVR1_FINECODE_S                                           8U
#define LRFDRFE_DCOOVR1_FINECODE_ALLONES                            0x00007F00U
#define LRFDRFE_DCOOVR1_FINECODE_ALLZEROS                           0x00000000U

// Field:   [7:0] SDMICODE 
//
// SDM input code override 
//
// When DCOOVR0.SDMICTL equals EN, field value overrides the fractional part of 
// DCO fine code to SDM. Encoding is <0.8u>: 
// 0x00: 0 
// ... 
// 0x7F: 0.99609375 
//
// The fractional value is added to the integer part. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// SPARE111 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_DTST_SPARE11_W                                               4U
#define LRFDRFE_DTST_SPARE11_M                                      0x00007800U
#define LRFDRFE_DTST_SPARE11_S                                              11U
#define LRFDRFE_DTST_SPARE11_ALLONES                                0x00007800U
#define LRFDRFE_DTST_SPARE11_ALLZEROS                               0x00000000U

// Field:  [10:8] VARTGLDLY 
//
// Variable domain toggle delay 
//
// Field sets delay on toggle launch compared to data launch. CLK equals launch 
// clock for signal selected in SIG. It can be eiter CKVD16 or reference clock. 
// ENUMs: 
// CLK_7_PER                Toggle lags data by 7 CKVD16 periods. 
// CLK_6_PER                Toggle lags data by 6 CKVD16 periods. 
// CLK_5_PER                Toggle lags data by 5 CKVD16 periods. 
// CLK_4_PER                Toggle lags data by 4 CKVD16 periods. 
// CLK_3_PER                Toggle lags data by 3 CKVD16 periods. 
// CLK_2_PER                Toggle lags data by 2 CKVD16 periods. 
// CLK_1_PER                Toggle lags data by 1 CKVD16 periods. 
// CLK_0_PER                Toggle lags data by 0 CKVD16 periods. 
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
// Reference domain toggle delay 
//
// Field sets delay on toggle launch compared to data launch. CLK equals launch 
// clock for signal selected in SIG. It can be eiter CKVD16 or reference clock. 
// ENUMs: 
// CLK_1_PER                Toggle lags data by 1 HFXT/BAW periods. 
// CLK_0_PER                Toggle lags data by 0 HFXT/BAW periods. 
#define LRFDRFE_DTST_REFTGLDLY                                      0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_M                                    0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_S                                             7U
#define LRFDRFE_DTST_REFTGLDLY_CLK_1_PER                            0x00000080U
#define LRFDRFE_DTST_REFTGLDLY_CLK_0_PER                            0x00000000U

// Field:     [6] TRNSEQ 
//
// Trainer sequence control 
//
// When trainer sequence is enabled, dtst data will not reflect SIG 
// configuration. Instead, it will toggle between 0x5555 and 0xAAAA for every 
// update uof the data specified by SIG. 
// ENUMs: 
// EN                       Enable trainer sequence 
// DIS                      Disable trainer sequence 
#define LRFDRFE_DTST_TRNSEQ                                         0x00000040U
#define LRFDRFE_DTST_TRNSEQ_M                                       0x00000040U
#define LRFDRFE_DTST_TRNSEQ_S                                                6U
#define LRFDRFE_DTST_TRNSEQ_EN                                      0x00000040U
#define LRFDRFE_DTST_TRNSEQ_DIS                                     0x00000000U

// Field:     [5] SPARE5 
//
// SPARE5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DTST_SPARE5                                         0x00000020U
#define LRFDRFE_DTST_SPARE5_M                                       0x00000020U
#define LRFDRFE_DTST_SPARE5_S                                                5U
#define LRFDRFE_DTST_SPARE5_ONE                                     0x00000020U
#define LRFDRFE_DTST_SPARE5_ZERO                                    0x00000000U

// Field:   [4:0] SIG 
//
// Signal Configuration 
//
// Selects which signal to route to DTST data port.  Any change to MSB may 
// cause modem to detect false toggle. Hence, the first sample must  be 
// discarded in modem after a change to MSB. 
//
// Whenever signal po_tdc_stop_dly_sel is sampled, discard the first three 
// samples. 
//
// All bits in dtst_data vector originates from the same reference clock edge, 
// unless otherwise noted. 
// ENUMs: 
// VAR_NC_15                dtst_data = 0x0000 
// VAR_NC_14                dtst_data = 0x0000 
// VAR_NC_13                dtst_data = 0x0000 
// VAR_NC_12                dtst_data = 0x0000 
// VAR_NC_11                dtst_data = 0x0000 
// VAR_LOOP_UPD_FINECODE    dtst_data : 
//
//                          [15] : 
//                          (u_pll/pll_loop_update) 
//                          [14:0] : 
//                          u_pll/po_ckvd16_finecode_pll 
// VAR_LOCK_FINECODE        dtst_data : 
//
//                          [15] : 
//                          (u_pll/po_ckvd48_pllmon_lock  XOR 
//                          u_pll/po_ckvd48_pllmon_lol) 
//                          [14:0] : 
//                          u_pll/po_ckvd16_finecode_pll 
// VAR_MPX_CAN              dtst_data : 
//
//                          [15] : u_mpx/freq_can[16] 
//                          [14:0] : 
//                          u_mpx/freq_can[14:0] 
//
//                          Format is 1.15s. This 
//                          field holds how much phase DTX adds to DCO per 
//                          reference frequency. This is a slice of the 
//                          signals that goes to u_pll which is 3.18s. 
//                          Hence, wrapping can occur. 
// VAR_TDCSTOP_STATUS_TDC   dtst_data : 
//
//                          [15:14] : 
//                          po_tdc_stop_dly_sel 
//                          [13] : 
//                          u_pll/pi_tdc_msb_error 
//                          [12] : 
//                          u_pll/pll_loop_update 
//                          [11] : 
//                          (u_pll/po_ckvd48_pllmon_lock  XOR 
//                          u_pll/po_ckvd48_pllmon_lol) 
//                          [10:0]: 
//                          u_pll/pi_tdc_data 
//
//                          Note that [12:11] are 
//                          samples from previous reference clock edge. 
// VAR_TDCSTOP_PHERR        dtst_data : 
//
//                          [15:14] : 
//                          po_tdc_stop_dly_sel 
//                          [13] 
//                          u_pll/phase_error[16] 
//                          [12:0]: 
//                          u_pll/phase_error[12:0] 
//
//                          [13:0] : phase_error. 
//                          Format is 3.11s. 
// VAR_PH_COMP_PHERR_TDCSTOPdtst_data : 
//
//                          [15:14] : 
//                          po_tdc_stop_dly_sel 
//                          [13] : 
//                          u_pll/phase_error[16] 
//                          [12:9]: 
//                          u_pll/phase_error[11:8] 
//                          [8:0] : 
//                          u_pll/var_phase[14: 6] 
//
//                          [13:9] : phase error. 
//                          Format is 2.3s. 
//                          [8:0]   : variable phase. 
//                          Format is 4.5u. 
// VAR_PH_TDCCORR           dtst_data : 
//
//                          [15] ; 
//                          u_pll/pi_tdc_msb_error 
//                          [14:11] : 
//                          u_pll/pi_pi_cnt_lsb 
//                          [10:0] : 
//                          u_pll/tdc_data_corr 
// VAR_PH_RAW               dtst_data : 
//
//                          [15] ; 
//                          u_pll/pi_tdc_msb_error 
//                          [14:11] : 
//                          u_pll/pi_pi_cnt_lsb 
//                          [10:0] : 
//                          u_pll/pi_tdc_data 
// VAR_PHERR_LOWER          dtst_data : 
//
//                          [15] : 
//                          u_pll/phase_error[16] 
//                          [14:0] : 
//                          u_pll/phase_error[14:0] 
//
//                          Format is 5.11s. Phase 
//                          error wraps if if too large. 
// VAR_PHERR_UPPER          dtst_data = u_pll/phase_error[16:1] 
//
//                          Format is 6.10s. 
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
// REF_FERR_MAG             dtst_data = u_fsm/po_dtst_fsm_ferr_mag 
//
//                          Format is14.2u. The 
//                          signal is only updated for frequency 
//                          measurements that affect the calibration 
//                          result. 
// REF_FSMCAL               dtst_data : 
//
//                          [15] : '0' 
//                          [14] : 
//                          u_fsm/pi_pll_lock_ind 
//                          [13:10] : 
//                          u_fsm/po_dsts_fsm_state 
//                          [9:6] : 
//                          u_fsm/po_dtst_fsm_coarse 
//                          [5:0] : 
//                          u_fsm/po_dtst_fsm_mid 
// REF_NC_0                 dtst_data = 0x0000 
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
// Lock 
//
// PLLMON1.PHELOCKCNT and PLLMON1.PHELOCKTHR configures the behaviour. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DLOEV_LOCK                                          0x00000080U
#define LRFDRFE_DLOEV_LOCK_M                                        0x00000080U
#define LRFDRFE_DLOEV_LOCK_S                                                 7U
#define LRFDRFE_DLOEV_LOCK_ONE                                      0x00000080U
#define LRFDRFE_DLOEV_LOCK_ZERO                                     0x00000000U

// Field:     [6] LOL 
//
// Loss of lock 
//
// PLLMON0.PHELOLCNT and PLLMON0.PHELOLTHR configures the behaviour. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DLOEV_LOL                                           0x00000040U
#define LRFDRFE_DLOEV_LOL_M                                         0x00000040U
#define LRFDRFE_DLOEV_LOL_S                                                  6U
#define LRFDRFE_DLOEV_LOL_ONE                                       0x00000040U
#define LRFDRFE_DLOEV_LOL_ZERO                                      0x00000000U

// Field:     [5] FCABVTHR 
//
// Finecode above threshold 
//
// PLLMON0.FCTHR sets threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DLOEV_FCABVTHR                                      0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_M                                    0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_S                                             5U
#define LRFDRFE_DLOEV_FCABVTHR_ONE                                  0x00000020U
#define LRFDRFE_DLOEV_FCABVTHR_ZERO                                 0x00000000U

// Field:     [4] FCBLWTHR 
//
// Finecode below threshold 
//
// PLLMON0.FCTHR sets threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DLOEV_FCBLWTHR                                      0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_M                                    0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_S                                             4U
#define LRFDRFE_DLOEV_FCBLWTHR_ONE                                  0x00000010U
#define LRFDRFE_DLOEV_FCBLWTHR_ZERO                                 0x00000000U

// Field:   [3:0] STATE 
//
// DLO FSM state 
//
// INTERNAL NOTE: 
// See implementation specification for details. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Data selected by DTST.SIG when the DTST interface is enabled. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// DCO frequency span 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// DCO frequency span 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Value 
//
// Sum of inverter delays calculated by HW at the end of the TDC calibration. 
// The number of delays summed is controlled by CAL0.TDCAVG and 
// DLOCTL0.TDCSTOP. FW uses value to calculate CAL2.KTDCINV. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Calibrated mid code 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_CALRES_MIDCODE_W                                             6U
#define LRFDRFE_CALRES_MIDCODE_M                                    0x000003F0U
#define LRFDRFE_CALRES_MIDCODE_S                                             4U
#define LRFDRFE_CALRES_MIDCODE_ALLONES                              0x000003F0U
#define LRFDRFE_CALRES_MIDCODE_ALLZEROS                             0x00000000U

// Field:   [3:0] CRSCODE 
//
// Calibrated coarse code 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Control GPI7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI7                                            0x00000080U
#define LRFDRFE_GPI_GPI7_M                                          0x00000080U
#define LRFDRFE_GPI_GPI7_S                                                   7U
#define LRFDRFE_GPI_GPI7_ONE                                        0x00000080U
#define LRFDRFE_GPI_GPI7_ZERO                                       0x00000000U

// Field:     [6] GPI6 
//
// Control GPI6 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI6                                            0x00000040U
#define LRFDRFE_GPI_GPI6_M                                          0x00000040U
#define LRFDRFE_GPI_GPI6_S                                                   6U
#define LRFDRFE_GPI_GPI6_ONE                                        0x00000040U
#define LRFDRFE_GPI_GPI6_ZERO                                       0x00000000U

// Field:     [5] GPI5 
//
// Control GPI5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI5                                            0x00000020U
#define LRFDRFE_GPI_GPI5_M                                          0x00000020U
#define LRFDRFE_GPI_GPI5_S                                                   5U
#define LRFDRFE_GPI_GPI5_ONE                                        0x00000020U
#define LRFDRFE_GPI_GPI5_ZERO                                       0x00000000U

// Field:     [4] GPI4 
//
// Control GPI4 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI4                                            0x00000010U
#define LRFDRFE_GPI_GPI4_M                                          0x00000010U
#define LRFDRFE_GPI_GPI4_S                                                   4U
#define LRFDRFE_GPI_GPI4_ONE                                        0x00000010U
#define LRFDRFE_GPI_GPI4_ZERO                                       0x00000000U

// Field:     [3] GPI3 
//
// Control GPI3 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI3                                            0x00000008U
#define LRFDRFE_GPI_GPI3_M                                          0x00000008U
#define LRFDRFE_GPI_GPI3_S                                                   3U
#define LRFDRFE_GPI_GPI3_ONE                                        0x00000008U
#define LRFDRFE_GPI_GPI3_ZERO                                       0x00000000U

// Field:     [2] GPI2 
//
// Control GPI2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI2                                            0x00000004U
#define LRFDRFE_GPI_GPI2_M                                          0x00000004U
#define LRFDRFE_GPI_GPI2_S                                                   2U
#define LRFDRFE_GPI_GPI2_ONE                                        0x00000004U
#define LRFDRFE_GPI_GPI2_ZERO                                       0x00000000U

// Field:     [1] GPI1 
//
// Control GPI1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPI_GPI1                                            0x00000002U
#define LRFDRFE_GPI_GPI1_M                                          0x00000002U
#define LRFDRFE_GPI_GPI1_S                                                   1U
#define LRFDRFE_GPI_GPI1_ONE                                        0x00000002U
#define LRFDRFE_GPI_GPI1_ZERO                                       0x00000000U

// Field:     [0] GPI0 
//
// Control GPI0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Input value in linear units 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Logarithmic output value 
//
// Logaritmic value of MATHACCELIN.VAL. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Divider output value 
//
// Calculation performed: MATHACCELIN.VAL/3 
//
// Supports input values <= 46, higher values are saturated. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Event capture source 
//
// Index selects the corresponding event from RFE event bus, EVT0 and EVT1. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_TIMCTL_CPTSRC_W                                              6U
#define LRFDRFE_TIMCTL_CPTSRC_M                                     0x00003F00U
#define LRFDRFE_TIMCTL_CPTSRC_S                                              8U
#define LRFDRFE_TIMCTL_CPTSRC_ALLONES                               0x00003F00U
#define LRFDRFE_TIMCTL_CPTSRC_ALLZEROS                              0x00000000U

// Field:     [7] CPTCTL 
//
// Counter capture control 
//
// Upon selected capture event, the counter value will be captured into 
// TIMCAPT. 
// ENUMs: 
// EN                       Enable counter capture mode 
// DIS                      Disable counter capture mode 
#define LRFDRFE_TIMCTL_CPTCTL                                       0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_M                                     0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_S                                              7U
#define LRFDRFE_TIMCTL_CPTCTL_EN                                    0x00000080U
#define LRFDRFE_TIMCTL_CPTCTL_DIS                                   0x00000000U

// Field:   [6:5] CNTRSRC 
//
// Counter event source 
// ENUMs: 
// FREF                     Count FREF ticks 
// MAGN1                    Use magnitude estimator 1 data enable 
// MAGN0                    Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDRFE_TIMCTL_CNTRSRC_W                                             2U
#define LRFDRFE_TIMCTL_CNTRSRC_M                                    0x00000060U
#define LRFDRFE_TIMCTL_CNTRSRC_S                                             5U
#define LRFDRFE_TIMCTL_CNTRSRC_FREF                                 0x00000060U
#define LRFDRFE_TIMCTL_CNTRSRC_MAGN1                                0x00000040U
#define LRFDRFE_TIMCTL_CNTRSRC_MAGN0                                0x00000020U
#define LRFDRFE_TIMCTL_CNTRSRC_CLK                                  0x00000000U

// Field:     [4] CNTRCLR 
//
// Counter clear value in TIMCNT. 
// ENUMs: 
// ONE                      Clear counter value 
// ZERO                     No action 
#define LRFDRFE_TIMCTL_CNTRCLR                                      0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_M                                    0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_S                                             4U
#define LRFDRFE_TIMCTL_CNTRCLR_ONE                                  0x00000010U
#define LRFDRFE_TIMCTL_CNTRCLR_ZERO                                 0x00000000U

// Field:     [3] CNTRCTL 
//
// 16-bit counter control 
//
// The counter will continue from its current value. 
// ENUMs: 
// EN                       Enable counter 
// DIS                      Disable counter 
#define LRFDRFE_TIMCTL_CNTRCTL                                      0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_M                                    0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_S                                             3U
#define LRFDRFE_TIMCTL_CNTRCTL_EN                                   0x00000008U
#define LRFDRFE_TIMCTL_CNTRCTL_DIS                                  0x00000000U

// Field:   [2:1] TIMSRC 
//
// Timer tick source 
// ENUMs: 
// FREF                     Count FREF ticks 
// MAGN1                    Use magnitude estimator 1 data enable 
// MAGN0                    Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDRFE_TIMCTL_TIMSRC_W                                              2U
#define LRFDRFE_TIMCTL_TIMSRC_M                                     0x00000006U
#define LRFDRFE_TIMCTL_TIMSRC_S                                              1U
#define LRFDRFE_TIMCTL_TIMSRC_FREF                                  0x00000006U
#define LRFDRFE_TIMCTL_TIMSRC_MAGN1                                 0x00000004U
#define LRFDRFE_TIMCTL_TIMSRC_MAGN0                                 0x00000002U
#define LRFDRFE_TIMCTL_TIMSRC_CLK                                   0x00000000U

// Field:     [0] TIMCTL 
//
// 16-bit timer control 
//
// It will generate a timer interrupt after TIMPER timer ticks. Note that the 
// internal timer value is not readable from the RFE. If this is needed the 
// counter should be used instead of the timer. 
// ENUMs: 
// EN                       Enable timer 
// DIS                      Disable timer and clear internal timer value 
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
// Programmable increment for the counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Configurable 16 bit period that can be used for either the timer or the 
// counter. In timer context, when timer value reach the timer period (i.e. it 
// expires) a TIMER_IRQ event will occur, and the timer will restart from zero 
// (until the timer is manually disabled). In counter context, a COUNTER_IRQ 
// event will occur when the counter is equal to or higher than the period 
// value. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// 16 bit value of counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Captured value of counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Sends a command to the tracer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Tracer busy status 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Number of parameters 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDRFE_TRCCMD_PARCNT_W                                              2U
#define LRFDRFE_TRCCMD_PARCNT_M                                     0x00000300U
#define LRFDRFE_TRCCMD_PARCNT_S                                              8U
#define LRFDRFE_TRCCMD_PARCNT_ALLONES                               0x00000300U
#define LRFDRFE_TRCCMD_PARCNT_ALLZEROS                              0x00000000U

// Field:   [7:0] PKTHDR 
//
// Packet header 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Parameter 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Parameter 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Select GPO7 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO7 
#define LRFDRFE_GPOCTL_SEL7                                         0x00008000U
#define LRFDRFE_GPOCTL_SEL7_M                                       0x00008000U
#define LRFDRFE_GPOCTL_SEL7_S                                               15U
#define LRFDRFE_GPOCTL_SEL7_HW                                      0x00008000U
#define LRFDRFE_GPOCTL_SEL7_SW                                      0x00000000U

// Field:    [14] SEL6 
//
// Select GPO6 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO6 
#define LRFDRFE_GPOCTL_SEL6                                         0x00004000U
#define LRFDRFE_GPOCTL_SEL6_M                                       0x00004000U
#define LRFDRFE_GPOCTL_SEL6_S                                               14U
#define LRFDRFE_GPOCTL_SEL6_HW                                      0x00004000U
#define LRFDRFE_GPOCTL_SEL6_SW                                      0x00000000U

// Field:    [13] SEL5 
//
// Select GPO5 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO5 
#define LRFDRFE_GPOCTL_SEL5                                         0x00002000U
#define LRFDRFE_GPOCTL_SEL5_M                                       0x00002000U
#define LRFDRFE_GPOCTL_SEL5_S                                               13U
#define LRFDRFE_GPOCTL_SEL5_HW                                      0x00002000U
#define LRFDRFE_GPOCTL_SEL5_SW                                      0x00000000U

// Field:    [12] SEL4 
//
// Select GPO4 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO4 
#define LRFDRFE_GPOCTL_SEL4                                         0x00001000U
#define LRFDRFE_GPOCTL_SEL4_M                                       0x00001000U
#define LRFDRFE_GPOCTL_SEL4_S                                               12U
#define LRFDRFE_GPOCTL_SEL4_HW                                      0x00001000U
#define LRFDRFE_GPOCTL_SEL4_SW                                      0x00000000U

// Field:    [11] SEL3 
//
// Select GPO3 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO3 
#define LRFDRFE_GPOCTL_SEL3                                         0x00000800U
#define LRFDRFE_GPOCTL_SEL3_M                                       0x00000800U
#define LRFDRFE_GPOCTL_SEL3_S                                               11U
#define LRFDRFE_GPOCTL_SEL3_HW                                      0x00000800U
#define LRFDRFE_GPOCTL_SEL3_SW                                      0x00000000U

// Field:    [10] SEL2 
//
// Select GPO2 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO2 
#define LRFDRFE_GPOCTL_SEL2                                         0x00000400U
#define LRFDRFE_GPOCTL_SEL2_M                                       0x00000400U
#define LRFDRFE_GPOCTL_SEL2_S                                               10U
#define LRFDRFE_GPOCTL_SEL2_HW                                      0x00000400U
#define LRFDRFE_GPOCTL_SEL2_SW                                      0x00000000U

// Field:     [9] SEL1 
//
// Select GPO1 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO1 
#define LRFDRFE_GPOCTL_SEL1                                         0x00000200U
#define LRFDRFE_GPOCTL_SEL1_M                                       0x00000200U
#define LRFDRFE_GPOCTL_SEL1_S                                                9U
#define LRFDRFE_GPOCTL_SEL1_HW                                      0x00000200U
#define LRFDRFE_GPOCTL_SEL1_SW                                      0x00000000U

// Field:     [8] SEL0 
//
// Select GPO0 source 
// ENUMs: 
// HW                       The pin is controlled by its HW source 
// SW                       The pin is controlled by GPOCTRL.GPO0 
#define LRFDRFE_GPOCTL_SEL0                                         0x00000100U
#define LRFDRFE_GPOCTL_SEL0_M                                       0x00000100U
#define LRFDRFE_GPOCTL_SEL0_S                                                8U
#define LRFDRFE_GPOCTL_SEL0_HW                                      0x00000100U
#define LRFDRFE_GPOCTL_SEL0_SW                                      0x00000000U

// Field:     [7] GPO7 
//
// Control GPO7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO7                                         0x00000080U
#define LRFDRFE_GPOCTL_GPO7_M                                       0x00000080U
#define LRFDRFE_GPOCTL_GPO7_S                                                7U
#define LRFDRFE_GPOCTL_GPO7_ONE                                     0x00000080U
#define LRFDRFE_GPOCTL_GPO7_ZERO                                    0x00000000U

// Field:     [6] GPO6 
//
// Control GPO6 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO6                                         0x00000040U
#define LRFDRFE_GPOCTL_GPO6_M                                       0x00000040U
#define LRFDRFE_GPOCTL_GPO6_S                                                6U
#define LRFDRFE_GPOCTL_GPO6_ONE                                     0x00000040U
#define LRFDRFE_GPOCTL_GPO6_ZERO                                    0x00000000U

// Field:     [5] GPO5 
//
// Control GPO5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO5                                         0x00000020U
#define LRFDRFE_GPOCTL_GPO5_M                                       0x00000020U
#define LRFDRFE_GPOCTL_GPO5_S                                                5U
#define LRFDRFE_GPOCTL_GPO5_ONE                                     0x00000020U
#define LRFDRFE_GPOCTL_GPO5_ZERO                                    0x00000000U

// Field:     [4] GPO4 
//
// Control GPO4 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO4                                         0x00000010U
#define LRFDRFE_GPOCTL_GPO4_M                                       0x00000010U
#define LRFDRFE_GPOCTL_GPO4_S                                                4U
#define LRFDRFE_GPOCTL_GPO4_ONE                                     0x00000010U
#define LRFDRFE_GPOCTL_GPO4_ZERO                                    0x00000000U

// Field:     [3] GPO3 
//
// Control GPO3 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO3                                         0x00000008U
#define LRFDRFE_GPOCTL_GPO3_M                                       0x00000008U
#define LRFDRFE_GPOCTL_GPO3_S                                                3U
#define LRFDRFE_GPOCTL_GPO3_ONE                                     0x00000008U
#define LRFDRFE_GPOCTL_GPO3_ZERO                                    0x00000000U

// Field:     [2] GPO2 
//
// Control GPO2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO2                                         0x00000004U
#define LRFDRFE_GPOCTL_GPO2_M                                       0x00000004U
#define LRFDRFE_GPOCTL_GPO2_S                                                2U
#define LRFDRFE_GPOCTL_GPO2_ONE                                     0x00000004U
#define LRFDRFE_GPOCTL_GPO2_ZERO                                    0x00000000U

// Field:     [1] GPO1 
//
// Control GPO1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_GPOCTL_GPO1                                         0x00000002U
#define LRFDRFE_GPOCTL_GPO1_M                                       0x00000002U
#define LRFDRFE_GPOCTL_GPO1_S                                                1U
#define LRFDRFE_GPOCTL_GPO1_ONE                                     0x00000002U
#define LRFDRFE_GPOCTL_GPO1_ZERO                                    0x00000000U

// Field:     [0] GPO0 
//
// Control GPO0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
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
// Active low reset of ADC clock domain within Modem 
// ENUMs: 
// ACTIVE                   Don't reset 
// RESET                    Reset 
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN                                0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_M                              0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_S                                       4U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_ACTIVE                         0x00000010U
#define LRFDRFE_ANAISOCTL_ADCDIGRSTN_RESET                          0x00000000U

// Field:     [3] IFADC2SVTISO 
//
// Isolation between IFADC and Modem 
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO                              0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_M                            0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_S                                     3U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_ISOLATE                      0x00000008U
#define LRFDRFE_ANAISOCTL_IFADC2SVTISO_CONNECT                      0x00000000U

// Field:     [2] DIV2IFADCISO 
//
// Isolation between DIVBUF and IFADC 
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO                              0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_M                            0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_S                                     2U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_ISOLATE                      0x00000004U
#define LRFDRFE_ANAISOCTL_DIV2IFADCISO_CONNECT                      0x00000000U

// Field:     [1] MTDC2SVTISO 
//
// Isolation between MTDC and Modem 
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO                               0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_M                             0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_S                                      1U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_ISOLATE                       0x00000002U
#define LRFDRFE_ANAISOCTL_MTDC2SVTISO_CONNECT                       0x00000000U

// Field:     [0] DIV2MTDCISO 
//
// Isolation between DIVBUF and MTDC 
// ENUMs: 
// ISOLATE                  Isolate 
// CONNECT                  Don't isolate 
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
// DIV2 PH180 path control 
//
// Enable DIV2 PH180 path 
// INTERNAL NOTE: 
// renamed from EN_DIV2_PH180 
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE_DIVCTL_DIV2PH180                                    0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_M                                  0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_S                                          15U
#define LRFDRFE_DIVCTL_DIV2PH180_EN                                 0x00008000U
#define LRFDRFE_DIVCTL_DIV2PH180_DIS                                0x00000000U

// Field:    [14] DIV2PH0 
//
// DIV2 PH0 path control 
//
// Enable DIV2 PH0 path 
// INTERNAL NOTE: 
// renamed from EN_DIV2_PH0 
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE_DIVCTL_DIV2PH0                                      0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_M                                    0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_S                                            14U
#define LRFDRFE_DIVCTL_DIV2PH0_EN                                   0x00004000U
#define LRFDRFE_DIVCTL_DIV2PH0_DIS                                  0x00000000U

// Field:    [13] DIV2PH270 
//
// DIV2 PH270 path control 
//
// Enable DIV2 PH270 path 
//
// INTERNAL NOTE: 
// renamed from EN_DIV2_PH270 
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE_DIVCTL_DIV2PH270                                    0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_M                                  0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_S                                          13U
#define LRFDRFE_DIVCTL_DIV2PH270_EN                                 0x00002000U
#define LRFDRFE_DIVCTL_DIV2PH270_DIS                                0x00000000U

// Field:    [12] DIV2PH90 
//
// DIV2 PH90 path control 
//
// Enable DIV2 PH90 path 
// INTERNAL NOTE: 
// renamed from EN_DIV2_PH90 
// ENUMs: 
// EN                       Enable path 
// DIS                      Disable path 
#define LRFDRFE_DIVCTL_DIV2PH90                                     0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_M                                   0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_S                                           12U
#define LRFDRFE_DIVCTL_DIV2PH90_EN                                  0x00001000U
#define LRFDRFE_DIVCTL_DIV2PH90_DIS                                 0x00000000U

// Field:    [11] SPARE11 
//
// Reserved 
// ENUMs: 
// ONE                      Bit is one 
// ZERO                     Bit is 0 
#define LRFDRFE_DIVCTL_SPARE11                                      0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_M                                    0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_S                                            11U
#define LRFDRFE_DIVCTL_SPARE11_ONE                                  0x00000800U
#define LRFDRFE_DIVCTL_SPARE11_ZERO                                 0x00000000U

// Field:    [10] S1G20DBMMUX 
//
// Not connected 
// ENUMs: 
// DISABLE                  Disable mux 
// ENABLEN                  Enable mux 
#define LRFDRFE_DIVCTL_S1G20DBMMUX                                  0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_M                                0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_S                                        10U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_DISABLE                          0x00000400U
#define LRFDRFE_DIVCTL_S1G20DBMMUX_ENABLEN                          0x00000000U

// Field:     [9] ADCDIV 
//
// ADC divider control 
//
// Field enables divider that generates IFADC clock. 
//
// INTERNAL NOTE: 
// Renamed from EN_ADC 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_ADCDIV                                       0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_M                                     0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_S                                              9U
#define LRFDRFE_DIVCTL_ADCDIV_EN                                    0x00000200U
#define LRFDRFE_DIVCTL_ADCDIV_DIS                                   0x00000000U

// Field:     [8] ENSYNTH 
//
// Enables CKVD clock to MTDC 
// ENUMs: 
// EN                       Clock is enabled 
// DIS                      Clock is disabled 
#define LRFDRFE_DIVCTL_ENSYNTH                                      0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_M                                    0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_S                                             8U
#define LRFDRFE_DIVCTL_ENSYNTH_EN                                   0x00000100U
#define LRFDRFE_DIVCTL_ENSYNTH_DIS                                  0x00000000U

// Field:     [7] TXPH18020DBMDIV 
//
// Not connected 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV                              0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_M                            0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_S                                     7U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_EN                           0x00000080U
#define LRFDRFE_DIVCTL_TXPH18020DBMDIV_DIS                          0x00000000U

// Field:     [6] TXPH020DBMDIV 
//
// Not connected 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_TXPH020DBMDIV                                0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_M                              0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_S                                       6U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_EN                             0x00000040U
#define LRFDRFE_DIVCTL_TXPH020DBMDIV_DIS                            0x00000000U

// Field:     [5] TXPH180DIV 
//
// TX 180-phase divider control 
//
// Field enables divider that generates inverted TX RF signal to PA. 
//
// INTERNAL NOTE: 
// renamed from EN_TX_PH180, there is no such thing as a TX clock 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_TXPH180DIV                                   0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_M                                 0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_S                                          5U
#define LRFDRFE_DIVCTL_TXPH180DIV_EN                                0x00000020U
#define LRFDRFE_DIVCTL_TXPH180DIV_DIS                               0x00000000U

// Field:     [4] TXPH0DIV 
//
// TX 0-phase divider control 
//
// Field enables divider that generates TX RF signal to PA. 
//
// INTERNAL NOTE: 
// renamed from EN_TX_PH0, there is no such thing as a TX clock 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_TXPH0DIV                                     0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_M                                   0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_S                                            4U
#define LRFDRFE_DIVCTL_TXPH0DIV_EN                                  0x00000010U
#define LRFDRFE_DIVCTL_TXPH0DIV_DIS                                 0x00000000U

// Field:     [3] RXPH90DIV 
//
// RX quadrature-phase LO divider control 
//
// Field enables quadrature-phase RX LO divider. 
//
// INTERNAL NOTE: 
// renamed form EN_RX_Q, Oddgeir mentioned that original text was wrong wrt 
// phase. 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_RXPH90DIV                                    0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_M                                  0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_S                                           3U
#define LRFDRFE_DIVCTL_RXPH90DIV_EN                                 0x00000008U
#define LRFDRFE_DIVCTL_RXPH90DIV_DIS                                0x00000000U

// Field:     [2] RXPH0DIV 
//
// RX in-phase LO divider control 
//
// Field enables in-phase RX LO divider. 
//
// INTERNAL NOTE: 
// renamed form EN_RX_I, Oddgeir mentioned that original text was wrong wrt 
// phase. 
// ENUMs: 
// EN                       Enable divider 
// DIS                      Disable divider 
#define LRFDRFE_DIVCTL_RXPH0DIV                                     0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_M                                   0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_S                                            2U
#define LRFDRFE_DIVCTL_RXPH0DIV_EN                                  0x00000004U
#define LRFDRFE_DIVCTL_RXPH0DIV_DIS                                 0x00000000U

// Field:     [1] Spare1 
//
// Not connected, not used in LRF 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_DIVCTL_SPARE1                                       0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_M                                     0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_S                                              1U
#define LRFDRFE_DIVCTL_SPARE1_ONE                                   0x00000002U
#define LRFDRFE_DIVCTL_SPARE1_ZERO                                  0x00000000U

// Field:     [0] EN 
//
// Divider enable 
// ENUMs: 
// ON                       Enable divider 
// OFF                      Disable divider 
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
// Reserved for future use 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDRFE_RXCTRL_SPARE                                        0x00001000U
#define LRFDRFE_RXCTRL_SPARE_M                                      0x00001000U
#define LRFDRFE_RXCTRL_SPARE_S                                              12U
#define LRFDRFE_RXCTRL_SPARE_ONE                                    0x00001000U
#define LRFDRFE_RXCTRL_SPARE_ZERO                                   0x00000000U

// Field:  [11:9] ATTN 
//
// Attenuator Control 
// ENUMs: 
// _21DB                    21dB attenuation 
// _18DB                    18dB attenuation 
// _15DB                    15dB attenuation 
// _12DB                    12dB attenuation 
// _9DB                     9dB attenuation 
// _6DB                     6dB attenuation 
// _3DB                     3dB attenuation 
// NOATT                    No attenuation 
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
// IFAMP Gain Control 
// ENUMs: 
// MAX                      Set IFAMP gain to MAX 
// MIN3DB                   Set gain to MAX - 3 dB 
// MIN6DB                   Set gain to MAX - 6 dB 
// MIN9DB                   Set gain to MAX - 9 dB 
// MIN12DB                  Set gain to MAX - 12 dB 
// MIN15DB                  Set gain to MAX - 15 dB 
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
// LNA Gain Control 
// ENUMs: 
// MAX                      Set gain to MAX 
// MIN3DB                   Set gain to MAX - 3 dB 
// MIN6DB                   Set gain to MAX - 6 dB 
// MIN9DB                   Set gain to MAX - 9 dB 
// MIN12DB                  Set gain to MAX - 12 dB 
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
// Accumulated magnitude over the period 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Accumulated magnitude over the period 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Current RSSI value (signed). If this register reads as -128 (0x80) it means 
// that the value is not yet valid. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Maximum RSSI value since start of measurements cycle. If this field reads as 
// -128 (0x80) it means that the value is not yet valid. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Current RF front-end gain, in dB 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Result of quantizer calibration. Valid only when calibration is done 
// ENUMs: 
// COMP1                    I comparator 
// COMP0                    Q Comparator 
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_W                                      5U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_M                             0x0000007CU
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_S                                      2U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_COMP1                         0x00000004U
#define LRFDRFE_IFADCSTAT_QUANTCALVAL_COMP0                         0x00000000U

// Field:     [1] QUANTCALDONE 
//
// Status of the quantizer calibration 
// ENUMs: 
// READY                    Calibration is complete 
// NOT_READY                Calibration is not finished 
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
// Indicates status of serial divider 
// ENUMs: 
// BUSY                     Serial divider is busy and result is not available 
//                          yet 
// IDLE                     Serial divider is idle 
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
// Dividend input (write only, reads as 0x0). 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Dividend input (write only, reads as 0x0). 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Divisor input. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Divisor input 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Quotient output 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Quotient output 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Product of DIVISORL_VALLSB and DIVISORH_VALMSB 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Upper 16-bit of DIVISORL.VALLSB multiplied by DIVISORH.VALMSB 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
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
// Multiplier result ready / HW multiplier idle 
// ENUMs: 
// BUSY                     Multiplier is busy, result is not ready yet 
// IDLE                     Multiplier is idle 
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
// Controls unsigned / signed mode of serial multiplier 
// ENUMs: 
// SIGNED                   Multiplier assumes inputs are signed numbers 
// UNSIGNED                 Multiplier assumes inputs are unsigned numbers 
#define LRFDRFE_MULTCFG_MODE                                        0x00000001U
#define LRFDRFE_MULTCFG_MODE_M                                      0x00000001U
#define LRFDRFE_MULTCFG_MODE_S                                               0U
#define LRFDRFE_MULTCFG_MODE_SIGNED                                 0x00000001U
#define LRFDRFE_MULTCFG_MODE_UNSIGNED                               0x00000000U


#endif // __LRFDRFE__
