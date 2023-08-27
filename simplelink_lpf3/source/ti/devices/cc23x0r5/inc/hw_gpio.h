/******************************************************************************
*  Filename:       hw_gpio_h
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

#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

//*****************************************************************************
//
// This section defines the register offsets of
// GPIO component
//
//*****************************************************************************
// Module Description
#define GPIO_O_DESC                                                 0x00000000U

// Module Description Extended
#define GPIO_O_DESCEX                                               0x00000004U

// Interrupt Mask
#define GPIO_O_IMASK                                                0x00000044U

// Raw interrupt status
#define GPIO_O_RIS                                                  0x0000004CU

// Masked interrupt status
#define GPIO_O_MIS                                                  0x00000054U

// Interrupt set
#define GPIO_O_ISET                                                 0x0000005CU

// Interrupt clear
#define GPIO_O_ICLR                                                 0x00000064U

// Interrupt mask set
#define GPIO_O_IMSET                                                0x0000006CU

// Interrupt mask clear
#define GPIO_O_IMCLR                                                0x00000074U

// Alias for Data out 3 to 0
#define GPIO_O_DOUT3_0                                              0x00000100U

// Alias for Data out 7 to 4
#define GPIO_O_DOUT7_4                                              0x00000104U

// Alias for Data out 11 to 8
#define GPIO_O_DOUT11_8                                             0x00000108U

// Alias for Data out 15 to 12
#define GPIO_O_DOUT15_12                                            0x0000010CU

// Alias for Data out 19 to 16
#define GPIO_O_DOUT19_16                                            0x00000110U

// Alias for Data out 23 to 20
#define GPIO_O_DOUT23_20                                            0x00000114U

// Alias for Data out 27 to 24
#define GPIO_O_DOUT27_24                                            0x00000118U

// Data out 31 to 0
#define GPIO_O_DOUT31_0                                             0x00000200U

// Data out set 31 to 0
#define GPIO_O_DOUTSET31_0                                          0x00000210U

// Data out clear 31 to 0
#define GPIO_O_DOUTCLR31_0                                          0x00000220U

// Data out toggle 31 to 0
#define GPIO_O_DOUTTGL31_0                                          0x00000230U

// Alias for Data out toggle 3 to 0
#define GPIO_O_DOUTTGL3_0                                           0x00000300U

// Alias for Data out toggle 7 to 4
#define GPIO_O_DOUTTGL7_4                                           0x00000304U

// Alias for Data out toggle 11 to 8
#define GPIO_O_DOUTTGL11_8                                          0x00000308U

// Alias for Data out toggle 15 to 12
#define GPIO_O_DOUTTGL15_12                                         0x0000030CU

// Alias for Data out toggle 19 to 16
#define GPIO_O_DOUTTGL19_16                                         0x00000310U

// Alias for Data out toggle 23 to 20
#define GPIO_O_DOUTTGL23_20                                         0x00000314U

// Alias for Data out toggle 27 to 24
#define GPIO_O_DOUTTGL27_24                                         0x00000318U

// Alias for Data out enable 3 to 0
#define GPIO_O_DOE3_0                                               0x00000400U

// Alias for Data out enable 7 to 4
#define GPIO_O_DOE7_4                                               0x00000404U

// Alias for Data out enable 11 to 8
#define GPIO_O_DOE11_8                                              0x00000408U

// Alias for Data out enable 15 to 12
#define GPIO_O_DOE15_12                                             0x0000040CU

// Alias for Data out enable 19 to 16
#define GPIO_O_DOE19_16                                             0x00000410U

// Alias for Data out enable 23 to 20
#define GPIO_O_DOE23_20                                             0x00000414U

// Alias for Data out enable 27 to 24
#define GPIO_O_DOE27_24                                             0x00000418U

// Data out enable 31 to 0
#define GPIO_O_DOE31_0                                              0x00000500U

// Data out enable set 31 to 0
#define GPIO_O_DOESET31_0                                           0x00000510U

// Data out enable clear 31 to 0
#define GPIO_O_DOECLR31_0                                           0x00000520U

// Data out enable toggle 31 to 0
#define GPIO_O_DOETGL31_0                                           0x00000530U

// Alias for Data input 3 to 0
#define GPIO_O_DIN3_0                                               0x00000600U

// Alias for Data input 7 to 4
#define GPIO_O_DIN7_4                                               0x00000604U

// Alias for Data input 11 to 8
#define GPIO_O_DIN11_8                                              0x00000608U

// Alias for Data input 15 to 12
#define GPIO_O_DIN15_12                                             0x0000060CU

// Alias for Data input 19 to 16
#define GPIO_O_DIN19_16                                             0x00000610U

// Alias for Data input 23 to 20
#define GPIO_O_DIN23_20                                             0x00000614U

// Alias for Data input 27 to 24
#define GPIO_O_DIN27_24                                             0x00000618U

// Data input 31 to 0
#define GPIO_O_DIN31_0                                              0x00000700U

// Event configuration
#define GPIO_O_EVTCFG                                               0x00000800U

//*****************************************************************************
//
// Register: GPIO_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define GPIO_DESC_MODID_W                                                   16U
#define GPIO_DESC_MODID_M                                           0xFFFF0000U
#define GPIO_DESC_MODID_S                                                   16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set from aggregated
// IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
//
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define GPIO_DESC_STDIPOFF_W                                                 4U
#define GPIO_DESC_STDIPOFF_M                                        0x0000F000U
#define GPIO_DESC_STDIPOFF_S                                                12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define GPIO_DESC_INSTIDX_W                                                  4U
#define GPIO_DESC_INSTIDX_M                                         0x00000F00U
#define GPIO_DESC_INSTIDX_S                                                  8U

// Field:   [7:4] MAJREV
//
// Major revision of IP (0-15).
#define GPIO_DESC_MAJREV_W                                                   4U
#define GPIO_DESC_MAJREV_M                                          0x000000F0U
#define GPIO_DESC_MAJREV_S                                                   4U

// Field:   [3:0] MINREV
//
// Minor revision of IP (0-15).
#define GPIO_DESC_MINREV_W                                                   4U
#define GPIO_DESC_MINREV_M                                          0x0000000FU
#define GPIO_DESC_MINREV_S                                                   0U

//*****************************************************************************
//
// Register: GPIO_O_DESCEX
//
//*****************************************************************************
// Field:   [5:0] NUMDIO
//
// This provides the total number of DIOs supported by GPIO. The number of DIOs
// supprted is NUMDIO + 1
#define GPIO_DESCEX_NUMDIO_W                                                 6U
#define GPIO_DESCEX_NUMDIO_M                                        0x0000003FU
#define GPIO_DESCEX_NUMDIO_S                                                 0U

//*****************************************************************************
//
// Register: GPIO_O_IMASK
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Interrupt mask for DIO25
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO25                                            0x02000000U
#define GPIO_IMASK_DIO25_M                                          0x02000000U
#define GPIO_IMASK_DIO25_S                                                  25U
#define GPIO_IMASK_DIO25_SET                                        0x02000000U
#define GPIO_IMASK_DIO25_CLR                                        0x00000000U

// Field:    [24] DIO24
//
// Interrupt mask for DIO24
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO24                                            0x01000000U
#define GPIO_IMASK_DIO24_M                                          0x01000000U
#define GPIO_IMASK_DIO24_S                                                  24U
#define GPIO_IMASK_DIO24_SET                                        0x01000000U
#define GPIO_IMASK_DIO24_CLR                                        0x00000000U

// Field:    [23] DIO23
//
// Interrupt mask for DIO23
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO23                                            0x00800000U
#define GPIO_IMASK_DIO23_M                                          0x00800000U
#define GPIO_IMASK_DIO23_S                                                  23U
#define GPIO_IMASK_DIO23_SET                                        0x00800000U
#define GPIO_IMASK_DIO23_CLR                                        0x00000000U

// Field:    [22] DIO22
//
// Interrupt mask for DIO22
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO22                                            0x00400000U
#define GPIO_IMASK_DIO22_M                                          0x00400000U
#define GPIO_IMASK_DIO22_S                                                  22U
#define GPIO_IMASK_DIO22_SET                                        0x00400000U
#define GPIO_IMASK_DIO22_CLR                                        0x00000000U

// Field:    [21] DIO21
//
// Interrupt mask for DIO21
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO21                                            0x00200000U
#define GPIO_IMASK_DIO21_M                                          0x00200000U
#define GPIO_IMASK_DIO21_S                                                  21U
#define GPIO_IMASK_DIO21_SET                                        0x00200000U
#define GPIO_IMASK_DIO21_CLR                                        0x00000000U

// Field:    [20] DIO20
//
// Interrupt mask for DIO20
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO20                                            0x00100000U
#define GPIO_IMASK_DIO20_M                                          0x00100000U
#define GPIO_IMASK_DIO20_S                                                  20U
#define GPIO_IMASK_DIO20_SET                                        0x00100000U
#define GPIO_IMASK_DIO20_CLR                                        0x00000000U

// Field:    [19] DIO19
//
// Interrupt mask for DIO19
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO19                                            0x00080000U
#define GPIO_IMASK_DIO19_M                                          0x00080000U
#define GPIO_IMASK_DIO19_S                                                  19U
#define GPIO_IMASK_DIO19_SET                                        0x00080000U
#define GPIO_IMASK_DIO19_CLR                                        0x00000000U

// Field:    [18] DIO18
//
// Interrupt mask for DIO18
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO18                                            0x00040000U
#define GPIO_IMASK_DIO18_M                                          0x00040000U
#define GPIO_IMASK_DIO18_S                                                  18U
#define GPIO_IMASK_DIO18_SET                                        0x00040000U
#define GPIO_IMASK_DIO18_CLR                                        0x00000000U

// Field:    [17] DIO17
//
// Interrupt mask for DIO17
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO17                                            0x00020000U
#define GPIO_IMASK_DIO17_M                                          0x00020000U
#define GPIO_IMASK_DIO17_S                                                  17U
#define GPIO_IMASK_DIO17_SET                                        0x00020000U
#define GPIO_IMASK_DIO17_CLR                                        0x00000000U

// Field:    [16] DIO16
//
// Interrupt mask for DIO16
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO16                                            0x00010000U
#define GPIO_IMASK_DIO16_M                                          0x00010000U
#define GPIO_IMASK_DIO16_S                                                  16U
#define GPIO_IMASK_DIO16_SET                                        0x00010000U
#define GPIO_IMASK_DIO16_CLR                                        0x00000000U

// Field:    [15] DIO15
//
// Interrupt mask for DIO15
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO15                                            0x00008000U
#define GPIO_IMASK_DIO15_M                                          0x00008000U
#define GPIO_IMASK_DIO15_S                                                  15U
#define GPIO_IMASK_DIO15_SET                                        0x00008000U
#define GPIO_IMASK_DIO15_CLR                                        0x00000000U

// Field:    [14] DIO14
//
// Interrupt mask for DIO14
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO14                                            0x00004000U
#define GPIO_IMASK_DIO14_M                                          0x00004000U
#define GPIO_IMASK_DIO14_S                                                  14U
#define GPIO_IMASK_DIO14_SET                                        0x00004000U
#define GPIO_IMASK_DIO14_CLR                                        0x00000000U

// Field:    [13] DIO13
//
// Interrupt mask for DIO13
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO13                                            0x00002000U
#define GPIO_IMASK_DIO13_M                                          0x00002000U
#define GPIO_IMASK_DIO13_S                                                  13U
#define GPIO_IMASK_DIO13_SET                                        0x00002000U
#define GPIO_IMASK_DIO13_CLR                                        0x00000000U

// Field:    [12] DIO12
//
// Interrupt mask for DIO12
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO12                                            0x00001000U
#define GPIO_IMASK_DIO12_M                                          0x00001000U
#define GPIO_IMASK_DIO12_S                                                  12U
#define GPIO_IMASK_DIO12_SET                                        0x00001000U
#define GPIO_IMASK_DIO12_CLR                                        0x00000000U

// Field:    [11] DIO11
//
// Interrupt mask for DIO11
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO11                                            0x00000800U
#define GPIO_IMASK_DIO11_M                                          0x00000800U
#define GPIO_IMASK_DIO11_S                                                  11U
#define GPIO_IMASK_DIO11_SET                                        0x00000800U
#define GPIO_IMASK_DIO11_CLR                                        0x00000000U

// Field:    [10] DIO10
//
// Interrupt mask for DIO10
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO10                                            0x00000400U
#define GPIO_IMASK_DIO10_M                                          0x00000400U
#define GPIO_IMASK_DIO10_S                                                  10U
#define GPIO_IMASK_DIO10_SET                                        0x00000400U
#define GPIO_IMASK_DIO10_CLR                                        0x00000000U

// Field:     [9] DIO9
//
// Interrupt mask for DIO9
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO9                                             0x00000200U
#define GPIO_IMASK_DIO9_M                                           0x00000200U
#define GPIO_IMASK_DIO9_S                                                    9U
#define GPIO_IMASK_DIO9_SET                                         0x00000200U
#define GPIO_IMASK_DIO9_CLR                                         0x00000000U

// Field:     [8] DIO8
//
// Interrupt mask for DIO8
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO8                                             0x00000100U
#define GPIO_IMASK_DIO8_M                                           0x00000100U
#define GPIO_IMASK_DIO8_S                                                    8U
#define GPIO_IMASK_DIO8_SET                                         0x00000100U
#define GPIO_IMASK_DIO8_CLR                                         0x00000000U

// Field:     [7] DIO7
//
// Interrupt mask for DIO7
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO7                                             0x00000080U
#define GPIO_IMASK_DIO7_M                                           0x00000080U
#define GPIO_IMASK_DIO7_S                                                    7U
#define GPIO_IMASK_DIO7_SET                                         0x00000080U
#define GPIO_IMASK_DIO7_CLR                                         0x00000000U

// Field:     [6] DIO6
//
// Interrupt mask for DIO6
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO6                                             0x00000040U
#define GPIO_IMASK_DIO6_M                                           0x00000040U
#define GPIO_IMASK_DIO6_S                                                    6U
#define GPIO_IMASK_DIO6_SET                                         0x00000040U
#define GPIO_IMASK_DIO6_CLR                                         0x00000000U

// Field:     [5] DIO5
//
// Interrupt mask for DIO5
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO5                                             0x00000020U
#define GPIO_IMASK_DIO5_M                                           0x00000020U
#define GPIO_IMASK_DIO5_S                                                    5U
#define GPIO_IMASK_DIO5_SET                                         0x00000020U
#define GPIO_IMASK_DIO5_CLR                                         0x00000000U

// Field:     [4] DIO4
//
// Interrupt mask for DIO4
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO4                                             0x00000010U
#define GPIO_IMASK_DIO4_M                                           0x00000010U
#define GPIO_IMASK_DIO4_S                                                    4U
#define GPIO_IMASK_DIO4_SET                                         0x00000010U
#define GPIO_IMASK_DIO4_CLR                                         0x00000000U

// Field:     [3] DIO3
//
// Interrupt mask for DIO3
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO3                                             0x00000008U
#define GPIO_IMASK_DIO3_M                                           0x00000008U
#define GPIO_IMASK_DIO3_S                                                    3U
#define GPIO_IMASK_DIO3_SET                                         0x00000008U
#define GPIO_IMASK_DIO3_CLR                                         0x00000000U

// Field:     [2] DIO2
//
// Interrupt mask for DIO2
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO2                                             0x00000004U
#define GPIO_IMASK_DIO2_M                                           0x00000004U
#define GPIO_IMASK_DIO2_S                                                    2U
#define GPIO_IMASK_DIO2_SET                                         0x00000004U
#define GPIO_IMASK_DIO2_CLR                                         0x00000000U

// Field:     [1] DIO1
//
// Interrupt mask for DIO1
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO1                                             0x00000002U
#define GPIO_IMASK_DIO1_M                                           0x00000002U
#define GPIO_IMASK_DIO1_S                                                    1U
#define GPIO_IMASK_DIO1_SET                                         0x00000002U
#define GPIO_IMASK_DIO1_CLR                                         0x00000000U

// Field:     [0] DIO0
//
// Interrupt mask for DIO0
// ENUMs:
// SET                      Set Interrrupt Mask
// CLR                      Clear Interrupt Mask
#define GPIO_IMASK_DIO0                                             0x00000001U
#define GPIO_IMASK_DIO0_M                                           0x00000001U
#define GPIO_IMASK_DIO0_S                                                    0U
#define GPIO_IMASK_DIO0_SET                                         0x00000001U
#define GPIO_IMASK_DIO0_CLR                                         0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_RIS
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Raw interrupt flag for DIO25
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO25                                              0x02000000U
#define GPIO_RIS_DIO25_M                                            0x02000000U
#define GPIO_RIS_DIO25_S                                                    25U
#define GPIO_RIS_DIO25_SET                                          0x02000000U
#define GPIO_RIS_DIO25_CLR                                          0x00000000U

// Field:    [24] DIO24
//
// Raw interrupt flag for DIO24
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO24                                              0x01000000U
#define GPIO_RIS_DIO24_M                                            0x01000000U
#define GPIO_RIS_DIO24_S                                                    24U
#define GPIO_RIS_DIO24_SET                                          0x01000000U
#define GPIO_RIS_DIO24_CLR                                          0x00000000U

// Field:    [23] DIO23
//
// Raw interrupt flag for DIO23
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO23                                              0x00800000U
#define GPIO_RIS_DIO23_M                                            0x00800000U
#define GPIO_RIS_DIO23_S                                                    23U
#define GPIO_RIS_DIO23_SET                                          0x00800000U
#define GPIO_RIS_DIO23_CLR                                          0x00000000U

// Field:    [22] DIO22
//
// Raw interrupt flag for DIO22
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO22                                              0x00400000U
#define GPIO_RIS_DIO22_M                                            0x00400000U
#define GPIO_RIS_DIO22_S                                                    22U
#define GPIO_RIS_DIO22_SET                                          0x00400000U
#define GPIO_RIS_DIO22_CLR                                          0x00000000U

// Field:    [21] DIO21
//
// Raw interrupt flag for DIO21
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO21                                              0x00200000U
#define GPIO_RIS_DIO21_M                                            0x00200000U
#define GPIO_RIS_DIO21_S                                                    21U
#define GPIO_RIS_DIO21_SET                                          0x00200000U
#define GPIO_RIS_DIO21_CLR                                          0x00000000U

// Field:    [20] DIO20
//
// Raw interrupt flag for DIO20
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO20                                              0x00100000U
#define GPIO_RIS_DIO20_M                                            0x00100000U
#define GPIO_RIS_DIO20_S                                                    20U
#define GPIO_RIS_DIO20_SET                                          0x00100000U
#define GPIO_RIS_DIO20_CLR                                          0x00000000U

// Field:    [19] DIO19
//
// Raw interrupt flag for DIO19
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO19                                              0x00080000U
#define GPIO_RIS_DIO19_M                                            0x00080000U
#define GPIO_RIS_DIO19_S                                                    19U
#define GPIO_RIS_DIO19_SET                                          0x00080000U
#define GPIO_RIS_DIO19_CLR                                          0x00000000U

// Field:    [18] DIO18
//
// Raw interrupt flag for DIO18
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO18                                              0x00040000U
#define GPIO_RIS_DIO18_M                                            0x00040000U
#define GPIO_RIS_DIO18_S                                                    18U
#define GPIO_RIS_DIO18_SET                                          0x00040000U
#define GPIO_RIS_DIO18_CLR                                          0x00000000U

// Field:    [17] DIO17
//
// Raw interrupt flag for DIO17
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO17                                              0x00020000U
#define GPIO_RIS_DIO17_M                                            0x00020000U
#define GPIO_RIS_DIO17_S                                                    17U
#define GPIO_RIS_DIO17_SET                                          0x00020000U
#define GPIO_RIS_DIO17_CLR                                          0x00000000U

// Field:    [16] DIO16
//
// Raw interrupt flag for DIO16
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO16                                              0x00010000U
#define GPIO_RIS_DIO16_M                                            0x00010000U
#define GPIO_RIS_DIO16_S                                                    16U
#define GPIO_RIS_DIO16_SET                                          0x00010000U
#define GPIO_RIS_DIO16_CLR                                          0x00000000U

// Field:    [15] DIO15
//
// Raw interrupt flag for DIO15
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO15                                              0x00008000U
#define GPIO_RIS_DIO15_M                                            0x00008000U
#define GPIO_RIS_DIO15_S                                                    15U
#define GPIO_RIS_DIO15_SET                                          0x00008000U
#define GPIO_RIS_DIO15_CLR                                          0x00000000U

// Field:    [14] DIO14
//
// Raw interrupt flag for DIO14
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO14                                              0x00004000U
#define GPIO_RIS_DIO14_M                                            0x00004000U
#define GPIO_RIS_DIO14_S                                                    14U
#define GPIO_RIS_DIO14_SET                                          0x00004000U
#define GPIO_RIS_DIO14_CLR                                          0x00000000U

// Field:    [13] DIO13
//
// Raw interrupt flag for DIO13
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO13                                              0x00002000U
#define GPIO_RIS_DIO13_M                                            0x00002000U
#define GPIO_RIS_DIO13_S                                                    13U
#define GPIO_RIS_DIO13_SET                                          0x00002000U
#define GPIO_RIS_DIO13_CLR                                          0x00000000U

// Field:    [12] DIO12
//
// Raw interrupt flag for DIO12
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO12                                              0x00001000U
#define GPIO_RIS_DIO12_M                                            0x00001000U
#define GPIO_RIS_DIO12_S                                                    12U
#define GPIO_RIS_DIO12_SET                                          0x00001000U
#define GPIO_RIS_DIO12_CLR                                          0x00000000U

// Field:    [11] DIO11
//
// Raw interrupt flag for DIO11
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO11                                              0x00000800U
#define GPIO_RIS_DIO11_M                                            0x00000800U
#define GPIO_RIS_DIO11_S                                                    11U
#define GPIO_RIS_DIO11_SET                                          0x00000800U
#define GPIO_RIS_DIO11_CLR                                          0x00000000U

// Field:    [10] DIO10
//
// Raw interrupt flag for DIO10
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO10                                              0x00000400U
#define GPIO_RIS_DIO10_M                                            0x00000400U
#define GPIO_RIS_DIO10_S                                                    10U
#define GPIO_RIS_DIO10_SET                                          0x00000400U
#define GPIO_RIS_DIO10_CLR                                          0x00000000U

// Field:     [9] DIO9
//
// Raw interrupt flag for DIO9
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO9                                               0x00000200U
#define GPIO_RIS_DIO9_M                                             0x00000200U
#define GPIO_RIS_DIO9_S                                                      9U
#define GPIO_RIS_DIO9_SET                                           0x00000200U
#define GPIO_RIS_DIO9_CLR                                           0x00000000U

// Field:     [8] DIO8
//
// Raw interrupt flag for DIO8
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO8                                               0x00000100U
#define GPIO_RIS_DIO8_M                                             0x00000100U
#define GPIO_RIS_DIO8_S                                                      8U
#define GPIO_RIS_DIO8_SET                                           0x00000100U
#define GPIO_RIS_DIO8_CLR                                           0x00000000U

// Field:     [7] DIO7
//
// Raw interrupt flag for DIO7
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO7                                               0x00000080U
#define GPIO_RIS_DIO7_M                                             0x00000080U
#define GPIO_RIS_DIO7_S                                                      7U
#define GPIO_RIS_DIO7_SET                                           0x00000080U
#define GPIO_RIS_DIO7_CLR                                           0x00000000U

// Field:     [6] DIO6
//
// Raw interrupt flag for DIO6
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO6                                               0x00000040U
#define GPIO_RIS_DIO6_M                                             0x00000040U
#define GPIO_RIS_DIO6_S                                                      6U
#define GPIO_RIS_DIO6_SET                                           0x00000040U
#define GPIO_RIS_DIO6_CLR                                           0x00000000U

// Field:     [5] DIO5
//
// Raw interrupt flag for DIO5
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO5                                               0x00000020U
#define GPIO_RIS_DIO5_M                                             0x00000020U
#define GPIO_RIS_DIO5_S                                                      5U
#define GPIO_RIS_DIO5_SET                                           0x00000020U
#define GPIO_RIS_DIO5_CLR                                           0x00000000U

// Field:     [4] DIO4
//
// Raw interrupt flag for DIO4
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO4                                               0x00000010U
#define GPIO_RIS_DIO4_M                                             0x00000010U
#define GPIO_RIS_DIO4_S                                                      4U
#define GPIO_RIS_DIO4_SET                                           0x00000010U
#define GPIO_RIS_DIO4_CLR                                           0x00000000U

// Field:     [3] DIO3
//
// Raw interrupt flag for DIO3
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO3                                               0x00000008U
#define GPIO_RIS_DIO3_M                                             0x00000008U
#define GPIO_RIS_DIO3_S                                                      3U
#define GPIO_RIS_DIO3_SET                                           0x00000008U
#define GPIO_RIS_DIO3_CLR                                           0x00000000U

// Field:     [2] DIO2
//
// Raw interrupt flag for DIO2
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO2                                               0x00000004U
#define GPIO_RIS_DIO2_M                                             0x00000004U
#define GPIO_RIS_DIO2_S                                                      2U
#define GPIO_RIS_DIO2_SET                                           0x00000004U
#define GPIO_RIS_DIO2_CLR                                           0x00000000U

// Field:     [1] DIO1
//
// Raw interrupt flag for DIO1
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO1                                               0x00000002U
#define GPIO_RIS_DIO1_M                                             0x00000002U
#define GPIO_RIS_DIO1_S                                                      1U
#define GPIO_RIS_DIO1_SET                                           0x00000002U
#define GPIO_RIS_DIO1_CLR                                           0x00000000U

// Field:     [0] DIO0
//
// Raw interrupt flag for DIO0
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_RIS_DIO0                                               0x00000001U
#define GPIO_RIS_DIO0_M                                             0x00000001U
#define GPIO_RIS_DIO0_S                                                      0U
#define GPIO_RIS_DIO0_SET                                           0x00000001U
#define GPIO_RIS_DIO0_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_MIS
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Masked interrupt flag for DIO25
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO25                                              0x02000000U
#define GPIO_MIS_DIO25_M                                            0x02000000U
#define GPIO_MIS_DIO25_S                                                    25U
#define GPIO_MIS_DIO25_SET                                          0x02000000U
#define GPIO_MIS_DIO25_CLR                                          0x00000000U

// Field:    [24] DIO24
//
// Masked interrupt flag for DIO24
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO24                                              0x01000000U
#define GPIO_MIS_DIO24_M                                            0x01000000U
#define GPIO_MIS_DIO24_S                                                    24U
#define GPIO_MIS_DIO24_SET                                          0x01000000U
#define GPIO_MIS_DIO24_CLR                                          0x00000000U

// Field:    [23] DIO23
//
// Masked interrupt flag for DIO23
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO23                                              0x00800000U
#define GPIO_MIS_DIO23_M                                            0x00800000U
#define GPIO_MIS_DIO23_S                                                    23U
#define GPIO_MIS_DIO23_SET                                          0x00800000U
#define GPIO_MIS_DIO23_CLR                                          0x00000000U

// Field:    [22] DIO22
//
// Masked interrupt flag for DIO22
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO22                                              0x00400000U
#define GPIO_MIS_DIO22_M                                            0x00400000U
#define GPIO_MIS_DIO22_S                                                    22U
#define GPIO_MIS_DIO22_SET                                          0x00400000U
#define GPIO_MIS_DIO22_CLR                                          0x00000000U

// Field:    [21] DIO21
//
// Masked interrupt flag for DIO21
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO21                                              0x00200000U
#define GPIO_MIS_DIO21_M                                            0x00200000U
#define GPIO_MIS_DIO21_S                                                    21U
#define GPIO_MIS_DIO21_SET                                          0x00200000U
#define GPIO_MIS_DIO21_CLR                                          0x00000000U

// Field:    [20] DIO20
//
// Masked interrupt flag for DIO20
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO20                                              0x00100000U
#define GPIO_MIS_DIO20_M                                            0x00100000U
#define GPIO_MIS_DIO20_S                                                    20U
#define GPIO_MIS_DIO20_SET                                          0x00100000U
#define GPIO_MIS_DIO20_CLR                                          0x00000000U

// Field:    [19] DIO19
//
// Masked interrupt flag for DIO19
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO19                                              0x00080000U
#define GPIO_MIS_DIO19_M                                            0x00080000U
#define GPIO_MIS_DIO19_S                                                    19U
#define GPIO_MIS_DIO19_SET                                          0x00080000U
#define GPIO_MIS_DIO19_CLR                                          0x00000000U

// Field:    [18] DIO18
//
// Masked interrupt flag for DIO18
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO18                                              0x00040000U
#define GPIO_MIS_DIO18_M                                            0x00040000U
#define GPIO_MIS_DIO18_S                                                    18U
#define GPIO_MIS_DIO18_SET                                          0x00040000U
#define GPIO_MIS_DIO18_CLR                                          0x00000000U

// Field:    [17] DIO17
//
// Masked interrupt flag for DIO17
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO17                                              0x00020000U
#define GPIO_MIS_DIO17_M                                            0x00020000U
#define GPIO_MIS_DIO17_S                                                    17U
#define GPIO_MIS_DIO17_SET                                          0x00020000U
#define GPIO_MIS_DIO17_CLR                                          0x00000000U

// Field:    [16] DIO16
//
// Masked interrupt flag for DIO16
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO16                                              0x00010000U
#define GPIO_MIS_DIO16_M                                            0x00010000U
#define GPIO_MIS_DIO16_S                                                    16U
#define GPIO_MIS_DIO16_SET                                          0x00010000U
#define GPIO_MIS_DIO16_CLR                                          0x00000000U

// Field:    [15] DIO15
//
// Masked interrupt flag for DIO15
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO15                                              0x00008000U
#define GPIO_MIS_DIO15_M                                            0x00008000U
#define GPIO_MIS_DIO15_S                                                    15U
#define GPIO_MIS_DIO15_SET                                          0x00008000U
#define GPIO_MIS_DIO15_CLR                                          0x00000000U

// Field:    [14] DIO14
//
// Masked interrupt flag for DIO14
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO14                                              0x00004000U
#define GPIO_MIS_DIO14_M                                            0x00004000U
#define GPIO_MIS_DIO14_S                                                    14U
#define GPIO_MIS_DIO14_SET                                          0x00004000U
#define GPIO_MIS_DIO14_CLR                                          0x00000000U

// Field:    [13] DIO13
//
// Masked interrupt flag for DIO13
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO13                                              0x00002000U
#define GPIO_MIS_DIO13_M                                            0x00002000U
#define GPIO_MIS_DIO13_S                                                    13U
#define GPIO_MIS_DIO13_SET                                          0x00002000U
#define GPIO_MIS_DIO13_CLR                                          0x00000000U

// Field:    [12] DIO12
//
// Masked interrupt flag for DIO12
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO12                                              0x00001000U
#define GPIO_MIS_DIO12_M                                            0x00001000U
#define GPIO_MIS_DIO12_S                                                    12U
#define GPIO_MIS_DIO12_SET                                          0x00001000U
#define GPIO_MIS_DIO12_CLR                                          0x00000000U

// Field:    [11] DIO11
//
// Masked interrupt flag for DIO11
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO11                                              0x00000800U
#define GPIO_MIS_DIO11_M                                            0x00000800U
#define GPIO_MIS_DIO11_S                                                    11U
#define GPIO_MIS_DIO11_SET                                          0x00000800U
#define GPIO_MIS_DIO11_CLR                                          0x00000000U

// Field:    [10] DIO10
//
// Masked interrupt flag for DIO10
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO10                                              0x00000400U
#define GPIO_MIS_DIO10_M                                            0x00000400U
#define GPIO_MIS_DIO10_S                                                    10U
#define GPIO_MIS_DIO10_SET                                          0x00000400U
#define GPIO_MIS_DIO10_CLR                                          0x00000000U

// Field:     [9] DIO9
//
// Masked interrupt flag for DIO9
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO9                                               0x00000200U
#define GPIO_MIS_DIO9_M                                             0x00000200U
#define GPIO_MIS_DIO9_S                                                      9U
#define GPIO_MIS_DIO9_SET                                           0x00000200U
#define GPIO_MIS_DIO9_CLR                                           0x00000000U

// Field:     [8] DIO8
//
// Masked interrupt flag for DIO8
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO8                                               0x00000100U
#define GPIO_MIS_DIO8_M                                             0x00000100U
#define GPIO_MIS_DIO8_S                                                      8U
#define GPIO_MIS_DIO8_SET                                           0x00000100U
#define GPIO_MIS_DIO8_CLR                                           0x00000000U

// Field:     [7] DIO7
//
// Masked interrupt flag for DIO7
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO7                                               0x00000080U
#define GPIO_MIS_DIO7_M                                             0x00000080U
#define GPIO_MIS_DIO7_S                                                      7U
#define GPIO_MIS_DIO7_SET                                           0x00000080U
#define GPIO_MIS_DIO7_CLR                                           0x00000000U

// Field:     [6] DIO6
//
// Masked interrupt flag for DIO6
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO6                                               0x00000040U
#define GPIO_MIS_DIO6_M                                             0x00000040U
#define GPIO_MIS_DIO6_S                                                      6U
#define GPIO_MIS_DIO6_SET                                           0x00000040U
#define GPIO_MIS_DIO6_CLR                                           0x00000000U

// Field:     [5] DIO5
//
// Masked interrupt flag for DIO5
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO5                                               0x00000020U
#define GPIO_MIS_DIO5_M                                             0x00000020U
#define GPIO_MIS_DIO5_S                                                      5U
#define GPIO_MIS_DIO5_SET                                           0x00000020U
#define GPIO_MIS_DIO5_CLR                                           0x00000000U

// Field:     [4] DIO4
//
// Masked interrupt flag for DIO4
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO4                                               0x00000010U
#define GPIO_MIS_DIO4_M                                             0x00000010U
#define GPIO_MIS_DIO4_S                                                      4U
#define GPIO_MIS_DIO4_SET                                           0x00000010U
#define GPIO_MIS_DIO4_CLR                                           0x00000000U

// Field:     [3] DIO3
//
// Masked interrupt flag for DIO3
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO3                                               0x00000008U
#define GPIO_MIS_DIO3_M                                             0x00000008U
#define GPIO_MIS_DIO3_S                                                      3U
#define GPIO_MIS_DIO3_SET                                           0x00000008U
#define GPIO_MIS_DIO3_CLR                                           0x00000000U

// Field:     [2] DIO2
//
// Masked interrupt flag for DIO2
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO2                                               0x00000004U
#define GPIO_MIS_DIO2_M                                             0x00000004U
#define GPIO_MIS_DIO2_S                                                      2U
#define GPIO_MIS_DIO2_SET                                           0x00000004U
#define GPIO_MIS_DIO2_CLR                                           0x00000000U

// Field:     [1] DIO1
//
// Masked interrupt flag for DIO1
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO1                                               0x00000002U
#define GPIO_MIS_DIO1_M                                             0x00000002U
#define GPIO_MIS_DIO1_S                                                      1U
#define GPIO_MIS_DIO1_SET                                           0x00000002U
#define GPIO_MIS_DIO1_CLR                                           0x00000000U

// Field:     [0] DIO0
//
// Masked interrupt flag for DIO0
// ENUMs:
// SET                      Interrupt occured
// CLR                      Interrupt did not occur
#define GPIO_MIS_DIO0                                               0x00000001U
#define GPIO_MIS_DIO0_M                                             0x00000001U
#define GPIO_MIS_DIO0_S                                                      0U
#define GPIO_MIS_DIO0_SET                                           0x00000001U
#define GPIO_MIS_DIO0_CLR                                           0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_ISET
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Set DIO25 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO25                                             0x02000000U
#define GPIO_ISET_DIO25_M                                           0x02000000U
#define GPIO_ISET_DIO25_S                                                   25U
#define GPIO_ISET_DIO25_SET                                         0x02000000U
#define GPIO_ISET_DIO25_NOEFF                                       0x00000000U

// Field:    [24] DIO24
//
// Set DIO24 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO24                                             0x01000000U
#define GPIO_ISET_DIO24_M                                           0x01000000U
#define GPIO_ISET_DIO24_S                                                   24U
#define GPIO_ISET_DIO24_SET                                         0x01000000U
#define GPIO_ISET_DIO24_NOEFF                                       0x00000000U

// Field:    [23] DIO23
//
// Set DIO23 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO23                                             0x00800000U
#define GPIO_ISET_DIO23_M                                           0x00800000U
#define GPIO_ISET_DIO23_S                                                   23U
#define GPIO_ISET_DIO23_SET                                         0x00800000U
#define GPIO_ISET_DIO23_NOEFF                                       0x00000000U

// Field:    [22] DIO22
//
// Set DIO22 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO22                                             0x00400000U
#define GPIO_ISET_DIO22_M                                           0x00400000U
#define GPIO_ISET_DIO22_S                                                   22U
#define GPIO_ISET_DIO22_SET                                         0x00400000U
#define GPIO_ISET_DIO22_NOEFF                                       0x00000000U

// Field:    [21] DIO21
//
// Set DIO21 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO21                                             0x00200000U
#define GPIO_ISET_DIO21_M                                           0x00200000U
#define GPIO_ISET_DIO21_S                                                   21U
#define GPIO_ISET_DIO21_SET                                         0x00200000U
#define GPIO_ISET_DIO21_NOEFF                                       0x00000000U

// Field:    [20] DIO20
//
// Set DIO20 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO20                                             0x00100000U
#define GPIO_ISET_DIO20_M                                           0x00100000U
#define GPIO_ISET_DIO20_S                                                   20U
#define GPIO_ISET_DIO20_SET                                         0x00100000U
#define GPIO_ISET_DIO20_NOEFF                                       0x00000000U

// Field:    [19] DIO19
//
// Set DIO19 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO19                                             0x00080000U
#define GPIO_ISET_DIO19_M                                           0x00080000U
#define GPIO_ISET_DIO19_S                                                   19U
#define GPIO_ISET_DIO19_SET                                         0x00080000U
#define GPIO_ISET_DIO19_NOEFF                                       0x00000000U

// Field:    [18] DIO18
//
// Set DIO18 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO18                                             0x00040000U
#define GPIO_ISET_DIO18_M                                           0x00040000U
#define GPIO_ISET_DIO18_S                                                   18U
#define GPIO_ISET_DIO18_SET                                         0x00040000U
#define GPIO_ISET_DIO18_NOEFF                                       0x00000000U

// Field:    [17] DIO17
//
// Set DIO17 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO17                                             0x00020000U
#define GPIO_ISET_DIO17_M                                           0x00020000U
#define GPIO_ISET_DIO17_S                                                   17U
#define GPIO_ISET_DIO17_SET                                         0x00020000U
#define GPIO_ISET_DIO17_NOEFF                                       0x00000000U

// Field:    [16] DIO16
//
// Set DIO16 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO16                                             0x00010000U
#define GPIO_ISET_DIO16_M                                           0x00010000U
#define GPIO_ISET_DIO16_S                                                   16U
#define GPIO_ISET_DIO16_SET                                         0x00010000U
#define GPIO_ISET_DIO16_NOEFF                                       0x00000000U

// Field:    [15] DIO15
//
// Set DIO15 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO15                                             0x00008000U
#define GPIO_ISET_DIO15_M                                           0x00008000U
#define GPIO_ISET_DIO15_S                                                   15U
#define GPIO_ISET_DIO15_SET                                         0x00008000U
#define GPIO_ISET_DIO15_NOEFF                                       0x00000000U

// Field:    [14] DIO14
//
// Set DIO14 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO14                                             0x00004000U
#define GPIO_ISET_DIO14_M                                           0x00004000U
#define GPIO_ISET_DIO14_S                                                   14U
#define GPIO_ISET_DIO14_SET                                         0x00004000U
#define GPIO_ISET_DIO14_NOEFF                                       0x00000000U

// Field:    [13] DIO13
//
// Set DIO13 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO13                                             0x00002000U
#define GPIO_ISET_DIO13_M                                           0x00002000U
#define GPIO_ISET_DIO13_S                                                   13U
#define GPIO_ISET_DIO13_SET                                         0x00002000U
#define GPIO_ISET_DIO13_NOEFF                                       0x00000000U

// Field:    [12] DIO12
//
// Set DIO12 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO12                                             0x00001000U
#define GPIO_ISET_DIO12_M                                           0x00001000U
#define GPIO_ISET_DIO12_S                                                   12U
#define GPIO_ISET_DIO12_SET                                         0x00001000U
#define GPIO_ISET_DIO12_NOEFF                                       0x00000000U

// Field:    [11] DIO11
//
// Set DIO11 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO11                                             0x00000800U
#define GPIO_ISET_DIO11_M                                           0x00000800U
#define GPIO_ISET_DIO11_S                                                   11U
#define GPIO_ISET_DIO11_SET                                         0x00000800U
#define GPIO_ISET_DIO11_NOEFF                                       0x00000000U

// Field:    [10] DIO10
//
// Set DIO10 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO10                                             0x00000400U
#define GPIO_ISET_DIO10_M                                           0x00000400U
#define GPIO_ISET_DIO10_S                                                   10U
#define GPIO_ISET_DIO10_SET                                         0x00000400U
#define GPIO_ISET_DIO10_NOEFF                                       0x00000000U

// Field:     [9] DIO9
//
// Set DIO9 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO9                                              0x00000200U
#define GPIO_ISET_DIO9_M                                            0x00000200U
#define GPIO_ISET_DIO9_S                                                     9U
#define GPIO_ISET_DIO9_SET                                          0x00000200U
#define GPIO_ISET_DIO9_NOEFF                                        0x00000000U

// Field:     [8] DIO8
//
// Set DIO8 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO8                                              0x00000100U
#define GPIO_ISET_DIO8_M                                            0x00000100U
#define GPIO_ISET_DIO8_S                                                     8U
#define GPIO_ISET_DIO8_SET                                          0x00000100U
#define GPIO_ISET_DIO8_NOEFF                                        0x00000000U

// Field:     [7] DIO7
//
// Set DIO7 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO7                                              0x00000080U
#define GPIO_ISET_DIO7_M                                            0x00000080U
#define GPIO_ISET_DIO7_S                                                     7U
#define GPIO_ISET_DIO7_SET                                          0x00000080U
#define GPIO_ISET_DIO7_NOEFF                                        0x00000000U

// Field:     [6] DIO6
//
// Set DIO6 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO6                                              0x00000040U
#define GPIO_ISET_DIO6_M                                            0x00000040U
#define GPIO_ISET_DIO6_S                                                     6U
#define GPIO_ISET_DIO6_SET                                          0x00000040U
#define GPIO_ISET_DIO6_NOEFF                                        0x00000000U

// Field:     [5] DIO5
//
// Set DIO5 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO5                                              0x00000020U
#define GPIO_ISET_DIO5_M                                            0x00000020U
#define GPIO_ISET_DIO5_S                                                     5U
#define GPIO_ISET_DIO5_SET                                          0x00000020U
#define GPIO_ISET_DIO5_NOEFF                                        0x00000000U

// Field:     [4] DIO4
//
// Set DIO4 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO4                                              0x00000010U
#define GPIO_ISET_DIO4_M                                            0x00000010U
#define GPIO_ISET_DIO4_S                                                     4U
#define GPIO_ISET_DIO4_SET                                          0x00000010U
#define GPIO_ISET_DIO4_NOEFF                                        0x00000000U

// Field:     [3] DIO3
//
// Set DIO3 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO3                                              0x00000008U
#define GPIO_ISET_DIO3_M                                            0x00000008U
#define GPIO_ISET_DIO3_S                                                     3U
#define GPIO_ISET_DIO3_SET                                          0x00000008U
#define GPIO_ISET_DIO3_NOEFF                                        0x00000000U

// Field:     [2] DIO2
//
// Set DIO2 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO2                                              0x00000004U
#define GPIO_ISET_DIO2_M                                            0x00000004U
#define GPIO_ISET_DIO2_S                                                     2U
#define GPIO_ISET_DIO2_SET                                          0x00000004U
#define GPIO_ISET_DIO2_NOEFF                                        0x00000000U

// Field:     [1] DIO1
//
// Set DIO1 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO1                                              0x00000002U
#define GPIO_ISET_DIO1_M                                            0x00000002U
#define GPIO_ISET_DIO1_S                                                     1U
#define GPIO_ISET_DIO1_SET                                          0x00000002U
#define GPIO_ISET_DIO1_NOEFF                                        0x00000000U

// Field:     [0] DIO0
//
// Set DIO0 in RIS
// ENUMs:
// SET                      Set Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ISET_DIO0                                              0x00000001U
#define GPIO_ISET_DIO0_M                                            0x00000001U
#define GPIO_ISET_DIO0_S                                                     0U
#define GPIO_ISET_DIO0_SET                                          0x00000001U
#define GPIO_ISET_DIO0_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_ICLR
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Clears DIO25 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO25                                             0x02000000U
#define GPIO_ICLR_DIO25_M                                           0x02000000U
#define GPIO_ICLR_DIO25_S                                                   25U
#define GPIO_ICLR_DIO25_CLR                                         0x02000000U
#define GPIO_ICLR_DIO25_NOEFF                                       0x00000000U

// Field:    [24] DIO24
//
// Clears DIO24 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO24                                             0x01000000U
#define GPIO_ICLR_DIO24_M                                           0x01000000U
#define GPIO_ICLR_DIO24_S                                                   24U
#define GPIO_ICLR_DIO24_CLR                                         0x01000000U
#define GPIO_ICLR_DIO24_NOEFF                                       0x00000000U

// Field:    [23] DIO23
//
// Clears DIO23 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO23                                             0x00800000U
#define GPIO_ICLR_DIO23_M                                           0x00800000U
#define GPIO_ICLR_DIO23_S                                                   23U
#define GPIO_ICLR_DIO23_CLR                                         0x00800000U
#define GPIO_ICLR_DIO23_NOEFF                                       0x00000000U

// Field:    [22] DIO22
//
// Clears DIO22 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO22                                             0x00400000U
#define GPIO_ICLR_DIO22_M                                           0x00400000U
#define GPIO_ICLR_DIO22_S                                                   22U
#define GPIO_ICLR_DIO22_CLR                                         0x00400000U
#define GPIO_ICLR_DIO22_NOEFF                                       0x00000000U

// Field:    [21] DIO21
//
// Clears DIO21 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO21                                             0x00200000U
#define GPIO_ICLR_DIO21_M                                           0x00200000U
#define GPIO_ICLR_DIO21_S                                                   21U
#define GPIO_ICLR_DIO21_CLR                                         0x00200000U
#define GPIO_ICLR_DIO21_NOEFF                                       0x00000000U

// Field:    [20] DIO20
//
// Clears DIO20 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO20                                             0x00100000U
#define GPIO_ICLR_DIO20_M                                           0x00100000U
#define GPIO_ICLR_DIO20_S                                                   20U
#define GPIO_ICLR_DIO20_CLR                                         0x00100000U
#define GPIO_ICLR_DIO20_NOEFF                                       0x00000000U

// Field:    [19] DIO19
//
// Clears DIO19 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO19                                             0x00080000U
#define GPIO_ICLR_DIO19_M                                           0x00080000U
#define GPIO_ICLR_DIO19_S                                                   19U
#define GPIO_ICLR_DIO19_CLR                                         0x00080000U
#define GPIO_ICLR_DIO19_NOEFF                                       0x00000000U

// Field:    [18] DIO18
//
// Clears DIO18 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO18                                             0x00040000U
#define GPIO_ICLR_DIO18_M                                           0x00040000U
#define GPIO_ICLR_DIO18_S                                                   18U
#define GPIO_ICLR_DIO18_CLR                                         0x00040000U
#define GPIO_ICLR_DIO18_NOEFF                                       0x00000000U

// Field:    [17] DIO17
//
// Clears DIO17 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO17                                             0x00020000U
#define GPIO_ICLR_DIO17_M                                           0x00020000U
#define GPIO_ICLR_DIO17_S                                                   17U
#define GPIO_ICLR_DIO17_CLR                                         0x00020000U
#define GPIO_ICLR_DIO17_NOEFF                                       0x00000000U

// Field:    [16] DIO16
//
// Clears DIO16 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO16                                             0x00010000U
#define GPIO_ICLR_DIO16_M                                           0x00010000U
#define GPIO_ICLR_DIO16_S                                                   16U
#define GPIO_ICLR_DIO16_CLR                                         0x00010000U
#define GPIO_ICLR_DIO16_NOEFF                                       0x00000000U

// Field:    [15] DIO15
//
// Clears DIO15 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO15                                             0x00008000U
#define GPIO_ICLR_DIO15_M                                           0x00008000U
#define GPIO_ICLR_DIO15_S                                                   15U
#define GPIO_ICLR_DIO15_CLR                                         0x00008000U
#define GPIO_ICLR_DIO15_NOEFF                                       0x00000000U

// Field:    [14] DIO14
//
// Clears DIO14 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO14                                             0x00004000U
#define GPIO_ICLR_DIO14_M                                           0x00004000U
#define GPIO_ICLR_DIO14_S                                                   14U
#define GPIO_ICLR_DIO14_CLR                                         0x00004000U
#define GPIO_ICLR_DIO14_NOEFF                                       0x00000000U

// Field:    [13] DIO13
//
// Clears DIO13 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO13                                             0x00002000U
#define GPIO_ICLR_DIO13_M                                           0x00002000U
#define GPIO_ICLR_DIO13_S                                                   13U
#define GPIO_ICLR_DIO13_CLR                                         0x00002000U
#define GPIO_ICLR_DIO13_NOEFF                                       0x00000000U

// Field:    [12] DIO12
//
// Clears DIO12 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO12                                             0x00001000U
#define GPIO_ICLR_DIO12_M                                           0x00001000U
#define GPIO_ICLR_DIO12_S                                                   12U
#define GPIO_ICLR_DIO12_CLR                                         0x00001000U
#define GPIO_ICLR_DIO12_NOEFF                                       0x00000000U

// Field:    [11] DIO11
//
// Clears DIO11 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO11                                             0x00000800U
#define GPIO_ICLR_DIO11_M                                           0x00000800U
#define GPIO_ICLR_DIO11_S                                                   11U
#define GPIO_ICLR_DIO11_CLR                                         0x00000800U
#define GPIO_ICLR_DIO11_NOEFF                                       0x00000000U

// Field:    [10] DIO10
//
// Clears DIO10 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO10                                             0x00000400U
#define GPIO_ICLR_DIO10_M                                           0x00000400U
#define GPIO_ICLR_DIO10_S                                                   10U
#define GPIO_ICLR_DIO10_CLR                                         0x00000400U
#define GPIO_ICLR_DIO10_NOEFF                                       0x00000000U

// Field:     [9] DIO9
//
// Clears DIO9 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO9                                              0x00000200U
#define GPIO_ICLR_DIO9_M                                            0x00000200U
#define GPIO_ICLR_DIO9_S                                                     9U
#define GPIO_ICLR_DIO9_CLR                                          0x00000200U
#define GPIO_ICLR_DIO9_NOEFF                                        0x00000000U

// Field:     [8] DIO8
//
// Clears DIO8 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO8                                              0x00000100U
#define GPIO_ICLR_DIO8_M                                            0x00000100U
#define GPIO_ICLR_DIO8_S                                                     8U
#define GPIO_ICLR_DIO8_CLR                                          0x00000100U
#define GPIO_ICLR_DIO8_NOEFF                                        0x00000000U

// Field:     [7] DIO7
//
// Clears DIO7 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO7                                              0x00000080U
#define GPIO_ICLR_DIO7_M                                            0x00000080U
#define GPIO_ICLR_DIO7_S                                                     7U
#define GPIO_ICLR_DIO7_CLR                                          0x00000080U
#define GPIO_ICLR_DIO7_NOEFF                                        0x00000000U

// Field:     [6] DIO6
//
// Clears DIO6 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO6                                              0x00000040U
#define GPIO_ICLR_DIO6_M                                            0x00000040U
#define GPIO_ICLR_DIO6_S                                                     6U
#define GPIO_ICLR_DIO6_CLR                                          0x00000040U
#define GPIO_ICLR_DIO6_NOEFF                                        0x00000000U

// Field:     [5] DIO5
//
// Clears DIO5 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO5                                              0x00000020U
#define GPIO_ICLR_DIO5_M                                            0x00000020U
#define GPIO_ICLR_DIO5_S                                                     5U
#define GPIO_ICLR_DIO5_CLR                                          0x00000020U
#define GPIO_ICLR_DIO5_NOEFF                                        0x00000000U

// Field:     [4] DIO4
//
// Clears DIO4 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO4                                              0x00000010U
#define GPIO_ICLR_DIO4_M                                            0x00000010U
#define GPIO_ICLR_DIO4_S                                                     4U
#define GPIO_ICLR_DIO4_CLR                                          0x00000010U
#define GPIO_ICLR_DIO4_NOEFF                                        0x00000000U

// Field:     [3] DIO3
//
// Clears DIO3 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO3                                              0x00000008U
#define GPIO_ICLR_DIO3_M                                            0x00000008U
#define GPIO_ICLR_DIO3_S                                                     3U
#define GPIO_ICLR_DIO3_CLR                                          0x00000008U
#define GPIO_ICLR_DIO3_NOEFF                                        0x00000000U

// Field:     [2] DIO2
//
// Clears DIO2 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO2                                              0x00000004U
#define GPIO_ICLR_DIO2_M                                            0x00000004U
#define GPIO_ICLR_DIO2_S                                                     2U
#define GPIO_ICLR_DIO2_CLR                                          0x00000004U
#define GPIO_ICLR_DIO2_NOEFF                                        0x00000000U

// Field:     [1] DIO1
//
// Clears DIO1 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO1                                              0x00000002U
#define GPIO_ICLR_DIO1_M                                            0x00000002U
#define GPIO_ICLR_DIO1_S                                                     1U
#define GPIO_ICLR_DIO1_CLR                                          0x00000002U
#define GPIO_ICLR_DIO1_NOEFF                                        0x00000000U

// Field:     [0] DIO0
//
// Clears DIO0 in RIS
// ENUMs:
// CLR                      Clear Interrupt
// NOEFF                    Writing 0 has no effect
#define GPIO_ICLR_DIO0                                              0x00000001U
#define GPIO_ICLR_DIO0_M                                            0x00000001U
#define GPIO_ICLR_DIO0_S                                                     0U
#define GPIO_ICLR_DIO0_CLR                                          0x00000001U
#define GPIO_ICLR_DIO0_NOEFF                                        0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_IMSET
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Sets DIO25 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO25                                            0x02000000U
#define GPIO_IMSET_DIO25_M                                          0x02000000U
#define GPIO_IMSET_DIO25_S                                                  25U
#define GPIO_IMSET_DIO25_SET                                        0x02000000U
#define GPIO_IMSET_DIO25_NOEFF                                      0x00000000U

// Field:    [24] DIO24
//
// Sets DIO24 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO24                                            0x01000000U
#define GPIO_IMSET_DIO24_M                                          0x01000000U
#define GPIO_IMSET_DIO24_S                                                  24U
#define GPIO_IMSET_DIO24_SET                                        0x01000000U
#define GPIO_IMSET_DIO24_NOEFF                                      0x00000000U

// Field:    [23] DIO23
//
// Sets DIO23 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO23                                            0x00800000U
#define GPIO_IMSET_DIO23_M                                          0x00800000U
#define GPIO_IMSET_DIO23_S                                                  23U
#define GPIO_IMSET_DIO23_SET                                        0x00800000U
#define GPIO_IMSET_DIO23_NOEFF                                      0x00000000U

// Field:    [22] DIO22
//
// Sets DIO22 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO22                                            0x00400000U
#define GPIO_IMSET_DIO22_M                                          0x00400000U
#define GPIO_IMSET_DIO22_S                                                  22U
#define GPIO_IMSET_DIO22_SET                                        0x00400000U
#define GPIO_IMSET_DIO22_NOEFF                                      0x00000000U

// Field:    [21] DIO21
//
// Sets DIO21 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO21                                            0x00200000U
#define GPIO_IMSET_DIO21_M                                          0x00200000U
#define GPIO_IMSET_DIO21_S                                                  21U
#define GPIO_IMSET_DIO21_SET                                        0x00200000U
#define GPIO_IMSET_DIO21_NOEFF                                      0x00000000U

// Field:    [20] DIO20
//
// Sets DIO20 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO20                                            0x00100000U
#define GPIO_IMSET_DIO20_M                                          0x00100000U
#define GPIO_IMSET_DIO20_S                                                  20U
#define GPIO_IMSET_DIO20_SET                                        0x00100000U
#define GPIO_IMSET_DIO20_NOEFF                                      0x00000000U

// Field:    [19] DIO19
//
// Sets DIO19 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO19                                            0x00080000U
#define GPIO_IMSET_DIO19_M                                          0x00080000U
#define GPIO_IMSET_DIO19_S                                                  19U
#define GPIO_IMSET_DIO19_SET                                        0x00080000U
#define GPIO_IMSET_DIO19_NOEFF                                      0x00000000U

// Field:    [18] DIO18
//
// Sets DIO18 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO18                                            0x00040000U
#define GPIO_IMSET_DIO18_M                                          0x00040000U
#define GPIO_IMSET_DIO18_S                                                  18U
#define GPIO_IMSET_DIO18_SET                                        0x00040000U
#define GPIO_IMSET_DIO18_NOEFF                                      0x00000000U

// Field:    [17] DIO17
//
// Sets DIO17 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO17                                            0x00020000U
#define GPIO_IMSET_DIO17_M                                          0x00020000U
#define GPIO_IMSET_DIO17_S                                                  17U
#define GPIO_IMSET_DIO17_SET                                        0x00020000U
#define GPIO_IMSET_DIO17_NOEFF                                      0x00000000U

// Field:    [16] DIO16
//
// Sets DIO16 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO16                                            0x00010000U
#define GPIO_IMSET_DIO16_M                                          0x00010000U
#define GPIO_IMSET_DIO16_S                                                  16U
#define GPIO_IMSET_DIO16_SET                                        0x00010000U
#define GPIO_IMSET_DIO16_NOEFF                                      0x00000000U

// Field:    [15] DIO15
//
// Sets DIO15 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO15                                            0x00008000U
#define GPIO_IMSET_DIO15_M                                          0x00008000U
#define GPIO_IMSET_DIO15_S                                                  15U
#define GPIO_IMSET_DIO15_SET                                        0x00008000U
#define GPIO_IMSET_DIO15_NOEFF                                      0x00000000U

// Field:    [14] DIO14
//
// Sets DIO14 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO14                                            0x00004000U
#define GPIO_IMSET_DIO14_M                                          0x00004000U
#define GPIO_IMSET_DIO14_S                                                  14U
#define GPIO_IMSET_DIO14_SET                                        0x00004000U
#define GPIO_IMSET_DIO14_NOEFF                                      0x00000000U

// Field:    [13] DIO13
//
// Sets DIO13 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO13                                            0x00002000U
#define GPIO_IMSET_DIO13_M                                          0x00002000U
#define GPIO_IMSET_DIO13_S                                                  13U
#define GPIO_IMSET_DIO13_SET                                        0x00002000U
#define GPIO_IMSET_DIO13_NOEFF                                      0x00000000U

// Field:    [12] DIO12
//
// Sets DIO12 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO12                                            0x00001000U
#define GPIO_IMSET_DIO12_M                                          0x00001000U
#define GPIO_IMSET_DIO12_S                                                  12U
#define GPIO_IMSET_DIO12_SET                                        0x00001000U
#define GPIO_IMSET_DIO12_NOEFF                                      0x00000000U

// Field:    [11] DIO11
//
// Sets DIO11 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO11                                            0x00000800U
#define GPIO_IMSET_DIO11_M                                          0x00000800U
#define GPIO_IMSET_DIO11_S                                                  11U
#define GPIO_IMSET_DIO11_SET                                        0x00000800U
#define GPIO_IMSET_DIO11_NOEFF                                      0x00000000U

// Field:    [10] DIO10
//
// Sets DIO10 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO10                                            0x00000400U
#define GPIO_IMSET_DIO10_M                                          0x00000400U
#define GPIO_IMSET_DIO10_S                                                  10U
#define GPIO_IMSET_DIO10_SET                                        0x00000400U
#define GPIO_IMSET_DIO10_NOEFF                                      0x00000000U

// Field:     [9] DIO9
//
// Sets DIO9 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO9                                             0x00000200U
#define GPIO_IMSET_DIO9_M                                           0x00000200U
#define GPIO_IMSET_DIO9_S                                                    9U
#define GPIO_IMSET_DIO9_SET                                         0x00000200U
#define GPIO_IMSET_DIO9_NOEFF                                       0x00000000U

// Field:     [8] DIO8
//
// Sets DIO8 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO8                                             0x00000100U
#define GPIO_IMSET_DIO8_M                                           0x00000100U
#define GPIO_IMSET_DIO8_S                                                    8U
#define GPIO_IMSET_DIO8_SET                                         0x00000100U
#define GPIO_IMSET_DIO8_NOEFF                                       0x00000000U

// Field:     [7] DIO7
//
// Sets DIO7 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO7                                             0x00000080U
#define GPIO_IMSET_DIO7_M                                           0x00000080U
#define GPIO_IMSET_DIO7_S                                                    7U
#define GPIO_IMSET_DIO7_SET                                         0x00000080U
#define GPIO_IMSET_DIO7_NOEFF                                       0x00000000U

// Field:     [6] DIO6
//
// Sets DIO6 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO6                                             0x00000040U
#define GPIO_IMSET_DIO6_M                                           0x00000040U
#define GPIO_IMSET_DIO6_S                                                    6U
#define GPIO_IMSET_DIO6_SET                                         0x00000040U
#define GPIO_IMSET_DIO6_NOEFF                                       0x00000000U

// Field:     [5] DIO5
//
// Sets DIO5 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO5                                             0x00000020U
#define GPIO_IMSET_DIO5_M                                           0x00000020U
#define GPIO_IMSET_DIO5_S                                                    5U
#define GPIO_IMSET_DIO5_SET                                         0x00000020U
#define GPIO_IMSET_DIO5_NOEFF                                       0x00000000U

// Field:     [4] DIO4
//
// Sets DIO4 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO4                                             0x00000010U
#define GPIO_IMSET_DIO4_M                                           0x00000010U
#define GPIO_IMSET_DIO4_S                                                    4U
#define GPIO_IMSET_DIO4_SET                                         0x00000010U
#define GPIO_IMSET_DIO4_NOEFF                                       0x00000000U

// Field:     [3] DIO3
//
// Sets DIO3 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO3                                             0x00000008U
#define GPIO_IMSET_DIO3_M                                           0x00000008U
#define GPIO_IMSET_DIO3_S                                                    3U
#define GPIO_IMSET_DIO3_SET                                         0x00000008U
#define GPIO_IMSET_DIO3_NOEFF                                       0x00000000U

// Field:     [2] DIO2
//
// Sets DIO2 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO2                                             0x00000004U
#define GPIO_IMSET_DIO2_M                                           0x00000004U
#define GPIO_IMSET_DIO2_S                                                    2U
#define GPIO_IMSET_DIO2_SET                                         0x00000004U
#define GPIO_IMSET_DIO2_NOEFF                                       0x00000000U

// Field:     [1] DIO1
//
// Sets DIO1 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO1                                             0x00000002U
#define GPIO_IMSET_DIO1_M                                           0x00000002U
#define GPIO_IMSET_DIO1_S                                                    1U
#define GPIO_IMSET_DIO1_SET                                         0x00000002U
#define GPIO_IMSET_DIO1_NOEFF                                       0x00000000U

// Field:     [0] DIO0
//
// Sets DIO0 in IMASK
// ENUMs:
// SET                      Set interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMSET_DIO0                                             0x00000001U
#define GPIO_IMSET_DIO0_M                                           0x00000001U
#define GPIO_IMSET_DIO0_S                                                    0U
#define GPIO_IMSET_DIO0_SET                                         0x00000001U
#define GPIO_IMSET_DIO0_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_IMCLR
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Clears DIO25 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO25                                            0x02000000U
#define GPIO_IMCLR_DIO25_M                                          0x02000000U
#define GPIO_IMCLR_DIO25_S                                                  25U
#define GPIO_IMCLR_DIO25_CLR                                        0x02000000U
#define GPIO_IMCLR_DIO25_NOEFF                                      0x00000000U

// Field:    [24] DIO24
//
// Clears DIO24 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO24                                            0x01000000U
#define GPIO_IMCLR_DIO24_M                                          0x01000000U
#define GPIO_IMCLR_DIO24_S                                                  24U
#define GPIO_IMCLR_DIO24_CLR                                        0x01000000U
#define GPIO_IMCLR_DIO24_NOEFF                                      0x00000000U

// Field:    [23] DIO23
//
// Clears DIO23 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO23                                            0x00800000U
#define GPIO_IMCLR_DIO23_M                                          0x00800000U
#define GPIO_IMCLR_DIO23_S                                                  23U
#define GPIO_IMCLR_DIO23_CLR                                        0x00800000U
#define GPIO_IMCLR_DIO23_NOEFF                                      0x00000000U

// Field:    [22] DIO22
//
// Clears DIO22 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO22                                            0x00400000U
#define GPIO_IMCLR_DIO22_M                                          0x00400000U
#define GPIO_IMCLR_DIO22_S                                                  22U
#define GPIO_IMCLR_DIO22_CLR                                        0x00400000U
#define GPIO_IMCLR_DIO22_NOEFF                                      0x00000000U

// Field:    [21] DIO21
//
// Clears DIO21 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO21                                            0x00200000U
#define GPIO_IMCLR_DIO21_M                                          0x00200000U
#define GPIO_IMCLR_DIO21_S                                                  21U
#define GPIO_IMCLR_DIO21_CLR                                        0x00200000U
#define GPIO_IMCLR_DIO21_NOEFF                                      0x00000000U

// Field:    [20] DIO20
//
// Clears DIO20 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO20                                            0x00100000U
#define GPIO_IMCLR_DIO20_M                                          0x00100000U
#define GPIO_IMCLR_DIO20_S                                                  20U
#define GPIO_IMCLR_DIO20_CLR                                        0x00100000U
#define GPIO_IMCLR_DIO20_NOEFF                                      0x00000000U

// Field:    [19] DIO19
//
// Clears DIO19 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO19                                            0x00080000U
#define GPIO_IMCLR_DIO19_M                                          0x00080000U
#define GPIO_IMCLR_DIO19_S                                                  19U
#define GPIO_IMCLR_DIO19_CLR                                        0x00080000U
#define GPIO_IMCLR_DIO19_NOEFF                                      0x00000000U

// Field:    [18] DIO18
//
// Clears DIO18 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO18                                            0x00040000U
#define GPIO_IMCLR_DIO18_M                                          0x00040000U
#define GPIO_IMCLR_DIO18_S                                                  18U
#define GPIO_IMCLR_DIO18_CLR                                        0x00040000U
#define GPIO_IMCLR_DIO18_NOEFF                                      0x00000000U

// Field:    [17] DIO17
//
// Clears DIO17 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO17                                            0x00020000U
#define GPIO_IMCLR_DIO17_M                                          0x00020000U
#define GPIO_IMCLR_DIO17_S                                                  17U
#define GPIO_IMCLR_DIO17_CLR                                        0x00020000U
#define GPIO_IMCLR_DIO17_NOEFF                                      0x00000000U

// Field:    [16] DIO16
//
// Clears DIO16 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO16                                            0x00010000U
#define GPIO_IMCLR_DIO16_M                                          0x00010000U
#define GPIO_IMCLR_DIO16_S                                                  16U
#define GPIO_IMCLR_DIO16_CLR                                        0x00010000U
#define GPIO_IMCLR_DIO16_NOEFF                                      0x00000000U

// Field:    [15] DIO15
//
// Clears DIO15 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO15                                            0x00008000U
#define GPIO_IMCLR_DIO15_M                                          0x00008000U
#define GPIO_IMCLR_DIO15_S                                                  15U
#define GPIO_IMCLR_DIO15_CLR                                        0x00008000U
#define GPIO_IMCLR_DIO15_NOEFF                                      0x00000000U

// Field:    [14] DIO14
//
// Clears DIO14 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO14                                            0x00004000U
#define GPIO_IMCLR_DIO14_M                                          0x00004000U
#define GPIO_IMCLR_DIO14_S                                                  14U
#define GPIO_IMCLR_DIO14_CLR                                        0x00004000U
#define GPIO_IMCLR_DIO14_NOEFF                                      0x00000000U

// Field:    [13] DIO13
//
// Clears DIO13 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO13                                            0x00002000U
#define GPIO_IMCLR_DIO13_M                                          0x00002000U
#define GPIO_IMCLR_DIO13_S                                                  13U
#define GPIO_IMCLR_DIO13_CLR                                        0x00002000U
#define GPIO_IMCLR_DIO13_NOEFF                                      0x00000000U

// Field:    [12] DIO12
//
// Clears DIO12 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO12                                            0x00001000U
#define GPIO_IMCLR_DIO12_M                                          0x00001000U
#define GPIO_IMCLR_DIO12_S                                                  12U
#define GPIO_IMCLR_DIO12_CLR                                        0x00001000U
#define GPIO_IMCLR_DIO12_NOEFF                                      0x00000000U

// Field:    [11] DIO11
//
// Clears DIO11 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO11                                            0x00000800U
#define GPIO_IMCLR_DIO11_M                                          0x00000800U
#define GPIO_IMCLR_DIO11_S                                                  11U
#define GPIO_IMCLR_DIO11_CLR                                        0x00000800U
#define GPIO_IMCLR_DIO11_NOEFF                                      0x00000000U

// Field:    [10] DIO10
//
// Clears DIO10 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO10                                            0x00000400U
#define GPIO_IMCLR_DIO10_M                                          0x00000400U
#define GPIO_IMCLR_DIO10_S                                                  10U
#define GPIO_IMCLR_DIO10_CLR                                        0x00000400U
#define GPIO_IMCLR_DIO10_NOEFF                                      0x00000000U

// Field:     [9] DIO9
//
// Clears DIO9 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO9                                             0x00000200U
#define GPIO_IMCLR_DIO9_M                                           0x00000200U
#define GPIO_IMCLR_DIO9_S                                                    9U
#define GPIO_IMCLR_DIO9_CLR                                         0x00000200U
#define GPIO_IMCLR_DIO9_NOEFF                                       0x00000000U

// Field:     [8] DIO8
//
// Clears DIO8 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO8                                             0x00000100U
#define GPIO_IMCLR_DIO8_M                                           0x00000100U
#define GPIO_IMCLR_DIO8_S                                                    8U
#define GPIO_IMCLR_DIO8_CLR                                         0x00000100U
#define GPIO_IMCLR_DIO8_NOEFF                                       0x00000000U

// Field:     [7] DIO7
//
// Clears DIO7 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO7                                             0x00000080U
#define GPIO_IMCLR_DIO7_M                                           0x00000080U
#define GPIO_IMCLR_DIO7_S                                                    7U
#define GPIO_IMCLR_DIO7_CLR                                         0x00000080U
#define GPIO_IMCLR_DIO7_NOEFF                                       0x00000000U

// Field:     [6] DIO6
//
// Clears DIO6 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO6                                             0x00000040U
#define GPIO_IMCLR_DIO6_M                                           0x00000040U
#define GPIO_IMCLR_DIO6_S                                                    6U
#define GPIO_IMCLR_DIO6_CLR                                         0x00000040U
#define GPIO_IMCLR_DIO6_NOEFF                                       0x00000000U

// Field:     [5] DIO5
//
// Clears DIO5 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO5                                             0x00000020U
#define GPIO_IMCLR_DIO5_M                                           0x00000020U
#define GPIO_IMCLR_DIO5_S                                                    5U
#define GPIO_IMCLR_DIO5_CLR                                         0x00000020U
#define GPIO_IMCLR_DIO5_NOEFF                                       0x00000000U

// Field:     [4] DIO4
//
// Clears DIO4 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO4                                             0x00000010U
#define GPIO_IMCLR_DIO4_M                                           0x00000010U
#define GPIO_IMCLR_DIO4_S                                                    4U
#define GPIO_IMCLR_DIO4_CLR                                         0x00000010U
#define GPIO_IMCLR_DIO4_NOEFF                                       0x00000000U

// Field:     [3] DIO3
//
// Clears DIO3 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO3                                             0x00000008U
#define GPIO_IMCLR_DIO3_M                                           0x00000008U
#define GPIO_IMCLR_DIO3_S                                                    3U
#define GPIO_IMCLR_DIO3_CLR                                         0x00000008U
#define GPIO_IMCLR_DIO3_NOEFF                                       0x00000000U

// Field:     [2] DIO2
//
// Clears DIO2 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO2                                             0x00000004U
#define GPIO_IMCLR_DIO2_M                                           0x00000004U
#define GPIO_IMCLR_DIO2_S                                                    2U
#define GPIO_IMCLR_DIO2_CLR                                         0x00000004U
#define GPIO_IMCLR_DIO2_NOEFF                                       0x00000000U

// Field:     [1] DIO1
//
// Clears DIO1 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO1                                             0x00000002U
#define GPIO_IMCLR_DIO1_M                                           0x00000002U
#define GPIO_IMCLR_DIO1_S                                                    1U
#define GPIO_IMCLR_DIO1_CLR                                         0x00000002U
#define GPIO_IMCLR_DIO1_NOEFF                                       0x00000000U

// Field:     [0] DIO0
//
// Clears DIO0 in IMASK
// ENUMs:
// CLR                      Clear interrupt mask
// NOEFF                    Writing 0 has no effect
#define GPIO_IMCLR_DIO0                                             0x00000001U
#define GPIO_IMCLR_DIO0_M                                           0x00000001U
#define GPIO_IMCLR_DIO0_S                                                    0U
#define GPIO_IMCLR_DIO0_CLR                                         0x00000001U
#define GPIO_IMCLR_DIO0_NOEFF                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT3_0
//
//*****************************************************************************
// Field:    [24] DIO3
//
// Data output for DIO3
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT3_0_DIO3                                           0x01000000U
#define GPIO_DOUT3_0_DIO3_M                                         0x01000000U
#define GPIO_DOUT3_0_DIO3_S                                                 24U
#define GPIO_DOUT3_0_DIO3_ONE                                       0x01000000U
#define GPIO_DOUT3_0_DIO3_ZERO                                      0x00000000U

// Field:    [16] DIO2
//
// Data output for DIO2
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT3_0_DIO2                                           0x00010000U
#define GPIO_DOUT3_0_DIO2_M                                         0x00010000U
#define GPIO_DOUT3_0_DIO2_S                                                 16U
#define GPIO_DOUT3_0_DIO2_ONE                                       0x00010000U
#define GPIO_DOUT3_0_DIO2_ZERO                                      0x00000000U

// Field:     [8] DIO1
//
// Data output for DIO1
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT3_0_DIO1                                           0x00000100U
#define GPIO_DOUT3_0_DIO1_M                                         0x00000100U
#define GPIO_DOUT3_0_DIO1_S                                                  8U
#define GPIO_DOUT3_0_DIO1_ONE                                       0x00000100U
#define GPIO_DOUT3_0_DIO1_ZERO                                      0x00000000U

// Field:     [0] DIO0
//
// Data output for DIO0
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT3_0_DIO0                                           0x00000001U
#define GPIO_DOUT3_0_DIO0_M                                         0x00000001U
#define GPIO_DOUT3_0_DIO0_S                                                  0U
#define GPIO_DOUT3_0_DIO0_ONE                                       0x00000001U
#define GPIO_DOUT3_0_DIO0_ZERO                                      0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT7_4
//
//*****************************************************************************
// Field:    [24] DIO7
//
// Data output for DIO7
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT7_4_DIO7                                           0x01000000U
#define GPIO_DOUT7_4_DIO7_M                                         0x01000000U
#define GPIO_DOUT7_4_DIO7_S                                                 24U
#define GPIO_DOUT7_4_DIO7_ONE                                       0x01000000U
#define GPIO_DOUT7_4_DIO7_ZERO                                      0x00000000U

// Field:    [16] DIO6
//
// Data output for DIO6
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT7_4_DIO6                                           0x00010000U
#define GPIO_DOUT7_4_DIO6_M                                         0x00010000U
#define GPIO_DOUT7_4_DIO6_S                                                 16U
#define GPIO_DOUT7_4_DIO6_ONE                                       0x00010000U
#define GPIO_DOUT7_4_DIO6_ZERO                                      0x00000000U

// Field:     [8] DIO5
//
// Data output for DIO5
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT7_4_DIO5                                           0x00000100U
#define GPIO_DOUT7_4_DIO5_M                                         0x00000100U
#define GPIO_DOUT7_4_DIO5_S                                                  8U
#define GPIO_DOUT7_4_DIO5_ONE                                       0x00000100U
#define GPIO_DOUT7_4_DIO5_ZERO                                      0x00000000U

// Field:     [0] DIO4
//
// Data output for DIO4
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT7_4_DIO4                                           0x00000001U
#define GPIO_DOUT7_4_DIO4_M                                         0x00000001U
#define GPIO_DOUT7_4_DIO4_S                                                  0U
#define GPIO_DOUT7_4_DIO4_ONE                                       0x00000001U
#define GPIO_DOUT7_4_DIO4_ZERO                                      0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT11_8
//
//*****************************************************************************
// Field:    [24] DIO11
//
// Data output for DIO11
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT11_8_DIO11                                         0x01000000U
#define GPIO_DOUT11_8_DIO11_M                                       0x01000000U
#define GPIO_DOUT11_8_DIO11_S                                               24U
#define GPIO_DOUT11_8_DIO11_ONE                                     0x01000000U
#define GPIO_DOUT11_8_DIO11_ZERO                                    0x00000000U

// Field:    [16] DIO10
//
// Data output for DIO10
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT11_8_DIO10                                         0x00010000U
#define GPIO_DOUT11_8_DIO10_M                                       0x00010000U
#define GPIO_DOUT11_8_DIO10_S                                               16U
#define GPIO_DOUT11_8_DIO10_ONE                                     0x00010000U
#define GPIO_DOUT11_8_DIO10_ZERO                                    0x00000000U

// Field:     [8] DIO9
//
// Data output for DIO9
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT11_8_DIO9                                          0x00000100U
#define GPIO_DOUT11_8_DIO9_M                                        0x00000100U
#define GPIO_DOUT11_8_DIO9_S                                                 8U
#define GPIO_DOUT11_8_DIO9_ONE                                      0x00000100U
#define GPIO_DOUT11_8_DIO9_ZERO                                     0x00000000U

// Field:     [0] DIO8
//
// Data output for DIO8
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT11_8_DIO8                                          0x00000001U
#define GPIO_DOUT11_8_DIO8_M                                        0x00000001U
#define GPIO_DOUT11_8_DIO8_S                                                 0U
#define GPIO_DOUT11_8_DIO8_ONE                                      0x00000001U
#define GPIO_DOUT11_8_DIO8_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT15_12
//
//*****************************************************************************
// Field:    [24] DIO15
//
// Data output for DIO15
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT15_12_DIO15                                        0x01000000U
#define GPIO_DOUT15_12_DIO15_M                                      0x01000000U
#define GPIO_DOUT15_12_DIO15_S                                              24U
#define GPIO_DOUT15_12_DIO15_ONE                                    0x01000000U
#define GPIO_DOUT15_12_DIO15_ZERO                                   0x00000000U

// Field:    [16] DIO14
//
// Data output for DIO14
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT15_12_DIO14                                        0x00010000U
#define GPIO_DOUT15_12_DIO14_M                                      0x00010000U
#define GPIO_DOUT15_12_DIO14_S                                              16U
#define GPIO_DOUT15_12_DIO14_ONE                                    0x00010000U
#define GPIO_DOUT15_12_DIO14_ZERO                                   0x00000000U

// Field:     [8] DIO13
//
// Data output for DIO13
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT15_12_DIO13                                        0x00000100U
#define GPIO_DOUT15_12_DIO13_M                                      0x00000100U
#define GPIO_DOUT15_12_DIO13_S                                               8U
#define GPIO_DOUT15_12_DIO13_ONE                                    0x00000100U
#define GPIO_DOUT15_12_DIO13_ZERO                                   0x00000000U

// Field:     [0] DIO12
//
// Data output for DIO12
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT15_12_DIO12                                        0x00000001U
#define GPIO_DOUT15_12_DIO12_M                                      0x00000001U
#define GPIO_DOUT15_12_DIO12_S                                               0U
#define GPIO_DOUT15_12_DIO12_ONE                                    0x00000001U
#define GPIO_DOUT15_12_DIO12_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT19_16
//
//*****************************************************************************
// Field:    [24] DIO19
//
// Data output for DIO19
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT19_16_DIO19                                        0x01000000U
#define GPIO_DOUT19_16_DIO19_M                                      0x01000000U
#define GPIO_DOUT19_16_DIO19_S                                              24U
#define GPIO_DOUT19_16_DIO19_ONE                                    0x01000000U
#define GPIO_DOUT19_16_DIO19_ZERO                                   0x00000000U

// Field:    [16] DIO18
//
// Data output for DIO18
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT19_16_DIO18                                        0x00010000U
#define GPIO_DOUT19_16_DIO18_M                                      0x00010000U
#define GPIO_DOUT19_16_DIO18_S                                              16U
#define GPIO_DOUT19_16_DIO18_ONE                                    0x00010000U
#define GPIO_DOUT19_16_DIO18_ZERO                                   0x00000000U

// Field:     [8] DIO17
//
// Data output for DIO17
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT19_16_DIO17                                        0x00000100U
#define GPIO_DOUT19_16_DIO17_M                                      0x00000100U
#define GPIO_DOUT19_16_DIO17_S                                               8U
#define GPIO_DOUT19_16_DIO17_ONE                                    0x00000100U
#define GPIO_DOUT19_16_DIO17_ZERO                                   0x00000000U

// Field:     [0] DIO16
//
// Data output for DIO16
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT19_16_DIO16                                        0x00000001U
#define GPIO_DOUT19_16_DIO16_M                                      0x00000001U
#define GPIO_DOUT19_16_DIO16_S                                               0U
#define GPIO_DOUT19_16_DIO16_ONE                                    0x00000001U
#define GPIO_DOUT19_16_DIO16_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT23_20
//
//*****************************************************************************
// Field:    [24] DIO23
//
// Data output for DIO23
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT23_20_DIO23                                        0x01000000U
#define GPIO_DOUT23_20_DIO23_M                                      0x01000000U
#define GPIO_DOUT23_20_DIO23_S                                              24U
#define GPIO_DOUT23_20_DIO23_ONE                                    0x01000000U
#define GPIO_DOUT23_20_DIO23_ZERO                                   0x00000000U

// Field:    [16] DIO22
//
// Data output for DIO22
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT23_20_DIO22                                        0x00010000U
#define GPIO_DOUT23_20_DIO22_M                                      0x00010000U
#define GPIO_DOUT23_20_DIO22_S                                              16U
#define GPIO_DOUT23_20_DIO22_ONE                                    0x00010000U
#define GPIO_DOUT23_20_DIO22_ZERO                                   0x00000000U

// Field:     [8] DIO21
//
// Data output for DIO21
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT23_20_DIO21                                        0x00000100U
#define GPIO_DOUT23_20_DIO21_M                                      0x00000100U
#define GPIO_DOUT23_20_DIO21_S                                               8U
#define GPIO_DOUT23_20_DIO21_ONE                                    0x00000100U
#define GPIO_DOUT23_20_DIO21_ZERO                                   0x00000000U

// Field:     [0] DIO20
//
// Data output for DIO20
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT23_20_DIO20                                        0x00000001U
#define GPIO_DOUT23_20_DIO20_M                                      0x00000001U
#define GPIO_DOUT23_20_DIO20_S                                               0U
#define GPIO_DOUT23_20_DIO20_ONE                                    0x00000001U
#define GPIO_DOUT23_20_DIO20_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT27_24
//
//*****************************************************************************
// Field:     [8] DIO25
//
// Data output for DIO25
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT27_24_DIO25                                        0x00000100U
#define GPIO_DOUT27_24_DIO25_M                                      0x00000100U
#define GPIO_DOUT27_24_DIO25_S                                               8U
#define GPIO_DOUT27_24_DIO25_ONE                                    0x00000100U
#define GPIO_DOUT27_24_DIO25_ZERO                                   0x00000000U

// Field:     [0] DIO24
//
// Data output for DIO24
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT27_24_DIO24                                        0x00000001U
#define GPIO_DOUT27_24_DIO24_M                                      0x00000001U
#define GPIO_DOUT27_24_DIO24_S                                               0U
#define GPIO_DOUT27_24_DIO24_ONE                                    0x00000001U
#define GPIO_DOUT27_24_DIO24_ZERO                                   0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUT31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Data output for DIO25
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO25                                         0x02000000U
#define GPIO_DOUT31_0_DIO25_M                                       0x02000000U
#define GPIO_DOUT31_0_DIO25_S                                               25U
#define GPIO_DOUT31_0_DIO25_ONE                                     0x02000000U
#define GPIO_DOUT31_0_DIO25_ZERO                                    0x00000000U

// Field:    [24] DIO24
//
// Data output for DIO24
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO24                                         0x01000000U
#define GPIO_DOUT31_0_DIO24_M                                       0x01000000U
#define GPIO_DOUT31_0_DIO24_S                                               24U
#define GPIO_DOUT31_0_DIO24_ONE                                     0x01000000U
#define GPIO_DOUT31_0_DIO24_ZERO                                    0x00000000U

// Field:    [23] DIO23
//
// Data output for DIO23
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO23                                         0x00800000U
#define GPIO_DOUT31_0_DIO23_M                                       0x00800000U
#define GPIO_DOUT31_0_DIO23_S                                               23U
#define GPIO_DOUT31_0_DIO23_ONE                                     0x00800000U
#define GPIO_DOUT31_0_DIO23_ZERO                                    0x00000000U

// Field:    [22] DIO22
//
// Data output for DIO22
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO22                                         0x00400000U
#define GPIO_DOUT31_0_DIO22_M                                       0x00400000U
#define GPIO_DOUT31_0_DIO22_S                                               22U
#define GPIO_DOUT31_0_DIO22_ONE                                     0x00400000U
#define GPIO_DOUT31_0_DIO22_ZERO                                    0x00000000U

// Field:    [21] DIO21
//
// Data output for DIO21
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO21                                         0x00200000U
#define GPIO_DOUT31_0_DIO21_M                                       0x00200000U
#define GPIO_DOUT31_0_DIO21_S                                               21U
#define GPIO_DOUT31_0_DIO21_ONE                                     0x00200000U
#define GPIO_DOUT31_0_DIO21_ZERO                                    0x00000000U

// Field:    [20] DIO20
//
// Data output for DIO20
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO20                                         0x00100000U
#define GPIO_DOUT31_0_DIO20_M                                       0x00100000U
#define GPIO_DOUT31_0_DIO20_S                                               20U
#define GPIO_DOUT31_0_DIO20_ONE                                     0x00100000U
#define GPIO_DOUT31_0_DIO20_ZERO                                    0x00000000U

// Field:    [19] DIO19
//
// Data output for DIO19
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO19                                         0x00080000U
#define GPIO_DOUT31_0_DIO19_M                                       0x00080000U
#define GPIO_DOUT31_0_DIO19_S                                               19U
#define GPIO_DOUT31_0_DIO19_ONE                                     0x00080000U
#define GPIO_DOUT31_0_DIO19_ZERO                                    0x00000000U

// Field:    [18] DIO18
//
// Data output for DIO18
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO18                                         0x00040000U
#define GPIO_DOUT31_0_DIO18_M                                       0x00040000U
#define GPIO_DOUT31_0_DIO18_S                                               18U
#define GPIO_DOUT31_0_DIO18_ONE                                     0x00040000U
#define GPIO_DOUT31_0_DIO18_ZERO                                    0x00000000U

// Field:    [17] DIO17
//
// Data output for DIO17
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO17                                         0x00020000U
#define GPIO_DOUT31_0_DIO17_M                                       0x00020000U
#define GPIO_DOUT31_0_DIO17_S                                               17U
#define GPIO_DOUT31_0_DIO17_ONE                                     0x00020000U
#define GPIO_DOUT31_0_DIO17_ZERO                                    0x00000000U

// Field:    [16] DIO16
//
// Data output for DIO16
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO16                                         0x00010000U
#define GPIO_DOUT31_0_DIO16_M                                       0x00010000U
#define GPIO_DOUT31_0_DIO16_S                                               16U
#define GPIO_DOUT31_0_DIO16_ONE                                     0x00010000U
#define GPIO_DOUT31_0_DIO16_ZERO                                    0x00000000U

// Field:    [15] DIO15
//
// Data output for DIO15
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO15                                         0x00008000U
#define GPIO_DOUT31_0_DIO15_M                                       0x00008000U
#define GPIO_DOUT31_0_DIO15_S                                               15U
#define GPIO_DOUT31_0_DIO15_ONE                                     0x00008000U
#define GPIO_DOUT31_0_DIO15_ZERO                                    0x00000000U

// Field:    [14] DIO14
//
// Data output for DIO14
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO14                                         0x00004000U
#define GPIO_DOUT31_0_DIO14_M                                       0x00004000U
#define GPIO_DOUT31_0_DIO14_S                                               14U
#define GPIO_DOUT31_0_DIO14_ONE                                     0x00004000U
#define GPIO_DOUT31_0_DIO14_ZERO                                    0x00000000U

// Field:    [13] DIO13
//
// Data output for DIO13
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO13                                         0x00002000U
#define GPIO_DOUT31_0_DIO13_M                                       0x00002000U
#define GPIO_DOUT31_0_DIO13_S                                               13U
#define GPIO_DOUT31_0_DIO13_ONE                                     0x00002000U
#define GPIO_DOUT31_0_DIO13_ZERO                                    0x00000000U

// Field:    [12] DIO12
//
// Data output for DIO12
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO12                                         0x00001000U
#define GPIO_DOUT31_0_DIO12_M                                       0x00001000U
#define GPIO_DOUT31_0_DIO12_S                                               12U
#define GPIO_DOUT31_0_DIO12_ONE                                     0x00001000U
#define GPIO_DOUT31_0_DIO12_ZERO                                    0x00000000U

// Field:    [11] DIO11
//
// Data output for DIO11
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO11                                         0x00000800U
#define GPIO_DOUT31_0_DIO11_M                                       0x00000800U
#define GPIO_DOUT31_0_DIO11_S                                               11U
#define GPIO_DOUT31_0_DIO11_ONE                                     0x00000800U
#define GPIO_DOUT31_0_DIO11_ZERO                                    0x00000000U

// Field:    [10] DIO10
//
// Data output for DIO10
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO10                                         0x00000400U
#define GPIO_DOUT31_0_DIO10_M                                       0x00000400U
#define GPIO_DOUT31_0_DIO10_S                                               10U
#define GPIO_DOUT31_0_DIO10_ONE                                     0x00000400U
#define GPIO_DOUT31_0_DIO10_ZERO                                    0x00000000U

// Field:     [9] DIO9
//
// Data output for DIO9
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO9                                          0x00000200U
#define GPIO_DOUT31_0_DIO9_M                                        0x00000200U
#define GPIO_DOUT31_0_DIO9_S                                                 9U
#define GPIO_DOUT31_0_DIO9_ONE                                      0x00000200U
#define GPIO_DOUT31_0_DIO9_ZERO                                     0x00000000U

// Field:     [8] DIO8
//
// Data output for DIO8
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO8                                          0x00000100U
#define GPIO_DOUT31_0_DIO8_M                                        0x00000100U
#define GPIO_DOUT31_0_DIO8_S                                                 8U
#define GPIO_DOUT31_0_DIO8_ONE                                      0x00000100U
#define GPIO_DOUT31_0_DIO8_ZERO                                     0x00000000U

// Field:     [7] DIO7
//
// Data output for DIO7
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO7                                          0x00000080U
#define GPIO_DOUT31_0_DIO7_M                                        0x00000080U
#define GPIO_DOUT31_0_DIO7_S                                                 7U
#define GPIO_DOUT31_0_DIO7_ONE                                      0x00000080U
#define GPIO_DOUT31_0_DIO7_ZERO                                     0x00000000U

// Field:     [6] DIO6
//
// Data output for DIO6
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO6                                          0x00000040U
#define GPIO_DOUT31_0_DIO6_M                                        0x00000040U
#define GPIO_DOUT31_0_DIO6_S                                                 6U
#define GPIO_DOUT31_0_DIO6_ONE                                      0x00000040U
#define GPIO_DOUT31_0_DIO6_ZERO                                     0x00000000U

// Field:     [5] DIO5
//
// Data output for DIO5
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO5                                          0x00000020U
#define GPIO_DOUT31_0_DIO5_M                                        0x00000020U
#define GPIO_DOUT31_0_DIO5_S                                                 5U
#define GPIO_DOUT31_0_DIO5_ONE                                      0x00000020U
#define GPIO_DOUT31_0_DIO5_ZERO                                     0x00000000U

// Field:     [4] DIO4
//
// Data output for DIO4
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO4                                          0x00000010U
#define GPIO_DOUT31_0_DIO4_M                                        0x00000010U
#define GPIO_DOUT31_0_DIO4_S                                                 4U
#define GPIO_DOUT31_0_DIO4_ONE                                      0x00000010U
#define GPIO_DOUT31_0_DIO4_ZERO                                     0x00000000U

// Field:     [3] DIO3
//
// Data output for DIO3
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO3                                          0x00000008U
#define GPIO_DOUT31_0_DIO3_M                                        0x00000008U
#define GPIO_DOUT31_0_DIO3_S                                                 3U
#define GPIO_DOUT31_0_DIO3_ONE                                      0x00000008U
#define GPIO_DOUT31_0_DIO3_ZERO                                     0x00000000U

// Field:     [2] DIO2
//
// Data output for DIO2
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO2                                          0x00000004U
#define GPIO_DOUT31_0_DIO2_M                                        0x00000004U
#define GPIO_DOUT31_0_DIO2_S                                                 2U
#define GPIO_DOUT31_0_DIO2_ONE                                      0x00000004U
#define GPIO_DOUT31_0_DIO2_ZERO                                     0x00000000U

// Field:     [1] DIO1
//
// Data output for DIO1
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO1                                          0x00000002U
#define GPIO_DOUT31_0_DIO1_M                                        0x00000002U
#define GPIO_DOUT31_0_DIO1_S                                                 1U
#define GPIO_DOUT31_0_DIO1_ONE                                      0x00000002U
#define GPIO_DOUT31_0_DIO1_ZERO                                     0x00000000U

// Field:     [0] DIO0
//
// Data output for DIO0
// ENUMs:
// ONE                      Output is set to 1
// ZERO                     Output is set to 0
#define GPIO_DOUT31_0_DIO0                                          0x00000001U
#define GPIO_DOUT31_0_DIO0_M                                        0x00000001U
#define GPIO_DOUT31_0_DIO0_S                                                 0U
#define GPIO_DOUT31_0_DIO0_ONE                                      0x00000001U
#define GPIO_DOUT31_0_DIO0_ZERO                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTSET31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Set bit DOUT31_0.DIO25
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO25                                      0x02000000U
#define GPIO_DOUTSET31_0_DIO25_M                                    0x02000000U
#define GPIO_DOUTSET31_0_DIO25_S                                            25U
#define GPIO_DOUTSET31_0_DIO25_SET                                  0x02000000U
#define GPIO_DOUTSET31_0_DIO25_NOEFF                                0x00000000U

// Field:    [24] DIO24
//
// Set bit DOUT31_0.DIO24
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO24                                      0x01000000U
#define GPIO_DOUTSET31_0_DIO24_M                                    0x01000000U
#define GPIO_DOUTSET31_0_DIO24_S                                            24U
#define GPIO_DOUTSET31_0_DIO24_SET                                  0x01000000U
#define GPIO_DOUTSET31_0_DIO24_NOEFF                                0x00000000U

// Field:    [23] DIO23
//
// Set bit DOUT31_0.DIO23
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO23                                      0x00800000U
#define GPIO_DOUTSET31_0_DIO23_M                                    0x00800000U
#define GPIO_DOUTSET31_0_DIO23_S                                            23U
#define GPIO_DOUTSET31_0_DIO23_SET                                  0x00800000U
#define GPIO_DOUTSET31_0_DIO23_NOEFF                                0x00000000U

// Field:    [22] DIO22
//
// Set bit DOUT31_0.DIO22
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO22                                      0x00400000U
#define GPIO_DOUTSET31_0_DIO22_M                                    0x00400000U
#define GPIO_DOUTSET31_0_DIO22_S                                            22U
#define GPIO_DOUTSET31_0_DIO22_SET                                  0x00400000U
#define GPIO_DOUTSET31_0_DIO22_NOEFF                                0x00000000U

// Field:    [21] DIO21
//
// Set bit DOUT31_0.DIO21
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO21                                      0x00200000U
#define GPIO_DOUTSET31_0_DIO21_M                                    0x00200000U
#define GPIO_DOUTSET31_0_DIO21_S                                            21U
#define GPIO_DOUTSET31_0_DIO21_SET                                  0x00200000U
#define GPIO_DOUTSET31_0_DIO21_NOEFF                                0x00000000U

// Field:    [20] DIO20
//
// Set bit DOUT31_0.DIO20
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO20                                      0x00100000U
#define GPIO_DOUTSET31_0_DIO20_M                                    0x00100000U
#define GPIO_DOUTSET31_0_DIO20_S                                            20U
#define GPIO_DOUTSET31_0_DIO20_SET                                  0x00100000U
#define GPIO_DOUTSET31_0_DIO20_NOEFF                                0x00000000U

// Field:    [19] DIO19
//
// Set bit DOUT31_0.DIO19
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO19                                      0x00080000U
#define GPIO_DOUTSET31_0_DIO19_M                                    0x00080000U
#define GPIO_DOUTSET31_0_DIO19_S                                            19U
#define GPIO_DOUTSET31_0_DIO19_SET                                  0x00080000U
#define GPIO_DOUTSET31_0_DIO19_NOEFF                                0x00000000U

// Field:    [18] DIO18
//
// Set bit DOUT31_0.DIO18
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO18                                      0x00040000U
#define GPIO_DOUTSET31_0_DIO18_M                                    0x00040000U
#define GPIO_DOUTSET31_0_DIO18_S                                            18U
#define GPIO_DOUTSET31_0_DIO18_SET                                  0x00040000U
#define GPIO_DOUTSET31_0_DIO18_NOEFF                                0x00000000U

// Field:    [17] DIO17
//
// Set bit DOUT31_0.DIO17
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO17                                      0x00020000U
#define GPIO_DOUTSET31_0_DIO17_M                                    0x00020000U
#define GPIO_DOUTSET31_0_DIO17_S                                            17U
#define GPIO_DOUTSET31_0_DIO17_SET                                  0x00020000U
#define GPIO_DOUTSET31_0_DIO17_NOEFF                                0x00000000U

// Field:    [16] DIO16
//
// Set bit DOUT31_0.DIO16
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO16                                      0x00010000U
#define GPIO_DOUTSET31_0_DIO16_M                                    0x00010000U
#define GPIO_DOUTSET31_0_DIO16_S                                            16U
#define GPIO_DOUTSET31_0_DIO16_SET                                  0x00010000U
#define GPIO_DOUTSET31_0_DIO16_NOEFF                                0x00000000U

// Field:    [15] DIO15
//
// Set bit DOUT31_0.DIO15
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO15                                      0x00008000U
#define GPIO_DOUTSET31_0_DIO15_M                                    0x00008000U
#define GPIO_DOUTSET31_0_DIO15_S                                            15U
#define GPIO_DOUTSET31_0_DIO15_SET                                  0x00008000U
#define GPIO_DOUTSET31_0_DIO15_NOEFF                                0x00000000U

// Field:    [14] DIO14
//
// Set bit DOUT31_0.DIO14
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO14                                      0x00004000U
#define GPIO_DOUTSET31_0_DIO14_M                                    0x00004000U
#define GPIO_DOUTSET31_0_DIO14_S                                            14U
#define GPIO_DOUTSET31_0_DIO14_SET                                  0x00004000U
#define GPIO_DOUTSET31_0_DIO14_NOEFF                                0x00000000U

// Field:    [13] DIO13
//
// Set bit DOUT31_0.DIO13
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO13                                      0x00002000U
#define GPIO_DOUTSET31_0_DIO13_M                                    0x00002000U
#define GPIO_DOUTSET31_0_DIO13_S                                            13U
#define GPIO_DOUTSET31_0_DIO13_SET                                  0x00002000U
#define GPIO_DOUTSET31_0_DIO13_NOEFF                                0x00000000U

// Field:    [12] DIO12
//
// Set bit DOUT31_0.DIO12
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO12                                      0x00001000U
#define GPIO_DOUTSET31_0_DIO12_M                                    0x00001000U
#define GPIO_DOUTSET31_0_DIO12_S                                            12U
#define GPIO_DOUTSET31_0_DIO12_SET                                  0x00001000U
#define GPIO_DOUTSET31_0_DIO12_NOEFF                                0x00000000U

// Field:    [11] DIO11
//
// Set bit DOUT31_0.DIO11
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO11                                      0x00000800U
#define GPIO_DOUTSET31_0_DIO11_M                                    0x00000800U
#define GPIO_DOUTSET31_0_DIO11_S                                            11U
#define GPIO_DOUTSET31_0_DIO11_SET                                  0x00000800U
#define GPIO_DOUTSET31_0_DIO11_NOEFF                                0x00000000U

// Field:    [10] DIO10
//
// Set bit DOUT31_0.DIO10
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO10                                      0x00000400U
#define GPIO_DOUTSET31_0_DIO10_M                                    0x00000400U
#define GPIO_DOUTSET31_0_DIO10_S                                            10U
#define GPIO_DOUTSET31_0_DIO10_SET                                  0x00000400U
#define GPIO_DOUTSET31_0_DIO10_NOEFF                                0x00000000U

// Field:     [9] DIO9
//
// Set bit DOUT31_0.DIO9
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO9                                       0x00000200U
#define GPIO_DOUTSET31_0_DIO9_M                                     0x00000200U
#define GPIO_DOUTSET31_0_DIO9_S                                              9U
#define GPIO_DOUTSET31_0_DIO9_SET                                   0x00000200U
#define GPIO_DOUTSET31_0_DIO9_NOEFF                                 0x00000000U

// Field:     [8] DIO8
//
// Set bit DOUT31_0.DIO8
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO8                                       0x00000100U
#define GPIO_DOUTSET31_0_DIO8_M                                     0x00000100U
#define GPIO_DOUTSET31_0_DIO8_S                                              8U
#define GPIO_DOUTSET31_0_DIO8_SET                                   0x00000100U
#define GPIO_DOUTSET31_0_DIO8_NOEFF                                 0x00000000U

// Field:     [7] DIO7
//
// Set bit DOUT31_0.DIO7
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO7                                       0x00000080U
#define GPIO_DOUTSET31_0_DIO7_M                                     0x00000080U
#define GPIO_DOUTSET31_0_DIO7_S                                              7U
#define GPIO_DOUTSET31_0_DIO7_SET                                   0x00000080U
#define GPIO_DOUTSET31_0_DIO7_NOEFF                                 0x00000000U

// Field:     [6] DIO6
//
// Set bit DOUT31_0.DIO6
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO6                                       0x00000040U
#define GPIO_DOUTSET31_0_DIO6_M                                     0x00000040U
#define GPIO_DOUTSET31_0_DIO6_S                                              6U
#define GPIO_DOUTSET31_0_DIO6_SET                                   0x00000040U
#define GPIO_DOUTSET31_0_DIO6_NOEFF                                 0x00000000U

// Field:     [5] DIO5
//
// Set bit DOUT31_0.DIO5
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO5                                       0x00000020U
#define GPIO_DOUTSET31_0_DIO5_M                                     0x00000020U
#define GPIO_DOUTSET31_0_DIO5_S                                              5U
#define GPIO_DOUTSET31_0_DIO5_SET                                   0x00000020U
#define GPIO_DOUTSET31_0_DIO5_NOEFF                                 0x00000000U

// Field:     [4] DIO4
//
// Set bit DOUT31_0.DIO4
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO4                                       0x00000010U
#define GPIO_DOUTSET31_0_DIO4_M                                     0x00000010U
#define GPIO_DOUTSET31_0_DIO4_S                                              4U
#define GPIO_DOUTSET31_0_DIO4_SET                                   0x00000010U
#define GPIO_DOUTSET31_0_DIO4_NOEFF                                 0x00000000U

// Field:     [3] DIO3
//
// Set bit DOUT31_0.DIO3
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO3                                       0x00000008U
#define GPIO_DOUTSET31_0_DIO3_M                                     0x00000008U
#define GPIO_DOUTSET31_0_DIO3_S                                              3U
#define GPIO_DOUTSET31_0_DIO3_SET                                   0x00000008U
#define GPIO_DOUTSET31_0_DIO3_NOEFF                                 0x00000000U

// Field:     [2] DIO2
//
// Set bit DOUT31_0.DIO2
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO2                                       0x00000004U
#define GPIO_DOUTSET31_0_DIO2_M                                     0x00000004U
#define GPIO_DOUTSET31_0_DIO2_S                                              2U
#define GPIO_DOUTSET31_0_DIO2_SET                                   0x00000004U
#define GPIO_DOUTSET31_0_DIO2_NOEFF                                 0x00000000U

// Field:     [1] DIO1
//
// Set bit DOUT31_0.DIO1
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO1                                       0x00000002U
#define GPIO_DOUTSET31_0_DIO1_M                                     0x00000002U
#define GPIO_DOUTSET31_0_DIO1_S                                              1U
#define GPIO_DOUTSET31_0_DIO1_SET                                   0x00000002U
#define GPIO_DOUTSET31_0_DIO1_NOEFF                                 0x00000000U

// Field:     [0] DIO0
//
// Set bit DOUT31_0.DIO0
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOUTSET31_0_DIO0                                       0x00000001U
#define GPIO_DOUTSET31_0_DIO0_M                                     0x00000001U
#define GPIO_DOUTSET31_0_DIO0_S                                              0U
#define GPIO_DOUTSET31_0_DIO0_SET                                   0x00000001U
#define GPIO_DOUTSET31_0_DIO0_NOEFF                                 0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTCLR31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Clear bit DOUT31_0.DIO25
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO25                                      0x02000000U
#define GPIO_DOUTCLR31_0_DIO25_M                                    0x02000000U
#define GPIO_DOUTCLR31_0_DIO25_S                                            25U
#define GPIO_DOUTCLR31_0_DIO25_CLR                                  0x02000000U
#define GPIO_DOUTCLR31_0_DIO25_NOEFF                                0x00000000U

// Field:    [24] DIO24
//
// Clear bit DOUT31_0.DIO24
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO24                                      0x01000000U
#define GPIO_DOUTCLR31_0_DIO24_M                                    0x01000000U
#define GPIO_DOUTCLR31_0_DIO24_S                                            24U
#define GPIO_DOUTCLR31_0_DIO24_CLR                                  0x01000000U
#define GPIO_DOUTCLR31_0_DIO24_NOEFF                                0x00000000U

// Field:    [23] DIO23
//
// Clear bit DOUT31_0.DIO23
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO23                                      0x00800000U
#define GPIO_DOUTCLR31_0_DIO23_M                                    0x00800000U
#define GPIO_DOUTCLR31_0_DIO23_S                                            23U
#define GPIO_DOUTCLR31_0_DIO23_CLR                                  0x00800000U
#define GPIO_DOUTCLR31_0_DIO23_NOEFF                                0x00000000U

// Field:    [22] DIO22
//
// Clear bit DOUT31_0.DIO22
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO22                                      0x00400000U
#define GPIO_DOUTCLR31_0_DIO22_M                                    0x00400000U
#define GPIO_DOUTCLR31_0_DIO22_S                                            22U
#define GPIO_DOUTCLR31_0_DIO22_CLR                                  0x00400000U
#define GPIO_DOUTCLR31_0_DIO22_NOEFF                                0x00000000U

// Field:    [21] DIO21
//
// Clear bit DOUT31_0.DIO21
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO21                                      0x00200000U
#define GPIO_DOUTCLR31_0_DIO21_M                                    0x00200000U
#define GPIO_DOUTCLR31_0_DIO21_S                                            21U
#define GPIO_DOUTCLR31_0_DIO21_CLR                                  0x00200000U
#define GPIO_DOUTCLR31_0_DIO21_NOEFF                                0x00000000U

// Field:    [20] DIO20
//
// Clear bit DOUT31_0.DIO20
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO20                                      0x00100000U
#define GPIO_DOUTCLR31_0_DIO20_M                                    0x00100000U
#define GPIO_DOUTCLR31_0_DIO20_S                                            20U
#define GPIO_DOUTCLR31_0_DIO20_CLR                                  0x00100000U
#define GPIO_DOUTCLR31_0_DIO20_NOEFF                                0x00000000U

// Field:    [19] DIO19
//
// Clear bit DOUT31_0.DIO19
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO19                                      0x00080000U
#define GPIO_DOUTCLR31_0_DIO19_M                                    0x00080000U
#define GPIO_DOUTCLR31_0_DIO19_S                                            19U
#define GPIO_DOUTCLR31_0_DIO19_CLR                                  0x00080000U
#define GPIO_DOUTCLR31_0_DIO19_NOEFF                                0x00000000U

// Field:    [18] DIO18
//
// Clear bit DOUT31_0.DIO18
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO18                                      0x00040000U
#define GPIO_DOUTCLR31_0_DIO18_M                                    0x00040000U
#define GPIO_DOUTCLR31_0_DIO18_S                                            18U
#define GPIO_DOUTCLR31_0_DIO18_CLR                                  0x00040000U
#define GPIO_DOUTCLR31_0_DIO18_NOEFF                                0x00000000U

// Field:    [17] DIO17
//
// Clear bit DOUT31_0.DIO17
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO17                                      0x00020000U
#define GPIO_DOUTCLR31_0_DIO17_M                                    0x00020000U
#define GPIO_DOUTCLR31_0_DIO17_S                                            17U
#define GPIO_DOUTCLR31_0_DIO17_CLR                                  0x00020000U
#define GPIO_DOUTCLR31_0_DIO17_NOEFF                                0x00000000U

// Field:    [16] DIO16
//
// Clear bit DOUT31_0.DIO16
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO16                                      0x00010000U
#define GPIO_DOUTCLR31_0_DIO16_M                                    0x00010000U
#define GPIO_DOUTCLR31_0_DIO16_S                                            16U
#define GPIO_DOUTCLR31_0_DIO16_CLR                                  0x00010000U
#define GPIO_DOUTCLR31_0_DIO16_NOEFF                                0x00000000U

// Field:    [15] DIO15
//
// Clear bit DOUT31_0.DIO15
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO15                                      0x00008000U
#define GPIO_DOUTCLR31_0_DIO15_M                                    0x00008000U
#define GPIO_DOUTCLR31_0_DIO15_S                                            15U
#define GPIO_DOUTCLR31_0_DIO15_CLR                                  0x00008000U
#define GPIO_DOUTCLR31_0_DIO15_NOEFF                                0x00000000U

// Field:    [14] DIO14
//
// Clear bit DOUT31_0.DIO14
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO14                                      0x00004000U
#define GPIO_DOUTCLR31_0_DIO14_M                                    0x00004000U
#define GPIO_DOUTCLR31_0_DIO14_S                                            14U
#define GPIO_DOUTCLR31_0_DIO14_CLR                                  0x00004000U
#define GPIO_DOUTCLR31_0_DIO14_NOEFF                                0x00000000U

// Field:    [13] DIO13
//
// Clear bit DOUT31_0.DIO13
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO13                                      0x00002000U
#define GPIO_DOUTCLR31_0_DIO13_M                                    0x00002000U
#define GPIO_DOUTCLR31_0_DIO13_S                                            13U
#define GPIO_DOUTCLR31_0_DIO13_CLR                                  0x00002000U
#define GPIO_DOUTCLR31_0_DIO13_NOEFF                                0x00000000U

// Field:    [12] DIO12
//
// Clear bit DOUT31_0.DIO12
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO12                                      0x00001000U
#define GPIO_DOUTCLR31_0_DIO12_M                                    0x00001000U
#define GPIO_DOUTCLR31_0_DIO12_S                                            12U
#define GPIO_DOUTCLR31_0_DIO12_CLR                                  0x00001000U
#define GPIO_DOUTCLR31_0_DIO12_NOEFF                                0x00000000U

// Field:    [11] DIO11
//
// Clear bit DOUT31_0.DIO11
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO11                                      0x00000800U
#define GPIO_DOUTCLR31_0_DIO11_M                                    0x00000800U
#define GPIO_DOUTCLR31_0_DIO11_S                                            11U
#define GPIO_DOUTCLR31_0_DIO11_CLR                                  0x00000800U
#define GPIO_DOUTCLR31_0_DIO11_NOEFF                                0x00000000U

// Field:    [10] DIO10
//
// Clear bit DOUT31_0.DIO10
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO10                                      0x00000400U
#define GPIO_DOUTCLR31_0_DIO10_M                                    0x00000400U
#define GPIO_DOUTCLR31_0_DIO10_S                                            10U
#define GPIO_DOUTCLR31_0_DIO10_CLR                                  0x00000400U
#define GPIO_DOUTCLR31_0_DIO10_NOEFF                                0x00000000U

// Field:     [9] DIO9
//
// Clear bit DOUT31_0.DIO9
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO9                                       0x00000200U
#define GPIO_DOUTCLR31_0_DIO9_M                                     0x00000200U
#define GPIO_DOUTCLR31_0_DIO9_S                                              9U
#define GPIO_DOUTCLR31_0_DIO9_CLR                                   0x00000200U
#define GPIO_DOUTCLR31_0_DIO9_NOEFF                                 0x00000000U

// Field:     [8] DIO8
//
// Clear bit DOUT31_0.DIO8
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO8                                       0x00000100U
#define GPIO_DOUTCLR31_0_DIO8_M                                     0x00000100U
#define GPIO_DOUTCLR31_0_DIO8_S                                              8U
#define GPIO_DOUTCLR31_0_DIO8_CLR                                   0x00000100U
#define GPIO_DOUTCLR31_0_DIO8_NOEFF                                 0x00000000U

// Field:     [7] DIO7
//
// Clear bit DOUT31_0.DIO7
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO7                                       0x00000080U
#define GPIO_DOUTCLR31_0_DIO7_M                                     0x00000080U
#define GPIO_DOUTCLR31_0_DIO7_S                                              7U
#define GPIO_DOUTCLR31_0_DIO7_CLR                                   0x00000080U
#define GPIO_DOUTCLR31_0_DIO7_NOEFF                                 0x00000000U

// Field:     [6] DIO6
//
// Clear bit DOUT31_0.DIO6
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO6                                       0x00000040U
#define GPIO_DOUTCLR31_0_DIO6_M                                     0x00000040U
#define GPIO_DOUTCLR31_0_DIO6_S                                              6U
#define GPIO_DOUTCLR31_0_DIO6_CLR                                   0x00000040U
#define GPIO_DOUTCLR31_0_DIO6_NOEFF                                 0x00000000U

// Field:     [5] DIO5
//
// Clear bit DOUT31_0.DIO5
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO5                                       0x00000020U
#define GPIO_DOUTCLR31_0_DIO5_M                                     0x00000020U
#define GPIO_DOUTCLR31_0_DIO5_S                                              5U
#define GPIO_DOUTCLR31_0_DIO5_CLR                                   0x00000020U
#define GPIO_DOUTCLR31_0_DIO5_NOEFF                                 0x00000000U

// Field:     [4] DIO4
//
// Clear bit DOUT31_0.DIO4
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO4                                       0x00000010U
#define GPIO_DOUTCLR31_0_DIO4_M                                     0x00000010U
#define GPIO_DOUTCLR31_0_DIO4_S                                              4U
#define GPIO_DOUTCLR31_0_DIO4_CLR                                   0x00000010U
#define GPIO_DOUTCLR31_0_DIO4_NOEFF                                 0x00000000U

// Field:     [3] DIO3
//
// Clear bit DOUT31_0.DIO3
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO3                                       0x00000008U
#define GPIO_DOUTCLR31_0_DIO3_M                                     0x00000008U
#define GPIO_DOUTCLR31_0_DIO3_S                                              3U
#define GPIO_DOUTCLR31_0_DIO3_CLR                                   0x00000008U
#define GPIO_DOUTCLR31_0_DIO3_NOEFF                                 0x00000000U

// Field:     [2] DIO2
//
// Clear bit DOUT31_0.DIO2
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO2                                       0x00000004U
#define GPIO_DOUTCLR31_0_DIO2_M                                     0x00000004U
#define GPIO_DOUTCLR31_0_DIO2_S                                              2U
#define GPIO_DOUTCLR31_0_DIO2_CLR                                   0x00000004U
#define GPIO_DOUTCLR31_0_DIO2_NOEFF                                 0x00000000U

// Field:     [1] DIO1
//
// Clear bit DOUT31_0.DIO1
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO1                                       0x00000002U
#define GPIO_DOUTCLR31_0_DIO1_M                                     0x00000002U
#define GPIO_DOUTCLR31_0_DIO1_S                                              1U
#define GPIO_DOUTCLR31_0_DIO1_CLR                                   0x00000002U
#define GPIO_DOUTCLR31_0_DIO1_NOEFF                                 0x00000000U

// Field:     [0] DIO0
//
// Clear bit DOUT31_0.DIO0
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOUTCLR31_0_DIO0                                       0x00000001U
#define GPIO_DOUTCLR31_0_DIO0_M                                     0x00000001U
#define GPIO_DOUTCLR31_0_DIO0_S                                              0U
#define GPIO_DOUTCLR31_0_DIO0_CLR                                   0x00000001U
#define GPIO_DOUTCLR31_0_DIO0_NOEFF                                 0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Toggles bit DOUT31_0.DIO25
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO25                                      0x02000000U
#define GPIO_DOUTTGL31_0_DIO25_M                                    0x02000000U
#define GPIO_DOUTTGL31_0_DIO25_S                                            25U
#define GPIO_DOUTTGL31_0_DIO25_TOGGLE                               0x02000000U
#define GPIO_DOUTTGL31_0_DIO25_NOEFF                                0x00000000U

// Field:    [24] DIO24
//
// Toggles bit DOUT31_0.DIO24
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO24                                      0x01000000U
#define GPIO_DOUTTGL31_0_DIO24_M                                    0x01000000U
#define GPIO_DOUTTGL31_0_DIO24_S                                            24U
#define GPIO_DOUTTGL31_0_DIO24_TOGGLE                               0x01000000U
#define GPIO_DOUTTGL31_0_DIO24_NOEFF                                0x00000000U

// Field:    [23] DIO23
//
// Toggles bit DOUT31_0.DIO23
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO23                                      0x00800000U
#define GPIO_DOUTTGL31_0_DIO23_M                                    0x00800000U
#define GPIO_DOUTTGL31_0_DIO23_S                                            23U
#define GPIO_DOUTTGL31_0_DIO23_TOGGLE                               0x00800000U
#define GPIO_DOUTTGL31_0_DIO23_NOEFF                                0x00000000U

// Field:    [22] DIO22
//
// Toggles bit DOUT31_0.DIO22
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO22                                      0x00400000U
#define GPIO_DOUTTGL31_0_DIO22_M                                    0x00400000U
#define GPIO_DOUTTGL31_0_DIO22_S                                            22U
#define GPIO_DOUTTGL31_0_DIO22_TOGGLE                               0x00400000U
#define GPIO_DOUTTGL31_0_DIO22_NOEFF                                0x00000000U

// Field:    [21] DIO21
//
// Toggles bit DOUT31_0.DIO21
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO21                                      0x00200000U
#define GPIO_DOUTTGL31_0_DIO21_M                                    0x00200000U
#define GPIO_DOUTTGL31_0_DIO21_S                                            21U
#define GPIO_DOUTTGL31_0_DIO21_TOGGLE                               0x00200000U
#define GPIO_DOUTTGL31_0_DIO21_NOEFF                                0x00000000U

// Field:    [20] DIO20
//
// Toggles bit DOUT31_0.DIO20
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO20                                      0x00100000U
#define GPIO_DOUTTGL31_0_DIO20_M                                    0x00100000U
#define GPIO_DOUTTGL31_0_DIO20_S                                            20U
#define GPIO_DOUTTGL31_0_DIO20_TOGGLE                               0x00100000U
#define GPIO_DOUTTGL31_0_DIO20_NOEFF                                0x00000000U

// Field:    [19] DIO19
//
// Toggles bit DOUT31_0.DIO19
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO19                                      0x00080000U
#define GPIO_DOUTTGL31_0_DIO19_M                                    0x00080000U
#define GPIO_DOUTTGL31_0_DIO19_S                                            19U
#define GPIO_DOUTTGL31_0_DIO19_TOGGLE                               0x00080000U
#define GPIO_DOUTTGL31_0_DIO19_NOEFF                                0x00000000U

// Field:    [18] DIO18
//
// Toggles bit DOUT31_0.DIO18
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO18                                      0x00040000U
#define GPIO_DOUTTGL31_0_DIO18_M                                    0x00040000U
#define GPIO_DOUTTGL31_0_DIO18_S                                            18U
#define GPIO_DOUTTGL31_0_DIO18_TOGGLE                               0x00040000U
#define GPIO_DOUTTGL31_0_DIO18_NOEFF                                0x00000000U

// Field:    [17] DIO17
//
// Toggles bit DOUT31_0.DIO17
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO17                                      0x00020000U
#define GPIO_DOUTTGL31_0_DIO17_M                                    0x00020000U
#define GPIO_DOUTTGL31_0_DIO17_S                                            17U
#define GPIO_DOUTTGL31_0_DIO17_TOGGLE                               0x00020000U
#define GPIO_DOUTTGL31_0_DIO17_NOEFF                                0x00000000U

// Field:    [16] DIO16
//
// Toggles bit DOUT31_0.DIO16
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO16                                      0x00010000U
#define GPIO_DOUTTGL31_0_DIO16_M                                    0x00010000U
#define GPIO_DOUTTGL31_0_DIO16_S                                            16U
#define GPIO_DOUTTGL31_0_DIO16_TOGGLE                               0x00010000U
#define GPIO_DOUTTGL31_0_DIO16_NOEFF                                0x00000000U

// Field:    [15] DIO15
//
// Toggles bit DOUT31_0.DIO15
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO15                                      0x00008000U
#define GPIO_DOUTTGL31_0_DIO15_M                                    0x00008000U
#define GPIO_DOUTTGL31_0_DIO15_S                                            15U
#define GPIO_DOUTTGL31_0_DIO15_TOGGLE                               0x00008000U
#define GPIO_DOUTTGL31_0_DIO15_NOEFF                                0x00000000U

// Field:    [14] DIO14
//
// Toggles bit DOUT31_0.DIO14
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO14                                      0x00004000U
#define GPIO_DOUTTGL31_0_DIO14_M                                    0x00004000U
#define GPIO_DOUTTGL31_0_DIO14_S                                            14U
#define GPIO_DOUTTGL31_0_DIO14_TOGGLE                               0x00004000U
#define GPIO_DOUTTGL31_0_DIO14_NOEFF                                0x00000000U

// Field:    [13] DIO13
//
// Toggles bit DOUT31_0.DIO13
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO13                                      0x00002000U
#define GPIO_DOUTTGL31_0_DIO13_M                                    0x00002000U
#define GPIO_DOUTTGL31_0_DIO13_S                                            13U
#define GPIO_DOUTTGL31_0_DIO13_TOGGLE                               0x00002000U
#define GPIO_DOUTTGL31_0_DIO13_NOEFF                                0x00000000U

// Field:    [12] DIO12
//
// Toggles bit DOUT31_0.DIO12
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO12                                      0x00001000U
#define GPIO_DOUTTGL31_0_DIO12_M                                    0x00001000U
#define GPIO_DOUTTGL31_0_DIO12_S                                            12U
#define GPIO_DOUTTGL31_0_DIO12_TOGGLE                               0x00001000U
#define GPIO_DOUTTGL31_0_DIO12_NOEFF                                0x00000000U

// Field:    [11] DIO11
//
// Toggles bit DOUT31_0.DIO11
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO11                                      0x00000800U
#define GPIO_DOUTTGL31_0_DIO11_M                                    0x00000800U
#define GPIO_DOUTTGL31_0_DIO11_S                                            11U
#define GPIO_DOUTTGL31_0_DIO11_TOGGLE                               0x00000800U
#define GPIO_DOUTTGL31_0_DIO11_NOEFF                                0x00000000U

// Field:    [10] DIO10
//
// Toggles bit DOUT31_0.DIO10
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO10                                      0x00000400U
#define GPIO_DOUTTGL31_0_DIO10_M                                    0x00000400U
#define GPIO_DOUTTGL31_0_DIO10_S                                            10U
#define GPIO_DOUTTGL31_0_DIO10_TOGGLE                               0x00000400U
#define GPIO_DOUTTGL31_0_DIO10_NOEFF                                0x00000000U

// Field:     [9] DIO9
//
// Toggles bit DOUT31_0.DIO9
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO9                                       0x00000200U
#define GPIO_DOUTTGL31_0_DIO9_M                                     0x00000200U
#define GPIO_DOUTTGL31_0_DIO9_S                                              9U
#define GPIO_DOUTTGL31_0_DIO9_TOGGLE                                0x00000200U
#define GPIO_DOUTTGL31_0_DIO9_NOEFF                                 0x00000000U

// Field:     [8] DIO8
//
// Toggles bit DOUT31_0.DIO8
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO8                                       0x00000100U
#define GPIO_DOUTTGL31_0_DIO8_M                                     0x00000100U
#define GPIO_DOUTTGL31_0_DIO8_S                                              8U
#define GPIO_DOUTTGL31_0_DIO8_TOGGLE                                0x00000100U
#define GPIO_DOUTTGL31_0_DIO8_NOEFF                                 0x00000000U

// Field:     [7] DIO7
//
// Toggles bit DOUT31_0.DIO7
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO7                                       0x00000080U
#define GPIO_DOUTTGL31_0_DIO7_M                                     0x00000080U
#define GPIO_DOUTTGL31_0_DIO7_S                                              7U
#define GPIO_DOUTTGL31_0_DIO7_TOGGLE                                0x00000080U
#define GPIO_DOUTTGL31_0_DIO7_NOEFF                                 0x00000000U

// Field:     [6] DIO6
//
// Toggles bit DOUT31_0.DIO6
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO6                                       0x00000040U
#define GPIO_DOUTTGL31_0_DIO6_M                                     0x00000040U
#define GPIO_DOUTTGL31_0_DIO6_S                                              6U
#define GPIO_DOUTTGL31_0_DIO6_TOGGLE                                0x00000040U
#define GPIO_DOUTTGL31_0_DIO6_NOEFF                                 0x00000000U

// Field:     [5] DIO5
//
// Toggles bit DOUT31_0.DIO5
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO5                                       0x00000020U
#define GPIO_DOUTTGL31_0_DIO5_M                                     0x00000020U
#define GPIO_DOUTTGL31_0_DIO5_S                                              5U
#define GPIO_DOUTTGL31_0_DIO5_TOGGLE                                0x00000020U
#define GPIO_DOUTTGL31_0_DIO5_NOEFF                                 0x00000000U

// Field:     [4] DIO4
//
// Toggles bit DOUT31_0.DIO4
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO4                                       0x00000010U
#define GPIO_DOUTTGL31_0_DIO4_M                                     0x00000010U
#define GPIO_DOUTTGL31_0_DIO4_S                                              4U
#define GPIO_DOUTTGL31_0_DIO4_TOGGLE                                0x00000010U
#define GPIO_DOUTTGL31_0_DIO4_NOEFF                                 0x00000000U

// Field:     [3] DIO3
//
// Toggles bit DOUT31_0.DIO3
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO3                                       0x00000008U
#define GPIO_DOUTTGL31_0_DIO3_M                                     0x00000008U
#define GPIO_DOUTTGL31_0_DIO3_S                                              3U
#define GPIO_DOUTTGL31_0_DIO3_TOGGLE                                0x00000008U
#define GPIO_DOUTTGL31_0_DIO3_NOEFF                                 0x00000000U

// Field:     [2] DIO2
//
// Toggles bit DOUT31_0.DIO2
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO2                                       0x00000004U
#define GPIO_DOUTTGL31_0_DIO2_M                                     0x00000004U
#define GPIO_DOUTTGL31_0_DIO2_S                                              2U
#define GPIO_DOUTTGL31_0_DIO2_TOGGLE                                0x00000004U
#define GPIO_DOUTTGL31_0_DIO2_NOEFF                                 0x00000000U

// Field:     [1] DIO1
//
// Toggles bit DOUT31_0.DIO1
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO1                                       0x00000002U
#define GPIO_DOUTTGL31_0_DIO1_M                                     0x00000002U
#define GPIO_DOUTTGL31_0_DIO1_S                                              1U
#define GPIO_DOUTTGL31_0_DIO1_TOGGLE                                0x00000002U
#define GPIO_DOUTTGL31_0_DIO1_NOEFF                                 0x00000000U

// Field:     [0] DIO0
//
// Toggles bit DOUT31_0.DIO0
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL31_0_DIO0                                       0x00000001U
#define GPIO_DOUTTGL31_0_DIO0_M                                     0x00000001U
#define GPIO_DOUTTGL31_0_DIO0_S                                              0U
#define GPIO_DOUTTGL31_0_DIO0_TOGGLE                                0x00000001U
#define GPIO_DOUTTGL31_0_DIO0_NOEFF                                 0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL3_0
//
//*****************************************************************************
// Field:    [24] DIO3
//
// Toggles bit DOUT31_0.DIO3
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL3_0_DIO3                                        0x01000000U
#define GPIO_DOUTTGL3_0_DIO3_M                                      0x01000000U
#define GPIO_DOUTTGL3_0_DIO3_S                                              24U
#define GPIO_DOUTTGL3_0_DIO3_TOGGLE                                 0x01000000U
#define GPIO_DOUTTGL3_0_DIO3_NOEFF                                  0x00000000U

// Field:    [16] DIO2
//
// Toggles bit DOUT31_0.DIO2
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL3_0_DIO2                                        0x00010000U
#define GPIO_DOUTTGL3_0_DIO2_M                                      0x00010000U
#define GPIO_DOUTTGL3_0_DIO2_S                                              16U
#define GPIO_DOUTTGL3_0_DIO2_TOGGLE                                 0x00010000U
#define GPIO_DOUTTGL3_0_DIO2_NOEFF                                  0x00000000U

// Field:     [8] DIO1
//
// Toggles bit DOUT31_0.DIO1
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL3_0_DIO1                                        0x00000100U
#define GPIO_DOUTTGL3_0_DIO1_M                                      0x00000100U
#define GPIO_DOUTTGL3_0_DIO1_S                                               8U
#define GPIO_DOUTTGL3_0_DIO1_TOGGLE                                 0x00000100U
#define GPIO_DOUTTGL3_0_DIO1_NOEFF                                  0x00000000U

// Field:     [0] DIO0
//
// Toggles bit DOUT31_0.DIO0
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL3_0_DIO0                                        0x00000001U
#define GPIO_DOUTTGL3_0_DIO0_M                                      0x00000001U
#define GPIO_DOUTTGL3_0_DIO0_S                                               0U
#define GPIO_DOUTTGL3_0_DIO0_TOGGLE                                 0x00000001U
#define GPIO_DOUTTGL3_0_DIO0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL7_4
//
//*****************************************************************************
// Field:    [24] DIO7
//
// Toggles bit DOUT31_0.DIO7
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL7_4_DIO7                                        0x01000000U
#define GPIO_DOUTTGL7_4_DIO7_M                                      0x01000000U
#define GPIO_DOUTTGL7_4_DIO7_S                                              24U
#define GPIO_DOUTTGL7_4_DIO7_TOGGLE                                 0x01000000U
#define GPIO_DOUTTGL7_4_DIO7_NOEFF                                  0x00000000U

// Field:    [16] DIO6
//
// Toggles bit DOUT31_0.DIO6
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL7_4_DIO6                                        0x00010000U
#define GPIO_DOUTTGL7_4_DIO6_M                                      0x00010000U
#define GPIO_DOUTTGL7_4_DIO6_S                                              16U
#define GPIO_DOUTTGL7_4_DIO6_TOGGLE                                 0x00010000U
#define GPIO_DOUTTGL7_4_DIO6_NOEFF                                  0x00000000U

// Field:     [8] DIO5
//
// Toggles bit DOUT31_0.DIO5
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL7_4_DIO5                                        0x00000100U
#define GPIO_DOUTTGL7_4_DIO5_M                                      0x00000100U
#define GPIO_DOUTTGL7_4_DIO5_S                                               8U
#define GPIO_DOUTTGL7_4_DIO5_TOGGLE                                 0x00000100U
#define GPIO_DOUTTGL7_4_DIO5_NOEFF                                  0x00000000U

// Field:     [0] DIO4
//
// Toggles bit DOUT31_0.DIO4
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL7_4_DIO4                                        0x00000001U
#define GPIO_DOUTTGL7_4_DIO4_M                                      0x00000001U
#define GPIO_DOUTTGL7_4_DIO4_S                                               0U
#define GPIO_DOUTTGL7_4_DIO4_TOGGLE                                 0x00000001U
#define GPIO_DOUTTGL7_4_DIO4_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL11_8
//
//*****************************************************************************
// Field:    [24] DIO11
//
// Toggles bit DOUT31_0.DIO11
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL11_8_DIO11                                      0x01000000U
#define GPIO_DOUTTGL11_8_DIO11_M                                    0x01000000U
#define GPIO_DOUTTGL11_8_DIO11_S                                            24U
#define GPIO_DOUTTGL11_8_DIO11_TOGGLE                               0x01000000U
#define GPIO_DOUTTGL11_8_DIO11_NOEFF                                0x00000000U

// Field:    [16] DIO10
//
// Toggles bit DOUT31_0.DIO10
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL11_8_DIO10                                      0x00010000U
#define GPIO_DOUTTGL11_8_DIO10_M                                    0x00010000U
#define GPIO_DOUTTGL11_8_DIO10_S                                            16U
#define GPIO_DOUTTGL11_8_DIO10_TOGGLE                               0x00010000U
#define GPIO_DOUTTGL11_8_DIO10_NOEFF                                0x00000000U

// Field:     [8] DIO9
//
// Toggles bit DOUT31_0.DIO9
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL11_8_DIO9                                       0x00000100U
#define GPIO_DOUTTGL11_8_DIO9_M                                     0x00000100U
#define GPIO_DOUTTGL11_8_DIO9_S                                              8U
#define GPIO_DOUTTGL11_8_DIO9_TOGGLE                                0x00000100U
#define GPIO_DOUTTGL11_8_DIO9_NOEFF                                 0x00000000U

// Field:     [0] DIO8
//
// Toggles bit DOUT31_0.DIO8
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL11_8_DIO8                                       0x00000001U
#define GPIO_DOUTTGL11_8_DIO8_M                                     0x00000001U
#define GPIO_DOUTTGL11_8_DIO8_S                                              0U
#define GPIO_DOUTTGL11_8_DIO8_TOGGLE                                0x00000001U
#define GPIO_DOUTTGL11_8_DIO8_NOEFF                                 0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL15_12
//
//*****************************************************************************
// Field:    [24] DIO15
//
// Toggles bit DOUT31_0.DIO15
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL15_12_DIO15                                     0x01000000U
#define GPIO_DOUTTGL15_12_DIO15_M                                   0x01000000U
#define GPIO_DOUTTGL15_12_DIO15_S                                           24U
#define GPIO_DOUTTGL15_12_DIO15_TOGGLE                              0x01000000U
#define GPIO_DOUTTGL15_12_DIO15_NOEFF                               0x00000000U

// Field:    [16] DIO14
//
// Toggles bit DOUT31_0.DIO14
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL15_12_DIO14                                     0x00010000U
#define GPIO_DOUTTGL15_12_DIO14_M                                   0x00010000U
#define GPIO_DOUTTGL15_12_DIO14_S                                           16U
#define GPIO_DOUTTGL15_12_DIO14_TOGGLE                              0x00010000U
#define GPIO_DOUTTGL15_12_DIO14_NOEFF                               0x00000000U

// Field:     [8] DIO13
//
// Toggles bit DOUT31_0.DIO13
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL15_12_DIO13                                     0x00000100U
#define GPIO_DOUTTGL15_12_DIO13_M                                   0x00000100U
#define GPIO_DOUTTGL15_12_DIO13_S                                            8U
#define GPIO_DOUTTGL15_12_DIO13_TOGGLE                              0x00000100U
#define GPIO_DOUTTGL15_12_DIO13_NOEFF                               0x00000000U

// Field:     [0] DIO12
//
// Toggles bit DOUT31_0.DIO12
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL15_12_DIO12                                     0x00000001U
#define GPIO_DOUTTGL15_12_DIO12_M                                   0x00000001U
#define GPIO_DOUTTGL15_12_DIO12_S                                            0U
#define GPIO_DOUTTGL15_12_DIO12_TOGGLE                              0x00000001U
#define GPIO_DOUTTGL15_12_DIO12_NOEFF                               0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL19_16
//
//*****************************************************************************
// Field:    [24] DIO19
//
// Toggles bit DOUT31_0.DIO19
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL19_16_DIO19                                     0x01000000U
#define GPIO_DOUTTGL19_16_DIO19_M                                   0x01000000U
#define GPIO_DOUTTGL19_16_DIO19_S                                           24U
#define GPIO_DOUTTGL19_16_DIO19_TOGGLE                              0x01000000U
#define GPIO_DOUTTGL19_16_DIO19_NOEFF                               0x00000000U

// Field:    [16] DIO18
//
// Toggles bit DOUT31_0.DIO18
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL19_16_DIO18                                     0x00010000U
#define GPIO_DOUTTGL19_16_DIO18_M                                   0x00010000U
#define GPIO_DOUTTGL19_16_DIO18_S                                           16U
#define GPIO_DOUTTGL19_16_DIO18_TOGGLE                              0x00010000U
#define GPIO_DOUTTGL19_16_DIO18_NOEFF                               0x00000000U

// Field:     [8] DIO17
//
// Toggles bit DOUT31_0.DIO17
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL19_16_DIO17                                     0x00000100U
#define GPIO_DOUTTGL19_16_DIO17_M                                   0x00000100U
#define GPIO_DOUTTGL19_16_DIO17_S                                            8U
#define GPIO_DOUTTGL19_16_DIO17_TOGGLE                              0x00000100U
#define GPIO_DOUTTGL19_16_DIO17_NOEFF                               0x00000000U

// Field:     [0] DIO16
//
// Toggles bit DOUT31_0.DIO16
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL19_16_DIO16                                     0x00000001U
#define GPIO_DOUTTGL19_16_DIO16_M                                   0x00000001U
#define GPIO_DOUTTGL19_16_DIO16_S                                            0U
#define GPIO_DOUTTGL19_16_DIO16_TOGGLE                              0x00000001U
#define GPIO_DOUTTGL19_16_DIO16_NOEFF                               0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL23_20
//
//*****************************************************************************
// Field:    [24] DIO23
//
// Toggles bit DOUT31_0.DIO23
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL23_20_DIO23                                     0x01000000U
#define GPIO_DOUTTGL23_20_DIO23_M                                   0x01000000U
#define GPIO_DOUTTGL23_20_DIO23_S                                           24U
#define GPIO_DOUTTGL23_20_DIO23_TOGGLE                              0x01000000U
#define GPIO_DOUTTGL23_20_DIO23_NOEFF                               0x00000000U

// Field:    [16] DIO22
//
// Toggles bit DOUT31_0.DIO22
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL23_20_DIO22                                     0x00010000U
#define GPIO_DOUTTGL23_20_DIO22_M                                   0x00010000U
#define GPIO_DOUTTGL23_20_DIO22_S                                           16U
#define GPIO_DOUTTGL23_20_DIO22_TOGGLE                              0x00010000U
#define GPIO_DOUTTGL23_20_DIO22_NOEFF                               0x00000000U

// Field:     [8] DIO21
//
// Toggles bit DOUT31_0.DIO21
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL23_20_DIO21                                     0x00000100U
#define GPIO_DOUTTGL23_20_DIO21_M                                   0x00000100U
#define GPIO_DOUTTGL23_20_DIO21_S                                            8U
#define GPIO_DOUTTGL23_20_DIO21_TOGGLE                              0x00000100U
#define GPIO_DOUTTGL23_20_DIO21_NOEFF                               0x00000000U

// Field:     [0] DIO20
//
// Toggles bit DOUT31_0.DIO20
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL23_20_DIO20                                     0x00000001U
#define GPIO_DOUTTGL23_20_DIO20_M                                   0x00000001U
#define GPIO_DOUTTGL23_20_DIO20_S                                            0U
#define GPIO_DOUTTGL23_20_DIO20_TOGGLE                              0x00000001U
#define GPIO_DOUTTGL23_20_DIO20_NOEFF                               0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOUTTGL27_24
//
//*****************************************************************************
// Field:     [8] DIO25
//
// Toggles bit DOUT31_0.DIO25
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL27_24_DIO25                                     0x00000100U
#define GPIO_DOUTTGL27_24_DIO25_M                                   0x00000100U
#define GPIO_DOUTTGL27_24_DIO25_S                                            8U
#define GPIO_DOUTTGL27_24_DIO25_TOGGLE                              0x00000100U
#define GPIO_DOUTTGL27_24_DIO25_NOEFF                               0x00000000U

// Field:     [0] DIO24
//
// Toggles bit DOUT31_0.DIO24
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOUTTGL27_24_DIO24                                     0x00000001U
#define GPIO_DOUTTGL27_24_DIO24_M                                   0x00000001U
#define GPIO_DOUTTGL27_24_DIO24_S                                            0U
#define GPIO_DOUTTGL27_24_DIO24_TOGGLE                              0x00000001U
#define GPIO_DOUTTGL27_24_DIO24_NOEFF                               0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE3_0
//
//*****************************************************************************
// Field:    [24] DIO3
//
// Data output enable for DIO3
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE3_0_DIO3                                            0x01000000U
#define GPIO_DOE3_0_DIO3_M                                          0x01000000U
#define GPIO_DOE3_0_DIO3_S                                                  24U
#define GPIO_DOE3_0_DIO3_EN                                         0x01000000U
#define GPIO_DOE3_0_DIO3_DIS                                        0x00000000U

// Field:    [16] DIO2
//
// Data output enable for DIO2
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE3_0_DIO2                                            0x00010000U
#define GPIO_DOE3_0_DIO2_M                                          0x00010000U
#define GPIO_DOE3_0_DIO2_S                                                  16U
#define GPIO_DOE3_0_DIO2_EN                                         0x00010000U
#define GPIO_DOE3_0_DIO2_DIS                                        0x00000000U

// Field:     [8] DIO1
//
// Data output enable for DIO1
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE3_0_DIO1                                            0x00000100U
#define GPIO_DOE3_0_DIO1_M                                          0x00000100U
#define GPIO_DOE3_0_DIO1_S                                                   8U
#define GPIO_DOE3_0_DIO1_EN                                         0x00000100U
#define GPIO_DOE3_0_DIO1_DIS                                        0x00000000U

// Field:     [0] DIO0
//
// Data output enable for DIO0
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE3_0_DIO0                                            0x00000001U
#define GPIO_DOE3_0_DIO0_M                                          0x00000001U
#define GPIO_DOE3_0_DIO0_S                                                   0U
#define GPIO_DOE3_0_DIO0_EN                                         0x00000001U
#define GPIO_DOE3_0_DIO0_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE7_4
//
//*****************************************************************************
// Field:    [24] DIO7
//
// Data output enable for DIO7
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE7_4_DIO7                                            0x01000000U
#define GPIO_DOE7_4_DIO7_M                                          0x01000000U
#define GPIO_DOE7_4_DIO7_S                                                  24U
#define GPIO_DOE7_4_DIO7_EN                                         0x01000000U
#define GPIO_DOE7_4_DIO7_DIS                                        0x00000000U

// Field:    [16] DIO6
//
// Data output enable for DIO6
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE7_4_DIO6                                            0x00010000U
#define GPIO_DOE7_4_DIO6_M                                          0x00010000U
#define GPIO_DOE7_4_DIO6_S                                                  16U
#define GPIO_DOE7_4_DIO6_EN                                         0x00010000U
#define GPIO_DOE7_4_DIO6_DIS                                        0x00000000U

// Field:     [8] DIO5
//
// Data output enable for DIO5
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE7_4_DIO5                                            0x00000100U
#define GPIO_DOE7_4_DIO5_M                                          0x00000100U
#define GPIO_DOE7_4_DIO5_S                                                   8U
#define GPIO_DOE7_4_DIO5_EN                                         0x00000100U
#define GPIO_DOE7_4_DIO5_DIS                                        0x00000000U

// Field:     [0] DIO4
//
// Data output enable for DIO4
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE7_4_DIO4                                            0x00000001U
#define GPIO_DOE7_4_DIO4_M                                          0x00000001U
#define GPIO_DOE7_4_DIO4_S                                                   0U
#define GPIO_DOE7_4_DIO4_EN                                         0x00000001U
#define GPIO_DOE7_4_DIO4_DIS                                        0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE11_8
//
//*****************************************************************************
// Field:    [24] DIO11
//
// Data output enable for DIO11
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE11_8_DIO11                                          0x01000000U
#define GPIO_DOE11_8_DIO11_M                                        0x01000000U
#define GPIO_DOE11_8_DIO11_S                                                24U
#define GPIO_DOE11_8_DIO11_EN                                       0x01000000U
#define GPIO_DOE11_8_DIO11_DIS                                      0x00000000U

// Field:    [16] DIO10
//
// Data output enable for DIO10
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE11_8_DIO10                                          0x00010000U
#define GPIO_DOE11_8_DIO10_M                                        0x00010000U
#define GPIO_DOE11_8_DIO10_S                                                16U
#define GPIO_DOE11_8_DIO10_EN                                       0x00010000U
#define GPIO_DOE11_8_DIO10_DIS                                      0x00000000U

// Field:     [8] DIO9
//
// Data output enable for DIO9
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE11_8_DIO9                                           0x00000100U
#define GPIO_DOE11_8_DIO9_M                                         0x00000100U
#define GPIO_DOE11_8_DIO9_S                                                  8U
#define GPIO_DOE11_8_DIO9_EN                                        0x00000100U
#define GPIO_DOE11_8_DIO9_DIS                                       0x00000000U

// Field:     [0] DIO8
//
// Data output enable for DIO8
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE11_8_DIO8                                           0x00000001U
#define GPIO_DOE11_8_DIO8_M                                         0x00000001U
#define GPIO_DOE11_8_DIO8_S                                                  0U
#define GPIO_DOE11_8_DIO8_EN                                        0x00000001U
#define GPIO_DOE11_8_DIO8_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE15_12
//
//*****************************************************************************
// Field:    [24] DIO15
//
// Data output enable for DIO15
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE15_12_DIO15                                         0x01000000U
#define GPIO_DOE15_12_DIO15_M                                       0x01000000U
#define GPIO_DOE15_12_DIO15_S                                               24U
#define GPIO_DOE15_12_DIO15_EN                                      0x01000000U
#define GPIO_DOE15_12_DIO15_DIS                                     0x00000000U

// Field:    [16] DIO14
//
// Data output enable for DIO14
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE15_12_DIO14                                         0x00010000U
#define GPIO_DOE15_12_DIO14_M                                       0x00010000U
#define GPIO_DOE15_12_DIO14_S                                               16U
#define GPIO_DOE15_12_DIO14_EN                                      0x00010000U
#define GPIO_DOE15_12_DIO14_DIS                                     0x00000000U

// Field:     [8] DIO13
//
// Data output enable for DIO13
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE15_12_DIO13                                         0x00000100U
#define GPIO_DOE15_12_DIO13_M                                       0x00000100U
#define GPIO_DOE15_12_DIO13_S                                                8U
#define GPIO_DOE15_12_DIO13_EN                                      0x00000100U
#define GPIO_DOE15_12_DIO13_DIS                                     0x00000000U

// Field:     [0] DIO12
//
// Data output enable for DIO12
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE15_12_DIO12                                         0x00000001U
#define GPIO_DOE15_12_DIO12_M                                       0x00000001U
#define GPIO_DOE15_12_DIO12_S                                                0U
#define GPIO_DOE15_12_DIO12_EN                                      0x00000001U
#define GPIO_DOE15_12_DIO12_DIS                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE19_16
//
//*****************************************************************************
// Field:    [24] DIO19
//
// Data output enable for DIO19
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE19_16_DIO19                                         0x01000000U
#define GPIO_DOE19_16_DIO19_M                                       0x01000000U
#define GPIO_DOE19_16_DIO19_S                                               24U
#define GPIO_DOE19_16_DIO19_EN                                      0x01000000U
#define GPIO_DOE19_16_DIO19_DIS                                     0x00000000U

// Field:    [16] DIO18
//
// Data output enable for DIO18
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE19_16_DIO18                                         0x00010000U
#define GPIO_DOE19_16_DIO18_M                                       0x00010000U
#define GPIO_DOE19_16_DIO18_S                                               16U
#define GPIO_DOE19_16_DIO18_EN                                      0x00010000U
#define GPIO_DOE19_16_DIO18_DIS                                     0x00000000U

// Field:     [8] DIO17
//
// Data output enable for DIO17
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE19_16_DIO17                                         0x00000100U
#define GPIO_DOE19_16_DIO17_M                                       0x00000100U
#define GPIO_DOE19_16_DIO17_S                                                8U
#define GPIO_DOE19_16_DIO17_EN                                      0x00000100U
#define GPIO_DOE19_16_DIO17_DIS                                     0x00000000U

// Field:     [0] DIO16
//
// Data output enable for DIO16
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE19_16_DIO16                                         0x00000001U
#define GPIO_DOE19_16_DIO16_M                                       0x00000001U
#define GPIO_DOE19_16_DIO16_S                                                0U
#define GPIO_DOE19_16_DIO16_EN                                      0x00000001U
#define GPIO_DOE19_16_DIO16_DIS                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE23_20
//
//*****************************************************************************
// Field:    [24] DIO23
//
// Data output enable for DIO23
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE23_20_DIO23                                         0x01000000U
#define GPIO_DOE23_20_DIO23_M                                       0x01000000U
#define GPIO_DOE23_20_DIO23_S                                               24U
#define GPIO_DOE23_20_DIO23_EN                                      0x01000000U
#define GPIO_DOE23_20_DIO23_DIS                                     0x00000000U

// Field:    [16] DIO22
//
// Data output enable for DIO22
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE23_20_DIO22                                         0x00010000U
#define GPIO_DOE23_20_DIO22_M                                       0x00010000U
#define GPIO_DOE23_20_DIO22_S                                               16U
#define GPIO_DOE23_20_DIO22_EN                                      0x00010000U
#define GPIO_DOE23_20_DIO22_DIS                                     0x00000000U

// Field:     [8] DIO21
//
// Data output enable for DIO21
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE23_20_DIO21                                         0x00000100U
#define GPIO_DOE23_20_DIO21_M                                       0x00000100U
#define GPIO_DOE23_20_DIO21_S                                                8U
#define GPIO_DOE23_20_DIO21_EN                                      0x00000100U
#define GPIO_DOE23_20_DIO21_DIS                                     0x00000000U

// Field:     [0] DIO20
//
// Data output enable for DIO20
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE23_20_DIO20                                         0x00000001U
#define GPIO_DOE23_20_DIO20_M                                       0x00000001U
#define GPIO_DOE23_20_DIO20_S                                                0U
#define GPIO_DOE23_20_DIO20_EN                                      0x00000001U
#define GPIO_DOE23_20_DIO20_DIS                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE27_24
//
//*****************************************************************************
// Field:     [8] DIO25
//
// Data output enable for DIO25
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE27_24_DIO25                                         0x00000100U
#define GPIO_DOE27_24_DIO25_M                                       0x00000100U
#define GPIO_DOE27_24_DIO25_S                                                8U
#define GPIO_DOE27_24_DIO25_EN                                      0x00000100U
#define GPIO_DOE27_24_DIO25_DIS                                     0x00000000U

// Field:     [0] DIO24
//
// Data output enable for DIO24
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE27_24_DIO24                                         0x00000001U
#define GPIO_DOE27_24_DIO24_M                                       0x00000001U
#define GPIO_DOE27_24_DIO24_S                                                0U
#define GPIO_DOE27_24_DIO24_EN                                      0x00000001U
#define GPIO_DOE27_24_DIO24_DIS                                     0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOE31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Data output enable for DIO25
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO25                                          0x02000000U
#define GPIO_DOE31_0_DIO25_M                                        0x02000000U
#define GPIO_DOE31_0_DIO25_S                                                25U
#define GPIO_DOE31_0_DIO25_EN                                       0x02000000U
#define GPIO_DOE31_0_DIO25_DIS                                      0x00000000U

// Field:    [24] DIO24
//
// Data output enable for DIO24
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO24                                          0x01000000U
#define GPIO_DOE31_0_DIO24_M                                        0x01000000U
#define GPIO_DOE31_0_DIO24_S                                                24U
#define GPIO_DOE31_0_DIO24_EN                                       0x01000000U
#define GPIO_DOE31_0_DIO24_DIS                                      0x00000000U

// Field:    [23] DIO23
//
// Data output enable for DIO23
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO23                                          0x00800000U
#define GPIO_DOE31_0_DIO23_M                                        0x00800000U
#define GPIO_DOE31_0_DIO23_S                                                23U
#define GPIO_DOE31_0_DIO23_EN                                       0x00800000U
#define GPIO_DOE31_0_DIO23_DIS                                      0x00000000U

// Field:    [22] DIO22
//
// Data output enable for DIO22
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO22                                          0x00400000U
#define GPIO_DOE31_0_DIO22_M                                        0x00400000U
#define GPIO_DOE31_0_DIO22_S                                                22U
#define GPIO_DOE31_0_DIO22_EN                                       0x00400000U
#define GPIO_DOE31_0_DIO22_DIS                                      0x00000000U

// Field:    [21] DIO21
//
// Data output enable for DIO21
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO21                                          0x00200000U
#define GPIO_DOE31_0_DIO21_M                                        0x00200000U
#define GPIO_DOE31_0_DIO21_S                                                21U
#define GPIO_DOE31_0_DIO21_EN                                       0x00200000U
#define GPIO_DOE31_0_DIO21_DIS                                      0x00000000U

// Field:    [20] DIO20
//
// Data output enable for DIO20
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO20                                          0x00100000U
#define GPIO_DOE31_0_DIO20_M                                        0x00100000U
#define GPIO_DOE31_0_DIO20_S                                                20U
#define GPIO_DOE31_0_DIO20_EN                                       0x00100000U
#define GPIO_DOE31_0_DIO20_DIS                                      0x00000000U

// Field:    [19] DIO19
//
// Data output enable for DIO19
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO19                                          0x00080000U
#define GPIO_DOE31_0_DIO19_M                                        0x00080000U
#define GPIO_DOE31_0_DIO19_S                                                19U
#define GPIO_DOE31_0_DIO19_EN                                       0x00080000U
#define GPIO_DOE31_0_DIO19_DIS                                      0x00000000U

// Field:    [18] DIO18
//
// Data output enable for DIO18
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO18                                          0x00040000U
#define GPIO_DOE31_0_DIO18_M                                        0x00040000U
#define GPIO_DOE31_0_DIO18_S                                                18U
#define GPIO_DOE31_0_DIO18_EN                                       0x00040000U
#define GPIO_DOE31_0_DIO18_DIS                                      0x00000000U

// Field:    [17] DIO17
//
// Data output enable for DIO17
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO17                                          0x00020000U
#define GPIO_DOE31_0_DIO17_M                                        0x00020000U
#define GPIO_DOE31_0_DIO17_S                                                17U
#define GPIO_DOE31_0_DIO17_EN                                       0x00020000U
#define GPIO_DOE31_0_DIO17_DIS                                      0x00000000U

// Field:    [16] DIO16
//
// Data output enable for DIO16
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO16                                          0x00010000U
#define GPIO_DOE31_0_DIO16_M                                        0x00010000U
#define GPIO_DOE31_0_DIO16_S                                                16U
#define GPIO_DOE31_0_DIO16_EN                                       0x00010000U
#define GPIO_DOE31_0_DIO16_DIS                                      0x00000000U

// Field:    [15] DIO15
//
// Data output enable for DIO15
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO15                                          0x00008000U
#define GPIO_DOE31_0_DIO15_M                                        0x00008000U
#define GPIO_DOE31_0_DIO15_S                                                15U
#define GPIO_DOE31_0_DIO15_EN                                       0x00008000U
#define GPIO_DOE31_0_DIO15_DIS                                      0x00000000U

// Field:    [14] DIO14
//
// Data output enable for DIO14
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO14                                          0x00004000U
#define GPIO_DOE31_0_DIO14_M                                        0x00004000U
#define GPIO_DOE31_0_DIO14_S                                                14U
#define GPIO_DOE31_0_DIO14_EN                                       0x00004000U
#define GPIO_DOE31_0_DIO14_DIS                                      0x00000000U

// Field:    [13] DIO13
//
// Data output enable for DIO13
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO13                                          0x00002000U
#define GPIO_DOE31_0_DIO13_M                                        0x00002000U
#define GPIO_DOE31_0_DIO13_S                                                13U
#define GPIO_DOE31_0_DIO13_EN                                       0x00002000U
#define GPIO_DOE31_0_DIO13_DIS                                      0x00000000U

// Field:    [12] DIO12
//
// Data output enable for DIO12
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO12                                          0x00001000U
#define GPIO_DOE31_0_DIO12_M                                        0x00001000U
#define GPIO_DOE31_0_DIO12_S                                                12U
#define GPIO_DOE31_0_DIO12_EN                                       0x00001000U
#define GPIO_DOE31_0_DIO12_DIS                                      0x00000000U

// Field:    [11] DIO11
//
// Data output enable for DIO11
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO11                                          0x00000800U
#define GPIO_DOE31_0_DIO11_M                                        0x00000800U
#define GPIO_DOE31_0_DIO11_S                                                11U
#define GPIO_DOE31_0_DIO11_EN                                       0x00000800U
#define GPIO_DOE31_0_DIO11_DIS                                      0x00000000U

// Field:    [10] DIO10
//
// Data output enable for DIO10
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO10                                          0x00000400U
#define GPIO_DOE31_0_DIO10_M                                        0x00000400U
#define GPIO_DOE31_0_DIO10_S                                                10U
#define GPIO_DOE31_0_DIO10_EN                                       0x00000400U
#define GPIO_DOE31_0_DIO10_DIS                                      0x00000000U

// Field:     [9] DIO9
//
// Data output enable for DIO9
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO9                                           0x00000200U
#define GPIO_DOE31_0_DIO9_M                                         0x00000200U
#define GPIO_DOE31_0_DIO9_S                                                  9U
#define GPIO_DOE31_0_DIO9_EN                                        0x00000200U
#define GPIO_DOE31_0_DIO9_DIS                                       0x00000000U

// Field:     [8] DIO8
//
// Data output enable for DIO8
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO8                                           0x00000100U
#define GPIO_DOE31_0_DIO8_M                                         0x00000100U
#define GPIO_DOE31_0_DIO8_S                                                  8U
#define GPIO_DOE31_0_DIO8_EN                                        0x00000100U
#define GPIO_DOE31_0_DIO8_DIS                                       0x00000000U

// Field:     [7] DIO7
//
// Data output enable for DIO7
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO7                                           0x00000080U
#define GPIO_DOE31_0_DIO7_M                                         0x00000080U
#define GPIO_DOE31_0_DIO7_S                                                  7U
#define GPIO_DOE31_0_DIO7_EN                                        0x00000080U
#define GPIO_DOE31_0_DIO7_DIS                                       0x00000000U

// Field:     [6] DIO6
//
// Data output enable for DIO6
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO6                                           0x00000040U
#define GPIO_DOE31_0_DIO6_M                                         0x00000040U
#define GPIO_DOE31_0_DIO6_S                                                  6U
#define GPIO_DOE31_0_DIO6_EN                                        0x00000040U
#define GPIO_DOE31_0_DIO6_DIS                                       0x00000000U

// Field:     [5] DIO5
//
// Data output enable for DIO5
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO5                                           0x00000020U
#define GPIO_DOE31_0_DIO5_M                                         0x00000020U
#define GPIO_DOE31_0_DIO5_S                                                  5U
#define GPIO_DOE31_0_DIO5_EN                                        0x00000020U
#define GPIO_DOE31_0_DIO5_DIS                                       0x00000000U

// Field:     [4] DIO4
//
// Data output enable for DIO4
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO4                                           0x00000010U
#define GPIO_DOE31_0_DIO4_M                                         0x00000010U
#define GPIO_DOE31_0_DIO4_S                                                  4U
#define GPIO_DOE31_0_DIO4_EN                                        0x00000010U
#define GPIO_DOE31_0_DIO4_DIS                                       0x00000000U

// Field:     [3] DIO3
//
// Data output enable for DIO3
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO3                                           0x00000008U
#define GPIO_DOE31_0_DIO3_M                                         0x00000008U
#define GPIO_DOE31_0_DIO3_S                                                  3U
#define GPIO_DOE31_0_DIO3_EN                                        0x00000008U
#define GPIO_DOE31_0_DIO3_DIS                                       0x00000000U

// Field:     [2] DIO2
//
// Data output enable for DIO2
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO2                                           0x00000004U
#define GPIO_DOE31_0_DIO2_M                                         0x00000004U
#define GPIO_DOE31_0_DIO2_S                                                  2U
#define GPIO_DOE31_0_DIO2_EN                                        0x00000004U
#define GPIO_DOE31_0_DIO2_DIS                                       0x00000000U

// Field:     [1] DIO1
//
// Data output enable for DIO1
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO1                                           0x00000002U
#define GPIO_DOE31_0_DIO1_M                                         0x00000002U
#define GPIO_DOE31_0_DIO1_S                                                  1U
#define GPIO_DOE31_0_DIO1_EN                                        0x00000002U
#define GPIO_DOE31_0_DIO1_DIS                                       0x00000000U

// Field:     [0] DIO0
//
// Data output enable for DIO0
// ENUMs:
// EN                       Output enabled
// DIS                      Output disabled
#define GPIO_DOE31_0_DIO0                                           0x00000001U
#define GPIO_DOE31_0_DIO0_M                                         0x00000001U
#define GPIO_DOE31_0_DIO0_S                                                  0U
#define GPIO_DOE31_0_DIO0_EN                                        0x00000001U
#define GPIO_DOE31_0_DIO0_DIS                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOESET31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Sets bit DOE31_0.DIO25
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO25                                       0x02000000U
#define GPIO_DOESET31_0_DIO25_M                                     0x02000000U
#define GPIO_DOESET31_0_DIO25_S                                             25U
#define GPIO_DOESET31_0_DIO25_SET                                   0x02000000U
#define GPIO_DOESET31_0_DIO25_NOEFF                                 0x00000000U

// Field:    [24] DIO24
//
// Sets bit DOE31_0.DIO24
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO24                                       0x01000000U
#define GPIO_DOESET31_0_DIO24_M                                     0x01000000U
#define GPIO_DOESET31_0_DIO24_S                                             24U
#define GPIO_DOESET31_0_DIO24_SET                                   0x01000000U
#define GPIO_DOESET31_0_DIO24_NOEFF                                 0x00000000U

// Field:    [23] DIO23
//
// Sets bit DOE31_0.DIO23
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO23                                       0x00800000U
#define GPIO_DOESET31_0_DIO23_M                                     0x00800000U
#define GPIO_DOESET31_0_DIO23_S                                             23U
#define GPIO_DOESET31_0_DIO23_SET                                   0x00800000U
#define GPIO_DOESET31_0_DIO23_NOEFF                                 0x00000000U

// Field:    [22] DIO22
//
// Sets bit DOE31_0.DIO22
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO22                                       0x00400000U
#define GPIO_DOESET31_0_DIO22_M                                     0x00400000U
#define GPIO_DOESET31_0_DIO22_S                                             22U
#define GPIO_DOESET31_0_DIO22_SET                                   0x00400000U
#define GPIO_DOESET31_0_DIO22_NOEFF                                 0x00000000U

// Field:    [21] DIO21
//
// Sets bit DOE31_0.DIO21
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO21                                       0x00200000U
#define GPIO_DOESET31_0_DIO21_M                                     0x00200000U
#define GPIO_DOESET31_0_DIO21_S                                             21U
#define GPIO_DOESET31_0_DIO21_SET                                   0x00200000U
#define GPIO_DOESET31_0_DIO21_NOEFF                                 0x00000000U

// Field:    [20] DIO20
//
// Sets bit DOE31_0.DIO20
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO20                                       0x00100000U
#define GPIO_DOESET31_0_DIO20_M                                     0x00100000U
#define GPIO_DOESET31_0_DIO20_S                                             20U
#define GPIO_DOESET31_0_DIO20_SET                                   0x00100000U
#define GPIO_DOESET31_0_DIO20_NOEFF                                 0x00000000U

// Field:    [19] DIO19
//
// Sets bit DOE31_0.DIO19
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO19                                       0x00080000U
#define GPIO_DOESET31_0_DIO19_M                                     0x00080000U
#define GPIO_DOESET31_0_DIO19_S                                             19U
#define GPIO_DOESET31_0_DIO19_SET                                   0x00080000U
#define GPIO_DOESET31_0_DIO19_NOEFF                                 0x00000000U

// Field:    [18] DIO18
//
// Sets bit DOE31_0.DIO18
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO18                                       0x00040000U
#define GPIO_DOESET31_0_DIO18_M                                     0x00040000U
#define GPIO_DOESET31_0_DIO18_S                                             18U
#define GPIO_DOESET31_0_DIO18_SET                                   0x00040000U
#define GPIO_DOESET31_0_DIO18_NOEFF                                 0x00000000U

// Field:    [17] DIO17
//
// Sets bit DOE31_0.DIO17
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO17                                       0x00020000U
#define GPIO_DOESET31_0_DIO17_M                                     0x00020000U
#define GPIO_DOESET31_0_DIO17_S                                             17U
#define GPIO_DOESET31_0_DIO17_SET                                   0x00020000U
#define GPIO_DOESET31_0_DIO17_NOEFF                                 0x00000000U

// Field:    [16] DIO16
//
// Sets bit DOE31_0.DIO16
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO16                                       0x00010000U
#define GPIO_DOESET31_0_DIO16_M                                     0x00010000U
#define GPIO_DOESET31_0_DIO16_S                                             16U
#define GPIO_DOESET31_0_DIO16_SET                                   0x00010000U
#define GPIO_DOESET31_0_DIO16_NOEFF                                 0x00000000U

// Field:    [15] DIO15
//
// Sets bit DOE31_0.DIO15
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO15                                       0x00008000U
#define GPIO_DOESET31_0_DIO15_M                                     0x00008000U
#define GPIO_DOESET31_0_DIO15_S                                             15U
#define GPIO_DOESET31_0_DIO15_SET                                   0x00008000U
#define GPIO_DOESET31_0_DIO15_NOEFF                                 0x00000000U

// Field:    [14] DIO14
//
// Sets bit DOE31_0.DIO14
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO14                                       0x00004000U
#define GPIO_DOESET31_0_DIO14_M                                     0x00004000U
#define GPIO_DOESET31_0_DIO14_S                                             14U
#define GPIO_DOESET31_0_DIO14_SET                                   0x00004000U
#define GPIO_DOESET31_0_DIO14_NOEFF                                 0x00000000U

// Field:    [13] DIO13
//
// Sets bit DOE31_0.DIO13
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO13                                       0x00002000U
#define GPIO_DOESET31_0_DIO13_M                                     0x00002000U
#define GPIO_DOESET31_0_DIO13_S                                             13U
#define GPIO_DOESET31_0_DIO13_SET                                   0x00002000U
#define GPIO_DOESET31_0_DIO13_NOEFF                                 0x00000000U

// Field:    [12] DIO12
//
// Sets bit DOE31_0.DIO12
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO12                                       0x00001000U
#define GPIO_DOESET31_0_DIO12_M                                     0x00001000U
#define GPIO_DOESET31_0_DIO12_S                                             12U
#define GPIO_DOESET31_0_DIO12_SET                                   0x00001000U
#define GPIO_DOESET31_0_DIO12_NOEFF                                 0x00000000U

// Field:    [11] DIO11
//
// Sets bit DOE31_0.DIO11
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO11                                       0x00000800U
#define GPIO_DOESET31_0_DIO11_M                                     0x00000800U
#define GPIO_DOESET31_0_DIO11_S                                             11U
#define GPIO_DOESET31_0_DIO11_SET                                   0x00000800U
#define GPIO_DOESET31_0_DIO11_NOEFF                                 0x00000000U

// Field:    [10] DIO10
//
// Sets bit DOE31_0.DIO10
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO10                                       0x00000400U
#define GPIO_DOESET31_0_DIO10_M                                     0x00000400U
#define GPIO_DOESET31_0_DIO10_S                                             10U
#define GPIO_DOESET31_0_DIO10_SET                                   0x00000400U
#define GPIO_DOESET31_0_DIO10_NOEFF                                 0x00000000U

// Field:     [9] DIO9
//
// Sets bit DOE31_0.DIO9
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO9                                        0x00000200U
#define GPIO_DOESET31_0_DIO9_M                                      0x00000200U
#define GPIO_DOESET31_0_DIO9_S                                               9U
#define GPIO_DOESET31_0_DIO9_SET                                    0x00000200U
#define GPIO_DOESET31_0_DIO9_NOEFF                                  0x00000000U

// Field:     [8] DIO8
//
// Sets bit DOE31_0.DIO8
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO8                                        0x00000100U
#define GPIO_DOESET31_0_DIO8_M                                      0x00000100U
#define GPIO_DOESET31_0_DIO8_S                                               8U
#define GPIO_DOESET31_0_DIO8_SET                                    0x00000100U
#define GPIO_DOESET31_0_DIO8_NOEFF                                  0x00000000U

// Field:     [7] DIO7
//
// Sets bit DOE31_0.DIO7
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO7                                        0x00000080U
#define GPIO_DOESET31_0_DIO7_M                                      0x00000080U
#define GPIO_DOESET31_0_DIO7_S                                               7U
#define GPIO_DOESET31_0_DIO7_SET                                    0x00000080U
#define GPIO_DOESET31_0_DIO7_NOEFF                                  0x00000000U

// Field:     [6] DIO6
//
// Sets bit DOE31_0.DIO6
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO6                                        0x00000040U
#define GPIO_DOESET31_0_DIO6_M                                      0x00000040U
#define GPIO_DOESET31_0_DIO6_S                                               6U
#define GPIO_DOESET31_0_DIO6_SET                                    0x00000040U
#define GPIO_DOESET31_0_DIO6_NOEFF                                  0x00000000U

// Field:     [5] DIO5
//
// Sets bit DOE31_0.DIO5
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO5                                        0x00000020U
#define GPIO_DOESET31_0_DIO5_M                                      0x00000020U
#define GPIO_DOESET31_0_DIO5_S                                               5U
#define GPIO_DOESET31_0_DIO5_SET                                    0x00000020U
#define GPIO_DOESET31_0_DIO5_NOEFF                                  0x00000000U

// Field:     [4] DIO4
//
// Sets bit DOE31_0.DIO4
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO4                                        0x00000010U
#define GPIO_DOESET31_0_DIO4_M                                      0x00000010U
#define GPIO_DOESET31_0_DIO4_S                                               4U
#define GPIO_DOESET31_0_DIO4_SET                                    0x00000010U
#define GPIO_DOESET31_0_DIO4_NOEFF                                  0x00000000U

// Field:     [3] DIO3
//
// Sets bit DOE31_0.DIO3
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO3                                        0x00000008U
#define GPIO_DOESET31_0_DIO3_M                                      0x00000008U
#define GPIO_DOESET31_0_DIO3_S                                               3U
#define GPIO_DOESET31_0_DIO3_SET                                    0x00000008U
#define GPIO_DOESET31_0_DIO3_NOEFF                                  0x00000000U

// Field:     [2] DIO2
//
// Sets bit DOE31_0.DIO2
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO2                                        0x00000004U
#define GPIO_DOESET31_0_DIO2_M                                      0x00000004U
#define GPIO_DOESET31_0_DIO2_S                                               2U
#define GPIO_DOESET31_0_DIO2_SET                                    0x00000004U
#define GPIO_DOESET31_0_DIO2_NOEFF                                  0x00000000U

// Field:     [1] DIO1
//
// Sets bit DOE31_0.DIO1
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO1                                        0x00000002U
#define GPIO_DOESET31_0_DIO1_M                                      0x00000002U
#define GPIO_DOESET31_0_DIO1_S                                               1U
#define GPIO_DOESET31_0_DIO1_SET                                    0x00000002U
#define GPIO_DOESET31_0_DIO1_NOEFF                                  0x00000000U

// Field:     [0] DIO0
//
// Sets bit DOE31_0.DIO0
// ENUMs:
// SET
// NOEFF                    No effect
#define GPIO_DOESET31_0_DIO0                                        0x00000001U
#define GPIO_DOESET31_0_DIO0_M                                      0x00000001U
#define GPIO_DOESET31_0_DIO0_S                                               0U
#define GPIO_DOESET31_0_DIO0_SET                                    0x00000001U
#define GPIO_DOESET31_0_DIO0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOECLR31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Clears bit DOE31_0.DIO25
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO25                                       0x02000000U
#define GPIO_DOECLR31_0_DIO25_M                                     0x02000000U
#define GPIO_DOECLR31_0_DIO25_S                                             25U
#define GPIO_DOECLR31_0_DIO25_CLR                                   0x02000000U
#define GPIO_DOECLR31_0_DIO25_NOEFF                                 0x00000000U

// Field:    [24] DIO24
//
// Clears bit DOE31_0.DIO24
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO24                                       0x01000000U
#define GPIO_DOECLR31_0_DIO24_M                                     0x01000000U
#define GPIO_DOECLR31_0_DIO24_S                                             24U
#define GPIO_DOECLR31_0_DIO24_CLR                                   0x01000000U
#define GPIO_DOECLR31_0_DIO24_NOEFF                                 0x00000000U

// Field:    [23] DIO23
//
// Clears bit DOE31_0.DIO23
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO23                                       0x00800000U
#define GPIO_DOECLR31_0_DIO23_M                                     0x00800000U
#define GPIO_DOECLR31_0_DIO23_S                                             23U
#define GPIO_DOECLR31_0_DIO23_CLR                                   0x00800000U
#define GPIO_DOECLR31_0_DIO23_NOEFF                                 0x00000000U

// Field:    [22] DIO22
//
// Clears bit DOE31_0.DIO22
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO22                                       0x00400000U
#define GPIO_DOECLR31_0_DIO22_M                                     0x00400000U
#define GPIO_DOECLR31_0_DIO22_S                                             22U
#define GPIO_DOECLR31_0_DIO22_CLR                                   0x00400000U
#define GPIO_DOECLR31_0_DIO22_NOEFF                                 0x00000000U

// Field:    [21] DIO21
//
// Clears bit DOE31_0.DIO21
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO21                                       0x00200000U
#define GPIO_DOECLR31_0_DIO21_M                                     0x00200000U
#define GPIO_DOECLR31_0_DIO21_S                                             21U
#define GPIO_DOECLR31_0_DIO21_CLR                                   0x00200000U
#define GPIO_DOECLR31_0_DIO21_NOEFF                                 0x00000000U

// Field:    [20] DIO20
//
// Clears bit DOE31_0.DIO20
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO20                                       0x00100000U
#define GPIO_DOECLR31_0_DIO20_M                                     0x00100000U
#define GPIO_DOECLR31_0_DIO20_S                                             20U
#define GPIO_DOECLR31_0_DIO20_CLR                                   0x00100000U
#define GPIO_DOECLR31_0_DIO20_NOEFF                                 0x00000000U

// Field:    [19] DIO19
//
// Clears bit DOE31_0.DIO19
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO19                                       0x00080000U
#define GPIO_DOECLR31_0_DIO19_M                                     0x00080000U
#define GPIO_DOECLR31_0_DIO19_S                                             19U
#define GPIO_DOECLR31_0_DIO19_CLR                                   0x00080000U
#define GPIO_DOECLR31_0_DIO19_NOEFF                                 0x00000000U

// Field:    [18] DIO18
//
// Clears bit DOE31_0.DIO18
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO18                                       0x00040000U
#define GPIO_DOECLR31_0_DIO18_M                                     0x00040000U
#define GPIO_DOECLR31_0_DIO18_S                                             18U
#define GPIO_DOECLR31_0_DIO18_CLR                                   0x00040000U
#define GPIO_DOECLR31_0_DIO18_NOEFF                                 0x00000000U

// Field:    [17] DIO17
//
// Clears bit DOE31_0.DIO17
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO17                                       0x00020000U
#define GPIO_DOECLR31_0_DIO17_M                                     0x00020000U
#define GPIO_DOECLR31_0_DIO17_S                                             17U
#define GPIO_DOECLR31_0_DIO17_CLR                                   0x00020000U
#define GPIO_DOECLR31_0_DIO17_NOEFF                                 0x00000000U

// Field:    [16] DIO16
//
// Clears bit DOE31_0.DIO16
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO16                                       0x00010000U
#define GPIO_DOECLR31_0_DIO16_M                                     0x00010000U
#define GPIO_DOECLR31_0_DIO16_S                                             16U
#define GPIO_DOECLR31_0_DIO16_CLR                                   0x00010000U
#define GPIO_DOECLR31_0_DIO16_NOEFF                                 0x00000000U

// Field:    [15] DIO15
//
// Clears bit DOE31_0.DIO15
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO15                                       0x00008000U
#define GPIO_DOECLR31_0_DIO15_M                                     0x00008000U
#define GPIO_DOECLR31_0_DIO15_S                                             15U
#define GPIO_DOECLR31_0_DIO15_CLR                                   0x00008000U
#define GPIO_DOECLR31_0_DIO15_NOEFF                                 0x00000000U

// Field:    [14] DIO14
//
// Clears bit DOE31_0.DIO14
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO14                                       0x00004000U
#define GPIO_DOECLR31_0_DIO14_M                                     0x00004000U
#define GPIO_DOECLR31_0_DIO14_S                                             14U
#define GPIO_DOECLR31_0_DIO14_CLR                                   0x00004000U
#define GPIO_DOECLR31_0_DIO14_NOEFF                                 0x00000000U

// Field:    [13] DIO13
//
// Clears bit DOE31_0.DIO13
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO13                                       0x00002000U
#define GPIO_DOECLR31_0_DIO13_M                                     0x00002000U
#define GPIO_DOECLR31_0_DIO13_S                                             13U
#define GPIO_DOECLR31_0_DIO13_CLR                                   0x00002000U
#define GPIO_DOECLR31_0_DIO13_NOEFF                                 0x00000000U

// Field:    [12] DIO12
//
// Clears bit DOE31_0.DIO12
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO12                                       0x00001000U
#define GPIO_DOECLR31_0_DIO12_M                                     0x00001000U
#define GPIO_DOECLR31_0_DIO12_S                                             12U
#define GPIO_DOECLR31_0_DIO12_CLR                                   0x00001000U
#define GPIO_DOECLR31_0_DIO12_NOEFF                                 0x00000000U

// Field:    [11] DIO11
//
// Clears bit DOE31_0.DIO11
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO11                                       0x00000800U
#define GPIO_DOECLR31_0_DIO11_M                                     0x00000800U
#define GPIO_DOECLR31_0_DIO11_S                                             11U
#define GPIO_DOECLR31_0_DIO11_CLR                                   0x00000800U
#define GPIO_DOECLR31_0_DIO11_NOEFF                                 0x00000000U

// Field:    [10] DIO10
//
// Clears bit DOE31_0.DIO10
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO10                                       0x00000400U
#define GPIO_DOECLR31_0_DIO10_M                                     0x00000400U
#define GPIO_DOECLR31_0_DIO10_S                                             10U
#define GPIO_DOECLR31_0_DIO10_CLR                                   0x00000400U
#define GPIO_DOECLR31_0_DIO10_NOEFF                                 0x00000000U

// Field:     [9] DIO9
//
// Clears bit DOE31_0.DIO9
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO9                                        0x00000200U
#define GPIO_DOECLR31_0_DIO9_M                                      0x00000200U
#define GPIO_DOECLR31_0_DIO9_S                                               9U
#define GPIO_DOECLR31_0_DIO9_CLR                                    0x00000200U
#define GPIO_DOECLR31_0_DIO9_NOEFF                                  0x00000000U

// Field:     [8] DIO8
//
// Clears bit DOE31_0.DIO8
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO8                                        0x00000100U
#define GPIO_DOECLR31_0_DIO8_M                                      0x00000100U
#define GPIO_DOECLR31_0_DIO8_S                                               8U
#define GPIO_DOECLR31_0_DIO8_CLR                                    0x00000100U
#define GPIO_DOECLR31_0_DIO8_NOEFF                                  0x00000000U

// Field:     [7] DIO7
//
// Clears bit DOE31_0.DIO7
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO7                                        0x00000080U
#define GPIO_DOECLR31_0_DIO7_M                                      0x00000080U
#define GPIO_DOECLR31_0_DIO7_S                                               7U
#define GPIO_DOECLR31_0_DIO7_CLR                                    0x00000080U
#define GPIO_DOECLR31_0_DIO7_NOEFF                                  0x00000000U

// Field:     [6] DIO6
//
// Clears bit DOE31_0.DIO6
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO6                                        0x00000040U
#define GPIO_DOECLR31_0_DIO6_M                                      0x00000040U
#define GPIO_DOECLR31_0_DIO6_S                                               6U
#define GPIO_DOECLR31_0_DIO6_CLR                                    0x00000040U
#define GPIO_DOECLR31_0_DIO6_NOEFF                                  0x00000000U

// Field:     [5] DIO5
//
// Clears bit DOE31_0.DIO5
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO5                                        0x00000020U
#define GPIO_DOECLR31_0_DIO5_M                                      0x00000020U
#define GPIO_DOECLR31_0_DIO5_S                                               5U
#define GPIO_DOECLR31_0_DIO5_CLR                                    0x00000020U
#define GPIO_DOECLR31_0_DIO5_NOEFF                                  0x00000000U

// Field:     [4] DIO4
//
// Clears bit DOE31_0.DIO4
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO4                                        0x00000010U
#define GPIO_DOECLR31_0_DIO4_M                                      0x00000010U
#define GPIO_DOECLR31_0_DIO4_S                                               4U
#define GPIO_DOECLR31_0_DIO4_CLR                                    0x00000010U
#define GPIO_DOECLR31_0_DIO4_NOEFF                                  0x00000000U

// Field:     [3] DIO3
//
// Clears bit DOE31_0.DIO3
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO3                                        0x00000008U
#define GPIO_DOECLR31_0_DIO3_M                                      0x00000008U
#define GPIO_DOECLR31_0_DIO3_S                                               3U
#define GPIO_DOECLR31_0_DIO3_CLR                                    0x00000008U
#define GPIO_DOECLR31_0_DIO3_NOEFF                                  0x00000000U

// Field:     [2] DIO2
//
// Clears bit DOE31_0.DIO2
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO2                                        0x00000004U
#define GPIO_DOECLR31_0_DIO2_M                                      0x00000004U
#define GPIO_DOECLR31_0_DIO2_S                                               2U
#define GPIO_DOECLR31_0_DIO2_CLR                                    0x00000004U
#define GPIO_DOECLR31_0_DIO2_NOEFF                                  0x00000000U

// Field:     [1] DIO1
//
// Clears bit DOE31_0.DIO1
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO1                                        0x00000002U
#define GPIO_DOECLR31_0_DIO1_M                                      0x00000002U
#define GPIO_DOECLR31_0_DIO1_S                                               1U
#define GPIO_DOECLR31_0_DIO1_CLR                                    0x00000002U
#define GPIO_DOECLR31_0_DIO1_NOEFF                                  0x00000000U

// Field:     [0] DIO0
//
// Clears bit DOE31_0.DIO0
// ENUMs:
// CLR                      Clear
// NOEFF                    No effect
#define GPIO_DOECLR31_0_DIO0                                        0x00000001U
#define GPIO_DOECLR31_0_DIO0_M                                      0x00000001U
#define GPIO_DOECLR31_0_DIO0_S                                               0U
#define GPIO_DOECLR31_0_DIO0_CLR                                    0x00000001U
#define GPIO_DOECLR31_0_DIO0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DOETGL31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Toggles bit DOE31_0.DIO25
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO25                                       0x02000000U
#define GPIO_DOETGL31_0_DIO25_M                                     0x02000000U
#define GPIO_DOETGL31_0_DIO25_S                                             25U
#define GPIO_DOETGL31_0_DIO25_TOGGLE                                0x02000000U
#define GPIO_DOETGL31_0_DIO25_NOEFF                                 0x00000000U

// Field:    [24] DIO24
//
// Toggles bit DOE31_0.DIO24
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO24                                       0x01000000U
#define GPIO_DOETGL31_0_DIO24_M                                     0x01000000U
#define GPIO_DOETGL31_0_DIO24_S                                             24U
#define GPIO_DOETGL31_0_DIO24_TOGGLE                                0x01000000U
#define GPIO_DOETGL31_0_DIO24_NOEFF                                 0x00000000U

// Field:    [23] DIO23
//
// Toggles bit DOE31_0.DIO23
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO23                                       0x00800000U
#define GPIO_DOETGL31_0_DIO23_M                                     0x00800000U
#define GPIO_DOETGL31_0_DIO23_S                                             23U
#define GPIO_DOETGL31_0_DIO23_TOGGLE                                0x00800000U
#define GPIO_DOETGL31_0_DIO23_NOEFF                                 0x00000000U

// Field:    [22] DIO22
//
// Toggles bit DOE31_0.DIO22
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO22                                       0x00400000U
#define GPIO_DOETGL31_0_DIO22_M                                     0x00400000U
#define GPIO_DOETGL31_0_DIO22_S                                             22U
#define GPIO_DOETGL31_0_DIO22_TOGGLE                                0x00400000U
#define GPIO_DOETGL31_0_DIO22_NOEFF                                 0x00000000U

// Field:    [21] DIO21
//
// Toggles bit DOE31_0.DIO21
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO21                                       0x00200000U
#define GPIO_DOETGL31_0_DIO21_M                                     0x00200000U
#define GPIO_DOETGL31_0_DIO21_S                                             21U
#define GPIO_DOETGL31_0_DIO21_TOGGLE                                0x00200000U
#define GPIO_DOETGL31_0_DIO21_NOEFF                                 0x00000000U

// Field:    [20] DIO20
//
// Toggles bit DOE31_0.DIO20
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO20                                       0x00100000U
#define GPIO_DOETGL31_0_DIO20_M                                     0x00100000U
#define GPIO_DOETGL31_0_DIO20_S                                             20U
#define GPIO_DOETGL31_0_DIO20_TOGGLE                                0x00100000U
#define GPIO_DOETGL31_0_DIO20_NOEFF                                 0x00000000U

// Field:    [19] DIO19
//
// Toggles bit DOE31_0.DIO19
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO19                                       0x00080000U
#define GPIO_DOETGL31_0_DIO19_M                                     0x00080000U
#define GPIO_DOETGL31_0_DIO19_S                                             19U
#define GPIO_DOETGL31_0_DIO19_TOGGLE                                0x00080000U
#define GPIO_DOETGL31_0_DIO19_NOEFF                                 0x00000000U

// Field:    [18] DIO18
//
// Toggles bit DOE31_0.DIO18
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO18                                       0x00040000U
#define GPIO_DOETGL31_0_DIO18_M                                     0x00040000U
#define GPIO_DOETGL31_0_DIO18_S                                             18U
#define GPIO_DOETGL31_0_DIO18_TOGGLE                                0x00040000U
#define GPIO_DOETGL31_0_DIO18_NOEFF                                 0x00000000U

// Field:    [17] DIO17
//
// Toggles bit DOE31_0.DIO17
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO17                                       0x00020000U
#define GPIO_DOETGL31_0_DIO17_M                                     0x00020000U
#define GPIO_DOETGL31_0_DIO17_S                                             17U
#define GPIO_DOETGL31_0_DIO17_TOGGLE                                0x00020000U
#define GPIO_DOETGL31_0_DIO17_NOEFF                                 0x00000000U

// Field:    [16] DIO16
//
// Toggles bit DOE31_0.DIO16
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO16                                       0x00010000U
#define GPIO_DOETGL31_0_DIO16_M                                     0x00010000U
#define GPIO_DOETGL31_0_DIO16_S                                             16U
#define GPIO_DOETGL31_0_DIO16_TOGGLE                                0x00010000U
#define GPIO_DOETGL31_0_DIO16_NOEFF                                 0x00000000U

// Field:    [15] DIO15
//
// Toggles bit DOE31_0.DIO15
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO15                                       0x00008000U
#define GPIO_DOETGL31_0_DIO15_M                                     0x00008000U
#define GPIO_DOETGL31_0_DIO15_S                                             15U
#define GPIO_DOETGL31_0_DIO15_TOGGLE                                0x00008000U
#define GPIO_DOETGL31_0_DIO15_NOEFF                                 0x00000000U

// Field:    [14] DIO14
//
// Toggles bit DOE31_0.DIO14
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO14                                       0x00004000U
#define GPIO_DOETGL31_0_DIO14_M                                     0x00004000U
#define GPIO_DOETGL31_0_DIO14_S                                             14U
#define GPIO_DOETGL31_0_DIO14_TOGGLE                                0x00004000U
#define GPIO_DOETGL31_0_DIO14_NOEFF                                 0x00000000U

// Field:    [13] DIO13
//
// Toggles bit DOE31_0.DIO13
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO13                                       0x00002000U
#define GPIO_DOETGL31_0_DIO13_M                                     0x00002000U
#define GPIO_DOETGL31_0_DIO13_S                                             13U
#define GPIO_DOETGL31_0_DIO13_TOGGLE                                0x00002000U
#define GPIO_DOETGL31_0_DIO13_NOEFF                                 0x00000000U

// Field:    [12] DIO12
//
// Toggles bit DOE31_0.DIO12
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO12                                       0x00001000U
#define GPIO_DOETGL31_0_DIO12_M                                     0x00001000U
#define GPIO_DOETGL31_0_DIO12_S                                             12U
#define GPIO_DOETGL31_0_DIO12_TOGGLE                                0x00001000U
#define GPIO_DOETGL31_0_DIO12_NOEFF                                 0x00000000U

// Field:    [11] DIO11
//
// Toggles bit DOE31_0.DIO11
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO11                                       0x00000800U
#define GPIO_DOETGL31_0_DIO11_M                                     0x00000800U
#define GPIO_DOETGL31_0_DIO11_S                                             11U
#define GPIO_DOETGL31_0_DIO11_TOGGLE                                0x00000800U
#define GPIO_DOETGL31_0_DIO11_NOEFF                                 0x00000000U

// Field:    [10] DIO10
//
// Toggles bit DOE31_0.DIO10
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO10                                       0x00000400U
#define GPIO_DOETGL31_0_DIO10_M                                     0x00000400U
#define GPIO_DOETGL31_0_DIO10_S                                             10U
#define GPIO_DOETGL31_0_DIO10_TOGGLE                                0x00000400U
#define GPIO_DOETGL31_0_DIO10_NOEFF                                 0x00000000U

// Field:     [9] DIO9
//
// Toggles bit DOE31_0.DIO9
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO9                                        0x00000200U
#define GPIO_DOETGL31_0_DIO9_M                                      0x00000200U
#define GPIO_DOETGL31_0_DIO9_S                                               9U
#define GPIO_DOETGL31_0_DIO9_TOGGLE                                 0x00000200U
#define GPIO_DOETGL31_0_DIO9_NOEFF                                  0x00000000U

// Field:     [8] DIO8
//
// Toggles bit DOE31_0.DIO8
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO8                                        0x00000100U
#define GPIO_DOETGL31_0_DIO8_M                                      0x00000100U
#define GPIO_DOETGL31_0_DIO8_S                                               8U
#define GPIO_DOETGL31_0_DIO8_TOGGLE                                 0x00000100U
#define GPIO_DOETGL31_0_DIO8_NOEFF                                  0x00000000U

// Field:     [7] DIO7
//
// Toggles bit DOE31_0.DIO7
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO7                                        0x00000080U
#define GPIO_DOETGL31_0_DIO7_M                                      0x00000080U
#define GPIO_DOETGL31_0_DIO7_S                                               7U
#define GPIO_DOETGL31_0_DIO7_TOGGLE                                 0x00000080U
#define GPIO_DOETGL31_0_DIO7_NOEFF                                  0x00000000U

// Field:     [6] DIO6
//
// Toggles bit DOE31_0.DIO6
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO6                                        0x00000040U
#define GPIO_DOETGL31_0_DIO6_M                                      0x00000040U
#define GPIO_DOETGL31_0_DIO6_S                                               6U
#define GPIO_DOETGL31_0_DIO6_TOGGLE                                 0x00000040U
#define GPIO_DOETGL31_0_DIO6_NOEFF                                  0x00000000U

// Field:     [5] DIO5
//
// Toggles bit DOE31_0.DIO5
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO5                                        0x00000020U
#define GPIO_DOETGL31_0_DIO5_M                                      0x00000020U
#define GPIO_DOETGL31_0_DIO5_S                                               5U
#define GPIO_DOETGL31_0_DIO5_TOGGLE                                 0x00000020U
#define GPIO_DOETGL31_0_DIO5_NOEFF                                  0x00000000U

// Field:     [4] DIO4
//
// Toggles bit DOE31_0.DIO4
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO4                                        0x00000010U
#define GPIO_DOETGL31_0_DIO4_M                                      0x00000010U
#define GPIO_DOETGL31_0_DIO4_S                                               4U
#define GPIO_DOETGL31_0_DIO4_TOGGLE                                 0x00000010U
#define GPIO_DOETGL31_0_DIO4_NOEFF                                  0x00000000U

// Field:     [3] DIO3
//
// Toggles bit DOE31_0.DIO3
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO3                                        0x00000008U
#define GPIO_DOETGL31_0_DIO3_M                                      0x00000008U
#define GPIO_DOETGL31_0_DIO3_S                                               3U
#define GPIO_DOETGL31_0_DIO3_TOGGLE                                 0x00000008U
#define GPIO_DOETGL31_0_DIO3_NOEFF                                  0x00000000U

// Field:     [2] DIO2
//
// Toggles bit DOE31_0.DIO2
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO2                                        0x00000004U
#define GPIO_DOETGL31_0_DIO2_M                                      0x00000004U
#define GPIO_DOETGL31_0_DIO2_S                                               2U
#define GPIO_DOETGL31_0_DIO2_TOGGLE                                 0x00000004U
#define GPIO_DOETGL31_0_DIO2_NOEFF                                  0x00000000U

// Field:     [1] DIO1
//
// Toggles bit DOE31_0.DIO1
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO1                                        0x00000002U
#define GPIO_DOETGL31_0_DIO1_M                                      0x00000002U
#define GPIO_DOETGL31_0_DIO1_S                                               1U
#define GPIO_DOETGL31_0_DIO1_TOGGLE                                 0x00000002U
#define GPIO_DOETGL31_0_DIO1_NOEFF                                  0x00000000U

// Field:     [0] DIO0
//
// Toggles bit DOE31_0.DIO0
// ENUMs:
// TOGGLE                   Toggle
// NOEFF                    No effect
#define GPIO_DOETGL31_0_DIO0                                        0x00000001U
#define GPIO_DOETGL31_0_DIO0_M                                      0x00000001U
#define GPIO_DOETGL31_0_DIO0_S                                               0U
#define GPIO_DOETGL31_0_DIO0_TOGGLE                                 0x00000001U
#define GPIO_DOETGL31_0_DIO0_NOEFF                                  0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN3_0
//
//*****************************************************************************
// Field:    [24] DIO3
//
// Data input from DIO3
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN3_0_DIO3                                            0x01000000U
#define GPIO_DIN3_0_DIO3_M                                          0x01000000U
#define GPIO_DIN3_0_DIO3_S                                                  24U
#define GPIO_DIN3_0_DIO3_ONE                                        0x01000000U
#define GPIO_DIN3_0_DIO3_ZERO                                       0x00000000U

// Field:    [16] DIO2
//
// Data input from DIO2
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN3_0_DIO2                                            0x00010000U
#define GPIO_DIN3_0_DIO2_M                                          0x00010000U
#define GPIO_DIN3_0_DIO2_S                                                  16U
#define GPIO_DIN3_0_DIO2_ONE                                        0x00010000U
#define GPIO_DIN3_0_DIO2_ZERO                                       0x00000000U

// Field:     [8] DIO1
//
// Data input from DIO1
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN3_0_DIO1                                            0x00000100U
#define GPIO_DIN3_0_DIO1_M                                          0x00000100U
#define GPIO_DIN3_0_DIO1_S                                                   8U
#define GPIO_DIN3_0_DIO1_ONE                                        0x00000100U
#define GPIO_DIN3_0_DIO1_ZERO                                       0x00000000U

// Field:     [0] DIO0
//
// Data input from DIO0
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN3_0_DIO0                                            0x00000001U
#define GPIO_DIN3_0_DIO0_M                                          0x00000001U
#define GPIO_DIN3_0_DIO0_S                                                   0U
#define GPIO_DIN3_0_DIO0_ONE                                        0x00000001U
#define GPIO_DIN3_0_DIO0_ZERO                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN7_4
//
//*****************************************************************************
// Field:    [24] DIO7
//
// Data input from DIO7
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN7_4_DIO7                                            0x01000000U
#define GPIO_DIN7_4_DIO7_M                                          0x01000000U
#define GPIO_DIN7_4_DIO7_S                                                  24U
#define GPIO_DIN7_4_DIO7_ONE                                        0x01000000U
#define GPIO_DIN7_4_DIO7_ZERO                                       0x00000000U

// Field:    [16] DIO6
//
// Data input from DIO6
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN7_4_DIO6                                            0x00010000U
#define GPIO_DIN7_4_DIO6_M                                          0x00010000U
#define GPIO_DIN7_4_DIO6_S                                                  16U
#define GPIO_DIN7_4_DIO6_ONE                                        0x00010000U
#define GPIO_DIN7_4_DIO6_ZERO                                       0x00000000U

// Field:     [8] DIO5
//
// Data input from DIO5
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN7_4_DIO5                                            0x00000100U
#define GPIO_DIN7_4_DIO5_M                                          0x00000100U
#define GPIO_DIN7_4_DIO5_S                                                   8U
#define GPIO_DIN7_4_DIO5_ONE                                        0x00000100U
#define GPIO_DIN7_4_DIO5_ZERO                                       0x00000000U

// Field:     [0] DIO4
//
// Data input from DIO4
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN7_4_DIO4                                            0x00000001U
#define GPIO_DIN7_4_DIO4_M                                          0x00000001U
#define GPIO_DIN7_4_DIO4_S                                                   0U
#define GPIO_DIN7_4_DIO4_ONE                                        0x00000001U
#define GPIO_DIN7_4_DIO4_ZERO                                       0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN11_8
//
//*****************************************************************************
// Field:    [24] DIO11
//
// Data input from DIO11
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN11_8_DIO11                                          0x01000000U
#define GPIO_DIN11_8_DIO11_M                                        0x01000000U
#define GPIO_DIN11_8_DIO11_S                                                24U
#define GPIO_DIN11_8_DIO11_ONE                                      0x01000000U
#define GPIO_DIN11_8_DIO11_ZERO                                     0x00000000U

// Field:    [16] DIO10
//
// Data input from DIO10
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN11_8_DIO10                                          0x00010000U
#define GPIO_DIN11_8_DIO10_M                                        0x00010000U
#define GPIO_DIN11_8_DIO10_S                                                16U
#define GPIO_DIN11_8_DIO10_ONE                                      0x00010000U
#define GPIO_DIN11_8_DIO10_ZERO                                     0x00000000U

// Field:     [8] DIO9
//
// Data input from DIO9
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN11_8_DIO9                                           0x00000100U
#define GPIO_DIN11_8_DIO9_M                                         0x00000100U
#define GPIO_DIN11_8_DIO9_S                                                  8U
#define GPIO_DIN11_8_DIO9_ONE                                       0x00000100U
#define GPIO_DIN11_8_DIO9_ZERO                                      0x00000000U

// Field:     [0] DIO8
//
// Data input from DIO8
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN11_8_DIO8                                           0x00000001U
#define GPIO_DIN11_8_DIO8_M                                         0x00000001U
#define GPIO_DIN11_8_DIO8_S                                                  0U
#define GPIO_DIN11_8_DIO8_ONE                                       0x00000001U
#define GPIO_DIN11_8_DIO8_ZERO                                      0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN15_12
//
//*****************************************************************************
// Field:    [24] DIO15
//
// Data input from DIO15
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN15_12_DIO15                                         0x01000000U
#define GPIO_DIN15_12_DIO15_M                                       0x01000000U
#define GPIO_DIN15_12_DIO15_S                                               24U
#define GPIO_DIN15_12_DIO15_ONE                                     0x01000000U
#define GPIO_DIN15_12_DIO15_ZERO                                    0x00000000U

// Field:    [16] DIO14
//
// Data input from DIO14
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN15_12_DIO14                                         0x00010000U
#define GPIO_DIN15_12_DIO14_M                                       0x00010000U
#define GPIO_DIN15_12_DIO14_S                                               16U
#define GPIO_DIN15_12_DIO14_ONE                                     0x00010000U
#define GPIO_DIN15_12_DIO14_ZERO                                    0x00000000U

// Field:     [8] DIO13
//
// Data input from DIO13
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN15_12_DIO13                                         0x00000100U
#define GPIO_DIN15_12_DIO13_M                                       0x00000100U
#define GPIO_DIN15_12_DIO13_S                                                8U
#define GPIO_DIN15_12_DIO13_ONE                                     0x00000100U
#define GPIO_DIN15_12_DIO13_ZERO                                    0x00000000U

// Field:     [0] DIO12
//
// Data input from DIO12
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN15_12_DIO12                                         0x00000001U
#define GPIO_DIN15_12_DIO12_M                                       0x00000001U
#define GPIO_DIN15_12_DIO12_S                                                0U
#define GPIO_DIN15_12_DIO12_ONE                                     0x00000001U
#define GPIO_DIN15_12_DIO12_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN19_16
//
//*****************************************************************************
// Field:    [24] DIO19
//
// Data input from DIO19
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN19_16_DIO19                                         0x01000000U
#define GPIO_DIN19_16_DIO19_M                                       0x01000000U
#define GPIO_DIN19_16_DIO19_S                                               24U
#define GPIO_DIN19_16_DIO19_ONE                                     0x01000000U
#define GPIO_DIN19_16_DIO19_ZERO                                    0x00000000U

// Field:    [16] DIO18
//
// Data input from DIO18
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN19_16_DIO18                                         0x00010000U
#define GPIO_DIN19_16_DIO18_M                                       0x00010000U
#define GPIO_DIN19_16_DIO18_S                                               16U
#define GPIO_DIN19_16_DIO18_ONE                                     0x00010000U
#define GPIO_DIN19_16_DIO18_ZERO                                    0x00000000U

// Field:     [8] DIO17
//
// Data input from DIO17
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN19_16_DIO17                                         0x00000100U
#define GPIO_DIN19_16_DIO17_M                                       0x00000100U
#define GPIO_DIN19_16_DIO17_S                                                8U
#define GPIO_DIN19_16_DIO17_ONE                                     0x00000100U
#define GPIO_DIN19_16_DIO17_ZERO                                    0x00000000U

// Field:     [0] DIO16
//
// Data input from DIO16
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN19_16_DIO16                                         0x00000001U
#define GPIO_DIN19_16_DIO16_M                                       0x00000001U
#define GPIO_DIN19_16_DIO16_S                                                0U
#define GPIO_DIN19_16_DIO16_ONE                                     0x00000001U
#define GPIO_DIN19_16_DIO16_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN23_20
//
//*****************************************************************************
// Field:    [24] DIO23
//
// Data input from DIO23
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN23_20_DIO23                                         0x01000000U
#define GPIO_DIN23_20_DIO23_M                                       0x01000000U
#define GPIO_DIN23_20_DIO23_S                                               24U
#define GPIO_DIN23_20_DIO23_ONE                                     0x01000000U
#define GPIO_DIN23_20_DIO23_ZERO                                    0x00000000U

// Field:    [16] DIO22
//
// Data input from DIO22
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN23_20_DIO22                                         0x00010000U
#define GPIO_DIN23_20_DIO22_M                                       0x00010000U
#define GPIO_DIN23_20_DIO22_S                                               16U
#define GPIO_DIN23_20_DIO22_ONE                                     0x00010000U
#define GPIO_DIN23_20_DIO22_ZERO                                    0x00000000U

// Field:     [8] DIO21
//
// Data input from DIO21
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN23_20_DIO21                                         0x00000100U
#define GPIO_DIN23_20_DIO21_M                                       0x00000100U
#define GPIO_DIN23_20_DIO21_S                                                8U
#define GPIO_DIN23_20_DIO21_ONE                                     0x00000100U
#define GPIO_DIN23_20_DIO21_ZERO                                    0x00000000U

// Field:     [0] DIO20
//
// Data input from DIO20
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN23_20_DIO20                                         0x00000001U
#define GPIO_DIN23_20_DIO20_M                                       0x00000001U
#define GPIO_DIN23_20_DIO20_S                                                0U
#define GPIO_DIN23_20_DIO20_ONE                                     0x00000001U
#define GPIO_DIN23_20_DIO20_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN27_24
//
//*****************************************************************************
// Field:     [8] DIO25
//
// Data input from DIO25
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN27_24_DIO25                                         0x00000100U
#define GPIO_DIN27_24_DIO25_M                                       0x00000100U
#define GPIO_DIN27_24_DIO25_S                                                8U
#define GPIO_DIN27_24_DIO25_ONE                                     0x00000100U
#define GPIO_DIN27_24_DIO25_ZERO                                    0x00000000U

// Field:     [0] DIO24
//
// Data input from DIO24
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN27_24_DIO24                                         0x00000001U
#define GPIO_DIN27_24_DIO24_M                                       0x00000001U
#define GPIO_DIN27_24_DIO24_S                                                0U
#define GPIO_DIN27_24_DIO24_ONE                                     0x00000001U
#define GPIO_DIN27_24_DIO24_ZERO                                    0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_DIN31_0
//
//*****************************************************************************
// Field:    [25] DIO25
//
// Data input from DIO25
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO25                                          0x02000000U
#define GPIO_DIN31_0_DIO25_M                                        0x02000000U
#define GPIO_DIN31_0_DIO25_S                                                25U
#define GPIO_DIN31_0_DIO25_ONE                                      0x02000000U
#define GPIO_DIN31_0_DIO25_ZERO                                     0x00000000U

// Field:    [24] DIO24
//
// Data input from DIO24
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO24                                          0x01000000U
#define GPIO_DIN31_0_DIO24_M                                        0x01000000U
#define GPIO_DIN31_0_DIO24_S                                                24U
#define GPIO_DIN31_0_DIO24_ONE                                      0x01000000U
#define GPIO_DIN31_0_DIO24_ZERO                                     0x00000000U

// Field:    [23] DIO23
//
// Data input from DIO23
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO23                                          0x00800000U
#define GPIO_DIN31_0_DIO23_M                                        0x00800000U
#define GPIO_DIN31_0_DIO23_S                                                23U
#define GPIO_DIN31_0_DIO23_ONE                                      0x00800000U
#define GPIO_DIN31_0_DIO23_ZERO                                     0x00000000U

// Field:    [22] DIO22
//
// Data input from DIO22
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO22                                          0x00400000U
#define GPIO_DIN31_0_DIO22_M                                        0x00400000U
#define GPIO_DIN31_0_DIO22_S                                                22U
#define GPIO_DIN31_0_DIO22_ONE                                      0x00400000U
#define GPIO_DIN31_0_DIO22_ZERO                                     0x00000000U

// Field:    [21] DIO21
//
// Data input from DIO21
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO21                                          0x00200000U
#define GPIO_DIN31_0_DIO21_M                                        0x00200000U
#define GPIO_DIN31_0_DIO21_S                                                21U
#define GPIO_DIN31_0_DIO21_ONE                                      0x00200000U
#define GPIO_DIN31_0_DIO21_ZERO                                     0x00000000U

// Field:    [20] DIO20
//
// Data input from DIO20
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO20                                          0x00100000U
#define GPIO_DIN31_0_DIO20_M                                        0x00100000U
#define GPIO_DIN31_0_DIO20_S                                                20U
#define GPIO_DIN31_0_DIO20_ONE                                      0x00100000U
#define GPIO_DIN31_0_DIO20_ZERO                                     0x00000000U

// Field:    [19] DIO19
//
// Data input from DIO19
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO19                                          0x00080000U
#define GPIO_DIN31_0_DIO19_M                                        0x00080000U
#define GPIO_DIN31_0_DIO19_S                                                19U
#define GPIO_DIN31_0_DIO19_ONE                                      0x00080000U
#define GPIO_DIN31_0_DIO19_ZERO                                     0x00000000U

// Field:    [18] DIO18
//
// Data input from DIO18
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO18                                          0x00040000U
#define GPIO_DIN31_0_DIO18_M                                        0x00040000U
#define GPIO_DIN31_0_DIO18_S                                                18U
#define GPIO_DIN31_0_DIO18_ONE                                      0x00040000U
#define GPIO_DIN31_0_DIO18_ZERO                                     0x00000000U

// Field:    [17] DIO17
//
// Data input from DIO17
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO17                                          0x00020000U
#define GPIO_DIN31_0_DIO17_M                                        0x00020000U
#define GPIO_DIN31_0_DIO17_S                                                17U
#define GPIO_DIN31_0_DIO17_ONE                                      0x00020000U
#define GPIO_DIN31_0_DIO17_ZERO                                     0x00000000U

// Field:    [16] DIO16
//
// Data input from DIO16
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO16                                          0x00010000U
#define GPIO_DIN31_0_DIO16_M                                        0x00010000U
#define GPIO_DIN31_0_DIO16_S                                                16U
#define GPIO_DIN31_0_DIO16_ONE                                      0x00010000U
#define GPIO_DIN31_0_DIO16_ZERO                                     0x00000000U

// Field:    [15] DIO15
//
// Data input from DIO15
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO15                                          0x00008000U
#define GPIO_DIN31_0_DIO15_M                                        0x00008000U
#define GPIO_DIN31_0_DIO15_S                                                15U
#define GPIO_DIN31_0_DIO15_ONE                                      0x00008000U
#define GPIO_DIN31_0_DIO15_ZERO                                     0x00000000U

// Field:    [14] DIO14
//
// Data input from DIO14
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO14                                          0x00004000U
#define GPIO_DIN31_0_DIO14_M                                        0x00004000U
#define GPIO_DIN31_0_DIO14_S                                                14U
#define GPIO_DIN31_0_DIO14_ONE                                      0x00004000U
#define GPIO_DIN31_0_DIO14_ZERO                                     0x00000000U

// Field:    [13] DIO13
//
// Data input from DIO13
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO13                                          0x00002000U
#define GPIO_DIN31_0_DIO13_M                                        0x00002000U
#define GPIO_DIN31_0_DIO13_S                                                13U
#define GPIO_DIN31_0_DIO13_ONE                                      0x00002000U
#define GPIO_DIN31_0_DIO13_ZERO                                     0x00000000U

// Field:    [12] DIO12
//
// Data input from DIO12
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO12                                          0x00001000U
#define GPIO_DIN31_0_DIO12_M                                        0x00001000U
#define GPIO_DIN31_0_DIO12_S                                                12U
#define GPIO_DIN31_0_DIO12_ONE                                      0x00001000U
#define GPIO_DIN31_0_DIO12_ZERO                                     0x00000000U

// Field:    [11] DIO11
//
// Data input from DIO11
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO11                                          0x00000800U
#define GPIO_DIN31_0_DIO11_M                                        0x00000800U
#define GPIO_DIN31_0_DIO11_S                                                11U
#define GPIO_DIN31_0_DIO11_ONE                                      0x00000800U
#define GPIO_DIN31_0_DIO11_ZERO                                     0x00000000U

// Field:    [10] DIO10
//
// Data input from DIO10
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO10                                          0x00000400U
#define GPIO_DIN31_0_DIO10_M                                        0x00000400U
#define GPIO_DIN31_0_DIO10_S                                                10U
#define GPIO_DIN31_0_DIO10_ONE                                      0x00000400U
#define GPIO_DIN31_0_DIO10_ZERO                                     0x00000000U

// Field:     [9] DIO9
//
// Data input from DIO9
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO9                                           0x00000200U
#define GPIO_DIN31_0_DIO9_M                                         0x00000200U
#define GPIO_DIN31_0_DIO9_S                                                  9U
#define GPIO_DIN31_0_DIO9_ONE                                       0x00000200U
#define GPIO_DIN31_0_DIO9_ZERO                                      0x00000000U

// Field:     [8] DIO8
//
// Data input from DIO8
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO8                                           0x00000100U
#define GPIO_DIN31_0_DIO8_M                                         0x00000100U
#define GPIO_DIN31_0_DIO8_S                                                  8U
#define GPIO_DIN31_0_DIO8_ONE                                       0x00000100U
#define GPIO_DIN31_0_DIO8_ZERO                                      0x00000000U

// Field:     [7] DIO7
//
// Data input from DIO7
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO7                                           0x00000080U
#define GPIO_DIN31_0_DIO7_M                                         0x00000080U
#define GPIO_DIN31_0_DIO7_S                                                  7U
#define GPIO_DIN31_0_DIO7_ONE                                       0x00000080U
#define GPIO_DIN31_0_DIO7_ZERO                                      0x00000000U

// Field:     [6] DIO6
//
// Data input from DIO6
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO6                                           0x00000040U
#define GPIO_DIN31_0_DIO6_M                                         0x00000040U
#define GPIO_DIN31_0_DIO6_S                                                  6U
#define GPIO_DIN31_0_DIO6_ONE                                       0x00000040U
#define GPIO_DIN31_0_DIO6_ZERO                                      0x00000000U

// Field:     [5] DIO5
//
// Data input from DIO5
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO5                                           0x00000020U
#define GPIO_DIN31_0_DIO5_M                                         0x00000020U
#define GPIO_DIN31_0_DIO5_S                                                  5U
#define GPIO_DIN31_0_DIO5_ONE                                       0x00000020U
#define GPIO_DIN31_0_DIO5_ZERO                                      0x00000000U

// Field:     [4] DIO4
//
// Data input from DIO4
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO4                                           0x00000010U
#define GPIO_DIN31_0_DIO4_M                                         0x00000010U
#define GPIO_DIN31_0_DIO4_S                                                  4U
#define GPIO_DIN31_0_DIO4_ONE                                       0x00000010U
#define GPIO_DIN31_0_DIO4_ZERO                                      0x00000000U

// Field:     [3] DIO3
//
// Data input from DIO3
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO3                                           0x00000008U
#define GPIO_DIN31_0_DIO3_M                                         0x00000008U
#define GPIO_DIN31_0_DIO3_S                                                  3U
#define GPIO_DIN31_0_DIO3_ONE                                       0x00000008U
#define GPIO_DIN31_0_DIO3_ZERO                                      0x00000000U

// Field:     [2] DIO2
//
// Data input from DIO2
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO2                                           0x00000004U
#define GPIO_DIN31_0_DIO2_M                                         0x00000004U
#define GPIO_DIN31_0_DIO2_S                                                  2U
#define GPIO_DIN31_0_DIO2_ONE                                       0x00000004U
#define GPIO_DIN31_0_DIO2_ZERO                                      0x00000000U

// Field:     [1] DIO1
//
// Data input from DIO1
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO1                                           0x00000002U
#define GPIO_DIN31_0_DIO1_M                                         0x00000002U
#define GPIO_DIN31_0_DIO1_S                                                  1U
#define GPIO_DIN31_0_DIO1_ONE                                       0x00000002U
#define GPIO_DIN31_0_DIO1_ZERO                                      0x00000000U

// Field:     [0] DIO0
//
// Data input from DIO0
// ENUMs:
// ONE                      Input value is 1
// ZERO                     Input value is 0
#define GPIO_DIN31_0_DIO0                                           0x00000001U
#define GPIO_DIN31_0_DIO0_M                                         0x00000001U
#define GPIO_DIN31_0_DIO0_S                                                  0U
#define GPIO_DIN31_0_DIO0_ONE                                       0x00000001U
#define GPIO_DIN31_0_DIO0_ZERO                                      0x00000000U

//*****************************************************************************
//
// Register: GPIO_O_EVTCFG
//
//*****************************************************************************
// Field:     [8] EVTEN
//
// Enables GPIO to publish edge qualified selected DIO event on SVT event
// fabric.
// Design note: The edge detector flop is cleared automatically for the
// selected DIO once the event is published.
// ENUMs:
// EN                       Enable
// DIS                      Disable
#define GPIO_EVTCFG_EVTEN                                           0x00000100U
#define GPIO_EVTCFG_EVTEN_M                                         0x00000100U
#define GPIO_EVTCFG_EVTEN_S                                                  8U
#define GPIO_EVTCFG_EVTEN_EN                                        0x00000100U
#define GPIO_EVTCFG_EVTEN_DIS                                       0x00000000U

// Field:   [5:0] DIOSEL
//
// This is used to select DIO for event generation. For example, DIOSEL = 0x0
// selects DIO0 and DIOSEL = 0x8 selects DIO8.
// ENUMs:
// MAXIMUM                  Maximum value
// MINIMUM                  Minimum value
#define GPIO_EVTCFG_DIOSEL_W                                                 6U
#define GPIO_EVTCFG_DIOSEL_M                                        0x0000003FU
#define GPIO_EVTCFG_DIOSEL_S                                                 0U
#define GPIO_EVTCFG_DIOSEL_MAXIMUM                                  0x0000003FU
#define GPIO_EVTCFG_DIOSEL_MINIMUM                                  0x00000000U


#endif // __GPIO__
