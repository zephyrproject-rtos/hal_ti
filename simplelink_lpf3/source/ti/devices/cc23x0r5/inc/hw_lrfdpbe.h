/******************************************************************************
*  Filename:       hw_lrfdpbe_h
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

#ifndef __HW_LRFDPBE_H__
#define __HW_LRFDPBE_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDPBE component
//
//*****************************************************************************
// Packet Building Engine Enable Register 
#define LRFDPBE_O_ENABLE                                            0x00000000U

// PBE program source select register 
#define LRFDPBE_O_FWSRC                                             0x00000004U

// Packet Building Engine Initialization Register 
#define LRFDPBE_O_INIT                                              0x00000008U

// Packet Building Engine (PBE) Strobe Register 0 
#define LRFDPBE_O_STROBES0                                          0x0000000CU

// Interrupt generate register 
#define LRFDPBE_O_IRQ                                               0x00000010U

// PBE Event Flag Register 0 
#define LRFDPBE_O_EVT0                                              0x00000014U

// PBE Event Flag Register 1 
#define LRFDPBE_O_EVT1                                              0x00000018U

// PBE Event Mask Register 0 
#define LRFDPBE_O_EVTMSK0                                           0x0000001CU

// PBE Event Mask Register 1 
#define LRFDPBE_O_EVTMSK1                                           0x00000020U

// PBE Event Clear Register 0 
#define LRFDPBE_O_EVTCLR0                                           0x00000024U

// PBE Event Mask Register 1 
#define LRFDPBE_O_EVTCLR1                                           0x00000028U

// Packet Building Engine Power-down Register 
#define LRFDPBE_O_PDREQ                                             0x0000002CU

// PBE API Command Register 
#define LRFDPBE_O_API                                               0x00000030U

// PBE-to-MCE Send Data Register 
#define LRFDPBE_O_MCEDATOUT0                                        0x00000034U

// MCE-to-PBE Receive Data Register 
#define LRFDPBE_O_MCEDATIN0                                         0x00000038U

// PBE-to-MCE Send Command Register 
#define LRFDPBE_O_MCECMDOUT                                         0x0000003CU

// MCE-to-PBE Receive Command Register 
#define LRFDPBE_O_MCECMDIN                                          0x00000040U

// Modem API Command Register 
#define LRFDPBE_O_MDMAPI                                            0x00000044U

// Modem Command Status Register 
#define LRFDPBE_O_MDMMSGBOX                                         0x00000048U

// Frequency Offset 
#define LRFDPBE_O_FREQ                                              0x0000004CU

// Link quality indicator 
#define LRFDPBE_O_MDMLQI                                            0x00000050U

// PBE-to-RFE Send Data Register 
#define LRFDPBE_O_RFEDATOUT0                                        0x00000054U

// RFE-to-PBE Receive Data Register 
#define LRFDPBE_O_RFEDATIN0                                         0x00000058U

// PBE-to-RFE Send Command Register 
#define LRFDPBE_O_RFECMDOUT                                         0x0000005CU

// RFE-to-PBE Receive Command Register 
#define LRFDPBE_O_RFECMDIN                                          0x00000060U

// RFE API Command Register 
#define LRFDPBE_O_RFEAPI                                            0x00000064U

// RFE Command Parameter 0 
#define LRFDPBE_O_RFECMDPAR0                                        0x00000068U

// RFE Command Parameter 1 
#define LRFDPBE_O_RFECMDPAR1                                        0x0000006CU

// RFE Command Status and Message Box Register 
#define LRFDPBE_O_RFEMSGBOX                                         0x00000070U

// RSSI Value Register 
#define LRFDPBE_O_RFERSSI                                           0x00000074U

// RSSI Maximum Value Register 
#define LRFDPBE_O_RFERSSIMAX                                        0x00000078U

// RF front-end gain value 
#define LRFDPBE_O_RFERFGAIN                                         0x0000007CU

// Modem Sync Word Register 0 
#define LRFDPBE_O_MDMSYNCAL                                         0x00000080U

// Modem Sync Word Register 1 
#define LRFDPBE_O_MDMSYNCAH                                         0x00000084U

// Modem Sync Word Register 2 
#define LRFDPBE_O_MDMSYNCBL                                         0x00000088U

// Modem Sync Word Register 3 
#define LRFDPBE_O_MDMSYNCBH                                         0x0000008CU

// Modem API Command Parameter 0 
#define LRFDPBE_O_MDMCMDPAR0                                        0x00000090U

// Modem API Command Parameter 1 
#define LRFDPBE_O_MDMCMDPAR1                                        0x00000094U

// Modem API Command Parameter 2 
#define LRFDPBE_O_MDMCMDPAR2                                        0x00000098U

// LFSR 0 Polynomial Definition 
#define LRFDPBE_O_POLY0L                                            0x000000A0U

// LFSR 0 Polynomial Definition 
#define LRFDPBE_O_POLY0H                                            0x000000A4U

// LFSR 1 Polynomial Definition 
#define LRFDPBE_O_POLY1L                                            0x000000A8U

// LFSR 1 Polynomial Definition 
#define LRFDPBE_O_POLY1H                                            0x000000ACU

// Packet Handler Accelerator Config Register 
#define LRFDPBE_O_PHACFG                                            0x000000B0U

// FIFO configuration register 
#define LRFDPBE_O_FCFG0                                             0x000000B4U

// FIFO configuration register 
#define LRFDPBE_O_FCFG1                                             0x000000B8U

// FIFO configuration register 
#define LRFDPBE_O_FCFG2                                             0x000000BCU

// FIFO configuration register 
#define LRFDPBE_O_FCFG3                                             0x000000C0U

// FIFO configuration register 
#define LRFDPBE_O_FCFG4                                             0x000000C4U

// FIFO configuration register 
#define LRFDPBE_O_FCFG5                                             0x000000C8U

// FIFO write pointer 
#define LRFDPBE_O_RXFWBTHRS                                         0x000000CCU

// FIFO read pointer 
#define LRFDPBE_O_RXFRBTHRS                                         0x000000D0U

// FIFO write pointer 
#define LRFDPBE_O_TXFWBTHRS                                         0x000000D4U

// FIFO read pointer 
#define LRFDPBE_O_TXFRBTHRS                                         0x000000D8U

// PBE Timer Control Register 
#define LRFDPBE_O_TIMCTL                                            0x000000DCU

// Prescaler setting for timer 0 and timer 1 
#define LRFDPBE_O_TIMPRE                                            0x000000E0U

// PBE Timer Period Configuration 
#define LRFDPBE_O_TIMPER0                                           0x000000E4U

// PBE Timer Period Configuration 
#define LRFDPBE_O_TIMPER1                                           0x000000E8U

// PBE Counter Capture Value 
#define LRFDPBE_O_TIMCAPT0                                          0x000000ECU

// PBE Counter Capture Value 
#define LRFDPBE_O_TIMCAPT1                                          0x000000F0U

// PBE Tracer Send Trigger Register 
#define LRFDPBE_O_TRCCTL                                            0x00000100U

// PBE Tracer Status Register 
#define LRFDPBE_O_TRCSTAT                                           0x00000104U

// PBE Tracer Commmand Register 
#define LRFDPBE_O_TRCCMD                                            0x00000108U

// PBE Tracer Command Parameter Register 0 
#define LRFDPBE_O_TRCPAR0                                           0x0000010CU

// PBE Tracer Command Parameter Register 1 
#define LRFDPBE_O_TRCPAR1                                           0x00000110U

// PBE Direct GPO control register 
#define LRFDPBE_O_GPOCTRL                                           0x00000114U

// Modem FIFO Write Register 
#define LRFDPBE_O_MDMFWR                                            0x00000118U

// Modem FIFO Read Register 
#define LRFDPBE_O_MDMFRD                                            0x0000011CU

// Modem FIFO Write Configuration 
#define LRFDPBE_O_MDMFWRCTL                                         0x00000120U

// Modem FIFO Read Configuration 
#define LRFDPBE_O_MDMFRDCTL                                         0x00000124U

// Modem FIFO Configuration for watermark thresholds 
#define LRFDPBE_O_MDMFCFG                                           0x00000128U

// Modem FIFO Status Flags 
#define LRFDPBE_O_MDMFSTA                                           0x0000012CU

// Packet Handler Accelerator Status 
#define LRFDPBE_O_PHASTA                                            0x00000134U

// LFSR 0 Current Value 
#define LRFDPBE_O_LFSR0L                                            0x00000138U

// LFSR 0 Current Value 
#define LRFDPBE_O_LFSR0H                                            0x0000013CU

// LFSR 0 Current Value, Bit-reversed 
#define LRFDPBE_O_LFSR0BRL                                          0x00000140U

// LFSR 0 Current Value, Bit-reversed 
#define LRFDPBE_O_LFSR0BRH                                          0x00000144U

// LFSR 1 Current Value 
#define LRFDPBE_O_LFSR1L                                            0x00000148U

// LFSR 1 Current Value 
#define LRFDPBE_O_LFSR1H                                            0x0000014CU

// LFSR 1 Current Value, Bit-reversed 
#define LRFDPBE_O_LFSR1BRL                                          0x00000150U

// LFSR 1 Current Value, Bit-reversed 
#define LRFDPBE_O_LFSR1BRH                                          0x00000154U

// LFSR 0 Input, LSB First 
#define LRFDPBE_O_LFSR0INL                                          0x00000158U

// Control input size of LSFR 0 
#define LRFDPBE_O_LFSR0N                                            0x0000015CU

// LFSR 0 Input, MSB First 
#define LRFDPBE_O_LFSR0INM                                          0x00000160U

// LFSR 0 Output 
#define LRFDPBE_O_PHAOUT0                                           0x00000164U

// LFSR 1 Input, LSB First 
#define LRFDPBE_O_LFSR1INL                                          0x00000168U

// Controls input size of LFSR 1 
#define LRFDPBE_O_LFSR1N                                            0x0000016CU

// LFSR 1 Input, MSB First 
#define LRFDPBE_O_LFSR1INM                                          0x00000170U

// LFSR 0 Output, Bit-reversed 
#define LRFDPBE_O_PHAOUT0BR                                         0x00000174U

// Systimer capture value 
#define LRFDPBE_O_SYSTIM0L                                          0x00000180U

// Systimer capture value 
#define LRFDPBE_O_SYSTIM0H                                          0x00000184U

// Systimer capture value 
#define LRFDPBE_O_SYSTIM1L                                          0x00000188U

// Systimer capture value 
#define LRFDPBE_O_SYSTIM1H                                          0x0000018CU

// Systimer capture value 
#define LRFDPBE_O_SYSTIM2L                                          0x00000190U

// Systimer capture value 
#define LRFDPBE_O_SYSTIM2H                                          0x00000194U

// PBE Direct GPI Status 
#define LRFDPBE_O_GPI                                               0x00000198U

// The FIFO command register 
#define LRFDPBE_O_FCMD                                              0x000001A0U

// FIFO status register 
#define LRFDPBE_O_FSTAT                                             0x000001A4U

// FIFO write pointer 
#define LRFDPBE_O_RXFWP                                             0x000001A8U

// FIFO read pointer 
#define LRFDPBE_O_RXFRP                                             0x000001ACU

// Rx FIFO start of written package 
#define LRFDPBE_O_RXFSWP                                            0x000001B0U

// Rxfifo start of read package. 
#define LRFDPBE_O_RXFSRP                                            0x000001B4U

// TXFIFO write pointer 
#define LRFDPBE_O_TXFWP                                             0x000001B8U

// TXFIFO read pointer 
#define LRFDPBE_O_TXFRP                                             0x000001BCU

// TXFIFO start of written package 
#define LRFDPBE_O_TXFSWP                                            0x000001C0U

// TXFIFO start of read package. 
#define LRFDPBE_O_TXFSRP                                            0x000001C4U

// The amount of bytes which are deallocated and not yet written. 
#define LRFDPBE_O_RXFWRITABLE                                       0x000001C8U

// The amount of bytes which are comitted and not yet read. 
#define LRFDPBE_O_RXFREADABLE                                       0x000001CCU

// The amount of bytes which are deallocated and not yet written. 
#define LRFDPBE_O_TXFWRITABLE                                       0x000001D0U

// The amount of bytes which are comitted and not yet read. 
#define LRFDPBE_O_TXFREADABLE                                       0x000001D4U

// FIFO read access register 
#define LRFDPBE_O_RXFBRD                                            0x000001D8U

// FIFO access register 
#define LRFDPBE_O_RXFBWR                                            0x000001DCU

// FIFO read access register 
#define LRFDPBE_O_TXFBRD                                            0x000001E0U

// FIFO access register 
#define LRFDPBE_O_TXFBWR                                            0x000001E4U

// FIFO read access register 
#define LRFDPBE_O_RXFHRD                                            0x000001E8U

// FIFO access register 
#define LRFDPBE_O_RXFHWR                                            0x000001ECU

// FIFO read access register 
#define LRFDPBE_O_TXFHRD                                            0x000001F0U

// FIFO access register 
#define LRFDPBE_O_TXFHWR                                            0x000001F4U

//*****************************************************************************
//
// Register: LRFDPBE_O_ENABLE
//
//*****************************************************************************
// Field:     [2] MDMF 
//
// Modem fifo, OR'ed with equivalent siganl in modem 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_ENABLE_MDMF                                         0x00000004U
#define LRFDPBE_ENABLE_MDMF_M                                       0x00000004U
#define LRFDPBE_ENABLE_MDMF_S                                                2U
#define LRFDPBE_ENABLE_MDMF_EN                                      0x00000004U
#define LRFDPBE_ENABLE_MDMF_DIS                                     0x00000000U

// Field:     [1] LOCTIM 
//
// Enables the Local timer 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_ENABLE_LOCTIM                                       0x00000002U
#define LRFDPBE_ENABLE_LOCTIM_M                                     0x00000002U
#define LRFDPBE_ENABLE_LOCTIM_S                                              1U
#define LRFDPBE_ENABLE_LOCTIM_EN                                    0x00000002U
#define LRFDPBE_ENABLE_LOCTIM_DIS                                   0x00000000U

// Field:     [0] TOPSM 
//
// Enables the TOPsm (PBE) 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_ENABLE_TOPSM                                        0x00000001U
#define LRFDPBE_ENABLE_TOPSM_M                                      0x00000001U
#define LRFDPBE_ENABLE_TOPSM_S                                               0U
#define LRFDPBE_ENABLE_TOPSM_EN                                     0x00000001U
#define LRFDPBE_ENABLE_TOPSM_DIS                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FWSRC
//
//*****************************************************************************
// Field:     [2] DATARAM 
//
// Selects which RAM will be used for data storage 
// ENUMs: 
// S2RRAM                   Use S2RRAM for data 
// PBERAM                   Use PBERAM for data 
#define LRFDPBE_FWSRC_DATARAM                                       0x00000004U
#define LRFDPBE_FWSRC_DATARAM_M                                     0x00000004U
#define LRFDPBE_FWSRC_DATARAM_S                                              2U
#define LRFDPBE_FWSRC_DATARAM_S2RRAM                                0x00000004U
#define LRFDPBE_FWSRC_DATARAM_PBERAM                                0x00000000U

// Field:     [1] FWRAM 
//
// Select which RAM we run FW from 
// ENUMs: 
// S2RRAM                   Run code from S2RRAM 
// PBERAM                   Run code from PBERAM 
#define LRFDPBE_FWSRC_FWRAM                                         0x00000002U
#define LRFDPBE_FWSRC_FWRAM_M                                       0x00000002U
#define LRFDPBE_FWSRC_FWRAM_S                                                1U
#define LRFDPBE_FWSRC_FWRAM_S2RRAM                                  0x00000002U
#define LRFDPBE_FWSRC_FWRAM_PBERAM                                  0x00000000U

// Field:     [0] BANK 
//
// Sets the MSB of the address to the memory holding the program. 
// ENUMs: 
// ONE                      Run code from bank 1 
// ZERO                     Run code from bank 0 
#define LRFDPBE_FWSRC_BANK                                          0x00000001U
#define LRFDPBE_FWSRC_BANK_M                                        0x00000001U
#define LRFDPBE_FWSRC_BANK_S                                                 0U
#define LRFDPBE_FWSRC_BANK_ONE                                      0x00000001U
#define LRFDPBE_FWSRC_BANK_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_INIT
//
//*****************************************************************************
// Field:     [4] RFE 
//
// Do an INIT of the TOPSM in RFE, OR'ed with equivalent signal in RFE 
// ENUMs: 
// RESET                    The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_INIT_RFE                                            0x00000010U
#define LRFDPBE_INIT_RFE_M                                          0x00000010U
#define LRFDPBE_INIT_RFE_S                                                   4U
#define LRFDPBE_INIT_RFE_RESET                                      0x00000010U
#define LRFDPBE_INIT_RFE_NO_EFFECT                                  0x00000000U

// Field:     [3] MDM 
//
// Do an INIT of the TOPSM in MDM, OR'ed with equivalent signal in MDM 
// ENUMs: 
// RESET                    The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_INIT_MDM                                            0x00000008U
#define LRFDPBE_INIT_MDM_M                                          0x00000008U
#define LRFDPBE_INIT_MDM_S                                                   3U
#define LRFDPBE_INIT_MDM_RESET                                      0x00000008U
#define LRFDPBE_INIT_MDM_NO_EFFECT                                  0x00000000U

// Field:     [2] MDMF 
//
// Modem FIFO, OR'ed with equivalent signal in MDM 
// ENUMs: 
// RESET                    The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_INIT_MDMF                                           0x00000004U
#define LRFDPBE_INIT_MDMF_M                                         0x00000004U
#define LRFDPBE_INIT_MDMF_S                                                  2U
#define LRFDPBE_INIT_MDMF_RESET                                     0x00000004U
#define LRFDPBE_INIT_MDMF_NO_EFFECT                                 0x00000000U

// Field:     [1] LOCTIM 
//
// Synch reset Local timer 
// ENUMs: 
// RESET                    The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_INIT_LOCTIM                                         0x00000002U
#define LRFDPBE_INIT_LOCTIM_M                                       0x00000002U
#define LRFDPBE_INIT_LOCTIM_S                                                1U
#define LRFDPBE_INIT_LOCTIM_RESET                                   0x00000002U
#define LRFDPBE_INIT_LOCTIM_NO_EFFECT                               0x00000000U

// Field:     [0] TOPSM 
//
// Synch reset TOPsm (PBE) 
// ENUMs: 
// RESET                    The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_INIT_TOPSM                                          0x00000001U
#define LRFDPBE_INIT_TOPSM_M                                        0x00000001U
#define LRFDPBE_INIT_TOPSM_S                                                 0U
#define LRFDPBE_INIT_TOPSM_RESET                                    0x00000001U
#define LRFDPBE_INIT_TOPSM_NO_EFFECT                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_STROBES0
//
//*****************************************************************************
// Field:     [6] TIMCAPT1 
//
// PBE timer 1 capture strobe 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_STROBES0_TIMCAPT1                                   0x00000040U
#define LRFDPBE_STROBES0_TIMCAPT1_M                                 0x00000040U
#define LRFDPBE_STROBES0_TIMCAPT1_S                                          6U
#define LRFDPBE_STROBES0_TIMCAPT1_ONE                               0x00000040U
#define LRFDPBE_STROBES0_TIMCAPT1_ZERO                              0x00000000U

// Field:     [5] TIMCAPT0 
//
// PBE timer 0 capture strobe 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_STROBES0_TIMCAPT0                                   0x00000020U
#define LRFDPBE_STROBES0_TIMCAPT0_M                                 0x00000020U
#define LRFDPBE_STROBES0_TIMCAPT0_S                                          5U
#define LRFDPBE_STROBES0_TIMCAPT0_ONE                               0x00000020U
#define LRFDPBE_STROBES0_TIMCAPT0_ZERO                              0x00000000U

// Field:     [4] S2RTRIG 
//
// Arm/Trigger the S2R module 
// ENUMs: 
// ARM                      The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_STROBES0_S2RTRIG                                    0x00000010U
#define LRFDPBE_STROBES0_S2RTRIG_M                                  0x00000010U
#define LRFDPBE_STROBES0_S2RTRIG_S                                           4U
#define LRFDPBE_STROBES0_S2RTRIG_ARM                                0x00000010U
#define LRFDPBE_STROBES0_S2RTRIG_NO_EFFECT                          0x00000000U

// Field:     [3] DMATRIG 
//
// FW triggered DMA transfer 
// ENUMs: 
// ARM                      The bit is 1 
// NO_EFFECT                The bit is 0 
#define LRFDPBE_STROBES0_DMATRIG                                    0x00000008U
#define LRFDPBE_STROBES0_DMATRIG_M                                  0x00000008U
#define LRFDPBE_STROBES0_DMATRIG_S                                           3U
#define LRFDPBE_STROBES0_DMATRIG_ARM                                0x00000008U
#define LRFDPBE_STROBES0_DMATRIG_NO_EFFECT                          0x00000000U

// Field:     [2] SYSTCAPT2 
//
// Systimer capture 2 strobe 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_STROBES0_SYSTCAPT2                                  0x00000004U
#define LRFDPBE_STROBES0_SYSTCAPT2_M                                0x00000004U
#define LRFDPBE_STROBES0_SYSTCAPT2_S                                         2U
#define LRFDPBE_STROBES0_SYSTCAPT2_ONE                              0x00000004U
#define LRFDPBE_STROBES0_SYSTCAPT2_ZERO                             0x00000000U

// Field:     [1] SYSTCAPT1 
//
// Systimer capture1 strobe 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_STROBES0_SYSTCAPT1                                  0x00000002U
#define LRFDPBE_STROBES0_SYSTCAPT1_M                                0x00000002U
#define LRFDPBE_STROBES0_SYSTCAPT1_S                                         1U
#define LRFDPBE_STROBES0_SYSTCAPT1_ONE                              0x00000002U
#define LRFDPBE_STROBES0_SYSTCAPT1_ZERO                             0x00000000U

// Field:     [0] SYSTCAPT0 
//
// Systimer capture 0 strobe 0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_STROBES0_SYSTCAPT0                                  0x00000001U
#define LRFDPBE_STROBES0_SYSTCAPT0_M                                0x00000001U
#define LRFDPBE_STROBES0_SYSTCAPT0_S                                         0U
#define LRFDPBE_STROBES0_SYSTCAPT0_ONE                              0x00000001U
#define LRFDPBE_STROBES0_SYSTCAPT0_ZERO                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_IRQ
//
//*****************************************************************************
// Field:    [15] SOFT15 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT15                                          0x00008000U
#define LRFDPBE_IRQ_SOFT15_M                                        0x00008000U
#define LRFDPBE_IRQ_SOFT15_S                                                15U
#define LRFDPBE_IRQ_SOFT15_ON                                       0x00008000U
#define LRFDPBE_IRQ_SOFT15_OFF                                      0x00000000U

// Field:    [14] SOFT14 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT14                                          0x00004000U
#define LRFDPBE_IRQ_SOFT14_M                                        0x00004000U
#define LRFDPBE_IRQ_SOFT14_S                                                14U
#define LRFDPBE_IRQ_SOFT14_ON                                       0x00004000U
#define LRFDPBE_IRQ_SOFT14_OFF                                      0x00000000U

// Field:    [13] SOFT13 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT13                                          0x00002000U
#define LRFDPBE_IRQ_SOFT13_M                                        0x00002000U
#define LRFDPBE_IRQ_SOFT13_S                                                13U
#define LRFDPBE_IRQ_SOFT13_ON                                       0x00002000U
#define LRFDPBE_IRQ_SOFT13_OFF                                      0x00000000U

// Field:    [12] SOFT12 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT12                                          0x00001000U
#define LRFDPBE_IRQ_SOFT12_M                                        0x00001000U
#define LRFDPBE_IRQ_SOFT12_S                                                12U
#define LRFDPBE_IRQ_SOFT12_ON                                       0x00001000U
#define LRFDPBE_IRQ_SOFT12_OFF                                      0x00000000U

// Field:    [11] SOFT11 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT11                                          0x00000800U
#define LRFDPBE_IRQ_SOFT11_M                                        0x00000800U
#define LRFDPBE_IRQ_SOFT11_S                                                11U
#define LRFDPBE_IRQ_SOFT11_ON                                       0x00000800U
#define LRFDPBE_IRQ_SOFT11_OFF                                      0x00000000U

// Field:    [10] SOFT10 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT10                                          0x00000400U
#define LRFDPBE_IRQ_SOFT10_M                                        0x00000400U
#define LRFDPBE_IRQ_SOFT10_S                                                10U
#define LRFDPBE_IRQ_SOFT10_ON                                       0x00000400U
#define LRFDPBE_IRQ_SOFT10_OFF                                      0x00000000U

// Field:     [9] SOFT9 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT9                                           0x00000200U
#define LRFDPBE_IRQ_SOFT9_M                                         0x00000200U
#define LRFDPBE_IRQ_SOFT9_S                                                  9U
#define LRFDPBE_IRQ_SOFT9_ON                                        0x00000200U
#define LRFDPBE_IRQ_SOFT9_OFF                                       0x00000000U

// Field:     [8] SOFT8 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT8                                           0x00000100U
#define LRFDPBE_IRQ_SOFT8_M                                         0x00000100U
#define LRFDPBE_IRQ_SOFT8_S                                                  8U
#define LRFDPBE_IRQ_SOFT8_ON                                        0x00000100U
#define LRFDPBE_IRQ_SOFT8_OFF                                       0x00000000U

// Field:     [7] SOFT7 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT7                                           0x00000080U
#define LRFDPBE_IRQ_SOFT7_M                                         0x00000080U
#define LRFDPBE_IRQ_SOFT7_S                                                  7U
#define LRFDPBE_IRQ_SOFT7_ON                                        0x00000080U
#define LRFDPBE_IRQ_SOFT7_OFF                                       0x00000000U

// Field:     [6] SOFT6 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT6                                           0x00000040U
#define LRFDPBE_IRQ_SOFT6_M                                         0x00000040U
#define LRFDPBE_IRQ_SOFT6_S                                                  6U
#define LRFDPBE_IRQ_SOFT6_ON                                        0x00000040U
#define LRFDPBE_IRQ_SOFT6_OFF                                       0x00000000U

// Field:     [5] SOFT5 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT5                                           0x00000020U
#define LRFDPBE_IRQ_SOFT5_M                                         0x00000020U
#define LRFDPBE_IRQ_SOFT5_S                                                  5U
#define LRFDPBE_IRQ_SOFT5_ON                                        0x00000020U
#define LRFDPBE_IRQ_SOFT5_OFF                                       0x00000000U

// Field:     [4] SOFT4 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT4                                           0x00000010U
#define LRFDPBE_IRQ_SOFT4_M                                         0x00000010U
#define LRFDPBE_IRQ_SOFT4_S                                                  4U
#define LRFDPBE_IRQ_SOFT4_ON                                        0x00000010U
#define LRFDPBE_IRQ_SOFT4_OFF                                       0x00000000U

// Field:     [3] SOFT3 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT3                                           0x00000008U
#define LRFDPBE_IRQ_SOFT3_M                                         0x00000008U
#define LRFDPBE_IRQ_SOFT3_S                                                  3U
#define LRFDPBE_IRQ_SOFT3_ON                                        0x00000008U
#define LRFDPBE_IRQ_SOFT3_OFF                                       0x00000000U

// Field:     [2] SOFT2 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT2                                           0x00000004U
#define LRFDPBE_IRQ_SOFT2_M                                         0x00000004U
#define LRFDPBE_IRQ_SOFT2_S                                                  2U
#define LRFDPBE_IRQ_SOFT2_ON                                        0x00000004U
#define LRFDPBE_IRQ_SOFT2_OFF                                       0x00000000U

// Field:     [1] SOFT1 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT1                                           0x00000002U
#define LRFDPBE_IRQ_SOFT1_M                                         0x00000002U
#define LRFDPBE_IRQ_SOFT1_S                                                  1U
#define LRFDPBE_IRQ_SOFT1_ON                                        0x00000002U
#define LRFDPBE_IRQ_SOFT1_OFF                                       0x00000000U

// Field:     [0] SOFT0 
//
// Software defined interrupt 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_IRQ_SOFT0                                           0x00000001U
#define LRFDPBE_IRQ_SOFT0_M                                         0x00000001U
#define LRFDPBE_IRQ_SOFT0_S                                                  0U
#define LRFDPBE_IRQ_SOFT0_ON                                        0x00000001U
#define LRFDPBE_IRQ_SOFT0_OFF                                       0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVT0
//
//*****************************************************************************
// Field:    [15] MDMFAEMPTY 
//
// Modem fifo is emptied below the empty threshold 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_MDMFAEMPTY                                     0x00008000U
#define LRFDPBE_EVT0_MDMFAEMPTY_M                                   0x00008000U
#define LRFDPBE_EVT0_MDMFAEMPTY_S                                           15U
#define LRFDPBE_EVT0_MDMFAEMPTY_ONE                                 0x00008000U
#define LRFDPBE_EVT0_MDMFAEMPTY_ZERO                                0x00000000U

// Field:    [14] S2RSTOP 
//
// S2R has written to the STOP_ADDRESS location 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_S2RSTOP                                        0x00004000U
#define LRFDPBE_EVT0_S2RSTOP_M                                      0x00004000U
#define LRFDPBE_EVT0_S2RSTOP_S                                              14U
#define LRFDPBE_EVT0_S2RSTOP_ONE                                    0x00004000U
#define LRFDPBE_EVT0_S2RSTOP_ZERO                                   0x00000000U

// Field:    [13] FIFOERR 
//
// Error event from fifo 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_FIFOERR                                        0x00002000U
#define LRFDPBE_EVT0_FIFOERR_M                                      0x00002000U
#define LRFDPBE_EVT0_FIFOERR_S                                              13U
#define LRFDPBE_EVT0_FIFOERR_ONE                                    0x00002000U
#define LRFDPBE_EVT0_FIFOERR_ZERO                                   0x00000000U

// Field:    [12] MDMFAFULL 
//
// Modem fifo is filled above the threshold 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_MDMFAFULL                                      0x00001000U
#define LRFDPBE_EVT0_MDMFAFULL_M                                    0x00001000U
#define LRFDPBE_EVT0_MDMFAFULL_S                                            12U
#define LRFDPBE_EVT0_MDMFAFULL_ONE                                  0x00001000U
#define LRFDPBE_EVT0_MDMFAFULL_ZERO                                 0x00000000U

// Field:    [11] SYSTCMP2 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_SYSTCMP2                                       0x00000800U
#define LRFDPBE_EVT0_SYSTCMP2_M                                     0x00000800U
#define LRFDPBE_EVT0_SYSTCMP2_S                                             11U
#define LRFDPBE_EVT0_SYSTCMP2_ONE                                   0x00000800U
#define LRFDPBE_EVT0_SYSTCMP2_ZERO                                  0x00000000U

// Field:    [10] SYSTCMP1 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_SYSTCMP1                                       0x00000400U
#define LRFDPBE_EVT0_SYSTCMP1_M                                     0x00000400U
#define LRFDPBE_EVT0_SYSTCMP1_S                                             10U
#define LRFDPBE_EVT0_SYSTCMP1_ONE                                   0x00000400U
#define LRFDPBE_EVT0_SYSTCMP1_ZERO                                  0x00000000U

// Field:     [9] SYSTCMP0 
//
// Systimer compare event 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_SYSTCMP0                                       0x00000200U
#define LRFDPBE_EVT0_SYSTCMP0_M                                     0x00000200U
#define LRFDPBE_EVT0_SYSTCMP0_S                                              9U
#define LRFDPBE_EVT0_SYSTCMP0_ONE                                   0x00000200U
#define LRFDPBE_EVT0_SYSTCMP0_ZERO                                  0x00000000U

// Field:     [8] MDMMSGBOX 
//
// New command status from MCE received in MDMMSGBOX register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_MDMMSGBOX                                      0x00000100U
#define LRFDPBE_EVT0_MDMMSGBOX_M                                    0x00000100U
#define LRFDPBE_EVT0_MDMMSGBOX_S                                             8U
#define LRFDPBE_EVT0_MDMMSGBOX_ONE                                  0x00000100U
#define LRFDPBE_EVT0_MDMMSGBOX_ZERO                                 0x00000000U

// Field:     [7] RFEMSGBOX 
//
// New command status from RFE received in RFEMSGBOX register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_RFEMSGBOX                                      0x00000080U
#define LRFDPBE_EVT0_RFEMSGBOX_M                                    0x00000080U
#define LRFDPBE_EVT0_RFEMSGBOX_S                                             7U
#define LRFDPBE_EVT0_RFEMSGBOX_ONE                                  0x00000080U
#define LRFDPBE_EVT0_RFEMSGBOX_ZERO                                 0x00000000U

// Field:     [6] RFEDAT 
//
// New data from RFE received in RFEDATIN0 register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_RFEDAT                                         0x00000040U
#define LRFDPBE_EVT0_RFEDAT_M                                       0x00000040U
#define LRFDPBE_EVT0_RFEDAT_S                                                6U
#define LRFDPBE_EVT0_RFEDAT_ONE                                     0x00000040U
#define LRFDPBE_EVT0_RFEDAT_ZERO                                    0x00000000U

// Field:     [5] RFECMD 
//
// New command from RFE received in RFECMDIN register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_RFECMD                                         0x00000020U
#define LRFDPBE_EVT0_RFECMD_M                                       0x00000020U
#define LRFDPBE_EVT0_RFECMD_S                                                5U
#define LRFDPBE_EVT0_RFECMD_ONE                                     0x00000020U
#define LRFDPBE_EVT0_RFECMD_ZERO                                    0x00000000U

// Field:     [4] MDMDAT 
//
// New data from MCE received in MCEDATIN0 register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_MDMDAT                                         0x00000010U
#define LRFDPBE_EVT0_MDMDAT_M                                       0x00000010U
#define LRFDPBE_EVT0_MDMDAT_S                                                4U
#define LRFDPBE_EVT0_MDMDAT_ONE                                     0x00000010U
#define LRFDPBE_EVT0_MDMDAT_ZERO                                    0x00000000U

// Field:     [3] MDMCMD 
//
// New command from MCE received in MCECMDIN register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_MDMCMD                                         0x00000008U
#define LRFDPBE_EVT0_MDMCMD_M                                       0x00000008U
#define LRFDPBE_EVT0_MDMCMD_S                                                3U
#define LRFDPBE_EVT0_MDMCMD_ONE                                     0x00000008U
#define LRFDPBE_EVT0_MDMCMD_ZERO                                    0x00000000U

// Field:     [2] TIMER1 
//
// Counter value reached in local timer. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_TIMER1                                         0x00000004U
#define LRFDPBE_EVT0_TIMER1_M                                       0x00000004U
#define LRFDPBE_EVT0_TIMER1_S                                                2U
#define LRFDPBE_EVT0_TIMER1_ONE                                     0x00000004U
#define LRFDPBE_EVT0_TIMER1_ZERO                                    0x00000000U

// Field:     [1] TIMER0 
//
// Timer period expired in local timer. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_TIMER0                                         0x00000002U
#define LRFDPBE_EVT0_TIMER0_M                                       0x00000002U
#define LRFDPBE_EVT0_TIMER0_S                                                1U
#define LRFDPBE_EVT0_TIMER0_ONE                                     0x00000002U
#define LRFDPBE_EVT0_TIMER0_ZERO                                    0x00000000U

// Field:     [0] PBEAPI 
//
// New command from CPE has been written in API register. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT0_PBEAPI                                         0x00000001U
#define LRFDPBE_EVT0_PBEAPI_M                                       0x00000001U
#define LRFDPBE_EVT0_PBEAPI_S                                                0U
#define LRFDPBE_EVT0_PBEAPI_ONE                                     0x00000001U
#define LRFDPBE_EVT0_PBEAPI_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVT1
//
//*****************************************************************************
// Field:    [12] TXRDBTHR 
//
// The TX FIFO contains TXFRBTHRS or more readable bytes. 
// ENUMs: 
// MET                      The TX FIFO contains TXFRBTHRS or more readable 
//                          bytes. 
// BELOW                    The TX FIFO contains less than the threshold 
//                          TXFRBTHRS readable bytes. 
#define LRFDPBE_EVT1_TXRDBTHR                                       0x00001000U
#define LRFDPBE_EVT1_TXRDBTHR_M                                     0x00001000U
#define LRFDPBE_EVT1_TXRDBTHR_S                                             12U
#define LRFDPBE_EVT1_TXRDBTHR_MET                                   0x00001000U
#define LRFDPBE_EVT1_TXRDBTHR_BELOW                                 0x00000000U

// Field:    [11] TXWRBTHR 
//
// The TX FIFO contains TXFWBTHRS or more writable bytes. 
// ENUMs: 
// MET                      The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
// BELOW                    The TX FIFO contains less than the threshold 
//                          TXFWBTHRS writable bytes. 
#define LRFDPBE_EVT1_TXWRBTHR                                       0x00000800U
#define LRFDPBE_EVT1_TXWRBTHR_M                                     0x00000800U
#define LRFDPBE_EVT1_TXWRBTHR_S                                             11U
#define LRFDPBE_EVT1_TXWRBTHR_MET                                   0x00000800U
#define LRFDPBE_EVT1_TXWRBTHR_BELOW                                 0x00000000U

// Field:    [10] RXRDBTHR 
//
// The RX FIFO contains RXFRBTHRS or more readable bytes. 
// ENUMs: 
// MET                      The TX FIFO contains TXFRBTHRS or more readable 
//                          bytes. 
// BELOW                    The TX FIFO contains less than the threshold 
//                          TXFRBTHRS readable bytes. 
#define LRFDPBE_EVT1_RXRDBTHR                                       0x00000400U
#define LRFDPBE_EVT1_RXRDBTHR_M                                     0x00000400U
#define LRFDPBE_EVT1_RXRDBTHR_S                                             10U
#define LRFDPBE_EVT1_RXRDBTHR_MET                                   0x00000400U
#define LRFDPBE_EVT1_RXRDBTHR_BELOW                                 0x00000000U

// Field:     [9] RXWRBTHR 
//
// The RX FIFO contains RXFWBTHRS or more writable bytes. 
// ENUMs: 
// MET                      The RX FIFO contains RXFWBTHRS or more writable 
//                          bytes. 
// BELOW                    The RX FIFO contains less than the threshold 
//                          RXFWBTHRS writable bytes. 
#define LRFDPBE_EVT1_RXWRBTHR                                       0x00000200U
#define LRFDPBE_EVT1_RXWRBTHR_M                                     0x00000200U
#define LRFDPBE_EVT1_RXWRBTHR_S                                              9U
#define LRFDPBE_EVT1_RXWRBTHR_MET                                   0x00000200U
#define LRFDPBE_EVT1_RXWRBTHR_BELOW                                 0x00000000U

// Field:     [8] MDMPROG 
//
// Programmable event from modem 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_MDMPROG                                        0x00000100U
#define LRFDPBE_EVT1_MDMPROG_M                                      0x00000100U
#define LRFDPBE_EVT1_MDMPROG_S                                               8U
#define LRFDPBE_EVT1_MDMPROG_ONE                                    0x00000100U
#define LRFDPBE_EVT1_MDMPROG_ZERO                                   0x00000000U

// Field:     [7] PBEGPI7 
//
// External input event line GPI7 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI7                                        0x00000080U
#define LRFDPBE_EVT1_PBEGPI7_M                                      0x00000080U
#define LRFDPBE_EVT1_PBEGPI7_S                                               7U
#define LRFDPBE_EVT1_PBEGPI7_ONE                                    0x00000080U
#define LRFDPBE_EVT1_PBEGPI7_ZERO                                   0x00000000U

// Field:     [6] PBEGPI6 
//
// External input event line GPI6 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI6                                        0x00000040U
#define LRFDPBE_EVT1_PBEGPI6_M                                      0x00000040U
#define LRFDPBE_EVT1_PBEGPI6_S                                               6U
#define LRFDPBE_EVT1_PBEGPI6_ONE                                    0x00000040U
#define LRFDPBE_EVT1_PBEGPI6_ZERO                                   0x00000000U

// Field:     [5] PBEGPI5 
//
// External input event line GPI5 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI5                                        0x00000020U
#define LRFDPBE_EVT1_PBEGPI5_M                                      0x00000020U
#define LRFDPBE_EVT1_PBEGPI5_S                                               5U
#define LRFDPBE_EVT1_PBEGPI5_ONE                                    0x00000020U
#define LRFDPBE_EVT1_PBEGPI5_ZERO                                   0x00000000U

// Field:     [4] PBEGPI4 
//
// External input event line GPI4 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI4                                        0x00000010U
#define LRFDPBE_EVT1_PBEGPI4_M                                      0x00000010U
#define LRFDPBE_EVT1_PBEGPI4_S                                               4U
#define LRFDPBE_EVT1_PBEGPI4_ONE                                    0x00000010U
#define LRFDPBE_EVT1_PBEGPI4_ZERO                                   0x00000000U

// Field:     [3] PBEGPI3 
//
// External input event line GPI3 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI3                                        0x00000008U
#define LRFDPBE_EVT1_PBEGPI3_M                                      0x00000008U
#define LRFDPBE_EVT1_PBEGPI3_S                                               3U
#define LRFDPBE_EVT1_PBEGPI3_ONE                                    0x00000008U
#define LRFDPBE_EVT1_PBEGPI3_ZERO                                   0x00000000U

// Field:     [2] PBEGPI2 
//
// External input event line GPI2 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI2                                        0x00000004U
#define LRFDPBE_EVT1_PBEGPI2_M                                      0x00000004U
#define LRFDPBE_EVT1_PBEGPI2_S                                               2U
#define LRFDPBE_EVT1_PBEGPI2_ONE                                    0x00000004U
#define LRFDPBE_EVT1_PBEGPI2_ZERO                                   0x00000000U

// Field:     [1] PBEGPI1 
//
// External input event line GPI1 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI1                                        0x00000002U
#define LRFDPBE_EVT1_PBEGPI1_M                                      0x00000002U
#define LRFDPBE_EVT1_PBEGPI1_S                                               1U
#define LRFDPBE_EVT1_PBEGPI1_ONE                                    0x00000002U
#define LRFDPBE_EVT1_PBEGPI1_ZERO                                   0x00000000U

// Field:     [0] PBEGPI0 
//
// External input event line GPI0 from IOC. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_EVT1_PBEGPI0                                        0x00000001U
#define LRFDPBE_EVT1_PBEGPI0_M                                      0x00000001U
#define LRFDPBE_EVT1_PBEGPI0_S                                               0U
#define LRFDPBE_EVT1_PBEGPI0_ONE                                    0x00000001U
#define LRFDPBE_EVT1_PBEGPI0_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVTMSK0
//
//*****************************************************************************
// Field:    [15] MDMFAEMPTY 
//
// Enable mask for event EVT0.MDMFAEMPTY 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_MDMFAEMPTY                                  0x00008000U
#define LRFDPBE_EVTMSK0_MDMFAEMPTY_M                                0x00008000U
#define LRFDPBE_EVTMSK0_MDMFAEMPTY_S                                        15U
#define LRFDPBE_EVTMSK0_MDMFAEMPTY_EN                               0x00008000U
#define LRFDPBE_EVTMSK0_MDMFAEMPTY_DIS                              0x00000000U

// Field:    [14] S2RSTOP 
//
// Enable mask for event EVT0.S2RSTOP 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_S2RSTOP                                     0x00004000U
#define LRFDPBE_EVTMSK0_S2RSTOP_M                                   0x00004000U
#define LRFDPBE_EVTMSK0_S2RSTOP_S                                           14U
#define LRFDPBE_EVTMSK0_S2RSTOP_EN                                  0x00004000U
#define LRFDPBE_EVTMSK0_S2RSTOP_DIS                                 0x00000000U

// Field:    [13] FIFOERR 
//
// Enable mask for event EVT0.FIFOERR 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_FIFOERR                                     0x00002000U
#define LRFDPBE_EVTMSK0_FIFOERR_M                                   0x00002000U
#define LRFDPBE_EVTMSK0_FIFOERR_S                                           13U
#define LRFDPBE_EVTMSK0_FIFOERR_EN                                  0x00002000U
#define LRFDPBE_EVTMSK0_FIFOERR_DIS                                 0x00000000U

// Field:    [12] MDMFAFULL 
//
// Enable mask for event EVT0.MDMFAFULL 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_MDMFAFULL                                   0x00001000U
#define LRFDPBE_EVTMSK0_MDMFAFULL_M                                 0x00001000U
#define LRFDPBE_EVTMSK0_MDMFAFULL_S                                         12U
#define LRFDPBE_EVTMSK0_MDMFAFULL_EN                                0x00001000U
#define LRFDPBE_EVTMSK0_MDMFAFULL_DIS                               0x00000000U

// Field:    [11] SYSTCMP2 
//
// Enable mask for event EVT0.SYSTCMP2 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_SYSTCMP2                                    0x00000800U
#define LRFDPBE_EVTMSK0_SYSTCMP2_M                                  0x00000800U
#define LRFDPBE_EVTMSK0_SYSTCMP2_S                                          11U
#define LRFDPBE_EVTMSK0_SYSTCMP2_EN                                 0x00000800U
#define LRFDPBE_EVTMSK0_SYSTCMP2_DIS                                0x00000000U

// Field:    [10] SYSTCMP1 
//
// Enable mask for event EVT0.SYSTCMP1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_SYSTCMP1                                    0x00000400U
#define LRFDPBE_EVTMSK0_SYSTCMP1_M                                  0x00000400U
#define LRFDPBE_EVTMSK0_SYSTCMP1_S                                          10U
#define LRFDPBE_EVTMSK0_SYSTCMP1_EN                                 0x00000400U
#define LRFDPBE_EVTMSK0_SYSTCMP1_DIS                                0x00000000U

// Field:     [9] SYSTCMP0 
//
// Enable mask for event EVT0.SYSTCMP0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_SYSTCMP0                                    0x00000200U
#define LRFDPBE_EVTMSK0_SYSTCMP0_M                                  0x00000200U
#define LRFDPBE_EVTMSK0_SYSTCMP0_S                                           9U
#define LRFDPBE_EVTMSK0_SYSTCMP0_EN                                 0x00000200U
#define LRFDPBE_EVTMSK0_SYSTCMP0_DIS                                0x00000000U

// Field:     [8] MDMMSGBOX 
//
// Enable mask for event EVT0.MDMMSGBOX 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_MDMMSGBOX                                   0x00000100U
#define LRFDPBE_EVTMSK0_MDMMSGBOX_M                                 0x00000100U
#define LRFDPBE_EVTMSK0_MDMMSGBOX_S                                          8U
#define LRFDPBE_EVTMSK0_MDMMSGBOX_EN                                0x00000100U
#define LRFDPBE_EVTMSK0_MDMMSGBOX_DIS                               0x00000000U

// Field:     [7] RFEMSGBOX 
//
// Enable mask for event EVT0.RFEMSGBOX 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_RFEMSGBOX                                   0x00000080U
#define LRFDPBE_EVTMSK0_RFEMSGBOX_M                                 0x00000080U
#define LRFDPBE_EVTMSK0_RFEMSGBOX_S                                          7U
#define LRFDPBE_EVTMSK0_RFEMSGBOX_EN                                0x00000080U
#define LRFDPBE_EVTMSK0_RFEMSGBOX_DIS                               0x00000000U

// Field:     [6] RFEDAT 
//
// Enable mask for event EVT0.RFEDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_RFEDAT                                      0x00000040U
#define LRFDPBE_EVTMSK0_RFEDAT_M                                    0x00000040U
#define LRFDPBE_EVTMSK0_RFEDAT_S                                             6U
#define LRFDPBE_EVTMSK0_RFEDAT_EN                                   0x00000040U
#define LRFDPBE_EVTMSK0_RFEDAT_DIS                                  0x00000000U

// Field:     [5] RFECMD 
//
// Enable mask for event EVT0.RFECMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_RFECMD                                      0x00000020U
#define LRFDPBE_EVTMSK0_RFECMD_M                                    0x00000020U
#define LRFDPBE_EVTMSK0_RFECMD_S                                             5U
#define LRFDPBE_EVTMSK0_RFECMD_EN                                   0x00000020U
#define LRFDPBE_EVTMSK0_RFECMD_DIS                                  0x00000000U

// Field:     [4] MDMDAT 
//
// Enable mask for event EVT0.MDMDAT 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_MDMDAT                                      0x00000010U
#define LRFDPBE_EVTMSK0_MDMDAT_M                                    0x00000010U
#define LRFDPBE_EVTMSK0_MDMDAT_S                                             4U
#define LRFDPBE_EVTMSK0_MDMDAT_EN                                   0x00000010U
#define LRFDPBE_EVTMSK0_MDMDAT_DIS                                  0x00000000U

// Field:     [3] MDMCMD 
//
// Enable mask for event EVT0.MDMCMD 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_MDMCMD                                      0x00000008U
#define LRFDPBE_EVTMSK0_MDMCMD_M                                    0x00000008U
#define LRFDPBE_EVTMSK0_MDMCMD_S                                             3U
#define LRFDPBE_EVTMSK0_MDMCMD_EN                                   0x00000008U
#define LRFDPBE_EVTMSK0_MDMCMD_DIS                                  0x00000000U

// Field:     [2] TIMER1 
//
// Enable mask for event EVT0.TIMER1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_TIMER1                                      0x00000004U
#define LRFDPBE_EVTMSK0_TIMER1_M                                    0x00000004U
#define LRFDPBE_EVTMSK0_TIMER1_S                                             2U
#define LRFDPBE_EVTMSK0_TIMER1_EN                                   0x00000004U
#define LRFDPBE_EVTMSK0_TIMER1_DIS                                  0x00000000U

// Field:     [1] TIMER0 
//
// Enable mask for event EVT0.TIMER0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_TIMER0                                      0x00000002U
#define LRFDPBE_EVTMSK0_TIMER0_M                                    0x00000002U
#define LRFDPBE_EVTMSK0_TIMER0_S                                             1U
#define LRFDPBE_EVTMSK0_TIMER0_EN                                   0x00000002U
#define LRFDPBE_EVTMSK0_TIMER0_DIS                                  0x00000000U

// Field:     [0] PBEAPI 
//
// Enable mask for event EVT0.PBEAPI 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK0_PBEAPI                                      0x00000001U
#define LRFDPBE_EVTMSK0_PBEAPI_M                                    0x00000001U
#define LRFDPBE_EVTMSK0_PBEAPI_S                                             0U
#define LRFDPBE_EVTMSK0_PBEAPI_EN                                   0x00000001U
#define LRFDPBE_EVTMSK0_PBEAPI_DIS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVTMSK1
//
//*****************************************************************************
// Field:    [12] TXRDBTHR 
//
// Enable mask for event EVT0.TXRDBTHR 
// ENUMs: 
// EN                       The TX FIFO contains TXFRBTHRS or more readable 
//                          bytes. 
// DIS                      The TX FIFO contains less than the threshold 
//                          TXFRBTHRS readable bytes. 
#define LRFDPBE_EVTMSK1_TXRDBTHR                                    0x00001000U
#define LRFDPBE_EVTMSK1_TXRDBTHR_M                                  0x00001000U
#define LRFDPBE_EVTMSK1_TXRDBTHR_S                                          12U
#define LRFDPBE_EVTMSK1_TXRDBTHR_EN                                 0x00001000U
#define LRFDPBE_EVTMSK1_TXRDBTHR_DIS                                0x00000000U

// Field:    [11] TXWRBTHR 
//
// Enable mask for event EVT0.TXWRBTHR 
// ENUMs: 
// EN                       The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
// DIS                      The TX FIFO contains less than the threshold 
//                          TXFWBTHRS writable bytes. 
#define LRFDPBE_EVTMSK1_TXWRBTHR                                    0x00000800U
#define LRFDPBE_EVTMSK1_TXWRBTHR_M                                  0x00000800U
#define LRFDPBE_EVTMSK1_TXWRBTHR_S                                          11U
#define LRFDPBE_EVTMSK1_TXWRBTHR_EN                                 0x00000800U
#define LRFDPBE_EVTMSK1_TXWRBTHR_DIS                                0x00000000U

// Field:    [10] RXRDBTHR 
//
// Enable mask for event EVT0.RXRDBTHR 
// ENUMs: 
// EN                       The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
// DIS                      The TX FIFO contains less than the threshold 
//                          TXFWBTHRS writable bytes. 
#define LRFDPBE_EVTMSK1_RXRDBTHR                                    0x00000400U
#define LRFDPBE_EVTMSK1_RXRDBTHR_M                                  0x00000400U
#define LRFDPBE_EVTMSK1_RXRDBTHR_S                                          10U
#define LRFDPBE_EVTMSK1_RXRDBTHR_EN                                 0x00000400U
#define LRFDPBE_EVTMSK1_RXRDBTHR_DIS                                0x00000000U

// Field:     [9] RXWRBTHR 
//
// Enable mask for event EVT0.RXWRBTHR 
// ENUMs: 
// EN                       The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
// DIS                      The TX FIFO contains less than the threshold 
//                          TXFWBTHRS writable bytes. 
#define LRFDPBE_EVTMSK1_RXWRBTHR                                    0x00000200U
#define LRFDPBE_EVTMSK1_RXWRBTHR_M                                  0x00000200U
#define LRFDPBE_EVTMSK1_RXWRBTHR_S                                           9U
#define LRFDPBE_EVTMSK1_RXWRBTHR_EN                                 0x00000200U
#define LRFDPBE_EVTMSK1_RXWRBTHR_DIS                                0x00000000U

// Field:     [8] MDMPROG 
//
// Enable mask for event EVT0.MDMPROG 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_MDMPROG                                     0x00000100U
#define LRFDPBE_EVTMSK1_MDMPROG_M                                   0x00000100U
#define LRFDPBE_EVTMSK1_MDMPROG_S                                            8U
#define LRFDPBE_EVTMSK1_MDMPROG_EN                                  0x00000100U
#define LRFDPBE_EVTMSK1_MDMPROG_DIS                                 0x00000000U

// Field:     [7] PBEGPI7 
//
// Enable mask for event EVT0.PBEGPI7 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI7                                     0x00000080U
#define LRFDPBE_EVTMSK1_PBEGPI7_M                                   0x00000080U
#define LRFDPBE_EVTMSK1_PBEGPI7_S                                            7U
#define LRFDPBE_EVTMSK1_PBEGPI7_EN                                  0x00000080U
#define LRFDPBE_EVTMSK1_PBEGPI7_DIS                                 0x00000000U

// Field:     [6] PBEGPI6 
//
// Enable mask for event EVT0.PBEGPI6 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI6                                     0x00000040U
#define LRFDPBE_EVTMSK1_PBEGPI6_M                                   0x00000040U
#define LRFDPBE_EVTMSK1_PBEGPI6_S                                            6U
#define LRFDPBE_EVTMSK1_PBEGPI6_EN                                  0x00000040U
#define LRFDPBE_EVTMSK1_PBEGPI6_DIS                                 0x00000000U

// Field:     [5] PBEGPI5 
//
// Enable mask for event EVT0.PBEGPI5 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI5                                     0x00000020U
#define LRFDPBE_EVTMSK1_PBEGPI5_M                                   0x00000020U
#define LRFDPBE_EVTMSK1_PBEGPI5_S                                            5U
#define LRFDPBE_EVTMSK1_PBEGPI5_EN                                  0x00000020U
#define LRFDPBE_EVTMSK1_PBEGPI5_DIS                                 0x00000000U

// Field:     [4] PBEGPI4 
//
// Enable mask for event EVT0.PBEGPI4 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI4                                     0x00000010U
#define LRFDPBE_EVTMSK1_PBEGPI4_M                                   0x00000010U
#define LRFDPBE_EVTMSK1_PBEGPI4_S                                            4U
#define LRFDPBE_EVTMSK1_PBEGPI4_EN                                  0x00000010U
#define LRFDPBE_EVTMSK1_PBEGPI4_DIS                                 0x00000000U

// Field:     [3] PBEGPI3 
//
// Enable mask for event EVT0.PBEGPI3 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI3                                     0x00000008U
#define LRFDPBE_EVTMSK1_PBEGPI3_M                                   0x00000008U
#define LRFDPBE_EVTMSK1_PBEGPI3_S                                            3U
#define LRFDPBE_EVTMSK1_PBEGPI3_EN                                  0x00000008U
#define LRFDPBE_EVTMSK1_PBEGPI3_DIS                                 0x00000000U

// Field:     [2] PBEGPI2 
//
// Enable mask for event EVT0.PBEGPI2 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI2                                     0x00000004U
#define LRFDPBE_EVTMSK1_PBEGPI2_M                                   0x00000004U
#define LRFDPBE_EVTMSK1_PBEGPI2_S                                            2U
#define LRFDPBE_EVTMSK1_PBEGPI2_EN                                  0x00000004U
#define LRFDPBE_EVTMSK1_PBEGPI2_DIS                                 0x00000000U

// Field:     [1] PBEGPI1 
//
// Enable mask for event EVT0.PBEGPI1 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI1                                     0x00000002U
#define LRFDPBE_EVTMSK1_PBEGPI1_M                                   0x00000002U
#define LRFDPBE_EVTMSK1_PBEGPI1_S                                            1U
#define LRFDPBE_EVTMSK1_PBEGPI1_EN                                  0x00000002U
#define LRFDPBE_EVTMSK1_PBEGPI1_DIS                                 0x00000000U

// Field:     [0] PBEGPI0 
//
// Enable mask for event EVT0.PBEGPI0 
// ENUMs: 
// EN                       The bit is 1 
// DIS                      The bit is 0 
#define LRFDPBE_EVTMSK1_PBEGPI0                                     0x00000001U
#define LRFDPBE_EVTMSK1_PBEGPI0_M                                   0x00000001U
#define LRFDPBE_EVTMSK1_PBEGPI0_S                                            0U
#define LRFDPBE_EVTMSK1_PBEGPI0_EN                                  0x00000001U
#define LRFDPBE_EVTMSK1_PBEGPI0_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVTCLR0
//
//*****************************************************************************
// Field:    [15] MDMFAEMPTY 
//
// Clear event EVT0.MDMFAEMPTY 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_MDMFAEMPTY                                  0x00008000U
#define LRFDPBE_EVTCLR0_MDMFAEMPTY_M                                0x00008000U
#define LRFDPBE_EVTCLR0_MDMFAEMPTY_S                                        15U
#define LRFDPBE_EVTCLR0_MDMFAEMPTY_CLEAR                            0x00008000U
#define LRFDPBE_EVTCLR0_MDMFAEMPTY_RETAIN                           0x00000000U

// Field:    [14] S2RSTOP 
//
// Clear event EVT0.S2RSTOP 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_S2RSTOP                                     0x00004000U
#define LRFDPBE_EVTCLR0_S2RSTOP_M                                   0x00004000U
#define LRFDPBE_EVTCLR0_S2RSTOP_S                                           14U
#define LRFDPBE_EVTCLR0_S2RSTOP_CLEAR                               0x00004000U
#define LRFDPBE_EVTCLR0_S2RSTOP_RETAIN                              0x00000000U

// Field:    [13] FIFOERR 
//
// Clear event EVT0.FIFOERR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_FIFOERR                                     0x00002000U
#define LRFDPBE_EVTCLR0_FIFOERR_M                                   0x00002000U
#define LRFDPBE_EVTCLR0_FIFOERR_S                                           13U
#define LRFDPBE_EVTCLR0_FIFOERR_CLEAR                               0x00002000U
#define LRFDPBE_EVTCLR0_FIFOERR_RETAIN                              0x00000000U

// Field:    [12] MDMFAFULL 
//
// Clear event EVT0.MDMFAFULL 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_MDMFAFULL                                   0x00001000U
#define LRFDPBE_EVTCLR0_MDMFAFULL_M                                 0x00001000U
#define LRFDPBE_EVTCLR0_MDMFAFULL_S                                         12U
#define LRFDPBE_EVTCLR0_MDMFAFULL_CLEAR                             0x00001000U
#define LRFDPBE_EVTCLR0_MDMFAFULL_RETAIN                            0x00000000U

// Field:    [11] SYSTCMP2 
//
// Clear event EVT0.SYSTCMP2 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_SYSTCMP2                                    0x00000800U
#define LRFDPBE_EVTCLR0_SYSTCMP2_M                                  0x00000800U
#define LRFDPBE_EVTCLR0_SYSTCMP2_S                                          11U
#define LRFDPBE_EVTCLR0_SYSTCMP2_CLEAR                              0x00000800U
#define LRFDPBE_EVTCLR0_SYSTCMP2_RETAIN                             0x00000000U

// Field:    [10] SYSTCMP1 
//
// Clear event EVT0.SYSTCMP1 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_SYSTCMP1                                    0x00000400U
#define LRFDPBE_EVTCLR0_SYSTCMP1_M                                  0x00000400U
#define LRFDPBE_EVTCLR0_SYSTCMP1_S                                          10U
#define LRFDPBE_EVTCLR0_SYSTCMP1_CLEAR                              0x00000400U
#define LRFDPBE_EVTCLR0_SYSTCMP1_RETAIN                             0x00000000U

// Field:     [9] SYSTCMP0 
//
// Clear event EVT0.SYSTCMP0 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_SYSTCMP0                                    0x00000200U
#define LRFDPBE_EVTCLR0_SYSTCMP0_M                                  0x00000200U
#define LRFDPBE_EVTCLR0_SYSTCMP0_S                                           9U
#define LRFDPBE_EVTCLR0_SYSTCMP0_CLEAR                              0x00000200U
#define LRFDPBE_EVTCLR0_SYSTCMP0_RETAIN                             0x00000000U

// Field:     [8] MDMMSGBOX 
//
// Clear event EVT0.MDMMSGBOX 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_MDMMSGBOX                                   0x00000100U
#define LRFDPBE_EVTCLR0_MDMMSGBOX_M                                 0x00000100U
#define LRFDPBE_EVTCLR0_MDMMSGBOX_S                                          8U
#define LRFDPBE_EVTCLR0_MDMMSGBOX_CLEAR                             0x00000100U
#define LRFDPBE_EVTCLR0_MDMMSGBOX_RETAIN                            0x00000000U

// Field:     [7] RFEMSGBOX 
//
// Clear event EVT0.RFEMSGBOX 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_RFEMSGBOX                                   0x00000080U
#define LRFDPBE_EVTCLR0_RFEMSGBOX_M                                 0x00000080U
#define LRFDPBE_EVTCLR0_RFEMSGBOX_S                                          7U
#define LRFDPBE_EVTCLR0_RFEMSGBOX_CLEAR                             0x00000080U
#define LRFDPBE_EVTCLR0_RFEMSGBOX_RETAIN                            0x00000000U

// Field:     [6] RFEDAT 
//
// Clear event EVT0.RFEDAT 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_RFEDAT                                      0x00000040U
#define LRFDPBE_EVTCLR0_RFEDAT_M                                    0x00000040U
#define LRFDPBE_EVTCLR0_RFEDAT_S                                             6U
#define LRFDPBE_EVTCLR0_RFEDAT_CLEAR                                0x00000040U
#define LRFDPBE_EVTCLR0_RFEDAT_RETAIN                               0x00000000U

// Field:     [5] RFECMD 
//
// Clear event EVT0.RFECMD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_RFECMD                                      0x00000020U
#define LRFDPBE_EVTCLR0_RFECMD_M                                    0x00000020U
#define LRFDPBE_EVTCLR0_RFECMD_S                                             5U
#define LRFDPBE_EVTCLR0_RFECMD_CLEAR                                0x00000020U
#define LRFDPBE_EVTCLR0_RFECMD_RETAIN                               0x00000000U

// Field:     [4] MDMDAT 
//
// Clear event EVT0.MDMDAT 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_MDMDAT                                      0x00000010U
#define LRFDPBE_EVTCLR0_MDMDAT_M                                    0x00000010U
#define LRFDPBE_EVTCLR0_MDMDAT_S                                             4U
#define LRFDPBE_EVTCLR0_MDMDAT_CLEAR                                0x00000010U
#define LRFDPBE_EVTCLR0_MDMDAT_RETAIN                               0x00000000U

// Field:     [3] MDMCMD 
//
// Clear event EVT0.MDMCMD 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_MDMCMD                                      0x00000008U
#define LRFDPBE_EVTCLR0_MDMCMD_M                                    0x00000008U
#define LRFDPBE_EVTCLR0_MDMCMD_S                                             3U
#define LRFDPBE_EVTCLR0_MDMCMD_CLEAR                                0x00000008U
#define LRFDPBE_EVTCLR0_MDMCMD_RETAIN                               0x00000000U

// Field:     [2] TIMER1 
//
// Clear event EVT0.TIMER1 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_TIMER1                                      0x00000004U
#define LRFDPBE_EVTCLR0_TIMER1_M                                    0x00000004U
#define LRFDPBE_EVTCLR0_TIMER1_S                                             2U
#define LRFDPBE_EVTCLR0_TIMER1_CLEAR                                0x00000004U
#define LRFDPBE_EVTCLR0_TIMER1_RETAIN                               0x00000000U

// Field:     [1] TIMER0 
//
// Clear event EVT0.TIMER0 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_TIMER0                                      0x00000002U
#define LRFDPBE_EVTCLR0_TIMER0_M                                    0x00000002U
#define LRFDPBE_EVTCLR0_TIMER0_S                                             1U
#define LRFDPBE_EVTCLR0_TIMER0_CLEAR                                0x00000002U
#define LRFDPBE_EVTCLR0_TIMER0_RETAIN                               0x00000000U

// Field:     [0] PBEAPI 
//
// Clear event EVT0.PBEAPI 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR0_PBEAPI                                      0x00000001U
#define LRFDPBE_EVTCLR0_PBEAPI_M                                    0x00000001U
#define LRFDPBE_EVTCLR0_PBEAPI_S                                             0U
#define LRFDPBE_EVTCLR0_PBEAPI_CLEAR                                0x00000001U
#define LRFDPBE_EVTCLR0_PBEAPI_RETAIN                               0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_EVTCLR1
//
//*****************************************************************************
// Field:    [12] TXRDBTHR 
//
// Clear event EVT0.TXRDBTHR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_TXRDBTHR                                    0x00001000U
#define LRFDPBE_EVTCLR1_TXRDBTHR_M                                  0x00001000U
#define LRFDPBE_EVTCLR1_TXRDBTHR_S                                          12U
#define LRFDPBE_EVTCLR1_TXRDBTHR_CLEAR                              0x00001000U
#define LRFDPBE_EVTCLR1_TXRDBTHR_RETAIN                             0x00000000U

// Field:    [11] TXWRBTHR 
//
// Clear event EVT0.TXWRBTHR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_TXWRBTHR                                    0x00000800U
#define LRFDPBE_EVTCLR1_TXWRBTHR_M                                  0x00000800U
#define LRFDPBE_EVTCLR1_TXWRBTHR_S                                          11U
#define LRFDPBE_EVTCLR1_TXWRBTHR_CLEAR                              0x00000800U
#define LRFDPBE_EVTCLR1_TXWRBTHR_RETAIN                             0x00000000U

// Field:    [10] RXRDBTHR 
//
// Clear event EVT0.RXRDBTHR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_RXRDBTHR                                    0x00000400U
#define LRFDPBE_EVTCLR1_RXRDBTHR_M                                  0x00000400U
#define LRFDPBE_EVTCLR1_RXRDBTHR_S                                          10U
#define LRFDPBE_EVTCLR1_RXRDBTHR_CLEAR                              0x00000400U
#define LRFDPBE_EVTCLR1_RXRDBTHR_RETAIN                             0x00000000U

// Field:     [9] RXWRBTHR 
//
// Clear event EVT0.RXWRBTHR 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_RXWRBTHR                                    0x00000200U
#define LRFDPBE_EVTCLR1_RXWRBTHR_M                                  0x00000200U
#define LRFDPBE_EVTCLR1_RXWRBTHR_S                                           9U
#define LRFDPBE_EVTCLR1_RXWRBTHR_CLEAR                              0x00000200U
#define LRFDPBE_EVTCLR1_RXWRBTHR_RETAIN                             0x00000000U

// Field:     [8] MDMPROG 
//
// Clear event EVT0.MDMPROG 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_MDMPROG                                     0x00000100U
#define LRFDPBE_EVTCLR1_MDMPROG_M                                   0x00000100U
#define LRFDPBE_EVTCLR1_MDMPROG_S                                            8U
#define LRFDPBE_EVTCLR1_MDMPROG_CLEAR                               0x00000100U
#define LRFDPBE_EVTCLR1_MDMPROG_RETAIN                              0x00000000U

// Field:     [7] PBEGPI7 
//
// Clear event EVT0.PBEGPI7 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI7                                     0x00000080U
#define LRFDPBE_EVTCLR1_PBEGPI7_M                                   0x00000080U
#define LRFDPBE_EVTCLR1_PBEGPI7_S                                            7U
#define LRFDPBE_EVTCLR1_PBEGPI7_CLEAR                               0x00000080U
#define LRFDPBE_EVTCLR1_PBEGPI7_RETAIN                              0x00000000U

// Field:     [6] PBEGPI6 
//
// Clear event EVT0.PBEGPI6 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI6                                     0x00000040U
#define LRFDPBE_EVTCLR1_PBEGPI6_M                                   0x00000040U
#define LRFDPBE_EVTCLR1_PBEGPI6_S                                            6U
#define LRFDPBE_EVTCLR1_PBEGPI6_CLEAR                               0x00000040U
#define LRFDPBE_EVTCLR1_PBEGPI6_RETAIN                              0x00000000U

// Field:     [5] PBEGPI5 
//
// Clear event EVT0.PBEGPI5 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI5                                     0x00000020U
#define LRFDPBE_EVTCLR1_PBEGPI5_M                                   0x00000020U
#define LRFDPBE_EVTCLR1_PBEGPI5_S                                            5U
#define LRFDPBE_EVTCLR1_PBEGPI5_CLEAR                               0x00000020U
#define LRFDPBE_EVTCLR1_PBEGPI5_RETAIN                              0x00000000U

// Field:     [4] PBEGPI4 
//
// Clear event EVT0.PBEGPI4 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI4                                     0x00000010U
#define LRFDPBE_EVTCLR1_PBEGPI4_M                                   0x00000010U
#define LRFDPBE_EVTCLR1_PBEGPI4_S                                            4U
#define LRFDPBE_EVTCLR1_PBEGPI4_CLEAR                               0x00000010U
#define LRFDPBE_EVTCLR1_PBEGPI4_RETAIN                              0x00000000U

// Field:     [3] PBEGPI3 
//
// Clear event EVT0.PBEGPI3 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI3                                     0x00000008U
#define LRFDPBE_EVTCLR1_PBEGPI3_M                                   0x00000008U
#define LRFDPBE_EVTCLR1_PBEGPI3_S                                            3U
#define LRFDPBE_EVTCLR1_PBEGPI3_CLEAR                               0x00000008U
#define LRFDPBE_EVTCLR1_PBEGPI3_RETAIN                              0x00000000U

// Field:     [2] PBEGPI2 
//
// Clear event EVT0.PBEGPI2 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI2                                     0x00000004U
#define LRFDPBE_EVTCLR1_PBEGPI2_M                                   0x00000004U
#define LRFDPBE_EVTCLR1_PBEGPI2_S                                            2U
#define LRFDPBE_EVTCLR1_PBEGPI2_CLEAR                               0x00000004U
#define LRFDPBE_EVTCLR1_PBEGPI2_RETAIN                              0x00000000U

// Field:     [1] PBEGPI1 
//
// Clear event EVT0.PBEGPI1 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI1                                     0x00000002U
#define LRFDPBE_EVTCLR1_PBEGPI1_M                                   0x00000002U
#define LRFDPBE_EVTCLR1_PBEGPI1_S                                            1U
#define LRFDPBE_EVTCLR1_PBEGPI1_CLEAR                               0x00000002U
#define LRFDPBE_EVTCLR1_PBEGPI1_RETAIN                              0x00000000U

// Field:     [0] PBEGPI0 
//
// Clear event EVT0.PBEGPI0 
// ENUMs: 
// CLEAR                    The bit is 1 
// RETAIN                   The bit is 0 
#define LRFDPBE_EVTCLR1_PBEGPI0                                     0x00000001U
#define LRFDPBE_EVTCLR1_PBEGPI0_M                                   0x00000001U
#define LRFDPBE_EVTCLR1_PBEGPI0_S                                            0U
#define LRFDPBE_EVTCLR1_PBEGPI0_CLEAR                               0x00000001U
#define LRFDPBE_EVTCLR1_PBEGPI0_RETAIN                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_PDREQ
//
//*****************************************************************************
// Field:     [0] TOPSMPDREQ 
//
// Requests power down for TOPsm core. If the TOPsm has an ongoing memory 
// access, the hardware will safely gate the clock after the transaction has 
// completed. 
// ENUMs: 
// ON                       The bit is 1 
// OFF                      The bit is 0 
#define LRFDPBE_PDREQ_TOPSMPDREQ                                    0x00000001U
#define LRFDPBE_PDREQ_TOPSMPDREQ_M                                  0x00000001U
#define LRFDPBE_PDREQ_TOPSMPDREQ_S                                           0U
#define LRFDPBE_PDREQ_TOPSMPDREQ_ON                                 0x00000001U
#define LRFDPBE_PDREQ_TOPSMPDREQ_OFF                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_API
//
//*****************************************************************************
// Field:   [4:0] PBECMD 
//
// PBE Command 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_API_PBECMD_W                                                 5U
#define LRFDPBE_API_PBECMD_M                                        0x0000001FU
#define LRFDPBE_API_PBECMD_S                                                 0U
#define LRFDPBE_API_PBECMD_ALLONES                                  0x0000001FU
#define LRFDPBE_API_PBECMD_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MCEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data to send to the MCE. Writing to this register will trigger an event in 
// the MCE, and the data value written here will be readable in 
// LRFDMDM:PBEDATIN0 register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MCEDATOUT0_VAL_W                                            16U
#define LRFDPBE_MCEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDPBE_MCEDATOUT0_VAL_S                                             0U
#define LRFDPBE_MCEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_MCEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MCEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data received from MCE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MCEDATIN0_VAL_W                                             16U
#define LRFDPBE_MCEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDPBE_MCEDATIN0_VAL_S                                              0U
#define LRFDPBE_MCEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDPBE_MCEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MCECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command to send to the MCE. Writing to this register will trigger an event 
// in the MCE, and the command value written here will be readable in 
// LRFDMDM:PBECMDIN register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MCECMDOUT_VAL_W                                              4U
#define LRFDPBE_MCECMDOUT_VAL_M                                     0x0000000FU
#define LRFDPBE_MCECMDOUT_VAL_S                                              0U
#define LRFDPBE_MCECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDPBE_MCECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MCECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command received from MCE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MCECMDIN_VAL_W                                               4U
#define LRFDPBE_MCECMDIN_VAL_M                                      0x0000000FU
#define LRFDPBE_MCECMDIN_VAL_S                                               0U
#define LRFDPBE_MCECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDPBE_MCECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMAPI
//
//*****************************************************************************
// Field:   [7:4] PROTOCOLID 
//
// Protocol ID 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMAPI_PROTOCOLID_W                                          4U
#define LRFDPBE_MDMAPI_PROTOCOLID_M                                 0x000000F0U
#define LRFDPBE_MDMAPI_PROTOCOLID_S                                          4U
#define LRFDPBE_MDMAPI_PROTOCOLID_ALLONES                           0x000000F0U
#define LRFDPBE_MDMAPI_PROTOCOLID_ALLZEROS                          0x00000000U

// Field:   [3:0] MDMCMD 
//
// Modem command 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMAPI_MDMCMD_W                                              4U
#define LRFDPBE_MDMAPI_MDMCMD_M                                     0x0000000FU
#define LRFDPBE_MDMAPI_MDMCMD_S                                              0U
#define LRFDPBE_MDMAPI_MDMCMD_ALLONES                               0x0000000FU
#define LRFDPBE_MDMAPI_MDMCMD_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMMSGBOX
//
//*****************************************************************************
// Field:   [7:0] VALUE 
//
// Diverse status, error, report bits from MCE. Controlled by software. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMMSGBOX_VALUE_W                                            8U
#define LRFDPBE_MDMMSGBOX_VALUE_M                                   0x000000FFU
#define LRFDPBE_MDMMSGBOX_VALUE_S                                            0U
#define LRFDPBE_MDMMSGBOX_VALUE_ALLONES                             0x000000FFU
#define LRFDPBE_MDMMSGBOX_VALUE_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FREQ
//
//*****************************************************************************
// Field:  [15:0] OFFSET 
//
// Frequency Offset from MCE. Controlled by software. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_FREQ_OFFSET_W                                               16U
#define LRFDPBE_FREQ_OFFSET_M                                       0x0000FFFFU
#define LRFDPBE_FREQ_OFFSET_S                                                0U
#define LRFDPBE_FREQ_OFFSET_ALLONES                                 0x0000FFFFU
#define LRFDPBE_FREQ_OFFSET_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMLQI
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// LQI status from MCE. Controlled by software. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMLQI_VAL_W                                                 8U
#define LRFDPBE_MDMLQI_VAL_M                                        0x000000FFU
#define LRFDPBE_MDMLQI_VAL_S                                                 0U
#define LRFDPBE_MDMLQI_VAL_ALLONES                                  0x000000FFU
#define LRFDPBE_MDMLQI_VAL_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFEDATOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data to send to the RFE. Writing to this register will trigger an event in 
// the RFE, and the data value written here will be readable in 
// LRFDRFE:PBEDATIN0 register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFEDATOUT0_VAL_W                                            16U
#define LRFDPBE_RFEDATOUT0_VAL_M                                    0x0000FFFFU
#define LRFDPBE_RFEDATOUT0_VAL_S                                             0U
#define LRFDPBE_RFEDATOUT0_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_RFEDATOUT0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFEDATIN0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Data received from RFE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFEDATIN0_VAL_W                                             16U
#define LRFDPBE_RFEDATIN0_VAL_M                                     0x0000FFFFU
#define LRFDPBE_RFEDATIN0_VAL_S                                              0U
#define LRFDPBE_RFEDATIN0_VAL_ALLONES                               0x0000FFFFU
#define LRFDPBE_RFEDATIN0_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFECMDOUT
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command to send to the RFE. Writing to this register will trigger an event 
// in the RFE, and the command value written here will be readable in 
// LRFDRFE:PBECMDIN register. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFECMDOUT_VAL_W                                              4U
#define LRFDPBE_RFECMDOUT_VAL_M                                     0x0000000FU
#define LRFDPBE_RFECMDOUT_VAL_S                                              0U
#define LRFDPBE_RFECMDOUT_VAL_ALLONES                               0x0000000FU
#define LRFDPBE_RFECMDOUT_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFECMDIN
//
//*****************************************************************************
// Field:   [3:0] VAL 
//
// Command received from RFE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFECMDIN_VAL_W                                               4U
#define LRFDPBE_RFECMDIN_VAL_M                                      0x0000000FU
#define LRFDPBE_RFECMDIN_VAL_S                                               0U
#define LRFDPBE_RFECMDIN_VAL_ALLONES                                0x0000000FU
#define LRFDPBE_RFECMDIN_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFEAPI
//
//*****************************************************************************
// Field:   [7:4] PROTOCOLID 
//
// Protocol ID 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFEAPI_PROTOCOLID_W                                          4U
#define LRFDPBE_RFEAPI_PROTOCOLID_M                                 0x000000F0U
#define LRFDPBE_RFEAPI_PROTOCOLID_S                                          4U
#define LRFDPBE_RFEAPI_PROTOCOLID_ALLONES                           0x000000F0U
#define LRFDPBE_RFEAPI_PROTOCOLID_ALLZEROS                          0x00000000U

// Field:   [3:0] RFECMD 
//
// RFE Command 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFEAPI_RFECMD_W                                              4U
#define LRFDPBE_RFEAPI_RFECMD_M                                     0x0000000FU
#define LRFDPBE_RFEAPI_RFECMD_S                                              0U
#define LRFDPBE_RFEAPI_RFECMD_ALLONES                               0x0000000FU
#define LRFDPBE_RFEAPI_RFECMD_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFECMDPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFECMDPAR0_VAL_W                                            16U
#define LRFDPBE_RFECMDPAR0_VAL_M                                    0x0000FFFFU
#define LRFDPBE_RFECMDPAR0_VAL_S                                             0U
#define LRFDPBE_RFECMDPAR0_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_RFECMDPAR0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFECMDPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFECMDPAR1_VAL_W                                            16U
#define LRFDPBE_RFECMDPAR1_VAL_M                                    0x0000FFFFU
#define LRFDPBE_RFECMDPAR1_VAL_S                                             0U
#define LRFDPBE_RFECMDPAR1_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_RFECMDPAR1_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFEMSGBOX
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Diverse status, error, report bits from RFE 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFEMSGBOX_VAL_W                                              8U
#define LRFDPBE_RFEMSGBOX_VAL_M                                     0x000000FFU
#define LRFDPBE_RFEMSGBOX_VAL_S                                              0U
#define LRFDPBE_RFEMSGBOX_VAL_ALLONES                               0x000000FFU
#define LRFDPBE_RFEMSGBOX_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFERSSI
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Current RSSI value (signed). If this register reads as -128 (0x80) it means 
// that the value is not yet valid. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFERSSI_VAL_W                                                8U
#define LRFDPBE_RFERSSI_VAL_M                                       0x000000FFU
#define LRFDPBE_RFERSSI_VAL_S                                                0U
#define LRFDPBE_RFERSSI_VAL_ALLONES                                 0x000000FFU
#define LRFDPBE_RFERSSI_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFERSSIMAX
//
//*****************************************************************************
// Field:   [7:0] VAL 
//
// Maximum RSSI value since start of measurements cycle. If this field reads as 
// -128 (0x80) it means that the value is not yet valid. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFERSSIMAX_VAL_W                                             8U
#define LRFDPBE_RFERSSIMAX_VAL_M                                    0x000000FFU
#define LRFDPBE_RFERSSIMAX_VAL_S                                             0U
#define LRFDPBE_RFERSSIMAX_VAL_ALLONES                              0x000000FFU
#define LRFDPBE_RFERSSIMAX_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RFERFGAIN
//
//*****************************************************************************
// Field:   [7:0] DBGAIN 
//
// Current RF front-end gain, in dB 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RFERFGAIN_DBGAIN_W                                           8U
#define LRFDPBE_RFERFGAIN_DBGAIN_M                                  0x000000FFU
#define LRFDPBE_RFERFGAIN_DBGAIN_S                                           0U
#define LRFDPBE_RFERFGAIN_DBGAIN_ALLONES                            0x000000FFU
#define LRFDPBE_RFERFGAIN_DBGAIN_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMSYNCAL
//
//*****************************************************************************
// Field:  [15:0] SWALSB 
//
// Sync word A bits 15:0. Sync words shorter than 32 bits must be stored as 
// most signicant bits of sync word A. The sync word is expected to be 
// transmitted/received in lsb to msb order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMSYNCAL_SWALSB_W                                          16U
#define LRFDPBE_MDMSYNCAL_SWALSB_M                                  0x0000FFFFU
#define LRFDPBE_MDMSYNCAL_SWALSB_S                                           0U
#define LRFDPBE_MDMSYNCAL_SWALSB_ALLONES                            0x0000FFFFU
#define LRFDPBE_MDMSYNCAL_SWALSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMSYNCAH
//
//*****************************************************************************
// Field:  [15:0] SWAMSB 
//
// Sync word A bits 31:16. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word A. The sync word is expected to be 
// transmitted/received in lsb to msb order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMSYNCAH_SWAMSB_W                                          16U
#define LRFDPBE_MDMSYNCAH_SWAMSB_M                                  0x0000FFFFU
#define LRFDPBE_MDMSYNCAH_SWAMSB_S                                           0U
#define LRFDPBE_MDMSYNCAH_SWAMSB_ALLONES                            0x0000FFFFU
#define LRFDPBE_MDMSYNCAH_SWAMSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMSYNCBL
//
//*****************************************************************************
// Field:  [15:0] SWBLSB 
//
// Sync word B bits 15:0. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word B. The sync word is expected to be 
// transmitted/received in lsb to msb order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMSYNCBL_SWBLSB_W                                          16U
#define LRFDPBE_MDMSYNCBL_SWBLSB_M                                  0x0000FFFFU
#define LRFDPBE_MDMSYNCBL_SWBLSB_S                                           0U
#define LRFDPBE_MDMSYNCBL_SWBLSB_ALLONES                            0x0000FFFFU
#define LRFDPBE_MDMSYNCBL_SWBLSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMSYNCBH
//
//*****************************************************************************
// Field:  [15:0] SWBMSB 
//
// Sync word B bits 31:16. Sync words shorter than 32 bits must be stored as 
// most significant bits of sync word B. The sync word is expected to be 
// transmitted/received in lsb to msb order. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMSYNCBH_SWBMSB_W                                          16U
#define LRFDPBE_MDMSYNCBH_SWBMSB_M                                  0x0000FFFFU
#define LRFDPBE_MDMSYNCBH_SWBMSB_S                                           0U
#define LRFDPBE_MDMSYNCBH_SWBMSB_ALLONES                            0x0000FFFFU
#define LRFDPBE_MDMSYNCBH_SWBMSB_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMCMDPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 0. Software defined function. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMCMDPAR0_VAL_W                                            16U
#define LRFDPBE_MDMCMDPAR0_VAL_M                                    0x0000FFFFU
#define LRFDPBE_MDMCMDPAR0_VAL_S                                             0U
#define LRFDPBE_MDMCMDPAR0_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_MDMCMDPAR0_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMCMDPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 1. Software defined function. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMCMDPAR1_VAL_W                                            16U
#define LRFDPBE_MDMCMDPAR1_VAL_M                                    0x0000FFFFU
#define LRFDPBE_MDMCMDPAR1_VAL_S                                             0U
#define LRFDPBE_MDMCMDPAR1_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_MDMCMDPAR1_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMCMDPAR2
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 2. Software defined function. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMCMDPAR2_VAL_W                                            16U
#define LRFDPBE_MDMCMDPAR2_VAL_M                                    0x0000FFFFU
#define LRFDPBE_MDMCMDPAR2_VAL_S                                             0U
#define LRFDPBE_MDMCMDPAR2_VAL_ALLONES                              0x0000FFFFU
#define LRFDPBE_MDMCMDPAR2_VAL_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_POLY0L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 0 polynomial taps, lower half 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_POLY0L_VALLSB_W                                             16U
#define LRFDPBE_POLY0L_VALLSB_M                                     0x0000FFFFU
#define LRFDPBE_POLY0L_VALLSB_S                                              0U
#define LRFDPBE_POLY0L_VALLSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_POLY0L_VALLSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_POLY0H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 0 polynomial taps, upper half 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_POLY0H_VALMSB_W                                             16U
#define LRFDPBE_POLY0H_VALMSB_M                                     0x0000FFFFU
#define LRFDPBE_POLY0H_VALMSB_S                                              0U
#define LRFDPBE_POLY0H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_POLY0H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_POLY1L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 1 polynomial taps, low part 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_POLY1L_VALLSB_W                                             16U
#define LRFDPBE_POLY1L_VALLSB_M                                     0x0000FFFFU
#define LRFDPBE_POLY1L_VALLSB_S                                              0U
#define LRFDPBE_POLY1L_VALLSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_POLY1L_VALLSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_POLY1H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 1 polynomial taps, high part 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_POLY1H_VALMSB_W                                             16U
#define LRFDPBE_POLY1H_VALMSB_M                                     0x0000FFFFU
#define LRFDPBE_POLY1H_VALMSB_S                                              0U
#define LRFDPBE_POLY1H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_POLY1H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_PHACFG
//
//*****************************************************************************
// Field:   [2:1] MODE1 
//
// Dual LFSR operating mode 
// ENUMs: 
// PARAL                    LFSR0 and LFSR1 are operated in parallel 
// CASC                     LFSR0 whitener is followed by LFSR1 CRC 
// INDEP                    LFSR0 and LFSR1 are operated independently 
#define LRFDPBE_PHACFG_MODE1_W                                               2U
#define LRFDPBE_PHACFG_MODE1_M                                      0x00000006U
#define LRFDPBE_PHACFG_MODE1_S                                               1U
#define LRFDPBE_PHACFG_MODE1_PARAL                                  0x00000004U
#define LRFDPBE_PHACFG_MODE1_CASC                                   0x00000002U
#define LRFDPBE_PHACFG_MODE1_INDEP                                  0x00000000U

// Field:     [0] MODE0 
//
// LFSR 0 operating mode 
// ENUMs: 
// WHITE                    LFSR 0 is in whitening mode 
// CRC                      LFSR 0 is in CRC mode 
#define LRFDPBE_PHACFG_MODE0                                        0x00000001U
#define LRFDPBE_PHACFG_MODE0_M                                      0x00000001U
#define LRFDPBE_PHACFG_MODE0_S                                               0U
#define LRFDPBE_PHACFG_MODE0_WHITE                                  0x00000001U
#define LRFDPBE_PHACFG_MODE0_CRC                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG0
//
//*****************************************************************************
// Field:     [7] TXIRQMET 
//
// Select source for pbe_irq(17) 
// ENUMs: 
// TXRDBTHR                 The TX FIFO contains TXFRBTHRS or more readable 
//                          bytes. 
// TXWRBTHR                 The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
#define LRFDPBE_FCFG0_TXIRQMET                                      0x00000080U
#define LRFDPBE_FCFG0_TXIRQMET_M                                    0x00000080U
#define LRFDPBE_FCFG0_TXIRQMET_S                                             7U
#define LRFDPBE_FCFG0_TXIRQMET_TXRDBTHR                             0x00000080U
#define LRFDPBE_FCFG0_TXIRQMET_TXWRBTHR                             0x00000000U

// Field:     [6] RXIRQMET 
//
// Select source for pbe_irq(16) 
// ENUMs: 
// RXWRBTHR                 The RX FIFO contains RXFWBTHRS or more writable 
//                          bytes. 
// RXRDBTHR                 The RX FIFO contains RXFRBTHRS or more readable 
//                          bytes. 
#define LRFDPBE_FCFG0_RXIRQMET                                      0x00000040U
#define LRFDPBE_FCFG0_RXIRQMET_M                                    0x00000040U
#define LRFDPBE_FCFG0_RXIRQMET_S                                             6U
#define LRFDPBE_FCFG0_RXIRQMET_RXWRBTHR                             0x00000040U
#define LRFDPBE_FCFG0_RXIRQMET_RXRDBTHR                             0x00000000U

// Field:     [5] TXACOM 
//
// Automatic FIFO commit configuration 
// ENUMs: 
// EN                       Always set TXSWP := TXWP 
// DIS                      commit TXFIFO only on command 0x95 
#define LRFDPBE_FCFG0_TXACOM                                        0x00000020U
#define LRFDPBE_FCFG0_TXACOM_M                                      0x00000020U
#define LRFDPBE_FCFG0_TXACOM_S                                               5U
#define LRFDPBE_FCFG0_TXACOM_EN                                     0x00000020U
#define LRFDPBE_FCFG0_TXACOM_DIS                                    0x00000000U

// Field:     [4] TXADEAL 
//
// Automatic deallocation setting 
// ENUMs: 
// EN                       Always set TXFSRP := TXFRP. 
// DIS                      Deallocate TXFIFO only on command 0x92 
#define LRFDPBE_FCFG0_TXADEAL                                       0x00000010U
#define LRFDPBE_FCFG0_TXADEAL_M                                     0x00000010U
#define LRFDPBE_FCFG0_TXADEAL_S                                              4U
#define LRFDPBE_FCFG0_TXADEAL_EN                                    0x00000010U
#define LRFDPBE_FCFG0_TXADEAL_DIS                                   0x00000000U

// Field:     [1] RXACOM 
//
// Automatic FIFO commit configuration 
// ENUMs: 
// EN                       Always set RXFSWP := RXFWP 
// DIS                      commit rxfifo only on command 0x85 
#define LRFDPBE_FCFG0_RXACOM                                        0x00000002U
#define LRFDPBE_FCFG0_RXACOM_M                                      0x00000002U
#define LRFDPBE_FCFG0_RXACOM_S                                               1U
#define LRFDPBE_FCFG0_RXACOM_EN                                     0x00000002U
#define LRFDPBE_FCFG0_RXACOM_DIS                                    0x00000000U

// Field:     [0] RXADEAL 
//
// Automatic deallocation setting 
// ENUMs: 
// EN                       Always set RXFSRP := RXFRP. 
// DIS                      Deallocate RXFIFO only on command 0x82 
#define LRFDPBE_FCFG0_RXADEAL                                       0x00000001U
#define LRFDPBE_FCFG0_RXADEAL_M                                     0x00000001U
#define LRFDPBE_FCFG0_RXADEAL_S                                              0U
#define LRFDPBE_FCFG0_RXADEAL_EN                                    0x00000001U
#define LRFDPBE_FCFG0_RXADEAL_DIS                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG1
//
//*****************************************************************************
// Field:   [8:0] TXSTRT 
//
// FIFO start address, offset from start of BUFRAM. Address is 32-bit word 
// address (not byte address) 
// ENUMs: 
// ONES                     All bits are 1s 
// ZEROS                    All bits are zero 
#define LRFDPBE_FCFG1_TXSTRT_W                                               9U
#define LRFDPBE_FCFG1_TXSTRT_M                                      0x000001FFU
#define LRFDPBE_FCFG1_TXSTRT_S                                               0U
#define LRFDPBE_FCFG1_TXSTRT_ONES                                   0x000001FFU
#define LRFDPBE_FCFG1_TXSTRT_ZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG2
//
//*****************************************************************************
// Field:  [10:8] TXHSIZE 
//
// Select transfer size to calculate DMA_SREQ_TRIGGER MD(more data) and FREE, 
// for both RX FIFO and TX FIFO. 
// ENUMs: 
// WORD                     MCU receives IRQ when the TX FIFO contains more or 
//                          equal amount of data than the configured 
//                          threshold. 
// HALFW                    MCU receives IRQ when the TX FIFO contains less 
//                          amount of data than the configured threshold. 
// BYTE                     MCU receives IRQ when the TX FIFO contains less 
//                          amount of data than the configured threshold. 
#define LRFDPBE_FCFG2_TXHSIZE_W                                              3U
#define LRFDPBE_FCFG2_TXHSIZE_M                                     0x00000700U
#define LRFDPBE_FCFG2_TXHSIZE_S                                              8U
#define LRFDPBE_FCFG2_TXHSIZE_WORD                                  0x00000200U
#define LRFDPBE_FCFG2_TXHSIZE_HALFW                                 0x00000100U
#define LRFDPBE_FCFG2_TXHSIZE_BYTE                                  0x00000000U

// Field:   [7:0] TXSIZE 
//
// TXFIFO size in number of 32-bit words 
// ENUMs: 
// ONES                     All bits are 1s 
// ZEROS                    All bits are zero 
#define LRFDPBE_FCFG2_TXSIZE_W                                               8U
#define LRFDPBE_FCFG2_TXSIZE_M                                      0x000000FFU
#define LRFDPBE_FCFG2_TXSIZE_S                                               0U
#define LRFDPBE_FCFG2_TXSIZE_ONES                                   0x000000FFU
#define LRFDPBE_FCFG2_TXSIZE_ZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG3
//
//*****************************************************************************
// Field:   [8:0] RXSTRT 
//
// FIFO start address, offset from start of BUFRAM. Address is 32-bit word 
// adress (not byte address) 
// ENUMs: 
// ONES                     All bits are 1s 
// ZEROS                    All bits are zero 
#define LRFDPBE_FCFG3_RXSTRT_W                                               9U
#define LRFDPBE_FCFG3_RXSTRT_M                                      0x000001FFU
#define LRFDPBE_FCFG3_RXSTRT_S                                               0U
#define LRFDPBE_FCFG3_RXSTRT_ONES                                   0x000001FFU
#define LRFDPBE_FCFG3_RXSTRT_ZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG4
//
//*****************************************************************************
// Field:  [10:8] RXHSIZE 
//
// Select transfer size to calculate DMA_SREQ_TRIGGER MD(more data) and FREE, 
// for both RX FIFO and TX FIFO. 
// ENUMs: 
// WORD                     MCU receives IRQ when the TX FIFO contains more or 
//                          equal amount of data than the configured 
//                          threshold. 
// HALFW                    MCU receives IRQ when the TX FIFO contains less 
//                          amount of data than the configured threshold. 
// BYTE                     MCU receives IRQ when the TX FIFO contains less 
//                          amount of data than the configured threshold. 
#define LRFDPBE_FCFG4_RXHSIZE_W                                              3U
#define LRFDPBE_FCFG4_RXHSIZE_M                                     0x00000700U
#define LRFDPBE_FCFG4_RXHSIZE_S                                              8U
#define LRFDPBE_FCFG4_RXHSIZE_WORD                                  0x00000200U
#define LRFDPBE_FCFG4_RXHSIZE_HALFW                                 0x00000100U
#define LRFDPBE_FCFG4_RXHSIZE_BYTE                                  0x00000000U

// Field:   [7:0] RXSIZE 
//
// RXFIFO size in number of 32-bit words 
// ENUMs: 
// ONES                     Always set RXFSWP := RXFWP 
// ZEROS                    commit rxfifo only on command 0x85 
#define LRFDPBE_FCFG4_RXSIZE_W                                               8U
#define LRFDPBE_FCFG4_RXSIZE_M                                      0x000000FFU
#define LRFDPBE_FCFG4_RXSIZE_S                                               0U
#define LRFDPBE_FCFG4_RXSIZE_ONES                                   0x000000FFU
#define LRFDPBE_FCFG4_RXSIZE_ZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCFG5
//
//*****************************************************************************
// Field:   [8:6] DMASREQ 
//
// DMA trigger select. Triggers DMA when selected trigger occurs. Note that it 
// is a mix of pulse type and level type triggers 
// ENUMs: 
// TXFIFOFREE               The TX FIFO contains FCFG2_TXHSIZE or more 
//                          writable bytes. 
// TXFIFOMD                 The TX FIFO contains FCFG2_TXHSIZE or more 
//                          readable bytes. 
// RXFIFOFREE               The RX FIFO contains FCFG4_RXHSIZE or more 
//                          writable bytes. 
// RXFIFOMD                 The RX FIFO contains FCFG4_RXHSIZE or more 
//                          readable bytes. 
// NONE                     No triggers generated 
#define LRFDPBE_FCFG5_DMASREQ_W                                              3U
#define LRFDPBE_FCFG5_DMASREQ_M                                     0x000001C0U
#define LRFDPBE_FCFG5_DMASREQ_S                                              6U
#define LRFDPBE_FCFG5_DMASREQ_TXFIFOFREE                            0x00000100U
#define LRFDPBE_FCFG5_DMASREQ_TXFIFOMD                              0x000000C0U
#define LRFDPBE_FCFG5_DMASREQ_RXFIFOFREE                            0x00000080U
#define LRFDPBE_FCFG5_DMASREQ_RXFIFOMD                              0x00000040U
#define LRFDPBE_FCFG5_DMASREQ_NONE                                  0x00000000U

// Field:   [4:0] DMAREQ 
//
// DMA trigger select. Triggers DMA when selected trigger occurs. Note that it 
// is a mix of pulse type and level type triggers 
// ENUMs: 
// TXFIFO_COMMIT            TXFIFO is committed 
// TXFIFO_DISCARD           TXFIFO is discarded 
// TXFIFO_RETRY             TXFIFO is retried 
// TXFIFO_DEALLOC           TXFIFO is deallocated 
// TXFIFO_RESET             TXFIFO is reset 
// TXWRBTHR_MET             The TX FIFO contains TXFWBTHRS or more writable 
//                          bytes. 
// TXRDBTHR_MET             The TX FIFO contains TXFRBTHRS or more readable 
//                          bytes. 
// RXFIFO_COMMIT            RXFIFO is committed 
// RXFIFO_DISCARD           RXFIFO is discarded 
// RXFIFO_RETRY             RXFIFO is retried 
// RXFIFO_DEALLOC           RXFIFO is deallocated 
// RXFIFO_RESET             RXFIFO is reset 
// RXWRBTHR_MET             The RX FIFO contains RXFWBTHRS or more writable 
//                          bytes. 
// RXRDBTHR_MET             The RX FIFO contains RXFRBTHRS or more readable 
//                          bytes. 
// NONE                     No triggers generated 
#define LRFDPBE_FCFG5_DMAREQ_W                                               5U
#define LRFDPBE_FCFG5_DMAREQ_M                                      0x0000001FU
#define LRFDPBE_FCFG5_DMAREQ_S                                               0U
#define LRFDPBE_FCFG5_DMAREQ_TXFIFO_COMMIT                          0x0000000FU
#define LRFDPBE_FCFG5_DMAREQ_TXFIFO_DISCARD                         0x0000000EU
#define LRFDPBE_FCFG5_DMAREQ_TXFIFO_RETRY                           0x0000000DU
#define LRFDPBE_FCFG5_DMAREQ_TXFIFO_DEALLOC                         0x0000000CU
#define LRFDPBE_FCFG5_DMAREQ_TXFIFO_RESET                           0x0000000BU
#define LRFDPBE_FCFG5_DMAREQ_TXWRBTHR_MET                           0x0000000AU
#define LRFDPBE_FCFG5_DMAREQ_TXRDBTHR_MET                           0x00000009U
#define LRFDPBE_FCFG5_DMAREQ_RXFIFO_COMMIT                          0x00000007U
#define LRFDPBE_FCFG5_DMAREQ_RXFIFO_DISCARD                         0x00000006U
#define LRFDPBE_FCFG5_DMAREQ_RXFIFO_RETRY                           0x00000005U
#define LRFDPBE_FCFG5_DMAREQ_RXFIFO_DEALLOC                         0x00000004U
#define LRFDPBE_FCFG5_DMAREQ_RXFIFO_RESET                           0x00000003U
#define LRFDPBE_FCFG5_DMAREQ_RXWRBTHR_MET                           0x00000002U
#define LRFDPBE_FCFG5_DMAREQ_RXRDBTHR_MET                           0x00000001U
#define LRFDPBE_FCFG5_DMAREQ_NONE                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFWBTHRS
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFWBTHRS_BYTES_W                                           10U
#define LRFDPBE_RXFWBTHRS_BYTES_M                                   0x000003FFU
#define LRFDPBE_RXFWBTHRS_BYTES_S                                            0U
#define LRFDPBE_RXFWBTHRS_BYTES_ALLONES                             0x000003FFU
#define LRFDPBE_RXFWBTHRS_BYTES_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFRBTHRS
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFRBTHRS_BYTES_W                                           10U
#define LRFDPBE_RXFRBTHRS_BYTES_M                                   0x000003FFU
#define LRFDPBE_RXFRBTHRS_BYTES_S                                            0U
#define LRFDPBE_RXFRBTHRS_BYTES_ALLONES                             0x000003FFU
#define LRFDPBE_RXFRBTHRS_BYTES_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFWBTHRS
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFWBTHRS_BYTES_W                                           10U
#define LRFDPBE_TXFWBTHRS_BYTES_M                                   0x000003FFU
#define LRFDPBE_TXFWBTHRS_BYTES_S                                            0U
#define LRFDPBE_TXFWBTHRS_BYTES_ALLONES                             0x000003FFU
#define LRFDPBE_TXFWBTHRS_BYTES_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFRBTHRS
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFRBTHRS_BYTES_W                                           10U
#define LRFDPBE_TXFRBTHRS_BYTES_M                                   0x000003FFU
#define LRFDPBE_TXFRBTHRS_BYTES_S                                            0U
#define LRFDPBE_TXFRBTHRS_BYTES_ALLONES                             0x000003FFU
#define LRFDPBE_TXFRBTHRS_BYTES_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMCTL
//
//*****************************************************************************
// Field: [15:11] CPTSRC1 
//
// Selects bit number from event bus to use for a counter capture. Event number 
// in range 0 to 31 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TIMCTL_CPTSRC1_W                                             5U
#define LRFDPBE_TIMCTL_CPTSRC1_M                                    0x0000F800U
#define LRFDPBE_TIMCTL_CPTSRC1_S                                            11U
#define LRFDPBE_TIMCTL_CPTSRC1_ALLONES                              0x0000F800U
#define LRFDPBE_TIMCTL_CPTSRC1_ALLZEROS                             0x00000000U

// Field:    [10] ENCPT1 
//
// Enable timer capture on event. Upon a capture event, the timer value will be 
// captured in TIMCAPT register. The timer value can always be captured using 
// the STROBES0.TIMCAPT1 
// ENUMs: 
// ON                       Enable capture mode for counter 
// OFF                      Disable capture mode for counter 
#define LRFDPBE_TIMCTL_ENCPT1                                       0x00000400U
#define LRFDPBE_TIMCTL_ENCPT1_M                                     0x00000400U
#define LRFDPBE_TIMCTL_ENCPT1_S                                             10U
#define LRFDPBE_TIMCTL_ENCPT1_ON                                    0x00000400U
#define LRFDPBE_TIMCTL_ENCPT1_OFF                                   0x00000000U

// Field:     [9] SRC1 
//
// Select timer tick source for timer 
// ENUMs: 
// PRE1                     Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDPBE_TIMCTL_SRC1                                         0x00000200U
#define LRFDPBE_TIMCTL_SRC1_M                                       0x00000200U
#define LRFDPBE_TIMCTL_SRC1_S                                                9U
#define LRFDPBE_TIMCTL_SRC1_PRE1                                    0x00000200U
#define LRFDPBE_TIMCTL_SRC1_CLK                                     0x00000000U

// Field:     [8] EN1 
//
// Enable 16-bit timer1. It will generate a timer interrupt after TIMPER1 timer 
// ticks. 
// ENUMs: 
// ON                       Will enable timer 
// OFF                      Will disable timer and clear internal timer value 
#define LRFDPBE_TIMCTL_EN1                                          0x00000100U
#define LRFDPBE_TIMCTL_EN1_M                                        0x00000100U
#define LRFDPBE_TIMCTL_EN1_S                                                 8U
#define LRFDPBE_TIMCTL_EN1_ON                                       0x00000100U
#define LRFDPBE_TIMCTL_EN1_OFF                                      0x00000000U

// Field:   [7:3] CPTSRC0 
//
// Selects bit number from event bus to use for a counter capture. Event number 
// in range 0 to 31 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TIMCTL_CPTSRC0_W                                             5U
#define LRFDPBE_TIMCTL_CPTSRC0_M                                    0x000000F8U
#define LRFDPBE_TIMCTL_CPTSRC0_S                                             3U
#define LRFDPBE_TIMCTL_CPTSRC0_ALLONES                              0x000000F8U
#define LRFDPBE_TIMCTL_CPTSRC0_ALLZEROS                             0x00000000U

// Field:     [2] ENCPT0 
//
// Enable timer capture on event. Upon a capture event, the timer value will be 
// captured in TIMCAPT register. The timer value can always be captured using 
// the STROBES0.TIMCAPT0 
// ENUMs: 
// ON                       Enable capture mode for counter 
// OFF                      Disable capture mode for counter 
#define LRFDPBE_TIMCTL_ENCPT0                                       0x00000004U
#define LRFDPBE_TIMCTL_ENCPT0_M                                     0x00000004U
#define LRFDPBE_TIMCTL_ENCPT0_S                                              2U
#define LRFDPBE_TIMCTL_ENCPT0_ON                                    0x00000004U
#define LRFDPBE_TIMCTL_ENCPT0_OFF                                   0x00000000U

// Field:     [1] SRC0 
//
// Select timer tick source for timer 
// ENUMs: 
// PRE0                     Use magnitude estimator 0 data enable 
// CLK                      Use clock 
#define LRFDPBE_TIMCTL_SRC0                                         0x00000002U
#define LRFDPBE_TIMCTL_SRC0_M                                       0x00000002U
#define LRFDPBE_TIMCTL_SRC0_S                                                1U
#define LRFDPBE_TIMCTL_SRC0_PRE0                                    0x00000002U
#define LRFDPBE_TIMCTL_SRC0_CLK                                     0x00000000U

// Field:     [0] EN0 
//
// Enable 16-bit timer0. It will generate a timer interrupt after TIMPER0 timer 
// ticks. Note that the internal timer value is not readable from the PBE. 
// ENUMs: 
// ON                       Will enable timer 
// OFF                      Will disable timer and clear internal timer value 
#define LRFDPBE_TIMCTL_EN0                                          0x00000001U
#define LRFDPBE_TIMCTL_EN0_M                                        0x00000001U
#define LRFDPBE_TIMCTL_EN0_S                                                 0U
#define LRFDPBE_TIMCTL_EN0_ON                                       0x00000001U
#define LRFDPBE_TIMCTL_EN0_OFF                                      0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMPRE
//
//*****************************************************************************
// Field:  [13:8] PRE1 
//
// Prescaler setting for timer 1, timer speed will be reduced to clk/(PRE1+1) 
// ENUMs: 
// DIV64                    DIV64 mode 
// NO_DIV                   No prescaling 
#define LRFDPBE_TIMPRE_PRE1_W                                                6U
#define LRFDPBE_TIMPRE_PRE1_M                                       0x00003F00U
#define LRFDPBE_TIMPRE_PRE1_S                                                8U
#define LRFDPBE_TIMPRE_PRE1_DIV64                                   0x00003F00U
#define LRFDPBE_TIMPRE_PRE1_NO_DIV                                  0x00000000U

// Field:   [5:0] PRE0 
//
// Prescaler setting for timer 0, timer speed will be reduced to clk/(PRE0+1) 
// ENUMs: 
// DIV64                    DIV64 mode 
// NO_DIV                   No prescaling 
#define LRFDPBE_TIMPRE_PRE0_W                                                6U
#define LRFDPBE_TIMPRE_PRE0_M                                       0x0000003FU
#define LRFDPBE_TIMPRE_PRE0_S                                                0U
#define LRFDPBE_TIMPRE_PRE0_DIV64                                   0x0000003FU
#define LRFDPBE_TIMPRE_PRE0_NO_DIV                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMPER0
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
#define LRFDPBE_TIMPER0_VAL_W                                               16U
#define LRFDPBE_TIMPER0_VAL_M                                       0x0000FFFFU
#define LRFDPBE_TIMPER0_VAL_S                                                0U
#define LRFDPBE_TIMPER0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TIMPER0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMPER1
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
#define LRFDPBE_TIMPER1_VAL_W                                               16U
#define LRFDPBE_TIMPER1_VAL_M                                       0x0000FFFFU
#define LRFDPBE_TIMPER1_VAL_S                                                0U
#define LRFDPBE_TIMPER1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TIMPER1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMCAPT0
//
//*****************************************************************************
// Field:  [15:0] VALUE 
//
// Captured value of counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TIMCAPT0_VALUE_W                                            16U
#define LRFDPBE_TIMCAPT0_VALUE_M                                    0x0000FFFFU
#define LRFDPBE_TIMCAPT0_VALUE_S                                             0U
#define LRFDPBE_TIMCAPT0_VALUE_ALLONES                              0x0000FFFFU
#define LRFDPBE_TIMCAPT0_VALUE_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TIMCAPT1
//
//*****************************************************************************
// Field:  [15:0] VALUE 
//
// Captured value of counter 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TIMCAPT1_VALUE_W                                            16U
#define LRFDPBE_TIMCAPT1_VALUE_M                                    0x0000FFFFU
#define LRFDPBE_TIMCAPT1_VALUE_S                                             0U
#define LRFDPBE_TIMCAPT1_VALUE_ALLONES                              0x0000FFFFU
#define LRFDPBE_TIMCAPT1_VALUE_ALLZEROS                             0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TRCCTL
//
//*****************************************************************************
// Field:     [0] SEND 
//
// Sends a command to the tracer 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_TRCCTL_SEND                                         0x00000001U
#define LRFDPBE_TRCCTL_SEND_M                                       0x00000001U
#define LRFDPBE_TRCCTL_SEND_S                                                0U
#define LRFDPBE_TRCCTL_SEND_ONE                                     0x00000001U
#define LRFDPBE_TRCCTL_SEND_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TRCSTAT
//
//*****************************************************************************
// Field:     [0] BUSY 
//
// Checks if the tracer is busy 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_TRCSTAT_BUSY                                        0x00000001U
#define LRFDPBE_TRCSTAT_BUSY_M                                      0x00000001U
#define LRFDPBE_TRCSTAT_BUSY_S                                               0U
#define LRFDPBE_TRCSTAT_BUSY_ONE                                    0x00000001U
#define LRFDPBE_TRCSTAT_BUSY_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TRCCMD
//
//*****************************************************************************
// Field:   [9:8] PARCNT 
//
// Number of parameters 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TRCCMD_PARCNT_W                                              2U
#define LRFDPBE_TRCCMD_PARCNT_M                                     0x00000300U
#define LRFDPBE_TRCCMD_PARCNT_S                                              8U
#define LRFDPBE_TRCCMD_PARCNT_ALLONES                               0x00000300U
#define LRFDPBE_TRCCMD_PARCNT_ALLZEROS                              0x00000000U

// Field:   [7:0] PKTHDR 
//
// Packet header 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TRCCMD_PKTHDR_W                                              8U
#define LRFDPBE_TRCCMD_PKTHDR_M                                     0x000000FFU
#define LRFDPBE_TRCCMD_PKTHDR_S                                              0U
#define LRFDPBE_TRCCMD_PKTHDR_ALLONES                               0x000000FFU
#define LRFDPBE_TRCCMD_PKTHDR_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TRCPAR0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TRCPAR0_VAL_W                                               16U
#define LRFDPBE_TRCPAR0_VAL_M                                       0x0000FFFFU
#define LRFDPBE_TRCPAR0_VAL_S                                                0U
#define LRFDPBE_TRCPAR0_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TRCPAR0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TRCPAR1
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Parameter 1 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TRCPAR1_VAL_W                                               16U
#define LRFDPBE_TRCPAR1_VAL_M                                       0x0000FFFFU
#define LRFDPBE_TRCPAR1_VAL_S                                                0U
#define LRFDPBE_TRCPAR1_VAL_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TRCPAR1_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_GPOCTRL
//
//*****************************************************************************
// Field:     [7] GPO7 
//
// Control GPO7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO7                                        0x00000080U
#define LRFDPBE_GPOCTRL_GPO7_M                                      0x00000080U
#define LRFDPBE_GPOCTRL_GPO7_S                                               7U
#define LRFDPBE_GPOCTRL_GPO7_ONE                                    0x00000080U
#define LRFDPBE_GPOCTRL_GPO7_ZERO                                   0x00000000U

// Field:     [6] GPO6 
//
// Control GPO6 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO6                                        0x00000040U
#define LRFDPBE_GPOCTRL_GPO6_M                                      0x00000040U
#define LRFDPBE_GPOCTRL_GPO6_S                                               6U
#define LRFDPBE_GPOCTRL_GPO6_ONE                                    0x00000040U
#define LRFDPBE_GPOCTRL_GPO6_ZERO                                   0x00000000U

// Field:     [5] GPO5 
//
// Control GPO5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO5                                        0x00000020U
#define LRFDPBE_GPOCTRL_GPO5_M                                      0x00000020U
#define LRFDPBE_GPOCTRL_GPO5_S                                               5U
#define LRFDPBE_GPOCTRL_GPO5_ONE                                    0x00000020U
#define LRFDPBE_GPOCTRL_GPO5_ZERO                                   0x00000000U

// Field:     [4] GPO4 
//
// Control GPO4 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO4                                        0x00000010U
#define LRFDPBE_GPOCTRL_GPO4_M                                      0x00000010U
#define LRFDPBE_GPOCTRL_GPO4_S                                               4U
#define LRFDPBE_GPOCTRL_GPO4_ONE                                    0x00000010U
#define LRFDPBE_GPOCTRL_GPO4_ZERO                                   0x00000000U

// Field:     [3] GPO3 
//
// Control GPO3 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO3                                        0x00000008U
#define LRFDPBE_GPOCTRL_GPO3_M                                      0x00000008U
#define LRFDPBE_GPOCTRL_GPO3_S                                               3U
#define LRFDPBE_GPOCTRL_GPO3_ONE                                    0x00000008U
#define LRFDPBE_GPOCTRL_GPO3_ZERO                                   0x00000000U

// Field:     [2] GPO2 
//
// Control GPO2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO2                                        0x00000004U
#define LRFDPBE_GPOCTRL_GPO2_M                                      0x00000004U
#define LRFDPBE_GPOCTRL_GPO2_S                                               2U
#define LRFDPBE_GPOCTRL_GPO2_ONE                                    0x00000004U
#define LRFDPBE_GPOCTRL_GPO2_ZERO                                   0x00000000U

// Field:     [1] GPO1 
//
// Control GPO1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO1                                        0x00000002U
#define LRFDPBE_GPOCTRL_GPO1_M                                      0x00000002U
#define LRFDPBE_GPOCTRL_GPO1_S                                               1U
#define LRFDPBE_GPOCTRL_GPO1_ONE                                    0x00000002U
#define LRFDPBE_GPOCTRL_GPO1_ZERO                                   0x00000000U

// Field:     [0] GPO0 
//
// Control GPO0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPOCTRL_GPO0                                        0x00000001U
#define LRFDPBE_GPOCTRL_GPO0_M                                      0x00000001U
#define LRFDPBE_GPOCTRL_GPO0_S                                               0U
#define LRFDPBE_GPOCTRL_GPO0_ONE                                    0x00000001U
#define LRFDPBE_GPOCTRL_GPO0_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFWR
//
//*****************************************************************************
// Field:  [15:0] PAYLOADIN 
//
// FIFO write port. The actual port size is configurable in LRFDMDM:FIFOWRCTRL. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMFWR_PAYLOADIN_W                                          16U
#define LRFDPBE_MDMFWR_PAYLOADIN_M                                  0x0000FFFFU
#define LRFDPBE_MDMFWR_PAYLOADIN_S                                           0U
#define LRFDPBE_MDMFWR_PAYLOADIN_ALLONES                            0x0000FFFFU
#define LRFDPBE_MDMFWR_PAYLOADIN_ALLZEROS                           0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFRD
//
//*****************************************************************************
// Field:  [15:0] PAYLOADOUT 
//
// FIFO read port. The actual port size is configurable in LRFDMDM:FIFORDCTRL. 
// A new value is read by writing LRFDMDM:FIFOWR.PAYLOADIN. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMFRD_PAYLOADOUT_W                                         16U
#define LRFDPBE_MDMFRD_PAYLOADOUT_M                                 0x0000FFFFU
#define LRFDPBE_MDMFRD_PAYLOADOUT_S                                          0U
#define LRFDPBE_MDMFRD_PAYLOADOUT_ALLONES                           0x0000FFFFU
#define LRFDPBE_MDMFRD_PAYLOADOUT_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFWRCTL
//
//*****************************************************************************
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
#define LRFDPBE_MDMFWRCTL_WORDSZWR_W                                         4U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_M                                0x0000000FU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_S                                         0U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS16                           0x0000000FU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS15                           0x0000000EU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS14                           0x0000000DU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS13                           0x0000000CU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS12                           0x0000000BU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS11                           0x0000000AU
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS10                           0x00000009U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS9                            0x00000008U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS8                            0x00000007U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS7                            0x00000006U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS6                            0x00000005U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS5                            0x00000004U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS4                            0x00000003U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS3                            0x00000002U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS2                            0x00000001U
#define LRFDPBE_MDMFWRCTL_WORDSZWR_BITS1                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFRDCTL
//
//*****************************************************************************
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
#define LRFDPBE_MDMFRDCTL_WORDSZRD_W                                         4U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_M                                0x0000000FU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_S                                         0U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS16                           0x0000000FU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS15                           0x0000000EU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS14                           0x0000000DU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS13                           0x0000000CU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS12                           0x0000000BU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS11                           0x0000000AU
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS10                           0x00000009U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS9                            0x00000008U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS8                            0x00000007U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS7                            0x00000006U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS6                            0x00000005U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS5                            0x00000004U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS4                            0x00000003U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS3                            0x00000002U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS2                            0x00000001U
#define LRFDPBE_MDMFRDCTL_WORDSZRD_BITS1                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFCFG
//
//*****************************************************************************
// Field:  [15:8] AFULLTHR 
//
// Almost full threshold value in bits. This threshold affects the 
// LRFDMDM:FIFOSTA.ALMOSTFULL and LRFDMDM:FIFOSTA.TXREADY status bits. The FIFO 
// can hold up to 64 bits. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMFCFG_AFULLTHR_W                                           8U
#define LRFDPBE_MDMFCFG_AFULLTHR_M                                  0x0000FF00U
#define LRFDPBE_MDMFCFG_AFULLTHR_S                                           8U
#define LRFDPBE_MDMFCFG_AFULLTHR_ALLONES                            0x0000FF00U
#define LRFDPBE_MDMFCFG_AFULLTHR_ALLZEROS                           0x00000000U

// Field:   [7:0] AEMPTYTHR 
//
// Almost empty threshold in bits. This threshold affects the 
// LRFDMDM:FIFOSTA.ALMOSTEMPTY and LRFDMDM:FIFOSTA.RXVALID status bits. The 
// FIFO can hold up to 64 bits. 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_MDMFCFG_AEMPTYTHR_W                                          8U
#define LRFDPBE_MDMFCFG_AEMPTYTHR_M                                 0x000000FFU
#define LRFDPBE_MDMFCFG_AEMPTYTHR_S                                          0U
#define LRFDPBE_MDMFCFG_AEMPTYTHR_ALLONES                           0x000000FFU
#define LRFDPBE_MDMFCFG_AEMPTYTHR_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_MDMFSTA
//
//*****************************************************************************
// Field:     [5] OVFL 
//
// FIFO overflow error. If this flag is asserted the modem FIFO must be 
// re-initialized with LRFDMDM:INIT.TXRXFIFO to clear it. Note that 
// re-initializing will flush the FIFO. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_OVFL                                        0x00000020U
#define LRFDPBE_MDMFSTA_OVFL_M                                      0x00000020U
#define LRFDPBE_MDMFSTA_OVFL_S                                               5U
#define LRFDPBE_MDMFSTA_OVFL_ONE                                    0x00000020U
#define LRFDPBE_MDMFSTA_OVFL_ZERO                                   0x00000000U

// Field:     [4] ALMOSTFULL 
//
// FIFO is almost full. Asserts when the FIFO fill level is above the almost 
// full threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_ALMOSTFULL                                  0x00000010U
#define LRFDPBE_MDMFSTA_ALMOSTFULL_M                                0x00000010U
#define LRFDPBE_MDMFSTA_ALMOSTFULL_S                                         4U
#define LRFDPBE_MDMFSTA_ALMOSTFULL_ONE                              0x00000010U
#define LRFDPBE_MDMFSTA_ALMOSTFULL_ZERO                             0x00000000U

// Field:     [3] ALMOSTEMPTY 
//
// FIFO is almost empty. Asserts when the FIFO fill level is below the almost 
// empty threshold. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_ALMOSTEMPTY                                 0x00000008U
#define LRFDPBE_MDMFSTA_ALMOSTEMPTY_M                               0x00000008U
#define LRFDPBE_MDMFSTA_ALMOSTEMPTY_S                                        3U
#define LRFDPBE_MDMFSTA_ALMOSTEMPTY_ONE                             0x00000008U
#define LRFDPBE_MDMFSTA_ALMOSTEMPTY_ZERO                            0x00000000U

// Field:     [2] UNFL 
//
// FIFO underflow error. If this flag is asserted the modem FIFO must be 
// re-initialized with LRFDMDM:INIT.TXRXFIFO to clear it. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_UNFL                                        0x00000004U
#define LRFDPBE_MDMFSTA_UNFL_M                                      0x00000004U
#define LRFDPBE_MDMFSTA_UNFL_S                                               2U
#define LRFDPBE_MDMFSTA_UNFL_ONE                                    0x00000004U
#define LRFDPBE_MDMFSTA_UNFL_ZERO                                   0x00000000U

// Field:     [1] RXVALID 
//
// A full data word is valid and can be read in LRFDMDM:FIFORD register read 
// port. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_RXVALID                                     0x00000002U
#define LRFDPBE_MDMFSTA_RXVALID_M                                   0x00000002U
#define LRFDPBE_MDMFSTA_RXVALID_S                                            1U
#define LRFDPBE_MDMFSTA_RXVALID_ONE                                 0x00000002U
#define LRFDPBE_MDMFSTA_RXVALID_ZERO                                0x00000000U

// Field:     [0] TXREADY 
//
// The LRFDMDM:FIFOWR register write port is ready to receive a data word. 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_MDMFSTA_TXREADY                                     0x00000001U
#define LRFDPBE_MDMFSTA_TXREADY_M                                   0x00000001U
#define LRFDPBE_MDMFSTA_TXREADY_S                                            0U
#define LRFDPBE_MDMFSTA_TXREADY_ONE                                 0x00000001U
#define LRFDPBE_MDMFSTA_TXREADY_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_PHASTA
//
//*****************************************************************************
// Field:   [1:0] BUSY 
//
// Status busy flags. 
// ENUMs: 
// BUSY                     LFSR n sub-engine busy 
// IDLE                     LFSR n sub-engine idle 
#define LRFDPBE_PHASTA_BUSY_W                                                2U
#define LRFDPBE_PHASTA_BUSY_M                                       0x00000003U
#define LRFDPBE_PHASTA_BUSY_S                                                0U
#define LRFDPBE_PHASTA_BUSY_BUSY                                    0x00000001U
#define LRFDPBE_PHASTA_BUSY_IDLE                                    0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 0 low part value, bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0L_VALLSB_W                                             16U
#define LRFDPBE_LFSR0L_VALLSB_M                                     0x0000FFFFU
#define LRFDPBE_LFSR0L_VALLSB_S                                              0U
#define LRFDPBE_LFSR0L_VALLSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_LFSR0L_VALLSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 0 high part value, bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0H_VALMSB_W                                             16U
#define LRFDPBE_LFSR0H_VALMSB_M                                     0x0000FFFFU
#define LRFDPBE_LFSR0H_VALMSB_S                                              0U
#define LRFDPBE_LFSR0H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_LFSR0H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0BRL
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 0 value, bit reversed order bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0BRL_VALLSB_W                                           16U
#define LRFDPBE_LFSR0BRL_VALLSB_M                                   0x0000FFFFU
#define LRFDPBE_LFSR0BRL_VALLSB_S                                            0U
#define LRFDPBE_LFSR0BRL_VALLSB_ALLONES                             0x0000FFFFU
#define LRFDPBE_LFSR0BRL_VALLSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0BRH
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 0 value, bit reversed order bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0BRH_VALMSB_W                                           16U
#define LRFDPBE_LFSR0BRH_VALMSB_M                                   0x0000FFFFU
#define LRFDPBE_LFSR0BRH_VALMSB_S                                            0U
#define LRFDPBE_LFSR0BRH_VALMSB_ALLONES                             0x0000FFFFU
#define LRFDPBE_LFSR0BRH_VALMSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 1 low part value, bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1L_VALLSB_W                                             16U
#define LRFDPBE_LFSR1L_VALLSB_M                                     0x0000FFFFU
#define LRFDPBE_LFSR1L_VALLSB_S                                              0U
#define LRFDPBE_LFSR1L_VALLSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_LFSR1L_VALLSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 1 high part value, bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1H_VALMSB_W                                             16U
#define LRFDPBE_LFSR1H_VALMSB_M                                     0x0000FFFFU
#define LRFDPBE_LFSR1H_VALMSB_S                                              0U
#define LRFDPBE_LFSR1H_VALMSB_ALLONES                               0x0000FFFFU
#define LRFDPBE_LFSR1H_VALMSB_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1BRL
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// LFSR 1 value, bit reversed order bits 15:0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1BRL_VALLSB_W                                           16U
#define LRFDPBE_LFSR1BRL_VALLSB_M                                   0x0000FFFFU
#define LRFDPBE_LFSR1BRL_VALLSB_S                                            0U
#define LRFDPBE_LFSR1BRL_VALLSB_ALLONES                             0x0000FFFFU
#define LRFDPBE_LFSR1BRL_VALLSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1BRH
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// LFSR 1 value, bit reversed order bits 31:16 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1BRH_VALMSB_W                                           16U
#define LRFDPBE_LFSR1BRH_VALMSB_M                                   0x0000FFFFU
#define LRFDPBE_LFSR1BRH_VALMSB_S                                            0U
#define LRFDPBE_LFSR1BRH_VALMSB_ALLONES                             0x0000FFFFU
#define LRFDPBE_LFSR1BRH_VALMSB_ALLZEROS                            0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0INL
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// LFSR 0 input value LSB first 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0INL_VAL_W                                              16U
#define LRFDPBE_LFSR0INL_VAL_M                                      0x0000FFFFU
#define LRFDPBE_LFSR0INL_VAL_S                                               0U
#define LRFDPBE_LFSR0INL_VAL_ALLONES                                0x00000003U
#define LRFDPBE_LFSR0INL_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0N
//
//*****************************************************************************
// Field:   [3:0] SIZE 
//
// Number of bits to clock into LSFR0 upon next write to LFSR0INL or LFSR0INM 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR0N_SIZE_W                                                4U
#define LRFDPBE_LFSR0N_SIZE_M                                       0x0000000FU
#define LRFDPBE_LFSR0N_SIZE_S                                                0U
#define LRFDPBE_LFSR0N_SIZE_ALLONES                                 0x0000000FU
#define LRFDPBE_LFSR0N_SIZE_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR0INM
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// LFSR 0 input value MSB first 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_LFSR0INM_VAL_W                                              16U
#define LRFDPBE_LFSR0INM_VAL_M                                      0x0000FFFFU
#define LRFDPBE_LFSR0INM_VAL_S                                               0U
#define LRFDPBE_LFSR0INM_VAL_ONE                                    0x00000001U
#define LRFDPBE_LFSR0INM_VAL_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_PHAOUT0
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Output value of LFSR0 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_PHAOUT0_VAL_W                                               16U
#define LRFDPBE_PHAOUT0_VAL_M                                       0x0000FFFFU
#define LRFDPBE_PHAOUT0_VAL_S                                                0U
#define LRFDPBE_PHAOUT0_VAL_ALLONES                                 0x0000DCD7U
#define LRFDPBE_PHAOUT0_VAL_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1INL
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// LFSR 1 input value LSB first 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1INL_VAL_W                                              16U
#define LRFDPBE_LFSR1INL_VAL_M                                      0x0000FFFFU
#define LRFDPBE_LFSR1INL_VAL_S                                               0U
#define LRFDPBE_LFSR1INL_VAL_ALLONES                                0x00000003U
#define LRFDPBE_LFSR1INL_VAL_ALLZEROS                               0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1N
//
//*****************************************************************************
// Field:   [3:0] SIZE 
//
// Number of bits to clock into LSFR1 upon next write to LFSR1INL or LFSR1INM 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_LFSR1N_SIZE_W                                                4U
#define LRFDPBE_LFSR1N_SIZE_M                                       0x0000000FU
#define LRFDPBE_LFSR1N_SIZE_S                                                0U
#define LRFDPBE_LFSR1N_SIZE_ALLONES                                 0x0000000FU
#define LRFDPBE_LFSR1N_SIZE_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_LFSR1INM
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// LFSR 1 input value MSB first 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_LFSR1INM_VAL_W                                              16U
#define LRFDPBE_LFSR1INM_VAL_M                                      0x0000FFFFU
#define LRFDPBE_LFSR1INM_VAL_S                                               0U
#define LRFDPBE_LFSR1INM_VAL_ONE                                    0x00000001U
#define LRFDPBE_LFSR1INM_VAL_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_PHAOUT0BR
//
//*****************************************************************************
// Field:  [15:0] VAL 
//
// Output value of LFSR0 in bit reversed order 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_PHAOUT0BR_VAL_W                                             16U
#define LRFDPBE_PHAOUT0BR_VAL_M                                     0x0000FFFFU
#define LRFDPBE_PHAOUT0BR_VAL_S                                              0U
#define LRFDPBE_PHAOUT0BR_VAL_ALLONES                               0x0000FFFFU
#define LRFDPBE_PHAOUT0BR_VAL_ALLZEROS                              0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM0L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// SYSTIM0 capture low part value, bits 15:0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM0L_VALLSB_W                                           16U
#define LRFDPBE_SYSTIM0L_VALLSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM0L_VALLSB_S                                            0U
#define LRFDPBE_SYSTIM0L_VALLSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM0L_VALLSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM0H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// SYSTIM0 capture high part value, bits 31:16 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM0H_VALMSB_W                                           16U
#define LRFDPBE_SYSTIM0H_VALMSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM0H_VALMSB_S                                            0U
#define LRFDPBE_SYSTIM0H_VALMSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM0H_VALMSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM1L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// SYSTIM1 capture low part value, bits 15:0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM1L_VALLSB_W                                           16U
#define LRFDPBE_SYSTIM1L_VALLSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM1L_VALLSB_S                                            0U
#define LRFDPBE_SYSTIM1L_VALLSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM1L_VALLSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM1H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// SYSTIM1 capture high part value, bits 31:16 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM1H_VALMSB_W                                           16U
#define LRFDPBE_SYSTIM1H_VALMSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM1H_VALMSB_S                                            0U
#define LRFDPBE_SYSTIM1H_VALMSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM1H_VALMSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM2L
//
//*****************************************************************************
// Field:  [15:0] VALLSB 
//
// SYSTIM2 capture low part value, bits 15:0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM2L_VALLSB_W                                           16U
#define LRFDPBE_SYSTIM2L_VALLSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM2L_VALLSB_S                                            0U
#define LRFDPBE_SYSTIM2L_VALLSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM2L_VALLSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_SYSTIM2H
//
//*****************************************************************************
// Field:  [15:0] VALMSB 
//
// SYSTIM2 capture high part value, bits 31:16 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_SYSTIM2H_VALMSB_W                                           16U
#define LRFDPBE_SYSTIM2H_VALMSB_M                                   0x0000FFFFU
#define LRFDPBE_SYSTIM2H_VALMSB_S                                            0U
#define LRFDPBE_SYSTIM2H_VALMSB_ONE                                 0x00000001U
#define LRFDPBE_SYSTIM2H_VALMSB_ZERO                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_GPI
//
//*****************************************************************************
// Field:     [7] GPI7 
//
// Control GPI7 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI7                                            0x00000080U
#define LRFDPBE_GPI_GPI7_M                                          0x00000080U
#define LRFDPBE_GPI_GPI7_S                                                   7U
#define LRFDPBE_GPI_GPI7_ONE                                        0x00000080U
#define LRFDPBE_GPI_GPI7_ZERO                                       0x00000000U

// Field:     [6] GPI6 
//
// Control GPI6 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI6                                            0x00000040U
#define LRFDPBE_GPI_GPI6_M                                          0x00000040U
#define LRFDPBE_GPI_GPI6_S                                                   6U
#define LRFDPBE_GPI_GPI6_ONE                                        0x00000040U
#define LRFDPBE_GPI_GPI6_ZERO                                       0x00000000U

// Field:     [5] GPI5 
//
// Control GPI5 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI5                                            0x00000020U
#define LRFDPBE_GPI_GPI5_M                                          0x00000020U
#define LRFDPBE_GPI_GPI5_S                                                   5U
#define LRFDPBE_GPI_GPI5_ONE                                        0x00000020U
#define LRFDPBE_GPI_GPI5_ZERO                                       0x00000000U

// Field:     [4] GPI4 
//
// Control GPI4 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI4                                            0x00000010U
#define LRFDPBE_GPI_GPI4_M                                          0x00000010U
#define LRFDPBE_GPI_GPI4_S                                                   4U
#define LRFDPBE_GPI_GPI4_ONE                                        0x00000010U
#define LRFDPBE_GPI_GPI4_ZERO                                       0x00000000U

// Field:     [3] GPI3 
//
// Control GPI3 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI3                                            0x00000008U
#define LRFDPBE_GPI_GPI3_M                                          0x00000008U
#define LRFDPBE_GPI_GPI3_S                                                   3U
#define LRFDPBE_GPI_GPI3_ONE                                        0x00000008U
#define LRFDPBE_GPI_GPI3_ZERO                                       0x00000000U

// Field:     [2] GPI2 
//
// Control GPI2 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI2                                            0x00000004U
#define LRFDPBE_GPI_GPI2_M                                          0x00000004U
#define LRFDPBE_GPI_GPI2_S                                                   2U
#define LRFDPBE_GPI_GPI2_ONE                                        0x00000004U
#define LRFDPBE_GPI_GPI2_ZERO                                       0x00000000U

// Field:     [1] GPI1 
//
// Control GPI1 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI1                                            0x00000002U
#define LRFDPBE_GPI_GPI1_M                                          0x00000002U
#define LRFDPBE_GPI_GPI1_S                                                   1U
#define LRFDPBE_GPI_GPI1_ONE                                        0x00000002U
#define LRFDPBE_GPI_GPI1_ZERO                                       0x00000000U

// Field:     [0] GPI0 
//
// Control GPI0 
// ENUMs: 
// ONE                      The bit is 1 
// ZERO                     The bit is 0 
#define LRFDPBE_GPI_GPI0                                            0x00000001U
#define LRFDPBE_GPI_GPI0_M                                          0x00000001U
#define LRFDPBE_GPI_GPI0_S                                                   0U
#define LRFDPBE_GPI_GPI0_ONE                                        0x00000001U
#define LRFDPBE_GPI_GPI0_ZERO                                       0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_FCMD
//
//*****************************************************************************
// Field:   [7:0] DATA 
//
// Command either RX or TX FIFO or both. Strobe signals which clear after 
// write. 
// ENUMs: 
// FIFO_COMMIT              Commit both FIFOs 
// FIFO_DISCARD             Discard both FIFOs 
// FIFO_RETRY               Retry both FIFOs 
// FIFO_DEALLOC             Deallocate both FIFOS 
// FIFO_RESET               Reset (empty) both FIFOs 
// RXFIFO_RETRY             Retry rxfifo. This sets RXFRP := RXFSRP 
// RXFIFO_DISCARD           Discard rxfifo. This sets RXFWP := RXFSWP 
// RXFIFO_COMMIT            Commit rxfifo. This sets RXFSWP := RXFWP 
// TXFIFO_RESET             Reset (empty) txfifo. Set TXF* := 0 
// TXFIFO_DEALLOC           Deallocate txfifo. This sets TXFSRP := TXFRP. 
// TXFIFO_RETRY             Retry txfifo. This sets TXFRP := TXFSRP 
// TXFIFO_DISCARD           Discard txfifo. This sets TXFWP := TXFSWP 
// TXFIFO_COMMIT            Commit txfifo. This sets TXFSWP := TXFWP 
// RXFIFO_DEALLOC           Deallocate rxfifo. This sets RXFSRP := RXFRP. 
// RXFIFO_RESET             Reset (empty) rxfifo. Set RXF* := 0 
#define LRFDPBE_FCMD_DATA_W                                                  8U
#define LRFDPBE_FCMD_DATA_M                                         0x000000FFU
#define LRFDPBE_FCMD_DATA_S                                                  0U
#define LRFDPBE_FCMD_DATA_FIFO_COMMIT                               0x0000000FU
#define LRFDPBE_FCMD_DATA_FIFO_DISCARD                              0x0000000EU
#define LRFDPBE_FCMD_DATA_FIFO_RETRY                                0x0000000DU
#define LRFDPBE_FCMD_DATA_FIFO_DEALLOC                              0x0000000CU
#define LRFDPBE_FCMD_DATA_FIFO_RESET                                0x0000000BU
#define LRFDPBE_FCMD_DATA_RXFIFO_RETRY                              0x0000000AU
#define LRFDPBE_FCMD_DATA_RXFIFO_DISCARD                            0x00000009U
#define LRFDPBE_FCMD_DATA_RXFIFO_COMMIT                             0x00000008U
#define LRFDPBE_FCMD_DATA_TXFIFO_RESET                              0x00000007U
#define LRFDPBE_FCMD_DATA_TXFIFO_DEALLOC                            0x00000006U
#define LRFDPBE_FCMD_DATA_TXFIFO_RETRY                              0x00000005U
#define LRFDPBE_FCMD_DATA_TXFIFO_DISCARD                            0x00000004U
#define LRFDPBE_FCMD_DATA_TXFIFO_COMMIT                             0x00000003U
#define LRFDPBE_FCMD_DATA_RXFIFO_DEALLOC                            0x00000002U
#define LRFDPBE_FCMD_DATA_RXFIFO_RESET                              0x00000001U

//*****************************************************************************
//
// Register: LRFDPBE_O_FSTAT
//
//*****************************************************************************
// Field:    [11] TXUNFL 
//
// Underflow occurred in the TX FIFO. 
// ENUMs: 
// TRUE                     Underflow has occurred 
// FALSE                    Normal operation ensues 
#define LRFDPBE_FSTAT_TXUNFL                                        0x00000800U
#define LRFDPBE_FSTAT_TXUNFL_M                                      0x00000800U
#define LRFDPBE_FSTAT_TXUNFL_S                                              11U
#define LRFDPBE_FSTAT_TXUNFL_TRUE                                   0x00000800U
#define LRFDPBE_FSTAT_TXUNFL_FALSE                                  0x00000000U

// Field:    [10] TXOVFL 
//
// Overflow occurred in the TX FIFO. 
// ENUMs: 
// TRUE                     Overflow has occurred 
// FALSE                    Normal operation ensues 
#define LRFDPBE_FSTAT_TXOVFL                                        0x00000400U
#define LRFDPBE_FSTAT_TXOVFL_M                                      0x00000400U
#define LRFDPBE_FSTAT_TXOVFL_S                                              10U
#define LRFDPBE_FSTAT_TXOVFL_TRUE                                   0x00000400U
#define LRFDPBE_FSTAT_TXOVFL_FALSE                                  0x00000000U

// Field:     [9] TXEMPTY 
//
// TXFIFO empty flag 
// ENUMs: 
// TRUE                     TXFIFO is empty 
// FALSE                    TXFIFO is not empty 
#define LRFDPBE_FSTAT_TXEMPTY                                       0x00000200U
#define LRFDPBE_FSTAT_TXEMPTY_M                                     0x00000200U
#define LRFDPBE_FSTAT_TXEMPTY_S                                              9U
#define LRFDPBE_FSTAT_TXEMPTY_TRUE                                  0x00000200U
#define LRFDPBE_FSTAT_TXEMPTY_FALSE                                 0x00000000U

// Field:     [8] TXFULL 
//
// TXFIFO full flag 
// ENUMs: 
// TRUE                     TXFIFO is full 
// FALSE                    TXFIFO is not full 
#define LRFDPBE_FSTAT_TXFULL                                        0x00000100U
#define LRFDPBE_FSTAT_TXFULL_M                                      0x00000100U
#define LRFDPBE_FSTAT_TXFULL_S                                               8U
#define LRFDPBE_FSTAT_TXFULL_TRUE                                   0x00000100U
#define LRFDPBE_FSTAT_TXFULL_FALSE                                  0x00000000U

// Field:     [3] RXUNFL 
//
// Underflow occurred in the RX FIFO. 
// ENUMs: 
// TRUE                     Underflow has occurred 
// FALSE                    Normal operation ensues 
#define LRFDPBE_FSTAT_RXUNFL                                        0x00000008U
#define LRFDPBE_FSTAT_RXUNFL_M                                      0x00000008U
#define LRFDPBE_FSTAT_RXUNFL_S                                               3U
#define LRFDPBE_FSTAT_RXUNFL_TRUE                                   0x00000008U
#define LRFDPBE_FSTAT_RXUNFL_FALSE                                  0x00000000U

// Field:     [2] RXOVFL 
//
// Overflow occurred in the RX FIFO. 
// ENUMs: 
// TRUE                     Overflow has occurred 
// FALSE                    Normal operation ensues 
#define LRFDPBE_FSTAT_RXOVFL                                        0x00000004U
#define LRFDPBE_FSTAT_RXOVFL_M                                      0x00000004U
#define LRFDPBE_FSTAT_RXOVFL_S                                               2U
#define LRFDPBE_FSTAT_RXOVFL_TRUE                                   0x00000004U
#define LRFDPBE_FSTAT_RXOVFL_FALSE                                  0x00000000U

// Field:     [1] RXEMPTY 
//
// RXFIFO empty flag 
// ENUMs: 
// TRUE                     RXFIFO is empty 
// FALSE                    RXFIFO is not empty 
#define LRFDPBE_FSTAT_RXEMPTY                                       0x00000002U
#define LRFDPBE_FSTAT_RXEMPTY_M                                     0x00000002U
#define LRFDPBE_FSTAT_RXEMPTY_S                                              1U
#define LRFDPBE_FSTAT_RXEMPTY_TRUE                                  0x00000002U
#define LRFDPBE_FSTAT_RXEMPTY_FALSE                                 0x00000000U

// Field:     [0] RXFULL 
//
// RXFIFO full flag 
// ENUMs: 
// TRUE                     RXFIFO is full 
// FALSE                    RXFIFO is not full 
#define LRFDPBE_FSTAT_RXFULL                                        0x00000001U
#define LRFDPBE_FSTAT_RXFULL_M                                      0x00000001U
#define LRFDPBE_FSTAT_RXFULL_S                                               0U
#define LRFDPBE_FSTAT_RXFULL_TRUE                                   0x00000001U
#define LRFDPBE_FSTAT_RXFULL_FALSE                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFWP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Write pointer 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFWP_PTR_W                                                 10U
#define LRFDPBE_RXFWP_PTR_M                                         0x000003FFU
#define LRFDPBE_RXFWP_PTR_S                                                  0U
#define LRFDPBE_RXFWP_PTR_ALLONES                                   0x000003FFU
#define LRFDPBE_RXFWP_PTR_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFRP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Read pointer 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFRP_PTR_W                                                 10U
#define LRFDPBE_RXFRP_PTR_M                                         0x000003FFU
#define LRFDPBE_RXFRP_PTR_S                                                  0U
#define LRFDPBE_RXFRP_PTR_ALLONES                                   0x000003FFU
#define LRFDPBE_RXFRP_PTR_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFSWP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Pointer to start of written package 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFSWP_PTR_W                                                10U
#define LRFDPBE_RXFSWP_PTR_M                                        0x000003FFU
#define LRFDPBE_RXFSWP_PTR_S                                                 0U
#define LRFDPBE_RXFSWP_PTR_ALLONES                                  0x000003FFU
#define LRFDPBE_RXFSWP_PTR_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFSRP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Pointer to start of read package 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFSRP_PTR_W                                                10U
#define LRFDPBE_RXFSRP_PTR_M                                        0x000003FFU
#define LRFDPBE_RXFSRP_PTR_S                                                 0U
#define LRFDPBE_RXFSRP_PTR_ALLONES                                  0x000003FFU
#define LRFDPBE_RXFSRP_PTR_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFWP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Write pointer 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFWP_PTR_W                                                 10U
#define LRFDPBE_TXFWP_PTR_M                                         0x000003FFU
#define LRFDPBE_TXFWP_PTR_S                                                  0U
#define LRFDPBE_TXFWP_PTR_ALLONES                                   0x000003FFU
#define LRFDPBE_TXFWP_PTR_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFRP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Read pointer 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFRP_PTR_W                                                 10U
#define LRFDPBE_TXFRP_PTR_M                                         0x000003FFU
#define LRFDPBE_TXFRP_PTR_S                                                  0U
#define LRFDPBE_TXFRP_PTR_ALLONES                                   0x000003FFU
#define LRFDPBE_TXFRP_PTR_ALLZEROS                                  0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFSWP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Pointer to start of written package 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFSWP_PTR_W                                                10U
#define LRFDPBE_TXFSWP_PTR_M                                        0x000003FFU
#define LRFDPBE_TXFSWP_PTR_S                                                 0U
#define LRFDPBE_TXFSWP_PTR_ALLONES                                  0x000003FFU
#define LRFDPBE_TXFSWP_PTR_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFSRP
//
//*****************************************************************************
// Field:   [9:0] PTR 
//
// Pointer to start of read package 
// ENUMs: 
// ALLONES_2                All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFSRP_PTR_W                                                10U
#define LRFDPBE_TXFSRP_PTR_M                                        0x000003FFU
#define LRFDPBE_TXFSRP_PTR_S                                                 0U
#define LRFDPBE_TXFSRP_PTR_ALLONES_2                                0x000003FFU
#define LRFDPBE_TXFSRP_PTR_ALLZEROS                                 0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFWRITABLE
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// The amount of writable bytes for the RX FIFO may be directly read here 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFWRITABLE_BYTES_W                                         10U
#define LRFDPBE_RXFWRITABLE_BYTES_M                                 0x000003FFU
#define LRFDPBE_RXFWRITABLE_BYTES_S                                          0U
#define LRFDPBE_RXFWRITABLE_BYTES_ALLONES                           0x000003FFU
#define LRFDPBE_RXFWRITABLE_BYTES_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFREADABLE
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// The amount of readable bytes for the RX FIFO may be directly read here 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFREADABLE_BYTES_W                                         10U
#define LRFDPBE_RXFREADABLE_BYTES_M                                 0x000003FFU
#define LRFDPBE_RXFREADABLE_BYTES_S                                          0U
#define LRFDPBE_RXFREADABLE_BYTES_ALLONES                           0x000003FFU
#define LRFDPBE_RXFREADABLE_BYTES_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFWRITABLE
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// The amount of writable bytes for the TX FIFO may be directly read here 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFWRITABLE_BYTES_W                                         10U
#define LRFDPBE_TXFWRITABLE_BYTES_M                                 0x000003FFU
#define LRFDPBE_TXFWRITABLE_BYTES_S                                          0U
#define LRFDPBE_TXFWRITABLE_BYTES_ALLONES                           0x000003FFU
#define LRFDPBE_TXFWRITABLE_BYTES_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFREADABLE
//
//*****************************************************************************
// Field:   [9:0] BYTES 
//
// The amount of readable bytes for the TX FIFO may be directly read here 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFREADABLE_BYTES_W                                         10U
#define LRFDPBE_TXFREADABLE_BYTES_M                                 0x000003FFU
#define LRFDPBE_TXFREADABLE_BYTES_S                                          0U
#define LRFDPBE_TXFREADABLE_BYTES_ALLONES                           0x000003FFU
#define LRFDPBE_TXFREADABLE_BYTES_ALLZEROS                          0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFBRD
//
//*****************************************************************************
// Field:   [7:0] DATA 
//
// Data to be read 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFBRD_DATA_W                                                8U
#define LRFDPBE_RXFBRD_DATA_M                                       0x000000FFU
#define LRFDPBE_RXFBRD_DATA_S                                                0U
#define LRFDPBE_RXFBRD_DATA_ALLONES                                 0x000000FFU
#define LRFDPBE_RXFBRD_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFBWR
//
//*****************************************************************************
// Field:   [7:0] DATA 
//
// Data to be written 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFBWR_DATA_W                                                8U
#define LRFDPBE_RXFBWR_DATA_M                                       0x000000FFU
#define LRFDPBE_RXFBWR_DATA_S                                                0U
#define LRFDPBE_RXFBWR_DATA_ALLONES                                 0x000000FFU
#define LRFDPBE_RXFBWR_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFBRD
//
//*****************************************************************************
// Field:   [7:0] DATA 
//
// Data to be read 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFBRD_DATA_W                                                8U
#define LRFDPBE_TXFBRD_DATA_M                                       0x000000FFU
#define LRFDPBE_TXFBRD_DATA_S                                                0U
#define LRFDPBE_TXFBRD_DATA_ALLONES                                 0x000000FFU
#define LRFDPBE_TXFBRD_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFBWR
//
//*****************************************************************************
// Field:   [7:0] DATA 
//
// Data to be written 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFBWR_DATA_W                                                8U
#define LRFDPBE_TXFBWR_DATA_M                                       0x000000FFU
#define LRFDPBE_TXFBWR_DATA_S                                                0U
#define LRFDPBE_TXFBWR_DATA_ALLONES                                 0x000000FFU
#define LRFDPBE_TXFBWR_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFHRD
//
//*****************************************************************************
// Field:  [15:0] DATA 
//
// Data to be read 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFHRD_DATA_W                                               16U
#define LRFDPBE_RXFHRD_DATA_M                                       0x0000FFFFU
#define LRFDPBE_RXFHRD_DATA_S                                                0U
#define LRFDPBE_RXFHRD_DATA_ALLONES                                 0x0000FFFFU
#define LRFDPBE_RXFHRD_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_RXFHWR
//
//*****************************************************************************
// Field:  [15:0] DATA 
//
// Data to be written 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_RXFHWR_DATA_W                                               16U
#define LRFDPBE_RXFHWR_DATA_M                                       0x0000FFFFU
#define LRFDPBE_RXFHWR_DATA_S                                                0U
#define LRFDPBE_RXFHWR_DATA_ALLONES                                 0x0000FFFFU
#define LRFDPBE_RXFHWR_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFHRD
//
//*****************************************************************************
// Field:  [15:0] DATA 
//
// Data to be read 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFHRD_DATA_W                                               16U
#define LRFDPBE_TXFHRD_DATA_M                                       0x0000FFFFU
#define LRFDPBE_TXFHRD_DATA_S                                                0U
#define LRFDPBE_TXFHRD_DATA_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TXFHRD_DATA_ALLZEROS                                0x00000000U

//*****************************************************************************
//
// Register: LRFDPBE_O_TXFHWR
//
//*****************************************************************************
// Field:  [15:0] DATA 
//
// Data to be written 
// ENUMs: 
// ALLONES                  All the bits are 1 
// ALLZEROS                 All the bits are 0 
#define LRFDPBE_TXFHWR_DATA_W                                               16U
#define LRFDPBE_TXFHWR_DATA_M                                       0x0000FFFFU
#define LRFDPBE_TXFHWR_DATA_S                                                0U
#define LRFDPBE_TXFHWR_DATA_ALLONES                                 0x0000FFFFU
#define LRFDPBE_TXFHWR_DATA_ALLZEROS                                0x00000000U


#endif // __LRFDPBE__
