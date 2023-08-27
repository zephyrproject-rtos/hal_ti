/******************************************************************************
*  Filename:       hw_evtsvt_h
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

#ifndef __HW_EVTSVT_H__
#define __HW_EVTSVT_H__

//*****************************************************************************
//
// This section defines the register offsets of
// EVTSVT component
//
//*****************************************************************************
// Description
#define EVTSVT_O_DESC                                               0x00000000U

// Extended Description
#define EVTSVT_O_DESCEX                                             0x00000004U

// Digital test bus control
#define EVTSVT_O_DTB                                                0x00000064U

// Output Selection for CPU NMI Exception
#define EVTSVT_O_NMISEL                                             0x00000400U

// Output Selection for CPU Interrupt CPUIRQ0
#define EVTSVT_O_CPUIRQ0SEL                                         0x00000404U

// Output Selection for CPU Interrupt CPUIRQ1
#define EVTSVT_O_CPUIRQ1SEL                                         0x00000408U

// Output Selection for CPU Interrupt CPUIRQ2
#define EVTSVT_O_CPUIRQ2SEL                                         0x0000040CU

// Output Selection for CPU Interrupt CPUIRQ3
#define EVTSVT_O_CPUIRQ3SEL                                         0x00000410U

// Output Selection for CPU Interrupt CPUIRQ4
#define EVTSVT_O_CPUIRQ4SEL                                         0x00000414U

// Output Selection for CPU Interrupt CPUIRQ5
#define EVTSVT_O_CPUIRQ5SEL                                         0x00000418U

// Output Selection for CPU Interrupt CPUIRQ6
#define EVTSVT_O_CPUIRQ6SEL                                         0x0000041CU

// Output Selection for CPU Interrupt CPUIRQ7
#define EVTSVT_O_CPUIRQ7SEL                                         0x00000420U

// Output Selection for CPU Interrupt CPUIRQ8
#define EVTSVT_O_CPUIRQ8SEL                                         0x00000424U

// Output Selection for CPU Interrupt CPUIRQ9
#define EVTSVT_O_CPUIRQ9SEL                                         0x00000428U

// Output Selection for CPU Interrupt CPUIRQ10
#define EVTSVT_O_CPUIRQ10SEL                                        0x0000042CU

// Output Selection for CPU Interrupt CPUIRQ11
#define EVTSVT_O_CPUIRQ11SEL                                        0x00000430U

// Output Selection for CPU Interrupt CPUIRQ12
#define EVTSVT_O_CPUIRQ12SEL                                        0x00000434U

// Output Selection for CPU Interrupt CPUIRQ13
#define EVTSVT_O_CPUIRQ13SEL                                        0x00000438U

// Output Selection for CPU Interrupt CPUIRQ14
#define EVTSVT_O_CPUIRQ14SEL                                        0x0000043CU

// Output Selection for CPU Interrupt CPUIRQ15
#define EVTSVT_O_CPUIRQ15SEL                                        0x00000440U

// Output Selection for CPU Interrupt CPUIRQ16
#define EVTSVT_O_CPUIRQ16SEL                                        0x00000444U

// Output Selection for CPU Interrupt CPUIRQ17
#define EVTSVT_O_CPUIRQ17SEL                                        0x00000448U

// Output Selection for CPU Interrupt CPUIRQ18
#define EVTSVT_O_CPUIRQ18SEL                                        0x0000044CU

// Output Selection for SYSTIMC0
#define EVTSVT_O_SYSTIMC0SEL                                        0x00000450U

//  Output Selection for SYSTIMC1
#define EVTSVT_O_SYSTIMC1SEL                                        0x00000454U

// Output Selection for SYSTIMC2
#define EVTSVT_O_SYSTIMC2SEL                                        0x00000458U

// Output Selection for SYSTIMC3
#define EVTSVT_O_SYSTIMC3SEL                                        0x0000045CU

// Output Selection for SYSTIMC4
#define EVTSVT_O_SYSTIMC4SEL                                        0x00000460U

// Output Selection for ADCTRG
#define EVTSVT_O_ADCTRGSEL                                          0x00000464U

// Output Selection for LGPTSYNC
#define EVTSVT_O_LGPTSYNCSEL                                        0x00000468U

// Output Selection for LGPT0IN0
#define EVTSVT_O_LGPT0IN0SEL                                        0x0000046CU

// Output Selection for LGPT0IN1
#define EVTSVT_O_LGPT0IN1SEL                                        0x00000470U

// Output Selection for LGPT0IN2
#define EVTSVT_O_LGPT0IN2SEL                                        0x00000474U

// Output Selection for LGPT0TEN
#define EVTSVT_O_LGPT0TENSEL                                        0x00000478U

// Output Selection for LGPT1IN0
#define EVTSVT_O_LGPT1IN0SEL                                        0x0000047CU

// Output Selection for LGPT1IN1
#define EVTSVT_O_LGPT1IN1SEL                                        0x00000480U

// Output Selection for LGPT1IN2
#define EVTSVT_O_LGPT1IN2SEL                                        0x00000484U

// Output Selection for LGPT1TEN
#define EVTSVT_O_LGPT1TENSEL                                        0x00000488U

// Output Selection for LGPT2IN0
#define EVTSVT_O_LGPT2IN0SEL                                        0x0000048CU

// Output Selection for LGPT2IN1
#define EVTSVT_O_LGPT2IN1SEL                                        0x00000490U

// Output Selection for LGPT2IN2
#define EVTSVT_O_LGPT2IN2SEL                                        0x00000494U

// Output Selection for LGPT2TEN
#define EVTSVT_O_LGPT2TENSEL                                        0x00000498U

// Output Selection for LGPT3IN0
#define EVTSVT_O_LGPT3IN0SEL                                        0x0000049CU

// Output Selection for LGPT3IN1
#define EVTSVT_O_LGPT3IN1SEL                                        0x000004A0U

// Output Selection for LGPT3IN2
#define EVTSVT_O_LGPT3IN2SEL                                        0x000004A4U

// Output Selection for LGPT3TEN
#define EVTSVT_O_LGPT3TENSEL                                        0x000004A8U

// Output Selection for LRFDIN0
#define EVTSVT_O_LRFDIN0SEL                                         0x000004ACU

// Output Selection for LRFDIN1
#define EVTSVT_O_LRFDIN1SEL                                         0x000004B0U

// Output Selection for LRFDIN2
#define EVTSVT_O_LRFDIN2SEL                                         0x000004B4U

// Output Selection for DMA CH0
#define EVTSVT_O_DMACH0SEL                                          0x00000C00U

// Output Selection for DMA CH1
#define EVTSVT_O_DMACH1SEL                                          0x00000C04U

// Output Selection for DMA CH2
#define EVTSVT_O_DMACH2SEL                                          0x00000C08U

// Output Selection for DMA CH3
#define EVTSVT_O_DMACH3SEL                                          0x00000C0CU

// Output Selection for DMA CH4
#define EVTSVT_O_DMACH4SEL                                          0x00000C10U

// Output Selection for DMA CH5
#define EVTSVT_O_DMACH5SEL                                          0x00000C14U

// Output Selection for DMA CH6
#define EVTSVT_O_DMACH6SEL                                          0x00000C18U

// Output Selection for DMA CH7
#define EVTSVT_O_DMACH7SEL                                          0x00000C1CU

//*****************************************************************************
//
// Register: EVTSVT_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define EVTSVT_DESC_MODID_W                                                 16U
#define EVTSVT_DESC_MODID_M                                         0xFFFF0000U
#define EVTSVT_DESC_MODID_S                                                 16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
// 0: Standard IP MMRs do not exist
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define EVTSVT_DESC_STDIPOFF_W                                               4U
#define EVTSVT_DESC_STDIPOFF_M                                      0x0000F000U
#define EVTSVT_DESC_STDIPOFF_S                                              12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define EVTSVT_DESC_INSTIDX_W                                                4U
#define EVTSVT_DESC_INSTIDX_M                                       0x00000F00U
#define EVTSVT_DESC_INSTIDX_S                                                8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define EVTSVT_DESC_MAJREV_W                                                 4U
#define EVTSVT_DESC_MAJREV_M                                        0x000000F0U
#define EVTSVT_DESC_MAJREV_S                                                 4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define EVTSVT_DESC_MINREV_W                                                 4U
#define EVTSVT_DESC_MINREV_M                                        0x0000000FU
#define EVTSVT_DESC_MINREV_S                                                 0U

//*****************************************************************************
//
// Register: EVTSVT_O_DESCEX
//
//*****************************************************************************
// Field: [31:22] IDMA
//
// Number of DMA input channels
#define EVTSVT_DESCEX_IDMA_W                                                10U
#define EVTSVT_DESCEX_IDMA_M                                        0xFFC00000U
#define EVTSVT_DESCEX_IDMA_S                                                22U

// Field: [21:17] NDMA
//
// Number of DMA output channels
#define EVTSVT_DESCEX_NDMA_W                                                 5U
#define EVTSVT_DESCEX_NDMA_M                                        0x003E0000U
#define EVTSVT_DESCEX_NDMA_S                                                17U

// Field:    [16] PD
//
// Power Domain.
// 0 : SVT
//  1 : ULL
#define EVTSVT_DESCEX_PD                                            0x00010000U
#define EVTSVT_DESCEX_PD_M                                          0x00010000U
#define EVTSVT_DESCEX_PD_S                                                  16U

// Field:  [15:8] NSUB
//
// Number of Subscribers
#define EVTSVT_DESCEX_NSUB_W                                                 8U
#define EVTSVT_DESCEX_NSUB_M                                        0x0000FF00U
#define EVTSVT_DESCEX_NSUB_S                                                 8U

// Field:   [7:0] NPUB
//
// Number of Publishers
#define EVTSVT_DESCEX_NPUB_W                                                 8U
#define EVTSVT_DESCEX_NPUB_M                                        0x000000FFU
#define EVTSVT_DESCEX_NPUB_S                                                 0U

//*****************************************************************************
//
// Register: EVTSVT_O_DTB
//
//*****************************************************************************
// Field:   [1:0] SEL
//
// Digital test bus selection mux control.
// Non-zero select values output a 16 bit selected group of signals per value.
// ENUMs:
// DIS                      All 16 observation signals are set to zero.
#define EVTSVT_DTB_SEL_W                                                     2U
#define EVTSVT_DTB_SEL_M                                            0x00000003U
#define EVTSVT_DTB_SEL_S                                                     0U
#define EVTSVT_DTB_SEL_DIS                                          0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_NMISEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
// AON_NMI_SEL              Selects an AON_NMI source, controlled by
//                          EVTULL:NMISEL
// NONE                     Always inactive
#define EVTSVT_NMISEL_PUBID_W                                                6U
#define EVTSVT_NMISEL_PUBID_M                                       0x0000003FU
#define EVTSVT_NMISEL_PUBID_S                                                0U
#define EVTSVT_NMISEL_PUBID_LGPT3_ADC                               0x00000039U
#define EVTSVT_NMISEL_PUBID_LGPT3_DMA                               0x00000038U
#define EVTSVT_NMISEL_PUBID_LGPT3_COMB                              0x00000037U
#define EVTSVT_NMISEL_PUBID_LGPT3C2                                 0x00000036U
#define EVTSVT_NMISEL_PUBID_LGPT3C1                                 0x00000035U
#define EVTSVT_NMISEL_PUBID_LGPT3C0                                 0x00000034U
#define EVTSVT_NMISEL_PUBID_LGPT2_ADC                               0x00000033U
#define EVTSVT_NMISEL_PUBID_LGPT2_DMA                               0x00000032U
#define EVTSVT_NMISEL_PUBID_LGPT2_COMB                              0x00000031U
#define EVTSVT_NMISEL_PUBID_LGPT2C2                                 0x00000030U
#define EVTSVT_NMISEL_PUBID_LGPT2C1                                 0x0000002FU
#define EVTSVT_NMISEL_PUBID_LGPT2C0                                 0x0000002EU
#define EVTSVT_NMISEL_PUBID_LRFD_EVT2                               0x0000002CU
#define EVTSVT_NMISEL_PUBID_LRFD_EVT1                               0x0000002BU
#define EVTSVT_NMISEL_PUBID_LRFD_EVT0                               0x0000002AU
#define EVTSVT_NMISEL_PUBID_LGPT1_ADC                               0x00000029U
#define EVTSVT_NMISEL_PUBID_LGPT1_DMA                               0x00000028U
#define EVTSVT_NMISEL_PUBID_LGPT1C2                                 0x00000027U
#define EVTSVT_NMISEL_PUBID_LGPT1C1                                 0x00000026U
#define EVTSVT_NMISEL_PUBID_LGPT1C0                                 0x00000025U
#define EVTSVT_NMISEL_PUBID_LGPT0_ADC                               0x00000024U
#define EVTSVT_NMISEL_PUBID_LGPT0_DMA                               0x00000023U
#define EVTSVT_NMISEL_PUBID_LGPT0C2                                 0x00000022U
#define EVTSVT_NMISEL_PUBID_LGPT0C1                                 0x00000021U
#define EVTSVT_NMISEL_PUBID_LGPT0C0                                 0x00000020U
#define EVTSVT_NMISEL_PUBID_SYSTIM4                                 0x0000001FU
#define EVTSVT_NMISEL_PUBID_SYSTIM3                                 0x0000001EU
#define EVTSVT_NMISEL_PUBID_SYSTIM2                                 0x0000001DU
#define EVTSVT_NMISEL_PUBID_SYSTIM1                                 0x0000001CU
#define EVTSVT_NMISEL_PUBID_SYSTIM0                                 0x0000001BU
#define EVTSVT_NMISEL_PUBID_SYSTIM_LT                               0x0000001AU
#define EVTSVT_NMISEL_PUBID_SYSTIM_HB                               0x00000019U
#define EVTSVT_NMISEL_PUBID_I2C0_IRQ                                0x00000018U
#define EVTSVT_NMISEL_PUBID_UART0_COMB                              0x00000017U
#define EVTSVT_NMISEL_PUBID_AES_COMB                                0x00000016U
#define EVTSVT_NMISEL_PUBID_DMA_ERR                                 0x00000015U
#define EVTSVT_NMISEL_PUBID_DMA_DONE_COMB                           0x00000014U
#define EVTSVT_NMISEL_PUBID_LGPT1_COMB                              0x00000013U
#define EVTSVT_NMISEL_PUBID_LGPT0_COMB                              0x00000012U
#define EVTSVT_NMISEL_PUBID_ADC_EVT                                 0x00000011U
#define EVTSVT_NMISEL_PUBID_ADC_COMB                                0x00000010U
#define EVTSVT_NMISEL_PUBID_SPI0_COMB                               0x0000000FU
#define EVTSVT_NMISEL_PUBID_LRFD_IRQ2                               0x0000000EU
#define EVTSVT_NMISEL_PUBID_LRFD_IRQ1                               0x0000000DU
#define EVTSVT_NMISEL_PUBID_LRFD_IRQ0                               0x0000000CU
#define EVTSVT_NMISEL_PUBID_FLASH_IRQ                               0x0000000BU
#define EVTSVT_NMISEL_PUBID_GPIO_EVT                                0x0000000AU
#define EVTSVT_NMISEL_PUBID_GPIO_COMB                               0x00000009U
#define EVTSVT_NMISEL_PUBID_SYSTIM_COMB                             0x00000008U
#define EVTSVT_NMISEL_PUBID_AON_NMI_SEL                             0x00000001U
#define EVTSVT_NMISEL_PUBID_NONE                                    0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ0SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ0SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ0SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3_ADC                           0x00000039U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3_DMA                           0x00000038U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3_COMB                          0x00000037U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3C2                             0x00000036U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3C1                             0x00000035U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT3C0                             0x00000034U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2_ADC                           0x00000033U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2_DMA                           0x00000032U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2_COMB                          0x00000031U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2C2                             0x00000030U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2C1                             0x0000002FU
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT2C0                             0x0000002EU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_EVT2                           0x0000002CU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_EVT1                           0x0000002BU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_EVT0                           0x0000002AU
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1_ADC                           0x00000029U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1_DMA                           0x00000028U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1C2                             0x00000027U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1C1                             0x00000026U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1C0                             0x00000025U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0_ADC                           0x00000024U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0_DMA                           0x00000023U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0C2                             0x00000022U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0C1                             0x00000021U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0C0                             0x00000020U
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM4                             0x0000001FU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM3                             0x0000001EU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM2                             0x0000001DU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM1                             0x0000001CU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM0                             0x0000001BU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM_LT                           0x0000001AU
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM_HB                           0x00000019U
#define EVTSVT_CPUIRQ0SEL_PUBID_I2C0_IRQ                            0x00000018U
#define EVTSVT_CPUIRQ0SEL_PUBID_UART0_COMB                          0x00000017U
#define EVTSVT_CPUIRQ0SEL_PUBID_AES_COMB                            0x00000016U
#define EVTSVT_CPUIRQ0SEL_PUBID_DMA_ERR                             0x00000015U
#define EVTSVT_CPUIRQ0SEL_PUBID_DMA_DONE_COMB                       0x00000014U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT1_COMB                          0x00000013U
#define EVTSVT_CPUIRQ0SEL_PUBID_LGPT0_COMB                          0x00000012U
#define EVTSVT_CPUIRQ0SEL_PUBID_ADC_EVT                             0x00000011U
#define EVTSVT_CPUIRQ0SEL_PUBID_ADC_COMB                            0x00000010U
#define EVTSVT_CPUIRQ0SEL_PUBID_SPI0_COMB                           0x0000000FU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_IRQ2                           0x0000000EU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_IRQ1                           0x0000000DU
#define EVTSVT_CPUIRQ0SEL_PUBID_LRFD_IRQ0                           0x0000000CU
#define EVTSVT_CPUIRQ0SEL_PUBID_FLASH_IRQ                           0x0000000BU
#define EVTSVT_CPUIRQ0SEL_PUBID_GPIO_EVT                            0x0000000AU
#define EVTSVT_CPUIRQ0SEL_PUBID_GPIO_COMB                           0x00000009U
#define EVTSVT_CPUIRQ0SEL_PUBID_SYSTIM_COMB                         0x00000008U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_IOC_COMB                        0x00000007U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_LPMCMP_IRQ                      0x00000006U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_DBG_COMB                        0x00000005U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_RTC_COMB                        0x00000004U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_CKM_COMB                        0x00000003U
#define EVTSVT_CPUIRQ0SEL_PUBID_AON_PMU_COMB                        0x00000002U
#define EVTSVT_CPUIRQ0SEL_PUBID_NONE                                0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ1SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ1SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ1SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3_ADC                           0x00000039U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3_DMA                           0x00000038U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3_COMB                          0x00000037U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3C2                             0x00000036U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3C1                             0x00000035U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT3C0                             0x00000034U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2_ADC                           0x00000033U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2_DMA                           0x00000032U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2_COMB                          0x00000031U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2C2                             0x00000030U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2C1                             0x0000002FU
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT2C0                             0x0000002EU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_EVT2                           0x0000002CU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_EVT1                           0x0000002BU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_EVT0                           0x0000002AU
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1_ADC                           0x00000029U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1_DMA                           0x00000028U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1C2                             0x00000027U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1C1                             0x00000026U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1C0                             0x00000025U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0_ADC                           0x00000024U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0_DMA                           0x00000023U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0C2                             0x00000022U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0C1                             0x00000021U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0C0                             0x00000020U
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM4                             0x0000001FU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM3                             0x0000001EU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM2                             0x0000001DU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM1                             0x0000001CU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM0                             0x0000001BU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM_LT                           0x0000001AU
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM_HB                           0x00000019U
#define EVTSVT_CPUIRQ1SEL_PUBID_I2C0_IRQ                            0x00000018U
#define EVTSVT_CPUIRQ1SEL_PUBID_UART0_COMB                          0x00000017U
#define EVTSVT_CPUIRQ1SEL_PUBID_AES_COMB                            0x00000016U
#define EVTSVT_CPUIRQ1SEL_PUBID_DMA_ERR                             0x00000015U
#define EVTSVT_CPUIRQ1SEL_PUBID_DMA_DONE_COMB                       0x00000014U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT1_COMB                          0x00000013U
#define EVTSVT_CPUIRQ1SEL_PUBID_LGPT0_COMB                          0x00000012U
#define EVTSVT_CPUIRQ1SEL_PUBID_ADC_EVT                             0x00000011U
#define EVTSVT_CPUIRQ1SEL_PUBID_ADC_COMB                            0x00000010U
#define EVTSVT_CPUIRQ1SEL_PUBID_SPI0_COMB                           0x0000000FU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_IRQ2                           0x0000000EU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_IRQ1                           0x0000000DU
#define EVTSVT_CPUIRQ1SEL_PUBID_LRFD_IRQ0                           0x0000000CU
#define EVTSVT_CPUIRQ1SEL_PUBID_FLASH_IRQ                           0x0000000BU
#define EVTSVT_CPUIRQ1SEL_PUBID_GPIO_EVT                            0x0000000AU
#define EVTSVT_CPUIRQ1SEL_PUBID_GPIO_COMB                           0x00000009U
#define EVTSVT_CPUIRQ1SEL_PUBID_SYSTIM_COMB                         0x00000008U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_IOC_COMB                        0x00000007U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_LPMCMP_IRQ                      0x00000006U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_DBG_COMB                        0x00000005U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_RTC_COMB                        0x00000004U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_CKM_COMB                        0x00000003U
#define EVTSVT_CPUIRQ1SEL_PUBID_AON_PMU_COMB                        0x00000002U
#define EVTSVT_CPUIRQ1SEL_PUBID_NONE                                0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ2SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ2SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ2SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ2SEL_PUBID_LGPT3_COMB                          0x00000037U
#define EVTSVT_CPUIRQ2SEL_PUBID_LGPT2_COMB                          0x00000031U
#define EVTSVT_CPUIRQ2SEL_PUBID_I2C0_IRQ                            0x00000018U
#define EVTSVT_CPUIRQ2SEL_PUBID_UART0_COMB                          0x00000017U
#define EVTSVT_CPUIRQ2SEL_PUBID_AES_COMB                            0x00000016U
#define EVTSVT_CPUIRQ2SEL_PUBID_DMA_ERR                             0x00000015U
#define EVTSVT_CPUIRQ2SEL_PUBID_DMA_DONE_COMB                       0x00000014U
#define EVTSVT_CPUIRQ2SEL_PUBID_LGPT1_COMB                          0x00000013U
#define EVTSVT_CPUIRQ2SEL_PUBID_LGPT0_COMB                          0x00000012U
#define EVTSVT_CPUIRQ2SEL_PUBID_ADC_COMB                            0x00000010U
#define EVTSVT_CPUIRQ2SEL_PUBID_SPI0_COMB                           0x0000000FU
#define EVTSVT_CPUIRQ2SEL_PUBID_LRFD_IRQ2                           0x0000000EU
#define EVTSVT_CPUIRQ2SEL_PUBID_LRFD_IRQ1                           0x0000000DU
#define EVTSVT_CPUIRQ2SEL_PUBID_LRFD_IRQ0                           0x0000000CU
#define EVTSVT_CPUIRQ2SEL_PUBID_FLASH_IRQ                           0x0000000BU
#define EVTSVT_CPUIRQ2SEL_PUBID_GPIO_COMB                           0x00000009U
#define EVTSVT_CPUIRQ2SEL_PUBID_SYSTIM_COMB                         0x00000008U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_IOC_COMB                        0x00000007U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_LPMCMP_IRQ                      0x00000006U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_DBG_COMB                        0x00000005U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_RTC_COMB                        0x00000004U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_CKM_COMB                        0x00000003U
#define EVTSVT_CPUIRQ2SEL_PUBID_AON_PMU_COMB                        0x00000002U
#define EVTSVT_CPUIRQ2SEL_PUBID_NONE                                0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ3SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ3SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ3SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ3SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ3SEL_PUBID_LGPT3_COMB                          0x00000037U
#define EVTSVT_CPUIRQ3SEL_PUBID_LGPT2_COMB                          0x00000031U
#define EVTSVT_CPUIRQ3SEL_PUBID_I2C0_IRQ                            0x00000018U
#define EVTSVT_CPUIRQ3SEL_PUBID_UART0_COMB                          0x00000017U
#define EVTSVT_CPUIRQ3SEL_PUBID_AES_COMB                            0x00000016U
#define EVTSVT_CPUIRQ3SEL_PUBID_DMA_ERR                             0x00000015U
#define EVTSVT_CPUIRQ3SEL_PUBID_DMA_DONE_COMB                       0x00000014U
#define EVTSVT_CPUIRQ3SEL_PUBID_LGPT1_COMB                          0x00000013U
#define EVTSVT_CPUIRQ3SEL_PUBID_LGPT0_COMB                          0x00000012U
#define EVTSVT_CPUIRQ3SEL_PUBID_ADC_COMB                            0x00000010U
#define EVTSVT_CPUIRQ3SEL_PUBID_SPI0_COMB                           0x0000000FU
#define EVTSVT_CPUIRQ3SEL_PUBID_LRFD_IRQ2                           0x0000000EU
#define EVTSVT_CPUIRQ3SEL_PUBID_LRFD_IRQ1                           0x0000000DU
#define EVTSVT_CPUIRQ3SEL_PUBID_LRFD_IRQ0                           0x0000000CU
#define EVTSVT_CPUIRQ3SEL_PUBID_FLASH_IRQ                           0x0000000BU
#define EVTSVT_CPUIRQ3SEL_PUBID_GPIO_COMB                           0x00000009U
#define EVTSVT_CPUIRQ3SEL_PUBID_SYSTIM_COMB                         0x00000008U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_IOC_COMB                        0x00000007U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_LPMCMP_IRQ                      0x00000006U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_DBG_COMB                        0x00000005U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_RTC_COMB                        0x00000004U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_CKM_COMB                        0x00000003U
#define EVTSVT_CPUIRQ3SEL_PUBID_AON_PMU_COMB                        0x00000002U
#define EVTSVT_CPUIRQ3SEL_PUBID_NONE                                0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ4SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ4SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ4SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ4SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ4SEL_PUBID_LGPT3_COMB                          0x00000037U
#define EVTSVT_CPUIRQ4SEL_PUBID_LGPT2_COMB                          0x00000031U
#define EVTSVT_CPUIRQ4SEL_PUBID_I2C0_IRQ                            0x00000018U
#define EVTSVT_CPUIRQ4SEL_PUBID_UART0_COMB                          0x00000017U
#define EVTSVT_CPUIRQ4SEL_PUBID_AES_COMB                            0x00000016U
#define EVTSVT_CPUIRQ4SEL_PUBID_DMA_ERR                             0x00000015U
#define EVTSVT_CPUIRQ4SEL_PUBID_DMA_DONE_COMB                       0x00000014U
#define EVTSVT_CPUIRQ4SEL_PUBID_LGPT1_COMB                          0x00000013U
#define EVTSVT_CPUIRQ4SEL_PUBID_LGPT0_COMB                          0x00000012U
#define EVTSVT_CPUIRQ4SEL_PUBID_ADC_COMB                            0x00000010U
#define EVTSVT_CPUIRQ4SEL_PUBID_SPI0_COMB                           0x0000000FU
#define EVTSVT_CPUIRQ4SEL_PUBID_LRFD_IRQ2                           0x0000000EU
#define EVTSVT_CPUIRQ4SEL_PUBID_LRFD_IRQ1                           0x0000000DU
#define EVTSVT_CPUIRQ4SEL_PUBID_LRFD_IRQ0                           0x0000000CU
#define EVTSVT_CPUIRQ4SEL_PUBID_FLASH_IRQ                           0x0000000BU
#define EVTSVT_CPUIRQ4SEL_PUBID_GPIO_COMB                           0x00000009U
#define EVTSVT_CPUIRQ4SEL_PUBID_SYSTIM_COMB                         0x00000008U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_IOC_COMB                        0x00000007U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_LPMCMP_IRQ                      0x00000006U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_DBG_COMB                        0x00000005U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_RTC_COMB                        0x00000004U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_CKM_COMB                        0x00000003U
#define EVTSVT_CPUIRQ4SEL_PUBID_AON_PMU_COMB                        0x00000002U
#define EVTSVT_CPUIRQ4SEL_PUBID_NONE                                0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ5SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
#define EVTSVT_CPUIRQ5SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ5SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ5SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ5SEL_PUBID_GPIO_COMB                           0x00000009U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ6SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
#define EVTSVT_CPUIRQ6SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ6SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ6SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ6SEL_PUBID_LRFD_IRQ0                           0x0000000CU

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ7SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
#define EVTSVT_CPUIRQ7SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ7SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ7SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ7SEL_PUBID_LRFD_IRQ1                           0x0000000DU

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ8SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
#define EVTSVT_CPUIRQ8SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ8SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ8SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ8SEL_PUBID_DMA_DONE_COMB                       0x00000014U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ9SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
#define EVTSVT_CPUIRQ9SEL_PUBID_W                                            6U
#define EVTSVT_CPUIRQ9SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_CPUIRQ9SEL_PUBID_S                                            0U
#define EVTSVT_CPUIRQ9SEL_PUBID_AES_COMB                            0x00000016U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ10SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
#define EVTSVT_CPUIRQ10SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ10SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ10SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ10SEL_PUBID_SPI0_COMB                          0x0000000FU

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ11SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
#define EVTSVT_CPUIRQ11SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ11SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ11SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ11SEL_PUBID_UART0_COMB                         0x00000017U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ12SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
#define EVTSVT_CPUIRQ12SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ12SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ12SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ12SEL_PUBID_I2C0_IRQ                           0x00000018U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ13SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
#define EVTSVT_CPUIRQ13SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ13SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ13SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ13SEL_PUBID_LGPT0_COMB                         0x00000012U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ14SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
#define EVTSVT_CPUIRQ14SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ14SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ14SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ14SEL_PUBID_LGPT1_COMB                         0x00000013U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ15SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
#define EVTSVT_CPUIRQ15SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ15SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ15SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ15SEL_PUBID_ADC_COMB                           0x00000010U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ16SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_CPUIRQ16SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ16SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ16SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_CPUIRQ16SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_CPUIRQ16SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_CPUIRQ16SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_CPUIRQ16SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_CPUIRQ16SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_CPUIRQ16SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_CPUIRQ16SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_CPUIRQ16SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_CPUIRQ16SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_CPUIRQ16SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_CPUIRQ16SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_CPUIRQ16SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_CPUIRQ16SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_CPUIRQ16SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_CPUIRQ16SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_CPUIRQ16SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ17SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
#define EVTSVT_CPUIRQ17SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ17SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ17SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ17SEL_PUBID_LGPT2_COMB                         0x00000031U

//*****************************************************************************
//
// Register: EVTSVT_O_CPUIRQ18SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
#define EVTSVT_CPUIRQ18SEL_PUBID_W                                           6U
#define EVTSVT_CPUIRQ18SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_CPUIRQ18SEL_PUBID_S                                           0U
#define EVTSVT_CPUIRQ18SEL_PUBID_LGPT3_COMB                         0x00000037U

//*****************************************************************************
//
// Register: EVTSVT_O_SYSTIMC0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// AON_RTC_COMB             AON_RTC event, controlled by the RTC:IMASK setting
#define EVTSVT_SYSTIMC0SEL_PUBID_W                                           6U
#define EVTSVT_SYSTIMC0SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_SYSTIMC0SEL_PUBID_S                                           0U
#define EVTSVT_SYSTIMC0SEL_PUBID_AON_RTC_COMB                       0x00000004U

//*****************************************************************************
//
// Register: EVTSVT_O_SYSTIMC1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_SYSTIMC1SEL_PUBID_W                                           6U
#define EVTSVT_SYSTIMC1SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_SYSTIMC1SEL_PUBID_S                                           0U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_SYSTIMC1SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_SYSTIMC1SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_SYSTIMC1SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_SYSTIMC1SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_SYSTIMC1SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_SYSTIMC1SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_SYSTIMC1SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_SYSTIMC1SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_SYSTIMC1SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_SYSTIMC1SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_SYSTIMC1SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_SYSTIMC1SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_SYSTIMC1SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_SYSTIMC1SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_SYSTIMC1SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_SYSTIMC1SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_SYSTIMC2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
#define EVTSVT_SYSTIMC2SEL_PUBID_W                                           6U
#define EVTSVT_SYSTIMC2SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_SYSTIMC2SEL_PUBID_S                                           0U
#define EVTSVT_SYSTIMC2SEL_PUBID_LRFD_EVT0                          0x0000002AU

//*****************************************************************************
//
// Register: EVTSVT_O_SYSTIMC3SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
#define EVTSVT_SYSTIMC3SEL_PUBID_W                                           6U
#define EVTSVT_SYSTIMC3SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_SYSTIMC3SEL_PUBID_S                                           0U
#define EVTSVT_SYSTIMC3SEL_PUBID_LRFD_EVT1                          0x0000002BU

//*****************************************************************************
//
// Register: EVTSVT_O_SYSTIMC4SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
#define EVTSVT_SYSTIMC4SEL_PUBID_W                                           6U
#define EVTSVT_SYSTIMC4SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_SYSTIMC4SEL_PUBID_S                                           0U
#define EVTSVT_SYSTIMC4SEL_PUBID_LRFD_EVT2                          0x0000002CU

//*****************************************************************************
//
// Register: EVTSVT_O_ADCTRGSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_ADCTRGSEL_PUBID_W                                             6U
#define EVTSVT_ADCTRGSEL_PUBID_M                                    0x0000003FU
#define EVTSVT_ADCTRGSEL_PUBID_S                                             0U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3_ADC                            0x00000039U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3_DMA                            0x00000038U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3_COMB                           0x00000037U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3C2                              0x00000036U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3C1                              0x00000035U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT3C0                              0x00000034U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2_ADC                            0x00000033U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2_DMA                            0x00000032U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2_COMB                           0x00000031U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2C2                              0x00000030U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2C1                              0x0000002FU
#define EVTSVT_ADCTRGSEL_PUBID_LGPT2C0                              0x0000002EU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_EVT2                            0x0000002CU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_EVT1                            0x0000002BU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_EVT0                            0x0000002AU
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1_ADC                            0x00000029U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1_DMA                            0x00000028U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1C2                              0x00000027U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1C1                              0x00000026U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1C0                              0x00000025U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0_ADC                            0x00000024U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0_DMA                            0x00000023U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0C2                              0x00000022U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0C1                              0x00000021U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0C0                              0x00000020U
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM4                              0x0000001FU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM3                              0x0000001EU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM2                              0x0000001DU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM1                              0x0000001CU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM0                              0x0000001BU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM_LT                            0x0000001AU
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM_HB                            0x00000019U
#define EVTSVT_ADCTRGSEL_PUBID_I2C0_IRQ                             0x00000018U
#define EVTSVT_ADCTRGSEL_PUBID_UART0_COMB                           0x00000017U
#define EVTSVT_ADCTRGSEL_PUBID_AES_COMB                             0x00000016U
#define EVTSVT_ADCTRGSEL_PUBID_DMA_ERR                              0x00000015U
#define EVTSVT_ADCTRGSEL_PUBID_DMA_DONE_COMB                        0x00000014U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT1_COMB                           0x00000013U
#define EVTSVT_ADCTRGSEL_PUBID_LGPT0_COMB                           0x00000012U
#define EVTSVT_ADCTRGSEL_PUBID_ADC_EVT                              0x00000011U
#define EVTSVT_ADCTRGSEL_PUBID_ADC_COMB                             0x00000010U
#define EVTSVT_ADCTRGSEL_PUBID_SPI0_COMB                            0x0000000FU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_IRQ2                            0x0000000EU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_IRQ1                            0x0000000DU
#define EVTSVT_ADCTRGSEL_PUBID_LRFD_IRQ0                            0x0000000CU
#define EVTSVT_ADCTRGSEL_PUBID_FLASH_IRQ                            0x0000000BU
#define EVTSVT_ADCTRGSEL_PUBID_GPIO_EVT                             0x0000000AU
#define EVTSVT_ADCTRGSEL_PUBID_GPIO_COMB                            0x00000009U
#define EVTSVT_ADCTRGSEL_PUBID_SYSTIM_COMB                          0x00000008U
#define EVTSVT_ADCTRGSEL_PUBID_AON_IOC_COMB                         0x00000007U
#define EVTSVT_ADCTRGSEL_PUBID_AON_LPMCMP_IRQ                       0x00000006U
#define EVTSVT_ADCTRGSEL_PUBID_AON_DBG_COMB                         0x00000005U
#define EVTSVT_ADCTRGSEL_PUBID_AON_RTC_COMB                         0x00000004U
#define EVTSVT_ADCTRGSEL_PUBID_AON_CKM_COMB                         0x00000003U
#define EVTSVT_ADCTRGSEL_PUBID_AON_PMU_COMB                         0x00000002U
#define EVTSVT_ADCTRGSEL_PUBID_NONE                                 0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPTSYNCSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_LGPTSYNCSEL_PUBID_W                                           6U
#define EVTSVT_LGPTSYNCSEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPTSYNCSEL_PUBID_S                                           0U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPTSYNCSEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_LGPTSYNCSEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_LGPTSYNCSEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_LGPTSYNCSEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_LGPTSYNCSEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_LGPTSYNCSEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_LGPTSYNCSEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPTSYNCSEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_LGPTSYNCSEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_LGPTSYNCSEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_LGPTSYNCSEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_LGPTSYNCSEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPTSYNCSEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_LGPTSYNCSEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_LGPTSYNCSEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_LGPTSYNCSEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT0IN0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_LGPT0IN0SEL_PUBID_W                                           6U
#define EVTSVT_LGPT0IN0SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT0IN0SEL_PUBID_S                                           0U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT0IN0SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_LGPT0IN0SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_LGPT0IN0SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_LGPT0IN0SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_LGPT0IN0SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_LGPT0IN0SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_LGPT0IN0SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT0IN0SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_LGPT0IN0SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_LGPT0IN0SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_LGPT0IN0SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_LGPT0IN0SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT0IN0SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_LGPT0IN0SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_LGPT0IN0SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_LGPT0IN0SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT0IN1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT0IN1SEL_PUBID_W                                           6U
#define EVTSVT_LGPT0IN1SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT0IN1SEL_PUBID_S                                           0U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT0IN1SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT0IN1SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT0IN1SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT0IN1SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT0IN1SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT0IN1SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT0IN1SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT0IN1SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT0IN2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT0IN2SEL_PUBID_W                                           6U
#define EVTSVT_LGPT0IN2SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT0IN2SEL_PUBID_S                                           0U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT0IN2SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT0IN2SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT0IN2SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT0IN2SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT0IN2SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT0IN2SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT0IN2SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT0IN2SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT0TENSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT0TENSEL_PUBID_W                                           6U
#define EVTSVT_LGPT0TENSEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT0TENSEL_PUBID_S                                           0U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT0TENSEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT0TENSEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT0TENSEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT0TENSEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT0TENSEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT0TENSEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT0TENSEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT0TENSEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT1IN0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_LGPT1IN0SEL_PUBID_W                                           6U
#define EVTSVT_LGPT1IN0SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT1IN0SEL_PUBID_S                                           0U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT1IN0SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_LGPT1IN0SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_LGPT1IN0SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_LGPT1IN0SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_LGPT1IN0SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_LGPT1IN0SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_LGPT1IN0SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT1IN0SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_LGPT1IN0SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_LGPT1IN0SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_LGPT1IN0SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_LGPT1IN0SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT1IN0SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_LGPT1IN0SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_LGPT1IN0SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_LGPT1IN0SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT1IN1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT1IN1SEL_PUBID_W                                           6U
#define EVTSVT_LGPT1IN1SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT1IN1SEL_PUBID_S                                           0U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT1IN1SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT1IN1SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT1IN1SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT1IN1SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT1IN1SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT1IN1SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT1IN1SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT1IN1SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT1IN2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT1IN2SEL_PUBID_W                                           6U
#define EVTSVT_LGPT1IN2SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT1IN2SEL_PUBID_S                                           0U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT1IN2SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT1IN2SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT1IN2SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT1IN2SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT1IN2SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT1IN2SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT1IN2SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT1IN2SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT1TENSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT1TENSEL_PUBID_W                                           6U
#define EVTSVT_LGPT1TENSEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT1TENSEL_PUBID_S                                           0U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT1TENSEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT1TENSEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT1TENSEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT1TENSEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT1TENSEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT1TENSEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT1TENSEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT1TENSEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT2IN0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_LGPT2IN0SEL_PUBID_W                                           6U
#define EVTSVT_LGPT2IN0SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT2IN0SEL_PUBID_S                                           0U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT2IN0SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_LGPT2IN0SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_LGPT2IN0SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_LGPT2IN0SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_LGPT2IN0SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_LGPT2IN0SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_LGPT2IN0SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT2IN0SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_LGPT2IN0SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_LGPT2IN0SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_LGPT2IN0SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_LGPT2IN0SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT2IN0SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_LGPT2IN0SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_LGPT2IN0SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_LGPT2IN0SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT2IN1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT2IN1SEL_PUBID_W                                           6U
#define EVTSVT_LGPT2IN1SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT2IN1SEL_PUBID_S                                           0U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT2IN1SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT2IN1SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT2IN1SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT2IN1SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT2IN1SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT2IN1SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT2IN1SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT2IN1SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT2IN2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT2IN2SEL_PUBID_W                                           6U
#define EVTSVT_LGPT2IN2SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT2IN2SEL_PUBID_S                                           0U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT2IN2SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT2IN2SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT2IN2SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT2IN2SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT2IN2SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT2IN2SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT2IN2SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT2IN2SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT2TENSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT2TENSEL_PUBID_W                                           6U
#define EVTSVT_LGPT2TENSEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT2TENSEL_PUBID_S                                           0U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT2TENSEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT2TENSEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT2TENSEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT2TENSEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT2TENSEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT2TENSEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT2TENSEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT2TENSEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT3IN0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_LGPT3IN0SEL_PUBID_W                                           6U
#define EVTSVT_LGPT3IN0SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT3IN0SEL_PUBID_S                                           0U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3_COMB                         0x00000037U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2_COMB                         0x00000031U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT3IN0SEL_PUBID_I2C0_IRQ                           0x00000018U
#define EVTSVT_LGPT3IN0SEL_PUBID_UART0_COMB                         0x00000017U
#define EVTSVT_LGPT3IN0SEL_PUBID_AES_COMB                           0x00000016U
#define EVTSVT_LGPT3IN0SEL_PUBID_DMA_ERR                            0x00000015U
#define EVTSVT_LGPT3IN0SEL_PUBID_DMA_DONE_COMB                      0x00000014U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT1_COMB                         0x00000013U
#define EVTSVT_LGPT3IN0SEL_PUBID_LGPT0_COMB                         0x00000012U
#define EVTSVT_LGPT3IN0SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT3IN0SEL_PUBID_ADC_COMB                           0x00000010U
#define EVTSVT_LGPT3IN0SEL_PUBID_SPI0_COMB                          0x0000000FU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_IRQ2                          0x0000000EU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_IRQ1                          0x0000000DU
#define EVTSVT_LGPT3IN0SEL_PUBID_LRFD_IRQ0                          0x0000000CU
#define EVTSVT_LGPT3IN0SEL_PUBID_FLASH_IRQ                          0x0000000BU
#define EVTSVT_LGPT3IN0SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT3IN0SEL_PUBID_GPIO_COMB                          0x00000009U
#define EVTSVT_LGPT3IN0SEL_PUBID_SYSTIM_COMB                        0x00000008U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_IOC_COMB                       0x00000007U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_LPMCMP_IRQ                     0x00000006U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_DBG_COMB                       0x00000005U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_RTC_COMB                       0x00000004U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_CKM_COMB                       0x00000003U
#define EVTSVT_LGPT3IN0SEL_PUBID_AON_PMU_COMB                       0x00000002U
#define EVTSVT_LGPT3IN0SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT3IN1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT3IN1SEL_PUBID_W                                           6U
#define EVTSVT_LGPT3IN1SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT3IN1SEL_PUBID_S                                           0U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT3IN1SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT3IN1SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT3IN1SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT3IN1SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT3IN1SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT3IN1SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT3IN1SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT3IN1SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT3IN2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT3IN2SEL_PUBID_W                                           6U
#define EVTSVT_LGPT3IN2SEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT3IN2SEL_PUBID_S                                           0U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT3IN2SEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT3IN2SEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT3IN2SEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT3IN2SEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT3IN2SEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT3IN2SEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT3IN2SEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT3IN2SEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LGPT3TENSEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// NONE                     Always inactive
#define EVTSVT_LGPT3TENSEL_PUBID_W                                           6U
#define EVTSVT_LGPT3TENSEL_PUBID_M                                  0x0000003FU
#define EVTSVT_LGPT3TENSEL_PUBID_S                                           0U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT3_ADC                          0x00000039U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT3_DMA                          0x00000038U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT3C2                            0x00000036U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT3C1                            0x00000035U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT3C0                            0x00000034U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT2_ADC                          0x00000033U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT2_DMA                          0x00000032U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT2C2                            0x00000030U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT2C1                            0x0000002FU
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT2C0                            0x0000002EU
#define EVTSVT_LGPT3TENSEL_PUBID_LRFD_EVT2                          0x0000002CU
#define EVTSVT_LGPT3TENSEL_PUBID_LRFD_EVT1                          0x0000002BU
#define EVTSVT_LGPT3TENSEL_PUBID_LRFD_EVT0                          0x0000002AU
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT1_ADC                          0x00000029U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT1_DMA                          0x00000028U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT1C2                            0x00000027U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT1C1                            0x00000026U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT1C0                            0x00000025U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT0_ADC                          0x00000024U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT0_DMA                          0x00000023U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT0C2                            0x00000022U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT0C1                            0x00000021U
#define EVTSVT_LGPT3TENSEL_PUBID_LGPT0C0                            0x00000020U
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM4                            0x0000001FU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM3                            0x0000001EU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM2                            0x0000001DU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM1                            0x0000001CU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM0                            0x0000001BU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM_LT                          0x0000001AU
#define EVTSVT_LGPT3TENSEL_PUBID_SYSTIM_HB                          0x00000019U
#define EVTSVT_LGPT3TENSEL_PUBID_ADC_EVT                            0x00000011U
#define EVTSVT_LGPT3TENSEL_PUBID_GPIO_EVT                           0x0000000AU
#define EVTSVT_LGPT3TENSEL_PUBID_NONE                               0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_LRFDIN0SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
#define EVTSVT_LRFDIN0SEL_PUBID_W                                            6U
#define EVTSVT_LRFDIN0SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_LRFDIN0SEL_PUBID_S                                            0U
#define EVTSVT_LRFDIN0SEL_PUBID_SYSTIM2                             0x0000001DU

//*****************************************************************************
//
// Register: EVTSVT_O_LRFDIN1SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
#define EVTSVT_LRFDIN1SEL_PUBID_W                                            6U
#define EVTSVT_LRFDIN1SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_LRFDIN1SEL_PUBID_S                                            0U
#define EVTSVT_LRFDIN1SEL_PUBID_SYSTIM3                             0x0000001EU

//*****************************************************************************
//
// Register: EVTSVT_O_LRFDIN2SEL
//
//*****************************************************************************
// Field:   [5:0] PUBID
//
// Read only selection value
// ENUMs:
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
#define EVTSVT_LRFDIN2SEL_PUBID_W                                            6U
#define EVTSVT_LRFDIN2SEL_PUBID_M                                   0x0000003FU
#define EVTSVT_LRFDIN2SEL_PUBID_S                                            0U
#define EVTSVT_LRFDIN2SEL_PUBID_SYSTIM4                             0x0000001FU

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH0SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// UART0RXTRG               Selects uart0rxtrg as channel source
// SPI0TXTRG                Selects spi0txtrg as channel source
#define EVTSVT_DMACH0SEL_IPID_W                                              3U
#define EVTSVT_DMACH0SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH0SEL_IPID_S                                              0U
#define EVTSVT_DMACH0SEL_IPID_UART0RXTRG                            0x00000007U
#define EVTSVT_DMACH0SEL_IPID_SPI0TXTRG                             0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH1SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// UART0TXTRG               Selects uart0txtrg as channel source
// SPI0RXTRG                Selects spi0rxtrg as channel source
#define EVTSVT_DMACH1SEL_IPID_W                                              3U
#define EVTSVT_DMACH1SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH1SEL_IPID_S                                              0U
#define EVTSVT_DMACH1SEL_IPID_UART0TXTRG                            0x00000006U
#define EVTSVT_DMACH1SEL_IPID_SPI0RXTRG                             0x00000001U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH2SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// UART0TXTRG               Selects uart0txtrg as channel source
// RSVD                     Reserved value. Should not be programmed.
#define EVTSVT_DMACH2SEL_IPID_W                                              3U
#define EVTSVT_DMACH2SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH2SEL_IPID_S                                              0U
#define EVTSVT_DMACH2SEL_IPID_UART0TXTRG                            0x00000006U
#define EVTSVT_DMACH2SEL_IPID_RSVD                                  0x00000002U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH3SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// UART0RXTRG               Selects uart0rxtrg as channel source
// ADC0TRG                  Selects adc0trg as channel source
#define EVTSVT_DMACH3SEL_IPID_W                                              3U
#define EVTSVT_DMACH3SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH3SEL_IPID_S                                              0U
#define EVTSVT_DMACH3SEL_IPID_UART0RXTRG                            0x00000007U
#define EVTSVT_DMACH3SEL_IPID_ADC0TRG                               0x00000005U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH4SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LAESTRGA                 Selects laestrga as channel source
// RSVD                     Reserved value. Should not be programmed.
#define EVTSVT_DMACH4SEL_IPID_W                                              3U
#define EVTSVT_DMACH4SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH4SEL_IPID_S                                              0U
#define EVTSVT_DMACH4SEL_IPID_LAESTRGA                              0x00000003U
#define EVTSVT_DMACH4SEL_IPID_RSVD                                  0x00000002U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH5SEL
//
//*****************************************************************************
// Field:   [2:0] IPID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// ADC0TRG                  Selects adc0trg as channel source
// LAESTRGB                 Selects laestrgb as channel source
#define EVTSVT_DMACH5SEL_IPID_W                                              3U
#define EVTSVT_DMACH5SEL_IPID_M                                     0x00000007U
#define EVTSVT_DMACH5SEL_IPID_S                                              0U
#define EVTSVT_DMACH5SEL_IPID_ADC0TRG                               0x00000005U
#define EVTSVT_DMACH5SEL_IPID_LAESTRGB                              0x00000004U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH6SEL
//
//*****************************************************************************
// Field:    [16] EDGDETDIS
//
// Edge detect disable.
// 0: Enabled.
// 1: Disabled
#define EVTSVT_DMACH6SEL_EDGDETDIS                                  0x00010000U
#define EVTSVT_DMACH6SEL_EDGDETDIS_M                                0x00010000U
#define EVTSVT_DMACH6SEL_EDGDETDIS_S                                        16U

// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_DMACH6SEL_PUBID_W                                             6U
#define EVTSVT_DMACH6SEL_PUBID_M                                    0x0000003FU
#define EVTSVT_DMACH6SEL_PUBID_S                                             0U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3_ADC                            0x00000039U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3_DMA                            0x00000038U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3_COMB                           0x00000037U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3C2                              0x00000036U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3C1                              0x00000035U
#define EVTSVT_DMACH6SEL_PUBID_LGPT3C0                              0x00000034U
#define EVTSVT_DMACH6SEL_PUBID_LGPT2_ADC                            0x00000033U
#define EVTSVT_DMACH6SEL_PUBID_LGPT2_DMA                            0x00000032U
#define EVTSVT_DMACH6SEL_PUBID_LGPT2_COMB                           0x00000031U
#define EVTSVT_DMACH6SEL_PUBID_LGPT2C2                              0x00000030U
#define EVTSVT_DMACH6SEL_PUBID_LGPT2C1                              0x0000002FU
#define EVTSVT_DMACH6SEL_PUBID_LGPT2C0                              0x0000002EU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_EVT2                            0x0000002CU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_EVT1                            0x0000002BU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_EVT0                            0x0000002AU
#define EVTSVT_DMACH6SEL_PUBID_LGPT1_ADC                            0x00000029U
#define EVTSVT_DMACH6SEL_PUBID_LGPT1_DMA                            0x00000028U
#define EVTSVT_DMACH6SEL_PUBID_LGPT1C2                              0x00000027U
#define EVTSVT_DMACH6SEL_PUBID_LGPT1C1                              0x00000026U
#define EVTSVT_DMACH6SEL_PUBID_LGPT1C0                              0x00000025U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0_ADC                            0x00000024U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0_DMA                            0x00000023U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0C2                              0x00000022U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0C1                              0x00000021U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0C0                              0x00000020U
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM4                              0x0000001FU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM3                              0x0000001EU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM2                              0x0000001DU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM1                              0x0000001CU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM0                              0x0000001BU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM_LT                            0x0000001AU
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM_HB                            0x00000019U
#define EVTSVT_DMACH6SEL_PUBID_I2C0_IRQ                             0x00000018U
#define EVTSVT_DMACH6SEL_PUBID_UART0_COMB                           0x00000017U
#define EVTSVT_DMACH6SEL_PUBID_AES_COMB                             0x00000016U
#define EVTSVT_DMACH6SEL_PUBID_DMA_ERR                              0x00000015U
#define EVTSVT_DMACH6SEL_PUBID_DMA_DONE_COMB                        0x00000014U
#define EVTSVT_DMACH6SEL_PUBID_LGPT1_COMB                           0x00000013U
#define EVTSVT_DMACH6SEL_PUBID_LGPT0_COMB                           0x00000012U
#define EVTSVT_DMACH6SEL_PUBID_ADC_EVT                              0x00000011U
#define EVTSVT_DMACH6SEL_PUBID_ADC_COMB                             0x00000010U
#define EVTSVT_DMACH6SEL_PUBID_SPI0_COMB                            0x0000000FU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_IRQ2                            0x0000000EU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_IRQ1                            0x0000000DU
#define EVTSVT_DMACH6SEL_PUBID_LRFD_IRQ0                            0x0000000CU
#define EVTSVT_DMACH6SEL_PUBID_FLASH_IRQ                            0x0000000BU
#define EVTSVT_DMACH6SEL_PUBID_GPIO_EVT                             0x0000000AU
#define EVTSVT_DMACH6SEL_PUBID_GPIO_COMB                            0x00000009U
#define EVTSVT_DMACH6SEL_PUBID_SYSTIM_COMB                          0x00000008U
#define EVTSVT_DMACH6SEL_PUBID_AON_IOC_COMB                         0x00000007U
#define EVTSVT_DMACH6SEL_PUBID_AON_LPMCMP_IRQ                       0x00000006U
#define EVTSVT_DMACH6SEL_PUBID_AON_DBG_COMB                         0x00000005U
#define EVTSVT_DMACH6SEL_PUBID_AON_RTC_COMB                         0x00000004U
#define EVTSVT_DMACH6SEL_PUBID_AON_CKM_COMB                         0x00000003U
#define EVTSVT_DMACH6SEL_PUBID_AON_PMU_COMB                         0x00000002U
#define EVTSVT_DMACH6SEL_PUBID_NONE                                 0x00000000U

//*****************************************************************************
//
// Register: EVTSVT_O_DMACH7SEL
//
//*****************************************************************************
// Field:    [16] EDGDETDIS
//
// Edge detect disable.
// 0: Enabled.
// 1: Disabled
#define EVTSVT_DMACH7SEL_EDGDETDIS                                  0x00010000U
#define EVTSVT_DMACH7SEL_EDGDETDIS_M                                0x00010000U
#define EVTSVT_DMACH7SEL_EDGDETDIS_S                                        16U

// Field:   [5:0] PUBID
//
// Read/write selection value.
// Writing any other value than values defined by a ENUM may result in
// undefined behavior.
// ENUMs:
// LGPT3_ADC                LGPT3 ADC trigger event, controlled by
//                          LGPT3:ADCTRG setting
// LGPT3_DMA                LGPT3 DMA request event, controlled by LGPT3:DMA
//                          setting
// LGPT3_COMB               LGPT3 combined interrupt, interrupt flags are
//                          found here LGPT3:MIS
// LGPT3C2                  LGPT3 compare/capture output event 2, controlled
//                          by LGPT3:C2CFG setting
// LGPT3C1                  LGPT3 compare/capture output event 1, controlled
//                          by LGPT3:C1CFG setting
// LGPT3C0                  LGPT3 compare/capture output event 0, controlled
//                          by LGPT3:C0CFG setting
// LGPT2_ADC                LGPT2 ADC trigger event, controlled by
//                          LGPT2:ADCTRG setting
// LGPT2_DMA                LGPT2 DMA request event, controlled by LGPT2:DMA
//                          setting
// LGPT2_COMB               LGPT2 combined interrupt, interrupt flags are
//                          found here LGPT2:MIS
// LGPT2C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT2:C2CFG setting
// LGPT2C1                  LGPT2 compare/capture output event 1, controlled
//                          by LGPT2:C1CFG setting
// LGPT2C0                  LGPT2 compare/capture output event 0, controlled
//                          by LGPT2:C0CFG setting
// LRFD_EVT2                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC2
// LRFD_EVT1                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC1
// LRFD_EVT0                LRFD interrupt to SYSTIM, controlled by
//                          LRFDDBELL:SYSTIMOEV.SRC0
// LGPT1_ADC                LGPT1 ADC trigger event, controlled by
//                          LGPT1:ADCTRG setting
// LGPT1_DMA                LGPT1 DMA request event, controlled by LGPT1:DMA
//                          setting
// LGPT1C2                  LGPT1 compare/capture output event 2, controlled
//                          by LGPT1:C2CFG setting
// LGPT1C1                  LGPT1 compare/capture output event 1, controlled
//                          by LGPT1:C1CFG setting
// LGPT1C0                  LGPT1 compare/capture output event 0, controlled
//                          by LGPT1:C0CFG setting
// LGPT0_ADC                LGPT0 ADC trigger event, controlled by
//                          LGPT0:ADCTRG setting
// LGPT0_DMA                LGPT0 DMA request event, controlled by LGPT0:DMA
//                          setting
// LGPT0C2                  LGPT0 compare/capture output event 2, controlled
//                          by LGPT0:C2CFG setting
// LGPT0C1                  LGPT0 compare/capture output event 1, controlled
//                          by LGPT0:C1CFG setting
// LGPT0C0                  LGPT0 compare/capture output event 0, controlled
//                          by LGPT0:C0CFG setting
// SYSTIM4                  SYSTIM Channel 4 event, event flag is
//                          SYSTIM:MIS.EVT4
// SYSTIM3                  SYSTIM Channel 3 event, event flag is
//                          SYSTIM:MIS.EVT3
// SYSTIM2                  SYSTIM Channel 2 event, event flag is
//                          SYSTIM:MIS.EVT2
// SYSTIM1                  SYSTIM Channel 1 event, event flag is
//                          SYSTIM:MIS.EVT1
// SYSTIM0                  SYSTIM Channel 0 event, event flag is
//                          SYSTIM:MIS.EVT0
// SYSTIM_LT                SYSTIM interrupt driven by synchronizing LFTICK
//                          signal to SVT clock
// SYSTIM_HB                SYSTIM heartbeat, can be set by SYSTIM:TIMEBIT
// I2C0_IRQ                 Interrupt event from I2C0, interrupt flags can be
//                          found here I2C0:MIS
// UART0_COMB               UART0 combined interrupt, interrupt flags are
//                          found here UART0:MIS
// AES_COMB                 AES accelerator combined interrupt request,
//                          interrupt flags can be found here AES:MIS
// DMA_ERR                  DMA bus error, corresponds to DMA:ERROR.STATUS
// DMA_DONE_COMB            DMA combined done interrupt, corresponding flags
//                          can be found here DMA:REQDONE
// LGPT1_COMB               LGPT1 combined interrupt, interrupt flags are
//                          found here LGPT1:MIS
// LGPT0_COMB               LGPT0 combined interrupt, interrupt flags are
//                          found here LGPT0:MIS
// ADC_EVT                  ADC general published event, interrupt flags can
//                          be found here ADC:MIS1
// ADC_COMB                 ADC combined interrupt request, interrupt flags
//                          can be found here ADC:MIS0
// SPI0_COMB                SPI0 combined interrupt request, interrupt flags
//                          can be found here SPI0:MIS
// LRFD_IRQ2                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS2
// LRFD_IRQ1                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS1
// LRFD_IRQ0                LRFD combined event, interrupt flags can be found
//                          here LRFDDBELL:MIS0
// FLASH_IRQ                NoWrapper Flash interrupt indicating that the
//                          flash operation has completed, interrupt flags
//                          can be found here FLASH:MIS
// GPIO_EVT                 GPIO generic published event, controlled by
//                          GPIO:EVTCFG
// GPIO_COMB                GPIO combined wake up interrupt, interrupt flags
//                          can be found here GPIO:MIS
// SYSTIM_COMB              SYSTIM combined interrupt, interrupt flags are
//                          found here SYSTIM:MIS
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
#define EVTSVT_DMACH7SEL_PUBID_W                                             6U
#define EVTSVT_DMACH7SEL_PUBID_M                                    0x0000003FU
#define EVTSVT_DMACH7SEL_PUBID_S                                             0U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3_ADC                            0x00000039U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3_DMA                            0x00000038U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3_COMB                           0x00000037U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3C2                              0x00000036U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3C1                              0x00000035U
#define EVTSVT_DMACH7SEL_PUBID_LGPT3C0                              0x00000034U
#define EVTSVT_DMACH7SEL_PUBID_LGPT2_ADC                            0x00000033U
#define EVTSVT_DMACH7SEL_PUBID_LGPT2_DMA                            0x00000032U
#define EVTSVT_DMACH7SEL_PUBID_LGPT2_COMB                           0x00000031U
#define EVTSVT_DMACH7SEL_PUBID_LGPT2C2                              0x00000030U
#define EVTSVT_DMACH7SEL_PUBID_LGPT2C1                              0x0000002FU
#define EVTSVT_DMACH7SEL_PUBID_LGPT2C0                              0x0000002EU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_EVT2                            0x0000002CU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_EVT1                            0x0000002BU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_EVT0                            0x0000002AU
#define EVTSVT_DMACH7SEL_PUBID_LGPT1_ADC                            0x00000029U
#define EVTSVT_DMACH7SEL_PUBID_LGPT1_DMA                            0x00000028U
#define EVTSVT_DMACH7SEL_PUBID_LGPT1C2                              0x00000027U
#define EVTSVT_DMACH7SEL_PUBID_LGPT1C1                              0x00000026U
#define EVTSVT_DMACH7SEL_PUBID_LGPT1C0                              0x00000025U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0_ADC                            0x00000024U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0_DMA                            0x00000023U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0C2                              0x00000022U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0C1                              0x00000021U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0C0                              0x00000020U
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM4                              0x0000001FU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM3                              0x0000001EU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM2                              0x0000001DU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM1                              0x0000001CU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM0                              0x0000001BU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM_LT                            0x0000001AU
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM_HB                            0x00000019U
#define EVTSVT_DMACH7SEL_PUBID_I2C0_IRQ                             0x00000018U
#define EVTSVT_DMACH7SEL_PUBID_UART0_COMB                           0x00000017U
#define EVTSVT_DMACH7SEL_PUBID_AES_COMB                             0x00000016U
#define EVTSVT_DMACH7SEL_PUBID_DMA_ERR                              0x00000015U
#define EVTSVT_DMACH7SEL_PUBID_DMA_DONE_COMB                        0x00000014U
#define EVTSVT_DMACH7SEL_PUBID_LGPT1_COMB                           0x00000013U
#define EVTSVT_DMACH7SEL_PUBID_LGPT0_COMB                           0x00000012U
#define EVTSVT_DMACH7SEL_PUBID_ADC_EVT                              0x00000011U
#define EVTSVT_DMACH7SEL_PUBID_ADC_COMB                             0x00000010U
#define EVTSVT_DMACH7SEL_PUBID_SPI0_COMB                            0x0000000FU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_IRQ2                            0x0000000EU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_IRQ1                            0x0000000DU
#define EVTSVT_DMACH7SEL_PUBID_LRFD_IRQ0                            0x0000000CU
#define EVTSVT_DMACH7SEL_PUBID_FLASH_IRQ                            0x0000000BU
#define EVTSVT_DMACH7SEL_PUBID_GPIO_EVT                             0x0000000AU
#define EVTSVT_DMACH7SEL_PUBID_GPIO_COMB                            0x00000009U
#define EVTSVT_DMACH7SEL_PUBID_SYSTIM_COMB                          0x00000008U
#define EVTSVT_DMACH7SEL_PUBID_AON_IOC_COMB                         0x00000007U
#define EVTSVT_DMACH7SEL_PUBID_AON_LPMCMP_IRQ                       0x00000006U
#define EVTSVT_DMACH7SEL_PUBID_AON_DBG_COMB                         0x00000005U
#define EVTSVT_DMACH7SEL_PUBID_AON_RTC_COMB                         0x00000004U
#define EVTSVT_DMACH7SEL_PUBID_AON_CKM_COMB                         0x00000003U
#define EVTSVT_DMACH7SEL_PUBID_AON_PMU_COMB                         0x00000002U
#define EVTSVT_DMACH7SEL_PUBID_NONE                                 0x00000000U


#endif // __EVTSVT__
