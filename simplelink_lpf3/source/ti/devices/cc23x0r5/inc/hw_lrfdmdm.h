/******************************************************************************
*  Filename:       hw_lrfdmdm_h
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

#ifndef __HW_LRFDMDM_H__
#define __HW_LRFDMDM_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDMDM component
//
//*****************************************************************************
// Modem Enable Register 
#define LRFDMDM_O_ENABLE                                            0x00000000U

// MCE program source select register 
#define LRFDMDM_O_FWSRC                                             0x00000004U

// Modem Initialize Register 
#define LRFDMDM_O_INIT                                              0x00000008U

// Demodulator Enable Register 0 
#define LRFDMDM_O_DEMENABLE0                                        0x00000010U

// Demodulator Enable Register 1 
#define LRFDMDM_O_DEMENABLE1                                        0x00000014U

// Demodulator Initialize Register 0 
#define LRFDMDM_O_DEMINIT0                                          0x00000018U

// Demodulator Initialize Register 1 
#define LRFDMDM_O_DEMINIT1                                          0x0000001CU

// Modem Command Engine (MCE) Strobe Register 0 
#define LRFDMDM_O_STRB0                                             0x00000020U

// Modem Command Engine (MCE) Strobe Register 1 
#define LRFDMDM_O_STRB1                                             0x00000024U

// MCE Event Flag Register 0 
#define LRFDMDM_O_EVT0                                              0x00000028U

// MCE Event Flag Register 1 
#define LRFDMDM_O_EVT1                                              0x0000002CU

// MCE Event Flag Register 2 
#define LRFDMDM_O_EVT2                                              0x00000030U

// MCE Event Mask Register 0 
#define LRFDMDM_O_EVTMSK0                                           0x00000038U

// MCE Event Mask Register 1 
#define LRFDMDM_O_EVTMSK1                                           0x0000003CU

// MCE Event Mask Register 2 
#define LRFDMDM_O_EVTMSK2                                           0x00000040U

// MCE Event Clear Register 0 
#define LRFDMDM_O_EVTCLR0                                           0x00000048U

// MCE Event Clear Register 1 
#define LRFDMDM_O_EVTCLR1                                           0x0000004CU

// MCE Event Clear Register 2 
#define LRFDMDM_O_EVTCLR2                                           0x00000050U

// Modem Power Down Request Register 
#define LRFDMDM_O_PDREQ                                             0x00000058U

// Modem API Command Register 
#define LRFDMDM_O_API                                               0x0000005CU

// Modem API Command Parameter 0 
#define LRFDMDM_O_CMDPAR0                                           0x00000060U

// Modem API Command Parameter 1 
#define LRFDMDM_O_CMDPAR1                                           0x00000064U

// Modem API Command Parameter 2 
#define LRFDMDM_O_CMDPAR2                                           0x00000068U

// Modem Command Status Register 
#define LRFDMDM_O_MSGBOX                                            0x0000006CU

// Frequency Offset 
#define LRFDMDM_O_FREQ                                              0x00000070U

// Modem FIFO Write Register 
#define LRFDMDM_O_FIFOWR                                            0x00000074U

// Modem FIFO Read Register 
#define LRFDMDM_O_FIFORD                                            0x00000078U

// Modem FIFO Write Configuration 
#define LRFDMDM_O_FIFOWRCTRL                                        0x00000080U

// Modem FIFO Read Configuration 
#define LRFDMDM_O_FIFORDCTRL                                        0x00000084U

// Modem FIFO Status Flags 
#define LRFDMDM_O_FIFOSTA                                           0x0000008CU

// MCE-to-RFE Send Data Register 
#define LRFDMDM_O_RFEDATOUT0                                        0x00000090U

// RFE-to-MCE Receive Data Register 
#define LRFDMDM_O_RFEDATIN0                                         0x00000094U

// MCE-to-RFE Send Command Register 
#define LRFDMDM_O_RFECMDOUT                                         0x00000098U

// RFE-to-MCE Receive Command Register 
#define LRFDMDM_O_RFECMDIN                                          0x0000009CU

// MCE-to-PBE Send Data Register 
#define LRFDMDM_O_PBEDATOUT0                                        0x000000A0U

// RFE-to-MCE Receive Data Register 
#define LRFDMDM_O_PBEDATIN0                                         0x000000A4U

// MCE-to-PBE Send Command Register 
#define LRFDMDM_O_PBECMDOUT                                         0x000000A8U

// PBE-to-MCE Receive Command Register 
#define LRFDMDM_O_PBECMDIN                                          0x000000ACU

// Link quality indicator 
#define LRFDMDM_O_LQIEST                                            0x000000B0U

// PBE event mux 
#define LRFDMDM_O_PBEEVTMUX                                         0x000000B4U

// SYSTIME event mux 0 
#define LRFDMDM_O_SYSTIMEVTMUX0                                     0x000000B8U

// SYSTIME event mux 1 
#define LRFDMDM_O_SYSTIMEVTMUX1                                     0x000000BCU

// ADC Digital Interface Configuration 
#define LRFDMDM_O_ADCDIGCONF                                        0x000000C0U

// Modulator Preamble Control 
#define LRFDMDM_O_MODPRECTRL                                        0x000000C4U

// Modulator Symbol Mapping Register 0 
#define LRFDMDM_O_MODSYMMAP0                                        0x000000C8U

// Modulator Symbol Mapping Register 1 
#define LRFDMDM_O_MODSYMMAP1                                        0x000000CCU

// Modulator Soft Symbol Transmit 
#define LRFDMDM_O_MODSOFTTX                                         0x000000D0U

// Modem Baud Rate Control 
#define LRFDMDM_O_BAUD                                              0x000000D4U

// Modem Baud Rate Prescaler Control 
#define LRFDMDM_O_BAUDPRE                                           0x000000D8U

// Modulator Main Config Register 
#define LRFDMDM_O_MODMAIN                                           0x000000DCU

// Demodulator Config Register 0 
#define LRFDMDM_O_DEMMISC0                                          0x000000E0U

// Demodulator Config Register 1 
#define LRFDMDM_O_DEMMISC1                                          0x000000E4U

// Demodulator Config Register 2 
#define LRFDMDM_O_DEMMISC2                                          0x000000E8U

// Demodulator Config Register 3 
#define LRFDMDM_O_DEMMISC3                                          0x000000ECU

// Demodulator I/Q Mismatch Compensation Register 
#define LRFDMDM_O_DEMIQMC0                                          0x000000F0U

// Dynamic Sample Buffer Config Register 
#define LRFDMDM_O_DEMDSBU                                           0x000000F4U

// Demodulator Coarse DC Offset Estimator Register 0 
#define LRFDMDM_O_DEMCODC0                                          0x000000F8U

// Demodulator Fine DC Offset Estimator Register 0 
#define LRFDMDM_O_DEMFIDC0                                          0x000000FCU

// Demodulator Front-End Crossbar Register 0 
#define LRFDMDM_O_DEMFEXB0                                          0x00000100U

// Demodulator Decode Stage Crossbar Register 0 
#define LRFDMDM_O_DEMDSXB0                                          0x00000104U

// Demodulator Fine Frequency Offset Estimator Register 0 
#define LRFDMDM_O_DEMFIFE0                                          0x00000108U

// Demodulator Matched Filter Register 0 
#define LRFDMDM_O_DEMMAFI0                                          0x0000010CU

// Demodulator Matched Filter Register 1 
#define LRFDMDM_O_DEMMAFI1                                          0x00000110U

// Demodulator Matched Filter Register 2 
#define LRFDMDM_O_DEMMAFI2                                          0x00000114U

// Demodulator Correlator 1-bit Engine Register 0 
#define LRFDMDM_O_DEMC1BE0                                          0x00000118U

// Demodulator Correlator 1-bit Engine Register 1 
#define LRFDMDM_O_DEMC1BE1                                          0x0000011CU

// Demodulator Correlator 1-bit Engine Register 2 
#define LRFDMDM_O_DEMC1BE2                                          0x00000120U

// Modem Spare 0 
#define LRFDMDM_O_SPARE0                                            0x00000124U

// Modem Spare 1 
#define LRFDMDM_O_SPARE1                                            0x00000128U

// Modem Spare 2 
#define LRFDMDM_O_SPARE2                                            0x0000012CU

// Modem Spare 3 
#define LRFDMDM_O_SPARE3                                            0x00000130U

// Demodulator Sync Word Qualifier Register 0 
#define LRFDMDM_O_DEMSWQU0                                          0x00000134U

// Correlator reference register 0 
#define LRFDMDM_O_DEMC1BEREF0                                       0x00000138U

// Correlator reference register 1 
#define LRFDMDM_O_DEMC1BEREF1                                       0x0000013CU

// Correlator reference register 2 
#define LRFDMDM_O_DEMC1BEREF2                                       0x00000140U

// Correlator reference register 3 
#define LRFDMDM_O_DEMC1BEREF3                                       0x00000144U

// Dynamic Modem Control Signals from MCE 
#define LRFDMDM_O_MODCTRL                                           0x00000148U

// Dynamic Modulator Preamble Register 
#define LRFDMDM_O_MODPREAMBLE                                       0x0000014CU

// Demodulator Fractional Resampler Register 0 
#define LRFDMDM_O_DEMFRAC0                                          0x00000150U

// Demodulator Fractional Resampler Register 1 
#define LRFDMDM_O_DEMFRAC1                                          0x00000154U

// Demodulator Fractional Resampler Register 2 
#define LRFDMDM_O_DEMFRAC2                                          0x00000158U

// Demodulator Fractional Resampler Register 3 
#define LRFDMDM_O_DEMFRAC3                                          0x0000015CU

// Demodulator Coarse DC Offset Estimator Register 1 
#define LRFDMDM_O_DEMCODC1                                          0x00000160U

// Demodulator Coarse DC Offset Estimator Register 2 
#define LRFDMDM_O_DEMCODC2                                          0x00000164U

// Demodulator Fine DC Offset Estimator Register 1 
#define LRFDMDM_O_DEMFIDC1                                          0x00000168U

// Demodulator Fine DC Offset Estimator Register 2 
#define LRFDMDM_O_DEMFIDC2                                          0x0000016CU

// Demodulator Fine Frequency Offset Estimator Register 1 
#define LRFDMDM_O_DEMFIFE1                                          0x00000170U

// Demodulator Manual Frequency Compensation Register 0 
#define LRFDMDM_O_DEMMAFC0                                          0x00000174U

// Demodulator Matched Filter Register 4 
#define LRFDMDM_O_DEMMAFI4                                          0x00000178U

// Demodulator Sync Word DC Imbalance Register 
#define LRFDMDM_O_DEMSWIMBAL                                        0x0000017CU

// Demodulator Soft PDIFF Value Register 
#define LRFDMDM_O_DEMSOFTPDIFF                                      0x00000180U

// Demodulator Debug Register 
#define LRFDMDM_O_DEMDEBUG                                          0x00000184U

// Viterbi Control Register 
#define LRFDMDM_O_VITCTRL                                           0x00000188U

// Viterbi Compute Register 
#define LRFDMDM_O_VITCOMPUTE                                        0x0000018CU

// Viterbi APM Readback Register 
#define LRFDMDM_O_VITAPMRDBACK                                      0x00000190U

// Viterbi State Register 
#define LRFDMDM_O_VITSTATE                                          0x00000194U

// Viterbi Branch Metric 1 and 0 Register 
#define LRFDMDM_O_VITBRMETRIC10                                     0x00000198U

// Viterbi Branch Metric 3 and 2 Register 
#define LRFDMDM_O_VITBRMETRIC32                                     0x0000019CU

// Viterbi Branch Metric 5 and 4 Register 
#define LRFDMDM_O_VITBRMETRIC54                                     0x000001A0U

// Viterbi Branch Metric 7 and 6 Register 
#define LRFDMDM_O_VITBRMETRIC76                                     0x000001A4U

// Modem Timer and Counter Control Register 
#define LRFDMDM_O_TIMCTL                                            0x000001E4U

// Modem Counter Increment Configuration 
#define LRFDMDM_O_TIMINC                                            0x000001E8U

// Modem Timer/Counter Period Configuration 
#define LRFDMDM_O_TIMPER                                            0x000001ECU

// Modem Counter Value 
#define LRFDMDM_O_TIMCNT                                            0x000001F0U

// Modem Counter Capture Value 
#define LRFDMDM_O_TIMCAPT                                           0x000001F4U

// Modem Timebase Control Register 
#define LRFDMDM_O_TIMEBASE                                          0x000001F8U

// Local Count Ones Input Register 
#define LRFDMDM_O_COUNT1IN                                          0x000001FCU

// Local Count Ones Result Register 
#define LRFDMDM_O_COUNT1RES                                         0x00000200U

// Local Branch Metric Accelerator Module Register 1 
#define LRFDMDM_O_BRMACC1                                           0x00000208U

// Local Branch Metric Accelerator Module Register 2 
#define LRFDMDM_O_BRMACC2                                           0x0000020CU

// MCE Tracer Send Trigger Register 
#define LRFDMDM_O_MCETRCCTRL                                        0x00000210U

// MCE Tracer Status Register 
#define LRFDMDM_O_MCETRCSTAT                                        0x00000214U

// MCE Tracer Command Register 
#define LRFDMDM_O_MCETRCCMD                                         0x00000218U

// MCE Tracer Command Parameter Register 0 
#define LRFDMDM_O_MCETRCPAR0                                        0x0000021CU

// MCE Tracer Command Parameter Register 1 
#define LRFDMDM_O_MCETRCPAR1                                        0x00000220U

// Modem Readback Capture Register 0 
#define LRFDMDM_O_RDCAPT0                                           0x00000224U

// Modem Readback Capture Register 1 
#define LRFDMDM_O_RDCAPT1                                           0x00000228U

// Frontend capture readback register 0 
#define LRFDMDM_O_FECAPT0                                           0x0000022CU

// Frontend capture readback register 1 
#define LRFDMDM_O_FECAPT1                                           0x00000230U

// Decoding stage capture register 0 
#define LRFDMDM_O_DSCAPT0                                           0x00000234U

// Decoding stage capture register 1 
#define LRFDMDM_O_DSCAPT1                                           0x00000238U

// Decoding stage capture register 2 
#define LRFDMDM_O_DSCAPT2                                           0x0000023CU

// Decoding stage capture register 3 
#define LRFDMDM_O_DSCAPT3                                           0x00000240U

// Demodulator sync word qualifier register 1 
#define LRFDMDM_O_DEMSWQU1                                          0x00000244U

// Control of the MCE GPO signals 
#define LRFDMDM_O_GPOCTRL0                                          0x00000248U

// Control of the MCE GPO signals 
#define LRFDMDM_O_GPOCTRL1                                          0x0000024CU

// RFE received signal strength indicator 
#define LRFDMDM_O_RFERSSI                                           0x00000250U

// RFE received signal strength indicator 
#define LRFDMDM_O_RFEMAXRSSI                                        0x00000254U

// RFE front end gain setting 
#define LRFDMDM_O_RFEDBGAIN                                         0x00000258U

// Modem Sync Word Register 0 
#define LRFDMDM_O_SYNC0                                             0x0000025CU

// Modem Sync Word Register 1 
#define LRFDMDM_O_SYNC1                                             0x00000260U

// Modem Sync Word Register 2 
#define LRFDMDM_O_SYNC2                                             0x00000264U

// Modem Sync Word Register 3 
#define LRFDMDM_O_SYNC3                                             0x00000268U

//*****************************************************************************
//
// Register: LRFDMDM_O_ENABLE
//
//*****************************************************************************
// Field:     [5] ADCDIG 
//
// Enables the ADC Digital interface 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_ADCDIG                                       0x00000020U
#define LRFDMDM_ENABLE_ADCDIG_M                                     0x00000020U
#define LRFDMDM_ENABLE_ADCDIG_S                                              5U
#define LRFDMDM_ENABLE_ADCDIG_EN                                    0x00000020U
#define LRFDMDM_ENABLE_ADCDIG_DIS                                   0x00000000U

// Field:     [4] DEMODULATOR 
//
// Enables the Demodulator 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_DEMODULATOR                                  0x00000010U
#define LRFDMDM_ENABLE_DEMODULATOR_M                                0x00000010U
#define LRFDMDM_ENABLE_DEMODULATOR_S                                         4U
#define LRFDMDM_ENABLE_DEMODULATOR_EN                               0x00000010U
#define LRFDMDM_ENABLE_DEMODULATOR_DIS                              0x00000000U

// Field:     [3] MODULATOR 
//
// Enables the Modulator 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_MODULATOR                                    0x00000008U
#define LRFDMDM_ENABLE_MODULATOR_M                                  0x00000008U
#define LRFDMDM_ENABLE_MODULATOR_S                                           3U
#define LRFDMDM_ENABLE_MODULATOR_EN                                 0x00000008U
#define LRFDMDM_ENABLE_MODULATOR_DIS                                0x00000000U

// Field:     [2] TIMEBASE 
//
// Enables the Modem Timebase 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_TIMEBASE                                     0x00000004U
#define LRFDMDM_ENABLE_TIMEBASE_M                                   0x00000004U
#define LRFDMDM_ENABLE_TIMEBASE_S                                            2U
#define LRFDMDM_ENABLE_TIMEBASE_EN                                  0x00000004U
#define LRFDMDM_ENABLE_TIMEBASE_DIS                                 0x00000000U

// Field:     [1] TXRXFIFO 
//
// Enables the TX/RX FIFO 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_TXRXFIFO                                     0x00000002U
#define LRFDMDM_ENABLE_TXRXFIFO_M                                   0x00000002U
#define LRFDMDM_ENABLE_TXRXFIFO_S                                            1U
#define LRFDMDM_ENABLE_TXRXFIFO_EN                                  0x00000002U
#define LRFDMDM_ENABLE_TXRXFIFO_DIS                                 0x00000000U

// Field:     [0] TOPSM 
//
// Enables the TOPsm (MCE) 
// ENUMs: 
// EN                       Enable 
// DIS                      Disable 
#define LRFDMDM_ENABLE_TOPSM                                        0x00000001U
#define LRFDMDM_ENABLE_TOPSM_M                                      0x00000001U
#define LRFDMDM_ENABLE_TOPSM_S                                               0U
#define LRFDMDM_ENABLE_TOPSM_EN                                     0x00000001U
#define LRFDMDM_ENABLE_TOPSM_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FWSRC
//
//*****************************************************************************
// Field:     [2] DATARAM 
//
// Selects which RAM will be used for data storage 
// ENUMs: 
// S2RRAM                   Use S2RRAM for data 
// MDMRAM                   Use MDMRAM for data 
#define LRFDMDM_FWSRC_DATARAM                                       0x00000004U
#define LRFDMDM_FWSRC_DATARAM_M                                     0x00000004U
#define LRFDMDM_FWSRC_DATARAM_S                                              2U
#define LRFDMDM_FWSRC_DATARAM_S2RRAM                                0x00000004U
#define LRFDMDM_FWSRC_DATARAM_MDMRAM                                0x00000000U

// Field:     [1] FWRAM 
//
// Select which RAM we run FW from 
// ENUMs: 
// S2RRAM                   Run code from S2RRAM 
// MDMRAM                   Run code from MDMRAM 
#define LRFDMDM_FWSRC_FWRAM                                         0x00000002U
#define LRFDMDM_FWSRC_FWRAM_M                                       0x00000002U
#define LRFDMDM_FWSRC_FWRAM_S                                                1U
#define LRFDMDM_FWSRC_FWRAM_S2RRAM                                  0x00000002U
#define LRFDMDM_FWSRC_FWRAM_MDMRAM                                  0x00000000U

// Field:     [0] BANK 
//
// Sets the MSB of the address to the memory holding the program 
// ENUMs: 
// ONE                      Run code from bank 1 
// ZERO                     Run code from bank 0 
#define LRFDMDM_FWSRC_BANK                                          0x00000001U
#define LRFDMDM_FWSRC_BANK_M                                        0x00000001U
#define LRFDMDM_FWSRC_BANK_S                                                 0U
#define LRFDMDM_FWSRC_BANK_ONE                                      0x00000001U
#define LRFDMDM_FWSRC_BANK_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_INIT
//
//*****************************************************************************
// Field:     [5] ADCDIG 
//
// Synch reset ADC Digital interface 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_ADCDIG                                         0x00000020U
#define LRFDMDM_INIT_ADCDIG_M                                       0x00000020U
#define LRFDMDM_INIT_ADCDIG_S                                                5U
#define LRFDMDM_INIT_ADCDIG_RESET                                   0x00000020U
#define LRFDMDM_INIT_ADCDIG_NO_EFFECT                               0x00000000U

// Field:     [4] DEMODULATOR 
//
// Synch reset Demodulator 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_DEMODULATOR                                    0x00000010U
#define LRFDMDM_INIT_DEMODULATOR_M                                  0x00000010U
#define LRFDMDM_INIT_DEMODULATOR_S                                           4U
#define LRFDMDM_INIT_DEMODULATOR_RESET                              0x00000010U
#define LRFDMDM_INIT_DEMODULATOR_NO_EFFECT                          0x00000000U

// Field:     [3] MODULATOR 
//
// Synch reset Modulator 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_MODULATOR                                      0x00000008U
#define LRFDMDM_INIT_MODULATOR_M                                    0x00000008U
#define LRFDMDM_INIT_MODULATOR_S                                             3U
#define LRFDMDM_INIT_MODULATOR_RESET                                0x00000008U
#define LRFDMDM_INIT_MODULATOR_NO_EFFECT                            0x00000000U

// Field:     [2] TIMEBASE 
//
// Synch reset Modem Timebase 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_TIMEBASE                                       0x00000004U
#define LRFDMDM_INIT_TIMEBASE_M                                     0x00000004U
#define LRFDMDM_INIT_TIMEBASE_S                                              2U
#define LRFDMDM_INIT_TIMEBASE_RESET                                 0x00000004U
#define LRFDMDM_INIT_TIMEBASE_NO_EFFECT                             0x00000000U

// Field:     [1] TXRXFIFO 
//
// Synch reset TX/RX FIFO 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_TXRXFIFO                                       0x00000002U
#define LRFDMDM_INIT_TXRXFIFO_M                                     0x00000002U
#define LRFDMDM_INIT_TXRXFIFO_S                                              1U
#define LRFDMDM_INIT_TXRXFIFO_RESET                                 0x00000002U
#define LRFDMDM_INIT_TXRXFIFO_NO_EFFECT                             0x00000000U

// Field:     [0] TOPSM 
//
// Synch reset TOPsm (MCE) 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_INIT_TOPSM                                          0x00000001U
#define LRFDMDM_INIT_TOPSM_M                                        0x00000001U
#define LRFDMDM_INIT_TOPSM_S                                                 0U
#define LRFDMDM_INIT_TOPSM_RESET                                    0x00000001U
#define LRFDMDM_INIT_TOPSM_NO_EFFECT                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMENABLE0
//
//*****************************************************************************
// Field:     [8] FRAC 
//
// Enables the fractional resampler 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_FRAC                                     0x00000100U
#define LRFDMDM_DEMENABLE0_FRAC_M                                   0x00000100U
#define LRFDMDM_DEMENABLE0_FRAC_S                                            8U
#define LRFDMDM_DEMENABLE0_FRAC_EN                                  0x00000100U
#define LRFDMDM_DEMENABLE0_FRAC_DIS                                 0x00000000U

// Field:     [7] FIDC 
//
// Enables the fine DC estimator 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_FIDC                                     0x00000080U
#define LRFDMDM_DEMENABLE0_FIDC_M                                   0x00000080U
#define LRFDMDM_DEMENABLE0_FIDC_S                                            7U
#define LRFDMDM_DEMENABLE0_FIDC_EN                                  0x00000080U
#define LRFDMDM_DEMENABLE0_FIDC_DIS                                 0x00000000U

// Field:     [6] CHFI 
//
// Enables the channel filter 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_CHFI                                     0x00000040U
#define LRFDMDM_DEMENABLE0_CHFI_M                                   0x00000040U
#define LRFDMDM_DEMENABLE0_CHFI_S                                            6U
#define LRFDMDM_DEMENABLE0_CHFI_EN                                  0x00000040U
#define LRFDMDM_DEMENABLE0_CHFI_DIS                                 0x00000000U

// Field:     [5] BDEC 
//
// Enables the cascaded dec-by-2 stages (bde1 and bde2) 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_BDEC                                     0x00000020U
#define LRFDMDM_DEMENABLE0_BDEC_M                                   0x00000020U
#define LRFDMDM_DEMENABLE0_BDEC_S                                            5U
#define LRFDMDM_DEMENABLE0_BDEC_EN                                  0x00000020U
#define LRFDMDM_DEMENABLE0_BDEC_DIS                                 0x00000000U

// Field:     [4] IQMC 
//
// Enables the IQ mismatch compensation 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_IQMC                                     0x00000010U
#define LRFDMDM_DEMENABLE0_IQMC_M                                   0x00000010U
#define LRFDMDM_DEMENABLE0_IQMC_S                                            4U
#define LRFDMDM_DEMENABLE0_IQMC_EN                                  0x00000010U
#define LRFDMDM_DEMENABLE0_IQMC_DIS                                 0x00000000U

// Field:     [3] MGE1 
//
// Enables the magnitude estimator engine #1 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_MGE1                                     0x00000008U
#define LRFDMDM_DEMENABLE0_MGE1_M                                   0x00000008U
#define LRFDMDM_DEMENABLE0_MGE1_S                                            3U
#define LRFDMDM_DEMENABLE0_MGE1_EN                                  0x00000008U
#define LRFDMDM_DEMENABLE0_MGE1_DIS                                 0x00000000U

// Field:     [2] MGE0 
//
// Enables the magnitude estimator engine #0 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_MGE0                                     0x00000004U
#define LRFDMDM_DEMENABLE0_MGE0_M                                   0x00000004U
#define LRFDMDM_DEMENABLE0_MGE0_S                                            2U
#define LRFDMDM_DEMENABLE0_MGE0_EN                                  0x00000004U
#define LRFDMDM_DEMENABLE0_MGE0_DIS                                 0x00000000U

// Field:     [1] CODC 
//
// Enables the coarse DC estimator 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_CODC                                     0x00000002U
#define LRFDMDM_DEMENABLE0_CODC_M                                   0x00000002U
#define LRFDMDM_DEMENABLE0_CODC_S                                            1U
#define LRFDMDM_DEMENABLE0_CODC_EN                                  0x00000002U
#define LRFDMDM_DEMENABLE0_CODC_DIS                                 0x00000000U

// Field:     [0] CMIX 
//
// Enables the N/1024 complex mixer 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE0_CMIX                                     0x00000001U
#define LRFDMDM_DEMENABLE0_CMIX_M                                   0x00000001U
#define LRFDMDM_DEMENABLE0_CMIX_S                                            0U
#define LRFDMDM_DEMENABLE0_CMIX_EN                                  0x00000001U
#define LRFDMDM_DEMENABLE0_CMIX_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMENABLE1
//
//*****************************************************************************
// Field:    [13] VITE 
//
// Enables the Viterbi module 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_VITE                                     0x00002000U
#define LRFDMDM_DEMENABLE1_VITE_M                                   0x00002000U
#define LRFDMDM_DEMENABLE1_VITE_S                                           13U
#define LRFDMDM_DEMENABLE1_VITE_EN                                  0x00002000U
#define LRFDMDM_DEMENABLE1_VITE_DIS                                 0x00000000U

// Field:    [12] MLSE 
//
// Enables the MLSE module 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_MLSE                                     0x00001000U
#define LRFDMDM_DEMENABLE1_MLSE_M                                   0x00001000U
#define LRFDMDM_DEMENABLE1_MLSE_S                                           12U
#define LRFDMDM_DEMENABLE1_MLSE_EN                                  0x00001000U
#define LRFDMDM_DEMENABLE1_MLSE_DIS                                 0x00000000U

// Field:    [11] SOFD 
//
// Enables the soft decision module 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_SOFD                                     0x00000800U
#define LRFDMDM_DEMENABLE1_SOFD_M                                   0x00000800U
#define LRFDMDM_DEMENABLE1_SOFD_S                                           11U
#define LRFDMDM_DEMENABLE1_SOFD_EN                                  0x00000800U
#define LRFDMDM_DEMENABLE1_SOFD_DIS                                 0x00000000U

// Field:    [10] SWQU 
//
// Enables the sync word qualifier 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_SWQU                                     0x00000400U
#define LRFDMDM_DEMENABLE1_SWQU_M                                   0x00000400U
#define LRFDMDM_DEMENABLE1_SWQU_S                                           10U
#define LRFDMDM_DEMENABLE1_SWQU_EN                                  0x00000400U
#define LRFDMDM_DEMENABLE1_SWQU_DIS                                 0x00000000U

// Field:     [9] MAFC 
//
// Enables the manual frequency compensation module 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_MAFC                                     0x00000200U
#define LRFDMDM_DEMENABLE1_MAFC_M                                   0x00000200U
#define LRFDMDM_DEMENABLE1_MAFC_S                                            9U
#define LRFDMDM_DEMENABLE1_MAFC_EN                                  0x00000200U
#define LRFDMDM_DEMENABLE1_MAFC_DIS                                 0x00000000U

// Field:     [8] MAFI 
//
// Enables the matched filter 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_MAFI                                     0x00000100U
#define LRFDMDM_DEMENABLE1_MAFI_M                                   0x00000100U
#define LRFDMDM_DEMENABLE1_MAFI_S                                            8U
#define LRFDMDM_DEMENABLE1_MAFI_EN                                  0x00000100U
#define LRFDMDM_DEMENABLE1_MAFI_DIS                                 0x00000000U

// Field:     [7] FIFE 
//
// Enables the fine frequency offset estimator 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_FIFE                                     0x00000080U
#define LRFDMDM_DEMENABLE1_FIFE_M                                   0x00000080U
#define LRFDMDM_DEMENABLE1_FIFE_S                                            7U
#define LRFDMDM_DEMENABLE1_FIFE_EN                                  0x00000080U
#define LRFDMDM_DEMENABLE1_FIFE_DIS                                 0x00000000U

// Field:     [6] PDIF 
//
// Enables the phase differentiation 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_PDIF                                     0x00000040U
#define LRFDMDM_DEMENABLE1_PDIF_M                                   0x00000040U
#define LRFDMDM_DEMENABLE1_PDIF_S                                            6U
#define LRFDMDM_DEMENABLE1_PDIF_EN                                  0x00000040U
#define LRFDMDM_DEMENABLE1_PDIF_DIS                                 0x00000000U

// Field:     [5] CA2P 
//
// Enables the cart 2 polar conversion 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_CA2P                                     0x00000020U
#define LRFDMDM_DEMENABLE1_CA2P_M                                   0x00000020U
#define LRFDMDM_DEMENABLE1_CA2P_S                                            5U
#define LRFDMDM_DEMENABLE1_CA2P_EN                                  0x00000020U
#define LRFDMDM_DEMENABLE1_CA2P_DIS                                 0x00000000U

// Field:     [4] C1BE 
//
// Enables the correlation 1-bit engine 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_C1BE                                     0x00000010U
#define LRFDMDM_DEMENABLE1_C1BE_M                                   0x00000010U
#define LRFDMDM_DEMENABLE1_C1BE_S                                            4U
#define LRFDMDM_DEMENABLE1_C1BE_EN                                  0x00000010U
#define LRFDMDM_DEMENABLE1_C1BE_DIS                                 0x00000000U

// Field:     [3] LQIE 
//
// Enables the LQI engine 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_LQIE                                     0x00000008U
#define LRFDMDM_DEMENABLE1_LQIE_M                                   0x00000008U
#define LRFDMDM_DEMENABLE1_LQIE_S                                            3U
#define LRFDMDM_DEMENABLE1_LQIE_EN                                  0x00000008U
#define LRFDMDM_DEMENABLE1_LQIE_DIS                                 0x00000000U

// Field:     [2] F4BA 
//
// Enables the clock-domain crossing fifo 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_F4BA                                     0x00000004U
#define LRFDMDM_DEMENABLE1_F4BA_M                                   0x00000004U
#define LRFDMDM_DEMENABLE1_F4BA_S                                            2U
#define LRFDMDM_DEMENABLE1_F4BA_EN                                  0x00000004U
#define LRFDMDM_DEMENABLE1_F4BA_DIS                                 0x00000000U

// Field:     [1] STIM 
//
// Enables the symbol timing tracker 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_STIM                                     0x00000002U
#define LRFDMDM_DEMENABLE1_STIM_M                                   0x00000002U
#define LRFDMDM_DEMENABLE1_STIM_S                                            1U
#define LRFDMDM_DEMENABLE1_STIM_EN                                  0x00000002U
#define LRFDMDM_DEMENABLE1_STIM_DIS                                 0x00000000U

// Field:     [0] DSBU 
//
// Enables the dynamic sample buffer 
// ENUMs: 
// EN                       Enable module 
// DIS                      Disable 
#define LRFDMDM_DEMENABLE1_DSBU                                     0x00000001U
#define LRFDMDM_DEMENABLE1_DSBU_M                                   0x00000001U
#define LRFDMDM_DEMENABLE1_DSBU_S                                            0U
#define LRFDMDM_DEMENABLE1_DSBU_EN                                  0x00000001U
#define LRFDMDM_DEMENABLE1_DSBU_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMINIT0
//
//*****************************************************************************
// Field:     [8] FRAC 
//
// Synch reset fractional resampler 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_FRAC                                       0x00000100U
#define LRFDMDM_DEMINIT0_FRAC_M                                     0x00000100U
#define LRFDMDM_DEMINIT0_FRAC_S                                              8U
#define LRFDMDM_DEMINIT0_FRAC_RESET                                 0x00000100U
#define LRFDMDM_DEMINIT0_FRAC_NO_EFFECT                             0x00000000U

// Field:     [7] FIDC 
//
// Synch reset fine DC estimator 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_FIDC                                       0x00000080U
#define LRFDMDM_DEMINIT0_FIDC_M                                     0x00000080U
#define LRFDMDM_DEMINIT0_FIDC_S                                              7U
#define LRFDMDM_DEMINIT0_FIDC_RESET                                 0x00000080U
#define LRFDMDM_DEMINIT0_FIDC_NO_EFFECT                             0x00000000U

// Field:     [6] CHFI 
//
// Synch reset channel filter 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_CHFI                                       0x00000040U
#define LRFDMDM_DEMINIT0_CHFI_M                                     0x00000040U
#define LRFDMDM_DEMINIT0_CHFI_S                                              6U
#define LRFDMDM_DEMINIT0_CHFI_RESET                                 0x00000040U
#define LRFDMDM_DEMINIT0_CHFI_NO_EFFECT                             0x00000000U

// Field:     [5] BDEC 
//
// Synch reset cascaded dec-by-2 stages (bde1 and bde2) 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_BDEC                                       0x00000020U
#define LRFDMDM_DEMINIT0_BDEC_M                                     0x00000020U
#define LRFDMDM_DEMINIT0_BDEC_S                                              5U
#define LRFDMDM_DEMINIT0_BDEC_RESET                                 0x00000020U
#define LRFDMDM_DEMINIT0_BDEC_NO_EFFECT                             0x00000000U

// Field:     [4] IQMC 
//
// Synch reset IQ mismatch compensation 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_IQMC                                       0x00000010U
#define LRFDMDM_DEMINIT0_IQMC_M                                     0x00000010U
#define LRFDMDM_DEMINIT0_IQMC_S                                              4U
#define LRFDMDM_DEMINIT0_IQMC_RESET                                 0x00000010U
#define LRFDMDM_DEMINIT0_IQMC_NO_EFFECT                             0x00000000U

// Field:     [3] MGE1 
//
// Synch reset magnitude estimator engine #1 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_MGE1                                       0x00000008U
#define LRFDMDM_DEMINIT0_MGE1_M                                     0x00000008U
#define LRFDMDM_DEMINIT0_MGE1_S                                              3U
#define LRFDMDM_DEMINIT0_MGE1_RESET                                 0x00000008U
#define LRFDMDM_DEMINIT0_MGE1_NO_EFFECT                             0x00000000U

// Field:     [2] MGE0 
//
// Synch reset magnitude estimator engine #0 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_MGE0                                       0x00000004U
#define LRFDMDM_DEMINIT0_MGE0_M                                     0x00000004U
#define LRFDMDM_DEMINIT0_MGE0_S                                              2U
#define LRFDMDM_DEMINIT0_MGE0_RESET                                 0x00000004U
#define LRFDMDM_DEMINIT0_MGE0_NO_EFFECT                             0x00000000U

// Field:     [1] CODC 
//
// Synch reset coarse DC estimator 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_CODC                                       0x00000002U
#define LRFDMDM_DEMINIT0_CODC_M                                     0x00000002U
#define LRFDMDM_DEMINIT0_CODC_S                                              1U
#define LRFDMDM_DEMINIT0_CODC_RESET                                 0x00000002U
#define LRFDMDM_DEMINIT0_CODC_NO_EFFECT                             0x00000000U

// Field:     [0] CMIX 
//
// Synch reset N/1024 complex mixer 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT0_CMIX                                       0x00000001U
#define LRFDMDM_DEMINIT0_CMIX_M                                     0x00000001U
#define LRFDMDM_DEMINIT0_CMIX_S                                              0U
#define LRFDMDM_DEMINIT0_CMIX_RESET                                 0x00000001U
#define LRFDMDM_DEMINIT0_CMIX_NO_EFFECT                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMINIT1
//
//*****************************************************************************
// Field:    [13] VITE 
//
// Synch reset Viterbi Module 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_VITE                                       0x00002000U
#define LRFDMDM_DEMINIT1_VITE_M                                     0x00002000U
#define LRFDMDM_DEMINIT1_VITE_S                                             13U
#define LRFDMDM_DEMINIT1_VITE_RESET                                 0x00002000U
#define LRFDMDM_DEMINIT1_VITE_NO_EFFECT                             0x00000000U

// Field:    [12] MLSE 
//
// Synch reset MLSE module 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_MLSE                                       0x00001000U
#define LRFDMDM_DEMINIT1_MLSE_M                                     0x00001000U
#define LRFDMDM_DEMINIT1_MLSE_S                                             12U
#define LRFDMDM_DEMINIT1_MLSE_RESET                                 0x00001000U
#define LRFDMDM_DEMINIT1_MLSE_NO_EFFECT                             0x00000000U

// Field:    [11] SOFD 
//
// Synch reset soft decision module 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_SOFD                                       0x00000800U
#define LRFDMDM_DEMINIT1_SOFD_M                                     0x00000800U
#define LRFDMDM_DEMINIT1_SOFD_S                                             11U
#define LRFDMDM_DEMINIT1_SOFD_RESET                                 0x00000800U
#define LRFDMDM_DEMINIT1_SOFD_NO_EFFECT                             0x00000000U

// Field:    [10] SWQU 
//
// Synch reset sync word qualifyer 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_SWQU                                       0x00000400U
#define LRFDMDM_DEMINIT1_SWQU_M                                     0x00000400U
#define LRFDMDM_DEMINIT1_SWQU_S                                             10U
#define LRFDMDM_DEMINIT1_SWQU_RESET                                 0x00000400U
#define LRFDMDM_DEMINIT1_SWQU_NO_EFFECT                             0x00000000U

// Field:     [9] MAFC 
//
// Synch reset manual frequency compensation module 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_MAFC                                       0x00000200U
#define LRFDMDM_DEMINIT1_MAFC_M                                     0x00000200U
#define LRFDMDM_DEMINIT1_MAFC_S                                              9U
#define LRFDMDM_DEMINIT1_MAFC_RESET                                 0x00000200U
#define LRFDMDM_DEMINIT1_MAFC_NO_EFFECT                             0x00000000U

// Field:     [8] MAFI 
//
// Synch reset matched filter 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_MAFI                                       0x00000100U
#define LRFDMDM_DEMINIT1_MAFI_M                                     0x00000100U
#define LRFDMDM_DEMINIT1_MAFI_S                                              8U
#define LRFDMDM_DEMINIT1_MAFI_RESET                                 0x00000100U
#define LRFDMDM_DEMINIT1_MAFI_NO_EFFECT                             0x00000000U

// Field:     [7] FIFE 
//
// Synch reset fine frequency offset estimator 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_FIFE                                       0x00000080U
#define LRFDMDM_DEMINIT1_FIFE_M                                     0x00000080U
#define LRFDMDM_DEMINIT1_FIFE_S                                              7U
#define LRFDMDM_DEMINIT1_FIFE_RESET                                 0x00000080U
#define LRFDMDM_DEMINIT1_FIFE_NO_EFFECT                             0x00000000U

// Field:     [6] PDIF 
//
// Synch reset phase differentiation 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_PDIF                                       0x00000040U
#define LRFDMDM_DEMINIT1_PDIF_M                                     0x00000040U
#define LRFDMDM_DEMINIT1_PDIF_S                                              6U
#define LRFDMDM_DEMINIT1_PDIF_RESET                                 0x00000040U
#define LRFDMDM_DEMINIT1_PDIF_NO_EFFECT                             0x00000000U

// Field:     [5] CA2P 
//
// Synch reset cart 2 polar conversion 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_CA2P                                       0x00000020U
#define LRFDMDM_DEMINIT1_CA2P_M                                     0x00000020U
#define LRFDMDM_DEMINIT1_CA2P_S                                              5U
#define LRFDMDM_DEMINIT1_CA2P_RESET                                 0x00000020U
#define LRFDMDM_DEMINIT1_CA2P_NO_EFFECT                             0x00000000U

// Field:     [4] C1BE 
//
// Synch reset correlation 1-bit engine 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_C1BE                                       0x00000010U
#define LRFDMDM_DEMINIT1_C1BE_M                                     0x00000010U
#define LRFDMDM_DEMINIT1_C1BE_S                                              4U
#define LRFDMDM_DEMINIT1_C1BE_RESET                                 0x00000010U
#define LRFDMDM_DEMINIT1_C1BE_NO_EFFECT                             0x00000000U

// Field:     [3] LQIE 
//
// Synch reset LQI engine 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_LQIE                                       0x00000008U
#define LRFDMDM_DEMINIT1_LQIE_M                                     0x00000008U
#define LRFDMDM_DEMINIT1_LQIE_S                                              3U
#define LRFDMDM_DEMINIT1_LQIE_RESET                                 0x00000008U
#define LRFDMDM_DEMINIT1_LQIE_NO_EFFECT                             0x00000000U

// Field:     [2] F4BA 
//
// Synch reset clock-domain crossing fifo 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_F4BA                                       0x00000004U
#define LRFDMDM_DEMINIT1_F4BA_M                                     0x00000004U
#define LRFDMDM_DEMINIT1_F4BA_S                                              2U
#define LRFDMDM_DEMINIT1_F4BA_RESET                                 0x00000004U
#define LRFDMDM_DEMINIT1_F4BA_NO_EFFECT                             0x00000000U

// Field:     [1] STIM 
//
// Synch reset symbol timing tracker 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_STIM                                       0x00000002U
#define LRFDMDM_DEMINIT1_STIM_M                                     0x00000002U
#define LRFDMDM_DEMINIT1_STIM_S                                              1U
#define LRFDMDM_DEMINIT1_STIM_RESET                                 0x00000002U
#define LRFDMDM_DEMINIT1_STIM_NO_EFFECT                             0x00000000U

// Field:     [0] DSBU 
//
// Synch reset dynamic sample buffer 
// ENUMs: 
// RESET                    Reset module 
// NO_EFFECT                No effect 
#define LRFDMDM_DEMINIT1_DSBU                                       0x00000001U
#define LRFDMDM_DEMINIT1_DSBU_M                                     0x00000001U
#define LRFDMDM_DEMINIT1_DSBU_S                                              0U
#define LRFDMDM_DEMINIT1_DSBU_RESET                                 0x00000001U
#define LRFDMDM_DEMINIT1_DSBU_NO_EFFECT                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_STRB0
//
//*****************************************************************************
// Field:    [11] TIMBADVANCE 
//
// Advance the timebase one 4baud sample, so the current symbol will have three 
// 4baud samples. 
// ENUMs: 
// ON                       The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDMDM_STRB0_TIMBADVANCE                                   0x00000800U
#define LRFDMDM_STRB0_TIMBADVANCE_M                                 0x00000800U
#define LRFDMDM_STRB0_TIMBADVANCE_S                                         11U
#define LRFDMDM_STRB0_TIMBADVANCE_ON                                0x00000800U
#define LRFDMDM_STRB0_TIMBADVANCE_NO_EFFECT                         0x00000000U

// Field:    [10] TIMBSTALL 
//
// Stall the timebase one 4baud sample, so the current symbol will have five 
// 4baud samples. 
// ENUMs: 
// ON                       The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDMDM_STRB0_TIMBSTALL                                     0x00000400U
#define LRFDMDM_STRB0_TIMBSTALL_M                                   0x00000400U
#define LRFDMDM_STRB0_TIMBSTALL_S                                           10U
#define LRFDMDM_STRB0_TIMBSTALL_ON                                  0x00000400U
#define LRFDMDM_STRB0_TIMBSTALL_NO_EFFECT                           0x00000000U

// Field:     [9] EVT5 
//
// Firmware defined 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT5                                          0x00000200U
#define LRFDMDM_STRB0_EVT5_M                                        0x00000200U
#define LRFDMDM_STRB0_EVT5_S                                                 9U
#define LRFDMDM_STRB0_EVT5_ONE                                      0x00000200U
#define LRFDMDM_STRB0_EVT5_ZERO                                     0x00000000U

// Field:     [8] EVT4 
//
// Firmware defined 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT4                                          0x00000100U
#define LRFDMDM_STRB0_EVT4_M                                        0x00000100U
#define LRFDMDM_STRB0_EVT4_S                                                 8U
#define LRFDMDM_STRB0_EVT4_ONE                                      0x00000100U
#define LRFDMDM_STRB0_EVT4_ZERO                                     0x00000000U

// Field:     [7] MLSETERM 
//
// Terminate MLSE unit 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_STRB0_MLSETERM                                      0x00000080U
#define LRFDMDM_STRB0_MLSETERM_M                                    0x00000080U
#define LRFDMDM_STRB0_MLSETERM_S                                             7U
#define LRFDMDM_STRB0_MLSETERM_ON                                   0x00000080U
#define LRFDMDM_STRB0_MLSETERM_OFF                                  0x00000000U

// Field:     [6] EVT3 
//
// Firmware defined 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT3                                          0x00000040U
#define LRFDMDM_STRB0_EVT3_M                                        0x00000040U
#define LRFDMDM_STRB0_EVT3_S                                                 6U
#define LRFDMDM_STRB0_EVT3_ONE                                      0x00000040U
#define LRFDMDM_STRB0_EVT3_ZERO                                     0x00000000U

// Field:     [5] EVT2 
//
// Firmware defined SYSTIMER event 2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT2                                          0x00000020U
#define LRFDMDM_STRB0_EVT2_M                                        0x00000020U
#define LRFDMDM_STRB0_EVT2_S                                                 5U
#define LRFDMDM_STRB0_EVT2_ONE                                      0x00000020U
#define LRFDMDM_STRB0_EVT2_ZERO                                     0x00000000U

// Field:     [4] EVT1 
//
// Firmware defined SYSTIMER event 1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT1                                          0x00000010U
#define LRFDMDM_STRB0_EVT1_M                                        0x00000010U
#define LRFDMDM_STRB0_EVT1_S                                                 4U
#define LRFDMDM_STRB0_EVT1_ONE                                      0x00000010U
#define LRFDMDM_STRB0_EVT1_ZERO                                     0x00000000U

// Field:     [3] EVT0 
//
// Firmware defined SYSTIMER event 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB0_EVT0                                          0x00000008U
#define LRFDMDM_STRB0_EVT0_M                                        0x00000008U
#define LRFDMDM_STRB0_EVT0_S                                                 3U
#define LRFDMDM_STRB0_EVT0_ONE                                      0x00000008U
#define LRFDMDM_STRB0_EVT0_ZERO                                     0x00000000U

// Field:     [2] TIMBALIGN 
//
// Align the 1baud to the next 4baud event 
// ENUMs: 
// ON                       The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDMDM_STRB0_TIMBALIGN                                     0x00000004U
#define LRFDMDM_STRB0_TIMBALIGN_M                                   0x00000004U
#define LRFDMDM_STRB0_TIMBALIGN_S                                            2U
#define LRFDMDM_STRB0_TIMBALIGN_ON                                  0x00000004U
#define LRFDMDM_STRB0_TIMBALIGN_NO_EFFECT                           0x00000000U

// Field:     [1] DSBURST 
//
// Restart DSBU 
// ENUMs: 
// RESTART                  Restart module 
// NO_EFFECT                No effect 
#define LRFDMDM_STRB0_DSBURST                                       0x00000002U
#define LRFDMDM_STRB0_DSBURST_M                                     0x00000002U
#define LRFDMDM_STRB0_DSBURST_S                                              1U
#define LRFDMDM_STRB0_DSBURST_RESTART                               0x00000002U
#define LRFDMDM_STRB0_DSBURST_NO_EFFECT                             0x00000000U

// Field:     [0] CMDDONE 
//
// Signal command done to CPE 
// ENUMs: 
// YES                      The bit is 1 
// NO                       The bit is 0 
#define LRFDMDM_STRB0_CMDDONE                                       0x00000001U
#define LRFDMDM_STRB0_CMDDONE_M                                     0x00000001U
#define LRFDMDM_STRB0_CMDDONE_S                                              0U
#define LRFDMDM_STRB0_CMDDONE_YES                                   0x00000001U
#define LRFDMDM_STRB0_CMDDONE_NO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_STRB1
//
//*****************************************************************************
// Field:    [13] S2RTRG 
//
// Arm/Trigger the S2R module 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_S2RTRG                                        0x00002000U
#define LRFDMDM_STRB1_S2RTRG_M                                      0x00002000U
#define LRFDMDM_STRB1_S2RTRG_S                                              13U
#define LRFDMDM_STRB1_S2RTRG_ONE                                    0x00002000U
#define LRFDMDM_STRB1_S2RTRG_ZERO                                   0x00000000U

// Field:    [12] DMATRG 
//
// FW triggered DMA transfer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_DMATRG                                        0x00001000U
#define LRFDMDM_STRB1_DMATRG_M                                      0x00001000U
#define LRFDMDM_STRB1_DMATRG_S                                              12U
#define LRFDMDM_STRB1_DMATRG_ONE                                    0x00001000U
#define LRFDMDM_STRB1_DMATRG_ZERO                                   0x00000000U

// Field:    [11] SYSTCAPT2 
//
// Systimer capture event 2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_SYSTCAPT2                                     0x00000800U
#define LRFDMDM_STRB1_SYSTCAPT2_M                                   0x00000800U
#define LRFDMDM_STRB1_SYSTCAPT2_S                                           11U
#define LRFDMDM_STRB1_SYSTCAPT2_ONE                                 0x00000800U
#define LRFDMDM_STRB1_SYSTCAPT2_ZERO                                0x00000000U

// Field:    [10] SYSTCAPT1 
//
// Systimer capture event 1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_SYSTCAPT1                                     0x00000400U
#define LRFDMDM_STRB1_SYSTCAPT1_M                                   0x00000400U
#define LRFDMDM_STRB1_SYSTCAPT1_S                                           10U
#define LRFDMDM_STRB1_SYSTCAPT1_ONE                                 0x00000400U
#define LRFDMDM_STRB1_SYSTCAPT1_ZERO                                0x00000000U

// Field:     [9] SYSTCAPT0 
//
// Systimer capture event 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_SYSTCAPT0                                     0x00000200U
#define LRFDMDM_STRB1_SYSTCAPT0_M                                   0x00000200U
#define LRFDMDM_STRB1_SYSTCAPT0_S                                            9U
#define LRFDMDM_STRB1_SYSTCAPT0_ONE                                 0x00000200U
#define LRFDMDM_STRB1_SYSTCAPT0_ZERO                                0x00000000U

// Field:     [8] C1BEPEAKAB 
//
// Restart C1BE peak A and B search 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BEPEAKAB                                    0x00000100U
#define LRFDMDM_STRB1_C1BEPEAKAB_M                                  0x00000100U
#define LRFDMDM_STRB1_C1BEPEAKAB_S                                           8U
#define LRFDMDM_STRB1_C1BEPEAKAB_ONE                                0x00000100U
#define LRFDMDM_STRB1_C1BEPEAKAB_ZERO                               0x00000000U

// Field:     [7] C1BEPEAKC 
//
// Restart C1BE peak C search (corr C is corr A+B combined = 64 symbols = 256 
// samples) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BEPEAKC                                     0x00000080U
#define LRFDMDM_STRB1_C1BEPEAKC_M                                   0x00000080U
#define LRFDMDM_STRB1_C1BEPEAKC_S                                            7U
#define LRFDMDM_STRB1_C1BEPEAKC_ONE                                 0x00000080U
#define LRFDMDM_STRB1_C1BEPEAKC_ZERO                                0x00000000U

// Field:     [6] C1BEPEAKB 
//
// Restart C1BE peak B search (32 symbols = 128 samples) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BEPEAKB                                     0x00000040U
#define LRFDMDM_STRB1_C1BEPEAKB_M                                   0x00000040U
#define LRFDMDM_STRB1_C1BEPEAKB_S                                            6U
#define LRFDMDM_STRB1_C1BEPEAKB_ONE                                 0x00000040U
#define LRFDMDM_STRB1_C1BEPEAKB_ZERO                                0x00000000U

// Field:     [5] C1BEPEAKA 
//
// Restart C1BE peak A search (32 symbols = 128 samples) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BEPEAKA                                     0x00000020U
#define LRFDMDM_STRB1_C1BEPEAKA_M                                   0x00000020U
#define LRFDMDM_STRB1_C1BEPEAKA_S                                            5U
#define LRFDMDM_STRB1_C1BEPEAKA_ONE                                 0x00000020U
#define LRFDMDM_STRB1_C1BEPEAKA_ZERO                                0x00000000U

// Field:     [4] C1BEADVANCE 
//
// Speed up correlator autocopy with one sample 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BEADVANCE                                   0x00000010U
#define LRFDMDM_STRB1_C1BEADVANCE_M                                 0x00000010U
#define LRFDMDM_STRB1_C1BEADVANCE_S                                          4U
#define LRFDMDM_STRB1_C1BEADVANCE_ONE                               0x00000010U
#define LRFDMDM_STRB1_C1BEADVANCE_ZERO                              0x00000000U

// Field:     [3] C1BESTALL 
//
// Slow down correlator autocopy with one sample 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BESTALL                                     0x00000008U
#define LRFDMDM_STRB1_C1BESTALL_M                                   0x00000008U
#define LRFDMDM_STRB1_C1BESTALL_S                                            3U
#define LRFDMDM_STRB1_C1BESTALL_ONE                                 0x00000008U
#define LRFDMDM_STRB1_C1BESTALL_ZERO                                0x00000000U

// Field:   [2:1] C1BEROT 
//
// Correlator rotate command to shift reg B 
// ENUMs: 
// ROT16R                   Rotate 16 samples to the right 
// ROT1L                    Rotate 1 sample to the left 
// ROT1R                    Rotate 1 sample to the right 
// ROT0                     No additional rotation (normal shift-right mode) 
#define LRFDMDM_STRB1_C1BEROT_W                                              2U
#define LRFDMDM_STRB1_C1BEROT_M                                     0x00000006U
#define LRFDMDM_STRB1_C1BEROT_S                                              1U
#define LRFDMDM_STRB1_C1BEROT_ROT16R                                0x00000006U
#define LRFDMDM_STRB1_C1BEROT_ROT1L                                 0x00000004U
#define LRFDMDM_STRB1_C1BEROT_ROT1R                                 0x00000002U
#define LRFDMDM_STRB1_C1BEROT_ROT0                                  0x00000000U

// Field:     [0] C1BECOPY 
//
// Copy contents of shift reg A into shift reg B 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_STRB1_C1BECOPY                                      0x00000001U
#define LRFDMDM_STRB1_C1BECOPY_M                                    0x00000001U
#define LRFDMDM_STRB1_C1BECOPY_S                                             0U
#define LRFDMDM_STRB1_C1BECOPY_ONE                                  0x00000001U
#define LRFDMDM_STRB1_C1BECOPY_ZERO                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVT0
//
//*****************************************************************************
// Field:    [15] PBEDAT 
//
// New data from PBE received in PBEDATIN0 register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_PBEDAT                                         0x00008000U
#define LRFDMDM_EVT0_PBEDAT_M                                       0x00008000U
#define LRFDMDM_EVT0_PBEDAT_S                                               15U
#define LRFDMDM_EVT0_PBEDAT_ONE                                     0x00008000U
#define LRFDMDM_EVT0_PBEDAT_ZERO                                    0x00000000U

// Field:    [14] PBECMD 
//
// New command from PBE received in PBECMDIN register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_PBECMD                                         0x00004000U
#define LRFDMDM_EVT0_PBECMD_M                                       0x00004000U
#define LRFDMDM_EVT0_PBECMD_S                                               14U
#define LRFDMDM_EVT0_PBECMD_ONE                                     0x00004000U
#define LRFDMDM_EVT0_PBECMD_ZERO                                    0x00000000U

// Field:    [13] RFEDAT 
//
// New data from RFE received in RFEDATIN0 register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_RFEDAT                                         0x00002000U
#define LRFDMDM_EVT0_RFEDAT_M                                       0x00002000U
#define LRFDMDM_EVT0_RFEDAT_S                                               13U
#define LRFDMDM_EVT0_RFEDAT_ONE                                     0x00002000U
#define LRFDMDM_EVT0_RFEDAT_ZERO                                    0x00000000U

// Field:    [12] BDEC 
//
// BDEC output enable event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_BDEC                                           0x00001000U
#define LRFDMDM_EVT0_BDEC_M                                         0x00001000U
#define LRFDMDM_EVT0_BDEC_S                                                 12U
#define LRFDMDM_EVT0_BDEC_ONE                                       0x00001000U
#define LRFDMDM_EVT0_BDEC_ZERO                                      0x00000000U

// Field:    [11] FRAC 
//
// FRAC output enable event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_FRAC                                           0x00000800U
#define LRFDMDM_EVT0_FRAC_M                                         0x00000800U
#define LRFDMDM_EVT0_FRAC_S                                                 11U
#define LRFDMDM_EVT0_FRAC_ONE                                       0x00000800U
#define LRFDMDM_EVT0_FRAC_ZERO                                      0x00000000U

// Field:    [10] SYSTIMEVT2 
//
// Event 2 from SYSTIMER 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_SYSTIMEVT2                                     0x00000400U
#define LRFDMDM_EVT0_SYSTIMEVT2_M                                   0x00000400U
#define LRFDMDM_EVT0_SYSTIMEVT2_S                                           10U
#define LRFDMDM_EVT0_SYSTIMEVT2_ONE                                 0x00000400U
#define LRFDMDM_EVT0_SYSTIMEVT2_ZERO                                0x00000000U

// Field:     [9] SYSTIMEVT1 
//
// Event 1 from SYSTIMER 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_SYSTIMEVT1                                     0x00000200U
#define LRFDMDM_EVT0_SYSTIMEVT1_M                                   0x00000200U
#define LRFDMDM_EVT0_SYSTIMEVT1_S                                            9U
#define LRFDMDM_EVT0_SYSTIMEVT1_ONE                                 0x00000200U
#define LRFDMDM_EVT0_SYSTIMEVT1_ZERO                                0x00000000U

// Field:     [8] SYSTIMEVT0 
//
// Event 0 from SYSTIMER 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_SYSTIMEVT0                                     0x00000100U
#define LRFDMDM_EVT0_SYSTIMEVT0_M                                   0x00000100U
#define LRFDMDM_EVT0_SYSTIMEVT0_S                                            8U
#define LRFDMDM_EVT0_SYSTIMEVT0_ONE                                 0x00000100U
#define LRFDMDM_EVT0_SYSTIMEVT0_ZERO                                0x00000000U

// Field:     [7] FIFOWR 
//
// A write to the modem FIFO (via FIFOWR register), probably by CPE. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_FIFOWR                                         0x00000080U
#define LRFDMDM_EVT0_FIFOWR_M                                       0x00000080U
#define LRFDMDM_EVT0_FIFOWR_S                                                7U
#define LRFDMDM_EVT0_FIFOWR_ONE                                     0x00000080U
#define LRFDMDM_EVT0_FIFOWR_ZERO                                    0x00000000U

// Field:     [6] COUNTER 
//
// Counter value reached in local timer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_COUNTER                                        0x00000040U
#define LRFDMDM_EVT0_COUNTER_M                                      0x00000040U
#define LRFDMDM_EVT0_COUNTER_S                                               6U
#define LRFDMDM_EVT0_COUNTER_ONE                                    0x00000040U
#define LRFDMDM_EVT0_COUNTER_ZERO                                   0x00000000U

// Field:     [5] RFECMD 
//
// New command from RFE received in RFECMDIN register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_RFECMD                                         0x00000020U
#define LRFDMDM_EVT0_RFECMD_M                                       0x00000020U
#define LRFDMDM_EVT0_RFECMD_S                                                5U
#define LRFDMDM_EVT0_RFECMD_ONE                                     0x00000020U
#define LRFDMDM_EVT0_RFECMD_ZERO                                    0x00000000U

// Field:     [4] FIFOOVFL 
//
// Modem FIFO overflow error event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_FIFOOVFL                                       0x00000010U
#define LRFDMDM_EVT0_FIFOOVFL_M                                     0x00000010U
#define LRFDMDM_EVT0_FIFOOVFL_S                                              4U
#define LRFDMDM_EVT0_FIFOOVFL_ONE                                   0x00000010U
#define LRFDMDM_EVT0_FIFOOVFL_ZERO                                  0x00000000U

// Field:     [3] FIFOUNFL 
//
// Modem FIFO underflow error event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_FIFOUNFL                                       0x00000008U
#define LRFDMDM_EVT0_FIFOUNFL_M                                     0x00000008U
#define LRFDMDM_EVT0_FIFOUNFL_S                                              3U
#define LRFDMDM_EVT0_FIFOUNFL_ONE                                   0x00000008U
#define LRFDMDM_EVT0_FIFOUNFL_ZERO                                  0x00000000U

// Field:     [2] CLKEN4BAUD 
//
// Clock enable event at 4 times baud rate 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_CLKEN4BAUD                                     0x00000004U
#define LRFDMDM_EVT0_CLKEN4BAUD_M                                   0x00000004U
#define LRFDMDM_EVT0_CLKEN4BAUD_S                                            2U
#define LRFDMDM_EVT0_CLKEN4BAUD_ONE                                 0x00000004U
#define LRFDMDM_EVT0_CLKEN4BAUD_ZERO                                0x00000000U

// Field:     [1] TIMER 
//
// Timer period expired in local timer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_TIMER                                          0x00000002U
#define LRFDMDM_EVT0_TIMER_M                                        0x00000002U
#define LRFDMDM_EVT0_TIMER_S                                                 1U
#define LRFDMDM_EVT0_TIMER_ONE                                      0x00000002U
#define LRFDMDM_EVT0_TIMER_ZERO                                     0x00000000U

// Field:     [0] MDMAPI 
//
// New command from PBE has been written in API register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT0_MDMAPI                                         0x00000001U
#define LRFDMDM_EVT0_MDMAPI_M                                       0x00000001U
#define LRFDMDM_EVT0_MDMAPI_S                                                0U
#define LRFDMDM_EVT0_MDMAPI_ONE                                     0x00000001U
#define LRFDMDM_EVT0_MDMAPI_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVT1
//
//*****************************************************************************
// Field:     [8] REFCLK 
//
// PLL REFCLK tick 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_REFCLK                                         0x00000100U
#define LRFDMDM_EVT1_REFCLK_M                                       0x00000100U
#define LRFDMDM_EVT1_REFCLK_S                                                8U
#define LRFDMDM_EVT1_REFCLK_ONE                                     0x00000100U
#define LRFDMDM_EVT1_REFCLK_ZERO                                    0x00000000U

// Field:     [7] S2RSTOP 
//
// S2R module has written to the STOP_ADDRESS register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_S2RSTOP                                        0x00000080U
#define LRFDMDM_EVT1_S2RSTOP_M                                      0x00000080U
#define LRFDMDM_EVT1_S2RSTOP_S                                               7U
#define LRFDMDM_EVT1_S2RSTOP_ONE                                    0x00000080U
#define LRFDMDM_EVT1_S2RSTOP_ZERO                                   0x00000000U

// Field:     [6] SWQUFALSESYNC 
//
// Sync word qualifier rejected sync due to bit errors (happens if a correlator 
// event was incorrect due to noise). 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_SWQUFALSESYNC                                  0x00000040U
#define LRFDMDM_EVT1_SWQUFALSESYNC_M                                0x00000040U
#define LRFDMDM_EVT1_SWQUFALSESYNC_S                                         6U
#define LRFDMDM_EVT1_SWQUFALSESYNC_ONE                              0x00000040U
#define LRFDMDM_EVT1_SWQUFALSESYNC_ZERO                             0x00000000U

// Field:     [5] SWQUSYNCED 
//
// Sync word qualifier detected sync word 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_SWQUSYNCED                                     0x00000020U
#define LRFDMDM_EVT1_SWQUSYNCED_M                                   0x00000020U
#define LRFDMDM_EVT1_SWQUSYNCED_S                                            5U
#define LRFDMDM_EVT1_SWQUSYNCED_ONE                                 0x00000020U
#define LRFDMDM_EVT1_SWQUSYNCED_ZERO                                0x00000000U

// Field:     [4] CLKENBAUDF 
//
// Clock enable event at flushed baud rate 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_CLKENBAUDF                                     0x00000010U
#define LRFDMDM_EVT1_CLKENBAUDF_M                                   0x00000010U
#define LRFDMDM_EVT1_CLKENBAUDF_S                                            4U
#define LRFDMDM_EVT1_CLKENBAUDF_ONE                                 0x00000010U
#define LRFDMDM_EVT1_CLKENBAUDF_ZERO                                0x00000000U

// Field:     [3] FIFORVALID 
//
// Modem FIFO has valid data so a new word can be read from it, via FIFORD. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_FIFORVALID                                     0x00000008U
#define LRFDMDM_EVT1_FIFORVALID_M                                   0x00000008U
#define LRFDMDM_EVT1_FIFORVALID_S                                            3U
#define LRFDMDM_EVT1_FIFORVALID_ONE                                 0x00000008U
#define LRFDMDM_EVT1_FIFORVALID_ZERO                                0x00000000U

// Field:     [2] FIFOWREADY 
//
// Modem FIFO is ready for more data so a new word can be written to it, via 
// FIFOWR register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_FIFOWREADY                                     0x00000004U
#define LRFDMDM_EVT1_FIFOWREADY_M                                   0x00000004U
#define LRFDMDM_EVT1_FIFOWREADY_S                                            2U
#define LRFDMDM_EVT1_FIFOWREADY_ONE                                 0x00000004U
#define LRFDMDM_EVT1_FIFOWREADY_ZERO                                0x00000000U

// Field:     [1] CLKENBAUD 
//
// Clock enable event at baud rate 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_CLKENBAUD                                      0x00000002U
#define LRFDMDM_EVT1_CLKENBAUD_M                                    0x00000002U
#define LRFDMDM_EVT1_CLKENBAUD_S                                             1U
#define LRFDMDM_EVT1_CLKENBAUD_ONE                                  0x00000002U
#define LRFDMDM_EVT1_CLKENBAUD_ZERO                                 0x00000000U

// Field:     [0] PREAMBLEDONE 
//
// Preamble done interrupt from modulator 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT1_PREAMBLEDONE                                   0x00000001U
#define LRFDMDM_EVT1_PREAMBLEDONE_M                                 0x00000001U
#define LRFDMDM_EVT1_PREAMBLEDONE_S                                          0U
#define LRFDMDM_EVT1_PREAMBLEDONE_ONE                               0x00000001U
#define LRFDMDM_EVT1_PREAMBLEDONE_ZERO                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVT2
//
//*****************************************************************************
// Field:    [15] GPI1 
//
// External input event line GPI1 from IOC 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_GPI1                                           0x00008000U
#define LRFDMDM_EVT2_GPI1_M                                         0x00008000U
#define LRFDMDM_EVT2_GPI1_S                                                 15U
#define LRFDMDM_EVT2_GPI1_ONE                                       0x00008000U
#define LRFDMDM_EVT2_GPI1_ZERO                                      0x00000000U

// Field:    [14] GPI0 
//
// External input event line GPI0 from IOC. (Also, when loopback mode is 
// enabled in DEMDEBUG.LOOPBACKMODE, this input line represents the symbols fed 
// to the demodulator's decode stage). 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_GPI0                                           0x00004000U
#define LRFDMDM_EVT2_GPI0_M                                         0x00004000U
#define LRFDMDM_EVT2_GPI0_S                                                 14U
#define LRFDMDM_EVT2_GPI0_ONE                                       0x00004000U
#define LRFDMDM_EVT2_GPI0_ZERO                                      0x00000000U

// Field:    [12] C1BEBLOADED 
//
// C1BE correlator B loaded (by auto-copy function) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEBLOADED                                    0x00001000U
#define LRFDMDM_EVT2_C1BEBLOADED_M                                  0x00001000U
#define LRFDMDM_EVT2_C1BEBLOADED_S                                          12U
#define LRFDMDM_EVT2_C1BEBLOADED_ONE                                0x00001000U
#define LRFDMDM_EVT2_C1BEBLOADED_ZERO                               0x00000000U

// Field:    [11] C1BECMBANY 
//
// C1BE correlator AB combined, any peak detect: (abs(corr A) > thr A) and 
// (abs(corr B) > thr B). Event occurs one sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECMBANY                                     0x00000800U
#define LRFDMDM_EVT2_C1BECMBANY_M                                   0x00000800U
#define LRFDMDM_EVT2_C1BECMBANY_S                                           11U
#define LRFDMDM_EVT2_C1BECMBANY_ONE                                 0x00000800U
#define LRFDMDM_EVT2_C1BECMBANY_ZERO                                0x00000000U

// Field:    [10] C1BECMBNEG 
//
// C1BE correlator AB combined, negative peak detect: (corr A < -thr A) and 
// (corr B < -thr B). Event occurs one sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECMBNEG                                     0x00000400U
#define LRFDMDM_EVT2_C1BECMBNEG_M                                   0x00000400U
#define LRFDMDM_EVT2_C1BECMBNEG_S                                           10U
#define LRFDMDM_EVT2_C1BECMBNEG_ONE                                 0x00000400U
#define LRFDMDM_EVT2_C1BECMBNEG_ZERO                                0x00000000U

// Field:     [9] C1BECMBPOS 
//
// C1BE correlator AB combined, positive peak detect: (corr A > thr A) and 
// (corr B > thr B). Event occurs one sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECMBPOS                                     0x00000200U
#define LRFDMDM_EVT2_C1BECMBPOS_M                                   0x00000200U
#define LRFDMDM_EVT2_C1BECMBPOS_S                                            9U
#define LRFDMDM_EVT2_C1BECMBPOS_ONE                                 0x00000200U
#define LRFDMDM_EVT2_C1BECMBPOS_ZERO                                0x00000000U

// Field:     [8] C1BECANY 
//
// C1BE correlator C, any peak detect: abs(corr C) > thr C. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECANY                                       0x00000100U
#define LRFDMDM_EVT2_C1BECANY_M                                     0x00000100U
#define LRFDMDM_EVT2_C1BECANY_S                                              8U
#define LRFDMDM_EVT2_C1BECANY_ONE                                   0x00000100U
#define LRFDMDM_EVT2_C1BECANY_ZERO                                  0x00000000U

// Field:     [7] C1BECNEG 
//
// C1BE correlator C, negative peak detect: corr C < -thr C. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECNEG                                       0x00000080U
#define LRFDMDM_EVT2_C1BECNEG_M                                     0x00000080U
#define LRFDMDM_EVT2_C1BECNEG_S                                              7U
#define LRFDMDM_EVT2_C1BECNEG_ONE                                   0x00000080U
#define LRFDMDM_EVT2_C1BECNEG_ZERO                                  0x00000000U

// Field:     [6] C1BECPOS 
//
// C1BE correlator C, positive peak detect: corr C > thr C. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BECPOS                                       0x00000040U
#define LRFDMDM_EVT2_C1BECPOS_M                                     0x00000040U
#define LRFDMDM_EVT2_C1BECPOS_S                                              6U
#define LRFDMDM_EVT2_C1BECPOS_ONE                                   0x00000040U
#define LRFDMDM_EVT2_C1BECPOS_ZERO                                  0x00000000U

// Field:     [5] C1BEBANY 
//
// C1BE correlator B, any peak detect: abs(corr B) > thr B. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEBANY                                       0x00000020U
#define LRFDMDM_EVT2_C1BEBANY_M                                     0x00000020U
#define LRFDMDM_EVT2_C1BEBANY_S                                              5U
#define LRFDMDM_EVT2_C1BEBANY_ONE                                   0x00000020U
#define LRFDMDM_EVT2_C1BEBANY_ZERO                                  0x00000000U

// Field:     [4] C1BEBNEG 
//
// C1BE correlator B, negative peak detect: corr B < -threshold B. Event occurs 
// one sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEBNEG                                       0x00000010U
#define LRFDMDM_EVT2_C1BEBNEG_M                                     0x00000010U
#define LRFDMDM_EVT2_C1BEBNEG_S                                              4U
#define LRFDMDM_EVT2_C1BEBNEG_ONE                                   0x00000010U
#define LRFDMDM_EVT2_C1BEBNEG_ZERO                                  0x00000000U

// Field:     [3] C1BEBPOS 
//
// C1BE correlator B, positive peak detect: corr B > threshold B. Event occurs 
// one sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEBPOS                                       0x00000008U
#define LRFDMDM_EVT2_C1BEBPOS_M                                     0x00000008U
#define LRFDMDM_EVT2_C1BEBPOS_S                                              3U
#define LRFDMDM_EVT2_C1BEBPOS_ONE                                   0x00000008U
#define LRFDMDM_EVT2_C1BEBPOS_ZERO                                  0x00000000U

// Field:     [2] C1BEAANY 
//
// C1BE correlator A, any peak detect: abs(corr A) > thr A. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEAANY                                       0x00000004U
#define LRFDMDM_EVT2_C1BEAANY_M                                     0x00000004U
#define LRFDMDM_EVT2_C1BEAANY_S                                              2U
#define LRFDMDM_EVT2_C1BEAANY_ONE                                   0x00000004U
#define LRFDMDM_EVT2_C1BEAANY_ZERO                                  0x00000000U

// Field:     [1] C1BEANEG 
//
// C1BE correlator A, negative peak detect: corr A < -thr A. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEANEG                                       0x00000002U
#define LRFDMDM_EVT2_C1BEANEG_M                                     0x00000002U
#define LRFDMDM_EVT2_C1BEANEG_S                                              1U
#define LRFDMDM_EVT2_C1BEANEG_ONE                                   0x00000002U
#define LRFDMDM_EVT2_C1BEANEG_ZERO                                  0x00000000U

// Field:     [0] C1BEAPOS 
//
// C1BE correlator A, positive peak detect: corr A > thr A. Event occurs one 
// sample after actual peak. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_EVT2_C1BEAPOS                                       0x00000001U
#define LRFDMDM_EVT2_C1BEAPOS_M                                     0x00000001U
#define LRFDMDM_EVT2_C1BEAPOS_S                                              0U
#define LRFDMDM_EVT2_C1BEAPOS_ONE                                   0x00000001U
#define LRFDMDM_EVT2_C1BEAPOS_ZERO                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTMSK0
//
//*****************************************************************************
// Field:    [15] PBEDAT 
//
// Enable mask for event EVT0.PBEDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_PBEDAT                                      0x00008000U
#define LRFDMDM_EVTMSK0_PBEDAT_M                                    0x00008000U
#define LRFDMDM_EVTMSK0_PBEDAT_S                                            15U
#define LRFDMDM_EVTMSK0_PBEDAT_EN                                   0x00008000U
#define LRFDMDM_EVTMSK0_PBEDAT_DIS                                  0x00000000U

// Field:    [14] PBECMD 
//
// Enable mask for event EVT0.PBECMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_PBECMD                                      0x00004000U
#define LRFDMDM_EVTMSK0_PBECMD_M                                    0x00004000U
#define LRFDMDM_EVTMSK0_PBECMD_S                                            14U
#define LRFDMDM_EVTMSK0_PBECMD_EN                                   0x00004000U
#define LRFDMDM_EVTMSK0_PBECMD_DIS                                  0x00000000U

// Field:    [13] RFEDAT 
//
// Enable mask for event EVT0.RFEDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_RFEDAT                                      0x00002000U
#define LRFDMDM_EVTMSK0_RFEDAT_M                                    0x00002000U
#define LRFDMDM_EVTMSK0_RFEDAT_S                                            13U
#define LRFDMDM_EVTMSK0_RFEDAT_EN                                   0x00002000U
#define LRFDMDM_EVTMSK0_RFEDAT_DIS                                  0x00000000U

// Field:    [12] BDEC 
//
// Enable mask for event EVT0.BDEC 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_BDEC                                        0x00001000U
#define LRFDMDM_EVTMSK0_BDEC_M                                      0x00001000U
#define LRFDMDM_EVTMSK0_BDEC_S                                              12U
#define LRFDMDM_EVTMSK0_BDEC_EN                                     0x00001000U
#define LRFDMDM_EVTMSK0_BDEC_DIS                                    0x00000000U

// Field:    [11] FRAC 
//
// Enable mask for event EVT0.FRAC 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_FRAC                                        0x00000800U
#define LRFDMDM_EVTMSK0_FRAC_M                                      0x00000800U
#define LRFDMDM_EVTMSK0_FRAC_S                                              11U
#define LRFDMDM_EVTMSK0_FRAC_EN                                     0x00000800U
#define LRFDMDM_EVTMSK0_FRAC_DIS                                    0x00000000U

// Field:    [10] SYSTIMEVT2 
//
// Enable mask for event EVT0.SYSTIMEVT2 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_SYSTIMEVT2                                  0x00000400U
#define LRFDMDM_EVTMSK0_SYSTIMEVT2_M                                0x00000400U
#define LRFDMDM_EVTMSK0_SYSTIMEVT2_S                                        10U
#define LRFDMDM_EVTMSK0_SYSTIMEVT2_EN                               0x00000400U
#define LRFDMDM_EVTMSK0_SYSTIMEVT2_DIS                              0x00000000U

// Field:     [9] SYSTIMEVT1 
//
// Enable mask for event EVT0.SYSTIMEVT1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_SYSTIMEVT1                                  0x00000200U
#define LRFDMDM_EVTMSK0_SYSTIMEVT1_M                                0x00000200U
#define LRFDMDM_EVTMSK0_SYSTIMEVT1_S                                         9U
#define LRFDMDM_EVTMSK0_SYSTIMEVT1_EN                               0x00000200U
#define LRFDMDM_EVTMSK0_SYSTIMEVT1_DIS                              0x00000000U

// Field:     [8] SYSTIMEVT0 
//
// Enable mask for event EVT0.SYSTIMEVT0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_SYSTIMEVT0                                  0x00000100U
#define LRFDMDM_EVTMSK0_SYSTIMEVT0_M                                0x00000100U
#define LRFDMDM_EVTMSK0_SYSTIMEVT0_S                                         8U
#define LRFDMDM_EVTMSK0_SYSTIMEVT0_EN                               0x00000100U
#define LRFDMDM_EVTMSK0_SYSTIMEVT0_DIS                              0x00000000U

// Field:     [7] FIFOWR 
//
// Enable mask for event EVT0.FIFOWR 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_FIFOWR                                      0x00000080U
#define LRFDMDM_EVTMSK0_FIFOWR_M                                    0x00000080U
#define LRFDMDM_EVTMSK0_FIFOWR_S                                             7U
#define LRFDMDM_EVTMSK0_FIFOWR_EN                                   0x00000080U
#define LRFDMDM_EVTMSK0_FIFOWR_DIS                                  0x00000000U

// Field:     [6] COUNTER 
//
// Enable mask for event EVT0.COUNTER 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_COUNTER                                     0x00000040U
#define LRFDMDM_EVTMSK0_COUNTER_M                                   0x00000040U
#define LRFDMDM_EVTMSK0_COUNTER_S                                            6U
#define LRFDMDM_EVTMSK0_COUNTER_EN                                  0x00000040U
#define LRFDMDM_EVTMSK0_COUNTER_DIS                                 0x00000000U

// Field:     [5] RFECMD 
//
// Enable mask for event EVT0.RFECMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_RFECMD                                      0x00000020U
#define LRFDMDM_EVTMSK0_RFECMD_M                                    0x00000020U
#define LRFDMDM_EVTMSK0_RFECMD_S                                             5U
#define LRFDMDM_EVTMSK0_RFECMD_EN                                   0x00000020U
#define LRFDMDM_EVTMSK0_RFECMD_DIS                                  0x00000000U

// Field:     [4] FIFOOVFL 
//
// Enable mask for event EVT0.FIFOOVFL 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_FIFOOVFL                                    0x00000010U
#define LRFDMDM_EVTMSK0_FIFOOVFL_M                                  0x00000010U
#define LRFDMDM_EVTMSK0_FIFOOVFL_S                                           4U
#define LRFDMDM_EVTMSK0_FIFOOVFL_EN                                 0x00000010U
#define LRFDMDM_EVTMSK0_FIFOOVFL_DIS                                0x00000000U

// Field:     [3] FIFOUNFL 
//
// Enable mask for event EVT0.FIFOUNFL 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_FIFOUNFL                                    0x00000008U
#define LRFDMDM_EVTMSK0_FIFOUNFL_M                                  0x00000008U
#define LRFDMDM_EVTMSK0_FIFOUNFL_S                                           3U
#define LRFDMDM_EVTMSK0_FIFOUNFL_EN                                 0x00000008U
#define LRFDMDM_EVTMSK0_FIFOUNFL_DIS                                0x00000000U

// Field:     [2] CLKEN4BAUD 
//
// Enable mask for event EVT0.CLKEN4BAUD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_CLKEN4BAUD                                  0x00000004U
#define LRFDMDM_EVTMSK0_CLKEN4BAUD_M                                0x00000004U
#define LRFDMDM_EVTMSK0_CLKEN4BAUD_S                                         2U
#define LRFDMDM_EVTMSK0_CLKEN4BAUD_EN                               0x00000004U
#define LRFDMDM_EVTMSK0_CLKEN4BAUD_DIS                              0x00000000U

// Field:     [1] TIMER 
//
// Enable mask for event EVT0.TIMER 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_TIMER                                       0x00000002U
#define LRFDMDM_EVTMSK0_TIMER_M                                     0x00000002U
#define LRFDMDM_EVTMSK0_TIMER_S                                              1U
#define LRFDMDM_EVTMSK0_TIMER_EN                                    0x00000002U
#define LRFDMDM_EVTMSK0_TIMER_DIS                                   0x00000000U

// Field:     [0] MDMAPI 
//
// Enable mask for event EVT0.MDMAPI 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK0_MDMAPI                                      0x00000001U
#define LRFDMDM_EVTMSK0_MDMAPI_M                                    0x00000001U
#define LRFDMDM_EVTMSK0_MDMAPI_S                                             0U
#define LRFDMDM_EVTMSK0_MDMAPI_EN                                   0x00000001U
#define LRFDMDM_EVTMSK0_MDMAPI_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTMSK1
//
//*****************************************************************************
// Field:     [8] REFCLK 
//
// Enable mask for EVT1.REFCLK 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_REFCLK                                      0x00000100U
#define LRFDMDM_EVTMSK1_REFCLK_M                                    0x00000100U
#define LRFDMDM_EVTMSK1_REFCLK_S                                             8U
#define LRFDMDM_EVTMSK1_REFCLK_EN                                   0x00000100U
#define LRFDMDM_EVTMSK1_REFCLK_DIS                                  0x00000000U

// Field:     [7] S2RSTOP 
//
// Enable mask for EVT1.S2RSTOP 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_S2RSTOP                                     0x00000080U
#define LRFDMDM_EVTMSK1_S2RSTOP_M                                   0x00000080U
#define LRFDMDM_EVTMSK1_S2RSTOP_S                                            7U
#define LRFDMDM_EVTMSK1_S2RSTOP_EN                                  0x00000080U
#define LRFDMDM_EVTMSK1_S2RSTOP_DIS                                 0x00000000U

// Field:     [6] SWQUFALSESYNC 
//
// Enable mask for event EVT1.SWQUFALSESYNC 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_SWQUFALSESYNC                               0x00000040U
#define LRFDMDM_EVTMSK1_SWQUFALSESYNC_M                             0x00000040U
#define LRFDMDM_EVTMSK1_SWQUFALSESYNC_S                                      6U
#define LRFDMDM_EVTMSK1_SWQUFALSESYNC_EN                            0x00000040U
#define LRFDMDM_EVTMSK1_SWQUFALSESYNC_DIS                           0x00000000U

// Field:     [5] SWQUSYNCED 
//
// Enable mask for event EVT1.SWQUSYNCED 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_SWQUSYNCED                                  0x00000020U
#define LRFDMDM_EVTMSK1_SWQUSYNCED_M                                0x00000020U
#define LRFDMDM_EVTMSK1_SWQUSYNCED_S                                         5U
#define LRFDMDM_EVTMSK1_SWQUSYNCED_EN                               0x00000020U
#define LRFDMDM_EVTMSK1_SWQUSYNCED_DIS                              0x00000000U

// Field:     [4] CLKENBAUDF 
//
// Enable mask for event EVT1.CLKENBAUDF 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_CLKENBAUDF                                  0x00000010U
#define LRFDMDM_EVTMSK1_CLKENBAUDF_M                                0x00000010U
#define LRFDMDM_EVTMSK1_CLKENBAUDF_S                                         4U
#define LRFDMDM_EVTMSK1_CLKENBAUDF_EN                               0x00000010U
#define LRFDMDM_EVTMSK1_CLKENBAUDF_DIS                              0x00000000U

// Field:     [3] FIFORVALID 
//
// Enable mask for event EVT1.FIFORVALID 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_FIFORVALID                                  0x00000008U
#define LRFDMDM_EVTMSK1_FIFORVALID_M                                0x00000008U
#define LRFDMDM_EVTMSK1_FIFORVALID_S                                         3U
#define LRFDMDM_EVTMSK1_FIFORVALID_EN                               0x00000008U
#define LRFDMDM_EVTMSK1_FIFORVALID_DIS                              0x00000000U

// Field:     [2] FIFOWREADY 
//
// Enable mask for event EVT1.FIFOWREADY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_FIFOWREADY                                  0x00000004U
#define LRFDMDM_EVTMSK1_FIFOWREADY_M                                0x00000004U
#define LRFDMDM_EVTMSK1_FIFOWREADY_S                                         2U
#define LRFDMDM_EVTMSK1_FIFOWREADY_EN                               0x00000004U
#define LRFDMDM_EVTMSK1_FIFOWREADY_DIS                              0x00000000U

// Field:     [1] CLKENBAUD 
//
// Enable mask for event EVT1.CLKENBAUD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_CLKENBAUD                                   0x00000002U
#define LRFDMDM_EVTMSK1_CLKENBAUD_M                                 0x00000002U
#define LRFDMDM_EVTMSK1_CLKENBAUD_S                                          1U
#define LRFDMDM_EVTMSK1_CLKENBAUD_EN                                0x00000002U
#define LRFDMDM_EVTMSK1_CLKENBAUD_DIS                               0x00000000U

// Field:     [0] PREAMBLEDONE 
//
// Enable mask for event EVT1.PREAMBLEDONE 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK1_PREAMBLEDONE                                0x00000001U
#define LRFDMDM_EVTMSK1_PREAMBLEDONE_M                              0x00000001U
#define LRFDMDM_EVTMSK1_PREAMBLEDONE_S                                       0U
#define LRFDMDM_EVTMSK1_PREAMBLEDONE_EN                             0x00000001U
#define LRFDMDM_EVTMSK1_PREAMBLEDONE_DIS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTMSK2
//
//*****************************************************************************
// Field:    [15] GPI1 
//
// Enable mask for event EVT2.GPI1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_GPI1                                        0x00008000U
#define LRFDMDM_EVTMSK2_GPI1_M                                      0x00008000U
#define LRFDMDM_EVTMSK2_GPI1_S                                              15U
#define LRFDMDM_EVTMSK2_GPI1_EN                                     0x00008000U
#define LRFDMDM_EVTMSK2_GPI1_DIS                                    0x00000000U

// Field:    [14] GPI0 
//
// Enable mask for event EVT2.GPI0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_GPI0                                        0x00004000U
#define LRFDMDM_EVTMSK2_GPI0_M                                      0x00004000U
#define LRFDMDM_EVTMSK2_GPI0_S                                              14U
#define LRFDMDM_EVTMSK2_GPI0_EN                                     0x00004000U
#define LRFDMDM_EVTMSK2_GPI0_DIS                                    0x00000000U

// Field:    [12] C1BEBLOADED 
//
// Enable mask for event EVT2.C1BEBLOADED 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEBLOADED                                 0x00001000U
#define LRFDMDM_EVTMSK2_C1BEBLOADED_M                               0x00001000U
#define LRFDMDM_EVTMSK2_C1BEBLOADED_S                                       12U
#define LRFDMDM_EVTMSK2_C1BEBLOADED_EN                              0x00001000U
#define LRFDMDM_EVTMSK2_C1BEBLOADED_DIS                             0x00000000U

// Field:    [11] C1BECMBANY 
//
// Enable mask for event EVT2.C1BECMBANY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECMBANY                                  0x00000800U
#define LRFDMDM_EVTMSK2_C1BECMBANY_M                                0x00000800U
#define LRFDMDM_EVTMSK2_C1BECMBANY_S                                        11U
#define LRFDMDM_EVTMSK2_C1BECMBANY_EN                               0x00000800U
#define LRFDMDM_EVTMSK2_C1BECMBANY_DIS                              0x00000000U

// Field:    [10] C1BECMBNEG 
//
// Enable mask for event EVT2.C1BECMBNEG 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECMBNEG                                  0x00000400U
#define LRFDMDM_EVTMSK2_C1BECMBNEG_M                                0x00000400U
#define LRFDMDM_EVTMSK2_C1BECMBNEG_S                                        10U
#define LRFDMDM_EVTMSK2_C1BECMBNEG_EN                               0x00000400U
#define LRFDMDM_EVTMSK2_C1BECMBNEG_DIS                              0x00000000U

// Field:     [9] C1BECMBPOS 
//
// Enable mask for event EVT2.C1BECMBPOS 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECMBPOS                                  0x00000200U
#define LRFDMDM_EVTMSK2_C1BECMBPOS_M                                0x00000200U
#define LRFDMDM_EVTMSK2_C1BECMBPOS_S                                         9U
#define LRFDMDM_EVTMSK2_C1BECMBPOS_EN                               0x00000200U
#define LRFDMDM_EVTMSK2_C1BECMBPOS_DIS                              0x00000000U

// Field:     [8] C1BECANY 
//
// Enable mask for event EVT2.C1BECANY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECANY                                    0x00000100U
#define LRFDMDM_EVTMSK2_C1BECANY_M                                  0x00000100U
#define LRFDMDM_EVTMSK2_C1BECANY_S                                           8U
#define LRFDMDM_EVTMSK2_C1BECANY_EN                                 0x00000100U
#define LRFDMDM_EVTMSK2_C1BECANY_DIS                                0x00000000U

// Field:     [7] C1BECNEG 
//
// Enable mask for event EVT2.C1BECNEG 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECNEG                                    0x00000080U
#define LRFDMDM_EVTMSK2_C1BECNEG_M                                  0x00000080U
#define LRFDMDM_EVTMSK2_C1BECNEG_S                                           7U
#define LRFDMDM_EVTMSK2_C1BECNEG_EN                                 0x00000080U
#define LRFDMDM_EVTMSK2_C1BECNEG_DIS                                0x00000000U

// Field:     [6] C1BECPOS 
//
// Enable mask for event EVT2.C1BECPOS 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BECPOS                                    0x00000040U
#define LRFDMDM_EVTMSK2_C1BECPOS_M                                  0x00000040U
#define LRFDMDM_EVTMSK2_C1BECPOS_S                                           6U
#define LRFDMDM_EVTMSK2_C1BECPOS_EN                                 0x00000040U
#define LRFDMDM_EVTMSK2_C1BECPOS_DIS                                0x00000000U

// Field:     [5] C1BEBANY 
//
// Enable mask for event EVT2.C1BEBANY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEBANY                                    0x00000020U
#define LRFDMDM_EVTMSK2_C1BEBANY_M                                  0x00000020U
#define LRFDMDM_EVTMSK2_C1BEBANY_S                                           5U
#define LRFDMDM_EVTMSK2_C1BEBANY_EN                                 0x00000020U
#define LRFDMDM_EVTMSK2_C1BEBANY_DIS                                0x00000000U

// Field:     [4] C1BEBNEG 
//
// Enable mask for event EVT2.C1BEBNEG 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEBNEG                                    0x00000010U
#define LRFDMDM_EVTMSK2_C1BEBNEG_M                                  0x00000010U
#define LRFDMDM_EVTMSK2_C1BEBNEG_S                                           4U
#define LRFDMDM_EVTMSK2_C1BEBNEG_EN                                 0x00000010U
#define LRFDMDM_EVTMSK2_C1BEBNEG_DIS                                0x00000000U

// Field:     [3] C1BEBPOS 
//
// Enable mask for event EVT2.C1BEBPOS 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEBPOS                                    0x00000008U
#define LRFDMDM_EVTMSK2_C1BEBPOS_M                                  0x00000008U
#define LRFDMDM_EVTMSK2_C1BEBPOS_S                                           3U
#define LRFDMDM_EVTMSK2_C1BEBPOS_EN                                 0x00000008U
#define LRFDMDM_EVTMSK2_C1BEBPOS_DIS                                0x00000000U

// Field:     [2] C1BEAANY 
//
// Enable mask for event EVT2.C1BEAANY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEAANY                                    0x00000004U
#define LRFDMDM_EVTMSK2_C1BEAANY_M                                  0x00000004U
#define LRFDMDM_EVTMSK2_C1BEAANY_S                                           2U
#define LRFDMDM_EVTMSK2_C1BEAANY_EN                                 0x00000004U
#define LRFDMDM_EVTMSK2_C1BEAANY_DIS                                0x00000000U

// Field:     [1] C1BEANEG 
//
// Enable mask for event EVT2.C1BEANEG 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEANEG                                    0x00000002U
#define LRFDMDM_EVTMSK2_C1BEANEG_M                                  0x00000002U
#define LRFDMDM_EVTMSK2_C1BEANEG_S                                           1U
#define LRFDMDM_EVTMSK2_C1BEANEG_EN                                 0x00000002U
#define LRFDMDM_EVTMSK2_C1BEANEG_DIS                                0x00000000U

// Field:     [0] C1BEAPOS 
//
// Enable mask for event EVT2.C1BEAPOS 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_EVTMSK2_C1BEAPOS                                    0x00000001U
#define LRFDMDM_EVTMSK2_C1BEAPOS_M                                  0x00000001U
#define LRFDMDM_EVTMSK2_C1BEAPOS_S                                           0U
#define LRFDMDM_EVTMSK2_C1BEAPOS_EN                                 0x00000001U
#define LRFDMDM_EVTMSK2_C1BEAPOS_DIS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTCLR0
//
//*****************************************************************************
// Field:    [15] PBEDAT 
//
// Clear event EVT0.PBEDAT 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_PBEDAT                                      0x00008000U
#define LRFDMDM_EVTCLR0_PBEDAT_M                                    0x00008000U
#define LRFDMDM_EVTCLR0_PBEDAT_S                                            15U
#define LRFDMDM_EVTCLR0_PBEDAT_CLEAR                                0x00008000U
#define LRFDMDM_EVTCLR0_PBEDAT_RETAIN                               0x00000000U

// Field:    [14] PBECMD 
//
// Clear event EVT0.PBECMD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_PBECMD                                      0x00004000U
#define LRFDMDM_EVTCLR0_PBECMD_M                                    0x00004000U
#define LRFDMDM_EVTCLR0_PBECMD_S                                            14U
#define LRFDMDM_EVTCLR0_PBECMD_CLEAR                                0x00004000U
#define LRFDMDM_EVTCLR0_PBECMD_RETAIN                               0x00000000U

// Field:    [13] RFEDAT 
//
// Clear event EVT0.RFEDAT 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_RFEDAT                                      0x00002000U
#define LRFDMDM_EVTCLR0_RFEDAT_M                                    0x00002000U
#define LRFDMDM_EVTCLR0_RFEDAT_S                                            13U
#define LRFDMDM_EVTCLR0_RFEDAT_CLEAR                                0x00002000U
#define LRFDMDM_EVTCLR0_RFEDAT_RETAIN                               0x00000000U

// Field:    [12] BDEC 
//
// Clear event EVT0.BDEC 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_BDEC                                        0x00001000U
#define LRFDMDM_EVTCLR0_BDEC_M                                      0x00001000U
#define LRFDMDM_EVTCLR0_BDEC_S                                              12U
#define LRFDMDM_EVTCLR0_BDEC_CLEAR                                  0x00001000U
#define LRFDMDM_EVTCLR0_BDEC_RETAIN                                 0x00000000U

// Field:    [11] FRAC 
//
// Clear event EVT0.FRAC 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_FRAC                                        0x00000800U
#define LRFDMDM_EVTCLR0_FRAC_M                                      0x00000800U
#define LRFDMDM_EVTCLR0_FRAC_S                                              11U
#define LRFDMDM_EVTCLR0_FRAC_CLEAR                                  0x00000800U
#define LRFDMDM_EVTCLR0_FRAC_RETAIN                                 0x00000000U

// Field:    [10] SYSTIMEVT2 
//
// Clear event EVT0.SYSTIMEVT2 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_SYSTIMEVT2                                  0x00000400U
#define LRFDMDM_EVTCLR0_SYSTIMEVT2_M                                0x00000400U
#define LRFDMDM_EVTCLR0_SYSTIMEVT2_S                                        10U
#define LRFDMDM_EVTCLR0_SYSTIMEVT2_CLEAR                            0x00000400U
#define LRFDMDM_EVTCLR0_SYSTIMEVT2_RETAIN                           0x00000000U

// Field:     [9] SYSTIMEVT1 
//
// Clear event EVT0.SYSTIMEVT1 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_SYSTIMEVT1                                  0x00000200U
#define LRFDMDM_EVTCLR0_SYSTIMEVT1_M                                0x00000200U
#define LRFDMDM_EVTCLR0_SYSTIMEVT1_S                                         9U
#define LRFDMDM_EVTCLR0_SYSTIMEVT1_CLEAR                            0x00000200U
#define LRFDMDM_EVTCLR0_SYSTIMEVT1_RETAIN                           0x00000000U

// Field:     [8] SYSTIMEVT0 
//
// Clear event EVT0.SYSTIMEVT0 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_SYSTIMEVT0                                  0x00000100U
#define LRFDMDM_EVTCLR0_SYSTIMEVT0_M                                0x00000100U
#define LRFDMDM_EVTCLR0_SYSTIMEVT0_S                                         8U
#define LRFDMDM_EVTCLR0_SYSTIMEVT0_CLEAR                            0x00000100U
#define LRFDMDM_EVTCLR0_SYSTIMEVT0_RETAIN                           0x00000000U

// Field:     [7] FIFOWR 
//
// Clear event EVT0.FIFOWR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_FIFOWR                                      0x00000080U
#define LRFDMDM_EVTCLR0_FIFOWR_M                                    0x00000080U
#define LRFDMDM_EVTCLR0_FIFOWR_S                                             7U
#define LRFDMDM_EVTCLR0_FIFOWR_CLEAR                                0x00000080U
#define LRFDMDM_EVTCLR0_FIFOWR_RETAIN                               0x00000000U

// Field:     [6] COUNTER 
//
// Clear event EVT0.COUNTER 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_COUNTER                                     0x00000040U
#define LRFDMDM_EVTCLR0_COUNTER_M                                   0x00000040U
#define LRFDMDM_EVTCLR0_COUNTER_S                                            6U
#define LRFDMDM_EVTCLR0_COUNTER_CLEAR                               0x00000040U
#define LRFDMDM_EVTCLR0_COUNTER_RETAIN                              0x00000000U

// Field:     [5] RFECMD 
//
// Clear event EVT0.RFECMD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_RFECMD                                      0x00000020U
#define LRFDMDM_EVTCLR0_RFECMD_M                                    0x00000020U
#define LRFDMDM_EVTCLR0_RFECMD_S                                             5U
#define LRFDMDM_EVTCLR0_RFECMD_CLEAR                                0x00000020U
#define LRFDMDM_EVTCLR0_RFECMD_RETAIN                               0x00000000U

// Field:     [4] FIFOOVFL 
//
// Clear event EVT0.FIFOOVFL 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_FIFOOVFL                                    0x00000010U
#define LRFDMDM_EVTCLR0_FIFOOVFL_M                                  0x00000010U
#define LRFDMDM_EVTCLR0_FIFOOVFL_S                                           4U
#define LRFDMDM_EVTCLR0_FIFOOVFL_CLEAR                              0x00000010U
#define LRFDMDM_EVTCLR0_FIFOOVFL_RETAIN                             0x00000000U

// Field:     [3] FIFOUNFL 
//
// Clear event EVT0.FIFOUNFL 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_FIFOUNFL                                    0x00000008U
#define LRFDMDM_EVTCLR0_FIFOUNFL_M                                  0x00000008U
#define LRFDMDM_EVTCLR0_FIFOUNFL_S                                           3U
#define LRFDMDM_EVTCLR0_FIFOUNFL_CLEAR                              0x00000008U
#define LRFDMDM_EVTCLR0_FIFOUNFL_RETAIN                             0x00000000U

// Field:     [2] CLKEN4BAUD 
//
// Clear event EVT0.CLKEN4BAUD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_CLKEN4BAUD                                  0x00000004U
#define LRFDMDM_EVTCLR0_CLKEN4BAUD_M                                0x00000004U
#define LRFDMDM_EVTCLR0_CLKEN4BAUD_S                                         2U
#define LRFDMDM_EVTCLR0_CLKEN4BAUD_CLEAR                            0x00000004U
#define LRFDMDM_EVTCLR0_CLKEN4BAUD_RETAIN                           0x00000000U

// Field:     [1] TIMER 
//
// Clear event EVT0.TIMER 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_TIMER                                       0x00000002U
#define LRFDMDM_EVTCLR0_TIMER_M                                     0x00000002U
#define LRFDMDM_EVTCLR0_TIMER_S                                              1U
#define LRFDMDM_EVTCLR0_TIMER_CLEAR                                 0x00000002U
#define LRFDMDM_EVTCLR0_TIMER_RETAIN                                0x00000000U

// Field:     [0] MDMAPI 
//
// Clear event EVT0.MDMAPI 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR0_MDMAPI                                      0x00000001U
#define LRFDMDM_EVTCLR0_MDMAPI_M                                    0x00000001U
#define LRFDMDM_EVTCLR0_MDMAPI_S                                             0U
#define LRFDMDM_EVTCLR0_MDMAPI_CLEAR                                0x00000001U
#define LRFDMDM_EVTCLR0_MDMAPI_RETAIN                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTCLR1
//
//*****************************************************************************
// Field:     [8] REFCLK 
//
// Clear event EVT1.REFCLK 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_REFCLK                                      0x00000100U
#define LRFDMDM_EVTCLR1_REFCLK_M                                    0x00000100U
#define LRFDMDM_EVTCLR1_REFCLK_S                                             8U
#define LRFDMDM_EVTCLR1_REFCLK_CLEAR                                0x00000100U
#define LRFDMDM_EVTCLR1_REFCLK_RETAIN                               0x00000000U

// Field:     [7] S2RSTOP 
//
// Clear event EVT1.S2RSTOP 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_S2RSTOP                                     0x00000080U
#define LRFDMDM_EVTCLR1_S2RSTOP_M                                   0x00000080U
#define LRFDMDM_EVTCLR1_S2RSTOP_S                                            7U
#define LRFDMDM_EVTCLR1_S2RSTOP_CLEAR                               0x00000080U
#define LRFDMDM_EVTCLR1_S2RSTOP_RETAIN                              0x00000000U

// Field:     [6] SWQUFALSESYNC 
//
// Clear event EVT1.SWQUFALSESYNC 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_SWQUFALSESYNC                               0x00000040U
#define LRFDMDM_EVTCLR1_SWQUFALSESYNC_M                             0x00000040U
#define LRFDMDM_EVTCLR1_SWQUFALSESYNC_S                                      6U
#define LRFDMDM_EVTCLR1_SWQUFALSESYNC_CLEAR                         0x00000040U
#define LRFDMDM_EVTCLR1_SWQUFALSESYNC_RETAIN                        0x00000000U

// Field:     [5] SWQUSYNCED 
//
// Clear event EVT1.SWQUSYNCED 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_SWQUSYNCED                                  0x00000020U
#define LRFDMDM_EVTCLR1_SWQUSYNCED_M                                0x00000020U
#define LRFDMDM_EVTCLR1_SWQUSYNCED_S                                         5U
#define LRFDMDM_EVTCLR1_SWQUSYNCED_CLEAR                            0x00000020U
#define LRFDMDM_EVTCLR1_SWQUSYNCED_RETAIN                           0x00000000U

// Field:     [4] CLKENBAUDF 
//
// Clear event EVT1.CLKENBAUDF 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_CLKENBAUDF                                  0x00000010U
#define LRFDMDM_EVTCLR1_CLKENBAUDF_M                                0x00000010U
#define LRFDMDM_EVTCLR1_CLKENBAUDF_S                                         4U
#define LRFDMDM_EVTCLR1_CLKENBAUDF_CLEAR                            0x00000010U
#define LRFDMDM_EVTCLR1_CLKENBAUDF_RETAIN                           0x00000000U

// Field:     [3] FIFORVALID 
//
// Clear event EVT1.FIFORVALID 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_FIFORVALID                                  0x00000008U
#define LRFDMDM_EVTCLR1_FIFORVALID_M                                0x00000008U
#define LRFDMDM_EVTCLR1_FIFORVALID_S                                         3U
#define LRFDMDM_EVTCLR1_FIFORVALID_CLEAR                            0x00000008U
#define LRFDMDM_EVTCLR1_FIFORVALID_RETAIN                           0x00000000U

// Field:     [2] FIFOWREADY 
//
// Clear event EVT1.FIFOWREADY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_FIFOWREADY                                  0x00000004U
#define LRFDMDM_EVTCLR1_FIFOWREADY_M                                0x00000004U
#define LRFDMDM_EVTCLR1_FIFOWREADY_S                                         2U
#define LRFDMDM_EVTCLR1_FIFOWREADY_CLEAR                            0x00000004U
#define LRFDMDM_EVTCLR1_FIFOWREADY_RETAIN                           0x00000000U

// Field:     [1] CLKENBAUD 
//
// Clear event EVT1.CLKENBAUD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_CLKENBAUD                                   0x00000002U
#define LRFDMDM_EVTCLR1_CLKENBAUD_M                                 0x00000002U
#define LRFDMDM_EVTCLR1_CLKENBAUD_S                                          1U
#define LRFDMDM_EVTCLR1_CLKENBAUD_CLEAR                             0x00000002U
#define LRFDMDM_EVTCLR1_CLKENBAUD_RETAIN                            0x00000000U

// Field:     [0] PREAMBLEDONE 
//
// Clear event EVT1.PREAMBLEDONE 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR1_PREAMBLEDONE                                0x00000001U
#define LRFDMDM_EVTCLR1_PREAMBLEDONE_M                              0x00000001U
#define LRFDMDM_EVTCLR1_PREAMBLEDONE_S                                       0U
#define LRFDMDM_EVTCLR1_PREAMBLEDONE_CLEAR                          0x00000001U
#define LRFDMDM_EVTCLR1_PREAMBLEDONE_RETAIN                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_EVTCLR2
//
//*****************************************************************************
// Field:    [15] GPI1 
//
// Clear event EVT2.GPI1 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_GPI1                                        0x00008000U
#define LRFDMDM_EVTCLR2_GPI1_M                                      0x00008000U
#define LRFDMDM_EVTCLR2_GPI1_S                                              15U
#define LRFDMDM_EVTCLR2_GPI1_CLEAR                                  0x00008000U
#define LRFDMDM_EVTCLR2_GPI1_RETAIN                                 0x00000000U

// Field:    [14] GPI0 
//
// Clear event EVT2.GPI0 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_GPI0                                        0x00004000U
#define LRFDMDM_EVTCLR2_GPI0_M                                      0x00004000U
#define LRFDMDM_EVTCLR2_GPI0_S                                              14U
#define LRFDMDM_EVTCLR2_GPI0_CLEAR                                  0x00004000U
#define LRFDMDM_EVTCLR2_GPI0_RETAIN                                 0x00000000U

// Field:    [12] C1BEBLOADED 
//
// Clear event EVT2.C1BEBLOADED 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEBLOADED                                 0x00001000U
#define LRFDMDM_EVTCLR2_C1BEBLOADED_M                               0x00001000U
#define LRFDMDM_EVTCLR2_C1BEBLOADED_S                                       12U
#define LRFDMDM_EVTCLR2_C1BEBLOADED_CLEAR                           0x00001000U
#define LRFDMDM_EVTCLR2_C1BEBLOADED_RETAIN                          0x00000000U

// Field:    [11] C1BECMBANY 
//
// Clear event EVT2.C1BECMBANY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECMBANY                                  0x00000800U
#define LRFDMDM_EVTCLR2_C1BECMBANY_M                                0x00000800U
#define LRFDMDM_EVTCLR2_C1BECMBANY_S                                        11U
#define LRFDMDM_EVTCLR2_C1BECMBANY_CLEAR                            0x00000800U
#define LRFDMDM_EVTCLR2_C1BECMBANY_RETAIN                           0x00000000U

// Field:    [10] C1BECMBNEG 
//
// Clear event EVT2.C1BECMBNEG 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECMBNEG                                  0x00000400U
#define LRFDMDM_EVTCLR2_C1BECMBNEG_M                                0x00000400U
#define LRFDMDM_EVTCLR2_C1BECMBNEG_S                                        10U
#define LRFDMDM_EVTCLR2_C1BECMBNEG_CLEAR                            0x00000400U
#define LRFDMDM_EVTCLR2_C1BECMBNEG_RETAIN                           0x00000000U

// Field:     [9] C1BECMBPOS 
//
// Clear event EVT2.C1BECMBPOS 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECMBPOS                                  0x00000200U
#define LRFDMDM_EVTCLR2_C1BECMBPOS_M                                0x00000200U
#define LRFDMDM_EVTCLR2_C1BECMBPOS_S                                         9U
#define LRFDMDM_EVTCLR2_C1BECMBPOS_CLEAR                            0x00000200U
#define LRFDMDM_EVTCLR2_C1BECMBPOS_RETAIN                           0x00000000U

// Field:     [8] C1BECANY 
//
// Clear event EVT2.C1BECANY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECANY                                    0x00000100U
#define LRFDMDM_EVTCLR2_C1BECANY_M                                  0x00000100U
#define LRFDMDM_EVTCLR2_C1BECANY_S                                           8U
#define LRFDMDM_EVTCLR2_C1BECANY_CLEAR                              0x00000100U
#define LRFDMDM_EVTCLR2_C1BECANY_RETAIN                             0x00000000U

// Field:     [7] C1BECNEG 
//
// Clear event EVT2.C1BECNEG 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECNEG                                    0x00000080U
#define LRFDMDM_EVTCLR2_C1BECNEG_M                                  0x00000080U
#define LRFDMDM_EVTCLR2_C1BECNEG_S                                           7U
#define LRFDMDM_EVTCLR2_C1BECNEG_CLEAR                              0x00000080U
#define LRFDMDM_EVTCLR2_C1BECNEG_RETAIN                             0x00000000U

// Field:     [6] C1BECPOS 
//
// Clear event EVT2.C1BECPOS 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BECPOS                                    0x00000040U
#define LRFDMDM_EVTCLR2_C1BECPOS_M                                  0x00000040U
#define LRFDMDM_EVTCLR2_C1BECPOS_S                                           6U
#define LRFDMDM_EVTCLR2_C1BECPOS_CLEAR                              0x00000040U
#define LRFDMDM_EVTCLR2_C1BECPOS_RETAIN                             0x00000000U

// Field:     [5] C1BEBANY 
//
// Clear event EVT2.C1BEBANY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEBANY                                    0x00000020U
#define LRFDMDM_EVTCLR2_C1BEBANY_M                                  0x00000020U
#define LRFDMDM_EVTCLR2_C1BEBANY_S                                           5U
#define LRFDMDM_EVTCLR2_C1BEBANY_CLEAR                              0x00000020U
#define LRFDMDM_EVTCLR2_C1BEBANY_RETAIN                             0x00000000U

// Field:     [4] C1BEBNEG 
//
// Clear event EVT2.C1BEBNEG 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEBNEG                                    0x00000010U
#define LRFDMDM_EVTCLR2_C1BEBNEG_M                                  0x00000010U
#define LRFDMDM_EVTCLR2_C1BEBNEG_S                                           4U
#define LRFDMDM_EVTCLR2_C1BEBNEG_CLEAR                              0x00000010U
#define LRFDMDM_EVTCLR2_C1BEBNEG_RETAIN                             0x00000000U

// Field:     [3] C1BEBPOS 
//
// Clear event EVT2.C1BEBPOS 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEBPOS                                    0x00000008U
#define LRFDMDM_EVTCLR2_C1BEBPOS_M                                  0x00000008U
#define LRFDMDM_EVTCLR2_C1BEBPOS_S                                           3U
#define LRFDMDM_EVTCLR2_C1BEBPOS_CLEAR                              0x00000008U
#define LRFDMDM_EVTCLR2_C1BEBPOS_RETAIN                             0x00000000U

// Field:     [2] C1BEAANY 
//
// Clear event EVT2.C1BEAANY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEAANY                                    0x00000004U
#define LRFDMDM_EVTCLR2_C1BEAANY_M                                  0x00000004U
#define LRFDMDM_EVTCLR2_C1BEAANY_S                                           2U
#define LRFDMDM_EVTCLR2_C1BEAANY_CLEAR                              0x00000004U
#define LRFDMDM_EVTCLR2_C1BEAANY_RETAIN                             0x00000000U

// Field:     [1] C1BEANEG 
//
// Clear event EVT2.C1BEANEG 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEANEG                                    0x00000002U
#define LRFDMDM_EVTCLR2_C1BEANEG_M                                  0x00000002U
#define LRFDMDM_EVTCLR2_C1BEANEG_S                                           1U
#define LRFDMDM_EVTCLR2_C1BEANEG_CLEAR                              0x00000002U
#define LRFDMDM_EVTCLR2_C1BEANEG_RETAIN                             0x00000000U

// Field:     [0] C1BEAPOS 
//
// Clear event EVT2.C1BEAPOS 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDMDM_EVTCLR2_C1BEAPOS                                    0x00000001U
#define LRFDMDM_EVTCLR2_C1BEAPOS_M                                  0x00000001U
#define LRFDMDM_EVTCLR2_C1BEAPOS_S                                           0U
#define LRFDMDM_EVTCLR2_C1BEAPOS_CLEAR                              0x00000001U
#define LRFDMDM_EVTCLR2_C1BEAPOS_RETAIN                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PDREQ
//
//*****************************************************************************
// Field:     [0] TOPSMPDREQ 
//
// Requests power-down for TOPsm core. If the TOPsm has an ongoing memory 
// access, the hardware will safely gate the clock after the transaction has 
// completed. 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_PDREQ_TOPSMPDREQ                                    0x00000001U
#define LRFDMDM_PDREQ_TOPSMPDREQ_M                                  0x00000001U
#define LRFDMDM_PDREQ_TOPSMPDREQ_S                                           0U
#define LRFDMDM_PDREQ_TOPSMPDREQ_ON                                 0x00000001U
#define LRFDMDM_PDREQ_TOPSMPDREQ_OFF                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_API
//
//*****************************************************************************
// Field:   [7:4] PROTOCOLID 
//
// Protocol ID 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_API_PROTOCOLID_W                                             4U
#define LRFDMDM_API_PROTOCOLID_M                                    0x000000F0U
#define LRFDMDM_API_PROTOCOLID_S                                             4U
#define LRFDMDM_API_PROTOCOLID_ALLONES                              0x000000F0U
#define LRFDMDM_API_PROTOCOLID_ALLZEROS                             0x00000000U

// Field:   [3:0] MDMCMD 
//
// Modem command 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All bits are 0 
#define LRFDMDM_API_MDMCMD_W                                                 4U
#define LRFDMDM_API_MDMCMD_M                                        0x0000000FU
#define LRFDMDM_API_MDMCMD_S                                                 0U
#define LRFDMDM_API_MDMCMD_ALLONES                                  0x0000000FU
#define LRFDMDM_API_MDMCMD_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_CMDPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 0, software defined function 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_CMDPAR0_VAL_W                                               16U
#define LRFDMDM_CMDPAR0_VAL_M                                       0x0000FFFFU
#define LRFDMDM_CMDPAR0_VAL_S                                                0U
#define LRFDMDM_CMDPAR0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDMDM_CMDPAR0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_CMDPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 1, software defined function 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_CMDPAR1_VAL_W                                               16U
#define LRFDMDM_CMDPAR1_VAL_M                                       0x0000FFFFU
#define LRFDMDM_CMDPAR1_VAL_S                                                0U
#define LRFDMDM_CMDPAR1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDMDM_CMDPAR1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_CMDPAR2
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 2, software defined function 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_CMDPAR2_VAL_W                                               16U
#define LRFDMDM_CMDPAR2_VAL_M                                       0x0000FFFFU
#define LRFDMDM_CMDPAR2_VAL_S                                                0U
#define LRFDMDM_CMDPAR2_VAL_ALLONES                                 0x0000FFFFU
#define LRFDMDM_CMDPAR2_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MSGBOX
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Diverse status, error, report bits from MCE. Readable as well in PBE. 
// Controlled by software. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MSGBOX_VAL_W                                                 8U
#define LRFDMDM_MSGBOX_VAL_M                                        0x000000FFU
#define LRFDMDM_MSGBOX_VAL_S                                                 0U
#define LRFDMDM_MSGBOX_VAL_ALLONES                                  0x000000FFU
#define LRFDMDM_MSGBOX_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FREQ
//
//*****************************************************************************
// Field:  [15:0] OFFSET 
//
// Frequency Offset from MCE, controlled by software 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_FREQ_OFFSET_W                                               16U
#define LRFDMDM_FREQ_OFFSET_M                                       0x0000FFFFU
#define LRFDMDM_FREQ_OFFSET_S                                                0U
#define LRFDMDM_FREQ_OFFSET_ALLONES                                 0x0000FFFFU
#define LRFDMDM_FREQ_OFFSET_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FIFOWR
//
//*****************************************************************************
// Field:  [15:0] PAYLOADIN 
//
// FIFO write port. The actual port size is configurable in FIFOWRCTRL 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_FIFOWR_PAYLOADIN_W                                          16U
#define LRFDMDM_FIFOWR_PAYLOADIN_M                                  0x0000FFFFU
#define LRFDMDM_FIFOWR_PAYLOADIN_S                                           0U
#define LRFDMDM_FIFOWR_PAYLOADIN_ALLONES                            0x0000FFFFU
#define LRFDMDM_FIFOWR_PAYLOADIN_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FIFORD
//
//*****************************************************************************
// Field:  [15:0] PAYLOADOUT 
//
// FIFO read port. The actual port size is configurable in FIFORDCTRL 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_FIFORD_PAYLOADOUT_W                                         16U
#define LRFDMDM_FIFORD_PAYLOADOUT_M                                 0x0000FFFFU
#define LRFDMDM_FIFORD_PAYLOADOUT_S                                          0U
#define LRFDMDM_FIFORD_PAYLOADOUT_ALLONES                           0x0000FFFFU
#define LRFDMDM_FIFORD_PAYLOADOUT_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FIFOWRCTRL
//
//*****************************************************************************
// Field:   [5:4] FIFOWRPORT 
//
// FIFO write port mapping 
// ENUMs: 
// PBE                      PBE has write access 
// MODEM                    Modem has write access 
// MDMFIFOWR                The FIFOWR register is used for write access 
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_W                                      2U
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_M                             0x00000030U
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_S                                      4U
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_PBE                           0x00000020U
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_MODEM                         0x00000010U
#define LRFDMDM_FIFOWRCTRL_FIFOWRPORT_MDMFIFOWR                     0x00000000U

// Field:   [3:0] WORDSZWR 
//
// Actual bits in every word write access 
// ENUMs: 
// BITS16                   16 bits 
// BITS15                   15 bits 
// BITS14                   14 bits 
// BITS13                   13 bits 
// BITS12                   12 bits 
// BITS11                   11 bits 
// BITS10                   10 bits 
// BITS9                    9 bits 
// BITS8                    8 bits 
// BITS7                    7 bits 
// BITS6                    6 bits 
// BITS5                    5 bits 
// BITS4                    4 bits 
// BITS3                    3 bits 
// BITS2                    2 bits 
// BITS1                    1 bit 
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_W                                        4U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_M                               0x0000000FU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_S                                        0U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS16                          0x0000000FU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS15                          0x0000000EU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS14                          0x0000000DU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS13                          0x0000000CU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS12                          0x0000000BU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS11                          0x0000000AU
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS10                          0x00000009U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS9                           0x00000008U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS8                           0x00000007U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS7                           0x00000006U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS6                           0x00000005U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS5                           0x00000004U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS4                           0x00000003U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS3                           0x00000002U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS2                           0x00000001U
#define LRFDMDM_FIFOWRCTRL_WORDSZWR_BITS1                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FIFORDCTRL
//
//*****************************************************************************
// Field:   [5:4] FIFORDPORT 
//
// FIFO read port mapping 
// ENUMs: 
// PBE                      PBE has read access 
// MODEM                    Modem has read access 
// MDMFIFORD                The FIFORD register is used for read access 
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_W                                      2U
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_M                             0x00000030U
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_S                                      4U
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_PBE                           0x00000020U
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_MODEM                         0x00000010U
#define LRFDMDM_FIFORDCTRL_FIFORDPORT_MDMFIFORD                     0x00000000U

// Field:   [3:0] WORDSZRD 
//
// Actual bits in every word read access 
// ENUMs: 
// BITS16                   16 bits 
// BITS15                   15 bits 
// BITS14                   14 bits 
// BITS13                   13 bits 
// BITS12                   12 bits 
// BITS11                   11 bits 
// BITS10                   10 bits 
// BITS9                    9 bits 
// BITS8                    8 bits 
// BITS7                    7 bits 
// BITS6                    6 bits 
// BITS5                    5 bits 
// BITS4                    4 bits 
// BITS3                    3 bits 
// BITS2                    2 bits 
// BITS1                    1 bit 
#define LRFDMDM_FIFORDCTRL_WORDSZRD_W                                        4U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_M                               0x0000000FU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_S                                        0U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS16                          0x0000000FU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS15                          0x0000000EU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS14                          0x0000000DU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS13                          0x0000000CU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS12                          0x0000000BU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS11                          0x0000000AU
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS10                          0x00000009U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS9                           0x00000008U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS8                           0x00000007U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS7                           0x00000006U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS6                           0x00000005U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS5                           0x00000004U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS4                           0x00000003U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS3                           0x00000002U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS2                           0x00000001U
#define LRFDMDM_FIFORDCTRL_WORDSZRD_BITS1                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FIFOSTA
//
//*****************************************************************************
// Field:     [5] OVERFLOW 
//
// FIFO overflow error. If this flag is asserted the modem FIFO must be 
// re-initialized with INIT.TXRXFIFO to clear it. Note that re-initializing 
// will flush the FIFO. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_OVERFLOW                                    0x00000020U
#define LRFDMDM_FIFOSTA_OVERFLOW_M                                  0x00000020U
#define LRFDMDM_FIFOSTA_OVERFLOW_S                                           5U
#define LRFDMDM_FIFOSTA_OVERFLOW_ONE                                0x00000020U
#define LRFDMDM_FIFOSTA_OVERFLOW_ZERO                               0x00000000U

// Field:     [4] ALMOSTFULL 
//
// FIFO is almost full. Asserts when the FIFO fill level is above the almost 
// full threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_ALMOSTFULL                                  0x00000010U
#define LRFDMDM_FIFOSTA_ALMOSTFULL_M                                0x00000010U
#define LRFDMDM_FIFOSTA_ALMOSTFULL_S                                         4U
#define LRFDMDM_FIFOSTA_ALMOSTFULL_ONE                              0x00000010U
#define LRFDMDM_FIFOSTA_ALMOSTFULL_ZERO                             0x00000000U

// Field:     [3] ALMOSTEMPTY 
//
// FIFO is almost empty. Asserts when the FIFO fill level is below the almost 
// empty threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_ALMOSTEMPTY                                 0x00000008U
#define LRFDMDM_FIFOSTA_ALMOSTEMPTY_M                               0x00000008U
#define LRFDMDM_FIFOSTA_ALMOSTEMPTY_S                                        3U
#define LRFDMDM_FIFOSTA_ALMOSTEMPTY_ONE                             0x00000008U
#define LRFDMDM_FIFOSTA_ALMOSTEMPTY_ZERO                            0x00000000U

// Field:     [2] UNDERFLOW 
//
// FIFO underflow error. If this flag is asserted the modem FIFO must be 
// re-initialized with INIT.TXRXFIFO to clear it. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_UNDERFLOW                                   0x00000004U
#define LRFDMDM_FIFOSTA_UNDERFLOW_M                                 0x00000004U
#define LRFDMDM_FIFOSTA_UNDERFLOW_S                                          2U
#define LRFDMDM_FIFOSTA_UNDERFLOW_ONE                               0x00000004U
#define LRFDMDM_FIFOSTA_UNDERFLOW_ZERO                              0x00000000U

// Field:     [1] RXVALID 
//
// A full data word is valid and can be read in FIFORD register read port. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_RXVALID                                     0x00000002U
#define LRFDMDM_FIFOSTA_RXVALID_M                                   0x00000002U
#define LRFDMDM_FIFOSTA_RXVALID_S                                            1U
#define LRFDMDM_FIFOSTA_RXVALID_ONE                                 0x00000002U
#define LRFDMDM_FIFOSTA_RXVALID_ZERO                                0x00000000U

// Field:     [0] TXREADY 
//
// The FIFOWR register write port is ready to receive a data word. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_FIFOSTA_TXREADY                                     0x00000001U
#define LRFDMDM_FIFOSTA_TXREADY_M                                   0x00000001U
#define LRFDMDM_FIFOSTA_TXREADY_S                                            0U
#define LRFDMDM_FIFOSTA_TXREADY_ONE                                 0x00000001U
#define LRFDMDM_FIFOSTA_TXREADY_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data to send to RFE. Writing to this register will trigger an event in the 
// RFE, and the command value written here will be readable in 
// LRFDRFE:MCEDATIN0 register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFEDATOUT0_VAL_W                                            16U
#define LRFDMDM_RFEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDMDM_RFEDATOUT0_VAL_S                                             0U
#define LRFDMDM_RFEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDMDM_RFEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data received from RFE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFEDATIN0_VAL_W                                             16U
#define LRFDMDM_RFEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDMDM_RFEDATIN0_VAL_S                                              0U
#define LRFDMDM_RFEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDMDM_RFEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command to send to RFE. Writing to this register will trigger an event in 
// the RFE, and the command value written here will be readable in 
// LRFDRFE:MCECMDIN register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFECMDOUT_VAL_W                                              4U
#define LRFDMDM_RFECMDOUT_VAL_M                                     0x0000000FU
#define LRFDMDM_RFECMDOUT_VAL_S                                              0U
#define LRFDMDM_RFECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDMDM_RFECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command received from RFE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFECMDIN_VAL_W                                               4U
#define LRFDMDM_RFECMDIN_VAL_M                                      0x0000000FU
#define LRFDMDM_RFECMDIN_VAL_S                                               0U
#define LRFDMDM_RFECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDMDM_RFECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PBEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data to send to PBE. Writing to this register will trigger an event in the 
// PBE, and the command value written here will be readable in 
// LRFDPBE:MCEDATIN0 register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_PBEDATOUT0_VAL_W                                            16U
#define LRFDMDM_PBEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDMDM_PBEDATOUT0_VAL_S                                             0U
#define LRFDMDM_PBEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDMDM_PBEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PBEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data received from PBE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_PBEDATIN0_VAL_W                                             16U
#define LRFDMDM_PBEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDMDM_PBEDATIN0_VAL_S                                              0U
#define LRFDMDM_PBEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDMDM_PBEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PBECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command to send to PBE. Writing to this register will trigger an event in 
// the PBE, and the command value written here will be readable in 
// LRFDPBE:MCECMDIN register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_PBECMDOUT_VAL_W                                              4U
#define LRFDMDM_PBECMDOUT_VAL_M                                     0x0000000FU
#define LRFDMDM_PBECMDOUT_VAL_S                                              0U
#define LRFDMDM_PBECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDMDM_PBECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PBECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command received from PBE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_PBECMDIN_VAL_W                                               4U
#define LRFDMDM_PBECMDIN_VAL_M                                      0x0000000FU
#define LRFDMDM_PBECMDIN_VAL_S                                               0U
#define LRFDMDM_PBECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDMDM_PBECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_LQIEST
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// LQI Estimate value to PBE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_LQIEST_VAL_W                                                 8U
#define LRFDMDM_LQIEST_VAL_M                                        0x000000FFU
#define LRFDMDM_LQIEST_VAL_S                                                 0U
#define LRFDMDM_LQIEST_VAL_ALLONES                                  0x000000FFU
#define LRFDMDM_LQIEST_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_PBEEVTMUX
//
//*****************************************************************************
// Field:   [5:0] SEL 
//
// Select one internal event and route to the PBE for usage in the event-unit 
// there 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_PBEEVTMUX_SEL_W                                              6U
#define LRFDMDM_PBEEVTMUX_SEL_M                                     0x0000003FU
#define LRFDMDM_PBEEVTMUX_SEL_S                                              0U
#define LRFDMDM_PBEEVTMUX_SEL_ALLONES                               0x0000003FU
#define LRFDMDM_PBEEVTMUX_SEL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYSTIMEVTMUX0
//
//*****************************************************************************
// Field:  [11:6] SEL1 
//
// Selects one source to send to the systimer output event 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYSTIMEVTMUX0_SEL1_W                                         6U
#define LRFDMDM_SYSTIMEVTMUX0_SEL1_M                                0x00000FC0U
#define LRFDMDM_SYSTIMEVTMUX0_SEL1_S                                         6U
#define LRFDMDM_SYSTIMEVTMUX0_SEL1_ALLONES                          0x00000FC0U
#define LRFDMDM_SYSTIMEVTMUX0_SEL1_ALLZEROS                         0x00000000U

// Field:   [5:0] SEL0 
//
// Selects one source to send to the systimer output event 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYSTIMEVTMUX0_SEL0_W                                         6U
#define LRFDMDM_SYSTIMEVTMUX0_SEL0_M                                0x0000003FU
#define LRFDMDM_SYSTIMEVTMUX0_SEL0_S                                         0U
#define LRFDMDM_SYSTIMEVTMUX0_SEL0_ALLONES                          0x0000003FU
#define LRFDMDM_SYSTIMEVTMUX0_SEL0_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYSTIMEVTMUX1
//
//*****************************************************************************
// Field:   [5:0] SEL2 
//
// Selects one source to send to the systimer output event 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYSTIMEVTMUX1_SEL2_W                                         6U
#define LRFDMDM_SYSTIMEVTMUX1_SEL2_M                                0x0000003FU
#define LRFDMDM_SYSTIMEVTMUX1_SEL2_S                                         0U
#define LRFDMDM_SYSTIMEVTMUX1_SEL2_ALLONES                          0x0000003FU
#define LRFDMDM_SYSTIMEVTMUX1_SEL2_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_ADCDIGCONF
//
//*****************************************************************************
// Field:     [1] QBRANCHEN 
//
// Enables Q component data branch in ADCDIG 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_ADCDIGCONF_QBRANCHEN                                0x00000002U
#define LRFDMDM_ADCDIGCONF_QBRANCHEN_M                              0x00000002U
#define LRFDMDM_ADCDIGCONF_QBRANCHEN_S                                       1U
#define LRFDMDM_ADCDIGCONF_QBRANCHEN_ON                             0x00000002U
#define LRFDMDM_ADCDIGCONF_QBRANCHEN_OFF                            0x00000000U

// Field:     [0] IBRANCHEN 
//
// Enables I component data branch in ADCDIG 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_ADCDIGCONF_IBRANCHEN                                0x00000001U
#define LRFDMDM_ADCDIGCONF_IBRANCHEN_M                              0x00000001U
#define LRFDMDM_ADCDIGCONF_IBRANCHEN_S                                       0U
#define LRFDMDM_ADCDIGCONF_IBRANCHEN_ON                             0x00000001U
#define LRFDMDM_ADCDIGCONF_IBRANCHEN_OFF                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODPRECTRL
//
//*****************************************************************************
// Field:   [7:4] REPS 
//
// Number of preamble repetitions of preamble pattern 
// ENUMs: 
// REPS16                   16 repetitions 
// REPS15                   15 repetitions 
// REPS14                   14 repetitions 
// REPS13                   13 repetitions 
// REPS12                   12 repetitions 
// REPS11                   11 repetitions 
// REPS10                   10 repetitions 
// REPS9                    9 repetitions 
// REPS8                    8 repetitions 
// REPS7                    7 repetitions 
// REPS6                    6 repetitions 
// REPS5                    5 repetitions 
// REPS4                    4 repetitions 
// REPS3                    3 repetitions 
// REPS2                    2 repetitions 
// REPS1                    1 repetition (i.e. only once) 
#define LRFDMDM_MODPRECTRL_REPS_W                                            4U
#define LRFDMDM_MODPRECTRL_REPS_M                                   0x000000F0U
#define LRFDMDM_MODPRECTRL_REPS_S                                            4U
#define LRFDMDM_MODPRECTRL_REPS_REPS16                              0x000000F0U
#define LRFDMDM_MODPRECTRL_REPS_REPS15                              0x000000E0U
#define LRFDMDM_MODPRECTRL_REPS_REPS14                              0x000000D0U
#define LRFDMDM_MODPRECTRL_REPS_REPS13                              0x000000C0U
#define LRFDMDM_MODPRECTRL_REPS_REPS12                              0x000000B0U
#define LRFDMDM_MODPRECTRL_REPS_REPS11                              0x000000A0U
#define LRFDMDM_MODPRECTRL_REPS_REPS10                              0x00000090U
#define LRFDMDM_MODPRECTRL_REPS_REPS9                               0x00000080U
#define LRFDMDM_MODPRECTRL_REPS_REPS8                               0x00000070U
#define LRFDMDM_MODPRECTRL_REPS_REPS7                               0x00000060U
#define LRFDMDM_MODPRECTRL_REPS_REPS6                               0x00000050U
#define LRFDMDM_MODPRECTRL_REPS_REPS5                               0x00000040U
#define LRFDMDM_MODPRECTRL_REPS_REPS4                               0x00000030U
#define LRFDMDM_MODPRECTRL_REPS_REPS3                               0x00000020U
#define LRFDMDM_MODPRECTRL_REPS_REPS2                               0x00000010U
#define LRFDMDM_MODPRECTRL_REPS_REPS1                               0x00000000U

// Field:   [3:0] SIZE 
//
// Preamble pattern size in bits 
// ENUMs: 
// BITS16                   16 bits 
// BITS8                    8 bits 
// BITS4                    4 bits 
#define LRFDMDM_MODPRECTRL_SIZE_W                                            4U
#define LRFDMDM_MODPRECTRL_SIZE_M                                   0x0000000FU
#define LRFDMDM_MODPRECTRL_SIZE_S                                            0U
#define LRFDMDM_MODPRECTRL_SIZE_BITS16                              0x0000000FU
#define LRFDMDM_MODPRECTRL_SIZE_BITS8                               0x00000007U
#define LRFDMDM_MODPRECTRL_SIZE_BITS4                               0x00000003U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODSYMMAP0
//
//*****************************************************************************
// Field: [15:12] SYM3 
//
// Decimal value for bits '11' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP0_SYM3_W                                            4U
#define LRFDMDM_MODSYMMAP0_SYM3_M                                   0x0000F000U
#define LRFDMDM_MODSYMMAP0_SYM3_S                                           12U
#define LRFDMDM_MODSYMMAP0_SYM3_ALLONES                             0x0000F000U
#define LRFDMDM_MODSYMMAP0_SYM3_ALLZEROS                            0x00000000U

// Field:  [11:8] SYM2 
//
// Decimal value for bits '10' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP0_SYM2_W                                            4U
#define LRFDMDM_MODSYMMAP0_SYM2_M                                   0x00000F00U
#define LRFDMDM_MODSYMMAP0_SYM2_S                                            8U
#define LRFDMDM_MODSYMMAP0_SYM2_ALLONES                             0x00000F00U
#define LRFDMDM_MODSYMMAP0_SYM2_ALLZEROS                            0x00000000U

// Field:   [7:4] SYM1 
//
// Decimal value for bit '1' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP0_SYM1_W                                            4U
#define LRFDMDM_MODSYMMAP0_SYM1_M                                   0x000000F0U
#define LRFDMDM_MODSYMMAP0_SYM1_S                                            4U
#define LRFDMDM_MODSYMMAP0_SYM1_ALLONES                             0x000000F0U
#define LRFDMDM_MODSYMMAP0_SYM1_ALLZEROS                            0x00000000U

// Field:   [3:0] SYM0 
//
// Decimal value for bit '0' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP0_SYM0_W                                            4U
#define LRFDMDM_MODSYMMAP0_SYM0_M                                   0x0000000FU
#define LRFDMDM_MODSYMMAP0_SYM0_S                                            0U
#define LRFDMDM_MODSYMMAP0_SYM0_ALLONES                             0x0000000FU
#define LRFDMDM_MODSYMMAP0_SYM0_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODSYMMAP1
//
//*****************************************************************************
// Field: [15:12] SYM7 
//
// Decimal value for bits '111' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP1_SYM7_W                                            4U
#define LRFDMDM_MODSYMMAP1_SYM7_M                                   0x0000F000U
#define LRFDMDM_MODSYMMAP1_SYM7_S                                           12U
#define LRFDMDM_MODSYMMAP1_SYM7_ALLONES                             0x0000F000U
#define LRFDMDM_MODSYMMAP1_SYM7_ALLZEROS                            0x00000000U

// Field:  [11:8] SYM6 
//
// Decimal value for bits '110' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP1_SYM6_W                                            4U
#define LRFDMDM_MODSYMMAP1_SYM6_M                                   0x00000F00U
#define LRFDMDM_MODSYMMAP1_SYM6_S                                            8U
#define LRFDMDM_MODSYMMAP1_SYM6_ALLONES                             0x00000F00U
#define LRFDMDM_MODSYMMAP1_SYM6_ALLZEROS                            0x00000000U

// Field:   [7:4] SYM5 
//
// Decimal value for bits '101' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP1_SYM5_W                                            4U
#define LRFDMDM_MODSYMMAP1_SYM5_M                                   0x000000F0U
#define LRFDMDM_MODSYMMAP1_SYM5_S                                            4U
#define LRFDMDM_MODSYMMAP1_SYM5_ALLONES                             0x000000F0U
#define LRFDMDM_MODSYMMAP1_SYM5_ALLZEROS                            0x00000000U

// Field:   [3:0] SYM4 
//
// Decimal value for bits '100' 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSYMMAP1_SYM4_W                                            4U
#define LRFDMDM_MODSYMMAP1_SYM4_M                                   0x0000000FU
#define LRFDMDM_MODSYMMAP1_SYM4_S                                            0U
#define LRFDMDM_MODSYMMAP1_SYM4_ALLONES                             0x0000000FU
#define LRFDMDM_MODSYMMAP1_SYM4_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODSOFTTX
//
//*****************************************************************************
// Field:   [3:0] SOFTSYMBOL 
//
// Soft symbol {-7..+7} used when MODCTRL.SOFTTXENABLE is enabled. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODSOFTTX_SOFTSYMBOL_W                                       4U
#define LRFDMDM_MODSOFTTX_SOFTSYMBOL_M                              0x0000000FU
#define LRFDMDM_MODSOFTTX_SOFTSYMBOL_S                                       0U
#define LRFDMDM_MODSOFTTX_SOFTSYMBOL_ALLONES                        0x0000000FU
#define LRFDMDM_MODSOFTTX_SOFTSYMBOL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_BAUD
//
//*****************************************************************************
// Field:  [15:0] RATEWORD 
//
// Rate word (bits [20:5]). The 5 LSBs of the 21-bit rate word are defined in 
// BAUDPRE.EXTRATEWORD register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BAUD_RATEWORD_W                                             16U
#define LRFDMDM_BAUD_RATEWORD_M                                     0x0000FFFFU
#define LRFDMDM_BAUD_RATEWORD_S                                              0U
#define LRFDMDM_BAUD_RATEWORD_ALLONES                               0x0000FFFFU
#define LRFDMDM_BAUD_RATEWORD_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_BAUDPRE
//
//*****************************************************************************
// Field: [15:13] ALIGNVALUE 
//
// Align value for timebase after sync 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BAUDPRE_ALIGNVALUE_W                                         3U
#define LRFDMDM_BAUDPRE_ALIGNVALUE_M                                0x0000E000U
#define LRFDMDM_BAUDPRE_ALIGNVALUE_S                                        13U
#define LRFDMDM_BAUDPRE_ALIGNVALUE_ALLONES                          0x0000E000U
#define LRFDMDM_BAUDPRE_ALIGNVALUE_ALLZEROS                         0x00000000U

// Field:  [12:8] EXTRATEWORD 
//
// Extended Rate Word (bits [4:0]). These are the 5 LSBs extending the 16 MSBs 
// configured in BAUD.RATEWORD to form a 21 bit rate word. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BAUDPRE_EXTRATEWORD_W                                        5U
#define LRFDMDM_BAUDPRE_EXTRATEWORD_M                               0x00001F00U
#define LRFDMDM_BAUDPRE_EXTRATEWORD_S                                        8U
#define LRFDMDM_BAUDPRE_EXTRATEWORD_ALLONES                         0x00001F00U
#define LRFDMDM_BAUDPRE_EXTRATEWORD_ALLZEROS                        0x00000000U

// Field:   [7:0] PRESCALER 
//
// Prescaler value, range 1 to 255 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BAUDPRE_PRESCALER_W                                          8U
#define LRFDMDM_BAUDPRE_PRESCALER_M                                 0x000000FFU
#define LRFDMDM_BAUDPRE_PRESCALER_S                                          0U
#define LRFDMDM_BAUDPRE_PRESCALER_ALLONES                           0x000000FFU
#define LRFDMDM_BAUDPRE_PRESCALER_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODMAIN
//
//*****************************************************************************
// Field:   [3:2] FECSELECT 
//
// Forward Error Correction Selection. Used for some signal-wiring in modulator 
// and demodulator. 
// ENUMs: 
// BLR                      Bluetooth LE coded long range compatible FEC 
// RESERVED                 Reserved 
// IEEE15_4                 IEEE 802.15.4 
// NOSEL                    No FEC encoding selected 
#define LRFDMDM_MODMAIN_FECSELECT_W                                          2U
#define LRFDMDM_MODMAIN_FECSELECT_M                                 0x0000000CU
#define LRFDMDM_MODMAIN_FECSELECT_S                                          2U
#define LRFDMDM_MODMAIN_FECSELECT_BLR                               0x0000000CU
#define LRFDMDM_MODMAIN_FECSELECT_RESERVED                          0x00000008U
#define LRFDMDM_MODMAIN_FECSELECT_IEEE15_4                          0x00000004U
#define LRFDMDM_MODMAIN_FECSELECT_NOSEL                             0x00000000U

// Field:   [1:0] MODLEVELS 
//
// Number of modulation levels 
// ENUMs: 
// LVL8                     8 levels 
// LVL4                     4 levels 
// LVL2                     2 levels 
#define LRFDMDM_MODMAIN_MODLEVELS_W                                          2U
#define LRFDMDM_MODMAIN_MODLEVELS_M                                 0x00000003U
#define LRFDMDM_MODMAIN_MODLEVELS_S                                          0U
#define LRFDMDM_MODMAIN_MODLEVELS_LVL8                              0x00000002U
#define LRFDMDM_MODMAIN_MODLEVELS_LVL4                              0x00000001U
#define LRFDMDM_MODMAIN_MODLEVELS_LVL2                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMISC0
//
//*****************************************************************************
// Field:   [9:0] CMIXN 
//
// Signed factor of mixer phasor, Fmix=n*Fs/1024 , where n in range [-512, 511] 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMISC0_CMIXN_W                                            10U
#define LRFDMDM_DEMMISC0_CMIXN_M                                    0x000003FFU
#define LRFDMDM_DEMMISC0_CMIXN_S                                             0U
#define LRFDMDM_DEMMISC0_CMIXN_ALLONES                              0x000003FFU
#define LRFDMDM_DEMMISC0_CMIXN_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMISC1
//
//*****************************************************************************
// Field:  [12:8] CDCTGAINMA 
//
// Gives the gain mantissa of the CDC P/Q tracker 
// ENUMs: 
// ALLONES                  Maximum gain mantissa. 
// ALLZEROS                 When CDCTGAINMA is set to zero, the tracker loop 
//                          is disabled. 
#define LRFDMDM_DEMMISC1_CDCTGAINMA_W                                        5U
#define LRFDMDM_DEMMISC1_CDCTGAINMA_M                               0x00001F00U
#define LRFDMDM_DEMMISC1_CDCTGAINMA_S                                        8U
#define LRFDMDM_DEMMISC1_CDCTGAINMA_ALLONES                         0x00001F00U
#define LRFDMDM_DEMMISC1_CDCTGAINMA_ALLZEROS                        0x00000000U

// Field:   [7:5] CDCTGAINEX 
//
// Gives the gain exponent of the CDC P/Q tracker 
// ENUMs: 
// ALLONES                  When CDCTGAINEX is set to all zeroes, the 
//                          CDCGAINMA multiplier is 512 
// ALLZEROS                 When CDCTGAINEX is set to all zeroes, the 
//                          CDCGAINMA multiplier is 4 
#define LRFDMDM_DEMMISC1_CDCTGAINEX_W                                        3U
#define LRFDMDM_DEMMISC1_CDCTGAINEX_M                               0x000000E0U
#define LRFDMDM_DEMMISC1_CDCTGAINEX_S                                        5U
#define LRFDMDM_DEMMISC1_CDCTGAINEX_ALLONES                         0x000000E0U
#define LRFDMDM_DEMMISC1_CDCTGAINEX_ALLZEROS                        0x00000000U

// Field:     [4] CDCCOLRST 
//
// Collision restart for CDC FIFO 
// ENUMs: 
// EN                       Enable collision detect and restart feature 
// DIS                      Do not enable collision detect and restart feature 
#define LRFDMDM_DEMMISC1_CDCCOLRST                                  0x00000010U
#define LRFDMDM_DEMMISC1_CDCCOLRST_M                                0x00000010U
#define LRFDMDM_DEMMISC1_CDCCOLRST_S                                         4U
#define LRFDMDM_DEMMISC1_CDCCOLRST_EN                               0x00000010U
#define LRFDMDM_DEMMISC1_CDCCOLRST_DIS                              0x00000000U

// Field:   [3:2] MGE1SRCSEL 
//
// Source select magnitude estimator 1 
// ENUMs: 
// CHFI                     Output of CHFI 
// FEXB1                    Output of the FEXB, as selected by 
//                          DEMFEXB0.OUT2SRCSEL register 
// FIDC                     Output of the FIDC (x4 samples) 
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_W                                        2U
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_M                               0x0000000CU
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_S                                        2U
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_CHFI                            0x00000008U
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_FEXB1                           0x00000004U
#define LRFDMDM_DEMMISC1_MGE1SRCSEL_FIDC                            0x00000000U

// Field:   [1:0] CHFIBW 
//
// Select bandwidth (cut-off frequency) of demodulator channel filter 
// ENUMs: 
// BW0_29                   0.29 * Fs. Using FIR filter with taps [2 3 1 -8 
//                          -18 -14 17 72 126 149 126 72 17 -14 -18 -8 1 3 
//                          2]. 
// BW0_41667                0.41667 * Fs. Using FIR filter with taps [-1 -4 2 
//                          12 4 -25 -31 38 154 213 154 38 -31 -25 4 12 2 
//                          -4 -1]. 
// BW0_3333                 0.33333 * Fs. Using FIR filter with taps [0 4 6 0 
//                          -16 -25 0 65 138 170 138 65 0 -25 -16 0 6 4 0]. 
// BW0_5                    0.5 * Fs. Using FIR filter with taps [3 0 -9 0 20 
//                          0 -46 0 160 256 160 0 -46 0 20 0 -9 0 3]. 
#define LRFDMDM_DEMMISC1_CHFIBW_W                                            2U
#define LRFDMDM_DEMMISC1_CHFIBW_M                                   0x00000003U
#define LRFDMDM_DEMMISC1_CHFIBW_S                                            0U
#define LRFDMDM_DEMMISC1_CHFIBW_BW0_29                              0x00000003U
#define LRFDMDM_DEMMISC1_CHFIBW_BW0_41667                           0x00000002U
#define LRFDMDM_DEMMISC1_CHFIBW_BW0_3333                            0x00000001U
#define LRFDMDM_DEMMISC1_CHFIBW_BW0_5                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMISC2
//
//*****************************************************************************
// Field:    [14] MLSERUN 
//
// Enable maximum likelihood sequence estimation (MLSE) desicions 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_DEMMISC2_MLSERUN                                    0x00004000U
#define LRFDMDM_DEMMISC2_MLSERUN_M                                  0x00004000U
#define LRFDMDM_DEMMISC2_MLSERUN_S                                          14U
#define LRFDMDM_DEMMISC2_MLSERUN_EN                                 0x00004000U
#define LRFDMDM_DEMMISC2_MLSERUN_DIS                                0x00000000U

// Field: [13:12] MAFCGAIN 
//
// Set gain in MAFC. Multiplies symbols with 2^N before symbol recovery stage 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMISC2_MAFCGAIN_W                                          2U
#define LRFDMDM_DEMMISC2_MAFCGAIN_M                                 0x00003000U
#define LRFDMDM_DEMMISC2_MAFCGAIN_S                                         12U
#define LRFDMDM_DEMMISC2_MAFCGAIN_ALLONES                           0x00003000U
#define LRFDMDM_DEMMISC2_MAFCGAIN_ALLZEROS                          0x00000000U

// Field:    [11] STIMBYPASS 
//
// Use to bypass STIM estimator 
// ENUMs: 
// EN                       Perform estimation only (no timing correction) 
// DIS                      Perform both estimation and correct timing 
#define LRFDMDM_DEMMISC2_STIMBYPASS                                 0x00000800U
#define LRFDMDM_DEMMISC2_STIMBYPASS_M                               0x00000800U
#define LRFDMDM_DEMMISC2_STIMBYPASS_S                                       11U
#define LRFDMDM_DEMMISC2_STIMBYPASS_EN                              0x00000800U
#define LRFDMDM_DEMMISC2_STIMBYPASS_DIS                             0x00000000U

// Field:    [10] STIMESTONLY 
//
// Only perform symbol timing error estimation in STIM, without doing timing 
// correction 
// ENUMs: 
// EN                       Perform estimation only (no timing correction) 
// DIS                      Perform both estimation and correct timing 
#define LRFDMDM_DEMMISC2_STIMESTONLY                                0x00000400U
#define LRFDMDM_DEMMISC2_STIMESTONLY_M                              0x00000400U
#define LRFDMDM_DEMMISC2_STIMESTONLY_S                                      10U
#define LRFDMDM_DEMMISC2_STIMESTONLY_EN                             0x00000400U
#define LRFDMDM_DEMMISC2_STIMESTONLY_DIS                            0x00000000U

// Field:   [9:7] STIMTEAPERIOD 
//
// Symbol timing error accumulator period (4 to 128 symbols) in STIM 
// ENUMs: 
// SYM128                   128 symbols 
// SYM64                    64 symbols 
// SYM32                    32 symbols 
// SYM16                    16 symbols 
// SYM8                     8 symbols 
// SYM4                     4 symbols 
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_W                                     3U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_M                            0x00000380U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_S                                     7U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM128                       0x00000280U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM64                        0x00000200U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM32                        0x00000180U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM16                        0x00000100U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM8                         0x00000080U
#define LRFDMDM_DEMMISC2_STIMTEAPERIOD_SYM4                         0x00000000U

// Field:   [6:4] STIMTEAGAIN 
//
// Symbol timing error accumulator gain in STIM 
// ENUMs: 
// DIV4                     Gain is 1/4 
// DIV8                     Gain is 1/8 
// DIV16                    Gain is 1/16 
// DIV32                    Gain is 1/32 
// DIV64                    Gain is 1/64 
// DIV128                   Gain is 1/128 
// DIV256                   Gain is 1/256 
// DIV512                   Gain is 1/512 
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_W                                       3U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_M                              0x00000070U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_S                                       4U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV4                           0x00000070U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV8                           0x00000060U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV16                          0x00000050U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV32                          0x00000040U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV64                          0x00000030U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV128                         0x00000020U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV256                         0x00000010U
#define LRFDMDM_DEMMISC2_STIMTEAGAIN_DIV512                         0x00000000U

// Field:     [3] PDIFLINPREDEN 
//
// Enable linear predictor in PDIF at CORDIC output 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_DEMMISC2_PDIFLINPREDEN                              0x00000008U
#define LRFDMDM_DEMMISC2_PDIFLINPREDEN_M                            0x00000008U
#define LRFDMDM_DEMMISC2_PDIFLINPREDEN_S                                     3U
#define LRFDMDM_DEMMISC2_PDIFLINPREDEN_ON                           0x00000008U
#define LRFDMDM_DEMMISC2_PDIFLINPREDEN_OFF                          0x00000000U

// Field:     [2] PDIFDESPECK 
//
// Enable despeckler in PDIF at CORDIC output 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_DEMMISC2_PDIFDESPECK                                0x00000004U
#define LRFDMDM_DEMMISC2_PDIFDESPECK_M                              0x00000004U
#define LRFDMDM_DEMMISC2_PDIFDESPECK_S                                       2U
#define LRFDMDM_DEMMISC2_PDIFDESPECK_EN                             0x00000004U
#define LRFDMDM_DEMMISC2_PDIFDESPECK_DIS                            0x00000000U

// Field:     [1] PDIFIQCONJEN 
//
// Conjugate the complex I/Q signal in PDIF 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_DEMMISC2_PDIFIQCONJEN                               0x00000002U
#define LRFDMDM_DEMMISC2_PDIFIQCONJEN_M                             0x00000002U
#define LRFDMDM_DEMMISC2_PDIFIQCONJEN_S                                      1U
#define LRFDMDM_DEMMISC2_PDIFIQCONJEN_ON                            0x00000002U
#define LRFDMDM_DEMMISC2_PDIFIQCONJEN_OFF                           0x00000000U

// Field:     [0] PDIFLIMITRANGE 
//
// Limit range on maximal PDIF output, i.e. instantaneous frequency sample 
// ENUMs: 
// EN                       Limit the range to 7-bit, i.e. +/- 64 
// DIS                      Allow full 8-bit range, i.e. +/- 128 
#define LRFDMDM_DEMMISC2_PDIFLIMITRANGE                             0x00000001U
#define LRFDMDM_DEMMISC2_PDIFLIMITRANGE_M                           0x00000001U
#define LRFDMDM_DEMMISC2_PDIFLIMITRANGE_S                                    0U
#define LRFDMDM_DEMMISC2_PDIFLIMITRANGE_EN                          0x00000001U
#define LRFDMDM_DEMMISC2_PDIFLIMITRANGE_DIS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMISC3
//
//*****************************************************************************
// Field: [14:13] BDE2DVGA 
//
// DVGA settings for BDE2. The DVGA control for BDE2 is shared with the RFE in 
// its LRFDRFE:GAINCTRL.BDE2DVGA register. 
// Software should determine who uses them. Please note that if both processors 
// attempt to control it, the resulting setting will be the two settings ORed 
// together. 
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
#define LRFDMDM_DEMMISC3_BDE2DVGA_W                                          2U
#define LRFDMDM_DEMMISC3_BDE2DVGA_M                                 0x00006000U
#define LRFDMDM_DEMMISC3_BDE2DVGA_S                                         13U
#define LRFDMDM_DEMMISC3_BDE2DVGA_GAIN8                             0x00006000U
#define LRFDMDM_DEMMISC3_BDE2DVGA_GAIN4                             0x00004000U
#define LRFDMDM_DEMMISC3_BDE2DVGA_GAIN2                             0x00002000U
#define LRFDMDM_DEMMISC3_BDE2DVGA_GAIN1                             0x00000000U

// Field:    [12] BDE1FILTMODE 
//
// BDE1 Filter only mode. When enabled, BDE1 lp filters in signal path, but no 
// decimation occurs. 
// ENUMs: 
// DIV2                     Decimate by 2 
// DIV1                     Decimate by 1 (no decimation) 
#define LRFDMDM_DEMMISC3_BDE1FILTMODE                               0x00001000U
#define LRFDMDM_DEMMISC3_BDE1FILTMODE_M                             0x00001000U
#define LRFDMDM_DEMMISC3_BDE1FILTMODE_S                                     12U
#define LRFDMDM_DEMMISC3_BDE1FILTMODE_DIV2                          0x00001000U
#define LRFDMDM_DEMMISC3_BDE1FILTMODE_DIV1                          0x00000000U

// Field: [11:10] LQIPERIOD 
//
// LQI measurement period 
// ENUMs: 
// SYM1024                  1024 symbols 
// SYM256                   256 symbols 
// SYM64                    64 symbols 
// SYM16                    16 symbols 
#define LRFDMDM_DEMMISC3_LQIPERIOD_W                                         2U
#define LRFDMDM_DEMMISC3_LQIPERIOD_M                                0x00000C00U
#define LRFDMDM_DEMMISC3_LQIPERIOD_S                                        10U
#define LRFDMDM_DEMMISC3_LQIPERIOD_SYM1024                          0x00000C00U
#define LRFDMDM_DEMMISC3_LQIPERIOD_SYM256                           0x00000800U
#define LRFDMDM_DEMMISC3_LQIPERIOD_SYM64                            0x00000400U
#define LRFDMDM_DEMMISC3_LQIPERIOD_SYM16                            0x00000000U

// Field:   [9:8] BDE1DVGA 
//
// DVGA settings for BDE1. The DVGA control for BDE1 is shared with the RFE in 
// its LRFDRFE:GAINCTRL.BDE1DVGA register. 
// Software should determine who uses them. Please note that if both processors 
// attempt to control it, the resulting setting will be the two settings ORed 
// together. 
// ENUMs: 
// GAIN8                    Gain 8 
// GAIN4                    Gain 4 
// GAIN2                    Gain 2 
// GAIN1                    Gain 1 
#define LRFDMDM_DEMMISC3_BDE1DVGA_W                                          2U
#define LRFDMDM_DEMMISC3_BDE1DVGA_M                                 0x00000300U
#define LRFDMDM_DEMMISC3_BDE1DVGA_S                                          8U
#define LRFDMDM_DEMMISC3_BDE1DVGA_GAIN8                             0x00000300U
#define LRFDMDM_DEMMISC3_BDE1DVGA_GAIN4                             0x00000200U
#define LRFDMDM_DEMMISC3_BDE1DVGA_GAIN2                             0x00000100U
#define LRFDMDM_DEMMISC3_BDE1DVGA_GAIN1                             0x00000000U

// Field:     [7] BDE1NUMSTAGES 
//
// BDE1 decimation filter setting 
// ENUMs: 
// DIV2                     Decimate by 2 
// DIV1                     Decimate by 1 (no decimation) 
#define LRFDMDM_DEMMISC3_BDE1NUMSTAGES                              0x00000080U
#define LRFDMDM_DEMMISC3_BDE1NUMSTAGES_M                            0x00000080U
#define LRFDMDM_DEMMISC3_BDE1NUMSTAGES_S                                     7U
#define LRFDMDM_DEMMISC3_BDE1NUMSTAGES_DIV2                         0x00000080U
#define LRFDMDM_DEMMISC3_BDE1NUMSTAGES_DIV1                         0x00000000U

// Field:   [6:5] PDIFDECIM 
//
// Additional decimation in PDIF 
// ENUMs: 
// DIV4                     Decimate by 4 
// DIV2                     Decimate by 2 
// DIV1                     No decimation 
#define LRFDMDM_DEMMISC3_PDIFDECIM_W                                         2U
#define LRFDMDM_DEMMISC3_PDIFDECIM_M                                0x00000060U
#define LRFDMDM_DEMMISC3_PDIFDECIM_S                                         5U
#define LRFDMDM_DEMMISC3_PDIFDECIM_DIV4                             0x00000040U
#define LRFDMDM_DEMMISC3_PDIFDECIM_DIV2                             0x00000020U
#define LRFDMDM_DEMMISC3_PDIFDECIM_DIV1                             0x00000000U

// Field:   [4:0] BDE2DECRATIO 
//
// BDE2 decimation filter setting 
// ENUMs: 
// DIV8                     Decimate by 8 
// DIV4                     Decimate by 4 
// DIV2                     Decimate by 2 
// DIV1                     Decimate by 1 (no decimation) 
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_W                                      5U
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_M                             0x0000001FU
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_S                                      0U
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_DIV8                          0x00000003U
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_DIV4                          0x00000002U
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_DIV2                          0x00000001U
#define LRFDMDM_DEMMISC3_BDE2DECRATIO_DIV1                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMIQMC0
//
//*****************************************************************************
// Field:  [15:8] GAINFACTOR 
//
// Gain factor to compensate for unequal gains between the I and Q signal paths 
// in the analog RF front-end. 
// The compensation is done by scaling the I path amplitude (no compensation of 
// Q path). 
// The gain factor is given as an unsigned number in the range [0,255] 
// corresponding to gain factor range [0,2], 
//  where value 128 gives gain factor 1.0 (no gain). Any gain compensation is 
// applied in a stage after the phase compensation. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMIQMC0_GAINFACTOR_W                                        8U
#define LRFDMDM_DEMIQMC0_GAINFACTOR_M                               0x0000FF00U
#define LRFDMDM_DEMIQMC0_GAINFACTOR_S                                        8U
#define LRFDMDM_DEMIQMC0_GAINFACTOR_ALLONES                         0x0000FF00U
#define LRFDMDM_DEMIQMC0_GAINFACTOR_ALLZEROS                        0x00000000U

// Field:   [7:0] PHASEFACTOR 
//
// Phase factor to compensate for unorthogonal I and Q signals. 
// The phase factor is given as a signed number in the range [-128,127] 
// corresponding to phase factor range [-0.5, 0.496], 
// where the phase factor can be calculated as phase_factor = tan(phase_error). 
// This gives an available phase error compensation range of [-26.6, 26.4] 
// degrees. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMIQMC0_PHASEFACTOR_W                                       8U
#define LRFDMDM_DEMIQMC0_PHASEFACTOR_M                              0x000000FFU
#define LRFDMDM_DEMIQMC0_PHASEFACTOR_S                                       0U
#define LRFDMDM_DEMIQMC0_PHASEFACTOR_ALLONES                        0x000000FFU
#define LRFDMDM_DEMIQMC0_PHASEFACTOR_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMDSBU
//
//*****************************************************************************
// Field:  [15:8] DSBUAVGLENGTH 
//
// Length for moving average of the newest DSBU samples. 
// The buffer can hold up to 256 samples. Length of 255 is maximum. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMDSBU_DSBUAVGLENGTH_W                                      8U
#define LRFDMDM_DEMDSBU_DSBUAVGLENGTH_M                             0x0000FF00U
#define LRFDMDM_DEMDSBU_DSBUAVGLENGTH_S                                      8U
#define LRFDMDM_DEMDSBU_DSBUAVGLENGTH_ALLONES                       0x0000FF00U
#define LRFDMDM_DEMDSBU_DSBUAVGLENGTH_ALLZEROS                      0x00000000U

// Field:   [7:0] DSBUDELAY 
//
// Output delay from sample buffer, as offset between write and read pointers. 
// The buffer can hold up to 256 samples. Delay of 0 means maximum. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMDSBU_DSBUDELAY_W                                          8U
#define LRFDMDM_DEMDSBU_DSBUDELAY_M                                 0x000000FFU
#define LRFDMDM_DEMDSBU_DSBUDELAY_S                                          0U
#define LRFDMDM_DEMDSBU_DSBUDELAY_ALLONES                           0x000000FFU
#define LRFDMDM_DEMDSBU_DSBUDELAY_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMCODC0
//
//*****************************************************************************
// Field:    [11] ESTSEL 
//
// Select which estimator to show as readable output 
// ENUMs: 
// IIR                      Read back latest IIR estimate 
// ACC                      Read back latest accumulator estimate 
#define LRFDMDM_DEMCODC0_ESTSEL                                     0x00000800U
#define LRFDMDM_DEMCODC0_ESTSEL_M                                   0x00000800U
#define LRFDMDM_DEMCODC0_ESTSEL_S                                           11U
#define LRFDMDM_DEMCODC0_ESTSEL_IIR                                 0x00000800U
#define LRFDMDM_DEMCODC0_ESTSEL_ACC                                 0x00000000U

// Field:  [10:9] COMPSEL 
//
// Select estimator to use for coarse DC offset compensation 
// ENUMs: 
// IIR                      Compensate with latest IIR estimate 
// ACC                      Compensate with latest accumulator estimate 
// MANUAL                   Use manually programmable values from DEMCODC1 
//                          registers 
#define LRFDMDM_DEMCODC0_COMPSEL_W                                           2U
#define LRFDMDM_DEMCODC0_COMPSEL_M                                  0x00000600U
#define LRFDMDM_DEMCODC0_COMPSEL_S                                           9U
#define LRFDMDM_DEMCODC0_COMPSEL_IIR                                0x00000600U
#define LRFDMDM_DEMCODC0_COMPSEL_ACC                                0x00000400U
#define LRFDMDM_DEMCODC0_COMPSEL_MANUAL                             0x00000000U

// Field:     [8] IIRUSEINITIAL 
//
// When enabled, a configurable value is loaded to initialize IIR filter when 
// CODC estimator is re-initialized. 
// ENUMs: 
// EN                       Use the manual compensation values in DEMCODC1 for 
//                          initialization 
// DIS                      Initialize IIR filter with value zero 
#define LRFDMDM_DEMCODC0_IIRUSEINITIAL                              0x00000100U
#define LRFDMDM_DEMCODC0_IIRUSEINITIAL_M                            0x00000100U
#define LRFDMDM_DEMCODC0_IIRUSEINITIAL_S                                     8U
#define LRFDMDM_DEMCODC0_IIRUSEINITIAL_EN                           0x00000100U
#define LRFDMDM_DEMCODC0_IIRUSEINITIAL_DIS                          0x00000000U

// Field:   [7:5] IIRGAIN 
//
// Adjust first-order IIR filter adaptation which controls filter bandwidth. 
// ENUMs: 
// DIV1024                  Use 1/1024 IIR adaptation 
// DIV512                   Use 1/512 IIR adaptation 
// DIV256                   Use 1/256 IIR adaptation 
// DIV128                   Use 1/128 IIR adaptation 
// DIV64                    Use 1/64 IIR adaptation 
// DIV32                    Use 1/32 IIR adaptation 
// DIV16                    Use 1/16 IIR adaptation 
// OFF                      Filter disabled 
#define LRFDMDM_DEMCODC0_IIRGAIN_W                                           3U
#define LRFDMDM_DEMCODC0_IIRGAIN_M                                  0x000000E0U
#define LRFDMDM_DEMCODC0_IIRGAIN_S                                           5U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV1024                            0x000000E0U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV512                             0x000000C0U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV256                             0x000000A0U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV128                             0x00000080U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV64                              0x00000060U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV32                              0x00000040U
#define LRFDMDM_DEMCODC0_IIRGAIN_DIV16                              0x00000020U
#define LRFDMDM_DEMCODC0_IIRGAIN_OFF                                0x00000000U

// Field:     [4] IIREN 
//
// Enable first-order IIR filter inside CODC 
// ENUMs: 
// ON                       Enable IIR estimator 
// OFF                      Disable IIR estimator 
#define LRFDMDM_DEMCODC0_IIREN                                      0x00000010U
#define LRFDMDM_DEMCODC0_IIREN_M                                    0x00000010U
#define LRFDMDM_DEMCODC0_IIREN_S                                             4U
#define LRFDMDM_DEMCODC0_IIREN_ON                                   0x00000010U
#define LRFDMDM_DEMCODC0_IIREN_OFF                                  0x00000000U

// Field:     [3] ACCMODE 
//
// Accumulator estimator mode 
// ENUMs: 
// CONT                     Generate new DC estimates continuously 
// SINGLE                   Generate a single DC estimate only, then stop 
#define LRFDMDM_DEMCODC0_ACCMODE                                    0x00000008U
#define LRFDMDM_DEMCODC0_ACCMODE_M                                  0x00000008U
#define LRFDMDM_DEMCODC0_ACCMODE_S                                           3U
#define LRFDMDM_DEMCODC0_ACCMODE_CONT                               0x00000008U
#define LRFDMDM_DEMCODC0_ACCMODE_SINGLE                             0x00000000U

// Field:   [2:1] ACCPERIOD 
//
// Integration period for accumulator estimator 
// ENUMs: 
// SMPL512                  512 samples 
// SMPL128                  128 samples 
// SMPL32                   32 samples 
// SMPL8                    8 samples 
#define LRFDMDM_DEMCODC0_ACCPERIOD_W                                         2U
#define LRFDMDM_DEMCODC0_ACCPERIOD_M                                0x00000006U
#define LRFDMDM_DEMCODC0_ACCPERIOD_S                                         1U
#define LRFDMDM_DEMCODC0_ACCPERIOD_SMPL512                          0x00000006U
#define LRFDMDM_DEMCODC0_ACCPERIOD_SMPL128                          0x00000004U
#define LRFDMDM_DEMCODC0_ACCPERIOD_SMPL32                           0x00000002U
#define LRFDMDM_DEMCODC0_ACCPERIOD_SMPL8                            0x00000000U

// Field:     [0] ACCEN 
//
// Enable accumulator based estimator inside CODC 
// ENUMs: 
// ON                       Enable accumulator estimator 
// OFF                      Disable accumulator estimator 
#define LRFDMDM_DEMCODC0_ACCEN                                      0x00000001U
#define LRFDMDM_DEMCODC0_ACCEN_M                                    0x00000001U
#define LRFDMDM_DEMCODC0_ACCEN_S                                             0U
#define LRFDMDM_DEMCODC0_ACCEN_ON                                   0x00000001U
#define LRFDMDM_DEMCODC0_ACCEN_OFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFIDC0
//
//*****************************************************************************
// Field:   [5:4] COMPSEL 
//
// Select estimator to use for fine DC offset compensation 
// ENUMs: 
// ACC                      Compensate with latest accumulator estimate 
// MANUAL                   Use manually programmable values from DEMFIDC1 
//                          registers 
#define LRFDMDM_DEMFIDC0_COMPSEL_W                                           2U
#define LRFDMDM_DEMFIDC0_COMPSEL_M                                  0x00000030U
#define LRFDMDM_DEMFIDC0_COMPSEL_S                                           4U
#define LRFDMDM_DEMFIDC0_COMPSEL_ACC                                0x00000020U
#define LRFDMDM_DEMFIDC0_COMPSEL_MANUAL                             0x00000000U

// Field:   [3:2] ACCPERIOD 
//
// Integration period for accumulator estimator 
// ENUMs: 
// SMPL512                  512 samples 
// SMPL128                  128 samples 
// SMPL32                   32 samples 
// SMPL8                    8 samples 
#define LRFDMDM_DEMFIDC0_ACCPERIOD_W                                         2U
#define LRFDMDM_DEMFIDC0_ACCPERIOD_M                                0x0000000CU
#define LRFDMDM_DEMFIDC0_ACCPERIOD_S                                         2U
#define LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL512                          0x0000000CU
#define LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128                          0x00000008U
#define LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32                           0x00000004U
#define LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL8                            0x00000000U

// Field:     [1] ACCMODE 
//
// Accumulator estimator mode 
// ENUMs: 
// CONT                     Generate new DC estimates continuously 
// SINGLE                   Generate a single DC estimate only, then stop 
#define LRFDMDM_DEMFIDC0_ACCMODE                                    0x00000002U
#define LRFDMDM_DEMFIDC0_ACCMODE_M                                  0x00000002U
#define LRFDMDM_DEMFIDC0_ACCMODE_S                                           1U
#define LRFDMDM_DEMFIDC0_ACCMODE_CONT                               0x00000002U
#define LRFDMDM_DEMFIDC0_ACCMODE_SINGLE                             0x00000000U

// Field:     [0] ACCEN 
//
// Enable accumulator based estimator inside FIDC 
// ENUMs: 
// ON                       Enable accumulator estimator 
// OFF                      Disable accumulator estimator 
#define LRFDMDM_DEMFIDC0_ACCEN                                      0x00000001U
#define LRFDMDM_DEMFIDC0_ACCEN_M                                    0x00000001U
#define LRFDMDM_DEMFIDC0_ACCEN_S                                             0U
#define LRFDMDM_DEMFIDC0_ACCEN_ON                                   0x00000001U
#define LRFDMDM_DEMFIDC0_ACCEN_OFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFEXB0
//
//*****************************************************************************
// Field:    [13] OUT2PASSTHROUGH 
//
// Front-end crossbar output #2 is direct passthrough of the crossbar input 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMFEXB0_OUT2PASSTHROUGH                            0x00002000U
#define LRFDMDM_DEMFEXB0_OUT2PASSTHROUGH_M                          0x00002000U
#define LRFDMDM_DEMFEXB0_OUT2PASSTHROUGH_S                                  13U
#define LRFDMDM_DEMFEXB0_OUT2PASSTHROUGH_ONE                        0x00002000U
#define LRFDMDM_DEMFEXB0_OUT2PASSTHROUGH_ZERO                       0x00000000U

// Field: [12:11] OUT2SRCSEL 
//
// Source select for XBAR output #2 (towards magnitude estimation engine MGE0) 
// ENUMs: 
// BDE1                     Source is complex N*Fs/1024 mixer (CMIX) 
// CMIX                     Source is complex N*Fs/1024 mixer (CMIX) 
// CODC                     Source is coarse DC remover (CODC) 
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_W                                        2U
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_M                               0x00001800U
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_S                                       11U
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_BDE1                            0x00001000U
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_CMIX                            0x00000800U
#define LRFDMDM_DEMFEXB0_OUT2SRCSEL_CODC                            0x00000000U

// Field:    [10] OUT1PASSTHROUGH 
//
// Front-end crossbar output #1 is direct passthrough of the crossbar input 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMFEXB0_OUT1PASSTHROUGH                            0x00000400U
#define LRFDMDM_DEMFEXB0_OUT1PASSTHROUGH_M                          0x00000400U
#define LRFDMDM_DEMFEXB0_OUT1PASSTHROUGH_S                                  10U
#define LRFDMDM_DEMFEXB0_OUT1PASSTHROUGH_ONE                        0x00000400U
#define LRFDMDM_DEMFEXB0_OUT1PASSTHROUGH_ZERO                       0x00000000U

// Field:   [9:8] OUT1SRCSEL 
//
// Source select for XBAR output #1 (main output, towards BDE2 and rest of 
// demodulator) 
// ENUMs: 
// BDE1                     Source is complex N*Fs/1024 mixer (CMIX) 
// CMIX                     Source is complex N*Fs/1024 mixer (CMIX) 
// CODC                     Source is coarse DC remover (CODC) 
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_W                                        2U
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_M                               0x00000300U
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_S                                        8U
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_BDE1                            0x00000200U
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_CMIX                            0x00000100U
#define LRFDMDM_DEMFEXB0_OUT1SRCSEL_CODC                            0x00000000U

// Field:   [7:6] B4SRCSEL 
//
// Not used 
// ENUMs: 
// ONES                     Source is complex N*Fs/1024 mixer (ONES) 
// ZEROS                    Source is complex N*Fs/1024 mixer (ZEROS) 
#define LRFDMDM_DEMFEXB0_B4SRCSEL_W                                          2U
#define LRFDMDM_DEMFEXB0_B4SRCSEL_M                                 0x000000C0U
#define LRFDMDM_DEMFEXB0_B4SRCSEL_S                                          6U
#define LRFDMDM_DEMFEXB0_B4SRCSEL_ONES                              0x000000C0U
#define LRFDMDM_DEMFEXB0_B4SRCSEL_ZEROS                             0x00000000U

// Field:   [5:4] B3SRCSEL 
//
// Source select for BDE1 (XBAR block #3) 
// ENUMs: 
// CMIX                     Source is complex N*Fs/1024 mixer (CMIX) 
// CODC                     Source is complex N*Fs/1024 mixer (CMIX) 
// INPUT                    Source is crossbar main input 
#define LRFDMDM_DEMFEXB0_B3SRCSEL_W                                          2U
#define LRFDMDM_DEMFEXB0_B3SRCSEL_M                                 0x00000030U
#define LRFDMDM_DEMFEXB0_B3SRCSEL_S                                          4U
#define LRFDMDM_DEMFEXB0_B3SRCSEL_CMIX                              0x00000020U
#define LRFDMDM_DEMFEXB0_B3SRCSEL_CODC                              0x00000010U
#define LRFDMDM_DEMFEXB0_B3SRCSEL_INPUT                             0x00000000U

// Field:   [3:2] B2SRCSEL 
//
// Source select for CMIX (XBAR block #2) 
// ENUMs: 
// BDE1                     Source is coarse DC remover (CODC) 
// CODC                     Source is coarse DC remover (CODC) 
// INPUT                    Source is crossbar main input 
#define LRFDMDM_DEMFEXB0_B2SRCSEL_W                                          2U
#define LRFDMDM_DEMFEXB0_B2SRCSEL_M                                 0x0000000CU
#define LRFDMDM_DEMFEXB0_B2SRCSEL_S                                          2U
#define LRFDMDM_DEMFEXB0_B2SRCSEL_BDE1                              0x00000008U
#define LRFDMDM_DEMFEXB0_B2SRCSEL_CODC                              0x00000004U
#define LRFDMDM_DEMFEXB0_B2SRCSEL_INPUT                             0x00000000U

// Field:   [1:0] B1SRCSEL 
//
// Source select for CODC (XBAR block #1) 
// ENUMs: 
// BDE1                     Source is complex N*Fs/1024 mixer (CMIX) 
// CMIX                     Source is complex N*Fs/1024 mixer (CMIX) 
// INPUT                    Source is crossbar main input 
#define LRFDMDM_DEMFEXB0_B1SRCSEL_W                                          2U
#define LRFDMDM_DEMFEXB0_B1SRCSEL_M                                 0x00000003U
#define LRFDMDM_DEMFEXB0_B1SRCSEL_S                                          0U
#define LRFDMDM_DEMFEXB0_B1SRCSEL_BDE1                              0x00000002U
#define LRFDMDM_DEMFEXB0_B1SRCSEL_CMIX                              0x00000001U
#define LRFDMDM_DEMFEXB0_B1SRCSEL_INPUT                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMDSXB0
//
//*****************************************************************************
// Field:     [5] OUT2PASSTHROUGH 
//
// Crossbar output #2 is direct passthrough of the crossbar input 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMDSXB0_OUT2PASSTHROUGH                            0x00000020U
#define LRFDMDM_DEMDSXB0_OUT2PASSTHROUGH_M                          0x00000020U
#define LRFDMDM_DEMDSXB0_OUT2PASSTHROUGH_S                                   5U
#define LRFDMDM_DEMDSXB0_OUT2PASSTHROUGH_ONE                        0x00000020U
#define LRFDMDM_DEMDSXB0_OUT2PASSTHROUGH_ZERO                       0x00000000U

// Field:     [4] OUT1PASSTHROUGH 
//
// Crossbar output #1 is direct passthrough of the crossbar input 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMDSXB0_OUT1PASSTHROUGH                            0x00000010U
#define LRFDMDM_DEMDSXB0_OUT1PASSTHROUGH_M                          0x00000010U
#define LRFDMDM_DEMDSXB0_OUT1PASSTHROUGH_S                                   4U
#define LRFDMDM_DEMDSXB0_OUT1PASSTHROUGH_ONE                        0x00000010U
#define LRFDMDM_DEMDSXB0_OUT1PASSTHROUGH_ZERO                       0x00000000U

// Field:     [3] OUTSRCSEL2 
//
// Source select XBAR output, branch 1 (baud branch) 
// ENUMs: 
// MAFI                     Source is matched filter (MAFI) 
// FIFE                     Source is fine frequency offset estimator (FIFE) 
#define LRFDMDM_DEMDSXB0_OUTSRCSEL2                                 0x00000008U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL2_M                               0x00000008U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL2_S                                        3U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL2_MAFI                            0x00000008U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL2_FIFE                            0x00000000U

// Field:     [2] OUTSRCSEL1 
//
// Source select for XBAR output, branch 2 (flushed branch) 
// ENUMs: 
// MAFI                     Source is matched filter (MAFI) 
// FIFE                     Source is fine frequency offset estimator (FIFE) 
#define LRFDMDM_DEMDSXB0_OUTSRCSEL1                                 0x00000004U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL1_M                               0x00000004U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL1_S                                        2U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL1_MAFI                            0x00000004U
#define LRFDMDM_DEMDSXB0_OUTSRCSEL1_FIFE                            0x00000000U

// Field:     [1] B2SRCSEL 
//
// Source select for MAFI (XBAR block #2) 
// ENUMs: 
// FIFE                     Source is fine frequency offset estimator (FIFE) 
// INPUT                    Source is crossbar main input 
#define LRFDMDM_DEMDSXB0_B2SRCSEL                                   0x00000002U
#define LRFDMDM_DEMDSXB0_B2SRCSEL_M                                 0x00000002U
#define LRFDMDM_DEMDSXB0_B2SRCSEL_S                                          1U
#define LRFDMDM_DEMDSXB0_B2SRCSEL_FIFE                              0x00000002U
#define LRFDMDM_DEMDSXB0_B2SRCSEL_INPUT                             0x00000000U

// Field:     [0] B1SRCSEL 
//
// Source select for FIFE (XBAR block #1) 
// ENUMs: 
// MAFI                     Source is matched filter (MAFI) 
// INPUT                    Source is crossbar main input 
#define LRFDMDM_DEMDSXB0_B1SRCSEL                                   0x00000001U
#define LRFDMDM_DEMDSXB0_B1SRCSEL_M                                 0x00000001U
#define LRFDMDM_DEMDSXB0_B1SRCSEL_S                                          0U
#define LRFDMDM_DEMDSXB0_B1SRCSEL_MAFI                              0x00000001U
#define LRFDMDM_DEMDSXB0_B1SRCSEL_INPUT                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFIFE0
//
//*****************************************************************************
// Field:    [11] FINEFOESEL 
//
// Select which estimator to show as readable output 
// ENUMs: 
// ACC                      Latest accumulator estimate 
// IIR                      Latest IIR estimate 
#define LRFDMDM_DEMFIFE0_FINEFOESEL                                 0x00000800U
#define LRFDMDM_DEMFIFE0_FINEFOESEL_M                               0x00000800U
#define LRFDMDM_DEMFIFE0_FINEFOESEL_S                                       11U
#define LRFDMDM_DEMFIFE0_FINEFOESEL_ACC                             0x00000800U
#define LRFDMDM_DEMFIFE0_FINEFOESEL_IIR                             0x00000000U

// Field:  [10:9] FOCFFSEL 
//
// Select which estimate source to be used in feed-forward compensation point 
// ENUMs: 
// MANUAL                   Use programmable manual value from register bank. 
//                          (Note: an input register is not implemented, so 
//                          the manual compensation value is tied to '0') 
// ACC                      Compensate with latest accumulator estimate 
// IIR                      Compensate with latest IIR estimate 
#define LRFDMDM_DEMFIFE0_FOCFFSEL_W                                          2U
#define LRFDMDM_DEMFIFE0_FOCFFSEL_M                                 0x00000600U
#define LRFDMDM_DEMFIFE0_FOCFFSEL_S                                          9U
#define LRFDMDM_DEMFIFE0_FOCFFSEL_MANUAL                            0x00000400U
#define LRFDMDM_DEMFIFE0_FOCFFSEL_ACC                               0x00000200U
#define LRFDMDM_DEMFIFE0_FOCFFSEL_IIR                               0x00000000U

// Field:     [8] ACCCNTMODE 
//
// Accumulator estimator mode 
// ENUMs: 
// CONT                     Generate new frequency offset estimates 
//                          continuously 
// SINGLE                   Generate a single frequency offset estimate only, 
//                          then stop 
#define LRFDMDM_DEMFIFE0_ACCCNTMODE                                 0x00000100U
#define LRFDMDM_DEMFIFE0_ACCCNTMODE_M                               0x00000100U
#define LRFDMDM_DEMFIFE0_ACCCNTMODE_S                                        8U
#define LRFDMDM_DEMFIFE0_ACCCNTMODE_CONT                            0x00000100U
#define LRFDMDM_DEMFIFE0_ACCCNTMODE_SINGLE                          0x00000000U

// Field:   [7:6] ACCPERIOD 
//
// Integration period for accumulator 
// ENUMs: 
// PER512                   512 samples 
// PER256                   256 samples 
// PER128                   128 samples 
// PER64                    64 samples 
#define LRFDMDM_DEMFIFE0_ACCPERIOD_W                                         2U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_M                                0x000000C0U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_S                                         6U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_PER512                           0x000000C0U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_PER256                           0x00000080U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_PER128                           0x00000040U
#define LRFDMDM_DEMFIFE0_ACCPERIOD_PER64                            0x00000000U

// Field:     [5] ACCEN 
//
// Enable accumulator based frequency offset estimator inside FIFE 
// ENUMs: 
// ON                       Enable accumulator estimator 
// OFF                      Disable accumulator estimator 
#define LRFDMDM_DEMFIFE0_ACCEN                                      0x00000020U
#define LRFDMDM_DEMFIFE0_ACCEN_M                                    0x00000020U
#define LRFDMDM_DEMFIFE0_ACCEN_S                                             5U
#define LRFDMDM_DEMFIFE0_ACCEN_ON                                   0x00000020U
#define LRFDMDM_DEMFIFE0_ACCEN_OFF                                  0x00000000U

// Field:     [4] IIRUSEINITIAL 
//
// When enabled, a configurable value is loaded to initialize IIR filter when 
// FIFE estimator is re-initialized. 
// ENUMs: 
// EN                       Use the manual compensation value in DEMFIFE1 for 
//                          initialization 
// DIS                      Initialize IIR filter with value zero 
#define LRFDMDM_DEMFIFE0_IIRUSEINITIAL                              0x00000010U
#define LRFDMDM_DEMFIFE0_IIRUSEINITIAL_M                            0x00000010U
#define LRFDMDM_DEMFIFE0_IIRUSEINITIAL_S                                     4U
#define LRFDMDM_DEMFIFE0_IIRUSEINITIAL_EN                           0x00000010U
#define LRFDMDM_DEMFIFE0_IIRUSEINITIAL_DIS                          0x00000000U

// Field:   [3:1] IIRGAIN 
//
// Adjust first-order IIR filter adaptation which controls filter bandwidth 
// ENUMs: 
// DIV1024                  Use 1/1024 IIR adaptation 
// DIV512                   Use 1/512 IIR adaptation 
// DIV256                   Use 1/256 IIR adaptation 
// DIV128                   Use 1/128 IIR adaptation 
// DIV64                    Use 1/64 IIR adaptation 
// DIV32                    Use 1/32 IIR adaptation 
// DIV16                    Use 1/16 IIR adaptation 
// OFF                      Filter disabled 
#define LRFDMDM_DEMFIFE0_IIRGAIN_W                                           3U
#define LRFDMDM_DEMFIFE0_IIRGAIN_M                                  0x0000000EU
#define LRFDMDM_DEMFIFE0_IIRGAIN_S                                           1U
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV1024                            0x0000000EU
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV512                             0x0000000CU
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV256                             0x0000000AU
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV128                             0x00000008U
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV64                              0x00000006U
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV32                              0x00000004U
#define LRFDMDM_DEMFIFE0_IIRGAIN_DIV16                              0x00000002U
#define LRFDMDM_DEMFIFE0_IIRGAIN_OFF                                0x00000000U

// Field:     [0] IIREN 
//
// Enable first-order IIR filter based freq offset estimator inside FIFE 
// ENUMs: 
// ON                       Enable IIR estimator 
// OFF                      Disable IIR estimator 
#define LRFDMDM_DEMFIFE0_IIREN                                      0x00000001U
#define LRFDMDM_DEMFIFE0_IIREN_M                                    0x00000001U
#define LRFDMDM_DEMFIFE0_IIREN_S                                             0U
#define LRFDMDM_DEMFIFE0_IIREN_ON                                   0x00000001U
#define LRFDMDM_DEMFIFE0_IIREN_OFF                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMAFI0
//
//*****************************************************************************
// Field:  [15:8] C1C7 
//
// Filter coefficient c1 (and c7) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI0_C1C7_W                                              8U
#define LRFDMDM_DEMMAFI0_C1C7_M                                     0x0000FF00U
#define LRFDMDM_DEMMAFI0_C1C7_S                                              8U
#define LRFDMDM_DEMMAFI0_C1C7_ALLONES                               0x0000FF00U
#define LRFDMDM_DEMMAFI0_C1C7_ALLZEROS                              0x00000000U

// Field:   [7:0] C0C8 
//
// Filter coefficient c0 (and c8) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI0_C0C8_W                                              8U
#define LRFDMDM_DEMMAFI0_C0C8_M                                     0x000000FFU
#define LRFDMDM_DEMMAFI0_C0C8_S                                              0U
#define LRFDMDM_DEMMAFI0_C0C8_ALLONES                               0x000000FFU
#define LRFDMDM_DEMMAFI0_C0C8_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMAFI1
//
//*****************************************************************************
// Field:  [15:8] C3C5 
//
// Filter coefficient c3 (and c5) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI1_C3C5_W                                              8U
#define LRFDMDM_DEMMAFI1_C3C5_M                                     0x0000FF00U
#define LRFDMDM_DEMMAFI1_C3C5_S                                              8U
#define LRFDMDM_DEMMAFI1_C3C5_ALLONES                               0x0000FF00U
#define LRFDMDM_DEMMAFI1_C3C5_ALLZEROS                              0x00000000U

// Field:   [7:0] C2C6 
//
// Filter coefficient c2 (and c6) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI1_C2C6_W                                              8U
#define LRFDMDM_DEMMAFI1_C2C6_M                                     0x000000FFU
#define LRFDMDM_DEMMAFI1_C2C6_S                                              0U
#define LRFDMDM_DEMMAFI1_C2C6_ALLONES                               0x000000FFU
#define LRFDMDM_DEMMAFI1_C2C6_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMAFI2
//
//*****************************************************************************
// Field:   [8:0] C4 
//
// Filter coefficient c4. The matched filter will have unity gain when the sum 
// of all coefficients c0 to c8 equals 512. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI2_C4_W                                                9U
#define LRFDMDM_DEMMAFI2_C4_M                                       0x000001FFU
#define LRFDMDM_DEMMAFI2_C4_S                                                0U
#define LRFDMDM_DEMMAFI2_C4_ALLONES                                 0x000001FFU
#define LRFDMDM_DEMMAFI2_C4_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BE0
//
//*****************************************************************************
// Field: [15:11] MASKB 
//
// Mask for correlator B to select the correlator length to use. 
// The number specifies number of nibbles (i.e. 4-bit block, which typically 
// corresponds to one symbol) 
// of the correlator holding the oldest samples that will be ignored in 
// computations. 
// When set to zero, the full 128 sample (=32 symbol) correlator length will be 
// used. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE0_MASKB_W                                             5U
#define LRFDMDM_DEMC1BE0_MASKB_M                                    0x0000F800U
#define LRFDMDM_DEMC1BE0_MASKB_S                                            11U
#define LRFDMDM_DEMC1BE0_MASKB_ALLONES                              0x0000F800U
#define LRFDMDM_DEMC1BE0_MASKB_ALLZEROS                             0x00000000U

// Field:  [10:6] MASKA 
//
// Mask for correlator A to select the correlator length to use. 
// The number specifies number of nibbles (i.e. 4-bit block, which typically 
// corresponds to one symbol) 
// of the correlator holding the oldest samples that will be ignored in 
// computations. 
// When set to zero, the full 128 sample (=32 symbol) correlator length will be 
// used. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE0_MASKA_W                                             5U
#define LRFDMDM_DEMC1BE0_MASKA_M                                    0x000007C0U
#define LRFDMDM_DEMC1BE0_MASKA_S                                             6U
#define LRFDMDM_DEMC1BE0_MASKA_ALLONES                              0x000007C0U
#define LRFDMDM_DEMC1BE0_MASKA_ALLZEROS                             0x00000000U

// Field:   [5:4] CASCCONF 
//
// Correlator cascade configuration 
// ENUMs: 
// PARALLEL                 Connect correlators in parallel 
// SERIAL                   Connect correlators in series (A -> B) 
// SINGLE                   Correlator B not used 
#define LRFDMDM_DEMC1BE0_CASCCONF_W                                          2U
#define LRFDMDM_DEMC1BE0_CASCCONF_M                                 0x00000030U
#define LRFDMDM_DEMC1BE0_CASCCONF_S                                          4U
#define LRFDMDM_DEMC1BE0_CASCCONF_PARALLEL                          0x00000020U
#define LRFDMDM_DEMC1BE0_CASCCONF_SERIAL                            0x00000010U
#define LRFDMDM_DEMC1BE0_CASCCONF_SINGLE                            0x00000000U

// Field:   [3:0] COPYCONF 
//
// Control auto copy of contents from corr A to corr B 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE0_COPYCONF_W                                          4U
#define LRFDMDM_DEMC1BE0_COPYCONF_M                                 0x0000000FU
#define LRFDMDM_DEMC1BE0_COPYCONF_S                                          0U
#define LRFDMDM_DEMC1BE0_COPYCONF_ALLONES                           0x0000000FU
#define LRFDMDM_DEMC1BE0_COPYCONF_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BE1
//
//*****************************************************************************
// Field:  [15:8] THRESHOLDB 
//
// Correlation threshold value for correlator B 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE1_THRESHOLDB_W                                        8U
#define LRFDMDM_DEMC1BE1_THRESHOLDB_M                               0x0000FF00U
#define LRFDMDM_DEMC1BE1_THRESHOLDB_S                                        8U
#define LRFDMDM_DEMC1BE1_THRESHOLDB_ALLONES                         0x0000FF00U
#define LRFDMDM_DEMC1BE1_THRESHOLDB_ALLZEROS                        0x00000000U

// Field:   [7:0] THRESHOLDA 
//
// Correlation threshold value for correlator A 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE1_THRESHOLDA_W                                        8U
#define LRFDMDM_DEMC1BE1_THRESHOLDA_M                               0x000000FFU
#define LRFDMDM_DEMC1BE1_THRESHOLDA_S                                        0U
#define LRFDMDM_DEMC1BE1_THRESHOLDA_ALLONES                         0x000000FFU
#define LRFDMDM_DEMC1BE1_THRESHOLDA_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BE2
//
//*****************************************************************************
// Field:    [10] PARLOADCONF 
//
// Configuration to control peak event generation (applies to correlators A, B, 
// D, E) 
// ENUMs: 
// ATOD                     Trigger peak event only if peak is highest in 
//                          correlator since search start 
// ATOB                     Trigger peak event on all peaks above threshold 
#define LRFDMDM_DEMC1BE2_PARLOADCONF                                0x00000400U
#define LRFDMDM_DEMC1BE2_PARLOADCONF_M                              0x00000400U
#define LRFDMDM_DEMC1BE2_PARLOADCONF_S                                      10U
#define LRFDMDM_DEMC1BE2_PARLOADCONF_ATOD                           0x00000400U
#define LRFDMDM_DEMC1BE2_PARLOADCONF_ATOB                           0x00000000U

// Field:   [9:8] PEAKCONF 
//
// Configuration to control peak event generation (applies to correlators A, B, 
// D, E) 
// ENUMs: 
// BESTAB                   Trigger peak event for combined highest peak 
//                          search for corr "A and B" and "D and E" in 
//                          pairs 
// BEST                     Trigger peak event only if peak is highest in 
//                          correlator since search start 
// THRESH                   Trigger peak event on all peaks above threshold 
#define LRFDMDM_DEMC1BE2_PEAKCONF_W                                          2U
#define LRFDMDM_DEMC1BE2_PEAKCONF_M                                 0x00000300U
#define LRFDMDM_DEMC1BE2_PEAKCONF_S                                          8U
#define LRFDMDM_DEMC1BE2_PEAKCONF_BESTAB                            0x00000200U
#define LRFDMDM_DEMC1BE2_PEAKCONF_BEST                              0x00000100U
#define LRFDMDM_DEMC1BE2_PEAKCONF_THRESH                            0x00000000U

// Field:   [7:0] THRESHOLDC 
//
// Correlation threshold value for correlator C (corr C is A+B concatenated) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BE2_THRESHOLDC_W                                        8U
#define LRFDMDM_DEMC1BE2_THRESHOLDC_M                               0x000000FFU
#define LRFDMDM_DEMC1BE2_THRESHOLDC_S                                        0U
#define LRFDMDM_DEMC1BE2_THRESHOLDC_ALLONES                         0x000000FFU
#define LRFDMDM_DEMC1BE2_THRESHOLDC_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SPARE0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SPARE0_VAL_W                                                16U
#define LRFDMDM_SPARE0_VAL_M                                        0x0000FFFFU
#define LRFDMDM_SPARE0_VAL_S                                                 0U
#define LRFDMDM_SPARE0_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_SPARE0_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SPARE1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SPARE1_VAL_W                                                16U
#define LRFDMDM_SPARE1_VAL_M                                        0x0000FFFFU
#define LRFDMDM_SPARE1_VAL_S                                                 0U
#define LRFDMDM_SPARE1_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_SPARE1_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SPARE2
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SPARE2_VAL_W                                                16U
#define LRFDMDM_SPARE2_VAL_M                                        0x0000FFFFU
#define LRFDMDM_SPARE2_VAL_S                                                 0U
#define LRFDMDM_SPARE2_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_SPARE2_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SPARE3
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Spare register for use by firmware 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SPARE3_VAL_W                                                16U
#define LRFDMDM_SPARE3_VAL_M                                        0x0000FFFFU
#define LRFDMDM_SPARE3_VAL_S                                                 0U
#define LRFDMDM_SPARE3_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_SPARE3_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMSWQU0
//
//*****************************************************************************
// Field:     [7] SYNCMODE 
//
// 0: Search for A and B in parallell 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMSWQU0_SYNCMODE                                   0x00000080U
#define LRFDMDM_DEMSWQU0_SYNCMODE_M                                 0x00000080U
#define LRFDMDM_DEMSWQU0_SYNCMODE_S                                          7U
#define LRFDMDM_DEMSWQU0_SYNCMODE_ONE                               0x00000080U
#define LRFDMDM_DEMSWQU0_SYNCMODE_ZERO                              0x00000000U

// Field:     [6] AUTOMAFC 
//
// Let sync word qualifier automatically control the manual frequency offset 
// compensation (MAFC) block when it is running. 
// ENUMs: 
// ON                       Give control to sync word qualifier 
// OFF                      Keep manual control over MAFC 
#define LRFDMDM_DEMSWQU0_AUTOMAFC                                   0x00000040U
#define LRFDMDM_DEMSWQU0_AUTOMAFC_M                                 0x00000040U
#define LRFDMDM_DEMSWQU0_AUTOMAFC_S                                          6U
#define LRFDMDM_DEMSWQU0_AUTOMAFC_ON                                0x00000040U
#define LRFDMDM_DEMSWQU0_AUTOMAFC_OFF                               0x00000000U

// Field:     [5] RUN 
//
// Start/stop sync word qualifier. 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_DEMSWQU0_RUN                                        0x00000020U
#define LRFDMDM_DEMSWQU0_RUN_M                                      0x00000020U
#define LRFDMDM_DEMSWQU0_RUN_S                                               5U
#define LRFDMDM_DEMSWQU0_RUN_ON                                     0x00000020U
#define LRFDMDM_DEMSWQU0_RUN_OFF                                    0x00000000U

// Field:   [4:0] REFLEN 
//
// Bit length of sync word qualifier reference vector, constituted by (reflen + 
// 1) most significant bits of sync word A and/or B. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMSWQU0_REFLEN_W                                            5U
#define LRFDMDM_DEMSWQU0_REFLEN_M                                   0x0000001FU
#define LRFDMDM_DEMSWQU0_REFLEN_S                                            0U
#define LRFDMDM_DEMSWQU0_REFLEN_ALLONES                             0x0000001FU
#define LRFDMDM_DEMSWQU0_REFLEN_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BEREF0
//
//*****************************************************************************
// Field:  [15:0] CAR15C0 
//
// Corr A reference bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BEREF0_CAR15C0_W                                       16U
#define LRFDMDM_DEMC1BEREF0_CAR15C0_M                               0x0000FFFFU
#define LRFDMDM_DEMC1BEREF0_CAR15C0_S                                        0U
#define LRFDMDM_DEMC1BEREF0_CAR15C0_ALLONES                         0x0000FFFFU
#define LRFDMDM_DEMC1BEREF0_CAR15C0_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BEREF1
//
//*****************************************************************************
// Field:  [15:0] CAR31C16 
//
// Corr A reference bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BEREF1_CAR31C16_W                                      16U
#define LRFDMDM_DEMC1BEREF1_CAR31C16_M                              0x0000FFFFU
#define LRFDMDM_DEMC1BEREF1_CAR31C16_S                                       0U
#define LRFDMDM_DEMC1BEREF1_CAR31C16_ALLONES                        0x0000FFFFU
#define LRFDMDM_DEMC1BEREF1_CAR31C16_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BEREF2
//
//*****************************************************************************
// Field:  [15:0] CBR15C0 
//
// Corr B reference bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BEREF2_CBR15C0_W                                       16U
#define LRFDMDM_DEMC1BEREF2_CBR15C0_M                               0x0000FFFFU
#define LRFDMDM_DEMC1BEREF2_CBR15C0_S                                        0U
#define LRFDMDM_DEMC1BEREF2_CBR15C0_ALLONES                         0x0000FFFFU
#define LRFDMDM_DEMC1BEREF2_CBR15C0_ALLZEROS                        0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMC1BEREF3
//
//*****************************************************************************
// Field:  [15:0] CBR31C16 
//
// Corr B reference bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMC1BEREF3_CBR31C16_W                                      16U
#define LRFDMDM_DEMC1BEREF3_CBR31C16_M                              0x0000FFFFU
#define LRFDMDM_DEMC1BEREF3_CBR31C16_S                                       0U
#define LRFDMDM_DEMC1BEREF3_CBR31C16_ALLONES                        0x0000FFFFU
#define LRFDMDM_DEMC1BEREF3_CBR31C16_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODCTRL
//
//*****************************************************************************
// Field:    [11] DSBUSEL 
//
// Select DSBU input source. It is not valid anymore. This bitfield is reserved 
// for future use. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_MODCTRL_DSBUSEL                                     0x00000800U
#define LRFDMDM_MODCTRL_DSBUSEL_M                                   0x00000800U
#define LRFDMDM_MODCTRL_DSBUSEL_S                                           11U
#define LRFDMDM_MODCTRL_DSBUSEL_ONE                                 0x00000800U
#define LRFDMDM_MODCTRL_DSBUSEL_ZERO                                0x00000000U

// Field:    [10] HDISMODE 
//
// Enable Hilbert discriminator mode for data descicion 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_MODCTRL_HDISMODE                                    0x00000400U
#define LRFDMDM_MODCTRL_HDISMODE_M                                  0x00000400U
#define LRFDMDM_MODCTRL_HDISMODE_S                                          10U
#define LRFDMDM_MODCTRL_HDISMODE_EN                                 0x00000400U
#define LRFDMDM_MODCTRL_HDISMODE_DIS                                0x00000000U

// Field:     [9] PARBITQUALEN 
//
// Enable Parallel Bit Qualifier (read DEMC1BEA) 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_MODCTRL_PARBITQUALEN                                0x00000200U
#define LRFDMDM_MODCTRL_PARBITQUALEN_M                              0x00000200U
#define LRFDMDM_MODCTRL_PARBITQUALEN_S                                       9U
#define LRFDMDM_MODCTRL_PARBITQUALEN_ON                             0x00000200U
#define LRFDMDM_MODCTRL_PARBITQUALEN_OFF                            0x00000000U

// Field:   [8:7] STIMMODE 
//
// Controls STIM module for different modes 
// ENUMs: 
// EARLY                    STIM starts early 
// LATE                     STIM starts late 
// NORMAL                   Normal Mode 
#define LRFDMDM_MODCTRL_STIMMODE_W                                           2U
#define LRFDMDM_MODCTRL_STIMMODE_M                                  0x00000180U
#define LRFDMDM_MODCTRL_STIMMODE_S                                           7U
#define LRFDMDM_MODCTRL_STIMMODE_EARLY                              0x00000100U
#define LRFDMDM_MODCTRL_STIMMODE_LATE                               0x00000080U
#define LRFDMDM_MODCTRL_STIMMODE_NORMAL                             0x00000000U

// Field:     [6] C1BEMODE 
//
// Controls the C1BE mode 
// ENUMs: 
// EARLYLATE                Set the C1BE in special early/late mode 
// NORMAL                   Normal mode 
#define LRFDMDM_MODCTRL_C1BEMODE                                    0x00000040U
#define LRFDMDM_MODCTRL_C1BEMODE_M                                  0x00000040U
#define LRFDMDM_MODCTRL_C1BEMODE_S                                           6U
#define LRFDMDM_MODCTRL_C1BEMODE_EARLYLATE                          0x00000040U
#define LRFDMDM_MODCTRL_C1BEMODE_NORMAL                             0x00000000U

// Field:     [5] SOFTPDIFFMODE 
//
// Enable Soft PDIFF mode for RX 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_MODCTRL_SOFTPDIFFMODE                               0x00000020U
#define LRFDMDM_MODCTRL_SOFTPDIFFMODE_M                             0x00000020U
#define LRFDMDM_MODCTRL_SOFTPDIFFMODE_S                                      5U
#define LRFDMDM_MODCTRL_SOFTPDIFFMODE_EN                            0x00000020U
#define LRFDMDM_MODCTRL_SOFTPDIFFMODE_DIS                           0x00000000U

// Field:     [4] SOFTTXENABLE 
//
// Enable SOFT TX mode, controlled via MODSOFTTX 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_MODCTRL_SOFTTXENABLE                                0x00000010U
#define LRFDMDM_MODCTRL_SOFTTXENABLE_M                              0x00000010U
#define LRFDMDM_MODCTRL_SOFTTXENABLE_S                                       4U
#define LRFDMDM_MODCTRL_SOFTTXENABLE_ON                             0x00000010U
#define LRFDMDM_MODCTRL_SOFTTXENABLE_OFF                            0x00000000U

// Field:     [3] FECENABLE 
//
// Global FEC modes enable 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_MODCTRL_FECENABLE                                   0x00000008U
#define LRFDMDM_MODCTRL_FECENABLE_M                                 0x00000008U
#define LRFDMDM_MODCTRL_FECENABLE_S                                          3U
#define LRFDMDM_MODCTRL_FECENABLE_ON                                0x00000008U
#define LRFDMDM_MODCTRL_FECENABLE_OFF                               0x00000000U

// Field:     [2] FEC5TERMINATE 
//
// Goes into termination mode in 5Mbps TX FEC. This bitfield is not valid 
// anymore. 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDMDM_MODCTRL_FEC5TERMINATE                               0x00000004U
#define LRFDMDM_MODCTRL_FEC5TERMINATE_M                             0x00000004U
#define LRFDMDM_MODCTRL_FEC5TERMINATE_S                                      2U
#define LRFDMDM_MODCTRL_FEC5TERMINATE_ON                            0x00000004U
#define LRFDMDM_MODCTRL_FEC5TERMINATE_OFF                           0x00000000U

// Field:     [1] TONEINSERT 
//
// Inserts a tone 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_MODCTRL_TONEINSERT                                  0x00000002U
#define LRFDMDM_MODCTRL_TONEINSERT_M                                0x00000002U
#define LRFDMDM_MODCTRL_TONEINSERT_S                                         1U
#define LRFDMDM_MODCTRL_TONEINSERT_EN                               0x00000002U
#define LRFDMDM_MODCTRL_TONEINSERT_DIS                              0x00000000U

// Field:     [0] PREAMBLEINSERT 
//
// Inserts preamble 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDMDM_MODCTRL_PREAMBLEINSERT                              0x00000001U
#define LRFDMDM_MODCTRL_PREAMBLEINSERT_M                            0x00000001U
#define LRFDMDM_MODCTRL_PREAMBLEINSERT_S                                     0U
#define LRFDMDM_MODCTRL_PREAMBLEINSERT_EN                           0x00000001U
#define LRFDMDM_MODCTRL_PREAMBLEINSERT_DIS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MODPREAMBLE
//
//*****************************************************************************
// Field:  [15:0] WORD 
//
// 16 bit preamble word pattern. The LSB is transmitted first 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MODPREAMBLE_WORD_W                                          16U
#define LRFDMDM_MODPREAMBLE_WORD_M                                  0x0000FFFFU
#define LRFDMDM_MODPREAMBLE_WORD_S                                           0U
#define LRFDMDM_MODPREAMBLE_WORD_ALLONES                            0x0000FFFFU
#define LRFDMDM_MODPREAMBLE_WORD_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFRAC0
//
//*****************************************************************************
// Field:  [15:0] P15C0 
//
// Downsampler P[15:0]. Sample rate of the output signal: Fs_out = Fs_in * P/Q. 
// The hardware requires the resampling factor P/Q to be in the range [1/4, 1], 
// i.e. only down-sampling with a factor in the range [1,4] is supported. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFRAC0_P15C0_W                                            16U
#define LRFDMDM_DEMFRAC0_P15C0_M                                    0x0000FFFFU
#define LRFDMDM_DEMFRAC0_P15C0_S                                             0U
#define LRFDMDM_DEMFRAC0_P15C0_ALLONES                              0x0000FFFFU
#define LRFDMDM_DEMFRAC0_P15C0_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFRAC1
//
//*****************************************************************************
// Field:  [11:0] P27C16 
//
// Downsampler P[27:16] 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFRAC1_P27C16_W                                           12U
#define LRFDMDM_DEMFRAC1_P27C16_M                                   0x00000FFFU
#define LRFDMDM_DEMFRAC1_P27C16_S                                            0U
#define LRFDMDM_DEMFRAC1_P27C16_ALLONES                             0x00000FFFU
#define LRFDMDM_DEMFRAC1_P27C16_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFRAC2
//
//*****************************************************************************
// Field:  [15:0] Q15C0 
//
// Downsampler Q[15:0]. Sample rate of the output signal: Fs_out = Fs_in * P/Q. 
// The hardware requires the resampling factor P/Q to be in the range [1/4, 1], 
//  i.e. only down-sampling with a factor in the range [1,4] is supported. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFRAC2_Q15C0_W                                            16U
#define LRFDMDM_DEMFRAC2_Q15C0_M                                    0x0000FFFFU
#define LRFDMDM_DEMFRAC2_Q15C0_S                                             0U
#define LRFDMDM_DEMFRAC2_Q15C0_ALLONES                              0x0000FFFFU
#define LRFDMDM_DEMFRAC2_Q15C0_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFRAC3
//
//*****************************************************************************
// Field:  [11:0] Q27C16 
//
// Downsampler Q[27:16] 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFRAC3_Q27C16_W                                           12U
#define LRFDMDM_DEMFRAC3_Q27C16_M                                   0x00000FFFU
#define LRFDMDM_DEMFRAC3_Q27C16_S                                            0U
#define LRFDMDM_DEMFRAC3_Q27C16_ALLONES                             0x00000FFFU
#define LRFDMDM_DEMFRAC3_Q27C16_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMCODC1
//
//*****************************************************************************
// Field:  [12:0] COMPIVAL 
//
// Compensation value, I branch 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMCODC1_COMPIVAL_W                                         13U
#define LRFDMDM_DEMCODC1_COMPIVAL_M                                 0x00001FFFU
#define LRFDMDM_DEMCODC1_COMPIVAL_S                                          0U
#define LRFDMDM_DEMCODC1_COMPIVAL_ALLONES                           0x00001FFFU
#define LRFDMDM_DEMCODC1_COMPIVAL_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMCODC2
//
//*****************************************************************************
// Field:  [12:0] COMPQVAL 
//
// Compensation value, Q branch 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMCODC2_COMPQVAL_W                                         13U
#define LRFDMDM_DEMCODC2_COMPQVAL_M                                 0x00001FFFU
#define LRFDMDM_DEMCODC2_COMPQVAL_S                                          0U
#define LRFDMDM_DEMCODC2_COMPQVAL_ALLONES                           0x00001FFFU
#define LRFDMDM_DEMCODC2_COMPQVAL_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFIDC1
//
//*****************************************************************************
// Field:  [12:0] COMPIVAL 
//
// Compensation value for I path 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFIDC1_COMPIVAL_W                                         13U
#define LRFDMDM_DEMFIDC1_COMPIVAL_M                                 0x00001FFFU
#define LRFDMDM_DEMFIDC1_COMPIVAL_S                                          0U
#define LRFDMDM_DEMFIDC1_COMPIVAL_ALLONES                           0x00001FFFU
#define LRFDMDM_DEMFIDC1_COMPIVAL_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFIDC2
//
//*****************************************************************************
// Field:  [12:0] COMPQVAL 
//
// Compensation value for Q path 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFIDC2_COMPQVAL_W                                         13U
#define LRFDMDM_DEMFIDC2_COMPQVAL_M                                 0x00001FFFU
#define LRFDMDM_DEMFIDC2_COMPQVAL_S                                          0U
#define LRFDMDM_DEMFIDC2_COMPQVAL_ALLONES                           0x00001FFFU
#define LRFDMDM_DEMFIDC2_COMPQVAL_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMFIFE1
//
//*****************************************************************************
// Field:   [7:0] FOCFBREGVAL 
//
// Value for feed-back compensation point (signed) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMFIFE1_FOCFBREGVAL_W                                       8U
#define LRFDMDM_DEMFIFE1_FOCFBREGVAL_M                              0x000000FFU
#define LRFDMDM_DEMFIFE1_FOCFBREGVAL_S                                       0U
#define LRFDMDM_DEMFIFE1_FOCFBREGVAL_ALLONES                        0x000000FFU
#define LRFDMDM_DEMFIFE1_FOCFBREGVAL_ALLZEROS                       0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMAFC0
//
//*****************************************************************************
// Field:   [7:0] COMPVAL 
//
// Value for manual compensation (signed) 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFC0_COMPVAL_W                                           8U
#define LRFDMDM_DEMMAFC0_COMPVAL_M                                  0x000000FFU
#define LRFDMDM_DEMMAFC0_COMPVAL_S                                           0U
#define LRFDMDM_DEMMAFC0_COMPVAL_ALLONES                            0x000000FFU
#define LRFDMDM_DEMMAFC0_COMPVAL_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMMAFI4
//
//*****************************************************************************
// Field:   [7:0] TERMVAL 
//
// Input value to terminate matched filter with. Writing to this register 
// triggers the termination. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMMAFI4_TERMVAL_W                                           8U
#define LRFDMDM_DEMMAFI4_TERMVAL_M                                  0x000000FFU
#define LRFDMDM_DEMMAFI4_TERMVAL_S                                           0U
#define LRFDMDM_DEMMAFI4_TERMVAL_ALLONES                            0x000000FFU
#define LRFDMDM_DEMMAFI4_TERMVAL_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMSWIMBAL
//
//*****************************************************************************
// Field:  [15:8] IMBALB 
//
// DC imbalance in sync word B, applied via SWQU upon C1BE correlator A peak 
// event 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMSWIMBAL_IMBALB_W                                          8U
#define LRFDMDM_DEMSWIMBAL_IMBALB_M                                 0x0000FF00U
#define LRFDMDM_DEMSWIMBAL_IMBALB_S                                          8U
#define LRFDMDM_DEMSWIMBAL_IMBALB_ALLONES                           0x0000FF00U
#define LRFDMDM_DEMSWIMBAL_IMBALB_ALLZEROS                          0x00000000U

// Field:   [7:0] IMBALA 
//
// DC imbalance in sync word A, applied via SWQU upon C1BE correlator B peak 
// event 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMSWIMBAL_IMBALA_W                                          8U
#define LRFDMDM_DEMSWIMBAL_IMBALA_M                                 0x000000FFU
#define LRFDMDM_DEMSWIMBAL_IMBALA_S                                          0U
#define LRFDMDM_DEMSWIMBAL_IMBALA_ALLONES                           0x000000FFU
#define LRFDMDM_DEMSWIMBAL_IMBALA_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMSOFTPDIFF
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Replaces PDIFF output when in Soft PDIFF Mode. Can be used for manually 
// feeding samples (e.g. on-off-keying (OOK) samples from RFE) into the 
// demodulator decode stage. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMSOFTPDIFF_VAL_W                                           8U
#define LRFDMDM_DEMSOFTPDIFF_VAL_M                                  0x000000FFU
#define LRFDMDM_DEMSOFTPDIFF_VAL_S                                           0U
#define LRFDMDM_DEMSOFTPDIFF_VAL_ALLONES                            0x000000FFU
#define LRFDMDM_DEMSOFTPDIFF_VAL_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMDEBUG
//
//*****************************************************************************
// Field:  [11:9] LOOPBACKPIN 
//
// Choose which GPI pin is connected to loopback 
// ENUMs: 
// GPI7                     GPI7 connected to loopback 
// GPI6                     GPI6 connected to loopback 
// GPI5                     GPI5 connected to loopback 
// GPI4                     GPI4 connected to loopback 
// GPI3                     GPI3 connected to loopback 
// GPI2                     GPI2 connected to loopback 
// GPI1                     GPI1 connected to loopback 
// GPI0                     GPI0 connected to loopback 
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_W                                       3U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_M                              0x00000E00U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_S                                       9U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI7                           0x00000E00U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI6                           0x00000C00U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI5                           0x00000A00U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI4                           0x00000800U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI3                           0x00000600U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI2                           0x00000400U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI1                           0x00000200U
#define LRFDMDM_DEMDEBUG_LOOPBACKPIN_GPI0                           0x00000000U

// Field:     [8] DECSTAGETRIGGER 
//
// Set high to trigger event to S2R module. Need to be written low again (no HW 
// clear) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMDEBUG_DECSTAGETRIGGER                            0x00000100U
#define LRFDMDM_DEMDEBUG_DECSTAGETRIGGER_M                          0x00000100U
#define LRFDMDM_DEMDEBUG_DECSTAGETRIGGER_S                                   8U
#define LRFDMDM_DEMDEBUG_DECSTAGETRIGGER_ONE                        0x00000100U
#define LRFDMDM_DEMDEBUG_DECSTAGETRIGGER_ZERO                       0x00000000U

// Field:   [7:5] DECSTAGEDEBUG 
//
// Selects which decode stage signal source to dump for debugging via S2R 
// module. 
// The decode stage samples are signed 8-bit samples, 
// packed into 32-bit words with the oldest sample as the most significant 
// byte. 
// ENUMs: 
// SOFD                     Dump SOFD output samples 
// STIM                     Dump STIM output samples 
// MAFC                     Dump MAFC output samples 
// C1BE                     Dump C1BE correlator A value (truncated to 8 LSBs 
//                          only, may overflow if correlator value is 
//                          +128). 
// MAFI                     Dump MAFI output samples 
// FIFE                     Dump PDIF output samples 
// PDIF                     Dump PDIF output samples 
// NOSEL                    No source selected 
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_W                                     3U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_M                            0x000000E0U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_S                                     5U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_SOFD                         0x000000E0U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_STIM                         0x000000C0U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_MAFC                         0x000000A0U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_C1BE                         0x00000080U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_MAFI                         0x00000060U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_FIFE                         0x00000040U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_PDIF                         0x00000020U
#define LRFDMDM_DEMDEBUG_DECSTAGEDEBUG_NOSEL                        0x00000000U

// Field:     [4] FRONTENDTRIGGER 
//
// Set high to trigger event to S2R module. Need to be written low again (no HW 
// clear) 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMDEBUG_FRONTENDTRIGGER                            0x00000010U
#define LRFDMDM_DEMDEBUG_FRONTENDTRIGGER_M                          0x00000010U
#define LRFDMDM_DEMDEBUG_FRONTENDTRIGGER_S                                   4U
#define LRFDMDM_DEMDEBUG_FRONTENDTRIGGER_ONE                        0x00000010U
#define LRFDMDM_DEMDEBUG_FRONTENDTRIGGER_ZERO                       0x00000000U

// Field:   [3:1] FRONTENDDEBUG 
//
// Selects which front-end stage signal source to dump for debugging via S2R 
// module. 
// The front-end stage samples are signed 16-bit samples from both I and Q 
// signal path, 
// packed together into 32-bit words with the I sample as the 16 MSB and Q 
// sample as the 16 LSB. 
// ENUMs: 
// FIDC                     Dump FRAC output samples 
// FRAC                     Dump FRAC output samples 
// CHFI                     Dump CHFI output samples 
// BDE2                     Dump BDE2 output samples 
// FEXB2                    Dump FEXB output #2 samples, as selected by 
//                          DEMFEXB0.OUT2SRCSEL register 
// BDE1                     Dump BDE1 output samples 
// IQMC                     Dump IQMC output samples 
// NOSEL                    No source selected 
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_W                                     3U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_M                            0x0000000EU
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_S                                     1U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_FIDC                         0x0000000EU
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_FRAC                         0x0000000CU
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_CHFI                         0x0000000AU
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_BDE2                         0x00000008U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_FEXB2                        0x00000006U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_BDE1                         0x00000004U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_IQMC                         0x00000002U
#define LRFDMDM_DEMDEBUG_FRONTENDDEBUG_NOSEL                        0x00000000U

// Field:     [0] LOOPBACKMODE 
//
// Enables loopback mode 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMDEBUG_LOOPBACKMODE                               0x00000001U
#define LRFDMDM_DEMDEBUG_LOOPBACKMODE_M                             0x00000001U
#define LRFDMDM_DEMDEBUG_LOOPBACKMODE_S                                      0U
#define LRFDMDM_DEMDEBUG_LOOPBACKMODE_ONE                           0x00000001U
#define LRFDMDM_DEMDEBUG_LOOPBACKMODE_ZERO                          0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITCTRL
//
//*****************************************************************************
// Field:   [7:6] METRSEL 
//
// Selects which HW module is connected to viterbi decoder 
// ENUMs: 
// MLSE                     Use MLSE Metrics 
// SOFD                     Use SOFD Metrics 
// PHAC                     Use PHAC Metrics 
// MET5M                    Use 5Mbps Metrics 
#define LRFDMDM_VITCTRL_METRSEL_W                                            2U
#define LRFDMDM_VITCTRL_METRSEL_M                                   0x000000C0U
#define LRFDMDM_VITCTRL_METRSEL_S                                            6U
#define LRFDMDM_VITCTRL_METRSEL_MLSE                                0x000000C0U
#define LRFDMDM_VITCTRL_METRSEL_SOFD                                0x00000080U
#define LRFDMDM_VITCTRL_METRSEL_PHAC                                0x00000040U
#define LRFDMDM_VITCTRL_METRSEL_MET5M                               0x00000000U

// Field:   [5:2] APMRDBACKSEL 
//
// Selects the APM to read back via VITAPMRDBACK register. 
// ENUMs: 
// APM7                     View APM 7 
// APM6                     View APM 6 
// APM5                     View APM 5 
// APM4                     View APM 4 
// APM3                     View APM 3 
// APM2                     View APM 2 
// APM1                     View APM 1 
// APM0                     View APM 0 
// NOSEL                    No selection 
#define LRFDMDM_VITCTRL_APMRDBACKSEL_W                                       4U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_M                              0x0000003CU
#define LRFDMDM_VITCTRL_APMRDBACKSEL_S                                       2U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM7                           0x0000003CU
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM6                           0x00000038U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM5                           0x00000034U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM4                           0x00000030U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM3                           0x0000002CU
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM2                           0x00000028U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM1                           0x00000024U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_APM0                           0x00000020U
#define LRFDMDM_VITCTRL_APMRDBACKSEL_NOSEL                          0x00000000U

// Field:     [1] ACSITERATIONS 
//
// Number of iterations per ACS element 
// ENUMs: 
// CODE23                   4 iterations per ACS (4 branches, 2/3 codes) 
// CODE12                   2 iterations per ACS (2 branches, 1/2 codes) 
#define LRFDMDM_VITCTRL_ACSITERATIONS                               0x00000002U
#define LRFDMDM_VITCTRL_ACSITERATIONS_M                             0x00000002U
#define LRFDMDM_VITCTRL_ACSITERATIONS_S                                      1U
#define LRFDMDM_VITCTRL_ACSITERATIONS_CODE23                        0x00000002U
#define LRFDMDM_VITCTRL_ACSITERATIONS_CODE12                        0x00000000U

// Field:     [0] METRICS 
//
// Select Metrics 
// ENUMs: 
// SOFT                     Use soft Metrics (register based) 
// HW                       Use HW metrics as defined by VITCTRL.METRSEL bits 
#define LRFDMDM_VITCTRL_METRICS                                     0x00000001U
#define LRFDMDM_VITCTRL_METRICS_M                                   0x00000001U
#define LRFDMDM_VITCTRL_METRICS_S                                            0U
#define LRFDMDM_VITCTRL_METRICS_SOFT                                0x00000001U
#define LRFDMDM_VITCTRL_METRICS_HW                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITCOMPUTE
//
//*****************************************************************************
// Field:     [0] START 
//
// Initiates a compute cycle 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_VITCOMPUTE_START                                    0x00000001U
#define LRFDMDM_VITCOMPUTE_START_M                                  0x00000001U
#define LRFDMDM_VITCOMPUTE_START_S                                           0U
#define LRFDMDM_VITCOMPUTE_START_ONE                                0x00000001U
#define LRFDMDM_VITCOMPUTE_START_ZERO                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITAPMRDBACK
//
//*****************************************************************************
// Field:   [9:0] VALUE 
//
// APM for element i (selected in VITCTRL register). 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITAPMRDBACK_VALUE_W                                        10U
#define LRFDMDM_VITAPMRDBACK_VALUE_M                                0x000003FFU
#define LRFDMDM_VITAPMRDBACK_VALUE_S                                         0U
#define LRFDMDM_VITAPMRDBACK_VALUE_ALLONES                          0x000003FFU
#define LRFDMDM_VITAPMRDBACK_VALUE_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITSTATE
//
//*****************************************************************************
// Field:   [2:0] VALUE 
//
// Current Winning State 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITSTATE_VALUE_W                                             3U
#define LRFDMDM_VITSTATE_VALUE_M                                    0x00000007U
#define LRFDMDM_VITSTATE_VALUE_S                                             0U
#define LRFDMDM_VITSTATE_VALUE_ALLONES                              0x00000007U
#define LRFDMDM_VITSTATE_VALUE_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITBRMETRIC10
//
//*****************************************************************************
// Field:  [15:8] MET1 
//
// Branch Metric 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC10_MET1_W                                         8U
#define LRFDMDM_VITBRMETRIC10_MET1_M                                0x0000FF00U
#define LRFDMDM_VITBRMETRIC10_MET1_S                                         8U
#define LRFDMDM_VITBRMETRIC10_MET1_ALLONES                          0x0000FF00U
#define LRFDMDM_VITBRMETRIC10_MET1_ALLZEROS                         0x00000000U

// Field:   [7:0] MET0 
//
// Branch Metric 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC10_MET0_W                                         8U
#define LRFDMDM_VITBRMETRIC10_MET0_M                                0x000000FFU
#define LRFDMDM_VITBRMETRIC10_MET0_S                                         0U
#define LRFDMDM_VITBRMETRIC10_MET0_ALLONES                          0x000000FFU
#define LRFDMDM_VITBRMETRIC10_MET0_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITBRMETRIC32
//
//*****************************************************************************
// Field:  [15:8] MET3 
//
// Branch Metric 3 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC32_MET3_W                                         8U
#define LRFDMDM_VITBRMETRIC32_MET3_M                                0x0000FF00U
#define LRFDMDM_VITBRMETRIC32_MET3_S                                         8U
#define LRFDMDM_VITBRMETRIC32_MET3_ALLONES                          0x0000FF00U
#define LRFDMDM_VITBRMETRIC32_MET3_ALLZEROS                         0x00000000U

// Field:   [7:0] MET2 
//
// Branch Metric 2 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC32_MET2_W                                         8U
#define LRFDMDM_VITBRMETRIC32_MET2_M                                0x000000FFU
#define LRFDMDM_VITBRMETRIC32_MET2_S                                         0U
#define LRFDMDM_VITBRMETRIC32_MET2_ALLONES                          0x000000FFU
#define LRFDMDM_VITBRMETRIC32_MET2_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITBRMETRIC54
//
//*****************************************************************************
// Field:  [15:8] MET5 
//
// Branch Metric 5 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC54_MET5_W                                         8U
#define LRFDMDM_VITBRMETRIC54_MET5_M                                0x0000FF00U
#define LRFDMDM_VITBRMETRIC54_MET5_S                                         8U
#define LRFDMDM_VITBRMETRIC54_MET5_ALLONES                          0x0000FF00U
#define LRFDMDM_VITBRMETRIC54_MET5_ALLZEROS                         0x00000000U

// Field:   [7:0] MET4 
//
// Branch Metric 4 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC54_MET4_W                                         8U
#define LRFDMDM_VITBRMETRIC54_MET4_M                                0x000000FFU
#define LRFDMDM_VITBRMETRIC54_MET4_S                                         0U
#define LRFDMDM_VITBRMETRIC54_MET4_ALLONES                          0x000000FFU
#define LRFDMDM_VITBRMETRIC54_MET4_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_VITBRMETRIC76
//
//*****************************************************************************
// Field:  [15:8] MET7 
//
// Branch Metric 7 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC76_MET7_W                                         8U
#define LRFDMDM_VITBRMETRIC76_MET7_M                                0x0000FF00U
#define LRFDMDM_VITBRMETRIC76_MET7_S                                         8U
#define LRFDMDM_VITBRMETRIC76_MET7_ALLONES                          0x0000FF00U
#define LRFDMDM_VITBRMETRIC76_MET7_ALLZEROS                         0x00000000U

// Field:   [7:0] MET6 
//
// Branch Metric 6 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_VITBRMETRIC76_MET6_W                                         8U
#define LRFDMDM_VITBRMETRIC76_MET6_M                                0x000000FFU
#define LRFDMDM_VITBRMETRIC76_MET6_S                                         0U
#define LRFDMDM_VITBRMETRIC76_MET6_ALLONES                          0x000000FFU
#define LRFDMDM_VITBRMETRIC76_MET6_ALLZEROS                         0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMCTL
//
//*****************************************************************************
// Field:  [13:8] CPTSRC 
//
// Selects bit number from event bus for a counter capture. Event number in 
// range 0 to 63 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_TIMCTL_CPTSRC_W                                              6U
#define LRFDMDM_TIMCTL_CPTSRC_M                                     0x00003F00U
#define LRFDMDM_TIMCTL_CPTSRC_S                                              8U
#define LRFDMDM_TIMCTL_CPTSRC_ALLONES                               0x00003F00U
#define LRFDMDM_TIMCTL_CPTSRC_ALLZEROS                              0x00000000U

// Field:     [7] CPTCTL 
//
// Enable counter capture on event.  Upon a capture event, the counter value 
// will be captured in TIMCAPT register. 
// ENUMs: 
// EN                       Enable capture mode for counter 
// DIS                      Disable capture mode for counter 
#define LRFDMDM_TIMCTL_CPTCTL                                       0x00000080U
#define LRFDMDM_TIMCTL_CPTCTL_M                                     0x00000080U
#define LRFDMDM_TIMCTL_CPTCTL_S                                              7U
#define LRFDMDM_TIMCTL_CPTCTL_EN                                    0x00000080U
#define LRFDMDM_TIMCTL_CPTCTL_DIS                                   0x00000000U

// Field:   [6:5] CNTRSRC 
//
// Select event source for counter 
// ENUMs: 
// CLK4BAUDF                Use 4xBaud flushed event 
// CLK4BAUD                 Use 4xBaud event 
// CLKBAUD                  Use baud event 
// CLK                      Use clock 
#define LRFDMDM_TIMCTL_CNTRSRC_W                                             2U
#define LRFDMDM_TIMCTL_CNTRSRC_M                                    0x00000060U
#define LRFDMDM_TIMCTL_CNTRSRC_S                                             5U
#define LRFDMDM_TIMCTL_CNTRSRC_CLK4BAUDF                            0x00000060U
#define LRFDMDM_TIMCTL_CNTRSRC_CLK4BAUD                             0x00000040U
#define LRFDMDM_TIMCTL_CNTRSRC_CLKBAUD                              0x00000020U
#define LRFDMDM_TIMCTL_CNTRSRC_CLK                                  0x00000000U

// Field:     [4] CNTRCLR 
//
// Clear counter value in TIMCNT to zero when this bit is set to 1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_TIMCTL_CNTRCLR                                      0x00000010U
#define LRFDMDM_TIMCTL_CNTRCLR_M                                    0x00000010U
#define LRFDMDM_TIMCTL_CNTRCLR_S                                             4U
#define LRFDMDM_TIMCTL_CNTRCLR_ONE                                  0x00000010U
#define LRFDMDM_TIMCTL_CNTRCLR_ZERO                                 0x00000000U

// Field:     [3] CNTRCTL 
//
// Enable 16-bit counter when set to 1. The counter will continue from its 
// current value. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_TIMCTL_CNTRCTL                                      0x00000008U
#define LRFDMDM_TIMCTL_CNTRCTL_M                                    0x00000008U
#define LRFDMDM_TIMCTL_CNTRCTL_S                                             3U
#define LRFDMDM_TIMCTL_CNTRCTL_ONE                                  0x00000008U
#define LRFDMDM_TIMCTL_CNTRCTL_ZERO                                 0x00000000U

// Field:   [2:1] TIMSRC 
//
// Select timer tick source for timer 
// ENUMs: 
// CLK4BAUDF                4xBaud flushed 
// CLK4BAUD                 4xBaud 
// CLKBAUD                  Baud 
// CLK                      Clock 
#define LRFDMDM_TIMCTL_TIMSRC_W                                              2U
#define LRFDMDM_TIMCTL_TIMSRC_M                                     0x00000006U
#define LRFDMDM_TIMCTL_TIMSRC_S                                              1U
#define LRFDMDM_TIMCTL_TIMSRC_CLK4BAUDF                             0x00000006U
#define LRFDMDM_TIMCTL_TIMSRC_CLK4BAUD                              0x00000004U
#define LRFDMDM_TIMCTL_TIMSRC_CLKBAUD                               0x00000002U
#define LRFDMDM_TIMCTL_TIMSRC_CLK                                   0x00000000U

// Field:     [0] TIMCTL 
//
// Enable 16-bit timer. It will generate a timer interrupt after TIMPER timer 
// ticks. 
// Note that the internal timer value is not readable from the MCE. If this is 
// needed the counter should be used instead of the timer. 
// ENUMs: 
// EN                       Will enable timer 
// DIS                      Will disable timer and clear internal timer value 
#define LRFDMDM_TIMCTL_TIMCTL                                       0x00000001U
#define LRFDMDM_TIMCTL_TIMCTL_M                                     0x00000001U
#define LRFDMDM_TIMCTL_TIMCTL_S                                              0U
#define LRFDMDM_TIMCTL_TIMCTL_EN                                    0x00000001U
#define LRFDMDM_TIMCTL_TIMCTL_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMINC
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Programmable counter increment. For each counter event: TIMCNT + 1). 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_TIMINC_VAL_W                                                16U
#define LRFDMDM_TIMINC_VAL_M                                        0x0000FFFFU
#define LRFDMDM_TIMINC_VAL_S                                                 0U
#define LRFDMDM_TIMINC_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_TIMINC_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMPER
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Configurable 16 bit period that can be used for either the timer or the 
// counter. 
// In timer context, when timer value reach the timer period (i.e. it expires) 
// a TIMER_IRQ event will occur, 
// and the timer will restart from zero (until the timer is manually disabled). 
// In counter context, a COUNTER_IRQ event will occur when the counter is equal 
// to or higher than the period value. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_TIMPER_VAL_W                                                16U
#define LRFDMDM_TIMPER_VAL_M                                        0x0000FFFFU
#define LRFDMDM_TIMPER_VAL_S                                                 0U
#define LRFDMDM_TIMPER_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_TIMPER_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMCNT
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// 16 bit counter value that can be read by the MCE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_TIMCNT_VAL_W                                                16U
#define LRFDMDM_TIMCNT_VAL_M                                        0x0000FFFFU
#define LRFDMDM_TIMCNT_VAL_S                                                 0U
#define LRFDMDM_TIMCNT_VAL_ALLONES                                  0x0000FFFFU
#define LRFDMDM_TIMCNT_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMCAPT
//
//*****************************************************************************
// Field:  [15:0] VALUE 
//
// Captured value of counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_TIMCAPT_VALUE_W                                             16U
#define LRFDMDM_TIMCAPT_VALUE_M                                     0x0000FFFFU
#define LRFDMDM_TIMCAPT_VALUE_S                                              0U
#define LRFDMDM_TIMCAPT_VALUE_ALLONES                               0x0000FFFFU
#define LRFDMDM_TIMCAPT_VALUE_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_TIMEBASE
//
//*****************************************************************************
// Field:     [0] FLUSH 
//
// Starts a flushing process 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_TIMEBASE_FLUSH                                      0x00000001U
#define LRFDMDM_TIMEBASE_FLUSH_M                                    0x00000001U
#define LRFDMDM_TIMEBASE_FLUSH_S                                             0U
#define LRFDMDM_TIMEBASE_FLUSH_ONE                                  0x00000001U
#define LRFDMDM_TIMEBASE_FLUSH_ZERO                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_COUNT1IN
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Input data, which we shall find the number of 1's in 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_COUNT1IN_VAL_W                                              16U
#define LRFDMDM_COUNT1IN_VAL_M                                      0x0000FFFFU
#define LRFDMDM_COUNT1IN_VAL_S                                               0U
#define LRFDMDM_COUNT1IN_VAL_ALLONES                                0x0000FFFFU
#define LRFDMDM_COUNT1IN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_COUNT1RES
//
//*****************************************************************************
// Field:   [4:0] VAL 
//
// Number of 1's in the COUNT1IN register 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_COUNT1RES_VAL_W                                              5U
#define LRFDMDM_COUNT1RES_VAL_M                                     0x0000001FU
#define LRFDMDM_COUNT1RES_VAL_S                                              0U
#define LRFDMDM_COUNT1RES_VAL_ALLONES                               0x0000001FU
#define LRFDMDM_COUNT1RES_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_BRMACC1
//
//*****************************************************************************
// Field:  [15:8] METRIC01 
//
// Metric to 01 (-1 +1) symbol. Immediately calculated when BRMACC0 register is 
// written. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BRMACC1_METRIC01_W                                           8U
#define LRFDMDM_BRMACC1_METRIC01_M                                  0x0000FF00U
#define LRFDMDM_BRMACC1_METRIC01_S                                           8U
#define LRFDMDM_BRMACC1_METRIC01_ALLONES                            0x0000FF00U
#define LRFDMDM_BRMACC1_METRIC01_ALLZEROS                           0x00000000U

// Field:   [7:0] METRIC00 
//
// Metric to 00 (-1 -1) symbol. Immediately calculated when BRMACC0 register is 
// written. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BRMACC1_METRIC00_W                                           8U
#define LRFDMDM_BRMACC1_METRIC00_M                                  0x000000FFU
#define LRFDMDM_BRMACC1_METRIC00_S                                           0U
#define LRFDMDM_BRMACC1_METRIC00_ALLONES                            0x000000FFU
#define LRFDMDM_BRMACC1_METRIC00_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_BRMACC2
//
//*****************************************************************************
// Field:  [15:8] METRIC11 
//
// Metric to 11 (+1 +1) symbol. Immediately calculated when BRMACC0 register is 
// written. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BRMACC2_METRIC11_W                                           8U
#define LRFDMDM_BRMACC2_METRIC11_M                                  0x0000FF00U
#define LRFDMDM_BRMACC2_METRIC11_S                                           8U
#define LRFDMDM_BRMACC2_METRIC11_ALLONES                            0x0000FF00U
#define LRFDMDM_BRMACC2_METRIC11_ALLZEROS                           0x00000000U

// Field:   [7:0] METRIC10 
//
// Metric to 10 (+1 -1) symbol. Immediately calculated when BRMACC0 register is 
// written. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_BRMACC2_METRIC10_W                                           8U
#define LRFDMDM_BRMACC2_METRIC10_M                                  0x000000FFU
#define LRFDMDM_BRMACC2_METRIC10_S                                           0U
#define LRFDMDM_BRMACC2_METRIC10_ALLONES                            0x000000FFU
#define LRFDMDM_BRMACC2_METRIC10_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MCETRCCTRL
//
//*****************************************************************************
// Field:     [0] SEND 
//
// Sends a command to the tracer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_MCETRCCTRL_SEND                                     0x00000001U
#define LRFDMDM_MCETRCCTRL_SEND_M                                   0x00000001U
#define LRFDMDM_MCETRCCTRL_SEND_S                                            0U
#define LRFDMDM_MCETRCCTRL_SEND_ONE                                 0x00000001U
#define LRFDMDM_MCETRCCTRL_SEND_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MCETRCSTAT
//
//*****************************************************************************
// Field:     [0] BUSY 
//
// Checks if the tracer is busy 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_MCETRCSTAT_BUSY                                     0x00000001U
#define LRFDMDM_MCETRCSTAT_BUSY_M                                   0x00000001U
#define LRFDMDM_MCETRCSTAT_BUSY_S                                            0U
#define LRFDMDM_MCETRCSTAT_BUSY_ONE                                 0x00000001U
#define LRFDMDM_MCETRCSTAT_BUSY_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MCETRCCMD
//
//*****************************************************************************
// Field:   [9:8] PARCNT 
//
// Number of parameters 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MCETRCCMD_PARCNT_W                                           2U
#define LRFDMDM_MCETRCCMD_PARCNT_M                                  0x00000300U
#define LRFDMDM_MCETRCCMD_PARCNT_S                                           8U
#define LRFDMDM_MCETRCCMD_PARCNT_ALLONES                            0x00000300U
#define LRFDMDM_MCETRCCMD_PARCNT_ALLZEROS                           0x00000000U

// Field:   [7:0] PKTHDR 
//
// Packet header 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MCETRCCMD_PKTHDR_W                                           8U
#define LRFDMDM_MCETRCCMD_PKTHDR_M                                  0x000000FFU
#define LRFDMDM_MCETRCCMD_PKTHDR_S                                           0U
#define LRFDMDM_MCETRCCMD_PKTHDR_ALLONES                            0x000000FFU
#define LRFDMDM_MCETRCCMD_PKTHDR_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MCETRCPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MCETRCPAR0_VAL_W                                            16U
#define LRFDMDM_MCETRCPAR0_VAL_M                                    0x0000FFFFU
#define LRFDMDM_MCETRCPAR0_VAL_S                                             0U
#define LRFDMDM_MCETRCPAR0_VAL_ALLONES                              0x0000FFFFU
#define LRFDMDM_MCETRCPAR0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_MCETRCPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_MCETRCPAR1_VAL_W                                            16U
#define LRFDMDM_MCETRCPAR1_VAL_M                                    0x0000FFFFU
#define LRFDMDM_MCETRCPAR1_VAL_S                                             0U
#define LRFDMDM_MCETRCPAR1_VAL_ALLONES                              0x0000FFFFU
#define LRFDMDM_MCETRCPAR1_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RDCAPT0
//
//*****************************************************************************
// Field:     [5] CHFI 
//
// Capture CHFI output samples into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_CHFI                                        0x00000020U
#define LRFDMDM_RDCAPT0_CHFI_M                                      0x00000020U
#define LRFDMDM_RDCAPT0_CHFI_S                                               5U
#define LRFDMDM_RDCAPT0_CHFI_ONE                                    0x00000020U
#define LRFDMDM_RDCAPT0_CHFI_ZERO                                   0x00000000U

// Field:     [4] BDE2 
//
// Capture BDE2 output samples into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_BDE2                                        0x00000010U
#define LRFDMDM_RDCAPT0_BDE2_M                                      0x00000010U
#define LRFDMDM_RDCAPT0_BDE2_S                                               4U
#define LRFDMDM_RDCAPT0_BDE2_ONE                                    0x00000010U
#define LRFDMDM_RDCAPT0_BDE2_ZERO                                   0x00000000U

// Field:     [3] FIDC 
//
// Capture FIDC output samples into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_FIDC                                        0x00000008U
#define LRFDMDM_RDCAPT0_FIDC_M                                      0x00000008U
#define LRFDMDM_RDCAPT0_FIDC_S                                               3U
#define LRFDMDM_RDCAPT0_FIDC_ONE                                    0x00000008U
#define LRFDMDM_RDCAPT0_FIDC_ZERO                                   0x00000000U

// Field:     [2] FRAC 
//
// Capture FRAC output samples into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_FRAC                                        0x00000004U
#define LRFDMDM_RDCAPT0_FRAC_M                                      0x00000004U
#define LRFDMDM_RDCAPT0_FRAC_S                                               2U
#define LRFDMDM_RDCAPT0_FRAC_ONE                                    0x00000004U
#define LRFDMDM_RDCAPT0_FRAC_ZERO                                   0x00000000U

// Field:     [1] MGEX 
//
// Capture MGE1 and MGE2 output values into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_MGEX                                        0x00000002U
#define LRFDMDM_RDCAPT0_MGEX_M                                      0x00000002U
#define LRFDMDM_RDCAPT0_MGEX_S                                               1U
#define LRFDMDM_RDCAPT0_MGEX_ONE                                    0x00000002U
#define LRFDMDM_RDCAPT0_MGEX_ZERO                                   0x00000000U

// Field:     [0] CODC 
//
// Capture CODC output samples into FECAPT0 and FECAPT1. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT0_CODC                                        0x00000001U
#define LRFDMDM_RDCAPT0_CODC_M                                      0x00000001U
#define LRFDMDM_RDCAPT0_CODC_S                                               0U
#define LRFDMDM_RDCAPT0_CODC_ONE                                    0x00000001U
#define LRFDMDM_RDCAPT0_CODC_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RDCAPT1
//
//*****************************************************************************
// Field:    [11] C1BEX2 
//
// Capture C1BE B correlation peak x[n-1] value into DSCAPT0 RC register. 
// Capture C1BE B correlation peak value into DSCAPT1 RC register. 
// Capture C1BE B correlation peak x[n+1] value into DSCAPT2 RC register. 
// Capture C1BE B qual value into DSCAPT3 RC register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_C1BEX2                                      0x00000800U
#define LRFDMDM_RDCAPT1_C1BEX2_M                                    0x00000800U
#define LRFDMDM_RDCAPT1_C1BEX2_S                                            11U
#define LRFDMDM_RDCAPT1_C1BEX2_ONE                                  0x00000800U
#define LRFDMDM_RDCAPT1_C1BEX2_ZERO                                 0x00000000U

// Field:    [10] C1BEX1 
//
// Capture C1BE A correlation peak x[n-1] value into DSCAPT0 RC register. 
// Capture C1BE A correlation peak value into DSCAPT1 RC register. 
// Capture C1BE A correlation peak x[n+1] value into DSCAPT2 RC register. 
// Capture C1BE A qual value into DSCAPT3 RC register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_C1BEX1                                      0x00000400U
#define LRFDMDM_RDCAPT1_C1BEX1_M                                    0x00000400U
#define LRFDMDM_RDCAPT1_C1BEX1_S                                            10U
#define LRFDMDM_RDCAPT1_C1BEX1_ONE                                  0x00000400U
#define LRFDMDM_RDCAPT1_C1BEX1_ZERO                                 0x00000000U

// Field:     [9] C1BEX0 
//
// Capture C1BE A values into DSCAPT0 RC register 
// Capture C1BE B values into DSCAPT1 RC register 
// Capture C1BE C values into DSCAPT2 RC register 
// Capture C1BE Corr Peak C into DSCAPT3 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_C1BEX0                                      0x00000200U
#define LRFDMDM_RDCAPT1_C1BEX0_M                                    0x00000200U
#define LRFDMDM_RDCAPT1_C1BEX0_S                                             9U
#define LRFDMDM_RDCAPT1_C1BEX0_ONE                                  0x00000200U
#define LRFDMDM_RDCAPT1_C1BEX0_ZERO                                 0x00000000U

// Field:     [8] SOFD 
//
// Capture SOFD soft symbol into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_SOFD                                        0x00000100U
#define LRFDMDM_RDCAPT1_SOFD_M                                      0x00000100U
#define LRFDMDM_RDCAPT1_SOFD_S                                               8U
#define LRFDMDM_RDCAPT1_SOFD_ONE                                    0x00000100U
#define LRFDMDM_RDCAPT1_SOFD_ZERO                                   0x00000000U

// Field:     [7] LQIE 
//
// Capture LQIE value into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_LQIE                                        0x00000080U
#define LRFDMDM_RDCAPT1_LQIE_M                                      0x00000080U
#define LRFDMDM_RDCAPT1_LQIE_S                                               7U
#define LRFDMDM_RDCAPT1_LQIE_ONE                                    0x00000080U
#define LRFDMDM_RDCAPT1_LQIE_ZERO                                   0x00000000U

// Field:     [6] STIM 
//
// Capture STIM Events value into DSCAPT0 RC register bit 50. 
// Capture STIM Delta value into DSCAPT1 RC register bit 3:0. 
// Capture STIM Gardner Error(9:8)  into DSCAPT1 RC register bit 7:6. 
// Capture STIM Gardner Error(7:0)  into DSCAPT2 RC register. 
// Capture STIM output sample into DSCAPT3 RC register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_STIM                                        0x00000040U
#define LRFDMDM_RDCAPT1_STIM_M                                      0x00000040U
#define LRFDMDM_RDCAPT1_STIM_S                                               6U
#define LRFDMDM_RDCAPT1_STIM_ONE                                    0x00000040U
#define LRFDMDM_RDCAPT1_STIM_ZERO                                   0x00000000U

// Field:     [5] FIFE 
//
// Capture FIFE sample into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_FIFE                                        0x00000020U
#define LRFDMDM_RDCAPT1_FIFE_M                                      0x00000020U
#define LRFDMDM_RDCAPT1_FIFE_S                                               5U
#define LRFDMDM_RDCAPT1_FIFE_ONE                                    0x00000020U
#define LRFDMDM_RDCAPT1_FIFE_ZERO                                   0x00000000U

// Field:     [4] PDIF 
//
// Capture PDIF sample into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_PDIF                                        0x00000010U
#define LRFDMDM_RDCAPT1_PDIF_M                                      0x00000010U
#define LRFDMDM_RDCAPT1_PDIF_S                                               4U
#define LRFDMDM_RDCAPT1_PDIF_ONE                                    0x00000010U
#define LRFDMDM_RDCAPT1_PDIF_ZERO                                   0x00000000U

// Field:     [3] CA2P 
//
// Capture CA2P sample into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_CA2P                                        0x00000008U
#define LRFDMDM_RDCAPT1_CA2P_M                                      0x00000008U
#define LRFDMDM_RDCAPT1_CA2P_S                                               3U
#define LRFDMDM_RDCAPT1_CA2P_ONE                                    0x00000008U
#define LRFDMDM_RDCAPT1_CA2P_ZERO                                   0x00000000U

// Field:     [2] MAFI 
//
// Capture MAFI sample into DSCAPT0 RC register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_MAFI                                        0x00000004U
#define LRFDMDM_RDCAPT1_MAFI_M                                      0x00000004U
#define LRFDMDM_RDCAPT1_MAFI_S                                               2U
#define LRFDMDM_RDCAPT1_MAFI_ONE                                    0x00000004U
#define LRFDMDM_RDCAPT1_MAFI_ZERO                                   0x00000000U

// Field:     [1] DSBU 
//
// Capture DSBU read pointer into DSCAPT0 register 
// Capture DSBU write pointer into DSCAPT1 register 
// Capture DSBU average value into DSCAPT2 register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_DSBU                                        0x00000002U
#define LRFDMDM_RDCAPT1_DSBU_M                                      0x00000002U
#define LRFDMDM_RDCAPT1_DSBU_S                                               1U
#define LRFDMDM_RDCAPT1_DSBU_ONE                                    0x00000002U
#define LRFDMDM_RDCAPT1_DSBU_ZERO                                   0x00000000U

// Field:     [0] MLSEBIT 
//
// Capture MLSE bit into DSCAPT0 register 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_RDCAPT1_MLSEBIT                                     0x00000001U
#define LRFDMDM_RDCAPT1_MLSEBIT_M                                   0x00000001U
#define LRFDMDM_RDCAPT1_MLSEBIT_S                                            0U
#define LRFDMDM_RDCAPT1_MLSEBIT_ONE                                 0x00000001U
#define LRFDMDM_RDCAPT1_MLSEBIT_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FECAPT0
//
//*****************************************************************************
// Field:  [12:0] VAL 
//
// Readback value, I channel 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_FECAPT0_VAL_W                                               13U
#define LRFDMDM_FECAPT0_VAL_M                                       0x00001FFFU
#define LRFDMDM_FECAPT0_VAL_S                                                0U
#define LRFDMDM_FECAPT0_VAL_ALLONES                                 0x00001FFFU
#define LRFDMDM_FECAPT0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_FECAPT1
//
//*****************************************************************************
// Field:  [12:0] VAL 
//
// Readback value, Q channel 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_FECAPT1_VAL_W                                               13U
#define LRFDMDM_FECAPT1_VAL_M                                       0x00001FFFU
#define LRFDMDM_FECAPT1_VAL_S                                                0U
#define LRFDMDM_FECAPT1_VAL_ALLONES                                 0x00001FFFU
#define LRFDMDM_FECAPT1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DSCAPT0
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Readback channel 0 after writing to RDCAPT1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DSCAPT0_VAL_W                                                8U
#define LRFDMDM_DSCAPT0_VAL_M                                       0x000000FFU
#define LRFDMDM_DSCAPT0_VAL_S                                                0U
#define LRFDMDM_DSCAPT0_VAL_ALLONES                                 0x000000FFU
#define LRFDMDM_DSCAPT0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DSCAPT1
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Readback channel 1 after writing to RDCAPT1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DSCAPT1_VAL_W                                                8U
#define LRFDMDM_DSCAPT1_VAL_M                                       0x000000FFU
#define LRFDMDM_DSCAPT1_VAL_S                                                0U
#define LRFDMDM_DSCAPT1_VAL_ALLONES                                 0x000000FFU
#define LRFDMDM_DSCAPT1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DSCAPT2
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Readback channel 2 after writing to RDCAPT1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DSCAPT2_VAL_W                                                8U
#define LRFDMDM_DSCAPT2_VAL_M                                       0x000000FFU
#define LRFDMDM_DSCAPT2_VAL_S                                                0U
#define LRFDMDM_DSCAPT2_VAL_ALLONES                                 0x000000FFU
#define LRFDMDM_DSCAPT2_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DSCAPT3
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Readback channel 3 after writing to RDCAPT1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DSCAPT3_VAL_W                                                8U
#define LRFDMDM_DSCAPT3_VAL_M                                       0x000000FFU
#define LRFDMDM_DSCAPT3_VAL_S                                                0U
#define LRFDMDM_DSCAPT3_VAL_ALLONES                                 0x000000FFU
#define LRFDMDM_DSCAPT3_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_DEMSWQU1
//
//*****************************************************************************
// Field:   [9:2] MAFCCOMPVAL 
//
// Frequency Offset value computed by SWQU 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_DEMSWQU1_MAFCCOMPVAL_W                                       8U
#define LRFDMDM_DEMSWQU1_MAFCCOMPVAL_M                              0x000003FCU
#define LRFDMDM_DEMSWQU1_MAFCCOMPVAL_S                                       2U
#define LRFDMDM_DEMSWQU1_MAFCCOMPVAL_ALLONES                        0x000003FCU
#define LRFDMDM_DEMSWQU1_MAFCCOMPVAL_ALLZEROS                       0x00000000U

// Field:     [1] SWSEL 
//
// Shows which sync word had a peak event and was selected for sync word 
// qualification test. 
// This is to tell which sync word was detected when radio operates in receive 
// mode with dual sync word search. 
// ENUMs: 
// B                        The C1BE emitted a correlator B peak event and 
//                          SWQU selected sync word B for qualification 
//                          test 
// A                        The C1BE emitted a correlator A peak event and 
//                          SWQU selected sync word A for qualification 
//                          test (or no SWQU sync word test has been 
//                          performed yet) 
#define LRFDMDM_DEMSWQU1_SWSEL                                      0x00000002U
#define LRFDMDM_DEMSWQU1_SWSEL_M                                    0x00000002U
#define LRFDMDM_DEMSWQU1_SWSEL_S                                             1U
#define LRFDMDM_DEMSWQU1_SWSEL_B                                    0x00000002U
#define LRFDMDM_DEMSWQU1_SWSEL_A                                    0x00000000U

// Field:     [0] SYNCED 
//
// Reads as '1' when the sync word specified by DEMSWQU1.SWSEL has passed 
// qualification, otherwise '0'. 
// Note that the sync word qualification is only performed on MSB portion of 
// the reference vector, 
// as specified in DEMSWQU0.REFLEN register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_DEMSWQU1_SYNCED                                     0x00000001U
#define LRFDMDM_DEMSWQU1_SYNCED_M                                   0x00000001U
#define LRFDMDM_DEMSWQU1_SYNCED_S                                            0U
#define LRFDMDM_DEMSWQU1_SYNCED_ONE                                 0x00000001U
#define LRFDMDM_DEMSWQU1_SYNCED_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_GPOCTRL0
//
//*****************************************************************************
// Field: [15:14] GPO7 
//
// Direct control of MCE_GPO(7) : 
// 00 : FW source 7 
// 01: HW source 7 
// 10: HW source 15 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// TOPSM_WAIT               Output hardware clk 
// SW7                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO7_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO7_M                                     0x0000C000U
#define LRFDMDM_GPOCTRL0_GPO7_S                                             14U
#define LRFDMDM_GPOCTRL0_GPO7_THREE                                 0x0000C000U
#define LRFDMDM_GPOCTRL0_GPO7_TWO                                   0x00008000U
#define LRFDMDM_GPOCTRL0_GPO7_TOPSM_WAIT                            0x00004000U
#define LRFDMDM_GPOCTRL0_GPO7_SW7                                   0x00000000U

// Field: [13:12] GPO6 
//
// Direct control of MCE_GPO(6) : 
// 00 : FW source 6 
// 01: HW source 6 
// 10: HW source 14 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// TRANSPARENT_OUT          The bit is 1 
// SW6                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO6_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO6_M                                     0x00003000U
#define LRFDMDM_GPOCTRL0_GPO6_S                                             12U
#define LRFDMDM_GPOCTRL0_GPO6_THREE                                 0x00003000U
#define LRFDMDM_GPOCTRL0_GPO6_TWO                                   0x00002000U
#define LRFDMDM_GPOCTRL0_GPO6_TRANSPARENT_OUT                       0x00001000U
#define LRFDMDM_GPOCTRL0_GPO6_SW6                                   0x00000000U

// Field: [11:10] GPO5 
//
// Direct control of MCE_GPO(5) : 
// 00 : FW source 5 
// 01: HW source 5 
// 10: HW source 13 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// DEM_OUT_WORD             The bit is 1 
// SW5                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO5_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO5_M                                     0x00000C00U
#define LRFDMDM_GPOCTRL0_GPO5_S                                             10U
#define LRFDMDM_GPOCTRL0_GPO5_THREE                                 0x00000C00U
#define LRFDMDM_GPOCTRL0_GPO5_TWO                                   0x00000800U
#define LRFDMDM_GPOCTRL0_GPO5_DEM_OUT_WORD                          0x00000400U
#define LRFDMDM_GPOCTRL0_GPO5_SW5                                   0x00000000U

// Field:   [9:8] GPO4 
//
// Direct control of MCE_GPO(4) : 
// 00 : FW source 4 
// 01: HW source 4 
// 10: HW source 12 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// CORR_PEAK_C              The bit is 1 
// SW4                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO4_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO4_M                                     0x00000300U
#define LRFDMDM_GPOCTRL0_GPO4_S                                              8U
#define LRFDMDM_GPOCTRL0_GPO4_THREE                                 0x00000300U
#define LRFDMDM_GPOCTRL0_GPO4_TWO                                   0x00000200U
#define LRFDMDM_GPOCTRL0_GPO4_CORR_PEAK_C                           0x00000100U
#define LRFDMDM_GPOCTRL0_GPO4_SW4                                   0x00000000U

// Field:   [7:6] GPO3 
//
// Direct control of MCE_GPO(3) : 
// 00 : FW source 3 
// 01: HW source 3 
// 10: HW source 11 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// CORR_PEAK_B              The bit is 1 
// SW3                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO3_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO3_M                                     0x000000C0U
#define LRFDMDM_GPOCTRL0_GPO3_S                                              6U
#define LRFDMDM_GPOCTRL0_GPO3_THREE                                 0x000000C0U
#define LRFDMDM_GPOCTRL0_GPO3_TWO                                   0x00000080U
#define LRFDMDM_GPOCTRL0_GPO3_CORR_PEAK_B                           0x00000040U
#define LRFDMDM_GPOCTRL0_GPO3_SW3                                   0x00000000U

// Field:   [5:4] GPO2 
//
// Direct control of MCE_GPO(2) : 
// 00 : FW source 2 
// 01: HW source 2 
// 10: HW source 10 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// CORR_PEAK_A              The bit is 1 
// SW2                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO2_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO2_M                                     0x00000030U
#define LRFDMDM_GPOCTRL0_GPO2_S                                              4U
#define LRFDMDM_GPOCTRL0_GPO2_THREE                                 0x00000030U
#define LRFDMDM_GPOCTRL0_GPO2_TWO                                   0x00000020U
#define LRFDMDM_GPOCTRL0_GPO2_CORR_PEAK_A                           0x00000010U
#define LRFDMDM_GPOCTRL0_GPO2_SW2                                   0x00000000U

// Field:   [3:2] GPO1 
//
// Direct control of MCE_GPO(1) : 
// 00 : FW source 1 
// 01: HW source 1 
// 10: HW source 9 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// TWO                      HW source 2 
// HWCLK1                   Output Loopback symbol on pin MDMGPO1 
// SW1                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO1_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO1_M                                     0x0000000CU
#define LRFDMDM_GPOCTRL0_GPO1_S                                              2U
#define LRFDMDM_GPOCTRL0_GPO1_THREE                                 0x0000000CU
#define LRFDMDM_GPOCTRL0_GPO1_TWO                                   0x00000008U
#define LRFDMDM_GPOCTRL0_GPO1_HWCLK1                                0x00000004U
#define LRFDMDM_GPOCTRL0_GPO1_SW1                                   0x00000000U

// Field:   [1:0] GPO0 
//
// Direct control of MCE_GPO(0) : 
// 00 : FW source 0 
// 01: HW source 0 
// 10: HW source 8 
// 11: Reserved 
// ENUMs: 
// THREE                    HW Source 3 
// LOOPBACK                 HW source 2 
// HWCLK0                   Output hardware clock on pin MDMGPO0 
// SW0                      Output GPOCTRL1.SW 
#define LRFDMDM_GPOCTRL0_GPO0_W                                              2U
#define LRFDMDM_GPOCTRL0_GPO0_M                                     0x00000003U
#define LRFDMDM_GPOCTRL0_GPO0_S                                              0U
#define LRFDMDM_GPOCTRL0_GPO0_THREE                                 0x00000003U
#define LRFDMDM_GPOCTRL0_GPO0_LOOPBACK                              0x00000002U
#define LRFDMDM_GPOCTRL0_GPO0_HWCLK0                                0x00000001U
#define LRFDMDM_GPOCTRL0_GPO0_SW0                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_GPOCTRL1
//
//*****************************************************************************
// Field: [15:14] HWCLKSTRETCH 
//
// Control strech for hwclk0 and hwclk1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_GPOCTRL1_HWCLKSTRETCH_W                                      2U
#define LRFDMDM_GPOCTRL1_HWCLKSTRETCH_M                             0x0000C000U
#define LRFDMDM_GPOCTRL1_HWCLKSTRETCH_S                                     14U
#define LRFDMDM_GPOCTRL1_HWCLKSTRETCH_ONE                           0x00004000U
#define LRFDMDM_GPOCTRL1_HWCLKSTRETCH_ZERO                          0x00000000U

// Field: [13:11] HWCLKMUX1 
//
// Select clock source for hwclk1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_GPOCTRL1_HWCLKMUX1_W                                         3U
#define LRFDMDM_GPOCTRL1_HWCLKMUX1_M                                0x00003800U
#define LRFDMDM_GPOCTRL1_HWCLKMUX1_S                                        11U
#define LRFDMDM_GPOCTRL1_HWCLKMUX1_ONE                              0x00000800U
#define LRFDMDM_GPOCTRL1_HWCLKMUX1_ZERO                             0x00000000U

// Field:  [10:8] HWCLKMUX0 
//
// Select clock source for hwclk0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_GPOCTRL1_HWCLKMUX0_W                                         3U
#define LRFDMDM_GPOCTRL1_HWCLKMUX0_M                                0x00000700U
#define LRFDMDM_GPOCTRL1_HWCLKMUX0_S                                         8U
#define LRFDMDM_GPOCTRL1_HWCLKMUX0_ONE                              0x00000100U
#define LRFDMDM_GPOCTRL1_HWCLKMUX0_ZERO                             0x00000000U

// Field:   [7:0] SW 
//
// Software controlled GPO 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDMDM_GPOCTRL1_SW_W                                                8U
#define LRFDMDM_GPOCTRL1_SW_M                                       0x000000FFU
#define LRFDMDM_GPOCTRL1_SW_S                                                0U
#define LRFDMDM_GPOCTRL1_SW_ONE                                     0x00000001U
#define LRFDMDM_GPOCTRL1_SW_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFERSSI
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Current RSSI estimate 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFERSSI_VAL_W                                                8U
#define LRFDMDM_RFERSSI_VAL_M                                       0x000000FFU
#define LRFDMDM_RFERSSI_VAL_S                                                0U
#define LRFDMDM_RFERSSI_VAL_ALLONES                                 0x000000FFU
#define LRFDMDM_RFERSSI_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFEMAXRSSI
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Highest RSSI since start of reception 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFEMAXRSSI_VAL_W                                             8U
#define LRFDMDM_RFEMAXRSSI_VAL_M                                    0x000000FFU
#define LRFDMDM_RFEMAXRSSI_VAL_S                                             0U
#define LRFDMDM_RFEMAXRSSI_VAL_ALLONES                              0x000000FFU
#define LRFDMDM_RFEMAXRSSI_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_RFEDBGAIN
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Current gain setting 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_RFEDBGAIN_VAL_W                                              8U
#define LRFDMDM_RFEDBGAIN_VAL_M                                     0x000000FFU
#define LRFDMDM_RFEDBGAIN_VAL_S                                              0U
#define LRFDMDM_RFEDBGAIN_VAL_ALLONES                               0x000000FFU
#define LRFDMDM_RFEDBGAIN_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYNC0
//
//*****************************************************************************
// Field:  [15:0] SWA15C0 
//
// Sync word A bits 15:0. Sync words shorter than 32 bits must be stored as 
// most signicant bits of sync word A. 
// The sync word is expected to be transmitted/received in LSB to MSB order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYNC0_SWA15C0_W                                             16U
#define LRFDMDM_SYNC0_SWA15C0_M                                     0x0000FFFFU
#define LRFDMDM_SYNC0_SWA15C0_S                                              0U
#define LRFDMDM_SYNC0_SWA15C0_ALLONES                               0x0000FFFFU
#define LRFDMDM_SYNC0_SWA15C0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYNC1
//
//*****************************************************************************
// Field:  [15:0] SWA31C16 
//
// Sync word A bits 31:16. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word A. 
// The sync word is expected to be transmitted/received in LSB to MSB order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYNC1_SWA31C16_W                                            16U
#define LRFDMDM_SYNC1_SWA31C16_M                                    0x0000FFFFU
#define LRFDMDM_SYNC1_SWA31C16_S                                             0U
#define LRFDMDM_SYNC1_SWA31C16_ALLONES                              0x0000FFFFU
#define LRFDMDM_SYNC1_SWA31C16_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYNC2
//
//*****************************************************************************
// Field:  [15:0] SWB15C0 
//
// Sync word B bits 15:0. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word B. 
// The sync word is expected to be transmitted/received in LSB to MSB order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYNC2_SWB15C0_W                                             16U
#define LRFDMDM_SYNC2_SWB15C0_M                                     0x0000FFFFU
#define LRFDMDM_SYNC2_SWB15C0_S                                              0U
#define LRFDMDM_SYNC2_SWB15C0_ALLONES                               0x0000FFFFU
#define LRFDMDM_SYNC2_SWB15C0_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDMDM_O_SYNC3
//
//*****************************************************************************
// Field:  [15:0] SWB31C16 
//
// Sync word B bits 31:16. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word B. 
// The sync word is expected to be transmitted/received in LSB to MSB order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDMDM_SYNC3_SWB31C16_W                                            16U
#define LRFDMDM_SYNC3_SWB31C16_M                                    0x0000FFFFU
#define LRFDMDM_SYNC3_SWB31C16_S                                             0U
#define LRFDMDM_SYNC3_SWB31C16_ALLONES                              0x0000FFFFU
#define LRFDMDM_SYNC3_SWB31C16_ALLZEROS                             0x00000000U


#endif // __LRFDMDM__
