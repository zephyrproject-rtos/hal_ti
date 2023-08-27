/******************************************************************************
*  Filename:       hw_clkctl_h
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

#ifndef __HW_CLKCTL_H__
#define __HW_CLKCTL_H__

//*****************************************************************************
//
// This section defines the register offsets of
// CLKCTL component
//
//*****************************************************************************
// Description Register.
#define CLKCTL_O_DESC                                               0x00000000U

// Extended Description Register 0.
#define CLKCTL_O_DESCEX0                                            0x00000004U

// Extended Description Register 1.
#define CLKCTL_O_DESCEX1                                            0x00000008U

// Clock Configuration Register 0.
#define CLKCTL_O_CLKCFG0                                            0x0000000CU

// Clock Configuration Register 1.
#define CLKCTL_O_CLKCFG1                                            0x00000010U

// Clock Enable Set Register 0.
#define CLKCTL_O_CLKENSET0                                          0x00000014U

// Clock Enable Set Register 1.
#define CLKCTL_O_CLKENSET1                                          0x00000018U

// Clock Enable Clear Register 0.
#define CLKCTL_O_CLKENCLR0                                          0x00000020U

// Clock Enable Clear Register 1.
#define CLKCTL_O_CLKENCLR1                                          0x00000024U

// Internal. Only to be used through TI provided API.
#define CLKCTL_O_STBYPTR                                            0x0000003CU

// IDLE Configuration Register.
#define CLKCTL_O_IDLECFG                                            0x00000048U

//*****************************************************************************
//
// Register: CLKCTL_O_DESC
//
//*****************************************************************************
// Field: [31:16] MODID
//
// Module identifier used to uniquely identify this IP.
#define CLKCTL_DESC_MODID_W                                                 16U
#define CLKCTL_DESC_MODID_M                                         0xFFFF0000U
#define CLKCTL_DESC_MODID_S                                                 16U

// Field: [15:12] STDIPOFF
//
// Standard IP MMR block offset. Standard IP MMRs are the set of from
// aggregated IRQ registers till DTB.
//
// 0: Standard IP MMRs do not exist
// 0x1-0xF: Standard IP MMRs begin at offset of (64*STDIPOFF from the base IP
// address)
#define CLKCTL_DESC_STDIPOFF_W                                               4U
#define CLKCTL_DESC_STDIPOFF_M                                      0x0000F000U
#define CLKCTL_DESC_STDIPOFF_S                                              12U

// Field:  [11:8] INSTIDX
//
// IP Instance ID number. If multiple instances of IP exist in the device, this
// field can identify the instance number (0-15).
#define CLKCTL_DESC_INSTIDX_W                                                4U
#define CLKCTL_DESC_INSTIDX_M                                       0x00000F00U
#define CLKCTL_DESC_INSTIDX_S                                                8U

// Field:   [7:4] MAJREV
//
// Major revision of IP 0-15
#define CLKCTL_DESC_MAJREV_W                                                 4U
#define CLKCTL_DESC_MAJREV_M                                        0x000000F0U
#define CLKCTL_DESC_MAJREV_S                                                 4U

// Field:   [3:0] MINREV
//
// Minor revision of IP 0-15.
#define CLKCTL_DESC_MINREV_W                                                 4U
#define CLKCTL_DESC_MINREV_M                                        0x0000000FU
#define CLKCTL_DESC_MINREV_S                                                 0U

//*****************************************************************************
//
// Register: CLKCTL_O_DESCEX0
//
//*****************************************************************************
// Field:    [30] LGPT3
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LGPT3                                        0x40000000U
#define CLKCTL_DESCEX0_LGPT3_M                                      0x40000000U
#define CLKCTL_DESCEX0_LGPT3_S                                              30U
#define CLKCTL_DESCEX0_LGPT3_IP_AVAIL                               0x40000000U
#define CLKCTL_DESCEX0_LGPT3_IP_UNAVAIL                             0x00000000U

// Field:    [29] LGPT2
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LGPT2                                        0x20000000U
#define CLKCTL_DESCEX0_LGPT2_M                                      0x20000000U
#define CLKCTL_DESCEX0_LGPT2_S                                              29U
#define CLKCTL_DESCEX0_LGPT2_IP_AVAIL                               0x20000000U
#define CLKCTL_DESCEX0_LGPT2_IP_UNAVAIL                             0x00000000U

// Field:    [28] LGPT1
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LGPT1                                        0x10000000U
#define CLKCTL_DESCEX0_LGPT1_M                                      0x10000000U
#define CLKCTL_DESCEX0_LGPT1_S                                              28U
#define CLKCTL_DESCEX0_LGPT1_IP_AVAIL                               0x10000000U
#define CLKCTL_DESCEX0_LGPT1_IP_UNAVAIL                             0x00000000U

// Field:    [27] LGPT0
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LGPT0                                        0x08000000U
#define CLKCTL_DESCEX0_LGPT0_M                                      0x08000000U
#define CLKCTL_DESCEX0_LGPT0_S                                              27U
#define CLKCTL_DESCEX0_LGPT0_IP_AVAIL                               0x08000000U
#define CLKCTL_DESCEX0_LGPT0_IP_UNAVAIL                             0x00000000U

// Field:    [17] DMA
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_DMA                                          0x00020000U
#define CLKCTL_DESCEX0_DMA_M                                        0x00020000U
#define CLKCTL_DESCEX0_DMA_S                                                17U
#define CLKCTL_DESCEX0_DMA_IP_AVAIL                                 0x00020000U
#define CLKCTL_DESCEX0_DMA_IP_UNAVAIL                               0x00000000U

// Field:    [16] LAES
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LAES                                         0x00010000U
#define CLKCTL_DESCEX0_LAES_M                                       0x00010000U
#define CLKCTL_DESCEX0_LAES_S                                               16U
#define CLKCTL_DESCEX0_LAES_IP_AVAIL                                0x00010000U
#define CLKCTL_DESCEX0_LAES_IP_UNAVAIL                              0x00000000U

// Field:    [14] ADC0
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_ADC0                                         0x00004000U
#define CLKCTL_DESCEX0_ADC0_M                                       0x00004000U
#define CLKCTL_DESCEX0_ADC0_S                                               14U
#define CLKCTL_DESCEX0_ADC0_IP_AVAIL                                0x00004000U
#define CLKCTL_DESCEX0_ADC0_IP_UNAVAIL                              0x00000000U

// Field:    [10] SPI0
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_SPI0                                         0x00000400U
#define CLKCTL_DESCEX0_SPI0_M                                       0x00000400U
#define CLKCTL_DESCEX0_SPI0_S                                               10U
#define CLKCTL_DESCEX0_SPI0_IP_AVAIL                                0x00000400U
#define CLKCTL_DESCEX0_SPI0_IP_UNAVAIL                              0x00000000U

// Field:     [6] I2C0
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_I2C0                                         0x00000040U
#define CLKCTL_DESCEX0_I2C0_M                                       0x00000040U
#define CLKCTL_DESCEX0_I2C0_S                                                6U
#define CLKCTL_DESCEX0_I2C0_IP_AVAIL                                0x00000040U
#define CLKCTL_DESCEX0_I2C0_IP_UNAVAIL                              0x00000000U

// Field:     [2] UART0
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_UART0                                        0x00000004U
#define CLKCTL_DESCEX0_UART0_M                                      0x00000004U
#define CLKCTL_DESCEX0_UART0_S                                               2U
#define CLKCTL_DESCEX0_UART0_IP_AVAIL                               0x00000004U
#define CLKCTL_DESCEX0_UART0_IP_UNAVAIL                             0x00000000U

// Field:     [1] LRFD
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_LRFD                                         0x00000002U
#define CLKCTL_DESCEX0_LRFD_M                                       0x00000002U
#define CLKCTL_DESCEX0_LRFD_S                                                1U
#define CLKCTL_DESCEX0_LRFD_IP_AVAIL                                0x00000002U
#define CLKCTL_DESCEX0_LRFD_IP_UNAVAIL                              0x00000000U

// Field:     [0] GPIO
//
// IP status on device
// ENUMs:
// IP_AVAIL                 IP is available
// IP_UNAVAIL               IP is unavailable
#define CLKCTL_DESCEX0_GPIO                                         0x00000001U
#define CLKCTL_DESCEX0_GPIO_M                                       0x00000001U
#define CLKCTL_DESCEX0_GPIO_S                                                0U
#define CLKCTL_DESCEX0_GPIO_IP_AVAIL                                0x00000001U
#define CLKCTL_DESCEX0_GPIO_IP_UNAVAIL                              0x00000000U

//*****************************************************************************
//
// Register: CLKCTL_O_DESCEX1
//
//*****************************************************************************
// Field: [31:30] FLASHSZ
//
// System flash availability
// ENUMs:
// SZ3                      Flash size set to level 3 (Max size)
// SZ2                      Flash size set to level 2
// SZ1                      Flash size set to level 1
// SZ0                      Flash size set to level 0 (Min size)
#define CLKCTL_DESCEX1_FLASHSZ_W                                             2U
#define CLKCTL_DESCEX1_FLASHSZ_M                                    0xC0000000U
#define CLKCTL_DESCEX1_FLASHSZ_S                                            30U
#define CLKCTL_DESCEX1_FLASHSZ_SZ3                                  0xC0000000U
#define CLKCTL_DESCEX1_FLASHSZ_SZ2                                  0x80000000U
#define CLKCTL_DESCEX1_FLASHSZ_SZ1                                  0x40000000U
#define CLKCTL_DESCEX1_FLASHSZ_SZ0                                  0x00000000U

// Field: [29:28] SRAMSZ
//
// System SRAM availability
// ENUMs:
// SZ3                      SRAM size set to level 3 (Max size)
// SZ2                      SRAM size set to level 2
// SZ1                      SRAM size set to level 1
// SZ0                      SRAM size set to level 0 (Min size)
#define CLKCTL_DESCEX1_SRAMSZ_W                                              2U
#define CLKCTL_DESCEX1_SRAMSZ_M                                     0x30000000U
#define CLKCTL_DESCEX1_SRAMSZ_S                                             28U
#define CLKCTL_DESCEX1_SRAMSZ_SZ3                                   0x30000000U
#define CLKCTL_DESCEX1_SRAMSZ_SZ2                                   0x20000000U
#define CLKCTL_DESCEX1_SRAMSZ_SZ1                                   0x10000000U
#define CLKCTL_DESCEX1_SRAMSZ_SZ0                                   0x00000000U

// Field:  [15:8] ROPT
//
// System radio feature availability
// ENUMs:
// MAX                      All features available
#define CLKCTL_DESCEX1_ROPT_W                                                8U
#define CLKCTL_DESCEX1_ROPT_M                                       0x0000FF00U
#define CLKCTL_DESCEX1_ROPT_S                                                8U
#define CLKCTL_DESCEX1_ROPT_MAX                                     0x0000FF00U

//*****************************************************************************
//
// Register: CLKCTL_O_CLKCFG0
//
//*****************************************************************************
// Field:    [30] LGPT3
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LGPT3                                        0x40000000U
#define CLKCTL_CLKCFG0_LGPT3_M                                      0x40000000U
#define CLKCTL_CLKCFG0_LGPT3_S                                              30U
#define CLKCTL_CLKCFG0_LGPT3_CLK_EN                                 0x40000000U
#define CLKCTL_CLKCFG0_LGPT3_CLK_DIS                                0x00000000U

// Field:    [29] LGPT2
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LGPT2                                        0x20000000U
#define CLKCTL_CLKCFG0_LGPT2_M                                      0x20000000U
#define CLKCTL_CLKCFG0_LGPT2_S                                              29U
#define CLKCTL_CLKCFG0_LGPT2_CLK_EN                                 0x20000000U
#define CLKCTL_CLKCFG0_LGPT2_CLK_DIS                                0x00000000U

// Field:    [28] LGPT1
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LGPT1                                        0x10000000U
#define CLKCTL_CLKCFG0_LGPT1_M                                      0x10000000U
#define CLKCTL_CLKCFG0_LGPT1_S                                              28U
#define CLKCTL_CLKCFG0_LGPT1_CLK_EN                                 0x10000000U
#define CLKCTL_CLKCFG0_LGPT1_CLK_DIS                                0x00000000U

// Field:    [27] LGPT0
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LGPT0                                        0x08000000U
#define CLKCTL_CLKCFG0_LGPT0_M                                      0x08000000U
#define CLKCTL_CLKCFG0_LGPT0_S                                              27U
#define CLKCTL_CLKCFG0_LGPT0_CLK_EN                                 0x08000000U
#define CLKCTL_CLKCFG0_LGPT0_CLK_DIS                                0x00000000U

// Field:    [17] DMA
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_DMA                                          0x00020000U
#define CLKCTL_CLKCFG0_DMA_M                                        0x00020000U
#define CLKCTL_CLKCFG0_DMA_S                                                17U
#define CLKCTL_CLKCFG0_DMA_CLK_EN                                   0x00020000U
#define CLKCTL_CLKCFG0_DMA_CLK_DIS                                  0x00000000U

// Field:    [16] LAES
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LAES                                         0x00010000U
#define CLKCTL_CLKCFG0_LAES_M                                       0x00010000U
#define CLKCTL_CLKCFG0_LAES_S                                               16U
#define CLKCTL_CLKCFG0_LAES_CLK_EN                                  0x00010000U
#define CLKCTL_CLKCFG0_LAES_CLK_DIS                                 0x00000000U

// Field:    [14] ADC0
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_ADC0                                         0x00004000U
#define CLKCTL_CLKCFG0_ADC0_M                                       0x00004000U
#define CLKCTL_CLKCFG0_ADC0_S                                               14U
#define CLKCTL_CLKCFG0_ADC0_CLK_EN                                  0x00004000U
#define CLKCTL_CLKCFG0_ADC0_CLK_DIS                                 0x00000000U

// Field:    [10] SPI0
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_SPI0                                         0x00000400U
#define CLKCTL_CLKCFG0_SPI0_M                                       0x00000400U
#define CLKCTL_CLKCFG0_SPI0_S                                               10U
#define CLKCTL_CLKCFG0_SPI0_CLK_EN                                  0x00000400U
#define CLKCTL_CLKCFG0_SPI0_CLK_DIS                                 0x00000000U

// Field:     [6] I2C0
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_I2C0                                         0x00000040U
#define CLKCTL_CLKCFG0_I2C0_M                                       0x00000040U
#define CLKCTL_CLKCFG0_I2C0_S                                                6U
#define CLKCTL_CLKCFG0_I2C0_CLK_EN                                  0x00000040U
#define CLKCTL_CLKCFG0_I2C0_CLK_DIS                                 0x00000000U

// Field:     [2] UART0
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_UART0                                        0x00000004U
#define CLKCTL_CLKCFG0_UART0_M                                      0x00000004U
#define CLKCTL_CLKCFG0_UART0_S                                               2U
#define CLKCTL_CLKCFG0_UART0_CLK_EN                                 0x00000004U
#define CLKCTL_CLKCFG0_UART0_CLK_DIS                                0x00000000U

// Field:     [1] LRFD
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_LRFD                                         0x00000002U
#define CLKCTL_CLKCFG0_LRFD_M                                       0x00000002U
#define CLKCTL_CLKCFG0_LRFD_S                                                1U
#define CLKCTL_CLKCFG0_LRFD_CLK_EN                                  0x00000002U
#define CLKCTL_CLKCFG0_LRFD_CLK_DIS                                 0x00000000U

// Field:     [0] GPIO
//
// IP clock configuration
// ENUMs:
// CLK_EN                   Clock is enabled
// CLK_DIS                  Clock is disabled
#define CLKCTL_CLKCFG0_GPIO                                         0x00000001U
#define CLKCTL_CLKCFG0_GPIO_M                                       0x00000001U
#define CLKCTL_CLKCFG0_GPIO_S                                                0U
#define CLKCTL_CLKCFG0_GPIO_CLK_EN                                  0x00000001U
#define CLKCTL_CLKCFG0_GPIO_CLK_DIS                                 0x00000000U

//*****************************************************************************
//
// Register: CLKCTL_O_CLKCFG1
//
//*****************************************************************************
//*****************************************************************************
//
// Register: CLKCTL_O_CLKENSET0
//
//*****************************************************************************
// Field:    [30] LGPT3
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LGPT3                                      0x40000000U
#define CLKCTL_CLKENSET0_LGPT3_M                                    0x40000000U
#define CLKCTL_CLKENSET0_LGPT3_S                                            30U
#define CLKCTL_CLKENSET0_LGPT3_CLK_SET                              0x40000000U
#define CLKCTL_CLKENSET0_LGPT3_CLK_UNCHGD                           0x00000000U

// Field:    [29] LGPT2
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LGPT2                                      0x20000000U
#define CLKCTL_CLKENSET0_LGPT2_M                                    0x20000000U
#define CLKCTL_CLKENSET0_LGPT2_S                                            29U
#define CLKCTL_CLKENSET0_LGPT2_CLK_SET                              0x20000000U
#define CLKCTL_CLKENSET0_LGPT2_CLK_UNCHGD                           0x00000000U

// Field:    [28] LGPT1
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LGPT1                                      0x10000000U
#define CLKCTL_CLKENSET0_LGPT1_M                                    0x10000000U
#define CLKCTL_CLKENSET0_LGPT1_S                                            28U
#define CLKCTL_CLKENSET0_LGPT1_CLK_SET                              0x10000000U
#define CLKCTL_CLKENSET0_LGPT1_CLK_UNCHGD                           0x00000000U

// Field:    [27] LGPT0
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LGPT0                                      0x08000000U
#define CLKCTL_CLKENSET0_LGPT0_M                                    0x08000000U
#define CLKCTL_CLKENSET0_LGPT0_S                                            27U
#define CLKCTL_CLKENSET0_LGPT0_CLK_SET                              0x08000000U
#define CLKCTL_CLKENSET0_LGPT0_CLK_UNCHGD                           0x00000000U

// Field:    [17] DMA
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_DMA                                        0x00020000U
#define CLKCTL_CLKENSET0_DMA_M                                      0x00020000U
#define CLKCTL_CLKENSET0_DMA_S                                              17U
#define CLKCTL_CLKENSET0_DMA_CLK_SET                                0x00020000U
#define CLKCTL_CLKENSET0_DMA_CLK_UNCHGD                             0x00000000U

// Field:    [16] LAES
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LAES                                       0x00010000U
#define CLKCTL_CLKENSET0_LAES_M                                     0x00010000U
#define CLKCTL_CLKENSET0_LAES_S                                             16U
#define CLKCTL_CLKENSET0_LAES_CLK_SET                               0x00010000U
#define CLKCTL_CLKENSET0_LAES_CLK_UNCHGD                            0x00000000U

// Field:    [14] ADC0
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_ADC0                                       0x00004000U
#define CLKCTL_CLKENSET0_ADC0_M                                     0x00004000U
#define CLKCTL_CLKENSET0_ADC0_S                                             14U
#define CLKCTL_CLKENSET0_ADC0_CLK_SET                               0x00004000U
#define CLKCTL_CLKENSET0_ADC0_CLK_UNCHGD                            0x00000000U

// Field:    [10] SPI0
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_SPI0                                       0x00000400U
#define CLKCTL_CLKENSET0_SPI0_M                                     0x00000400U
#define CLKCTL_CLKENSET0_SPI0_S                                             10U
#define CLKCTL_CLKENSET0_SPI0_CLK_SET                               0x00000400U
#define CLKCTL_CLKENSET0_SPI0_CLK_UNCHGD                            0x00000000U

// Field:     [6] I2C0
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_I2C0                                       0x00000040U
#define CLKCTL_CLKENSET0_I2C0_M                                     0x00000040U
#define CLKCTL_CLKENSET0_I2C0_S                                              6U
#define CLKCTL_CLKENSET0_I2C0_CLK_SET                               0x00000040U
#define CLKCTL_CLKENSET0_I2C0_CLK_UNCHGD                            0x00000000U

// Field:     [2] UART0
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_UART0                                      0x00000004U
#define CLKCTL_CLKENSET0_UART0_M                                    0x00000004U
#define CLKCTL_CLKENSET0_UART0_S                                             2U
#define CLKCTL_CLKENSET0_UART0_CLK_SET                              0x00000004U
#define CLKCTL_CLKENSET0_UART0_CLK_UNCHGD                           0x00000000U

// Field:     [1] LRFD
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_LRFD                                       0x00000002U
#define CLKCTL_CLKENSET0_LRFD_M                                     0x00000002U
#define CLKCTL_CLKENSET0_LRFD_S                                              1U
#define CLKCTL_CLKENSET0_LRFD_CLK_SET                               0x00000002U
#define CLKCTL_CLKENSET0_LRFD_CLK_UNCHGD                            0x00000000U

// Field:     [0] GPIO
//
// Configure IP clock enable
// ENUMs:
// CLK_SET                  Set IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENSET0_GPIO                                       0x00000001U
#define CLKCTL_CLKENSET0_GPIO_M                                     0x00000001U
#define CLKCTL_CLKENSET0_GPIO_S                                              0U
#define CLKCTL_CLKENSET0_GPIO_CLK_SET                               0x00000001U
#define CLKCTL_CLKENSET0_GPIO_CLK_UNCHGD                            0x00000000U

//*****************************************************************************
//
// Register: CLKCTL_O_CLKENSET1
//
//*****************************************************************************
//*****************************************************************************
//
// Register: CLKCTL_O_CLKENCLR0
//
//*****************************************************************************
// Field:    [30] LGPT3
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LGPT3                                      0x40000000U
#define CLKCTL_CLKENCLR0_LGPT3_M                                    0x40000000U
#define CLKCTL_CLKENCLR0_LGPT3_S                                            30U
#define CLKCTL_CLKENCLR0_LGPT3_CLK_CLR                              0x40000000U
#define CLKCTL_CLKENCLR0_LGPT3_CLK_UNCHGD                           0x00000000U

// Field:    [29] LGPT2
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LGPT2                                      0x20000000U
#define CLKCTL_CLKENCLR0_LGPT2_M                                    0x20000000U
#define CLKCTL_CLKENCLR0_LGPT2_S                                            29U
#define CLKCTL_CLKENCLR0_LGPT2_CLK_CLR                              0x20000000U
#define CLKCTL_CLKENCLR0_LGPT2_CLK_UNCHGD                           0x00000000U

// Field:    [28] LGPT1
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LGPT1                                      0x10000000U
#define CLKCTL_CLKENCLR0_LGPT1_M                                    0x10000000U
#define CLKCTL_CLKENCLR0_LGPT1_S                                            28U
#define CLKCTL_CLKENCLR0_LGPT1_CLK_CLR                              0x10000000U
#define CLKCTL_CLKENCLR0_LGPT1_CLK_UNCHGD                           0x00000000U

// Field:    [27] LGPT0
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LGPT0                                      0x08000000U
#define CLKCTL_CLKENCLR0_LGPT0_M                                    0x08000000U
#define CLKCTL_CLKENCLR0_LGPT0_S                                            27U
#define CLKCTL_CLKENCLR0_LGPT0_CLK_CLR                              0x08000000U
#define CLKCTL_CLKENCLR0_LGPT0_CLK_UNCHGD                           0x00000000U

// Field:    [17] DMA
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_DMA                                        0x00020000U
#define CLKCTL_CLKENCLR0_DMA_M                                      0x00020000U
#define CLKCTL_CLKENCLR0_DMA_S                                              17U
#define CLKCTL_CLKENCLR0_DMA_CLK_CLR                                0x00020000U
#define CLKCTL_CLKENCLR0_DMA_CLK_UNCHGD                             0x00000000U

// Field:    [16] LAES
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LAES                                       0x00010000U
#define CLKCTL_CLKENCLR0_LAES_M                                     0x00010000U
#define CLKCTL_CLKENCLR0_LAES_S                                             16U
#define CLKCTL_CLKENCLR0_LAES_CLK_CLR                               0x00010000U
#define CLKCTL_CLKENCLR0_LAES_CLK_UNCHGD                            0x00000000U

// Field:    [14] ADC0
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_ADC0                                       0x00004000U
#define CLKCTL_CLKENCLR0_ADC0_M                                     0x00004000U
#define CLKCTL_CLKENCLR0_ADC0_S                                             14U
#define CLKCTL_CLKENCLR0_ADC0_CLK_CLR                               0x00004000U
#define CLKCTL_CLKENCLR0_ADC0_CLK_UNCHGD                            0x00000000U

// Field:    [10] SPI0
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_SPI0                                       0x00000400U
#define CLKCTL_CLKENCLR0_SPI0_M                                     0x00000400U
#define CLKCTL_CLKENCLR0_SPI0_S                                             10U
#define CLKCTL_CLKENCLR0_SPI0_CLK_CLR                               0x00000400U
#define CLKCTL_CLKENCLR0_SPI0_CLK_UNCHGD                            0x00000000U

// Field:     [6] I2C0
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_I2C0                                       0x00000040U
#define CLKCTL_CLKENCLR0_I2C0_M                                     0x00000040U
#define CLKCTL_CLKENCLR0_I2C0_S                                              6U
#define CLKCTL_CLKENCLR0_I2C0_CLK_CLR                               0x00000040U
#define CLKCTL_CLKENCLR0_I2C0_CLK_UNCHGD                            0x00000000U

// Field:     [2] UART0
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_UART0                                      0x00000004U
#define CLKCTL_CLKENCLR0_UART0_M                                    0x00000004U
#define CLKCTL_CLKENCLR0_UART0_S                                             2U
#define CLKCTL_CLKENCLR0_UART0_CLK_CLR                              0x00000004U
#define CLKCTL_CLKENCLR0_UART0_CLK_UNCHGD                           0x00000000U

// Field:     [1] LRFD
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_LRFD                                       0x00000002U
#define CLKCTL_CLKENCLR0_LRFD_M                                     0x00000002U
#define CLKCTL_CLKENCLR0_LRFD_S                                              1U
#define CLKCTL_CLKENCLR0_LRFD_CLK_CLR                               0x00000002U
#define CLKCTL_CLKENCLR0_LRFD_CLK_UNCHGD                            0x00000000U

// Field:     [0] GPIO
//
// Configure IP clock enable
// ENUMs:
// CLK_CLR                  Clear IP clock enable
// CLK_UNCHGD               IP clock enable is unchanged
#define CLKCTL_CLKENCLR0_GPIO                                       0x00000001U
#define CLKCTL_CLKENCLR0_GPIO_M                                     0x00000001U
#define CLKCTL_CLKENCLR0_GPIO_S                                              0U
#define CLKCTL_CLKENCLR0_GPIO_CLK_CLR                               0x00000001U
#define CLKCTL_CLKENCLR0_GPIO_CLK_UNCHGD                            0x00000000U

//*****************************************************************************
//
// Register: CLKCTL_O_CLKENCLR1
//
//*****************************************************************************
//*****************************************************************************
//
// Register: CLKCTL_O_STBYPTR
//
//*****************************************************************************
// Field:  [31:0] VAL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// MIN                      Internal. Only to be used through TI provided API.
#define CLKCTL_STBYPTR_VAL_W                                                32U
#define CLKCTL_STBYPTR_VAL_M                                        0xFFFFFFFFU
#define CLKCTL_STBYPTR_VAL_S                                                 0U
#define CLKCTL_STBYPTR_VAL_MIN                                      0x00000000U

//*****************************************************************************
//
// Register: CLKCTL_O_IDLECFG
//
//*****************************************************************************
// Field:     [0] MODE
//
// Flash LDO configuration in SLEEP/IDLE mode.
// ENUMs:
// LDO_OFF                  Flash LDO is off in SLEEP/IDLE mode.
//                          Decreases power
//                          consumption in SLEEP/IDLE mode, but gives
//                          longer wake up time.
//
//                          Note: NVM clock is turned
//                          off independent of DMA status. Therefore SW
//                          must ensure that DMA never access NVM in this
//                          mode.
// LDO_ON                   Flash LDO is on in SLEEP/IDLE mode.
//                          Gives fast wake up time
//                          from SLEEP/IDLE mode, but increased power
//                          consumption.
#define CLKCTL_IDLECFG_MODE                                         0x00000001U
#define CLKCTL_IDLECFG_MODE_M                                       0x00000001U
#define CLKCTL_IDLECFG_MODE_S                                                0U
#define CLKCTL_IDLECFG_MODE_LDO_OFF                                 0x00000001U
#define CLKCTL_IDLECFG_MODE_LDO_ON                                  0x00000000U


#endif // __CLKCTL__
